// InfoMgr.h : main header file for the INFOMGR application
//

#if !defined(AFX_INFOMGR_H__44D6F438_2838_4A77_9F98_59A7F0430C2E__INCLUDED_)
#define AFX_INFOMGR_H__44D6F438_2838_4A77_9F98_59A7F0430C2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CInfoMgrApp:
// See InfoMgr.cpp for the implementation of this class
//

class CInfoMgrApp : public CWinApp
{
public:
	BOOL bTitleUpdated;
	afx_msg void OnFileNew();
	void OnFileOpenDef();
	CInfoMgrApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfoMgrApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CInfoMgrApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFOMGR_H__44D6F438_2838_4A77_9F98_59A7F0430C2E__INCLUDED_)
