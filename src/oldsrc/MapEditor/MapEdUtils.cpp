#include "stdafx.h"
#include <headers.h>

 // temp
/*
    dk->AddObject();
    CurrentObj=dk->NextObject;
    CurrentObj->Allocate(0,2*10);
	CreateCube(Vertex(-32,-32,-32),64,64,64);
    CalcTexCoord(CurrentObj,128,128,*Pos,0,0);
	CurrentObj->CalcAllPlanes();

	CurrentObj->BSPTree=new CBSPTree;
	CurrentObj->BSPTree->InitPolygons(CurrentObj,1,FALSE);

	Object *TempCut=BuildCutter();

	SubObject(CurrentObj,TempCut);
*/
	//dk->AddObject(BuildCutter(Vertex(128,64,0),Vertex(16,32,0)));

	/* WORKING 
    dk->AddObject();
    CurrentObj=dk->NextObject;
    CurrentObj->Allocate(0,2*10);
	//CreateCube(Vertex(0,0,0),64,64,64);
	CreateNGon(Vertex(0,0,0),64,8,Vertex(1,0,0),Vertex(0,1,0),Vertex(0,0,1),10);
    CalcTexCoord(CurrentObj,128,128,*Pos,0,0);
	CurrentObj->CalcAllPlanes();


	CurrentObj->BSPTree=new CBSPTree;
	CurrentObj->BSPTree->InitPolygons(CurrentObj,1,FALSE);


    dk->AddObject();
    CurrentObj=dk->NextObject;
    CurrentObj->Allocate(0,2*10);
	//CreateCube(Vertex(48,16,16),32,32,32);
	
	CreateNGon(Vertex(48,48,0),64,8,Vertex(1,0,0),Vertex(0,1,0),Vertex(0,0,1),10);
    CalcTexCoord(CurrentObj,128,128,*Pos,0,0);
	CurrentObj->CalcAllPlanes();

	CurrentObj->BSPTree=new CBSPTree;
	CurrentObj->BSPTree->InitPolygons(CurrentObj,1,FALSE);

	SubObject(dk->FirstObject,dk->FirstObject->Next);
*/
	//dk->DelObject(dk->FirstObject->Next);

	//HollowObject(CurrentObj);

 
/*
	
    dk->AddObject();
    CurrentObj=dk->NextObject;
    //CurrentObj->Allocate(0,8);
	CurrentObj->Allocate(0,(2*10));
	//CreateCubeSpecial(Vertex(48,16,16),64,64,64);
	CreateNGon(Vertex(48,48,0),64,64,Vertex(1,0,0),Vertex(0,1,0),Vertex(0,0,1),10);
    CalcTexCoord(CurrentObj,128,128,*Pos,0,0);
	CurrentObj->CalcAllPlanes();

	CurrentObj->BSPTree=new CBSPTree;
	CurrentObj->BSPTree->InitPolygons(CurrentObj,1,FALSE);

	//SubObject(dk->FirstObject,dk->FirstObject->Next);

	//dk->DelObject(dk->FirstObject->Next);

	HollowObject(CurrentObj);
*/
	//dk->DelObject(CurrentObj);


// temp

#include "MapEdUtils.h"

extern "C" Desk *dk;
extern "C" Object *CurrentObj;
extern "C" Plan dap;
extern "C" OGLView *View;

#define CSG_NONE				0
#define CSG_DIFFERENCE			1
#define CSG_INTERSECTION		2
#define CSG_UNION				3

int g_iCSGMode=CSG_INTERSECTION;

int GetView()
{
    int ViewInd=dk->Active;
	if ((dk->ViewNg[ViewInd].vx==0)&&(dk->ViewNg[ViewInd].vy==0)&&(dk->ViewNg[ViewInd].vz==0)) return 1;//TEXT("Top");
	if ((dk->ViewNg[ViewInd].vx==-90)&&(dk->ViewNg[ViewInd].vy==0)&&(dk->ViewNg[ViewInd].vz==0)) return 2;//TEXT("Front");
	if ((dk->ViewNg[ViewInd].vx==-90)&&(dk->ViewNg[ViewInd].vy==0)&&(dk->ViewNg[ViewInd].vz==90)) return 3;//TEXT("Right");

	if ((dk->ViewNg[ViewInd].vx==0)&&(dk->ViewNg[ViewInd].vy==180)&&(dk->ViewNg[ViewInd].vz==180)) return 4;//TEXT("Bottom");
	if ((dk->ViewNg[ViewInd].vx==90)&&(dk->ViewNg[ViewInd].vy==180)&&(dk->ViewNg[ViewInd].vz==0)) return 5;//TEXT("Back");
	if ((dk->ViewNg[ViewInd].vx==270)&&(dk->ViewNg[ViewInd].vy==0)&&(dk->ViewNg[ViewInd].vz==270)) return 6;//TEXT("Left");

	return 999;
}


