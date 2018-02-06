// KPatch.h: interface for the CKPatch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KPATCH_H__2FE7CF23_E950_4223_A5AE_CE9819DB7531__INCLUDED_)
#define AFX_KPATCH_H__2FE7CF23_E950_4223_A5AE_CE9819DB7531__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class KAPSUL_DESC CKPatch : public CKObjectBase
{
public:

	Vertex *pv;
    UVCoords** puv;
	int nb2patch;
	int *CtrlsPt;
	int nb2vert,nb2pt;
	int Tesselate;
	Vertex *pts;
	unsigned int **strips;

	CKPatch *Prev,*Next;
    CKTexture *Tex1,*Tex2,*Tex3,*Tex4;

	int nbTexCanals;
	int nbTexCoords[4];

public:
	void IsBoxed(int nbPatchX,int nbPatchY,Vertex Start,Vertex Fact);
	void IsPlanar(int nbPatchX, int nbPatchY,Vertex Start,Vertex pSize,Vertex pX,Vertex pY,double U,double V);
	CKPatch(CKScene *pScene,CKPatch *daPrev,CKPatch *daNext);
	CKPatch();
	virtual ~CKPatch();
	bool Allocate(int nb2p, int nb2v);
	inline float Get(int base, int i, float t);
	inline float GetDeriv(int base, int i, float t);
	void Reset(void);
	void Build(int newSteps);
	void IsCopyOf(CKPatch *dap);
	bool AllocateUV(int Canal, int nb2uv);
	void ComputeTexCoords(int CanalNb,double U,double V,int nbpX,int nbpY);
	void GetMinMax(void);
	void ApplyTexture(CKTexture *daTex,int TexNb=0);
	void Update(void);


};

#endif // !defined(AFX_KPATCH_H__2FE7CF23_E950_4223_A5AE_CE9819DB7531__INCLUDED_)
