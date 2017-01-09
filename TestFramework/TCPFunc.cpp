#include "stdafx.h"
#include "TCPFunc.h"


TCPFunc::TCPFunc()
{
	m_iCurSystemCode = 1;
}


TCPFunc::~TCPFunc()
{
}

void TCPFunc::initNetwork()
{
	readConfigure();
	char iip[20];
	sprintf(iip, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);

	// 네트워크 연결 생성
	///////////////////////////////////////////////////////////////////	
	//m_pTCPServer = new CNetworkTCPServer(iip , port1);	
	m_pTCPServer = new CNetworkTCPServer("127.0.0.1", 5100);
	m_pTCPServer->addCallback(getEventMsg, this);
	//////////////////////////////////////////////////////////////////

	// 메시지 관련 버퍼 초기화
	initMsgBuf();
}

void TCPFunc::initMsgBuf()
{
	// 메시지 관련 버퍼 초기화
	////////////////////////////////////////////////////////////////////////////////
	m_ichBufIndex = 0;		// 받은정보중 데이터가 있는부분
	m_ipreRcvSize = 0;		// 다음 패킷 받을때 붙여야 할 부분

	memset(&m_chBuf, 0x00, NETWORK_MAXSIZE);	// 메시지 버퍼 초기화
												////////////////////////////////////////////////////////////////////////////////
}

void TCPFunc::SendEventData(char* packetData, int packetDataSize)
{
	char sendBuf[NETWORK_MAXSIZE];

	ICD_HEADER header;
	int headsize = sizeof(ICD_HEADER);
	memset(&header, 0x00, sizeof(ICD_HEADER));
	int totsize = headsize + packetDataSize;

	header.H_Timestamp = GetTimeStamp();
	header.H_Length = totsize / 4;
	header.H_Sender_Equip_Code = m_iCurSystemCode;

	//header.C_TImeHour = 7;
	//header.C_TImeMinute = 12;
	//header.C_TImeSec = 22;
	//header.C_TImeMSec = 111;

	memcpy(&sendBuf, (char*)&header, headsize);						// 헤더 붙이기 
	memcpy(&sendBuf[headsize], (char*)packetData, packetDataSize);		// 데이터 불이기

																		//	dhPrint("packet size => H:%d, D:%d => total:%d, time:%d\n", headsize, packetDataSize, totsize, sizeof(header.H_Timestamp));

	if (m_pTCPServer->getConnectionState() == true)
	{
		m_pTCPServer->sendData(sendBuf, totsize);
	}
	else
	{
		TRACE("not connect a TCP/IP, then not sending data!!\n");
	}
}

void TCPFunc::SendUpdateData(char* packetData, int packetDataSize)
{
	char sendBuf[NETWORK_MAXSIZE];

	ICD_HEADER header;
	memset(&header, 0x00, sizeof(ICD_HEADER));
	int headsize = sizeof(ICD_HEADER);
	int totsize = headsize + packetDataSize;

//	header.C_TimeStamp = GetTimeStamp();
//	header.C_Length = totsize / 4;
//	header.C_SenderCode = m_iCurSystemCode;

//	header.C_TImeHour = 7;
//	header.C_TImeMinute = 12;
//	header.C_TImeSec = 22;
//	header.C_TImeMSec = 111;

	memcpy(&sendBuf, (char*)&header, headsize);						// 헤더 붙이기 
	memcpy(&sendBuf[headsize], (char*)packetData, packetDataSize);		// 데이터 불이기

																		//	dhPrint("packet size => H:%d, D:%d => total:%d, time:%d\n", headsize, packetDataSize, totsize, sizeof(header.H_Timestamp));

	if (m_pTCPServer->getConnectionState() == true)
	{
		m_pTCPServer->sendData(sendBuf, totsize);
	}
	else
	{
		TRACE("not connect a TCP/IP, then not sending data!!\n");
	}
}

