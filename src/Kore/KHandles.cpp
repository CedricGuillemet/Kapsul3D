// KHandles.cpp: implementation of the CKHandles class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KHandles.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern CKOption *KOption2;

CKHandles::CKHandles()
{
	DrawHanks=new Vertex[48];
	Hanks=new Vertex[48];
	CalculateHandles=true;

}

CKHandles::~CKHandles()
{
	delete [] DrawHanks;
	delete [] Hanks;
}



void CKHandles::CalcHandles(CKScene *m_Scene,int ActiveView,Vertex HandMin,Vertex HandMax)
{
	Vertex temp;
	int i;
	Vertex handles[8];
	//DMPOutputString("Calculate\r\n");
/*
	if (m_Scene->ViewType[ActiveView]==4)
	//if (ActiveView>=100)
	{
		
		CurHookMaxSel.x=(m_Scene->UVMaxSel.u*64);
		CurHookMaxSel.y=-(m_Scene->UVMaxSel.v*64);
		CurHookMaxSel.z=0;

		CurHookMinSel.x=(m_Scene->UVMinSel.u*64);
		CurHookMinSel.y=-(m_Scene->UVMinSel.v*64);
		CurHookMinSel.z=0;

	}
	else
	{
		CurHookMaxSel=m_Scene->HookMaxSel;
		CurHookMinSel=m_Scene->HookMinSel;
	}
*/

	CurHookMaxSel=HandMin;
	CurHookMinSel=HandMax;

	handles[0]=CurHookMinSel;

	handles[1].x=CurHookMaxSel.x;
	handles[1].y=CurHookMinSel.y;
	handles[1].z=CurHookMinSel.z;

	handles[2].x=CurHookMaxSel.x;
	handles[2].y=CurHookMaxSel.y;
	handles[2].z=CurHookMinSel.z;

	handles[3].x=CurHookMinSel.x;
	handles[3].y=CurHookMaxSel.y;
	handles[3].z=CurHookMinSel.z;

	handles[4].x=CurHookMinSel.x;
	handles[4].y=CurHookMinSel.y;
	handles[4].z=CurHookMaxSel.z;

	handles[5].x=CurHookMaxSel.x;
	handles[5].y=CurHookMinSel.y;
	handles[5].z=CurHookMaxSel.z;

	handles[6]=CurHookMaxSel;

	handles[7].x=CurHookMinSel.x; 
	handles[7].y=CurHookMaxSel.y;
	handles[7].z=CurHookMaxSel.z;

	Vertex dif;
	dif=(CurHookMaxSel-CurHookMinSel)/4;

	Hanks[0]=Vertex(handles[0].x,handles[0].y,handles[0].z);
	Hanks[1]=Vertex(handles[0].x+dif.x,handles[0].y,handles[0].z);

	Hanks[2]=Vertex(handles[0].x,handles[0].y,handles[0].z);
	Hanks[3]=Vertex(handles[0].x,handles[0].y+dif.y,handles[0].z);

	Hanks[4]=Vertex(handles[0].x,handles[0].y,handles[0].z);
	Hanks[5]=Vertex(handles[0].x,handles[0].y,handles[0].z+dif.z);

	Hanks[6]=Vertex(handles[1].x,handles[1].y,handles[1].z);
	Hanks[7]=Vertex(handles[1].x-dif.x,handles[1].y,handles[1].z);

	Hanks[8]=Vertex(handles[1].x,handles[1].y,handles[1].z);
	Hanks[9]=Vertex(handles[1].x,handles[1].y+dif.y,handles[1].z);

	Hanks[10]=Vertex(handles[1].x,handles[1].y,handles[1].z);
	Hanks[11]=Vertex(handles[1].x,handles[1].y,handles[1].z+dif.z);

	Hanks[12]=Vertex(handles[2].x,handles[2].y,handles[2].z);
	Hanks[13]=Vertex(handles[2].x-dif.x,handles[2].y,handles[2].z);

	Hanks[14]=Vertex(handles[2].x,handles[2].y,handles[2].z);
	Hanks[15]=Vertex(handles[2].x,handles[2].y-dif.y,handles[2].z);

	Hanks[16]=Vertex(handles[2].x,handles[2].y,handles[2].z);
	Hanks[17]=Vertex(handles[2].x,handles[2].y,handles[2].z+dif.z);

	Hanks[18]=Vertex(handles[3].x,handles[3].y,handles[3].z);
	Hanks[19]=Vertex(handles[3].x+dif.x,handles[3].y,handles[3].z);

	Hanks[20]=Vertex(handles[3].x,handles[3].y,handles[3].z);
	Hanks[21]=Vertex(handles[3].x,handles[3].y-dif.y,handles[3].z);

	Hanks[22]=Vertex(handles[3].x,handles[3].y,handles[3].z);
	Hanks[23]=Vertex(handles[3].x,handles[3].y,handles[3].z+dif.z);

	Hanks[24]=Vertex(handles[4].x,handles[4].y,handles[4].z);
	Hanks[25]=Vertex(handles[4].x+dif.x,handles[4].y,handles[4].z);

	Hanks[26]=Vertex(handles[4].x,handles[4].y,handles[4].z);
	Hanks[27]=Vertex(handles[4].x,handles[4].y+dif.y,handles[4].z);

	Hanks[28]=Vertex(handles[4].x,handles[4].y,handles[4].z);
	Hanks[29]=Vertex(handles[4].x,handles[4].y,handles[4].z-dif.z);

	Hanks[30]=Vertex(handles[5].x,handles[5].y,handles[5].z);
	Hanks[31]=Vertex(handles[5].x-dif.x,handles[5].y,handles[5].z);

	Hanks[32]=Vertex(handles[5].x,handles[5].y,handles[5].z);
	Hanks[33]=Vertex(handles[5].x,handles[5].y+dif.y,handles[5].z);

	Hanks[34]=Vertex(handles[5].x,handles[5].y,handles[5].z);
	Hanks[35]=Vertex(handles[5].x,handles[5].y,handles[5].z-dif.z);

	Hanks[36]=Vertex(handles[6].x,handles[6].y,handles[6].z);
	Hanks[37]=Vertex(handles[6].x-dif.x,handles[6].y,handles[6].z);

	Hanks[38]=Vertex(handles[6].x,handles[6].y,handles[6].z);
	Hanks[39]=Vertex(handles[6].x,handles[6].y-dif.y,handles[6].z);

	Hanks[40]=Vertex(handles[6].x,handles[6].y,handles[6].z);
	Hanks[41]=Vertex(handles[6].x,handles[6].y,handles[6].z-dif.z);

	Hanks[42]=Vertex(handles[7].x,handles[7].y,handles[7].z);
	Hanks[43]=Vertex(handles[7].x+dif.x,handles[7].y,handles[7].z);

	Hanks[44]=Vertex(handles[7].x,handles[7].y,handles[7].z);
	Hanks[45]=Vertex(handles[7].x,handles[7].y-dif.y,handles[7].z);

	Hanks[46]=Vertex(handles[7].x,handles[7].y,handles[7].z);
	Hanks[47]=Vertex(handles[7].x,handles[7].y,handles[7].z-dif.z);

	for (i=0;i<48;i++)
		DrawHanks[i]=Hanks[i];

/*
	int viewport[16];
	double mvmatrix[16],projmatrix[16];

    glGetIntegerv(GL_VIEWPORT,viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
    glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);
*/
	int nbFront=8;

	for (i=0;i<8;i++)
	{
		double tmp3;
		//gluProject(handles[i].x,handles[i].y,handles[i].z,mvmatrix,projmatrix,viewport, &spt[i].x,&spt[i].y,&tmp3);
		m_Scene->m_Renderer->Project(m_Scene->Active,handles[i].x,handles[i].y,handles[i].z,spt[i].x,spt[i].y,tmp3);
		/*
		gluProject(handles[i].x,handles[i].y,handles[i].z,
			m_Scene->mvmatrix[m_Scene->Active],m_Scene->projmatrix[m_Scene->Active],m_Scene->viewport[m_Scene->Active], 
			);
		*/
		if (tmp3<=0) nbFront--;
	}

	if (nbFront<3) return;
	MinPt=spt[0];
	MaxPt=spt[0];
	for (i=1;i<8;i++)
	{
		if (spt[i].x<MinPt.x) MinPt.x=spt[i].x;
		if (spt[i].y<MinPt.y) MinPt.y=spt[i].y;
		if (spt[i].x>MaxPt.x) MaxPt.x=spt[i].x;
		if (spt[i].y>MaxPt.y) MaxPt.y=spt[i].y;
	}

	double dav1=((MaxPt.x-MinPt.x)/(double)SELTESSELATE);

	for (i=0;i<=SELTESSELATE;i++)
	{
		a2DHandles[i].x=MinPt.x+(dav1*(double)i);
		a2DHandles[i].y=MinPt.y;

		a2DHandles[i+SELTESSELATE].x=MaxPt.x;
		a2DHandles[i+SELTESSELATE].y=MinPt.y+(((MaxPt.y-MinPt.y)/SELTESSELATE)*(float)i);

		a2DHandles[i+(SELTESSELATE*2)].x=MaxPt.x+(((MinPt.x-MaxPt.x)/SELTESSELATE)*(float)i);
		a2DHandles[i+(SELTESSELATE*2)].y=MaxPt.y;

		a2DHandles[i+(SELTESSELATE*3)].x=MinPt.x;
		a2DHandles[i+(SELTESSELATE*3)].y=MaxPt.y+(((MinPt.y-MaxPt.y)/SELTESSELATE)*(float)i);


	}

	a2DHandles[(SELTESSELATE*4)].x=MinPt.x-10;
	a2DHandles[(SELTESSELATE*4)].y=MinPt.y-10;
	

	double tmp3;


	MYPOINT spt[8],MinPt,MaxPt;

	/*
	int viewport[16];
	double mvmatrix[16],projmatrix[16];

    glGetIntegerv(GL_VIEWPORT,viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
    glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);
*/

	for (i=0;i<8;i++)
	{
		//double tmp3;
		/*
		gluProject(handles[i].x,handles[i].y,handles[i].z,
			m_Scene->mvmatrix[m_Scene->Active],m_Scene->projmatrix[m_Scene->Active],m_Scene->viewport[m_Scene->Active], 
			&spt[i].x,&spt[i].y,&tmp3);
			*/
		m_Scene->m_Renderer->Project(m_Scene->Active,handles[i].x,handles[i].y,handles[i].z,spt[i].x,spt[i].y,tmp3);
		//if (tmp3<=0) nbFront--;
	}

	//if (nbFront<3) return 0;
	MinPt=spt[0];
	MaxPt=spt[0];
	for (i=1;i<8;i++)
	{
		if (spt[i].x<MinPt.x) MinPt.x=spt[i].x;
		if (spt[i].y<MinPt.y) MinPt.y=spt[i].y;
		if (spt[i].x>MaxPt.x) MaxPt.x=spt[i].x;
		if (spt[i].y>MaxPt.y) MaxPt.y=spt[i].y;
	}


	ta2DHandles[0].x=MinPt.x;
	ta2DHandles[0].y=MinPt.y;
	ta2DHandles[1].x=MinPt.x;
	ta2DHandles[1].y=MaxPt.y;
	ta2DHandles[2].x=MaxPt.x;
	ta2DHandles[2].y=MaxPt.y;
	ta2DHandles[3].x=MaxPt.x;
	ta2DHandles[3].y=MinPt.y;
	ta2DHandles[4].x=MinPt.x+(MaxPt.x-MinPt.x)/2;
	ta2DHandles[4].y=MinPt.y;
	ta2DHandles[5].x=MinPt.x+(MaxPt.x-MinPt.x)/2;
	ta2DHandles[5].y=MaxPt.y;
	ta2DHandles[6].x=MinPt.x;
	ta2DHandles[6].y=MinPt.y+(MaxPt.y-MinPt.y)/2;
	ta2DHandles[7].x=MaxPt.x;
	ta2DHandles[7].y=MinPt.y+(MaxPt.y-MinPt.y)/2;
	ta2DHandles[8].x=MinPt.x-10;
	ta2DHandles[8].y=MinPt.y-10;
	ta2DHandles[9].x=MinPt.x+(MaxPt.x-MinPt.x)/2;
	ta2DHandles[9].y=MinPt.y+(MaxPt.y-MinPt.y)/2;



}

