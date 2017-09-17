// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__E112E4E2_0813_4135_BCC6_2D040DF64B9C__INCLUDED_)
#define AFX_MAINFRM_H__E112E4E2_0813_4135_BCC6_2D040DF64B9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImageStatusBar.h"
#include "LeftView.h"

#define MAX_BITMAPS 3
#define WM_EXIT_COPY WM_USER+100
#define EXIT_COPY_FILE_STATUS 0
#define EXIT_RESTORE_LIST 1


class CNBrowserView;

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
protected:
	CSplitterWnd m_wndSplitter;
public:

// Operations
public:
LRESULT CMainFrame::OnExitCopy(WPARAM uID, LPARAM lEvent);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
	CNBrowserView* GetRightPane();
    CLeftView* GetLeftPane();

	CToolBar    m_wndToolBar;
	CImageStatusBar  m_wndStatusBar;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members


	CReBar      m_wndReBar;
	CDialogBar      m_wndDlgBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewRefresh();
	afx_msg void OnButttonRefresh();
	afx_msg void OnButtonPane();
	afx_msg void OnButtonUpLevel();
	afx_msg void OnButtonDeleteFile();
	afx_msg void OnFileDelete();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	//}}AFX_MSG
	afx_msg void OnUpdateViewStyles(CCmdUI* pCmdUI);
	afx_msg void OnViewStyle(UINT nCommandID);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__E112E4E2_0813_4135_BCC6_2D040DF64B9C__INCLUDED_)
