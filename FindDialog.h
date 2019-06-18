#if !defined(AFX_FINDDIALOG_H__7C2D39B2_02EC_4F49_BE16_49AA443A27A8__INCLUDED_)
#define AFX_FINDDIALOG_H__7C2D39B2_02EC_4F49_BE16_49AA443A27A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFindDialog dialog

class CFindDialog : public CDialog
{
// Construction
public:
	CLeftView * pLeftView;
	void MarkTheItem(HTREEITEM hItem);
	void SearchTheBranch(HTREEITEM hItem);
	BOOL IsTheRecord(CRecord * p);
	BOOL IsTheItem(HTREEITEM hItem);
	BOOL ShowFound(CRecord * p);
	CInfoMgrDoc * pDocument;
	void ShowAllInstances(CRecord * p);
	CRecord * head;
	CTreeCtrl * treeCtrl;
	CFindDialog(CLeftView * pV,CInfoMgrDoc * pDoc);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFindDialog)
	enum { IDD = IDD_FIND_DIALOG };
	BOOL	m_CaseSensitive;
	BOOL	m_SearchDescription;
	BOOL	m_SearchDetail;
	BOOL	m_SearchName;
	CString	m_SearchString;
	int		m_SearchScope;
	int		m_SearchForHowmany;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFindDialog)
	afx_msg void OnOKsearch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDDIALOG_H__7C2D39B2_02EC_4F49_BE16_49AA443A27A8__INCLUDED_)
