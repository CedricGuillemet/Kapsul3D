// Maps.cpp: implementation of the CMaps class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"


//#include "memmgr/mmgr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMaps::CMaps()
{
    FirstImg=NULL;
    NextImg=NULL;
}

CMaps::~CMaps()
{

}

CImage * CMaps::AddMap(char *MapName)
{
    CImage *tmpCImg;

    tmpCImg=AlreadyIn(MapName);

    if (tmpCImg==NULL)
    {

        if (FirstImg==NULL)
        {
            FirstImg=new (CImage);
            NextImg=FirstImg;
        }
        else
        {
            NextImg->Next=new (CImage);
            NextImg= NextImg->Next;
        }
        strcpy(NextImg->FileName,MapName);

        return NextImg;
    }
    else
    {
        return tmpCImg;
    }
    //NextImg->LoadFile(MapName);
    
}

CImage * CMaps::AlreadyIn(char *MapName)
{
    CImage *par;

    par=FirstImg;
    while(par!=NULL)
    {
        if (strcmp(par->FileName,MapName)==0) return par;
        par=par->Next;
    }
    return NULL;
}