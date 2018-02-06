// PrecalcLight.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "PrecalcLight.h"
#include "LightCalc.h"
#include "../entity/Entities/light.h"
#include "../entity/lightp.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//extern "C" CKScene *m_Plugin->m_Scene;

typedef struct
{
    int Indice;
    int x;
    int y;
    BYTE *lpBits;
	CKMesh *daMesh;
} tristr;

int Compare(const void *arg1,const void *arg2)
{
    tristr *a1,*a2;

    a1=(tristr*)arg1;
    a2=(tristr*)arg2;

    if ( (a1->x*a1->y)>(a2->x*a2->y) ) return -1;
    if ( (a1->x*a1->y)<(a2->x*a2->y) ) return 1;

    return 0;
}

// ----------------------------------------------------------------------------
typedef float vec_t;
typedef vec_t vec2_t[3];
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];
#define VectorScale(a,b,c) {c[0]=b*a[0];c[1]=b*a[1];c[2]=b*a[2];}
#define VectorSubtract(a,b,c) {c[0]=a[0]-b[0];c[1]=a[1]-b[1];c[2]=a[2]-b[2];}
#define DotProductf(x,y) (x[0]*y[0]+x[1]*y[1]+x[2]*y[2])

#define VectorCopy(a,b) {b[0]=a[0];b[1]=a[1];b[2]=a[2];}
float DotProduct(Vertex &x,Vertex &y)
{
	return (x.x*y.x + x.y*y.y + x.z*y.z);
}

vec_t VectorNormalize( const vec3_t in, vec3_t out ) {
	vec_t	length, ilength;

	length = sqrt (in[0]*in[0] + in[1]*in[1] + in[2]*in[2]);
	if (length == 0)
	{
		//VectorClear (out);
        out[0]=0;
        out[1]=0;
        out[2]=0;
		return 0;
	}

	ilength = 1.0/length;
	out[0] = in[0]*ilength;
	out[1] = in[1]*ilength;
	out[2] = in[2]*ilength;

	return length;
}

float LIGHTMAP_SIZE=512;
float LIGHTMAP_THRES=1.0f;

CKPolygon *CurrentPolygon;

