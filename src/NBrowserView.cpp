// NBrowserView.cpp : implementation of the CNBrowserView class
//

#include "stdafx.h"
#include "NBrowser.h"

#include "NBrowserDoc.h"
#include "NBrowserView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static DWORD ThreadId;
static DWORD ThreadCopyId;
static DWORD ThreadWaitId;
static HANDLE hThreads = NULL;
static HANDLE hCopyThreads = NULL;
static HANDLE hWaitThreads = NULL;
char strCopyFileFolder[256];

CListCtrl *g_ListCtrl;
char szShowCurrentFolder[256];
CList<CString,CString&> ListFileCopy;


int intWaitFlag;
   DWORD WINAPI CopyThreadProc(LPVOID lpParameter);
   DWORD WINAPI WaitThreadProc(LPVOID lpParameter);



      
static char strTest[255];

static int intSortField = 0;

// Sort the item in reverse alphabetical order.
static int CALLBACK  MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
   // lParamSort contains a pointer to the list view control.
   // The lParam of an item is just its index.
	sortindex *p_Param1 = (sortindex *)lParam1;
	sortindex *p_Param2 = (sortindex *)lParam2;

	switch(intSortField)
	{


	case SORT_BY_NAME: // SO
		{
		CString    strItem1 = p_Param1->FileName;
		CString    strItem2 = p_Param2->FileName;
		strItem1.MakeUpper();
		strItem2.MakeUpper();
		return strcmp(strItem1, strItem2);
		}
   
    case SORT_BY_LENGTH:   
		{
	      int k = (int) (p_Param1->lenfile - p_Param2->lenfile);
	      return k;
		}



	case SORT_BY_TYPE:
		{
     CString    strItem1 ; 
     CString    strItem2 ;
          strItem1 = p_Param1->fileType;
	   if (p_Param1->FileName[0]==FOLDERTYPE){
		  strItem1.Insert(0," "); 
	   } else {
		  strItem1.Insert(0,"1"); 
	   }


          strItem2 = p_Param2->fileType;
	   if (p_Param2->FileName[0]==FOLDERTYPE){
		  strItem2.Insert(0," "); 
	   } else {
		  strItem2.Insert(0,"1"); 
	   }


     strItem1.MakeUpper();
     strItem2.MakeUpper();
     return strcmp(strItem1, strItem2);
   }
	case SORT_BY_DATE_MODIFY:
      return CompareFileTime(&p_Param1->filetime,&p_Param2->filetime);
	}


return 0;
}




#define ODSsz(f, s)  {\
                     char        szDebug[128];\
                     wsprintf(szDebug, f, (LPSTR)s);\
                     OutputDebugString(szDebug);\
                     wsprintf(szDebug, " %s, %u\r\n", (LPSTR)__FILE__, __LINE__);\
                     OutputDebugString(szDebug);\
                     }

/////////////////////////////////////////////////////////////////////////////
// CNBrowserView

IMPLEMENT_DYNCREATE(CNBrowserView, CListView)

BEGIN_MESSAGE_MAP(CNBrowserView, CListView)
	//{{AFX_MSG_MAP(CNBrowserView)
	ON_WM_DROPFILES()
	ON_WM_MOUSEMOVE()
	ON_NOTIFY(HDN_ITEMCLICK, 0, OnItemclick) 
	ON_NOTIFY_REFLECT(LVN_DELETEITEM, OnDeleteitem)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(LVN_KEYDOWN, OnKeydown)
	ON_COMMAND(ID_VIEW_LARGEICON, OnViewLargeicon)
	ON_COMMAND(ID_VIEW_DETAILS, OnViewDetails)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNBrowserView construction/destruction

CNBrowserView::CNBrowserView()
{
   szCurrentFolder[0]=0;
   strCopyFileFolder[0]=0;

}

CNBrowserView::~CNBrowserView()
{
}

BOOL CNBrowserView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CNBrowserView drawing

void CNBrowserView::OnDraw(CDC* pDC)
{
	CNBrowserDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CListCtrl& refCtrl = GetListCtrl();
	refCtrl.InsertItem(0, "Item!");
	// TODO: add draw code for native data here
}




