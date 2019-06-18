// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "InfoMgr.h"

#include "InfoMgrDoc.h"
#include "LeftView.h"
#include "InfoMgrView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	ON_WM_CREATE()
	//{{AFX_MSG_MAP(CLeftView)	
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelectionChanged)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRightClick)
	ON_WM_RBUTTONDOWN()	
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_FIND, OnSearch)
	ON_COMMAND(ID_SORT, OnSort)
	ON_COMMAND(ID_LISTINST, OnListinst)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_EDIT_UNDO, OnUndo)
	ON_COMMAND(ID_EDIT_POSITION, OnMovePosition)
	ON_COMMAND(ID_MOVEUP, OnMoveup)
	ON_COMMAND(ID_MOVEDOWN, OnMovedown)
	ON_COMMAND(ID_EDIT_REDO, OnRedo)
	ON_COMMAND(ID_EDIT_Collapse, OnEDITCollapse)
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
	//ON_WM_CONTEXTMENU()	
	ON_COMMAND(ID_CLEAR,OnClearIcons)
	ON_COMMAND(ID_SHOWALL,OnShowAll)
	ON_COMMAND(ID_EDIT_INSERT,OnInsert)
	ON_COMMAND(ID_EDIT_COPY,OnCopy)
	ON_COMMAND(ID_EDIT_PASTE,OnPaste)
	ON_COMMAND(ID_EDIT_CUT,OnMove)
	ON_COMMAND(ID_EDIT_DELETE,OnDelete)	
	ON_COMMAND(ID_EDIT_ITEM,OnEditItem)
END_MESSAGE_MAP()
#define SHIFT	5
#define DELITEM 4
#define INSERT	3
#define MOVE	2
#define COPY	1
#define NOTHING 0
/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView()
{
	// TODO: add construction code here	
	bMove=NOTHING;
	TreeNodeHandleOnClipboard=NULL;
	head=tail=NULL;
	doingMoveUpDown=FALSE;
	hDragSrc=NULL;			//added on 417
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	if (!CTreeView::PreCreateWindow (cs))
        return FALSE;
	
	cs.style |= TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	CInfoMgrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
	//SetWindowPos(this,0,0,400,200,SWP_SHOWWINDOW);
	//DragAcceptFiles();
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

CInfoMgrDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CInfoMgrDoc)));
	return (CInfoMgrDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers
void CLeftView::OnContextMenu(CWnd * pWnd, CPoint point){
	//point is to the screen !
	/*
	CString msg;
	msg.Format("you right clicked on x=%d, y=%d",point.x,point.y);
	MessageBox(msg,"Context menu");
	*/
	CMenu menu;
	menu.LoadMenu(IDR_CONTEXTMENU);
	CMenu * pContextmenu=menu.GetSubMenu(0);
	pContextmenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,point.x,point.y,AfxGetMainWnd());

}
void CLeftView::OnInsert(){
	
	//MessageBox("Insert !!!","Context menu running");	
	HTREEITEM hItem= GetTreeCtrl().GetSelectedItem();
//	GetTreeCtrl().InsertItem("Position 4",3,4,hItem,

	CRecord * node=new CRecord(&GetTreeCtrl());
	//node->insert(hItem);		// pass in parent node handle
	CRecord * target;
	if(hItem)
		target=(CRecord *)GetTreeCtrl().GetItemData(hItem);
	else
		target=NULL;
	HTREEITEM justinserted=BigInsert(target,node);
	//HTREEITEM justinserted=node->insert(hItem);
	GetDocument()->AddToList(node);	
	GetDocument()->SetModifiedFlag();
	RecordAction((HTREEITEM)node->ID,justinserted,INSERT,target,node);
	GetTreeCtrl().SelectItem(justinserted);	// make the one just inserted selected
	OnEditItem();							// then edit the item
}
void CLeftView::OnDelete(){
	HTREEITEM hItem= GetTreeCtrl().GetSelectedItem();
	HTREEITEM hParentItem=GetTreeCtrl().GetParentItem(hItem);
	CRecord * pDeleted=(CRecord *)GetTreeCtrl().GetItemData(hItem);
	doingMoveUpDown=TRUE;
	DeleteTree(hItem);
	doingMoveUpDown=FALSE;
	GetDocument()->SetModifiedFlag();

	RecordAction(hParentItem,pDeleted,DELITEM);
	//MessageBox(_T("Deleted !!!"),_T("Context menu running"));	
	CString msg;
	msg.Format(_T("%s deleted !"),pDeleted->Name);
	msgbox(this,1,msg,_T("Deleting ..."));
}

