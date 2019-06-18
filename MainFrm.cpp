// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "InfoMgr.h"

#include "MainFrm.h"
#include "LeftView.h"
#include "InfoMgrView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_PLAYMODE, OnPlaymode)
	ON_UPDATE_COMMAND_UI(ID_PLAYMODE, OnUpdatePlaymode)
	ON_COMMAND(ID_INSERTONLY, OnInsertonly)
	ON_UPDATE_COMMAND_UI(ID_INSERTONLY, OnUpdateInsertonly)
	ON_COMMAND(ID_EDIT_ReadOnly, OnEDITReadOnly)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ReadOnly, OnUpdateEDITReadOnly)
	ON_UPDATE_COMMAND_UI(ID_EDIT_INSERT, OnUpdateEditInsert)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ITEM, OnUpdateEditItem)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_POSITION, OnUpdateEditPosition)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_UPDATE_COMMAND_UI(ID_SORT, OnUpdateSort)
	ON_UPDATE_COMMAND_UI(ID_MOVEDOWN, OnUpdateMovedown)
	ON_UPDATE_COMMAND_UI(ID_MOVEUP, OnUpdateMoveup)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnUpdateViewStyles)
	ON_COMMAND_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnViewStyle)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	PlayMode=FALSE;	
	m_InsertOnOneFileDrop=FALSE;
	m_bReadOnly=TRUE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
