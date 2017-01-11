// TestFrameworkDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "TestFramework.h"
#include "TestFrameworkDlg.h"
#include "afxdialogex.h"
#include "objectBase.h"
#include <fstream>
#include <time.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CTestFrameworkDlg ��ȭ ����

CTestFrameworkDlg::CTestFrameworkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TESTFRAMEWORK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestFrameworkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_EDIT_ID, m_cvEditObjectID);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cvCbxObjectType);
	DDX_Control(pDX, IDC_EDIT_X, m_cvEditX);
	DDX_Control(pDX, IDC_EDIT_Y, m_cvEditY);
	DDX_Control(pDX, IDC_EDIT_Z, m_cvEditZ);
	DDX_Control(pDX, IDC_EDIT_H, m_cvEditH);
	DDX_Control(pDX, IDC_EDIT_P, m_cvEditP);
	DDX_Control(pDX, IDC_EDIT_R, m_cvEditR);
	DDX_Control(pDX, IDC_COMBO2, m_cvCbxStatus);
	DDX_Control(pDX, IDC_COMBO_IFF, m_cvCbxIFF);
	DDX_Control(pDX, IDC_EDIT_TORPEDOID, m_cvEditTorpedoID);
	DDX_Control(pDX, IDC_COMBO_T_IMAGETYPE, m_cvCbxImgType);
	DDX_Control(pDX, IDC_COMBO_TORPEDOLIST, m_cvCbxSubObjectList);
	DDX_Control(pDX, IDC_COMBO_T_TYPE, m_cvCbxTorpedoType);
	DDX_Control(pDX, IDC_COMBO_IMAGETYPE, m_cvCbxPlatformImgList);
	DDX_Control(pDX, IDC_COMBO_D_TYPE, m_cvCbxDecoyType);
	DDX_Control(pDX, IDC_COMBO_D_IMAGETYPE, m_cvCbxDecoyImgType);
	DDX_Control(pDX, IDC_COMBO_DECOYLIST, m_cvCbxDecoyList);
	DDX_Control(pDX, IDC_EDIT_DECOYID, m_cvEditDecoyID);
	DDX_Control(pDX, IDC_STATIC_TUBE_NUM, m_cvTxtTubeNum);
	DDX_Control(pDX, IDC_COMBO_SEA_AREA, m_cvCbxSeaarea);
	DDX_Control(pDX, IDC_EDIT_ORG_LAT, m_cvEditOrgLat);
	DDX_Control(pDX, IDC_EDIT_ORG_LON, m_cvEditOrgLon);
	DDX_Control(pDX, IDC_EDIT_LAT, m_cvEditLat);
	DDX_Control(pDX, IDC_EDIT_LONG, m_cvEditLong);
	DDX_Control(pDX, IDC_COMBO_LIST_OBJECT, m_cvCbxObjectList);
	DDX_Control(pDX, IDC_BUTTON_SIM_START, m_cvBtnStart);
	DDX_Control(pDX, IDC_BUTTON_SIM_PAUSE, m_cvBtnPause);
	DDX_Control(pDX, IDC_BUTTON_SIM_STOP, m_cvBtnStop);
}

BEGIN_MESSAGE_MAP(CTestFrameworkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD_OBJECT, &CTestFrameworkDlg::OnBnClickedButtonAddObject)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &CTestFrameworkDlg::OnCbnSelchangeComboType)
	ON_CBN_SELCHANGE(IDC_COMBO_T_TYPE, &CTestFrameworkDlg::OnCbnSelchangeComboTType)
	ON_CBN_SELCHANGE(IDC_COMBO_D_TYPE, &CTestFrameworkDlg::OnCbnSelchangeComboDType)
	ON_BN_CLICKED(IDC_BUTTON_ADD_TORPEDO, &CTestFrameworkDlg::OnBnClickedButtonAddTorpedo)
	ON_BN_CLICKED(IDC_BUTTON_ADD_DECOY, &CTestFrameworkDlg::OnBnClickedButtonAddDecoy)
	ON_BN_CLICKED(IDC_BUTTON_DEL_OBJECT, &CTestFrameworkDlg::OnBnClickedButtonDelObject)
	ON_BN_CLICKED(IDC_BUTTON_SIM_START, &CTestFrameworkDlg::OnBnClickedButtonSimStart)
	ON_BN_CLICKED(IDC_BUTTON_SIM_PAUSE, &CTestFrameworkDlg::OnBnClickedButtonSimPause)
	ON_BN_CLICKED(IDC_BUTTON_SIM_STOP, &CTestFrameworkDlg::OnBnClickedButtonSimStop)
