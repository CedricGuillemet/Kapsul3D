//---------------------------------------------------------------------------
#ifndef LightH
#define LightH

#include "Kapsul3D.h"

class __declspec( dllexport ) CLight
{
    public:
	    void PrecalcSpot(void);
        CLight(CLight *daPrev=NULL,CLight *daNext=NULL);
        ~CLight();

    CLight *Next,*Prev;
	unsigned int Unique;

	bool Hided;

	Vertex Source,Target;

    bool SourceSelected,TargetSelected,Selected;

    int Type; // 0:omni,1:spot
    int SpotType; //Rectangular,circular

	double Radius;
    double Radius2;

    double tanRad1;
    double tanRad2;

	char *Name;

    double TopWidth;
    double TopHeight;

    double BottomWidth;
    double BottomHeight;

	unsigned char r,g,b;

	unsigned char	Brightness;
    double Length;

	void DrawOmni(Vertex & daViewSize,int ViewInd,int Primitive);
	void DrawSpot(Vertex & daViewSize,int ViewInd,int Primitive);
	void DrawNeon(Vertex & daViewSize,int ViewInd,int Primitive);

    void operator =(CLight *cmpt);

	Vertex GetMaxOf(void);
	Vertex GetMinOf(void);
	void Draw(Vertex & daViewSize,int ViewInd,int Primitive);
	void IsCopyOf(CLight *cmpt);
};
//---------------------------------------------------------------------------
#endif
 