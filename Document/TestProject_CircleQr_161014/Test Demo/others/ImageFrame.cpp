// ImageFrame.cpp : implementation of the CImageFrame class
//

#include "stdafx.h"
#include "Test.h"

#include "ImageFrame.h"
#include "ResultView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageFrame

IMPLEMENT_DYNCREATE(CImageFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CImageFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CImageFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageFrame construction/destruction

CImageFrame::CImageFrame()
{
	// TODO: add member initialization code here
	
}

CImageFrame::~CImageFrame()
{
}

BOOL CImageFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CImageFrame diagnostics

#ifdef _DEBUG
void CImageFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CImageFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImageFrame message handlers

int CImageFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_ImageToolBar.Create(this,WS_CHILD | WS_VISIBLE | CBRS_SIZE_DYNAMIC |
		CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY, IDR_IMAGE_TOOLBAR) ||
		!m_ImageToolBar.LoadToolBar(IDR_IMAGE_TOOLBAR))
	{
		TRACE0("Failed to create MainToolbar\n");
		return -1;
	}
	
	m_ImageToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	
	return 0;
}

BOOL CImageFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
	{
		TRACE0("Failed to CreateStaticSplitter\n");
		return FALSE;
	}
	
	// add the first splitter pane - the default view in column 0
	if (!m_wndSplitter.CreateView(0, 0,
		pContext->m_pNewViewClass, CSize(130, 50), pContext))
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}
	
	// add the second splitter pane - an input view in column 1
	if (!m_wndSplitter.CreateView(0, 1,
		RUNTIME_CLASS(CResultView), CSize(0, 0), pContext))
	{
		TRACE0("Failed to create second pane\n");
		return FALSE;
	}
	
	// activate the input view
	CRect r;
	GetClientRect(&r);

	m_wndSplitter.SetColumnInfo(0,r.Width()/2,100);
	m_wndSplitter.SetColumnInfo(1,r.Width()/2,0);
	SetActiveView((CView*)m_wndSplitter.GetPane(0,0));
	RecalcLayout();
	
	return TRUE;
}
