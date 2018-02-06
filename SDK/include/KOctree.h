// KOctree.h: interface for the CKOctree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KOCTREE_H__9A97A5DB_F83A_4C31_8D80_932AF8F93A49__INCLUDED_)
#define AFX_KOCTREE_H__9A97A5DB_F83A_4C31_8D80_932AF8F93A49__INCLUDED_

#include "Vertex.h"
#include "KOctreeNode.h"
#include "KBoundBox.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class  __declspec(dllexport) CKOctree  
{
public:
    inline bool BoxFitIn(CKBoundBox &cb,Vertex &Start,Vertex &Len);
	CKOctreeNode * FindBestNode(CKOctreeNode *Node,CKBoundBox &box);
	CKOctreeNode * AddFace(Vertex a,Vertex b,Vertex c);
	CKOctree(Vertex MinWS,Vertex MaxWS);
	void LoadFromDisk(FILE *fp);
	void WriteToDisk(FILE *fp);
	virtual ~CKOctree();
    __inline int NextPow2(int Number);
    CKOctreeNode *Root;
    CKBoundBox tempbnd;
    CKBoundBox wbox;
    Vertex WorldMin,WorldMax;
};

#endif // !defined(AFX_KOCTREE_H__9A97A5DB_F83A_4C31_8D80_932AF8F93A49__INCLUDED_)
