//-----------------------------------------------------------------------------
// File: BSPTree.cpp
//
// Desc: BSP Tree Compilation / Rendering etc
//
// Copyright (c) 2000-2001. Adam Hoult & Gary Simmons. All rights reserved.
//-----------------------------------------------------------------------------

#include "stdafx.h"

//-----------------------------------------------------------------------------
// Name : CKBSPTree () (Constructor)
// Desc : Initialises Everything We Need
//-----------------------------------------------------------------------------
CKBSPTree::CKBSPTree()
{
	FatalError		= FALSE;
	Polygons		= NULL;
	Planes			= NULL;
	Nodes			= NULL;
	Leaves			= NULL;
	PolygonDeleted	= NULL;
	RootNode		= -1;
	NodeCount		= 0;
	PolyCount		= 0;
	PlaneCount		= 0;
	LeafCount		= 0;
}

//-----------------------------------------------------------------------------
// Name : ~CKBSPTree () (Destructor)
// Desc : Destroys Everything We No Longer Need
//-----------------------------------------------------------------------------
CKBSPTree::~CKBSPTree()
{
	KillTree();
	KillPolys();
}

//-----------------------------------------------------------------------------
// Name : KillTree ()
// Desc : Destroys Everything We No Longer Need
//-----------------------------------------------------------------------------
void CKBSPTree::KillTree()
{
	
	// Kill The Leaf Data
	if ( Leaves )	
	{ 
		free( Leaves );	
		Leaves		= NULL; 
	}
	// Free the planes
	if ( Planes )	
	{ 
		free( Planes );	
		Planes		= NULL; 
	}
	// Free the Nodes
	if ( Nodes )	
	{ 
		free( Nodes );	
		Nodes		= NULL; 
	}
	
	// Clean Up
	FatalError		= FALSE;
	//BrushBase		= NULL;
	RootNode		= -1;
	NodeCount		= 0;
	PlaneCount		= 0;
	LeafCount		= 0;
}

//-----------------------------------------------------------------------------
// Name : KillPolys ()
// Desc : Destroys the polygons we created in the array.
//-----------------------------------------------------------------------------
void CKBSPTree::KillPolys()
{
	// Kill the polygon data
	if ( Polygons ) { 
		// We need to free up our vertices and indices
		// allocated memory.
		for ( int i = 0; i < PolyCount; i++ ) {
			if ( Polygons[i].Vertices ) 
			{ 
				free(Polygons[i].Vertices); 
				Polygons[i].Vertices = NULL; 
			}
			if ( Polygons[i].Indices )  
			{ 
				free(Polygons[i].Indices);  
				Polygons[i].Indices  = NULL; 
			}
		} // End For I
		// Free the polygon data
		free( Polygons ); 
		Polygons	= NULL;
	} // End If Polygons != NULL
	
	// Free PolygonDeleted Data
	if ( PolygonDeleted )	
	{ 
		free( PolygonDeleted );
		PolygonDeleted = NULL; 
	}

	PolyCount		= 0;
}

void CKBSPTree::InitPolygons( CKMesh *brush, long BrushCount, bool BSPCollect )
{
	FatalError = FALSE;
	
	KillTree();				// Free our previous tree
	
//	BrushBase = brush;
	
	PolygonList = NULL;
	
	// If we don't want to collect these polygons from
	// a bsp tree, we will collect the polygons from
	// the brush itself

	BSPPOLYGON *Child = NULL;

	if ( !BSPCollect ) {
		for ( ULONG f = 0; f < brush->nb2poly; f++ ) {
			Child = AddPolygon( Child, &brush->pl[f],brush );
			//Child = AddPolygonSplit( Child, &brush->Faces[f] );
		} // End For Brush Faces
		
	} else {
		for ( int b = 0; b < BrushCount; b++ ) {
			CKBSPTree * MiniBSP = (CKBSPTree*)brush->BSPTree;
			if ( MiniBSP == NULL ) continue;
			for ( int f = 0; f < MiniBSP->PolyCount; f++ ) {
				if (!MiniBSP->PolygonDeleted[f]) {
					if ( MiniBSP->Polygons[f].VertexCount < 3 ) continue;
					Child = AddBSPPolygon( Child, &MiniBSP->Polygons[f] );
				} // End If poly is not deleted
			} // End For Brush Faces
		} // Next Brush
	} // End If BrushCount == 1

	
	// Before we build the tree we must free our old poly array
	// NOTE: the reason we kill the polys separately is because
	// this initpolygons may actually be required to collect
	// polys from itself when collecting polys from a bsp tree.
	KillPolys();
	
	// Add the root node.
	RootNode = AllocAddNode();
	// Now compile the actual tree from this data
	BuildBSPTree( RootNode, PolygonList );

	// Flag as Clean
	IsDirty = FALSE;

}

//-----------------------------------------------------------------------------
// Name : AddBSPPolygon ()
// Desc : Extended Add Polygon. This function add's a simple Poly copied from
//        a BSP Tree Polygon to the LINKED LIST
//-----------------------------------------------------------------------------
BSPPOLYGON *CKBSPTree::AddBSPPolygon( BSPPOLYGON *Parent, BSPPOLYGON*Poly )
{
	BSPPOLYGON *Child		= new BSPPOLYGON;
	Child->IndexCount		= Poly->IndexCount;
	Child->VertexCount		= Poly->VertexCount;
	Child->Normal			= Poly->Normal;
	Child->TextureIndex		= Poly->TextureIndex;
	Child->UsedAsSplitter	= 0;
	Child->NextPoly			= NULL;

	Child->Vertices			= (Vertex*)malloc(Poly->VertexCount * sizeof(Vertex));
	Child->Indices			= (WORD*)malloc(Poly->IndexCount * sizeof(WORD));

	memcpy( &Child->Vertices[0], &Poly->Vertices[0], Poly->VertexCount * sizeof(Vertex));
	memcpy( &Child->Indices[0], &Poly->Indices[0], Poly->IndexCount * sizeof(WORD));
	
	if ( Parent != NULL)		Parent->NextPoly	= Child;
	if ( PolygonList == NULL)	PolygonList			= Child;
	return Child;
}

