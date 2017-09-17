// NBrowserDoc.h : interface of the CNBrowserDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NBROWSERDOC_H__FE332E92_6713_4952_8565_4A20CA88DF9A__INCLUDED_)
#define AFX_NBROWSERDOC_H__FE332E92_6713_4952_8565_4A20CA88DF9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CNBrowserDoc : public CDocument
{
protected: // create from serialization only
	CNBrowserDoc();
	DECLARE_DYNCREATE(CNBrowserDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNBrowserDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNBrowserDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNBrowserDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NBROWSERDOC_H__FE332E92_6713_4952_8565_4A20CA88DF9A__INCLUDED_)
