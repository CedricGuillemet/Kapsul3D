// KPatch.h: interface for the CKPatch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KPATCH_H__2FE7CF23_E950_4223_A5AE_CE9819DB7531__INCLUDED_)
#define AFX_KPATCH_H__2FE7CF23_E950_4223_A5AE_CE9819DB7531__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class __declspec( dllexport ) CKPatch  
{
public:
	int Unique;
	Vertex *pv;
    UVCoords* puv;
	int nb2patch;
	int *CtrlsPt;
	int nb2vert,nb2pt;
	int Tesselate;
	Vertex *pts;
	unsigned int **strips;
	Desk *dk;
	CKPatch *Prev,*Next;
    CTexture *Tex1;
    char *TexName1;
public:
	void IsBoxed(int nbPatchX,int nbPatchY,Vertex Start,Vertex Fact);
	CKPatch(Desk *_dk,CKPatch *daPrev,CKPatch *daNext);
	virtual ~CKPatch();
	bool Allocate(int nb2p, int nb2v);
	inline float Get(int base, int i, float t);
	inline float GetDeriv(int base, int i, float t);
	void Reset(void);
	void Build(int newSteps);
	void Draw(int State);

};

#endif // !defined(AFX_KPATCH_H__2FE7CF23_E950_4223_A5AE_CE9819DB7531__INCLUDED_)
