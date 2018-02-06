//////////////////////////////////////////////////////////////////////
//
// 3DObjectStuff.h: header file for 3DObjectStuff.cpp
//
//////////////////////////////////////////////////////////////////////

#include "3dtypes.h"

#if !defined(_3DOBJECT_STUFF_INCLUDED_)
#define _3DOBJECT_STUFF_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

extern bool Compute3DObject_to_KapsulScene(t_3Dobject *The3DObject,CKScene *TheKapsulScene);
extern bool ComputeKapsulScene_to_3DObject(CKScene *TheKapsulScene,t_3Dobject *The3DObject);

#endif // !defined(_3DOBJECT_STUFF_INCLUDED_)
