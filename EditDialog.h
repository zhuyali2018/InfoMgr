//{{AFX_INCLUDES()

//}}AFX_INCLUDES
#if !defined(AFX_EDITDIALOG_H__95B4B8E0_C882_4BD8_81B9_9B51609506A0__INCLUDED_)
#define AFX_EDITDIALOG_H__95B4B8E0_C882_4BD8_81B9_9B51609506A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditDialog.h : header file
//
#include "richtext.h"
#include "LeftView.h"
/////////////////////////////////////////////////////////////////////////////
// CEditDialog dialog

class CEditDialog : public CDialog
{
// Construction
public:
	BOOL m_bReadOnly;
	void InsertNode(_TCHAR * link);
	HICON m_hIcon;
	BOOL bDisplaying;
	CRecord * pRecord;
	CLeftView * pView;
	CEditDialog(CWnd* pParent,CRecord *p);   // standard constructor	
	void OnDropFiles(HDROP hDropInfo);
// Dialog Data
	//{{AFX_DATA(CEditDialog)
	enum { IDD = IDD_EDIT_DIALOG };
	CButton	m_CtrlRichTextChk;
	CEdit	m_CtrlDetail0;
	CEdit	m_CtrlDesp;
	CRichText m_CtrlDetail;
	CEdit	m_CtrlName;//
	CButton	m_bnOK;
	CButton	m_bnCancel;
	CString	m_Description;
	CString	m_Name;
	CString	m_Detail;
	CString	m_Detail0;
	BOOL	m_bRichText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditDialog)
	virtual void OnOK();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnCHECKRichTextt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITDIALOG_H__95B4B8E0_C882_4BD8_81B9_9B51609506A0__INCLUDED_)
