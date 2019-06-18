// InfoMgrDoc.cpp : implementation of the CInfoMgrDoc class
//

#include "stdafx.h"
#include "InfoMgr.h"

#include "InfoMgrDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfoMgrDoc

IMPLEMENT_DYNCREATE(CInfoMgrDoc, CDocument)

BEGIN_MESSAGE_MAP(CInfoMgrDoc, CDocument)
	//{{AFX_MSG_MAP(CInfoMgrDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	//ON_COMMAND(ID_POP,PopulateTreeView)	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoMgrDoc construction/destruction

CInfoMgrDoc::CInfoMgrDoc()
{
	// TODO: add one-time construction code here
	//SaveProcessID=0;
	head=tail=NULL;
	treeCtrl=NULL;
}

CInfoMgrDoc::~CInfoMgrDoc()
{
}

BOOL CInfoMgrDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	TRACE(_T("in CInfoMgrDoc::OnNewDocument , Filename is %s....\n"),GetPathName());
	//MessageBox(NULL,"in CInfoMgrDoc::OnNewDocument","dEbug",MB_OK);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CInfoMgrDoc serialization

void CInfoMgrDoc::Serialize(CArchive& ar)
{	//CFile::modeCreate|CFile::modeReadWrite|CFile::typeText);
	//::MessageBox(NULL,"In Serialize","CInfoMgrDoc::Serialize",MB_OK);	
	if (ar.IsStoring())
	{
		//SaveToFile(ar);	// faster
		SaveToFileWithOrder(ar);	//save order
	}
	else
	{
		// TODO: add loading code here
		//MessageBox(NULL,"Loading", "Load",MB_OK);
		CDetailFile DetailFile(ar.GetFile()->GetFilePath(),CFile::modeRead/*|CFile::typeText*/);
		DetailFile.LoadDetails();
		CString line;
		int IDCounter=0;
		if(ar.ReadString(line)){
			IDCounter=ParseForIDCounter(line);
			if(IDCounter<=0){				
				return;
			}
		}else
			return;
		CRecord::idCounter=IDCounter;

		POSITION pos = GetFirstViewPosition();
		CTreeView* pFirstView = (CTreeView*)GetNextView( pos );
		treeCtrl=&pFirstView->GetTreeCtrl();
	
		while(ar.ReadString(line)){
			LoadRecord(line,&DetailFile);
		}
		//MessageBox(NULL,"Loaded", "Load",MB_OK);	
		PopulateTreeView();
		//TRACE("Read str1=%s, str2=%s, str0=%s \n",str[1],str[2],str[0]);		
	}
	//CObject::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CInfoMgrDoc diagnostics

#ifdef _DEBUG
void CInfoMgrDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CInfoMgrDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInfoMgrDoc commands

BOOL CInfoMgrDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	CInfoMgrApp * thisapp=(CInfoMgrApp *)AfxGetApp();
	thisapp->bTitleUpdated=FALSE;
	TRACE(_T("File to be saved: %s\n"),lpszPathName);
	return CDocument::OnSaveDocument(lpszPathName);	
}



void CInfoMgrDoc::AddToList(CRecord *recordObj)
{
	if(head==NULL){
		head=recordObj;
		tail=head;		
	}else{
		tail->Next=recordObj;
		recordObj->Prev=tail;
		tail=recordObj;
	}
}

void CInfoMgrDoc::SaveDetail(CRecord *ptr)
{

}

int CInfoMgrDoc::ParseForIDCounter(CString line)
{
	int len=line.GetLength();
	if(len<12)
		return 0;
	int pos=line.Find(_T("<RecordID="));
	//int pos=line.Find((wchar_t *)"<RecordID=");
	if(pos==-1){
		MessageBox(NULL,line,_T("Parse error in this line for IDcounter"),MB_OK);
		return 0;
	}
	int pos1=line.Find(_T(">"));
	//int pos1=line.Find((wchar_t *)(">"));
	if(pos1<10)
		return 0;
	CString strID=line.Mid(pos+10,pos1-10-pos);
	//MessageBox.Show(strID,"strID");
	int ret=_ttoi(strID);
	return ret;
}

