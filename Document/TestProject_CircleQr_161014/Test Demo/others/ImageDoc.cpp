// ImageDoc.cpp : implementation of the CImageDoc class
//

#include "stdafx.h"
#include "Test.h"
#include "MainFrame.h"

#include "ImageDoc.h"
#include "ResultView.h"
#include "../BaseClass/ImageBase.h"
#include "../BaseClass/ImageIO.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageDoc

IMPLEMENT_DYNCREATE(CImageDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageDoc, CDocument)
	//{{AFX_MSG_MAP(CImageDoc)
	ON_COMMAND(ID_IMAGE_NEXT, OnImageNext)
	ON_COMMAND(ID_IMAGE_PREV, OnImagePrev)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_PREV, OnUpdateImagePrev)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_NEXT, OnUpdateImageNext)
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(ID_COMBO_FILE_LIST, OnFileListComboSel)
	ON_COMMAND(ID_RECOG_ALL, OnRecogRecogall)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageDoc construction/destruction
//extern "C" _declspec(dllimport) bool RecogDigits_Buf(BYTE* pGrayImg,int w,int h,TCHAR* szRes,int &left,int &top,int &right,int &bottom);



typedef int (__stdcall* LPRECOG_DLL)(BYTE*,int,int,TCHAR*);
HMODULE hModule;
LPRECOG_DLL	lpFnRecog_Dll;

CImageDoc::CImageDoc()
{	
	m_pOrgDIB	= NULL;
	m_pZoomDib	= NULL;
	hModule = ::LoadLibrary(_T("TestDll.dll"));
	if(hModule)
	{
		lpFnRecog_Dll = (LPRECOG_DLL)GetProcAddress(hModule,"skRecogCircleQrBarcode_GrayImg");
	}
}

CImageDoc::~CImageDoc()
{
	if(m_pOrgDIB != NULL)delete[] m_pOrgDIB; m_pOrgDIB = NULL;
	if(m_pZoomDib != NULL)delete[] m_pZoomDib; m_pZoomDib = NULL;
	if(hModule)
		::FreeLibrary(hModule);

	int i,nCount = m_arrFileAry.GetSize();
	for(i=0;i<nCount;i++)
	{
		delete (CString*)m_arrFileAry.GetAt(i);
		m_arrFileAry.RemoveAt(i);
		i--; nCount--;
	}

}

/////////////////////////////////////////////////////////////////////////////
// CImageDoc serialization

void CImageDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CImageDoc diagnostics

#ifdef _DEBUG
void CImageDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImageDoc commands
void CImageDoc::InitializeDoc()
{
	POSITION pos = theApp.GetFirstDocTemplatePosition();
	CDocTemplate* pTemplateImg;
	pTemplateImg = theApp.GetNextDocTemplate(pos);
	pos=pTemplateImg->GetFirstDocPosition();
	CDocument* pDoc;
	while(pos!=NULL)
	{
		pDoc=pTemplateImg->GetNextDoc(pos);
		if ((pDoc!=NULL) && (pDoc!=this))
		{
			pTemplateImg->RemoveDocument(pDoc);
			pDoc->OnCloseDocument();
		}
	}
}

