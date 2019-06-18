// DetailFile.h: interface for the CDetailFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DETAILFILE_H__F550C213_4F10_44AA_AB9B_23BE5E913277__INCLUDED_)
#define AFX_DETAILFILE_H__F550C213_4F10_44AA_AB9B_23BE5E913277__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DetailObj.h"
class CDetailFile  
{
public:
	int linecounter;
	TCHAR * p;
	TCHAR pbuf[100];
	UINT nBytesRead;
	BOOL ReadString(CString& line);
	CString getDetail(int ID);
	CDetailObj * detailTail;
	CDetailObj * detailRoot;
	void LoadDetails();
	void WriteString(int ID,CString line);
	BOOL fileOK;
	CStdioFile	f;		// uncomment for 4.02
	//CFile f;
	CDetailFile(CString filename,UINT fmode);
	virtual ~CDetailFile();

};

#endif // !defined(AFX_DETAILFILE_H__F550C213_4F10_44AA_AB9B_23BE5E913277__INCLUDED_)