int CLeftView::OnCreate(LPCREATESTRUCT lpcs)
{
	if (CTreeView::OnCreate (lpcs) == -1)
        return -1;

    m_imglDrives.Create (IDR_DRIVEIMAGES, 16, 1, RGB (255, 0, 255));
    GetTreeCtrl ().SetImageList (&m_imglDrives, TVSIL_NORMAL);
	//GetTreeCtrl ().SetImageList (&m_imglDrives1, TVSIL_STATE );
	
	//COLORREF crColor = RGB(0,255,0);
	//GetTreeCtrl ().SetInsertMarkColor(crColor);
	//GetTreeCtrl ().SetItemHeight(16);

	m_dropTarget.Register(this);
	//SetWindowLong(this->m_hWnd,0,TVS_HASLINES) ;
    //InitTree ();
	DragAcceptFiles();
    return 0;
}
void CLeftView::OnCopy(){
	//MessageBox("OnCopy called","Context menu running");	
	//GetTreeCtrl().SetBkColor(RGB(255,240,240));
	RestoreClipboardItemStates();	
	TreeNodeHandleOnClipboard = GetTreeCtrl().GetSelectedItem();
	UINT nState=TVIS_CUT ; 
	UINT nStateMask=TVIS_CUT ; 		
	GetTreeCtrl().SetItemState(TreeNodeHandleOnClipboard,nState,nStateMask);
	bMove=COPY;
}
void CLeftView::OnPaste(){		
	if(bMove==NOTHING)	// if bMove==NOTHING, TreeNodeHandleOnClipboard might be NULL
		return;
	if(bMove==COPY){
		DoCopy(TreeNodeHandleOnClipboard,GetTreeCtrl().GetSelectedItem());
		RestoreClipboardItemStates();
	}else if(bMove==MOVE){
		DoMove(TreeNodeHandleOnClipboard,GetTreeCtrl().GetSelectedItem());
		TreeNodeHandleOnClipboard=NULL;
	}else if(bMove==SHIFT){	
		DoLink(TreeNodeHandleOnClipboard,GetTreeCtrl().GetSelectedItem());
		TreeNodeHandleOnClipboard=NULL;
	}
	bMove=NOTHING;
}
void CLeftView::OnMove(){
	RestoreClipboardItemStates();	
	TreeNodeHandleOnClipboard = GetTreeCtrl().GetSelectedItem();
	UINT nState=TVIS_CUT ; 
	UINT nStateMask=TVIS_CUT ; 		
	GetTreeCtrl().SetItemState(TreeNodeHandleOnClipboard,nState,nStateMask);
	bMove=MOVE;
}

void CLeftView::DeleteTree(HTREEITEM hItem)
{	
	//HTREEITEM savedhItem=hItem;	
	CRecord * pRootNode=(CRecord *)GetTreeCtrl().GetItemData(hItem); // pointer to root node of subtree to be deleted
	HTREEITEM hParent=GetTreeCtrl().GetParentItem(hItem);			// parent node handle
	CRecord * pParentNode;
	int parentID;
	if(hParent==0){		// if does not have a parent
		parentID=0;
	}else{
		pParentNode=(CRecord * )GetTreeCtrl().GetItemData(hParent);
		parentID=pParentNode->ID;
	}
	if(!pRootNode)
		return;		//something is wrong
	
	// update the nodeHandleList
	pRootNode->RemoveFromHandleList(hItem);		
	// update the parentIDList		
	pRootNode->RemoveFromParentIDList(hParent);	
	int pCount=pRootNode->parentIDlist.GetCount();
	DeleteChildren(hItem,pCount);		
	//delete all items whose parent ID is the parentID
	if(pRootNode->AnyNodeHandle()){
		while(pRootNode->pos){
			HTREEITEM h=pRootNode->GetNextNodeHandle();
			HTREEITEM hParent=GetTreeCtrl().GetParentItem(h);
			if(hParent!=0){
				CRecord * pParent=(CRecord *)GetTreeCtrl().GetItemData(hParent);
				if(parentID==pParent->ID){
					pRootNode->RemoveFromHandleList(h);		//<=inserted this line to fix the bug
					GetTreeCtrl().DeleteItem(h);
				}
			}
		}
	}	
	GetTreeCtrl().DeleteItem(hItem);
}
////////////////////////////////////////////////////////////////////////////////////
// delete children only handle wise and parent ID wise, no DeleteItem is necessary
void CLeftView::DeleteChildren(HTREEITEM hRoot,int parentCount){
	// The pointer to my tree control.
	CTreeCtrl* pmyTreeCtrl=&GetTreeCtrl();
	CRecord * pRoot=(CRecord *)pmyTreeCtrl->GetItemData(hRoot);
	CRecord * pChild;				
	// The item whose children will be deleted.
	HTREEITEM hmyItem=hRoot;

	// Delete all of the children of hmyItem.
	if (pmyTreeCtrl->ItemHasChildren(hmyItem)){
		HTREEITEM hNextItem;
		HTREEITEM hChildItem = pmyTreeCtrl->GetChildItem(hmyItem);

		while (hChildItem != NULL){
			hNextItem = pmyTreeCtrl->GetNextItem(hChildItem, TVGN_NEXT);			
			pChild=(CRecord *)pmyTreeCtrl->GetItemData(hChildItem);
			//pChild->RemoveFromHandleList(hRoot);			<== fixed a bug
			pChild->RemoveFromHandleList(hChildItem);			
			if((parentCount==0)&&(!doingMoveUpDown))				// if root does not have any parent, remove the parentID
				pChild->RemoveFromParentIDList(pRoot->ID);
			int theParentCount=pChild->parentIDlist.GetCount();
			DeleteChildren(hChildItem,theParentCount);
			//pmyTreeCtrl->DeleteItem(hChildItem);
			hChildItem = hNextItem;
		}
	}
}


