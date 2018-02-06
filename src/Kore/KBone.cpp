//---------------------------------------------------------------------------
#include "stdafx.h"

//#include "memmgr/mmgr.h"


CKBone::CKBone(CKBone *daPrev,CKBone *daNext)
{
    Prev=daPrev;
    Next=daNext;

    FirstBone=NULL;
    NextBone=NULL;
/*
    for (i=0;i<IK_MAXCNX;i++)
    {
        ConnectedTo[i]=-1;
    }
    nbConnectedTo=0;

    nb2VertAttach=0;
    nb2VertAttachStart=0;
    nb2VertAttachAv=0;
*/
//    ngz=0;
	FirstBA=NULL;
	NextBA=NULL;
	curMatrix=new CKMatrix;
	matrix=new CKMatrix;
	AbsPos=new Vertex;

    Selected=false;

    Rot.x=0;
    Rot.y=0;
    Rot.z=0;
	Name="";

//	KF=NULL;
	//Name=new char [32];

}


CKBone::~CKBone()
{
//	delete [] Name;
	delete AbsPos;
	delete curMatrix;
	delete matrix;

	CKBoneAttach *daBA,*daBA2;
	CKBone *daCKBone,*daCKBone2;

	daBA=FirstBA;
	while (daBA!=NULL)
	{
		daBA2=daBA->Next;
		delete daBA;

		daBA=daBA2;
	}

	daCKBone=FirstBone;
	while(daCKBone!=NULL)
	{
		daCKBone2=daCKBone->Next;
		delete daCKBone;

		daCKBone=daCKBone2;
	}

}
/*
void  CKBone::AddAttachedVert(void)
{
	
    bool value;
    int i;
    CKBoneAttach **tmpCKBoneAttach;

    if ( (nb2VertAttachStart+1)>nb2VertAttachAv )
    {
        if (nb2VertAttachAv==0)
        {
            Attached=(CKBoneAttach **)malloc(sizeof(CKBoneAttach)*MEM_CKBone_ENT);
            for (i=0;i<MEM_CKBone_ENT;i++)
            {
                Attached[i]=new (CKBoneAttach);
            }

        }
        else
        {
            Attached=(CKBoneAttach**)realloc(Attached,sizeof(CKBoneAttach)*(nb2VertAttachAv+MEM_CKBone_ENT));
            for (i=nb2VertAttachAv;i<(MEM_CKBone_ENT+nb2VertAttachAv);i++)
            {
                Attached[i]=(CKBoneAttach*)malloc(sizeof(CKBoneAttach));
            }
        }

        nb2VertAttachAv+=MEM_CKBone_ENT;
    }
    nb2VertAttachStart++;
	
}


void  CKBone::DeleteAttachedVert(void)
{
    nb2VertAttachStart=0;
}


void CKBone::AddVert(Vertex * Origin, int VertIndex,double Weight)
{
    AddAttachedVert();
    Attached[nb2VertAttachStart-1]->Origin=Origin;
    Attached[nb2VertAttachStart-1]->OriginVal=(*Origin);

	Attached[nb2VertAttachStart-1]
    Attached[nb2VertAttachStart-1]->OriginIndex=VertIndex;

}
*/

void  CKBone::ComputeBoneX(Vertex DaCent, double dang)
{
    Vertex danew,danew2;
    Vertex *pv;
    Vertex yop,pt2,Joint,ngd;
	CKBoneAttach *daBA;

	

    Joint=DaCent;
    ngd.x=dang;

    daBA=FirstBA;
	while(daBA!=NULL)
    {
        pv=daBA->Origin;

        pt2=(*pv);//Attached[i]->OriginVal;//

        yop.x=RotX((pt2.x-Joint.x),(pt2.y-Joint.y),ngd.x);
        yop.y=RotY((pt2.x-Joint.x),(pt2.y-Joint.y),ngd.x);
        yop.z=(pt2.z-Joint.z);

        (*pv)=(Joint+yop);
		daBA=daBA->Next;
    }
}

void  CKBone::ComputeBoneY(Vertex DaCent, double dang)
{
    Vertex danew,danew2;
    Vertex *pv;
	CKBoneAttach *daBA;

    Vertex yop,pt2,Joint,ngd;

    Joint=DaCent;
    ngd.x=dang;

    daBA=FirstBA;
	while(daBA!=NULL)
    {
        pv=daBA->Origin;

        pt2=(*pv);//Attached[i]->OriginVal;//

        yop.y=RotX((pt2.y-Joint.y),(pt2.z-Joint.z),ngd.x);
        yop.z=RotY((pt2.y-Joint.y),(pt2.z-Joint.z),ngd.x);
        yop.x=(pt2.x-Joint.x);

        (*pv)=(Joint+yop);
		daBA=daBA->Next;
    }
}

void  CKBone::ComputeBoneZ(Vertex DaCent, double dang)
{
    Vertex danew,danew2;
    Vertex *pv;

    Vertex yop,pt2,Joint,ngd;
	CKBoneAttach *daBA;

    Joint=DaCent;
    ngd.x=dang;

    daBA=FirstBA;
	while(daBA!=NULL)
    {
        pv=daBA->Origin;
        //pv=Attached[i]->Origin;

        pt2=(*pv);//Attached[i]->OriginVal;//

        yop.x=RotX((pt2.x-Joint.x),(pt2.z-Joint.z),ngd.x);
        yop.z=RotY((pt2.x-Joint.x),(pt2.z-Joint.z),ngd.x);
        yop.y=(pt2.y-Joint.y);

        (*pv)=(Joint+yop);
		daBA=daBA->Next;
    }
}

void CKBone::AddVert(Vertex *Origin,int Index,double Weight)
{
    if (FirstBA==NULL)
    {
        FirstBA=new (CKBoneAttach)(NULL,NULL);
        NextBA=FirstBA;
    }
    else
    {
        NextBA->Next=new (CKBoneAttach)(NextBA,NULL);
		NextBA=NextBA->Next;
    }

	NextBA->OriginIndex=Index;
    NextBA->Origin=Origin;
    NextBA->OriginVal=(*Origin);
	NextBA->Weight=Weight;
}

void CKBone::DelAttached(void)
{
    CKBoneAttach *daBufVert,*daBufVert2;

    daBufVert=FirstBA;
    while(daBufVert!=NULL)
    {
        daBufVert2=daBufVert->Next;
        delete daBufVert;
        daBufVert=NULL;
        daBufVert=daBufVert2;
    }
    FirstBA=NULL;
    NextBA=NULL;
}


void CKBone::IsCopyOf(CKBone *cmpt)
{

}