// ImageDoc.h : interface of the CImageDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEDOC_H__B2DF3038_2450_4630_86F3_D5FD80840D31__INCLUDED_)
#define AFX_IMAGEDOC_H__B2DF3038_2450_4630_86F3_D5FD80840D31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


typedef struct tagProblemData
{
	TCHAR chCode[40];
	RECT rect[40];
	int nRtNum;
}ProblemData;
typedef struct tagBigProblemData
{
	int startId;
	int problemNum;
	int problemType; //0: kequanti, 1 check, 2: rectangle;
}BigProblemData;
class CResult{
public:
	ProblemData OutLine;
	ProblemData class_no;
	ProblemData pupil_no;
	ProblemData subject_no;

	ProblemData Problem[200];
	int nProblemNum;
	BigProblemData BigData[100];
	int nBigDataNum;
public:
	CResult(){ memset(this,0,sizeof(CResult));};
};
#define NOR_W	1006
#define NOR_H	600

class CImageDoc : public CDocument
{
protected: // create from serialization only
	CImageDoc();
	DECLARE_DYNCREATE(CImageDoc)
		
		// Attributes
public:
	CString		m_szFileName;
	CString		m_szDirPath;
	CFileAry	m_arrFileAry;
	int			m_nCurSelPos;
public:
	int			m_nW,m_nH,m_nBitCount;
	int			m_nBiBitcount;
	BYTE		*m_pOrgDIB;
	BYTE		*m_pZoomDib;
	CRect		m_rtResult;

	CResult		m_Result;
// Operations
public:
	void	InitializeDoc();
	void	SetImage();
	int		GetFileNameId(CFileAry& FileAry,CString FileName); 
	BOOL	GetImageNameList(LPCTSTR lpszDirName);
	bool	GetInRectFromFileName(LPCTSTR ss,int inRect[4]);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageDoc)
	public:
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImageDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CImageDoc)
	afx_msg void OnImageNext();
	afx_msg void OnImagePrev();
	afx_msg void OnUpdateImagePrev(CCmdUI* pCmdUI);
	afx_msg void OnUpdateImageNext(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnFileListComboSel();
	DECLARE_MESSAGE_MAP()

public:

	afx_msg void OnRecogRecogall();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEDOC_H__B2DF3038_2450_4630_86F3_D5FD80840D31__INCLUDED_)