int CLeftView::getParentID(HTREEITEM me)
{
	HTREEITEM hsrcParent=GetTreeCtrl().GetParentItem(me);
	CRecord * srcParentNode;
	if(hsrcParent)
		srcParentNode=(CRecord * )GetTreeCtrl().GetItemData(hsrcParent);
	else
		return 0;
	return srcParentNode->ID;
}

HTREEITEM CLeftView::BigInsert(CRecord *target, CRecord *source)
{
	return BigInsertAfter(target,source,TVI_LAST);	
}
void CLeftView::OnEditItem(){
	HTREEITEM hSelected=GetTreeCtrl().GetSelectedItem();
	if(!hSelected) return;	// if none selected,do nothing
	
	CRecord * p=(CRecord *)GetTreeCtrl().GetItemData(hSelected);
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
		{
			BOOL bReadOnly=((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_bReadOnly;	
			if(bReadOnly) break;
		}
		UpdateAllItemInstances(p);
		GetDocument()->SetModifiedFlag();
		// Do something
		break;
	case IDCANCEL:
		// Do something
		break;
	default:
		// Do something
		break;
	};
}
void CLeftView::OnSelectionChanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	HTREEITEM h=GetTreeCtrl().GetSelectedItem();
	if(h==0){
		*pResult = 0;
		return;
	}
	CRecord * cr=(CRecord *)GetTreeCtrl().GetItemData(h);
	CString name=cr->Name;	
	//MessageBox(name,"Selection Changed");	
	GetDocument ()->UpdateAllViews (this, (LPARAM) h,(CObject *)&GetTreeCtrl());
	//--------------------------------
	*pResult = 0;
}

void CLeftView::UpdateAllItemInstances(CRecord *p)
{
	if(p->AnyNodeHandle()){
		while(p->pos){
			HTREEITEM item=p->GetNextNodeHandle();
			GetTreeCtrl().SetItem(item,TVIF_TEXT,p->Name,0,0,0,0,0);  //update the item's label	
		}		
	}
}

void CLeftView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (lHint == NULL) return;   // very important, on start up, it is NULL
	if((const unsigned int)pSender==0xffffffff){
		if(head!=NULL){
			DeleteFrom(head);
			head=tail=NULL;
		}
	}
	CRecord * p=(CRecord *) lHint;
	UpdateAllItemInstances(p);
	GetDocument()->SetModifiedFlag();
}

void CLeftView::OnRightClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	//MessageBox("right clicked");
	//OnContextMenu(this,NULL);
	*pResult = 0;
}

void CLeftView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	/*
		//UINT nState=TVIS_BOLD; 
		//UINT nStateMask=TVIS_BOLD; 		
		//GetTreeCtrl().SetItemState(hSelectedItem,nState,nStateMask);
		//GetTreeCtrl().SetInsertMark(hSelectedItem);			
	}*/
	//-----------------------------------------------	

	UINT uFlags;
	HTREEITEM hItem=GetTreeCtrl().HitTest(point,&uFlags);	
	
	GetTreeCtrl().SelectItem(hItem);	
	ClientToScreen( &point );
	OnContextMenu(this,point);

	//CTreeView::OnRButtonDown(nFlags, point);
}


