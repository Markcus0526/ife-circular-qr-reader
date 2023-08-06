// ImageView.cpp : implementation of the CImageView class
//

#include "stdafx.h"
#include "Test.h"
#include "MainFrame.h"
#include "ImageFrame.h"

#include "ImageDoc.h"
#include "ImageView.h"
#include "ResultView.h"
#include "../BaseClass/ImageIO.h"
#include "../BaseClass/ImageBase.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageView

IMPLEMENT_DYNCREATE(CImageView, CScrollView)

BEGIN_MESSAGE_MAP(CImageView, CScrollView)
	//{{AFX_MSG_MAP(CImageView)
	ON_COMMAND(ID_VIEW_RECT, OnViewRect)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RECT, OnUpdateViewRect)
	ON_COMMAND(ID_VIEW_ORDER, OnViewOrder)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ORDER, OnUpdateViewOrder)
	ON_COMMAND(ID_VIEW_ZOOM_IN, OnViewZoomIn)
	ON_COMMAND(ID_VIEW_ZOOM_OUT, OnViewZoomOut)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM_IN, OnUpdateViewZoomIn)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM_OUT, OnUpdateViewZoomOut)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageView construction/destruction

CImageView::CImageView()
{
	m_bRectView		= TRUE;
	m_bOrderView	= FALSE;

	m_fViewRate = 0.2;//0.2;1.0;
}

CImageView::~CImageView()
{
}

BOOL CImageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CImageView drawing

void CImageView::OnDraw(CDC* pDC)
{
	CImageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	if(pDoc->m_pOrgDIB == NULL)return;
	int w,h;
	CImageBase::GetWidthHeight(pDoc->m_pOrgDIB,w,h);
	w = (int)(m_fViewRate*w);
	h = (int)(m_fViewRate*h);
	if(pDoc->m_pZoomDib == NULL)
		pDoc->m_pZoomDib = CImageBase::ZoomDib(pDoc->m_pOrgDIB,w,h);
	SetScrollSizes(MM_TEXT,CSize(w,h));

	DrawDib(pDC,CRect(0,0,w,h),pDoc->m_pZoomDib);
	int m,n,i;
	for(i=0;i<pDoc->m_Result.OutLine.nRtNum;i++)
	{
		DrawRectangle(pDC,pDoc->m_Result.OutLine.rect[i]);
	}
	for(i=0;i<pDoc->m_Result.class_no.nRtNum;i++)
	{
		DrawRectangle(pDC,pDoc->m_Result.class_no.rect[i]);
	}
	for(i=0;i<pDoc->m_Result.pupil_no.nRtNum;i++)
	{
		DrawRectangle(pDC,pDoc->m_Result.pupil_no.rect[i]);
	}
	for(i=0;i<pDoc->m_Result.subject_no.nRtNum;i++)
	{
		DrawRectangle(pDC,pDoc->m_Result.subject_no.rect[i]);
	}
	for(n=0;n<pDoc->m_Result.nProblemNum;n++)for(i=0;i<pDoc->m_Result.Problem[n].nRtNum;i++)
	{
		DrawRectangle(pDC,pDoc->m_Result.Problem[n].rect[i]);
	}

}
void CImageView::DrawRectangle(CDC *pDC,CRect Rt)
{
	CRect rt = Rt;
	rt.left = (int)(m_fViewRate*rt.left);
	rt.top = (int)(m_fViewRate*rt.top);
	rt.right = (int)(m_fViewRate*rt.right);
	rt.bottom = (int)(m_fViewRate*rt.bottom);
	pDC->Draw3dRect(rt,RGB(255,0,0),RGB(255,0,0));
}
void CImageView::DrawDib(CDC *pDC,CRect Rt,BYTE *pDib)
{
	if(pDib==NULL) return;
	
	LPBITMAPINFOHEADER lpBIH=(LPBITMAPINFOHEADER)pDib ;
	int w=(int)lpBIH->biWidth;
	int h=(int)lpBIH->biHeight;
	BYTE *lpBits= Get_lpBits(pDib);
	
	::StretchDIBits( pDC->GetSafeHdc(), 
		Rt.left,Rt.top, Rt.Width(),Rt.Height(),0,0, w,h,
		(LPSTR)lpBits,
		(LPBITMAPINFO)lpBIH,
		DIB_RGB_COLORS,
		SRCCOPY);
}
BYTE* CImageView::Get_lpBits(BYTE *pDib)
{
	LPBITMAPINFOHEADER lpBIH=(LPBITMAPINFOHEADER)pDib ;
	int w = (int)lpBIH->biWidth;
	int h = (int)lpBIH->biHeight;
	int QuadSize;
	if(lpBIH->biBitCount == 1)		QuadSize = sizeof(RGBQUAD)*2;
	else if(lpBIH->biBitCount == 2)	QuadSize = sizeof(RGBQUAD)*4;
	else if(lpBIH->biBitCount == 4)	QuadSize = sizeof(RGBQUAD)*16;
	else if(lpBIH->biBitCount == 8)	QuadSize = sizeof(RGBQUAD)*256;
	else							QuadSize = 0;//16,24,32
	BYTE* lpBits = (BYTE*) (pDib + sizeof(BITMAPINFOHEADER)+ QuadSize);
	return lpBits;
}
void CImageView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
	
	CImageFrame* pIF = (CImageFrame*)GetParentFrame();
	pIF->ShowWindow(SW_MAXIMIZE);
}

