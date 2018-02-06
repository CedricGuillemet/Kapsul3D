//---------------------------------------------------------------------------
#include "stdafx.h"

//#include "memmgr/mmgr.h"

unsigned int G_Unique=0;

CKMesh::CKMesh()
{
    Prev=NULL;
    Next=NULL;
    Selected=false;

    matrix=new CKMatrix();
    matrix->Identity();
    nb2vert=0;
    nb2poly=0;
    pv=NULL;
	pl=NULL;
    FrameInd=0;
    nb2Frames=1;

    Tex1=NULL;//dk->FirstTexture;
	Tex2=NULL;
	Tex3=NULL;
	Tex4=NULL;

    puv[0]=NULL;
    puv[1]=NULL;
    puv[2]=NULL;
    puv[3]=NULL;

    nbTexCanals=1;
    nbTexCoords[0]=NULL;
    nbTexCoords[1]=NULL;
    nbTexCoords[2]=NULL;
    nbTexCoords[3]=NULL;

	Unique=G_Unique++;
	BSPTree=NULL;
	Tag=0;

//	Indices=NULL;
//	nbIndices=NULL;
//	Opv=NULL;
//	TexInd[0]=NULL;
//	TexInd[1]=NULL;
//	TexInd[2]=NULL;
//	TexInd[3]=NULL;

//	Ocl=NULL;
//	Oclp=NULL;
	Hided=false;
	NeedTexRecalc=false;

//	IntPtrPoly=NULL;
//	nb2IntPtrPoly=0;
//	IntPtrAvPoly=0;

//	IntPtrUV=NULL;
//	nb2IntPtrUV=0;
//IntPtrAvUV=0;

	m_Scene=NULL;
	Skel=NULL;

}

CKMesh::CKMesh(CKScene *daScene,CKMesh *daPrev,CKMesh *daNext)
{
	m_Scene=daScene;
    Prev=daPrev;
    Next=daNext;
    Selected=false;

    matrix=new CKMatrix();
    matrix->Identity();
    nb2vert=0;
    nb2poly=0;
    pv=NULL;
	pl=NULL;
    FrameInd=0;
    nb2Frames=1;

    Tex1=m_Scene->FirstTexture;
	Tex2=NULL;
	Tex3=NULL;
	Tex4=NULL;

    puv[0]=NULL;
    puv[1]=NULL;
    puv[2]=NULL;
    puv[3]=NULL;

    nbTexCanals=1;
    nbTexCoords[0]=NULL;
    nbTexCoords[1]=NULL;
    nbTexCoords[2]=NULL;
    nbTexCoords[3]=NULL;
	Unique=G_Unique++;
	BSPTree=NULL;
	Tag=0;

//	Indices=NULL;
//	nbIndices=NULL;
//	Opv=NULL;
//	TexInd[0]=NULL;
//	TexInd[1]=NULL;
//	TexInd[2]=NULL;
//	TexInd[3]=NULL;

//	Ocl=NULL;
//	Oclp=NULL;
	Hided=false;
	NeedTexRecalc=false;

//	IntPtrPoly=NULL;
//	nb2IntPtrPoly=0;
//	IntPtrAvPoly=0;

//	IntPtrUV=NULL;
//	nb2IntPtrUV=0;
//	IntPtrAvUV=0;

	m_Scene=NULL;
	Skel=NULL;
}

/*
void CKMesh::OptimGeom(void)
{
	return;

	// security
	if (!OptimDirty)
		return ;

	int nbTris=0;
	int i,j,k;
	int nbTexCoordOptim=0;

	for (i=0;i<nb2poly;i++)
		nbTris+=pl[i].nb2vert-2;

	nbIndices=nbTris*3;

	if (Oldindices!=nbIndices)
	{
		if (Indices!=NULL) 
			free(Indices);
		if (Opv!=NULL) 
			free(Opv);
		if (TexInd[0]!=NULL) 
			free(TexInd[0]);
		if (TexInd[1]!=NULL) 
			free(TexInd[1]);
		if (TexInd[2]!=NULL) 
			free(TexInd[2]);
		if (TexInd[3]!=NULL) 
			free(TexInd[3]);
		if (Ocl!=NULL) 
			free(Ocl);
		if (Oclp!=NULL) 
			free(Oclp);

		Indices=(unsigned int *)malloc(nbIndices*sizeof(unsigned int));
		Opv=(Vertex *)malloc(nbIndices*sizeof(Vertex));
		Ocl=(GLColor*)malloc(nbIndices*sizeof(GLColor));
		Oclp=(GLColor*)malloc(nbIndices*sizeof(GLColor));

		for (i=0;i<4;i++)
		{
			if (puv[i]!=NULL) 
			{ 
				TexInd[i]=(UVCoords*)malloc(nbIndices*sizeof(UVCoords)); 
				nbTexCoordOptim=i+1; 
			}
		}
		
	}

	int IndAv=0;

	for (i=0;i<nb2poly;i++)
	{
		for (j=0;j<pl[i].nb2vert-2;j++)
		{
			Indices[IndAv]=IndAv;
			Indices[IndAv+1]=IndAv+1;
			Indices[IndAv+2]=IndAv+2;

			Opv[IndAv]=pv[pl[i].nbvert[0]];
			Opv[IndAv+1]=pv[pl[i].nbvert[j+1]];
			Opv[IndAv+2]=pv[pl[i].nbvert[j+2]];

			Ocl[IndAv].r=255;
			Ocl[IndAv+1].r=255;
			Ocl[IndAv+2].r=255;

			Ocl[IndAv].g=((pv[pl[i].nbvert[0]].Selected|Selected)?0:255);
			Ocl[IndAv+1].g=((pv[pl[i].nbvert[j+1]].Selected|Selected)?0:255);
			Ocl[IndAv+2].g=((pv[pl[i].nbvert[j+2]].Selected|Selected)?0:255);

			Ocl[IndAv].b=Ocl[IndAv].g;
			Ocl[IndAv+1].b=Ocl[IndAv+1].g;
			Ocl[IndAv+2].b=Ocl[IndAv+2].g;

			// par poly
			Oclp[IndAv].r=255;
			Oclp[IndAv+1].r=255;
			Oclp[IndAv+2].r=255;

			Oclp[IndAv].g=((pl[i].Selected|Selected)?0:255);
			Oclp[IndAv+1].g=((pl[i].Selected|Selected)?0:255);
			Oclp[IndAv+2].g=((pl[i].Selected|Selected)?0:255);

			Oclp[IndAv].b=Oclp[IndAv].g;
			Oclp[IndAv+1].b=Oclp[IndAv+1].g;
			Oclp[IndAv+2].b=Oclp[IndAv+2].g;


			for (k=0;k<nbTexCoordOptim;k++)
			{
				TexInd[k][IndAv]=puv[k][pl[i].Tex[k][0]];
				TexInd[k][IndAv+1]=puv[k][pl[i].Tex[k][j+1]];
				TexInd[k][IndAv+2]=puv[k][pl[i].Tex[k][j+2]];
			}
			IndAv+=3;
		}
	}
	OptimDirty=false;
}
*/
CKMesh::~CKMesh()
{
    int j;

    delete matrix;

    if (pv!=NULL) free(pv);

    if (pl!=NULL) free(pl);

/*
	if (Indices!=NULL) 
		free(Indices);
	if (Opv!=NULL) 
		free(Opv);
	if (TexInd[0]!=NULL) 
		free(TexInd[0]);
	if (TexInd[1]!=NULL) 
		free(TexInd[1]);
	if (TexInd[2]!=NULL) 
		free(TexInd[2]);
	if (TexInd[3]!=NULL) 
		free(TexInd[3]);
	if (Ocl!=NULL) 
		free(Ocl);
		*/
}

bool CKMesh::AllocatePoly(int nb2p, int nb2v)
{
    bool value;
	
    if (nb2p!=0)
    {
        if (nb2poly!=0)
        {
            if (nb2p!=nb2poly)
			{
                pl=(CKPolygon*)realloc(pl,sizeof(CKPolygon)*nb2p);
				if (nb2p>nb2poly)
					memset(&pl[nb2poly],0,sizeof(CKPolygon)*(nb2p-nb2poly));
			}
        }
        else
        {
            pl=(CKPolygon*)malloc(sizeof(CKPolygon)*nb2p);
			memset(pl,0,sizeof(CKPolygon)*nb2p);
        }
		
        if (nb2p!=0)
        {
            nb2poly=nb2p;
        }

    }
	
    if (nb2v!=0)
    {
        if (nb2vert!=0)
        {
            pv=(Vertex*)realloc(pv,sizeof(Vertex)*nb2v);
			if (nb2v>nb2vert)
				memset(&pv[nb2vert],0,sizeof(Vertex)*(nb2v-nb2vert));
        }
        else
        {
            pv=(Vertex*)malloc(sizeof(Vertex)*nb2v);
			memset(pv,0,sizeof(Vertex)*nb2v);
        }
		
        if (nb2v!=0)
        {
            nb2vert=nb2v;
        }

    }
	
	// Preallocation
	/*
	if ((nb2vert!=0)&&(nb2poly!=0))
	{
		if (IntPtrPoly==NULL)
		{
			nb2IntPtrPoly=nb2poly*4;
			IntPtrPoly=(int*)malloc(nb2IntPtrPoly*sizeof(int));
			memset(IntPtrPoly,0,nb2IntPtrPoly*sizeof(int));
			IntPtrAvPoly=0;
		}
		else
		{
			if ((nb2poly*4)>nb2IntPtrPoly)
			{
				nb2IntPtrPoly=nb2poly*4;
				IntPtrPoly=(int*)realloc(IntPtrPoly,nb2IntPtrPoly*sizeof(int));
				if (!KeepIndex) IntPtrAvPoly=0;
			}
		}
		if (IntPtrUV==NULL)
		{
			nb2IntPtrUV=nb2poly*4;
			IntPtrUV=(int*)malloc(nb2IntPtrUV*sizeof(int));
			memset(IntPtrUV,0,nb2IntPtrUV*sizeof(int));
			IntPtrAvUV=NULL;
		}
		else
		{
			if ((nb2poly*4)>nb2IntPtrUV)
			{
				nb2IntPtrUV=nb2poly*4;
				IntPtrUV=(int*)realloc(IntPtrUV,nb2IntPtrUV*sizeof(int));
				if (!KeepIndex) IntPtrAvUV=0;
			}
		}
	}
    */
    return value;
}