void UnionObject(Object *Obj1,Object *Obj2)
{
	int		  f;
	BOOL	  ClipSolid1 = FALSE, ClipSolid2 = FALSE;
	CBSPTree *CSGTree = NULL, *TGTTree = NULL, *CPYTree = NULL;

	ClipSolid1 = FALSE; ClipSolid2 = FALSE; 

	CSGTree = ((CBSPTree*)Obj1->BSPTree);
	
	// Store target tree for easy access
	TGTTree = ((CBSPTree*)Obj2->BSPTree);
	// Clip the tree against the CSG Tree
	CSGTree->ClipTree( CSGTree->RootNode, NULL, 0, TGTTree, ClipSolid1, TRUE );
	// First Make a copy of the CSG brush and manipulate this, instead
	// of the actual CSG brush, remember that we may need to add polys to several
	// intersecting brushes.
	CPYTree = CSGTree->CopyTree();
	TGTTree->ClipTree( TGTTree->RootNode, NULL, 0, CPYTree, ClipSolid2, FALSE);
	// Add all surviving polygons to the target tree
	for ( f = 0; f < CPYTree->PolyCount; f++ )
	{
		if ( !CPYTree->PolygonDeleted[f] ) TGTTree->AddPolygonEX( &CPYTree->Polygons[f] );
	} // Next f
	// Free Up the Copy of the CSG Tree
	//delete CPYTree; CPYTree = NULL;

}

void SubObject(Object *Obj2,Object *Obj1)
{
	int		  f;
	BOOL	  ClipSolid1 = FALSE, ClipSolid2 = FALSE;
	CBSPTree *CSGTree = NULL, *TGTTree = NULL, *CPYTree = NULL;

	ClipSolid1 = TRUE; ClipSolid2 = FALSE; 

	CSGTree = ((CBSPTree*)Obj1->BSPTree);

	// Store target tree for easy access
	TGTTree = ((CBSPTree*)Obj2->BSPTree);
	// Clip the tree against the CSG Tree
	CSGTree->ClipTree( CSGTree->RootNode, NULL, 0, TGTTree, ClipSolid1, TRUE );
	// First Make a copy of the CSG brush and manipulate this, instead
	// of the actual CSG brush, remember that we may need to add polys to several
	// intersecting brushes.
	CPYTree = CSGTree->CopyTree();
	TGTTree->ClipTree( TGTTree->RootNode, NULL, 0, CPYTree, ClipSolid2, FALSE);
	// When in Difference Mode Invert The Copied Trees polygons
	CPYTree->InvertPolys();
	// Add all surviving polygons to the target tree
	for ( f = 0; f < CPYTree->PolyCount; f++ )
	{
		if ( !CPYTree->PolygonDeleted[f] ) TGTTree->AddPolygonEX( &CPYTree->Polygons[f] );
	} // Next f
	// Free Up the Copy of the CSG Tree
	//delete CPYTree; CPYTree = NULL;
	//TGTTree->RenderBSPPolys(0);

	TGTTree->Commit(Obj2);
	Obj2->CalcTexCoord(128,128,Vertex(0,0,0),0,0);
}


bool AddObject(Object *Obj2,Object *Obj1)
{
	BOOL	  ClipSolid1 = FALSE, ClipSolid2 = FALSE;
	CBSPTree *CSGTree = NULL, *TGTTree = NULL, *CPYTree = NULL;

	int Oldnbf1,Oldnbf2;

	Oldnbf1=Obj1->nb2poly;
	Oldnbf2=Obj2->nb2poly;

	((CBSPTree*)Obj1->BSPTree)->ClipTree( ((CBSPTree*)Obj1->BSPTree)->RootNode, NULL, 0, ((CBSPTree*)Obj2->BSPTree), TRUE, TRUE);
	((CBSPTree*)Obj2->BSPTree)->ClipTree( ((CBSPTree*)Obj2->BSPTree)->RootNode, NULL, 0, ((CBSPTree*)Obj1->BSPTree), TRUE, FALSE);



	if ( (Obj1->BSPTree->PolyCount!=Oldnbf1)&&(Obj2->BSPTree->PolyCount!=Oldnbf2) )
	{
		Obj1->BSPTree->Commit(Obj1);
		Obj2->BSPTree->Commit(Obj2);//AddTo(Obj1);
		return true;
	}
	else
   
	{
		Obj1->BSPTree->Commit(Obj1);
		Obj2->BSPTree->Commit(Obj2);
		return false;
	}
	//dk->DelObject(daObj);
}

