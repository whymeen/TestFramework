// DebugConsole.cpp: implementation of the CDebugConsole class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DebugConsole.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDebugConsole::CDebugConsole()
{
	AllocConsole();
	m_hOut = GetStdHandle(STD_OUTPUT_HANDLE);
}

CDebugConsole::~CDebugConsole()
{
	FreeConsole();
}

void CDebugConsole::print(TCHAR *tszMsg, ...)
{
    TCHAR strBuffer[512]; 

    va_list args; 
    va_start(args, tszMsg); 
	_vsntprintf( strBuffer, 512, tszMsg, args ); 
    va_end(args); 

	DWORD dwWrite;
	WriteConsole(m_hOut, strBuffer, strlen(strBuffer), &dwWrite, NULL);
}