END_MESSAGE_MAP()

// CTestFrameworkDlg �޽��� ó����

BOOL CTestFrameworkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	//�� ������ �б� ����
	readModelData();

	m_cvCbxObjectType.InsertString(OBJECT_TYPE_INIT, _T("�ʱⰪ"));
	m_cvCbxObjectType.InsertString(OBJECT_TYPE_SURFACESHIP, _T("������"));
	m_cvCbxObjectType.InsertString(OBJECT_TYPE_SUBMARINE, _T("�����"));
	//m_cvCbxObjectType.InsertString(OBJECT_TYPE_TORPEDO, "���");
	//m_cvCbxObjectType.InsertString(OBJECT_TYPE_DECOY, "�⸸��");
	//m_cvCbxObjectType.SetCurSel(OBJECT_TYPE_SUBMARINE);
	m_cvEditObjectID.SetReadOnly(true);

	m_cvCbxStatus.InsertString(OBJECT_STATUS_STANDBY, "���");
	m_cvCbxStatus.InsertString(OBJECT_STATUS_ENABLE, "���(�߻�)");
	m_cvCbxStatus.InsertString(OBJECT_STATUS_DISABLE, "����(�ı�)");
	m_cvCbxStatus.SetCurSel(OBJECT_STATUS_STANDBY);

	m_cvCbxIFF.InsertString(IFF_FRIEND, "�Ʊ�");
	m_cvCbxIFF.InsertString(IFF_ENEMY, "����");
	m_cvCbxIFF.SetCurSel(IFF_FRIEND);

	m_cvCbxTorpedoType.InsertString(0, "�߾��");
	m_cvCbxTorpedoType.InsertString(1, "����");

	m_cvCbxDecoyType.InsertString(0, "�����");

	m_iSubmarineID = 0;
	m_iSurfaceshipID = 0;
	m_iTorpedoID = 0;
	m_iDecoyID = 0;

	m_cvEditX.SetWindowText(_T("0"));
	m_cvEditY.SetWindowText(_T("0"));
	m_cvEditZ.SetWindowText(_T("0"));
	m_cvEditH.SetWindowText(_T("0"));
	m_cvEditP.SetWindowText(_T("0"));
	m_cvEditR.SetWindowText(_T("0"));
	m_cvEditOrgLat.SetWindowText(_T("0"));
	m_cvEditOrgLon.SetWindowText(_T("0"));
	m_cvEditLat.SetWindowText(_T("0"));
	m_cvEditLong.SetWindowText(_T("0"));
	m_cvEditTorpedoID.SetWindowText(_T("3000"));
	m_cvEditDecoyID.SetWindowText(_T("4000"));


	///////////////////////////////���� �ʱ�ȭ
	m_TCPFunc.m_pTCPServer = NULL;
	m_TCPFunc.m_pTCPClient = NULL;

	m_TCPFunc.initNetwork();
	m_TCPFunc.initMsgBuf();

	//////////////////////////////////////////
	//�ùķ��̼� ��ư �ʱ�ȭ
	m_cvBtnStart.EnableWindow(true);
	m_cvBtnPause.EnableWindow(false);
	m_cvBtnStop.EnableWindow(false);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CTestFrameworkDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CTestFrameworkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CTestFrameworkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestFrameworkDlg::OnBnClickedButtonAddObject()
{
	CString cstmp;

	int objectID, type, imageType, iIFF;
	double x, y, z, h, p, r, latitude, longitude;

	int i, torpedoNo, decoyNo;
	objectID = 0;

	m_cvEditObjectID.GetWindowText(cstmp);
	m_cvCbxObjectList.AddString(cstmp);    // ��ü ���� ��Ͽ� �߰� 
	objectID = _ttoi(cstmp);
	if (objectID > 2000 && objectID < 3001)
	{
		m_cvCbxStatus.SetCurSel(OBJECT_STATUS_STANDBY);
	}
	else
	{
		m_cvCbxStatus.SetCurSel(OBJECT_STATUS_ENABLE);
	}

	if (objectID == 0)
	{
		return;
	}

	if (m_pObjectManager.checkObjectID(objectID) == true)
	{
		AfxMessageBox("ID[%d] �� ��ü�� �̹� �����մϴ�. !!\n �ٸ� ID�� ����ϼ���.", objectID);
		m_cvEditObjectID.SetWindowText(_T(""));
		return;
	}

	type = m_cvCbxObjectType.GetCurSel();
	imageType = m_cvCbxPlatformImgList.GetCurSel() + 1;
	iIFF = m_cvCbxIFF.GetCurSel();

	m_cvEditX.GetWindowText(cstmp);
	x = _ttof(cstmp);

	m_cvEditY.GetWindowText(cstmp);
	y = _ttof(cstmp);

	m_cvEditZ.GetWindowText(cstmp);
	z = _ttof(cstmp);

	m_cvEditH.GetWindowText(cstmp);
	h = _ttof(cstmp);

	m_cvEditP.GetWindowText(cstmp);
	p = _ttof(cstmp);

	m_cvEditR.GetWindowText(cstmp);
	r = _ttof(cstmp);

	m_cvEditLat.GetWindowText(cstmp);
	latitude = _ttof(cstmp);

	m_cvEditLong.GetWindowText(cstmp);
	longitude = _ttof(cstmp);

	torpedoNo = m_vTorpedoList.size();
	decoyNo = m_vDecoyList.size();

	// ��ü ���� ��Ʈ��ũ�� ����
	//////////////////////////////////////////////////////////////////////////
	// ��Ʈ��ũ ����

	EVENT_OBJECT_CONTROL sendData;
	memset(&sendData, 0x00, sizeof(EVENT_OBJECT_CONTROL));

	sendData.type = MSG_CODE_EVENT_OBJECT_SETUP_0x12;
	sendData.length = sizeof(EVENT_OBJECT_CONTROL);

	sendData.mode = OBJECT_CTRL_CREATE;
	sendData.objectID = objectID;
	sendData.objectType = type;
	sendData.status = m_cvCbxStatus.GetCurSel();
	sendData.imageType = imageType;
	sendData.IFF = iIFF;

	sendData.x = x;
	sendData.y = y;
	sendData.z = z;
	sendData.u = 0;
	sendData.v = 0;
	sendData.w = 0;
	sendData.h = h;
	sendData.p = p;
	sendData.r = r;


	sendData.latitude = latitude;
	sendData.longitude = longitude;
	sendData.depth = z;
	sendData.range = 0;
	sendData.elevation = 0;
	sendData.bearing = 0;
	sendData.course = 0;
	sendData.pathAngle = 0;
	sendData.speed = 0;

	char sendBuf[NETWORK_MAXSIZE];
	memcpy(&sendBuf, (char*)&sendData, sizeof(EVENT_OBJECT_CONTROL));
	
	m_TCPFunc.SendEventData(sendBuf, sizeof(EVENT_OBJECT_CONTROL));
	// ��ü���� ���� �޸𸮿� ����
	//////////////////////////////////////////////////////////////////////////

	CObjectBase pObject;
	pObject.setObjectID(objectID);
	pObject.setObjectType(type);
	pObject.setObjectStatus(m_cvCbxStatus.GetCurSel());
	pObject.setObjectImageType(imageType);
	pObject.setIFF(iIFF);

	pObject.setTranslate(x, y, z);
	pObject.setRotate(h, p, r);

	// ��� ���� ���� �޸𸮿� ���� 
	for (i = 0; i < torpedoNo; i++)
	{
		STRUCT_TORPEDO_INFO pTorpedo;
		memset(&pTorpedo, 0x00, sizeof(STRUCT_TORPEDO_INFO));

		pTorpedo.iObjectID = m_vTorpedoList[i].objectID;
		pTorpedo.iObjectType = m_vTorpedoList[i].objectType;
		pTorpedo.iImageType = m_vTorpedoList[i].imageType;
		pTorpedo.bFired = false;

		pObject.m_vTorpedoList.push_back(pTorpedo);


		// ��Ʈ��ũ�� �������� ���� 
		//////////////////////////////////////////////////////////////////////////
		
		EVENT_TORPEDO_SETUP sendData;
		memset(&sendData, 0x00, sizeof(EVENT_TORPEDO_SETUP));

		sendData.type = MSG_CODE_EVENT_TORPEDO_SETUP_0x13;
		sendData.length = sizeof(EVENT_TORPEDO_SETUP);

		sendData.objectID = pTorpedo.iObjectID;
		sendData.imageType = pTorpedo.iImageType;
		sendData.parentID = objectID;

		switch (pTorpedo.iObjectType)
		{
		case OBJECT_TYPE_TORPEDO:			sendData.torpedoType = 0;			break;
		default:															    break;
		}

		sendData.tube_Number = i + 1;
		sendData.length = 123;
		sendData.diameter = 2;
		sendData.weight = 1000;
		sendData.maxspeed = 6;
		sendData.dB = 34;
		sendData.maxTime = 1000;
		sendData.maxRange = 100.f;
		sendData.searchPattenMode = 1;
		sendData.ACCMAbility = 2;
		sendData.guidanceMode = 3;
		sendData.strightSearchMode = 1;

		//sendData.x = x;
		//sendData.y = y;
		//sendData.z = z;
		//sendData.h = (Sflt32)h;
		//sendData.p = (Sflt32)p;
		//sendData.r = (Sflt32)r;
		//sendData.latitude = h;
		//sendData.longitude = p;
		//sendData.depth = r;

		char sendBuf[NETWORK_MAXSIZE];
		memcpy(&sendBuf, (char*)&sendData, sizeof(EVENT_TORPEDO_SETUP));
		m_TCPFunc.SendEventData(sendBuf, sizeof(EVENT_TORPEDO_SETUP)); 
		TRACE("%d ��� ���� \n", sendData.objectID);
	
	}
	//////////////////////////////////////////////////////////////////////////
	//�⸸�� ���� ���� �޸𸮿� ����
	for (i = 0; i<decoyNo; i++)
	{
		STRUCT_DECOY_INFO pDecoy;
		memset(&pDecoy, 0x00, sizeof(STRUCT_DECOY_INFO));

		pDecoy.iObjectID = m_vDecoyList[i].objectID;
		pDecoy.iObjectType = m_vDecoyList[i].objectType;
		pDecoy.iImageType = m_vDecoyList[i].imageType;
		pDecoy.bFired = false;

		pObject.m_vDecoyList.push_back(pDecoy);

		// ��Ʈ��ũ�� �������� ����
		//////////////////////////////////////////////////////////////////////////
		EVENT_DECOY_SETUP sendData;
		memset(&sendData, 0x00, sizeof(EVENT_DECOY_SETUP));

		sendData.type = MSG_CODE_EVENT_DECOY_SETUP_0x14;
		sendData.length = sizeof(EVENT_DECOY_SETUP);

		sendData.objectID = pDecoy.iObjectID;
		sendData.imageType = pDecoy.iImageType;
		sendData.parentID = objectID;

		switch (pDecoy.iObjectType)
		{
		case OBJECT_TYPE_DECOY:			sendData.decoyType = 0;			break;
		default:													    break;
		}

		sendData.length = 12;
		sendData.diameter = 2;
		sendData.weight = 500;
		sendData.maxspeed = 10;
		sendData.sounddB = 34.0;
		sendData.workingTime = 1000;
		sendData.reactionDelayTime = 100;
		sendData.workingDelayTime = 200;
		sendData.operationMode = 1;

		char sendBuf[NETWORK_MAXSIZE];
		memcpy(&sendBuf, (char*)&sendData, sizeof(EVENT_DECOY_SETUP));
		m_TCPFunc.SendEventData(sendBuf, sizeof(EVENT_DECOY_SETUP));
		TRACE("%d �⸸�� ����", sendData.objectID);
		//////////////////////////////////////////////////////////////////////////
	}

	m_pObjectManager.addObject(pObject);

	CString strTmp;
	strTmp.Format(_T("%d ��ü�� �����Ǿ����ϴ�."), objectID);
	m_List.AddString(strTmp);
	m_List.SetCurSel(m_List.GetCount() - 1);

	objectID += 1;
	cstmp.Format("%d", objectID);
	m_cvEditObjectID.SetWindowText(cstmp);

	// Ÿ�Ժ� curID �� ���� [7/29/2010 boxface]
	switch (m_cvCbxObjectType.GetCurSel())
	{
	case OBJECT_TYPE_SUBMARINE:
		SetCurSubmarineID(GetCurSubmarineID() + 1);
		break;
	case OBJECT_TYPE_SURFACESHIP:
		SetCurSurfaceshipID(GetCurSurfaceshipID() + 1);
		break;
	case OBJECT_TYPE_TORPEDO:
		SetCurTorpedoID(GetCurTorpedoID() + 1);
		break;
	case OBJECT_TYPE_DECOY:
		SetCurDecoyID(GetCurDecoyID() + 1);
		break;
	default:
		break;
	}

	// GUI �ʱ�ȭ [7/29/2010 boxface]
	m_cvCbxSubObjectList.ResetContent();
	m_cvCbxDecoyList.ResetContent();

	// torpedo vector ���� �ʱ�ȭ [7/29/2010 boxface]
	m_vTorpedoList.clear();
	m_vDecoyList.clear();

	cstmp.Format("TUBE NUM : %d", m_vTorpedoList.size() + 1);
	m_cvTxtTubeNum.SetWindowText(cstmp);
}

void CTestFrameworkDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}

void CTestFrameworkDlg::OnCbnSelchangeComboType()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int objectID;

	switch (m_cvCbxObjectType.GetCurSel())
	{
	case OBJECT_TYPE_SUBMARINE:
		objectID = GetCurSubmarineID() + SUBMARINE_ID;
		break;
	case OBJECT_TYPE_SURFACESHIP:
		objectID = GetCurSurfaceshipID() + SURFACESHIP_ID;
		break;
	case OBJECT_TYPE_TORPEDO:
		objectID = GetCurTorpedoID() + TORPEDO_ID;
		break;
	case OBJECT_TYPE_DECOY:
		objectID = GetCurDecoyID() + DECOY_ID;
		break;
	default:
		objectID = GetCurDecoyID() + 0;
		break;
	}

	CString cstmp;
	cstmp.Format(_T("%d"), objectID);

	m_cvEditObjectID.SetWindowText(cstmp);

	// �̹��� Ÿ������ ������Ʈ [7/30/2010 boxface]
	m_cvCbxPlatformImgList.ResetContent();
	int i, count = m_length.size();
	for (i = 0; i < count; i++)
	{
		if (m_length[i].type != m_cvCbxObjectType.GetCurSel())
		{
			continue;
		}

		int j, count0 = m_length[i].m_modelLength.size();
		for (j = 0; j < count0; j++)
		{
			m_cvCbxPlatformImgList.InsertString(j, (LPCTSTR)m_length[i].m_modelLength[j].modelName);
		}
	}

	m_cvCbxPlatformImgList.SetCurSel(0);
}