BSPPOLYGON *CKBSPTree::AddPolygon(BSPPOLYGON *Parent, CKPolygon *Face,CKMesh *Owner )
{
	int i;


	BSPPOLYGON *Child		= new BSPPOLYGON;
	Child->NextPoly			= NULL;
	Child->UsedAsSplitter	= 0;

	// Copy Poly Data
	Child->VertexCount		= Face->nb2vert;
	Child->IndexCount		= (Face->nb2vert-2)*3;

	Child->Normal.x			= Face->Normale.x;
	Child->Normal.y			= Face->Normale.y;
	Child->Normal.z			= Face->Normale.z;

	Child->TextureIndex		= 0;//Face->TextureIndex;
	
	// Reserve space for Vertex and Index Lists
	Child->Vertices			= (Vertex*)malloc( Child->VertexCount * sizeof(Vertex));
	Child->Indices			= (WORD*)malloc( Child->IndexCount * sizeof(WORD));


	// Copy the Vertex Data
	for ( i = 0; i < Face->nb2vert; i++) 
	{
		Child->Vertices[i].x =Owner->pv[Owner->pi[Face->FirstIndex+i]].x;
		Child->Vertices[i].y =Owner->pv[Owner->pi[Face->FirstIndex+i]].y;
		Child->Vertices[i].z =Owner->pv[Owner->pi[Face->FirstIndex+i]].z;
/* HERE
		Child->Vertices[i].Normal.x=Face->Normale.x;
		Child->Vertices[i].Normal.y=Face->Normale.y;
		Child->Vertices[i].Normal.z=Face->Normale.z;

		Child->Vertices[i].tu= Owner->puv[0][Face->Tex[0][i]].u;
		Child->Vertices[i].tv= Owner->puv[0][Face->Tex[0][i]].v;
*/
	} // Next Vertex

	//fclose(ostr);

	// Copy the Index Data
	int V1=1;
	int V2=2;
	for ( i = 0; i < Face->nb2vert-2; i++) 
	{
		Child->Indices[(i*3)] = 0;//Face->nbvert[i];
		Child->Indices[(i*3)+1] = V1;//Face->nbvert[i];
		Child->Indices[(i*3)+2] = V2;//Face->nbvert[i];

		V1++;
		V2++;
	}


	// Set parent's child linked list variable
	if (PolygonList==NULL) PolygonList = Child;
	if (Parent!=NULL) Parent->NextPoly = Child;
	return Child;
}

//-----------------------------------------------------------------------------
// Name : BuildBSPTree () ( Recursive )
// Desc : Build's the entire BSP Tree using the already initialised poly data
//-----------------------------------------------------------------------------
void CKBSPTree::BuildBSPTree( long CurrentNode, BSPPOLYGON *PolyList )
{

	Vertex a, b; float result;
	BSPPOLYGON *polyTest=NULL, *FrontList=NULL, *BackList=NULL;
	BSPPOLYGON *NextPolygon=NULL, *FrontSplit=NULL, *BackSplit=NULL;
	
	if ( FatalError == TRUE) return;

	// First of all we need to Select the best splitting
	// plane from the remaining polygon list.
	Nodes[CurrentNode].Plane = SelectBestSplitter( PolyList, CurrentNode );
	
	if ( FatalError == TRUE) return;

	// Store the poly list (we need to use the original later)
	polyTest = PolyList;

	while ( polyTest!=NULL ) {
		// Remember to store because 
		// polytest->Next will be altered
		NextPolygon = polyTest->NextPoly;

		switch ( ClassifyPoly( &Planes[Nodes[CurrentNode].Plane ], polyTest ) )
		{
			case CP_ONPLANE:
				// If the poly end's up on the plane, wee need to pass it
				// down the side the plane is facing, so we do a quick test
				// and pass it down the appropriate side.
				a = Planes[Nodes[CurrentNode].Plane].Normal;
				b = polyTest->Normal;	
				result = (float)fabs( ( a.x - b.x ) + ( a.y - b.y ) + ( a.z - b.z ) );
				if ( result < 0.1f ) {	
					polyTest->NextPoly	= FrontList;
					FrontList			= polyTest;
				} else {
					polyTest->NextPoly	= BackList;
					BackList			= polyTest;	
				} // End If Plane Facing
				break;
			case CP_FRONT:
				// Pass the poly straight down the front list.
				polyTest->NextPoly		= FrontList;
				FrontList				= polyTest;		
				break;
			case CP_BACK:
				// Pass the poly straight down the back list.
				polyTest->NextPoly		= BackList;
				BackList				= polyTest;	
				break;
			case CP_SPANNING:
				// If Poly is spanning the plane we need to split
				// it and pass each fragment down the appropriate side.
				FrontSplit = new BSPPOLYGON;
				BackSplit  = new BSPPOLYGON;
				ZeroMemory( FrontSplit, sizeof(BSPPOLYGON) );
				ZeroMemory( BackSplit , sizeof(BSPPOLYGON) );
				
				// Split the polygon
				SplitPolygon( polyTest, &Planes[Nodes[CurrentNode].Plane], FrontSplit, BackSplit );
    
				FrontSplit->UsedAsSplitter = polyTest->UsedAsSplitter;
				BackSplit->UsedAsSplitter  = polyTest->UsedAsSplitter;
				
				free ( polyTest->Vertices );
				free ( polyTest->Indices );
				delete polyTest; polyTest = NULL;
	
				// Copy fragements to the front/back list
				FrontSplit->NextPoly = FrontList;
				FrontList			 = FrontSplit;
				BackSplit->NextPoly	 = BackList;
				BackList			 = BackSplit;

				break;
			default:

				break;
		} //switch

		polyTest = NextPolygon;
	}// End while loop
   
	// Count the splitters remaining
	// In this list
	int SplitterCount = 0;
	BSPPOLYGON *tempf	  = FrontList;
	while ( tempf != NULL) {
		if ( tempf->UsedAsSplitter == 0) SplitterCount++;
		tempf = tempf->NextPoly;
	} 

	// If there are no splitters remaining
	// We can go ahead and add the leaf.
	if ( SplitterCount == 0) {
		BSPPOLYGON *Iterator = FrontList;
		BSPPOLYGON *Temp;
		
		// Add a new leaf
		AllocAddLeaf();
		Leaves[LeafCount-1].StartPoly = PolyCount;
		while (Iterator!=NULL) {
			Polygons[ AllocAddPoly() ] = *Iterator;
			Temp = Iterator;
			Iterator = Iterator->NextPoly;
			// we use the normal delete operator here because we dont want to delete the actual vertexLists and index lists
			// because we are still referenceing them in the Polygon Array
			delete Temp;
		} // End While
		Leaves[LeafCount-1].EndPoly = PolyCount;
		Nodes[CurrentNode].Front  = LeafCount-1;
		Nodes[CurrentNode].IsLeaf = 1;
	} else {
		// Otherwise create a new node, and
		// push the front list down the tree.
		Nodes[CurrentNode].IsLeaf = 0;
		Nodes[CurrentNode].Front =AllocAddNode();
		BuildBSPTree( NodeCount-1, FrontList );  
	} // End If No Splitters Left

	// If the back list is empty
	if (BackList == NULL) {
		Nodes[CurrentNode].Back = -1;
	} else {
		Nodes[CurrentNode].Back = AllocAddNode();
		BuildBSPTree( NodeCount-1, BackList );
	}  // End If BackList Empty.
  
}// end function

