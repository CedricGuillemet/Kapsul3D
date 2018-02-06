//---------------------------------------------------------------------------
#ifndef PlanH
#define PlanH

//#include "OGLView.h"
#include "Kapsul3D.h"

class __declspec( dllexport ) Plan
{
    public:

    Plan();
    ~Plan();

    Vertex pX,pY,pZ;
    double *MatRot;
	double *MatRot2,*daMatRot2;

    void PlanOfView(OGLView *View,int ViewInd);
    Vertex GetAbs(int X,int Y,int Z);
    void MatrixRotateNormale(double a);
    Vertex Rotate(Vertex daVal);
	Vertex Scale(Vertex daVal,Vertex ScaleVal);
	void ScaleMatrix();
    Vertex Translate(Vertex daVal,Vertex TransVal);
};
//---------------------------------------------------------------------------
#endif