void CInfoMgrDoc::LoadRecord(CString line,CDetailFile * details)
{
	CRecord * recordObj=new CRecord(line);	
	recordObj->treeCtrl=treeCtrl;
	if(recordObj->hasDetail){
		if(recordObj->ID==1558){
			int x=0;
			x++;
		}
		recordObj->Detail=details->getDetail(recordObj->ID);
	}
	AddToList(recordObj);			
}
void CInfoMgrDoc::PopulateTreeView(){		
	pSearchPtr=pNextPtr=head;
	CRecord * savePtr;
	while((pSearchPtr=FindNextWithParentID(0))!=NULL){
		//CYaliTreeNode *node=new CYaliTreeNode(treeCtrl,pSearchPtr);	
		HTREEITEM hnode=pSearchPtr->insert(NULL);		
		savePtr=pNextPtr;
		addChildren(hnode);		// add all children of the node	
		pNextPtr=savePtr;
	}
}

CRecord * CInfoMgrDoc::FindNextWithParentID(int parentID)
{
	pSearchPtr=pNextPtr;
	while(pSearchPtr!=NULL){
		POSITION pos = pSearchPtr->parentIDlist.GetHeadPosition();
		for (int i=0;i < pSearchPtr->parentIDlist.GetCount();i++){
			int myPID=pSearchPtr->parentIDlist.GetNext(pos);
			if(myPID==parentID){
				pNextPtr=pSearchPtr->Next;
				return pSearchPtr;
			}
		}		
		pSearchPtr=pSearchPtr->Next;
	}
	return NULL;
}
void CInfoMgrDoc::addChildren(HTREEITEM hparent)
{
	if(treeCtrl==NULL){
		POSITION pos = GetFirstViewPosition();
		if(pos==NULL){
			MessageBox(NULL,_T("treeCtrl is NULL"),_T("CInfoMgrDoc::addChildren"),MB_OK);
			return;
		}
		CTreeView* pFirstView = (CTreeView*)GetNextView( pos );
		treeCtrl=&pFirstView->GetTreeCtrl();
		if(treeCtrl==NULL){
			MessageBox(NULL,_T("treeCtrl is NULL"),_T("CInfoMgrDoc::addChildren"),MB_OK);
			return;
		}		
	}

	CRecord * parentNode=(CRecord *)treeCtrl->GetItemData(hparent);
	int parentID=parentNode->ID;
	pSearchPtr=pNextPtr=head;
	CRecord * savePtr;
	while((pSearchPtr=FindNextWithParentID(parentID))!=NULL){		
		HTREEITEM hnode=pSearchPtr->insert(hparent);		
		savePtr=pNextPtr;
		addChildren(hnode);		// add all children of the node	
		pNextPtr=savePtr;
	}

}
void CInfoMgrDoc::DeleteContents( ){
	//MessageBox(NULL,"DeleteContents","CInfoMgrDoc::DeleteContents",MB_OK);
	if(treeCtrl)
		if(::IsWindow(treeCtrl->m_hWnd))
			treeCtrl->DeleteAllItems();

	CRecord * p=head;
	CRecord * p1;
	if(treeCtrl==NULL){		
		if(head!=NULL)
			treeCtrl=p->treeCtrl;		
	}
	while(p!=NULL){
		//deleteAllNodes(p);
		p1=p->Next;		
		delete p;
		p=p1;
	}
	head=tail=NULL;
	//CView * pSenter=(CView *)0xffffffff;
	CView * pSenter=NULL;//(CView *)0xffffffff;
	this->UpdateAllViews(pSenter);
}