//-----------------------------------------------------------------------------
// Name : AllocAddNode ()
// Desc : Reallocates memory for the NODE array and returns the last added.
//-----------------------------------------------------------------------------
int CKBSPTree::AllocAddNode( )
{
	NodeCount++;
	Nodes = (NODE*)realloc( Nodes, NodeCount * sizeof(NODE) );
	Nodes[NodeCount-1].IsLeaf	= 0;
	Nodes[NodeCount-1].Plane	= -1;
	Nodes[NodeCount-1].Front	= -1;
	Nodes[NodeCount-1].Back		= -1;
	return NodeCount-1;
}

//-----------------------------------------------------------------------------
// Name : AllocAddLeaf ()
// Desc : Reallocates memory for the LEAF array and returns the last added.
//-----------------------------------------------------------------------------
int CKBSPTree::AllocAddLeaf( )
{
	LeafCount++;
	Leaves = (LEAF*)realloc( Leaves, LeafCount * sizeof(LEAF) );
	Leaves[LeafCount-1].StartPoly		= -1;
	Leaves[LeafCount-1].EndPoly			= -1;
	return LeafCount-1;
}

//-----------------------------------------------------------------------------
// Name : AllocAddPoly ()
// Desc : Reallocates memory for the POLY array and returns the last added.
//-----------------------------------------------------------------------------
int CKBSPTree::AllocAddPoly( )
{
	PolyCount++;
	Polygons		= (BSPPOLYGON*)realloc( Polygons, PolyCount * sizeof(BSPPOLYGON) );
	PolygonDeleted  = (bool*)realloc( PolygonDeleted, PolyCount * sizeof(bool) );
	PolygonDeleted[PolyCount-1]				= FALSE;
	Polygons[PolyCount-1].IndexCount		= 0;
	Polygons[PolyCount-1].Indices			= NULL;
	Polygons[PolyCount-1].VertexCount		= 0;
	Polygons[PolyCount-1].Vertices			= NULL;
	Polygons[PolyCount-1].Normal			= Vertex( 0.0f, 0.0f, 0.0f );
	Polygons[PolyCount-1].NextPoly			= NULL;
	Polygons[PolyCount-1].UsedAsSplitter	= 0;
	return PolyCount-1;
}

//-----------------------------------------------------------------------------
// Name : AllocAddPlane ()
// Desc : Reallocates memory for the PLANE array and returns the last added.
//-----------------------------------------------------------------------------
int CKBSPTree::AllocAddPlane( )
{
	PlaneCount++;
	Planes = (PLANE*)realloc( Planes, PlaneCount * sizeof(PLANE) );
	Planes[PlaneCount-1].PointOnPlane	= Vertex( 0.0f, 0.0f, 0.0f );
	Planes[PlaneCount-1].Normal			= Vertex( 0.0f, 0.0f, 0.0f );
	return PlaneCount-1;
}

