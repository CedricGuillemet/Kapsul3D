// ProjectTree.cpp: implementation of the CProjectTree class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "kapsulse.h"
#include "ProjectTree.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CProjectTree, CMultiTree)
	//{{AFX_MSG_MAP(CMultiTree)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CProjectTree::CProjectTree()
{

}

CProjectTree::~CProjectTree()
{

}

void CProjectTree::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//	CTreeCtrl::OnRButtonDown(nFlags, point);
	UINT nHF;
	BCMenu mnu,*mnu2;
	CPoint point2;

	hContextItem = HitTest(point, &nHF);
	int Type=GetItemId(hContextItem);
	SelectItem(hContextItem);
	if (!CanDropFile)
	{
		switch (Type)
		{
		case 0:
			mnu.LoadMenu(IDR_PROJECTCTXPRJ);
			mnu2=(BCMenu*)mnu.GetSubMenu(0);
			ClientToScreen(&point);
			mnu2->TrackPopupMenu(0,point.x,point.y,this);
			break;
		case 1:
			mnu.LoadMenu(IDR_PROJECTCTXFOLDER);
			mnu2=(BCMenu*)mnu.GetSubMenu(0);
			ClientToScreen(&point);
			mnu2->TrackPopupMenu(0,point.x,point.y,this);
			break;
		case 2:
			mnu.LoadMenu(IDR_PROJECTCTXFILE);
			mnu2=(BCMenu*)mnu.GetSubMenu(0);
			ClientToScreen(&point);
			mnu2->TrackPopupMenu(0,point.x,point.y,this);
			break;

		}
	}
}
