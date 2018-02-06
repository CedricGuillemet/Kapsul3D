// KMainEdit.h: interface for the CKMainEdit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KMAINEDIT_H__9E95DC94_27A6_49AE_8706_EA3D9552A16C__INCLUDED_)
#define AFX_KMAINEDIT_H__9E95DC94_27A6_49AE_8706_EA3D9552A16C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KViewEdit.h"

class CKMainEdit : public CKViewEdit  
{
public:
	CKMainEdit();
	virtual ~CKMainEdit();
	DECLARE_DYNCREATE(CKMainEdit)

	void KMouseDown(int Button,int iX, int iY);
	void KMouseMove(int Button, int iX, int iY);
	void KMouseUp(int Button, int iX, int iY);
	BOOL KMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	
private:

	void ShowContextMenu(int iX,int iY);
	void CalcHandles(int Indice);

	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnRButtonDown(UINT nFlags, CPoint point);
	void OnRButtonUp(UINT nFlags, CPoint point);
	void OnMButtonDown(UINT nFlags, CPoint point);
	void OnMButtonUp(UINT nFlags, CPoint point);

private:
	void BeginMoveView();
	void MoveView();
	void EndMoveView();

	void Pan3D();
	void Pan3D2();

	void SelectQuad();
	void SelectCircle();
	void EndSelectCircleQuad();

	void ClickSelectFence();

	void BeginRotateView();
	void RotateView();

	void Zoom();

	void BeginMoveBuffer();
	void MoveBuffer();
	void BeginRotateBuffer();
	void RotateBuffer();
	void BeginScaleBuffer();
	void ScaleBuffer();

	void BeginBendBuffer();
	void BendBuffer();

	void BeginTaperBuffer();
	void TaperBuffer();

	void BeginSquizBuffer();
	void SquizBuffer();

	void EndStandardOps();

	void RegionFit();
	void EndRegionFit();

	void ClickApplyTexMesh();
	void ClickRetrieveTexMesh();

	void ClickApplyTexPoly();
	void ClickRetrieveTexPoly();


	void UpdateTaggedByPlugin(void);
	void DoSnapping(Vertex &toSnap);

	void CopyMoving();
private:
	int ox,oy;
    Vertex hui,hui2,hui3;
	Vertex ScaleVal;
	//static int omx, omy, mx, my;
	int X,Y;
	UINT m_Button;
	MYPOINT tlng;
	double daNgx,daNgy;
	int mx,my;
	int HandleNb;

};

#endif // !defined(AFX_KMAINEDIT_H__9E95DC94_27A6_49AE_8706_EA3D9552A16C__INCLUDED_)