void CLeftView::RestoreClipboardItemStates()
{
	if(TreeNodeHandleOnClipboard==NULL) return;	
	//if a handle was on Clipboard		
	UINT nStateMask;
	UINT nState;
	nStateMask=TVIS_SELECTED|TVIS_CUT; 	//only get 2 states, selected and cut
	nState=GetTreeCtrl().GetItemState(TreeNodeHandleOnClipboard, nStateMask );	// get states in nState
	nStateMask=0xffff^nStateMask;		//flip the bits in mask	to get the states we are going to turn off	
	nState=nState&nStateMask;			// turn off the 2 bits
	GetTreeCtrl().SetItemState(TreeNodeHandleOnClipboard,nState,TVIS_SELECTED|TVIS_CUT);	// turn off the bits
	TreeNodeHandleOnClipboard=NULL;	
}
HTREEITEM hPreselectedBefore;	
BOOL AbsolutePath;
DROPEFFECT CLeftView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	// TODO: Add your specialized code here and/or call the base class	
	//TRACE(_T("OnDragOver %d: "),dn);
	UINT uFlags;
	HTREEITEM hPreselected=GetTreeCtrl().HitTest(point,&uFlags);	
	if(hPreselected){
		if(hPreselected!=hPreselectedBefore){
			if(hPreselectedBefore){
				GetTreeCtrl().SetItemImage(hPreselectedBefore,3,4);
			}
			CRecord * p=(CRecord *)GetTreeCtrl().GetItemData(hPreselected);
			TRACE(_T("Dragging over item %s\n"),p->Name);
			if(MK_ALT&dwKeyState){
				TRACE(_T("Alt pressed while Dragging over item %s\n"),p->Name);
				GetTreeCtrl().SetInsertMark(hPreselected);
			}
			if(MK_CONTROL&dwKeyState){
				TRACE(_T("Control key pressed while Dragging over item %s\n"),p->Name);				
			}
			GetTreeCtrl().SelectDropTarget(hPreselected); //<====inserted
			OnClearIcons();
			GetTreeCtrl().SetItemImage(hPreselected,1,2);
			if(hDragSrc!=NULL)
				GetTreeCtrl().SetItemImage(hDragSrc,0,4);			
		}
	}	
	//TRACE(_T("\n"));
	AbsolutePath=TRUE;
	//HTREEITEM hItemSrc=GetTreeCtrl().GetSelectedItem();	
	//DROPEFFECT effect=CTreeView::OnDragOver(pDataObject, dwKeyState, point);
	hPreselectedBefore=hPreselected;
	if(MK_CONTROL&dwKeyState){
		GetTreeCtrl().SetInsertMark(0);
		TRACE(_T("DROPEFFECT_COPY is being used ...(control key pressed)"));
		AbsolutePath=FALSE;
		return DROPEFFECT_COPY;
	}
	if(MK_ALT&dwKeyState){
		m_FileDrop=TRUE;
		TRACE(_T("DROPEFFECT_LINK is being used ...(Alt key pressed)"));
		return DROPEFFECT_LINK;
	}
	if(MK_ALT&dwKeyState){
		TRACE(_T("DROPEFFECT_LINK\n"));
		return DROPEFFECT_LINK; // use link to represent change order
	}
	GetTreeCtrl().SetInsertMark(0);
	return DROPEFFECT_MOVE;
}
void msg(int i){
	CString msg1;
	msg1.Format(_T("Position %d"),i);
    MessageBox(NULL,msg1,_T("Debug msg"),MB_OK);
}
void CLeftView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	// This action starts a drag and wong return until releaseing mouse

	//CString tmp;
    //tmp.Format(_T("Test"));
	//MessageBox(tmp);

	
	CTreeView::OnLButtonDown(nFlags, point);  // make the clicked on item selected etc.
	
	BOOL bReadOnly=((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_bReadOnly;	
	if(bReadOnly){	
		return;
	}
	m_FileDrop=FALSE;
	TRACE(_T("OnLButtonDown\n"));	
	//return ;/*
	//HTREEITEM hItemSrc=GetTreeCtrl().GetSelectedItem();
	UINT uFlags;
	hDragSrc=GetTreeCtrl().HitTest(point,&uFlags);
	
	if((hDragSrc!=NULL)&&((TVHT_ONITEMLABEL|TVHT_ONITEMRIGHT)&uFlags)&&(!bReadOnly)){
		CRecord * pSrcItem=(CRecord * )GetTreeCtrl().GetItemData(hDragSrc);		
		TRACE(_T("You are dragging Item %s\n"),pSrcItem->Name);
		//CDropSrc dropSrc;
		RECT rect;
		GetTreeCtrl().GetItemRect(hDragSrc,&rect,FALSE);
		DROPEFFECT DragEffect=m_dragSource.DoDragDrop(DROPEFFECT_COPY|DROPEFFECT_MOVE|DROPEFFECT_LINK,&rect);

		if(DragEffect==DROPEFFECT_COPY){
			TRACE(_T("Drag copy finished\n"));		
		}else if(DragEffect==DROPEFFECT_MOVE){
			TRACE(_T("Drag move finised\n"));			
		}
		GetTreeCtrl().SelectDropTarget(NULL);
		TRACE(_T("Drag & Drop finished\n"));
	
	}else{		
		if(!bReadOnly)
		GetTreeCtrl().SelectItem(NULL);		//deselect item
		TRACE(_T("No Item is selected\n"));

	}
}

void CLeftView::OnShowAll()
{
	//MessageBox(_T("OnShowAll"));
	HTREEITEM hItem=GetTreeCtrl().GetSelectedItem();
	if(!hItem) return;
	ShowAllInsstances(hItem);
}

void CLeftView::OnClearIcons()
{
	int n=IconSetList.GetCount();
	for(int i=n-1;i>=0;i--){
		HTREEITEM hItem=IconSetList.GetTail();
		GetTreeCtrl().SetItemImage(hItem,3,4);
		IconSetList.RemoveTail();
	}
}

void CLeftView::OnSearch() 
{
	// TODO: Add your command handler code here
	//MessageBox("Search");
	CFindDialog findDlg(this,GetDocument());
//	findDlg.ShowWindow(SW_SHOW);
	// Create and show the dialog box
	int nRet = -1;
	nRet = findDlg.DoModal();

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
		//GetDocument()->SetModifiedFlag();
		// Do something
		break;
	case IDCANCEL:
		// Do something
		break;
	default:
		// Do something
		break;
	};

}