//-----------------------------------------------------------------------------
// Name : SelectBestSplitter ()
// Desc : Picks the splitter which most closely matches the splitting heuristic
//-----------------------------------------------------------------------------
long CKBSPTree::SelectBestSplitter( BSPPOLYGON *PolyList, long CurrentNode )
{
	BSPPOLYGON *Splitter = PolyList, *CurrentPoly = NULL, *SelectedPoly = NULL;
	ULONG   BestScore = 1000000;

	// Traverse the Poly Linked List
	while ( Splitter != NULL ) {
		// If this has not been used as a splitter then
		if ( Splitter->UsedAsSplitter != 1 ) {
			// Create the testing splitter plane
			PLANE SplittersPlane;
			SplittersPlane.Normal		= Splitter->Normal;
			SplittersPlane.PointOnPlane	= Splitter->Vertices[0];
			
			CurrentPoly					= PolyList;
			ULONG score, splits, backfaces, frontfaces;
			score = splits = backfaces = frontfaces = 0;
			
			// Test against the other poly's
			// and count the score.
			while ( CurrentPoly != NULL ) {
				int result = ClassifyPoly( &SplittersPlane, CurrentPoly );
				switch ( result ) {
					case CP_ONPLANE:
						break;
					case CP_FRONT:
						frontfaces++;
						break;
					case CP_BACK:
						backfaces++;
						break;
					case CP_SPANNING:
						splits++;
						break;
					default:
						break;
				}// switch
				CurrentPoly = CurrentPoly->NextPoly;
			} // end while current poly
			
			// Tally the score (modify the splits * n)
			score = abs( frontfaces - backfaces ) + ( splits * 3 );
			
			if ( score < BestScore) {
				BestScore	 = score;
				SelectedPoly = Splitter;
			}
  
		}// end if this splitter has not been used yet		
		Splitter = Splitter->NextPoly;
	}// end while splitter == null	

	if ( SelectedPoly == NULL ) {
		FatalError = TRUE;
		return -1;
	}

	SelectedPoly->UsedAsSplitter = 1;

	// Return the selected poly's plane
	AllocAddPlane();
	Planes[PlaneCount-1].PointOnPlane = SelectedPoly->Vertices[0];
	Planes[PlaneCount-1].Normal		  = SelectedPoly->Normal;
	return ( PlaneCount-1 );
}

//-----------------------------------------------------------------------------
// Name : ClassifyPoly ()
// Desc : Given a plane and a poly, returns the poly's position relative
//        to the plane itself (i.e Front/Back/On/Spanning)
//-----------------------------------------------------------------------------
int CKBSPTree::ClassifyPoly( PLANE *Plane, BSPPOLYGON * Poly )
{
	int			Infront = 0, Behind = 0, OnPlane=0;
	float		result  = 0;
	Vertex	vec1   = Plane->PointOnPlane;

	// Loop round each vertex
	for ( int a = 0; a < Poly->VertexCount; a++ ) {
		Vertex vec2 = Poly->Vertices[a];
		Vertex Direction = vec1 - vec2;
		//result = DotProduct( &Direction, &Plane->Normal );
		result=((Direction.x*Plane->Normal.x)+(Direction.y*Plane->Normal.y)+(Direction.z*Plane->Normal.z));

		// Check the position
		if (result>g_EPSILON) {
			Behind++;
		} else if (result<-g_EPSILON) {
			Infront++;
		} else {
			OnPlane++;
			Infront++;
			Behind++;
		}
	} // End For Each Vertex

	if ( OnPlane == Poly->VertexCount ) 
		return CP_ONPLANE;
	if ( Behind  == Poly->VertexCount ) 
		return CP_BACK;
	if ( Infront == Poly->VertexCount ) 
		return CP_FRONT;
	return CP_SPANNING;
}

//-----------------------------------------------------------------------------
// Name : ClassifyPoint ()
// Desc : Given a plane and a point, returns the points's position relative
//        to the plane itself (i.e Front/Back/On)
//-----------------------------------------------------------------------------
int CKBSPTree::ClassifyPoint( Vertex *pos, PLANE *Plane ) 
{
	float result;
	Vertex *vec1		= &Plane->PointOnPlane;
	// HERE
	//Vertex Direction	= (*vec1) - (*pos);
	Vertex Direction;
	Direction.x=vec1->x-pos->x;
	Direction.y=vec1->y-pos->y;
	Direction.z=vec1->z-pos->z;

	//result					= DotProduct( &Direction, &Plane->Normal );
	result=((Direction.x*Plane->Normal.x)+(Direction.y*Plane->Normal.y)+(Direction.z*Plane->Normal.z));

	if ( result < -g_EPSILON ) return CP_FRONT;
	if ( result > g_EPSILON  ) return CP_BACK;
	return CP_ONPLANE;
}

