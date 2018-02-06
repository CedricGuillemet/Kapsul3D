//---------------------------------------------------------------------------
#include "stdafx.h"

//#include "memmgr/mmgr.h"

//---------------------------------------------------------------------------

Face::~Face()
{
    /*
	delete [] nbvert;
	delete [] u;
	delete [] v;
   */
}

inline bool Face::GetSelected() const
{
    return Selected;
}

inline void Face::SetSelected(bool selected)
{
    Selected = selected;
}


Face::Face()
{
    Selected=false;
    nbvert=new int[3];

}

Face::Face(int v1,int v2,int v3)
{
    Selected=false;
    nbvert=new int[3];

    nbvert[0]=v1;
    nbvert[1]=v2;
    nbvert[2]=v3;

}

void Face::operator =(Face cmpt)
{
    memcpy(nbvert,cmpt.nbvert,sizeof(int)*3);

    Selected=cmpt.Selected;
}

