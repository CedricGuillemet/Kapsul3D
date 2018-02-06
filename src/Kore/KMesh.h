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

#ifndef CKMeshH
#define CKMeshH

class TessVertex : public Vertex
{
public:
	TessVertex() {};
	~TessVertex() {};

	float u,v;

	inline void operator =(TessVertex cmpt);
};

inline void TessVertex::operator =(TessVertex cmpt)
{
    x=cmpt.x;
    y=cmpt.y;
    z=cmpt.z;

}

class KAPSUL_DESC CKMesh : public CKObjectBase
{
    private:
        // style
        int     Style;
		bool NeedTexRecalc;
    public:

	

	
	void CalcTexCoord(int tsx,int tsy,Vertex Origin,double uvu,double uvv);
	void UpdateMesh(void);

    CKMesh(CKScene *dk,CKMesh *daPrev,CKMesh *daNext);
	CKMesh::CKMesh();
    ~CKMesh();

	CKSkeleton *Skel; //associated skeletton
    // ajout

    void    AddCKMesh(Vertex *daDot);

    int nb2vert;
    int nb2poly;
    Vertex* pv;
    CKPolygon* pl;
	int *pi;

    CKMesh   *Next;
    CKMesh   *Prev;


    //Material *Mat;


    // Material properties
    CString MaterialName;

    CKTexture *Tex1;
    //char *TexName1;
    CKTexture *Tex2;
    //char *TexName2;
    CKTexture *Tex3;
    //char *TexName3;
    CKTexture *Tex4;
    //char *TexName4;

	void ApplyTexture(CKTexture *daTex,int TexNb=0);
	void GenerateUVPerFace(int CanalNb);
	void SetAutoTexRecalc(bool _autouv);
	bool GetAutoTexRecalc(void) { return NeedTexRecalc; };


    UVCoords* puv[4];
    int nbTexCanals;
    int nbTexCoords[4];
    //bool AllocateUV(int Canal, int nb2uv);
    bool AllocatePoly(int nb2p, int nb2v);
    // Frames
    int nb2Frames;
    int FrameInd;

    void SetNbFrames(int _nbFrames);
    void SetFrameInd(int _FrameInd);

    
    // Matricies
    CKMatrix *matrix;

    // states
    //bool Modified;

	// Plans
	void CalcAllPlanes(void);
	bool IsConvexe(void);
	void RebuildPoly(void);

    // Methods
//    void Compute(void);
	void Translate(Vertex TransVal);

	inline int GetIntPtrPoly(int iSize);

	// bsp
	CKBSPTree *BSPTree;

	
    int DelSelectedFaces(void);
    int DelSelectedVertex(void);
    int DelUnusedVertex(void);
    void SelectedFaceToScene(CKScene *DstDk);
	
	void CollapseIdenticalVertex(void);
    //void operator =(CKMesh *cmpt);
	void IsCopyOf(CKMesh *cmpt);
	int FindPoly(int i1,int i2,CKPolygon *Else);
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
	//unsigned int *Indices;
	//unsigned int nbIndices;
	//UVCoords *TexInd[4];
	//GLColor *Ocl,*Oclp;

	//void OptimGeom(void);

	// properties
	//unsigned long Property1;
	//int Oldindices;
	//void GeomIsDirty(void);

	// Min Max BB
	void GetMinMax(void);


	// prefabs
	CString PrefabName;
	CTime PrefabDate;
	void Lathing(CKShape *Shp,int NbTours,double U,double V);

	int FindEdge(int VtInd1,int VtInd2,int FromPoly,int &PolyNb,int &EdgeNb);
	void Extrud(Vertex daVect,float Size,int nbSteps,float Scale,bool bCapping);
	void InitAllPolyTag(unsigned int val);
	void MergeMesh(CKMesh *msh);
	void Explode(CKScene *Dest,float Decal);

	// subdivide

	//private int triangleCount = 0;

	// the table that holds the coordinates for all the vertices
	//private ArrayList vertexTable = new ArrayList();
	vector<TessVertex> vertexTable;

	// the table that holds the corners of all the triangle
	// all consective 3 element in this table represents a 
	// triangle
	//private ArrayList cornerTable = new ArrayList();
	vector<int> cornerTable;

	// the table that holds the opposite corner of another corner
	//private ArrayList oppositeTable = new ArrayList();
	vector<int> oppositeTable;

	// the table that holds the midpoints for any two corners 
	// calculated by the butterfly subdivision equation
	//private ArrayList midpointTable = new ArrayList();
	vector<int> midpointTable;

	// this table holds the boolean value for whether a 
	// corner has been visited
	//private ArrayList flagTable = new ArrayList();
	vector<bool> flagTable;

	// the table holds new corners after a pass of subdivision
	//private ArrayList newCornerTable = new ArrayList();
	vector<int> newCornerTable;

	int triangleCount;
	// -- 

	void buildOppositeTable();
	void buildMidpointTable();
	void buildFlagTable();
	void buildNewCornerTable();
	void SubDivide(int nTime);

	inline int numOfVertex();
	inline int numOfCorner();
	inline int midpointOfCorner(int index);
	inline bool flagOfCorner(int index);
	inline int rightOfCorner(int index); 
	inline int leftOfCorner(int index);
	inline int oppositeOfCorner(int index);
	inline int triangleOfCorner(int index);
	inline int nextOfCorner(int index);
	inline int prevOfCorner(int index);
	inline TessVertex vertexOfCorner(int index);


	void SplitSelectedPolyToTri(bool AllPolys=false);
	void DivideTriBy3(void);
	void DivideTriBy4(void);

};
//---------------------------------------------------------------------------
#endif