//-----------------------------------------------------------------------------
// Name : SplitPolygon ()
// Desc : Splits the passed polygon against the plane provided, the
//        fragments are then passed back through the Front/BackSplit
//-----------------------------------------------------------------------------
void CKBSPTree::SplitPolygon(BSPPOLYGON *Poly,PLANE *Plane,BSPPOLYGON *FrontSplit,BSPPOLYGON *BackSplit)
{
	// 50 is used here, as we should never
	// really have more points on a portal than this.
	Vertex		FrontList[50];
	Vertex		BackList[50];
	int				FrontCounter = 0;
	int				BackCounter = 0;

	int				PointLocation[50];

	int				InFront = 0, Behind = 0, OnPlane = 0;
	int				CurrentVertex = 0, Location = 0;

	// Determine each points location relative to the plane.
	for ( int i = 0; i < Poly->VertexCount; i++)	{
		Location = ClassifyPoint((Vertex*)&Poly->Vertices[i], Plane);
		if (Location == CP_FRONT )
			InFront++;
		else if (Location == CP_BACK )
			Behind++;
		else
			OnPlane++;

		PointLocation[i] = Location;
	} // Next Vertex

	if (!InFront) {
		memcpy(BackList, Poly->Vertices, Poly->VertexCount * sizeof(Vertex));
		BackCounter = Poly->VertexCount;
	}

	if (!Behind) {
		memcpy(FrontList, Poly->Vertices, Poly->VertexCount * sizeof(Vertex));
		FrontCounter = Poly->VertexCount;
	}

	if (InFront && Behind) {
		for ( i = 0; i < Poly->VertexCount; i++) {
			// Store Current vertex remembering to MOD with number of vertices.
			CurrentVertex = (i+1) % Poly->VertexCount;

			if (PointLocation[i] == CP_ONPLANE ) {
				FrontList[FrontCounter] = Poly->Vertices[i];
				FrontCounter++;
				BackList[BackCounter] = Poly->Vertices[i];
				BackCounter++;
				continue; // Skip to next vertex
			}
			if (PointLocation[i] == CP_FRONT ) {
				FrontList[FrontCounter] = Poly->Vertices[i];
				FrontCounter++;
			} else {
				BackList[BackCounter] = Poly->Vertices[i];
				BackCounter++;
			}
			
			// If the next vertex is not causing us to span the plane then continue
			if (PointLocation[CurrentVertex] == CP_ONPLANE || PointLocation[CurrentVertex] == PointLocation[i]) continue;
			
			// Otherwise create the new vertex
			Vertex IntersectPoint;
			float		percent;

			Get_Intersect( (Vertex*)&Poly->Vertices[i], (Vertex*)&Poly->Vertices[CurrentVertex], &Plane->PointOnPlane, &Plane->Normal, &IntersectPoint, &percent );

			// create new vertex and calculate new texture coordinate
			Vertex copy;
			/* HERE
			float deltax	= Poly->Vertices[CurrentVertex].tu - Poly->Vertices[i].tu;
			float deltay	= Poly->Vertices[CurrentVertex].tv - Poly->Vertices[i].tv;
			float texx		= Poly->Vertices[i].tu + ( deltax * percent );
			float texy		= Poly->Vertices[i].tv + ( deltay * percent );
			*/
			copy.x			= IntersectPoint.x; 
			copy.y = IntersectPoint.y; 
			copy.z = IntersectPoint.z;
			/* HERE
			copy.tu			= texx; 
			copy.tv = texy;
	*/

			BackList[BackCounter++]		= copy;			
			FrontList[FrontCounter++]	= copy;
		}
	}

	//OK THEN LETS BUILD THESE TWO POLYGONAL BAD BOYS

	// Reserve Memory for Front and Back Vertex Lists 
	FrontSplit->Vertices		 = (Vertex*)malloc(FrontCounter * sizeof(Vertex));
	BackSplit->Vertices			 = (Vertex*)malloc(BackCounter * sizeof(Vertex));

	FrontSplit->VertexCount		 = 0;
	BackSplit->VertexCount		 = 0;

	// Copy over the vertices into the new polys
	FrontSplit->VertexCount		 = FrontCounter;
	memcpy(FrontSplit->Vertices, FrontList, FrontCounter * sizeof(Vertex));
	
	BackSplit->VertexCount		= BackCounter;
	memcpy(BackSplit->Vertices, BackList, BackCounter * sizeof(Vertex));


	BackSplit->IndexCount		= ( BackSplit->VertexCount  - 2 ) * 3;
	FrontSplit->IndexCount		= ( FrontSplit->VertexCount - 2 ) * 3;
	
	// Reserve Memory for Front and Back Index Lists 
	BackSplit->Indices			= (WORD*)malloc(BackSplit->IndexCount * sizeof(WORD));
	FrontSplit->Indices			= (WORD*)malloc(FrontSplit->IndexCount * sizeof(WORD));
	
	// Fill in the Indices
	short IndxBase;
	for ( short loop = 0, v1 = 1, v2 = 2; loop < FrontSplit->IndexCount/3; loop++, v1 = v2, v2++) {
		IndxBase = loop * 3;
		FrontSplit->Indices[ IndxBase    ] =  0;
		FrontSplit->Indices[ IndxBase + 1] = v1;
		FrontSplit->Indices[ IndxBase + 2] = v2;
	} // Next Tri

	for ( loop = 0, v1 = 1, v2 = 2; loop < BackSplit->IndexCount/3; loop++, v1 = v2, v2++) {
		IndxBase = loop * 3;
		BackSplit->Indices[ IndxBase    ] =  0;
		BackSplit->Indices[ IndxBase + 1] = v1;
		BackSplit->Indices[ IndxBase + 2] = v2;
	} // Next Tri

	// Copy Extra Values
	FrontSplit->Normal			= Poly->Normal;
	BackSplit->Normal			= Poly->Normal;
	FrontSplit->TextureIndex	= Poly->TextureIndex;
	BackSplit->TextureIndex		= Poly->TextureIndex;

	// Copy over to vertex normals
	/* HERE
	for ( i = 0; i <  BackSplit->VertexCount; i++ )
		BackSplit->Vertices [i].Normal =  BackSplit->Normal;
	for ( i = 0; i < FrontSplit->VertexCount; i++ )  
		FrontSplit->Vertices[i].Normal = FrontSplit->Normal;
		*/

}

//-----------------------------------------------------------------------------
// Name : GetIntersect ()
// Desc : Returns the Intersection point between a ray and a  plane
//-----------------------------------------------------------------------------
bool CKBSPTree::Get_Intersect( Vertex *linestart, Vertex *lineend, Vertex *vertex, Vertex *normal, Vertex * intersection, float *percentage )
{
	Vertex direction, L1;
	float	    linelength, dist_from_plane;

	direction.x = lineend->x - linestart->x;
	direction.y = lineend->y - linestart->y;
	direction.z = lineend->z - linestart->z;

	//linelength = DotProduct( &direction, normal );
	linelength=((direction.x*normal->x)+(direction.y*normal->y)+(direction.z*normal->z));
	if (fabsf( linelength ) < g_EPSILON ) return false; 

	L1.x = vertex->x - linestart->x;
	L1.y = vertex->y - linestart->y;
	L1.z = vertex->z - linestart->z;

	//dist_from_plane = DotProduct( &L1, normal );
	dist_from_plane =((L1.x*normal->x)+(L1.y*normal->y)+(L1.z*normal->z));

	// How far from Linestart , intersection is as a percentage of 0 to 1 
	*percentage = dist_from_plane / linelength; 

	// The plane is behind the start of the line or
	// The line does not reach the plane
	if ( *percentage < 0.0f || *percentage > 1.0f ) return FALSE;

	// add the percentage of the line to line start
	intersection->x = linestart->x + direction.x * (*percentage);
	intersection->y = linestart->y + direction.y * (*percentage);
	intersection->z = linestart->z + direction.z * (*percentage);
	return TRUE;
}

