// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__E87D1739_E7DA_461F_96D1_611B57C76124__INCLUDED_)
#define AFX_MAINFRM_H__E87D1739_E7DA_461F_96D1_611B57C76124__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CInfoMgrView;

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
protected:
	//CSplitterWnd m_wndSplitter;	
public:
	CSplitterWnd m_wndSplitter;	
	CSplitterWnd m_wndSplitter2;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_bReadOnly;
	BOOL m_InsertOnOneFileDrop;
	BOOL PlayMode;
	virtual ~CMainFrame();
	CInfoMgrView* GetRightPane();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CReBar      m_wndReBar;
	CDialogBar  m_wndDlgBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPlaymode();
	afx_msg void OnUpdatePlaymode(CCmdUI* pCmdUI);
	afx_msg void OnInsertonly();
	afx_msg void OnUpdateInsertonly(CCmdUI* pCmdUI);
	afx_msg void OnEDITReadOnly();
	afx_msg void OnUpdateEDITReadOnly(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditInsert(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditItem(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPosition(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSort(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMovedown(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMoveup(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnUpdateViewStyles(CCmdUI* pCmdUI);
	afx_msg void OnViewStyle(UINT nCommandID);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__E87D1739_E7DA_461F_96D1_611B57C76124__INCLUDED_)