inline int CKMesh::GetIntPtrPoly(int iSize)
{
	int *iVal;

	if ((IntPtrAvPoly+iSize)>nb2IntPtrPoly)
	{
		// too much -> realloc
		nb2IntPtrPoly+=200;
		IntPtrPoly=(int*)realloc(IntPtrPoly,nb2IntPtrPoly*sizeof(int));
	}

	// ok
	iVal=&IntPtrPoly[IntPtrAvPoly];
	IntPtrAvPoly+=iSize;
	return iVal;
}
/*
inline int *CKMesh::GetIntPtrUV(int iSize)
{
	int *iVal;

	if ((IntPtrAvUV+iSize)>nb2IntPtrUV)
	{
		// too much -> realloc
		nb2IntPtrUV+=200;
		IntPtrUV=(int*)malloc(nb2IntPtrUV*sizeof(int));
	}

	// ok
	iVal=&IntPtrUV[IntPtrAvUV];
	IntPtrAvUV+=iSize;
	return iVal;
}
*/
/*
bool CKMesh::AllocateUV(int Canal, int nb2uv)
{
    if (nb2uv!=0)
    {
        if (nbTexCoords[Canal]!=0)
        {
            if (nb2uv!=nbTexCoords[Canal])
                puv[Canal]=(UVCoords*)realloc(puv[Canal],sizeof(UVCoords)*nb2uv);
        }
        else
        {
            puv[Canal]=(UVCoords*)malloc(sizeof(UVCoords)*nb2uv);
        }

        if (nb2uv!=0)
        {
            nbTexCoords[Canal]=nb2uv;
        }

		nbTexCanals=Canal+1;
    }

    return true;
}
*/
int CKMesh::DelSelectedFaces(void)
{
    int value;
    int realnbFaces=0,i,j,nb2fav=0;
    CKPolygon *newpf;

    for (i=0;i<nb2poly;i++)
    {
		bool NoVertSel=false;
		for (j=0;j<pl[i].nb2vert;j++)
			NoVertSel|=!pv[pl[i].nbvert[j]].Selected;

        if (NoVertSel)
        {
            realnbFaces++;
        }
    }

    if (realnbFaces==nb2poly) return 0;

    newpf=(CKPolygon*)malloc(sizeof(CKPolygon)*realnbFaces);
	memset(newpf,0,sizeof(CKPolygon)*realnbFaces);

    for (i=0;i<nb2poly;i++)
    {
        if (!pl[i].Selected)
        {
			newpf[nb2fav].Allocate(this,1,pl[i].nb2vert);

			for (j=0;j<pl[i].nb2vert;j++)
			{
				newpf[nb2fav].nbvert[j]=pl[i].nbvert[j];
				if (pl[i].Tex[0]!=NULL) newpf[nb2fav].Tex[0][j]=pl[i].Tex[0][j];
				if (pl[i].Tex[1]!=NULL) newpf[nb2fav].Tex[1][j]=pl[i].Tex[1][j];
				if (pl[i].Tex[2]!=NULL) newpf[nb2fav].Tex[2][j]=pl[i].Tex[2][j];
				if (pl[i].Tex[3]!=NULL) newpf[nb2fav].Tex[3][j]=pl[i].Tex[3][j];
			}

			newpf[nb2fav].Normale=pl[i].Normale;
			newpf[nb2fav].D=pl[i].D;
			newpf[nb2fav].Selected=false;

			for (j=0;j<8;j++)
				newpf[nb2fav].Maps[j]=pl[i].Maps[j];

            nb2fav++;
        }
    }


    value=nb2poly-realnbFaces;
    for (i=0;i<nb2poly;i++)
    {
		for (j=0;j<4;j++)
			if (pl[i].Tex[j]!=NULL) free(pl[i].Tex[j]);
		free(pl[i].nbvert);
	}

    
	free(this->pl);

    pl=newpf;
    nb2poly=realnbFaces;

    DelUnusedVertex();

    return value;
}

int CKMesh::DelSelectedVertex(void)
{
    int value=0;
    int i,j;

    for (i=0;i<nb2poly;i++)
    {
		bool AllVertSel=false;
		for (j=0;j<pl[i].nb2vert;j++)
			//if (pv[pl[i].nbvert[j]].Selected) AllVertSel=false;
			AllVertSel|=(pv[pl[i].nbvert[j]].Selected);

        if (AllVertSel)
            pl[i].Selected=true;
    }

    for (i=0;i<nb2poly;i++)
    {
        if ( pl[i].Selected )
        {
			for (j=0;j<pl[i].nb2vert;j++)
	            pv[pl[i].nbvert[j]].Selected=true;
        }
    }


    DelSelectedFaces();

    return value;
}

int CKMesh::DelUnusedVertex(void)
{
    int *TempBool;
    int value,i,j;
    Vertex *danewpv;
    int realnb2v=0,nbvav=0;


    TempBool=new int[nb2vert];
    memset(TempBool,0,sizeof(int)*nb2vert);

    for (i=0;i<nb2poly;i++)
    {
		for (j=0;j<pl[i].nb2vert;j++)
			TempBool[pl[i].nbvert[j]]=1;
    }

    for (i=0;i<nb2vert;i++)
    {
        if (TempBool[i])
        {
            realnb2v++;
        }
    }

    //danewpv=new Vertex [realnb2v];
	danewpv=(Vertex*)malloc(sizeof(Vertex)*realnb2v);
	memset(danewpv,0,sizeof(Vertex)*realnb2v);
    for (i=0;i<nb2vert;i++)
    {
        if (TempBool[i])
        {
            danewpv[nbvav]=pv[i];
            TempBool[i]=nbvav;
            nbvav++;
        }
    }

    for (i=0;i<nb2poly;i++)
    {
		for (j=0;j<pl[i].nb2vert;j++)
	        pl[i].nbvert[j]=TempBool[pl[i].nbvert[j]];
    }


    //delete [] pv ;
	free(pv);

    pv=danewpv;

    value=nb2vert-realnb2v;
    nb2vert=realnb2v;

    delete [] TempBool;

    return value;
}

void CKMesh::SelectedFaceToScene(CKScene *DstScene)
{
    int i,j;
    //int *TempBool;
    int nbvav=0;
    int nbfav=0;
    bool HasSome=false;
	int rnb2pl=0;



	// get # of poly to copy
    for (i=0;i<nb2poly;i++)
        if (pl[i].Selected)
			rnb2pl++;

	if (rnb2pl==0) return;

	// create dest CKMesh & copy vertex

    DstScene->AddMesh();

    DstScene->NextMesh->AllocatePoly(rnb2pl,nb2vert);
	memcpy(DstScene->NextMesh->pv,pv,sizeof(Vertex)*nb2vert);

	// copy uvcoords
	for (i=0;i<4;i++)
	{
		if (puv[i]!=NULL) 
		{
			DstScene->NextMesh->AllocateUV(i,nbTexCoords[i]);
			memcpy(DstScene->NextMesh->puv[i],puv[i],sizeof(UVCoords)*nbTexCoords[i]);
		}
	}

	// copy poly
    for (i=0;i<nb2poly;i++)
    {
		/*
		bool AllFaceSel=true;
		for (j=0;j<pl[i].nb2vert;j++)
			if (!pv[pl[i].nbvert[j]].Selected)
				AllFaceSel=false;
*/
        if ( /*AllFaceSel|*/pl[i].Selected)
        {
			DstScene->NextMesh->pl[nbfav].Allocate(DstScene->NextMesh,1,pl[i].nb2vert);
			for (j=0;j<pl[i].nb2vert;j++)
			{
				DstScene->NextMesh->pl[nbfav].nbvert[j]=pl[i].nbvert[j];
				if (pl[i].Tex[0]!=NULL) DstScene->NextMesh->pl[nbfav].Tex[0][j]=pl[i].Tex[0][j];
				if (pl[i].Tex[1]!=NULL) DstScene->NextMesh->pl[nbfav].Tex[1][j]=pl[i].Tex[1][j];
				if (pl[i].Tex[2]!=NULL) DstScene->NextMesh->pl[nbfav].Tex[2][j]=pl[i].Tex[2][j];
				if (pl[i].Tex[3]!=NULL) DstScene->NextMesh->pl[nbfav].Tex[3][j]=pl[i].Tex[3][j];
			}

			DstScene->NextMesh->pl[nbfav].Normale=pl[i].Normale;
			DstScene->NextMesh->pl[nbfav].D=pl[i].D;
			DstScene->NextMesh->pl[nbfav].Selected=false;


			for (int j=0;j<8;j++)
			{
				if (pl[i].Maps[j]!=NULL) 
				{
					DstScene->NextMesh->pl[i].Maps[j]=DstScene->AddTex(pl[i].Maps[j]->FileName);
					DstScene->NextMesh->pl[i].Maps[j]->Type=pl[i].Maps[j]->Type;
				}
			}


            nbfav++;
        }
    }

	DstScene->NextMesh->DelUnusedVertex();

	DstScene->NextMesh->Selected=true;
    for (i=0;i<DstScene->NextMesh->nb2vert;i++)
        DstScene->AddBufVert(&DstScene->NextMesh->pv[i]);

	DstScene->NextMesh->UpdateMesh();
}

