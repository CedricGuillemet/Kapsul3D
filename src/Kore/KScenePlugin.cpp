// KPrimitivePlugin.cpp: implementation of the CKScenePlugin class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KScenePlugin.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKScenePlugin::CKScenePlugin()
{

}

CKScenePlugin::~CKScenePlugin()
{

}

HWND CKScenePlugin::Open(HWND Parent)
{
	return NULL;
}

void CKScenePlugin::Close()
{
}

void CKScenePlugin::ReSize(int sx,int sy)
{
}

void CKScenePlugin::LoseFocus()
{
	
}

CString CKScenePlugin::GetName()
{
	return "";
}

CString CKScenePlugin::GetInfos()
{
	return "";
}

bool CKScenePlugin::CreatingStatus()
{
	return false;
}

void CKScenePlugin::SetScene(CKScene *pScene)
{
	
}

void CKScenePlugin::SetObject(void *pData,int DataType)
{

}

DWORD CKScenePlugin::OwnerDraw(CKRenderer *pRenderer,int ViewNb)
{
	return PLUGIN_ALL;
}

CBitmap *CKScenePlugin::GetBitmap()
{
	return NULL;
}

PrimBmp* CKScenePlugin::GetAllPrimitives()
{
	return NULL;
}

void CKScenePlugin::SetPrimitive(int PrimitiveNb)
{
}

void CKScenePlugin::DeleteStuff(void *pData,int DataType)
{
}

void CKScenePlugin::LMouseDown(int X,int Y,Vertex &Pos)
{
}

void CKScenePlugin::RMouseDown(int X,int Y,Vertex &Pos)
{
}

void CKScenePlugin::LMouseUp(int X,int Y,Vertex &Pos)
{
}

void CKScenePlugin::RMouseUp(int X,int Y,Vertex &Pos)
{
}

void CKScenePlugin::MouseMove(int X,int Y,Vertex &Pos)
{
}

int CKScenePlugin::ScenePluginType()
{

	return 0;
}

int CKScenePlugin::GetCursor(int X,int Y)
{
	return 0;
}

void CKScenePlugin::KeyDown(BYTE ckey)
{

}

void CKScenePlugin::KeyUp(BYTE ckey)
{

}

void CKScenePlugin::UpdateStuff(void *pObject,int PlugType)
{

}

void CKScenePlugin::UpdateSelection()
{

}