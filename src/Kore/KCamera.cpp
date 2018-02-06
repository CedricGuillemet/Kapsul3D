#include "stdafx.h"

//#include "memmgr/mmgr.h"
unsigned int CA_Unique=0;

CKCamera::~CKCamera()
{
//    delete Maths;
    
	delete projection;
	delete modelview;
	delete InverseModel;
	delete InverseProj;

}

CKCamera::CKCamera(void)
{
    //int i;
    Fov=60;
    ResoX=640;
    ResoY=480;
    Source.x=100;

    Selected=false;
    /*
    SrcSelected=false;
    DstSelected=false;    
      */          /*
    for (i=0;i<16;i++)
    {
        projection[i]=1;
        modelview[i]=1;
        inverse[i]=1;
    }
    */
    //ngx=0;
//    ngy=0;
//    Type=0;
//    Maths=new(Math);
//    FreeTargeted=false;
	projection = new CKMatrix;
	modelview = new CKMatrix;
	InverseModel = new CKMatrix;
	InverseProj = new CKMatrix;

    m_speed=0;

/*	m_x = 1;
	m_y = 1;
	m_z = 1;
	m_tx = 0;
	m_ty = 0;
	m_tz = 0;
	*/
    
	angle_a = 0;
	angle_b = 0;
	Unique=CA_Unique++;
	Hided=false;
	DrawHUD=false;
}

CKCamera::CKCamera(CKCamera *daPrev,CKCamera *daNext)
{

    Prev=daPrev;
    Next=daNext;

    //int i;
    Fov=60;
    ResoX=640;
    ResoY=480;
    Source.x=100;

    Selected=false;
    /*
    SrcSelected=false;
    DstSelected=false;    
      */          /*
    for (i=0;i<16;i++)
    {
        projection[i]=1;
        modelview[i]=1;
        inverse[i]=1;
    }
    */
    //ngx=0;
//    ngy=0;
//    Type=0;
//    Maths=new(Math);
//    FreeTargeted=false;
	projection = new CKMatrix;
	modelview = new CKMatrix;
	InverseModel = new CKMatrix;
	InverseProj = new CKMatrix;

    m_speed=0;

/*	m_x = 1;
	m_y = 1;
	m_z = 1;
	m_tx = 0;
	m_ty = 0;
	m_tz = 0;
	*/
    
	angle_a = 0;
	angle_b = 0;
    /*
	last_angle_a = 0;
	last_angle_b = 0;
	speed_a = 0;
	speed_b = 0;
	m_speed = 0.2f;
	old_angle_a = 0;
	old_angle_b = 0;
    */
/*

	m_x=50;
	m_y=50;
	m_z=50;

	m_tx=-10;
	m_ty=-10;
	m_tz=-10;
*/
	//CKCamera.SetCameraTargetPos(-10, -10, -10);
	Unique=CA_Unique++;
	Hided=false;
	DrawHUD=false;
}
/*
void CKCamera::Compute(void)
{
	/*
    double aspect;

    Length=Pythagore3D(Source,Dest);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
	aspect = ResoX;
    aspect/=ResoY;

    if (Type==1)
    {
        glOrtho( -ResoX/2, ResoX/2,-ResoY/2,ResoY/2,0,Length);
    }
    else
    {
        gluPerspective( Fov, aspect, 1, Length);
    }

    glMatrixMode( GL_MODELVIEW );
	glViewport(0,0,ResoX,ResoY);
    glLoadIdentity();
    
    if (FreeTargeted)
    {

        glRotatef(ngx,1,0,0);
        glRotatef(ngy,0,0,1);
        glTranslatef(Source.x,Source.y,Source.z);
    }
    else
    
    {
        gluLookAt(Source.x,Source.y,Source.z,Dest.x,Dest.y,Dest.z, 0.0,0.0,1.0);
    }

    projection->GetFrom(GL_PROJECTION_MATRIX);
    modelview->GetFrom(GL_MODELVIEW_MATRIX);

    modelview->InvertMatrix(InverseModel);
    projection->InvertMatrix(InverseProj);

}
*/

void CKCamera::SetSource(Vertex daSource)
{
    Source=daSource;
    //Compute();
	m_Scene->m_Renderer->SetCamera(this);

}


void CKCamera::SetDest(Vertex daDest)
{
    Dest=daDest;
    //Compute();
	m_Scene->m_Renderer->SetCamera(this);
}


double CKCamera::GetLength(void)
{
    return Length;
}

void CKCamera::BeginMove(void)
{
	OldMx=-1;
	OldMy=-1;
}


void CKCamera::EndDraw(void)
{
	/*
	angle_a=0;
	angle_b=0;

	old_angle_a=0;
	old_angle_b=0;
*/
	OldMx=-1;
	OldMy=-1;

}

