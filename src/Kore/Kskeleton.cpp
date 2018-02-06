#include "stdafx.h"

//#include "memmgr/mmgr.h"
unsigned int SK_Unique=0;

CKSkeleton::CKSkeleton(CKSkeleton *daPrev,CKSkeleton *daNext)
{
    Vertex vv,vv2,vv3;

    Prev=daPrev;
    Next=daNext;

    nbbone=0;
    nbboneAv=0;
    nbboneStart=0;

    Selected=false;

    FirstBone=NULL;
    NextBone=NULL;
	bone=NULL;
/*
	Name = new char [20];
	Name[0] = 0;
	ObjName = new char [20];
	ObjName [0] = 0;
*/
	Unique=SK_Unique++;

    pbs=NULL;
    BoneCount=0;
    pbs=(CKBone**)malloc(sizeof(CKBone*)*(512));
	Hided=false;
}

void CKSkeleton::DelBone(CKBone *daBone)
{
    CKBone *daBone2,*daBone3;

//    free(pbs);

	// delete children

    daBone2=FirstBone;
    while(daBone2!=NULL)
    {
        daBone3=daBone2->Next;
        DelBone(daBone2);
        daBone2=daBone3;
    }

	if (daBone==daBone->Parent->FirstBone)
		daBone->Parent->FirstBone=daBone->Next;

	if (daBone==daBone->Parent->NextBone)
		daBone->Parent->NextBone=daBone->Prev;

	if (daBone->Next!=NULL)
		daBone->Next->Prev=daBone->Prev;

	if (daBone->Prev!=NULL)
		daBone->Prev->Next=daBone->Next;

    delete daBone;

}

void CKSkeleton::DelSelectedBones(CKBone *daBone)
{
    CKBone *daBone2,*daBone3;

    daBone2=FirstBone;
    while(daBone2!=NULL)
    {
        daBone3=daBone2->Next;
        DelSelectedBones(daBone2);
        daBone2=daBone3;
    }
    if (daBone->Selected) DelBone(daBone);
}

CKSkeleton::~CKSkeleton()
{
    DelBone(bone);
}

CKBone * CKSkeleton::AddBone(CKBone *Parent)
{
    CKBone *daBone;

    if (Parent==NULL)
    {
        bone=new (CKBone)(NULL,NULL);
		bone->Parent=Parent;
        daBone=bone;
    }
    else
    {
        if (Parent->FirstBone==NULL)
        {
            Parent->FirstBone=new (CKBone)(NULL,NULL);
            Parent->NextBone=Parent->FirstBone;
        }
        else
        {
            Parent->NextBone->Next=new (CKBone)(Parent->NextBone,NULL);
            Parent->NextBone=Parent->NextBone->Next;
        }
		Parent->NextBone->Parent=Parent;
        daBone=Parent->NextBone;
    }
    GenerateBoneName(daBone);

	LinBones.push_back(daBone);

    

    pbs[BoneCount]=daBone;

    BoneCount++;

    return daBone;
}

void CKSkeleton::RotateX(CKBone * BoneIndex,Vertex dacent,double dang)
{
    Vertex yop,pt2,Joint,ngd;
	CKBone *daBone2;

    pt2=BoneIndex->Pos;
    Joint=dacent;
    ngd.x=dang;

    yop.x=RotX((pt2.x-Joint.x),(pt2.y-Joint.y),ngd.x);
    yop.y=RotY((pt2.x-Joint.x),(pt2.y-Joint.y),ngd.x);
    yop.z=(pt2.z-Joint.z);

    BoneIndex->Pos=(Joint+yop);
    BoneIndex->ComputeBoneX(Joint,ngd.x);

    daBone2=BoneIndex->FirstBone;
    while(daBone2!=NULL)
    {
		RotateX(daBone2,dacent,ngd.x);
        daBone2=daBone2->Next;
    }


}

void CKSkeleton::RotateY(CKBone * BoneIndex,Vertex dacent,double dang)
{
    Vertex yop,pt2,Joint,ngd;
	CKBone *daBone2;

    pt2=BoneIndex->Pos;
    Joint=dacent;
    ngd.x=dang;

    yop.y=RotX((pt2.y-Joint.y),(pt2.z-Joint.z),ngd.x);
    yop.z=RotY((pt2.y-Joint.y),(pt2.z-Joint.z),ngd.x);
    yop.x=(pt2.x-Joint.x);

    BoneIndex->Pos=(Joint+yop);
    BoneIndex->ComputeBoneY(Joint,ngd.x);

    daBone2=BoneIndex->FirstBone;
    while(daBone2!=NULL)
    {
		RotateY(daBone2,dacent,ngd.x);
        daBone2=daBone2->Next;
    }


}

