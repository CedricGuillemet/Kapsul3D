//---------------------------------------------------------------------------
#include "stdafx.h"

//#include "memmgr/mmgr.h"

typedef int TriangleList[10000];
unsigned int SH_Unique=0;

CKShape::CKShape(CKShape *daPrev,CKShape *daNext)
{
    Prev=daPrev;
    Next=daNext;

    FirstSegment=NULL;
    NextSegment=NULL;

    Count=0;
	m_Mesh=NULL;
    Selected=false;

	Unique=SH_Unique++;
	Hided=false;
	DrawSpline=false;

}

CKShape::~CKShape()
{
    CKSegment *tmpSegment,*tmpSegmentNext;


    tmpSegment=FirstSegment;
    while(tmpSegment!=NULL)
    {
        tmpSegmentNext=tmpSegment->Next;
        
        if (tmpSegmentNext==FirstSegment) break;

        delete tmpSegment;
        tmpSegment=tmpSegmentNext;
    }
}

void CKShape::DoAdd()
{
    Count++;
    if (FirstSegment==NULL)
    {
        FirstSegment=new (CKSegment)(NULL,NULL);
        NextSegment=FirstSegment;
    }
    else
    {
        NextSegment->Next=new (CKSegment)(NextSegment,(CKSegment*)NULL);
        NextSegment=NextSegment->Next;
    }
}
void CKShape::AddSegment(Vertex *daDot)
{
    DoAdd();
    NextSegment->Dot=(*daDot);
}

void CKShape::AddSegment(Vertex daDot)
{
    DoAdd();
    NextSegment->Dot=daDot;
}

void CKShape::AddSegment(double X,double Y,double Z)
{
    DoAdd();
    NextSegment->Dot.x=X;
    NextSegment->Dot.y=Y;
    NextSegment->Dot.z=Z;
}

CKSegment * CKShape::InsertAtFirst(Vertex daDot)
{
    
	CKSegment *tmp;

	Count++;
	tmp=new CKSegment(NULL,FirstSegment);
	FirstSegment->Prev=tmp;
	FirstSegment=tmp;
    tmp->Dot=daDot;

	return tmp;
}

CKSegment * CKShape::InsertAtFirst(double X,double Y,double Z)
{
	CKSegment *tmp;

	Count++;
	tmp=new CKSegment(NULL,FirstSegment);
	FirstSegment->Prev=tmp;
	FirstSegment=tmp;

    tmp->Dot.x=X;
    tmp->Dot.y=Y;
    tmp->Dot.z=Z;
	return tmp;

}


CKSegment * CKShape::InsertSegment(CKSegment *Seg,Vertex daDot)
{
	CKSegment *tmp;

	Count++;
	tmp=new CKSegment(Seg,Seg->Next);
	Seg->Next=tmp;
	if (Seg->Next!=NULL)
	{
		tmp->Next->Prev=tmp;
	}
    tmp->Dot=daDot;

	return tmp;
}

CKSegment * CKShape::InsertSegment(CKSegment *Seg,double X,double Y,double Z)
{
	CKSegment *tmp;

	Count++;
	tmp=new CKSegment(Seg,Seg->Next);
	Seg->Next=tmp;
	if (Seg->Next!=NULL)
	{
		Seg->Next->Prev=tmp;
	}
    tmp->Dot.x=X;
    tmp->Dot.y=Y;
    tmp->Dot.z=Z;

	return tmp;
}


void CKShape::SetSegment(Vertex *daDot)
{
    NextSegment->Dot=(*daDot);
}

void CKShape::SetSegment(double X,double Y,double Z)
{
    NextSegment->Dot.x=X;
    NextSegment->Dot.y=Y;
    NextSegment->Dot.z=Z;
}

void CKShape::SetStyle(int daStyle)
{
//    Style=daStyle;
}