void CKMesh::IsCopyOf(CKMesh *cmpt)
{
    int i,j;

	// Old face and Vertex
/*
    Allocate(cmpt->nb2faces,cmpt->nb2vert);

    for (i=0;i<nb2faces;i++)
        *pf[i]=*cmpt->pf[i];
*/


	// Texture coordiantes

	for (i=0;i<nbTexCanals;i++)
	{
		if (cmpt->nbTexCoords[i]!=0)
		{
			AllocateUV(i, cmpt->nbTexCoords[i]);
			for (j=0;j<cmpt->nbTexCoords[i];j++)
			{
				puv[i][j]=cmpt->puv[i][j];
			}
			nbTexCoords[i]=cmpt->nbTexCoords[i];
		}
	}

	// Polygones

	AllocatePoly(cmpt->nb2poly,cmpt->nb2vert);
	for (i=0;i<cmpt->nb2poly;i++)
	{
		pl[i].IsCopyOf(this,&cmpt->pl[i]);
	}

    for (i=0;i<nb2vert;i++)
        pv[i]=cmpt->pv[i];


	// CKMesh name

    Name=cmpt->Name;

    //Mat=cmpt->Mat;

    Tex1=cmpt->Tex1;
//    strcpy(TexName1,cmpt->TexName1);

    nb2Frames=cmpt->nb2Frames;
    
    memcpy(matrix,cmpt->matrix,sizeof(CKMatrix));

//    Modified=cmpt->Modified;
	// force selected to false because nothing is in Vertex buffer
    Selected=false;//cmpt->Selected;
	Unique=cmpt->Unique;


	Color.bRed =cmpt->Color.bRed;
	Color.bGreen =cmpt->Color.bGreen;
	Color.bBlue =cmpt->Color.bBlue;

	SetAutoTexRecalc(cmpt->GetAutoTexRecalc());
}

// Frames

void CKMesh::SetNbFrames(int _nbFrames)
{
//    int i;
    /*
    if (nb2f!=0)
    {
        if (nb2faces!=0)
        {
            for (i=nb2f;i<nb2faces;i++)
                delete pf[i];

            pf=(Face**)realloc(pf,sizeof(Face*)*nb2f);
        }
        else
        {
            pf=(Face**)malloc(sizeof(Face*)*nb2f);
        }

        if (nb2f!=0)
        {
            for (i=nb2faces;i<nb2f;i++)
                pf[i]=new(Face);

            nb2faces=nb2f;
        }
    }
*/
    if (_nbFrames!=nb2Frames)
    {
        if (_nbFrames==0)
            _nbFrames=1;

        if (nb2vert!=0)
        {
        /*
            for (i=(_nbFrames*nb2vert);i<(nb2Frames*nb2vert);i++)
                delete pv[i];
        */
            pv=(Vertex*)realloc(pv,(sizeof(Vertex)*nb2vert)*_nbFrames);
        }
        else
        {
            pv=(Vertex*)malloc((sizeof(Vertex)*nb2vert)*_nbFrames);
        }
/*
        for (i=(nb2vert*nb2Frames);i<(nb2vert*_nbFrames);i++)
            pv[i]=new(Vertex);
*/
        nb2Frames=_nbFrames;
    }
}

void CKMesh::SetFrameInd(int _FrameInd)
{
    FrameInd=_FrameInd;
}


void CKMesh::CalcAllPlanes(void)
{
	//CKPolygon daPoly;
	
	for (int i=0;i<nb2poly;i++)
		pl[i].CalcPlan(pv,pi);
}

bool CKMesh::IsConvexe(void)
{
	int i,j;

	if ((nb2poly==1)||(nb2poly==0))
		return false;

	for (i=0;i<nb2poly;i++)
	{
		if (i!=j)
		{
			for (j=0;j<nb2poly;j++)
			{
				if (pl[i].GetDist(pv[pl[i].nbvert[0]])>0.0001)
					return false;
			}
		}
	}

	return true;
}

// rebuild al coplanar polygons 
// BEWARE: All previous polygons are convexe ones !!!
/*
int CKMesh::RecursRebuild(CKPolygon **dapl,Vertex **dapv
*/
void CKMesh::RebuildPoly(void)
{
	CKMesh *TmpObj;
	int i,j;
	int PolyAv=0;
	int nb2Tris=0;

	// Find total Tris numbers

	for (i=0;i<nb2poly;i++)
	{
		nb2Tris+=(pl[i].nb2vert-2);
	}

	TmpObj->AllocatePoly(nb2Tris,0);

	// build tris from polys

	for (i=0;i<nb2poly;i++)
	{
		for (j=0;j<(pl[i].nb2vert-2);j++)
		{
			TmpObj->pl[PolyAv].Allocate(TmpObj,1,3);
			TmpObj->pl[PolyAv].nbvert[0]=pl[i].nbvert[0];
			TmpObj->pl[PolyAv].nbvert[1]=pl[i].nbvert[1+(j*2)];
			TmpObj->pl[PolyAv].nbvert[2]=pl[i].nbvert[2+(j*2)];
		}

	}

	// calculate normales

	for (i=0;i<TmpObj->nb2poly;i++)
		TmpObj->pl[i].CalcPlan(pv);

	//

		
}

void CKMesh::CollapseIdenticalVertex(void)
{
	int i,j,k,l;
	Vertex Temp;

	//return;

	for (i=0;i<nb2vert;i++)
	{
		Temp=pv[i];
		for (j=0;j<nb2vert;j++)
		{
			if (i!=j)
			{

				if ( (fabs(pv[j].x-Temp.x)<0.0001)&&
					(fabs(pv[j].y-Temp.y)<0.0001)&&
					(fabs(pv[j].z-Temp.z)<0.0001) )
				{
					// found identical 
					// so, replace

					for (k=0;k<nb2poly;k++)
					{
						for (l=0;l<pl[k].nb2vert;l++)
						{
							if (pl[k].nbvert[l]==j)
							{
								pl[k].nbvert[l]=i;
							}
						}
					}
				}
			}
		}
	}
}

void CKMesh::Translate(Vertex TransVal)
{
	int i;

	for (i=0;i<nb2vert;i++)
		pv[i]+=TransVal;
}

int CKMesh::FindPoly(int i1,int i2,CKPolygon *Else)
{
	int i,j;

	for (i=0;i<nb2poly;i++)
	{
		for (j=0;j<pl[i].nb2vert;j++)
		{
			if ((&pl[i])!=Else)
			{
				if  ( ((pl[i].nbvert[j]==i1)&&(pl[i].nbvert[((j+1)%pl[i].nb2vert)]==i2))||
					((pl[i].nbvert[j]==i2)&&(pl[i].nbvert[((j+1)%pl[i].nb2vert)]==i1)) ) 
				{
					return i;
				}
			}
		}
	}

	return -1;
}


