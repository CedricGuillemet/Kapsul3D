#include "stdafx.h"

inline VertBuf::VertBuf(Vertex *Ind,VertBuf *daPrev,VertBuf *daNext,int Index)
{
    AncVal.x=Ind->x;
    AncVal.y=Ind->y;
    AncVal.z=Ind->z;
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
    if (Dest!=NULL)
    {
        Dest->x=NewValue.x;
        Dest->y=NewValue.y;
        Dest->z=NewValue.z;

		switch (TargetType)
		{
		case PLUGIN_MESH:
			((CKMesh*)TargetCont)->Tag=1;
			break;
		case PLUGIN_SEGMENT:
			((CKSegment*)TargetCont)->Tag=1;
			break;
		case PLUGIN_SKELETON:
			((CKSkeleton*)TargetCont)->Tag=1;
			break;
		case PLUGIN_CAMERA:
			((CKCamera*)TargetCont)->Tag=1;
			break;
		case PLUGIN_PATCH:
			((CKPatch*)TargetCont)->Tag=1;
			break;
		case PLUGIN_BONE:
			((CKBone*)TargetCont)->Tag=1;
			break;
		case PLUGIN_ENTITY:
			((CKEntity*)TargetCont)->Tag=1;
			break;
		}
		/*
        if (Cam!=NULL)
			Cam->SetCKCamera();
		if (Skel!=NULL)
			Skel->BuildBase();
			*/
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