void UpdateBSPTrees( )
{
	int		  f;
	BOOL	  ClipSolid1 = FALSE, ClipSolid2 = FALSE;
	CBSPTree *CSGTree = NULL, *TGTTree = NULL, *CPYTree = NULL;
/*
	// Compile Mini-BSP Trees.
	for ( b = 0; b < BrushCount; b++ ){
		// Clear previously created tree
		if ( Brushes[b].BSPTree ) {
			delete ((CBSPTree*)Brushes[b].BSPTree);
			Brushes[b].BSPTree = NULL;
		} // End If
		if ( Brushes[b].BSPTree == NULL ) Brushes[b].BSPTree = new CBSPTree;
		((CBSPTree*)Brushes[b].BSPTree)->InitPolygons( &Brushes[b], 1, FALSE );
	} // Next Brush
*/
	Object *daObj;
	for (daObj=dk->FirstObject;daObj!=NULL;daObj=daObj->Next)
	{
		if (daObj->BSPTree)
		{
			delete daObj->BSPTree;
			daObj->BSPTree=NULL;
		}

		if (daObj->BSPTree==NULL)
			daObj->BSPTree=new CBSPTree;

		daObj->BSPTree->InitPolygons(daObj,1,FALSE);
	}

	
	// Setup our solid clipping flags
	switch ( g_iCSGMode ) 
	{
		case CSG_DIFFERENCE:
			ClipSolid1 = TRUE; ClipSolid2 = FALSE; 
			break;
		case CSG_INTERSECTION:
			ClipSolid1 = FALSE; ClipSolid2 = FALSE; 
			break;
	} // End Switch

/*
	if ( g_iCSGMode != CSG_NONE ) {
		// Store CSG Brush for easy access
		CSGTree = ((CBSPTree*)Brushes[g_iCSGBrush].BSPTree);
		// Perform op with CSG brush on each normal brush
		for ( b = 0; b < BrushCount; b++ ) {
			if ( b == g_iCSGBrush ) continue;
			if ( !BoundingBoxesIntersect(Brushes[g_iCSGBrush].Bounds, Brushes[b].Bounds) ) continue;
			// Store target tree for easy access
			TGTTree = ((CBSPTree*)Brushes[b].BSPTree);
			// Clip the tree against the CSG Tree
			CSGTree->ClipTree( CSGTree->RootNode, NULL, 0, TGTTree, ClipSolid1, TRUE );
			// First Make a copy of the CSG brush and manipulate this, instead
			// of the actual CSG brush, remember that we may need to add polys to several
			// intersecting brushes.
			CPYTree = CSGTree->CopyTree();
			TGTTree->ClipTree( TGTTree->RootNode, NULL, 0, CPYTree, ClipSolid2, FALSE);
			// When in Difference Mode Invert The Copied Trees polygons
			if ( g_iCSGMode == CSG_DIFFERENCE ) CPYTree->InvertPolys();
			// Add all surviving polygons to the target tree
			for ( f = 0; f < CPYTree->PolyCount; f++ ){
				if ( !CPYTree->PolygonDeleted[f] ) TGTTree->AddPolygonEX( &CPYTree->Polygons[f] );
			} // Next f
			// Free Up the Copy of the CSG Tree
			delete CPYTree; CPYTree = NULL;
			if ( g_iCSGMode == CSG_INTERSECTION) TGTTree->InitPolygons( &Brushes[b], 1, TRUE);
		} // Next Brush
	} // End if CSG Mode != CSG_NONE
*/
	if ( g_iCSGMode != CSG_NONE ) 
	{
		// Store CSG Brush for easy access
		CSGTree = ((CBSPTree*)dk->FirstObject->BSPTree);
		// Perform op with CSG brush on each normal brush
		for ( daObj=dk->FirstObject->Next; daObj!=NULL; daObj=daObj->Next) 
		{
			//if ( b == g_iCSGBrush ) continue;
			//if ( !BoundingBoxesIntersect(Brushes[g_iCSGBrush].Bounds, Brushes[b].Bounds) ) continue;

			// Store target tree for easy access
			TGTTree = ((CBSPTree*)daObj->BSPTree);
			// Clip the tree against the CSG Tree
			CSGTree->ClipTree( CSGTree->RootNode, NULL, 0, TGTTree, ClipSolid1, TRUE );
			// First Make a copy of the CSG brush and manipulate this, instead
			// of the actual CSG brush, remember that we may need to add polys to several
			// intersecting brushes.
			CPYTree = CSGTree->CopyTree();
			TGTTree->ClipTree( TGTTree->RootNode, NULL, 0, CPYTree, ClipSolid2, FALSE);
			// When in Difference Mode Invert The Copied Trees polygons
			if ( g_iCSGMode == CSG_DIFFERENCE ) CPYTree->InvertPolys();
			// Add all surviving polygons to the target tree
			for ( f = 0; f < CPYTree->PolyCount; f++ ){
				if ( !CPYTree->PolygonDeleted[f] ) TGTTree->AddPolygonEX( &CPYTree->Polygons[f] );
			} // Next f
			// Free Up the Copy of the CSG Tree
			delete CPYTree; CPYTree = NULL;
			TGTTree->RenderBSPPolys(0);
			//if ( g_iCSGMode == CSG_INTERSECTION) TGTTree->InitPolygons( daObj, 1, TRUE);
			//TGTTree->RenderBSPPolys(0);
		} // Next Brush
	} // End if CSG Mode != CSG_NONE


	/*
	// Now perform a union on all the resulting Trees.
	// THIS is how we perform pre-compile Hidden Surface removal.
	for ( b = 0; b < BrushCount; b++ ) {
		if ( b == g_iCSGBrush && g_iCSGMode != CSG_NONE) continue;
		((CBSPTree*)Brushes[b].BSPTree)->m_bMisc = FALSE;
		for ( int o = 0; o < BrushCount; o++ ) {
			if ( o == b || (o == g_iCSGBrush && g_iCSGMode != CSG_NONE)) continue;
			if (((CBSPTree*)Brushes[o].BSPTree)->m_bMisc == TRUE) continue;
			if ( BoundingBoxesIntersect(Brushes[o].Bounds, Brushes[b].Bounds) == TRUE ) {
				((CBSPTree*)Brushes[o].BSPTree)->ClipTree( ((CBSPTree*)Brushes[o].BSPTree)->RootNode, NULL, 0, ((CBSPTree*)Brushes[b].BSPTree), TRUE, TRUE);
				((CBSPTree*)Brushes[b].BSPTree)->ClipTree( ((CBSPTree*)Brushes[b].BSPTree)->RootNode, NULL, 0, ((CBSPTree*)Brushes[o].BSPTree), TRUE, FALSE);
			} //End If Bound Boxes Intersect
			// Because we do a role reversal for each brush in the tree
			// the below line ensures that each tree is only clipped once.
			((CBSPTree*)Brushes[b].BSPTree)->m_bMisc = TRUE;
		} // End For o
	} // End For b
*/

	Object *g_iCSGBrush=dk->FirstObject;

	// Now perform a union on all the resulting Trees.
	// THIS is how we perform pre-compile Hidden Surface removal.
	for ( daObj=dk->FirstObject; daObj!=NULL; daObj=daObj->Next ) 
	{
		if ( daObj == g_iCSGBrush && g_iCSGMode != CSG_NONE) continue;
		((CBSPTree*)daObj->BSPTree)->m_bMisc = FALSE;
		for ( Object *daO=dk->FirstObject; daO!=NULL; daO=daO->Next ) 
		{
			if ( daO == daObj || (daO == g_iCSGBrush && g_iCSGMode != CSG_NONE)) continue;
			if (((CBSPTree*)daO->BSPTree)->m_bMisc == TRUE) continue;

			//if ( BoundingBoxesIntersect(Brushes[o].Bounds, Brushes[b].Bounds) == TRUE ) 
			{
				((CBSPTree*)daO->BSPTree)->ClipTree( ((CBSPTree*)daO->BSPTree)->RootNode, NULL, 0, ((CBSPTree*)daObj->BSPTree), TRUE, TRUE);
				((CBSPTree*)daObj->BSPTree)->ClipTree( ((CBSPTree*)daObj->BSPTree)->RootNode, NULL, 0, ((CBSPTree*)daO->BSPTree), TRUE, FALSE);
			} //End If Bound Boxes Intersect
			// Because we do a role reversal for each brush in the tree
			// the below line ensures that each tree is only clipped once.
			((CBSPTree*)daObj->BSPTree)->m_bMisc = TRUE;
		} // End For o
	} // End For b

	/*
	// Compile final BSP if enabled
	if (g_bCompileFinal ) {	
		// Delete the CSG Brush as we must not include
		// this brush in the final BSP Compile process.
		if ( g_iCSGMode != CSG_NONE ) {
			delete (CBSPTree*)Brushes[g_iCSGBrush].BSPTree;
			Brushes[g_iCSGBrush].BSPTree = NULL;
		} // End If
		if ( FinalBSP == NULL ) FinalBSP = new CBSPTree;
		// Do the final compile
		FinalBSP->InitPolygons( Brushes, BrushCount, TRUE);
	} // End If
	*/
}

