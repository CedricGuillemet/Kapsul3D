
#if !defined(AFX_CKPluginPrim3D_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_)
#define AFX_CKPluginPrim3D_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <kapsul3D.h>

#include "tree/tree/tree.h"
#include "resource.h"
#include "primdiag.h"
#include "parameters.h"
class CPrimDiag;



class CKPluginPrim3D : CKScenePlugin
{
public:
	CKPluginPrim3D();
	virtual ~CKPluginPrim3D();

	HWND Open(HWND Parent);
	void Close();
	int ScenePluginType();
	void ReSize(int sx,int sy);
	void LoseFocus();

	CString GetName();
	CString GetInfos();

	bool CreatingStatus();
	void SetScene(CKScene *pScene);

	PrimBmp* GetAllPrimitives();
	void SetPrimitive(int PrimitiveNb);
	void DeleteStuff(void *pData=NULL,int DataType=0);

    void LMouseDown(int X,int Y,Vertex &Pos);
    void RMouseDown(int X,int Y,Vertex &Pos);
    void LMouseUp(int X,int Y,Vertex &Pos);
    void RMouseUp(int X,int Y,Vertex &Pos);
    void MouseMove(int X,int Y,Vertex &Pos);
public:
	void UpdateCurrentPrimitive(void);

public:

	CPrimDiag *BrowserDiag;
	

	//CParameters m_Parameters;

	int TypeEdit;
	int nbSegHemis,nbSegSphere,nbSeg1Grid,nbSeg2Grid,nbSeg1Torus,nbSeg2Torus;
	int nbSeg1Cylinder,nbSeg2Cylinder,nbSeg1Cone,nbSeg2Cone,nbSeg1Tube;
	int nbSeg2Tube,nbSeg1Patch,nbSeg2Patch,nbSegStairs;
	int nbSeg13DGrid,nbSeg23DGrid,nbSeg33DGrid;
	CKUndoRedo *CurrentUndo;
	int CreateSeg;
	Vertex Remem;
	HWND daview;
	Vertex StartVert,LengthVert;
	int dx,dy,X,Y,oX,oY;
	bool HasMoveCr;
	CKMesh *CurrentMesh;
	CKMesh *LeafMesh;
	CKPatch *CurrentPatch;
	
	Vertex rmX,rmY;
	Vertex RememBox,RememBox2,RememBox3;
	float Valv,Valu;
	double Radius1,Radius2,Radius3;
	double OriginNg;
	bool GNeedTexRecalc;
	CKScene *m_Scene;
	CKPlan Crp;
	Tree mytree;

	CBitmap m_Dib;
	PrimBmp daBmps;
	CKGenericMesh m_Gen;

	void ObjToUndo(void);
	void PatchToUndo(void);
	void LastToSel(void);

	CKSkeleton *CurSkel,*CurrentSkel;
	CKBone *CurrentBone;
	
};

#endif // !defined(AFX_KPRIMITIVEPLUGIN_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_)
