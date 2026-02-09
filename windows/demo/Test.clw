; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CImageDoc
LastTemplate=CEditView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Test.h"
LastPage=0

ClassCount=7
Class1=CTestApp
Class2=CImageDoc
Class3=CImageView
Class4=CMainFrame

ResourceCount=8
Resource1=IDD_ABOUTBOX (English (U.S.))
Resource2=IDR_IMAGE_TOOLBAR
Resource3=IDR_LINEDETYPE
Class5=CImageFrame
Class6=CAboutDlg
Resource4=IDR_IMAGE_TOOLBAR (English (U.S.))
Resource5=IDR_LINEDETYPE (English (U.S.))
Resource6=IDR_MAINFRAME
Class7=CResultView
Resource7=IDR_MAINFRAME (English (U.S.))
Resource8=IDD_ABOUTBOX

[CLS:CTestApp]
Type=0
HeaderFile=Test.h
ImplementationFile=Test.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CTestApp

[CLS:CImageDoc]
Type=0
HeaderFile=ImageDoc.h
ImplementationFile=ImageDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CImageDoc

[CLS:CImageView]
Type=0
HeaderFile=ImageView.h
ImplementationFile=ImageView.cpp
Filter=C
BaseClass=CScrollView
VirtualFilter=VWC
LastObject=ID_VIEW_ZOOM_IN


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrame.h
ImplementationFile=MainFrame.cpp
Filter=T
LastObject=ID_IMAGE_NEXT
BaseClass=CMDIFrameWnd
VirtualFilter=fWC


[CLS:CImageFrame]
Type=0
HeaderFile=ImageFrame.h
ImplementationFile=ImageFrame.cpp
Filter=M
BaseClass=CMDIChildWnd
VirtualFilter=mfWC
LastObject=CImageFrame


[CLS:CAboutDlg]
Type=0
HeaderFile=Test.cpp
ImplementationFile=Test.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_IMAGE_FILE_OPEN
Command2=ID_APP_EXIT
Command3=ID_VIEW_TOOLBAR
Command4=ID_VIEW_STATUS_BAR
Command5=ID_APP_ABOUT
CommandCount=5

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_IMAGE_FILE_OPEN
Command2=ID_FILE_SAVE
Command3=ID_IMAGE_PREV
Command4=ID_COMBO_FILE_LIST
Command5=ID_IMAGE_NEXT
CommandCount=5

[MNU:IDR_LINEDETYPE]
Type=1
Class=CImageView
Command1=ID_IMAGE_FILE_OPEN
Command2=ID_FILE_SAVE_AS
Command3=ID_APP_EXIT
Command4=ID_VIEW_TOOLBAR
Command5=ID_VIEW_STATUS_BAR
Command6=ID_VIEW_RECT
Command7=ID_VIEW_ORDER
Command8=ID_WINDOW_NEW
Command9=ID_WINDOW_CASCADE
Command10=ID_WINDOW_TILE_HORZ
Command11=ID_WINDOW_ARRANGE
Command12=ID_APP_ABOUT
CommandCount=12

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

[MNU:IDR_LINEDETYPE (English (U.S.))]
Type=1
Class=CImageView
Command1=ID_IMAGE_FILE_OPEN
Command2=ID_FILE_SAVE_AS
Command3=ID_APP_EXIT
Command4=ID_VIEW_TOOLBAR
Command5=ID_VIEW_STATUS_BAR
Command6=ID_VIEW_RECT
Command7=ID_VIEW_ORDER
Command8=ID_WINDOW_NEW
Command9=ID_WINDOW_CASCADE
Command10=ID_WINDOW_TILE_HORZ
Command11=ID_WINDOW_ARRANGE
Command12=ID_APP_ABOUT
CommandCount=12

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_IMAGE_FILE_OPEN
Command2=ID_APP_EXIT
Command3=ID_VIEW_TOOLBAR
Command4=ID_VIEW_STATUS_BAR
Command5=ID_APP_ABOUT
CommandCount=5

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_IMAGE_FILE_OPEN
Command2=ID_FILE_SAVE
Command3=ID_IMAGE_PREV
Command4=ID_COMBO_FILE_LIST
Command5=ID_IMAGE_NEXT
CommandCount=5

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
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

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[TB:IDR_IMAGE_TOOLBAR (English (U.S.))]
Type=1
Class=?
Command1=ID_VIEW_ZOOM_IN
Command2=ID_VIEW_ZOOM_OUT
CommandCount=2

[CLS:CResultView]
Type=0
HeaderFile=ResultView.h
ImplementationFile=ResultView.cpp
BaseClass=CEditView
Filter=C

[TB:IDR_IMAGE_TOOLBAR]
Type=1
Class=?
Command1=ID_VIEW_ZOOM_IN
Command2=ID_VIEW_ZOOM_OUT
CommandCount=2

