#include "stdafx.h"
void msgbox(CDocument * doc,float sec,CString msg,CString title) 
{
	POSITION pos = doc->GetFirstViewPosition();
	if(pos != NULL){
		CView* pView = doc->GetNextView(pos);

		CTMsgbox * msgbox=new CTMsgbox(pView->GetParentFrame(),sec,msg,title);
		if(!msgbox->bInterrupted)
			delete msgbox;
	}
}
void msgbox(CWnd * pView,float sec,CString msg,CString title) 
{
	if(pView==NULL) return;
	CTMsgbox * msgbox=new CTMsgbox(pView->GetParentFrame(),sec,msg,title);
	if(!msgbox->bInterrupted)
		delete msgbox;	
}