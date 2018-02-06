// GenericCKMeshs.h: interface for the CKGenericMesh class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENERICOBJECTS_H__CC8C1E10_4A50_4F34_B000_6C5DCB804B73__INCLUDED_)
#define AFX_GENERICOBJECTS_H__CC8C1E10_4A50_4F34_B000_6C5DCB804B73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class KAPSUL_DESC CKGenericMesh  
{
public:
	CKGenericMesh();
	virtual ~CKGenericMesh();
	
	Vertex VecX,VecY,VecZ;
	double Valu,Valv;
	bool	AutoUV;

	int First;//First Indice


	void CreateGrid(CKMesh *Obj,Vertex Center,double &sx,double &sy,int nbgx,int nbgy);
	void Create3DGrid(CKMesh *Obj,Vertex Center,double &sx,double &sy,double &sz,int nbgx,int nbgy,int nbgz);
	void CreateStairs(CKMesh *Obj,Vertex Center,double sx,double sy,double sz,int nbstairs);
	void CreateStairsSimple(CKMesh *Obj,Vertex Center,double sx,double sy,double sz,int nbstairs);
	void CreateCube(CKMesh *Obj,Vertex Start,double X,double Y,double Z);
	bool CreateTorus(CKMesh *Obj,Vertex Center,double Radius1,double Radius2,int nb2sec1,int nb2sec2,double OriginNg);
	bool CreateHemis(CKMesh *Obj,Vertex Center,double radius1,int nb2sec,double OriginNg);
	bool CreateCyl(CKMesh *Obj,Vertex Center,double &radius1,double &height,int nb2sec2,int nb2sec,double OriginNg);
	bool CreateTube(CKMesh *Obj,Vertex Center,double radius1,double radius2,double &height,int nb2sec2,int nb2sec,double OriginNg);
	bool CreateSphere(CKMesh *Obj,Vertex center,double radius,int nb2sec,double OriginNg);
	bool CreateCone(CKMesh *Obj,Vertex Center, double Radius1, double Radius2,double &height, int nb2sec2, int nb2sec1,double OriginNg);
};

#endif // !defined(AFX_GENERICOBJECTS_H__CC8C1E10_4A50_4F34_B000_6C5DCB804B73__INCLUDED_)
