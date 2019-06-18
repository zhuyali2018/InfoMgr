// InfoMgrView.cpp : implementation of the CInfoMgrView class
//

#include "stdafx.h"
#include "InfoMgr.h"

#include "InfoMgrDoc.h"
#include "InfoMgrView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfoMgrView

IMPLEMENT_DYNCREATE(CInfoMgrView, CListView)

BEGIN_MESSAGE_MAP(CInfoMgrView, CListView)
	//{{AFX_MSG_MAP(CInfoMgrView)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	//}}AFX_MSG_MAP
	ON_WM_CREATE ()	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoMgrView construction/destruction

CInfoMgrView::CInfoMgrView()
{
	// TODO: add construction code here

}

CInfoMgrView::~CInfoMgrView()
{
}

BOOL CInfoMgrView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	if (!CListView::PreCreateWindow (cs))
        return FALSE;

//	cs.style &= ~LVS_TYPEMASK;
    cs.style |= LVS_REPORT;
	return TRUE;;
}

/////////////////////////////////////////////////////////////////////////////
// CInfoMgrView drawing

void CInfoMgrView::OnDraw(CDC* pDC)
{
	CInfoMgrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CListCtrl& refCtrl = GetListCtrl();
	refCtrl.InsertItem(0, _T("Item!"));
	// TODO: add draw code for native data here
}

void CInfoMgrView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CInfoMgrView diagnostics

#ifdef _DEBUG
void CInfoMgrView::AssertValid() const
{
	CListView::AssertValid();
}

void CInfoMgrView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CInfoMgrDoc* CInfoMgrView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CInfoMgrDoc)));
	return (CInfoMgrDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInfoMgrView message handlers
void CInfoMgrView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}

void CInfoMgrView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class

	// delete all column headers
	if(pSender==(CView *)0xffffffff){	//OnListInstance signature: 0xffffffff
		GetListCtrl ().DeleteAllItems ();
		int nColumnCount = GetListCtrl().GetHeaderCtrl()->GetItemCount();
		// Delete all of the columns.
		for (int i=0;i < nColumnCount;i++){
			GetListCtrl().DeleteColumn(0);
		}
		return;
	}
	if (lHint == NULL) return;   // very important, on start up, it is NULL
	if (lHint==0xffffffff){
		CRecord * pR=(CRecord *)pHint;
		DisplayInstances(pR);
		return;
	}
	GetListCtrl ().DeleteAllItems ();	// clean up
	
	// get arguments passed in:
	HTREEITEM h=(HTREEITEM)lHint;
	treeCtrl=(CTreeCtrl *)pHint;
	
	//get pointer to selected tree item
	CRecord * pR=(CRecord *)treeCtrl->GetItemData(h);
	int ID=pR->ID;
	
	CInfoMgrDoc * pDoc=GetDocument();
	pDoc->pSearchPtr=pDoc->pNextPtr=pDoc->head;	//initialize pSearchPtr,pNextPtr
	
	CString strText;
	// loop through each child
	int nChildren=0;
	TCHAR buf[10];
	DisplayDefaultColumnName();
	// the following loop list each son of current node on the right pane control list
	while((pDoc->pSearchPtr=pDoc->FindNextWithParentID(ID))!=NULL){		
	
		LV_ITEM lvi;
		lvi.mask = LVIF_TEXT | LVIF_IMAGE ; 
		//lvi.mask =  LVIF_IMAGE ; 
		lvi.iItem = nChildren; 
		lvi.iSubItem = 0; 
		lvi.iImage = 0;
		lvi.pszText = _itot(nChildren+1,buf,10);//(char *)(LPCSTR)pDoc->pSearchPtr->Name; 
		//lvi.pszText = LPSTR_TEXTCALLBACK; 

		GetListCtrl ().InsertItem (&lvi);

		for(int j=1;j<5;j++){
			if(j==1)
#ifdef _UNICODE
				GetListCtrl ().SetItemText(nChildren,j,(TCHAR *)(LPCWSTR)pDoc->pSearchPtr->Name);
#else
				GetListCtrl ().SetItemText(nChildren,j,(TCHAR *)(LPCSTR)pDoc->pSearchPtr->Name);
#endif
			else if(j==2)
#ifdef _UNICODE
				GetListCtrl ().SetItemText(nChildren,j,(TCHAR *)(LPCWSTR)pDoc->pSearchPtr->Description);
#else
				GetListCtrl ().SetItemText(nChildren,j,(TCHAR *)(LPCSTR)pDoc->pSearchPtr->Description);
#endif
			else if(j==3)
				GetListCtrl ().SetItemText(nChildren,j,pDoc->pSearchPtr->hasDetail?_T("Yes"):_T("No"));
			else if(j==4)
				GetListCtrl ().SetItemText(nChildren,j,_itot(pDoc->pSearchPtr->ID,buf,10));
			
		}
		GetListCtrl().SetItemData(nChildren,(unsigned long)pDoc->pSearchPtr);
		nChildren++;
	}
	// if this is a leaf node, display full window
	CMainFrame * mf=(CMainFrame *)AfxGetApp()->m_pMainWnd;
	if(nChildren==0)
		//display current Node	
		mf->m_wndSplitter2.SetRowInfo(0,0,0);			
	else		
		mf->m_wndSplitter2.SetRowInfo(0,100,100);		
	mf->m_wndSplitter2.RecalcLayout();	
	
}
int CInfoMgrView::OnCreate (LPCREATESTRUCT lpcs)
{
    if (!CListView::OnCreate (lpcs) == -1)
        return -1;

//    m_imglLarge.Create (IDR_LARGEDOC, 32, 1, RGB (255, 0, 255));
//    m_imglSmall.Create (IDR_DRIVEIMAGES, 16, 1, RGB (255, 0, 255));

//    GetListCtrl ().SetImageList (&m_imglLarge, LVSIL_NORMAL);
//    GetListCtrl ().SetImageList (&m_imglSmall, LVSIL_STATE);

	GetListCtrl ().SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP  );
    return 0;
}

