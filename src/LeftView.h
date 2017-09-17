// LeftView.h : interface of the CLeftView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEFTVIEW_H__CBE781B2_A206_4CC2_ABFC_1A28CD8C08EF__INCLUDED_)
#define AFX_LEFTVIEW_H__CBE781B2_A206_4CC2_ABFC_1A28CD8C08EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define FOLDER_IN_PROGRESS "........"
#define MY_LOCAL_COMPUTER "My Local Computer"



class CNBrowserDoc;

class CLeftView : public CTreeView
{
protected: // create from serialization only
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Attributes
public:
	CNBrowserDoc* GetDocument();
	CTreeCtrl* m_pTreeCtrl;
	CImageList	*m_pimagelist;
	long mi_nOpen;
	long mi_nComputer;
	long mi_nClose;
	long mi_olditem;
    HTREEITEM hTreeViewsDocuments;
    HTREEITEM  hTreeComputer;
	HTREEITEM  m_hRightPaneFormView1;
	HTREEITEM  m_hRightPaneFormView2;
	HTREEITEM  m_hRightPaneEditView;
	HTREEITEM  m_hRightPaneListView;
	HTREEITEM  m_hRightPaneHorizSplitterView;
	HTREEITEM  m_hRightPaneVertSplitterView;
	HTREEITEM  m_hPreviousSelectedItem;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	void RestoreCurrentFolder();
	VOID RestoreFoldrer(HTREEITEM itemParent,BOOL showFile= FALSE);
	VOID CreateDriveList();
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLeftView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    HTREEITEM CLeftView::FindCurrentItem(CTreeCtrl *m_pTreeCtrl,HTREEITEM htiWork,CString strFin);
	VOID ResporeChieldFolder(HTREEITEM itemParent);

	VOID SetFolderIcon(HTREEITEM hti,DWORD mi_Open_Close);
public:
	void SelectItemByName(CString strPath);
	CTreeCtrl * MGetTreeCtrl();
	void Refresh();
	VOID CreatePathForHeaderTree(HTREEITEM item,char *pBuf);
	VOID ClearAllChield(HTREEITEM itemParent);
	VOID CreateMyLocalComputer(HTREEITEM item);
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CNBrowserDoc* CLeftView::GetDocument()
   { return (CNBrowserDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTVIEW_H__CBE781B2_A206_4CC2_ABFC_1A28CD8C08EF__INCLUDED_)
