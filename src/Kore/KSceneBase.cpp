//---------------------------------------------------------------------------
#include "stdafx.h"

//#include "memmgr/mmgr.h"
extern CKOption *KOption2;


CKSceneBase::CKSceneBase(/*CKSceneBase *daPrev,CKSceneBase *daNext*/)
{
	
	TexUnique=0;
//    CKSceneBase *daCKSceneBase;
    int i;
/*
    Next=daNext;
    Prev=daPrev;
*/
    
    FirstBufVert=NULL;
    NextBufVert=NULL;

    NextTexture=NULL;
    FirstTexture=NULL;

	// allocate

	//FileName=new char [256];
    //Name=new char [20];
    //temp=new char [50];
	cam=new CKCamera *[4];
//	light1_pos=new GLfloat [4];

	ViewNg=new Vertex [4];
	ViewPos=new Vertex [4];
	ViewSize=new Vertex [4];
	tmppos=new Vertex [4];
	tmpViewSize=new Vertex [4];
	TmpViewNg=new Vertex [4];

    ViewStart=new POINT [4];
	ViewEnd=new POINT [4];
    ViewType=new int [4];
/*
	viewport=new GLint* [4];
	mvmatrix=new GLdouble* [4];
	projmatrix=new GLdouble* [4];
*/


/*
    mvmatrix2=new GLdouble [16];
	projmatrix2=new GLdouble [16];
	*/
    State=new int [4];
	//CurrentName=new char [20];





    
//    Maths=new(Math);

    // recherche d'un "unnamed"
/*
    daCKSceneBase=Prev;
    nbUnnamed=0;
    while (daCKSceneBase!=NULL)
    {
        if (daCKSceneBase->IsNamed==false)
        {
            nbUnnamed++;
        }
        daCKSceneBase=daCKSceneBase->Prev;
    }

    daCKSceneBase=Next;
    while (daCKSceneBase!=NULL)
    {
        if (daCKSceneBase->IsNamed==false)
        {
            nbUnnamed++;
        }
        daCKSceneBase=daCKSceneBase->Next;
    }


    temp.Format("Noname%02d",nbUnnamed);
    Name=temp;//strcpy(Name,temp);
*/
//    IsNamed=false;
    Modified=false;
	m_UVSelUpdate=false;

    FrameInd=0;
    m_CountUV=0;

    // selection
    //Sel=new (Shape)(NULL,NULL);
	Sel=NULL;
	UVEdit=NULL;


	// view

	FullScreen=false;
    Active=0;
    AncActive=0;

	ViewType[0]=VIEWTYPE_PERSPECTIVE;
	ViewType[1]=VIEWTYPE_ORTHO;
	ViewType[2]=VIEWTYPE_ORTHO;
	ViewType[3]=VIEWTYPE_ORTHO;

    for (i=0;i<4;i++)
    {
        cam[i]=NULL;
        ViewSize[i].x=200;
        State[i]=0;
    }

	daViewMode=VIEW_MODE2x2;

    ComputeSize();

    ViewNg[2].x=00;
    ViewNg[2].y=00;
    ViewNg[2].z=00;

    ViewNg[3].x=-90;
    ViewNg[3].y=00;
    ViewNg[3].z=00;

    ViewNg[1].x=-90;
    ViewNg[1].y=00;
    ViewNg[1].z=90;



	SnapValCounter=0;
	AngleValCounter=0;

	SnapVal.x=KOption2->GridSpace(0);
	SnapVal.y=KOption2->GridSpace(0);
	SnapVal.z=KOption2->GridSpace(0);

	AngleSnapVal=KOption2->AngleSnap(0);

	m_GridVisible[0]=true;
	m_GridVisible[1]=true;
	m_GridVisible[2]=true;
	m_GridVisible[3]=true;

	// undo/redo

	FirstUndo=NULL;
	NextUndo=NULL;
	FirstRedo=NULL;
	NextRedo=NULL;

	
	SomeThingSel=false;
	MeshCreationCounter=0;

	nbAddedMesh=0;
	nbAddedShape=0;
	nbAddedPatch=0;
	nbAddedSkel=0;
	nbAddedCamera=0;
	nbAddedEntity=0;

	m_IsReading=false;
	// Tests

	
/*
	CKMesh *CurObj=AddMesh();
	CKGenericMesh mobj;

	mobj.CreateStairsSimple(CurObj,Vertex(0,0,0),64,128,128,5);
	CurObj->UpdateMesh();

	CKMesh *CurObj2=AddMesh();
	

	mobj.VecX=Vertex(1,0,0);
	mobj.VecY=Vertex(0,1,0);
	mobj.VecZ=Vertex(0,0,1);

	mobj.CreateCube(CurObj2,Vertex(50,50,50),128,128,128);
	//mobj.CreateStairsSimple(CurObj2,Vertex(50,0,0),64,128,128,8);
	CurObj2->UpdateMesh();

	CurObj->MergeMesh(CurObj2);
	*/

	/* BSP
	Mesh *CurObj=AddMesh();
	CGenericMeshs mobj;
	mobj.VecX=Vertex(1,0,0);
	mobj.VecY=Vertex(0,1,0);
	mobj.VecZ=Vertex(0,0,1);

	mobj.CreateCube(CurObj,Vertex(0,0,0),128,128,128);
	CurObj->UpdateMesh();
	CurObj->CalcAllPlanes();

	CurObj=AddMesh();
	mobj.CreateCube(CurObj,Vertex(64,64,64),128,128,128);
	CurObj->UpdateMesh();
	CurObj->CalcAllPlanes();

  */
/*	
	CurObj->BSPTree=new CBSPTree;
	CurObj->BSPTree->InitPolygons(CurObj,1,FALSE);
*/
	//AddEntity("IRC");

	//UndoViewChange();
	LatestVI=NULL;
}

CKSceneBase::~CKSceneBase()
{
	/*
    if (Next!=NULL)
        Next->Prev=Prev;

    if (Prev!=NULL)
        Prev->Next=Next;
*/
//    delete maps;

	/*
	for (int i=0;i<4;i++)
	{
		delete viewport[i];
		delete mvmatrix[i];
		delete projmatrix[i];
	}
	*/
/*
	delete [] viewport;
	delete [] mvmatrix;
	delete [] projmatrix;
*/


//	delete [] FileName;
    //delete [] Name;
    //delete [] temp;
	delete [] cam;
//	delete [] light1_pos;

	delete [] ViewNg;
	delete [] ViewPos;
	delete [] ViewSize;
	delete [] tmppos;
	delete [] tmpViewSize;
	delete [] TmpViewNg;

    delete [] ViewStart;
	delete [] ViewEnd;
    delete [] ViewType;
//    delete [] viewport;

	/*
    delete [] mvmatrix;
	delete [] projmatrix;

    delete [] mvmatrix2;
	delete [] projmatrix2;
	*/
    delete [] State;
//	delete [] CurrentName;

    delete Sel;

//	delete cSel;

	if (UVEdit!=NULL) free(UVEdit);
	// delete all textures

	CKTexture *datex=FirstTexture,*datex2;
	while (datex!=NULL)
	{
		datex2=datex->Next;
		delete datex;
		datex=datex2;
	}

	// delete all objects;
	/*
	CKMesh *daObj=FirstMesh,*daObj2;
	while (daObj!=NULL)
	{
		daObj2=daObj->Next;
		delete daObj;
		daObj=daObj2;
	}
	*/
	m_Meshes.erase(m_Meshes.begin(),m_Meshes.end());
		

	// delete all lights;
	/*
	CLight *daLight=FirstLight,*daLight2;
	while (daLight!=NULL)
	{
		daLight2=daLight->Next;
		delete daLight;
		daLight=daLight2;
	}
	*/
	nbAddedMesh=0;
	nbAddedShape=0;
	nbAddedPatch=0;
	nbAddedSkel=0;
	nbAddedCamera=0;
	nbAddedEntity=0;

	m_IsReading=false;

}

CKShape *CKSceneBase::AddShape()
{
	CKShape *nShape=new CKShape;

	GenerateName(PLUGIN_SHAPE);
	nShape->Name=CurrentName;

	m_Shapes.push_back(nShape);

	UpdateHierarchie((CKScene*)this);

	nbAddedShape++;

	return nShape;
}


void CKSceneBase::AddShape(CKShape *pShape)
{

	GenerateName(PLUGIN_SHAPE);
	pShape->Name=CurrentName;

	m_Shapes.push_back(pShape);

	UpdateHierarchie((CKScene*)this);

	nbAddedShape++;
}

CKEntity *CKSceneBase::AddEntity(CString EntType)
{
	CKEntity *nEntity=GetLib()->CreateEntityInterface(EntType);

	nEntity->m_Scene=(CKScene*)this;
	nEntity->EntType=EntType;

	m_Entities.push_back(nEntity);

	UpdateHierarchie((CKScene*)this);

	nbAddedEntity++;

	return nEntity;
}

void CKSceneBase::AddEntity(CKEntity *pEntity)
{
	pEntity->m_Scene=(CKScene*)this;
	m_Entities.push_back(nEntity);
	
	UpdateHierarchie((CKScene*)this);

	nbAddedEntity++;
}