void CInfoMgrView::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	// using the columnCount to determine what mode it is in, List of items or list of instances
	int nColumnCount = GetListCtrl().GetHeaderCtrl()->GetItemCount();
	if(nColumnCount!=5)	return;
	POSITION pos = GetListCtrl().GetFirstSelectedItemPosition();
	if(pos!=NULL){
		int nItem = GetListCtrl().GetNextSelectedItem(pos);
		CRecord * p=(CRecord *)GetListCtrl().GetItemData(nItem);		
		//MessageBox(p->Name,"item clicked");
		//CRecord * p=(CRecord *)GetTreeCtrl().GetItemData(hSelected);
		CEditDialog editDlg(this,p);
		// Create and show the dialog box
		int nRet = -1;
		nRet = editDlg.DoModal();

		// Handle the return value from DoModal
		switch ( nRet ){
		case -1: 
			AfxMessageBox(_T("Edit Dialog box could not be created!"));
			break;
		case IDABORT:
			// Do something
			break;
		case IDOK:
			//UpdateAllItemInstances(p);		
			// Do something
			GetDocument ()->UpdateAllViews (this, (LPARAM)p);
			UpdateListRecord(nItem,p);
			break;
		case IDCANCEL:
			// Do something
			break;
		default:
			// Do something
			break;
		};
	}
	*pResult = 0;
}


void CInfoMgrView::UpdateListRecord(int nItem, CRecord *p)
{
	TCHAR buf[10];
		for(int j=1;j<5;j++){
			if(j==1)
#ifdef _UNICODE
				GetListCtrl ().SetItemText(nItem,j,(TCHAR *)(LPCWSTR)p->Name);
#else
				GetListCtrl ().SetItemText(nItem,j,(TCHAR *)(LPCSTR)p->Name);
#endif
			else if(j==2)
#ifdef _UNICODE
				GetListCtrl ().SetItemText(nItem,j,(TCHAR *)(LPCWSTR)p->Description);
#else
				GetListCtrl ().SetItemText(nItem,j,(TCHAR *)(LPCSTR)p->Description);
#endif
			else if(j==3)
				GetListCtrl ().SetItemText(nItem,j,p->hasDetail?_T("Yes"):_T("No"));
			else if(j==4)
				GetListCtrl ().SetItemText(nItem,j,_itot(p->ID,buf,10));
		}			
}

