// ResultView.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "ImageDoc.h"
#include "ResultView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResultView

IMPLEMENT_DYNCREATE(CResultView, CEditView)

CResultView::CResultView()
{
}

CResultView::~CResultView()
{
}


BEGIN_MESSAGE_MAP(CResultView, CEditView)
	//{{AFX_MSG_MAP(CResultView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResultView drawing
void CResultView::OnDraw(CDC* pDC)
{
	CImageDoc* pDoc = (CImageDoc*)GetDocument();
	
	
	
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CResultView diagnostics

#ifdef _DEBUG
void CResultView::AssertValid() const
{
	CEditView::AssertValid();
}

void CResultView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
CImageDoc* CResultView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageDoc)));
	return (CImageDoc*)m_pDocument;
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CResultView message handlers