void CKMesh::TranslateVertex(int Indice,Vertex TransVal)
{
	int i,j;
	int plav=0;
	CKPolygon *daPoly[20];
	int PrevID[20],NextID[20];
	int indav;
	int nb2pols;
	int nb2uv=0;
	bool HasInd;

	// search poly using that vertex
	for (i=0;i<nb2poly;i++)
	{
		HasInd=false;

		for (j=0;j<pl[i].nb2vert;j++)
		{
			if (pl[i].nbvert[j]==Indice)
			{
				daPoly[plav]=&pl[i];
				PrevID[plav]=( ((j-1)<0)?(pl[i].nb2vert-1):(j-1));
				NextID[plav]=((j+1)%pl[i].nb2vert);
				
				PrevID[plav]=pl[i].nbvert[PrevID[plav]];
				NextID[plav]=pl[i].nbvert[NextID[plav]];
				HasInd=true;
				plav++;
			}
		}

		if (!HasInd)
			nb2uv+=pl[i].nb2vert;
	}
	
	// remove indice from polygon

	nb2pols=0;

	for (i=0;i<plav;i++)
	{
		indav=0;

		if (daPoly[i]->nb2vert>3)
		{
			nb2pols++;
			int CurnbPoly=0;

			for (j=0;j<daPoly[i]->nb2vert;j++)
			{
				if (daPoly[i]->nbvert[j]!=Indice)
				{
					daPoly[i]->nbvert[indav++]=daPoly[i]->nbvert[j];
					CurnbPoly++;
				}

				
			}
			daPoly[i]->Allocate(this,1,CurnbPoly/*daPoly[i]->nb2vert-1*/);
			nb2uv+=CurnbPoly;
		}
		else
		{
			daPoly[i]=NULL;
			nb2uv+=3;
		}
	}

	// simply create Triangle ! more next time.

	int TempIndTri=nb2poly;
	AllocatePoly(nb2poly+nb2pols,0);

	nb2pols=0;
	for (i=0;i<plav;i++)
	{
		if (daPoly[i]!=NULL)
		{
			pl[TempIndTri+nb2pols].Allocate(this,1,3);

			pl[TempIndTri+nb2pols].nbvert[0]=PrevID[i];
			pl[TempIndTri+nb2pols].nbvert[1]=Indice;
			pl[TempIndTri+nb2pols].nbvert[2]=NextID[i];

			nb2uv+=3;
			nb2pols++;
		}
	}

	// and finally translate da vertex

	pv[Indice]=TransVal;
	AllocateUV(0,nb2uv);

	/*
	// look for what to do

	for (i=0;i<plav;i++)
	{
		retPoly=FindPoly(PrevID[i],NextID[i],daPoly[i]);

		if (retPoly==-1)
		{
			// vertex inside polygon


		}
		else
		{


		}




	}
	*/


}



void CKMesh::ApplyTexture(CKTexture *daTex,int TexNb)
{
	int i;

	switch (TexNb)
	{
	case 0:
		Tex1=daTex;
		for (i=0;i<nb2poly;i++)
			pl[i].Maps[0]=daTex;
		break;
	case 1:
		Tex2=daTex;
		for (i=0;i<nb2poly;i++)
			pl[i].Maps[1]=daTex;
		break;
	case 2:
		Tex3=daTex;
		for (i=0;i<nb2poly;i++)
			pl[i].Maps[2]=daTex;
		break;
	case 3:
		Tex4=daTex;
		for (i=0;i<nb2poly;i++)
			pl[i].Maps[3]=daTex;
		break;
	}
}


void CKMesh::GenerateUVPerFace(int CanalNb)
{
	int i,j;
	int coordAv=0;

    for (i=0;i<nb2poly;i++)
    {
        for (j=0;j<pl[i].nb2vert;j++)
        {
			pl[i].Tex[CanalNb][j]=coordAv++;
		}
	}
	AllocateUV(CanalNb,coordAv);
	//memset(puv[0],0,coordAv*sizeof(UVCoords));
}

void CKMesh::CalcTexCoord(int tsx,int tsy,Vertex Origin,double uvu,double uvv)
{
    int i,j;
    Vertex Normale;
    int vav=0;
	int nb2uv=0;

	for (i=0;i<nb2poly;i++)
    {
        for (j=0;j<pl[i].nb2vert;j++)
			pl[i].Tex[0][j]=nb2uv++;
	}
	AllocateUV(0,nb2uv);



	

    for (i=0;i<nb2poly;i++)
    {
        Vertex v1=pv[pl[i].nbvert[0]]-pv[pl[i].nbvert[1]];
        Vertex v2=pv[pl[i].nbvert[2]]-pv[pl[i].nbvert[1]];
//Vertex result;
	Normale.x = (v1.y * v2.z) - (v1.z * v2.y);
	Normale.y = (v1.z * v2.x) - (v1.x * v2.z);
	Normale.z = (v1.x * v2.y) - (v1.y * v2.x);

        //Normale=CrossProduct(&v1,&v2);
        //Normale.Normalize();

        for (j=0;j<pl[i].nb2vert;j++)
        {
            pl[i].Tex[0][j]=vav;
            vav++;

            if ( (fabs(Normale.x)>fabs(Normale.y))&& (fabs(Normale.x)>fabs(Normale.z)))
            {
                puv[0][pl[i].Tex[0][j]].u=uvu+(pv[pl[i].nbvert[j]].z-Origin.z)/tsx;
                puv[0][pl[i].Tex[0][j]].v=uvv+(pv[pl[i].nbvert[j]].y-Origin.y)/tsy;
            }
            else
            if ( (fabs(Normale.y)>fabs(Normale.z))&& (fabs(Normale.y)>fabs(Normale.x)))
            {
                puv[0][pl[i].Tex[0][j]].u=uvu+(pv[pl[i].nbvert[j]].x-Origin.x)/tsx;
                puv[0][pl[i].Tex[0][j]].v=uvv+(pv[pl[i].nbvert[j]].z-Origin.z)/tsy;
            }
            else
            {
                puv[0][pl[i].Tex[0][j]].u=uvu+(pv[pl[i].nbvert[j]].x-Origin.x)/tsx;
                puv[0][pl[i].Tex[0][j]].v=uvv+(pv[pl[i].nbvert[j]].y-Origin.y)/tsy;

            }
        }

		// UV tweaker
		float tweaku,tweakv;
		if (pl[i].TweakUV)
		{
			float cs1=cos((pl[i].Rotate*PI)/360.0f);
			float sn1=sin((pl[i].Rotate*PI)/360.0f);

			for (j=0;j<pl[i].nb2vert;j++)
			{
				tweaku=puv[0][pl[i].Tex[0][j]].u;
				tweakv=puv[0][pl[i].Tex[0][j]].v;

				puv[0][pl[i].Tex[0][j]].u=tweaku*cs1-tweakv*sn1;
				puv[0][pl[i].Tex[0][j]].v=tweaku*sn1+tweakv*cs1;

                puv[0][pl[i].Tex[0][j]].u+=pl[i].TransU;
		        puv[0][pl[i].Tex[0][j]].v+=pl[i].TransV;

                puv[0][pl[i].Tex[0][j]].u*=(pl[i].ScaleU+((pl[i].ScaleU>=0)?1.0f:0));
		        puv[0][pl[i].Tex[0][j]].v*=(pl[i].ScaleV+((pl[i].ScaleV>=0)?1.0f:0));

			}
		}
    }
}

void CKMesh::UpdateMesh(void)
{
	if (NeedTexRecalc)
	{
		if (puv[0]!=NULL)
		{
			CalcTexCoord(256,256,pv[pl[0].nbvert[0]],puv[0][pl[0].Tex[0][0]].u,puv[0][pl[0].Tex[0][0]].v);
		}
	}
	GetMinMax();
	//m_Scene->
}

void CKMesh::GetMinMax(void)
{
	if (pv!=NULL)
	{
		Min=pv[0];
		Max=pv[0];
		for (int i=1;i<nb2vert;i++)
		{
			Min.GetMinOf(pv[i]);
			Max.GetMaxOf(pv[i]);
		}
	}
	else
	{
		Min=Vertex(0,0,0);
		Max=Vertex(0,0,0);
	}
}

void CKMesh::SetAutoTexRecalc(bool _autouv)
{
	NeedTexRecalc=_autouv;
	if (NeedTexRecalc)
	{
		GenerateUVPerFace(0);
		if (puv[0]!=NULL)
		{
			puv[0][pl[0].Tex[0][0]].u=0;
			puv[0][pl[0].Tex[0][0]].v=0;
		}
		UpdateMesh();
	}
}