CKMesh *CKSceneBase::AddMesh()
{
	CKMesh *nMesh=new CKMesh((CKScene*)this);

	GenerateName(PLUGIN_MESH);
	nMesh->Name=CurrentName;

	RGB *dacol=KOption2->ColorMesh(MeshCreationCounter);
	nMesh->Color.bRed =dacol->bRed;
	nMesh->Color.bGreen =dacol->bGreen;
	nMesh->Color.bBlue =dacol->bBlue;

	MeshCreationCounter++;
	MeshCreationCounter%=10;

	m_Meshes.push_back(nMesh);

	UpdateHierarchie((CKScene*)this);

	nbAddedMesh++;

	return nMesh;
}

CKPatch *CKSceneBase::AddPatch()
{
    CKPatch *nPatch=new CKPatch((CKScene*)this);
	
	GenerateName(PLUGIN_PATCH);
	nPatch->Name=CurrentName;

	m_Patches.push_back(nPatch);

	UpdateHierarchie((CKScene*)this);

	nbAddedPatch++;

	return nPatch;
}

void CKSceneBase::AddMesh(CKMesh *pMesh)
{
	GenerateName(PLUGIN_MESH);
	pMesh->Name=CurrentName;
	pMesh->m_Scene=(CKScene*)this;

	m_Meshes.push_back(pMesh);

	UpdateHierarchie((CKScene*)this);

	nbAddedMesh++;
}


CKCamera *CKSceneBase::AddCam()
{
    CKCamera *nCam=new CKCamera((CKScene*)this);

	GenerateName(PLUGIN_CAMERA);

	nCam->Name=CurrentName;

	m_Cameras.push_back(n_Cam);
	UpdateHierarchie((CKScene*)this);

	nbAddedCamera++;

	return nCam;
}

CKSkeleton *CKSceneBase::AddSkeleton()
{
	CKSkeleton *nSkel=new CKSkeleton((CKScene*)this);

	GenerateName(PLUGIN_SKELETON);
	nSkel->Name=CurrentName;

	UpdateHierarchie((CKScene*)this);

	return nSkel;
}

void CKSceneBase::DelCamera(CKCamera *pCam)
{



	UpdateHierarchie((CKScene*)this);

    delete daCam;
}

void CKSceneBase::DelPatch(CKPatch *pPatch)
{

	UpdateHierarchie((CKScene*)this);

    delete daPatch;
}

void CKSceneBase::DelEntity(CKEntity *pEntity)
{

	UpdateHierarchie((CKScene*)this);

    delete daEntity;
}

void CKSceneBase::DelSkeleton(CKSkeleton *pSkel)
{

	UpdateHierarchie((CKScene*)this);

    delete daSkel;
}

void CKSceneBase::DelShape(CKShape *pShape)
{

	UpdateHierarchie((CKScene*)this);

    delete daShape;
}

void CKSceneBase::DelMesh(CKMesh *pMesh)
{

	UpdateHierarchie((CKScene*)this);

    delete daMesh;
}



// insertion juste apres
/*
void CKSceneBase::InsertShape(CKShape *InsShape)
{
    CKShape *tmpShape;

    tmpShape=new (CKShape) (InsShape,InsShape->Next);
    InsShape->Next->Prev=tmpShape;
    InsShape->Next=tmpShape;
}
*/
/*
void CKSceneBase::SetName(CString val)
{
    //Name=val;
	Name=val;
    IsNamed=true;
}
*/
/*
Material *CKSceneBase::GetMaterial(char * MatName)
{
	
    Material *MatAv;

    MatAv=FirstMat;
    while (MatAv!=NULL)
    {
        if (strcmp(MatAv->Name,MatName)==0)
        {
            return MatAv;
        }

        MatAv=MatAv->Next;
    }

    return NULL;
}
*/
/*
Mesh *CKSceneBase::GetMesh(char * ObjName)
{
	
    Mesh *ObjAv;

    ObjAv=FirstMesh;
    while (ObjAv!=NULL)
    {
        if (strcmp(ObjAv->Name,ObjName)==0)
        {
            return ObjAv;
        }

        ObjAv=ObjAv->Next;
    }

    return NULL;
}

Camera *CKSceneBase::GetCamera(char * CamName)
{
	
    Camera *CamAv;

    CamAv=FirstCam;
    while (CamAv!=NULL)
    {
        if (strcmp(CamAv->Name,CamName)==0)
        {
            return CamAv;
        }

        CamAv=CamAv->Next;
    }

    return NULL;
}
*/
/*

void CKSceneBase::SelectCircle(int Prim,int Entity,int dx,int dy,int X,int Y,bool Crossing,OGLView *View)
{


}
*/


void CKSceneBase::AddBufVert(Vertex *DaVert,int Index)
{
    //if (!cSel->IsVertInBuf(DaVert))
    //{
        if (FirstBufVert==NULL)
        {
            FirstBufVert=new (VertBuf)(DaVert,NULL,NULL,Index);
            NextBufVert=FirstBufVert;
        }
        else
        {
            NextBufVert->Next=new (VertBuf)(DaVert,NextBufVert,NULL,Index);
            NextBufVert=NextBufVert->Next;
        }
    //}
}

void CKSceneBase::AddBufVert(Vertex *DaVert,CKMesh *Obj,int Index)
{
    if (FirstBufVert==NULL)
    {
        FirstBufVert=new (VertBuf)(DaVert,NULL,NULL,Index);
        NextBufVert=FirstBufVert;
        NextBufVert->TargetCont=(void*)Obj;
		NextBufVert->TargetType=PLUGIN_MESH;

    }
    else
    {
        NextBufVert->Next=new (VertBuf)(DaVert,NextBufVert,NULL,Index);
        NextBufVert=NextBufVert->Next;
        NextBufVert->TargetCont=(void*)Obj;
		NextBufVert->TargetType=PLUGIN_MESH;
    }
}
void CKSceneBase::AddBufVert(Vertex *DaVert,CKShape *Shp,CKSegment *Seg)
{
    if (FirstBufVert==NULL)
    {
        FirstBufVert=new (VertBuf)(DaVert,NULL,NULL,NULL);
        NextBufVert=FirstBufVert;
		/*
        NextBufVert->Shp=Shp;
		NextBufVert->Seg=Seg;
		*/
        NextBufVert->TargetCont=(void*)Seg;
		NextBufVert->TargetType=PLUGIN_SHAPE;

    }
    else
    {
        NextBufVert->Next=new (VertBuf)(DaVert,NextBufVert,NULL,NULL);
        NextBufVert=NextBufVert->Next;
		/*
        NextBufVert->Shp=Shp;
		NextBufVert->Seg=Seg;
		*/
        NextBufVert->TargetCont=(void*)Seg;
		NextBufVert->TargetType=PLUGIN_SHAPE;
    }
}
void CKSceneBase::AddBufVert(Vertex *DaVert,CKCamera *Cam,int Index)
{
    if (FirstBufVert==NULL)
    {
        FirstBufVert=new (VertBuf)(DaVert,NULL,NULL,Index);
        NextBufVert=FirstBufVert;
		NextBufVert->TargetCont=(void*)Cam;
		NextBufVert->TargetType=PLUGIN_CAMERA;

    }
    else
    {
        NextBufVert->Next=new (VertBuf)(DaVert,NextBufVert,NULL,Index);
        NextBufVert=NextBufVert->Next;
		NextBufVert->TargetCont=(void*)Cam;
		NextBufVert->TargetType=PLUGIN_CAMERA;
    }
}
/*
void CKSceneBase::AddBufVert(Vertex *DaVert,CLight *daLight,int Index)
{
    if (FirstBufVert==NULL)
    {
        FirstBufVert=new (VertBuf)(DaVert,NULL,NULL,Index);
        NextBufVert=FirstBufVert;
        //NextBufVert->Cam=Cam;
    }
    else
    {
        NextBufVert->Next=new (VertBuf)(DaVert,NextBufVert,NULL,Index);
        NextBufVert=NextBufVert->Next;
        //NextBufVert->Cam=Cam;
    }
}
*/
void CKSceneBase::AddBufVert(Vertex *DaVert,CKEntity *daEnt,int Index)
{
    if (FirstBufVert==NULL)
    {
        FirstBufVert=new (VertBuf)(DaVert,NULL,NULL,Index);
        NextBufVert=FirstBufVert;
        //NextBufVert->Ent=daEnt;
        NextBufVert->TargetCont=(void*)daEnt;
		NextBufVert->TargetType=PLUGIN_ENTITY;

    }
    else
    {
        NextBufVert->Next=new (VertBuf)(DaVert,NextBufVert,NULL,Index);
        NextBufVert=NextBufVert->Next;
        //xtBufVert->Ent=daEnt;
		NextBufVert->TargetCont=(void*)daEnt;
		NextBufVert->TargetType=PLUGIN_ENTITY;
    }
}