void CLeftView::ShowAllInsstances(HTREEITEM hItem)
{	
	ShowInstances(hItem,FALSE);
}
void CLeftView::ShowInstances(HTREEITEM hItem,BOOL bShowFirstOnly)
{
	CRecord * p=(CRecord *)GetTreeCtrl().GetItemData(hItem);
	ShowInstances(p,bShowFirstOnly);	
}
void CLeftView::ShowInstances(CRecord * p,BOOL bShowFirstOnly)
{	
	HTREEITEM hItem;
	if(p){
		if(p->AnyNodeHandle()){
			while(p->pos){
				hItem=p->GetNextNodeHandle();
				GetTreeCtrl().EnsureVisible(hItem);
				GetTreeCtrl().SetItemImage(hItem,1,2);
				IconSetList.AddTail(hItem);
				if(bShowFirstOnly) break;
			}		
		}
	}
}
HTREEITEM DroppedOnItem;
BOOL CLeftView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
	// TODO: Add your specialized code here and/or call the base class
	GetTreeCtrl().SetInsertMark(0);
	TRACE(_T("OnDrop\n"));
	UINT uFlags;
	HTREEITEM	hPreselected=GetTreeCtrl().HitTest(point,&uFlags);
	DroppedOnItem=hPreselected;
	if(hPreselected){
		CRecord * p=(CRecord *)GetTreeCtrl().GetItemData(hPreselected);
		CRecord * p0;
		if(hDragSrc!=NULL){
			p0=(CRecord *)GetTreeCtrl().GetItemData(hDragSrc);
			TRACE(_T("The Dragged Item %s is dropped on item %s\n"),p0->Name,p->Name);
			IconSetList.AddTail(hDragSrc);		// 
		}
		IconSetList.AddTail(hPreselected);		// 		
	}
	hPreselectedBefore=NULL;
	if(hDragSrc==hPreselected)
		return FALSE;
	if(m_FileDrop){
		return FALSE;
	}
	if(dropEffect==DROPEFFECT_MOVE)
		DoMove(hDragSrc,hPreselected);
	else if(dropEffect==DROPEFFECT_COPY)
		DoCopy(hDragSrc,hPreselected);
	else if(dropEffect==DROPEFFECT_LINK)
		DoLink(hDragSrc,hPreselected);
	return TRUE;//CTreeView::OnDrop(pDataObject, dropEffect, point);
}


void CLeftView::DoMove(HTREEITEM src, HTREEITEM dest)
{	
	HTREEITEM JustInserted=DoCopy(src,dest);
	if(!JustInserted) return;
	int srcParentID=getParentID(src);
	//should delete all the node as a subtree root 
	//whose handle is on the handlist of the obj this handle (TreeNodeHandleOnClipboard) points to
	// first, get CRecord obj of this handle
	CRecord * obj=(CRecord *)GetTreeCtrl().GetItemData(src);
	HTREEITEM parentItem=GetTreeCtrl().GetParentItem(src);
	CRecord * srcParentObj;
	if(parentItem)
		srcParentObj=(CRecord *)GetTreeCtrl().GetItemData(parentItem);
	else
		srcParentObj=NULL;
	CRecord * destobj=(CRecord *)GetTreeCtrl().GetItemData(JustInserted);
	// second, loop through the handle list to deletetree all of them	
	if(obj->AnyNodeHandle()){
		while(obj->pos){
			HTREEITEM handle=obj->GetNextNodeHandle();			
			int parentID=getParentID(handle);
			if((JustInserted!=handle)&&(parentID==srcParentID))	// keep the one just inserted
			{
				POSITION savePos=obj->pos;
				DeleteTree(handle);
				obj->pos=savePos;
			}
		}
	}		
	RecordAction(srcParentObj,destobj,MOVE);
}

