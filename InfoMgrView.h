// InfoMgrView.h : interface of the CInfoMgrView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFOMGRVIEW_H__85B58D93_3598_4A8A_9B36_8563F36B549F__INCLUDED_)
#define AFX_INFOMGRVIEW_H__85B58D93_3598_4A8A_9B36_8563F36B549F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CInfoMgrView : public CListView
{
protected: // create from serialization only
	CInfoMgrView();
	DECLARE_DYNCREATE(CInfoMgrView)

// Attributes
public:
	CInfoMgrDoc* GetDocument();
	void OnClick(NMHDR* pNMHDR, LRESULT* pResult) ;
	void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) ;	
	int OnCreate(LPCREATESTRUCT lpcs);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfoMgrView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	CString getItemName(HTREEITEM hItem);
	CString getItemPath(HTREEITEM hItem);
	void AddToList(int counter,HTREEITEM hItem);
	void DisplayInstanceColumnName();
	void DisplayInstances(CRecord * pR);
	CTreeCtrl * treeCtrl;
	void DisplayDefaultColumnName();
	void UpdateListRecord(int nItem, CRecord * p);
	virtual ~CInfoMgrView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CInfoMgrView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in InfoMgrView.cpp
inline CInfoMgrDoc* CInfoMgrView::GetDocument()
   { return (CInfoMgrDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFOMGRVIEW_H__85B58D93_3598_4A8A_9B36_8563F36B549F__INCLUDED_)