/////////////////////////////////////////////////////////////////////////////
// CImageView printing

BOOL CImageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CImageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CImageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CImageView diagnostics

#ifdef _DEBUG
void CImageView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageDoc* CImageView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageDoc)));
	return (CImageDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImageView message handlers

void CImageView::OnViewRect() 
{
	m_bRectView = !m_bRectView;
	Invalidate(FALSE);	
}

void CImageView::OnUpdateViewRect(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bRectView);
	
}

void CImageView::OnViewOrder() 
{
	if(m_bRectView == FALSE)
	{
		AfxMessageBox(L"This option can use only when drawing rects.!");
		return;
	}
	m_bOrderView = !m_bOrderView;
	Invalidate(FALSE);	
}

void CImageView::OnUpdateViewOrder(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bRectView);
	pCmdUI->SetCheck(m_bOrderView);	
}

void CImageView::OnViewZoomIn() 
{
	CImageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(m_fViewRate<3.8)	
	{
		m_fViewRate += 0.05;
		if(pDoc->m_pZoomDib) delete pDoc->m_pZoomDib; pDoc->m_pZoomDib = NULL;
		Invalidate();
	}
}

void CImageView::OnViewZoomOut() 
{
	CImageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	if(m_fViewRate>0.1)	
	{
		m_fViewRate -= 0.05;
		if(pDoc->m_pZoomDib) delete pDoc->m_pZoomDib; pDoc->m_pZoomDib = NULL;
		Invalidate();
	}
	
}

void CImageView::OnUpdateViewZoomIn(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_fViewRate<3.8);
	
}

void CImageView::OnUpdateViewZoomOut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_fViewRate>0.1);
	
}

void CImageView::OnFileSaveAs() 
{
	CImageDoc* pDoc = (CImageDoc*)GetDocument();

	static TCHAR BASED_CODE szImgFilter[] = 
		_T("Image Files(*.bmp;*.tif;*.jpeg;*.gif)|*.bmp;*.tif;*.jpg;*.gif|BMP File(*.bmp)|*.bmp|Tiff File(*.tif)|*.tif|Jpeg Files(*.jpg)|*.jpg|Gif Files(*.gif)|*.gif|PCX Files(*.pcx)|*.pcx|PNG Files(*.png)|*.png|MNG Files(*.mng)|*.mng|TGA Files(*.tga)|*.tga|PDF Files(*.pdf)|*.pdf|");
	
	CFileDialog fd(
		FALSE,
		_T("bmp"),
		NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, 
		szImgFilter,
		NULL
		);
	fd.m_ofn.Flags= OFN_EXPLORER  | OFN_ENABLEHOOK | OFN_ENABLESIZING;
	
	LPCTSTR pFnames;
	BOOL ImageIsPDF = FALSE;
	
	if (fd.DoModal() == IDOK)
	{
		pFnames=fd.m_ofn.lpstrFile+fd.m_ofn.nFileOffset;
		CImageIO::SaveBmpFile(pFnames,pDoc->m_pOrgDIB);
	}
	
}
