// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include <commctrl.h>
#include "NBrowser.h"

#include "NBrowserDoc.h"
#include "LeftView.h"
#include "MainFrm.h"
#include "NBrowserView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemexpanded)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(TVN_SELCHANGING, OnSelchanging)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView()
{
	m_pTreeCtrl = NULL;
	m_pimagelist = NULL;
	mi_olditem = -1;

}

CLeftView::~CLeftView()
{
	delete m_pimagelist;
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	CNBrowserDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


/////////////////////////////////////////////////////////////////////////////
// CLeftView printing

BOOL CLeftView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLeftView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLeftView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CNBrowserDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNBrowserDoc)));
	return (CNBrowserDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

int CLeftView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pimagelist = new CImageList();
    m_pimagelist->Create(16, 16, TRUE/*bMask*/,	4, ILC_COLOR8);
	mi_nClose = m_pimagelist->Add(AfxGetApp()->LoadIcon(IDI_CLOSE_FOLDER));
	mi_nOpen = m_pimagelist->Add(AfxGetApp()->LoadIcon(IDI_OPEN_FOLDER));
	mi_nComputer = m_pimagelist->Add(AfxGetApp()->LoadIcon(IDI_MY_LOCAL_COMPUTER));
	CreateDriveList();

	//Set background color of treeview. TVM_SETBKCOLOR requires Version 4.71 or newer of Comctl32.dll.
	//You can get an update to this DLL by installing the newest service pack for your OS.
	m_pTreeCtrl->SendMessage(TVM_SETBKCOLOR, 0, RGB(128,128,128)); // change the background color
	m_pTreeCtrl->SendMessage(TVM_SETTEXTCOLOR,0,RGB(255,255,255));
	LONG style = ::GetWindowLong(m_pTreeCtrl->m_hWnd, GWL_STYLE);


#define TVM_SETLINECOLOR            (TV_FIRST + 40)

	m_pTreeCtrl->SendMessage(TVM_SETLINECOLOR,0,RGB(49,0,99));
	
	DWORD m_dwDefaultStyle =  WS_CHILD | WS_VISIBLE | TVS_HASLINES  
			 | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS;  

	::SetWindowLong(m_pTreeCtrl->m_hWnd, GWL_STYLE, m_dwDefaultStyle);  // remove the style TVS_HASLINES
	m_pTreeCtrl->SetImageList(m_pimagelist,TVSIL_NORMAL);
		
	ShowWindow(SW_SHOW);
	UpdateWindow();	
	
	return 0;
}







VOID CLeftView::CreateDriveList()
{
	m_pTreeCtrl = &(GetTreeCtrl());
	





//	hTreeViewsDocuments = m_pTreeCtrl->InsertItem("My Local Documents", TVI_ROOT, TVI_FIRST);
//	m_hRightPaneFormView1        = m_pTreeCtrl->InsertItem("Form View 1"			, hTreeViewsDocuments);

	hTreeComputer   = m_pTreeCtrl->InsertItem(MY_LOCAL_COMPUTER, TVI_ROOT, TVI_LAST);
	SetFolderIcon(hTreeComputer,mi_nComputer);

    CreateMyLocalComputer(hTreeComputer);





	m_pTreeCtrl->Expand(hTreeComputer  , TVE_EXPAND);   
	m_pTreeCtrl->Expand(hTreeViewsDocuments  , TVE_EXPAND); 

}


void CLeftView::OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	


	HTREEITEM	hti;

 
       hti = (HTREEITEM)(pNMTreeView->itemNew).hItem; 



	*pResult = 0;
}

VOID CLeftView::SetFolderIcon(HTREEITEM hti,DWORD mi_nOpen_Close)

{


    TVITEM tvi; 
    
        tvi.mask = 
            TVIF_IMAGE |  
            TVIF_PARAM |
            TVIF_STATE | TVIF_SELECTEDIMAGE ; 

        tvi.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_STATE ; 
        tvi.hItem = hti; 

		TreeView_GetItem(m_pTreeCtrl->m_hWnd , &tvi); 



           tvi.hItem = hti; 
           tvi.iImage = mi_nOpen_Close; 
           tvi.iSelectedImage = mi_nOpen_Close; 
		TreeView_SetItem(m_pTreeCtrl->m_hWnd, &tvi); 

}


