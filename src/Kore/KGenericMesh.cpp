// GenericCKMeshs.cpp: implementation of the CKGenericMesh class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "kore.h"
//#include "GenericCKMeshs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKGenericMesh::CKGenericMesh()
{
	Valu=1.0f;
	Valv=1.0f;
	AutoUV=false;
}

CKGenericMesh::~CKGenericMesh()
{

}


void CKGenericMesh::CreateGrid(CKMesh *Obj,Vertex Center,double &sx,double &sy,int nbgx,int nbgy)
{
	int realnb2v,realnb2p;
	int i,j,ind;
    Vertex tmp1;
	double tmpx,tmpy;

	realnb2v=((nbgx+1)*(nbgy+1));
	realnb2p=nbgx*nbgy;

    ind=0;

    Obj->AllocatePoly(realnb2p,realnb2v);
	if (GetSnap())
	{
		Vertex vlngx=VecX*sx;
		vlngx.Snap(Obj->m_Scene->SnapVal);

		Vertex vlngy=VecY*sy;
		vlngy.Snap(Obj->m_Scene->SnapVal);

		// uniform
		if (fabs(VecX.x)>=0.0001f)
			sx=(vlngx.x/VecX.x);
		else
			if (fabs(VecX.y)>=0.0001f)
				sx=(vlngx.y/VecX.y);
			else
				sx=(vlngx.z/VecX.z);

		if (fabs(VecY.x)>=0.0001f)
			sy=(vlngy.x/VecY.x);
		else
			if (fabs(VecY.y)>=0.0001f)
				sy=(vlngy.y/VecY.y);
			else
				sy=(vlngy.z/VecY.z);
	}
	//Vertex daStart=Center;

	if (sx<0)
	{
		sx=-sx;
		Center-=(VecX*sx);
	}

	if (sy>0)
	{
		sy=-sy;
		Center-=(VecY*sy);
	}

	for (j=0;j<(nbgy+1);j++)
    {
		for (i=0;i<(nbgx+1);i++)
		{
			tmpx=(sx/(float)nbgx)*(float)( i);
			tmpy=(sy/(float)nbgy)*(float)( j);

            Obj->pv[ind]=((VecX*tmpx)+(VecY*tmpy))+Center;

			Obj->puv[0][ind].u=(Valu/(double)(nbgx))*(double)(i);
			Obj->puv[0][ind].v=(Valv/(double)(nbgy))*(double)(j);

			ind++;
		}
    }

	// creation des faces
    ind=0;
	for (j=0;j<nbgy;j++)
    {
    	for (i=0;i<nbgx;i++)
	    {
			First=Obj->pl[ind].Allocate(Obj,4);
		    
    		Obj->pi[First+0]=i+(j)*(nbgx+1);
			Obj->pi[First+1]=i+(j)*(nbgx+1)+1;
			Obj->pi[First+2]=i+(j+1)*(nbgx+1)+1;
			Obj->pi[First+3]=i+(j+1)*(nbgx+1);
            ind++;
    	}
    }

	// coords
	if (AutoUV)
	{
		Obj->SetAutoTexRecalc(true);
	}

}

