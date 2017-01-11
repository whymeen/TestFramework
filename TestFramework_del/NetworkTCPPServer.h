#ifndef _NETWORK_TCPP_SERVER_H_
#define _NETWORK_TCPP_SERVER_H_


#include <winsock.h>

#define MAX_RECEIVE_DATA_SIZE 30000

typedef void (WINAPIV * TMessageFunction)(char *message , int size , void *pclass);




class CNetworkTCPPServer {

public:    CNetworkTCPPServer(char *ip , short port);
		   ~CNetworkTCPPServer(void);

		   void         sendData(char *data , int size);
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

protected: TMessageFunction					pMessageFunction;
		   void								*m_pclass;

private:   


};




#endif