//XXX
/*
	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}		
*/	
//XXX-

	

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);
	

	//--------------set size of the main frame
	//this->MoveWindow(10,10,800,600,TRUE);
	DragAcceptFiles();

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	// create splitter window
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;
/*
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftView), CSize(400, 100), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CInfoMgrView), CSize(400, 400), pContext)||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CContentView), CSize(400, 400), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}
*/
	// add the first splitter pane - the default view in column 0
	if (!m_wndSplitter.CreateView(0, 0, pContext->m_pNewViewClass, CSize(400, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}
	// add the second splitter pane - which is a nested splitter with 2 rows
	if (!m_wndSplitter2.CreateStatic(
		&m_wndSplitter,     // our parent window is the first splitter
		2, 1,               // the new splitter is 2 rows, 1 column
		WS_CHILD | WS_VISIBLE | WS_BORDER,  // style, WS_BORDER is needed
		m_wndSplitter.IdFromRowCol(0, 1)
			// new splitter is in the first row, 2nd column of first splitter
	   ))
	{
		TRACE0("Failed to create nested splitter\n");
		return FALSE;
	}
	// now create the two views inside the nested splitter

	if (!m_wndSplitter2.CreateView(0, 0,
		RUNTIME_CLASS(CInfoMgrView), CSize(0, 0), pContext))
	{
		TRACE0("Failed to create second pane\n");
		return FALSE;
	}
	if (!m_wndSplitter2.CreateView(1, 0,
		RUNTIME_CLASS(CContentView), CSize(2400, 0), pContext))
	{
		TRACE0("Failed to create third pane\n");
		return FALSE;
	}

	// it all worked, we now have two splitter windows which contain
	//  three different views
	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	/*
	cs.lpszName="New Title ?";
	cs.cx=300;
	cs.cy=500;
	cs.x=100;
	cs.y=200;
	*/
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs	

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

CInfoMgrView* CMainFrame::GetRightPane()
{
	CWnd* pWnd = m_wndSplitter.GetPane(0, 1);
	CInfoMgrView* pView = DYNAMIC_DOWNCAST(CInfoMgrView, pWnd);
	return pView;
}

void CMainFrame::OnUpdateViewStyles(CCmdUI* pCmdUI)
{
	// TODO: customize or extend this code to handle choices on the
	// View menu.

	CInfoMgrView* pView = GetRightPane(); 

	// if the right-hand pane hasn't been created or isn't a view,
	// disable commands in our range

	if (pView == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		DWORD dwStyle = pView->GetStyle() & LVS_TYPEMASK;

		// if the command is ID_VIEW_LINEUP, only enable command
		// when we're in LVS_ICON or LVS_SMALLICON mode

		if (pCmdUI->m_nID == ID_VIEW_LINEUP)
		{
			if (dwStyle == LVS_ICON || dwStyle == LVS_SMALLICON)
				pCmdUI->Enable();
			else
				pCmdUI->Enable(FALSE);
		}
		else
		{
			// otherwise, use dots to reflect the style of the view
			pCmdUI->Enable();
			BOOL bChecked = FALSE;

			switch (pCmdUI->m_nID)
			{
			case ID_VIEW_DETAILS:
				bChecked = (dwStyle == LVS_REPORT);
				break;

			case ID_VIEW_SMALLICON:
				bChecked = (dwStyle == LVS_SMALLICON);
				break;

			case ID_VIEW_LARGEICON:
				bChecked = (dwStyle == LVS_ICON);
				break;

			case ID_VIEW_LIST:
				bChecked = (dwStyle == LVS_LIST);
				break;

			default:
				bChecked = FALSE;
				break;
			}

			pCmdUI->SetRadio(bChecked ? 1 : 0);
		}
	}
}


void CMainFrame::OnViewStyle(UINT nCommandID)
{
	// TODO: customize or extend this code to handle choices on the
	// View menu.
	CInfoMgrView* pView = GetRightPane();

	// if the right-hand pane has been created and is a CInfoMgrView,
	// process the menu commands...
	if (pView != NULL)
	{
		DWORD dwStyle = -1;

		switch (nCommandID)
		{
		case ID_VIEW_LINEUP:
			{
				// ask the list control to snap to grid
				CListCtrl& refListCtrl = pView->GetListCtrl();
				refListCtrl.Arrange(LVA_SNAPTOGRID);
			}
			break;

		// other commands change the style on the list control
		case ID_VIEW_DETAILS:
			dwStyle = LVS_REPORT;
			break;

		case ID_VIEW_SMALLICON:
			dwStyle = LVS_SMALLICON;
			break;

		case ID_VIEW_LARGEICON:
			dwStyle = LVS_ICON;
			break;

		case ID_VIEW_LIST:
			dwStyle = LVS_LIST;
			break;
		}

		// change the style; window will repaint automatically
		if (dwStyle != -1)
			pView->ModifyStyle(LVS_TYPEMASK, dwStyle);
	}
}


/*
void CMainFrame::OnCollapse() 
{
	// TODO: Add your command handler code here
	MessageBox("OnCollapse");
	CTreeCtrl* pmyTreeCtrl=&GetTreeCtrl();

}
*/
void CMainFrame::OnPlaymode() 
{
	// TODO: Add your command handler code here
	if(PlayMode)
		PlayMode=FALSE;
	else{
		PlayMode=TRUE;		
	}
	Invalidate ();
}

void CMainFrame::OnUpdatePlaymode(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->SetCheck(PlayMode);
}

void CMainFrame::OnInsertonly() 
{
	// TODO: Add your command handler code here
	if(m_InsertOnOneFileDrop)
		m_InsertOnOneFileDrop=FALSE;
	else{
		m_InsertOnOneFileDrop=TRUE;		
	}
	Invalidate ();
}

void CMainFrame::OnUpdateInsertonly(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_InsertOnOneFileDrop);
	
}

void CMainFrame::OnEDITReadOnly() 
{
	// TODO: Add your command handler code here
    if(m_bReadOnly)
		m_bReadOnly=FALSE;
	else
		m_bReadOnly=TRUE;	
	Invalidate();
}

void CMainFrame::OnUpdateEDITReadOnly(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bReadOnly);
	
}

void CMainFrame::OnUpdateEditInsert(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bReadOnly);
}

void CMainFrame::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bReadOnly);
}

void CMainFrame::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bReadOnly);
}

void CMainFrame::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bReadOnly);
}

void CMainFrame::OnUpdateEditItem(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bReadOnly);
}

void CMainFrame::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bReadOnly);
}

void CMainFrame::OnUpdateEditPosition(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bReadOnly);
}

void CMainFrame::OnUpdateEditRedo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bReadOnly);
}

void CMainFrame::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bReadOnly);
}

void CMainFrame::OnUpdateSort(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bReadOnly);
}

void CMainFrame::OnUpdateMovedown(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bReadOnly);
}

void CMainFrame::OnUpdateMoveup(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bReadOnly);
}