void CKGenericMesh::Create3DGrid(CKMesh *Obj,Vertex Center,double &sx,double &sy,double &sz,int nbgx,int nbgy,int nbgz)
{
	int realnb2v,realnb2p;
	int i,j,ind;
    Vertex tmp1;
	double tmpx,tmpy;

	realnb2v=(((nbgx+1)*(nbgy+1))+((nbgx+1)*(nbgz+1))+((nbgy+1)*(nbgz+1)))*2;
	realnb2p=((nbgx*nbgy)*2)+((nbgx*nbgz)*2)+((nbgy*nbgz)*2);

    ind=0;

    Obj->AllocatePoly(realnb2p,realnb2v);
	if (GetSnap())
	{
		Vertex vlngx=VecX*sx;
		vlngx.Snap(Obj->m_Scene->SnapVal);

		Vertex vlngy=VecY*sy;
		vlngy.Snap(Obj->m_Scene->SnapVal);

		Vertex vlngz=VecZ*sz;
		vlngz.Snap(Obj->m_Scene->SnapVal);

		// uniform
		if (fabs(VecX.x)>=0.0001f)
			sx=(vlngx.x/VecX.x);
		else
			if (fabs(VecX.y)>=0.0001f)
				sx=(vlngx.y/VecX.y);
			else
				sx=(vlngx.z/VecX.z);

		if (fabs(VecY.x)>=0.0001f)
			sy=(vlngy.x/VecY.x);
		else
			if (fabs(VecY.y)>=0.0001f)
				sy=(vlngy.y/VecY.y);
			else
				sy=(vlngy.z/VecY.z);

		if (fabs(VecZ.x)>=0.0001f)
			sz=(vlngz.x/VecZ.x);
		else
			if (fabs(VecZ.y)>=0.0001f)
				sz=(vlngz.y/VecZ.y);
			else
				sz=(vlngz.z/VecZ.z);
	}
	//Vertex daStart=Center;

	if (sx<0)
	{
		sx=-sx;
		Center-=(VecX*sx);
	}

	if (sy>0)
	{
		sy=-sy;
		Center-=(VecY*sy);
	}

	if (sz>0)
	{
		sz=-sz;
		Center-=(VecZ*sz);
	}

	// 1st Vertex Pass
	for (j=0;j<(nbgy+1);j++)
    {
		for (i=0;i<(nbgx+1);i++)
		{
			tmpx=(sx/(float)nbgx)*(float)( i);
			tmpy=(sy/(float)nbgy)*(float)( j);

            Obj->pv[ind]=((VecX*tmpx)+(VecY*tmpy))+Center+(VecZ*sz);

			Obj->puv[0][ind].u=(Valu/(double)(nbgx))*(double)(i);
			Obj->puv[0][ind].v=(Valv/(double)(nbgy))*(double)(j);
			ind++;
		}
    }
	int ind2=ind;
	for (j=0;j<(nbgy+1);j++)
    {
		for (i=0;i<(nbgx+1);i++)
		{
			tmpx=(sx/(float)nbgx)*(float)( i);
			tmpy=(sy/(float)nbgy)*(float)( j);

            Obj->pv[ind]=((VecX*tmpx)+(VecY*tmpy))+Center;

			Obj->puv[0][ind].u=(Valu/(double)(nbgx))*(double)(i);
			Obj->puv[0][ind].v=(Valv/(double)(nbgy))*(double)(j);

			ind++;
		}
    }
	

	//2nd
	int ind3=ind;
	for (j=0;j<(nbgz+1);j++)
    {
		for (i=0;i<(nbgx+1);i++)
		{
			tmpx=(sx/(float)nbgx)*(float)( i);
			tmpy=(sz/(float)nbgz)*(float)( j);

            Obj->pv[ind]=((VecX*tmpx)+(VecZ*tmpy))+Center;

			Obj->puv[0][ind].u=(Valu/(double)(nbgx))*(double)(i);
			Obj->puv[0][ind].v=(Valv/(double)(nbgz))*(double)(j);
			ind++;
		}
    }
	int ind4=ind;
	for (j=0;j<(nbgz+1);j++)
    {
		for (i=0;i<(nbgx+1);i++)
		{
			tmpx=(sx/(float)nbgx)*(float)( i);
			tmpy=(sz/(float)nbgz)*(float)( j);

            Obj->pv[ind]=((VecX*tmpx)+(VecZ*tmpy))+Center+(VecY*sy);

			Obj->puv[0][ind].u=(Valu/(double)(nbgx))*(double)(i);
			Obj->puv[0][ind].v=(Valv/(double)(nbgz))*(double)(j);
			ind++;
		}
    }

	//3rd

	int ind5=ind;
	for (j=0;j<(nbgz+1);j++)
    {
		for (i=0;i<(nbgy+1);i++)
		{
			tmpx=(sy/(float)nbgy)*(float)( i);
			tmpy=(sz/(float)nbgz)*(float)( j);

            Obj->pv[ind]=((VecY*tmpx)+(VecZ*tmpy))+Center+(VecX*sx);

			Obj->puv[0][ind].u=(Valu/(double)(nbgy))*(double)(i);
			Obj->puv[0][ind].v=(Valv/(double)(nbgz))*(double)(j);
			ind++;
		}
    }
	int ind6=ind;
	for (j=0;j<(nbgz+1);j++)
    {
		for (i=0;i<(nbgy+1);i++)
		{
			tmpx=(sy/(float)nbgy)*(float)( i);
			tmpy=(sz/(float)nbgz)*(float)( j);

            Obj->pv[ind]=((VecY*tmpx)+(VecZ*tmpy))+Center;

			Obj->puv[0][ind].u=(Valu/(double)(nbgy))*(double)(i);
			Obj->puv[0][ind].v=(Valv/(double)(nbgz))*(double)(j);
			ind++;
		}
    }

	// -- Faces -----

	// 1
    ind=0;
	for (j=0;j<nbgy;j++)
    {
    	for (i=0;i<nbgx;i++)
	    {
			First=Obj->pl[ind].Allocate(Obj,4);
		    
    		Obj->pi[First+0]=i+(j)*(nbgx+1);
			Obj->pi[First+1]=i+(j)*(nbgx+1)+1;
			Obj->pi[First+2]=i+(j+1)*(nbgx+1)+1;
			Obj->pi[First+3]=i+(j+1)*(nbgx+1);
            ind++;
    	}
    }
	for (j=0;j<nbgy;j++)
    {
    	for (i=0;i<nbgx;i++)
	    {
			First=Obj->pl[ind].Allocate(Obj,4);
		    
    		Obj->pi[First+3]=i+(j)*(nbgx+1)+ind2;
			Obj->pi[First+2]=i+(j)*(nbgx+1)+1+ind2;
			Obj->pi[First+1]=i+(j+1)*(nbgx+1)+1+ind2;
			Obj->pi[First+0]=i+(j+1)*(nbgx+1)+ind2;
            ind++;
    	}
    }
	// 2
	for (j=0;j<nbgz;j++)
    {
    	for (i=0;i<nbgx;i++)
	    {
			First=Obj->pl[ind].Allocate(Obj,4);
		    
    		Obj->pi[First+0]=i+(j)*(nbgx+1)+ind3;
			Obj->pi[First+1]=i+(j)*(nbgx+1)+1+ind3;
			Obj->pi[First+2]=i+(j+1)*(nbgx+1)+1+ind3;
			Obj->pi[First+3]=i+(j+1)*(nbgx+1)+ind3;
            ind++;
    	}
    }
	for (j=0;j<nbgz;j++)
    {
    	for (i=0;i<nbgx;i++)
	    {
			First=Obj->pl[ind].Allocate(Obj,4);
		    
    		Obj->pi[First+3]=i+(j)*(nbgx+1)+ind4;
			Obj->pi[First+2]=i+(j)*(nbgx+1)+1+ind4;
			Obj->pi[First+1]=i+(j+1)*(nbgx+1)+1+ind4;
			Obj->pi[First+0]=i+(j+1)*(nbgx+1)+ind4;
            ind++;
    	}
    }
	// 3
	for (j=0;j<nbgz;j++)
    {
    	for (i=0;i<nbgy;i++)
	    {
			First=Obj->pl[ind].Allocate(Obj,4);
		    
    		Obj->pi[First+0]=i+(j)*(nbgy+1)+ind5;
			Obj->pi[First+1]=i+(j)*(nbgy+1)+1+ind5;
			Obj->pi[First+2]=i+(j+1)*(nbgy+1)+1+ind5;
			Obj->pi[First+3]=i+(j+1)*(nbgy+1)+ind5;
            ind++;
    	}
    }
	for (j=0;j<nbgz;j++)
    {
    	for (i=0;i<nbgy;i++)
	    {
			First=Obj->pl[ind].Allocate(Obj,4);
		    
    		Obj->pi[First+3]=i+(j)*(nbgy+1)+ind6;
			Obj->pi[First+2]=i+(j)*(nbgy+1)+1+ind6;
			Obj->pi[First+1]=i+(j+1)*(nbgy+1)+1+ind6;
			Obj->pi[First+0]=i+(j+1)*(nbgy+1)+ind6;
            ind++;
    	}
    }
	// coords
	if (AutoUV)
	{
		Obj->SetAutoTexRecalc(true);
	}
	Obj->CollapseIdenticalVertex();
}

