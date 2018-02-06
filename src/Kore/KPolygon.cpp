#include "stdafx.h"

inline int CKPolygon::Allocate(CKMesh *daObj,int nbv)
{
	FirstIndex=daObj->GetIntPtrPoly(nbv);//(int*)malloc(sizeof(int)*nbv);

	nb2vert=nbv;
	return FirstIndex;
}