void CKSceneBase::AddBufVert(Vertex *DaVert,CKPatch *daPatch,int Index)
{
    if (FirstBufVert==NULL)
    {
        FirstBufVert=new (VertBuf)(DaVert,NULL,NULL,Index);
        NextBufVert=FirstBufVert;
        //NextBufVert->Patch=daPatch;
		NextBufVert->TargetCont=(void*)daPatch;
		NextBufVert->TargetType=PLUGIN_PATCH;

    }
    else
    {
        NextBufVert->Next=new (VertBuf)(DaVert,NextBufVert,NULL,Index);
        NextBufVert=NextBufVert->Next;
        //NextBufVert->Patch=daPatch;
		NextBufVert->TargetCont=(void*)daPatch;
		NextBufVert->TargetType=PLUGIN_PATCH;
    }
}
void CKSceneBase::AddBufVert(Vertex *DaVert,CKSkeleton *daSkel,CKBone *daBone)
{
    if (FirstBufVert==NULL)
    {
        FirstBufVert=new (VertBuf)(DaVert,NULL,NULL,NULL);
        NextBufVert=FirstBufVert;
		/*
        NextBufVert->Skel=daSkel;
		NextBufVert->Bone=daBone;
		*/
        NextBufVert->TargetCont=(void*)daSkel;
		NextBufVert->TargetType=PLUGIN_SKELETON;
    }
    else
    {
        NextBufVert->Next=new (VertBuf)(DaVert,NextBufVert,NULL,NULL);
        NextBufVert=NextBufVert->Next;
		/*
        NextBufVert->Skel=daSkel;
		NextBufVert->Bone=daBone;
		*/
        NextBufVert->TargetCont=(void*)daSkel;
		NextBufVert->TargetType=PLUGIN_SKELETON;
    }
}

void CKSceneBase::DeleteBufVert(void)
{
    VertBuf *daBufVert,*daBufVert2;

    daBufVert=FirstBufVert;
    while(daBufVert!=NULL)
    {
        daBufVert2=daBufVert->Next;
		daBufVert->Dest->Selected=false;
        delete daBufVert;
        daBufVert=NULL;
        daBufVert=daBufVert2;
    }
    FirstBufVert=NULL;
    NextBufVert=NULL;

	// erase undo vector
	UndoRedoEntriesCount.erase(UndoRedoEntriesCount.begin(),UndoRedoEntriesCount.end());

}

inline void CKSceneBase::DeleteBufVert(VertBuf *daBufVert)
{

	if (daBufVert==FirstBufVert)
        FirstBufVert=FirstBufVert->Next;

    if (daBufVert==NextBufVert)
        NextBufVert=NextBufVert->Prev;

    if (daBufVert->Next!=NULL)
        daBufVert->Next->Prev=daBufVert->Prev;

    if (daBufVert->Prev!=NULL)
        daBufVert->Prev->Next=daBufVert->Next;
}

void CKSceneBase::RemoveBufUnselected(void)
{
    VertBuf *daBufVert,*daBufVert2;

    daBufVert=FirstBufVert;
    while(daBufVert!=NULL)
    {
        daBufVert2=daBufVert->Next;
        if (!daBufVert->Dest->Selected)
        {
            if (daBufVert->Prev!=NULL)
                daBufVert->Prev->Next=daBufVert->Next;

            if (daBufVert->Next!=NULL)
                daBufVert->Next->Prev=daBufVert->Prev;

            if (daBufVert==FirstBufVert) FirstBufVert=daBufVert->Next;

            if (daBufVert==NextBufVert) NextBufVert=daBufVert->Prev;

            delete daBufVert;
        }
        daBufVert=daBufVert2;
    }
}


void CKSceneBase::TranslateBuf(CKPlan *dap,Vertex Trans)
{
    VertBuf *daBufVert;

    daBufVert=FirstBufVert;
    while(daBufVert!=NULL)
    {
        daBufVert->IsNow(daBufVert->AncVal+Trans);

        daBufVert=daBufVert->Next;
    }

}

void CKSceneBase::TranslateBuf(Vertex Trans)
{
    VertBuf *daBufVert;

    daBufVert=FirstBufVert;
    while(daBufVert!=NULL)
    {
        daBufVert->IsNow(daBufVert->AncVal+Trans);

        daBufVert=daBufVert->Next;
    }

}

void CKSceneBase::Flush(void)
{
    VertBuf *daBufVert;

    daBufVert=FirstBufVert;
    while(daBufVert!=NULL)
    {
        daBufVert->IsOldValue();
        daBufVert=daBufVert->Next;
    }
}

void CKSceneBase::UpdateBuf(void)
{
    VertBuf *daBufVert;

    daBufVert=FirstBufVert;
    while(daBufVert!=NULL)
    {
        daBufVert->UpdateValue();
        daBufVert=daBufVert->Next;
    }
}

void CKSceneBase::RotateBuf(CKPlan *dap,Vertex Center)
{
    VertBuf *daBufVert;

    daBufVert=FirstBufVert;
    while(daBufVert!=NULL)
    {
        daBufVert->IsNow((dap->Rotate(daBufVert->AncVal-Center)+Center));
        daBufVert=daBufVert->Next;
    }

}

void CKSceneBase::ScaleBuf(CKPlan *dap,Vertex Center,Vertex ScaleVal)
{
    VertBuf *daBufVert;

    daBufVert=FirstBufVert;
    while(daBufVert!=NULL)
    {
        daBufVert->IsNow((dap->Scale(daBufVert->AncVal-Center,ScaleVal)+Center));
        daBufVert=daBufVert->Next;
    }

}

Vertex CKSceneBase::GetMinBuf(void)
{
    VertBuf *daBufVert;
    Vertex Value;

    daBufVert=FirstBufVert;
    if (daBufVert==NULL) return Vertex(0,0,0);
    Value=daBufVert->AncVal;

    while(daBufVert!=NULL)
    {
        if (daBufVert->AncVal.x<Value.x) Value.x=daBufVert->AncVal.x;
        if (daBufVert->AncVal.y<Value.y) Value.y=daBufVert->AncVal.y;
        if (daBufVert->AncVal.z<Value.z) Value.z=daBufVert->AncVal.z;

        daBufVert=daBufVert->Next;
    }

    return Value;
}

Vertex CKSceneBase::GetMaxBuf(void)
{
    VertBuf *daBufVert;
    Vertex Value;

    daBufVert=FirstBufVert;
    if (daBufVert==NULL) return Vertex(0,0,0);
    Value=daBufVert->AncVal;

    while(daBufVert!=NULL)
    {
        if (daBufVert->AncVal.x>Value.x) Value.x=daBufVert->AncVal.x;
        if (daBufVert->AncVal.y>Value.y) Value.y=daBufVert->AncVal.y;
        if (daBufVert->AncVal.z>Value.z) Value.z=daBufVert->AncVal.z;

        daBufVert=daBufVert->Next;
    }

    return Value;
}
  /*
// -- op sur Shape/Face --------------------------------------------------------
bool CKSceneBase::IsIn(MYPOINT vt,MYPOINT *polydeb,MYPOINT *polyfin, int nb2daSegs)
{
    int i,j,k;
    int nbSect=0;
    double Sec[100];
    bool HasGood;
    MYPOINT daDeb,daFin,daVt;
    double daSec;
    Segment **tmpseg;

    for (i=0;i<nb2daSegs;i++)
    {
        if (ComprisIn(polydeb[i].x,polyfin[i].x,vt.x))
        {
            daSec=Interpolate(polydeb[i],polyfin[i],vt.x);

            HasGood=true;

            for (j=0;j<nbSect;j++)
            {
                if (Sec[j]==daSec)
                {
                    HasGood=false;
                }

            }

            if (HasGood)
            {
                Sec[nbSect++]=daSec;
            }
        }
    }

    qsort((void *)Sec, nbSect, sizeof(double), IsInSort);


    HasGood=false;

    for (i=0;i<(nbSect-1);i++)
    {

        k=(i&1);

        if ((ComprisIn(Sec[i],Sec[i+1],vt.y))&&(!k))
        {
            HasGood=true;
        }

    }

    return HasGood;
}
*/
//---------------------------------------------------------------------------