void CKGenericMesh::CreateStairs(CKMesh *Obj,Vertex Center,double sx,double sy,double sz,int nbstairs)
{
	int realnb2v,realnb2p;
	int i,j,ind;
    Vertex tmp1;

	//realnb2v=(((nbstairs*2)+1)*2)+6;
	realnb2v=((nbstairs+1)*4)+((nbstairs+2)*2)+2;
	realnb2p=((nbstairs+1)*2)+((nbstairs+1)*2)+(nbstairs+1)+1;//((nbstairs*2)+1)+3+((nbstairs+1)*2);

    ind=0;

    Obj->AllocatePoly(realnb2p,realnb2v);
	// must be filled automaticaly;

	for (i=0;i<((nbstairs+1)*4);i+=4)
	{
		Obj->pv[i]=Center+Vertex(0,(sy/(float)(nbstairs+1))*(float)((float)i/4.0f),0)
		+Vertex(0,0,((sz/((float)nbstairs+1))*(float)((float)i/4.0f) ));
		Obj->pv[i+1]=Obj->pv[i]+Vertex(sx,0,0);

		Obj->pv[i+2]=Obj->pv[i]+Vertex(0,0,(sz/((float)nbstairs+1)) );
		Obj->pv[i+3]=Obj->pv[i+2]+Vertex(sx,0,0);
	}
	Obj->pv[((nbstairs+1)*4)]=Center+Vertex(0,sy,sz);
	Obj->pv[((nbstairs+1)*4)+1]=Center+Vertex(sx,sy,sz);

	for (i=0;i<((nbstairs+2)*2);i+=2)
	{
		Obj->pv[2+((nbstairs+1)*4)+i]=Center+Vertex(0,(sy/(float)(nbstairs+1))*(float)((float)(i/2.0f)),0);
		Obj->pv[2+((nbstairs+1)*4)+i+1]=Obj->pv[2+((nbstairs+1)*4)+i]+Vertex(sx,0,0);
	}

	// marches	
	for (i=0;i<((nbstairs+1)*2);i++)
	{
		First=Obj->pl[i].Allocate(Obj,4);
		Obj->pi[First+0]=0+(i*2);
		Obj->pi[First+1]=1+(i*2);
		Obj->pi[First+2]=3+(i*2);
		Obj->pi[First+3]=2+(i*2);
	}
	
	//cotés
	int dan2=((nbstairs+1)*2);
	int dan=(2+((nbstairs+1)*4));
	for (i=0;i<((nbstairs+1)*2);i+=2)
	{
		First=Obj->pl[i+dan2].Allocate(Obj,4);
		Obj->pi[First+0]=(dan+i);
		Obj->pi[First+1]=2+(i*2);
		Obj->pi[First+2]=4+(i*2);
		Obj->pi[First+3]=(dan+i+2);

		First=Obj->pl[i+1+dan2].Allocate(Obj,4);
		Obj->pi[First+3]=(dan+i+1);
		Obj->pi[First+2]=3+(i*2);
		Obj->pi[First+1]=5+(i*2);
		Obj->pi[First+0]=(dan+i+3);

	}
	// dessous
	dan2=Obj->nb2poly-1-(nbstairs+1);
	dan=2+((nbstairs+1)*4);
	for (i=0;i<(nbstairs+1);i++)
	{
		First=Obj->pl[i+dan2].Allocate(Obj,4);
		Obj->pi[First+3]=0+(i*2)+dan;
		Obj->pi[First+2]=1+(i*2)+dan;
		Obj->pi[First+1]=3+(i*2)+dan;
		Obj->pi[First+0]=2+(i*2)+dan;
	}

	// behind

	dan2=Obj->nb2poly-1;//dan2+(nbstairs+1);
	First=Obj->pl[dan2].Allocate(Obj,4);
	Obj->pi[First+3]=2+((nbstairs+1)*4) + ((nbstairs+2)*2) -2;
	Obj->pi[First+2]=2+((nbstairs+1)*4) + ((nbstairs+2)*2) -1;
	Obj->pi[First+0]=((nbstairs+1)*4);
	Obj->pi[First+1]=((nbstairs+1)*4)+1;
/*
	ind=0;
	for (i=0;i<Obj->nb2poly;i++)
	{
		for (j=0;j<Obj->pl[i].nb2vert;j++)
		{
			Obj->pl[i].Tex[0][j]=ind++;
		}
	}
	*/
	Obj->GenerateUVPerFace(0);
	Obj->CalcTexCoord(sx/Valu,sy/Valv,Obj->pv[0],0,0);
}

void CKGenericMesh::CreateStairsSimple(CKMesh *Obj,Vertex Center,double sx,double sy,double sz,int nbstairs)
{
	int realnb2v,realnb2p;
	int i,j,ind;
    Vertex tmp1;

	//realnb2v=(((nbstairs*2)+1)*2)+6;
	realnb2v=((nbstairs+1)*4)+4;
	realnb2p=((nbstairs+1)*2)+2+((nbstairs+1)*2);//((nbstairs*2)+1)+3+((nbstairs+1)*2);

    ind=0;

    Obj->AllocatePoly(realnb2p,realnb2v);
	// must be filled automaticaly;

	for (i=0;i<((nbstairs+1)*4);i+=4)
	{
		Obj->pv[i]=Center+Vertex(0,(sy/(float)(nbstairs+1))*(float)((float)i/4.0f),0)
		+Vertex(0,0,((sz/((float)nbstairs+1))*(float)((float)i/4.0f) ));
		Obj->pv[i+1]=Obj->pv[i]+Vertex(sx,0,0);

		Obj->pv[i+2]=Obj->pv[i]+Vertex(0,0,(sz/((float)nbstairs+1)) );
		Obj->pv[i+3]=Obj->pv[i+2]+Vertex(sx,0,0);
	}
	Obj->pv[((nbstairs+1)*4)]=Center+Vertex(0,sy,sz);
	Obj->pv[((nbstairs+1)*4)+1]=Center+Vertex(sx,sy,sz);
	Obj->pv[((nbstairs+1)*4)+2]=Center+Vertex(0,sy,0);
	Obj->pv[((nbstairs+1)*4)+3]=Center+Vertex(sx,sy,0);



	// marches	
	for (i=0;i<((nbstairs+1)*2);i++)
	{
		First=Obj->pl[i].Allocate(Obj,4);
		Obj->pi[First+0]=0+(i*2);
		Obj->pi[First+1]=1+(i*2);
		Obj->pi[First+2]=3+(i*2);
		Obj->pi[First+3]=2+(i*2);
	}
	int dan2;

	dan2=((nbstairs+1)*2);

	// coté
	for (i=0;i<((nbstairs+1)*2);i+=2)
	{
		First=Obj->pl[i+dan2].Allocate(Obj,4);
		Obj->pi[First+0]=((nbstairs+1)*4)+2;
		Obj->pi[First+1]=(i*2);
		Obj->pi[First+2]=(i*2)+2;
		Obj->pi[First+3]=(i*2)+4;

		First=Obj->pl[i+1+dan2].Allocate(Obj,4);
		Obj->pi[First+1]=((nbstairs+1)*4)+2+1;
		Obj->pi[First+0]=(i*2)+1;
		Obj->pi[First+3]=(i*2)+2+1;
		Obj->pi[First+2]=(i*2)+4+1;
	}
	// behind

	dan2=Obj->nb2poly-2;//dan2+(nbstairs+1);
	First=Obj->pl[dan2].Allocate(Obj,4);
	Obj->pi[First+0]=((nbstairs+1)*4) ;
	Obj->pi[First+1]=((nbstairs+1)*4) +1;
	Obj->pi[First+3]=((nbstairs+1)*4)+2;
	Obj->pi[First+2]=((nbstairs+1)*4)+3;

	// underfeet
	dan2=Obj->nb2poly-1;//dan2+(nbstairs+1);
	First=Obj->pl[dan2].Allocate(Obj,4);
	Obj->pi[First+1]=0 ;
	Obj->pi[First+0]=1;
	Obj->pi[First+2]=((nbstairs+1)*4)+2;
	Obj->pi[First+3]=((nbstairs+1)*4)+3;


/*
	ind=0;
	for (i=0;i<Obj->nb2poly;i++)
	{
		for (j=0;j<Obj->pl[i].nb2vert;j++)
		{
			Obj->pl[i].Tex[0][j]=ind++;
		}
	}
	*/
	Obj->GenerateUVPerFace(0);
	Obj->CalcTexCoord(sx/Valu,sy/Valv,Obj->pv[0],0,0);
}