void CNBrowserView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
    DragAcceptFiles(TRUE);

	CListCtrl& ListCtrl = GetListCtrl();



	m_LargeImageList.Create(IDB_LARGEICONS, 32, 1, RGB(255, 255, 255));
	m_SmallImageList.Create(IDB_SMALLICONS, 16, 1, RGB(255, 255, 255));


	m_LargeImageList.SetOverlayImage(NUM_ITEMS, 1);
	m_SmallImageList.SetOverlayImage(NUM_ITEMS, 1);

	ListCtrl.SetImageList(&m_LargeImageList, LVSIL_NORMAL);
	ListCtrl.SetImageList(&m_SmallImageList, LVSIL_SMALL);


	int i;
	LV_COLUMN lvc;

	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	for(i = 0; i<NUM_COLUMNS; i++)
	{
		lvc.iSubItem = i;
		lvc.pszText = _gszColumnLabel[i];
		lvc.cx = _gnColumnWidth[i];
		lvc.fmt = _gnColumnFmt[i];
		ListCtrl.InsertColumn(i,&lvc);
	}


}

/////////////////////////////////////////////////////////////////////////////
// CNBrowserView printing

BOOL CNBrowserView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CNBrowserView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CNBrowserView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CNBrowserView diagnostics

#ifdef _DEBUG
void CNBrowserView::AssertValid() const
{
	CListView::AssertValid();
}