void CKHandles::RotateHandles(float degs,int ActiveView)
{
	// Rotate
	int i;
	double MidX,MidY;

	MidX=MinPt.x+((MaxPt.x-MinPt.x)/2.0f);
	MidY=MinPt.y+((MaxPt.y-MinPt.y)/2.0f);

	for (i=0;i<=(SELTESSELATE*4)+1;i++)
	{
		double tx,ty;
		tx=RotX((a2DHandles[i].x-MidX),(a2DHandles[i].y-MidY),DEG2RAD(degs));
		ty=RotY((a2DHandles[i].x-MidX),(a2DHandles[i].y-MidY),DEG2RAD(degs));

		a2DHandles[i].x=tx+MidX;
		a2DHandles[i].y=ty+MidY;
	}
}

void CKHandles::TranslateHandles(MYPOINT trans,int ActiveView)
{
	// translate
	int i;
	//DMPOutputString("Translate\r\n");
	for (i=0;i<=(SELTESSELATE*4)+1;i++)
	{
		double tx,ty;
		tx=a2DHandles[i].x+trans.x;
		ty=a2DHandles[i].y+trans.y;

		a2DHandles[i].x=tx;
		a2DHandles[i].y=ty;
	}
}

void CKHandles::ScaleHandles(int Corner,MYPOINT ScaleVal,int ActiveView)
{
	// translate
	int i;
	double MidX,MidY;

	MidX=ta2DHandles[Corner].x;
	MidY=ta2DHandles[Corner].y;

	for (i=0;i<=(SELTESSELATE*4)+1;i++)
	{
		double tx,ty;
		tx=((a2DHandles[i].x-MidX)*ScaleVal.x)+MidX;
		ty=((a2DHandles[i].y-MidY)*ScaleVal.y)+MidY;

		a2DHandles[i].x=tx;
		a2DHandles[i].y=ty;
	}
}