// Get coordinates from the mouse
void CKCamera::SetMouse(int mx, int my, int WinWidth, int WinHeight)
{


	if (OldMx==-1)
	{
		angle_b=0;
		angle_a=0;

		OldMx=mx;
		OldMy=my;
	
	}
	else
	{
		angle_b=(float)(mx-OldMx);
		angle_a=(float)(my-OldMy);

		OldMx=mx;
		OldMy=my;

	}
	
	/*
	if (p.x > WinWidth/2) p.x -= 2;
	else if (p.x < WinWidth/2) p.x += 2;

	if (p.y > WinHeight/2) p.y -= 2;
	else if (p.y < WinHeight/2) p.y += 2;
	*/
	//GetCursorPos(&p);
}
/*
// Increase speed of CKCamera
void CCKCamera::IncSpeed(float speed)
{
	m_speed += speed;	
	if (m_speed > 5) m_speed = 5;
}

// Decrease speed of CKCamera
void CCKCamera::DecSpeed(float speed)
{
	m_speed -= speed;
	if (m_speed < -5) m_speed = -5;
}

void CCKCamera::GetNewCoord(float *x, float *y, float *z)
{
	*x = new_x;
	*y = new_y;
	*z = new_z;
}
*/
// Move the CKCamera
void CKCamera::Move()
{
	Source.x = newpos.x;
	Source.y = newpos.y;
	Source.z = newpos.z;

	Dest.x = newpos.x;
	Dest.y = newpos.y+1;
	Dest.z = newpos.z;

}





void CKCamera::SetMousePos(void)
{
	GetCursorPos(&p);
}

void CKCamera::Run(double Percent)
{
    Vertex tmp;
    tmp=(((Dest-Source)*Percent)/100.0f);

    Source+=tmp;
    Dest+=tmp;
}

Vertex CKCamera::GetMaxOf()
{
	Vertex tmp=Source;

	tmp.GetMaxOf(Dest);

	return tmp;
}

Vertex CKCamera::GetMinOf()
{
	Vertex tmp=Source;

	tmp.GetMinOf(Dest);

	return tmp;
}

/*
void CKCamera::LookAt()
{
    gluLookAt(Source.x,Source.y,Source.z,Dest.x,Dest.y,Dest.z, 0,0,1);
}
*/
/*
void CKCamera::operator =(CKCamera *cmpt)
{
    Source=cmpt->Source;
    Dest=cmpt->Dest;
    ResoX=cmpt->ResoX;
    ResoY=cmpt->ResoY;
    Length=cmpt->Length;
    Fov=cmpt->Fov;

    Selected=cmpt->Selected;

    //bool    SrcSelected,DstSelected;

    angle_a=cmpt->angle_a;
    angle_b=cmpt->angle_b; 
    old_angle_a=cmpt->old_angle_a;
    old_angle_b=cmpt->old_angle_b;
    m_speed=cmpt->m_speed;

	OldMx=cmpt->OldMx;
    OldMy=cmpt->OldMy;
	newpos=cmpt->newpos;
	p=cmpt->p;

    *projection=cmpt->projection;
    *InverseModel=cmpt->InverseModel;
    *InverseProj=cmpt->InverseProj;
}
*/
void CKCamera::IsCopyOf(CKCamera *cmpt)
{
    Source=cmpt->Source;
    Dest=cmpt->Dest;
    ResoX=cmpt->ResoX;
	ResoY=cmpt->ResoY;
    Length=cmpt->Length;
    Fov=cmpt->Fov;

    Name=cmpt->Name;

    Selected=false;
    SrcSelected=false;
	DstSelected=false;

    angle_a=cmpt->angle_a;
	angle_b=cmpt->angle_b;
    old_angle_a=cmpt->old_angle_a;
	old_angle_b=cmpt->old_angle_b;
    m_speed=cmpt->m_speed;

	OldMx=cmpt->OldMx;
	OldMy=cmpt->OldMy;
	newpos=cmpt->newpos;
	p=cmpt->p;
    // matrix

    memcpy(projection,cmpt->projection,sizeof(CKMatrix));
	memcpy(modelview,cmpt->modelview,sizeof(CKMatrix));
	memcpy(InverseModel,cmpt->InverseModel,sizeof(CKMatrix));
	memcpy(InverseProj,cmpt->InverseProj,sizeof(CKMatrix));
	Unique=cmpt->Unique;
}

void CKCamera::Strafe(float Percent)
{
	Vertex tmp=(Source-Dest);
	Vertex daVect=CrossProduct(&tmp,&Vertex(0,0,1));
	daVect.Normalize();
	daVect=daVect*(Pythagore3D(Source,Dest)*Percent);
	Source+=daVect;
	Dest+=daVect;
	m_Scene->m_Renderer->SetCamera(this);
}

void CKCamera::MoveUp(float Percent)
{
	Vertex daVect=(Vertex(0,0,1)*Percent*Pythagore3D(Source,Dest));
	Source+=daVect;
	Dest+=daVect;
	m_Scene->m_Renderer->SetCamera(this);
}

void CKCamera::SetCamera()
{
	if (m_Scene!=NULL)
		m_Scene->m_Renderer->SetCamera(this);
}

void CKCamera::SetCamera(CKRenderer *pRenderer)
{
	pRenderer->SetCamera(this);
}