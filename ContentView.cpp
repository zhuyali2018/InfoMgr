// ContentView.cpp : implementation file
//

#include "stdafx.h"
#include "InfoMgr.h"
#include "ContentView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CContentView

IMPLEMENT_DYNCREATE(CContentView, CFormView)

CContentView::CContentView()
	: CFormView(CContentView::IDD)
{
	//{{AFX_DATA_INIT(CContentView)
	m_Name = _T("");
	m_Details = _T("");
	m_Description = _T("");
	//}}AFX_DATA_INIT	
	m_Resizing=FALSE;
	display121=FALSE;
}

CContentView::~CContentView()
{
}

void CContentView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CContentView)
	DDX_Control(pDX, IDC_EDITNAME, m_CtrlName);
	DDX_Control(pDX, IDC_EDITDTAILS, m_CtrlDetail);
	DDX_Control(pDX, IDC_EDITDESCRIPTION, m_CtrlDesp);
	DDX_Text(pDX, IDC_EDITNAME, m_Name);
	DDX_Text(pDX, IDC_EDITDTAILS, m_Details);
	DDX_Text(pDX, IDC_EDITDESCRIPTION, m_Description);
	DDX_Control(pDX, IDC_EXPLORER1, m_browser);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CContentView, CFormView)
	//{{AFX_MSG_MAP(CContentView)
	ON_WM_SIZE()		
	ON_WM_LBUTTONDBLCLK()	
	ON_WM_DROPFILES()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContentView diagnostics

#ifdef _DEBUG
void CContentView::AssertValid() const
{
	CFormView::AssertValid();
}

void CContentView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CContentView message handlers
void CContentView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (lHint == NULL) return;   // very important, on start up, it is NULL
	CMainFrame * mf=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (lHint==0xffffffff){
		mf->m_wndSplitter2.SetRowInfo(0,1400,1400);		
		mf->m_wndSplitter2.RecalcLayout();	
		return;
	}
	// get arguments passed in:
	HTREEITEM h=(HTREEITEM)lHint;
	CTreeCtrl *treeCtrl=(CTreeCtrl *)pHint;
	
	//get pointer to selected tree item
	CRecord * pR=(CRecord *)treeCtrl->GetItemData(h);
	int ID=pR->ID;
	m_Name=pR->Name;
	m_Details=pR->Detail;
	m_Description=pR->Description;
	if(m_Description.GetLength()>1){
		if((m_Description.Left(7).CompareNoCase(_T("http://"))==0)||    // if a web url
			(m_Description.Left(2)==_T("\\\\"))||						// if a network url
			(m_Description.Left(8).CompareNoCase(_T("https://"))==0)){	// if a web url
			m_browser.Navigate(m_Description,0,0,0,0);
			m_CtrlDetail.ShowWindow(SW_HIDE);
		}else if(m_Description[1]==_T(':')){  // if a local file
			DisplayImage(m_Description);	
			if(!m_DoNotDisplayBrowser)
				m_CtrlDetail.ShowWindow(SW_HIDE);
			else{
				m_Details="Not in Movie Play Mode";
				m_CtrlDetail.ShowWindow(SW_SHOW);
			}
		}else{
			m_CtrlDetail.ShowWindow(SW_SHOW);		
		}
	}else
		m_CtrlDetail.ShowWindow(SW_SHOW);		
	UpdateData(FALSE);
}

void CContentView::OnSize(UINT nType, int cx, int cy) 
{
	this->DragAcceptFiles();
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

	int x=60;
	int y=5;
	
	int h=22;
	int w=cx-100;
	
	int bottom=20;
	int right=21;
	int bnwidth=72;
	int bnheight=22;

	if(m_CtrlName.m_hWnd==NULL) return;
	m_CtrlName.MoveWindow(x,y,w+40,h);
	m_CtrlDesp.MoveWindow(x,y+24,w+40,h);
	m_CtrlDetail.MoveWindow(x-60,y+24+24,w+100,cy-50);
	m_browser.MoveWindow (x-60,y+24+24,w+100,cy-50);
	m_Resizing=TRUE;
	DisplayImage(m_Description);
}


