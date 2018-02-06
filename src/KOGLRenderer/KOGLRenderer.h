
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the KOGLRENDERER_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// KOGLRENDERER_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
// This class is exported from the KOGLRenderer.dll
#if !defined(CKOGLRenderer_H_)
#define CKOGLRenderer_H_

#include "font/font.h"
#include "KOGLParam.h"

/////////////////////////////////////////////////////////////////////////////
// CKOGLRendererApp
// See KOGLRenderer.cpp for the implementation of this class
//

class CKOGLRendererApp : public CWinApp
{
public:
	CKOGLRendererApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKOGLRendererApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CKOGLRendererApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



class CKOGLRenderer : public CKRenderer 
{
private:
	
public:
	CKOGLRenderer(CKScene *Scene);
	~CKOGLRenderer();

	// General
	CString GetRendererName();
	HWND CreateConfigWindow(HWND Parent);

	// API Init
	void EndRender();
	void BeginRender();
	void Render();
	void RenderOne(int ViewNb);

	void InitContext(HWND window);
	void DeleteContext();

	// drawing
	void DrawHandles(CKHandles Handles,int ActiveView,Vertex HandMin,Vertex HandMax);
	void Project(Vertex * vt, Vertex * dst, int ViewInd);
	void Project(int ViewNb,float x,float y,float z,double &dx,double &dy,double &dz);

	void DirectRender(Vertex *Verts,UVCoords *UVs,int *Indices,DWORD RenderType,int iNbIndex,float R,float G,float B,float A);

	Vertex GetIsoCoord(int X, int Y,int ViewInd);
	Vertex GetIsoCoord(int X, int Y,int ViewInd,Vertex Prj);
	Vertex GetIsoCoord(MYPOINT pt,int ViewInd);
	void DrawHandles(CKHandles *Handles,int ActiveView,Vertex &HandMin,Vertex &HandMax);

	void SetCamera(CKCamera *pCam);

	bool LoadTexture(CString FileName,void *TexID,int &SizeX,int &SizeY);
	void BindTexture(void *TexID);
	void FreeTexture(void *TexID);
	void DrawMesh(CKMesh * daO,int daState,int FrameInd);

private:
	void ExtractFrustum();
	int CubeInFrustum( Vertex &Src, Vertex &Size );
	void DrawGrid(int ViewInd);
	void DrawScene(int daState,int WichOne);
	void BuildGrid(Vertex Snap, Vertex Start);
	void DrawView(Vertex & pos, Vertex & ng, Vertex & daViewSize,POINT scStart, POINT scEnd,int Indice);
	void DrawUV(Vertex & pos, Vertex & ng, Vertex & daViewSize,POINT scStart, POINT scEnd,int Indice);
	void DrawInfos(int Indice);
	void SwapActive(void);
	void FlushIt(void);
	void DrawViewCamera(Vertex & pos, Vertex & ng, Vertex & ViewSize,POINT scStart, POINT scEnd,int Indice);
	void DrawViewFull(CKCamera *daCam);
	void DrawCamera(CKCamera * daCam);
	void DrawShape(CKShape * daS);
	void DrawSelection(void);
	void DrawMeshPolyWire(CKMesh * daO);
	void DrawMeshPolyWireDot(CKMesh * daO);
	void DrawMeshPolyFlatShaded(CKMesh * daO);
	void DrawMeshPolyMapped(CKMesh * daO);
	void DrawMeshPolyMappedOutLined(CKMesh * daO);
	void DrawBone(Vertex Node,CKBone *daBone,bool IsDot,bool IsRoot);
	void DrawSkeleton(CKSkeleton *daSkel);
	void DrawPatch(CKPatch *pPatch,int State);
	void DrawSkyBox(CKSkyBox *pSB,CKCamera *pCamera, unsigned int iFOV, float fAspect);
	
	CDC *m_pCDC;
	HGLRC m_hRC;
	font_t *font;
	float frustum[6][4];
	float aspect;
	GLuint grid;

	int Primitive;

	// Matrices

	int viewport[4][4];
    double mvmatrix[4][16],projmatrix[4][16];

	// Parameters window
	CKOGLParam Params;

};

#endif