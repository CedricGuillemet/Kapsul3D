//---------------------------------------------------------------------------
#ifndef LightH
#define LightH

#include "Kapsul3D.h"

class __declspec(dllexport) CLight : public CKEntity
{
    public:
	    void PrecalcSpot(void);
        CLight();
        ~CLight();

    CLight *Next,*Prev;
	unsigned int Unique;

	bool Hided;

	Vertex Source,Target;

    bool SourceSelected,TargetSelected,Selected;

    int Type; // 0:omni,1:spot
    int SpotType; //Rectangular,circular

	float Radius;
    float Radius2;

    float tanRad1;
    float tanRad2;

	CString Name;

    float TopWidth;
    float TopHeight;

    float BottomWidth;
    float BottomHeight;

	unsigned char r,g,b;

	unsigned char	Brightness;
    float Length;

	void DrawOmni(Vertex & daViewSize,int ViewInd,int Primitive);
	void DrawSpot(Vertex & daViewSize,int ViewInd,int Primitive);
	void DrawNeon(Vertex & daViewSize,int ViewInd,int Primitive);
	void DrawColorQuad(int ViewInd);

    void operator =(CLight *cmpt);

	CKRenderer *m_Renderer;
	Vertex GetMaxOf(void);
	Vertex GetMinOf(void);
	void Draw(CKRenderer *pRender,Vertex & daViewSize,int ViewInd,int Primitive);
	void IsCopyOf(CLight *cmpt);
	//bool SelectLight(CKScene *pScene,CKDrawScene *pDrawScene,int dx,int dy,int X,int Y,CKShape *daSh,bool AddIt,bool Crossing,int TypeSel,int WholeSelect);

};
//---------------------------------------------------------------------------
#endif
 