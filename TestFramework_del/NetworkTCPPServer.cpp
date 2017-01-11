#include "stdafx.h"
#include "NetworkTCPPServer.h"
#include <windows.h>
#include <process.h>











CNetworkTCPPServer::CNetworkTCPPServer(char *ip , short port)
{
	strcpy(m_ip , ip);
	m_port = port;

	m_end = false;
	m_connected = false;

	m_serverSocket = -1;
	m_clientSocket = -1;

	pMessageFunction = NULL;
	m_pclass = NULL;

	memset(m_receiveData , 0 , MAX_RECEIVE_DATA_SIZE);

	_beginthread(TcpServerThreadProc , 0 , this);
}

CNetworkTCPPServer::~CNetworkTCPPServer(void)
{
	Sleep(2000);
}

void CNetworkTCPPServer::sendData(char *data , int size)
{
	send(m_clientSocket , (char FAR *)data , size , 0);
}

void CNetworkTCPPServer::addCallback(void *callback , void *parent)
{
	pMessageFunction = (TMessageFunction)callback;
	m_pclass = parent;
}

void CNetworkTCPPServer::terminate(void)
{
	m_end = true;

	closesocket(m_clientSocket);
	closesocket(m_serverSocket);
}

bool CNetworkTCPPServer::getConnectionState(void)
{
	return m_connected;
}

void CNetworkTCPPServer::clear(void)
{
	memset(&m_receiveData , 0 , MAX_RECEIVE_DATA_SIZE);
}

void CNetworkTCPPServer::TcpServerThreadProc(void *ch)
{
	CNetworkTCPPServer *network = (CNetworkTCPPServer *)ch;

	int recvValue = -1;

	while(!(network->m_end))
	{
		if(recvValue == -1)
		{
			network->m_connected = false;

			if(network->m_serverSocket != -1)
				closesocket(network->m_serverSocket);
			if(network->m_clientSocket != -1)
				closesocket(network->m_clientSocket);

			while(true)
			{				
				if(TryServerConnect(ch) == 1)
				{
					network->m_connected = true;
					break;
				}

				Sleep(50);
			}
		}

		recvValue = recv(network->m_clientSocket , (char FAR *)&(network->m_receiveData) , MAX_RECEIVE_DATA_SIZE , 0);

		TRACE("%d\n" , recvValue);
		
		if(recvValue > 0)
			if(network->pMessageFunction)
				network->pMessageFunction(network->m_receiveData , recvValue , network->m_pclass);

		memset(&network->m_receiveData , 0 , MAX_RECEIVE_DATA_SIZE);
	}

	_endthread();
}

int CNetworkTCPPServer::TryServerConnect(void *ch)
{
	CNetworkTCPPServer *network = (CNetworkTCPPServer *)ch;


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
	network->m_serverAddr.sin_addr.s_addr =inet_addr(network->m_ip);
	memset(network->m_serverAddr.sin_zero,0,8);
	network->m_serverAddr.sin_port = htons(network->m_port);

	network->m_serverSocket = socket(AF_INET , SOCK_STREAM , 0);	   
	if(network->m_serverSocket == INVALID_SOCKET)
	    return 0;

	err = bind(network->m_serverSocket, (struct sockaddr *)&network->m_serverAddr, network->m_serverLen);
	if (err == SOCKET_ERROR)
	    return 0;

	err = listen(network->m_serverSocket , SOMAXCONN);
	if (err == SOCKET_ERROR)
		return 0;

	network->m_clientLen = sizeof(network->m_clientAddr);
	if ((network->m_clientSocket = accept(network->m_serverSocket , (struct sockaddr *)&network->m_clientAddr , &network->m_clientLen)) == INVALID_SOCKET)
		return 0;

	

	return 1;
}
