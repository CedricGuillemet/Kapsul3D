//---------------------------------------------------------------------------
#include "stdafx.h"

unsigned int L_Unique=0;

#include "Light.h"
extern CKScene *GScene;
//extern CKDrawScene GDrawScene;

CLight::CLight()
{
	/*
    Next = daNext;
    Prev = daPrev;
	*/
	//Name = new char [32];

	Radius=100.0f;
	Radius2 = 0;

	Unique = L_Unique++;
	Hided  = false;

	Name="Light"; //Light name
	r = 0.5f;			  //Light color
	g = 0.0f;
	b = 0.5f;
	Type	    = -1;	  //Omni light
	SpotType	= 1;	  //Circular
	Target.x= 0.0f;	  //Target x
	Target.y= 0.0f;	  //Target x
	Target.z= 0.0f;	  //Target x
}

CLight::~CLight()
{
}

Vertex CLight::GetMaxOf(void)
{
	// 0:omni,1:spot
	if (Type==0)
	{
		return Source;
	}
	else
	{
		Vertex tmp;
		tmp=Source;
		tmp.GetMaxOf(Target);
		return tmp;
	}
}


Vertex CLight::GetMinOf(void)
{
	if (Type==0)
	{
		return Source;
	}
	else
	{
		Vertex tmp;
		tmp=Source;
		tmp.GetMinOf(Target);
		return tmp;
	}

}

void CLight::operator =(CLight *cmpt)
{
    Source=cmpt->Source;
    Target=cmpt->Target;
    Type=cmpt->Type;

    Selected=cmpt->Selected;
    SpotType=cmpt->SpotType;

    Radius=cmpt->Radius;
	Name=cmpt->Name;
    r=cmpt->r;
    g=cmpt->g;
    b=cmpt->b;
    Brightness=cmpt->Brightness;
    
}

void CLight::DrawColorQuad(int ViewInd)
{
	Vertex vt[4];
	int Inds[4]={0,1,2,3};

	CKPlan plan;
	plan.PlanOfView(m_Renderer,ViewInd);


    vt[0]=Source+(plan.pX*10+plan.pY*10);//m_Renderer->GetIsoCoord(pt1.x,pt1.y,ViewInd,Vertex(0,0,0));
    vt[3]=Source+(plan.pX*28+plan.pY*10);//m_Renderer->GetIsoCoord(pt1.x,pt1.y,ViewInd,Vertex(0,0,0));
    vt[2]=Source+(plan.pX*28+plan.pY*28);//m_Renderer->GetIsoCoord(pt1.x,pt1.y,ViewInd,Vertex(0,0,0));
    vt[1]=Source+(plan.pX*10+plan.pY*28);//m_Renderer->GetIsoCoord(pt1.x,pt1.y,ViewInd,Vertex(0,0,0));

	m_Renderer->DirectRender(vt,NULL,Inds,KQUADS,4,b,g,r,1);
	m_Renderer->DirectRender(vt,NULL,Inds,KLINE_LOOP,4,1,1,1,1);


}
void CLight::DrawOmni(Vertex & daViewSize,int ViewInd,int Primitive)
{
	int i;
	static Vertex vt[48];
	static int Indices[48];
	float r,g,b,a;

	for (i=0;i<48;i++)
		Indices[i]=i;

	DrawColorQuad(ViewInd);
	
    if (Source.Selected)
	{
		r=1;g=0.5;b=0;a=1;
	}
	else
	{
		r=1;g=1;b=0;a=1;
	}

	
	vt[0]=Vertex((daViewSize.x/20)+Source.x,(daViewSize.x/20)+Source.y,(daViewSize.x/20)+Source.z);
	vt[1]=Vertex(-(daViewSize.x/20)+Source.x,-(daViewSize.x/20)+Source.y,-(daViewSize.x/20)+Source.z);

	vt[2]=Vertex((daViewSize.x/20)+Source.x,-(daViewSize.x/20)+Source.y,(daViewSize.x/20)+Source.z);
	vt[3]=Vertex(-(daViewSize.x/20)+Source.x,(daViewSize.x/20)+Source.y,-(daViewSize.x/20)+Source.z);

	vt[4]=Vertex((daViewSize.x/20)+Source.x,(daViewSize.x/20)+Source.y,-(daViewSize.x/20)+Source.z);
	vt[5]=Vertex(-(daViewSize.x/20)+Source.x,-(daViewSize.x/20)+Source.y,(daViewSize.x/20)+Source.z);

	vt[6]=Vertex((daViewSize.x/20)+Source.x,-(daViewSize.x/20)+Source.y,-(daViewSize.x/20)+Source.z);
	vt[7]=Vertex(-(daViewSize.x/20)+Source.x,(daViewSize.x/20)+Source.y,(daViewSize.x/20)+Source.z);

	m_Renderer->DirectRender(vt,NULL,Indices,KLINES,8,r,g,b,a);

	double temp;

	for (i=0;i<16;i++)
	{
		temp=(i*PI)/8;
		vt[i].x=cos(temp)*Radius;
		vt[i].y=sin(temp)*Radius;
		vt[i].z=0;

		vt[i+16].x=0;
		vt[i+16].y=sin(temp)*Radius;
		vt[i+16].z=cos(temp)*Radius;

		vt[i+32].x=sin(temp)*Radius;
		vt[i+32].y=0;
		vt[i+32].z=cos(temp)*Radius;

		vt[i]+=Source;
		vt[i+16]+=Source;
		vt[i+32]+=Source;
	}
	glEnd();

	m_Renderer->DirectRender(vt,NULL,Indices,KLINE_LOOP,16,r,g,b,a);
	m_Renderer->DirectRender(vt,NULL,&Indices[16],KLINE_LOOP,16,r,g,b,a);
	m_Renderer->DirectRender(vt,NULL,&Indices[32],KLINE_LOOP,16,r,g,b,a);

}