HTREEITEM CLeftView::DoCopy(HTREEITEM src, HTREEITEM dest)
{
	int srcParentID=getParentID(src);
	HTREEITEM hSelectedToPasteTo = dest;
	CRecord * srcNode,*targetNode;

	srcNode=(CRecord *)GetTreeCtrl().GetItemData(src);
	if(dest==0)
		targetNode=NULL;
	else{
		targetNode=(CRecord *)GetTreeCtrl().GetItemData(dest);
	
		if(targetNode->IsVerticalOffspringOf(GetDocument(),srcNode)){
			::MessageBox(NULL,_T("Invalid hierarchical Structure"),_T("Invalid Move/Copy Target"),MB_OK);
			return NULL;
		}
		if(srcNode->IsChildOf(targetNode)){
			::MessageBox(NULL,_T("Invalid hierarchical Structure"),_T("Invalid Move/Copy Target"),MB_OK);
			return NULL;
		}
	}
	//////////////////////////////////////////////////////////////////////////////////
	// like deleteTree, should insert to all the nodes whose handles are on the handlelist 
	// of the obj the handle points to with no exceptions
	// ////////////////orginal code:///////////////////////////////////////////////
	// HTREEITEM JustInserted=srcNode->insert(hSelectedToPasteTo);			
	// GetDocument()->addChildrenHandleWise(JustInserted);  // should be added handle wise, not ID wise
	//------------------------------------------------------------------
	// first, loop through handlelist of targetNode
	HTREEITEM JustInserted=BigInsert(targetNode,srcNode);
	GetDocument()->SetModifiedFlag();
	RecordAction(GetTreeCtrl().GetParentItem(src),JustInserted,COPY,targetNode,srcNode);
	return JustInserted;
}

void CLeftView::OnSort() 
{
	// TODO: Add your command handler code here
	HTREEITEM hSelected=GetTreeCtrl().GetSelectedItem();
	BOOL ret=GetTreeCtrl().SortChildren(hSelected);
	if(!ret)
		MessageBox(_T("Sorting children failed"));

}

void CLeftView::OnListinst() 
{
	// TODO: Add your command handler code here
	
	HTREEITEM h=GetTreeCtrl().GetSelectedItem();
	if(h==0){
		return;
	}
	CRecord * cr=(CRecord *)GetTreeCtrl().GetItemData(h);
	DWORD sig=0xffffffff;
	GetDocument ()->UpdateAllViews (this, (LPARAM)sig,(CObject *)cr); //goes to CInfoMgrView::OnUpdate

}

CString CLeftView::getItemName(HTREEITEM hItem)
{
	CRecord * p=(CRecord *)GetTreeCtrl().GetItemData(hItem);
	return p->Name;
}

void CLeftView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	//MessageBox("Double clicked");
	OnEditItem();
	*pResult = 0;
}