//-----------------------------------------------------------------------------
// Name : RenderBSPPolys ()
// Desc : Simply Renders all polys in the tree
//-----------------------------------------------------------------------------
void CKBSPTree::RenderBSPPolys( int BrushIndex ) 
{

	/*
	glColor4f(0,1,0,1);

	for ( int i = 0; i < PolyCount; i++ ) {
		if ( PolygonDeleted[i] == FALSE ) {

			glBegin(GL_LINE_LOOP);
			for (int j=0;j<Polygons[i].VertexCount;j++)
			{
				glVertex3f(Polygons[i].Vertices[j].x,
					Polygons[i].Vertices[j].y,
					Polygons[i].Vertices[j].z);

			}	
			glEnd();

		} // If polygon is not deleted then
	} // Next Polygon
	//fclose(ostr);
*/
}


//-----------------------------------------------------------------------------
// Name : ClipTree ()
// Desc : Clips One BSP Tree against another. This is an EXTREMELY useful
//        function, it is used by both the CSG and HSR routines. Passing
//        False to ClipSolid will essentially Perform a carve from the
//        this tree with the tree passed... Passing TRUE will clip away
//        Any areas of the tree inside the solid area of the tree passed.
//-----------------------------------------------------------------------------
bool CKBSPTree::ClipTree( long CurrentNode, long *Polygons, long pPolyCount, CKBSPTree *BSPTree, bool ClipSolid, bool RemoveCoPlanar)
{   
	Vertex a, b;
    long *FrontList = NULL;
    long *BackList = NULL;
    long FSplit = -1, BSplit = -1;
    long FListCount = 0;
    long BListCount = 0;
	float result;

	// Mark the tree to be clipped as dirty
	BSPTree->IsDirty = TRUE;

	bool FreePolyList = FALSE;
	// If this is the first call to cliptree
	// then we must build an index list first of all.
	if ( Polygons == NULL ) {
		FreePolyList = TRUE;
		Polygons = new long[BSPTree->PolyCount];
		for ( int i = 0; i < BSPTree->PolyCount; i++ ) {
			Polygons[i] = i;
		} // Next Poly
		pPolyCount = BSPTree->PolyCount;
		if (pPolyCount <= 0 ) return FALSE;
		if (PolyCount <= 0 ) return FALSE;
	} // End If Polygons == NULL
        
	// Pass Poly's down the tree etc.
    for ( int p = 0; p < pPolyCount; p++ ) {
        if ( BSPTree->PolygonDeleted[Polygons[p]] ) continue;
        switch ( ClassifyPoly( &Planes[Nodes[CurrentNode].Plane], &BSPTree->Polygons[Polygons[p]] ) ) 
		{
			case CP_ONPLANE:
				// Here we test the normal against the plane
				// if it is facing in the same direction then send it down the back
				// if RemoveCoPlanar is TRUE, otherwise it gets sent down the front.
				// However, if it is facing in the opposite direction to the plane,
				// we can safely send this down the back of the tree.
				a = Planes[Nodes[CurrentNode].Plane].Normal;
				b = BSPTree->Polygons[Polygons[p]].Normal;	
				result = (float)fabs( ( a.x - b.x ) + ( a.y - b.y ) + ( a.z - b.z ) );
				if ( result < 0.1f ) {	
					if (RemoveCoPlanar) {
						BListCount++;
						BackList = (long*)realloc(BackList, BListCount * sizeof(long));
						BackList[BListCount - 1] = Polygons[p];
					} else {
						FListCount++;
						FrontList = (long*)realloc(FrontList, FListCount * sizeof(long));
						FrontList[FListCount - 1] = Polygons[p];
					}
				} else {
						BListCount++;
						BackList = (long*)realloc(BackList, BListCount * sizeof(long));
						BackList[BListCount - 1] = Polygons[p];
				} // End If Plane Facing
				break;
            case CP_FRONT:
                FListCount++;
				FrontList = (long*)realloc(FrontList, FListCount * sizeof(long));
                FrontList[FListCount - 1] = Polygons[p];
				break;
            case CP_BACK:
                BListCount++;
				BackList = (long*)realloc(BackList, BListCount * sizeof(long));
                BackList[BListCount - 1] = Polygons[p];
				break;
            case CP_SPANNING:
				FListCount++;
				FrontList = (long*)realloc(FrontList, FListCount * sizeof(long));
				FrontList[FListCount - 1] = BSPTree->AllocAddPoly();
				FSplit = FListCount - 1;
				BListCount++;
				BackList = (long*)realloc(BackList, BListCount * sizeof(long));
				BackList[BListCount - 1] = BSPTree->AllocAddPoly();
				BSplit = BListCount - 1;
				SplitPolygon( &BSPTree->Polygons[Polygons[p]], &Planes[Nodes[CurrentNode].Plane], &BSPTree->Polygons[FrontList[FSplit]], &BSPTree->Polygons[BackList[BSplit]]) ;
                
				// Since this is a coincidental pre-process on mini bsp trees
				// we don't actually need to update the leaf polys. Which is 
				// convenient =)

				BSPTree->PolygonDeleted[Polygons[p]] = TRUE;
				break;
        } // End Switch
    } // End For p

	if ( ClipSolid ) {
		if ( Nodes[CurrentNode].Back == -1 ) {
			for ( int i = 0; i < BListCount; i++ ) {
				BSPTree->PolygonDeleted[BackList[i]] = TRUE;
			} // End For i
			BListCount = 0;
		}
	} else {
		if ( Nodes[CurrentNode].IsLeaf == 1 ) {
			for ( int i = 0; i < FListCount; i++ ) {
				BSPTree->PolygonDeleted[FrontList[i]] = TRUE;
			} // End For i
			FListCount = 0;
		}
	} // End If ( Clip Away the Areas in Solid Space )

	//Pass down the front tree
    if ( FListCount > 0 && Nodes[CurrentNode].IsLeaf == 0 && Nodes[CurrentNode].Front > -1) ClipTree( Nodes[CurrentNode].Front, FrontList, FListCount, BSPTree, ClipSolid, RemoveCoPlanar );
    
    //Pass down the back tree
	if ( BListCount > 0 && Nodes[CurrentNode].Back > -1) ClipTree( Nodes[CurrentNode].Back, BackList, BListCount, BSPTree, ClipSolid, RemoveCoPlanar );

	if ( FrontList ) { free( FrontList ) ; FrontList = NULL; }
	if ( BackList ) { free( BackList ) ; BackList = NULL; }
	// If we had to build our own PolyList, then free it up here.
	if ( FreePolyList ) delete []Polygons;
	return TRUE;
}

