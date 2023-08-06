// MainToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "MainToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainToolBar
#define COMBOBOX_WIDTH_PAGE 70
#define COMBOBOX_HEIGHT_PAGE 200
CMainToolBar::CMainToolBar()
{
}

CMainToolBar::~CMainToolBar()
{
}


BEGIN_MESSAGE_MAP(CMainToolBar, CToolBarEx)
	//{{AFX_MSG_MAP(CMainToolBar)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMainToolBar message handlers
void CMainToolBar::CreateFileListCombo()
{
	CRect rect(-COMBOBOX_WIDTH, -COMBOBOX_HEIGHT, 0, 0);
	if (!m_FileListCombo.Create(WS_CHILD | WS_DISABLED | CBS_DROPDOWN 
				| CBRS_SIZE_DYNAMIC | WS_VSCROLL | CBS_HASSTRINGS, 
				rect, this,	ID_COMBO_FILE_LIST))
	{
		return ;
	}

	HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	if (hFont == NULL)
		hFont = (HFONT)GetStockObject(ANSI_VAR_FONT);

  	m_FileListCombo.SendMessage(WM_SETFONT, (WPARAM)hFont);
	
	int nIndex=CommandToIndex( ID_COMBO_FILE_LIST);
	SetButtonInfo(nIndex, ID_COMBO_FILE_LIST, TBBS_SEPARATOR,COMBOBOX_WIDTH);
	
	if (m_FileListCombo.m_hWnd != NULL)
	{
		CRect rect;
		GetItemRect(nIndex, rect);
		m_High=rect.Height();

		m_FileListCombo.SetWindowPos(this, rect.left, rect.top+7, 0, 0, 
			SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOCOPYBITS);
		m_FileListCombo.ShowWindow(SW_SHOW);
	}

}

void CMainToolBar::SetFileListComboByFileName(CFileAry& fileAry)
{
	CString si;
//	CPathInfo* pU;
	int i;
	int Len = fileAry.GetSize();
	m_FileListCombo.ResetContent( );
//	si.Format(L"%d",Len);
//	AfxMessageBox(si);
	for(i=0;i<Len;i++) {
		CString* ss = (CString*)fileAry.GetAt(i);
		si.Format(L"%3d_%s",i,ss->GetBuffer(0));		
		m_FileListCombo.InsertString(i,si);
	}
	m_FileListCombo.SetCurSel(0);
	m_FileListCombo.EnableWindow(TRUE);
}

void CMainToolBar::ReSetFileListCombo()
{
	m_FileListCombo.ResetContent( );
	m_FileListCombo.EnableWindow(FALSE);
}
void CMainToolBar::CreateCommbo()
{
//	CreateFontCommbo(&m_ZoomListCombo,ID_COMBO_ZOOM_LIST);
//	CreateFontCommbo(&m_PageListCombo,ID_COMBO_PAGE_LIST);
}
void CMainToolBar::CreateFontCommbo(CComboBox* Combo,UINT nId)
{
	int	Wid;
	Wid=-COMBOBOX_WIDTH_PAGE;
	CRect rect(Wid, -COMBOBOX_HEIGHT_PAGE, 0, 0);
	if (!Combo->Create(WS_CHILD | WS_DISABLED | CBS_DROPDOWN 
				| CBRS_SIZE_DYNAMIC | WS_VSCROLL | CBS_HASSTRINGS, 
				rect, this,	nId))
	{
		return ;
	}

	HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	if (hFont == NULL)
		hFont = (HFONT)GetStockObject(ANSI_VAR_FONT);

  	Combo->SendMessage(WM_SETFONT, (WPARAM)hFont);
	
	int nIndex=CommandToIndex( nId);
	Wid=COMBOBOX_WIDTH_PAGE;
	SetButtonInfo(nIndex, nId, TBBS_SEPARATOR,Wid);
	
	if (Combo->m_hWnd != NULL)
	{
		CRect rect,rectFontName,rTemp;
		GetItemRect(nIndex, rect);
		m_High=rect.Height();

		Combo->SetWindowPos(this, rect.left, rect.top+5, 0, 0, 
			SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOCOPYBITS);
		Combo->ShowWindow(SW_SHOW);
	}
}
void CMainToolBar::SetZoomComboList(int nCurId)
{
/*	CComboBox *Combo = &m_ZoomListCombo;
	int i;
	char strZoom[][10]={"12.5%","25%","50%","75%","100%",
		"200%","400%","800%","Custom"};
	Combo->ResetContent();
	for(i=0;i<9;i++) 	Combo->InsertString(i, strZoom[i]);
	Combo->SetCurSel(nCurId-1);
	Combo->EnableWindow();*/
}

void CMainToolBar::SetPageComboList(int nMaxPage)
{
/*	CComboBox *Combo = &m_PageListCombo;
	CString s;
	int i;
	Combo->ResetContent();
	for(i=0;i<nMaxPage;i++){
		s.Format("%d",i);
		Combo->InsertString(i, s);
	}
	Combo->SetCurSel(0);
	Combo->EnableWindow();*/
}