#ifndef _NETWORK_TCP_CLIENT_H_
#define _NETWORK_TCP_CLIENT_H_

#include "dhCommon.h"

#include <winsock2.h>


typedef void (WINAPIV * MessageFunction1)(char *message , void *pclass, int rcvDataSize);


class DHTCPLIB_API CNetworkTCPClient {

public:    CNetworkTCPClient(char *ip , short port);
		   ~CNetworkTCPClient(void);

		   void         sendData(char *data , int size);
		   bool         getConnectionState(void);
		   void         clear(void);
		   void         terminate(void);

		   void	        addCallback(void *callback , void *parent);


protected: static void  TcpClientThreadProc(void *ch);
		   static int   TryClientConnect(void *ch);

private:   


public:    char         m_ip[20];
		   short        m_port;

		   bool         m_end;

	       bool         m_connected;

		   SOCKET       m_clientSocket;
		   sockaddr_in  m_clientAddr;
		   int          m_clientLen;


		   char         m_receiveData[MAX_RECEIVE_DATA_SIZE];


protected: MessageFunction1					pMessageFunction;
		   void								*m_pclass;

private:   

};


#endif