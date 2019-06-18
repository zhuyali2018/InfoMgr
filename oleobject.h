// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// COLEObject wrapper class

class COLEObject : public COleDispatchDriver
{
public:
	COLEObject() {}		// Calls COleDispatchDriver default constructor
	COLEObject(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	COLEObject(const COLEObject& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetIndex();
	CString GetKey();
	void SetKey(LPCTSTR lpszNewValue);
	CString GetClass();
	long GetDisplayType();
	void SetDisplayType(long nNewValue);
	VARIANT GetObjectVerbs();
	VARIANT GetObjectVerbFlags();
	long GetObjectVerbsCount();
	void DoVerb(const VARIANT& verb);
	long FetchVerbs();
};
