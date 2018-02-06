//-----------------------------------------------------------------------------
// File: BSPTree.H
//
// Desc: BSP Tree Compilation / Renderer
//
// Copyright (c) 2000-2001. Adam Hoult & Gary Simmons. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef _BSPTREE_H_
#define _BSPTREE_H_

//-----------------------------------------------------------------------------
// App Specific Includes
//-----------------------------------------------------------------------------
//#include "CSG.h"
const FLOAT g_PI       =  3.14159265358979323846f; // Pi
const FLOAT g_DEGTORAD =  0.01745329251994329547f; // Degrees to Radians
const FLOAT g_EPSILON  =  0.001f;				   // Float Tolerance

//-----------------------------------------------------------------------------
// Typedef Structures
//-----------------------------------------------------------------------------
typedef struct tagPLANE
{
	Vertex PointOnPlane;				// Point On Plane
	Vertex Normal;						// Plane Normal
} PLANE;

typedef struct BSPPOLYGON					// BSP Polygon (Typecast Safe with POLYGON)
{
	Vertex*	Vertices;					// Actual Vertex Data
	WORD*		Indices;					// Actual Indices for this poly
	WORD		VertexCount;				// Number Of Vertices
	WORD		IndexCount;					// Number of Indices
	Vertex	Normal;						// Faces Normal
	int			TextureIndex;				// Stores the texture index.
	BSPPOLYGON*	NextPoly;					// Linked List to next poly in chain.
	BYTE		UsedAsSplitter;				// Has this poly already been used
} BSPPOLYGON;

typedef struct
{
	long		StartPoly;					// Indices into polygon array
	long		EndPoly;					// End Amount of poly's to read
} LEAF;

typedef struct
{
	BYTE		IsLeaf;						// Does this node point to a leaf ??
	long		Plane;						// Index into Plane Array
	long		Front;						// Front Child (Another node or leaf if IsLeaf = 1)
	long		Back;						// Back Child (Node Only, will be -1 if NULL)
} NODE;


//-----------------------------------------------------------------------------
// Constants (Various constants for BSP Compilation / rendering )
//-----------------------------------------------------------------------------
#define			CP_FRONT			1		// In Front of Plane
#define			CP_BACK				2		// Behind Plane
#define			CP_ONPLANE			3		// Co Planar
#define			CP_SPANNING			4		// Spanning the plane

//-----------------------------------------------------------------------------
// Name : CKBSPTree ()
// Desc : BSP Class used for compilation, clipping / rendering the trees
//-----------------------------------------------------------------------------
class KAPSUL_DESC CKBSPTree 
{
public:
				CKBSPTree();
				~CKBSPTree();
	//------------------------------
	//     Function Prototypes 
	//------------------------------
	bool		ClipTree( long CurrentNode, long *Polygons, long pPolyCount, CKBSPTree *BSPTree, bool ClipSolid, bool RemoveCoPlanar);
	void		InitPolygons( CKMesh *brush, long BrushCount, bool BSPCollect );
	void		RenderBSPPolys( int BrushIndex );
	void		InvertPolys();
	void		Commit( CKMesh *Obj );
	void		CommitAddTo( CKMesh *Obj );

	BSPPOLYGON	*AddPolygonEX( BSPPOLYGON*Poly );
	CKBSPTree	*CopyTree();

	//------------------------------
	//      Public Variables
	//------------------------------
	BSPPOLYGON*		Polygons;					// Actual Polygon Data
	bool			FatalError;					// Did a fatal error occur ??
	bool*			PolygonDeleted;				// Temp Storage to check for Deleted Polys
//	BRUSH*			BrushBase;					// Which brush this is attatched to.
	long			PolyCount;					// Number Of polygons
	long			RootNode;					// Index to the Root Node.
	BSPPOLYGON		*PolygonList;				// Entry linked list poly.
	PLANE*			Planes;						// Node's Plane Data
	NODE*			Nodes;						// Tree Nodes
	LEAF*			Leaves;						// Tree's Leaves
	long			NodeCount;					// Number Of Nodes
	long			PlaneCount;					// Number Of Planes
	long			LeafCount;					// Number Of Leaves

	bool			IsDirty;					// Has the BSP been modified since it was built ?
	bool			m_bMisc;					// Miscellaneous bool we can use for many things

private:
	//------------------------------
	//     Function Prototypes 
	//------------------------------
	
	
	bool		Get_Intersect( Vertex *linestart, Vertex *lineend, Vertex *vertex, Vertex *normal, Vertex * intersection, float *percentage );
	void		SplitPolygon(BSPPOLYGON *Poly,PLANE *Plane,BSPPOLYGON *FrontSplit,BSPPOLYGON *BackSplit);
	long		SelectBestSplitter( BSPPOLYGON *PolyList, long CurrentNode );
	void		BuildBSPTree( long CurrentNode, BSPPOLYGON *PolyList );
	
	int			ClassifyPoly( PLANE *Plane, BSPPOLYGON * Poly );
	int			ClassifyPoint( Vertex *pos, PLANE *Plane ) ;
	int			AllocAddPlane( );
	int			AllocAddPoly( );
	int			AllocAddNode( );
	int			AllocAddLeaf( );
	void		KillTree();
	void		KillPolys();

	//BSPPOLYGON	*AddPolygonSplit (BSPPOLYGON *Parent, POLYGON    *Face );
	BSPPOLYGON	*AddPolygon(BSPPOLYGON *Parent, CKPolygon *Face,CKMesh *Owner );
	BSPPOLYGON  *AddBSPPolygon   (BSPPOLYGON *Parent, BSPPOLYGON *Poly );

};

#endif //_BSPTREE_H_