void CTestFrameworkDlg::readModelData()
{
	FILE *fp = fopen("ModelLength.dat", "r");
	int count = 0;

	if (fp)
	{
		char str[255];

		while (fscanf(fp, "%s", str) != EOF)
		{
			if (!strcmp(str, "-"))
			{
				_ModelLength length;

				length.type = count + 1;

				m_length.push_back(length);

				fscanf(fp, "%s", str);

				count++;
			}
			else
			{
				_WidthLengthHeight width;

				strcpy(width.modelName, str);

				fscanf(fp, "%f %f %f", &width.width, &width.length, &width.height);
				fscanf(fp, "%d", &width.nfx);
				for (int k = 0; k < width.nfx; k++)
				{
					fscanf(fp, "%f %f %f", &width.fx_x[k], &width.fx_y[k], &width.fx_z[k]);
				}

				m_length[count - 1].m_modelLength.push_back(width);

				//dhPrint("%f %f %f\n" , width.width , width.length , width.height);
			}
		}

		std::vector<_ModelLength>::iterator ModelLengthIt = m_length.begin();
		while (ModelLengthIt != m_length.end())
		{
			std::vector<_WidthLengthHeight>::iterator WidthLengthHeightIt = (*ModelLengthIt).m_modelLength.begin();
			while (WidthLengthHeightIt != (*ModelLengthIt).m_modelLength.end())
			{
				//dhPrint("Model Name : %s %f %f %f %d",
				//	(*WidthLengthHeightIt).modelName,
				//	(*WidthLengthHeightIt).width , (*WidthLengthHeightIt).length , (*WidthLengthHeightIt).height,
				//	(*WidthLengthHeightIt).nfx);
				for (int k = 0; k < (*WidthLengthHeightIt).nfx; k++)
				{
					//dhPrint(" %f %f %f " , (*WidthLengthHeightIt).fx_x[k] , (*WidthLengthHeightIt).fx_y[k] , (*WidthLengthHeightIt).fx_z[k]);
				}
				//dhPrint("\n");

				++WidthLengthHeightIt;
			}
			++ModelLengthIt;
		}

		fclose(fp);
	}
}