void CKGenericMesh::CreateCube(CKMesh *Obj,Vertex Start,double X,double Y,double Z)
{
    Vertex End;
	int i;

    Obj->AllocatePoly(6,24);
	
	for (i=0;i<24;i+=4)
	{
		Obj->puv[0][i].u=0;
		Obj->puv[0][i].v=0;
		Obj->puv[0][i+1].u=Valu;
		Obj->puv[0][i+1].v=0;
		Obj->puv[0][i+2].u=Valu;
		Obj->puv[0][i+2].v=Valv;
		Obj->puv[0][i+3].u=0;
		Obj->puv[0][i+3].v=Valv;

	}
/*
	Obj->pv[0]=Start;
	Obj->pv[1]=VecX*X					+Start;
	Obj->pv[2]=VecX*X+	VecY*Y			+Start;
	Obj->pv[3]=			VecY*Y			+Start;
	Obj->pv[4]=					VecZ*Z	+Start;
	Obj->pv[5]=VecX*X+			VecZ*Z	+Start;
	Obj->pv[6]=VecX*X+	VecY*Y+	VecZ*Z	+Start;
	Obj->pv[7]=VecY*Y+			VecZ*Z	+Start;
*/

	Obj->pv[0]=			VecY*Y			+Start;
	Obj->pv[1]=VecX*X+	VecY*Y			+Start;
	Obj->pv[2]=VecX*X					+Start;
	Obj->pv[3]=Start;

	Obj->pv[4]=					VecZ*Z	+Start;
	Obj->pv[5]=VecX*X+			VecZ*Z	+Start;
	Obj->pv[6]=VecX*X+	VecY*Y+	VecZ*Z	+Start;
	Obj->pv[7]=VecY*Y+			VecZ*Z	+Start;

	Obj->pv[8]=VecY*Y+			VecZ*Z	+Start;
	Obj->pv[9]=			VecY*Y			+Start;
	Obj->pv[10]=Start;
	Obj->pv[11]=					VecZ*Z	+Start;

	Obj->pv[12]=VecX*X					+Start;
	Obj->pv[13]=VecX*X+	VecY*Y			+Start;
	Obj->pv[14]=VecX*X+	VecY*Y+	VecZ*Z	+Start;
	Obj->pv[15]=VecX*X+			VecZ*Z	+Start;

	Obj->pv[16]=VecX*X+	VecY*Y+	VecZ*Z	+Start;
	Obj->pv[17]=VecX*X+	VecY*Y			+Start;
	Obj->pv[18]=			VecY*Y			+Start;
	Obj->pv[19]=VecY*Y+			VecZ*Z	+Start;

	Obj->pv[20]=Start;
	Obj->pv[21]=VecX*X					+Start;
	Obj->pv[22]=VecX*X+			VecZ*Z	+Start;
	Obj->pv[23]=					VecZ*Z	+Start;

    Obj->AllocatePoly(6,0);
    for (i=0;i<6;i++)
    {
        Obj->pl[i].Allocate(Obj,4);
    }

    // creation des faces

	// bottom
    Obj->pi[0+0]=0;
    Obj->pi[0+1]=1;
    Obj->pi[0+2]=2;
    Obj->pi[0+3]=3;
    // top
    Obj->pi[4+0]=4;
    Obj->pi[4+1]=5;
    Obj->pi[4+2]=6;
    Obj->pi[4+3]=7;
    // front
    Obj->pi[8+0]=8;
    Obj->pi[8+1]=9;
    Obj->pi[8+2]=10;
    Obj->pi[8+3]=11;
    // back
    Obj->pi[12+0]=12;
    Obj->pi[12+1]=13;
    Obj->pi[12+2]=14;
    Obj->pi[12+3]=15;
    // left  
    Obj->pi[16+0]=16;
    Obj->pi[16+1]=17;
    Obj->pi[16+2]=18;
    Obj->pi[16+3]=19;
    // right
    Obj->pi[20+0]=20;
    Obj->pi[20+1]=21;
    Obj->pi[20+2]=22;
	Obj->pi[20+3]=23;

	// UV
	if (AutoUV)
	{
		Obj->SetAutoTexRecalc(true);
	}
}

