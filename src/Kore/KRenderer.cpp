// KRenderer.cpp: implementation of the CKRenderer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
extern CKOption *KOption2;

#include "KRenderer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CKRenderer::CKRenderer()
{
}

CKRenderer::InitBase(CKScene *Scene)
{
	m_Option=KOption2;
	m_Scene=Scene;
	LocalizeNames();
	m_Plugin=NULL;
}

CKRenderer::~CKRenderer()
{

}

void CKRenderer::LocalizeNames(void)
{
	strTop=GetLocal()->GetString(185,"Top");
	strFront=GetLocal()->GetString(189,"Front");
	strRight=GetLocal()->GetString(188,"Right");
	strBottom=GetLocal()->GetString(186,"Bottom");
	strBack=GetLocal()->GetString(190,"Back");
	strLeft=GetLocal()->GetString(187,"Left");
	strUser=GetLocal()->GetString(900,"Ortho");
}

CString CKRenderer::GetName(int ViewInd)
{
	if (m_Scene->ViewType[ViewInd]==VIEWTYPE_ORTHO)
	{
		if ((m_Scene->ViewNg[ViewInd].x==0)&&(m_Scene->ViewNg[ViewInd].y==0)&&(m_Scene->ViewNg[ViewInd].z==0)) return strTop;//TEXT("Top");
		if ((m_Scene->ViewNg[ViewInd].x==-90)&&(m_Scene->ViewNg[ViewInd].y==0)&&(m_Scene->ViewNg[ViewInd].z==0)) return strFront;//TEXT("Front");
		if ((m_Scene->ViewNg[ViewInd].x==-90)&&(m_Scene->ViewNg[ViewInd].y==0)&&(m_Scene->ViewNg[ViewInd].z==90)) return strRight;//TEXT("Right");

		if ((m_Scene->ViewNg[ViewInd].x==0)&&(m_Scene->ViewNg[ViewInd].y==180)&&(m_Scene->ViewNg[ViewInd].z==180)) return strBottom;//TEXT("Bottom");
		if ((m_Scene->ViewNg[ViewInd].x==90)&&(m_Scene->ViewNg[ViewInd].y==180)&&(m_Scene->ViewNg[ViewInd].z==0)) return strBack;//TEXT("Back");
		if ((m_Scene->ViewNg[ViewInd].x==270)&&(m_Scene->ViewNg[ViewInd].y==0)&&(m_Scene->ViewNg[ViewInd].z==270)) return strLeft;//TEXT("Left");

		return strUser;
	}
	else
	if (m_Scene->ViewType[ViewInd]==VIEWTYPE_UV)
		return "UV mapping";
	else
	if (m_Scene->ViewType[ViewInd]==VIEWTYPE_PERSPECTIVE)
		return "Camera";
	else
	if (m_Scene->ViewType[ViewInd]==VIEWTYPE_CAMERA)
	{
		if (m_Scene->cam[ViewInd]!=NULL)
		{
			return m_Scene->cam[ViewInd]->Name;
		}
	}
    return "NULL";
}

int CKRenderer::GetViewType(int ViewInd)
{
	if (m_Scene->ViewType[ViewInd]==VIEWTYPE_ORTHO)
	{
		if ((m_Scene->ViewNg[ViewInd].x==0)&&(m_Scene->ViewNg[ViewInd].y==0)&&(m_Scene->ViewNg[ViewInd].z==0)) return 1;//TEXT("Top");
		if ((m_Scene->ViewNg[ViewInd].x==-90)&&(m_Scene->ViewNg[ViewInd].y==0)&&(m_Scene->ViewNg[ViewInd].z==0)) return 2;//TEXT("Front");
		if ((m_Scene->ViewNg[ViewInd].x==-90)&&(m_Scene->ViewNg[ViewInd].y==0)&&(m_Scene->ViewNg[ViewInd].z==90)) return 3;//TEXT("Right");

		if ((m_Scene->ViewNg[ViewInd].x==0)&&(m_Scene->ViewNg[ViewInd].y==180)&&(m_Scene->ViewNg[ViewInd].z==180)) return 4;//TEXT("Bottom");
		if ((m_Scene->ViewNg[ViewInd].x==90)&&(m_Scene->ViewNg[ViewInd].y==180)&&(m_Scene->ViewNg[ViewInd].z==0)) return 5;//TEXT("Back");
		if ((m_Scene->ViewNg[ViewInd].x==270)&&(m_Scene->ViewNg[ViewInd].y==0)&&(m_Scene->ViewNg[ViewInd].z==270)) return 6;//TEXT("Left");

		return 7;
	}
	else
	if (m_Scene->ViewType[ViewInd]==VIEWTYPE_UV)
		return 10;
	else
	if (m_Scene->ViewType[ViewInd]==VIEWTYPE_PERSPECTIVE)
		return 8;
	else
	if (m_Scene->ViewType[ViewInd]==VIEWTYPE_CAMERA)
		return 9;
	
    return 0;
}

void CKRenderer::Project(int ViewNb,float x,float y,float z,double &dx,double &dy,double &dz)
{
	
}

void CKRenderer::DrawHandles(CKHandles *Handles,int ActiveView,Vertex &HandMin,Vertex &HandMax)
{

}

Vertex CKRenderer::GetIsoCoord(int X, int Y,int ViewInd)
{
	return Vertex(0,0,0);
}

Vertex CKRenderer::GetIsoCoord(int X, int Y,int ViewInd,Vertex Prj)
{
	return Vertex(0,0,0);
}

void CKRenderer::Project(Vertex * vt, Vertex * dst, int ViewInd)
{

}

void CKRenderer::BeginRender(void)
{
}

void CKRenderer::RenderOne(int ViewNb)
{
}

void CKRenderer::EndRender(void)
{
}

void CKRenderer::Render(void)
{

}

void CKRenderer::InitContext(HWND window)
{
}

void CKRenderer::DeleteContext(void)
{

}
CString CKRenderer::GetRendererName()
{
	char temp[MAX_PATH];
	char FileName[MAX_PATH],FileExt[32];
	CString sRet="Unamed plugin ";
	if (GetModuleFileName(m_hInst,temp,MAX_PATH)!=0)
	{
		_splitpath(temp,NULL,NULL,FileName,FileExt);
		sRet+="(";
		sRet+=FileName;
		sRet+=FileExt;
		sRet+=")";
	}

	return sRet;
}

HWND CKRenderer::CreateConfigWindow(HWND Parent)
{
	return 0;
}

void CKRenderer::Resize(int X,int Y)
{
}

bool CKRenderer::LoadTexture(CString FileName,void *TexID,int &SizeX,int &SizeY)
{
	
	return NULL;
}

void CKRenderer::BindTexture(void *TexID)
{

}

void CKRenderer::FreeTexture(void *TexID)
{
}

void CKRenderer::DirectRender(Vertex *Verts,UVCoords *UVs,int *Indices,DWORD RenderType,int iNbIndex,float R,float G,float B,float A)
{
}

void CKRenderer::UpdateScene(int ObjectType,void *pData)
{
}

void CKRenderer::SetCamera(CKCamera *pCam)
{
}

void CKRenderer::DrawMesh(CKMesh * daO,int daState,int FrameInd)
{
}