BOOL CImageDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	InitializeDoc();	
	
	CString szOnlyFName;
	m_szFileName = lpszPathName;
	m_szDirPath = "";
	m_nCurSelPos = 0;	


	int len = m_szFileName.GetLength();
	int pos = m_szFileName.ReverseFind(_T('\\'));
	m_szDirPath = m_szFileName.Left(pos);
	szOnlyFName = m_szFileName.Right(len-pos-1);
	m_szDirPath += _T("\\");
	if(!GetImageNameList((LPCTSTR)m_szDirPath))
	{
		AfxMessageBox(L"There is no any image file.!");
		return FALSE;
	}

	CMainFrame *pM=(CMainFrame *)AfxGetMainWnd();	
	pM->m_wndToolBar.SetFileListComboByFileName(m_arrFileAry);

	m_nCurSelPos = GetFileNameId(m_arrFileAry,szOnlyFName); 
	pM->m_wndToolBar.m_FileListCombo.SetCurSel(m_nCurSelPos);
	SetImage();
	UpdateAllViews(NULL);

	return TRUE;
}
int CImageDoc::GetFileNameId(CFileAry& FileAry,CString FileName) 
{	
	CString s,*pFname;
	int i,num = FileAry.GetSize();
	for(i=0;i<num;i++){
		pFname = (CString*)FileAry.GetAt(i); 
		if(pFname->Compare(FileName)==0){
			break;
		}
	}
	if(i==num) i=0;
	return i;
}
BOOL CImageDoc::GetImageNameList(LPCTSTR lpszDirName)
{
	if (lpszDirName == NULL)
		return FALSE;
	int nSize = m_arrFileAry.GetSize();
	if (nSize > 0)
	{
		for (int i=0;i<nSize;i++)
			delete (CString*)m_arrFileAry.GetAt(i);
		m_arrFileAry.RemoveAll();
	}

	CString szDirPath;
	szDirPath.Format(L"%s",lpszDirName);
	
	SetCurrentDirectory(szDirPath);
	
	CString ext("*.bmp");
	CString* filePath = NULL;
	BOOL bContinue;
	CFileFind filefind;
	
	if((bContinue = filefind.FindFile(ext))){
		while(bContinue)
		{
			bContinue = filefind.FindNextFile();
			filePath = new CString;
			*filePath = filefind.GetFileName();
			m_arrFileAry.Add(filePath);
		}
		filefind.Close();
	}
	
	ext = "*.Tif";
	if((bContinue = filefind.FindFile(ext))){
		while(bContinue)
		{
			bContinue = filefind.FindNextFile();
			filePath = new CString;
			*filePath = filefind.GetFileName();
			m_arrFileAry.Add(filePath);
		}
		filefind.Close();
	}
	
	ext = "*.jpg";
	if((bContinue = filefind.FindFile(ext))){
		while(bContinue)
		{
			bContinue = filefind.FindNextFile();
			filePath = new CString;
			*filePath = filefind.GetFileName();
			m_arrFileAry.Add(filePath);
		}
		filefind.Close();
	}
	ext = "*.png";
	if((bContinue = filefind.FindFile(ext))){
		while(bContinue)
		{
			bContinue = filefind.FindNextFile();
			filePath = new CString;
			*filePath = filefind.GetFileName();
			m_arrFileAry.Add(filePath);
		}
		filefind.Close();
	}
	
	nSize = m_arrFileAry.GetSize();
	if (nSize>0)
		return TRUE;
/*	if (nSize>0)
	{
		for (int i=0;i<m_arrFileCombo.GetCount();i++)
			m_arrFileCombo.DeleteString(i);
		
		CString sNode,*pName;
		
		for (i=0;i<nSize;i++)
		{			
			pName = (CString*)m_arrFileAry.GetAt(i);
			CString s;
			s.Format("%d.%s",i,pName);
			m_arrFileCombo.InsertString(i,s);		
		}
		return TRUE;	
	}*/
	return FALSE;	
}

void CImageDoc::OnFileListComboSel()
{
	CMainFrame *pM=(CMainFrame *)AfxGetMainWnd();
	m_nCurSelPos = pM->m_wndToolBar.m_FileListCombo.GetCurSel();
	pM->m_wndToolBar.m_FileListCombo.SetCurSel(m_nCurSelPos);

	SetImage();
	UpdateAllViews(NULL);

}

void CImageDoc::OnImageNext() 
{
	CMainFrame *pM=(CMainFrame *)AfxGetMainWnd();
	int num = m_arrFileAry.GetSize();
	if(m_nCurSelPos >= num-1) return;

	m_nCurSelPos++;
	pM->m_wndToolBar.m_FileListCombo.SetCurSel(m_nCurSelPos);
	//--------------- User must this calling order ----------------
	SetImage();
	UpdateAllViews(NULL);

}

