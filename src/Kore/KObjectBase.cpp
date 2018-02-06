// KObjectBase.cpp: implementation of the CKObjectBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KObjectBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKObjectBase::CKObjectBase()
{
	RefCount1=0;
	RefCount2=0;
}

CKObjectBase::~CKObjectBase()
{

}

void CKObjectBase::IsCopyOf(CKObjectBase *pBase)
{

}


void CKObjectBase::UpdateBBManual(Vertex &vMin,Vertex &vMax)
{
	BBMin=vMin;
	BBMax=vMax;
}
