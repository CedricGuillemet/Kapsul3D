
#if !defined(AFX_CKPluginCamera_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_)
#define AFX_CKPluginCamera_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <kapsul3D.h>
#include "ModDiag.h"
class CKPluginCamera : public CKScenePlugin  
{
public:
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
	void DeleteStuff();

    void LMouseDown(int X,int Y,Vertex &Pos);
    void LMouseUp(int X,int Y,Vertex &Pos);
    void RMouseUp(int X,int Y,Vertex &Pos);
    void MouseMove(int X,int Y,Vertex &Pos);

private:

	PrimBmp daBmps;
	bool IsCreating;
	CKScene *m_Scene;
	CKCamera *CurrentCam;
	bool CreateSeg;
	Vertex Remem;
	bool HasMoveCr;
	CKUndoRedo *CurrentUndo;
	CModDiag *ModDiag;
};

#endif // !defined(AFX_KPRIMITIVEPLUGIN_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_)
