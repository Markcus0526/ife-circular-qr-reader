#if !defined(AFX_COMBOZOOM_H__97DC65AB_8F40_4681_85F2_4F0455A62D21__INCLUDED_)
#define AFX_COMBOZOOM_H__97DC65AB_8F40_4681_85F2_4F0455A62D21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComboZoom.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComboZoom window

class CComboZoom : public CComboBox
{
// Construction
public:
	CComboZoom();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboZoom)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetZoom();
	virtual ~CComboZoom();

	// Generated message map functions
protected:
	//{{AFX_MSG(CComboZoom)
	afx_msg void OnSelendok();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOZOOM_H__97DC65AB_8F40_4681_85F2_4F0455A62D21__INCLUDED_)
