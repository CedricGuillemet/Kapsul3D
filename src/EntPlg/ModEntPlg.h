// KPrimitivePlugin.h: interface for the CKScenePlugin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CKPluginEntPlg_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_)
#define AFX_CKPluginEntPlg_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <kapsul3D.h>

#include "DumpEntPlg.h"

class CKPluginEntPlg  : public CKScenePlugin
{
public:
	CKPluginEntPlg();
	virtual ~CKPluginEntPlg();

	HWND Open(HWND Parent);
	void Close();
	int ScenePluginType();
	void ReSize(int sx,int sy);
	void LoseFocus();

	CString GetName();
	CString GetInfos();

	bool CreatingStatus();
	void SetScene(CKScene *pScene);
	void SetObject(void *pData,int DataType=0);

	PrimBmp* GetAllPrimitives();
	void SetPrimitive(int PrimitiveNb);
	void DeleteStuff(void *pData=NULL,int DataType=0);
	void UpdateStuff(void *pObject,int PlugType);



    void LMouseDown(int X,int Y,Vertex &Pos);
    void RMouseDown(int X,int Y,Vertex &Pos);
    void LMouseUp(int X,int Y,Vertex &Pos);
    void RMouseUp(int X,int Y,Vertex &Pos);
    void MouseMove(int X,int Y,Vertex &Pos);

	void KeyDown(BYTE ckey);
	void KeyUp(BYTE ckey);

private:
//	HWND Parent;

//	HINSTANCE myHinst;
	bool IsCreating;
	CKScene *m_Scene;
	//CKDrawScene *GDrawScene;
	int TypeEdit;

	/*
		Process message handler
	*/
	CBitmap m_Dib;
	CWnd *tempo;
	CEntPlg *ModDiag;

//	CKEntity *CurrentEntity;
	//CEntity *CurrentPropEntity=NULL;
	CKEntityType *EntType;
	PrimBmp daBmps;
};

#endif // !defined(AFX_KPRIMITIVEPLUGIN_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_)
