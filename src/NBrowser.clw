; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CWinThread
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "NBrowser.h"
LastPage=0

ClassCount=7
Class1=CNBrowserApp
Class2=CNBrowserDoc
Class3=CNBrowserView
Class4=CMainFrame

ResourceCount=2
Resource1=IDD_ABOUTBOX
Class5=CLeftView
Class6=CAboutDlg
Class7=CCopyThread
Resource2=IDR_MAINFRAME

[CLS:CNBrowserApp]
Type=0
HeaderFile=NBrowser.h
ImplementationFile=NBrowser.cpp
Filter=N

[CLS:CNBrowserDoc]
Type=0
HeaderFile=NBrowserDoc.h
ImplementationFile=NBrowserDoc.cpp
Filter=N

[CLS:CNBrowserView]
Type=0
HeaderFile=NBrowserView.h
ImplementationFile=NBrowserView.cpp
Filter=C
BaseClass=CListView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame



[CLS:CLeftView]
Type=0
HeaderFile=LeftView.h
ImplementationFile=LeftView.cpp
Filter=T
BaseClass=CTreeView
VirtualFilter=VWC
LastObject=CLeftView

[CLS:CAboutDlg]
Type=0
HeaderFile=NBrowser.cpp
ImplementationFile=NBrowser.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=7
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1350569998

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_APP_EXIT
Command2=ID_FILE_DELETE
Command3=ID_VIEW_TOOLBAR
Command4=ID_VIEW_STATUS_BAR
Command5=ID_VIEW_REFRESH
Command6=ID_VIEW_LARGEICON
Command7=ID_VIEW_SMALLICON
Command8=ID_VIEW_LIST
Command9=ID_VIEW_DETAILS
Command10=ID_APP_ABOUT
CommandCount=10

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_BUTTON_PANE
Command2=ID_VIEW_LARGEICON
Command3=ID_VIEW_SMALLICON
Command4=ID_VIEW_LIST
Command5=ID_VIEW_DETAILS
Command6=ID_BUTTTON_REFRESH
Command7=ID_BUTTON_UP_LEVEL
Command8=ID_BUTTON_DELETE_FILE
Command9=ID_APP_ABOUT
CommandCount=9

[DLG:IDR_MAINFRAME]
Type=1
Class=?
ControlCount=0

[CLS:CCopyThread]
Type=0
HeaderFile=CopyThread.h
ImplementationFile=CopyThread.cpp
BaseClass=CWinThread
Filter=N

