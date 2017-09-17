// CopyThread.cpp : implementation file
//

#include "stdafx.h"
#include "NBrowser.h"
#include "CopyThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCopyThread

IMPLEMENT_DYNCREATE(CCopyThread, CWinThread)

CCopyThread::CCopyThread()
{
}

CCopyThread::~CCopyThread()
{
}

BOOL CCopyThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CCopyThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CCopyThread, CWinThread)
	//{{AFX_MSG_MAP(CCopyThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCopyThread message handlers
