; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "City.h"
LastPage=0

ClassCount=6
Class1=CCityApp
Class2=CCityDoc
Class3=CCityView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CToolBox
Resource2=IDR_MENU1
Resource3=IDR_MAINFRAME

[CLS:CCityApp]
Type=0
HeaderFile=City.h
ImplementationFile=City.cpp
Filter=N
LastObject=CCityApp

[CLS:CCityDoc]
Type=0
HeaderFile=CityDoc.h
ImplementationFile=CityDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CCityDoc

[CLS:CCityView]
Type=0
HeaderFile=CityView.h
ImplementationFile=CityView.cpp
Filter=C
LastObject=CCityView
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=City.cpp
ImplementationFile=City.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
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

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[CLS:CToolBox]
Type=0
HeaderFile=ToolBox.h
ImplementationFile=ToolBox.cpp
BaseClass=CDialog
Filter=D
LastObject=CToolBox
VirtualFilter=dWC

[MNU:IDR_MENU1]
Type=1
Command1=ID_FILE_NEW
CommandCount=1

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
CommandCount=1

