#if !defined(AFX_COPYTHREAD_H__26B30841_FD86_41A2_A299_C1C137C332B7__INCLUDED_)
#define AFX_COPYTHREAD_H__26B30841_FD86_41A2_A299_C1C137C332B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CopyThread.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CCopyThread thread

class CCopyThread : public CWinThread
{
	DECLARE_DYNCREATE(CCopyThread)
protected:
	CCopyThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCopyThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCopyThread();

	// Generated message map functions
	//{{AFX_MSG(CCopyThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COPYTHREAD_H__26B30841_FD86_41A2_A299_C1C137C332B7__INCLUDED_)