static HTREEITEM TreeWorkItemParent = NULL;
static HANDLE TreehThreads;
DWORD WINAPI TreeThreadProc(LPVOID lpParameter);
static DWORD TreeThreadId;
static BOOL WorkShowFile;



VOID CLeftView::RestoreFoldrer(HTREEITEM itemParent,BOOL showFile)
{

	   if (TreeWorkItemParent != NULL ){
	   } else {
		   WorkShowFile = showFile;
		   TreeWorkItemParent = itemParent;
         TreehThreads = CreateThread(NULL,0,TreeThreadProc,
                                   (LPVOID)this,0,&TreeThreadId);
	   }
}

   DWORD WINAPI TreeThreadProc(LPVOID lpParameter)
   {

   TVITEM tvi;
   CLeftView *p_LeftView = (CLeftView *)lpParameter;

	char BufWork[255];

      tvi.mask = TVIF_STATE | TVIF_TEXT; 
        tvi.hItem = TreeWorkItemParent; 
		tvi.pszText = BufWork;
		tvi.cchTextMax = 250;
		TreeView_GetItem(p_LeftView->m_pTreeCtrl->m_hWnd , &tvi); 


  if (strcmp(BufWork,MY_LOCAL_COMPUTER) == 0 ){
          p_LeftView->ClearAllChield(TreeWorkItemParent);
          p_LeftView->CreateMyLocalComputer(TreeWorkItemParent);
  } else {
   WIN32_FIND_DATA FileData;   // Data structure describes the file found
  HANDLE hSearch;             // Search handle returned by FindFirstFile
  TCHAR szNewPath[MAX_PATH];  // Name and path of the file copied



    
        tvi.mask = 
            TVIF_IMAGE |  
            TVIF_PARAM |
            TVIF_STATE | TVIF_SELECTEDIMAGE ; 

        tvi.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_STATE ; 
        tvi.hItem = TreeWorkItemParent; 

		TreeView_GetItem(p_LeftView->m_pTreeCtrl->m_hWnd , &tvi); 


 TCHAR szDirPath[255];
 p_LeftView->CreatePathForHeaderTree(TreeWorkItemParent, szDirPath);

	if (WorkShowFile == TRUE ){	
	} else {

     strcat(szDirPath,"\\*.*");

     BOOL bFinished = FALSE;
     HTREEITEM m_hRightPaneFormViewTemp;
	 HTREEITEM m_hRightPaneFormViewTemp2;

  // Start searching for .txt files in the root directory.

     hSearch = FindFirstFile (szDirPath, &FileData);
     if (hSearch == INVALID_HANDLE_VALUE)
	 {
		 TreeWorkItemParent = NULL;

        return 0;
	 }

          p_LeftView->ClearAllChield(TreeWorkItemParent);

     while (!bFinished)
  {
    lstrcpy (szNewPath, szDirPath);
    lstrcat (szNewPath, TEXT("\\"));
    lstrcat (szNewPath, FileData.cFileName);

 
      if ((FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
      {
		  if (FileData.cFileName[0]!='.'){
		if (WorkShowFile == FALSE ){
		     m_hRightPaneFormViewTemp = p_LeftView->m_pTreeCtrl->InsertItem(FileData.cFileName, TreeWorkItemParent, TVI_SORT);
			 	     m_hRightPaneFormViewTemp2 = p_LeftView->m_pTreeCtrl->InsertItem(FOLDER_IN_PROGRESS, m_hRightPaneFormViewTemp, TVI_SORT);

		}
		  }

      }
      else
	  {
		  if (WorkShowFile == TRUE ) { // show list files


//		((CMainFrame *)AfxGetMainWnd( ))->GetRightPane()->InsertFileList(FileData.cFileName,0,0,"test"); 


		  }
	  }

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
  }
  }
  TreeWorkItemParent = NULL;
  p_LeftView->m_pTreeCtrl->Invalidate();

  return 0;
}

void CLeftView::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{

	*pResult = 0;
}

void CLeftView::OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	HTREEITEM	hti;
    hti = (HTREEITEM)(pNMTreeView->itemOld).hItem;

   TVITEM tvi;

	char BufWork[255];

      tvi.mask = TVIF_STATE | TVIF_TEXT; 
        tvi.hItem = hti; 
		tvi.pszText = BufWork;
		tvi.cchTextMax = 250;
		TreeView_GetItem(m_pTreeCtrl->m_hWnd , &tvi); 


  if (strcmp(BufWork,MY_LOCAL_COMPUTER) != 0 ){
	SetFolderIcon(hti,mi_nClose);
  }

    hti = (HTREEITEM)(pNMTreeView->itemNew).hItem;	

    tvi.mask = TVIF_STATE | TVIF_TEXT; 
        tvi.hItem = hti; 
		tvi.pszText = BufWork;
		tvi.cchTextMax = 250;
		TreeView_GetItem(m_pTreeCtrl->m_hWnd , &tvi); 


  if (strcmp(BufWork,MY_LOCAL_COMPUTER) != 0 ){
	SetFolderIcon(hti,mi_nOpen);
  }

    TCHAR szDirPath[255];
    CreatePathForHeaderTree(hti, szDirPath);
    
      ((CMainFrame *)AfxGetMainWnd( ))->GetRightPane()->SetFolderName(szDirPath);
	  ((CMainFrame *)AfxGetMainWnd( ))->m_wndStatusBar.SetPaneText(0,szDirPath);
  
	
	*pResult = 0;
}

VOID CLeftView::ClearAllChield(HTREEITEM itemParent)
{

	HTREEITEM htiCurrent = NULL;
     htiCurrent = TreeView_GetNextItem(m_pTreeCtrl->m_hWnd,itemParent,TVGN_CHILD);
	while (htiCurrent != NULL){
	 TreeView_DeleteItem(m_pTreeCtrl->m_hWnd,htiCurrent);
     htiCurrent = TreeView_GetNextItem(m_pTreeCtrl->m_hWnd,itemParent,TVGN_CHILD);
	}
}

VOID CLeftView::ResporeChieldFolder(HTREEITEM itemParent)
{
	     HTREEITEM m_hRightPaneFormViewTemp;

	HTREEITEM htiCurrent = NULL;
     htiCurrent = TreeView_GetNextItem(m_pTreeCtrl->m_hWnd,itemParent,TVGN_CHILD);
	while (htiCurrent != NULL){
		     m_hRightPaneFormViewTemp = m_pTreeCtrl->InsertItem(FOLDER_IN_PROGRESS, htiCurrent, TVI_SORT);

		htiCurrent = TreeView_GetNextItem(m_pTreeCtrl->m_hWnd,htiCurrent,TVGN_NEXT);
	}

}



VOID CLeftView::CreatePathForHeaderTree(HTREEITEM itemParent, char *pBuf)
{
	char TempBuf[255];
	char Temp2[255];

	Temp2[0]=0;
	TempBuf[0]=0;
	char BufWork[255];
   TVITEM tvi; 
   char *inaStr;

	HTREEITEM htiCurrent = NULL;
       tvi.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_STATE | TVIF_TEXT; 
        tvi.hItem = itemParent; 
		tvi.pszText = BufWork;
		tvi.cchTextMax = 250;
		TreeView_GetItem(m_pTreeCtrl->m_hWnd , &tvi); 

		inaStr = strchr(BufWork,'(');
		if (inaStr == NULL ){
		  strcpy(TempBuf,BufWork);
		} else {
		  inaStr++;
		  strcpy(TempBuf,inaStr);
		  inaStr = strchr(TempBuf,')');
		  if (inaStr != NULL ){
			  *inaStr = 0;
		  }
		}


     htiCurrent = TreeView_GetNextItem(m_pTreeCtrl->m_hWnd,itemParent,TVGN_PARENT );



  while (htiCurrent != NULL){


    
        tvi.mask = TVIF_TEXT; 
        tvi.hItem = htiCurrent; 
		tvi.pszText = BufWork;
		tvi.cchTextMax = 250;

		TreeView_GetItem(m_pTreeCtrl->m_hWnd , &tvi); 
		if (strcmp(MY_LOCAL_COMPUTER,BufWork) != 0 ) {
		strcpy(Temp2,TempBuf);

		inaStr = strchr(BufWork,'(');
		if (inaStr == NULL ){
		  strcpy(TempBuf,BufWork);
		} else {
		  inaStr++;
		  strcpy(TempBuf,inaStr);
		  inaStr = strchr(TempBuf,')');
		  if (inaStr != NULL ){
			  *inaStr = 0;
		  }
		}
		if (strlen(Temp2) > 0 ){
		  strcat(TempBuf,"\\");
		  strcat(TempBuf,Temp2);
		}
		}

     htiCurrent = TreeView_GetNextItem(m_pTreeCtrl->m_hWnd,htiCurrent,TVGN_PARENT);
	}
   strcpy(pBuf,TempBuf);
}





VOID CLeftView::CreateMyLocalComputer(HTREEITEM item)
{



    UINT uType;
	HTREEITEM  hTreeMammals;
	char driveName[25];
	char strShowName[255];
	strcpy(driveName,"C:");

	char VolumeNameBuffer[MAX_PATH];
	 char FileSystemNameBuffer[MAX_PATH];
	 DWORD VolumeSerialNumber;
	 DWORD MaximumComponentLength;
     DWORD FileSystemFlags;
	 DWORD FileSystemNameSize;
	 DWORD nVolumeNameSize;

   
	for (UINT nDrive = 2;nDrive < 30; nDrive++){
		  driveName[0]='C'+nDrive-2;
       uType = GetDriveType (driveName);
	   
     switch (uType)
      {
//       DRIVE_UNKNOWN The drive type cannot be determined. 
//       DRIVE_NO_ROOT_DIR The root path is invalid. For example, no volume is mounted at the path. 
	 case DRIVE_REMOVABLE: // The disk can be removed from the drive. 
	 case DRIVE_FIXED:     // The disk cannot be removed from the drive. 
	 case DRIVE_REMOTE:    // The drive is a remote (network) drive. 
	 case DRIVE_CDROM:  // The drive is a CD-ROM drive. 
	 case DRIVE_RAMDISK: // The drive is a RAM disk. 
		 
	 nVolumeNameSize = MAX_PATH;
	 FileSystemNameSize = MAX_PATH;
     GetVolumeInformation(
         driveName,           // root directory
         VolumeNameBuffer,        // volume name buffer
         nVolumeNameSize,            // length of name buffer
         &VolumeSerialNumber,     // volume serial number
         &MaximumComponentLength, // maximum file name length
         &FileSystemFlags,        // file system options
         FileSystemNameBuffer,    // file system name buffer
         FileSystemNameSize         // length of file system name buffer
);




	 strcpy(strShowName,VolumeNameBuffer);
	 strcat(strShowName, " (");
	 strcat(strShowName, driveName);
	 strcat(strShowName, ") ");
//	 strcat(strShowName, FileSystemNameBuffer);
	 




   char strTestFile[255];
   strcpy(strTestFile,driveName);
   strcat(strTestFile,"\\NBrowser.sys");


   DWORD dwTestFile =GetFileAttributes(strTestFile);


     if (GetLastError())
	 {
   WIN32_FIND_DATA FileData;   // Data structure describes the file found
   HANDLE hSearch;             // Search handle returned by FindFirstFile
     hSearch = FindFirstFile (strTestFile, &FileData);
     if (hSearch == INVALID_HANDLE_VALUE){
		 if (GetLastError()== ERROR_FILE_NOT_FOUND){
	      hTreeMammals = m_pTreeCtrl->InsertItem(strShowName, hTreeComputer, TVI_LAST);
		 }
	 } else {
		 FindClose (hSearch);
	 }
	 } 
	 }
	}
	ResporeChieldFolder(hTreeComputer);
	m_pTreeCtrl->Invalidate();

}

void CLeftView::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;


	HTREEITEM	hti;

 
       hti = (HTREEITEM)(pNMTreeView->itemNew).hItem; 




	HTREEITEM htiCurrent = NULL;
     htiCurrent = TreeView_GetNextItem(m_pTreeCtrl->m_hWnd,hti,TVGN_CHILD);
	if (htiCurrent != NULL){
		TVITEM tvi;
		char BufWork[256];

        tvi.mask = TVIF_TEXT; 
        tvi.hItem = htiCurrent; 
		tvi.pszText = BufWork;
		tvi.cchTextMax = 250;

		TreeView_GetItem(m_pTreeCtrl->m_hWnd , &tvi); 



		if (strcmp(FOLDER_IN_PROGRESS,BufWork) == 0 ) {
		  RestoreFoldrer(hti);
		} else {
		
		}
    }


	
	*pResult = 0;
}

void CLeftView::RestoreCurrentFolder()
{

}

void CLeftView::Refresh()
{

	HTREEITEM htiCurrent = NULL;
    m_pTreeCtrl = &(GetTreeCtrl());
    HTREEITEM hItem = m_pTreeCtrl->GetSelectedItem();

     m_pTreeCtrl->Expand(hItem, TVE_COLLAPSE);
   
    ClearAllChield(hItem);
    htiCurrent = m_pTreeCtrl->InsertItem(FOLDER_IN_PROGRESS, hItem, TVI_SORT);

}

CTreeCtrl * CLeftView::MGetTreeCtrl()
{
    return &(GetTreeCtrl());
}




	  HTREEITEM CLeftView::FindCurrentItem(CTreeCtrl *m_pTreeCtrl,HTREEITEM htiWork1,CString strFin){
  		  TVITEM tvi;
		  HTREEITEM htiWork= htiWork1;
		  char BufWork[256];
		  BOOL boolOK = FALSE;
	while (htiWork != NULL){


        tvi.mask = TVIF_TEXT; 
        tvi.hItem = htiWork; 
		tvi.pszText = BufWork;
		tvi.cchTextMax = 250;

		TreeView_GetItem(m_pTreeCtrl->m_hWnd , &tvi); 

		if (strFin== CString(BufWork) ) {
			return htiWork;
		}

		htiWork = TreeView_GetNextItem(m_pTreeCtrl->m_hWnd,htiWork,TVGN_NEXT);
	}


	return NULL;
	  }



void CLeftView::SelectItemByName(CString strPath)
{


	HTREEITEM htiCurrent = NULL;
    m_pTreeCtrl = &(GetTreeCtrl());
    HTREEITEM hItem = m_pTreeCtrl->GetRootItem();


	HTREEITEM htiWork = NULL;
     htiCurrent = TreeView_GetNextItem(m_pTreeCtrl->m_hWnd,hItem,TVGN_CHILD);



		TVITEM tvi;
		char BufWork[256];
		char compStr[256];

	compStr[0]=(strPath.GetBuffer(3))[0];
	compStr[1]=(strPath.GetBuffer(3))[1];
	compStr[2]=0;
	BOOL boolOK= FALSE;

	while (htiCurrent != NULL){


        tvi.mask = TVIF_TEXT; 
        tvi.hItem = htiCurrent; 
		tvi.pszText = BufWork;
		tvi.cchTextMax = 250;

		TreeView_GetItem(m_pTreeCtrl->m_hWnd , &tvi); 
		CString strFin(BufWork);
		if (strFin.Find(compStr) >= 0 ) {
			boolOK = TRUE;
			break;
		}

		htiCurrent = TreeView_GetNextItem(m_pTreeCtrl->m_hWnd,htiCurrent,TVGN_NEXT);
	}

	if (!boolOK){
		TreeView_SelectItem(m_pTreeCtrl->m_hWnd,hItem);
		return;
	}


	int iPos = strPath.Find("\\",1);
	if (iPos < 0 ){
		TreeView_SelectItem(m_pTreeCtrl->m_hWnd,htiCurrent);
		return;
	}

	int iStartPos = iPos;
	iPos = strPath.Find("\\",iStartPos+1);
	CString strFin;
    while (iPos > 0 ){
	  strFin = strPath.Mid(iStartPos+1,iPos-iStartPos-1);

//
	htiWork=TreeView_GetNextItem(m_pTreeCtrl->m_hWnd,htiCurrent,TVGN_CHILD);

		HTREEITEM htiT;
		htiT = FindCurrentItem(m_pTreeCtrl,htiWork,strFin);
	  if (htiT == NULL ){
		  		TreeView_SelectItem(m_pTreeCtrl->m_hWnd,htiCurrent);
				return;
	  }



	htiCurrent = htiT;
//

	  iStartPos =iPos;
	  iPos = strPath.Find("\\",iStartPos+1);
	}

	  strFin = strPath.Mid(iStartPos+1);
	  htiWork=TreeView_GetNextItem(m_pTreeCtrl->m_hWnd,htiCurrent,TVGN_CHILD);
	  HTREEITEM htiT = FindCurrentItem(m_pTreeCtrl,htiWork,strFin);
	  if (htiT == NULL ){
		  		TreeView_SelectItem(m_pTreeCtrl->m_hWnd,htiCurrent);
	  } else {
		  		TreeView_SelectItem(m_pTreeCtrl->m_hWnd,htiT);
	  }



}