void CKHandles::BendBuf(int Corner,double ngb,int Sens)
{
    double ngr;
	int i;
	double MidX,MidY;

	MidX=ta2DHandles[Corner].x;
	MidY=ta2DHandles[Corner].y;

	MYPOINT tmpMax=ta2DHandles[2];
	MYPOINT tmpMin=ta2DHandles[4];

	ngb-=PI;
	ngb=fmod(ngb,PI);

	for (i=0;i<=(SELTESSELATE*4)+1;i++)
	{
		double tx,ty;
		double dif;


		if (Sens==1)
		{
			if ((tmpMax.x-MidX)!=0) dif=(tmpMax.x-MidX);
				else dif=(tmpMin.x-MidX);

			ngr=((a2DHandles[i].x-MidX)/dif)*(ngb);
		}
		else
		{
			if ((tmpMax.y-MidY)!=0) dif=(tmpMax.y-MidY);
				else dif=(tmpMin.y-MidY);

			ngr=((a2DHandles[i].y-MidY)/dif)*(ngb);
		}


		tx=RotX((a2DHandles[i].x-MidX),(a2DHandles[i].y-MidY),ngr);
		ty=RotY((a2DHandles[i].x-MidX),(a2DHandles[i].y-MidY),ngr);

		a2DHandles[i].x=tx+MidX;
		a2DHandles[i].y=ty+MidY;
	}

}

