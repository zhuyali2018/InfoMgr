// Record.cpp: implementation of the CRecord class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "InfoMgr.h"
#include "Record.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
// Image indexes
#define ILI_HARD_DISK       0
#define ILI_FLOPPY          1
#define ILI_CD_ROM          2
#define ILI_NET_DRIVE       0
#define ILI_RAM_DRIVE       0
#define ILI_CLOSED_FOLDER   3
#define ILI_OPEN_FOLDER     4


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRecord::CRecord()
{
	initializer();
}
CRecord::CRecord(CTreeCtrl * tc)
{	
	initializer();
	treeCtrl=tc;		
}
CRecord::CRecord(CString line)
{
	//hasDetail=FALSE;
	//ID=getNextRecordID();
	//TCHAR buf[20];
	//Name=(CString)"New Node "+itoa(ID,buf,10);
	saveID=0;
	ExpandWhenInsert=FALSE;
	Next=NULL;
	Prev=NULL;
	hasDetail=false;
	if(line==""){
		MessageBox(NULL,_T("Bad Record"),_T("Loading"),MB_OK);
		return;
	}
	CString tline=line;
	if(line.Find(_T("<ParentID>"))>0){		
		char delimiter='^';
		int count=0;
		int pos=tline.Find(delimiter);
		while((pos>=0)||(tline.GetLength()>0)){			
			CString substring;
			if(pos>=0)
				substring=tline.Mid(0,pos);		
			else
				substring=tline;
			count++;
			if(count==1) {				// ID
				ID=_ttoi(substring);
			}else if(count==2) {		// Parent IDs
				int pos2=substring.Find(_T("</ParentID>"));
				int pos3=substring.Find(_T("<ParentID>"));
				int len=pos2-pos3-10;
				CString tmp=substring.Mid(10,len);
				//foreach(string subID in tmp.Split('-')){
				int pos1=tmp.Find('-');				
				while(pos1>0){
					CString token=tmp.Mid(0,pos1);
					int id=_ttoi(token);
					AddParentID(id);
					tmp=tmp.Mid(pos1+1);
					pos1=tmp.Find('-');
				}
				if(tmp.GetLength()>0){	// if parent list is empty, that means the node has been deleted
					int id=_ttoi(tmp);
					AddParentID(id);	
				}
			}else if(count==3) {
				Name=substring;
			}else if(count==4) {
				Description=substring;
			}else if(count==5) {
				if(substring=="hasdetail")
					hasDetail=true;
				else
					hasDetail=false;
			}
			if(pos>=0){
				tline=tline.Mid(pos+1);
				pos=tline.Find(delimiter);
			}else
				tline="";			
		}
	}			
}

CRecord::~CRecord()
{

}

int CRecord::getNextRecordID()
{
	return ++idCounter;
}

void CRecord::AddParentID(HTREEITEM hParentNode)
{
	if(!hParentNode){	// if the parentNode is NULL, which means the root, ID should be 0
		AddParentID(0);
		return;
	}
	CRecord * ptr=(CRecord *)treeCtrl->GetItemData(hParentNode);
	if(ptr){
		AddParentID(ptr->ID);	// should work the same as above line
	}	
}
void CRecord::AddParentID(int parentID)
{
	int pid;
	if(AnyParentID()){	
		while(pos!=NULL){
			pid=GetNextParentID();
			if(pid==parentID) return;
		}
	}
	parentIDlist.AddTail(parentID);
}

void CRecord::initializer()
{
	hasDetail=FALSE;
	ID=getNextRecordID();
	TCHAR buf[20];
	Name=(CString)"New Node "+_itot(ID,buf,10);
	Next=NULL;
	Prev=NULL;
	saveID=0;
	ExpandWhenInsert=FALSE;
}


BOOL CRecord::AnyNodeHandle()
{
	pos = nodeHandleList.GetHeadPosition();
	if(pos)
		return TRUE;
	return FALSE;
}

HTREEITEM CRecord::GetNextNodeHandle()
{
	return nodeHandleList.GetNext(pos);	
}