void CKMesh::Lathing(CKShape *Shp,int NbTours,double U,double V)
{
	float MatRot[9];
	int i;
	int daCount=0;

	if (Shp->NextSegment->Next==Shp->FirstSegment)
	{
		MessageBox(NULL,"Shape must not be closed.","Shape error",MB_ICONERROR|MB_OK);
		return;
	}


	for (CKSegment *daSeg=Shp->FirstSegment;daSeg!=NULL;daSeg=daSeg->Next)
		daCount++;

	// check closed
	Vertex Dir=Shp->NextSegment->Dot-Shp->FirstSegment->Dot;
	Dir.Normalize();

	int nb2poly=(daCount-1)*NbTours;
	int nb2vert=(daCount)*NbTours;

	AllocatePoly(nb2poly,nb2vert);

	AllocateUV(0,nb2vert+daCount);


	int Vertav=0;
	int ind2=0;
	for (i=0;i<NbTours;i++)
	{
		double a=(((2*PI)/(double)NbTours)*(double)i);
		MatRot[0]=(Dir.x*Dir.x)+((1-(Dir.x*Dir.x))*cos(a));
		MatRot[1]=((Dir.x*Dir.y)*(1-cos(a)))-Dir.z*sin(a);
		MatRot[2]=((Dir.x*Dir.z)*(1-cos(a)))+(Dir.y*sin(a));

		MatRot[3]=((Dir.x*Dir.y)*(1-cos(a)))+(Dir.z*sin(a));
		MatRot[4]=(Dir.y*Dir.y)+((1-(Dir.y*Dir.y))*cos(a));
		MatRot[5]=((Dir.y*Dir.z)*(1-cos(a)))-Dir.x*sin(a);

		MatRot[6]=((Dir.x*Dir.z)*(1-cos(a)))-(Dir.y*sin(a));
		MatRot[7]=((Dir.y*Dir.z)*(1-cos(a)))+(Dir.x*sin(a));
		MatRot[8]=(Dir.z*Dir.z)+((1-(Dir.z*Dir.z))*cos(a));

		ind2=0;
		for (daSeg=Shp->FirstSegment;daSeg!=NULL;daSeg=daSeg->Next)
		{
			Vertex value;
			Vertex daVal=daSeg->Dot-Shp->FirstSegment->Dot;
			value.x=daVal.x*MatRot[0]+daVal.y*MatRot[1]+daVal.z*MatRot[2];
			value.y=daVal.x*MatRot[3]+daVal.y*MatRot[4]+daVal.z*MatRot[5];
			value.z=daVal.x*MatRot[6]+daVal.y*MatRot[7]+daVal.z*MatRot[8];

			pv[Vertav]=(value+Shp->FirstSegment->Dot);
			puv[0][Vertav].u=(double)((U/(double)NbTours)*(double)i);
			puv[0][Vertav].v=(double)((V/(double)daCount)*(double)ind2);
			Vertav++;
			ind2++;
		}
	}
	ind2=0;

	for (daSeg=Shp->FirstSegment;daSeg!=NULL;daSeg=daSeg->Next)
	{

		puv[0][Vertav].u=U;//(double)((1/(double)NbTours)*(double)i);
		puv[0][Vertav].v=(double)((V/(double)daCount)*(double)ind2);
		Vertav++;
		ind2++;
	}

	int plav=0;
	int ind=0;

	for (i=0;i<NbTours-1;i++)
	{
		for (daSeg=Shp->FirstSegment;daSeg->Next!=NULL;daSeg=daSeg->Next)
		{
			pl[plav].Allocate(this,1,4);
			pl[plav].nbvert[3]=ind;
			pl[plav].nbvert[2]=ind+1;
			pl[plav].nbvert[1]=daCount+ind+1;
			pl[plav].nbvert[0]=daCount+ind;

			pl[plav].Tex[0][0]=pl[plav].nbvert[0];
			pl[plav].Tex[0][1]=pl[plav].nbvert[1];
			pl[plav].Tex[0][2]=pl[plav].nbvert[2];
			pl[plav].Tex[0][3]=pl[plav].nbvert[3];
			plav++;

			ind++;
		}
		ind++;

		
	}
	ind2=0;
	for (daSeg=Shp->FirstSegment;daSeg->Next!=NULL;daSeg=daSeg->Next)
	{
		pl[plav].Allocate(this,1,4);
		pl[plav].nbvert[3]=ind;
		pl[plav].nbvert[2]=ind+1;
		pl[plav].nbvert[1]=ind2+1;
		pl[plav].nbvert[0]=ind2;

		pl[plav].Tex[0][0]=ind+daCount;
		pl[plav].Tex[0][1]=ind+daCount+1;
		pl[plav].Tex[0][2]=pl[plav].nbvert[2];
		pl[plav].Tex[0][3]=pl[plav].nbvert[3];
		plav++;

		ind++;
		ind2++;
	}
	CollapseIdenticalVertex();
	UpdateMesh();
}

#define EDGE_NOTUSED 0
#define EDGE_USEDBYSELECTEDPOLY 1
#define EDGE_USEDBYNONSELECTEDPOLY 2

class CKEdge
{
public:
	CKEdge() { Tag=0; };
	~CKEdge() {};
	int Src,Dst;
	int Tag;
	CKMesh *m_Mesh;
	int Poly;
};

// same wise testing as given

int CKMesh::FindEdge(int VtInd1,int VtInd2,int FromPoly,int &PolyNb,int &EdgeNb)
{
	for (int i=0;i<nb2poly;i++)
	{
		if (i!=FromPoly)
		{
			for (int j=0;j<pl[i].nb2vert;j++)
			{
				if ( ((pl[i].nbvert[j]==VtInd1)&&(pl[i].nbvert[(j+1)%pl[i].nb2vert]==VtInd2))||
					((pl[i].nbvert[j]==VtInd2)&&(pl[i].nbvert[(j+1)%pl[i].nb2vert]==VtInd1)) )
				{
					if (pl[i].Selected)
						return EDGE_USEDBYSELECTEDPOLY;
					else
						return EDGE_USEDBYNONSELECTEDPOLY;
				}
			}
		}
	}
	return EDGE_NOTUSED;
}

void CKMesh::Extrud(Vertex daVect,float Size,int nbSteps,float Scale,bool bCapping)
{
	int Count=0;
	int i,j;
	CKSegment *daSeg;
	vector<CKShape*> m_Shp;
	vector<CKEdge*> m_Edges;
	int PolyNb,EdgeNb;
	int UnusedEdgeCount;
	Vertex Center;

	// Get all the good edges
	InitAllPolyTag(0);

	for (i=0;i<nb2poly;i++)
	{
		if (pl[i].Selected)
		{
			for (int j=0;j<pl[i].nb2vert;j++)
			{
				int fdedge=FindEdge(pl[i].nbvert[j],pl[i].nbvert[(j+1)%pl[i].nb2vert],i,PolyNb,EdgeNb);

				if ((fdedge==EDGE_NOTUSED)||(fdedge==EDGE_USEDBYNONSELECTEDPOLY))
				{
					CKEdge *tmpEdg=new CKEdge;
					tmpEdg->Src=pl[i].nbvert[j];
					tmpEdg->Dst=pl[i].nbvert[(j+1)%pl[i].nb2vert];
					tmpEdg->m_Mesh=this;
					tmpEdg->Poly=i;
					m_Edges.push_back(tmpEdg);
				}
			}
		}
	}

	// build Shapes
	UnusedEdgeCount=m_Edges.size();

	int CurEdge=0;

	CKShape *CurShape=NULL;
	while (UnusedEdgeCount!=0)
	{
		if (CurShape==NULL)
		{
			CurShape=new CKShape;
			if (m_Edges[CurEdge]->Tag==0)
			{
				CurShape->AddSegment(pv[m_Edges[CurEdge]->Src]);
				CurShape->AddSegment(pv[m_Edges[CurEdge]->Dst]);
				pl[m_Edges[CurEdge]->Poly].Tag=(unsigned int)CurShape;
				m_Edges[CurEdge]->Tag=1;
				UnusedEdgeCount--;
			}
		}


		// Find next linked edge

		bool HasFound=false;
		for (i=0;i<m_Edges.size();i++)
		{
			if (m_Edges[i]->Tag==0)
			{
				if (m_Edges[CurEdge]->Dst==m_Edges[i]->Src)
				{
					// found next one
					HasFound=true;
					CurEdge=i;
					//CurShape->AddSegment(pv[pl[m_Edges[CurEdge]->Poly].nbvert[m_Edges[CurEdge]->Src]]);
					CKEdge *ed=m_Edges[CurEdge];
					int pvi=ed->Dst;

					CurShape->AddSegment(pv[pvi]);
					pl[m_Edges[CurEdge]->Poly].Tag=(unsigned int)CurShape;
					m_Edges[CurEdge]->Tag=1;
					UnusedEdgeCount--;
				}
			}
		}
		if (!HasFound)
		{
			// not found the consecutive edge so new shape 
			for (i=0;i<m_Edges.size();i++)
			{
				if (m_Edges[i]->Tag==0)
				{
					CurEdge=i;
					i=m_Edges.size();
				}
			
			}
/*
			delete m_Shp[m_Shp.size()-1];
			m_Shp.pop_back();
			m_Shp[m_Shp.size()-1]->Close();
			*/
			m_Shp.push_back(CurShape);
			CurShape=NULL;
		}

	}
	if (CurShape!=NULL) 
	{
		m_Shp.push_back(CurShape);
		CurShape=NULL;
	}

	// -- Detach Selected Faces ------------------------------------------------

	vector<int> m_VertInd;
	vector<CKShape*> m_shInd;
	Count=0;
	int tmptrf;

	// count vertex to duplicate and reup
	for (i=0;i<nb2poly;i++)
	{
		if (pl[i].Selected)
		{
			for (int j=0;j<pl[i].nb2vert;j++)
			{
				bool HasGood=false;
				// Is the indice already pushed?
				for (int k=0;k<m_VertInd.size();k++)
				{
					if (m_VertInd[k]==pl[i].nbvert[j])
					{
						HasGood=true;
						tmptrf=k;
						break;
					}
				}
				if (!HasGood)
				{
					m_VertInd.push_back(pl[i].nbvert[j]);
					m_shInd.push_back((CKShape*)pl[i].Tag);

					pl[i].nbvert[j]=Count+nb2vert;
					Count++;
				}
				else
				{
					pl[i].nbvert[j]=tmptrf+nb2vert;
				}
			}
		}
	}

	// Duplicate vertex
	int tmpnbv=nb2vert;
	AllocatePoly(0,nb2vert+Count);
	CKShape *ghshp;
	Vertex ctr;
	for (i=0;i<m_VertInd.size();i++)
	{
		pv[(i+tmpnbv)]=pv[m_VertInd[i]];
		
		if (Size!=0)
		{
			if (m_shInd[i]!=NULL)
			{
				ghshp=(CKShape*)m_shInd[i];
				ctr=ghshp->GetCenter();
				pv[(i+tmpnbv)]-=ctr;
				pv[(i+tmpnbv)].x*=Scale;
				pv[(i+tmpnbv)].y*=Scale;
				pv[(i+tmpnbv)].z*=Scale;
				pv[(i+tmpnbv)]+=ctr;
				pv[(i+tmpnbv)]+=m_shInd[i]->GetNormal()*Size;
			}
		}
		
	}

	// Fin -----------------------------------------------------------

	Vertex nVect;
	for (int ijshp=0;ijshp<m_Shp.size();ijshp++)
	{
		CKShape *daShp=m_Shp[ijshp];
		Center=daShp->GetCenter();
		if (daVect==Vertex(0,0,0))
			nVect=daShp->GetNormal();
		else
			nVect=daVect;

		int plav=nb2poly;
		int vtav=nb2vert;
		int txav=nbTexCoords[0];

		int nb2v=daShp->Count*(nbSteps+1);
		int nb2p=(daShp->Count-1)*nbSteps;

		
		AllocatePoly(plav+nb2p,vtav+nb2v);
		AllocateUV(0,txav+nb2v);

		float dscale=1;
		float dscaleuv=(1-Scale)/(float)nbSteps;
		// create vertex

		Count=0;

		for (i=0;i<(nbSteps+1);i++)
		{
			daSeg=daShp->FirstSegment;
			for (j=0;j<daShp->Count;j++)
			{
				pv[vtav+Count]=daSeg->Dot;
				pv[vtav+Count]-=Center;
				pv[vtav+Count].x*=dscale;
				pv[vtav+Count].y*=dscale;
				pv[vtav+Count].z*=dscale;

				pv[vtav+Count]+=Center;
				pv[vtav+Count]+=(nVect*((Size/nbSteps)*i));
				puv[0][txav+Count].u=(1.0f/(float)daShp->Count)*(float)j;
				puv[0][txav+Count].v=(1.0f/(float)(nbSteps+1))*(float)i;

				Count++;
				daSeg=daSeg->Next;
			}
			dscale-=dscaleuv;
		}

		// create polygons

		Count=0;
		for (i=0;i<nbSteps;i++)
		{
			for (j=0;j<(daShp->Count-1);j++)
			{
				//pv[Count++]=daSeg->Dot+(daVect*((Size/nbSteps)*i));
				pl[plav+Count].Allocate(this,1,4);

				pl[plav+Count].nbvert[0]=vtav+(j)+(i*daShp->Count);
				pl[plav+Count].nbvert[1]=vtav+(j+1)+(i*daShp->Count);
				pl[plav+Count].nbvert[2]=vtav+(j+1)+((i+1)*daShp->Count);
				pl[plav+Count].nbvert[3]=vtav+(j)+((i+1)*daShp->Count);

				pl[plav+Count].Tex[0][0]=txav+(j)+(i*daShp->Count);;
				pl[plav+Count].Tex[0][1]=txav+(j+1)+(i*daShp->Count);;
				pl[plav+Count].Tex[0][2]=txav+(j+1)+((i+1)*daShp->Count);;
				pl[plav+Count].Tex[0][3]=txav+(j)+((i+1)*daShp->Count);;
				pl[plav+Count].Selected=true;

				Count++;
			}
		}
	}

	if (m_Shp.size()!=0)
		CollapseIdenticalVertex();

	m_Shp.erase(m_Shp.begin(),m_Shp.end());
}


