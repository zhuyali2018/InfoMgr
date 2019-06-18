// LeftView.h : interface of the CLeftView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEFTVIEW_H__B35C4464_777E_4070_949E_0DB150FF9839__INCLUDED_)
#define AFX_LEFTVIEW_H__B35C4464_777E_4070_949E_0DB150FF9839__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxole.h>	// implement drop target
#include "UndoItem.h"

class CInfoMgrDoc;

class CLeftView : public CTreeView
{
protected: // create from serialization only
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Attributes
public:
	// drag/drop stuff	
	COleDropTarget m_dropTarget;
	COleDataSource m_dragSource;
	DROPEFFECT m_prevDropEffect;
	void InsertNode(_TCHAR *link);
	void DeleteChildren(HTREEITEM hRoot,int parentCount);
	HTREEITEM TreeNodeHandleOnClipboard;
	CInfoMgrDoc* GetDocument();
	void OnInsert();
	void OnDelete();
	void OnOpen();
	void OnCopy();
	void OnPaste();
	void OnMove();
	int  bMove;
	CImageList m_imglDrives;
	CList <HTREEITEM,HTREEITEM> IconSetList;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:		
	BOOL m_FileDrop;
	void InsertaSibling();
	void Redo(CUndoItem *pItem);
	void DeleteFrom(CUndoItem * pHead);
	BOOL doingMoveUpDown;
	HTREEITEM BigInsertAfter(CRecord * target, CRecord *source,HTREEITEM hAfter);
	void DoLink(HTREEITEM hDrag,HTREEITEM hDrop);
	void RecordAction(HTREEITEM hSrcParent, CRecord *pSrcRecord, int action);
	void RecordAction(CRecord * pSrcRecord, CRecord * pDestRecord, int action);
	void RecordAction(HTREEITEM src, HTREEITEM dest,int action,CRecord * pSrcRecord=NULL, CRecord * pDestRecord=NULL);
	void UndoAction(CUndoItem * item);
	void AddToUnDoList(CUndoItem * item);
	
	CUndoItem * tail;
	CUndoItem * head;
	CString getItemName(HTREEITEM hItem);
	HTREEITEM DoCopy(HTREEITEM src,HTREEITEM dest);
	void DoMove(HTREEITEM src,HTREEITEM dest);
	HTREEITEM hDragSrc;
	void ShowAllInsstances(HTREEITEM);
	void ShowInstances(HTREEITEM hItem,BOOL bShowFirstOnly);
	void ShowInstances(CRecord * p,BOOL bShowFirstOnly);
	void OnClearIcons();
	void OnShowAll();
	void RestoreClipboardItemStates();
	void UpdateAllItemInstances(CRecord *p);
	void OnEditItem();
	HTREEITEM BigInsert(CRecord * target,CRecord * source);
	int getParentID(HTREEITEM me);
	void DeleteTree(HTREEITEM hRootNode);
	int OnCreate(LPCREATESTRUCT lpcs);
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void OnContextMenu(CWnd*, CPoint);	

// Generated message map functions
protected:
	//{{AFX_MSG(CLeftView)
	afx_msg void OnSelectionChanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRightClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSearch();
	afx_msg void OnSort();
	afx_msg void OnListinst();
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnUndo();
	afx_msg void OnMovePosition();
	afx_msg void OnMoveup();
	afx_msg void OnMovedown();
	afx_msg void OnRedo();
	afx_msg void OnEDITCollapse();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CInfoMgrDoc* CLeftView::GetDocument()
   { return (CInfoMgrDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTVIEW_H__B35C4464_777E_4070_949E_0DB150FF9839__INCLUDED_)