void  CKShape::IsQuad(Vertex Corner1, Vertex Corner2,Vertex Corner3,Vertex Corner4)
{

    DoAdd();
    NextSegment->Dot=Corner1;
    DoAdd();
    NextSegment->Dot=Corner2;
    DoAdd();
    NextSegment->Dot=Corner3;
    DoAdd();
    NextSegment->Dot=Corner4;
    DoAdd();
    NextSegment->Dot=Corner1;

}


void  CKShape::IsCircle(int nbDots,Vertex *Dots)
{
    int i;


    for (i=0;i<nbDots;i++)
    {
        DoAdd();
        NextSegment->Dot=Dots[i];
    }
    DoAdd();
    NextSegment->Dot=Dots[0];

}


bool  CKShape::IsInside(Vertex Dot)
{
    //A FAIRE : Ajouter votre code source ici
	return true;
}

void  CKShape::DelAll(void)
{
    CKSegment *daSeg,*daSeg2,*EndIt;

    daSeg=NextSegment;
	EndIt=FirstSegment;
    while(daSeg!=NULL)
    {
        daSeg2=daSeg->Prev;
        daSeg->Prev=NULL;
        daSeg->Next=NULL;
        delete daSeg;
        daSeg=daSeg2;
		if (daSeg==EndIt) break;

    }
    FirstSegment=NULL;
    NextSegment=NULL;
}

void  CKShape::DelSeg(CKSegment *Seg)
{
    if (Seg==NextSegment) NextSegment=Seg->Prev;
	if (Seg==FirstSegment) FirstSegment=Seg->Next;

    delete Seg;
}

void  CKShape::Close(void)
{
    NextSegment->Next=FirstSegment;
}

bool CKShape::IsClosed(void)
{
	if (NextSegment->Dot==FirstSegment->Dot)
	{
		NextSegment->Prev->Next=FirstSegment;
		NextSegment=NextSegment->Prev;
	}

    return (NextSegment->Next==FirstSegment);
}

Vertex  CKShape::GetMinOf(void)
{
    CKSegment *daSeg;
    Vertex val;

    daSeg=FirstSegment;
    val=daSeg->Dot;

    while(daSeg!=NULL)
    {
        val.GetMinOf(daSeg->Dot);
        daSeg=daSeg->Next;
		if (daSeg==FirstSegment)
			break;
    }

    return val;
}

Vertex CKShape::GetMaxOf(void)
{
    CKSegment *daSeg;
    Vertex val;

    daSeg=FirstSegment;
    val=daSeg->Dot;

    while(daSeg!=NULL)
    {
        val.GetMaxOf(daSeg->Dot);
        daSeg=daSeg->Next;
		if (daSeg==FirstSegment)
			break;
    }

    return val;
}


