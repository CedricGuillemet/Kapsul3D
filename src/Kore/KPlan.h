//---------------------------------------------------------------------------
#ifndef PlanH
#define PlanH

//#include "OGLView.h"
#include "Kapsul3D.h"

class KAPSUL_DESC CKPlan
{
    public:

    CKPlan();
    ~CKPlan();

    Vertex pX,pY,pZ;
    double *MatRot;
	double *MatRot2,*daMatRot2;
	CKRenderer *m_Renderer;

    void PlanOfView(CKRenderer *Renderer,int ViewInd);
    Vertex GetAbs(int X,int Y,int Z);
    void MatrixRotateNormale(double a);
    Vertex Rotate(Vertex daVal);
	Vertex Scale(Vertex daVal,Vertex ScaleVal);
	void ScaleMatrix(bool Normalize=true);
    Vertex Translate(Vertex daVal,Vertex TransVal);
};
//---------------------------------------------------------------------------
#endif
