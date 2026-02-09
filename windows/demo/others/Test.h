// LineDetection.h : main header file for the LINEDETECTION application
//

#if !defined(AFX_LINEDETECTION_H__4D9460D5_5369_44D0_8C18_0F5D3EE33631__INCLUDED_)
#define AFX_LINEDETECTION_H__4D9460D5_5369_44D0_8C18_0F5D3EE33631__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestApp:
// See LineDetection.cpp for the implementation of this class

typedef CArray<CString*,CString*> CFileAry;
class CTestApp : public CWinApp
{
public:
	CTestApp();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTestApp)
	afx_msg void OnAppAbout();
	afx_msg void OnImageFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CView*	GetResultView();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINEDETECTION_H__4D9460D5_5369_44D0_8C18_0F5D3EE33631__INCLUDED_)

extern CTestApp	theApp;

