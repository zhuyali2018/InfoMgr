// InfoMgrDoc.h : interface of the CInfoMgrDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFOMGRDOC_H__522C8C68_8DFA_42AF_B050_F86BF7AFACD3__INCLUDED_)
#define AFX_INFOMGRDOC_H__522C8C68_8DFA_42AF_B050_F86BF7AFACD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Record.h"
class CInfoMgrDoc : public CDocument
{
protected: // create from serialization only
	CInfoMgrDoc();
	DECLARE_DYNCREATE(CInfoMgrDoc)

// Attributes
public:
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfoMgrDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents( );

	//}}AFX_VIRTUAL

// Implementation
public:	
	CDetailFile * DetailFile;
	void SaveTheRecord(CRecord * pItem);
	static int saveCounter;
	void SaveTheItem(HTREEITEM hItem);
	CArchive * m_ar;
	void SaveTheFamily(HTREEITEM hItem);
	void SaveToFileWithOrder(CArchive & ar);
	void SaveToFile(CArchive & ar);
	void addChildren(HTREEITEM hnode);
	CTreeCtrl * treeCtrl;
	CRecord * pSearchPtr;
	CRecord * pNextPtr;
	CRecord * FindNextWithParentID(int parentID);
	void PopulateTreeView();
	void LoadRecord(CString line,CDetailFile * details);
	int ParseForIDCounter(CString line);
	void SaveDetail(CRecord * ptr);
	void AddToList(CRecord * recordObj);
	CRecord * tail;
	CRecord * head;
	//int SaveProcessID;
	//void OnInsert();
	CString str[3];
	virtual BOOL OnSaveDocument( LPCTSTR lpszPathName );
	virtual ~CInfoMgrDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CInfoMgrDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFOMGRDOC_H__522C8C68_8DFA_42AF_B050_F86BF7AFACD3__INCLUDED_)