void HollowObject(Object *Obj)
{
	int i,j,k;


	Obj->CalcAllPlanes();


	if (Obj->BSPTree==NULL)
	{
		Obj->BSPTree=new CBSPTree;
		Obj->BSPTree->InitPolygons(Obj,1,FALSE);
	}

    //i=0;
	for (i=0;i<Obj->nb2poly;i++)
	{
		dk->AddObject();
		dk->NextObject->AllocatePoly(0,Obj->pl[i].nb2vert*2);

		int nb2Poly=2+Obj->pl[i].nb2vert;//+(2*(Obj->pl[i].nb2vert-2));

		dk->NextObject->AllocatePoly(nb2Poly,0);

		int nSide=Obj->pl[i].nb2vert;
		dk->NextObject->AllocateUV(0,(nSide*2)+(nSide*4));

		

		// caping
		dk->NextObject->pl[0].Allocate(dk->NextObject,1,nSide);
		dk->NextObject->pl[1].Allocate(dk->NextObject,1,nSide);
		int TexAv=0;

		for (j=0;j<nSide;j++)
		{
			dk->NextObject->pl[0].nbvert[nSide-j-1]=(nSide-1-j)*2;
			dk->NextObject->pl[0].Tex[0][nSide-j-1]=TexAv++;

			dk->NextObject->pl[1].nbvert[nSide-j-1]=(j*2)+1;
			dk->NextObject->pl[1].Tex[0][nSide-j-1]=TexAv++;

		}

		// get center of polygon
		Vertex PolyCenter;

		for (j=0;j<nSide;j++)
		{
			PolyCenter+=Obj->pv[Obj->pl[i].nbvert[j]];
		}
		PolyCenter/=nSide;

		// extruding 

		for (j=0;j<nSide;j++)
		{
			dk->NextObject->pl[j+2].Allocate(dk->NextObject,1,4);

			dk->NextObject->pv[j*2]=(Obj->pv[Obj->pl[i].nbvert[j]]-PolyCenter);
			dk->NextObject->pv[j*2].vx*=3;
			dk->NextObject->pv[j*2].vy*=3;
			dk->NextObject->pv[j*2].vz*=3;

			dk->NextObject->pv[j*2+1]=dk->NextObject->pv[j*2];

			dk->NextObject->pv[j*2]+=PolyCenter;
			

			//*dk->NextObject->pv[j*2+1]=(*Obj->pv[Obj->pl[i].nbvert[j]]-PolyCenter);
			//*dk->NextObject->pv[j*2+1]*=100.0f;
			dk->NextObject->pv[j*2+1]-=(Obj->pl[i].Normale*8.0f);
			dk->NextObject->pv[j*2+1]+=PolyCenter;

				
			dk->NextObject->pl[j+2].nbvert[3]=(j*2);
			dk->NextObject->pl[j+2].nbvert[2]=((j*2)+2)%(nSide*2);
			dk->NextObject->pl[j+2].nbvert[1]=((j*2)+3)%(nSide*2);
			dk->NextObject->pl[j+2].nbvert[0]=((j*2)+1)%(nSide*2);

			for (k=0;k<4;k++)
				dk->NextObject->pl[j+2].Tex[0][k]=TexAv++;//k+(nSide*2)+(j*nSide);
		}

		//CalcTexCoord(dk->NextObject,128,128,*dk->NextObject->pv[0],0,0);

        dk->NextObject->CalcAllPlanes();
        Obj->CalcAllPlanes();

		dk->NextObject->BSPTree=new CBSPTree;
		dk->NextObject->BSPTree->InitPolygons(dk->NextObject,1,FALSE);

		UnionObject(Obj,dk->NextObject);
        //AddObject(dk->NextObject,Obj);
		dk->NextObject->BSPTree->Commit(dk->NextObject);
        //Obj->BSPTree->Commit(Obj);
		if (Obj->pl[0].Maps[0]!=NULL)
			dk->NextObject->ApplyTexture(Obj->pl[0].Maps[0]);
		else
			dk->NextObject->ApplyTexture(Obj->Tex1);
	    dk->NextObject->CalcTexCoord(128,128,Vertex(0,0,0),0,0);

	}
	dk->DelObject(Obj);
}