bool CKGenericMesh::CreateTorus(CKMesh *Obj,Vertex Center,double Radius1,double Radius2,int nb2sec1,int nb2sec2,double OriginNg)
{
	int realnb2v,realnb2p;
	int i,j,ind;

	realnb2v=(nb2sec1*(nb2sec2));
	realnb2p=nb2sec1*(nb2sec2);

    Obj->AllocatePoly(realnb2p,realnb2v);
	

    ind=0;

	for (j=0;j<nb2sec2;j++)
    {
		for (i=0;i<(nb2sec1);i++)
		{
            Obj->pv[ind]=(VecX*cos((((double)i*(360.0f/(double)nb2sec1))*PI/180.0f)+OriginNg)*(Radius1+cos(((double)j*(360.0f/(double)nb2sec2))*PI/180.0f)*Radius2)+
    			    VecY*sin((((double)i*(360.0f/(double)nb2sec1))*PI/180.0f)+OriginNg)*(Radius1+cos(((double)j*(360.0f/(double)nb2sec2))*PI/180.0f)*Radius2)+
                    VecZ*sin(((double)j*(360.0f/(double)nb2sec2))*PI/180.0f)*Radius2)+Center;

			Obj->puv[0][ind].u=Valu*cos(((double)i*(360.0f/(double)nb2sec1))*PI/180.0f);//+OriginNg)*(Radius1+cos(((double)j*(360.0f/(double)nb2sec2))*PI/180.0f));
			Obj->puv[0][ind].v=Valv*sin(((double)j*(360.0f/(double)nb2sec2))*PI/180.0f);

			ind++;
		}
    }

	// creation des faces
    ind=0;
	for (j=0;j<nb2sec2;j++)
    {
    	for (i=0;i<nb2sec1;i++)
	    {
			First=Obj->pl[ind].Allocate(Obj,4);
			Obj->pi[First+0]=i+((j+1)%nb2sec2)*nb2sec1;
		    Obj->pi[First+1]=i+(j)*nb2sec1;
			Obj->pi[First+2]=((i+1)%nb2sec1)+((j)%nb2sec2)*nb2sec1;
    		Obj->pi[First+3]=((i+1)%nb2sec1)+((j+1)%nb2sec2)*nb2sec1;
            ind++;
    	}
    }

	// UV

	if (AutoUV)
	{
		Obj->SetAutoTexRecalc(true);
	}

	return TRUE;
}


// une hemisphere
bool CKGenericMesh::CreateHemis(CKMesh *Obj,Vertex Center,double radius1,int nb2sec,double OriginNg)
{
	int realnb2v,realnb2p;
	int i,j,ind;
	double fac;

	realnb2v=(nb2sec*(nb2sec+1));
	realnb2p=(nb2sec*nb2sec)+2;

    ind=0;

    Obj->AllocatePoly(realnb2p,realnb2v);
	


	for (j=0;j<(nb2sec+1);j++)
    {
		for (i=0;i<(nb2sec);i++)
		{
			if (j==(nb2sec-1)) fac=0;
				else fac=(radius1*cos(((double)j*(90.0f/(double)nb2sec))*PI/180.0f));
            Obj->pv[(j*nb2sec)+i]=(VecX*cos((((double)i*(360.0f/(double)nb2sec))*PI/180.0f)+OriginNg)*fac+
    			    VecY*sin((((double)i*(360.0f/(double)nb2sec))*PI/180.0f)+OriginNg)*fac+
				VecZ*(-sin(((double)j*(90.0f/(double)nb2sec))*PI/180.0f))*radius1)+Center;
			Obj->puv[0][(j*nb2sec)+i].u=(Valu/(double)(nb2sec))*(double)(i);
			Obj->puv[0][(j*nb2sec)+i].v=(Valv/(double)(nb2sec+1.0f))*(double)(j);
		}
    }

	// creation des faces
	//cote

	for (j=0;j<nb2sec;j++)
    {
	    for (i=0;i<nb2sec;i++)
    	{
			First=Obj->pl[ind].Allocate(Obj,4);
			Obj->pi[First+3]=i+nb2sec+j*nb2sec;
	    	Obj->pi[First+2]=i+j*nb2sec;
			Obj->pi[First+1]=((i+1)%nb2sec)+j*nb2sec;
    		Obj->pi[First+0]=((i+1)%nb2sec)+nb2sec+j*nb2sec;

            ind++;
        }
	}


	//haut et bas
	/*
	First=Obj->pl[ind].Allocate(Obj,nb2sec);
	Obj->pl[ind+1].Allocate(Obj,nb2sec);
	for (i=0;i<nb2sec;i++)
	{
		Obj->pi[First+nb2sec-i-1]=i;
		Obj->pl[ind+1].nbvert[i]=i+(nb2sec*nb2sec);
	}
*/
	// UV pour le dessous
	/*
		//haut et bas
		for (i=0;i<nb2sec;i++)
		{
			Obj->piuv[pl[ind].Tex[0]+nb2sec-i-1]=i+realnb2v;

			Obj->pl[ind+1].Tex[0][i]=i+(nb2sec*nb2sec);

			double fg=((double)i/(double)((double)nb2sec/2.0f))*PI;
			Obj->puv[0][i+realnb2v].u=((cos(fg)+1.0f)/2.0f)*Valu;
			Obj->puv[0][i+realnb2v].v=((sin(fg)+1.0f)/2.0f)*Valv;
		}
		*/

	// UV

	if (AutoUV)
	{
		Obj->SetAutoTexRecalc(true);
	}

    return TRUE;
}


