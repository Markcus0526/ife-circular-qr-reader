// TestDll.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "TestDll.h"
#include "FindRecogDigit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CTestDllApp

BEGIN_MESSAGE_MAP(CTestDllApp, CWinApp)
END_MESSAGE_MAP()


// CTestDllApp construction

CTestDllApp::CTestDllApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTestDllApp object

CTestDllApp theApp;
// CTestDllApp initialization

BOOL CTestDllApp::InitInstance()
{
	CWinApp::InitInstance();
	return TRUE;
}
int CTestDllApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	return CWinApp::ExitInstance();
}

// extern "C" _declspec(dllexport) bool _stdcall skRecogFromFile(TCHAR* szFileName,TCHAR* pResult)
// {
// 	CString fname(szFileName);
// 	BYTE* pDib;
// 	bool bRet;
// 	pDib = CImageIO::LoadImageFromFile(szFileName);
// 	if(!pDib) return false;
// 	bRet = (theApp.digit.Find_RecogDib(pDib, pResult) == TRUE);
// 	delete[] pDib;
// 	return bRet;
// }

extern "C" _declspec(dllexport) int _stdcall skRecogCircleQrBarcode_GrayImg(BYTE* grayImg,int w,int h,TCHAR* pResult)
{
	CFindRecogDigit digit;
	int bRet = digit.Find_RecogGrayImg(grayImg, w,h,pResult);
	return bRet;
}

