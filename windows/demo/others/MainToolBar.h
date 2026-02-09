#if !defined(AFX_MAINTOOLBAR_H__8D73F642_A579_11D4_BB84_00E04CDD9617__INCLUDED_)
#define AFX_MAINTOOLBAR_H__8D73F642_A579_11D4_BB84_00E04CDD9617__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainToolBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainToolBar window
#include "ToolBarEx.h"
//#include "ComboZoom.h"

#define COMBOBOX_WIDTH 270//150
#define COMBOBOX_HEIGHT 200
class CMainToolBar : public CToolBarEx
{
// Construction
public:
	CMainToolBar();
	
// Attributes
public:
	CComboBox	m_FileListCombo;
//	CComboZoom	m_ZoomListCombo;
//	CComboBox	m_PageListCombo;
	BYTE		m_High;
// Construction
public:
	void	CreateFileListCombo();
	void	SetFileListComboByFileName(CFileAry& fileAry);
	void	ReSetFileListCombo();

	void	CreateCommbo();
	void	CreateFontCommbo(CComboBox* Combo,UINT nId);
	void	SetZoomComboList(int nCurId);
	void	SetPageComboList(int nMaxPage);


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainToolBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMainToolBar)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINTOOLBAR_H__8D73F642_A579_11D4_BB84_00E04CDD9617__INCLUDED_)