void FlipVertical(BYTE* pImg,int w,int h)
{
	int i,j;
	BYTE* pImg1 = new BYTE[w*h];
	memcpy(pImg1,pImg,w*h);
	for(i=0;i<h;i++)
		for(j=0;j<w;j++)
			pImg[i*w+j] = pImg1[(h-1-i)*w+j];
	delete pImg1;
}
void FlipHorizontal(BYTE* pImg,int w,int h)
{
	int i,j;
	BYTE* pImg1 = new BYTE[w*h];
	memcpy(pImg1,pImg,w*h);
	for(i=0;i<h;i++)
		for(j=0;j<w;j++)
			pImg[i*w+j] = pImg1[i*w+w-1-j];
	delete pImg1;
}
#define RECOG_FALSE			0
#define RECOG_OK			1
#define RECOG_CHECK_ERROR	2
void CImageDoc::SetImage()
{
	if(m_pOrgDIB != NULL)delete[] m_pOrgDIB;m_pOrgDIB = NULL;
	if(m_pZoomDib != NULL)delete[] m_pZoomDib;m_pZoomDib = NULL;
	CString* szFn = (CString*)m_arrFileAry.GetAt(m_nCurSelPos);
	TCHAR* p = szFn->GetBuffer(szFn->GetLength());
	CString ss(p);
	ss = m_szDirPath+ss;

	CString fname = ss;
	m_pOrgDIB = CImageIO::LoadImageFromFile(fname);
	if(m_pOrgDIB == NULL) return;

	int nRes = RECOG_FALSE;
	TCHAR rst[40];
	if(hModule)
	{
		int w,h;
		BYTE* grayImg = CImageBase::MakeGrayImgFromAnyDib(m_pOrgDIB,w,h);
		nRes = lpFnRecog_Dll(grayImg,w,h,rst);
		delete[] grayImg;
	
	}
	
	m_nBitCount = CImageBase::GetBitCount(m_pOrgDIB);
	
	CString szResult;
	if(nRes == RECOG_FALSE)
		szResult.Format(_T("recog false"));
	else if(nRes == RECOG_CHECK_ERROR)
		szResult.Format(_T("uuid:%s\r\nrecog error\r\ncheck error"),rst);
	else
		szResult.Format(_T("uuid:%s\r\nrecog ok\r\ncheck ok"),rst);
	CResultView* pRV = (CResultView*)theApp.GetResultView();
	pRV->SetWindowText(szResult);
	//----------- Display the image info in status bar ------------	
	CMainFrame *pM=(CMainFrame *)AfxGetMainWnd();	
// 	CString szDisp;
// 	CImageBase::GetWidthHeight(m_pOrgDIB,m_nW,m_nH);
// 	szDisp.Format(L"(%dx%dx%d)",m_nW,m_nH,m_nBitCount);
// 	pM->SetTextToStatusBar(1,szDisp);
	UpdateAllViews(NULL);
	//-------------------------------------------------------------
}
void CImageDoc::OnImagePrev() 
{
	if(m_nCurSelPos <1) return;


	m_nCurSelPos--;

	CMainFrame *pM=(CMainFrame *)AfxGetMainWnd();	
	pM->m_wndToolBar.m_FileListCombo.SetCurSel(m_nCurSelPos);
	
	//--------------- User must this calling order ----------------
	SetImage();
	UpdateAllViews(NULL);	
	//-------------------------------------------------------------	


}

void CImageDoc::OnUpdateImagePrev(CCmdUI* pCmdUI) 
{
	int num = m_arrFileAry.GetSize();
	pCmdUI->Enable(m_nCurSelPos>0);
	
}

void CImageDoc::OnUpdateImageNext(CCmdUI* pCmdUI) 
{
	int num = m_arrFileAry.GetSize();
	pCmdUI->Enable(m_nCurSelPos<num-1);
	
}



void CImageDoc::OnRecogRecogall()
{

}