bool CKSceneBase::GetMinMax(long Stat,Vertex *DstMin,Vertex *DstMax)
{
    bool HasMin=false;
    CKMesh *daObj;
	CKCamera *daCam;
	CKShape *daShp;
	CKSkeleton *daSkel;
	CKEntity *daEntity;
	CKPatch *daPatch;

	// Mesh

    if (Stat&PLUGIN_MESH)
    {
        daObj=FirstMesh;
        if ((daObj!=NULL)&&(!HasMin))
        {
            (*DstMin)=daObj->Min;
			(*DstMax)=daObj->Max;
            HasMin=true;
        }
        while(daObj!=NULL)
        {
            DstMin->GetMinOf(daObj->Min);
			DstMax->GetMaxOf(daObj->Max);
            daObj=daObj->Next;
        }
    }

	// Camera

    if (Stat&PLUGIN_CAMERA)
    {
        daCam=FirstCam;
        if ((daCam!=NULL)&&(!HasMin))
        {
            (*DstMin)=daCam->GetMinOf();
			(*DstMax)=daCam->GetMaxOf();
            HasMin=true;
        }
        while(daCam!=NULL)
        {
            DstMin->GetMinOf(daCam->GetMinOf());
			DstMax->GetMaxOf(daCam->GetMaxOf());
            daCam=daCam->Next;
        }
    }

	// Shape

    if (Stat&PLUGIN_SHAPE)
    {
        daShp=FirstShape;
        if ((daShp!=NULL)&&(!HasMin))
        {
            (*DstMin)=daShp->GetMinOf();
			(*DstMax)=daShp->GetMaxOf();
            HasMin=true;
        }
        while(daShp!=NULL)
        {
            DstMin->GetMinOf(daShp->GetMinOf());
			DstMax->GetMaxOf(daShp->GetMaxOf());
            daShp=daShp->Next;
        }
    }

	// CKSkeleton

    if (Stat&PLUGIN_SKELETON)
    {
        daSkel=FirstSkel;
        if ((daSkel!=NULL)&&(!HasMin))
        {
            (*DstMin)=daSkel->GetMinOf();
			(*DstMax)=daSkel->GetMaxOf();
            HasMin=true;
        }
        while(daSkel!=NULL)
        {
            DstMin->GetMinOf(daSkel->GetMinOf());
			DstMax->GetMaxOf(daSkel->GetMaxOf());
            daSkel=daSkel->Next;
        }
    }

	// Patch
	if (Stat&PLUGIN_PATCH)
	{
        daPatch=FirstPatch;
        if ((daPatch!=NULL)&&(!HasMin))
        {
            (*DstMin)=daPatch->Min;
			(*DstMax)=daPatch->Max;
            HasMin=true;
        }
        while(daPatch!=NULL)
        {
            DstMin->GetMinOf(daPatch->Min);
			DstMin->GetMaxOf(daPatch->Max);
            daPatch=daPatch->Next;
        }
	}
	// Entities
	if (Stat&PLUGIN_ENTITY)
	{
        daEntity=FirstEntity;
        if ((daEntity!=NULL)&&(!HasMin))
        {
            (*DstMin)=daEntity->Min;
			(*DstMax)=daEntity->Max;
            HasMin=true;
        }
        while(daEntity!=NULL)
        {
            DstMin->GetMinOf(daEntity->Min);
			DstMax->GetMaxOf(daEntity->Max);
            daEntity=daEntity->Next;
        }

	}


    return HasMin;
}

void CKSceneBase::SetAxis(Vertex daAxis)
{
	Axis=daAxis;
	Modified=true;
}


void CKSceneBase::ComputeSize(void)
{
	switch(daViewMode)
	{
	case VIEW_MODE2x2:

			// 2x2

			ViewStart[0].x=Left;
			ViewStart[0].y=Top;
			ViewEnd[0].x=Width/2;
			ViewEnd[0].y=Height/2;

			ViewStart[1].x=Left+Width/2;
			ViewStart[1].y=Top;
			ViewEnd[1].x=Width/2;
			ViewEnd[1].y=Height/2;

			ViewStart[2].x=Left;
			ViewStart[2].y=Top+Height/2;
			ViewEnd[2].x=Width/2;
			ViewEnd[2].y=Height/2;

			ViewStart[3].x=Left+Width/2;
			ViewStart[3].y=Top+Height/2;
			ViewEnd[3].x=Width/2;
			ViewEnd[3].y=Height/2;
			break;

	case VIEW_MODE1x3a:

			//case1x3a

			ViewStart[0].x=Left+Width/2;
			ViewStart[0].y=Top;
			ViewEnd[0].x=Width/2;
			ViewEnd[0].y=Height;

			ViewStart[1].x=Left;
			ViewStart[1].y=Top;
			ViewEnd[1].x=Width/2;
			ViewEnd[1].y=Height/3;

			ViewStart[2].x=Left;
			ViewStart[2].y=Top+Height/3;
			ViewEnd[2].x=Width/2;
			ViewEnd[2].y=Height/3;

			ViewStart[3].x=Left;
			ViewStart[3].y=Top+2*(Height/3);
			ViewEnd[3].x=Width/2;
			ViewEnd[3].y=Height/3;
			break;
	case VIEW_MODE1x3b:
			//1x3b
			ViewStart[0].x=Left;
			ViewStart[0].y=Top;
			ViewEnd[0].x=Width;
			ViewEnd[0].y=Height/2;

			ViewStart[1].x=Left;
			ViewStart[1].y=Top+Height/2;
			ViewEnd[1].x=Width/3;
			ViewEnd[1].y=Height/2;

			ViewStart[2].x=Left+Width/3;
			ViewStart[2].y=Top+Height/2;
			ViewEnd[2].x=Width/3;
			ViewEnd[2].y=Height/2;

			ViewStart[3].x=Left+2*(Width/3);
			ViewStart[3].y=Top+(Height/2);
			ViewEnd[3].x=Width/3;
			ViewEnd[3].y=Height/2;
			break;
	case VIEW_MODE1x2b:
			//1x2a
	
			ViewStart[0].x=Left;
			ViewStart[0].y=Top;
			ViewEnd[0].x=Width;
			ViewEnd[0].y=Height/2;

			ViewStart[1].x=Left;
			ViewStart[1].y=Top+Height/2;
			ViewEnd[1].x=Width/2;
			ViewEnd[1].y=Height/2;

			ViewStart[2].x=Left+Width/2;
			ViewStart[2].y=Top+Height/2;
			ViewEnd[2].x=Width/2;
			ViewEnd[2].y=Height/2;

			ViewStart[3].x=Left;
			ViewStart[3].y=Top;
			ViewEnd[3].x=1;
			ViewEnd[3].y=1;
			break;
		
	case VIEW_MODE1x2a:
    
			//1x2b

			ViewStart[0].x=Left+Width/2;
			ViewStart[0].y=Top;
			ViewEnd[0].x=Width/2;
			ViewEnd[0].y=Height;

			ViewStart[1].x=Left;
			ViewStart[1].y=Top;
			ViewEnd[1].x=Width/2;
			ViewEnd[1].y=Height/2;

			ViewStart[2].x=Left;
			ViewStart[2].y=Top+Height/2;
			ViewEnd[2].x=Width/2;
			ViewEnd[2].y=Height/2;

			ViewStart[3].x=Left;
			ViewStart[3].y=Top;
			ViewEnd[3].x=1;
			ViewEnd[3].y=1;
			break;
	}

}
bool  CKSceneBase::SetActive(int X, int Y)
{
    int i;
    bool value;
    Y=Height-Y;

	if (!FullScreen)
	{

		AncActive=Active;

		for (i=0;i<4;i++)
		{
			if ( (X>=ViewStart[i].x) && (X<= (ViewEnd[i].x+ViewStart[i].x)) && (Y>=ViewStart[i].y) && (Y<=(ViewEnd[i].y+ViewStart[i].y)))
				Active=i;
		}

		value=(Active==AncActive);
	}
	else
		value=true;

    return value;
}


void  CKSceneBase::ReSize(int daWidth,int daHeight)
{
    Height=daHeight;
    Width=daWidth;
    Left=0;
    Top=0;
    ComputeSize();
    
}

bool CKSceneBase::DelShapeVert(void)
{
	CKShape *daShape,*EndIt;
	CKSegment *daSeg;
	bool daOk;
	
	bool PrevSelState;


	EndIt=NextShape;
	daShape=FirstShape;
	while (daShape!=NULL)
	{
        PrevSelState=true;

		if (daShape->NextSegment!=NULL)
		{
			if (daShape->NextSegment->Next==daShape->FirstSegment)
			{
				// closed

				daSeg=daShape->FirstSegment;
				while (daSeg!=NULL)
				{
					daOk=true;

					if ((!daSeg->Dot.Selected)&&(PrevSelState))
					{
						if (daSeg->Next!=NULL)
						{
							if (!daSeg->Next->Dot.Selected) 
							{
								AddShape();
							}
							else
							{
								daOk=false;
							}
						}
						else
						{
							daOk=false;
						}
					}

					if ((!daSeg->Dot.Selected)&&(daOk))
						NextShape->AddSegment(daSeg->Dot);


					PrevSelState=daSeg->Dot.Selected;
					daSeg=daSeg->Next;

					if (daSeg==daShape->FirstSegment)
                    {
		    			if ((!daSeg->Dot.Selected)&&(daOk))
    						NextShape->AddSegment(daSeg->Dot);

                        break;
                    }
                }
			}
			else
			{
				// opened

				daSeg=daShape->FirstSegment;
				while (daSeg!=NULL)
				{
					daOk=true;

					if ((!daSeg->Dot.Selected)&&(PrevSelState))
					{
						if (daSeg->Next!=NULL)
						{
							if (!daSeg->Next->Dot.Selected) 
							{
								AddShape();
							}
							else
							{
								daOk=false;
							}
						}
						else
						{
							daOk=false;
						}
					}

					if ((!daSeg->Dot.Selected)&&(daOk))
						NextShape->AddSegment(daSeg->Dot);


					PrevSelState=daSeg->Dot.Selected;
					daSeg=daSeg->Next;

					if (daSeg==daShape->FirstSegment) break;
					
				}
			}
			daShape->DelAll();

		}
		if (daShape==EndIt) break;

        daShape=daShape->Next;
    }

	return true;
}


