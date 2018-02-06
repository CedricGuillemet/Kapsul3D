//---------------------------------------------------------------------------
#include "stdafx.h"

//#include "memmgr/mmgr.h"
/*
#include "CKPlan.h"

#include "Maths.h"
*/

CKPlan::CKPlan()
{
	MatRot=new double [9];
	MatRot2=new double [16];
	daMatRot2=new double [16];
}

CKPlan::~CKPlan()
{
	delete [] MatRot;
	delete [] MatRot2;
	delete [] daMatRot2;
}

void CKPlan::PlanOfView(CKRenderer *Renderer,int ViewInd)
{
    //Math Maths;
    pX=Renderer->GetIsoCoord(1,0,ViewInd)-Renderer->GetIsoCoord(0,0,ViewInd);
    pY=Renderer->GetIsoCoord(0,1,ViewInd)-Renderer->GetIsoCoord(0,0,ViewInd);
    pZ=CrossProduct(&pX,&pY);
    pZ.Normalize();
	m_Renderer=Renderer;
}

Vertex CKPlan::GetAbs(int X,int Y,int Z)
{
    Vertex value,tmp;
    value.x=X*pX.x+Y*pY.x;
    value.y=X*pX.y+Y*pY.y;
    value.z=X*pX.z+Y*pY.z;

    tmp=pZ;
    tmp.x*=Z;
	tmp.y*=Z;
	tmp.z*=Z;

    value+=tmp;

    return value;

}

void CKPlan::MatrixRotateNormale(double a)
{
    MatRot[0]=(pZ.x*pZ.x)+((1-(pZ.x*pZ.x))*cos(a));
    MatRot[1]=((pZ.x*pZ.y)*(1-cos(a)))-pZ.z*sin(a);
    MatRot[2]=((pZ.x*pZ.z)*(1-cos(a)))+(pZ.y*sin(a));

    MatRot[3]=((pZ.x*pZ.y)*(1-cos(a)))+(pZ.z*sin(a));
    MatRot[4]=(pZ.y*pZ.y)+((1-(pZ.y*pZ.y))*cos(a));
    MatRot[5]=((pZ.y*pZ.z)*(1-cos(a)))-pZ.x*sin(a);

    MatRot[6]=((pZ.x*pZ.z)*(1-cos(a)))-(pZ.y*sin(a));
    MatRot[7]=((pZ.y*pZ.z)*(1-cos(a)))+(pZ.x*sin(a));
    MatRot[8]=(pZ.z*pZ.z)+((1-(pZ.z*pZ.z))*cos(a));
}

void CKPlan::ScaleMatrix(bool Normalize)
{
	if (Normalize)
	{
		pX.Normalize();
		pY.Normalize();
		pZ.Normalize();
	}

    MatRot2[0]=pX.x;
    MatRot2[1]=pY.x;
    MatRot2[2]=pZ.x;
	MatRot2[3]=0;

    MatRot2[4]=pX.y;
    MatRot2[5]=pY.y;
    MatRot2[6]=pZ.y;
	MatRot2[7]=0;

    MatRot2[8]=pX.z;
    MatRot2[9]=pY.z;
    MatRot2[10]=pZ.z;
	MatRot2[11]=0;

    MatRot2[12]=0;
    MatRot2[13]=0;
    MatRot2[14]=0;
	MatRot2[15]=1;

	InvertMatrix(MatRot2,daMatRot2);
}

Vertex CKPlan::Rotate(Vertex daVal)
{
    Vertex value;

    value.x=daVal.x*MatRot[0]+daVal.y*MatRot[1]+daVal.z*MatRot[2];
    value.y=daVal.x*MatRot[3]+daVal.y*MatRot[4]+daVal.z*MatRot[5];
    value.z=daVal.x*MatRot[6]+daVal.y*MatRot[7]+daVal.z*MatRot[8];

    return value;
}

Vertex CKPlan::Scale(Vertex daVal,Vertex ScaleVal)
{
    Vertex value,value2;

    value.x=daVal.x*daMatRot2[0]+daVal.y*daMatRot2[1]+daVal.z*daMatRot2[2];
    value.y=daVal.x*daMatRot2[4]+daVal.y*daMatRot2[5]+daVal.z*daMatRot2[6];
    value.z=daVal.x*daMatRot2[8]+daVal.y*daMatRot2[9]+daVal.z*daMatRot2[10];

	value.x*=ScaleVal.x;
	value.y*=ScaleVal.y;
	value.z*=ScaleVal.z;

    value2.x=value.x*MatRot2[0]+value.y*MatRot2[1]+value.z*MatRot2[2];
    value2.y=value.x*MatRot2[4]+value.y*MatRot2[5]+value.z*MatRot2[6];
    value2.z=value.x*MatRot2[8]+value.y*MatRot2[9]+value.z*MatRot2[10];

    return value2;
}

Vertex CKPlan::Translate(Vertex daVal,Vertex TransVal)
{
    Vertex value,value2;

    value.x=daVal.x*daMatRot2[0]+daVal.y*daMatRot2[1]+daVal.z*daMatRot2[2];
    value.y=daVal.x*daMatRot2[4]+daVal.y*daMatRot2[5]+daVal.z*daMatRot2[6];
    value.z=daVal.x*daMatRot2[8]+daVal.y*daMatRot2[9]+daVal.z*daMatRot2[10];

	value.x+=TransVal.x;
	value.y+=TransVal.y;
	value.z+=TransVal.z;

    value2.x=value.x*MatRot2[0]+value.y*MatRot2[1]+value.z*MatRot2[2];
    value2.y=value.x*MatRot2[4]+value.y*MatRot2[5]+value.z*MatRot2[6];
    value2.z=value.x*MatRot2[8]+value.y*MatRot2[9]+value.z*MatRot2[10];

    return value2;
}
//---------------------------------------------------------------------------