void CLight::DrawSpot(Vertex & daViewSize,int ViewInd,int Primitive)
{
	int i;
	static Vertex vt[100];
	static int Indices[100];
	float r,g,b,a;

	for (i=0;i<100;i++)
		Indices[i]=i;

	DrawColorQuad(ViewInd);

	// Matrix

	CKMatrix mModel;
	CKMatrix mModelInv;

	double Length=Pythagore3D(Source,Target);

	mModel.Identity();
	mModel.gluLookAt(Source.x,Source.y,Source.z,Target.x,Target.y,Target.z, 0.0,0.0,1.0);

	mModel.InvertMatrix(&mModelInv);


	Vertex tmp1(0,0,0);
	mModelInv.MultVectorByMatrix(&tmp1,&vt[0]);
	tmp1.z=-1.0f*Length;
	mModelInv.MultVectorByMatrix(&tmp1,&vt[1]);

	Indices[0]=0;
	Indices[1]=1;

	// Vertex Source/Dest

	if (Primitive==1)
	{
		if (Source.Selected)
			m_Renderer->DirectRender(vt,NULL,Indices,KPOINTS,1,1,0.5,0,1);
		else
			m_Renderer->DirectRender(vt,NULL,Indices,KPOINTS,1,1,1,0,1);

		if (Source.Selected)
			m_Renderer->DirectRender(vt,NULL,&Indices[1],KPOINTS,1,1,0.5,0,1);
		else
			m_Renderer->DirectRender(vt,NULL,&Indices[1],KPOINTS,1,1,1,0,1);
	}

	if ( (Source.Selected)&&(Target.Selected))
	{
		r=1;g=0.5;b=0;a=1;
	}
	else
	{
		r=1;g=1;b=0;a=1;
	}
		
	// circle

	m_Renderer->DirectRender(vt,NULL,Indices,KLINES,2,r,g,b,a);


	for (i=0;i<100;i++)
	{
		tmp1.x=cos((i*PI)/50)*Radius;
		tmp1.y=sin((i*PI)/50)*Radius;
		tmp1.z=-Length;
		mModelInv.MultVectorByMatrix(&tmp1,&vt[i]);
	}
	m_Renderer->DirectRender(vt,NULL,Indices,KLINE_STRIP,100,r,g,b,a);

	// 4 lines

	tmp1=Vertex(0,0,0);
	mModelInv.MultVectorByMatrix(&tmp1,&vt[0]);
	tmp1=Vertex(Radius,0,-Length);
	mModelInv.MultVectorByMatrix(&tmp1,&vt[1]);

	tmp1=Vertex(0,0,0);
	mModelInv.MultVectorByMatrix(&tmp1,&vt[2]);
	tmp1=Vertex(-Radius,0,-Length);
	mModelInv.MultVectorByMatrix(&tmp1,&vt[3]);

	tmp1=Vertex(0,0,0);
	mModelInv.MultVectorByMatrix(&tmp1,&vt[4]);
	tmp1=Vertex(0,-Radius,-Length);
	mModelInv.MultVectorByMatrix(&tmp1,&vt[5]);

	tmp1=Vertex(0,0,0);
	mModelInv.MultVectorByMatrix(&tmp1,&vt[6]);
	tmp1=Vertex(0,Radius,-Length);
	mModelInv.MultVectorByMatrix(&tmp1,&vt[7]);

	m_Renderer->DirectRender(vt,NULL,Indices,KLINES,8,r,g,b,a);
}