bool CKShape::GenerateMesh(CKShape *daShp)
{
    /*
    Vertex vt1,vt2;
    Vertex tmp1,tmp2,tmp3,tmp4,tmp5,tmp6,tmp7,tmp8,tmp9;
    Vertex tmp10,tmp11,tmp12,tmp13,tmp14,tmpprev;
    Vertex rotv;
    int VertAv=0;
    int FaceAv=0;
    Vertex Ordinate;
	int i,j;

	Segment *daSeg,*daSeg2;
	double modelview[16],InverseModel[16];
	Vertex Src,Dst;


	
    if (Obj!=NULL)
        delete Obj;

    Obj=new (Object)(NULL,NULL);
    Obj->Allocate((daShp->Count*((Count-1)*2)),(daShp->Count*(Count)));//(daShp->Count*(Count*2)),(daShp->Count*(Count+1)) );


	glPushMatrix();
	glMatrixMode( GL_MODELVIEW );



	daSeg=FirstSegment;
	while(daSeg!=NULL)
	{


		
		//glViewport(0,0,640,480);
		glLoadIdentity();
		if (daSeg->Next==NULL)
			Dst=daSeg->Dot;
		else
			Dst=daSeg->Next->Dot;

		if (daSeg->Prev==NULL)
			Src=daSeg->Dot;
		else
			Src=daSeg->Prev->Dot;
			


		gluLookAt(Src.x,Src.y,Src.z,Dst.x,Dst.y,Dst.z, 0.0,1.0,0.0);

		glGetDoublev(GL_MODELVIEW_MATRIX,modelview);

		InvertMatrix(modelview,InverseModel);

		daSeg2=daShp->FirstSegment;
		while(daSeg2!=NULL)
		{

			Obj->pv[VertAv]->x=daSeg2->Dot.x*InverseModel[0]+daSeg2->Dot.y*InverseModel[4]+daSeg2->Dot.z*InverseModel[8];
			Obj->pv[VertAv]->y=daSeg2->Dot.x*InverseModel[1]+daSeg2->Dot.y*InverseModel[5]+daSeg2->Dot.z*InverseModel[9];
			Obj->pv[VertAv]->z=daSeg2->Dot.x*InverseModel[2]+daSeg2->Dot.y*InverseModel[6]+daSeg2->Dot.z*InverseModel[10];
			(*Obj->pv[VertAv])+=daSeg->Dot;

			VertAv++;

			daSeg2=daSeg2->Next;
			if (daSeg2==daShp->FirstSegment) break;

		}
		daSeg=daSeg->Next;
		if (daSeg==FirstSegment) break;

	}

	glPopMatrix();

    FaceAv=0;

    for (i=0;i<(Count-1);i++)
    {
        for (j=0;j<(daShp->Count);j++)
        {
            Obj->pf[FaceAv]->nbvert[0]=j+i*(daShp->Count);
            Obj->pf[FaceAv]->nbvert[1]=j+(daShp->Count)+i*(daShp->Count);
            Obj->pf[FaceAv]->nbvert[2]=((j+1)%(daShp->Count))+(daShp->Count)+i*(daShp->Count);

            FaceAv++;

            Obj->pf[FaceAv]->nbvert[0]=j+i*(daShp->Count);
            Obj->pf[FaceAv]->nbvert[1]=((1+j)%(daShp->Count))+(daShp->Count)+i*(daShp->Count);
            Obj->pf[FaceAv]->nbvert[2]=((j+1)%(daShp->Count))+i*(daShp->Count);

            FaceAv++;
        }
        //nb2scalesegv++;

    }
*/
	return true;
}



bool CKShape::IsVertInShape(Vertex daVert,CKRenderer *Renderer)
{
    int i,j,k,nbSect;
    bool HasGood;
    double daSec;
    CKSegment *daSeg;
    MYPOINT sdeb,sfin,spt;
	double Sec[100];
    Vertex temp;



    nbSect=0;

    //spt=Get2D(daVert);

    if (Renderer!=NULL) Renderer->Project((Vertex*)&daVert,(Vertex*)&temp,Renderer->m_Scene->Active);
        else temp=daVert;
        
    spt.x=temp.x;
    spt.y=temp.y;


    daSeg=FirstSegment;

    // -- Height array ---------------------------------------------------------

    while (daSeg!=NULL)
    {
        //sdeb=Get2D(daSeg->Dot);
        if (Renderer!=NULL)
        {

		    Renderer->Project((Vertex*)&daSeg->Dot,(Vertex*)&temp,Renderer->m_Scene->Active);
		    sdeb.x=temp.x;
		    sdeb.y=temp.y;

            //sfin=Get2D(daSeg->Next->Dot);

		    Renderer->Project((Vertex*)&daSeg->Next->Dot,(Vertex*)&temp,Renderer->m_Scene->Active);
		    sfin.x=temp.x;
		    sfin.y=temp.y;
        }
        else
        {
            sdeb.x=daSeg->Dot.x;
            sdeb.y=daSeg->Dot.y;
            sfin.x=daSeg->Next->Dot.x;
            sfin.y=daSeg->Next->Dot.y;
        }


        if (COMPRISIN(sdeb.x,sfin.x,spt.x))
        {
            INTERPOLATE(daSec,sdeb,sfin,spt.x);


            HasGood=true;

            for (j=0;j<nbSect;j++)
                if (Sec[j]==daSec)
                    HasGood=false;

            if (HasGood)
                Sec[nbSect++]=daSec;
        }

        if (daSeg->Next==FirstSegment) break;
        daSeg=daSeg->Next;
    }
    qsort((void *)Sec, nbSect, sizeof(double), IsInSort);

    HasGood=false;

    for (i=0;i<(nbSect-1);i++)
    {

        k=(i&1);

        if ((COMPRISIN(Sec[i],Sec[i+1],spt.y))&&(!k))
            HasGood=true;
    }

    return HasGood;
}

