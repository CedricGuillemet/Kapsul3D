// WeightSkel.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "WeightSkel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWeightSkel dialog

CWeightSkel::CWeightSkel(CWnd* pParent /*=NULL*/)
	: CDialog(CWeightSkel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWeightSkel)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CWeightSkel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWeightSkel)
	DDX_Control(pDX, IDC_LISTSKEL, m_ListSkels);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWeightSkel, CDialog)
	//{{AFX_MSG_MAP(CWeightSkel)
	ON_BN_CLICKED(IDC_ASSIGNOBJ, OnAssignobj)
	ON_BN_CLICKED(IDC_SELTOBONE, OnSeltobone)
	ON_BN_CLICKED(IDC_GETSEL, OnGetsel)
	ON_BN_CLICKED(IDC_UNASSIGNED, OnUnassigned)
	ON_BN_CLICKED(IDC_AUTOWEIGHTS, OnAutoWeights)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWeightSkel message handlers

void CWeightSkel::OnAssignobj() 
{
	// TODO: Add your control notification handler code here
	
}

void CWeightSkel::OnSeltobone() 
{
	// TODO: Add your control notification handler code here
	
}

void CWeightSkel::OnGetsel() 
{
	// TODO: Add your control notification handler code here
	
}

void CWeightSkel::OnUnassigned() 
{
	// TODO: Add your control notification handler code here
	
}

double FallOff=350;

void CWeightSkel::OnAutoWeights() 
{
	/*
		GOOD Weight ==1
*/
	int i,j;

	m_Plugin->m_Scene->FirstSkel->m_Mesh=m_Plugin->m_Scene->FirstMesh;

	
	CKMesh *daMesh=m_Plugin->m_Scene->FirstMesh;
	CKSkeleton *Ske=m_Plugin->m_Scene->FirstSkel;

	for (i=0;i<daMesh->nb2vert;i++)
	{
		Ske->ComputeDistFromPoint(daMesh->pv[i]);

		double minDist=99999;
		CKBone *dabone=NULL;
		for (j=0;j<Ske->LinBones.size();j++)
		{
			//LinBones[i]->Distance=dist_Point_to_Segment( pt, LinBones[i]->Parent->Pos,LinBones[i]->Pos,LinBones[i]->DistType,d);
			if ((Ske->LinBones[j]->Distance<minDist)) //&&(Ske->LinBones[j]->DistType==2))
			{
				minDist=Ske->LinBones[j]->Distance;
				dabone=Ske->LinBones[j];
			}
		}

		if (dabone!=NULL)
			dabone->AddVert(&daMesh->pv[i],i,1);

	}
	Ske->BuildBase();
	/*

	int i,j,k;

	m_Plugin->m_Scene->FirstSkel->daObj=m_Plugin->m_Scene->FirstObject;

	
	Object *Obj=m_Plugin->m_Scene->FirstObject;
	Skeletton *Ske=m_Plugin->m_Scene->FirstSkel;

	for (i=0;i<Obj->nb2vert;i++)
	{
		Ske->ComputeDistFromPoint(Obj->pv[i]);
		double Maxdblval=99999999;

		double minDist[4]={Maxdblval,Maxdblval,Maxdblval,Maxdblval};
		Bone *dabone[4]={NULL,NULL,NULL,NULL};

		int nbbones=1;

		for (k=0;k<nbbones;k++)
		{
			for (j=0;j<Ske->LinBones.size();j++)
			{
				if (Ske->LinBones[j]->Distance<minDist[k])
				{
					minDist[k]=Ske->LinBones[j]->Distance;
					dabone[k]=Ske->LinBones[j];
				}
			
			}
			if (dabone[k]!=NULL)
			dabone[k]->Distance=Maxdblval;
		}

		double SumBones=0;
		for (k=0;k<nbbones;k++)
		{
			if (dabone[k]!=NULL)
				SumBones+=minDist[k];

		}

		for (j=0;j<nbbones;j++)
		{
			if (dabone[j]!=NULL)
			{

				double wght=minDist[j]/SumBones;
				dabone[j]->AddVert(&Obj->pv[i],i,wght);

			}
		}


	}

	Ske->BuildBase();
	*/
}