// un cylindre
bool CKGenericMesh::CreateCyl(CKMesh *Obj,Vertex Center,double &radius1,double &height,int nb2sec2,int nb2sec,double OriginNg)
{
	int realnb2v,realnb2p;
	int i,j,ind;

	
	realnb2v=(nb2sec*(nb2sec2+1));
	realnb2p=(nb2sec*nb2sec2)+2;//(2*(nb2sec-2));



	if (GetSnap())
	{
		Vertex vlngz=VecZ*height;
		vlngz.Snap(Obj->m_Scene->SnapVal);

		// uniform
		if (fabs(VecZ.x)>=0.0001f)
			height=(vlngz.x/VecZ.x);
		else
			if (fabs(VecZ.y)>=0.0001f)
				height=(vlngz.y/VecZ.y);
			else
				height=(vlngz.z/VecZ.z);

	}
	//Vertex daStart=Center;

	if (height>0)
	{
		height=-height;
		Center-=(VecZ*height);
	}


    Obj->AllocatePoly(realnb2p,realnb2v);
	
    
	ind=0;
	for (j=0;j<(nb2sec2+1);j++)
    {
		for (i=0;i<(nb2sec);i++)
		{
            Obj->pv[(j*nb2sec)+i]=(VecX*(cos((((double)i*(360.0f/(double)nb2sec))*PI/180.0f)+OriginNg)*radius1)+//((cos((double)i*(360.0f/(double)nb2sec))*PI/180.0f)*radius1),
    			    VecY*(sin((((double)i*(360.0f/(double)nb2sec))*PI/180.0f)+OriginNg)*radius1)+
					VecZ*((double)height/(double)nb2sec2)*(double)j)+Center;
		}
    }


	// creation des faces
	//cote

	for (j=0;j<nb2sec2;j++)
    {
	    for (i=0;i<nb2sec;i++)
    	{
			First=Obj->pl[ind].Allocate(Obj,4);
	    	Obj->pi[First+0]=i+j*nb2sec;
    		Obj->pi[First+1]=i+nb2sec+j*nb2sec;
			Obj->pi[First+3]=((i+1)%nb2sec)+j*nb2sec;
    		Obj->pi[First+2]=((i+1)%nb2sec)+nb2sec+j*nb2sec;
    		ind++;
        }
	}

	First=Obj->pl[ind].Allocate(Obj,nb2sec);
	Obj->pl[ind+1].Allocate(Obj,nb2sec);
	//haut et bas
	/*
	for (i=0;i<nb2sec;i++)
	{
		Obj->pi[First+i]=i;

		Obj->pl[ind+1].nbvert[nb2sec-1-i]=i+(nb2sec2*nb2sec);
	}
*/
	if (!AutoUV)
	{
		//Obj->AllocateUV(0,realnb2v+nb2sec);
		ind=0;
		for (j=0;j<(nb2sec2+1);j++)
		{
			for (i=0;i<(nb2sec);i++)
			{
				Obj->puv[0][(j*nb2sec)+i].u=((Valu/(double)(nb2sec))*(double)i);
				Obj->puv[0][(j*nb2sec)+i].v=((Valv/(double)(nb2sec2+1.0f))*(double)j);
			}
		}

/*
		// creation des faces
		//cote

		for (j=0;j<nb2sec2;j++)
		{
			for (i=0;i<nb2sec;i++)
    		{
	    		Obj->piuv[pl[ind].Tex[0]+0]=i+j*nb2sec;
    			Obj->piuv[pl[ind].Tex[0]+1]=i+nb2sec+j*nb2sec;
				Obj->piuv[pl[ind].Tex[0]+3]=((i+1)%nb2sec)+j*nb2sec;
    			Obj->piuv[pl[ind].Tex[0]+2]=((i+1)%nb2sec)+nb2sec+j*nb2sec;
    			ind++;
			}
		}

		//haut et bas
		for (i=0;i<nb2sec;i++)
		{
			Obj->piuv[pl[ind].Tex[0]+i]=i+realnb2v;
			Obj->pl[ind+1].Tex[0][nb2sec-1-i]=i+realnb2v;//+(nb2sec*nb2sec);
			double fg=((double)i/(double)((double)nb2sec/2.0f))*PI;
			Obj->puv[0][i+realnb2v].u=((cos(fg)+1.0f)/2.0f)*Valu;
			Obj->puv[0][i+realnb2v].v=((sin(fg)+1.0f)/2.0f)*Valv;
		}
		*/
	}
	else
	{
		Obj->SetAutoTexRecalc(true);
	}

	return TRUE;
}

