// EntityProp.cpp: implementation of the CEntityProp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Enti.h"
#include "EntityProp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEntityProp::CEntityProp(CEntityProp *daPrev,CEntityProp *daNext)
{
    Type=0;
    memset(Name,0,32);
    Prev=daPrev;
    Next=daNext;
    Vals=NULL;
    SizeVals=0;
}

CEntityProp::~CEntityProp()
{

}
