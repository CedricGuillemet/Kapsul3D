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
#include "CSG.h"

//-----------------------------------------------------------------------------
// Typedef Structures
//-----------------------------------------------------------------------------
typedef struct tagPLANE
{
	D3DXVECTOR3 PointOnPlane;				// Point On Plane
	D3DXVECTOR3 Normal;						// Plane Normal
} PLANE;

typedef struct BSPPOLYGON					// BSP Polygon (Typecast Safe with POLYGON)
{
	D3DVERTEX*	Vertices;					// Actual Vertex Data
	WORD*		Indices;					// Actual Indices for this poly
	WORD		VertexCount;				// Number Of Vertices
	WORD		IndexCount;					// Number of Indices
	D3DXVECTOR3	Normal;						// Faces Normal
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
// Name : CBSPTree ()
// Desc : BSP Class used for compilation, clipping / rendering the trees
//-----------------------------------------------------------------------------
class CBSPTree 
{
public:
				CBSPTree();
				~CBSPTree();
	//------------------------------
	//     Function Prototypes 
	//------------------------------
	BOOL		ClipTree( long CurrentNode, long *Polygons, long pPolyCount, CBSPTree *BSPTree, BOOL ClipSolid, BOOL RemoveCoPlanar);
	void		InitPolygons( Object *brush, long BrushCount, BOOL BSPCollect );
	void		RenderBSPPolys( int BrushIndex );
	void		InvertPolys();
	void		Commit( Object *Obj );
	void		CommitAddTo( Object *Obj );

	BSPPOLYGON	*AddPolygonEX( BSPPOLYGON*Poly );
	CBSPTree	*CopyTree();

	//------------------------------
	//      Public Variables
	//------------------------------
	BSPPOLYGON*		Polygons;					// Actual Polygon Data
	BOOL			FatalError;					// Did a fatal error occur ??
	BOOL*			PolygonDeleted;				// Temp Storage to check for Deleted Polys
	BRUSH*			BrushBase;					// Which brush this is attatched to.
	long			PolyCount;					// Number Of polygons
	long			RootNode;					// Index to the Root Node.
	BSPPOLYGON		*PolygonList;				// Entry linked list poly.
	PLANE*			Planes;						// Node's Plane Data
	NODE*			Nodes;						// Tree Nodes
	LEAF*			Leaves;						// Tree's Leaves
	long			NodeCount;					// Number Of Nodes
	long			PlaneCount;					// Number Of Planes
	long			LeafCount;					// Number Of Leaves

	BOOL			IsDirty;					// Has the BSP been modified since it was built ?
	BOOL			m_bMisc;					// Miscellaneous bool we can use for many things

private:
	//------------------------------
	//     Function Prototypes 
	//------------------------------
	
	
	BOOL		Get_Intersect( D3DXVECTOR3 *linestart, D3DXVECTOR3 *lineend, D3DXVECTOR3 *vertex, D3DXVECTOR3 *normal, D3DXVECTOR3 * intersection, float *percentage );
	void		SplitPolygon(BSPPOLYGON *Poly,PLANE *Plane,BSPPOLYGON *FrontSplit,BSPPOLYGON *BackSplit);
	long		SelectBestSplitter( BSPPOLYGON *PolyList, long CurrentNode );
	void		BuildBSPTree( long CurrentNode, BSPPOLYGON *PolyList );
	
	int			ClassifyPoly( PLANE *Plane, BSPPOLYGON * Poly );
	int			ClassifyPoint( D3DXVECTOR3 *pos, PLANE *Plane ) ;
	int			AllocAddPlane( );
	int			AllocAddPoly( );
	int			AllocAddNode( );
	int			AllocAddLeaf( );
	void		KillTree();
	void		KillPolys();

	BSPPOLYGON	*AddPolygonSplit (BSPPOLYGON *Parent, POLYGON    *Face );
	BSPPOLYGON	*AddPolygon(BSPPOLYGON *Parent, KPolygon *Face,Object *Owner );
	BSPPOLYGON  *AddBSPPolygon   (BSPPOLYGON *Parent, BSPPOLYGON *Poly );

};

#endif //_BSPTREE_H_