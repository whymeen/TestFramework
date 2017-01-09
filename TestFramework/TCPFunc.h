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

	void initNetwork();		// ��Ʈ��ũ �ʱ�ȭ
	void initMsgBuf();		// ��Ʈ��ũ �޽��� fool ���� �ʱ�ȭ

	void SendEventData(char* packetData, int packetDataSize);
	void SendUpdateData(char* packetData, int packetDataSize);

	static void getUpdateMsg(char *msg, void *param);	// ��Ʈ��ũ���� ���� �Լ�
	static void getEventMsg(char *msg, void *param, int dataSize);	// ��Ʈ��ũ���� ���� �Լ�

	void close();
	void readConfigure(void);

	int m_iCurSystemCode;
	unsigned int m_iTimeStamp;

	// read config value
	unsigned char ip[4];
	unsigned short port1, port2;

	const double GetTimeStamp();

};