void CInfoMgrDoc::SaveToFile(CArchive &ar)
{
	CDetailFile DetailFile(ar.GetFile()->GetFilePath(),CFile::modeCreate|CFile::modeWrite);
	CString line;
	line.Format(_T("<RecordID=%d>"),CRecord::idCounter);
	ar.WriteString(line+"\r\n");
	// loop through CRecord list from head to tail
	line="";
	CRecord * ptr=head;
	char buf[100];
	while(ptr!=NULL){
		line=itoa(ptr->ID,buf,10)+(CString)"^";	//ID^
		
		line += "<ParentID>";
		POSITION pos = ptr->parentIDlist.GetHeadPosition();
		for (int i=0;i < ptr->parentIDlist.GetCount();i++){
			int parentID=(int) ptr->parentIDlist.GetNext(pos);
			if(i==0)
				line += itoa(parentID,buf,10);
			else
				line += (CString)"-"+itoa(parentID,buf,10);
		}
		line += "</ParentID>";
		line +="^";
		line +=ptr->Name;
		line +="^";
		line +=ptr->Description;
		line +="^";
		if(ptr->hasDetail){
			line+="hasdetail";
			DetailFile.WriteString(ptr->ID,ptr->Detail);
		}else
			line+="nodetail";
		ar.WriteString(line+"\r\n");
		SaveDetail(ptr);
		ptr=ptr->Next;
	}		

	//ar.WriteString(str[1]+"\r\n");
	//ar.WriteString(str[2]+"\r\n");		
	CString tmp;
	tmp.Format(_T("Saved to %s"),ar.GetFile()->GetFilePath());
	//MessageBox(NULL,tmp,_T("Save"),MB_OK);
	msgbox(this,1,tmp,_T("Saving..."));
}

void CInfoMgrDoc::SaveToFileWithOrder(CArchive &ar)
{
	saveCounter++;
	m_ar=&ar;
	//CDetailFile DetailFile(ar.GetFile()->GetFilePath(),CFile::modeCreate|CFile::modeWrite);
	DetailFile=new CDetailFile(ar.GetFile()->GetFilePath(),CFile::modeCreate|CFile::modeWrite);
	CString line;
	line.Format(_T("<RecordID=%d>"),CRecord::idCounter);
	ar.WriteString(line+"\r\n");
	//------------start from root item-----------------
	HTREEITEM hItem=treeCtrl->GetRootItem();
	if(hItem==NULL) return;	// nothing to save
	while (hItem != NULL){
		SaveTheFamily(hItem);	//save it and its children
		hItem = treeCtrl->GetNextSiblingItem(hItem);
	}
	delete DetailFile;
	CString tmp;
	tmp.Format(_T("Saved to %s"),ar.GetFile()->GetFilePath());
	//MessageBox(NULL,tmp,_T("Save"),MB_OK);
	msgbox(this,1,tmp,_T("Saving..."));
}

void CInfoMgrDoc::SaveTheFamily(HTREEITEM hItem)
{
	SaveTheItem(hItem);
	if (treeCtrl->ItemHasChildren(hItem)){
		HTREEITEM hChildItem = treeCtrl->GetChildItem(hItem);
		while (hChildItem != NULL){
			SaveTheFamily(hChildItem);
			hChildItem = treeCtrl->GetNextSiblingItem(hChildItem);
		}
	}
}

void CInfoMgrDoc::SaveTheItem(HTREEITEM hItem)
{
	CRecord * pItem=(CRecord *)treeCtrl->GetItemData(hItem);
	if(pItem->saveID==saveCounter)
		return;
	SaveTheRecord(pItem);
	pItem->saveID=saveCounter;		// need to set here to avoid multiple save of the obj
}

void CInfoMgrDoc::SaveTheRecord(CRecord *ptr)
{
	CString line="";
	char buf[100];
	//ID
	line=itoa(ptr->ID,buf,10)+(CString)"^";	
	//ParentID	
	line += "<ParentID>";
	POSITION pos = ptr->parentIDlist.GetHeadPosition();
	for (int i=0;i < ptr->parentIDlist.GetCount();i++){
		int parentID=(int) ptr->parentIDlist.GetNext(pos);
		if(i==0)
			line += itoa(parentID,buf,10);
		else
			line += (CString)"-"+itoa(parentID,buf,10);
	}
	line += "</ParentID>";
	line +="^";
	// Name
	line +=ptr->Name;
	line +="^";
	// description
	line +=ptr->Description;
	line +="^";
	// detail
	if(ptr->hasDetail){
		line+="hasdetail";
		DetailFile->WriteString(ptr->ID,ptr->Detail);
	}else
		line+="nodetail";
	m_ar->WriteString(line+"\r\n");
	SaveDetail(ptr);			
}
