// ProjectTree.h: interface for the CProjectTree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTTREE_H__C89BC404_555C_498F_8ECB_96FA585E20E9__INCLUDED_)
#define AFX_PROJECTTREE_H__C89BC404_555C_498F_8ECB_96FA585E20E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MltiTree.h"

class CProjectTree : public CMultiTree  
{
public:
	CProjectTree();
	virtual ~CProjectTree();
protected:
	//{{AFX_MSG(CMultiTree)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_PROJECTTREE_H__C89BC404_555C_498F_8ECB_96FA585E20E9__INCLUDED_)
