// KUVEdit.h: interface for the CKUVEdit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KUVEDIT_H__D26B8B85_17F6_4511_842F_4CA53CFB539E__INCLUDED_)
#define AFX_KUVEDIT_H__D26B8B85_17F6_4511_842F_4CA53CFB539E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CKUVEdit  
{
public:
	CKUVEdit();
	virtual ~CKUVEdit();
	DWORD OwnerDraw(CKRenderer *pRenderer,int ViewNb);
	void LMouseDown(int X,int Y,Vertex &Pos);
	void LMouseUp(int X,int Y,Vertex &Pos);
	void MouseMove(int X,int Y,Vertex &Pos);
	void Init();

	int dx,dy;

	CKMesh SphereMap,CubeMap,PlanarMap,CylMap;
	CKMesh SphereMap2,CubeMap2,PlanarMap2,CylMap2;
	CKMesh *ApplyMapMesh;
	CKMesh *ApplyMapMesh2;
	CKHandles UVHand;
	bool IsMoving;
	Vertex m_ScaleMask;
	double ngl;
	MYPOINT m_ScaleSvgSize;
	int NewHand;
	Vertex Getng,Getng2;
	Vertex hui,huitemp;
	Vertex SnapVal;//(8,8,8);
	HINSTANCE myHinst;
	bool IsCreating;
	int TypeMap;
	CKScene *m_Scene;
	int TypeEd;
	CKPlan dap;
	Vertex OldTrans;
};

#endif // !defined(AFX_KUVEDIT_H__D26B8B85_17F6_4511_842F_4CA53CFB539E__INCLUDED_)