void CKSkeleton::RotateZ(CKBone * BoneIndex,Vertex dacent,double dang)
{
    Vertex yop,pt2,Joint,ngd;
	CKBone *daBone2;

    pt2=BoneIndex->Pos;
    Joint=dacent;
    ngd.x=dang;

    yop.x=RotX((pt2.x-Joint.x),(pt2.z-Joint.z),ngd.x);
    yop.z=RotY((pt2.x-Joint.x),(pt2.z-Joint.z),ngd.x);
    yop.y=(pt2.y-Joint.y);

    BoneIndex->Pos=(Joint+yop);
    BoneIndex->ComputeBoneZ(Joint,ngd.x);

    daBone2=BoneIndex->FirstBone;
    while(daBone2!=NULL)
    {
		RotateZ(daBone2,dacent,ngd.x);
        daBone2=daBone2->Next;
    }

}

////////////////////////////////////////////////////////////////////////////////

Vertex CKSkeleton::IKMoveBone(CKBone *BoneIndex, Vertex Position)
{
    Vertex pos2;
    CKBone * ParentBone;
    Vertex BoneTemp1,BoneTemp2;
    Vertex CrossProd;

    Vertex pt1,Joint,pt2;
    Vertex damove;
    Vertex temp;

    Vertex yop,yop2,yop3;
    Vertex ngd;

    damove=Position;

    // debut

    ParentBone=BoneIndex->Parent;

	if (ParentBone!=NULL)
	{
		pt2=BoneIndex->Pos;

		Joint=ParentBone->Pos;

		pt1=ParentBone->Pos;
		if (fabs(Position.z)<0.0001) Position.z=0;
		if (fabs(Position.y)<0.0001) Position.y=0;
		if (fabs(Position.x)<0.0001) Position.x=0;

		if ((Position.z==0)&&(Position.y!=0)&&(Position.x!=0))
		{
			ngd.x=-ng(Joint.x,Joint.y,(Position.x),(Position.y));
			ngd.x-=-ng(Joint.x,Joint.y,(pt2.x),(pt2.y));

			ngd.y=0;
			ngd.z=0;

			RotateX(BoneIndex,Joint,ngd.x);
		}

		if ((Position.x==0)&&(Position.y!=0)&&(Position.z!=0))
		{
			ngd.y=-ng(Joint.y,Joint.z,(Position.y),(Position.z));
			ngd.y-=-ng(Joint.y,Joint.z,(pt2.y),(pt2.z));

			ngd.x=0;
			ngd.z=0;


			RotateY(BoneIndex,Joint,ngd.y);
		}

		if ((Position.x!=0)&&(Position.y==0)&&(Position.z!=0))
		{
			ngd.z=-ng(Joint.x,Joint.z,(Position.x),(Position.z));
			ngd.z-=-ng(Joint.x,Joint.z,(pt2.x),(pt2.z));

			ngd.y=0;
			ngd.x=0;

			RotateZ(BoneIndex,Joint,ngd.z);
		}
	}
    return ngd;
}

bool CKSkeleton::RecurseAlreadyAttached(CKBone *daBone,Vertex *vt)
{
	CKBoneAttach *daBA;
    CKBone *daBone2;

	daBA=daBone->FirstBA;
	while(daBA!=NULL)
	{
		if (daBA->Origin==vt) return true;
		daBA=daBA->Next;
	}

    daBone2=daBone->FirstBone;
    while(daBone2!=NULL)
    {
		if (RecurseAlreadyAttached(daBone2,vt)) return true;

        daBone2=daBone2->Next;
    }
	return false;
}

bool CKSkeleton::AlreadyAttached(Vertex *vt)
{
    Vertex Clickhui,Clickhui2;
	CKBoneAttach *daBA;
    //

    CKBone *daBone;


	daBone=bone;

	daBA=daBone->FirstBA;
	while(daBA!=NULL)
	{
		if (daBA->Origin==vt) return true;
		daBA=daBA->Next;
	}


	daBone=bone->FirstBone;
	while(daBone!=NULL)
	{
		if (RecurseAlreadyAttached(daBone,vt)) return true;

		daBone=daBone->Next;
	}

 
    return false;
}

