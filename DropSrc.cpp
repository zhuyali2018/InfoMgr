// DropSrc.cpp: implementation of the CDropSrc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "InfoMgr.h"
#include "DropSrc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDropSrc::CDropSrc()
{

}

CDropSrc::~CDropSrc()
{

}
BOOL CDropSrc::OnBeginDrag( CWnd* pWnd ){
	//MessageBox(NULL,"OnBeginDrag","debug",MB_OK);
	TRACE(_T("CDropSrc::OnBegindrag\n"));
	return TRUE;
}