void CTestFrameworkDlg::OnCbnSelchangeComboTType()
{
	m_cvCbxImgType.ResetContent();

	int i, count = m_length.size();

	switch (m_cvCbxTorpedoType.GetCurSel())
	{
	case 0:
	{
		for (i = 0; i < count; i++)
		{
			if (m_length[i].type != OBJECT_TYPE_TORPEDO)
			{
				continue;
			}

			int j, count0 = m_length[i].m_modelLength.size();
			for (j = 0; j < count0; j++)
			{
				m_cvCbxImgType.InsertString(j, m_length[i].m_modelLength[j].modelName);
			}
		}
	}
	break;
	case 1:
	{
		for (i = 0; i < count; i++)
		{
			if (m_length[i].type != OBJECT_TYPE_TORPEDO)
			{
				continue;
			}

			int j, count0 = m_length[i].m_modelLength.size();
			for (j = 0; j < count0; j++)
			{
				m_cvCbxImgType.InsertString(j, m_length[i].m_modelLength[j].modelName);
			}
		}
	}
	break;
	default:
		m_cvCbxImgType.ResetContent();
		break;
	}

	m_cvCbxImgType.SetCurSel(0);
}

void CTestFrameworkDlg::OnCbnSelchangeComboDType()
{
	m_cvCbxDecoyImgType.ResetContent();

	int i, count = m_length.size();

	for (i = 0; i < count; i++)
	{
		if (m_length[i].type != OBJECT_TYPE_DECOY)
		{
			continue;
		}

		int j, count0 = m_length[i].m_modelLength.size();
		for (j = 0; j < count0; j++)
		{
			m_cvCbxDecoyImgType.InsertString(j, m_length[i].m_modelLength[j].modelName);
		}
	}

	m_cvCbxDecoyImgType.SetCurSel(0);
}

