// LineDetection.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Test.h"

#include "MainFrame.h"
#include "ImageFrame.h"
#include "ImageDoc.h"
#include "ImageView.h"
#include "ResultView.h"
#include "DirDialog.h"
#include "../BaseClass/ImageIO.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestApp

BEGIN_MESSAGE_MAP(CTestApp, CWinApp)
	//{{AFX_MSG_MAP(CTestApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_IMAGE_FILE_OPEN, OnImageFileOpen)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestApp construction

CTestApp::CTestApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTestApp object

CTestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTestApp initialization
BYTE* gCodeData, *gSymData, *gDicData;
BOOL CTestApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_LINEDETYPE,
		RUNTIME_CLASS(CImageDoc),
		RUNTIME_CLASS(CImageFrame), // custom MDI child frame
		RUNTIME_CLASS(CImageView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(SW_MAXIMIZE);
	pMainFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CTestApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CTestApp message handlers

static TCHAR BASED_CODE szImgFilter[] = 
	_T("Image Files(*.bmp;*.tif;*.jpeg;*.gif;*.png;*.smp)|*.bmp;*.tif;*.jpg;*.gif;*.png;*.smp|BMP File(*.bmp)|*.bmp|Tiff File(*.tif)|*.tif|Jpeg Files(*.jpg)|*.jpg|Gif Files(*.gif)|*.gif|PCX Files(*.pcx)|*.pcx|PNG Files(*.png)|*.png|MNG Files(*.mng)|*.mng|TGA Files(*.tga)|*.tga|All Files(*.*)|*.*|");
void CTestApp::OnImageFileOpen() 
{
	CFileDialog fd (TRUE,
		_T("bmp"),
		NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, 
		szImgFilter,
		NULL
		);
	fd.m_ofn.hInstance = theApp.m_hInstance;
	fd.m_ofn.Flags= OFN_EXPLORER  | OFN_ENABLEHOOK | OFN_ENABLESIZING;
	if (fd.DoModal() != IDOK) return ;

	CString szFilePath = fd.m_ofn.lpstrFile;
	CDocTemplate	*pTemplateImg;
	POSITION pos = GetFirstDocTemplatePosition();
	pTemplateImg = GetNextDocTemplate(pos);
	pTemplateImg->OpenDocumentFile(szFilePath);
	
}
/*	CDirDialog dlg;	
	dlg.m_strWindowTitle = "Select Passport Image Location";
	dlg.m_strTitle = "Browse Folder for LisencePlate Image Files location";

//#ifdef _DEBUG
	//dlg.m_strSelDir = "F:\\Oksang\\sihemji\\6th\\TestImage\\Blank\\";//"H:\\Dev_2015\\Beijing_Scana\\6th\\";
	dlg.m_strSelDir = "F:\\Oksang\\sihemji\\27-11-2015_9-18-27\\";//H:\\Dev_2015\\Beijing_Scana\\6th\\27-11-2015_9-18-27\\";
//#endif
	if( !dlg.DoBrowse(AfxGetMainWnd()) ) return;
	
	int nSize = m_arrFileAry.GetSize();
	if (nSize > 0)
	{
		for (int i=0;i<nSize;i++)
			delete (CString*)m_arrFileAry.GetAt(i);
		m_arrFileAry.RemoveAll();
	}
	
	if(dlg.m_strPath.Right(1)=='\\')
		m_szDirPath = dlg.m_strPath;
	else
		m_szDirPath = dlg.m_strPath + "\\";	
	
	if(!GetImageNameList((LPCTSTR)m_szDirPath))
	{
		AfxMessageBox(L"There is no any image file.!");
		return;
	}
	
	CMainFrame *pM=(CMainFrame *)AfxGetMainWnd();	
	pM->m_wndToolBar.SetFileListComboByFileName();

	m_nCurSelPos = 0;
	CString *ss = m_arrFileAry.GetAt(m_nCurSelPos);
	CString  sss(m_szDirPath+*ss);

	OpenDocumentFile(sss);	
		
}
*/


int CTestApp::ExitInstance() 
{

	return CWinApp::ExitInstance();
}
CView* CTestApp::GetResultView()
{
	POSITION pos;
	pos = GetFirstDocTemplatePosition();	
	CDocTemplate* pMdt = GetNextDocTemplate(pos);
	pos = pMdt->GetFirstDocPosition();
	CImageDoc* pDoc = (CImageDoc*)pMdt->GetNextDoc(pos);
	pos = pDoc->GetFirstViewPosition();
	pDoc->GetNextView(pos);
	CResultView* p = (CResultView*)pDoc->GetNextView(pos);
	return p;
}