void CKMesh::InitAllPolyTag(unsigned int val)
{
	for (int i=0;i<nb2poly;i++)
	{
		pl[i].Tag=val;
	}
}	


void CKMesh::MergeMesh(CKMesh *msh)
{
	int vtav=nb2vert;
	int plav=nb2poly;
	int puvav[4];
	int i,j,k;
	int Oldnb2vert=nb2vert;

	for (i=0;i<1;i++)
	{
		puvav[i]=nbTexCoords[i];
		AllocateUV(i,nbTexCoords[i]+msh->nbTexCoords[i]);
	}

	AllocatePoly(nb2poly+msh->nb2poly,nb2vert+msh->nb2vert);
	
	for (i=0;i<msh->nb2vert;i++)
	{
		pv[vtav++]=msh->pv[i];
	}

	for (i=0;i<msh->nb2poly;i++)
	{
		pl[plav].Allocate(this,msh->nbTexCanals,msh->pl[i].nb2vert);

		for (k=0;k<msh->pl[i].nb2vert;k++)
		{
			pl[plav].nbvert[k]=msh->pl[i].nbvert[k]+Oldnb2vert;

			for (j=0;j<msh->nbTexCanals;j++)
			{
				pl[plav].Tex[j][k]=msh->pl[i].Tex[j][k];
			}
		}
		plav++;
	}
}

void CKMesh::Explode(CKScene *Dest,float Decal)
{
	int i,j,k;

	CalcAllPlanes();

	for (i=0;i<nb2poly;i++)
	{
		CKMesh *msh=Dest->AddMesh();

		msh->AllocatePoly(1,pl[i].nb2vert);
		for (j=0;j<nbTexCanals;j++)
		{
			msh->AllocateUV(j,pl[i].nb2vert);
		}

		msh->pl[0].Allocate(msh,nbTexCanals,pl[i].nb2vert);

		for (j=0;j<pl[i].nb2vert;j++)
		{
			msh->pl[0].nbvert[j]=j;
			for (k=0;k<nbTexCanals;k++)
			{
				msh->pl[0].Tex[k][j]=j;
			}
		}

		// vertex/UV
		for (j=0;j<pl[i].nb2vert;j++)
		{
			msh->pv[j]=pv[pl[i].nbvert[j]];
			msh->pv[j]+=(pl[i].Normale*Decal);

			for (k=0;k<nbTexCanals;k++)
			{
				msh->puv[k][j].u=puv[k][pl[i].Tex[k][j]].u;
				msh->puv[k][j].v=puv[k][pl[i].Tex[k][j]].v;
			}
		}
		msh->Color=Color;
		msh->UpdateMesh();
	}
}

void CKMesh::SubDivide(int nTime)
{
	int i,j;
	triangleCount=0;

	// Poly -> Table

	TessVertex tsv;
	for (i=0;i<nb2vert;i++)
	{
		tsv.x=pv[i].x;
		tsv.y=pv[i].y;
		tsv.z=pv[i].z;

		vertexTable.push_back(tsv);
	}

	for (i=0;i<nb2poly;i++)
	{
		for (j=0;j<pl[i].nb2vert-2;j++)
		{
			cornerTable.push_back(pl[i].nbvert[0]);
			cornerTable.push_back(pl[i].nbvert[j+1]);
			cornerTable.push_back(pl[i].nbvert[j+2]);
			triangleCount++;
			vertexTable[pl[i].nbvert[0]].u=puv[0][pl[i].Tex[0][0]].u;
			vertexTable[pl[i].nbvert[0]].v=puv[0][pl[i].Tex[0][0]].v;
			vertexTable[pl[i].nbvert[j+1]].u=puv[0][pl[i].Tex[0][j+1]].u;
			vertexTable[pl[i].nbvert[j+1]].v=puv[0][pl[i].Tex[0][j+1]].v;
			vertexTable[pl[i].nbvert[j+2]].u=puv[0][pl[i].Tex[0][j+2]].u;
			vertexTable[pl[i].nbvert[j+2]].v=puv[0][pl[i].Tex[0][j+2]].v;
		}
	}

	// subdiv

	for (i=0;i<nTime ;i++ )
	{
		buildOppositeTable();
		
		buildMidpointTable();
		buildFlagTable();
		buildNewCornerTable();

		//cornerTable = null;
		cornerTable = newCornerTable;

		triangleCount = numOfCorner() / 3;
	}

	// Create new

	AllocatePoly((newCornerTable.size() / 3),vertexTable.size());
	for (i=0;i<vertexTable.size();i++)
	{
		pv[i].x=vertexTable[i].x;
		pv[i].y=vertexTable[i].y;
		pv[i].z=vertexTable[i].z;
	}
	AllocateUV(0,vertexTable.size());

	for (i=0;i<vertexTable.size();i++)
	{
		puv[0][i].u=vertexTable[i].u;
		puv[0][i].v=vertexTable[i].v;
	}

	for (i=0;i<(newCornerTable.size() / 3);i++)
	{
		pl[i].Allocate(this,1,3);
		pl[i].nbvert[0]=newCornerTable[i*3];
		pl[i].nbvert[1]=newCornerTable[(i*3)+1];
		pl[i].nbvert[2]=newCornerTable[(i*3)+2];

		pl[i].Tex[0][0]=newCornerTable[i*3];
		pl[i].Tex[0][1]=newCornerTable[(i*3)+1];
		pl[i].Tex[0][2]=newCornerTable[(i*3)+2];
	}

}


// process through the entire corner table
// find the opposite for each corner
void CKMesh::buildOppositeTable() 
{

	// initialize opposite table to -1	
	//oppositeTable = new ArrayList();	
	oppositeTable.erase(oppositeTable.begin(),oppositeTable.end());

	for (int i=0;i<numOfCorner() ;i++ )
	{
		oppositeTable.push_back(-1);
	}

	// loop through every corners
	for (int c=0; c <= 3 * triangleCount - 2 ;c++ )
	{
		// compare against all the other corners
		for (int b=c+1; b <= 3 * triangleCount - 1  ;b++ )
		{	
			// if this condition is satisfied then the two corners are opposite to each other
			if ((vertexOfCorner(nextOfCorner(c))==vertexOfCorner(prevOfCorner(b)) && 
					 vertexOfCorner(prevOfCorner(c))==vertexOfCorner(nextOfCorner(b))) || 
					(vertexOfCorner(nextOfCorner(c))==vertexOfCorner(nextOfCorner(b)) && 
					 vertexOfCorner(prevOfCorner(c))==vertexOfCorner(prevOfCorner(b)))
			)
			{	
				// set them to be each other opposites
				oppositeTable[c]=b;
				oppositeTable[b]=c;
				break;
			}
		}
	}
}