void TCPFunc::getEventMsg(char *msg, void *param, int dataSize)
{
	TCPFunc *pMF = (TCPFunc *)param;

	int bufIndex = 0;
	double dTimeStamp = 0;
	int iLength = 0;
	int type = -1;
	int length = -1;

	//////////////////////////////////////////////////////////////////////////
	// 임시 버퍼에 저장
	memcpy(&pMF->m_chBuf[pMF->m_ichBufIndex], &msg[bufIndex], dataSize);
	dataSize += pMF->m_ichBufIndex;
	//////////////////////////////////////////////////////////////////////////

	if (pMF->m_ichBufIndex != 0)
	{
		pMF->m_ichBufIndex = 0;
		pMF->m_ipreRcvSize = 0;
	}

	while ((bufIndex + 1) < dataSize)
	{

		ICD_HEADER header;

		memcpy(&header, &msg[bufIndex], sizeof(ICD_HEADER));
//		dTimeStamp = header.C_TimeStamp;
		iLength = header.H_Length;

		// 패킷 분석 완료여부 판단
		/////////////////////////////////////////////////////////////
		if (iLength > (dataSize - bufIndex))
		{
			pMF->initMsgBuf();
			pMF->m_ichBufIndex = dataSize - bufIndex;		// 받은정보중 데이터가 있는부분
			pMF->m_ipreRcvSize = iLength - pMF->m_ichBufIndex;	// 다음 패킷 받을때 붙여야 할 부분
			memcpy(&pMF->m_chBuf[0], &msg[bufIndex], pMF->m_ichBufIndex);

			//TRACE("receive event message 신호이어 붙이기 : m_ichBufIndex[%d] m_ipreRcvSize[%d]\n", m_ichBufIndex, m_ipreRcvSize);

			break;
		}
		/////////////////////////////////////////////////////////////

		bufIndex += sizeof(ICD_HEADER);

		unsigned char c, l;
		memcpy(&c, &msg[bufIndex], 1);
		memcpy(&l, &msg[bufIndex + 1], 1);

		type = c;
		length = l;

		TRACE("evenet message 신호 수신 type:[%#x], length:[%d] realSize[%d]\n", type, length, dataSize);

		switch (type)
		{
		case MSG_CODE_EVENT_SIMULATION_CONTROL_0x11:

			bufIndex += sizeof(EVENT_SIMULATION_CONTROL);
			break;
		case MSG_CODE_EVENT_OBJECT_SETUP_0x12:

			bufIndex += sizeof(EVENT_OBJECT_CONTROL);
			break;
		case MSG_CODE_EVENT_TORPEDO_SETUP_0x13:

			bufIndex += sizeof(EVENT_TORPEDO_SETUP);
			break;
		case MSG_CODE_EVENT_DECOY_SETUP_0x14:

			bufIndex += sizeof(EVENT_DECOY_SETUP);
			break;
		default:

			pMF->initMsgBuf();
			TRACE("unknown message 신호 수신 type:[%#x], length:[%d]\n", type, length);
			break;
		}
	}
}

void TCPFunc::close()
{
	if (m_pTCPClient)
	{
		delete m_pTCPClient;
	}
	m_pTCPClient = NULL;

	if (m_pTCPServer)
	{
		delete m_pTCPServer;
	}
	m_pTCPServer = NULL;
}

void TCPFunc::readConfigure(void)
{
	FILE *fp = fopen("configb.cfg", "r");
	if (fp)
	{
		char str[255];
		int a, b, c, d;
		fscanf(fp, "%s %d %d %d %d", str, &a, &b, &c, &d);
		ip[0] = (unsigned char)a;
		ip[1] = (unsigned char)b;
		ip[2] = (unsigned char)c;
		ip[3] = (unsigned char)d;

		fscanf(fp, "%s %d", str, &a);
		port1 = a;
		fscanf(fp, "%s %d", str, &a);
		port2 = a;

		fclose(fp);
	}
}

const double TCPFunc::GetTimeStamp()
{
	SYSTEMTIME sysTime;
	//GetSystemTime(&sysTime);		// 국제시간			[8/5/2010 boxface]
	GetLocalTime(&sysTime);			// 현지 지역시간	[8/5/2010 boxface]
	CString csTimeStamp;
	csTimeStamp.Format("%04d%02d%02d%02d%02d%02d%03d",
		sysTime.wYear, sysTime.wMonth, sysTime.wDay,
		sysTime.wHour, sysTime.wMinute, sysTime.wSecond,
		sysTime.wMilliseconds);

	return atof(csTimeStamp);
}