bool CKSceneBase::DelShapeSeg(void)
{
	CKShape *daShape,*EndIt;
	CKSegment *daSeg;
	bool daOk;
	
	bool PrevSelState;


	EndIt=NextShape;
	daShape=FirstShape;
	while (daShape!=NULL)
	{
        PrevSelState=true;

		if (daShape->NextSegment!=NULL)
		{
			if (daShape->NextSegment->Next==daShape->FirstSegment)
			{
				// closed

				daSeg=daShape->FirstSegment;
				while (daSeg!=NULL)
				{
					daOk=true;

					if ((!daSeg->SegSelected)&&(PrevSelState))
					{
						if (daSeg->Next!=NULL)
						{
							AddShape();
						}
                        else
                        {
                            daOk=false;
                        }
					}

					if ((!daSeg->SegSelected)&&(daOk))
						NextShape->AddSegment(daSeg->Dot);

					if ((daSeg->SegSelected)&&(daOk)&&(!PrevSelState))
						NextShape->AddSegment(daSeg->Dot);


					PrevSelState=daSeg->SegSelected;
					daSeg=daSeg->Next;

					if (daSeg==daShape->FirstSegment) 
                    {
/*                        
					    if ((!daSeg->SegSelected)&&(daOk))
						    NextShape->AddSegment(daSeg->Dot);

					    if ((daSeg->SegSelected)&&(daOk)&&(!PrevSelState))
						    NextShape->AddSegment(daSeg->Dot);
                            */
					    if (!PrevSelState)
						    NextShape->AddSegment(daSeg->Dot);

                        break;
                    }
					
				}
			}
			else
			{
				// opened

				daSeg=daShape->FirstSegment;
				while (daSeg!=NULL)
				{
					daOk=true;

					if ((!daSeg->SegSelected)&&(PrevSelState))
					{
						if (daSeg->Next!=NULL)
						{
							AddShape();
						}
                        else
                        {
                            daOk=false;
                        }
					}

					if ((!daSeg->SegSelected)&&(daOk))
						NextShape->AddSegment(daSeg->Dot);

					if ((daSeg->SegSelected)&&(daOk)&&(!PrevSelState))
						NextShape->AddSegment(daSeg->Dot);


					PrevSelState=daSeg->SegSelected;
					daSeg=daSeg->Next;

					if (daSeg==daShape->FirstSegment) break;
					
				}
			}
			daShape->DelAll();

		}
		if (daShape==EndIt) break;

        daShape=daShape->Next;
    }
	for (daShape=FirstShape;daShape!=NULL;)
	{
		EndIt=daShape->Next;
		if (daShape->FirstSegment==NULL)
			DelShape(daShape);

		daShape=EndIt;
	}
	return true;
}

// -- Naming -------------------------------------------------------------------

bool CKSceneBase::GenerateName(int NameType)
{
	char prefixe[50];

	int daindd;

	switch(NameType)
	{
		case PLUGIN_CAMERA:
			strcpy(prefixe,"Camera%03d");
			daindd=nbAddedCamera;
			break;
		case PLUGIN_MESH:
			strcpy(prefixe,"Mesh%03d");
			daindd=nbAddedMesh;
			break;
		case PLUGIN_SHAPE:
			strcpy(prefixe,"Shape%03d");
			daindd=nbAddedShape;
			break;
		case PLUGIN_SKELETON:
			strcpy(prefixe,"Skeleton%03d");
			daindd=nbAddedSkel;
			break;
		case PLUGIN_PATCH:
			strcpy(prefixe,"Patch%03d");
			daindd=nbAddedPatch;
			break;
		case PLUGIN_ENTITY:
			strcpy(prefixe,"Entity%03d");
			daindd=nbAddedEntity;
			break;

	}

	CurrentName.Format(prefixe,daindd);

    return true;
}


void *CKSceneBase::GetByName(CString name,int NameType)
{
	
    CKCamera *CamAv;
	CKMesh *ObjAv;
	CKSkeleton *SkeAv;
	CKShape *ShpAv;
//	Emitter *ParAv;
	CKPatch *PatchAv;


    CamAv=FirstCam;
	ObjAv=FirstMesh;
	PatchAv=FirstPatch;
	SkeAv=FirstSkel;
	ShpAv=FirstShape;
//	ParAv=FirstEmit;


	switch(NameType)
	{
		case PLUGIN_CAMERA:
		   while(CamAv!=NULL)
			{
				if (CamAv->Name==name)
					return CamAv;

				CamAv=CamAv->Next;
			}
			break;
		case PLUGIN_MESH:
		   while(ObjAv!=NULL)
			{
				if (ObjAv->Name==name)
					return ObjAv;

				ObjAv=ObjAv->Next;
			}

			break;
		case PLUGIN_SHAPE:
		   while(ShpAv!=NULL)
			{
				if (ShpAv->Name==name)
					return ShpAv;

				ShpAv=ShpAv->Next;
			}

			break;
		case PLUGIN_SKELETON:
		   while(SkeAv!=NULL)
			{
				if (SkeAv->Name==name)
					return SkeAv;

				SkeAv=SkeAv->Next;
			}

			break;
		case PLUGIN_PATCH:
		   while(PatchAv!=NULL)
			{
				if (PatchAv->Name,name)
					return PatchAv;

				PatchAv=PatchAv->Next;
			}

			break;
	}

    return NULL;
}
/*
CPrivateData * CKSceneBase::AddPrivate(char *Name)
{
    CPrivateData *pd;

    pd=FirstData;
    while (pd!=NULL)
    {
        if (strcmp(pd->Name,Name)==0)
        {
            return pd;
        }
        pd=pd->Next;
    }

	if (FirstData==NULL)
    {
        FirstData=new (CPrivateData)(NULL,NULL);
        NextData=FirstData;
    }
    else
    {
        NextData->Next=new (CPrivateData)(NextData,NULL);
        NextData=NextData->Next;
    }

    strcpy(NextData->Name,Name);

    NextData->lpBits=NULL;

    return NextData;

}

CPrivateData *CKSceneBase::GetPrivate(char *Name)
{
    CPrivateData *pd;

    pd=FirstData;
    while (pd!=NULL)
    {
        if (strcmp(pd->Name,Name)==0)
        {
            return pd;
        }
        pd=pd->Next;
    }

    return NULL;
}
*/
void CKSceneBase::CopySelectedTo(CKSceneBase *DstDk)
{
    CKShape *daShp;
    CKMesh *daObj;
    CKPatch *daPatch;
    CKSkeleton *daSkel;
    CKCamera *daCam;
    CKSegment *daSeg;
	CKEntity *daEnt;
    bool PrevSel;
	bool ASegAdded;
    int i;

    daShp=FirstShape;
    while(daShp!=NULL)
    {
        if (!daShp->Hided)
		{
			if (daShp->Selected) 
			{
				DstDk->AddShape();
				daSeg=daShp->FirstSegment;

				while(daSeg!=NULL)
				{
					DstDk->NextShape->AddSegment(daSeg->Dot);
					DstDk->AddBufVert(&DstDk->NextShape->NextSegment->Dot);
					daSeg=daSeg->Next;
					if (daSeg==daShp->FirstSegment)
					{
						DstDk->NextShape->Close();
						break;
					}
				}
				DstDk->NextShape->Selected=true;
			}
			else 
			{
				PrevSel=false;
            
				daSeg=daShp->FirstSegment;
				ASegAdded=false;

				while(daSeg!=NULL)
				{
					if (daSeg->SegSelected)
					{
						if (!PrevSel) DstDk->AddShape();
						DstDk->NextShape->AddSegment(daSeg->Dot);
						DstDk->AddBufVert(&DstDk->NextShape->NextSegment->Dot);
						ASegAdded=true;
					}

					if ((!daSeg->SegSelected)&&(PrevSel))
					{
						DstDk->NextShape->AddSegment(daSeg->Dot);
						DstDk->AddBufVert(&DstDk->NextShape->NextSegment->Dot);
						ASegAdded=true;
					}

					PrevSel=daSeg->SegSelected;
                
					daSeg=daSeg->Next;
					if (daSeg==daShp->FirstSegment) 
					{
						if ((!daSeg->SegSelected)&&(PrevSel))
						{
							DstDk->NextShape->AddSegment(daSeg->Dot);
							DstDk->AddBufVert(&DstDk->NextShape->NextSegment->Dot);
							ASegAdded=true;
						}

						break;
					}
				}
				if (ASegAdded)
					DstDk->NextShape->Selected=true;

			}
		}
        daShp=daShp->Next;

    }

    daObj=FirstMesh;
    while(daObj!=NULL)
    {
        if (!daObj->Hided)
		{
			if (daObj->Selected) 
			{
				DstDk->AddMesh();
				DstDk->NextMesh->IsCopyOf(daObj);
				DstDk->NextMesh->Selected=true;
				for (i=0;i<DstDk->NextMesh->nb2vert;i++)
					DstDk->AddBufVert(&DstDk->NextMesh->pv[i]);
			

				if (daObj->Tex1!=NULL) 
				{
					DstDk->NextMesh->Tex1=DstDk->AddTex(daObj->Tex1->FileName);
					DstDk->NextMesh->Tex1->Type=daObj->Tex1->Type;
				}
				if (daObj->Tex2!=NULL) 
				{
					DstDk->NextMesh->Tex2=DstDk->AddTex(daObj->Tex2->FileName);
					DstDk->NextMesh->Tex2->Type=daObj->Tex2->Type;
				}
				if (daObj->Tex3!=NULL) 
				{
					DstDk->NextMesh->Tex3=DstDk->AddTex(daObj->Tex3->FileName);
					DstDk->NextMesh->Tex3->Type=daObj->Tex3->Type;
				}
				if (daObj->Tex4!=NULL) 
				{
					DstDk->NextMesh->Tex4=DstDk->AddTex(daObj->Tex4->FileName);
					DstDk->NextMesh->Tex4->Type=daObj->Tex4->Type;
				}

				for (i=0;i<DstDk->NextMesh->nb2poly;i++)
				{
					for (int j=0;j<8;j++)
					{
						if (daObj->pl[i].Maps[j]!=NULL) 
						{
							DstDk->NextMesh->pl[i].Maps[j]=DstDk->AddTex(daObj->pl[i].Maps[j]->FileName);
							DstDk->NextMesh->pl[i].Maps[j]->Type=daObj->pl[i].Maps[j]->Type;
						}
					}
				}
				DstDk->NextMesh->UpdateMesh();

			}
			else
			{
				daObj->SelectedFaceToScene((CKScene*)DstDk);
			}
		}
        daObj=daObj->Next;
    }

	// Patch

    daPatch=FirstPatch;
    while(daPatch!=NULL)
    {
		if (!daPatch->Hided)
		{
			if (daPatch->Selected)
			{
				DstDk->AddPatch();
				DstDk->NextPatch->IsCopyOf(daPatch);
				DstDk->NextPatch->Selected=true;
				DstDk->NextPatch->Update();

				if (daPatch->Tex1!=NULL) 
				{
					DstDk->NextPatch->Tex1=DstDk->AddTex(daPatch->Tex1->FileName);
					DstDk->NextPatch->Tex1->Type=daPatch->Tex1->Type;
				}
				if (daPatch->Tex2!=NULL) 
				{
					DstDk->NextPatch->Tex2=DstDk->AddTex(daPatch->Tex2->FileName);
					DstDk->NextPatch->Tex2->Type=daPatch->Tex2->Type;
				}
				if (daPatch->Tex3!=NULL) 
				{
					DstDk->NextPatch->Tex3=DstDk->AddTex(daPatch->Tex3->FileName);
					DstDk->NextPatch->Tex3->Type=daPatch->Tex3->Type;
				}
				if (daPatch->Tex4!=NULL) 
				{
					DstDk->NextPatch->Tex4=DstDk->AddTex(daPatch->Tex4->FileName);
					DstDk->NextPatch->Tex4->Type=daPatch->Tex4->Type;
				}
			}
		}
        daPatch=daPatch->Next;
    }

	// Entity

    daEnt=FirstEntity;
    while(daEnt!=NULL)
    {
		if (!daEnt->Hided)
		{
			if (daEnt->Selected)
			{
				DstDk->AddEntity(daEnt->EntType);
				DstDk->NextEntity->IsCopyOf(daEnt);
				DstDk->NextEntity->Selected=true;
			}
		}
        daEnt=daEnt->Next;
    }

	// CKSkeleton

    daSkel=FirstSkel;
    while(daSkel!=NULL)
    {
		if (!daSkel->Hided)
		{
			if (daSkel->Selected) 
			{
				DelSkeleton(daSkel);
			}
			/*
			else
				daSkel->DelSelectedBones(daSkel->bone);
				*/
		}
        daSkel=daSkel->Next;
    }

    daCam=FirstCam;
    while(daCam!=NULL)
    {
		if (!daCam->Hided)
		{
			if ((daCam->Source.Selected)||(daCam->Dest.Selected))
			{
				DstDk->AddCam();
				DstDk->NextCam->IsCopyOf(daCam);
				DstDk->NextCam->Source.Selected=true;
				DstDk->NextCam->Dest.Selected=true;
				DstDk->AddBufVert(&DstDk->NextCam->Source);
				DstDk->NextBufVert->TargetCont=(void*)DstDk->NextCam;
				DstDk->NextBufVert->TargetType=PLUGIN_CAMERA;
				DstDk->AddBufVert(&DstDk->NextCam->Dest);
				DstDk->NextBufVert->TargetCont=(void*)DstDk->NextCam;
				DstDk->NextBufVert->TargetType=PLUGIN_CAMERA;
			}
		}
        daCam=daCam->Next;
    }
	
/*
	CKPlan dap;
	if (DstDk->cSel!=NULL)
	{
		dap.PlanOfView(DstDk->m_Renderer,DstDk->Active);
		dap.pX.Normalize();
		dap.pY.Normalize();
		Vertex tr=(dap.pX*SnapVal.x);
		Vertex tr2=(dap.pY*SnapVal.y);
		Vertex tr3=tr+tr2;
		DstDk->TranslateBuf(&dap,tr3);
		DstDk->UpdateBuf();
		DstDk->UpdateTaged(PLUGIN_ALL);

		DstDk->UpdateSmthSel();
	}
	*/
	UpdateSmthSel();

	DrawViews();
}