// calculate the midpoint for each corner

void CKMesh::buildMidpointTable() {
	
	//midpointTable = new ArrayList();
	midpointTable.erase(midpointTable.begin(),midpointTable.end());

	// initialize midpoint table to -1
	for (int i=0;i<numOfCorner() ;i++ )
	{
		midpointTable.push_back(-1);
	}

	// the index represents the last position
	// on the vertex table.  It is used to find  
	// the position where the new midtpoint will be
	// inserted
	int index = numOfVertex() - 1;
		
	// loop through all the corner
	for (int c=0; c <= 3 * triangleCount - 1 ;c++ )
	{
		// increment the index for the next midpoint
		index++;

		// set the midpoint table entry for this c to point
		// to its respective position in the vertex table,
		// do the same for its opposite
		midpointTable[c]=index;
		midpointTable[oppositeOfCorner(c)]=index;


		float x = 0;
		float y = 0;
		float z = 0;

		float u = 0;
		float v = 0;

		
		// calculate the x coordinate for the midpoint
		x = (vertexOfCorner(nextOfCorner(c)).x + vertexOfCorner(prevOfCorner(c)).x) / 2.0f +
			((vertexOfCorner(c).x + vertexOfCorner(oppositeOfCorner(c)).x) / 2.0f 
			- (vertexOfCorner(leftOfCorner(c)).x + vertexOfCorner(rightOfCorner(c)).x + 
			vertexOfCorner(leftOfCorner(oppositeOfCorner(c))).x + 
			vertexOfCorner(rightOfCorner(oppositeOfCorner(c))).x)/4)/4;
			
		// calculate the y coordinate for the midpoint
		y = (vertexOfCorner(nextOfCorner(c)).y + vertexOfCorner(prevOfCorner(c)).y) / 2.0f +
			((vertexOfCorner(c).y + vertexOfCorner(oppositeOfCorner(c)).y) / 2.0f 
			- (vertexOfCorner(leftOfCorner(c)).y + vertexOfCorner(rightOfCorner(c)).y + 
			vertexOfCorner(leftOfCorner(oppositeOfCorner(c))).y + 
			vertexOfCorner(rightOfCorner(oppositeOfCorner(c))).y)/4)/4;
		
		// calculate the z coordinate for the midpoint
		z = (vertexOfCorner(nextOfCorner(c)).z + vertexOfCorner(prevOfCorner(c)).z) / 2.0f +
			((vertexOfCorner(c).z + vertexOfCorner(oppositeOfCorner(c)).z) / 2.0f 
			- (vertexOfCorner(leftOfCorner(c)).z + vertexOfCorner(rightOfCorner(c)).z + 
			vertexOfCorner(leftOfCorner(oppositeOfCorner(c))).z + 
			vertexOfCorner(rightOfCorner(oppositeOfCorner(c))).z)/4)/4;			

		// u

		u=(vertexOfCorner(leftOfCorner(oppositeOfCorner(c))).u + vertexOfCorner(rightOfCorner(oppositeOfCorner(c))).u + vertexOfCorner(c).u )/3.0f;

		//v

		v=(vertexOfCorner(leftOfCorner(oppositeOfCorner(c))).v + vertexOfCorner(rightOfCorner(oppositeOfCorner(c))).v + vertexOfCorner(c).v )/3.0f;

		TessVertex midpoint;
		midpoint.x=x;
		midpoint.y=y;
		midpoint.z=z;
		midpoint.u=u;
		midpoint.v=v;
			
		// add this midpoint as a vertex to the vertex table
		vertexTable.push_back(midpoint);	

	}
}

// this method basically initialize 
// the flag table
void CKMesh::buildFlagTable()
{
	
	//flagTable = new ArrayList();
	flagTable.erase(flagTable.begin(),flagTable.end());

	// initialize flag table to true
	for (int i=0;i<numOfCorner() ;i++ )
	{
		flagTable.push_back(true);
	}		
}

// this method run the butterfly scheme
// to generate new corners for more triangles
 void CKMesh::buildNewCornerTable() 
 {

	// initialize the table
	//newCornerTable = new ArrayList();
	 newCornerTable.erase(newCornerTable.begin(),newCornerTable.end());

	// loop through every corner
	for (int c=0;c<=3*triangleCount - 1 ;c++ )
	{
		// if this corner hasn't been visited yet
		if (flagOfCorner(c))
		{	
			// set the flag for all corners of this triangle to false
			// to indicate that the three corners of this triangle 
			// has been visited
			/*
			flagTable.set(c, new Boolean(false));
			flagTable.set(nextOfCorner(c), new Boolean(false));
			flagTable.set(prevOfCorner(c), new Boolean(false));
			*/
			flagTable[c]=false;
			flagTable[nextOfCorner(c)]=false;
			flagTable[prevOfCorner(c)]=false;

			// first triangle added and its three corners
			newCornerTable.push_back(cornerTable[c]);
			newCornerTable.push_back(midpointOfCorner(prevOfCorner(c)));
			newCornerTable.push_back(midpointOfCorner(nextOfCorner(c)));

			// second triangle added and its three corners
			newCornerTable.push_back(midpointOfCorner(prevOfCorner(c)));
			newCornerTable.push_back(cornerTable[nextOfCorner(c)]);
			newCornerTable.push_back(midpointOfCorner(c));

			// third triangle added and its three corners
			newCornerTable.push_back(midpointOfCorner(nextOfCorner(c)));
			newCornerTable.push_back(midpointOfCorner(c));
			newCornerTable.push_back(cornerTable[prevOfCorner(c)]);

			// third triangle added and its three corners
			newCornerTable.push_back(midpointOfCorner(c));
			newCornerTable.push_back(midpointOfCorner(nextOfCorner(c)));
			newCornerTable.push_back(midpointOfCorner(prevOfCorner(c)));
		}
	}
}

// return the number of vertex currently
// in vertex table
inline int CKMesh::numOfVertex() 
{
	return vertexTable.size();
}

// return the number of corner currently
// in the corner table
inline int CKMesh::numOfCorner() 
{ 
	return cornerTable.size();
}

// this method is the c.m operator, given
// the index value of the corner, return
// the midpoint it faces
inline int CKMesh::midpointOfCorner(int index) 
{
	return midpointTable[index];
}

// given an index of a corner, it will return
// the visited status of this corner
// true => not visited; false => visited
inline bool CKMesh::flagOfCorner(int index) 
{
	return flagTable[index];

}

// this method is the c.r operator, given
// the index value of the corner, return
// right neighbor
inline int CKMesh::rightOfCorner(int index) 
{
	
	// c.r = c.n.o

	return oppositeOfCorner(nextOfCorner(index));
}

// this method is the c.l operator, given
// the index value of corner, return
// left neighbor
inline int CKMesh::leftOfCorner(int index) 
{

	// c.l = c.n.n.o

	return oppositeOfCorner(nextOfCorner(nextOfCorner(index)));
}


// this method is the c.o operator, given
// the index value of the corner, return
// the opposite corner index
inline int CKMesh::oppositeOfCorner(int index) 
{
	return oppositeTable[index];
}

// this methid is the c.t operator, given
// the index value of the corner, return
// which triangle it belongs to
inline int CKMesh::triangleOfCorner(int index) 
{
	div_t div_result;
	// c.t = c DIV 3
	div_result=div(index,3);
	//return (index / 3);
	return div_result.quot;

}


// this methid is the c.n operator, given
// the index value of the corner, return
// the index of the next corner
inline int CKMesh::nextOfCorner(int index) 
{
	
	// c.n = 3t + (c+1) MOD 3

	return ((3 * triangleOfCorner(index)) + ((index +1) % 3));
}


// this methid is the c.p operator, given
// the index value of the corner, return
// the index of the previous corner

inline int CKMesh::prevOfCorner(int index) 
{
	// c.p = c.n.n

	return nextOfCorner(nextOfCorner(index));
}	

// this method is the c.v operator, given 
// the index value of the corner, return
// the coordinate of its vertex

inline TessVertex CKMesh::vertexOfCorner(int index) 
{
		
	int vertex_index = cornerTable[index];

	return vertexTable[vertex_index];
}