void CKSkeleton::Del(CKBone *daBa)
{
	if (daBa==FirstBone)
		FirstBone=daBa->Next;

	if (daBa==NextBone)
		NextBone=daBa->Prev;

	if (daBa->Next!=NULL)
		daBa->Next->Prev=daBa->Prev;

	if (daBa->Prev!=NULL)
		daBa->Prev->Next=daBa->Next;

	delete daBa;
}


void CKSkeleton::DeformVert(CKBone *daBone,int FrameDest)
{
	CKBone *curBone;
	CKBoneAttach *daBA;
	Vertex post;
    Vertex *toSet;

	curBone = daBone->FirstBone;

	while(curBone!=NULL)
	{
		daBA=curBone->FirstBA;
		while(daBA!=NULL)
		{
			// Multiply the vertex by the combined matrix

			curBone->curMatrix->MultVectorByMatrix( (Vertex*)&daBA->OriginVal, &post);
			post.x*=daBA->Weight;
			post.y*=daBA->Weight;
			post.z*=daBA->Weight;
            toSet=&m_Mesh->pv[daBA->OriginIndex+FrameDest*m_Mesh->nb2vert];

            *toSet+=post;


			daBA=daBA->Next;
		}

		DeformVert(curBone,FrameDest);

		curBone=curBone->Next;
	}
}

///////////////////////////////////////////////////////////////////////////////

void CKSkeleton::RecBuildMatrix(CKBone *daBone,Vertex Origin)
{
	/*
	CKBone *curBone;
	CKMatrix tempMatrix;

	curBone=daBone->FirstBone;
	while(curBone!=NULL)
	{
		glPushMatrix();

        if (daBone->Parent!=NULL)
            Origin=daBone->Parent->Pos;

        glTranslatef((float)(daBone->Pos.x - Origin.x),(float)(daBone->Pos.y - Origin.y),(float)(daBone->Pos.z - Origin.z));

        glRotatef((float)curBone->Rot.z, 0.0f, 0.0f, 1.0f);
		glRotatef((float)curBone->Rot.y, 0.0f, 1.0f, 0.0f);
		glRotatef((float)curBone->Rot.x, 1.0f, 0.0f, 0.0f); 
	
		tempMatrix.GetFrom(GL_MODELVIEW_MATRIX);

		curBone->curMatrix->MultMatrix((CKMatrix*)&tempMatrix,curBone->matrix);

		curBone->curMatrix->MultVectorByMatrix( (Vertex*)&curBone->Pos, curBone->AbsPos);

		RecBuildMatrix(curBone,(daBone->Pos-Origin));

        glPopMatrix();

		curBone=curBone->Next;
	}	
	*/
}

void CKSkeleton::BuildMatrix(int FrameDest)
{
	/*
    CKMatrix tempMatrix;

	glPushMatrix();
	glLoadIdentity();

    glTranslatef((float)RootPos.x ,(float)RootPos.y ,(float)RootPos.z );

 

	glRotatef((float)bone->Rot.z, 0.0f, 0.0f, 1.0f);
	glRotatef((float)bone->Rot.y, 0.0f, 1.0f, 0.0f);
	glRotatef((float)bone->Rot.x, 1.0f, 0.0f, 0.0f); 
	
	tempMatrix.GetFrom(GL_MODELVIEW_MATRIX);

	bone->curMatrix->MultMatrix((CKMatrix*)&tempMatrix,bone->matrix);

	bone->curMatrix->MultVectorByMatrix( (Vertex*)&bone->Pos, bone->AbsPos);

	RecBuildMatrix(bone,RootPos);


    	// 2eme passe deformation

	glLoadIdentity();
	int i;

	for (i=0;i<LinBones.size();i++)
	{
		CKBoneAttach *daBA=LinBones[i]->FirstBA;
		while(daBA!=NULL)
		{
            m_Mesh->pv[daBA->OriginIndex]=Vertex(0,0,0);
			daBA=daBA->Next;
		}
	}




	DeformVert(bone,FrameDest);

	glPopMatrix();
	*/
}


void CKSkeleton::RecBuildBase(CKBone *daBone,Vertex Origin)
{
	
	CKBone *curBone;
	CKMatrix tempMatrix;

	curBone = daBone->FirstBone;
	while(curBone!=NULL)
	{

        if (daBone->Parent!=NULL)
            Origin=daBone->Parent->Pos;

		tempMatrix.Identity();
		tempMatrix.Translate((daBone->Pos - Origin));
		tempMatrix.InvertMatrix(curBone->matrix);

		(*curBone->AbsPos)=curBone->Pos;

		RecBuildBase(curBone,(curBone->Pos - Origin));

		curBone=curBone->Next;
	}	

}