CKTexture * CKSceneBase::AddTex(CString TexName)
{
	int ctTex=0;
    CKTexture *tmp;
	char FName[_MAX_PATH],FExt[50];

	if (TexName=="DefaultTexture")
		return FirstTexture;


	_splitpath(TexName.GetBuffer(0),NULL,NULL,FName,FExt);
	CString ShortName=FName;
	ShortName+=FExt;

    tmp=FirstTexture;
    while(tmp!=NULL)
    {
        if (ShortName==tmp->ShortName) return tmp;
		ctTex++;
        tmp=tmp->Next;
    }

    if (FirstTexture==NULL)
    {
        FirstTexture=new (CKTexture)((CKScene*)this,NULL,NULL);
        NextTexture=FirstTexture;
		NextTexture->m_Scene=(CKScene*)this;
		NextTexture->m_Renderer=m_Renderer;
    }
    else
    {
        NextTexture->Next=new (CKTexture)((CKScene*)this,NextTexture,(CKTexture*)NULL);
        NextTexture=NextTexture->Next;
		NextTexture->m_Scene=(CKScene*)this;
		NextTexture->m_Renderer=m_Renderer;

    }

    NextTexture->FileName=TexName;
	NextTexture->ShortName=ShortName;
	NextTexture->Type=TEXTURE_FILE;
	NextTexture->Indice=ctTex;

    return NextTexture;
}

CKTexture * CKSceneBase::GetTexByShortName(CString TexName)
{
	char FName[_MAX_PATH],FExt[50];

	if (TexName=="DefaultTexture")
		return FirstTexture;

	_splitpath(TexName.GetBuffer(0),NULL,NULL,FName,FExt);
	CString ShortName=FName;
	ShortName+=FExt;

    for (CKTexture *tmp=FirstTexture;tmp!=NULL;tmp=tmp->Next)
        if (ShortName==tmp->ShortName) return tmp;

    return NULL;
}

void CKSceneBase::DelTex(CKTexture *daTex)
{
    if (daTex==FirstTexture)
        FirstTexture=FirstTexture->Next;

    if (daTex==NextTexture)
        NextTexture=NextTexture->Prev;

    if (daTex->Next!=NULL)
        daTex->Next->Prev=daTex->Prev;

    if (daTex->Prev!=NULL)
        daTex->Prev->Next=daTex->Next;

    delete daTex;
}

/* 
	Returns true if a texture is still used in the CKSceneBase

*/
bool CKSceneBase::IsTextureStillUsed(CKTexture *daTex)
{

	return true;
}
/*
void CKSceneBase::RecalcTextureIndices(void)
{
	int Indice=0;
	for (CKTexture *datex=FirstTexture;datex!=NULL;datex=datex->Next)
	{
		datex->Indice=Indice;
		Indice++;
	}
}
*/
/*
	return unique numbers per entity

*/
void *CKSceneBase::GetByUnique(unsigned int _Unique,int Type)
{
	CKMesh *daObj;
	CKShape *daShp;
	CKCamera *daCam;
	CKEntity *daEntity;
	CKPatch *daPatch;
	CKSkeleton *daSkel;


	switch (Type)
	{
	case PLUGIN_MESH:
		for (daObj=FirstMesh;daObj!=NULL;daObj=daObj->Next)
			if (daObj->Unique==_Unique) return daObj;
		break;
	case PLUGIN_SHAPE:
		for (daShp=FirstShape;daShp!=NULL;daShp=daShp->Next)
			if (daShp->Unique==_Unique) return daShp;
		break;
	case PLUGIN_CAMERA:
		for (daCam=FirstCam;daCam!=NULL;daCam=daCam->Next)
			if (daCam->Unique==_Unique) return daCam;
		break;
	case PLUGIN_ENTITY:
		for (daEntity=FirstEntity;daEntity!=NULL;daEntity=daEntity->Next)
			if (daEntity->Unique==_Unique) return daEntity;
		break;
	case PLUGIN_PATCH:
		for (daPatch=FirstPatch;daPatch!=NULL;daPatch=daPatch->Next)
			if (daPatch->Unique==_Unique) return daPatch;
		break;
	case PLUGIN_SKELETON:
		for (daSkel=FirstSkel;daSkel!=NULL;daSkel=daSkel->Next)
			if (daSkel->Unique==_Unique) return daSkel;
		break;
	default:
		break;
	}

	return NULL;
}

// -- Undo --------------------------------------------------------------------

