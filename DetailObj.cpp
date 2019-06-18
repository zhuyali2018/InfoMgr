// DetailObj.cpp: implementation of the CDetailObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DetailObj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDetailObj::CDetailObj(int detailID)
{	
	Next=Prev=NULL;
	ID=detailID;
	Detail="";
}

CDetailObj::~CDetailObj()
{

}