Vertex CKShape::GetSpline(double percent)
{
    Vertex bspline;
    int danbSeg;
    int gnbSeg;
    double t;
    CKSegment *daSeg,*CurSeg;
    CKSegment *nSeg,*npSeg,*nmSeg,*nppSeg;

    percent=(percent!=100)?fmod(percent,100):99.99f;

    daSeg=FirstSegment;
    danbSeg=0;

    while(daSeg!=NULL)
    {
        danbSeg++;

        daSeg=daSeg->Next;

        if (daSeg==FirstSegment)
        {
            break;
        }

    }
    t=(percent*(double)danbSeg)/100;
    gnbSeg=floor(t);
    t-=int(t);

    daSeg=FirstSegment;
    danbSeg=0;

    while(daSeg!=NULL)
    {
        if (gnbSeg==danbSeg)
        {
            CurSeg=daSeg;
            break;
        }

        danbSeg++;

        daSeg=daSeg->Next;

        if (daSeg==FirstSegment)
        {
            break;
        }

    }

	CKSegment tmpNext(NULL,NULL);
	CKSegment tmpNext2(NULL,NULL);

    nSeg=CurSeg;
    if (nSeg->Next==NULL) 
    {
		//tmpNext.Dot=nSeg->Dot+(nSeg->Dot-nSeg->Next->Dot);
		//tmpNext2.Dot=nSeg->Dot+((nSeg->Dot-nSeg->Prev->Dot)*2);
        npSeg=nSeg;//&tmpNext;
        nppSeg=nSeg;//&tmpNext2;
		/*
		if (nSeg->Prev!=NULL)
		{
			npSeg=nSeg->Prev;
			nppSeg=nSeg->Prev;
			*/
    }
    else 
    {
        npSeg=nSeg->Next;
        if (nSeg->Next->Next==NULL)
		{
			tmpNext2.Dot=nSeg->Dot+((nSeg->Dot-nSeg->Next->Dot)*2);
			nppSeg=nSeg->Next;//&tmpNext2;
		}
        else
		{
			nppSeg=nSeg->Next->Next;
		}
    }

	CKSegment tmpPrev(NULL,NULL);
    if (nSeg->Prev==NULL)
	{
		if (NextSegment->Next==FirstSegment)
			nmSeg=NextSegment;
		else
		{
			//nmSeg=nSeg;
			tmpPrev.Dot=nSeg->Dot+(nSeg->Dot-nSeg->Next->Dot);
			nmSeg=&tmpPrev;
		}
	}
    else
	{
		nmSeg=nSeg->Prev;
	}

/*
- point is the key point table 
- STEPS is the number of steps 
- k is the current arc index 
- bl_i = bspline index (zero at first) 
*/

    double t2=t*t; 
    double t3=t*t*t;
    double k1=1-3*t+3*t2-t3; 
    double k2=4-6*t2+3*t3; 
    double k3=1+3*t+3*t2-3*t3; 
    bspline.x = 1/6.0*(k1*nmSeg->Dot.x+ k2*nSeg->Dot.x+ k3*npSeg->Dot.x+ t3*nppSeg->Dot.x); 
    bspline.y = 1/6.0*(k1*nmSeg->Dot.y+ k2*nSeg->Dot.y+ k3*npSeg->Dot.y+ t3*nppSeg->Dot.y); 
    bspline.z = 1/6.0*(k1*nmSeg->Dot.z+ k2*nSeg->Dot.z+ k3*npSeg->Dot.z+ t3*nppSeg->Dot.z); 

    return bspline;
}