void CKHandles::SquizBuf(int Corner,double Facteur,int Sens)
{
    //VertexBuf *vb;
    MYPOINT tmp;
    MYPOINT tmpCenter;
    MYPOINT tmpMax,tmpMin;
    Vertex destval;
    Vertex tmpr;
	int i;

    tmpCenter=ta2DHandles[Corner];
    tmpMax=ta2DHandles[2];
    tmpMin=ta2DHandles[4];
	MYPOINT dif;
	dif.x=tmpMax.x-tmpMin.x;
	dif.y=tmpMax.y-tmpMin.y;
	//Facteur/=2;

  	for (i=0;i<=(SELTESSELATE*4)+1;i++)
	{
        tmp=a2DHandles[i];

        tmpr.x=1;
        tmpr.y=1;
        tmpr.z=1;

		if (Sens==0)
		{
			tmpr.x=(((tmp.y-tmpCenter.y)/dif.y)*Facteur)+1.0f;
		}
		else
		{
			tmpr.y=(((tmp.x-tmpCenter.x)/dif.x)*Facteur)+1.0f;
		}
/*
        daBufVert->IsNow( Dap->Scale((daBufVert->AncVal-Axis),tmpr)+Axis );
        daBufVert=daBufVert->Next;
*/
		double tx,ty;
		tx=((a2DHandles[i].x-tmpCenter.x)*tmpr.x)+tmpCenter.x;
		ty=((a2DHandles[i].y-tmpCenter.y)*tmpr.y)+tmpCenter.y;

		a2DHandles[i].x=tx;
		a2DHandles[i].y=ty;
    }

}

