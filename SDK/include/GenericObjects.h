// GenericObjects.h: interface for the CGenericObjects class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENERICOBJECTS_H__CC8C1E10_4A50_4F34_B000_6C5DCB804B73__INCLUDED_)
#define AFX_GENERICOBJECTS_H__CC8C1E10_4A50_4F34_B000_6C5DCB804B73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class __declspec( dllexport ) CGenericObjects  
{
public:
	CGenericObjects();
	virtual ~CGenericObjects();
	
	Vertex VecX,VecY,VecZ;
	double Valu,Valv;


	void CreateGrid(Object *Obj,Vertex Center,double sx,double sy,int nbgx,int nbgy);
	void CreateCube(Object *Obj,Vertex Start,double X,double Y,double Z);
	bool CreateTorus(Object *Obj,Vertex Center,double Radius1,double Radius2,int nb2sec1,int nb2sec2,double OriginNg);
	bool CreateHemis(Object *Obj,Vertex Center,double radius1,int nb2sec,double OriginNg);
	bool CreateCyl(Object *Obj,Vertex Center,double radius1,double height,int nb2sec2,int nb2sec,double OriginNg);
	bool CreateTube(Object *Obj,Vertex Center,double radius1,double radius2,double height,int nb2sec2,int nb2sec,double OriginNg);
	bool CreateSphere(Object *Obj,Vertex center,double radius,int nb2sec,double OriginNg);
	bool CreateCone(Object *Obj,Vertex Center, double Radius1, double Radius2,double Height, int nb2sec2, int nb2sec1,double OriginNg);
};

#endif // !defined(AFX_GENERICOBJECTS_H__CC8C1E10_4A50_4F34_B000_6C5DCB804B73__INCLUDED_)
