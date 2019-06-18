// EditDialog.cpp : implementation file
//

#include "stdafx.h"
#include "InfoMgr.h"
#include "EditDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditDialog dialog


CEditDialog::CEditDialog(CWnd* pParent /*=NULL*/,CRecord *p)
	: CDialog(CEditDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditDialog)	
	m_Description = _T("");
	m_Name = _T("");
	m_Detail = _T("");
	m_Detail0 = _T("");
	m_bRichText = FALSE;
	//}}AFX_DATA_INIT
	pView=(CLeftView *)pParent;
	pRecord=p;
	m_Name=p->Name;
	m_Description=p->Description;
	////////////////////////////////////////////////
	//  Moved following to OnInitDialog()
	//if(p->hasDetail){
	//	//m_CtrlDetail.SetTextRTF(p->Detail);
	//	//m_CtrlDetail.SetText(p->Detail);
	//	p->Detail.Trim();
	//	if(p->Detail[0]=='{'){
	//		//m_CtrlDetail.SetTextRTF(p->Detail);
	//		m_CtrlDetail.SetTextRTF(_T("Test Richtext"));
	//		//m_Detail=p->Detail;
	//		m_bRichText = TRUE;
	//	}else{
	//		m_Detail0=p->Detail;
	//		UpdateData(FALSE);
	//	}
	//}
	//
	bDisplaying=FALSE;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bReadOnly=((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_bReadOnly;
}


void CEditDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditDialog)
	DDX_Control(pDX, IDC_CHECKRichTextt, m_CtrlRichTextChk);
	DDX_Control(pDX, IDC_EDIT_DETAIL0, m_CtrlDetail0);
	DDX_Control(pDX, IDC_EDIT_DESP, m_CtrlDesp);
	DDX_Control(pDX, IDC_EDIT_DETAIL, m_CtrlDetail);
	DDX_Control(pDX, IDC_EDIT_NAME, m_CtrlName);
	DDX_Control(pDX, IDOK, m_bnOK);
	DDX_Control(pDX, IDCANCEL, m_bnCancel);
	DDX_Text(pDX, IDC_EDIT_DESP, m_Description);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Name);
	DDX_Text(pDX, IDC_EDIT_DETAIL, m_Detail);
	DDX_Text(pDX, IDC_EDIT_DETAIL0, m_Detail0);
	DDX_Check(pDX, IDC_CHECKRichTextt, m_bRichText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditDialog, CDialog)
	//{{AFX_MSG_MAP(CEditDialog)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_DROPFILES()						//<===this line is key to drop files
	ON_BN_CLICKED(IDC_CHECKRichTextt, OnCHECKRichTextt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditDialog message handlers

void CEditDialog::OnOK() 
{
	// TODO: Add extra validation here
	if(m_bReadOnly){
		CDialog::OnOK();
		return;
	}
	UpdateData();
	pRecord->Name=m_Name;
	pRecord->Description=m_Description;
	m_Detail.TrimLeft();
	m_Detail.TrimRight();	
	
	//pRecord->Detail=m_Detail;
	if(m_bRichText){		
		pRecord->Detail=m_CtrlDetail.GetTextRTF();
		//pRecord->hasDetail=(m_Detail.GetLength()==0?FALSE:TRUE);
		pRecord->hasDetail=(pRecord->Detail.GetLength()==0?FALSE:TRUE);
	}else{		
		pRecord->Detail=m_Detail0;
		pRecord->hasDetail=(pRecord->Detail.GetLength()==0?FALSE:TRUE);
	}
	CDialog::OnOK();
}

void CEditDialog::OnSize(UINT nType, int cx, int cy) 
{
	TRACE(_T("CEditDialog::OnSize\n"));
	CDialog::OnSize(nType, cx, cy);
	if(!bDisplaying){
		bDisplaying=TRUE;
		return;
	}
	// TODO: Add your message handler code here
	TRACE(_T("cx=%d, cy=%d\n"),cx,cy);

	int x=78;
	int y=70;
	
	int h=22;
	int w=cx-100;
	
	int bottom=20;
	int right=21;
	int bnwidth=72;
	int bnheight=22;

	m_CtrlName.MoveWindow(x,y,w,h);
	m_CtrlDesp.MoveWindow(x,y+30,w,h);
	m_CtrlDetail.MoveWindow(x,y+30+30,w,cy-180);
	m_CtrlDetail0.MoveWindow(x,y+30+30,w,cy-180);
	m_bnCancel.MoveWindow(cx-right-2*bnwidth-12,cy-bottom-bnheight,bnwidth,bnheight);
	m_bnOK.MoveWindow(cx-right-bnwidth,cy-bottom-bnheight,bnwidth,bnheight);
	m_CtrlRichTextChk.MoveWindow(x,cy-bottom-bnheight,bnwidth*2,bnheight);
	Invalidate();
}

void CEditDialog::OnPaint() 
{
	//CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
		TRACE(_T("OnDraw 1\n"));
	}else{		
		TRACE(_T("OnDraw 2\n"));
		//------------------------------
		CString title=_T("Input and Modify Sheet");
		
		CFont font;		
		font.CreateFont(
			20,                        // nHeight
			10,                        // nWidth
			0,                         // nEscapement
			0,                         // nOrientation	===> no effect
			FW_BOLD,                   // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			ANSI_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			_T("Arial")				   // lpszFacename
		);                 


		CPaintDC dc(this); // device context for painting
		dc.SelectObject(&font);

		CRect rect;
		GetClientRect(&rect);
		dc.SetBkMode(TRANSPARENT);

		rect.top+=20;			// make the title lower from top
		
		dc.SetTextColor(RGB(10,10,10));		
		dc.DrawText(title,-1,&rect,DT_SINGLELINE|DT_CENTER);
		
		rect.top-=1;
		rect.left-=2;
		dc.SetTextColor(RGB(255,100,0));
		dc.DrawText(title,-1,&rect,DT_SINGLELINE|DT_CENTER);	
		//------------------------------
		//CDialog::OnPaint();		
	}
}

