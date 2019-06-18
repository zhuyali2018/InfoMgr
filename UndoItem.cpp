// UndoItem.cpp: implementation of the UndoItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "InfoMgr.h"
#include "UndoItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUndoItem::CUndoItem()
{
	Next=NULL;
	Prev=NULL;
}

CUndoItem::~CUndoItem()
{

}
