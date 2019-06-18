// TMsgbox.cpp: implementation of the CTMsgbox class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TMsgbox.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
/////////////////////////////////////////////////////////////////////////////
// CTMsgBox

BEGIN_MESSAGE_MAP(CTMsgbox, CWnd)
	//{{AFX_MSG_MAP(CTimeMsgBoxApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	//ON_COMMAND(ID_HELP, CWinApp::OnHelp)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	//ON_BN_CLICKED(1962,OnButtonClicked)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTMsgbox::CTMsgbox()
{

}

CTMsgbox::~CTMsgbox()
{

}

CTMsgbox::CTMsgbox(CWnd * pParent,float sec, CString msg, CString title)
{
	//this->SetWindowText(title);
	m_title=title;
	m_message=msg;
	bInterrupted=FALSE;
	//----------------------------------------	
	

	CRect rect;
	pParent->GetWindowRect(&rect);

	int width=(msg.GetLength()+10)*8; //300;
	int height=40;
	int x=rect.left+(rect.right -rect.left-width )/2;
	int y=rect.top  +(rect.bottom-rect.top -height)/2;
	Create(NULL,m_title,WS_OVERLAPPED|WS_SYSMENU,CRect(x,y,x+width,y+height),pParent,NULL,WS_EX_TOPMOST );
	ShowWindow(SW_SHOW);	
	SetIcon(pParent->GetIcon(FALSE),FALSE);
	for(int i=0;i<sec*100;i++){
		//msgbox->UpdateWindow();		
		MSG Message;
		while(PeekMessage(&Message,NULL, 0, 0,PM_REMOVE)){
			TranslateMessage(&Message);
			DispatchMessage(&Message);			
		}	
		Sleep(10);
		if(bInterrupted)
			break;
	}	
	
}
void CTMsgbox::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		//dc.DrawIcon(x, y, m_hIcon);
		
	}
	else
	{
		TRACE(_T("OnDraw 2\n"));		
		//------------------------------
		//int pos1=m_message.Find("^");
		CString title=m_message;
		//CString title1=m_message;
		//if(pos1>0){
		//	title=m_message.Mid(0,pos1);
		//	title1=m_message.Mid(pos1+1);
		//}
		
		
		CFont font;		
		font.CreateFont(
			12,                        // nHeight
			8,                         // nWidth
			0,                         // nEscapement
			0,                         // nOrientation	===> no effect
			FW_NORMAL,                   // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			ANSI_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			_T("Fixedsys")				   // lpszFacename
		);                 


		CPaintDC dc(this); // device context for painting
		dc.SelectObject(&font);
		
		CRect rect;
		GetClientRect(&rect);	
		CBrush* pBrush=new CBrush();
		pBrush->CreateSolidBrush(RGB(0,255,100));
		dc.FillRect( &rect,pBrush );

		dc.SetBkMode(TRANSPARENT);

		//rect.top+=20;			// make the title lower from top		
		//dc.SetTextColor(RGB(10,10,10));		
		//dc.DrawText(title,-1,&rect,DT_SINGLELINE|DT_CENTER);		
		//rect.top-=1;
		//rect.left-=2;
		dc.SetTextColor(RGB(0,0,0));
		//dc.DrawText(title,-1,&rect,DT_SINGLELINE|DT_CENTER);	
		int h=dc.DrawText(title,-1,&rect,DT_CALCRECT);	
		CRect rect1;
		GetWindowRect(&rect1);
		MoveWindow(rect1.left,rect1.top,rect1.right-rect1.left,60+h);
		GetClientRect(&rect1);
		//dc.DrawText(title,-1,&rect,DT_CENTER|DT_SINGLELINE);
		//if(pos1>0){
		//	dc.DrawText(title,-1,&rect1,DT_SINGLELINE|DT_LEFT|DT_NOCLIP|DT_WORDBREAK);	
		//	dc.SetTextColor(RGB(255,0,0));
		//	dc.DrawText(title1,-1,&rect1,DT_SINGLELINE|DT_CENTER);	
		//}else		
		dc.DrawText(title,-1,&rect1,DT_SINGLELINE|DT_CENTER|DT_VCENTER);	
		//dc.DrawText(title,-1,&rect1,DT_CENTER|DT_WORDBREAK);	
		//------------------------------
		
	}
}
void CTMsgbox::OnDestroy(){
	//MessageBox("OnDestroy");
	bInterrupted=TRUE;
}