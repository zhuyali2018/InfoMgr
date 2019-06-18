// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class COLEObject;

/////////////////////////////////////////////////////////////////////////////
// COLEObjects wrapper class

class COLEObjects : public COleDispatchDriver
{
public:
	COLEObjects() {}		// Calls COleDispatchDriver default constructor
	COLEObjects(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	COLEObjects(const COLEObjects& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	COLEObject GetItem(const VARIANT& Item);
	long GetCount();
	void Clear();
	COLEObject Add(const VARIANT& Index, const VARIANT& Key, const VARIANT& source, const VARIANT& objclass);
	void Remove(const VARIANT& Item);
};