//-----------------------------------------------------------------------------
// Name : InvertPolys ()
// Desc : Pretty self explanatory, simply inverts all the polys which were
//        generated by the compiler.
//-----------------------------------------------------------------------------
void CKBSPTree::InvertPolys()
{
	int			Counter	= 1;
	Vertex	*TVerts = NULL;
    for ( int i = 0; i < PolyCount; i++ ){
		if (PolygonDeleted[i]) continue;
        // create a temporary vertex array
		TVerts = new Vertex[Polygons[i].VertexCount];
		// copy vert 0 into the array
		TVerts[0] = Polygons[i].Vertices[0];
		Counter = 1;
		// copy the vertices in reverse order, into the array
        for ( int k = Polygons[i].VertexCount; k > 1; k--, Counter++ ) {
            TVerts[Counter] = Polygons[i].Vertices[k - 1];
        } // Next k
		// copy the vertices back over.
		memcpy( &Polygons[i].Vertices[0], &TVerts[0], Polygons[i].VertexCount * sizeof(Vertex));
		delete []TVerts;

		// Invert the polygons normal also
        Polygons[i].Normal = Vertex(0,0,0)-Polygons[i].Normal;

		// copy this inverted normal into the vertex normal for d3d lighting purposes.
		/* HERE
		for ( k = 0; k < Polygons[i].VertexCount; k++ ) {
			Polygons[i].Vertices[k].Normal = Polygons[i].Normal;
		}
		*/
        
		//Recalculate Indices
		int pCount = Polygons[i].IndexCount / 3;
		for ( int lloop = 0, v1 = 1, v2 = 2; lloop < pCount; lloop ++ ){
			Polygons[i].Indices[lloop *3]		 = 0;
			Polygons[i].Indices[(lloop * 3) + 1] = v1;
			Polygons[i].Indices[(lloop * 3) + 2] = v2;
			v1 = v2;
			v2 = v2 + 1;
		}
	} // Next i
}

//-----------------------------------------------------------------------------
// Name : AddPolygonEX ()
// Desc : Extended Add Polygon. This function add's a simple Poly copied from
//        a BSP Tree Polygon TO THE POLYGON ARRAY
//-----------------------------------------------------------------------------
BSPPOLYGON *CKBSPTree::AddPolygonEX( BSPPOLYGON*Poly )
{
	int Child = AllocAddPoly();
	Polygons[Child].IndexCount		= Poly->IndexCount;
	Polygons[Child].VertexCount		= Poly->VertexCount;
	Polygons[Child].Normal			= Poly->Normal;
	Polygons[Child].TextureIndex	= Poly->TextureIndex;
	Polygons[Child].UsedAsSplitter	= 0;
	Polygons[Child].NextPoly		= NULL;

	Polygons[Child].Vertices		= (Vertex*)malloc(Poly->VertexCount * sizeof(Vertex));
	Polygons[Child].Indices			= (WORD*)malloc(Poly->IndexCount * sizeof(WORD));

	memcpy( &Polygons[Child].Vertices[0], &Poly->Vertices[0], Poly->VertexCount * sizeof(Vertex));
	memcpy( &Polygons[Child].Indices[0], &Poly->Indices[0], Poly->IndexCount * sizeof(short));

	return &Polygons[Child];

}