void CLight::DrawNeon(Vertex & daViewSize,int ViewInd,int Primitive)
{
	int i;
	static Vertex vt[100];
	static int Indices[100];
	float r,g,b,a;

	for (i=0;i<100;i++)
		Indices[i]=i;

	DrawColorQuad(ViewInd);

	// Matrix

	CKMatrix mModel;
	CKMatrix mModelInv;

	double Length=Pythagore3D(Source,Target);

	mModel.Identity();
	mModel.gluLookAt(Source.x,Source.y,Source.z,Target.x,Target.y,Target.z, 0.0,0.0,1.0);

	mModel.InvertMatrix(&mModelInv);


	Vertex tmp1(0,0,0);
	mModelInv.MultVectorByMatrix(&tmp1,&vt[0]);
	tmp1.z=-1.0f*Length;
	mModelInv.MultVectorByMatrix(&tmp1,&vt[1]);

	Indices[0]=0;
	Indices[1]=1;

	// Vertex Source/Dest

	if (Primitive==1)
	{
		if (Source.Selected)
			m_Renderer->DirectRender(vt,NULL,Indices,KPOINTS,1,1,0.5,0,1);
		else
			m_Renderer->DirectRender(vt,NULL,Indices,KPOINTS,1,1,1,0,1);

		if (Source.Selected)
			m_Renderer->DirectRender(vt,NULL,&Indices[1],KPOINTS,1,1,0.5,0,1);
		else
			m_Renderer->DirectRender(vt,NULL,&Indices[1],KPOINTS,1,1,1,0,1);
	}

	if ( (Source.Selected)&&(Target.Selected))
	{
		r=1;g=0.5;b=0;a=1;
	}
	else
	{
		r=1;g=1;b=0;a=1;
	}
		
	// 2 circles

	m_Renderer->DirectRender(vt,NULL,Indices,KLINES,2,r,g,b,a);


	for (i=0;i<100;i++)
	{
		tmp1.x=cos((i*PI)/50)*Radius;
		tmp1.y=sin((i*PI)/50)*Radius;
		tmp1.z=-Length;
		mModelInv.MultVectorByMatrix(&tmp1,&vt[i]);
	}
	m_Renderer->DirectRender(vt,NULL,Indices,KLINE_STRIP,100,r,g,b,a);

	for (i=0;i<100;i++)
	{
		tmp1.x=cos((i*PI)/50)*Radius;
		tmp1.y=sin((i*PI)/50)*Radius;
		tmp1.z=0;
		mModelInv.MultVectorByMatrix(&tmp1,&vt[i]);
	}
	m_Renderer->DirectRender(vt,NULL,Indices,KLINE_STRIP,100,r,g,b,a);


	// 4 lines

	tmp1=Vertex(Radius,0,0);
	mModelInv.MultVectorByMatrix(&tmp1,&vt[0]);
	tmp1=Vertex(Radius,0,-Length);
	mModelInv.MultVectorByMatrix(&tmp1,&vt[1]);

	tmp1=Vertex(-Radius,0,0);
	mModelInv.MultVectorByMatrix(&tmp1,&vt[2]);
	tmp1=Vertex(-Radius,0,-Length);
	mModelInv.MultVectorByMatrix(&tmp1,&vt[3]);

	tmp1=Vertex(0,-Radius,0);
	mModelInv.MultVectorByMatrix(&tmp1,&vt[4]);
	tmp1=Vertex(0,-Radius,-Length);
	mModelInv.MultVectorByMatrix(&tmp1,&vt[5]);

	tmp1=Vertex(0,Radius,0);
	mModelInv.MultVectorByMatrix(&tmp1,&vt[6]);
	tmp1=Vertex(0,Radius,-Length);
	mModelInv.MultVectorByMatrix(&tmp1,&vt[7]);

	m_Renderer->DirectRender(vt,NULL,Indices,KLINES,8,r,g,b,a);

}