// un tube....
bool CKGenericMesh::CreateTube(CKMesh *Obj,Vertex Center,double radius1,double radius2,double &height,int nb2sec2,int nb2sec,double OriginNg)
{
	int realnb2v,realnb2p;
	int i,j,ind;
    Vertex tmp1;



	realnb2v=2*(nb2sec*(nb2sec2+1));
	realnb2p=((nb2sec*2)*nb2sec2)+(nb2sec*2);

	if (GetSnap())
	{
		Vertex vlngz=VecZ*height;
		vlngz.Snap(Obj->m_Scene->SnapVal);

		// uniform
		if (fabs(VecZ.x)>=0.0001f)
			height=(vlngz.x/VecZ.x);
		else
			if (fabs(VecZ.y)>=0.0001f)
				height=(vlngz.y/VecZ.y);
			else
				height=(vlngz.z/VecZ.z);

	}
	//Vertex daStart=Center;

	if (height>0)
	{
		height=-height;
		Center-=(VecZ*height);
	}

	if (radius1<radius2)
	{
		double dummy=radius2;
		radius2=radius1;
		radius1=dummy;
	}
//    CKMeshName=nom;
    ind=0;

    Obj->AllocatePoly(realnb2p,realnb2v);


	for (j=0;j<(nb2sec2+1);j++)
    {
		for (i=0;i<(nb2sec);i++)
		{
            Obj->pv[ind]=(VecX*cos((((double)i*(360.0f/(double)nb2sec))*PI/180.0f)+OriginNg)*radius1+
    			    VecY*sin((((double)i*(360.0f/(double)nb2sec))*PI/180.0f)+OriginNg)*radius1+
                    VecZ*(height/(double)nb2sec2)*(double)j)+Center;
            ind++;
		}
    }

	for (j=0;j<(nb2sec2+1);j++)
    {
		for (i=0;i<(nb2sec);i++)
		{
            Obj->pv[ind]=(VecX*cos((((double)i*(360.0f/(double)nb2sec))*PI/180.0f)+OriginNg)*radius2+
    			    VecY*sin((((double)i*(360.0f/(double)nb2sec))*PI/180.0f)+OriginNg)*radius2+
					VecZ*(height/(double)nb2sec2)*(double)j)+Center;
			ind++;
		}
    }

    ind=0;

	// creation des faces
	//cote

	for (j=0;j<nb2sec2;j++)
    {
    	for (i=0;i<nb2sec;i++)
    	{
			First=Obj->pl[ind].Allocate(Obj,4);
	    	Obj->pi[First+0]=i+j*nb2sec;
    		Obj->pi[First+1]=i+nb2sec+j*nb2sec;
			Obj->pi[First+3]=((i+1)%nb2sec)+j*nb2sec;
    		Obj->pi[First+2]=((i+1)%nb2sec)+nb2sec+j*nb2sec;
	    	ind++;
        }
	}

	for (j=0;j<nb2sec2;j++)
    {
	    for (i=0;i<nb2sec;i++)
    	{
			First=Obj->pl[ind].Allocate(Obj,4);
			Obj->pi[First+2]=i+nb2sec+j*nb2sec+(nb2sec*(nb2sec2+1));
	    	Obj->pi[First+3]=i+j*nb2sec+(nb2sec*(nb2sec2+1));
			Obj->pi[First+0]=((i+1)%nb2sec)+j*nb2sec+(nb2sec*(nb2sec2+1));
    		Obj->pi[First+1]=((i+1)%nb2sec)+nb2sec+j*nb2sec+(nb2sec*(nb2sec2+1));
    		ind++;

        }
	}
	
	for (i=0;i<nb2sec;i++)
	{
		First=Obj->pl[ind].Allocate(Obj,4);
		Obj->pi[First+3]=i+(nb2sec*(nb2sec2+1));
		Obj->pi[First+0]=i;
		Obj->pi[First+1]=((1+i)%nb2sec);
		Obj->pi[First+2]=((i+1)%nb2sec)+(nb2sec*(nb2sec2+1));
		ind++;
	}

	for (i=0;i<nb2sec;i++)
	{
		First=Obj->pl[ind].Allocate(Obj,4);

		Obj->pi[First+3]=i+(nb2sec*nb2sec2);
		Obj->pi[First+0]=i+(nb2sec*(nb2sec2+1))+(nb2sec*nb2sec2);
		Obj->pi[First+2]=((1+i)%nb2sec)+(nb2sec*nb2sec2);
		Obj->pi[First+1]=((i+1)%nb2sec)+(nb2sec*(nb2sec2+1))+(nb2sec*nb2sec2);

		ind++;
	}

	if (!AutoUV)
	{
		//Obj->AllocateUV(0,realnb2v+nb2sec*4);
		ind=0;

		for (j=0;j<(nb2sec2+1);j++)
		{
			for (i=0;i<(nb2sec);i++)
			{
				Obj->puv[0][ind].u=((Valu/(double)(nb2sec))*(double)i);
				Obj->puv[0][ind].v=((Valv/(double)(nb2sec2+1.0f))*(double)j);
				Obj->puv[0][ind].v*=2;
				ind++;
			}
		}

		for (j=0;j<(nb2sec2+1);j++)
		{
			for (i=0;i<(nb2sec);i++)
			{
				Obj->puv[0][ind].u=((Valu/(double)nb2sec)*(double)i);
				Obj->puv[0][ind].v=((Valv/((double)nb2sec2+1.0f))*(double)j);
				Obj->puv[0][ind].v*=2;
				ind++;
			}
		}

		ind=0;
/*
		// creation des faces
		//cote

		for (j=0;j<nb2sec2;j++)
		{
    		for (i=0;i<nb2sec;i++)
    		{
	    		Obj->piuv[pl[ind].Tex[0]+0]=i+j*nb2sec;
    			Obj->piuv[pl[ind].Tex[0]+1]=i+nb2sec+j*nb2sec;
				Obj->piuv[pl[ind].Tex[0]+3]=((i+1)%nb2sec)+j*nb2sec;
    			Obj->piuv[pl[ind].Tex[0]+2]=((i+1)%nb2sec)+nb2sec+j*nb2sec;
	    		ind++;
			}
		}

		for (j=0;j<nb2sec2;j++)
		{
			for (i=0;i<nb2sec;i++)
    		{
				Obj->piuv[pl[ind].Tex[0]+2]=i+nb2sec+j*nb2sec+(nb2sec*(nb2sec2+1));
	    		Obj->piuv[pl[ind].Tex[0]+3]=i+j*nb2sec+(nb2sec*(nb2sec2+1));
				Obj->piuv[pl[ind].Tex[0]+0]=((i+1)%nb2sec)+j*nb2sec+(nb2sec*(nb2sec2+1));
    			Obj->piuv[pl[ind].Tex[0]+1]=((i+1)%nb2sec)+nb2sec+j*nb2sec+(nb2sec*(nb2sec2+1));
    			ind++;
			}
		}
		//haut et bas
		for (i=0;i<nb2sec;i++)
		{
			Obj->puv[0][realnb2v+i*4].u=0;
			Obj->puv[0][realnb2v+i*4].v=(Valv/(float)nb2sec)*(double)i;;
			Obj->puv[0][realnb2v+i*4+1].u=Valu;
			Obj->puv[0][realnb2v+i*4+1].v=(Valv/(float)nb2sec)*(double)i;;
			Obj->puv[0][realnb2v+i*4+2].u=Valu;
			Obj->puv[0][realnb2v+i*4+2].v=(Valv/(float)nb2sec)*(double)(i+1);
			Obj->puv[0][realnb2v+i*4+3].u=0;
			Obj->puv[0][realnb2v+i*4+3].v=(Valv/(float)nb2sec)*(double)(i+1);
		}
		
		for (i=0;i<nb2sec;i++)
		{
			Obj->piuv[pl[ind].Tex[0]+3]=realnb2v+i*4;
			Obj->piuv[pl[ind].Tex[0]+0]=realnb2v+i*4+1;
			Obj->piuv[pl[ind].Tex[0]+1]=realnb2v+i*4+2;
			Obj->piuv[pl[ind].Tex[0]+2]=realnb2v+i*4+3;
			ind++;
		}

		for (i=0;i<nb2sec;i++)
		{
			Obj->piuv[pl[ind].Tex[0]+3]=realnb2v+i*4;
			Obj->piuv[pl[ind].Tex[0]+0]=realnb2v+i*4+1;
			Obj->piuv[pl[ind].Tex[0]+1]=realnb2v+i*4+2;
			Obj->piuv[pl[ind].Tex[0]+2]=realnb2v+i*4+3;
			ind++;
		}
		*/
	}
	else
	{
		Obj->SetAutoTexRecalc(true);
	}


    return TRUE;
}
// une tite sphere
bool CKGenericMesh::CreateSphere(CKMesh *Obj,Vertex center,double radius,int nb2sec,double OriginNg)
{
	int realnb2v,realnb2p;
	int i,j,ind;

	realnb2v=nb2sec*(nb2sec+1);
	realnb2p=nb2sec*nb2sec*2;

    ind=0;

    Obj->AllocatePoly(realnb2p,realnb2v);

	for (j=0;j<(nb2sec+1);j++)
    {
		for (i=0;i<(nb2sec);i++)
		{
            Obj->pv[ind]=((VecX*cos((((double)i*(360.0f/(double)nb2sec))*PI/180.0f)+OriginNg)*(radius*cos(((double)j*(180.0f/((double)nb2sec))+90.0f)*PI/180.0f)))+
    			    (VecY*sin((((double)i*(360.0f/(double)nb2sec))*PI/180.0f)+OriginNg)*(radius*cos(((double)j*(180.0f/((double)nb2sec))+90.0f)*PI/180.0f)))+
                    (VecZ*sin(((double)j*(180.0f/(double)nb2sec)+90.0f)*PI/180.0f)*radius))+center;

			ind++;
		}
    }

    ind=0;

	// creation des faces

	for (j=0;j<nb2sec;j++)
    {
    	for (i=0;i<nb2sec;i++)
	    {
			First=Obj->pl[ind].Allocate(Obj,3);
			Obj->pi[First+0]=((1+i)%nb2sec)+j*nb2sec;
		    Obj->pi[First+1]=i+j*nb2sec;
    		Obj->pi[First+2]=((i+1)%nb2sec)+nb2sec+j*nb2sec;
	    	ind++;
			First=Obj->pl[ind].Allocate(Obj,3);
    		Obj->pi[First+0]=i+j*nb2sec;
			Obj->pi[First+1]=nb2sec+i+j*nb2sec;
	    	Obj->pi[First+2]=((i+1)%nb2sec)+nb2sec+j*nb2sec;
		    ind++;
        }
	}

	if (!AutoUV)
	{
		//Obj->AllocateUV(0,realnb2v);

		ind=0;
		for (j=0;j<(nb2sec+1);j++)
		{
			for (i=0;i<(nb2sec);i++)
			{
				Obj->puv[0][ind].u=((Valu/(double)(nb2sec))*(double)i);
				Obj->puv[0][ind].v=((Valv/(double)(nb2sec+1.0f))*(double)j);
				ind++;
			}
		}

		ind=0;
/*
		// creation des faces

		for (j=0;j<nb2sec;j++)
		{
    		for (i=0;i<nb2sec;i++)
			{
				Obj->piuv[pl[ind].Tex[0]+0]=((1+i)%nb2sec)+j*nb2sec;
				Obj->piuv[pl[ind].Tex[0]+1]=i+j*nb2sec;
    			Obj->piuv[pl[ind].Tex[0]+2]=((i+1)%nb2sec)+nb2sec+j*nb2sec;
	    		ind++;
    			Obj->piuv[pl[ind].Tex[0]+0]=i+j*nb2sec;
				Obj->piuv[pl[ind].Tex[0]+1]=nb2sec+i+j*nb2sec;
	    		Obj->piuv[pl[ind].Tex[0]+2]=((i+1)%nb2sec)+nb2sec+j*nb2sec;
				ind++;
			}
		}
		*/
	}
	else
	{
		Obj->SetAutoTexRecalc(true);
	}

	return TRUE;
}