CKUndoRedo *CKSceneBase::AddUndo(CString _PlugName,int _nbEntries)
{
    if (FirstUndo==NULL)
    {
        FirstUndo=new (CKUndoRedo)(_PlugName,(CKScene*)this,_nbEntries,NULL,NULL);
        NextUndo=FirstUndo;
    }
    else
    {
        NextUndo->Next=new (CKUndoRedo)(_PlugName,(CKScene*)this,_nbEntries,NextUndo,NULL);
        NextUndo= NextUndo->Next;
    }
	// delete redo
	
    CKUndoRedo *daRedo,*daRedo2;

    daRedo=FirstRedo;
    while(daRedo!=NULL)
    {
        daRedo2=daRedo->Next;
        delete daRedo;
        daRedo=daRedo2;
    }
    FirstRedo=NULL;
    NextRedo=NULL;

	return NextUndo;
}

void CKSceneBase::AddRedo(CKUndoRedo *daUndo)
{
    if (FirstRedo==NULL)
    {
        FirstRedo=daUndo;
        NextRedo=FirstRedo;
		NextRedo->Prev=NULL;
		NextRedo->Next=NULL;
    }
    else
    {
        NextRedo->Next=daUndo;
		NextRedo->Next->Prev=NextRedo;
        NextRedo=NextRedo->Next;

    }
}

void CKSceneBase::AddUndo(CKUndoRedo *daRedo)
{
    if (FirstUndo==NULL)
    {
        FirstUndo=daRedo;
        NextUndo=FirstUndo;
		NextUndo->Prev=NULL;
		NextUndo->Next=NULL;

    }
    else
    {
        NextUndo->Next=daRedo;
		NextUndo->Next->Prev=NextUndo;
        NextUndo=NextUndo->Next;
    }
}

void CKSceneBase::Undo(CKScenePlugin *gen)
{
	if (NextUndo!=NULL)
	{
//		NextUndo->gen->Process(KM_UNDO,NextUndo,0);
		NextUndo->CommitAllPrev(gen);
		CKUndoRedo *tmpUndo=NextUndo;
		

		if (NextUndo->Prev==NULL)
		{
			NextUndo=NULL;
			FirstUndo=NULL;
		}
		else
		{
			NextUndo=NextUndo->Prev;
			NextUndo->Next=NULL;
		}

		DeleteBufVert();
		UpdateSmthSel();
		AddRedo(tmpUndo);
		
	}
}

void CKSceneBase::Redo(void)
{
	if (NextRedo!=NULL)
	{
		//NextRedo->gen->Process(KM_REDO,NextRedo,0);
		NextRedo->CommitAllAfter();
		CKUndoRedo *tmpUndo=NextRedo;

		

		if (NextRedo->Prev==NULL)
		{
			NextRedo=NULL;
			FirstRedo=NULL;
		}
		else
		{
			NextRedo=NextRedo->Prev;
			NextRedo->Next=NULL;
		}

		DeleteBufVert();
		UpdateSmthSel();
		AddUndo(tmpUndo);
	}
}

void CKSceneBase::InitAllTag(int Value,int PlugType)
{
	if (PlugType&PLUGIN_MESH)
		for(CKMesh *daObj=FirstMesh;daObj!=NULL;daObj=daObj->Next)
			daObj->Tag=Value;

	if (PlugType&PLUGIN_CAMERA)
		for(CKCamera *daCam=FirstCam;daCam!=NULL;daCam=daCam->Next)
			daCam->Tag=Value;

	if (PlugType&PLUGIN_PATCH)
		for(CKPatch *daPatch=FirstPatch;daPatch!=NULL;daPatch=daPatch->Next)
			daPatch->Tag=Value;

	if (PlugType&PLUGIN_ENTITY)
		for(CKEntity *daEntity=FirstEntity;daEntity!=NULL;daEntity=daEntity->Next)
			daEntity->Tag=Value;

	if (PlugType&PLUGIN_SHAPE)
		for(CKShape *daShape=FirstShape;daShape!=NULL;daShape=daShape->Next)
			daShape->Tag=Value;

	if (PlugType&PLUGIN_SKELETON)
		for(CKSkeleton *daSkel=FirstSkel;daSkel!=NULL;daSkel=daSkel->Next)
			daSkel->Tag=Value;
}

void CKSceneBase::UpdateTaged(int PlugType)
{
	if (PlugType&PLUGIN_MESH)
		for(CKMesh *daObj=FirstMesh;daObj!=NULL;daObj=daObj->Next)
			if (daObj->Tag==1) 
			{
				daObj->UpdateMesh();
			}

	if (PlugType&PLUGIN_CAMERA)
		for(CKCamera *daCam=FirstCam;daCam!=NULL;daCam=daCam->Next)
			if (daCam->Tag==1) 
			{
				//daCam->SetCamera();
				m_Renderer->SetCamera(daCam);
			}

	if (PlugType&PLUGIN_PATCH)
		for(CKPatch *daPatch=FirstPatch;daPatch!=NULL;daPatch=daPatch->Next)
			if (daPatch->Tag==1) 
			{
				daPatch->Build(10);
				daPatch->Update();
			}


	if (PlugType&PLUGIN_ENTITY)
		for(CKEntity *daEntity=FirstEntity;daEntity!=NULL;daEntity=daEntity->Next)
			if (daEntity->Tag==1) 
			{
				daEntity->Update();
				//CurrentPlugin(KM_UPDATEENTITY,(int)(CKScene*)this,0);
			}

	if (PlugType&PLUGIN_SHAPE)
		for(CKShape *daShape=FirstShape;daShape!=NULL;daShape=daShape->Next)
			if (daShape->Tag==1) 
			{
				daShape->UpdateShape();
			}

	if (PlugType&PLUGIN_SKELETON)
		for(CKSkeleton *daSkel=FirstSkel;daSkel!=NULL;daSkel=daSkel->Next)
			if (daSkel->Tag==1)
			{
				daSkel->UpdateSkel();
				//daSkel->BuildBase();
			}
}
/*

*/

bool CKSceneBase::SymBuf(Vertex Factor)
{
    VertBuf *daBufVert;
	CKPlan *Dap;
	Vertex Center=HookMinSel+((HookMaxSel-HookMinSel)/2.0f);


	Dap=new CKPlan();
	Dap->PlanOfView(m_Renderer,Active);
    Dap->ScaleMatrix();

    daBufVert=FirstBufVert;
    while(daBufVert!=NULL)
    {
        daBufVert->IsNow( Dap->Scale((daBufVert->AncVal-Center),Factor)+Center );
        daBufVert=daBufVert->Next;
    }

    delete Dap;

    return true;
}







bool CKSceneBase::RecCountSkel(CKBone *daBone)
{
	CKBone *curBone;

	if (daBone->Selected) return true;

	curBone = daBone->FirstBone;
	while(curBone!=NULL)
	{
		if (RecCountSkel(curBone)) return true;
		curBone=curBone->Next;
	}	
}



int CKSceneBase::GetNbSelectedMeshs(void)
{
	int nbObjSel=0;

	// Mesh;
	UndoRedoEntriesCount.erase(UndoRedoEntriesCount.begin(), UndoRedoEntriesCount.end());
						   
	for (CKMesh *daObj2=FirstMesh;daObj2!=NULL;daObj2=daObj2->Next)
	{
		if (daObj2->Selected) 
		{
			UndoRedoEntriesCount.push_back(new UndoEntryCount(daObj2,PLUGIN_MESH));
			
		}
		else
		{
			for (int i=0;i<daObj2->nb2vert;i++)
			{
				if (daObj2->pv[i].Selected)
				{
					UndoRedoEntriesCount.push_back(new UndoEntryCount(daObj2,PLUGIN_MESH));
					break;
				}
			}
		}
	}

	// camera
	for(CKCamera *daCam=FirstCam;daCam!=NULL;daCam=daCam->Next)
		if ((daCam->Selected)||(daCam->Source.Selected)||(daCam->Dest.Selected)) 
			UndoRedoEntriesCount.push_back(new UndoEntryCount(daCam,PLUGIN_CAMERA));

	// patch
	for(CKPatch *daPatch=FirstPatch;daPatch!=NULL;daPatch=daPatch->Next)
	{
		if (daPatch->Selected) 
		{
			UndoRedoEntriesCount.push_back(new UndoEntryCount(daPatch,PLUGIN_PATCH));
		}
		else
		{
			for (int i=0;i<daPatch->nb2vert;i++)
			{
				if (daPatch->pv[i].Selected)
				{
					UndoRedoEntriesCount.push_back(new UndoEntryCount(daPatch,PLUGIN_PATCH));
					break;
				}
			}
		}
	}

	// entity

	for(CKEntity *daEntity=FirstEntity;daEntity!=NULL;daEntity=daEntity->Next)
	{
		if (daEntity->Selected)
		{
			UndoRedoEntriesCount.push_back(new UndoEntryCount(daEntity,PLUGIN_ENTITY));
		}
		else
		{

		}
	}

	// shape

	for(CKShape *daShape=FirstShape;daShape!=NULL;daShape=daShape->Next)
	{
		if (daShape->Selected)
		{
			UndoRedoEntriesCount.push_back(new UndoEntryCount(daShape,PLUGIN_SHAPE));
		}
		else
		{
			CKSegment *DrawSeg;
			DrawSeg=daShape->FirstSegment;

			while(DrawSeg!=NULL)
			{
				if (DrawSeg->SegSelected)
				{
					UndoRedoEntriesCount.push_back(new UndoEntryCount(daShape,PLUGIN_SHAPE));
					break;
				}

				DrawSeg=DrawSeg->Next;

				if (DrawSeg==daShape->FirstSegment)
				{
					break;
				}
	        }
		}
	}

	for(CKSkeleton *daSkel=FirstSkel;daSkel!=NULL;daSkel=daSkel->Next)
	{
		if (daSkel->Selected)
		{
			UndoRedoEntriesCount.push_back(new UndoEntryCount(daSkel,PLUGIN_SKELETON));
		}
		else
		{
			if (RecCountSkel(daSkel->bone))
				UndoRedoEntriesCount.push_back(new UndoEntryCount(daSkel,PLUGIN_SKELETON));

		}
	}
	

	return nbObjSel;
}


