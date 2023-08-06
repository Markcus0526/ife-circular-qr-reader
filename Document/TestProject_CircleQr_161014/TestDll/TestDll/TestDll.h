// TestDll.h : main header file for the TestDll DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "Engine/FindRecogDigit.h"

// CTestDllApp
// See TestDll.cpp for the implementation of this class
//

class CTestDllApp : public CWinApp
{
public:
	CTestDllApp();
	CFindRecogDigit digit;
// Overrides
public:
	virtual BOOL InitInstance();
	BOOL	LoadResData(void* pObject,UINT nId,TCHAR* dicName);

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};