BOOL CEditDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetIcon(m_hIcon, TRUE);	
	OnCHECKRichTextt(); 
	m_CtrlName.SetSel(0,100);
	RECT Rect;
	GetWindowRect(&Rect );
	Rect.right+=200;
	Rect.bottom+=200;
	MoveWindow(&Rect,TRUE);

	if(m_bReadOnly){
		m_CtrlName.SetReadOnly();
		m_CtrlDesp.SetReadOnly();
		m_CtrlDetail.SetEnabled(FALSE);
		m_CtrlDetail0.SetReadOnly();
	}

	//-------------moved to here from constructor----------
	if(pRecord->hasDetail){
		//m_CtrlDetail.SetTextRTF(p->Detail);
		//m_CtrlDetail.SetText(p->Detail);
		pRecord->Detail.Trim();
		if(pRecord->Detail[0]=='{'){
			m_CtrlDetail.SetTextRTF(pRecord->Detail);
			m_Detail=pRecord->Detail;
			m_bRichText = TRUE;
		}else{
			m_Detail0=pRecord->Detail;			
		}
		UpdateData(FALSE);
		OnCHECKRichTextt();
	}
	//-----------------------------------------------------
	if((m_Description.GetLength()==0)&&(!m_bReadOnly)){
		/*CTime now=CTime::GetCurrentTime();
		CString strNow=now.Format(_T("%m/%d/%Y %H:%M:%S"));
		m_Description=_T("(")+strNow+_T(")");*/
		m_Description = _T("::\\images2016\\");
		UpdateData(FALSE);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditDialog::OnCHECKRichTextt() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if(m_bRichText){
		m_CtrlDetail.ShowWindow(SW_SHOW);
		m_CtrlDetail0.ShowWindow(SW_HIDE);
	}else{
		m_CtrlDetail.ShowWindow(SW_HIDE);
		m_CtrlDetail0.ShowWindow(SW_SHOW);
	}
}
void CEditDialog::OnDropFiles(HDROP hDropInfo){
	HDROP hdrop = hDropInfo;
	UpdateData(TRUE);	// freze what has inputed	
	_TCHAR szFileName[_MAX_PATH + 1];
    if (NULL != hdrop){
        UINT nFiles = DragQueryFile(hdrop, (UINT)-1, NULL, 0);
		BOOL InsertOnOneFileDrop=((CMainFrame *)(AfxGetApp()->m_pMainWnd))->m_InsertOnOneFileDrop;
		if((nFiles==1)&&(!InsertOnOneFileDrop)){
			//MessageBox("nFiles=1");
			DragQueryFile(hdrop, 0, (LPTSTR)szFileName, _MAX_PATH + 1);			
			m_Description=szFileName;
			UpdateData(FALSE);	
			return;
		}		
		//MessageBox("nFiles<>1");
        for(UINT nNames = 0; nNames < nFiles; nNames++) {
            ZeroMemory(szFileName, _MAX_PATH + 1);
            DragQueryFile(hdrop, nNames, (LPTSTR)szFileName, _MAX_PATH + 1);			
			//m_Description=szFileName;
			InsertNode(szFileName);
			UpdateData(FALSE);									
		}
		OnOK();
	}  
}
#define INSERT	3
extern CString exepath;
void CEditDialog::InsertNode(_TCHAR *link)
{	
	HTREEITEM hItem= pView->GetTreeCtrl().GetSelectedItem();
	CRecord * node=new CRecord(&(pView->GetTreeCtrl()));

	////////////////////////////////////////
	TRACE("Edit Dialog Relative Path\n");
	CString absPath=link;
	absPath.MakeUpper();
	exepath.MakeUpper();
	if(absPath.Find(exepath)==0){
		int loc=exepath.GetLength();
		node->Description=_T("::")+absPath.Mid(loc);   // add double colon to indicate a relative path
	}else
		node->Description=link;	
    /////////////////////////////////////////////////

	node->Name=link;
	//node->Description=link;  // replaced by block above for relative path
	int pos=node->Name.ReverseFind('\\');
	if(pos>0)
		node->Name=node->Name.Mid(pos+1);

	CRecord * target;
	if(hItem)
		target=(CRecord *)pView->GetTreeCtrl().GetItemData(hItem);
	else
		target=NULL;

	HTREEITEM justinserted=pView->BigInsert(target,node);

	pView->GetDocument()->AddToList(node);	
	pView->GetDocument()->SetModifiedFlag();
	pView->RecordAction((HTREEITEM)node->ID,justinserted,INSERT,target,node);
}