int CKShape::GetCount(void)
{
    CKSegment *daSeg;
    int value=0;

    daSeg=FirstSegment;
    while(daSeg!=NULL)
    {
        value++;
        daSeg=daSeg->Next;
		if (daSeg==FirstSegment) 
        {
            value++;
            break;
        }

    }


    value--;
    return value;
}

double CKShape::GetLength(void)
{
    CKSegment *daSeg;
    double value=0;

    daSeg=FirstSegment;
    while(daSeg!=NULL)
    {
        value+=Pythagore3D(daSeg->Dot,daSeg->Next->Dot);
        daSeg=daSeg->Next;
		if ((daSeg==FirstSegment)||(daSeg->Next==NULL))
        {
            break;
        }
    }
    return value;
}

double CKShape::GetLength(int nb)
{
    CKSegment *daSeg;
    double value=0;
    int danb=0;

    daSeg=FirstSegment;
    while((daSeg!=NULL)&&(danb<nb))
    {
        value+=Pythagore3D(daSeg->Dot,daSeg->Next->Dot);
        daSeg=daSeg->Next;
        danb++;
		if ((daSeg==FirstSegment)||(daSeg->Next==NULL))
        {
            break;
        }
    }
    return value;
}

void CKShape::IsCopyOf(CKShape *cmpt)
{
    CKSegment *daSeg;

    daSeg=cmpt->FirstSegment;
    while(daSeg!=NULL)
    {
		DoAdd();
		NextSegment->IsCopyOf(daSeg);

        daSeg=daSeg->Next;
		if (daSeg==cmpt->FirstSegment) 
        {
            break;
        }
    }

	// test close the shape
	if (cmpt->NextSegment->Next==cmpt->FirstSegment)
		NextSegment->Next=FirstSegment;

	// data themselves
    Selected=false;
	Name=cmpt->Name;
	Count=cmpt->Count;
	//dunno what to do with
    m_Mesh=NULL;
	Unique=cmpt->Unique;
}

void CKShape::UpdateBB(void)
{
	BBMin=GetMinOf();
	BBMax=GetMaxOf();
}

Vertex CKShape::GetCenter(void)
{
	Vertex Sum;
	float Count=0;

	CKSegment *daSeg;

    daSeg=FirstSegment;
    while(daSeg!=NULL)
    {
		Sum+=daSeg->Dot;
		Count+=1;

        daSeg=daSeg->Next;
		if ((daSeg==FirstSegment)||(daSeg->Next==NULL))
        {
            break;
        }
    }

	Sum/=Count;
	return Sum;
}

Vertex CKShape::GetNormal(void)
{
	Vertex Sum,tmps;
	Vertex p,q;

	CKSegment *daSeg;

    daSeg=FirstSegment;
    while(daSeg!=NULL)
    {
		p=(daSeg->Next->Dot-daSeg->Dot);
		q=(daSeg->Next->Next->Dot-daSeg->Next->Dot);
		
		tmps.x = p.y * q.z - p.z * q.y;
		tmps.y = p.z * q.x - p.x * q.z;
		tmps.z = p.x * q.y - p.y * q.x;

		Sum+=tmps;
        daSeg=daSeg->Next;
		if ((daSeg==FirstSegment)||(daSeg->Next->Next==NULL))
        {
            break;
        }
    }

	Sum.Normalize();
	return Sum;

}