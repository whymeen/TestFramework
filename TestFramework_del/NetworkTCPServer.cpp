#include "stdafx.h"
#include "NetworkTCPServer.h"
#include <windows.h>
#include <process.h>

CNetworkTCPServer::CNetworkTCPServer(char *ip , unsigned short port)
{
	strcpy(m_ip , ip);
	m_port = port;
	
	readConfigure();

	m_index = 0;

	m_end = false;
	m_connected = false;

	m_serverSocket = -1;

	pMessageFunction = NULL;
	m_pclass = NULL;

	for(int i = 0;i < 10;i++)
		m_client[i].use = -1;

	memset(m_receiveData , 0 , MAX_RECEIVE_DATA_SIZE);

	_beginthread(TcpServerThreadProc , 0 , this);

	for(int i = 0;i < 10;i++)
	{
		_beginthread(TcpServerReceiveThreadProc , 0 , this);
	}
}

CNetworkTCPServer::~CNetworkTCPServer(void)
{
}

void CNetworkTCPServer::sendData(int index , char *data , int size)
{
	send(m_client[index].m_clientSocket , (char FAR *)data , size , 0);
}

void CNetworkTCPServer::addCallback(void *callback , void *parent)
{
	pMessageFunction = (MessageFunction)callback;
	m_pclass = parent;
}

void CNetworkTCPServer::terminate(void)
{
	m_end = true;

	for(int i = 0;i < 10;i++)
	{
		if(m_client[i].use > 0)
			closesocket(m_client[i].m_clientSocket);
	}

	//closesocket(m_clientSocket);
	closesocket(m_serverSocket);
}

bool CNetworkTCPServer::getConnectionState(void)
{
	return m_connected;
}

void CNetworkTCPServer::clear(void)
{
	memset(&m_receiveData , 0 , MAX_RECEIVE_DATA_SIZE);
}

void CNetworkTCPServer::TcpServerThreadProc(void *ch)
{
	CNetworkTCPServer *network = (CNetworkTCPServer *)ch;

	int recvValue = -1;
	
	TryServerConnect(ch);

	while(!(network->m_end))
	{
		int             err;
		err = listen(network->m_serverSocket , SOMAXCONN);
		if (err == SOCKET_ERROR)
			break;

		_multiTCP tcp;
		tcp.m_clientLen = sizeof(tcp.m_clientAddr);
		if ((tcp.m_clientSocket = accept(network->m_serverSocket , (struct sockaddr *)&tcp.m_clientAddr , &tcp.m_clientLen)) == INVALID_SOCKET)
			break;
		else
		{
			int index = -1;
			for(int i = 1;i < 9;i++)
			{
				if((network->ip[i][0] == tcp.m_clientAddr.sin_addr.S_un.S_un_b.s_b1)
					&& (network->ip[i][1] == tcp.m_clientAddr.sin_addr.S_un.S_un_b.s_b2)
					&& (network->ip[i][2] == tcp.m_clientAddr.sin_addr.S_un.S_un_b.s_b3)
					&& (network->ip[i][3] == tcp.m_clientAddr.sin_addr.S_un.S_un_b.s_b4))
				{
					index = i - 1;
					break;
				}
			}

			if(index >= 0)
			{
				if(network->m_client[index].use == -1)
				{
					network->m_client[index].m_clientSocket = tcp.m_clientSocket;
					network->m_client[index].m_clientLen = tcp.m_clientLen;
					network->m_client[index].m_clientAddr = tcp.m_clientAddr;
					network->m_client[index].use = 1;
					//break;
				}
				else TRACE("기존에 접속된 client 가 있습니다.\n");
			}
		}

		TRACE("new client...\n");
	}

	_endthread();
}

void CNetworkTCPServer::TcpServerReceiveThreadProc(void *ch)
{
	CNetworkTCPServer *network = (CNetworkTCPServer *)ch;

	int ID = network->m_index;
	network->m_index++;


	char buff[100000];

	while(!(network->m_end))
	{
		if(network->m_client[ID].use > 0)
		{
			int size = recv(network->m_client[ID].m_clientSocket , (char FAR *)buff , 100000 , 0);
			if(size <= 0)
			{
				network->m_client[ID].use = -1;
			}
			else
			{
				if(network->pMessageFunction)
					network->pMessageFunction(ID , buff , size , network->m_pclass);
			}
		}

		Sleep(100);
	}

	_endthread();
}

int CNetworkTCPServer::TryServerConnect(void *ch)
{
	CNetworkTCPServer *network = (CNetworkTCPServer *)ch;


	int             err;
	unsigned long   ff=1;
	WORD            wVersionRequested;
	WSADATA         wsaData;	
	wVersionRequested = MAKEWORD(1,1);
	network->m_serverLen = sizeof(network->m_serverAddr);

	err = WSAStartup(wVersionRequested , &wsaData);
	if(LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) !=1)
	    return 0;

	network->m_serverAddr.sin_family = AF_INET;
	network->m_serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);//inet_addr(network->m_ip);
	memset(network->m_serverAddr.sin_zero,0,8);
	network->m_serverAddr.sin_port = htons(network->m_port);

	network->m_serverSocket = socket(AF_INET , SOCK_STREAM , 0);	   
	if(network->m_serverSocket == INVALID_SOCKET)
	    return 0;

	err = bind(network->m_serverSocket, (struct sockaddr *)&network->m_serverAddr, network->m_serverLen);
	if (err == SOCKET_ERROR)
	    return 0;

	return 1;
}

void CNetworkTCPServer::readConfigure(void)
{
	FILE *fp = fopen("config.cfg" , "r");
	if(fp)
	{
		char str[255];
		unsigned short port1 , port2;
		int a , b , c , d;
		fscanf(fp , "%s %d %d %d %d" , str , &a , &b , &c , &d);
		fscanf(fp , "%s %d" , str , &a);
		port1 = a;
		fscanf(fp , "%s %d" , str , &a);
		port2 = a;

		for(int i = 0;i < 9;i++)
		{
			fscanf(fp , "%s %d %d %d %d" , str , &a , &b , &c , &d);
			ip[i][0] = (unsigned char)a;
			ip[i][1] = (unsigned char)b;
			ip[i][2] = (unsigned char)c;
			ip[i][3] = (unsigned char)d;
		}

		fclose(fp);
	}
}