void CTestFrameworkDlg::OnBnClickedButtonAddTorpedo()
{
	CString cstmp, csTorpedoID;
	int type;

	// GUI���� ������ �� ȹ�� [8/5/2010 boxface]
	if (m_cvCbxTorpedoType.GetCurSel() == 0)
	{
		type = OBJECT_TYPE_TORPEDO;
	}
	else
	{
		type = OBJECT_TYPE_TORPEDO;
	}

	m_cvEditTorpedoID.GetWindowText(csTorpedoID);
	int objectID = atoi(csTorpedoID);
	m_cvEditObjectID.GetWindowText(cstmp);
	int parentID = atoi(cstmp);

	// �޺��ڽ��� ������ ������� �߰� [8/5/2010 boxface]
	m_cvCbxSubObjectList.AddString(csTorpedoID);
	m_cvCbxSubObjectList.SetCurSel(m_cvCbxSubObjectList.GetCount() - 1);

	// ������ ��������� ���� �޸𸮿� ���� [8/5/2010 boxface]
	SUB_OBJECT_INFO pTorpedo;

	pTorpedo.objectID = objectID;
	pTorpedo.objectType = type;
	pTorpedo.imageType = m_cvCbxImgType.GetCurSel() + 1;

	m_vTorpedoList.push_back(pTorpedo);

	// ����� ID�� �������� GUI�� ������Ʈ [8/5/2010 boxface]
	SetCurTorpedoID(GetCurTorpedoID() + 1);

	objectID = GetCurTorpedoID() + 3000;
	cstmp.Format("%d", objectID);
	m_cvEditTorpedoID.SetWindowText(cstmp);

	cstmp.Format("TUBE NUM : %d", m_vTorpedoList.size() + 1);
	m_cvTxtTubeNum.SetWindowText(cstmp);
}

void CTestFrameworkDlg::OnBnClickedButtonAddDecoy()
{
	CString cstmp, csDecoyID;
	int type;

	type = OBJECT_TYPE_DECOY;

	m_cvEditDecoyID.GetWindowText(csDecoyID);
	int objectID = atoi(csDecoyID);
	m_cvEditDecoyID.GetWindowText(cstmp);
	int parentID = atoi(cstmp);

	m_cvCbxDecoyList.AddString(csDecoyID);
	m_cvCbxDecoyList.SetCurSel(m_cvCbxDecoyList.GetCount() - 1);
	m_cvCbxDecoyList.UpdateData();

	SUB_OBJECT_INFO pDecoy;

	pDecoy.objectID = objectID;
	pDecoy.objectType = type;
	pDecoy.imageType = m_cvCbxDecoyImgType.GetCurSel() + 1;

	m_vDecoyList.push_back(pDecoy);

	SetCurDecoyID(GetCurDecoyID() + 1);

	objectID = GetCurDecoyID() + 4000;
	cstmp.Format("%d", objectID);
	m_cvEditDecoyID.SetWindowText(cstmp);
}