void CreateCube(Vertex Start,double X,double Y,double Z,bool Snap)
{
    Vertex End;
    Object *Obj;
    int i;
    double Valu=X/128.0f;
    double Valv=Y/128.0f;
//    double Valw=Z/128.0f;

    if (CurrentObj==NULL) Obj=dk->NextObject;
        else Obj=CurrentObj;

	Obj->pv[0]=Vertex(0,0,0)+Start;
	Obj->pv[1]=Vertex(X,0,0)+Start;
	Obj->pv[2]=Vertex(X,Y,0)+Start;
	Obj->pv[3]=Vertex(0,Y,0)+Start;
	Obj->pv[4]=Vertex(0,0,Z)+Start;
	Obj->pv[5]=Vertex(X,0,Z)+Start;
	Obj->pv[6]=Vertex(X,Y,Z)+Start;
	Obj->pv[7]=Vertex(0,Y,Z)+Start;
    for (i=0;i<8;i++)
    {
        Obj->pv[i].Snap(Vertex(8,8,8));

    }

    Obj->AllocateUV(0,24);
    for (i=0;i<24;i++)
    {
        Obj->puv[0][i].u=0;
        Obj->puv[0][i].v=0;
    }
    Obj->AllocatePoly(6,0);
    for (i=0;i<6;i++)
    {
        Obj->pl[i].Allocate(dk->NextObject,1,4);
        Obj->pl[i].Tex[0][0]=0;
        Obj->pl[i].Tex[0][1]=0;
        Obj->pl[i].Tex[0][2]=0;
        Obj->pl[i].Tex[0][3]=0;
    }
    // bottom
    Obj->pl[0].nbvert[0]=3;
    Obj->pl[0].nbvert[1]=2;
    Obj->pl[0].nbvert[2]=1;
    Obj->pl[0].nbvert[3]=0;
    // top
    Obj->pl[1].nbvert[0]=4;
    Obj->pl[1].nbvert[1]=5;
    Obj->pl[1].nbvert[2]=6;
    Obj->pl[1].nbvert[3]=7;
    // front
    Obj->pl[2].nbvert[0]=7;
    Obj->pl[2].nbvert[1]=3;
    Obj->pl[2].nbvert[2]=0;
    Obj->pl[2].nbvert[3]=4;
    // back
    Obj->pl[3].nbvert[0]=1;
    Obj->pl[3].nbvert[1]=2;
    Obj->pl[3].nbvert[2]=6;
    Obj->pl[3].nbvert[3]=5;
    // left  
    Obj->pl[4].nbvert[0]=6;
    Obj->pl[4].nbvert[1]=2;
    Obj->pl[4].nbvert[2]=3;
    Obj->pl[4].nbvert[3]=7;
    // right
    Obj->pl[5].nbvert[0]=0;
    Obj->pl[5].nbvert[1]=1;
    Obj->pl[5].nbvert[2]=5;
    Obj->pl[5].nbvert[3]=4;

    //CalcTexCoord(Obj,128,128,Start,tmpuv);
    Obj->Selected=true;
}

void CreateCubeSpecial(Vertex Start,double X,double Y,double Z,bool Snap)
{
    Vertex End;
    Object *Obj;
    int i;
    double Valu=X/128.0f;
    double Valv=Y/128.0f;
//    double Valw=Z/128.0f;

    if (CurrentObj==NULL) Obj=dk->NextObject;
        else Obj=CurrentObj;

	Obj->pv[0]=Vertex(0,0,0)+Start;
	Obj->pv[1]=Vertex(X,0,0)+Start;
	Obj->pv[2]=Vertex(X,Y,0)+Start;
	Obj->pv[3]=Vertex(0,Y,0)+Start;

	Obj->pv[4]=Vertex(0,0,Z)+Start;
	Obj->pv[5]=Vertex((X/2),0,Z)+Start;
	Obj->pv[6]=Vertex((X/2),(Y/2),Z)+Start;
	Obj->pv[7]=Vertex(0,(Y/2),Z)+Start;

    for (i=0;i<8;i++)
    {
        Obj->pv[i].Snap(Vertex(8,8,8));

    }

    Obj->AllocateUV(0,24);

    for (i=0;i<24;i++)
    {
        Obj->puv[0][i].u=0;
        Obj->puv[0][i].v=0;
    }

    Obj->AllocatePoly(6,0);

    for (i=0;i<6;i++)
    {
        Obj->pl[i].Allocate(dk->NextObject,1,4);
        Obj->pl[i].Tex[0][0]=0;
        Obj->pl[i].Tex[0][1]=0;
        Obj->pl[i].Tex[0][2]=0;
        //Obj->pl[i].Tex[0][3]=0;
    }

    // bottom
    Obj->pl[0].nbvert[0]=3;
    Obj->pl[0].nbvert[1]=2;
    Obj->pl[0].nbvert[2]=1;
    Obj->pl[0].nbvert[3]=0;
    // top
    Obj->pl[1].nbvert[0]=4;
    Obj->pl[1].nbvert[1]=5;
    Obj->pl[1].nbvert[2]=6;
    Obj->pl[1].nbvert[3]=7;
    // front
    Obj->pl[2].nbvert[0]=7;
    Obj->pl[2].nbvert[1]=3;
    Obj->pl[2].nbvert[2]=0;
    Obj->pl[2].nbvert[3]=4;
    // back
    Obj->pl[3].nbvert[0]=1;
    Obj->pl[3].nbvert[1]=2;
    Obj->pl[3].nbvert[2]=6;
    Obj->pl[3].nbvert[3]=5;
    // left  
    Obj->pl[4].nbvert[0]=6;
    Obj->pl[4].nbvert[1]=2;
    Obj->pl[4].nbvert[2]=3;
    Obj->pl[4].nbvert[3]=7;
    // right
    Obj->pl[5].nbvert[0]=0;
    Obj->pl[5].nbvert[1]=1;
    Obj->pl[5].nbvert[2]=5;
    Obj->pl[5].nbvert[3]=4;

    Obj->Selected=true;
}

