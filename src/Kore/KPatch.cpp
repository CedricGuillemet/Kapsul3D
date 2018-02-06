// KPatch.cpp: implementation of the CKPatch class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "kore.h"
#include "KPatch.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define PATCHTYPE 3 // quadratic
//#define PATCHTYPE 4 // cubic

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKPatch::CKPatch(CKScene *pScene,CKPatch *daPrev,CKPatch *daNext)
{
	m_Scene=pScene;
	Prev=daPrev;
	Next=daNext;
	nb2vert=0;
	nb2pt=0;
	pts=NULL;
	pv=NULL;
	Tesselate=0; // default tesselate
	puv=NULL;
	
	
    Tex1=m_Scene->FirstTexture;
	Tex2=NULL;
	Tex3=NULL;
	Tex4=NULL;
	
	Selected=false;
	Hided=false;
	
	puv=new UVCoords *[4];
    puv[0]=NULL;
    puv[1]=NULL;
    puv[2]=NULL;
    puv[3]=NULL;
	
    nbTexCanals=1;
    nbTexCoords[0]=NULL;
    nbTexCoords[1]=NULL;
    nbTexCoords[2]=NULL;
    nbTexCoords[3]=NULL;
	nb2patch=1;
	
}

CKPatch::CKPatch()
{
	m_Scene=NULL;
	Prev=NULL;
	Next=NULL;
	nb2vert=0;
	nb2pt=0;
	pts=NULL;
	pv=NULL;
	Tesselate=0; // default tesselate
	puv=NULL;
	
    Tex1=NULL;//dk->FirstTexture;
	Tex2=NULL;
	Tex3=NULL;
	Tex4=NULL;
	
	Selected=false;
	Hided=false;
	
	puv=new UVCoords *[4];
    puv[0]=NULL;
    puv[1]=NULL;
    puv[2]=NULL;
    puv[3]=NULL;
	
    nbTexCanals=1;
    nbTexCoords[0]=NULL;
    nbTexCoords[1]=NULL;
    nbTexCoords[2]=NULL;
    nbTexCoords[3]=NULL;
	nb2patch=1;
	
}
CKPatch::~CKPatch()
{
}

