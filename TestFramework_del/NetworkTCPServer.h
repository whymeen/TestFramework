#ifndef _NETWORK_TCP_SERVER_H_
#define _NETWORK_TCP_SERVER_H_


#include <winsock.h>
#include <iostream>
#include <vector>

#define MAX_RECEIVE_DATA_SIZE 30000

typedef void (WINAPIV * MessageFunction)(int ID , char *message , int size , void *pclass);



struct _multiTCP {
	int use;
	SOCKET      m_clientSocket;
	sockaddr_in m_clientAddr;
	int         m_clientLen;
};



class CNetworkTCPServer {

public:    CNetworkTCPServer(char *ip , unsigned short port);
		   ~CNetworkTCPServer(void);

		   void         sendData(int index , char *data , int size);
		   bool         getConnectionState(void);
		   void         clear(void);
		   void         terminate(void);
		   void	        addCallback(void *callback , void *parent);


protected: 

private:   static void TcpServerThreadProc(void *ch);
		   static void TcpServerReceiveThreadProc(void *ch);
		   static int  TryServerConnect(void *ch);
		   void readConfigure(void);




public:    char         m_ip[20];
		   unsigned short        m_port;

		   int          m_index;

		   bool         m_end;

	       bool         m_connected;

		   SOCKET       m_serverSocket;
		   sockaddr_in  m_serverAddr;
		   int          m_serverLen;

		   _multiTCP    m_client[10];

		   unsigned char ip[9][4];


		   char         m_receiveData[MAX_RECEIVE_DATA_SIZE];

protected: MessageFunction					pMessageFunction;
		   void								*m_pclass;

private:   


};




#endif