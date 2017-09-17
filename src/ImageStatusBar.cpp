/*CImageStatusBar.cpp: Source for CImageStatusBar by Ryan Lederman - Saturday, July 22 - See ReadMe.txt*/
  
#include "stdafx.h"
#include "ImageStatusBar.h"
//#include "notexpad.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CImageStatusBar::CImageStatusBar()
{

}

CImageStatusBar::~CImageStatusBar()
{
}


BEGIN_MESSAGE_MAP(CImageStatusBar, CStatusBar)
	//{{AFX_MSG_MAP(CImageStatusBar)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageStatusBar message handlers

void CImageStatusBar::OnPaint()
{	
	CPaintDC* dc = (CPaintDC*)GetDC();
	CStatusBar::OnPaint();
	DrawBitmaps(dc);
	ReleaseDC(dc);
}

void CImageStatusBar::DrawBitmaps(CPaintDC* dc)
{
	
	
	CBitmap bitmap[MAX_BITMAPS];
	CDC compDC;
	
	CFrameWnd* theFrame = (CFrameWnd*)AfxGetMainWnd();
	CEdit* theView = (CEdit*)theFrame->GetActiveView();
	int difference=0;
	int center=0;
	CString msg;
	CString paneText;
	BITMAP bmInfo;

	for (int x =0;x < NUM_OF_PANES ; x++)
	{
		if (paneBitmaps[x] != ISB_NOIMAGE)
		{	
			compDC.CreateCompatibleDC(dc);
			CRect rect;
			paneText = GetPaneText(x+1);
			GetItemRect(x+1,rect);
		
			bitmap[x].LoadBitmap(paneBitmaps[x]);
			bitmap[x].GetObject(sizeof(bmInfo),&bmInfo);
			compDC.SelectObject(&bitmap[x]);

			/*This will adjust the top & left of the bitmap's drawn rect
			according to ISB_ALIGN flag passed to SetBitmaps() or SetBitmap()*/
			int paneWidth = rect.left + rect.right  ;
			int paneHeight = rect.top + rect.bottom;

			/*This part of the function decides if the bitmap should be shown at all.
			if the width of the pane containing the bitmap is less than a certain width,
			you should make sure the bitmap does not paint, because it can draw over 
			parts of the status bar you do not wish it to. *Note*: if you happen to attempt
			to set pane 0's bitmap to ISB_NOIMAGE, your statusbar will become about 1000 pixels tall ! Do not do this!*/

			if (x == NUM_OF_PANES-NUM_OF_PANES)//First Pane
			{	
				if (paneWidth < 550) //Change 550 to suit your program
				{
					return;
				}

			}
			if (x == NUM_OF_PANES-1) //Last Pane
			{  
				if (paneWidth < 925) //Change 925 to suit your program
				{
					return;
				}
			}

			/*Place other If-statements for other panels here.
			  just return; to not draw bitmap*/

			rect.top = (paneHeight  /2) - (bmInfo.bmHeight/2); //Centers vertically
			

			switch (paneAlignments[x])
			{

				case ISB_LEFTALIGN:
					 //Left
					rect.left +=3;
					
					break;

				case ISB_CENTERALIGN:
					//Center
					 center = (paneWidth /2) - (bmInfo.bmWidth/2);
					rect.left = center;
					break;

				case ISB_RIGHTALIGN:
					difference=  rect.right  - bmInfo.bmWidth-3;
					rect.left = difference;
					break;

			}

		dc->BitBlt(rect.left,rect.top ,bmInfo.bmWidth ,bmInfo.bmHeight,&compDC,0,0,SRCCOPY);
		dc->ExcludeClipRect(rect);
		SetPaneText(x+1,paneText,FALSE);
		compDC.DeleteDC();
		}
	}
	ReleaseDC(&compDC);
	ReleaseDC(dc);
}

void CImageStatusBar::SetBitmaps(UINT Bitmaps[],int Alignments[])
{
	//This function must be called in the parent window's Create()
	//It initializes the member variable arrays of Bitmap IDs and
	//Alignment flags (ISB_RIGHTALIGN,ISB_CENTERALIGN, ISB_RIGHTALIGN, and ISB_NOIMAGE)
	//to arrays passed by parent window
	for (int x = 0 ; x < MAX_BITMAPS ; x++)
	{
		paneBitmaps[x]= Bitmaps[x];
		paneAlignments[x] = Alignments[x];
	}
	

}






void CImageStatusBar::SetBitmap(int paneIndex,UINT bitmapID,int isbAlignment)
{
	//Sets (one) bitmap's ID and Alignment
	paneBitmaps[paneIndex-1] = bitmapID;
	paneAlignments[paneIndex-1] = isbAlignment;
}

