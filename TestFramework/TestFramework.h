
// TestFramework.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CTestFrameworkApp:
// �� Ŭ������ ������ ���ؼ��� TestFramework.cpp�� �����Ͻʽÿ�.
//

class CTestFrameworkApp : public CWinApp
{
public:
	CTestFrameworkApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CTestFrameworkApp theApp;