// DropSrc.h: interface for the CDropSrc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DROPSRC_H__52846C22_26F5_4B82_8E14_B79023A42639__INCLUDED_)
#define AFX_DROPSRC_H__52846C22_26F5_4B82_8E14_B79023A42639__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxole.h>
class CDropSrc : public COleDropSource  
{
public:
	virtual BOOL OnBeginDrag( CWnd* pWnd );
/*
	virtual SCODE GiveFeedback( DROPEFFECT dropEffect ){
		TRACE(_T("In Give Feed Back with effect = %d\n"),dropEffect);
		return NULL;
	};
	virtual SCODE QueryContinueDrag( BOOL bEscapePressed, DWORD dwKeyState ){
			TRACE(_T("In QueryContinueDrag with bEscapePressed = %d and dwKeyState=%d\n"),bEscapePressed,dwKeyState);	
			return NULL;
	};
*/
	CDropSrc();
	virtual ~CDropSrc();

};

#endif // !defined(AFX_DROPSRC_H__52846C22_26F5_4B82_8E14_B79023A42639__INCLUDED_)