void CreateNGon(Vertex Start,double Length,double Height,Vertex mX,Vertex mY,Vertex mZ,int nSide)
{
    Vertex End;
    Object *Obj;
    int i,j;

    if (CurrentObj==NULL) Obj=dk->NextObject;
        else Obj=CurrentObj;

    for (i=0;i<nSide;i++)
    {
        double tx=(cos(((2*PI)/nSide)*i)*Length);
        double ty=(sin(((2*PI)/nSide)*i)*Length);

        Vertex tmp=(mX*tx)+(mY*ty)+Start;
	    Obj->pv[i*2]=tmp;

	    tmp=(mX*tx)+(mY*ty)+(mZ*Height)+Start;
        Obj->pv[i*2+1]=tmp;
    }

    Obj->AllocateUV(0,(nSide*2)+(4*nSide));

    Obj->AllocatePoly(2+nSide,0);

    Obj->pl[0].Allocate(dk->NextObject,1,nSide);
    Obj->pl[1].Allocate(dk->NextObject,1,nSide);

    for (i=0;i<nSide;i++)
    {
        Obj->pl[2+i].Allocate(dk->NextObject,1,4);

        Obj->pl[0].nbvert[i]=(nSide-1-i)*2;
        Obj->pl[0].Tex[0][i]=i;

        Obj->pl[1].nbvert[i]=(i*2)+1;
        Obj->pl[1].Tex[0][i]=i+nSide;
    }

    for (i=0;i<nSide;i++)
    {
        Obj->pl[i+2].nbvert[0]=(i*2);
        Obj->pl[i+2].nbvert[1]=((i*2)+2)%(nSide*2);
        Obj->pl[i+2].nbvert[2]=((i*2)+3)%(nSide*2);
        Obj->pl[i+2].nbvert[3]=((i*2)+1)%(nSide*2);

        for (j=0;j<4;j++)
            Obj->pl[i+2].Tex[0][j]=j+(nSide*2)+(i*nSide);
    }

    Obj->Selected=true;
}



void SetSelectedNGon(int nbSide)
{
	int i;

	dk->DeleteBufVert();

	Object *daObj=dk->FirstObject;
	while (daObj!=NULL)
	{
		if (daObj->Selected)
		{
			CurrentObj=daObj;

			Vertex daMin,daMax,daCenter;
			Vertex VX,VY,VZ;

			daMin=daObj->Min;
			daMax=daObj->Max;
			daCenter=(daMin+((daMax-daMin))/2.0f);

			double Length,Height;

			switch(GetView())
			{
			
			case 1:
				VX=Vertex(1,0,0);
				VY=Vertex(0,1,0);
				VZ=Vertex(0,0,1);
				Length=Pythagore(daMax.vx-daMin.vx,daMax.vy-daMin.vy)/2;
				Height=daMax.vz-daMin.vz;
				daCenter.vz=0;
				break;
			case 2:
				VX=Vertex(1,0,0);
				VY=Vertex(0,0,-1);
				VZ=Vertex(0,1,0);
				Length=Pythagore(daMax.vx-daMin.vx,daMax.vz-daMin.vz)/2;
				Height=daMax.vy-daMin.vy;
				daCenter.vy=0;
				break;
			case 3:
				VX=Vertex(0,-1,0);
				VY=Vertex(0,0,-1);
				VZ=Vertex(1,0,0);
				Length=Pythagore(daMax.vx-daMin.vx,daMax.vy-daMin.vy)/2;
				Height=daMax.vy-daMin.vy;
				daCenter.vy=0;
				break;
			case 4:
				VX=Vertex(-1,0,0);
				VY=Vertex(0,-1,0);
				VZ=Vertex(0,0,-1);
				Length=Pythagore(daMax.vx-daMin.vx,daMax.vy-daMin.vy)/2;
				Height=daMax.vz-daMin.vz;
				daCenter.vz=0;
				break;
			case 5:
				VX=Vertex(-1,0,0);
				VY=Vertex(0,0,1);
				VZ=Vertex(0,-1,0);
				Length=Pythagore(daMax.vx-daMin.vx,daMax.vy-daMin.vy)/2;
				Height=daMax.vz-daMin.vz;
				daCenter.vz=0;
				break;
			case 6:
				VX=Vertex(0,1,0);
				VY=Vertex(0,0,1);
				VZ=Vertex(-1,0,0);
				Length=Pythagore(daMax.vx-daMin.vx,daMax.vy-daMin.vy)/2;
				Height=daMax.vz-daMin.vz;
				daCenter.vz=0;
				break;
			default:
				VX=Vertex(1,0,0);
				VY=Vertex(0,1,0);
				VZ=Vertex(0,0,1);
				Length=Pythagore(daMax.vx-daMin.vx,daMax.vy-daMin.vy)/2;
				Height=daMax.vz-daMin.vz;
				daCenter.vz=0;
				break;


			}
			Length/=1.4142135623730950488016887242097f; //sqrt(2)


			//CurrentObj->AllocatePoly(nbSide+2,2*nbSide);
			daObj->AllocatePoly(0,2*nbSide);
			CreateNGon(daCenter,Length,Height,VX,VY,VZ,nbSide);
			CurrentObj->CalcTexCoord(128,128,CurrentObj->pv[CurrentObj->pl[0].nbvert[0]],0,0);

			// add vertex to buffer

			for (i=0;i<daObj->nb2vert;i++)
			{
				dk->AddBufVert(&daObj->pv[i],daObj);
				daObj->pv[i].Selected=true;
			}

		}
		daObj=daObj->Next;
	}

}