void CLight::Draw(CKRenderer *pRender,Vertex & daViewSize,int ViewInd,int Primitive)
{
	//Vertex CircleHui;
	m_Renderer=pRender;
	
	switch (Type)
	{
	case 0:
		DrawOmni(daViewSize,ViewInd,Primitive);
		break;
	case 1:
		DrawSpot(daViewSize,ViewInd,Primitive);
		break;
	case 2:
		DrawNeon(daViewSize,ViewInd,Primitive);
		break;
	}

}

void CLight::PrecalcSpot()
{
	if (Type==1)
	{
		//if (Radius2==0) Radius2=Radius*0.90;
		Radius2=Radius*0.90;

		tanRad1=tan(((Radius/2)*PI)/180.0f);
		tanRad2=tan(((Radius2/2)*PI)/180.0f);

		Length=sqrt((Target.x-Source.x)*(Target.x-Source.x)+
			(Target.y-Source.y)*(Target.y-Source.y)+
			(Target.z-Source.z)*(Target.z-Source.z) );
	}
}

void CLight::IsCopyOf(CLight *cmpt)
{
	Source=cmpt->Source;
	Target=cmpt->Target;

    SourceSelected=false;
	TargetSelected=false;
	Selected=false;

    Type=cmpt->Type; // 0:omni,1:spot
    SpotType=cmpt->SpotType; //Rectangular,circular

	Radius=cmpt->Radius;
    Radius2=cmpt->Radius2;


	//memcpy(Name,cmpt->Name,32);

    TopWidth=cmpt->TopWidth;
    TopHeight=cmpt->TopHeight;
    BottomWidth=cmpt->BottomWidth;
    BottomHeight=cmpt->BottomHeight;

	r=cmpt->r;
	g=cmpt->g;
	b=cmpt->b;

	Brightness=cmpt->Brightness;
    
	PrecalcSpot();
	Unique=cmpt->Unique;
}

