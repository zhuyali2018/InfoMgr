// FindDialog.cpp : implementation file
//

#include "stdafx.h"
#include "InfoMgr.h"
#include "FindDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CFindDialog dialog


CFindDialog::CFindDialog(CLeftView * pV,CInfoMgrDoc * pDoc)
	: CDialog(CFindDialog::IDD, pV)
{
	//{{AFX_DATA_INIT(CFindDialog)
	m_CaseSensitive = FALSE;
	m_SearchDescription = FALSE;
	m_SearchDetail = FALSE;
	m_SearchName = TRUE;
	m_SearchString = _T("");
	m_SearchScope = 0;
	m_SearchForHowmany = 1;
	//}}AFX_DATA_INIT
	treeCtrl=pDoc->treeCtrl;
	head=pDoc->head;
	pDocument=pDoc;
	pLeftView=pV;
}


void CFindDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindDialog)
	DDX_Check(pDX, IDC_CHK_CASE, m_CaseSensitive);
	DDX_Check(pDX, IDC_CHK_DESC, m_SearchDescription);
	DDX_Check(pDX, IDC_CHK_DETAIL, m_SearchDetail);
	DDX_Check(pDX, IDC_CHK_NAME, m_SearchName);
	DDX_Text(pDX, IDC_EDIT_SEARCHSTR, m_SearchString);
	DDX_Radio(pDX, IDC_RADIO_SEARCHALL, m_SearchScope);
	DDX_Radio(pDX, IDC_RADIO_SEARCHFIRST, m_SearchForHowmany);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindDialog, CDialog)
	//{{AFX_MSG_MAP(CFindDialog)
	ON_BN_CLICKED(IDOK, OnOKsearch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindDialog message handlers

void CFindDialog::OnOKsearch() 
{
	// TODO: Add your control notification handler code here	
	UpdateData();
	if(m_SearchScope==0){
		CRecord * p=head;
		while(p!=NULL){		
			if(ShowFound(p))
				if(m_SearchForHowmany==0) break;		
			p=p->Next;
		}
	}else{	
		HTREEITEM hItem=treeCtrl->GetSelectedItem();
		if(hItem)
			SearchTheBranch(hItem);
	}
	CDialog::OnOK();	
}


void CFindDialog::ShowAllInstances(CRecord *p)
{
	POSITION pos = pDocument->GetFirstViewPosition();
	if(pos==NULL){
		::MessageBox(NULL,_T("treeCtrl is NULL"),_T("CInfoMgrDoc::addChildren"),MB_OK);
		return;
	}
	CLeftView * pFirstView = (CLeftView*)pDocument->GetNextView( pos );
	if(pFirstView){		
		pFirstView->ShowInstances(p,!m_SearchForHowmany);
	}
	
}

BOOL CFindDialog::ShowFound(CRecord *p)
{	
	if(IsTheRecord(p)){
		 ShowAllInstances(p);
		 return TRUE;
	}
	return FALSE;
}
BOOL CFindDialog::IsTheItem(HTREEITEM hItem)
{
	CRecord * p=(CRecord *)treeCtrl->GetItemData(hItem);	
	return IsTheRecord(p);
}

BOOL CFindDialog::IsTheRecord(CRecord *p)
{
	CString Name=p->Name;	
	CString Description=p->Description; 
	CString Detail=p->Detail; 
	
	if(!m_CaseSensitive){
		Name.MakeLower();
		Description.MakeLower();
		Detail.MakeLower();
		m_SearchString.MakeLower();
	}

	BOOL Found=FALSE;
	if(m_SearchName)		if(Name.Find(m_SearchString)>=0)	   {Found=TRUE; goto exit; }		
	if(m_SearchDescription)	if(Description.Find(m_SearchString)>=0){Found=TRUE; goto exit; }				
	if(m_SearchDetail)		if(Detail.Find(m_SearchString)>=0)	   Found=TRUE;
exit:	
	return Found;
}

void CFindDialog::SearchTheBranch(HTREEITEM hItem)
{
	if(IsTheItem(hItem)){
		MarkTheItem(hItem);
	}
	if(treeCtrl->ItemHasChildren(hItem)){
		HTREEITEM hNextItem;
		HTREEITEM hChildItem = treeCtrl->GetChildItem(hItem);
		while (hChildItem != NULL){
			hNextItem = treeCtrl->GetNextItem(hChildItem, TVGN_NEXT);
			SearchTheBranch(hChildItem);		// resursive call
			hChildItem = hNextItem;
		}
	}
}

void CFindDialog::MarkTheItem(HTREEITEM hItem)
{
	treeCtrl->EnsureVisible(hItem);
	treeCtrl->SetItemImage(hItem,1,2);
	pLeftView->IconSetList.AddTail(hItem);	
}