void CNBrowserView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CNBrowserDoc* CNBrowserView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNBrowserDoc)));
	return (CNBrowserDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNBrowserView message handlers
void CNBrowserView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{

	//TODO: add code to react to the user changing the view style of your window
}

VOID CNBrowserView::InsertFileList(char *pFileName, DWORD nFileSizeHigh, DWORD nFileSizeLow, char *strModify)
{
  char buf[80];
	CListCtrl& ListCtrl = GetListCtrl();
	LV_ITEM lvi;
    DWORD itemNum = ListCtrl.GetItemCount();


        int ika4 = -1;
		for (int i = strlen(pFileName);i> 0; i--){
			if (pFileName[i]=='.'){
				ika4 = i;
				break;
			}
		}

		CString strTemp;
		if (ika4 > 0 ) {
		    strTemp = CString(&pFileName[ika4+1]);
			strTemp.MakeLower();
		}



		int iMask=1;

		if (strTemp=="exe") iMask=0;

		lvi.mask = LVIF_TEXT | LVIF_IMAGE ;
		lvi.iItem = itemNum;
		lvi.iSubItem = 0;
		lvi.pszText = pFileName;
		lvi.iImage = 1;
		lvi.stateMask = LVIS_STATEIMAGEMASK;
		lvi.state = INDEXTOSTATEIMAGEMASK(iMask);

		ListCtrl.InsertItem(&lvi);

			ListCtrl.SetItemText(itemNum,0,pFileName);


			ListCtrl.SetItemText(itemNum,2,strTemp);
			ListCtrl.SetItemText(itemNum,3,strModify);
			ListCtrl.SetItemText(itemNum,0,pFileName);

         long fSize = (nFileSizeHigh * MAXDWORD) + nFileSizeLow;
		 sprintf(buf,"%dKB",fSize/1024);

			ListCtrl.SetItemText(itemNum,1,buf);
			ListCtrl.SetItemData(itemNum,itemNum);
}


void CNBrowserView::OnDropFiles(HDROP hdrop) 
{


WORD cFiles, a; 
char lpszFile[MAX_PATH]; 

if (strlen(szCurrentFolder) == 0 ){
MessageBox("Please select your destination folder" ,"Error",MB_OK | MB_ICONERROR );
    DragFinish(hdrop);
} else {

	if (strlen(strCopyFileFolder) > 0 ) {
        MessageBox("Please wait. Process is busy" ,"Error",MB_OK | MB_ICONERROR );
	} else {

ListFileCopy.RemoveAll(); 
cFiles = DragQueryFile(hdrop, -1, NULL, 0); 
for(a = 0; a < cFiles; a++) { 
    DragQueryFile(hdrop, a, lpszFile, sizeof(lpszFile)); 
    ODSsz("CFileViewer::DropFiles filename=%s", lpszFile);
	CString pStr;
	pStr = CString(lpszFile);
	ListFileCopy.AddTail(pStr);
} 
 
	 intWaitFlag = 1;
     hWaitThreads = CreateThread(NULL,0,WaitThreadProc,
                                   (LPVOID)this,0,&ThreadWaitId);

	strcpy(strCopyFileFolder,szShowCurrentFolder);
         hCopyThreads = CreateThread(NULL,0,CopyThreadProc,
                                   (LPVOID)this,0,&ThreadCopyId);


	}  

    DragFinish(hdrop);
	
	CListView::OnDropFiles(hdrop);


} 

}

void CNBrowserView::SetFolderName(char *szPath)
{
  strcpy(szCurrentFolder,szPath);
  RestoreFileList();
}


   DWORD WINAPI CopyThreadProc(LPVOID lpParameter)
   {

    CNBrowserView *pW = ((CNBrowserView *)lpParameter);

	CString pStr;

POSITION pos = ListFileCopy.GetHeadPosition();
for (int i=0;i < ListFileCopy.GetCount();i++)
{
   pStr =  ListFileCopy.GetNext(pos);
	pW->MyCopyFile(pStr.GetBuffer(2));
}



	 intWaitFlag = 0;
	 Sleep(900);




	 
     PostMessage(AfxGetMainWnd()->GetSafeHwnd(), WM_EXIT_COPY, 
                EXIT_COPY_FILE_STATUS, 0);

	 return 0;
   }



   DWORD WINAPI WaitThreadProc(LPVOID lpParameter)
   {
	
	   while (intWaitFlag == 1 ){
		CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
		pFrame->m_wndStatusBar.SetBitmap(1,IDB_WAIT_SAVE,ISB_RIGHTALIGN);
		pFrame->m_wndStatusBar.Invalidate();
		Sleep(400);
		pFrame->m_wndStatusBar.SetBitmap(1,IDB_WAIT_SAVE_M,ISB_RIGHTALIGN);
		pFrame->m_wndStatusBar.Invalidate();
	     Sleep(200);
	   }
	return 0;

   }

   DWORD WINAPI ThreadProc(LPVOID lpParameter)
   {
	CNBrowserView *p_BrowserV = (CNBrowserView *) lpParameter;

		g_ListCtrl->DeleteAllItems(); 
    CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	pFrame->m_wndStatusBar.SetBitmap(3,IDB_NETWORK_ON,ISB_RIGHTALIGN);
	pFrame->m_wndStatusBar.Invalidate();

   WIN32_FIND_DATA FileData;   // Data structure describes the file found
  HANDLE hSearch;             // Search handle returned by FindFirstFile
  TCHAR szNewPath[MAX_PATH];  // Name and path of the file copied
  TCHAR szDirPath[MAX_PATH];


     strcpy(szDirPath,szShowCurrentFolder);
     strcat(szDirPath,"\\*.*");

     BOOL bFinished = FALSE;

  // Start searching for .txt files in the root directory.

     hSearch = FindFirstFile (szDirPath, &FileData);
     if (hSearch == INVALID_HANDLE_VALUE)
	 {
	    pFrame->m_wndStatusBar.SetBitmap(3,IDB_NETWORK_ERR,ISB_RIGHTALIGN);
		pFrame->m_wndStatusBar.Invalidate();
        return 0;
	 }

     while (!bFinished)
  {
    lstrcpy (szNewPath, szDirPath);
    lstrcat (szNewPath, TEXT("\\"));
    lstrcat (szNewPath, FileData.cFileName);


   FILETIME ftLocal;

	  CString strDateModify;

      SYSTEMTIME st;

      
       FileTimeToLocalFileTime(&(FileData.ftLastWriteTime), &ftLocal );

      FileTimeToSystemTime( &ftLocal, &st );
      strDateModify.Format(_T("%02d/%02d/%d %02d:%02d:%02d"),st.wDay,st.wMonth,st.wYear,st.wHour,st.wMinute,st.wSecond);    	   

      
//----------------------------------
 //      
	  	char pFileName[256];
		strcpy(pFileName,FileData.cFileName);
		CString strTemp("");
		int iMask=1;


		if (pFileName[0]!='.'){
 
      if ((FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
      {
		iMask = 27;
		strTemp = "File Folder";
      }
      else
	  {

  
        int ika4 = -1;
		for (int i = strlen(pFileName);i> 0; i--){
			if (pFileName[i]=='.'){
				ika4 = i;
				break;
			}
		}


		if (ika4 > 0 ) {
		    strTemp = CString(&pFileName[ika4+1]);
			strTemp.MakeLower();
		}

		if (strTemp == "exe") iMask = 0;
		if (strTemp == "bmp") iMask = 2;
		if (strTemp == "ini") iMask = 3;
		if (strTemp == "doc") iMask = 4;
		if (strTemp == "lst") iMask = 5;
		if (strTemp == "txt") iMask = 5;
		if (strTemp == "log") iMask = 5;
		if (strTemp == "dll") iMask = 6;
		if (strTemp == "ocx") iMask = 6;
		if (strTemp == "drv") iMask = 6;
		if (strTemp == "avi") iMask = 7;
		if (strTemp == "zip") iMask = 8;
		if (strTemp == "b64") iMask = 8;
		if (strTemp == "bhx") iMask = 8;
		if (strTemp == "cab") iMask = 17;
		if (strTemp == "htm") iMask = 9;
		if (strTemp == "html") iMask = 9;
		if (strTemp == "xls") iMask = 10;
		if (strTemp == "xlt") iMask = 10;
		if (strTemp == "xlshtml") iMask = 10;
		if (strTemp == "xlthtml") iMask = 10;
		if (strTemp == "csv") iMask = 11;
		if (strTemp == "reg") iMask = 12;
		if (strTemp == "mdb") iMask = 13;
		if (strTemp == "asa") iMask = 14;
		if (strTemp == "asp") iMask = 15;
		if (strTemp == "bat") iMask = 16;
		if (strTemp == "cer") iMask = 18;
		if (strTemp == "chm") iMask = 19;
		if (strTemp == "cpp") iMask = 20;
		if (strTemp == "crl") iMask = 21;
		if (strTemp == "fon") iMask = 22;
		if (strTemp == "gif") iMask = 23;
		if (strTemp == "hlp") iMask = 24;
		if (strTemp == "ins") iMask = 25;
		if (strTemp == "jpg") iMask = 26;
		if (strTemp == "jpeg") iMask = 26;
		if (strTemp == "js") iMask = 28;
		if (strTemp == "msi") iMask = 29;
		if (strTemp == "pdf") iMask = 30;
		if (strTemp == "rtf") iMask = 31;
		if (strTemp == "ppt") iMask = 32;
		if (strTemp == "pot") iMask = 33;
		if (strTemp == "zap") iMask = 34;
		if (strTemp == "ttf") iMask = 35;
		if (strTemp == "wav") iMask = 36;
		if (strTemp == "xml") iMask = 37;
		if (strTemp == "xsl") iMask = 38;
		if (strTemp == "wri") iMask = 39;
		if (strTemp == "vbs") iMask = 40;
		if (strTemp == "wsf") iMask = 40;
	  }

//
	LV_ITEM lvi;
    DWORD itemNum = g_ListCtrl->GetItemCount();

		lvi.mask = LVIF_TEXT | LVIF_IMAGE ;
		lvi.iItem = itemNum;
		lvi.iSubItem = 0;
		lvi.pszText = pFileName;
		lvi.iImage = iMask;
		lvi.stateMask = LVIS_STATEIMAGEMASK;
		lvi.state = INDEXTOSTATEIMAGEMASK(iMask);

		g_ListCtrl->InsertItem(&lvi);

			g_ListCtrl->SetItemText(itemNum,0,pFileName);

			g_ListCtrl->SetItemText(itemNum,2,strTemp);

			g_ListCtrl->SetItemText(itemNum,3,strDateModify);
			g_ListCtrl->SetItemText(itemNum,0,pFileName);

		 long fSize;	 
         fSize = (FileData.nFileSizeHigh * MAXDWORD) + FileData.nFileSizeLow;
		 char buf[256];
		 sprintf(buf,"%dKB",fSize/1024);

		 if (iMask == 27){
			g_ListCtrl->SetItemText(itemNum,1," ");
		 } else {
			g_ListCtrl->SetItemText(itemNum,1,buf);
		 }

			sortindex *p_sortIndex;
			p_sortIndex = new sortindex;


			char sortName[255];
			sortName[0]=0;
			if (iMask == 27 ){
			  sortName[0]=FOLDERTYPE;
			  sortName[1]=0;
			}
			strcat(sortName,pFileName);
			strcpy(p_sortIndex->FileName,sortName);
			p_sortIndex->lenfile = fSize;
			strcpy(p_sortIndex->fileType,strTemp);
			p_sortIndex->filetime = FileData.ftLastWriteTime;

			g_ListCtrl->SetItemData(itemNum,(LPARAM)p_sortIndex);
		}

//----------------------------------

    if (!FindNextFile (hSearch, &FileData))
    {
      bFinished = TRUE;

      if (GetLastError () == ERROR_NO_MORE_FILES)
      {
//        wsprintf (szMsg, TEXT("Found all of the files."));
      }
      else
      {
//        wsprintf (szMsg, TEXT("Unable to find next file."));
      }
    }
  }

  // Close the search handle.

  if (!FindClose (hSearch))
  {

  }

//-------
 
       g_ListCtrl->SortItems(MyCompareProc, (LPARAM) g_ListCtrl);

       PostMessage(AfxGetMainWnd()->GetSafeHwnd(), WM_EXIT_COPY, 
                EXIT_RESTORE_LIST, 0);


 


	return 0;      
   }






void CNBrowserView::RestoreFileList()
{

if (strlen(szCurrentFolder) == 0 ){
MessageBox("Please select your destination folder" ,"Error",MB_OK | MB_ICONERROR );
} else {


	CListCtrl& ListCtrl = GetListCtrl();
	g_ListCtrl = &ListCtrl; 
	strcpy(szShowCurrentFolder,szCurrentFolder);


		CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();

	if (hThreads != NULL ){
	  TerminateThread(hThreads,0);
	  hThreads = NULL;
	}

         hThreads = CreateThread(NULL,0,ThreadProc,
                                   (LPVOID)this,0,&ThreadId);
         if (hThreads == INVALID_HANDLE_VALUE){
		}     



  



}
}



void CNBrowserView::OnMouseMove(UINT nFlags, CPoint point) 
{
	  ((CMainFrame *)AfxGetMainWnd( ))->m_wndStatusBar.SetPaneText(0,szCurrentFolder);

	
	CListView::OnMouseMove(nFlags, point);
}

void CNBrowserView::MyCopyFile(char *strSrcInp)
{
	char strDesc[256];
	char strSrc[256];
	char strMessage[500];
	strcpy(strSrc,strSrcInp);
	strcpy(strDesc,strCopyFileFolder);
	strcat(strDesc,"\\");
	int ika4=0;
	for (int i=strlen(strSrcInp);i>0;i--){
		if (strSrcInp[i-1]=='\\'){
			ika4 = i;
			break;
		}
	}
   strcat(strDesc,&strSrcInp[ika4]);

   WIN32_FIND_DATA FileData;   // Data structure describes the file found
   HANDLE hSearch;             // Search handle returned by FindFirstFile
     hSearch = FindFirstFile (strDesc, &FileData);
     if (hSearch != INVALID_HANDLE_VALUE)
	 {
		 strcpy(strMessage,"This folder already contents a file named '");
		 strcat(strMessage,&strSrcInp[ika4]);
		 strcat(strMessage,"' Would you like to replace the existing file:"); 
		 if (MessageBox(strMessage,"Confirm File Replace",MB_YESNO | MB_ICONQUESTION )== IDYES ){
               CopyFile(strSrc,strDesc,FALSE);
			 }
		 FindClose (hSearch);
	 } else {
        CopyFile(strSrc,strDesc,FALSE);
	 }
  
}


void CNBrowserView::OnItemclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
    intSortField = phdn->iItem;


	CListCtrl& ListCtrl = GetListCtrl();
    CListCtrl* pmyListCtrl = &ListCtrl;
    ListCtrl.SortItems(MyCompareProc, (LPARAM) pmyListCtrl);
	
	*pResult = 0;
}

void CNBrowserView::OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
			sortindex *p_sortIndex;
			p_sortIndex = (sortindex *)pNMListView->lParam;
			delete p_sortIndex;


	*pResult = 0;
}

void CNBrowserView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{


    int nItem, nFlags;
    nFlags = LVNI_SELECTED;

	CListCtrl& ListCtrl = GetListCtrl();

    nItem = ListCtrl.GetNextItem(-1, nFlags );
    if ( nItem != -1 )
    {
	  sortindex *p_sortIndex = (sortindex *)(ListCtrl.GetItemData(nItem));
			if (p_sortIndex->FileName[0]== FOLDERTYPE ){
				CString strPath;
				strPath.Format(_T("%s\\%s"),szCurrentFolder,&(p_sortIndex->FileName[1]));

          CWnd *pWnd = (CMainFrame *)AfxGetMainWnd();
		  CMainFrame *pFrame =   DYNAMIC_DOWNCAST(CMainFrame, pWnd);
		  CLeftView *p_Left =(CLeftView *)pFrame->GetLeftPane();
 		  p_Left->SelectItemByName(strPath);
			}

    }




	*pResult = 0;
}

void CNBrowserView::UpOneLevel()
{
	if (strlen(szCurrentFolder) > 0 ){
	char szTemp[256];
	strcpy(szTemp,szCurrentFolder);
	for (int j=strlen(szTemp); j> 0; j-- ){
		if (szTemp[j] == '\\'){
		  szTemp[j] = 0;

          CWnd *pWnd = (CMainFrame *)AfxGetMainWnd();
		  CMainFrame *pFrame =   DYNAMIC_DOWNCAST(CMainFrame, pWnd);
		  CLeftView *p_Left =(CLeftView *)pFrame->GetLeftPane();
 		  p_Left->SelectItemByName(CString(szTemp));
		  break;
		}
	}
	}
}

void CNBrowserView::CheckTreeFolder()
{

    CTreeCtrl *p_Ctrl;
  CWnd *pWnd = (CMainFrame *)AfxGetMainWnd();
  CMainFrame *pFrame =   DYNAMIC_DOWNCAST(CMainFrame, pWnd);
  CLeftView *p_Left =(CLeftView *)pFrame->GetLeftPane();
		p_Ctrl = p_Left->MGetTreeCtrl();

	HTREEITEM htiCurrent = NULL;
    HTREEITEM hItem = p_Ctrl->GetSelectedItem();


     htiCurrent = TreeView_GetNextItem(p_Ctrl->m_hWnd,hItem,TVGN_CHILD);
	if (htiCurrent != NULL){
		TVITEM tvi;
		char BufWork[256];

        tvi.mask = TVIF_TEXT; 
        tvi.hItem = htiCurrent; 
		tvi.pszText = BufWork;
		tvi.cchTextMax = 250;

		TreeView_GetItem(p_Ctrl->m_hWnd , &tvi); 



		if (strcmp(FOLDER_IN_PROGRESS,BufWork) == 0 ) {

		//------- add  folders in the tree
	    TreeView_DeleteItem(p_Ctrl->m_hWnd,htiCurrent);

		//-----
	CListCtrl *pList = &GetListCtrl();

	int intCount = pList->GetItemCount();
	sortindex *p_sortindex;

for (int nItem=0;nItem < intCount ;nItem++)
{

	  CString strFileName = pList->GetItemText(nItem, 0);
	  p_sortindex = (sortindex *)pList->GetItemData(nItem);
	
		CString strFullNameF;
		strFullNameF.Format(_T("%s\\%s"),szCurrentFolder,strFileName);

		DWORD dwAttr = GetFileAttributes(strFullNameF);
        if (p_sortindex->FileName[0]== FOLDERTYPE ){
			HTREEITEM m_hTemp = p_Ctrl->InsertItem(strFileName, hItem, TVI_SORT);
	        HTREEITEM m_hTemp1 = p_Ctrl->InsertItem(FOLDER_IN_PROGRESS, m_hTemp, TVI_SORT);

		} 
}
//-------

		}
	}

}

void CNBrowserView::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	if (VK_DELETE == pLVKeyDow->wVKey){
		DeleteFile();
	}
	*pResult = 0;
}

void CNBrowserView::DeleteFile()
{
	CListCtrl *pList = &GetListCtrl();

POSITION pos = pList->GetFirstSelectedItemPosition();
if (pos == NULL){
}
else
{
   while (pos)
   {
      int nItem = pList->GetNextSelectedItem(pos);
	  CString strFileName = pList->GetItemText(nItem, 0);
	  CString strMessage;
		CString strF;
		strF.LoadString(IDS_DETETE_Q);
	    strMessage.Format(strF,strFileName);
	
		CString strFullNameF;
		strFullNameF.Format(_T("%s\\%s"),szCurrentFolder,strFileName);

		DWORD dwAttr = GetFileAttributes(strFullNameF);
		if (dwAttr== FILE_ATTRIBUTE_DIRECTORY ){
   //		RemoveDirectory(strFullNameF);
		} else {
   	       if (MessageBox(strMessage,"Confirm File Delete",MB_YESNO | MB_ICONQUESTION )== IDYES ){
		      ::DeleteFile(strFullNameF);
	  }
		}


    }
}


	RestoreFileList();
	
}

void CNBrowserView::OnViewLargeicon() 
{
this->Invalidate();	
}

void CNBrowserView::OnViewDetails() 
{
this->Invalidate();
}
