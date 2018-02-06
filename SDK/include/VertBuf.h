// Kapsul Core Library
// Copyright © 1999 - 2001, Cédric Guillemet
//
// Contact: lacrapul@club-internet.fr
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef VertBufH
#define VertBufH

#include "Kapsul3D.h"

class __declspec( dllexport ) VertBuf
{
    public:
        Vertex  AncVal;
        Vertex  *Dest;
        VertBuf  *Next,*Prev;
        Camera  *Cam;
		Skeletton *Skel;
        Object *Obj;
        Shape *Shp;
		CKPatch *Patch;
		int VertIndex;

        inline VertBuf(Vertex *Ind,VertBuf *daPrev,VertBuf *daNext,int Index);
        inline ~VertBuf();
        inline void IsNow(Vertex NewValue);
        inline void IsOldValue(void);
        inline void UpdateValue(void);
};

inline VertBuf::VertBuf(Vertex *Ind,VertBuf *daPrev,VertBuf *daNext,int Index)
{
    AncVal.vx=Ind->vx;
    AncVal.vy=Ind->vy;
    AncVal.vz=Ind->vz;
    Cam=NULL;
	Skel=NULL;
	Obj=NULL;
    Dest=Ind;
    Next=daNext;
    Prev=daPrev;
	VertIndex=Index;
}

inline VertBuf::~VertBuf()
{
}

inline void VertBuf::IsNow(Vertex NewValue)
{
    //(*Dest)=NewValue;
    if (Dest!=NULL)
    {
        Dest->vx=NewValue.vx;
        Dest->vy=NewValue.vy;
        Dest->vz=NewValue.vz;
        if (Cam!=NULL)
//            Cam->Compute();
			Cam->SetCamera();
		if (Skel!=NULL)
			Skel->BuildBase();
    }
}

inline void VertBuf::IsOldValue(void)
{
    (*Dest)=AncVal;
}

inline void VertBuf::UpdateValue(void)
{
    AncVal=(*Dest);
}

//---------------------------------------------------------------------------
#endif
 