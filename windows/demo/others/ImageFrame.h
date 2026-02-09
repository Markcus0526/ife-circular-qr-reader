// ImageFrame.h : interface of the CImageFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEFRAME_H__102E5DBD_2E5E_4D87_9C40_FFBA984DEC8A__INCLUDED_)
#define AFX_IMAGEFRAME_H__102E5DBD_2E5E_4D87_9C40_FFBA984DEC8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MainToolBar.h"
class CImageFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CImageFrame)
public:
	CImageFrame();

// Attributes
public:
	CMainToolBar	m_ImageToolBar;
	CSplitterWnd	m_wndSplitter;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImageFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CImageFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEFRAME_H__102E5DBD_2E5E_4D87_9C40_FFBA984DEC8A__INCLUDED_)
