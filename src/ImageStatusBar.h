#if !defined(AFX_IMAGESTATUSBAR_H__F1F1C855_5B9B_11D4_8F58_006008B13CA9__INCLUDED_)
#define AFX_IMAGESTATUSBAR_H__F1F1C855_5B9B_11D4_8F58_006008B13CA9__INCLUDED_

/*CImageStatusBar: Header File - By Ryan Lederman, July 21, 00
   Change MAX_BITMAPS and NUM_OF_PANES to fit your application*/

#if _MSC_VER > 1000
#pragma once
#endif 

#define MAX_BITMAPS 3 //Change to have more bitmaps
#define NUM_OF_PANES 3 //Change for your App
#define ISB_LEFTALIGN 2500
#define ISB_CENTERALIGN 2501
#define ISB_RIGHTALIGN 2502
#define ISB_NOIMAGE 2503

class CImageStatusBar : public CStatusBar
{

public:
	CImageStatusBar();
	int paneBitmaps[MAX_BITMAPS]; 
	int paneAlignments[MAX_BITMAPS];
	void SetBitmaps(UINT Bitmaps[], int Alignments[]);
	void DrawBitmaps(CPaintDC* dc);
	void SetBitmap(int paneIndex,UINT bitmapID,int isbAlignment);

public:


public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageStatusBar)
	public:
	protected:
	//}}AFX_VIRTUAL


public:
	virtual ~CImageStatusBar();


protected:
	//{{AFX_MSG(CImageStatusBar)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGESTATUSBAR_H__F1F1C855_5B9B_11D4_8F58_006008B13CA9__INCLUDED_)