void CInfoMgrView::DisplayDefaultColumnName()
{

	int nColumnCount = GetListCtrl().GetHeaderCtrl()->GetItemCount();

	// Delete all of the columns.
	for (int i=0;i < nColumnCount;i++){
		GetListCtrl().DeleteColumn(0);
	}
	GetListCtrl ().InsertColumn (0, _T("No"), LVCFMT_LEFT, 30);
    GetListCtrl ().InsertColumn (1, _T("Name"), LVCFMT_LEFT, 192);
    GetListCtrl ().InsertColumn (2, _T("Description"), LVCFMT_LEFT, 196);
    GetListCtrl ().InsertColumn (3, _T("Has Detail"), LVCFMT_LEFT, 50);
	GetListCtrl ().InsertColumn (4, _T("ID"), LVCFMT_LEFT, 50);
}

void CInfoMgrView::DisplayInstances(CRecord *p)
{
	DisplayInstanceColumnName();
	HTREEITEM hItem;
	if(p){
		if(p->AnyNodeHandle()){
			int counter=0;
			while(p->pos){
				hItem=p->GetNextNodeHandle();
				counter++;
				AddToList(counter,hItem);
			}		
		}
	}
}

void CInfoMgrView::DisplayInstanceColumnName()
{

	int nColumnCount = GetListCtrl().GetHeaderCtrl()->GetItemCount();
	GetListCtrl().DeleteAllItems();
	// Delete all of the columns.
	for (int i=0;i < nColumnCount;i++){
		GetListCtrl().DeleteColumn(0);
	}
	GetListCtrl ().InsertColumn (0, _T("No"), LVCFMT_LEFT, 30);
    GetListCtrl ().InsertColumn (1, _T("Name"), LVCFMT_LEFT, 90);    
	GetListCtrl ().InsertColumn (2, _T("Path"), LVCFMT_LEFT, 400);    
}

void CInfoMgrView::AddToList(int counter,HTREEITEM hItem)
{
	CString ItemPath=getItemPath(hItem);
	if(ItemPath=="")return;	//item path is "" means not exist
	TCHAR buf[10];
	LV_ITEM lvi;
	lvi.mask = LVIF_TEXT; 
	//lvi.mask =  LVIF_IMAGE ; 
	lvi.iItem = counter-1; 
	lvi.iSubItem = 0; 
	lvi.iImage = 0;
	lvi.pszText = _itot(counter,buf,10);//(char *)(LPCSTR)pDoc->pSearchPtr->Name; 
	//lvi.pszText = LPSTR_TEXTCALLBACK; 
	GetListCtrl ().InsertItem (&lvi);
	CRecord * p=(CRecord *)treeCtrl->GetItemData(hItem);		
	for(int j=1;j<3;j++){
		if(j==1)
#ifdef _UNICODE
			GetListCtrl ().SetItemText(counter-1,j,(TCHAR *)(LPCWSTR)p->Name);
#else
			GetListCtrl ().SetItemText(counter-1,j,(TCHAR *)(LPCSTR)p->Name);
#endif
		else if(j==2)
#ifdef _UNICODE
			GetListCtrl ().SetItemText(counter-1,j,(TCHAR *)(LPCWSTR)ItemPath);
#else
			GetListCtrl ().SetItemText(counter-1,j,(TCHAR *)(LPCSTR)ItemPath);
#endif
	}
}

CString CInfoMgrView::getItemPath(HTREEITEM hItem)
{
	CString ItemPath="";
	HTREEITEM hSelected=hItem;
	if(hSelected){
		do {
			CString itemname=getItemName(hSelected);
			if(itemname=="")
				return "";
			ItemPath=itemname+ItemPath;
			ItemPath="\\"+ItemPath;						
			
			hSelected=treeCtrl->GetParentItem(hSelected);			
		}while(hSelected);		
	}
	return ItemPath;
}
CString CInfoMgrView::getItemName(HTREEITEM hItem)
{
	CRecord * p=(CRecord *)treeCtrl->GetItemData(hItem);
	return p->Name;	
}