void CTestFrameworkDlg::OnBnClickedButtonDelObject()
{
	CString cstmp;
	m_cvCbxObjectList.GetLBText(m_cvCbxObjectList.GetCurSel(), cstmp);

	int objectID = atoi(cstmp);

	cstmp.Format(_T("%d ��ü�� �����Ǿ����ϴ�."), objectID);
	m_List.AddString(cstmp);
	m_List.SetCurSel(m_List.GetCount() - 1);

	// ��ü ���� ��Ʈ��ũ�� ���� [6/15/2010 boxface]
	//////////////////////////////////////////////////////////////////////////
	EVENT_OBJECT_CONTROL sendData;
	memset(&sendData, 0x00, sizeof(EVENT_OBJECT_CONTROL));

	sendData.type = MSG_CODE_EVENT_OBJECT_SETUP_0x12;
	sendData.length = sizeof(EVENT_OBJECT_CONTROL);

	sendData.mode = OBJECT_CTRL_DELETE;
	sendData.objectID = objectID;

	char sendBuf[NETWORK_MAXSIZE];
	memcpy(&sendBuf, (char*)&sendData, sizeof(EVENT_OBJECT_CONTROL));
	m_TCPFunc.SendEventData(sendBuf, sizeof(EVENT_OBJECT_CONTROL));

	// ��ü���� ���� �޸𸮿� ���� [6/15/2010 boxface]
	//////////////////////////////////////////////////////////////////////////
	m_pObjectManager.delObject(objectID);
	deleteObject(objectID);
}

void CTestFrameworkDlg::deleteObject(int objectID)
{
	int curObjectID;
	CString cstmp;

	int count = m_cvCbxObjectList.GetCount();
	for (int i = 0; i< count; i++)
	{
		m_cvCbxObjectList.GetLBText(i, cstmp);
		curObjectID = atoi(cstmp);
		if (objectID == curObjectID)
		{
			m_cvCbxObjectList.DeleteString(i);
			m_cvCbxObjectList.SetCurSel(0);
			return;
		}
	}
}



void CTestFrameworkDlg::OnBnClickedButtonSimStart()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	sendSimCtrl(SIMCTRL_START);

	m_cvBtnStart.EnableWindow(false);
	m_cvBtnPause.EnableWindow(true);
	m_cvBtnStop.EnableWindow(true);
}


void CTestFrameworkDlg::OnBnClickedButtonSimPause()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	sendSimCtrl(SIMCTRL_PAUSE);

	m_cvBtnStart.EnableWindow(true);
	m_cvBtnPause.EnableWindow(false);
	m_cvBtnStop.EnableWindow(true);
}


void CTestFrameworkDlg::OnBnClickedButtonSimStop()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	sendSimCtrl(SIMCTRL_STOP);

	m_cvBtnStart.EnableWindow(true);
	m_cvBtnPause.EnableWindow(false);
	m_cvBtnStop.EnableWindow(false);
}


void CTestFrameworkDlg::sendSimCtrl(int mode)
{
	// �ùķ��̼� ���۸���� ��Ʈ��ũ�� ���� [7/19/2010 boxface]
	//////////////////////////////////////////////////////////////////////////
	EVENT_SIMULATION_CONTROL sendData;
	memset(&sendData, 0x00, sizeof(EVENT_SIMULATION_CONTROL));

	sendData.type = MSG_CODE_EVENT_SIMULATION_CONTROL_0x11;
	sendData.length = sizeof(EVENT_SIMULATION_CONTROL);

	sendData.control_code = mode;

	char sendBuf[NETWORK_MAXSIZE];
	memcpy(&sendBuf, (char*)&sendData, sizeof(EVENT_SIMULATION_CONTROL));
	m_TCPFunc.SendEventData(sendBuf, sizeof(EVENT_SIMULATION_CONTROL));
	//////////////////////////////////////////////////////////////////////////
}