#if !defined(AFX_RESULTVIEW_H__0A0D205F_C0F6_427D_80E1_D7665B687FF0__INCLUDED_)
#define AFX_RESULTVIEW_H__0A0D205F_C0F6_427D_80E1_D7665B687FF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResultView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResultView view
class CImageDoc;
class CResultView : public CEditView
{
protected:
	CResultView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CResultView)

// Attributes
public:

// Operations
public:
	CImageDoc*	GetDocument();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResultView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CResultView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CResultView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#ifndef _DEBUG  // debug version in ImageView.cpp
inline CImageDoc* CResultView::GetDocument()
{ return (CImageDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESULTVIEW_H__0A0D205F_C0F6_427D_80E1_D7665B687FF0__INCLUDED_)
