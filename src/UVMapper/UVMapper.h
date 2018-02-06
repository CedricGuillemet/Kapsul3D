
#if !defined(AFX_KUVMapper_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_)
#define AFX_KUVMapper_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <kapsul3D.h>
#include "ModDiag.h"

class CKRenderer;
class CKEntity;

class CKUVMapper : public CKScenePlugin
{
public:
	CKUVMapper();
	~CKUVMapper();

	HWND Open(HWND Parent);
	void Close();
	int ScenePluginType();
	void ReSize(int sx,int sy);
	void LoseFocus();

	CString GetName();
	CString GetInfos();

	bool CreatingStatus();
	void SetScene(CKScene *pScene);
	DWORD OwnerDraw(CKRenderer *pRenderer,int ViewNb);
	int GetCursor(int X,int Y);

	CBitmap *GetBitmap();
	CBitmap *GetHotBitmap();

    void LMouseDown(int X,int Y,Vertex &Pos);
    void LMouseUp(int X,int Y,Vertex &Pos);
    void MouseMove(int X,int Y,Vertex &Pos);
public:
	Vertex OldTrans;
	CBitmap m_Dib;
	CBitmap m_Dib2;
	CPathModDiag *m_Diag;
	//CTexture MapTex(NULL,NULL);
	CKPlan dap;
	CKMesh *daMesh;

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
	int dx,dy;
	Vertex SnapVal;//(8,8,8);
	HINSTANCE myHinst;
	bool IsCreating;
	CKScene *m_Scene;
	int TypeMap;
	int TypeEd;
};

#endif // !defined(AFX_KPRIMITIVEPLUGIN_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_)