void CalcLightTexCoord(CKPolygon *dapl,Vertex *allv,int &Lightsx,int &Lightsy,Vertex &Origin,Vertex &Trx,Vertex &Try,CKMesh *daMesh)
{
    int j;
    vec3_t      daNorm;
    vec3_t		mins, maxs, size, exactSize;
	vec3_t		delta;
	//Vertex delta;
	int			w, h;
	int			x, y;
	int			axis;
	vec3_t		vecs[2];
	float		s, t;
	vec3_t		origin;
    int ci;
	float		d;
	vec3_t		planeNormal;
    Vertex min,max;

    dapl->CalcPlan(allv);


/*
//	Origin=min;
	Vertex VT,V1,V2;


    min=allv[dapl->nbvert[0]];
    max=min;
    for (j=1;j<dapl->nb2vert;j++)
    {
        min.GetMinOf(allv[dapl->nbvert[j]]);
        max.GetMaxOf(allv[dapl->nbvert[j]]);
    }


/*
	V1=allv[dapl->nbvert[1]]-allv[dapl->nbvert[0]];
	j=2;
	while ((V1.x==0)&&(V1.y==0))
	{
		V1=allv[dapl->nbvert[(j%dapl->nb2vert)]]-allv[dapl->nbvert[j-1]];
		j++;
	}
	V1.x=1;
	V1.y=0;
	V1.z=0;

	V1.x=fabs(V1.x);
	V1.y=fabs(V1.y);

  */
/*
	if (dapl->Normale.z!=0)
	{
		Vertex t1,t2,t3;
		t1.x=dapl->Normale.x;
		t1.y=dapl->Normale.z;

		t2.z=1;

		V1.Cross(t1,t2);
		V1.z=V1.y;
		V1.y=0;
	}
	else
	{
		if (dapl->Normale.y==0)
		{
			V1.x=0;
			V1.y=1;
			V1.z=0;
		}
		else
		{
			V1.x=1;
			V1.y=0;
			V1.z=0;
		}
	}

	V2.Cross(dapl->Normale,V1);
	
	V1.Normalize();
	V2.Normalize();

	V2.x=fabs(V2.x);
	V2.y=fabs(V2.y);
	V2.z=fabs(V2.z);

	V1.x=fabs(V1.x);
	V1.y=fabs(V1.y);
	V1.z=fabs(V1.z);

	Vertex dif=max-min;
	double lngx=fabs(DotProduct( dif, V1 ));
	double lngy=fabs(DotProduct( dif, V2 ));


	Origin=min;
	double dist=dapl->GetDist(min);
	Vertex gd=dapl->Normale;
	gd.x*=dist;
	gd.y*=dist;
	gd.z*=dist;
	Origin-=gd;

	for (ci = 0 ; ci < dapl->nb2vert ; ci++ ) 
	{
        delta=(allv[dapl->nbvert[ci]]-Origin);
        s = fabs(DotProduct( delta, V1 ));
		t = fabs(DotProduct( delta, V2 ));

        // IMPORTANT
		
		float u = s / (LIGHTMAP_SIZE+1);
		float v = t / (LIGHTMAP_SIZE+1);
		
		u/=LIGHTMAP_THRES;
		v/=LIGHTMAP_THRES;

		daMesh->puv[1][dapl->Tex[1][ci]].u=u;
		daMesh->puv[1][dapl->Tex[1][ci]].v=v;
	}




	lngx/=LIGHTMAP_THRES;
	lngy/=LIGHTMAP_THRES;
	

	Lightsx=lngx+1;
	Lightsy=lngy+1;

	Trx=V1;
	Trx.x*=LIGHTMAP_THRES;
	Trx.y*=LIGHTMAP_THRES;
	Trx.z*=LIGHTMAP_THRES;
	Try=V2;
	Try.x*=LIGHTMAP_THRES;
	Try.y*=LIGHTMAP_THRES;
	Try.z*=LIGHTMAP_THRES;



	DMPOutputString(" Origin (%5.2f,%5.2f,%5.2f) V1 (%5.2f,%5.2f,%5.2f) V2 (%5.2f,%5.2f,%5.2f) lng (%d,%d) \r\n",
		Origin.x,Origin.y,Origin.z,
		Trx.x,Trx.y,Trx.z,
		Try.x,Try.y,Try.z,Lightsx,Lightsy);
/*

    min=allv[dapl->nbvert[0]];
    max=min;
    for (j=1;j<dapl->nb2vert;j++)
    {
        min.GetMinOf(allv[dapl->nbvert[j]]);
        max.GetMaxOf(allv[dapl->nbvert[j]]);
    }

    //float fact=4;

    

    daNorm[0]=dapl->Normale.x;
    daNorm[1]=dapl->Normale.y;
    daNorm[2]=dapl->Normale.z;

    mins[0]=min.x;
    mins[1]=min.y;
    mins[2]=min.z;

    maxs[0]=max.x;
    maxs[1]=max.y;
    maxs[2]=max.z;
    
*/
	planeNormal[0]=dapl->Normale.x;
	planeNormal[1]=dapl->Normale.y;
	planeNormal[2]=dapl->Normale.z;

	daNorm[0]=dapl->Normale.x;
	daNorm[1]=dapl->Normale.y;
	daNorm[2]=dapl->Normale.z;

    min=allv[dapl->nbvert[0]];
    max=min;
    for (j=1;j<dapl->nb2vert;j++)
    {
        min.GetMinOf(allv[dapl->nbvert[j]]);
        max.GetMaxOf(allv[dapl->nbvert[j]]);
    }
	mins[0]=min.x;
	mins[1]=min.y;
	mins[2]=min.z;

	maxs[0]=max.x;
	maxs[1]=max.y;
	maxs[2]=max.z;

	// round to the lightmap resolution
	for ( ci = 0 ; ci < 3 ; ci++ ) {
		exactSize[ci] = maxs[ci] - mins[ci];
		mins[ci] = LIGHTMAP_THRES * floor( mins[ci] / LIGHTMAP_THRES );
		maxs[ci] = LIGHTMAP_THRES * ceil( maxs[ci] / LIGHTMAP_THRES );
		size[ci] = (maxs[ci] - mins[ci]) / LIGHTMAP_THRES+1 ;

        //planeNormal[ci] = fabs( daNorm[ci]);
	}

	// the two largest axis will be the lightmap size
	memset( vecs, 0, sizeof( vecs ) );

	planeNormal[0] = fabs( dapl->Normale.x );
	planeNormal[1] = fabs( dapl->Normale.y );
	planeNormal[2] = fabs( dapl->Normale.z );

	if ( planeNormal[0] >= planeNormal[1] && planeNormal[0] >= planeNormal[2] ) 
    {
		w = size[1];
		h = size[2];
		axis = 0;
		vecs[0][1] = 1.0 / LIGHTMAP_THRES;
		vecs[1][2] = 1.0 / LIGHTMAP_THRES;
	} 
    else 
    if ( planeNormal[1] >= planeNormal[0] && planeNormal[1] >= planeNormal[2] ) 
    {
		w = size[0];
		h = size[2];
		axis = 1;
		vecs[0][0] = 1.0 / LIGHTMAP_THRES;
		vecs[1][2] = 1.0 / LIGHTMAP_THRES;
	} 
    else 
    {
		w = size[0];
		h = size[1];
		axis = 2;
		vecs[0][0] = 1.0 / LIGHTMAP_THRES;
		vecs[1][1] = 1.0 / LIGHTMAP_THRES;
	}

	if ( w > LIGHTMAP_SIZE ) {
		VectorScale ( vecs[0], (float)LIGHTMAP_SIZE/w, vecs[0] );
		w = LIGHTMAP_SIZE;
	}
	
	if ( h > LIGHTMAP_SIZE ) {
		VectorScale ( vecs[1], (float)LIGHTMAP_SIZE/h, vecs[1] );
		h = LIGHTMAP_SIZE;
	}

    x=0;
    y=0;

    // calculate polygone texture coordinates
    // set the polygon U/V
	for (ci = 0 ; ci < dapl->nb2vert ; ci++ ) 
	{
        delta[0]=allv[dapl->nbvert[ci]].x-mins[0];
        delta[1]=allv[dapl->nbvert[ci]].y-mins[1];
        delta[2]=allv[dapl->nbvert[ci]].z-mins[2];
        s = DotProductf( delta, vecs[0] ) + x+0.5;
		t = DotProductf( delta, vecs[1] ) + y+0.5;

        // IMPORTANT
		
		float u = s / LIGHTMAP_SIZE;
		float v = t / LIGHTMAP_SIZE;

		daMesh->puv[1][dapl->Tex[1][ci]].u=u ;
		daMesh->puv[1][dapl->Tex[1][ci]].v=v;
	}

	// calculate the world coordinates of the lightmap samples

	// project mins onto plane to get origin
	vec3_t xyz;
	xyz[0]=allv[dapl->nbvert[0]].x;
	xyz[1]=allv[dapl->nbvert[0]].y;
	xyz[2]=allv[dapl->nbvert[0]].z;

	double ddist = DotProductf( xyz, daNorm );
	d = DotProductf( mins, daNorm ) - ddist;
    d/=daNorm[axis];

	VectorCopy( mins, origin );
	origin[axis] -= d;

	// project stepped lightmap blocks and subtract to get planevecs
	for ( ci = 0 ; ci < 2 ; ci++ ) {
		vec3_t	normalized;
		float	len;

		len = VectorNormalize( vecs[ci], normalized );
		VectorScale( normalized, (1.0/len), vecs[ci] );
		d = DotProductf( vecs[ci], daNorm );
		d /= daNorm[ axis ];
		vecs[ci][axis] -= d;
	}

    // return the values

    Origin.x=origin[0];
    Origin.y=origin[1];
    Origin.z=origin[2];

    Trx.x=(vecs[0][0]);
    Trx.y=(vecs[0][1]);
    Trx.z=(vecs[0][2]);

    Try.x=(vecs[1][0]);
    Try.y=(vecs[1][1]);
    Try.z=(vecs[1][2]);

    Lightsx=w;
    Lightsy=h;




/*



	Vertex V1=allv[dapl->nbvert[1]]-allv[dapl->nbvert[0]];
	j=2;
	while ((V1.x==0)&&(V1.y==0))
	{
		V1=allv[dapl->nbvert[(j%dapl->nb2vert)]]-allv[dapl->nbvert[j-1]];
		j++;
	}
	V1.z=0;

	V1.x=fabs(V1.x);
	V1.y=fabs(V1.y);
	V1.z=fabs(V1.z);


	Vertex V2;
	V2.Cross(dapl->Normale,V1);
	

	V2.x=fabs(V2.x);
	V2.y=fabs(V2.y);
	V2.z=fabs(V2.z);


	V1.Normalize();
	V2.Normalize();


	Trx=V1;
	Trx.x*=LIGHTMAP_THRES;
	Trx.y*=LIGHTMAP_THRES;
	Trx.z*=LIGHTMAP_THRES;
	Try=V2;
	Try.x*=LIGHTMAP_THRES;
	Try.y*=LIGHTMAP_THRES;
	Try.z*=LIGHTMAP_THRES;

	Origin=min;
	*/
}