//bool CLight::SelectLight(CKScene *pScene,CKDrawScene *pDrawScene,int dx,int dy,int X,int Y,CKShape *pShape,bool AddIt,bool Crossing,int TypeSel,int WholeSelect)
//{
 /*   MYPOINT sdeb,sfin;
    bool HasBeenSel=false;
    bool daAddIt,daAddIt1,daAddIt2;
 
    Vertex Clickhui=View->GetIsoCoord(dx,dy,GScene->Active);
    MYPOINT spt=Get2D(Clickhui);
 
    Vertex Clickhui2=View->GetIsoCoord(X,Y,GScene->Active);
    MYPOINT spt2=Get2D(Clickhui2);
 
 double Length=Pythagore((X-dx),(Y-dy));
 
 for (CLight *daLight=GScene->FirstLight;daLight!=NULL;daLight=daLight->Next)
    {
        sdeb=Get2D(daLight->Source);
        sfin=Get2D(daLight->Target);
 
  daAddIt1=false;
  daAddIt2=false;
 
        if (daLight->Type==0)
        {
            // omni
   switch(TypeSel)
   {
    case SELECT_SINGLE:
     daAddIt1=(Pythagore((sdeb.x-spt2.x),(sdeb.y-spt2.y))<3);
     break;
    case SELECT_CIRCLE:
     daAddIt1=(Pythagore((sdeb.x-spt.x),(sdeb.y-spt.y))<Length);
     break;
    case SELECT_QUAD:
     daAddIt1=( (((sdeb.x>=spt.x)&&(sdeb.x<=spt2.x))||((sdeb.x<=spt.x)&&(sdeb.x>=spt2.x)))&&
      (((sdeb.y>=spt.y)&&(sdeb.y<=spt2.y))||((sdeb.y<=spt.y)&&(sdeb.y>=spt2.y))) );
     break;
    case SELECT_FENCE:
     daAddIt1=pShape->IsVertInShape(daLight->Source,View);
     break;
   }
        }
        else
        {
            // spot
   switch(TypeSel)
   {
    case SELECT_SINGLE:
     if (WholeSelect==SELECT_WHOLE) 
     {
      daAddIt1=(SegDistance(sdeb,sfin,spt2)<3);
      daAddIt2=daAddIt1;
     }
     if (WholeSelect==SELECT_VERTEX) 
     {
      daAddIt1=(Pythagore((sdeb.x-spt2.x),(sdeb.y-spt2.y))<3);
      daAddIt2=(Pythagore((sfin.x-spt2.x),(sfin.y-spt2.y))<3);
     }
     break;
    case SELECT_CIRCLE:
     daAddIt1=(Pythagore((sdeb.x-spt.x),(sdeb.y-spt.y))<Length);
     daAddIt2=(Pythagore((sfin.x-spt.x),(sfin.y-spt.y))<Length);
     break;
    case SELECT_QUAD:
     daAddIt1=( (((sdeb.x>=spt.x)&&(sdeb.x<=spt2.x))||((sdeb.x<=spt.x)&&(sdeb.x>=spt2.x)))&&
      (((sdeb.y>=spt.y)&&(sdeb.y<=spt2.y))||((sdeb.y<=spt.y)&&(sdeb.y>=spt2.y))) );
     daAddIt2=( (((sfin.x>=spt.x)&&(sfin.x<=spt2.x))||((sfin.x<=spt.x)&&(sfin.x>=spt2.x)))&&
      (((sfin.y>=spt.y)&&(sfin.y<=spt2.y))||((sfin.y<=spt.y)&&(sfin.y>=spt2.y))) );
     break;
    case SELECT_FENCE:
     daAddIt1=pShape->IsVertInShape(daLight->Source,View);
     daAddIt2=pShape->IsVertInShape(daLight->Target,View);
     break;
   }
        }
 
  if (WholeSelect==SELECT_WHOLE) 
  {
   if (daLight->Type==0)
   {
    if (daAddIt1) 
		PUTVERTEX((&daLight->Source),daLight,0);
    daLight->Selected=daAddIt1;
 
   }
   else
   {
    if (Crossing) 
		daAddIt=daAddIt1 || daAddIt2;
     else 
		 daAddIt=daAddIt1 && daAddIt2;
 
    // Add it if OK!
    if (daAddIt)
    {
     PUTVERTEX((&daLight->Source),daLight,0);
     PUTVERTEX((&daLight->Target),daLight,1);
     daLight->Selected=AddIt;
    }
   }
  }
  else
  {
   if (daAddIt1) 
	   PUTVERTEX((&daLight->Source),daLight,0);
   if (daAddIt2) 
	   PUTVERTEX((&daLight->Target),daLight,1);
  }
    }
 
    GScene->RemoveBufUnselected();
 return HasBeenSel;*/
//return true;
//}
 