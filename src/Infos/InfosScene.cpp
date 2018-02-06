// InfosScene.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "InfosScene.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfosScene dialog


CInfosScene::CInfosScene(CWnd* pParent /*=NULL*/)
	: CDialog(CInfosScene::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInfosScene)
	//}}AFX_DATA_INIT
}


void CInfosScene::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfosScene)
	DDX_Control(pDX, IDC_OBJ, m_Mesh);
	DDX_Control(pDX, IDC_SKELETTON, m_Skeletons);
	DDX_Control(pDX, IDC_SHAPE, m_shapes);
	DDX_Control(pDX, IDC_SEGMENT, m_Segments);
	DDX_Control(pDX, IDC_OBJVERT, m_MeshVert);
	DDX_Control(pDX, IDC_PATCH, m_Patch);
	DDX_Control(pDX, IDC_OBJFACE, m_MeshFaces);
	DDX_Control(pDX, IDC_ENTITIES, m_Entities);
	DDX_Control(pDX, IDC_CAMERA, m_Camera);
	DDX_Control(pDX, IDC_BONE, m_Bone);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInfosScene, CDialog)
	//{{AFX_MSG_MAP(CInfosScene)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfosScene message handlers

int CInfosScene::RecCalcBone(CKBone *daBone)
{
	int bone=0;
	CKBone *daBone2;
	bone++;

	daBone2=daBone->FirstBone;
	while(daBone2!=NULL)
	{
		bone+=RecCalcBone(daBone2);

		daBone2=daBone2->Next;
	}
	return bone;
}



void CInfosScene::AffValues()
{
	int obj,objvert,objface,camera,shape,segment;
	int skeletton,bone,patch,entities;

	CKMesh *daMesh;
	CKCamera *daCam;
	CKShape *daShp;
	CKSkeleton *daSkel;
	CKSegment *daSeg;
	CKBone *daBone;
	CKPatch *daPatch;
	CKEntity *daEnt;


	obj=0;
	objvert=0;
	objface=0;

	camera=0;

	shape=0;
	segment=0;

	skeletton=0;
	bone=0;

	patch=0;

	entities=0;


	// Obj

	for (daMesh=m_Scene->FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
	{
		if (daMesh->nb2poly!=0)
		{
			obj++;
			objvert+=daMesh->nb2vert;
			objface+=daMesh->nb2poly;
		}
	}

	// cam

	for (daCam=m_Scene->FirstCam;daCam!=NULL;daCam=daCam->Next)
	{
		camera++;
	}

	// Entities

	for (daEnt=m_Scene->FirstEntity;daEnt!=NULL;daEnt=daEnt->Next)
	{
		entities++;
	}

	// Patch

	for (daPatch=m_Scene->FirstPatch;daPatch!=NULL;daPatch=daPatch->Next)
	{
		patch++;
	}

	// shape

	for (daShp=m_Scene->FirstShape;daShp!=NULL;daShp=daShp->Next)
	{

		daSeg=daShp->FirstSegment;
		if (daSeg!=NULL) shape++;
		while(daSeg!=NULL)
		{
			segment++;
			daSeg=daSeg->Next;
            if (daSeg==daShp->FirstSegment)
				break;
		}
	}

	// skeletton

	for (daSkel=m_Scene->FirstSkel;daSkel!=NULL;daSkel=daSkel->Next)
	{
		skeletton++;
		daBone=daSkel->bone;
		while(daBone!=NULL)
		{
			bone+=RecCalcBone(daBone);
			daBone=daBone->Next;
		}
	}

	// affichage
	CString affval;
	affval.Format("%d",obj);
	m_Mesh.SetWindowText(affval);

	affval.Format("%d",skeletton);
	m_Skeletons.SetWindowText(affval);

	affval.Format("%d",shape);
	m_shapes.SetWindowText(affval);

	affval.Format("%d",segment);
	m_Segments.SetWindowText(affval);

	affval.Format("%d",objvert);
	m_MeshVert.SetWindowText(affval);

	affval.Format("%d",patch);
	m_Patch.SetWindowText(affval);

	affval.Format("%d",objface);
	m_MeshFaces.SetWindowText(affval);

	affval.Format("%d",entities);
	m_Entities.SetWindowText(affval);

	affval.Format("%d",camera);
	m_Camera.SetWindowText(affval);

	affval.Format("%d",bone);
	m_Bone.SetWindowText(affval);

}