void Symetry(Vertex value)
{

	Vertex daMin,daMax,daCenter;
	Vertex VX,VY,VZ;

	daCenter=dk->cSel->GetCenterOfSel(&daMin,&daMax);
/*
	daMin=daObj->GetMinOf();
	daMax=daObj->GetMaxOf();
	daCenter=(daMin+((daMax-daMin))/2.0f);
*/
    VertBuf *daBufVert;
	Vertex temp,temp2;

    daBufVert=dk->FirstBufVert;
    while(daBufVert!=NULL)
    {
		temp=daBufVert->AncVal;
		temp2=temp;
		
		if (value.vx==1) temp2.vx=temp.vx+2*(daCenter.vx-temp.vx);
		if (value.vy==1) temp2.vy=temp.vy+2*(daCenter.vy-temp.vy);
		if (value.vz==1) temp2.vz=temp.vz+2*(daCenter.vz-temp.vz);

        daBufVert->IsNow(temp2);

        daBufVert=daBufVert->Next;
    }

	dk->UpdateBuf();
}


void RotateBuf(Vertex Vect,double ng)
{
	Vertex daMin,daMax,daCenter;
	Vertex value,value2;
    double nx2,ny2,nz2;
    double m1,m2,m3,m4,m5,m6,m7,m8,m9;


	daCenter=dk->cSel->GetCenterOfSel(&daMin,&daMax);
	/*
	daMin=dk->cSel->get
	daMax=daObj->GetMaxOf();
	daCenter=(daMin+((daMax-daMin))/2.0f);
*/
	ng*=PI;
	ng/=180;

    nx2=(Vect.vx*Vect.vx);
    ny2=(Vect.vy*Vect.vy);
    nz2=(Vect.vz*Vect.vz);

    m1=(nx2+((1-nx2)*cos(ng)));
    m2=((Vect.vx*Vect.vy*(1-cos(ng)))-(Vect.vz*sin(ng)));
    m3=((Vect.vx*Vect.vz*(1-cos(ng)))+(Vect.vy*sin(ng)));
    m4=((Vect.vx*Vect.vy*(1-cos(ng)))+(Vect.vz*sin(ng)));
    m5=(ny2+((1-ny2)*cos(ng)));
    m6=((Vect.vy*Vect.vz*(1-cos(ng)))-(Vect.vx*sin(ng)));
    m7=((Vect.vx*Vect.vz*(1-cos(ng)))-(Vect.vy*sin(ng)));
    m8=((Vect.vy*Vect.vz*(1-cos(ng)))+(Vect.vx*sin(ng)));
    m9=(nz2+((1-nz2)*cos(ng)));

	VertBuf *daVert;

	daVert=dk->FirstBufVert;
	while(daVert!=NULL)
	{
		value=(daVert->AncVal-daCenter);

		value2.vx=value.vx*m1+value.vy*m2+value.vz*m3;
		value2.vy=value.vx*m4+value.vy*m5+value.vz*m6;
		value2.vz=value.vx*m7+value.vy*m8+value.vz*m9;

		daVert->IsNow((value2+daCenter));

		daVert=daVert->Next;
	}

	dk->UpdateBuf();
}

void HollowSelectedObject(void)
{
	for (Object *daObj=dk->FirstObject;daObj!=NULL;daObj)
	{
		Object *daNext=daObj->Next;

		UpdateBspTree(daObj);

		if (daObj->Selected)
			HollowObject(daObj);

		daObj=daNext;
	}

	dk->cSel->UnSelectAll(false);
	dk->DeleteBufVert();
}

void UpdateBspTree(Object *daObj)
{
	daObj->CalcAllPlanes();

	if (daObj->BSPTree)
	{
		delete daObj->BSPTree;
		daObj->BSPTree=NULL;
	}

	if (daObj->BSPTree==NULL)
		daObj->BSPTree=new CBSPTree;

	daObj->BSPTree->InitPolygons(daObj,1,FALSE);
}
void SubSelectedObject(void)
{
	for (Object *daObj=dk->FirstObject;daObj!=NULL;daObj=daObj->Next)
	{
		Object *daNext=daObj->Next;

		if (daObj->Selected)
		{
			for (Object *daObj2=dk->FirstObject;daObj2!=NULL;daObj2=daObj2->Next)
			{
				if (daObj!=daObj2)
				{
					UpdateBspTree(daObj);
					UpdateBspTree(daObj2);

					SubObject(daObj2,daObj);
					//daObj2->BSPTree->Commit(daObj2);
				}
			}
		}
	}

	dk->cSel->UnSelectAll(false);
	dk->DeleteBufVert();
}

