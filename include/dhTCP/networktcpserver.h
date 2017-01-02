#ifndef _NETWORK_TCP_SERVER_H_
#define _NETWORK_TCP_SERVER_H_

#include "dhCommon.h"

#include <winsock.h>


typedef void (WINAPIV * MessageFunction1)(char *message , void *pclass, int rcvDataSize);


class DHTCPLIB_API CNetworkTCPServer {

public:    CNetworkTCPServer(char *ip , short port);
		   ~CNetworkTCPServer(void);

		   void         sendData(const char *data , int size);
		   bool         getConnectionState(void);
		   void         clear(void);
		   void         terminate(void);
		   void	        addCallback(void *callback , void *parent);


protected: 

private:   static void TcpServerThreadProc(void *ch);
		   static int  TryServerConnect(void *ch);




public:    char         m_ip[20];
		   short        m_port;

		   bool         m_end;

	       bool         m_connected;

		   SOCKET       m_serverSocket , m_clientSocket;
		   sockaddr_in  m_serverAddr , m_clientAddr;
		   int          m_serverLen , m_clientLen;


		   char         m_receiveData[MAX_RECEIVE_DATA_SIZE];

protected: MessageFunction1					pMessageFunction;
		   void								*m_pclass;

private:   


};




#endif