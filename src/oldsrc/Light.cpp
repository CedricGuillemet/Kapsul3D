//---------------------------------------------------------------------------
#include "stdafx.h"

unsigned int L_Unique=0;
//#include "memmgr/mmgr.h"

CLight::CLight(CLight *daPrev,CLight *daNext)
{
    Next=daNext;
    Prev=daPrev;
	Name =new char [32];
	Name[0]=0;
	Radius2=0;
/*
    Selected=false;
    SourceSelected=false;
    TargetSelected=false;
    */
	Unique=L_Unique++;
	Hided=false;
}

CLight::~CLight()
{
	delete [] Name;
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
	//strcpy(Name,cmpt->Name);
    r=cmpt->r;
    g=cmpt->g;
    b=cmpt->b;
    Brightness=cmpt->Brightness;
    
}

void CLight::DrawOmni(Vertex & daViewSize,int ViewInd,int Primitive)
{
	int i;

    if (Source.Selected)
        glColor4f(1,0.5,0,1);
    else
        glColor4f(1,1,0,1);

	glBegin(GL_LINES);
	glVertex3f((daViewSize.vx/20)+Source.vx,(daViewSize.vx/20)+Source.vy,(daViewSize.vx/20)+Source.vz);
	glVertex3f(-(daViewSize.vx/20)+Source.vx,-(daViewSize.vx/20)+Source.vy,-(daViewSize.vx/20)+Source.vz);

	glVertex3f((daViewSize.vx/20)+Source.vx,-(daViewSize.vx/20)+Source.vy,(daViewSize.vx/20)+Source.vz);
	glVertex3f(-(daViewSize.vx/20)+Source.vx,(daViewSize.vx/20)+Source.vy,-(daViewSize.vx/20)+Source.vz);

	glVertex3f((daViewSize.vx/20)+Source.vx,(daViewSize.vx/20)+Source.vy,-(daViewSize.vx/20)+Source.vz);
	glVertex3f(-(daViewSize.vx/20)+Source.vx,-(daViewSize.vx/20)+Source.vy,(daViewSize.vx/20)+Source.vz);

	glVertex3f((daViewSize.vx/20)+Source.vx,-(daViewSize.vx/20)+Source.vy,-(daViewSize.vx/20)+Source.vz);
	glVertex3f(-(daViewSize.vx/20)+Source.vx,(daViewSize.vx/20)+Source.vy,(daViewSize.vx/20)+Source.vz);

	glEnd();

	glPushMatrix();

	glTranslatef(Source.vx,Source.vy,Source.vz);

	glScalef(Radius,Radius,Radius);
	glBegin(GL_LINE_LOOP);
	double temp;

	for (i=0;i<16;i++)
	{
		temp=(i*PI)/8;

		glVertex3f(cos(temp),sin(temp),0);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);

	for (i=0;i<16;i++)
	{
		temp=(i*PI)/8;

		glVertex3f(0,sin(temp),cos(temp));
	}
	glEnd();


	glBegin(GL_LINE_LOOP);

	for (i=0;i<16;i++)
	{
		temp=(i*PI)/8;

		glVertex3f(sin(temp),0,cos(temp));
	}
	glEnd();

	glPopMatrix();
}

void CLight::DrawSpot(Vertex & daViewSize,int ViewInd,int Primitive)
{
	int i;


	GLdouble modelview[16],InverseModel[16];
	GLdouble projection[16],InverseProj[16];
	PrecalcSpot();

	glPushMatrix();	//1

	if (Primitive==1)
	{
		if (Source.Selected)
			glColor4f(1,0.5,0,1);
		else
			glColor4f(1,1,0,1);

		glPointSize(4);

		glBegin(GL_POINTS);
		glVertex3f(Source.vx,Source.vy,Source.vz);
		glEnd();

		if (Target.Selected)
			glColor4f(1,0.5,0,1);
		else
			glColor4f(1,1,0,1);

		glBegin(GL_POINTS);
		glVertex3f(Target.vx,Target.vy,Target.vz);
		glEnd();

	}

	if ( (Source.Selected)&&(Target.Selected))
		glColor4f(1,0.5,0,1);
	else
		glColor4f(1,1,0,1);


	double Length=Pythagore3D(Source,Target);


	glMatrixMode( GL_PROJECTION );

	glPushMatrix(); // 2
	glLoadIdentity();
	gluPerspective( Radius, 1,1, Length);
	glGetDoublev(GL_PROJECTION_MATRIX,projection);
	glPopMatrix(); //2

	glMatrixMode( GL_MODELVIEW );

	glPushMatrix();  //3
	glLoadIdentity();
	gluLookAt(Source.vx,Source.vy,Source.vz,Target.vx,Target.vy,Target.vz, 0.0,0.0,1.0);
	glGetDoublev(GL_MODELVIEW_MATRIX,modelview);
	glPopMatrix();  //3



	InvertMatrix(modelview,InverseModel);
	InvertMatrix(projection,InverseProj);



	glMultMatrixd(InverseModel);
/*
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, -1.0*Length);

	glEnd();
*/
	glMultMatrixd(InverseProj);

//		glScalef(Length*tanRad1,Length*tanRad1,1);
	glScalef(1,1,1);

	glBegin(GL_LINE_STRIP);

	for (i=0;i<100;i++)
	{
	glVertex3f(cos((i*PI)/50), sin((i*PI)/50), 1);
	//glVertex3i(-1, 1, 1);
	}

	glEnd();

	glBegin(GL_LINES);
	glVertex3i(0, 0, -1);
	glVertex3i(0.5, 1, 1);
	
	glVertex3i(0, 0, -1);
	glVertex3i(-0.5, -1, 1);

	glVertex3i(0, 0, -1);
	glVertex3i(1, 0.5, 1);
	
	glVertex3i(0, 0, -1);
	glVertex3i(-1,-0.5, 1);

	glEnd();

	//glPopMatrix(); // 


	glPopMatrix();	//1
}