BOOL CContentView::IsJPGFile(CString filepath){
	filepath.TrimRight();
	if(filepath.Right(4).CompareNoCase(_T(".jpg"))==0)
		return TRUE;
	if(filepath.Right(4).CompareNoCase(_T(".png"))==0)
		return TRUE;
	if(filepath.Right(4).CompareNoCase(_T(".gif"))==0)
		return TRUE;
	return FALSE;
}

CString CContentView::getCurrentPath(){
	//return "c:\\";
	TCHAR pwd[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, pwd);
	//::MessageBox(NULL, pwd, pwd, 0);
	return CString(pwd);
}
extern CString exepath;
void CContentView::DisplayImage(CString m_Description)
{
	m_DoNotDisplayBrowser=FALSE;
	// inserting for relative path-----
	CString prePath=_T("");
	if((m_Description.GetLength()>2)&&(m_Description[1]==_T(':'))&&(m_Description[0]==_T(':'))){
		prePath=exepath+m_Description.Mid(2);
		//above statement is always correct, so, comment out the following block
		/*prePath = exepath + m_Description.Mid(3);
		if (m_Description.Mid(2) == '\\') {
			prePath = exepath + m_Description.Mid(3);
		}
		else {
			prePath = exepath + m_Description.Mid(2);
		}*/
		//debug statement
		//::MessageBox(NULL, prePath, L"prePath", MB_OK);
	}else
		prePath=m_Description;
	//---------------------------------
	if(IsJPGFile(m_Description)){		
		long h=m_browser.GetHeight();
		long w=m_browser.GetWidth();
		CString curPath=getCurrentPath();
		CStdioFile f;
		CFileException pError;
		BOOL Opened=f.Open(curPath+"webpage.htm",CFile::modeCreate | CFile::modeWrite, &pError);
		if(Opened){
			CString line;
			line.Format(_T("<img src=\"%s\" width=%d>"),prePath,w-40);
			f.WriteString(line);
			f.Close();
			m_browser.Navigate(curPath+"webpage.htm",0,0,0,0);
		}//else           //version 4.08 removed the 2 lines
			//m_browser.Navigate(m_Description,0,0,0,0);
	}else if(IsMovieFile(m_Description)){
		BOOL PlayMode=((CMainFrame *)(AfxGetApp()->m_pMainWnd))->PlayMode;
		if((PlayMode)&&(!m_Resizing)){
			CString curPath=getCurrentPath();
			CStdioFile f;
			BOOL Opened=f.Open(curPath+"webpage.htm",CFile::modeCreate | CFile::modeWrite);
			if(Opened){
				CString line;
				//line.Format(_T("<img src=\"%s\" width=%d>"),m_Description,w-40);
				line.Format(_T("<center><embed src=\"%s\" width=640 height=480></embed></center>"),prePath);
				f.WriteString(line);
				f.Close();
				m_browser.Navigate(curPath+"webpage.htm",0,0,0,0);			
			}
		}
		if((!PlayMode)&&(!m_Resizing))
			m_DoNotDisplayBrowser=TRUE;
	}else{
		if(!m_Resizing)
			m_browser.Navigate(prePath,0,0,0,0);   // changed from m_Description to prePath to support .mp4 and all other relative path files
	}
	m_Resizing=FALSE;
}

void CContentView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//MessageBox("Double clicked");
	if(!display121){		
		m_browser.Navigate(m_Description,0,0,0,0);
		display121=TRUE;
	}else{		
		m_browser.Navigate(getCurrentPath()+"webpage.htm",0,0,0,0);
		display121=FALSE;
	}

	CFormView::OnLButtonDblClk(nFlags, point);
}

BOOL CContentView::IsMovieFile(CString filepath)
{
	filepath.TrimRight();
	if(filepath.Right(4).CompareNoCase(_T(".avi"))==0)
		return TRUE;
	if(filepath.Right(4).CompareNoCase(_T(".mpg"))==0)
		return TRUE;	
	if(filepath.Right(4).CompareNoCase(_T(".WMV"))==0)
		return TRUE;	
	if(filepath.Right(5).CompareNoCase(_T(".Rmvb"))==0)
		return TRUE;
	if(filepath.Right(3).CompareNoCase(_T(".Rm"))==0)
		return TRUE;
	
	return FALSE;	
}

void CContentView::OnDropFiles(HDROP hDropInfo) {
	MessageBox(_T("File Dropped"));
}

int CContentView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
		DragAcceptFiles();
	return 0;
}
