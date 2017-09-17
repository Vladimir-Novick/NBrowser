// NBrowserView.h : interface of the CNBrowserView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NBROWSERVIEW_H__BFD84025_3B3F_4EF1_83EC_1D42F68105EB__INCLUDED_)
#define AFX_NBROWSERVIEW_H__BFD84025_3B3F_4EF1_83EC_1D42F68105EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

#define NUM_COLUMNS 4
#define NUM_ITEMS   40
#define FOLDERTYPE 11


#define SORT_BY_NAME 0
#define SORT_BY_LENGTH 1
#define SORT_BY_TYPE 2
#define SORT_BY_DATE_MODIFY 3


struct sortindex{
	char FileName[128];
	char fileType[10];
	long lenfile;
	DWORD date;
	DWORD time;
	FILETIME filetime;
} ;




static _TCHAR *_gszColumnLabel[NUM_COLUMNS] =
{
	_T("Name"), _T("Size"), _T("Type"), _T("Modified")
};


static int _gnColumnWidth[NUM_COLUMNS] =
{
	250, 100, 100, 190
};

static int _gnColumnFmt[NUM_COLUMNS] =
{
	LVCFMT_LEFT, LVCFMT_RIGHT, LVCFMT_LEFT, LVCFMT_RIGHT
};


class CNBrowserView : public CListView
{
protected: // create from serialization only
	CNBrowserView();
	DECLARE_DYNCREATE(CNBrowserView)

// Attributes
public:
	CNBrowserDoc* GetDocument();
protected:
	CImageList m_LargeImageList;
	CImageList m_SmallImageList;
	char szCurrentFolder[256];

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNBrowserView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void RestoreFileList();
	void SetFolderName(char *szPath);
	VOID InsertFileList(char *pFileName,DWORD dwSize,DWORD dwType,char *strModify);
	virtual ~CNBrowserView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNBrowserView)
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnItemclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnViewLargeicon();
	afx_msg void OnViewDetails();
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
public:
	void CheckTreeFolder();
public:
	void DeleteFile();
	void UpOneLevel();
	void MyCopyFile(char *strSrc);
};

#ifndef _DEBUG  // debug version in NBrowserView.cpp
inline CNBrowserDoc* CNBrowserView::GetDocument()
   { return (CNBrowserDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NBROWSERVIEW_H__BFD84025_3B3F_4EF1_83EC_1D42F68105EB__INCLUDED_)
