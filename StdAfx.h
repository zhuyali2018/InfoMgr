// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__C72CEE9D_ECC0_4B81_918A_6EDA480572A9__INCLUDED_)
#define AFX_STDAFX_H__C72CEE9D_ECC0_4B81_918A_6EDA480572A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#define WINVER 0x0502

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxcview.h>
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#include "resource.h"       // main symbols
#include "DetailObj.h"
#include "DetailFile.h"
#include "InfoMgrDoc.h"
#include "Record.h"
#include "EditDialog.h"
#include "FindDialog.h"
#include "UndoItem.h"
#include "MainFrm.h"
#include "TMsgbox.h"
#include "ConstantDefs.h"
#include "ContentView.h"


void msgbox(CDocument * pParentWnd,float sec,CString msg,CString title);
void msgbox(CWnd * pView,float sec,CString msg,CString title);
#endif // !defined(AFX_STDAFX_H__C72CEE9D_ECC0_4B81_918A_6EDA480572A9__INCLUDED_)

