// NBrowser.h : main header file for the NBROWSER application
//

#if !defined(AFX_NBROWSER_H__FDB47A41_483E_49DE_8156_94FF0409A181__INCLUDED_)
#define AFX_NBROWSER_H__FDB47A41_483E_49DE_8156_94FF0409A181__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CNBrowserApp:
// See NBrowser.cpp for the implementation of this class
//

class CNBrowserApp : public CWinApp
{
public:
	CNBrowserApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNBrowserApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CNBrowserApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NBROWSER_H__FDB47A41_483E_49DE_8156_94FF0409A181__INCLUDED_)
