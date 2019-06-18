// Record.h: interface for the CRecord class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECORD_H__28BB8FEC_2D77_48D6_9739_594C3DE055DF__INCLUDED_)
#define AFX_RECORD_H__28BB8FEC_2D77_48D6_9739_594C3DE055DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

class CRecord 
{
public:	
	BOOL IsChildOf(CRecord *p);
	HTREEITEM insertAfter(HTREEITEM hParentNode,HTREEITEM hAfter);
	void AddHandle(HTREEITEM hItem);
	BOOL ExpandWhenInsert;
	BOOL IsVerticalOffspringOf(CDocument * pDoc,CRecord *p);
	int RemoveFromParentIDList(int parentID);
	int RemoveFromParentIDList(HTREEITEM hNode);
	int RemoveFromHandleList(HTREEITEM hItem);
	HTREEITEM insert(HTREEITEM hParentNode);
	int GetNextParentID();
	BOOL AnyParentID();
	POSITION pos;
	HTREEITEM GetNextNodeHandle();
	BOOL AnyNodeHandle();
	CRecord * Prev;
	CRecord * Next;
	CTreeCtrl * treeCtrl;
	void AddParentID(HTREEITEM hParentNode);
	void AddParentID(int parentID);
	static int idCounter;
	int getNextRecordID();
	CString Name;
	CString Description;
	CString Detail;
	BOOL	hasDetail;
	int		ID;				//recordID
	int saveID;				//to mark if the obj has been saved before in the same saving process
	//--
	CList <int,int> parentIDlist;	// parent node ID list
	CList <HTREEITEM,HTREEITEM> nodeHandleList;		// instance node ID list

	CRecord();
	CRecord(CString line);
	CRecord(CTreeCtrl * tc);
	virtual ~CRecord();
private:
	void initializer();
};

#endif // !defined(AFX_RECORD_H__28BB8FEC_2D77_48D6_9739_594C3DE055DF__INCLUDED_)
