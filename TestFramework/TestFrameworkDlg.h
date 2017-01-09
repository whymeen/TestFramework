// TestFrameworkDlg.h : 헤더 파일
//

#pragma once

#include "afxwin.h"
#include "ListenSocket.h"
#include "vector"
#include "ObjectMananger.h"
#include "TCPFunc.h"

struct _WidthLengthHeight
{
	//LPCTSTR modelName;
	char  modelName[20];
	float width;
	float length;
	float height;

	int   nfx;
	float fx_x[2];
	float fx_y[2];
	float fx_z[2];
};

struct _ModelLength
{
	int type;
	std::vector<_WidthLengthHeight> m_modelLength;
};
// CTestFrameworkDlg 대화 상자
class CTestFrameworkDlg : public CDialogEx
{
	// 생성입니다.
public:
	CTestFrameworkDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTFRAMEWORK_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	TCPFunc	m_TCPFunc;
	afx_msg void OnBnClickedButtonAddObject();
	CEdit m_cvEditObjectID;
	CEdit m_cvEditTorpedoID;
	CComboBox m_cvCbxObjectType;
	CComboBox m_cvCbxStatus;
	CComboBox m_cvCbxIFF;
	CComboBox m_cvCbxImgType;
	CComboBox m_cvCbxSubObjectList;
	CComboBox m_cvCbxTorpedoType;
	CComboBox m_cvCbxPlatformImgList;
	CComboBox m_cvCbxDecoyType;
	CComboBox m_cvCbxDecoyImgType;
	CComboBox m_cvCbxDecoyList;
	CEdit m_cvEditX;
	CEdit m_cvEditY;
	CEdit m_cvEditZ;
	CEdit m_cvEditH;
	CEdit m_cvEditP;
	CEdit m_cvEditR;
	CEdit m_cvEditDecoyID;
	CListBox m_List;
	CStatic m_cvTxtTubeNum;
	CComboBox m_cvCbxSeaarea;
	CEdit m_cvEditOrgLat;
	CEdit m_cvEditOrgLon;
	CEdit m_cvEditLat;
	CEdit m_cvEditLong;
	CButton m_cvBtnStart;
	CButton m_cvBtnPause;
	CButton m_cvBtnStop;
	CObjectMananger m_pObjectManager;
	std::vector<SUB_OBJECT_INFO>	m_vTorpedoList;
	std::vector<SUB_OBJECT_INFO>	m_vDecoyList;
	std::vector<_ModelLength> m_length;
	afx_msg void OnDestroy();

	afx_msg void OnCbnSelchangeComboType();

	int m_iCurSystemCode;
	int m_iSubmarineID;
	int m_iSurfaceshipID;
	int m_iTorpedoID;
	int m_iDecoyID;

	const int GetCurSubmarineID() { return m_iSubmarineID; }
	const int GetCurSurfaceshipID() { return m_iSurfaceshipID; }
	const int GetCurTorpedoID() { return m_iTorpedoID; }
	const int GetCurDecoyID() { return m_iDecoyID; }

	void SetCurSubmarineID(int id) { m_iSubmarineID = id; }
	void SetCurSurfaceshipID(int id) { m_iSurfaceshipID = id; }
	void SetCurTorpedoID(int id) { m_iTorpedoID = id; }
	void SetCurDecoyID(int id) { m_iDecoyID = id; }

	void readModelData();
	void deleteObject(int objectID);
	void sendSimCtrl(int mode);


	afx_msg void OnCbnSelchangeComboTType();
	afx_msg void OnCbnSelchangeComboDType();
	afx_msg void OnBnClickedButtonAddTorpedo();
	afx_msg void OnBnClickedButtonAddDecoy();

public:
	afx_msg void OnBnClickedButtonDelObject();
	CComboBox m_cvCbxObjectList;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButtonSimStart();
	afx_msg void OnBnClickedButtonSimPause();
	afx_msg void OnBnClickedButtonSimStop();
};