void CLight::DrawNeon(Vertex & daViewSize,int ViewInd,int Primitive)
{
	int i;


	GLdouble modelview[16],InverseModel[16];
	GLdouble projection[16],InverseProj[16];


	glPushMatrix();	//1

	if (Primitive==1)
	{
		if (Source.Selected)
			glColor4f(1,0.5,0,1);
		else
			glColor4f(1,1,0,1);

		glPointSize(4);

		glBegin(GL_POINTS);
		glVertex3f(Source.vx,Source.vy,Source.vz);
		glEnd();

		if (Target.Selected)
			glColor4f(1,0.5,0,1);
		else
			glColor4f(1,1,0,1);

		glBegin(GL_POINTS);
		glVertex3f(Target.vx,Target.vy,Target.vz);
		glEnd();

	}


	if ( (Source.Selected)&&(Target.Selected))
		glColor4f(1,0.5,0,1);
	else
		glColor4f(1,1,0,1);


	double Length=Pythagore3D(Source,Target);

	glMatrixMode( GL_PROJECTION );

	glPushMatrix(); // 2
	glLoadIdentity();
	gluPerspective( Radius, 1,1, Length);
	glGetDoublev(GL_PROJECTION_MATRIX,projection);
	glPopMatrix(); //2

	glMatrixMode( GL_MODELVIEW );

	glPushMatrix();  //3
	glLoadIdentity();
	gluLookAt(Source.vx,Source.vy,Source.vz,Target.vx,Target.vy,Target.vz, 0.0,0.0,1.0);
	glGetDoublev(GL_MODELVIEW_MATRIX,modelview);
	glPopMatrix();  //3



	InvertMatrix(modelview,InverseModel);
	InvertMatrix(projection,InverseProj);



	glMultMatrixd(InverseModel);
/*
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, -1.0*Length);

	glEnd();
*/
	//glMultMatrixd(InverseProj);

//		glScalef(Length*tanRad1,Length*tanRad1,1);
	glScalef(Radius,Radius,1);

	glBegin(GL_LINE_STRIP);
	for (i=0;i<100;i++)
		glVertex3f(cos((i*PI)/50), sin((i*PI)/50), -Length);
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (i=0;i<100;i++)
		glVertex3f(cos((i*PI)/50), sin((i*PI)/50), 0);
	glEnd();

	glBegin(GL_LINES);
	glVertex3i(1, 0, 0);
	glVertex3i(1, 0, -Length);

	glVertex3i(-1, 0, 0);
	glVertex3i(-1, 0, -Length);

	glVertex3i(0, -1, 0);
	glVertex3i(0, -1, -Length);

	glVertex3i(0, 1, 0);
	glVertex3i(0, 1, -Length);

	glEnd();
	
	glPopMatrix();
}

void CLight::Draw(Vertex & daViewSize,int ViewInd,int Primitive)
{
	int i;
	Vertex CircleHui;
	
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

		Length=sqrt((Target.vx-Source.vx)*(Target.vx-Source.vx)+
			(Target.vy-Source.vy)*(Target.vy-Source.vy)+
			(Target.vz-Source.vz)*(Target.vz-Source.vz) );
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


	memcpy(Name,cmpt->Name,32);

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