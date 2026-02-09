// ComboZoom.cpp : implementation file
//

#include "stdafx.h"
#include "..\ImgTool.h"
#include "..\MainFrm.h"
#include "..\ImgFrm.h"
#include "..\ImgDoc.h"
#include "..\ImgView.h"


#include "ComboZoom.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComboZoom
CComboZoom::CComboZoom()
{
}

CComboZoom::~CComboZoom()
{
}


BEGIN_MESSAGE_MAP(CComboZoom, CComboBox)
	//{{AFX_MSG_MAP(CComboZoom)
	ON_CONTROL_REFLECT(CBN_SELENDOK, OnSelendok)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboZoom message handlers

BOOL CComboZoom::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_ESCAPE:
		case VK_RETURN:
			SetZoom();
			break;
		case VK_UP:
		case VK_DOWN:
			if ((GetKeyState(VK_MENU) >= 0) && (GetKeyState(VK_CONTROL) >=0) &&
				!GetDroppedState())
			{
				ShowDropDown();
				break;
			}
		}
	}
	return CComboBox::PreTranslateMessage(pMsg);
}

void CComboZoom::OnSelendok() 
{
	char			szZoom[MAX_PATH];
	double			fZoom;
	int				nIndex = GetCurSel();
	CMainFrame		*pMainFrame = (CMainFrame *)theApp.m_pMainWnd;
	CImgFrame		*pChildFrame;
	CImgDoc			*pDoc;
	CImgView		*pView;

	GetLBText(nIndex, szZoom);
	fZoom = atof(szZoom);
	pChildFrame = (CImgFrame *)pMainFrame->MDIGetActive();
	pDoc = (CImgDoc *)pChildFrame->GetActiveDocument();
	pView = (CImgView *)pChildFrame->GetActiveView();
	if(pDoc)
	{
		pView->SetZoomFactor(fZoom);
	}	
}

void CComboZoom::SetZoom()
{
	char			szZoom[MAX_PATH];
	double			fZoom;
	int				nLen;
	CMainFrame		*pMainFrame = (CMainFrame *)theApp.m_pMainWnd;
	CImgFrame		*pChildFrame;
	CImgDoc			*pDoc;
	CImgView		*pView;

	GetWindowText(szZoom, MAX_PATH);
	fZoom = atof(szZoom);
	if(fZoom > 800.0f)
		fZoom = 800.0f;
	else if(fZoom < 12.5f)
		fZoom = 12.5f;

	sprintf(szZoom, "%.2f", fZoom);
	nLen = strlen(szZoom);
	for(int i = nLen-1; i >= 0; i --)
		if(szZoom[i] != '0')
			break;
	if(szZoom[i] == '.')
		i--;
	szZoom[i+1] = 0;
	strcat(szZoom, "%");
	SetWindowText(szZoom);
	pChildFrame = (CImgFrame *)pMainFrame->MDIGetActive();
	pDoc = (CImgDoc *)pChildFrame->GetActiveDocument();
	pView = (CImgView *)pChildFrame->GetActiveView();
	if(pDoc)
	{
		pView->SetZoomFactor(fZoom);
	}	
}
