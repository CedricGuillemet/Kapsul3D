// PrivateData.cpp: implementation of the CPrivateData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//#include "memmgr/mmgr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPrivateData::CPrivateData(CPrivateData *daPrev,CPrivateData *daNext)
{

    Prev=daPrev;
    Next=daNext;

    Name=new char [32];

    AllocatedByte=0;

}

CPrivateData::~CPrivateData()
{
    delete [] Name;
}

void * CPrivateData::Allocate(int Size)
{
    if (AllocatedByte==0) 
        lpBits=malloc(Size);
    else
        lpBits=realloc(lpBits,Size);

    AllocatedByte=Size;

    return lpBits;
}