//-----------------------------------------------------------------------------
// Name : CopyTree ()
// Desc : Makes a copy of this tree, and places it in the DESTree passed.
//-----------------------------------------------------------------------------
CKBSPTree *CKBSPTree::CopyTree( )
{
	CKBSPTree * DESTree = NULL;
	if ( DESTree == NULL) DESTree = new CKBSPTree;

	// Copy Standard Vars
	DESTree->FatalError		= FatalError;
	//DESTree->BrushBase		= BrushBase;
	DESTree->RootNode		= RootNode;
	DESTree->NodeCount		= NodeCount;
	DESTree->PolyCount		= PolyCount;
	DESTree->PlaneCount		= PlaneCount;
	DESTree->LeafCount		= LeafCount;
	DESTree->PolygonList	= PolygonList;

	// Create arrays suitable in destination tree
	DESTree->PolygonDeleted	= (bool*)		malloc( PolyCount	* sizeof(bool)		);
	DESTree->Polygons		= (BSPPOLYGON*)	malloc( PolyCount	* sizeof(BSPPOLYGON));
	DESTree->Planes			= (PLANE*)		malloc( PlaneCount	* sizeof(PLANE)		);
	DESTree->Nodes			= (NODE*)		malloc( NodeCount	* sizeof(NODE)		);
	DESTree->Leaves			= (LEAF*)		malloc( LeafCount	* sizeof(LEAF)		);

	// Copy Data Over
	memcpy( DESTree->PolygonDeleted	, PolygonDeleted, PolyCount		* sizeof(bool)		);
	memcpy( DESTree->Polygons		, Polygons		, PolyCount		* sizeof(BSPPOLYGON));
	memcpy( DESTree->Planes			, Planes		, PlaneCount	* sizeof(PLANE)		);
	memcpy( DESTree->Nodes			, Nodes			, NodeCount		* sizeof(NODE)		);
	memcpy( DESTree->Leaves			, Leaves		, LeafCount		* sizeof(LEAF)		);

	// Now we need to allocate the internal arrays.
	// and copy over the specific data for each type
	for (int i = 0; i < PolyCount; i++ ) {
		// Vertices
		DESTree->Polygons[i].Vertices = NULL;
		DESTree->Polygons[i].Vertices = (Vertex*)malloc( Polygons[i].VertexCount * sizeof(Vertex));
		memcpy( DESTree->Polygons[i].Vertices, Polygons[i].Vertices, Polygons[i].VertexCount * sizeof(Vertex));
		// Indices
		DESTree->Polygons[i].Indices = NULL;
		DESTree->Polygons[i].Indices = (WORD*)malloc( Polygons[i].IndexCount * sizeof(WORD));
		memcpy( DESTree->Polygons[i].Indices, Polygons[i].Indices, Polygons[i].IndexCount * sizeof(WORD));
	} // Next i

	return DESTree;
}


void CKBSPTree::Commit( CKMesh *Obj ) 
{
	int i,j;
	int nb2vert=0,nb2poly=0;
	int plav=0,vertav=0;;

	for ( i = 0; i < PolyCount; i++ ) 
	{
		if (( PolygonDeleted[i] == FALSE ) && (Polygons[i].VertexCount>2 ))
		{
			nb2vert+=Polygons[i].VertexCount;
			nb2poly++;
		}
	}


	Obj->AllocatePoly(nb2poly,nb2vert);
	Obj->AllocateUV(0,nb2vert);

	for ( i = 0; i < PolyCount; i++ ) 
	{
		if ( ( PolygonDeleted[i] == FALSE ) && (Polygons[i].VertexCount>2 ) )
		{
			Obj->pl[plav].Allocate(Obj,1,Polygons[i].VertexCount);

			for (j=0;j<Polygons[i].VertexCount;j++)
			{
				Obj->pv[vertav+j].x=Polygons[i].Vertices[j].x;
				Obj->pv[vertav+j].y=Polygons[i].Vertices[j].y;
				Obj->pv[vertav+j].z=Polygons[i].Vertices[j].z;

				Obj->pl[plav].nbvert[j]=vertav+j;
				Obj->pl[plav].Tex[0][j]=vertav+j;
/* HERE
				Obj->puv[0][vertav+j].u=Polygons[i].Vertices[j].tu;
				Obj->puv[0][vertav+j].v=Polygons[i].Vertices[j].tv;
				*/
			}
			vertav+=Polygons[i].VertexCount;
			plav++;

		}
	} 

	Obj->CollapseIdenticalVertex();
}

void CKBSPTree::CommitAddTo( CKMesh *Obj ) 
{
	int i,j;
	int nb2vert=0,nb2poly=0;
	int plav=0,vertav=0;;

	for ( i = 0; i < PolyCount; i++ ) 
	{
		if ( PolygonDeleted[i] == FALSE ) 
		{
			nb2vert+=Polygons[i].VertexCount;
			nb2poly++;
		}
	}


	int tmpPolyAv=Obj->nb2poly;
	int tmpVertAv=Obj->nb2vert;

	Obj->AllocatePoly(nb2poly+tmpPolyAv,nb2vert+tmpVertAv);
	Obj->AllocateUV(0,Obj->nb2vert+tmpVertAv);
	

	for ( i = 0; i < PolyCount; i++ ) 
	{
		if ( PolygonDeleted[i] == FALSE ) 
		{
			Obj->pl[plav+tmpPolyAv].Allocate(Obj,1,Polygons[i].VertexCount);

			for (j=0;j<Polygons[i].VertexCount;j++)
			{
				Obj->pv[vertav+j+tmpVertAv].x=Polygons[i].Vertices[j].x;
				Obj->pv[vertav+j+tmpVertAv].y=Polygons[i].Vertices[j].y;
				Obj->pv[vertav+j+tmpVertAv].z=Polygons[i].Vertices[j].z;

				Obj->pl[plav+tmpPolyAv].nbvert[j]=vertav+j+tmpVertAv;
				/* HERE
				Obj->pl[plav+tmpPolyAv].Tex[0][j]=vertav+j+tmpVertAv;

				Obj->puv[0][vertav+j+tmpVertAv].u=Polygons[i].Vertices[j].tu;
				Obj->puv[0][vertav+j+tmpVertAv].v=Polygons[i].Vertices[j].tv;
				*/

			}
			vertav+=Polygons[i].VertexCount;
			plav++;

		}
	} 

	Obj->CollapseIdenticalVertex();
}