void CKSkeleton::BuildBase(void)
{
	
    CKMatrix tempMatrix;

	tempMatrix.Identity();

	tempMatrix.Translate(RootPos);
	tempMatrix.InvertMatrix(bone->matrix);

	(*bone->AbsPos)=bone->Pos;

	RecBuildBase(bone,RootPos);
}

///////////////////////////////////////////////////////////////////////////////

Vertex CKSkeleton::GetMinOfBone(CKBone *daBone)
{
	Vertex tmp;
	CKBone *daBone2;

	tmp=daBone->Pos;
	daBone2=daBone->FirstBone;

	while(daBone2!=NULL)
	{
		tmp.GetMinOf(GetMinOfBone(daBone2));
		daBone2=daBone2->Next;
	}
	
	return tmp;
}

Vertex CKSkeleton::GetMaxOfBone(CKBone *daBone)
{
	Vertex tmp;
	CKBone *daBone2;

	tmp=daBone->Pos;
	daBone2=daBone->FirstBone;

	while(daBone2!=NULL)
	{
		tmp.GetMaxOf(GetMaxOfBone(daBone2));
		daBone2=daBone2->Next;
	}
	
	return tmp;
}


Vertex CKSkeleton::GetMinOf(void)
{
	Vertex tmp;
	CKBone *daBone;

	tmp=RootPos;

	daBone=FirstBone;

	while(daBone!=NULL)
	{
		tmp.GetMinOf(GetMinOfBone(daBone));
		daBone=daBone->Next;
	}

	return tmp;
}

Vertex CKSkeleton::GetMaxOf(void)
{
	Vertex tmp;
	CKBone *daBone;

	tmp=RootPos;

	daBone=FirstBone;

	while(daBone!=NULL)
	{
		tmp.GetMaxOf(GetMaxOfBone(daBone));
		daBone=daBone->Next;
	}

	return tmp;
}

void CKSkeleton::GenerateBoneName(CKBone *daBone)
{
	CString temp;

/*
	for (int j=0;j<10000;j++)
	{
		temp.Format("Bone%d",j);
		HasGood=true;
		for (int i=0;i<BoneCount;i++)
		{
			if (pbs[i]->Name==temp) HasGood=false;
		
		}
		if (HasGood) daBone->Name=temp;
	}
	*/
	daBone->Name="BoneXXX";
}

CKBone *CKSkeleton::FindBone(CString BoneName)
{
	for (int i=0;i<BoneCount;i++)
	{
		if (pbs[i]->Name==BoneName) return pbs[i];
	}

	return NULL;
}

void CKSkeleton::IsCopyOf(CKSkeleton *cmpt)
{
	Unique=cmpt->Unique;
}

void CKSkeleton::UpdateSkel(void)
{
	BuildBase();
}

#define dot(u,v)   ((u).x * (v).x + (u).y * (v).y + (u).z * (v).z)
#define norm(v)    sqrt(dot(v,v))  // norm = length of vector
#define d(u,v)     norm(u-v)       

double dist_Point_to_Segment( Vertex &P, Vertex &S0,Vertex &S1,int &type,double &d)
{
    Vertex v = S1 - S0;
    Vertex w = P - S0;
    d=0;

    double c1 = dot(w,v);
    if ( c1 <= 0 )
    {
        type=0;
        return d(P, S0); // before
    }

    double c2 = dot(v,v);
    if ( c2 <= c1 )
    {
        type=1;
        return d(P, S1); // after
    }

    double b = c1 / c2;
    Vertex Pb = S0;
    Pb.x+= v.x*b;
    Pb.y+= v.y*b;
    Pb.z+= v.z*b;
    type=2;
    d=b;
    return d(P, Pb); //inside
}

void  CKSkeleton::ComputeDistFromPoint(Vertex &pt)
{
	int i;
	double d;

	for (i=0;i<LinBones.size();i++)
	{
		if (LinBones[i]->Parent==NULL)
			LinBones[i]->Distance=dist_Point_to_Segment( pt, RootPos,LinBones[i]->Pos,LinBones[i]->DistType,d);
		else
			LinBones[i]->Distance=dist_Point_to_Segment( pt, LinBones[i]->Parent->Pos,LinBones[i]->Pos,LinBones[i]->DistType,d);

		//if (LinBones[i]->DistType!=0) LinBones[i]->Distance=99999999;
	}
}