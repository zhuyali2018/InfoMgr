; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLeftView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "infomgr.h"
LastPage=0

ClassCount=9
Class1=CContentView
Class2=CEditDialog
Class3=CFindDialog
Class4=CInfoMgrApp
Class5=CAboutDlg
Class6=CInfoMgrDoc
Class7=CInfoMgrView
Class8=CLeftView
Class9=CMainFrame

ResourceCount=6
Resource1=IDR_CONTEXTMENU
Resource2=IDD_ABOUTBOX
Resource3=IDD_EDIT_DIALOG
Resource4=IDD_FIND_DIALOG
Resource5=IDR_MAINFRAME
Resource6=IDD_FORMVIEW

[CLS:CContentView]
Type=0
BaseClass=CFormView
HeaderFile=ContentView.h
ImplementationFile=ContentView.cpp
LastObject=CContentView
Filter=D
VirtualFilter=VWC

[CLS:CEditDialog]
Type=0
BaseClass=CDialog
HeaderFile=EditDialog.h
ImplementationFile=EditDialog.cpp
LastObject=CEditDialog

[CLS:CFindDialog]
Type=0
BaseClass=CDialog
HeaderFile=FindDialog.h
ImplementationFile=FindDialog.cpp
LastObject=CFindDialog

[CLS:CInfoMgrApp]
Type=0
BaseClass=CWinApp
HeaderFile=InfoMgr.h
ImplementationFile=InfoMgr.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=InfoMgr.cpp
ImplementationFile=InfoMgr.cpp
LastObject=CAboutDlg

[CLS:CInfoMgrDoc]
Type=0
BaseClass=CDocument
HeaderFile=InfoMgrDoc.h
ImplementationFile=InfoMgrDoc.cpp

[CLS:CInfoMgrView]
Type=0
BaseClass=CListView
HeaderFile=InfoMgrView.h
ImplementationFile=InfoMgrView.cpp

[CLS:CLeftView]
Type=0
BaseClass=CTreeView
HeaderFile=LeftView.h
ImplementationFile=LeftView.cpp
LastObject=CLeftView

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[DLG:IDD_FORMVIEW]
Type=1
Class=CContentView
ControlCount=6
Control1=IDC_EDITNAME,edit,1342248960
Control2=IDC_EDITDESCRIPTION,edit,1342248960
Control3=IDC_EDITDTAILS,{3B7C8860-D78F-101B-B9B5-04021C009402},1342242816
Control4=IDC_EXPLORER1,{8856F961-340A-11D0-A96B-00C04FD705A2},1342242816
Control5=IDC_STATIC,static,1342308354
Control6=IDC_STATIC,static,1342308354

[DLG:IDD_EDIT_DIALOG]
Type=1
Class=CEditDialog
ControlCount=10
Control1=IDC_STATIC,static,1342308354
Control2=IDC_STATIC,static,1342308354
Control3=IDC_EDIT_NAME,edit,1350631552
Control4=IDC_STATIC,static,1342308354
Control5=IDC_EDIT_DESP,edit,1350631552
Control6=IDOK,button,1342242817
Control7=IDCANCEL,button,1342242816
Control8=IDC_EDIT_DETAIL0,edit,1342247108
Control9=IDC_CHECKRichTextt,button,1342242819
Control10=IDC_EDIT_DETAIL,{3B7C8860-D78F-101B-B9B5-04021C009402},1342242816

[DLG:IDD_FIND_DIALOG]
Type=1
Class=CFindDialog
ControlCount=13
Control1=IDC_STATIC,static,1342308354
Control2=IDC_EDIT_SEARCHSTR,edit,1350631552
Control3=IDC_CHK_NAME,button,1342242819
Control4=IDC_CHK_DESC,button,1342242819
Control5=IDC_CHK_DETAIL,button,1342242819
Control6=IDC_CHK_CASE,button,1342242819
Control7=IDC_RADIO_SEARCHALL,button,1342308361
Control8=IDC_RADIO_SEARCHOFFSPRINGS,button,1342177289
Control9=IDC_STATIC,button,1342177287
Control10=IDC_RADIO_SEARCHFIRST,button,1342308361
Control11=IDC_RADIO_SEARCHFORALL,button,1342177289
Control12=IDOK,button,1342242817
Control13=IDCANCEL,button,1342242816

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATICVERSION,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPENDEF
Command3=ID_FILE_OPEN
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_EDIT_INSERT
Command7=ID_EDIT_ITEM
Command8=ID_SORT
Command9=ID_SHOWALL
Command10=ID_CLEAR
Command11=ID_FIND
Command12=ID_LISTINST
Command13=ID_EDIT_CUT
Command14=ID_EDIT_COPY
Command15=ID_EDIT_POSITION
Command16=ID_EDIT_PASTE
Command17=ID_EDIT_DELETE
Command18=ID_MOVEUP
Command19=ID_MOVEDOWN
Command20=ID_EDIT_UNDO
Command21=ID_EDIT_REDO
Command22=ID_EDIT_Collapse
Command23=ID_APP_ABOUT
CommandCount=23

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPENDEF
Command3=ID_FILE_OPEN
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_REDO
Command10=ID_EDIT_INSERT
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_POSITION
Command14=ID_EDIT_PASTE
Command15=ID_EDIT_DELETE
Command16=ID_EDIT_ITEM
Command17=ID_FIND
Command18=ID_VIEW_TOOLBAR
Command19=ID_VIEW_STATUS_BAR
Command20=ID_SORT
Command21=ID_LISTINST
Command22=ID_SHOWALL
Command23=ID_CLEAR
Command24=ID_EDIT_Collapse
Command25=ID_PLAYMODE
Command26=ID_INSERTONLY
Command27=ID_EDIT_ReadOnly
Command28=ID_APP_ABOUT
CommandCount=28

[MNU:IDR_CONTEXTMENU]
Type=1
Class=?
Command1=ID_EDIT_ITEM
Command2=ID_EDIT_INSERT
Command3=ID_SHOWALL
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_DELETE
Command8=ID_CLEAR
Command9=ID_FIND
Command10=ID_SORT
Command11=ID_LISTINST
Command12=ID_EDIT_UNDO
Command13=ID_EDIT_POSITION
CommandCount=13

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDR_MAINFRAME]
Type=1
Class=?
ControlCount=2
Control1=IDC_SLIDER,msctls_trackbar32,1342242840
Control2=IDC_BUTTON1,button,1342242816

