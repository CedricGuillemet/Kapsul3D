//---------------------------------------------------------------------------
#ifndef CKDrawSceneH
#define CKDrawSceneH

#include "Kapsul3D.h"
#include "KHandles.h"



class KAPSUL_DESC CKDrawScene
{

    public:


    //CKDrawScene(int daWidth,int daHeight,void *daDesk);
	CKDrawScene();

    ~CKDrawScene();
    void  DrawIt(void);
    void  ReSize(int daWidth,int daHeight);
    void  DrawScene(int daState,int WichOne);
    void  DrawViewFull(CKCamera *daCam);

    
	CKScene *m_Scene;
	GLfloat aspect;//,Height,Width,Left,Top;

    GLuint grid;
    void  BuildGrid(Vertex Snap, Vertex Start);


    Vertex  GetIsoCoord(int X, int Y,int Viewind,Vertex PrjZ=Vertex(0,0,0));
    Vertex  GetIsoCoord(MYPOINT pt,int ViewInd);

    //int Operate;
    void  DrawView(Vertex & pos, Vertex & ng,Vertex & ViewSize, POINT scStart, POINT scEnd,int Indice);
    void  DrawOne(int ViewInd);
    void  SwapActive(void);
    void  FlushIt(void);
    void  DrawViewCamera(Vertex & pos, Vertex & ng, Vertex & ViewSize,POINT scStart, POINT scEnd,int Indice);
    //Vertex temp;
    void  DrawCamera(CKCamera * daCam);
    void  DrawBox(void);
    void  Proj(Vertex * vt, Vertex * dst, int ViewInd);
    void  DrawShape(CKShape * daS);
    void  DrawMesh(CKMesh * daO,int daState,int FrameInd);    
    void  DrawMeshPolyWire(CKMesh * daO);
    void  DrawMeshPolyMapped(CKMesh * daO);
	void  DrawMeshPolyFlatShaded(CKMesh * daO);
	void  DrawMeshPolyMappedOutLined(CKMesh * daO);
    // desk to draw
    
    void  SetScene(void * daDk);
    CString GetName(int ViewInd);
    void  DrawSelection(void);
    //void  DrawEmit(Emitter *daEmit);
    void  DrawSkeleton(CKSkeleton *daSkel);
    void  DrawBone(Vertex Node,CKBone *daBone,bool IsDot,bool IsRoot);
//	void  DrawLight(Light *daLight,Vertex & daViewSize,int ViewInd);
	void  DrawGrid(int ViewInd);



	void  DrawUV(Vertex & pos, Vertex & ng, Vertex & daViewSize,POINT scStart, POINT scEnd,int Indice);

    bool DrawTicks;
    int Primitive;

	CKPlugin *m_Plugin;

	font_t *font;

	void PreCalc(void);

	

	float frustum[6][4];
	void ExtractFrustum(void);
	int CubeInFrustum( Vertex Src, Vertex Size );

	CString strTop,strFront,strRight,strBottom,strBack,strLeft,strUser;
	void LocalizeNames(void);

	void DrawInfos(int Indice);
	void CalcHandles(int Indice);
	int GetViewType(int ViewInd);
};

#endif
 