bool CKGenericMesh::CreateCone(CKMesh *Obj,Vertex Center, double Radius1, double Radius2,double &height, int nb2sec2, int nb2sec1,double OriginNg)
{//@CODE_329

	int realnb2v,realnb2p;
	int i,j,ind;

//    CKMeshName=nom;
	if (GetSnap())
	{
		Vertex vlngz=VecZ*height;
		vlngz.Snap(Obj->m_Scene->SnapVal);

		// uniform
		if (fabs(VecZ.x)>=0.0001f)
			height=(vlngz.x/VecZ.x);
		else
			if (fabs(VecZ.y)>=0.0001f)
				height=(vlngz.y/VecZ.y);
			else
				height=(vlngz.z/VecZ.z);

	}
	//Vertex daStart=Center;

	if (height<0)
	{
		height=-height;
		Center-=(VecZ*height);
	}

	realnb2v=(nb2sec1*(nb2sec2+1));
	realnb2p=(nb2sec1*nb2sec2)+2;//(2*(nb2sec1-2));
    ind=0;

    Obj->AllocatePoly(realnb2p,realnb2v);
	float fZ=(height/(double)nb2sec2);

	for (j=0;j<(nb2sec2+1);j++)
    {
		for (i=0;i<(nb2sec1);i++)
		{
            Obj->pv[(j*nb2sec1)+i]=((VecX*cos((((double)i*(360.0f/(double)nb2sec1))*PI/180.0f)+OriginNg)*(Radius2+(((Radius1-Radius2)/(double)nb2sec1)*(double)j)))+
    			    (VecY*sin((((double)i*(360.0f/(double)nb2sec1))*PI/180.0f)+OriginNg)*(Radius2+(((Radius1-Radius2)/(double)nb2sec1)*(double)j)))+
                    (VecZ*fZ*(double)j))+Center;
		}
    }


	// creation des faces
	//cote

	for (j=0;j<nb2sec2;j++)
    {
        for (i=0;i<nb2sec1;i++)
    	{
			First=Obj->pl[ind].Allocate(Obj,4);

			Obj->pi[First+0]=i+nb2sec1+j*nb2sec1;
		    Obj->pi[First+1]=i+j*nb2sec1;
			Obj->pi[First+2]=((i+1)%nb2sec1)+j*nb2sec1;
		    Obj->pi[First+3]=((i+1)%nb2sec1)+nb2sec1+j*nb2sec1;
            ind++;
        }
	}

	First=Obj->pl[ind].Allocate(Obj,nb2sec1);
	Obj->pl[ind+1].Allocate(Obj,nb2sec1);
	//haut et bas
	/*
	for (i=0;i<nb2sec1;i++)
	{
		Obj->pi[First+nb2sec1-1-i]=i;
		Obj->pl[ind+1].nbvert[i]=i+(nb2sec1*nb2sec2);
	}
*/
	if (!AutoUV)
	{
		ind=0;

		//Obj->AllocateUV(0,realnb2v+nb2sec1);

		for (j=0;j<(nb2sec2+1);j++)
		{
			for (i=0;i<(nb2sec1);i++)
			{
				Obj->puv[0][(j*nb2sec1)+i].u=((Valu/((double)nb2sec1))*(double)i);
				Obj->puv[0][(j*nb2sec1)+i].v=((Valv/((double)nb2sec2+1.0f))*(double)j);
				Obj->puv[0][(j*nb2sec1)+i].v*=2;
			}
		}

		// creation des faces
		//cote
/*
		for (j=0;j<nb2sec2;j++)
		{
			for (i=0;i<nb2sec1;i++)
    		{
				Obj->piuv[pl[ind].Tex[0]+0]=i+nb2sec1+j*nb2sec1;
				Obj->piuv[pl[ind].Tex[0]+1]=i+j*nb2sec1;
				Obj->piuv[pl[ind].Tex[0]+2]=((i+1)%nb2sec1)+j*nb2sec1;
				Obj->piuv[pl[ind].Tex[0]+3]=((i+1)%nb2sec1)+nb2sec1+j*nb2sec1;
				ind++;
			}
		}

		First=Obj->pl[ind].Allocate(Obj,nb2sec1);
		Obj->pl[ind+1].Allocate(Obj,nb2sec1);
		//haut et bas
		for (i=0;i<nb2sec1;i++)
		{
			Obj->piuv[pl[ind].Tex[0]+i]=i+realnb2v;

			Obj->pl[ind+1].Tex[0][i]=i+realnb2v;

			double fg=((double)i/(double)((double)nb2sec1/2.0f))*PI;
			Obj->puv[0][i+realnb2v].u=((cos(fg)+1.0f)/2.0f)*Valu;
			Obj->puv[0][i+realnb2v].v=((sin(fg)+1.0f)/2.0f)*Valv;
		}
		*/
	}
	else
	{
		Obj->SetAutoTexRecalc(true);
	}

    return true;
}