BOOL CRecord::AnyParentID()
{
	pos = parentIDlist.GetHeadPosition();
	if(pos)
		return TRUE;
	return FALSE;
}

int CRecord::GetNextParentID()
{
	return parentIDlist.GetNext(pos);	
}
HTREEITEM CRecord::insert(HTREEITEM hParentNode)
{	
	return insertAfter(hParentNode,TVI_LAST);
}

int CRecord::RemoveFromHandleList(HTREEITEM hItem)
{
	POSITION pos;
	if(hItem)
		pos=nodeHandleList.Find(hItem);	
	else
		pos=nodeHandleList.Find(NULL);	

	if(pos){		
		nodeHandleList.RemoveAt(pos);	// remove the ID from parentIDlist of recordObj
		return nodeHandleList.GetCount();			
	}
	return 0;
}

int CRecord::RemoveFromParentIDList(HTREEITEM parentHandle1)
{
	CRecord * parentNode;	
	if(parentHandle1!=0){
		parentNode=(CRecord * )treeCtrl->GetItemData(parentHandle1); // get  ptr to node
		return RemoveFromParentIDList(parentNode->ID);	
	}	
	return RemoveFromParentIDList(0);
}

int CRecord::RemoveFromParentIDList(int parentID)
{
	POSITION pos=parentIDlist.Find(parentID);
	if(pos){
		parentIDlist.RemoveAt(pos);	// remove the ID from parentIDlist of recordObj
		int count=parentIDlist.GetCount();			
		return count;
	}		
	return 0;
}

BOOL CRecord::IsVerticalOffspringOf(CDocument *pDoc1,CRecord *p)
{
	CInfoMgrDoc *pDoc=(CInfoMgrDoc *)pDoc1;
	int id1=p->ID;	//id to be checked against
	if(id1==ID)
		return TRUE;	// can not copy /past to your self
	int id;			//id of one of parents of this obj
	POSITION pos = parentIDlist.GetHeadPosition();
	for (int i=0;i < parentIDlist.GetCount();i++){	//loop through parent ID list
		id=parentIDlist.GetNext(pos);
		if(id==id1)									
			return TRUE;							// found a match in parent list
		CRecord *pCRecord=pDoc->head;				// if not match, check the parents of the parent
		while(pCRecord!=NULL){			//loop through the CRecord object list looking for obj with the ID
			if(id==pCRecord->ID){		// found parent record obj according to parent ID
				if(pCRecord->IsVerticalOffspringOf(pDoc,p))	// see if its parent list contains the checked ID
					return TRUE;					// if found, return true, if not continue the loop - recursive call
			}										
			pCRecord=pCRecord->Next;
		}
	}

	return FALSE;
}

void CRecord::AddHandle(HTREEITEM hItem)
{
	if(AnyNodeHandle()){
		while(pos){
			HTREEITEM item=GetNextNodeHandle();
			if(item==hItem)
				return;
		}	
	}
	nodeHandleList.AddTail(hItem);
}

HTREEITEM CRecord::insertAfter(HTREEITEM hParentNode, HTREEITEM hAfter)
{
	HTREEITEM hNode;
	if(treeCtrl){
		hNode=treeCtrl->InsertItem(Name,ILI_CLOSED_FOLDER,ILI_OPEN_FOLDER,hParentNode,hAfter);
		if(hNode){
			//nodeHandleList.AddTail(hNode);   //update nodeHandleList
			AddHandle(hNode);
			AddParentID(hParentNode);		//update parentIDlist
			treeCtrl->SetItemData(hNode,(unsigned long)this);	// set pointer to the node
			// expand after each insert
			if(ExpandWhenInsert)
				treeCtrl->Expand(hParentNode,TVE_EXPAND);
			return hNode;
		}
	}else
		MessageBox(NULL,_T("treeCtrl is NULL in this node"),Name,MB_OK);
	return NULL;
}

BOOL CRecord::IsChildOf(CRecord *p)
{
	int testParentID=p->ID;
	int pid;
	if(AnyParentID()){	
		while(pos!=NULL){
			pid=GetNextParentID();
			if(pid==testParentID) return TRUE;
		}
	}
	return FALSE;
}