void CKMesh::SplitSelectedPolyToTri(bool AllPolys)
{
	int i,j;

	for (i=0;i<nb2poly;i++)
	{
		if ((pl[i].Selected)||(AllPolys))
		{
			if (pl[i].nb2vert>3)
			{
				int AddedPoly=(pl[i].nb2vert-3);
				int plav=nb2poly;
				AllocatePoly(nb2poly+AddedPoly,nb2vert);

				for (j=0;j<AddedPoly;j++)
				{
					pl[plav+j].Allocate(this,1,3);
					pl[plav+j].nbvert[0]=pl[i].nbvert[0];
					pl[plav+j].nbvert[1]=pl[i].nbvert[2+j];
					pl[plav+j].nbvert[2]=pl[i].nbvert[3+j];

					pl[plav+j].Tex[0][0]=pl[i].Tex[0][0];
					pl[plav+j].Tex[0][1]=pl[i].Tex[0][2+j];
					pl[plav+j].Tex[0][2]=pl[i].Tex[0][3+j];

					pl[plav+j].Selected=pl[i].Selected;

				}

				pl[i].Allocate(this,1,3);

				pl[i].nbvert[0]=pl[i].nbvert[0];
				pl[i].nbvert[1]=pl[i].nbvert[1];
				pl[i].nbvert[2]=pl[i].nbvert[2];

				pl[i].Tex[0][0]=pl[i].Tex[0][0];
				pl[i].Tex[0][1]=pl[i].Tex[0][1];
				pl[i].Tex[0][2]=pl[i].Tex[0][2];

			}
		}
	}
}

void CKMesh::DivideTriBy3(void)
{
	int i;

	SplitSelectedPolyToTri(false);

	int nbMaxpl=nb2poly;
	for (i=0;i<nbMaxpl;i++)
	{
		if (pl[i].Selected)
		{	
			Vertex Middle=(pv[pl[i].nbvert[0]]+pv[pl[i].nbvert[1]]+pv[pl[i].nbvert[2]])/3;
			UVCoords txMiddle;
			txMiddle.u=(puv[0][pl[i].Tex[0][0]].u+puv[0][pl[i].Tex[0][1]].u+puv[0][pl[i].Tex[0][2]].u)/3;
			txMiddle.v=(puv[0][pl[i].Tex[0][0]].v+puv[0][pl[i].Tex[0][1]].v+puv[0][pl[i].Tex[0][2]].v)/3;

			int plav=nb2poly;
			int vtav=nb2vert;
			int txav=nbTexCoords[0];

			AllocatePoly(nb2poly+2,nb2vert+1);
			AllocateUV(0,nbTexCoords[0]+1);

			pv[vtav]=Middle;
			pv[vtav].Selected=true;

			puv[0][txav].u=txMiddle.u;
			puv[0][txav].v=txMiddle.v;

			pl[plav].Allocate(this,1,3);
			pl[plav].nbvert[0]=pl[i].nbvert[0];
			pl[plav].nbvert[1]=pl[i].nbvert[1];
			pl[plav].nbvert[2]=vtav;

			pl[plav].Tex[0][0]=pl[i].Tex[0][0];
			pl[plav].Tex[0][1]=pl[i].Tex[0][1];
			pl[plav].Tex[0][2]=txav;
			pl[plav].Selected=pl[i].Selected;


			pl[plav+1].Allocate(this,1,3);
			pl[plav+1].nbvert[0]=pl[i].nbvert[1];
			pl[plav+1].nbvert[1]=pl[i].nbvert[2];
			pl[plav+1].nbvert[2]=vtav;

			pl[plav+1].Tex[0][0]=pl[i].Tex[0][1];
			pl[plav+1].Tex[0][1]=pl[i].Tex[0][2];
			pl[plav+1].Tex[0][2]=txav;
			pl[plav+1].Selected=pl[i].Selected;

			pl[i].nbvert[0]=pl[i].nbvert[0];
			pl[i].nbvert[1]=vtav;
			pl[i].nbvert[2]=pl[i].nbvert[2];

			pl[i].Tex[0][0]=pl[i].Tex[0][0];
			pl[i].Tex[0][1]=txav;
			pl[i].Tex[0][2]=pl[i].Tex[0][2];
		}
	}
	// unselect Mesh vertex
	/*
	m_Scene->DeleteBufVert();
	*/
	VertBuf *daBuf2;
	for (VertBuf *daBuf=m_Scene->FirstBufVert;daBuf!=NULL;)
	{
		daBuf2=daBuf->Next;
		if (daBuf->TargetType==PLUGIN_MESH)
		{
			if ((CKMesh*)daBuf->TargetCont==this)
			{
				m_Scene->DeleteBufVert(daBuf);
				delete daBuf;
			}
		}
		daBuf=daBuf2;
	}
	
	// reselect them
	for (i=0;i<nb2vert;i++)
	{
		if (pv[i].Selected)
		{
			m_Scene->AddBufVert(&pv[i],this,i);
		}
	}
	
}

void CKMesh::DivideTriBy4(void)
{
	int i;

	SplitSelectedPolyToTri(false);

	int nbMaxpl=nb2poly;
	for (i=0;i<nbMaxpl;i++)
	{
		if (pl[i].Selected)
		{	
			Vertex Middle1=(pv[pl[i].nbvert[0]]+pv[pl[i].nbvert[1]])/2.0f;
			Vertex Middle2=(pv[pl[i].nbvert[1]]+pv[pl[i].nbvert[2]])/2.0f;
			Vertex Middle3=(pv[pl[i].nbvert[2]]+pv[pl[i].nbvert[0]])/2.0f;

			UVCoords txMiddle1,txMiddle2,txMiddle3;
			txMiddle1.u=(puv[0][pl[i].Tex[0][0]].u+puv[0][pl[i].Tex[0][1]].u)/2.0f;
			txMiddle1.v=(puv[0][pl[i].Tex[0][0]].v+puv[0][pl[i].Tex[0][1]].v)/2.0f;

			txMiddle2.u=(puv[0][pl[i].Tex[0][1]].u+puv[0][pl[i].Tex[0][2]].u)/2.0f;
			txMiddle2.v=(puv[0][pl[i].Tex[0][1]].v+puv[0][pl[i].Tex[0][2]].v)/2.0f;

			txMiddle3.u=(puv[0][pl[i].Tex[0][2]].u+puv[0][pl[i].Tex[0][0]].u)/2.0f;
			txMiddle3.v=(puv[0][pl[i].Tex[0][2]].v+puv[0][pl[i].Tex[0][0]].v)/2.0f;

			int plav=nb2poly;
			int vtav=nb2vert;
			int txav=nbTexCoords[0];

			AllocatePoly(nb2poly+3,nb2vert+3);
			AllocateUV(0,nbTexCoords[0]+3);
			pv[vtav]=Middle1;
			pv[vtav+1]=Middle2;
			pv[vtav+2]=Middle3;

			//
			pv[vtav].Selected=true;
			pv[vtav+1].Selected=true;
			pv[vtav+2].Selected=true;

			//

			puv[0][txav].u=txMiddle1.u;
			puv[0][txav].v=txMiddle1.v;
			puv[0][txav+1].u=txMiddle2.u;
			puv[0][txav+1].v=txMiddle2.v;
			puv[0][txav+2].u=txMiddle3.u;
			puv[0][txav+2].v=txMiddle3.v;

			CKPolygon tmppl;

			tmppl.IsCopyOf(this,&pl[i]);

			// pl 1
			pl[i].nbvert[0]=tmppl.nbvert[0];
			pl[i].nbvert[1]=vtav;
			pl[i].nbvert[2]=vtav+2;

			pl[i].Tex[0][0]=pl[i].Tex[0][0];
			pl[i].Tex[0][1]=txav;
			pl[i].Tex[0][2]=txav+2;

			// pl 2
			pl[plav].Allocate(this,1,3);
			pl[plav].nbvert[0]=vtav;
			pl[plav].nbvert[1]=tmppl.nbvert[1];
			pl[plav].nbvert[2]=vtav+1;

			pl[plav].Tex[0][0]=txav;
			pl[plav].Tex[0][1]=tmppl.Tex[0][1];
			pl[plav].Tex[0][2]=txav+1;
			pl[plav].Selected=pl[i].Selected;

			// pl 3
			pl[plav+1].Allocate(this,1,3);
			pl[plav+1].nbvert[0]=vtav+1;
			pl[plav+1].nbvert[1]=tmppl.nbvert[2];
			pl[plav+1].nbvert[2]=vtav+2;

			pl[plav+1].Tex[0][0]=txav+1;
			pl[plav+1].Tex[0][1]=tmppl.Tex[0][2];
			pl[plav+1].Tex[0][2]=txav+2;
			pl[plav+1].Selected=pl[i].Selected;

			// pl 3
			pl[plav+2].Allocate(this,1,3);
			pl[plav+2].nbvert[0]=vtav;
			pl[plav+2].nbvert[1]=vtav+1;
			pl[plav+2].nbvert[2]=vtav+2;

			pl[plav+2].Tex[0][0]=txav;
			pl[plav+2].Tex[0][1]=txav+1;
			pl[plav+2].Tex[0][2]=txav+2;
			pl[plav+2].Selected=pl[i].Selected;

		}
	}
	CollapseIdenticalVertex();
	// unselect Mesh vertex
	for (VertBuf *daBuf=m_Scene->FirstBufVert;daBuf!=NULL;daBuf=daBuf->Next)
	{
		if (daBuf->TargetType==PLUGIN_MESH)
			if ((CKMesh*)daBuf->TargetCont==this)
				m_Scene->DeleteBufVert(daBuf);
	}
	// reselect them
	for (i=0;i<nb2vert;i++)
	{
		if (pv[i].Selected)
		{
			m_Scene->AddBufVert(&pv[i],this,i);
		}
	}
}