void CKHandles::TaperBuf(int Corner,double Facteur,int Sens)
{
    MYPOINT tmp;
    MYPOINT tmpCenter;
    MYPOINT tmpMax,tmpMin;
    Vertex destval;
    Vertex tmpr;
	int i;

    tmpCenter=ta2DHandles[Corner];
    tmpMax=ta2DHandles[2];
    tmpMin=ta2DHandles[4];

	for (i=0;i<=(SELTESSELATE*4)+1;i++)
	{
        tmp=a2DHandles[i];

        tmpr.x=0;
        tmpr.y=0;
        tmpr.z=0;

        // right deform
		if (Sens==1)
			tmpr.x=((tmp.y-tmpCenter.y)/(tmpMax.y-tmpMin.y))*Facteur;
		else
			tmpr.y=((tmp.x-tmpCenter.x)/(tmpMax.x-tmpMin.x))*Facteur;

		a2DHandles[i].x+=tmpr.x;
		a2DHandles[i].y+=tmpr.y;
    }

}



int CKHandles::GetHandle(CKScene *m_Scene,int X,int Y)
{
	int RetVal=0;
	int i;
	double tmp3;
	

    Vertex Clickhui=m_Scene->m_Renderer->GetIsoCoord(X,Y,m_Scene->Active);
	MYPOINT pony;

	m_Scene->m_Renderer->Project(m_Scene->Active,Clickhui.x,Clickhui.y,Clickhui.z,pony.x,pony.y,tmp3);

	for (i=0;i<9;i++)
	{
		if (Pythagore(ta2DHandles[i].x-pony.x,ta2DHandles[i].y-pony.y)<7)
		{
			return (i+1);
		}
	}

	if (Pythagore(ta2DHandles[9].x-pony.x,ta2DHandles[9].y-pony.y)<30) return 10;

	for (i=0;i<9;i++)
	{
		if (SegDistance(ta2DHandles[i],ta2DHandles[(i+1)%8],pony)<3) return 10;
	}


	return 0;
}

void CKHandles::Get2DCenter(int ActiveView,MYPOINT &Center)
{
	Center.x=MinPt.x+(MaxPt.x-MinPt.x)/2;
	Center.y=MinPt.y+(MaxPt.y-MinPt.y)/2;
}