void AddSelectedObject(void)
{
	for (Object *daObj=dk->FirstObject;daObj!=NULL;)
	{
		Object *ObjTmp=daObj->Next;
		Object *daNext=daObj->Next;

		if (daObj->Selected)
		{
			Object *daObj2=daObj->Next;
			for (;daObj2!=NULL;daObj2=daObj2->Next)
			{
				if (daObj2->Selected)
				{
					UpdateBspTree(daObj);
					UpdateBspTree(daObj2);

					if (AddObject(daObj,daObj2))
					{
						// addition successfull
						//dk->DelObject(daObj);
						break;
					}
					else
					{
						// no addition at all

					}
				}
			}
		}
		daObj=ObjTmp;
	}

	dk->cSel->UnSelectAll(false);
	dk->DeleteBufVert();
}

void ApplyTexture(char *TexName)
{
	for (Object *daObj=dk->FirstObject;daObj!=NULL;daObj=daObj->Next)
	{
		if (daObj->Selected)
		{
			CTexture *daTex;
			daTex=dk->AddTex(TexName);
			daTex->Type=TEXTURE_FILE;
			daTex->Load();
//			strcpy(daObj->TexName1,TexName);
			daObj->Tex1=daTex;

		}
	}

}

Object *BuildCutter(Vertex v1,Vertex v2)
{

    Vertex End;
    Object *Obj;
    int i;

	Vertex Dif=v2-v1;
	Vertex Zd;

	dap.PlanOfView(View,dk->Active);
	/*

	if (Dif.vx==0) Zd.vx=10;
	if (Dif.vy==0) Zd.vy=10;
	if (Dif.vz==0) Zd.vz=10;
*/
	Zd=dap.pZ;
	Vertex Start(0,0,0);
	Zd.vx*=1000;
	Zd.vy*=1000;
	Zd.vz*=1000;



	Obj=new Object();
	Obj->AllocatePoly(0,8);

	Dif.vx*=100;
	Dif.vy*=100;
	Dif.vz*=100;

	Obj->pv[0]=v1-(Zd)-(Dif);
	Obj->pv[1]=v1+(Zd)-(Dif);
	Obj->pv[2]=v2+(Zd)+(Dif);
	Obj->pv[3]=v2-(Zd)+(Dif);

	Vertex Normale;
	Vertex *dpv=Obj->pv;

	Normale.Cross(dpv[1]-dpv[0], dpv[2]-dpv[0]);
	Normale.Normalize();

	Normale.vx*=1000;
	Normale.vy*=1000;
	Normale.vz*=1000;

	Obj->pv[4]=v1-Zd-(Normale)-(Dif);
	Obj->pv[5]=v1+Zd-(Normale)-(Dif);
	Obj->pv[6]=v2+Zd-(Normale)+(Dif);
	Obj->pv[7]=v2-Zd-(Normale)+(Dif);


    Obj->AllocateUV(0,24);
    for (i=0;i<24;i++)
    {
        Obj->puv[0][i].u=0;
        Obj->puv[0][i].v=0;
    }
    Obj->AllocatePoly(6,0);
    for (i=0;i<6;i++)
    {
        Obj->pl[i].Allocate(dk->NextObject,1,4);
        Obj->pl[i].Tex[0][0]=0;
        Obj->pl[i].Tex[0][1]=0;
        Obj->pl[i].Tex[0][2]=0;
        Obj->pl[i].Tex[0][3]=0;
    }
    // bottom
    Obj->pl[0].nbvert[0]=3;
    Obj->pl[0].nbvert[1]=2;
    Obj->pl[0].nbvert[2]=1;
    Obj->pl[0].nbvert[3]=0;
    // top
    Obj->pl[1].nbvert[0]=4;
    Obj->pl[1].nbvert[1]=5;
    Obj->pl[1].nbvert[2]=6;
    Obj->pl[1].nbvert[3]=7;
    // front
    Obj->pl[2].nbvert[0]=7;
    Obj->pl[2].nbvert[1]=3;
    Obj->pl[2].nbvert[2]=0;
    Obj->pl[2].nbvert[3]=4;
    // back
    Obj->pl[3].nbvert[0]=1;
    Obj->pl[3].nbvert[1]=2;
    Obj->pl[3].nbvert[2]=6;
    Obj->pl[3].nbvert[3]=5;
    // left  
    Obj->pl[4].nbvert[0]=6;
    Obj->pl[4].nbvert[1]=2;
    Obj->pl[4].nbvert[2]=3;
    Obj->pl[4].nbvert[3]=7;
    // right
    Obj->pl[5].nbvert[0]=0;
    Obj->pl[5].nbvert[1]=1;
    Obj->pl[5].nbvert[2]=5;
    Obj->pl[5].nbvert[3]=4;

    //CalcTexCoord(Obj,128,128,Start,tmpuv);
    Obj->Selected=true;

	Obj->CalcAllPlanes();
	Obj->BSPTree=new CBSPTree;
	Obj->BSPTree->InitPolygons(Obj,1,FALSE);

	return Obj;
}

int GetNbSelectedObjects(void)
{
	int nbObjSel=0;

	for (Object *daObj2=dk->FirstObject;daObj2!=NULL;daObj2=daObj2->Next)
		if (daObj2->Selected) nbObjSel++;

	return nbObjSel;
}