bool CKPatch::Allocate(int nb2p, int nb2v)
{
    if (nb2p!=0)
    {
        if (nb2pt!=0)
        {
            CtrlsPt=(int*)realloc(CtrlsPt,sizeof(int)*nb2p);
			memset(CtrlsPt,0,sizeof(int)*nb2p);
        }
        else
        {
            CtrlsPt=(int*)malloc(sizeof(int)*nb2p);
			memset(CtrlsPt,0,sizeof(int)*nb2p);
        }

		if (nb2p!=0)
        {
            nb2pt=nb2p;
        }
    }
	
    if (nb2v!=0)
    {
        if (nb2vert!=0)
        {
            pv=(Vertex*)realloc(pv,sizeof(Vertex)*nb2v);
			memset(pv,0,sizeof(Vertex)*nb2v);
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
	
    return true;
}

// Basis functions, should pre-compute
inline float CKPatch::Get(int base, int i, float t)
{
	float v = (1.0f - t);
	
	if (base == 2)
	{
		if (i == 0)
			return v * v;
		else if (i == 1)
			return 2 * t * v;
		else if (i == 2)
			return t * t;
	}
	else if (base == 3)
	{
		if (i == 0)
			return v * v * v;
		else if (i == 1)
			return 3 * t * v * v;
		else if (i == 2)
			return 3 * t * t * v;
		else if (i == 3)
			return t * t * t;         
	}
	return 0;
	
}

// Derivatives of the basis functions, should pre-compute
inline float CKPatch::GetDeriv(int base, int i, float t)
{
	float v = (1.0f - t);
	
	if (base == 2)
	{
		if (i == 0)
			return (2 * t) - 2;
		else if (i == 1)
			return 1 - (2 * t);
		else if (i == 2)
			return 2 * t;
	}
	else if (base == 3)
	{
		if (i == 0)
			return -3 * v * v;
		else if (i == 1)
			return 3 - (12 * t) + (9 * t * t);
		else if (i == 2)
			return (6 * t) - (9 * t * t);
		else if (i == 3)
			return 3 * t * t;
	}
	return 0;
}

void CKPatch::Reset(void)
{
	if (pts!=NULL) delete [] pts;
}

void CKPatch::Build(int newSteps)
{
	int i,j;
	/*
	if (type < 3 || type > 4)
	return;
	*/
	/*
	if (!newSteps)
	newSteps = 1;
	*/
	int avPatch;
	float inc = 0.0f;
	Vertex *dest = 0, *ndest = 0;
	int sp = 0, su = 0, sv = 0;
	int type=3;
	int base = type - 1;
	
	bool reAlloc = 0;
	
	// new tesselation level does not match current, need to re-allocate
	if (newSteps != Tesselate)
	{
		Reset();
		Tesselate = newSteps ? newSteps : 1;
		reAlloc = 1;
	}
	
	
	inc = 1.0f / (Tesselate);
	
	sp = Tesselate +1;
	
	
	
	if (reAlloc)
	{
		if (!(pts = new Vertex[nb2patch*sp * sp]))
		{
			Reset();
			return;
		}
	}
	
	
	//   ndest = norms;
	
	// build the patches
	// !!TODO make this faster, don't use the vec3_t operators
	dest = pts;
	for (avPatch=0;avPatch<nb2patch;avPatch++)
	{
		su=0;
		sv=0;
		
	for (float v = 0; sv <= Tesselate; v += inc, sv++, dest += sp)
	{
		
		for (float u = 0; su <= Tesselate; u += inc, su++)
		{
		
			Vertex p;
			p.x=0;
			p.y=0;
			p.z=0;
			/*
			p.x=0;
			p.y=0;
			p.z=0;
			*/
			//, n(0, 0, 0);
			//vec3_t ut(0, 0, 0), vt(0, 0, 0);
			
			for (j = 0; j < type; j++)
			{
				for (i = 0; i < type; i++)
				{
					// for the patch point
					float bU = Get(base, i, u);
					float bV = Get(base, j, v);
					
					// for the normals, need to get df(u,v)/du and df(u,v)/dv
					float derivbU = GetDeriv(base, i, u);
					float derivbV = GetDeriv(base, j, v);
					float dbVbU = derivbV * bU;
					float dbUbV = derivbU * bV;
					
					float tmp1=(bU * bV);
                    
					//p.Add( * ctrl[j][i]->pos);
					/*
					p.x+=tmp1*ctrl[j][i].x;
					p.y+=tmp1*ctrl[j][i].y;
					p.z+=tmp1*ctrl[j][i].z;
					*/
					p.x+=pv[CtrlsPt[j*3+i+(avPatch*9)]].x*tmp1;
					p.y+=pv[CtrlsPt[j*3+i+(avPatch*9)]].y*tmp1;
					p.z+=pv[CtrlsPt[j*3+i+(avPatch*9)]].z*tmp1;
					
					
				}
			}
			
			//n.Cross(ut, vt);
			//n.Normalize();
			dest[su] = p;
			//ndest[su] = n;
		}
		su = 0;
	}
	}
	
	int ndx = 0;
	
	if (reAlloc)  
	{
		if (!(strips = new unsigned int*[Tesselate]))
		{
			Reset();
			return;
		}
	}
	
	for (int cnt = 0; cnt < Tesselate; cnt++, ndx += sp)
	{
		if (reAlloc)
		{
			if (!(strips[cnt] = new unsigned int[sp * 2]))
			{  
				Reset();
				return;
			}
		}
		
		unsigned int *dest = strips[cnt];
		
		for (int x = 0, a = 0; x < sp; x++, a += 2)
		{     
			dest[a] = ndx + sp + x;
			dest[a + 1] = ndx + x;
		}
	}
	GetMinMax();
	
}


void CKPatch::IsBoxed(int nbPatchX, int nbPatchY,Vertex Start,Vertex Fact)
{
	nb2patch=(((nbPatchX==3)?1:((nbPatchX-1)/2))*((nbPatchY==3)?1:((nbPatchY-1)/2)))*6;
	
	Allocate(nbPatchX*nbPatchY*6,(nbPatchX*nbPatchY*2)+( (nbPatchX-2) * nbPatchY ) + ((nbPatchX-2)*(nbPatchY-2)));

}

void CKPatch::IsCopyOf(CKPatch *dap)
{
	int i;

	//int Unique;
	Allocate(dap->nb2pt,dap->nb2vert);
	memcpy(pv,dap->pv,sizeof(Vertex)*dap->nb2vert);
	memcpy(CtrlsPt,dap->CtrlsPt,sizeof(int)*dap->nb2pt);

	nbTexCanals=dap->nbTexCanals;
	int nbTexCoords[4];
	for (i=0;i<dap->nbTexCanals;i++)
	{
		nbTexCoords[i]=dap->nbTexCoords[i];
		AllocateUV(i,nbTexCoords[i]);
		memcpy(puv[i],dap->puv[i],sizeof(UVCoords)*dap->nbTexCoords[i]);
	}

	nb2patch=dap->nb2patch;
	m_Scene=dap->m_Scene;
    Tex1=dap->Tex1;
	Tex2=dap->Tex2;
	Tex3=dap->Tex3;
	Tex4=dap->Tex4;
	Name=dap->Name;
	Hided=false;
	BBMin=dap->BBMin;
	BBMax=dap->BBMax;
	Tag=0;
	Tesselate=1;
	Selected=false;
	Build(dap->Tesselate);

}

bool CKPatch::AllocateUV(int Canal, int nb2uv)
{
	
	if (nb2uv!=0)
	{
		if (nbTexCoords[Canal]!=0)
		{
			if (nb2uv!=nbTexCoords[Canal])
			{
				puv[Canal]=(UVCoords*)realloc(puv[Canal],sizeof(UVCoords)*nb2uv);
				memset(puv[Canal],0,sizeof(UVCoords)*nb2uv);
			}
		}
		else
		{
			puv[Canal]=(UVCoords*)malloc(sizeof(UVCoords)*nb2uv);
			memset(puv[Canal],0,sizeof(UVCoords)*nb2uv);
		}
		
		if (nb2uv!=0)
		{
			nbTexCoords[Canal]=nb2uv;
		}
		
		nbTexCanals=Canal+1;
	}
	
	return true;
}

void CKPatch::ComputeTexCoords(int CanalNb,double U,double V,int nbpX,int nbpY)
{
								
	int i,j;

	float inc = 0.0f;
	Vertex *dest = 0, *ndest = 0;
	int sp = 0, su = 0, sv = 0;
	int type=3;
	int base = type - 1;
	
	bool reAlloc = 0;
	
	
	inc = 1.0f / (Tesselate);
	
	sp = Tesselate +1;
	
	dest = pts;

	AllocateUV(CanalNb, (sp * sp*nb2patch));
	
	int TexAv=0;
	float du=U/(float)(nbpX*Tesselate);
	float dv=V/(float)(nbpY*Tesselate);

	for (j = 0; j < nbpY; j++)
	{
		for (i = 0; i < nbpX; i++)
		{
			for (float v = 0,sv=0; sv <= Tesselate; v += inc,sv++)
			{
				for (float u = 0,su=0; su <= Tesselate; u += inc,su++)
				{
					puv[0][TexAv].u=du*((i*Tesselate)+su);
					puv[0][TexAv].v=dv*((j*Tesselate)+sv);

					TexAv++;
				}
			}
		}
	}
	
}

void CKPatch::IsPlanar(int nbPatchX, int nbPatchY,Vertex Start,Vertex pSize,Vertex pX,Vertex pY,double U,double V)
{
	int i,j,k,l;
	

	nb2patch=nbPatchX*nbPatchY;//(((nbPatchX==3)?1:((nbPatchX-1)/2))*((nbPatchY==3)?1:((nbPatchY-1)/2)));
	
	Allocate(nbPatchX*nbPatchY*9,((nbPatchX*2)+1)*((nbPatchY*2)+1));
	ComputeTexCoords(0,U,V,nbPatchX,nbPatchY);

	float p1=(float)(nbPatchX*2);//(((float)nbPatchX*2.0f)+1.0f);
	float p2=(float)(nbPatchY*2);//(((float)nbPatchY*2.0f)+1.0f);
	pX.x/=p1;
	pX.y/=p1;
	pX.z/=p1;
	pY.x/=p2;
	pY.y/=p2;
	pY.z/=p2;

	//srand(GetTickCount());
	for (j = 0; j < ((nbPatchY*2)+1); j++)
	{
		for (i = 0; i < ((nbPatchX*2)+1); i++)
		{
			//pv[j*((nbPatchX*2)+1)+i]=(((Dap->pX*i)+(Dap->pY*j))*pSize)+Start;
			int decal=j*((nbPatchX*2)+1)+i;


			pv[decal]=( ((pX*i)+(pY*j))*pSize)+Start;
			/*
			pv[decal].y=j*10;
			pv[decal].z=(float)(rand()&7);
			*/

			
		}
	}

	int sp = Tesselate +1;
	if (pts!=NULL) delete [] pts;
	pts = new Vertex[nb2patch*sp * sp];

	int ptctl=0;
	int cour=0,cour2,cour3;
	for (j = 0; j < nbPatchY; j++)
	{
		cour3=cour;
		for (i = 0; i < nbPatchX; i++)
		{
			cour2=cour;
			for (k=0;k<3;k++)
			{
				for (l=0;l<3;l++)
				{
					CtrlsPt[ptctl++]=cour;
						//l+ ((k+ ((j*2)+1)) *((nbPatchX*2)+1) )+ ((i*2)+1);
					cour++;

				}
				cour+=((nbPatchX*2)+1)-3;
			}
			cour=cour2+2;
		}
		cour=cour3+(((nbPatchX*2)+1)*2);
	}


}

void CKPatch::GetMinMax(void)
{
	if (pv!=NULL)
	{
		BBMin=pv[0];
		BBMax=pv[0];
		for (int i=1;i<nb2vert;i++)
		{
			BBMin.GetMinOf(pv[i]);
			BBMax.GetMaxOf(pv[i]);
		}
	}
	else
	{
		BBMin=Vertex(0,0,0);
		BBMax=Vertex(0,0,0);
	}
}

void CKPatch::Update(void)
{
	GetMinMax();
}

void CKPatch::ApplyTexture(CKTexture *daTex,int TexNb)
{
	switch (TexNb)
	{
	case 0:
		Tex1=daTex;
		break;
	case 1:
		Tex2=daTex;
		break;
	case 2:
		Tex3=daTex;
		break;
	case 3:
		Tex4=daTex;
		break;
	}
}
