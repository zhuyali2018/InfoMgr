// InfoMgr.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "InfoMgr.h"
#include "ConstantDefs.h"
#include "MainFrm.h"
#include "InfoMgrDoc.h"
#include "LeftView.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
int CRecord::idCounter=0; //0 represents root
int CInfoMgrDoc::saveCounter=0;
CString exepath;  // path to the executable, Used for relative path
/////////////////////////////////////////////////////////////////////////////
// CInfoMgrApp

BEGIN_MESSAGE_MAP(CInfoMgrApp, CWinApp)
	//{{AFX_MSG_MAP(CInfoMgrApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	//ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)  //<< can not be deleted if following one is present
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	ON_COMMAND(ID_FILE_OPENDEF, OnFileOpenDef)	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoMgrApp construction

CInfoMgrApp::CInfoMgrApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance	
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CInfoMgrApp object

CInfoMgrApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CInfoMgrApp initialization

BOOL CInfoMgrApp::InitInstance()
{
	AfxEnableControlContainer();
	TRACE0("Yali In App.Init(), test for trace0\n");
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
//#else
	//Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Information Manager"));

	LoadStdProfileSettings(15);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	// without following statement, the Drag and drop won't work
	if (!AfxOleInit())	return FALSE ;


	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CInfoMgrDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CLeftView));
		//RUNTIME_CLASS(CContentView));
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);
	

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	
	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	//---------getting the default doc name---------------
	TCHAR name[100];
	DWORD flen=GetModuleFileName(NULL,name,100);

	TRACE(_T("Filename=%s\n"),name);
	CString fname=name;
	int len=fname.GetLength();
	int pos=fname.ReverseFind(_T('\\'));
	CString mname=fname.Mid(pos+1,len-pos-5);
	exepath=fname.Mid(0,pos+1);		//path that ends with a slash \
	//MessageBox(NULL,mname,fname,MB_OK);
	TRACE(_T("len=%d, pos=%d,fname=%s, mname=%s\nexepath=%s\n"),len,pos,fname,mname,exepath);
	mname+=_T(".inf");
	//-------------------end of getting doc name-----------
	OpenDocumentFile(mname); //<<===add thisline here to automatically open the default file
	//OpenDocumentFile(_T("ttt.inf"));

	// The one and only window has been initialized, so show and update it.
 	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	// Enable drag/drop open
	//m_pMainWnd->DragAcceptFiles();
	
	TRACE(_T("appNme=%s\n"),m_pszAppName);
	TRACE(_T("exeNme=%s\n"),m_pszExeName);
	TRACE(_T("HelpFile=%s\n"),m_pszHelpFilePath);
/*
	CString str,mytitle;
	mytitle="Information Manager Version 1.00";
	m_pMainWnd->GetWindowText(str);
//	MessageBox(NULL,str,"Title",MB_OK);
	CString title=str.Mid(0,str.Find("-"))+"- "+mytitle;
	m_pMainWnd->SetWindowText(title);
*/	
	bTitleUpdated=FALSE;
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
    virtual BOOL OnInitDialog();
// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_Version;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CString m_strHelpMessage;
	CEdit m_ctrlHelpWindow;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_Version = (CString)"InfoMgr "+VERSIONNAME+(CString)" Version 5.23";
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_STATICVERSION, m_Version);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_EDIT1, m_ctrlHelpWindow);
}
BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_strHelpMessage=_T("Version 4.00: Added support for relative path for picture and movie files\r\n\r\n")
		_T(" Relative path start with double semi colons :: \r\n")
		_T("To create a relative path: Keep control key pressed down when drop\r\n\r\n")
		_T("Version 4.01: Fixed the rich text displaying error\r\n")
		_T("Version 4.02: Fixed the rich text Retrieving error\r\n")
		_T("Version 4.03: Relative path for pics dropped on EditDialogBox\r\n")
		_T("\t and populate a timestamp on empty description field\r\n")
		_T("Version 4.04: Fixed the detail loading problem and extra CFCR adding problem\r\n")
		_T("Version 4.05: Modified to support .png picture file\r\n")
		_T("Version 4.06: Modified to support .gif picture file and fixed line wrap problem\r\n")
		_T("Version 4.07: Modified to support .mp4 and all other files with relative path\r\n")
		_T("Version 4.08: Modified to avoid dragging and cant find jpg file error\r\n")
		_T("Version 4.09: Modified to create temp file in current dir so that no admin right required\r\n")
		_T("Version 4.10: Modified to fix the ::FOLDER path for images\r\n")
		_T("Version 4.11: AutoPopulate ::\\images2016\\ \r\n")
		_T("Version 5.10: Added Descrip_tag field\r\n")
		_T("Version 5.20: Added code to OnSize() to postion field label properly\r\n")
		_T("Version 5.21: Changing starting ID from 1 to 0\r\n")
		_T("Version 5.22: Change icon\r\n")
		_T("Version 5.23: Skip empty lines when loading\r\n")
			;
	m_ctrlHelpWindow.SetWindowText(m_strHelpMessage);
	return TRUE;
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CInfoMgrApp::OnAppAbout()
{	
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CInfoMgrApp message handlers


void CInfoMgrApp::OnFileNew()
{
	//MessageBox(NULL,"InOnFilenew","Debug",MB_OK);
	bTitleUpdated=FALSE;
	CWinApp::OnFileNew();
	CRecord::idCounter=0;	//0 represents root
}
void CInfoMgrApp::OnFileOpenDef()
{
	//MessageBox(NULL,"In OnFileOpenDefault","Debug",MB_OK);
	//---------getting the default doc name---------------
	TCHAR name[100];
	DWORD flen=GetModuleFileName(NULL,name,100);

	TRACE(_T("Filename=%s\n"),name);
	CString fname=name;
	int len=fname.GetLength();
	int pos=fname.ReverseFind(_T('\\'));
	CString mname=fname.Mid(pos+1,len-pos-5);
	//MessageBox(NULL,mname,fname,MB_OK);
	TRACE(_T("len=%d, pos=%d,fname=%s, mname=%s\n"),len,pos,fname,mname);
	mname+=_T(".inf");
	//-------------------end of getting doc name-----------
	OpenDocumentFile(mname);
	bTitleUpdated=FALSE;
}


BOOL CInfoMgrApp::OnIdle(LONG lCount) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (CWinApp::OnIdle(lCount))
		return TRUE; 
	if(bTitleUpdated)
		return FALSE;
	
	CString maintitle;
	m_pMainWnd-> GetWindowText(maintitle);	
	if(maintitle.GetLength()<=0)
		return FALSE;
	int pos=maintitle.Find(_T("-"));
	if(pos>0){		
		CString filename=maintitle.Mid(0,pos);
		CString title=filename+"- "+"Information Manager "+VERSIONNAME+" version 5.23";
		m_pMainWnd-> SetWindowText(title);
		bTitleUpdated=TRUE;
	}
	return FALSE;
}

CDocument* CInfoMgrApp::OpenDocumentFile(LPCTSTR lpszFileName) 
{
	// TODO: Add your specialized code here and/or call the base class

	CString fname = lpszFileName;
	int len = fname.GetLength();
	int pos = fname.ReverseFind(_T('\\'));
	if(pos > -1 ){
	    CString mname = fname.Mid(pos + 1, len - pos - 5);
	    exepath = fname.Mid(0, pos + 1);		
	}
	bTitleUpdated=FALSE;
	return CWinApp::OpenDocumentFile(lpszFileName);
}
