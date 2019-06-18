// DetailObj.h: interface for the CDetailObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DETAILOBJ_H__90535399_7065_4206_B6CB_21F2A2BAB72C__INCLUDED_)
#define AFX_DETAILOBJ_H__90535399_7065_4206_B6CB_21F2A2BAB72C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDetailObj  
{
public:
	CDetailObj * Prev;
	CDetailObj * Next;
	int ID;
	CString Detail;
	CDetailObj(int detailID);
	virtual ~CDetailObj();
};

#endif // !defined(AFX_DETAILOBJ_H__90535399_7065_4206_B6CB_21F2A2BAB72C__INCLUDED_)