/////////////////////////////////////////////////////////////////////////////
// CPrecalcLight dialog


CPrecalcLight::CPrecalcLight(CWnd* pParent /*=NULL*/)
	: CDialog(CPrecalcLight::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrecalcLight)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPrecalcLight::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrecalcLight)
	DDX_Control(pDX, IDC_WRITERAW, m_WriteRaw);
	DDX_Control(pDX, IDC_ROUND, m_Round);
	DDX_Control(pDX, IDC_DENSITY, m_Density);
	DDX_Control(pDX, IDC_MSIZE, m_Size);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrecalcLight, CDialog)
	//{{AFX_MSG_MAP(CPrecalcLight)
	ON_BN_CLICKED(IDC_CALCULATE, OnCalculate)
	ON_BN_CLICKED(IDC_AMBIANT, OnAmbiant)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrecalcLight message handlers

void CPrecalcLight::OnCalculate() 
{
	m_Progress.ShowWindow(SW_SHOWNORMAL);

	
	int TotalPoly=0;
	int i,j,sx,sy;;
	int TexIndAv=0;

	int ListLightMapSize[]={128,256,512,1024};
	int ListLumelSize[]={2,4,8,16};
	int LightMapSize,LumelSize;

    Vertex orig,scx,scy;
    CLightCalc calc1;
	calc1.m_Scene=m_Plugin->m_Scene;

	CLight *daLight;

    float tu,tv,stu,stv;
    int ind;
    tristr *txsx;
	char tempo[256];
	int nbTexObj;
	CKMesh *daMesh;
	CKEntity *daEnt;

	LightMapSize=ListLightMapSize[m_Size.GetCurSel()];
	LumelSize=4;//ListLumelSize[m_Density.GetCurSel()];
	LIGHTMAP_SIZE=LightMapSize;
	LIGHTMAP_THRES=LumelSize;

    CKTextureSpacePacker packer(LightMapSize,LightMapSize);

    unsigned long Ticks=GetTickCount();

	// calculate total polygones and allocate UV ON SECOND CANAL !!!!!

	for (daMesh=m_Plugin->m_Scene->FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
	{
		TotalPoly+=daMesh->nb2poly;
		TexIndAv=0;
		nbTexObj=0;
		for (i=0;i<daMesh->nb2poly;i++)
		{
			nbTexObj+=daMesh->pl[i].nb2vert;
		}


		daMesh->AllocateUV(1,nbTexObj);
		for (i=0;i<daMesh->nb2poly;i++)
		{
			daMesh->pl[i].Allocate(daMesh,2,daMesh->pl[i].nb2vert);
			for (j=0;j<daMesh->pl[i].nb2vert;j++)
			{
				daMesh->pl[i].Tex[1][j]=TexIndAv;
				TexIndAv++;
			}
		}
		daMesh->CalcAllPlanes();
	}
	// precalc spots
	//for (daLight=m_Plugin->m_Scene->FirstLight;daLight!=NULL;daLight=daLight->Next)
	for (daEnt=m_Plugin->m_Scene->FirstEntity;daEnt!=NULL;daEnt=daEnt->Next)
	{
		if (strcmp(daEnt->EntType,"Light")==0)
		{
			daLight=&((CKEntityLight*)daEnt)->m_Light;
			daLight->PrecalcSpot();
		}
	}

	// calculate Lightmap

	m_Progress.SetRange(0,TotalPoly);

    txsx=new tristr [TotalPoly];

    TotalPoly=0;

	for (daMesh=m_Plugin->m_Scene->FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
	{
		for (i=0;i<daMesh->nb2poly;i++)
		{
			
			{
			CalcLightTexCoord(&daMesh->pl[i],daMesh->pv,sx,sy,orig,scx,scy,daMesh);
			txsx[TotalPoly].Indice=i;
			txsx[TotalPoly].x=sx;
			txsx[TotalPoly].y=sy;
			txsx[TotalPoly].daMesh=daMesh;
			txsx[TotalPoly].lpBits=new BYTE[sx*sy*3];
			memset(txsx[TotalPoly].lpBits,0x30,sx*sy*3);

			CurrentPolygon=&daMesh->pl[i];

//			for (daLight=m_Plugin->m_Scene->FirstLight;daLight!=NULL;daLight=daLight->Next)
			for (daEnt=m_Plugin->m_Scene->FirstEntity;daEnt!=NULL;daEnt=daEnt->Next)
			{
				if (strcmp(daEnt->EntType,"Light")==0)
				{
					daLight=&((CKEntityLight*)daEnt)->m_Light;
					{
						daLight->Radius2=daLight->Radius*0.5;
						calc1.CalcLightmap(orig,scx,scy, txsx[TotalPoly].lpBits,sx,sy, daLight);//,allp,allv,plav);
					}
				}
			}
			}
			TotalPoly++;
			m_Progress.SetPos(TotalPoly);
			
        }
    }



    // packit

	bool RoundIt=m_Round.GetCheck();

    qsort(txsx,TotalPoly,sizeof(tristr),Compare);
	m_Plugin->m_Scene->InitAllTag(-1,PLUGIN_MESH);

	for (i=0;i<TotalPoly;i++)
	{
		packer.AddTextureFragment(txsx[i].x,txsx[i].y,txsx[i].lpBits,ind,tu,tv,stu,stv,RoundIt);
		delete [] txsx[i].lpBits;

		for (j=0;j<txsx[i].daMesh->pl[txsx[i].Indice].nb2vert;j++)
		{
			txsx[i].daMesh->puv[1][txsx[i].daMesh->pl[txsx[i].Indice].Tex[1][j]].u+=(tu);
			txsx[i].daMesh->puv[1][txsx[i].daMesh->pl[txsx[i].Indice].Tex[1][j]].v+=(tv);
		}
		
		txsx[i].daMesh->pl[txsx[i].Indice].Tag=ind;

	}
    

	if (m_WriteRaw.GetCheck())
		packer.WriteRaw();

	packer.AddToScene(m_Plugin->m_Scene,true,1);

    delete [] txsx;


	m_Progress.ShowWindow(SW_HIDE);

	DrawViews();

    sprintf(tempo,"It took %5.2f secs",(float)(GetTickCount()-Ticks)/1000);
    MessageBox(tempo,"Precalcul finished.",MB_OK);
   
}

BOOL CPrecalcLight::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Size.SetCurSel(2);
	m_Density.SetCurSel(1);

	m_Round.SetCheck(1);
	m_WriteRaw.SetCheck(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrecalcLight::OnAmbiant() 
{
	// TODO: Add your control notification handler code here
	
}

void CPrecalcLight::OnOK() 
{
}

void CPrecalcLight::OnCancel() 
{
}