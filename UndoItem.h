// UndoItem.h: interface for the UndoItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNDOITEM_H__B916E803_87FB_485C_B284_68BD32099703__INCLUDED_)
#define AFX_UNDOITEM_H__B916E803_87FB_485C_B284_68BD32099703__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUndoItem  
{
public:
	int Action;

	HTREEITEM hDestitem;
	HTREEITEM hSrcParentitem;

	CRecord * pDestRecord;
	CRecord * pSrcRecord;
	
	CUndoItem * Prev;
	CUndoItem * Next;
	
	CUndoItem();
	virtual ~CUndoItem();

};

#endif // !defined(AFX_UNDOITEM_H__B916E803_87FB_485C_B284_68BD32099703__INCLUDED_)