void CLeftView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	/*
	CString tmp;
    tmp.Format(_T("nChar=%d, nRepCnt=%d, nFlags=%d"),nChar,nRepCnt,nFlags);
	MessageBox(tmp);
	CMainFrame * pMain=(CMainFrame*)(AfxGetApp()->m_pMainWnd);
	CWnd* rp = pMain->m_wndSplitter.GetPane(0, 1);
	//CInfoMgrView *rp=pMain->GetRightPane();
	if(rp)
		rp->ShowWindow(SW_HIDE);
	else
		MessageBox(_T("Failed to get Right Pane"));
	return;
	*/
	BOOL bReadOnly=((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_bReadOnly;
	if(bReadOnly){
		CTreeView::OnKeyDown(nChar, nRepCnt, nFlags);
		return;
	}
	if(nChar==45){			// insert key
		OnInsert();			// insert a child
	}else if(nChar==16){	// shift key
		InsertaSibling();	// insert a sibling
	}else if(nChar==13){	//Enter key
		OnEditItem();
	}else if(nChar==46){	//Del key
		OnDelete();
	}

	CTreeView::OnKeyDown(nChar, nRepCnt, nFlags);

}

void CLeftView::RecordAction(HTREEITEM hSrcParent, HTREEITEM dest, int action, CRecord * pTarget, CRecord * pSrc)
{
    CUndoItem * ActionRecord=new CUndoItem();
	ActionRecord->hSrcParentitem=hSrcParent;
	ActionRecord->hDestitem=dest;
	ActionRecord->Action=action;
	ActionRecord->pDestRecord=pTarget;
	ActionRecord->pSrcRecord=pSrc;
	AddToUnDoList(ActionRecord);
}
void CLeftView::RecordAction(CRecord *pSrcRecord, CRecord *pDestRecord, int action)
{
	CUndoItem * ActionRecord=new CUndoItem();
	ActionRecord->pSrcRecord=pSrcRecord;
	ActionRecord->pDestRecord=pDestRecord;
	ActionRecord->Action=action;
	AddToUnDoList(ActionRecord);
}
void CLeftView::RecordAction(HTREEITEM hSrcParent, CRecord *pSrcRecord, int action)
{
    CUndoItem * ActionRecord=new CUndoItem();
	ActionRecord->hSrcParentitem=hSrcParent;
	ActionRecord->pSrcRecord=pSrcRecord;
	ActionRecord->Action=action;
	AddToUnDoList(ActionRecord);
}
void CLeftView::AddToUnDoList(CUndoItem *item)
{
	if((head==NULL)|(tail==NULL)){
		head=item;
		tail=head;
	}else{
		if(tail->Next!=NULL)
			DeleteFrom(tail->Next);
		tail->Next=item;
		item->Prev=tail;
		tail=item;
	}	
	
	CWnd* pMain = AfxGetMainWnd();
	
}

void CLeftView::OnUndo() 
{
	// TODO: Add your command handler code here
	if(tail==NULL){		
		return;
	}
	UndoAction(tail);
}

void CLeftView::UndoAction(CUndoItem *item)
{
	if(item->Action==COPY){
		DeleteTree(item->hDestitem);
		if(tail)
			tail=tail->Prev;				
	}else if(item->Action==MOVE){
		//BigInsert(item->pDestRecord,item->pSrcRecord);
		HTREEITEM justInserted=BigInsert(item->pSrcRecord,item->pDestRecord);
		item->hDestitem=justInserted;
		if(tail){
			tail=tail->Prev;				
			OnUndo(); //undo the copy action;
		}
	}else if(item->Action==INSERT){
		DeleteTree(item->hDestitem);
		if(tail)
			tail=tail->Prev;				
		CRecord::idCounter--;
	}else if(item->Action==DELITEM){
		HTREEITEM hItem= item->hSrcParentitem;
		CRecord * node=item->pSrcRecord;
		//node->insert(hItem);		// pass in parent node handle
		CRecord * target;
		if(hItem)
			target=(CRecord *)GetTreeCtrl().GetItemData(hItem);
		else
			target=NULL;
		HTREEITEM justinserted=BigInsert(target,node);
		item->hDestitem=justinserted;
		// get rid of the node from the undo node list
		if(tail)
			tail=tail->Prev;		
	}
}



void CLeftView::DoLink(HTREEITEM hDrag, HTREEITEM hDrop)
{
	CRecord * p=(CRecord *)GetTreeCtrl().GetItemData(hDrag);
	HTREEITEM hParent=GetTreeCtrl().GetParentItem(hDrag);
	CRecord * pParent;
	if(hParent)
		pParent=(CRecord *)GetTreeCtrl().GetItemData(hParent);
	else
		pParent=NULL;
	doingMoveUpDown=TRUE;
	DeleteTree(hDrag);	
	BigInsertAfter(pParent,p,hDrop);
	doingMoveUpDown=FALSE;
}

void CLeftView::OnMovePosition() 
{
	// TODO: Add your command handler code here
	RestoreClipboardItemStates();	
	TreeNodeHandleOnClipboard = GetTreeCtrl().GetSelectedItem();
	UINT nState=TVIS_CUT ; 
	UINT nStateMask=TVIS_CUT ; 		
	GetTreeCtrl().SetItemState(TreeNodeHandleOnClipboard,nState,nStateMask);
	bMove=SHIFT;
}

HTREEITEM CLeftView::BigInsertAfter(CRecord *target, CRecord *source, HTREEITEM hAfter)
{
	HTREEITEM JustInserted=NULL;
	HTREEITEM FirstInserted=NULL;
	if(target==NULL){
		JustInserted=source->insertAfter(NULL,hAfter);			
		FirstInserted=JustInserted;
		if(JustInserted)
			GetDocument()->addChildren(JustInserted);  // should be added handle wise, not ID wise			
	}else if(target->AnyNodeHandle()){
		int counter=0;
		while(target->pos){		
			HTREEITEM handle=target->GetNextNodeHandle();	 // target handle
			//source->ExpandWhenInsert=TRUE;
			JustInserted=source->insertAfter(handle,hAfter);
			if(counter==0)
				FirstInserted=JustInserted;
			if(JustInserted)
				GetDocument()->addChildren(JustInserted);  // should be added handle wise, not ID wise			
			counter++;
		}
	}else
		JustInserted=NULL;
	if((FirstInserted)&&(doingMoveUpDown))
		GetTreeCtrl().SelectItem(FirstInserted);
	return JustInserted;
}

void CLeftView::OnMoveup() 
{
	// TODO: Add your command handler code here
	HTREEITEM hItem=GetTreeCtrl().GetSelectedItem();
	if(!hItem) return;
	HTREEITEM hPrev=GetTreeCtrl().GetPrevSiblingItem(hItem);
	if(!hPrev) return;
	hPrev=GetTreeCtrl().GetPrevSiblingItem(hPrev);
	if(!hPrev) return;
	DoLink(hItem,hPrev);
	GetDocument()->SetModifiedFlag();
}

void CLeftView::OnMovedown() 
{
	// TODO: Add your command handler code here	
	HTREEITEM hItem=GetTreeCtrl().GetSelectedItem();
	if(!hItem) return;
	HTREEITEM hNext=GetTreeCtrl().GetNextSiblingItem(hItem);
	if(!hNext) return;
	DoLink(hItem,hNext);
	GetDocument()->SetModifiedFlag();
}

void CLeftView::DeleteFrom(CUndoItem *pHead)
{
	CUndoItem *pTmp;
	while(pHead!=NULL){
		pTmp=pHead->Next;
		delete pHead;
		pHead=pTmp;
	}
	pHead=NULL;
}

void CLeftView::OnRedo() 
{
	// TODO: Add your command handler code here
	if(tail==NULL){
		if(head==NULL)
			return;
		tail=head;
		Redo(tail);	
		return;
	}
	if(tail->Next==NULL)
		return;
	Redo(tail->Next);
	tail=tail->Next;
}

void CLeftView::Redo(CUndoItem *pItem){
	if(pItem->Action==INSERT){		
		BigInsert(pItem->pDestRecord,pItem->pSrcRecord);
		CRecord::idCounter++;
		GetDocument()->SetModifiedFlag();		
	}else if(pItem->Action==DELITEM){
		DeleteTree(pItem->hDestitem);
		GetDocument()->SetModifiedFlag();
	}else if(pItem->Action==MOVE){
		DeleteTree(pItem->hDestitem);
		GetDocument()->SetModifiedFlag();
	}else if(pItem->Action==COPY){
		BigInsert(pItem->pDestRecord,pItem->pSrcRecord);		
		GetDocument()->SetModifiedFlag();	
		if(pItem->Next!=NULL){
			if(pItem->Next->Action==MOVE)
				tail=tail->Next;
				Redo(pItem->Next);
		}
	}	
}


void CLeftView::OnEDITCollapse() 
{
	// TODO: Add your command handler code here
	//MessageBox("OnCollapse");
	CTreeCtrl* pmyTreeCtrl=&GetTreeCtrl();
	HTREEITEM h=GetTreeCtrl().GetRootItem();
	HTREEITEM h1=GetTreeCtrl().GetNextItem(NULL,TVGN_CHILD) ;
	while(h1!=NULL){
		//CRecord * r=(CRecord *)pmyTreeCtrl->GetItemData(h1);
		//MessageBox(r->Name);
		pmyTreeCtrl->Expand(h1,TVE_COLLAPSE);
		h1=GetTreeCtrl().GetNextItem(h1,TVGN_NEXT ) ;
	}
}

void CLeftView::InsertaSibling()
{
	HTREEITEM hItem= GetTreeCtrl().GetSelectedItem();
	HTREEITEM ParentItem=GetTreeCtrl().GetParentItem(hItem);
	GetTreeCtrl().SelectItem(ParentItem);
	OnInsert();
}

void CLeftView::OnDropFiles(HDROP hDropInfo) 
{
	// TODO: Add your message handler code here and/or call default
	int i=2;
	TRACE(_T("OnDropFile %d\n"),i);
	HDROP hdrop = hDropInfo;
	_TCHAR szFileName[_MAX_PATH + 1];
    if (NULL != hdrop){
        UINT nFiles = DragQueryFile(hdrop, (UINT)-1, NULL, 0);
	    for(UINT nNames = 0; nNames < nFiles; nNames++) {
            ZeroMemory(szFileName, _MAX_PATH + 1);
            DragQueryFile(hdrop, nNames, (LPTSTR)szFileName, _MAX_PATH + 1);			
			//m_Description=szFileName;
			TRACE(_T("OnDropFile fname=%s\n"),szFileName);
			InsertNode(szFileName);
		}
	}  
	CTreeView::OnDropFiles(hDropInfo);
	
	CTreeCtrl* pmyTreeCtrl=&GetTreeCtrl();
	if(DroppedOnItem!=NULL)
		pmyTreeCtrl->Expand(DroppedOnItem,TVE_EXPAND);
}
#define INSERT	3
extern CString exepath;
void CLeftView::InsertNode(_TCHAR *link)
{	
	BOOL bReadOnly=((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_bReadOnly;	
	if(bReadOnly){	
		return;
	}
	HTREEITEM hItem= DroppedOnItem;//GetTreeCtrl().GetSelectedItem();
	CRecord * node=new CRecord(&(GetTreeCtrl()));

	if(AbsolutePath){
		TRACE("Absolute Path\n");
		node->Description=link;
	}else{
		TRACE("Relative Path\n");
		CString absPath=link;
		absPath.MakeUpper();
		exepath.MakeUpper();
		if(absPath.Find(exepath)==0){
			int loc=exepath.GetLength();
			node->Description=_T("::")+absPath.Mid(loc);   // add double colon to indicate a relative path
		}else
			node->Description=link;	
	}

	node->Name=link;
	//node->Description=link;
	int pos=node->Name.ReverseFind('\\');
	if(pos>0)
		node->Name=node->Name.Mid(pos+1);

	CRecord * target;
	if(hItem)
		target=(CRecord *)GetTreeCtrl().GetItemData(hItem);
	else
		target=NULL;

	HTREEITEM justinserted=BigInsert(target,node);

	GetDocument()->AddToList(node);	
	GetDocument()->SetModifiedFlag();
	RecordAction((HTREEITEM)node->ID,justinserted,INSERT,target,node);
}
