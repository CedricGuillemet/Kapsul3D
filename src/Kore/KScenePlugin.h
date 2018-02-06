// KPrimitivePlugin.h: interface for the CKScenePlugin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KPRIMITIVEPLUGIN_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_)
#define AFX_KPRIMITIVEPLUGIN_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <kapsul3D.h>
class CKRenderer;
class CKEntity;

typedef struct
{
	int NbBmps;
	CBitmap Bmp[50];
	int PrimNb[50];
} PrimBmp;

class KAPSUL_DESC CKScenePlugin  
{
public:
	CKScenePlugin();
	virtual ~CKScenePlugin();

	HINSTANCE m_hInst;
	HWND m_hWnd;

	virtual HWND Open(HWND Parent);
	virtual void Close();
	virtual int ScenePluginType();
	virtual void ReSize(int sx,int sy);
	virtual void LoseFocus();

	virtual CString GetName();
	virtual CString GetInfos();

	virtual bool CreatingStatus();
	virtual void SetScene(CKScene *pScene);
	virtual void SetObject(void *pData,int DataType=0);
	virtual DWORD OwnerDraw(CKRenderer *pRenderer,int ViewNb);
	virtual int GetCursor(int X,int Y);

	virtual CBitmap *GetBitmap();
	virtual PrimBmp* GetAllPrimitives();
	virtual void SetPrimitive(int PrimitiveNb);
	virtual void DeleteStuff(void *pData=NULL,int DataType=0);
	virtual void UpdateStuff(void *pObject,int PlugType);
	virtual void UpdateSelection();



    virtual void LMouseDown(int X,int Y,Vertex &Pos);
    virtual void RMouseDown(int X,int Y,Vertex &Pos);
    virtual void LMouseUp(int X,int Y,Vertex &Pos);
    virtual void RMouseUp(int X,int Y,Vertex &Pos);
    virtual void MouseMove(int X,int Y,Vertex &Pos);

	virtual void KeyDown(BYTE ckey);
	virtual void KeyUp(BYTE ckey);
};

#endif // !defined(AFX_KPRIMITIVEPLUGIN_H__3A32AA80_C324_4EC8_BD80_03E3C12940A8__INCLUDED_)
