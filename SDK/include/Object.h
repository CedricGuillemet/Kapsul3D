// Kapsul Core Library
// Copyright © 1999 - 2001, Cédric Guillemet
//
// Contact: lacrapul@club-internet.fr
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef ObjectH
#define ObjectH

#include "Headers.h"


class __declspec( dllexport ) Object
{
    private:
        // style
        int     Style;
        void    DoAdd();
    public:

	int Tag;

    Object(Desk *dk,Object *daPrev,Object *daNext);
	Object::Object();
    ~Object();
    // ajout

    void    AddObject(Vertex *daDot);

    //bool Allocate(int nb2f, int nb2v);

    int nb2vert;
    //int nb2faces;
    int nb2poly;
    //Face* pf;
    Vertex* pv;
    KPolygon* pl;
    char *Name;

    Object   *Next;
    Object   *Prev;


    //Material *Mat;


    // Material properties
    char *MaterialName;

    CTexture *Tex1;
    char *TexName1;
    CTexture *Tex2;
    char *TexName2;
    CTexture *Tex3;
    char *TexName3;
    CTexture *Tex4;
    char *TexName4;

    int BlendFunc;
    float BlendFuncValue;


    UVCoords** puv;
    int nbTexCanals;
    int nbTexCoords[4];
    bool AllocateUV(int Canal, int nb2uv);
    bool AllocatePoly(int nb2p, int nb2v);
    void SetAlphaTest(int _AlphaTestFunc,float _AlphaTestValue);
    // Frames
    int nb2Frames;
    int FrameInd;

    void SetNbFrames(int _nbFrames);
    void SetFrameInd(int _FrameInd);

    
    // Matricies
    Matrix *matrix;

    Vertex Min,Max;

    // states
    bool Modified;
    bool Selected;

	// Plans
	void CalcAllPlanes(void);
	bool IsConvexe(void);
	void RebuildPoly(void);

    // Methods
    void Compute(void);
    Vertex GetMinOf(void);
    Vertex GetMaxOf(void);
	void Translate(Vertex TransVal);

	// bsp
	CBSPTree *BSPTree;

	
    int DelSelectedFaces(void);
    int DelSelectedVertex(void);
    int DelUnusedVertex(void);
    void SelectedFaceToDk(Desk *DstDk);
	
	void CollapseIdenticalVertex(void);
    //void operator =(Object *cmpt);
	void IsCopyOf(Object *cmpt);
	int FindPoly(int i1,int i2,KPolygon *Else);
	void TranslateVertex(int Indice,Vertex TransVal);

	// strips
	/*
	bool IsStrip;
	unsigned int **Strips;
	unsigned int *nbStrips;
	unsigned int nbStripping;
	inline void AllocateStrips(int nbStrip)
	{
		IsStrip=true;
		Strips=new unsigned int*[nbStrip];
		nbStrips=new unsigned int[nbStrip];
		nbStripping=nbStrip;
		memset(nbStrips,0,sizeof(unsigned int)*nbStrip);
	}

	inline void AllocateOneStrip(int StripNb,int nbStrip)
	{
		nbStrips[StripNb]=nbStrip;
		Strips[StripNb]=new unsigned int[nbStrip];
	}
*/
	// optim buffer
	unsigned int *Indices;
	unsigned int nbIndices;
	Vertex *Opv;
	UVCoords *TexInd[4];
	bool OptimDirty;
	GLColor *Ocl,*Oclp;

	void OptimGeom(void);

	// Unique identifier
	unsigned int Unique;

	// properties
	unsigned long Property1;
	int Oldindices;
	void GeomIsDirty(void);

	//unsigned long Property2;

};
//---------------------------------------------------------------------------
#endif
