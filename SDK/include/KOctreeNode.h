// KOctreeNode.h: interface for the CKOctreeNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KOCTREENODE_H__9437B162_F0A0_4AA6_9C87_74B5561EC8D1__INCLUDED_)
#define AFX_KOCTREENODE_H__9437B162_F0A0_4AA6_9C87_74B5561EC8D1__INCLUDED_

#include "KBoundBox.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class  __declspec(dllexport) CKOctreeNode  
{
public:
	CKOctreeNode **Childs;
	CKBoundBox Bound;
	inline CKOctreeNode()
    {
        Childs=new CKOctreeNode* [8];
        for (int i=0;i<8;i++)
            Childs[i]=NULL;
    }

	inline virtual ~CKOctreeNode()
    {
        for (int i=0;i<8;i++)
            if (Childs[i]!=NULL) delete Childs[i];

        delete [] Childs;
    }

};

#endif // !defined(AFX_KOCTREENODE_H__9437B162_F0A0_4AA6_9C87_74B5561EC8D1__INCLUDED_)
