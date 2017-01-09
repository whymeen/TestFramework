#include "dhTCP/networktcpclient.h"
#include "dhTCP/NetworkTCPServer.h"

#include <afxmt.h>
#include "afxwin.h"

//#define NETWORK_MAXSIZE			50000
#define FRAME_30HZ				33

#pragma once
class TCPFunc
{
public:
	TCPFunc();
	~TCPFunc();

public:
	static TCPFunc*	m_instance;

	CNetworkTCPClient *m_pTCPClient;
	CNetworkTCPServer *m_pTCPServer;

	char m_chBuf[NETWORK_MAXSIZE + 10000];
	int m_ichBufIndex;
	int m_ipreRcvSize;

	static TCPFunc* getinstance() { return m_instance; }

	void initNetwork();		// 네트워크 초기화
	void initMsgBuf();		// 네트워크 메시지 fool 정보 초기화

	void SendEventData(char* packetData, int packetDataSize);
	void SendUpdateData(char* packetData, int packetDataSize);

	static void getUpdateMsg(char *msg, void *param);	// 네트워크정보 수신 함수
	static void getEventMsg(char *msg, void *param, int dataSize);	// 네트워크정보 수신 함수

	void close();
	void readConfigure(void);

	int m_iCurSystemCode;
	unsigned int m_iTimeStamp;

	// read config value
	unsigned char ip[4];
	unsigned short port1, port2;

	const double GetTimeStamp();

};


