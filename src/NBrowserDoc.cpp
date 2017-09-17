// NBrowserDoc.cpp : implementation of the CNBrowserDoc class
//

#include "stdafx.h"
#include "NBrowser.h"

#include "NBrowserDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNBrowserDoc

IMPLEMENT_DYNCREATE(CNBrowserDoc, CDocument)

BEGIN_MESSAGE_MAP(CNBrowserDoc, CDocument)
	//{{AFX_MSG_MAP(CNBrowserDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNBrowserDoc construction/destruction

CNBrowserDoc::CNBrowserDoc()
{
	// TODO: add one-time construction code here

}

CNBrowserDoc::~CNBrowserDoc()
{
}

BOOL CNBrowserDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CNBrowserDoc serialization

void CNBrowserDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CNBrowserDoc diagnostics

#ifdef _DEBUG
void CNBrowserDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNBrowserDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNBrowserDoc commands