void CKSceneBase::SetSelectedToAfterUndo(CString PlugName,int UndoType)
{
	CKUndoRedo *CurrentUndo=AddUndo(PlugName,UndoRedoEntriesCount.size());
	CurrentUndo->UndoType=UndoType;

	for (int UndoAv=0;UndoAv<UndoRedoEntriesCount.size();UndoAv++)
	{
		CurrentUndo->SetAfterEntry(UndoAv,UndoRedoEntriesCount[UndoAv]->TargetType,UndoRedoEntriesCount[UndoAv]->TargetPtr);
	}
}

void CKSceneBase::SetSelectedToBeforeUndo(CString PlugName,int UndoType)
{
	CKUndoRedo *CurrentUndo=AddUndo(PlugName,UndoRedoEntriesCount.size());
	CurrentUndo->UndoType=UndoType;

	for (int UndoAv=0;UndoAv<UndoRedoEntriesCount.size();UndoAv++)
	{
		CurrentUndo->SetPrevEntry(UndoAv,UndoRedoEntriesCount[UndoAv]->TargetType,UndoRedoEntriesCount[UndoAv]->TargetPtr);
	}
}


void CKSceneBase::SetSelectedToAfterUndoNoADD() //char *PlugName,int UndoType)
{
	CKUndoRedo *CurrentUndo=NextUndo;//AddUndo(PlugName,UndoRedoEntriesCount.size());

	for (int UndoAv=0;UndoAv<UndoRedoEntriesCount.size();UndoAv++)
	{
		CurrentUndo->SetAfterEntry(UndoAv,UndoRedoEntriesCount[UndoAv]->TargetType,UndoRedoEntriesCount[UndoAv]->TargetPtr);
	}
}

void CKSceneBase::SetSelectedToBeforeUndoNoADD() //char *PlugName,int UndoType)
{
	CKUndoRedo *CurrentUndo=NextUndo;//AddUndo(PlugName,UndoRedoEntriesCount.size());
	//CurrentUndo->UndoType=UndoType;

	for (int UndoAv=0;UndoAv<UndoRedoEntriesCount.size();UndoAv++)
	{
		CurrentUndo->SetPrevEntry(UndoAv,UndoRedoEntriesCount[UndoAv]->TargetType,UndoRedoEntriesCount[UndoAv]->TargetPtr);
	}
}


void CKSceneBase::ChangeGrid(int NewGridInd)
{
	if (NewGridInd<0)
		SnapValCounter=0;
	else
	if (NewGridInd>4)
		SnapValCounter=4;
	else
		SnapValCounter=NewGridInd;

	SnapVal.x=KOption2->GridSpace(SnapValCounter);
	SnapVal.y=KOption2->GridSpace(SnapValCounter);
	SnapVal.z=KOption2->GridSpace(SnapValCounter);
}

void CKSceneBase::ChangeAngle(int NewAngleInd)
{
	if (NewAngleInd<0)
		AngleValCounter=0;
	else
	if (NewAngleInd>4)
		AngleValCounter=4;
	else
		AngleValCounter=NewAngleInd;

	AngleSnapVal=KOption2->AngleSnap(AngleValCounter);
}
void CKSceneBase::SetSceneForReading(bool IsReading)
{
	m_IsReading=IsReading;
}

void CKSceneBase::ActiveViewToUndo()
{
	ViewInfos *curvf=new ViewInfos;
	LatestVI=curvf;

	curvf->ViewType=ViewType[Active];

	if (ViewType[Active]==VIEWTYPE_PERSPECTIVE)
	{
		curvf->cam.IsCopyOf(&Perspective[Active]);
	}
	else
	if (ViewType[Active]==VIEWTYPE_CAMERA)
	{
		curvf->cam.IsCopyOf(cam[Active]);
	}

	curvf->ViewNg=ViewNg[Active];
	curvf->ViewPos=ViewPos[Active];
	curvf->ViewSize=ViewSize[Active];

	VUndoInf[Active].push_back(curvf);

	// remove all redo
	VRedoInf[Active].erase(VRedoInf[Active].begin(),VRedoInf[Active].end());
}

void CKSceneBase::ActiveViewToCurrentRedo()
{
	int ind=VUndoInf[Active].size();

	ViewInfos *curvf=NULL;

	if (ind!=0)
		curvf=VUndoInf[Active][ind-1];
	
	if (curvf!=NULL)
	{
		curvf->RedoViewType=ViewType[Active];

		if (ViewType[Active]==VIEWTYPE_PERSPECTIVE)
		{
			curvf->Redocam.IsCopyOf(&Perspective[Active]);
		}
		else
		if (ViewType[Active]==VIEWTYPE_CAMERA)
		{
			curvf->Redocam.IsCopyOf(cam[Active]);
		}

		curvf->RedoViewNg=ViewNg[Active];
		curvf->RedoViewPos=ViewPos[Active];
		curvf->RedoViewSize=ViewSize[Active];
	}
}

void CKSceneBase::UndoViewChange()
{
	if (VUndoInf[Active].size()>0)
	{
		ViewInfos *curvf=VUndoInf[Active].back();
	
		ViewType[Active]=curvf->ViewType;

		if (ViewType[Active]==VIEWTYPE_PERSPECTIVE)
		{
			Perspective[Active].IsCopyOf(&curvf->cam);
		}
		else
		if (ViewType[Active]==VIEWTYPE_CAMERA)
		{
			cam[Active]->IsCopyOf(&curvf->cam);
		}

		ViewNg[Active]=curvf->ViewNg;
		ViewPos[Active]=curvf->ViewPos;
		ViewSize[Active]=curvf->ViewSize;

		// push Redo
		VRedoInf[Active].push_back(curvf);

		VUndoInf[Active].pop_back();

		DrawViews();
	}
}

void CKSceneBase::RedoViewChange()
{
	if (VRedoInf[Active].size()>0)
	{

		ViewInfos *curvf=VRedoInf[Active].back();
	
		ViewType[Active]=curvf->ViewType;

		if (ViewType[Active]==VIEWTYPE_PERSPECTIVE)
		{
			Perspective[Active].IsCopyOf(&curvf->Redocam);
		}
		else
		if (ViewType[Active]==VIEWTYPE_CAMERA)
		{
			cam[Active]->IsCopyOf(&curvf->Redocam);
		}

		ViewNg[Active]=curvf->RedoViewNg;
		ViewPos[Active]=curvf->RedoViewPos;
		ViewSize[Active]=curvf->RedoViewSize;

		// push Undo
		VUndoInf[Active].push_back(curvf);

		VRedoInf[Active].pop_back();

		DrawViews();
	}
}

void CKSceneBase::SetVIWheel(bool UseWheel)
{
	if (LatestVI!=NULL)
	{
		LatestVI->WheelChange=UseWheel;
	}
}

bool CKSceneBase::GetVIWheel()
{
	if (LatestVI!=NULL)
		return LatestVI->WheelChange;
	else
		return false;
}

void CKSceneBase::SetRenderer(CKRenderer *pRenderer)
{
	m_Renderer=pRenderer;

	for (int i=0;i<4;i++)
	{
		m_skybox[i].SetRenderer(pRenderer);
	}

	m_bkTop=new CKBackPic((CKScene*)this);
	m_bkFront=new CKBackPic((CKScene*)this);
	m_bkLeft=new CKBackPic((CKScene*)this);

	for (i=0;i<4;i++)
	{
		Perspective[i].m_Scene=(CKScene*)this;
		Perspective[i].SetSource(Vertex(0,-192,64));
		Perspective[i].SetDest(Vertex(0,0,0));
	}
}

void CKSceneBase::InitDefaultTexture()
{
	CKOption *tmpOpt=((CKOption*)GetGOption());
	if (tmpOpt!=NULL)
	{
		//AddTex("DefaultTexture");

		FirstTexture=new (CKTexture)((CKScene*)this,NULL,NULL);
        NextTexture=FirstTexture;
		NextTexture->m_Scene=(CKScene*)this;
		NextTexture->m_Renderer=m_Renderer;

		NextTexture->FileName=tmpOpt->GetDefaultTexture();//>Type=TEXTURE_RESSOURCE;

		char FName[_MAX_PATH],FExt[50];

		_splitpath(tmpOpt->GetDefaultTexture(),NULL,NULL,FName,FExt);
		CString ShortName=FName;
		ShortName+=FExt;


		NextTexture->ShortName=ShortName;

		NextTexture->Indice=0;
		
	}
}

void CKSceneBase::UpdateSmthSel(void)
{
}