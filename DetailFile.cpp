// DetailFile.cpp: implementation of the CDetailFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DetailFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDetailFile::CDetailFile(CString filename,UINT fmode)
{
	CString DetailFileName=filename;
	//ar.GetFile()->GetFilePath();
	int len=DetailFileName.GetLength();
	if(len>0){
		DetailFileName.SetAt(len-1,'x');		
		fileOK=f.Open(DetailFileName,fmode);//CFile::modeCreate|CFile::modeReadWrite);
		if(!fileOK){
			MessageBox(NULL,DetailFileName,_T("Unable to open the File"),MB_OK);
		}
	}else		
		MessageBox(NULL,DetailFileName,_T("Bad File Name"),MB_OK);

	p=pbuf;
	linecounter=0;
}

CDetailFile::~CDetailFile()
{
	if (!f.m_pStream)return;  //if never opened, do not close
		f.Close();
}

void CDetailFile::WriteString(int ID, CString line)
{
	line=line.Trim();  //this is the line that will remove all the carrage return on both ends of the string
	CString head;
	head.Format(_T("<DetailID=%d>\r\n"),ID);	
#ifdef _UNICODE
	TCHAR  * pbuf=(TCHAR *)(LPCWSTR)head;
#else
	TCHAR  * pbuf=(TCHAR *)(LPCSTR)head;
#endif
	int len=_tcslen(pbuf);	
	f.Write( pbuf,len*sizeof(TCHAR));
#ifdef _UNICODE
	pbuf=(TCHAR *)(LPCWSTR)line;
#else
	pbuf=(TCHAR *)(LPCSTR)line;
#endif

	len=_tcslen(pbuf);
	f.Write( pbuf,len*sizeof(TCHAR));

	CString tail=_T("\r\n</Detail>\r\n");	
#ifdef _UNICODE
	pbuf=(TCHAR *)(LPCWSTR)tail;
#else
	pbuf=(TCHAR *)(LPCSTR)tail;
#endif
	len=_tcslen(pbuf);
	f.Write(pbuf,len*sizeof(TCHAR));

	// org code for WriteString
/*
	f.WriteString(head);
	f.WriteString(line+_T("\n"));
	f.WriteString(_T"</Detail>\n"));
*/
}

void CDetailFile::LoadDetails()
{
	CString line;
	BOOL inDetail=FALSE;
	detailRoot=NULL;
	while(ReadString(line)){
		//if(line=="") break;
		line=line.Trim(_T(" \r\n"));
		int pos;
		if(((pos=line.Find(_T("<DetailID=")))>=0)&&(line.GetLength()>=12)&&(!inDetail)){
			int ID=_ttoi(line.Mid(10+pos,line.GetLength()-11));
			if(detailRoot==NULL){
				detailRoot=new CDetailObj(ID);					
				detailTail=detailRoot;
			}else{
				detailTail->Next=new CDetailObj(ID);
				detailTail->Next->Prev=detailTail;
				detailTail=(CDetailObj *)detailTail->Next;
			}
			inDetail=true;
		}else if((line.Find(_T("</Detail>"))>=0)&&inDetail){
			inDetail=false;
		}else if(inDetail){
			if(line.GetLength()>0)
				detailTail->Detail+=line+_T("\r\n");
		}else{
		
		}
		//	break;	// very important, might be in deadloop if missing
	}
}

CString CDetailFile::getDetail(int ID)
{
	CDetailObj * p=detailRoot;
	while(p!=NULL){
		if(p->ID==ID)
			return p->Detail;
		p=p->Next;
	}
	return "";
}

BOOL CDetailFile::ReadString(CString& line)
{
	if (!f.m_pStream) return FALSE;  //if file not open successfully, return
	linecounter++;
	line="";
	if(((p-pbuf)>=100)||(linecounter==1)){
		ZeroMemory(pbuf,100*sizeof(TCHAR));
		nBytesRead = f.Read( pbuf, 100*sizeof(TCHAR));
		p=pbuf;
	}
	while(nBytesRead==100*sizeof(TCHAR)){
		while((*p!=_T('\n'))&&(*p!=0)&&(nBytesRead==100*sizeof(TCHAR))){			
			line+=*p;
			p++;
			if((p-pbuf)>=100){
				ZeroMemory(pbuf,100*sizeof(TCHAR));
				nBytesRead = f.Read( pbuf, 100*sizeof(TCHAR) );
				p=pbuf;
			}
		}
		if(*p==_T('\n')){
			line+=*p;
			p++;
			if(*p==_T('\r')){
				line+=*p;
				p++;
				return TRUE;
			}
			return TRUE;
		}else if(*p==0){
			return FALSE;
		}
	}
	if((nBytesRead>0)&&(nBytesRead<100*sizeof(TCHAR))){				
		while(*p!=0){
			line+=*p;
			p++;
			if((p-pbuf)>=100){
				return FALSE;
			}else if(*p==0)
				return FALSE;
			else if(*p==_T('\r')){
				line+=*p;
				p++;
				if(*p==_T('\n')){
					line+=*p;
					p++;
					return TRUE;
				}
				return TRUE;
			}
		}
	}
	return FALSE;
}
