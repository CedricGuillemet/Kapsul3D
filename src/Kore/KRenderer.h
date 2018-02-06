// KRenderer.h: interface for the CKRenderer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KRENDERER_H__CFE1F7E8_DB72_41D6_86B6_AE0E91F02C28__INCLUDED_)
#define AFX_KRENDERER_H__CFE1F7E8_DB72_41D6_86B6_AE0E91F02C28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "KOption.h"
#include "KHandles.h"
#include "KScenePlugin.h"

enum RND_TYPES 
{
	KPOINTS,
	KLINE_STRIP,
	KLINE_LOOP,
	KLINES,
	KTRIANGLE_STRIP,
	KTRIANGLE_FAN,
	KTRIANGLES,
	KQUAD_STRIP,
	KQUADS,
	KPOLYGON,
};

class KAPSUL_DESC CKRenderer  
{
public:
	CKOption *m_Option;
	HINSTANCE m_hInst;

	CKRenderer();
	virtual ~CKRenderer();
	void SetPlugin(CKScenePlugin *Plugin);
	InitBase(CKScene *Scene);

	//  Handles
	virtual void DrawHandles(CKHandles *Handles,int ActiveView,Vertex &HandMin,Vertex &HandMax);

	// General
	virtual CString GetRendererName();
	virtual HWND CreateConfigWindow(HWND Parent);

	// World coordinates

	virtual Vertex GetIsoCoord(int X, int Y,int ViewInd);
	virtual Vertex GetIsoCoord(int X, int Y,int ViewInd,Vertex Prj);
	virtual void Project(int ViewNb,float x,float y,float z,double &dx,double &dy,double &dz);
	virtual void Project(Vertex * vt, Vertex * dst, int ViewInd);
	
	// Rendering
	virtual void BeginRender(void);
	virtual void RenderOne(int ViewNb);
	virtual void Render(void);
	virtual void EndRender(void);
	virtual void Resize(int X,int Y);
	virtual void DrawMesh(CKMesh * daO,int daState,int FrameInd);

	// Kapsul Context
	virtual void InitContext(HWND window);
	virtual void DeleteContext();

	// Textures
	virtual bool LoadTexture(CString FileName,void *TexID,int &SizeX,int &SizeY);
	virtual void BindTexture(void *TexID);
	virtual void FreeTexture(void *TexID);

	// Direct Rendering (Simple render : For General purposes entities/plugins)

	virtual void DirectRender(Vertex *Verts,UVCoords *UVs,int *Indices,DWORD RenderType,int iNbIndex,float R,float G,float B,float A);

	// Updating an Object from the scene

	virtual void UpdateScene(int ObjectType,void *pData);
	virtual void SetCamera(CKCamera *pCam);

public:
	HWND m_hWnd;
	CKScene *m_Scene;
	CKScenePlugin *m_Plugin;
protected:

	// Localized strings

	CString strTop,strFront,strRight,strBottom,strBack,strLeft,strUser;
	void LocalizeNames(void);
	CString GetName(int ViewInd);
	int GetViewType(int ViewInd);

};

#endif // !defined(AFX_KRENDERER_H__CFE1F7E8_DB72_41D6_86B6_AE0E91F02C28__INCLUDED_)
