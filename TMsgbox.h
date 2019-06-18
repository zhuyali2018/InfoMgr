// TMsgbox.h: interface for the CTMsgbox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TMSGBOX_H__33D2235E_5EAD_4BD2_88FE_84E2A4FE4423__INCLUDED_)
#define AFX_TMSGBOX_H__33D2235E_5EAD_4BD2_88FE_84E2A4FE4423__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTMsgbox : public CFrameWnd//CWnd  
{
public:
	BOOL bInterrupted;
	CString m_title;	
	CString m_message;
	CTMsgbox(CWnd * pParent,float ms,CString msg,CString title);
	CTMsgbox();
	virtual ~CTMsgbox();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_TMSGBOX_H__33D2235E_5EAD_4BD2_88FE_84E2A4FE4423__INCLUDED_)
