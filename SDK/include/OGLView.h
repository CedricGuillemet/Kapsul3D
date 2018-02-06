//---------------------------------------------------------------------------
#ifndef OGLViewH
#define OGLViewH

#include "Kapsul3D.h"

class __declspec( dllexport ) OGLView
{

    public:


    //OGLView(int daWidth,int daHeight,void *daDesk);
	OGLView();

    ~OGLView();
    void  DrawIt(void);
    void  ReSize(int daWidth,int daHeight);
    void  DrawScene(int daState,int WichOne);
    void  DrawViewFull(Camera *daCam);

    
	Desk *dk;
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
    void  DrawCamera(Camera * daCam);
    void  DrawBox(void);
    void  Proj(Vertex * vt, Vertex * dst, int ViewInd);
    void  DrawShape(Shape * daS);
    void  DrawObject(Object * daO,int daState,int FrameInd);    
    void  DrawObjectPolyWire(Object * daO);
    void  DrawObjectPolyMapped(Object * daO);
    // desk to draw
    
    void  SetDesk(void * daDk);
    char *  GetName(int ViewInd);
    void  DrawSelection(void);
    //void  DrawEmit(Emitter *daEmit);
    void  DrawSkeletton(Skeletton *daSkel);
    void  DrawBone(Vertex Node,Bone *daBone,bool IsDot,bool IsRoot);
	void  DrawLight(Light *daLight,Vertex & daViewSize,int ViewInd);
	void  DrawGrid(int ViewInd);
	void  DrawAxis(int ViewInd);

    bool DrawTicks;
    int Primitive;

	GenericLib *gen;

	font_t *font;

	void PreCalc(void);
};

#endif
 