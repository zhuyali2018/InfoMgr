//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES
#if !defined(AFX_CONTENTVIEW_H__FC8F2F12_32EB_4ED1_A9B2_9264E682A49C__INCLUDED_)
#define AFX_CONTENTVIEW_H__FC8F2F12_32EB_4ED1_A9B2_9264E682A49C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ContentView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CContentView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CContentView : public CFormView
{
protected:

	CContentView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CContentView)

// Form Data
public:
	//{{AFX_DATA(CContentView)
	enum { IDD = IDD_FORMVIEW };
	CEdit	m_CtrlName;
	CEdit	m_CtrlDetail;
	CEdit	m_CtrlDesp;
	CString	m_Name;
	CString	m_Details;
	CString	m_Description;
	CWebBrowser2	m_browser;
	//}}AFX_DATA

// Attributes
public:
	BOOL display121;
// Operations
public:
	BOOL m_DoNotDisplayBrowser;
	BOOL m_Resizing;
	BOOL IsMovieFile(CString filepath);
	void DisplayImage(CString m_Description);
	CString getCurrentPath();
	BOOL IsJPGFile(CString filepath);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContentView)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);	
	//}}AFX_VIRTUAL
	
// Implementation
protected:
	virtual ~CContentView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CContentView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);	
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTENTVIEW_H__FC8F2F12_32EB_4ED1_A9B2_9264E682A49C__INCLUDED_)
