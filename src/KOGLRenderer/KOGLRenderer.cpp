// KOGLRenderer.cpp : Defines the entry point for the DLL application.
//
#include "stdafx.h"
#include "KOGLRenderer.h"
#include "KOGLParam.h"

// This is the constructor of a class that has been exported.
// see KOGLRenderer.h for the class definition


BEGIN_MESSAGE_MAP(CKOGLRendererApp, CWinApp)
	//{{AFX_MSG_MAP(CKOGLRendererApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKOGLRendererApp construction

CKOGLRendererApp::CKOGLRendererApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CKOGLRendererApp object

CKOGLRendererApp theApp;



PFNGLACTIVETEXTUREARBPROC glActiveTextureARB=NULL;
PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB=NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB=NULL;

/*
CKOGLRenderer::CKOGLRenderer()
{
	MessageBox(NULL,"Default Renderer Constructor","Error",MB_OK);
}
*/
CKOGLRenderer::CKOGLRenderer(CKScene *Scene) 
{ 
	Primitive=1;

	InitBase(Scene);
}

CKOGLRenderer::~CKOGLRenderer()
{
	DeleteContext();
	if (font!=NULL) delete font;
}

CString CKOGLRenderer::GetRendererName()
{
	return "Default OpenGL renderer (V0.1)";
}

HWND CKOGLRenderer::CreateConfigWindow(HWND Parent)
{
	SWITCH_RESOURCE;

	//MessageBox(NULL,"OK","OK",MB_OK);
	//AfxSetResourceHandle(theApp.m_hInstance);
	
	Params.Create(MAKEINTRESOURCE(IDD_KOGLPARAM),CWnd::FromHandle(Parent));
	
	return Params.m_hWnd;
}

void CKOGLRenderer::DeleteContext()
{
// specify the target DeviceContext (window) of the subsequent OGL calls
    wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);

// release definitely OGL Rendering Context
	if (m_hRC!=NULL) ::wglDeleteContext(m_hRC);

// destroy Win Device Context
	//if(m_pCDC) delete m_pCDC;
}


void CKOGLRenderer::InitContext(HWND window)
{
	int         n;
	m_hWnd=window;
    
// initialize the private member
	m_pCDC= new CClientDC(CWnd::FromHandle(m_hWnd));

// choose the requested video mode
	static PIXELFORMATDESCRIPTOR pfd = 
	{
        sizeof(PIXELFORMATDESCRIPTOR),	// size of this pfd
        1,								// version number
        PFD_DRAW_TO_WINDOW |			// support window
        PFD_SUPPORT_OPENGL |			// support OpenGL
        PFD_DOUBLEBUFFER,				// double buffered
        PFD_TYPE_RGBA,                  // RGBA type
        24,                             // 24-bit color depth
        0, 0, 0, 0, 0, 0,               // color bits ignored
        0,                              // no alpha buffer
        0,                              // shift bit ignored
        0,                              // no accumulation buffer
        0, 0, 0, 0,                     // accum bits ignored
        32,                             // 32-bit z-buffer
        0,                              // no stencil buffer
        0,                              // no auxiliary buffer
        PFD_MAIN_PLANE,                 // main layer
        0,                              // reserved
        0, 0, 0                         // layer masks ignored
    };
// let the user change some parameters if he wants

// ask the system for such video mode
    ASSERT(m_pCDC != NULL);
    int pixelformat;
	if ( (pixelformat = ChoosePixelFormat(m_pCDC->GetSafeHdc(), &pfd)) == 0 )
    {
        AfxMessageBox("ChoosePixelFormat failed");
        return ;
    }

// try to set this video mode    
	if (SetPixelFormat(m_pCDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
    {
// the requested video mode is not available so get a default one
        pixelformat = 1;	
		if (DescribePixelFormat(m_pCDC->GetSafeHdc(), pixelformat, sizeof(PIXELFORMATDESCRIPTOR), &pfd)==0)
		{
// neither the requested nor the default are available: fail
			AfxMessageBox("SetPixelFormat failed (no OpenGL compatible video mode)");
			return ;
		}
    }	
// ask the system if the video mode is supported
    n=::GetPixelFormat(m_pCDC->GetSafeHdc());
    ::DescribePixelFormat(m_pCDC->GetSafeHdc(),n,sizeof(pfd),&pfd);

// create a palette if the requested video mode has 256 colors (indexed mode)
//    CreateRGBPalette();

// link the Win Device Context with the OGL Rendering Context
    m_hRC = wglCreateContext(m_pCDC->GetSafeHdc());

// specify the target DeviceContext (window) of the subsequent OGL calls
    wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);

//	PreCalc();

// performs default setting of rendering mode,etc..
	glEnable(GL_DEPTH_TEST);	// Z-Buffer
	glEnable(GL_CULL_FACE);		// Backface Culling
	glEnable(GL_TEXTURE_2D);	// Texturing
		
	// Solid polygons
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);


	font=new font_t;


	// Init extensions used    

	if (!glActiveTextureARB || !glMultiTexCoord2fARB || !glClientActiveTextureARB)
	{
		glActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC) wglGetProcAddress("glActiveTextureARB");
		glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC) wglGetProcAddress("glMultiTexCoord2fARB");
		glClientActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC) wglGetProcAddress("glClientActiveTextureARB");

	// Verify pointers
	if (!glActiveTextureARB || !glMultiTexCoord2fARB || !glClientActiveTextureARB)
		return ;
	}
	// sphere 

	// Create Grid OpenGL List

	int i;

    glNewList(2,GL_COMPILE);

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

	glEndList();

		
}
void CKOGLRenderer::BeginRender()
{

// specify the target DeviceContext of the subsequent OGL calls
	wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);

// clear background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CKOGLRenderer::EndRender()
{
// execute OGL commands (flush the OGL graphical pipeline)
	glFinish();

// if double buffering is used it's time to swap the buffers
	SwapBuffers(m_pCDC->GetSafeHdc());
}

void CKOGLRenderer::ExtractFrustum()
{
   float   proj[16];
   float   modl[16];
   float   clip[16];
   float   t;

   /* Get the current PROJECTION matrix from OpenGL */
   glGetFloatv( GL_PROJECTION_MATRIX, proj );

   /* Get the current MODELVIEW matrix from OpenGL */
   glGetFloatv( GL_MODELVIEW_MATRIX, modl );

   /* Combine the two matrices (multiply projection by modelview) */
   clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12];
   clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13];
   clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14];
   clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15];

   clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
   clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13];
   clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14];
   clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15];

   clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12];
   clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13];
   clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14];
   clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15];

   clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12];
   clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13];
   clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14];
   clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15];

   /* Extract the numbers for the RIGHT plane */
   frustum[0][0] = clip[ 3] - clip[ 0];
   frustum[0][1] = clip[ 7] - clip[ 4];
   frustum[0][2] = clip[11] - clip[ 8];
   frustum[0][3] = clip[15] - clip[12];

   /* Normalize the result */
   t = sqrt( frustum[0][0] * frustum[0][0] + frustum[0][1] * frustum[0][1] + frustum[0][2] * frustum[0][2] );
   frustum[0][0] /= t;
   frustum[0][1] /= t;
   frustum[0][2] /= t;
   frustum[0][3] /= t;

   /* Extract the numbers for the LEFT plane */
   frustum[1][0] = clip[ 3] + clip[ 0];
   frustum[1][1] = clip[ 7] + clip[ 4];
   frustum[1][2] = clip[11] + clip[ 8];
   frustum[1][3] = clip[15] + clip[12];

   /* Normalize the result */
   t = sqrt( frustum[1][0] * frustum[1][0] + frustum[1][1] * frustum[1][1] + frustum[1][2] * frustum[1][2] );
   frustum[1][0] /= t;
   frustum[1][1] /= t;
   frustum[1][2] /= t;
   frustum[1][3] /= t;

   /* Extract the BOTTOM plane */
   frustum[2][0] = clip[ 3] + clip[ 1];
   frustum[2][1] = clip[ 7] + clip[ 5];
   frustum[2][2] = clip[11] + clip[ 9];
   frustum[2][3] = clip[15] + clip[13];

   /* Normalize the result */
   t = sqrt( frustum[2][0] * frustum[2][0] + frustum[2][1] * frustum[2][1] + frustum[2][2] * frustum[2][2] );
   frustum[2][0] /= t;
   frustum[2][1] /= t;
   frustum[2][2] /= t;
   frustum[2][3] /= t;

   /* Extract the TOP plane */
   frustum[3][0] = clip[ 3] - clip[ 1];
   frustum[3][1] = clip[ 7] - clip[ 5];
   frustum[3][2] = clip[11] - clip[ 9];
   frustum[3][3] = clip[15] - clip[13];

   /* Normalize the result */
   t = sqrt( frustum[3][0] * frustum[3][0] + frustum[3][1] * frustum[3][1] + frustum[3][2] * frustum[3][2] );
   frustum[3][0] /= t;
   frustum[3][1] /= t;
   frustum[3][2] /= t;
   frustum[3][3] /= t;

   /* Extract the FAR plane */
   frustum[4][0] = clip[ 3] - clip[ 2];
   frustum[4][1] = clip[ 7] - clip[ 6];
   frustum[4][2] = clip[11] - clip[10];
   frustum[4][3] = clip[15] - clip[14];

   /* Normalize the result */
   t = sqrt( frustum[4][0] * frustum[4][0] + frustum[4][1] * frustum[4][1] + frustum[4][2] * frustum[4][2] );
   frustum[4][0] /= t;
   frustum[4][1] /= t;
   frustum[4][2] /= t;
   frustum[4][3] /= t;

   /* Extract the NEAR plane */
   frustum[5][0] = clip[ 3] + clip[ 2];
   frustum[5][1] = clip[ 7] + clip[ 6];
   frustum[5][2] = clip[11] + clip[10];
   frustum[5][3] = clip[15] + clip[14];

   /* Normalize the result */
   t = sqrt( frustum[5][0] * frustum[5][0] + frustum[5][1] * frustum[5][1] + frustum[5][2] * frustum[5][2] );
   frustum[5][0] /= t;
   frustum[5][1] /= t;
   frustum[5][2] /= t;
   frustum[5][3] /= t;
}



int CKOGLRenderer::CubeInFrustum( Vertex &Src, Vertex &Size )
{
   int p;
   int c;
   int c2 = 0;

   for( p = 0; p < 6; p++ )
   {
      c = 0;
      if( frustum[p][0] * (Src.x - Size.x) + frustum[p][1] * (Src.y - Size.y) + frustum[p][2] * (Src.z - Size.z) + frustum[p][3] > 0 )
         c++;
      if( frustum[p][0] * (Src.x + Size.x) + frustum[p][1] * (Src.y - Size.y) + frustum[p][2] * (Src.z - Size.z) + frustum[p][3] > 0 )
         c++;
      if( frustum[p][0] * (Src.x - Size.x) + frustum[p][1] * (Src.y + Size.y) + frustum[p][2] * (Src.z - Size.z) + frustum[p][3] > 0 )
         c++;
      if( frustum[p][0] * (Src.x + Size.x) + frustum[p][1] * (Src.y + Size.y) + frustum[p][2] * (Src.z - Size.z) + frustum[p][3] > 0 )
         c++;
      if( frustum[p][0] * (Src.x - Size.x) + frustum[p][1] * (Src.y - Size.y) + frustum[p][2] * (Src.z + Size.z) + frustum[p][3] > 0 )
         c++;
      if( frustum[p][0] * (Src.x + Size.x) + frustum[p][1] * (Src.y - Size.y) + frustum[p][2] * (Src.z + Size.z) + frustum[p][3] > 0 )
         c++;
      if( frustum[p][0] * (Src.x - Size.x) + frustum[p][1] * (Src.y + Size.y) + frustum[p][2] * (Src.z + Size.z) + frustum[p][3] > 0 )
         c++;
      if( frustum[p][0] * (Src.x + Size.x) + frustum[p][1] * (Src.y + Size.y) + frustum[p][2] * (Src.z + Size.z) + frustum[p][3] > 0 )
         c++;
      if( c == 0 )
         return 0;
      if( c == 8 )
         c2++;
   }
   return (c2 == 6) ? 2 : 1;
}




void CKOGLRenderer::DrawGrid(int ViewInd)
{
    int tmpm,i,j;
    int indm;
    double daPow;
	int nbgridx,nbgridy;
	Vertex daViewSize,start;

	glPushMatrix();	//1


	daViewSize=m_Scene->ViewSize[ViewInd];

	double tmpsqr=m_Scene->SnapVal.x*m_Scene->SnapVal.x;

    nbgridx=(int)ceil(( (2*daViewSize.x) / (tmpsqr) ) );
    nbgridy=(int)ceil(( (2*daViewSize.y) / (tmpsqr) ) );



    tmpm=nbgridx;
    indm=1;


    Vertex tmp1,tmp2;
    while (nbgridx>m_Scene->SnapVal.x)
    {
        indm++;

        nbgridx/=(int)(m_Scene->SnapVal.x);
        nbgridy/=(int)(m_Scene->SnapVal.y);
    }


    daPow=pow(m_Scene->SnapVal.x,(indm-1));
	if (m_Scene->ViewType[ViewInd]==VIEWTYPE_PERSPECTIVE)
	{
		tmp1=m_Scene->Perspective[ViewInd].Dest;
		tmp2=m_Scene->Perspective[ViewInd].Dest;
	}
	else
	if (m_Scene->ViewType[ViewInd]==VIEWTYPE_CAMERA)
	{
		tmp1=m_Scene->cam[ViewInd]->Dest;
		tmp2=m_Scene->cam[ViewInd]->Dest;
	}
	else
	{
		tmp1=m_Scene->ViewPos[ViewInd];
		tmp2=m_Scene->ViewPos[ViewInd];

		if ((m_Scene->ViewNg[ViewInd].x==0)&&(m_Scene->ViewNg[ViewInd].y==0)&&(m_Scene->ViewNg[ViewInd].z==0)) 
		{
			tmp2.x=m_Scene->ViewPos[ViewInd].x;
			tmp2.y=m_Scene->ViewPos[ViewInd].y;
		}
		if ((m_Scene->ViewNg[ViewInd].x==-90)&&(m_Scene->ViewNg[ViewInd].y==0)&&(m_Scene->ViewNg[ViewInd].z==0)) 
		{
			tmp2.x=m_Scene->ViewPos[ViewInd].x;
			tmp2.y=m_Scene->ViewPos[ViewInd].z;
		}
		if ((m_Scene->ViewNg[ViewInd].x==-90)&&(m_Scene->ViewNg[ViewInd].y==0)&&(m_Scene->ViewNg[ViewInd].z==90)) 
		{
			tmp2.x=-m_Scene->ViewPos[ViewInd].y;
			tmp2.y=m_Scene->ViewPos[ViewInd].z;
		}
		if ((m_Scene->ViewNg[ViewInd].x==0)&&(m_Scene->ViewNg[ViewInd].y==180)&&(m_Scene->ViewNg[ViewInd].z==180)) 
		{
			tmp2.x=m_Scene->ViewPos[ViewInd].x;
			tmp2.y=-m_Scene->ViewPos[ViewInd].y;
		}
		if ((m_Scene->ViewNg[ViewInd].x==90)&&(m_Scene->ViewNg[ViewInd].y==180)&&(m_Scene->ViewNg[ViewInd].z==0))
		{
			tmp2.x=-m_Scene->ViewPos[ViewInd].x;
			tmp2.y=m_Scene->ViewPos[ViewInd].z;
		}
		if ((m_Scene->ViewNg[ViewInd].x==270)&&(m_Scene->ViewNg[ViewInd].y==0)&&(m_Scene->ViewNg[ViewInd].z==270))
		{
			tmp2.x=m_Scene->ViewPos[ViewInd].y;
			tmp2.y=m_Scene->ViewPos[ViewInd].z;
		}
	}

    tmp2-=daViewSize;

    tmp2.x-=(tmpsqr*daPow);
    tmp2.y-=(tmpsqr*daPow);

    for (i=1;i<indm;i++)
    {
        tmp2.x/=(m_Scene->SnapVal.x);
        tmp2.y/=(m_Scene->SnapVal.y);

    }


	if ((m_Scene->ViewType[ViewInd]==VIEWTYPE_PERSPECTIVE)||(m_Scene->ViewType[ViewInd]==VIEWTYPE_CAMERA))
	{
		start.x=+tmp2.x-fmod(tmp2.x,(tmpsqr));
		start.y=+tmp2.y-fmod(tmp2.y,(tmpsqr));
		start.z=tmp2.z-fmod(tmp2.z,(tmpsqr*tmpsqr));
	}
	else
	{
		start.x=+tmp2.x-fmod(tmp2.x,(tmpsqr));
		start.y=+tmp2.y-fmod(tmp2.y,(tmpsqr));
		start.z=0;

		if ((fmod(m_Scene->ViewNg[ViewInd].y,180)==0)&&(fmod(m_Scene->ViewNg[ViewInd].x,90)==0)&&(fmod(m_Scene->ViewNg[ViewInd].z,90)==0)&&(m_Scene->ViewType[ViewInd]!=VIEWTYPE_CAMERA))
		{
			glRotatef(-m_Scene->ViewNg[ViewInd].z,0,0,1);
			glRotatef(-m_Scene->ViewNg[ViewInd].y,0,1,0);
			glRotatef(-m_Scene->ViewNg[ViewInd].x,1,0,0);
		}
	}
    

	if ((m_Scene->ViewType[ViewInd]==VIEWTYPE_PERSPECTIVE)||(m_Scene->ViewType[ViewInd]==VIEWTYPE_CAMERA))
	{
		// perspective

		// small grid

		glPushMatrix(); //2
		glScalef(daPow,daPow,daPow);

		glTranslatef(start.x,start.y,start.z);

		
		for (j=0;j<8;j++)
		{
			glPushMatrix(); // 3
			{
				for (i=0;i<m_Scene->SnapVal.x;i++)
				{
					glCallList(grid);

					glTranslatef(tmpsqr,0,0);
				}
			}
			glPopMatrix(); // 1
			glTranslatef(0,tmpsqr,0);
		}
		glPopMatrix(); //2
		
		// big grid
		
		start.x=tmp2.x-fmod(tmp2.x,(tmpsqr*tmpsqr));
		start.y=tmp2.y-fmod(tmp2.y,(tmpsqr*tmpsqr));
		start.z=tmp2.z-fmod(tmp2.z,(tmpsqr*tmpsqr));

		//glScalef(daPow,daPow,1);//daPow);

		glScalef(tmpsqr,tmpsqr,1);
		glTranslatef(start.x,start.y,start.z);
		glTranslatef(-tmpsqr*4,-tmpsqr*4,0);
		
		glPushMatrix(); // 4
		for (j=0;j<8;j++)
		{
			glPushMatrix(); // 5
			{
				for (i=0;i<8;i++)
				{
					glCallList(grid);

					glTranslatef(tmpsqr,0,0);
				}
			}
			glPopMatrix(); // 3
			glTranslatef(0,tmpsqr,0);
		}
		glPopMatrix(); //4
	}
	else
	{
		// iso
		glScalef(daPow,daPow,daPow);

		glTranslatef(start.x,start.y,0);

		glPushMatrix(); //6
		for (j=0;j<=(nbgridy+2);j++)
		{
			glPushMatrix(); // 7
			{
				for (i=0;i<=(nbgridy+2);i++)
				{
					glCallList(grid);

					glTranslatef(tmpsqr,0,0);
				}
			}
			glPopMatrix(); // 5
			glTranslatef(0,tmpsqr,0);
		}
		glPopMatrix(); //6
	}
    // --

    glPopMatrix(); //7
}

void  CKOGLRenderer::DrawScene(int daState,int WichOne)
{
    CKCamera *daCam;
    CKShape *daShape;
    CKMesh *daMesh;
    CKSkeleton *daSkel;
	CKPatch *daPatch;
	
	int retGenDraw;

	ExtractFrustum();

    glPushMatrix(); 


	if (m_Plugin==NULL)
	{
		retGenDraw=PLUGIN_ALL;
	}
	else
	{
		retGenDraw=m_Plugin->OwnerDraw(this,WichOne);
	}

	int dViewType=GetViewType(WichOne);

	if (m_Scene->m_bkTop->Active)
	{
		if ((dViewType==1)||(dViewType==4))
		{
			glDisable(GL_DEPTH_TEST);
			glEnable(GL_TEXTURE_2D);
			glBlendFunc(GL_SRC_COLOR,GL_DST_COLOR);	
			glColor4f(m_Scene->m_bkTop->Opacity,m_Scene->m_bkTop->Opacity,m_Scene->m_bkTop->Opacity,m_Scene->m_bkTop->Opacity);
			glEnable(GL_BLEND);
			m_Scene->m_bkTop->tex->Bind();
			glBegin(GL_QUADS);

			glTexCoord2f(0,0);
			glVertex3f(m_Scene->m_bkTop->Origin.x,m_Scene->m_bkTop->Origin.y,0);
			glTexCoord2f(1,0);
			glVertex3f(m_Scene->m_bkTop->Origin.x+m_Scene->m_bkTop->Size.x,m_Scene->m_bkTop->Origin.y,0);
			glTexCoord2f(1,1);
			glVertex3f(m_Scene->m_bkTop->Origin.x+m_Scene->m_bkTop->Size.x,m_Scene->m_bkTop->Origin.y+m_Scene->m_bkTop->Size.y,0);
			glTexCoord2f(0,1);
			glVertex3f(m_Scene->m_bkTop->Origin.x,m_Scene->m_bkTop->Origin.y+m_Scene->m_bkTop->Size.y,0);
			glEnd();
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_DEPTH_TEST);
		}
	}

	if (m_Scene->m_bkLeft->Active)
	{
		if ((dViewType==3)||(dViewType==6))
		{
			glDisable(GL_DEPTH_TEST);
			glEnable(GL_TEXTURE_2D);
			glBlendFunc(GL_SRC_COLOR,GL_DST_COLOR);	
			glColor4f(m_Scene->m_bkLeft->Opacity,m_Scene->m_bkLeft->Opacity,m_Scene->m_bkLeft->Opacity,m_Scene->m_bkLeft->Opacity);
			glEnable(GL_BLEND);
			m_Scene->m_bkLeft->tex->Bind();
			glBegin(GL_QUADS);

			glTexCoord2f(0,0);
			glVertex3f(0,m_Scene->m_bkLeft->Origin.x,m_Scene->m_bkLeft->Origin.y);
			glTexCoord2f(1,0);
			glVertex3f(0,m_Scene->m_bkLeft->Origin.x+m_Scene->m_bkLeft->Size.x,m_Scene->m_bkLeft->Origin.y);
			glTexCoord2f(1,1);
			glVertex3f(0,m_Scene->m_bkLeft->Origin.x+m_Scene->m_bkLeft->Size.x,m_Scene->m_bkLeft->Origin.y+m_Scene->m_bkLeft->Size.y);
			glTexCoord2f(0,1);
			glVertex3f(0,m_Scene->m_bkLeft->Origin.x,m_Scene->m_bkLeft->Origin.y+m_Scene->m_bkLeft->Size.y);
			glEnd();
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_DEPTH_TEST);
		}
	}

	if (m_Scene->m_bkFront->Active)
	{
		if ((dViewType==2)||(dViewType==5))
		{
			glDisable(GL_DEPTH_TEST);
			glEnable(GL_TEXTURE_2D);
			glBlendFunc(GL_SRC_COLOR,GL_DST_COLOR);	
			glColor4f(m_Scene->m_bkFront->Opacity,m_Scene->m_bkFront->Opacity,m_Scene->m_bkFront->Opacity,m_Scene->m_bkFront->Opacity);
			glEnable(GL_BLEND);
			m_Scene->m_bkFront->tex->Bind();
			glBegin(GL_QUADS);

			glTexCoord2f(0,0);
			glVertex3f(m_Scene->m_bkFront->Origin.x,0,m_Scene->m_bkFront->Origin.y);
			glTexCoord2f(1,0);
			glVertex3f(m_Scene->m_bkFront->Origin.x+m_Scene->m_bkFront->Size.x,0,m_Scene->m_bkFront->Origin.y);
			glTexCoord2f(1,1);
			glVertex3f(m_Scene->m_bkFront->Origin.x+m_Scene->m_bkFront->Size.x,0,m_Scene->m_bkFront->Origin.y+m_Scene->m_bkFront->Size.y);
			glTexCoord2f(0,1);
			glVertex3f(m_Scene->m_bkFront->Origin.x,0,m_Scene->m_bkFront->Origin.y+m_Scene->m_bkFront->Size.y);
			glEnd();
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_DEPTH_TEST);
		}
	}

	// Grid

	if ((retGenDraw&PLUGIN_GRID)&&(m_Scene->m_GridVisible[WichOne]))
	{
		grid=glGenLists(1);
		glNewList(grid,GL_COMPILE);
		BuildGrid(m_Scene->SnapVal,Vertex(0,0,0));
		glEndList();

		if ((m_Scene->ViewType[WichOne]==VIEWTYPE_PERSPECTIVE)||(m_Scene->ViewType[WichOne]==VIEWTYPE_CAMERA))
		{
			if (m_Option->GetShowGridCamera())
			{
				DrawGrid(WichOne);
			}
		}
		else
		{
			DrawGrid(WichOne);
		}
	}

	// erase Depth buffer if wanted


	if ((m_Scene->ViewType[WichOne]==VIEWTYPE_PERSPECTIVE)||(m_Scene->ViewType[WichOne]==VIEWTYPE_CAMERA))
	{
		// camera/perspective
		if (m_Option->GridBehindCamera())
		{
			glClearColor(0,0,0,0);
			glClear(GL_DEPTH_BUFFER_BIT);
		}
	}
	else
	{
		// iso views
		if (m_Option->GridBehindIso())
		{
			glClearColor(0,0,0,0);
			glClear(GL_DEPTH_BUFFER_BIT);
		}
	}

	// Axis

	/*
	if (retGenDraw&PLUGIN_AXIS)
	{
		DrawAxis(WichOne);
	}
	*/

    // CKCamera

	if (retGenDraw&PLUGIN_CAMERA)
	{
		daCam=m_Scene->FirstCam;
		while (daCam!=NULL)
		{
			SetCamera(daCam);

			if (daCam!=m_Scene->cam[WichOne])
			{
				
				if (!daCam->Hided) DrawCamera(daCam);
			}

			daCam=daCam->Next;
		}
	}

    // CKShape

	if (retGenDraw&PLUGIN_SHAPE)
	{
		

		daShape=m_Scene->FirstShape;
		while(daShape!=NULL)
		{
			if (!daShape->Hided)
			{
				DrawShape(daShape);
				if (daShape->m_Mesh!=NULL) 
				{
					daShape->GenerateMesh(m_Scene->FirstShape);
					DrawMesh(daShape->m_Mesh,daState,m_Scene->FrameInd);
				}
			}
			daShape=daShape->Next;
		}
	}

    // CKMesh

	if (retGenDraw&PLUGIN_MESH)
	{
		daMesh=m_Scene->FirstMesh;
		while(daMesh!=NULL)
		{
			if (!daMesh->Hided) 
			{
				if (CubeInFrustum(daMesh->Min,(daMesh->Max-daMesh->Min)))
				{
					DrawMesh(daMesh,daState,daMesh->FrameInd);
					//nb2obj++;
				}
			}
			daMesh=daMesh->Next;
		}
	}

	// patch
	

	if (retGenDraw&PLUGIN_PATCH)
	{
		daPatch=m_Scene->FirstPatch;
		while(daPatch!=NULL)
		{
			if (!daPatch->Hided) 
			{
				if (CubeInFrustum(daPatch->Min,(daPatch->Max-daPatch->Min)))
				{
					DrawPatch(daPatch,daState);
					//nb2patch++;
				}
			}
			daPatch=daPatch->Next;
		}
	}

    // CKSkeletons

	if (retGenDraw&PLUGIN_SKELETON)
	{
		daSkel=m_Scene->FirstSkel;
		while (daSkel!=NULL)
		{
			if (!daSkel->Hided) DrawSkeleton(daSkel);
			daSkel=daSkel->Next;
		}
	}

	// entities
	if (retGenDraw&PLUGIN_ENTITY)
	{
		for (CKEntity *daEnt=m_Scene->FirstEntity;daEnt!=NULL;daEnt=daEnt->Next)
		{
			if (!daEnt->Hided) 
			{
				if (CubeInFrustum(daEnt->Min,(daEnt->Max-daEnt->Min)))
				{
					daEnt->OwnerDraw(daState,WichOne);
				}
			}
		}
	}


	DrawSelection();
		

    glPopMatrix();	//3

	if (m_Scene->SomeThingSel)
	{
		switch (m_Scene->ViewType[WichOne])
		{
			case VIEWTYPE_PERSPECTIVE:
			case VIEWTYPE_CAMERA:
				if (m_Option->GetShowHandlesCamera())
					DrawHandles(&m_Scene->Hand3D,WichOne,m_Scene->HookMinSel,m_Scene->HookMaxSel);
				break;
			case VIEWTYPE_ORTHO:
				DrawHandles(&m_Scene->Hand3D,WichOne,m_Scene->HookMinSel,m_Scene->HookMaxSel);
				break;
		}
	}
}


void  CKOGLRenderer::BuildGrid(Vertex Snap, Vertex Start)
{
    double i;

    glBegin(GL_LINES);


    for (i=Start.x;i<=(Start.x+(Snap.x*Snap.x));i+=Snap.x)
    {
        if ( (i==Start.x) || (i==(Start.x+(Snap.x*Snap.x))))
			glColor3ub(m_Option->GridColor1()->bBlue,m_Option->GridColor1()->bGreen,m_Option->GridColor1()->bRed);
        else
			glColor3ub(m_Option->GridColor2()->bBlue,m_Option->GridColor2()->bGreen,m_Option->GridColor2()->bRed);

        glVertex3f((i),(Start.y),0);
        glVertex3f((i),(Start.y+(Snap.y*Snap.y)),0);
    }
    for (i=Start.y;i<=(Start.y+(Snap.y*Snap.y));i+=Snap.y)
    {
        if ((i==Start.y)||(i==(Start.y+(Snap.y*Snap.y))))
			glColor3ub(m_Option->GridColor1()->bBlue,m_Option->GridColor1()->bGreen,m_Option->GridColor1()->bRed);
        else
			glColor3ub(m_Option->GridColor2()->bBlue,m_Option->GridColor2()->bGreen,m_Option->GridColor2()->bRed);


        glVertex3f((Start.x),(i),0);
        glVertex3f((Start.x+(Snap.x*Snap.x)),(i),0);
    }
    glEnd();
}

Vertex CKOGLRenderer::GetIsoCoord(int X, int Y,int ViewInd)
{
	int realy;
    Vertex value;
    GLdouble ax,ay,az;
	double tmp1,tmp2,tmp3;
    
	if (m_Scene->FullScreen)
	{
		realy=viewport[ViewInd][3]-(GLint)Y;
	}
	else 
	{
		switch(m_Scene->daViewMode)
		{
			
			case VIEW_MODE1x2a:
				if (m_Scene->ViewEnd[ViewInd].y==m_Scene->Height)
					realy=viewport[ViewInd][3]-(GLint)Y;
				else
					realy=viewport[ViewInd][3]-(GLint)Y+(m_Scene->Height/2);
				break;
			case VIEW_MODE1x3a:
				if (m_Scene->ViewEnd[ViewInd].y==m_Scene->Height)
					realy=viewport[ViewInd][3]-(GLint)Y;
				else
					realy=viewport[ViewInd][3]-(GLint)Y+(2*(m_Scene->Height/3));
				break;

			default:

				realy=viewport[ViewInd][3]-(GLint)Y+(m_Scene->Height/2);
				break;
		}


	}
    gluProject(0,0,0,mvmatrix[ViewInd], projmatrix[ViewInd], viewport[ViewInd], &ax, &ay, &az);
    gluUnProject((GLdouble)X,realy,(GLdouble)az,mvmatrix[ViewInd],projmatrix[ViewInd],viewport[ViewInd],&tmp1,&tmp2,&tmp3);
	value.x=tmp1;
	value.y=tmp2;
	value.z=tmp3;
//    temp=value;
    return value;

}

Vertex CKOGLRenderer::GetIsoCoord(int X, int Y,int ViewInd,Vertex Prj)
{
	int realy;
    Vertex value;
    GLdouble ax,ay,az;
	double tmp1,tmp2,tmp3;
    
	if (m_Scene->FullScreen)
	{
		realy=viewport[ViewInd][3]-(GLint)Y;
	}
	else 
	{
		switch(m_Scene->daViewMode)
		{
			
			case VIEW_MODE1x2a:
				if (m_Scene->ViewEnd[ViewInd].y==m_Scene->Height)
					realy=viewport[ViewInd][3]-(GLint)Y;
				else
					realy=viewport[ViewInd][3]-(GLint)Y+(m_Scene->Height/2);
				break;
			case VIEW_MODE1x3a:
				if (m_Scene->ViewEnd[ViewInd].y==m_Scene->Height)
					realy=viewport[ViewInd][3]-(GLint)Y;
				else
					realy=viewport[ViewInd][3]-(GLint)Y+(2*(m_Scene->Height/3));
				break;

			default:

				realy=viewport[ViewInd][3]-(GLint)Y+(m_Scene->Height/2);
				break;
		}


	}
    gluProject(Prj.x,Prj.y,Prj.z,mvmatrix[ViewInd], projmatrix[ViewInd], viewport[ViewInd], &ax, &ay, &az);
    gluUnProject((GLdouble)X,realy,(GLdouble)az,mvmatrix[ViewInd],projmatrix[ViewInd],viewport[ViewInd],&tmp1,&tmp2,&tmp3);
	value.x=tmp1;
	value.y=tmp2;
	value.z=tmp3;
//    temp=value;
    return value;

}

Vertex  CKOGLRenderer::GetIsoCoord(MYPOINT pt,int ViewInd)
{
	int realy;
    Vertex value;
    GLdouble ax,ay,az;
	double tmp1,tmp2,tmp3;

    int X=pt.x;
    int Y=pt.y;
    
	if (m_Scene->FullScreen)
	{
		realy=viewport[ViewInd][3]-(GLint)Y;
	}
	else 
	{
		switch(m_Scene->daViewMode)
		{
			
			case VIEW_MODE1x2a:
				if (m_Scene->ViewEnd[ViewInd].y==m_Scene->Height)
					realy=viewport[ViewInd][3]-(GLint)Y;
				else
					realy=viewport[ViewInd][3]-(GLint)Y+(m_Scene->Height/2);
				break;
			case VIEW_MODE1x3a:
				if (m_Scene->ViewEnd[ViewInd].y==m_Scene->Height)
					realy=viewport[ViewInd][3]-(GLint)Y;
				else
					realy=viewport[ViewInd][3]-(GLint)Y+(2*(m_Scene->Height/3));
				break;

			default:

				realy=viewport[ViewInd][3]-(GLint)Y+(m_Scene->Height/2);
				break;
		}


	}
    gluProject(0,0,0,mvmatrix[ViewInd], projmatrix[ViewInd], viewport[ViewInd], &ax, &ay, &az);
    gluUnProject((GLdouble)X,realy,(GLdouble)az,mvmatrix[ViewInd],projmatrix[ViewInd],viewport[ViewInd],&tmp1,&tmp2,&tmp3);
	
	value.x=tmp1;
	value.y=tmp2;
	value.z=tmp3;
//    temp=value;
    return value;

}
void  CKOGLRenderer::DrawView(Vertex & pos, Vertex & ng, Vertex & daViewSize,POINT scStart, POINT scEnd,int Indice)
{
    Vertex dapos;
    Vertex svgStart,start;
    double ind;

    ind=m_Scene->SnapVal.x;

	
	if (m_Scene->FullScreen)
	{
	}
	else
	{
		glEnable(GL_SCISSOR_TEST);
		glScissor(scStart.x,scStart.y,scEnd.x,scEnd.y);
	}
	if (Indice==m_Scene->Active)
		glClearColor(((float)m_Option->ActiveBackColor()->bBlue/256.0f),((float)m_Option->ActiveBackColor()->bGreen/256.0f),((float)m_Option->ActiveBackColor()->bRed/256.0f),0);
	else
		glClearColor(((float)m_Option->NActiveBackColor()->bBlue/256.0f),((float)m_Option->NActiveBackColor()->bGreen/256.0f),((float)m_Option->NActiveBackColor()->bRed/256.0f),0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);

	glMatrixMode( GL_PROJECTION );
    glLoadIdentity();


	if (m_Scene->ViewEnd[Indice].y==0)
		aspect=1;
	else
	{
		/*
		if (m_Scene->FullScreen)
		{
			aspect=(m_Scene->Width);
			aspect/=(m_Scene->Height);
		}
		else
		*/
		{
			aspect=(m_Scene->ViewEnd[Indice].x);
			aspect/=(m_Scene->ViewEnd[Indice].y);
		}
	}

	//aspect=1;

    daViewSize.y=daViewSize.x/aspect;

	
	glOrtho( -daViewSize.x, daViewSize.x,-daViewSize.y,daViewSize.y,-10000000.0,1000000);

    glMatrixMode( GL_MODELVIEW );

	glLoadIdentity();

	if (m_Scene->FullScreen)
	{
		glViewport(0,0,m_Scene->Width,m_Scene->Height);
	}
	else
	{
		glViewport(scStart.x,scStart.y,scEnd.x,scEnd.y);
	}


    glRotatef(ng.x,1,0,0);
    glRotatef(ng.y,0,1,0);
    glRotatef(ng.z,0,0,1);


    // -- grille ---------------------------------------------------------------

    glTranslatef(-pos.x,-pos.y,-pos.z);

    // axis

    glGetIntegerv(GL_VIEWPORT,viewport[Indice]);
    glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix[Indice]);
    glGetDoublev(GL_PROJECTION_MATRIX,projmatrix[Indice]);

    DrawScene(m_Scene->State[Indice],Indice);

	glPopMatrix();

    glGetIntegerv(GL_VIEWPORT,viewport[Indice]);
    glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix[Indice]);
    glGetDoublev(GL_PROJECTION_MATRIX,projmatrix[Indice]);

	DrawInfos(Indice);
}

void CKOGLRenderer::DrawUV(Vertex & pos, Vertex & ng, Vertex & daViewSize,POINT scStart, POINT scEnd,int Indice)
{
    Vertex dapos;
    Vertex svgStart,start;
    double ind;

    ind=m_Scene->SnapVal.x;

	
	if (m_Scene->FullScreen)
	{
	}
	else
	{
		glEnable(GL_SCISSOR_TEST);
		glScissor(scStart.x,scStart.y,scEnd.x,scEnd.y);
	}
	if (Indice==m_Scene->Active)
		glClearColor(((float)m_Option->ActiveBackColor()->bBlue/256.0f),((float)m_Option->ActiveBackColor()->bGreen/256.0f),((float)m_Option->ActiveBackColor()->bRed/256.0f),0);
	else
		glClearColor(((float)m_Option->NActiveBackColor()->bBlue/256.0f),((float)m_Option->NActiveBackColor()->bGreen/256.0f),((float)m_Option->NActiveBackColor()->bRed/256.0f),0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);

	glMatrixMode( GL_PROJECTION );
    glLoadIdentity();


	if (m_Scene->ViewEnd[Indice].y==0)
		aspect=1;
	else
	{
		{
			aspect=(m_Scene->ViewEnd[Indice].x);
			aspect/=(m_Scene->ViewEnd[Indice].y);
		}
	}

	//aspect=1;

    daViewSize.y=daViewSize.x/aspect;

	
	glOrtho( -daViewSize.x, daViewSize.x,-daViewSize.y,daViewSize.y,-10000000.0,1000000);

    glMatrixMode( GL_MODELVIEW );

	glLoadIdentity();

	if (m_Scene->FullScreen)
	{
		glViewport(0,0,m_Scene->Width,m_Scene->Height);
	}
	else
	{
		glViewport(scStart.x,scStart.y,scEnd.x,scEnd.y);
	}

/*
    glRotatef(ng.x,1,0,0);
    glRotatef(ng.y,0,1,0);
    glRotatef(ng.z,0,0,1);
*/

    // -- grille ---------------------------------------------------------------

    glTranslatef(-pos.x,-pos.y,-pos.z);

    // axis

    glGetIntegerv(GL_VIEWPORT,viewport[Indice]);
    glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix[Indice]);
    glGetDoublev(GL_PROJECTION_MATRIX,projmatrix[Indice]);

    glEnable(GL_TEXTURE_2D);


	CKPlan dap;



	glDisable(GL_CULL_FACE);
	if (m_Scene->FirstMesh!=NULL)
	{
		m_Scene->FirstMesh->Tex1->Bind();
		float dsx,dsy;
		dsx=m_Scene->FirstMesh->Tex1->SizeX;
		dsy=m_Scene->FirstMesh->Tex1->SizeY;

		glPushMatrix();

		dap.PlanOfView(this,Indice);

		Vertex daa,dab,dac;

		dap.pX.Normalize();
		dap.pY.Normalize();
		dap.pZ.Normalize();


		daa=(dap.pX*dsx);
		dab=(dap.pX*dsx+dap.pY*dsy);
		dac=(dap.pY*dsy);

		glPushMatrix();
		//glScalef(64,64,64);
		
		glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex3f(0,0,0);
		glTexCoord2f(0,1);
		glVertex3f(daa.x,daa.y,daa.z);
		glTexCoord2f(1,1);
		glVertex3f(dab.x,dab.y,dab.z);
		glTexCoord2f(1,0);
		glVertex3f(dac.x,dac.y,dac.z);
		glEnd();

		glPopMatrix();

		glEnable(GL_CULL_FACE);
		glDisable(GL_TEXTURE_2D);

		// draw the mapping triangles

		

		int i,j;
		Vertex tmpd;

		glDisable(GL_DEPTH_TEST);

//		int DrawType;

		

			
		glColor4f(1,1,1,1);

		for (CKMesh *daMesh=m_Scene->FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
		{
			if (daMesh->Selected)
			{
				for (i=0;i<daMesh->nb2poly;i++)
				{
					glBegin(GL_LINE_LOOP);
					
					for (j=0;j<daMesh->pl[i].nb2vert;j++)
					{
						tmpd=dap.pX*(daMesh->puv[0][daMesh->pl[i].Tex[0][j]].u*dsx);
						tmpd+=(dap.pY*(daMesh->puv[0][daMesh->pl[i].Tex[0][j]].v*dsy));

						glVertex3f(tmpd.x,tmpd.y,tmpd.z);
					}

					glEnd();
						
				}
			}
			else
			{
				for (i=0;i<daMesh->nb2poly;i++)
				{
					if (daMesh->pl[i].Selected)
					{
						glBegin(GL_LINE_LOOP);
						
						for (j=0;j<daMesh->pl[i].nb2vert;j++)
						{
							tmpd=dap.pX*daMesh->puv[0][daMesh->pl[i].Tex[0][j]].u*dsx;
							tmpd+=(dap.pY*daMesh->puv[0][daMesh->pl[i].Tex[0][j]].v*dsy);

							glVertex3f(tmpd.x,tmpd.y,tmpd.z);
						}

						glEnd();
					}
				}
			}
		}

	

		glPointSize(4);
		glColor4f(1,0,0,1);

		glBegin(GL_POINTS);
		for (i=0;i<m_Scene->m_CountUV;i++)
		{
			if (m_Scene->UVEdit[i].Selected)
			{
				/*
				tmpd=dap.pX*(m_Scene->UVEdit[i].u*64);
				tmpd+=(dap.pY*(m_Scene->UVEdit[i].v*64));
				*/

				tmpd=dap.pX*(m_Scene->UVEdit[i].daMesh->puv[0][m_Scene->UVEdit[i].PuvInd].u*dsx);
				tmpd+=(dap.pY*(m_Scene->UVEdit[i].daMesh->puv[0][m_Scene->UVEdit[i].PuvInd].v*dsy));

				glVertex3f(tmpd.x,tmpd.y,tmpd.z);
			}
		}
		glEnd();

		glPointSize(1);

		glEnable(GL_DEPTH_TEST);

		if (m_Scene->UVMinSel.u!=999999)
		{
			Vertex HandMin,HandMax;

			HandMax.x=(m_Scene->UVMaxSel.u*dsx);
			HandMax.y=-(m_Scene->UVMaxSel.v*dsy);
			HandMax.z=0;

			HandMin.x=(m_Scene->UVMinSel.u*dsx);
			HandMin.y=-(m_Scene->UVMinSel.v*dsy);
			HandMin.z=0;

			//HandUV.CalcHandles(m_Scene,Indice);
			DrawHandles(&m_Scene->HandUV,Indice,HandMin,HandMax);
			//CalcHandles(m_Scene->Active);
		}

		glPopMatrix();




		DrawSelection();
	}

	glPopMatrix();

    glGetIntegerv(GL_VIEWPORT,viewport[Indice]);
    glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix[Indice]);
    glGetDoublev(GL_PROJECTION_MATRIX,projmatrix[Indice]);

	DrawInfos(Indice);
}
void CKOGLRenderer::DrawInfos(int Indice)
{
	CString ViewName;
	CKCamera *daCam=NULL;

	if (m_Scene->ViewType[Indice]!=VIEWTYPE_CAMERA)
	{
		ViewName=GetName(Indice);
	}
	else if (m_Scene->ViewType[Indice]==VIEWTYPE_PERSPECTIVE)
	{
		ViewName="Camera";
	}
	else if (m_Scene->ViewType[Indice]==VIEWTYPE_UV)
	{
		ViewName="Edit UVs";
	}
	
	if (m_Scene->ViewType[Indice]==VIEWTYPE_CAMERA)
	{
		daCam=m_Scene->cam[Indice];
	}
	else
	{
		daCam=&m_Scene->Perspective[Indice];
	}


	int sx,sy;
	if (m_Scene->FullScreen)
	{
		sx=m_Scene->Width;
		sy=m_Scene->Height;
	}
	else
	{
		sx=m_Scene->ViewEnd[Indice].x;
		sy=m_Scene->ViewEnd[Indice].y;
	}

	if (m_Scene->Active==Indice)
	{
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();

		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();

		glColor4f(1,1,0.5,1);
		glOrtho( -1000,1000,-1000,1000,-10000000.0,1000000);
		
		//glDisable(GL_CULL_FACE);
		glBegin(GL_LINE_LOOP);

		glVertex2f(-999,-999);
		glVertex2f(-999,999);
		glVertex2f(999,999);
		glVertex2f(999,-999);
		
		glEnd();

		

		if (daCam!=NULL)
		if (daCam->DrawHUD)
		{
			glBegin(GL_LINES);
			glVertex2f(0,0);
			glVertex2f(15,0);
			glVertex2f(0,0);
			glVertex2f(0,15);
			glVertex2f(0,0);
			glVertex2f(-15,0);
			glVertex2f(0,0);
			glVertex2f(0,-15);


			glEnd();

		}

		glColor4f(1,1,1,1);
		//font->Draw(4, 4, temp);
	}
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();



	char temp[20];
	strcpy(temp,GetName(Indice));


	glOrtho( 0,sx,0,sy,-10000000.0,1000000);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, font->texid);
	font->WalkString(0,sy-m_Option->GetFontSize(), ViewName.GetBuffer(0));

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void  CKOGLRenderer::SwapActive(void)
{
	
	BeginRender();
    RenderOne(m_Scene->AncActive);

    RenderOne(m_Scene->Active);
	EndRender();
}


void  CKOGLRenderer::FlushIt(void)
{
    SwapBuffers(wglGetCurrentDC());
}


void  CKOGLRenderer::DrawViewCamera(Vertex & pos, Vertex & ng, Vertex & ViewSize,POINT scStart, POINT scEnd,int Indice)
{
    Vertex dapos;
//    int nbgridx,nbgridy;//,nbgridz;
    Vertex svgStart,start;
	CKCamera *daCam;
    double ind;

    ind=m_Scene->SnapVal.x;

	if (m_Scene->FullScreen)
	{
	}
	else
	{
		glEnable(GL_SCISSOR_TEST);
		glScissor(scStart.x,scStart.y,scEnd.x,scEnd.y);
	}
	if (Indice==m_Scene->Active)
		glClearColor(((float)m_Option->ActiveBackColor()->bBlue/256.0f),((float)m_Option->ActiveBackColor()->bGreen/256.0f),((float)m_Option->ActiveBackColor()->bRed/256.0f),0);
	else
		glClearColor(((float)m_Option->NActiveBackColor()->bBlue/256.0f),((float)m_Option->NActiveBackColor()->bGreen/256.0f),((float)m_Option->NActiveBackColor()->bRed/256.0f),0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);

	glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

	if (m_Scene->ViewType[Indice]==VIEWTYPE_CAMERA)
	{
		daCam=m_Scene->cam[Indice];
	}
	else
	{
		daCam=&m_Scene->Perspective[Indice];
		daCam->Fov=m_Option->CameraFov();
	}


	aspect=daCam->ResoX;
	aspect/=daCam->ResoY;
	ViewSize.y=ViewSize.x/aspect;
	gluPerspective(daCam->Fov, aspect, 0.1, 1000000.0);


    glMatrixMode( GL_MODELVIEW );

	glLoadIdentity();

	if (m_Scene->FullScreen)
	{
		glViewport(0,0,m_Scene->Width,m_Scene->Height);
	}
	else
	{
		glViewport(scStart.x,scStart.y,scEnd.x,scEnd.y);
	}


    glLoadIdentity();

	//m_Scene->m_skybox[Indice].Draw(m_Scene->cam[Indice],0,aspect);
	//if (m_Scene->daSky!=NULL) m_Scene->daSky->Draw(m_Scene->cam[Indice],0,aspect);

	DrawSkyBox(&m_Scene->m_skybox[Indice],daCam,0,aspect);
	gluLookAt(daCam->Source.x,daCam->Source.y,daCam->Source.z, daCam->Dest.x,daCam->Dest.y,daCam->Dest.z, 0,0,1);


	if (m_Scene->ViewType[Indice]==VIEWTYPE_CAMERA)
	{
		DrawScene(m_Scene->State[Indice],Indice);
		/*
		char temp[20];
		strcpy(temp,GetName(Indice));
		font->Draw(8, scEnd.y-20, temp);
		*/
	}
	else
	{
		DrawScene(m_Scene->State[Indice],Indice);
		/*
		font->Draw(8, scEnd.y-20, "Camera");
		*/
	}

    glGetIntegerv(GL_VIEWPORT,viewport[Indice]);
    glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix[Indice]);
    glGetDoublev(GL_PROJECTION_MATRIX,projmatrix[Indice]);
	DrawInfos(Indice);
/*
    // fausse camera
	if (m_Scene->Active==Indice)
	{
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();

		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();

		glColor4f(1,1,0.5,1);
		glOrtho( -100,100,-100,100,-10000000.0,1000000);
		
		//glDisable(GL_CULL_FACE);
		glBegin(GL_LINE_LOOP);

		glVertex2f(-99,-99);
		glVertex2f(-99,99);
		glVertex2f(99,99);
		glVertex2f(99,-99);
		glEnd();

		// Camera HUD
		if (daCam->DrawHUD)
		{
			glBegin(GL_LINES);
			glVertex2f(0,0);
			glVertex2f(4,0);
			glVertex2f(0,0);
			glVertex2f(0,4);
			glVertex2f(0,0);
			glVertex2f(-4,0);
			glVertex2f(0,0);
			glVertex2f(0,-4);


			glEnd();

		}
		glColor4f(1,1,1,1);
	}
	*/
}


void  CKOGLRenderer::DrawViewFull(CKCamera *daCam)
{
    Vertex dapos;
    Vertex svgStart,start;
    double ind;

    ind=m_Scene->SnapVal.x;

	glClearColor(0,0,0,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    glEnable(GL_DEPTH_TEST);

	glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

	aspect = 640;
    aspect/=480;

    gluPerspective( daCam->Fov, aspect, 0.1, 1000000.0);

    glMatrixMode( GL_MODELVIEW );

	glViewport(0,0,640,480);

    glLoadIdentity();

    gluLookAt(daCam->Source.x,daCam->Source.y,daCam->Source.z, daCam->Dest.x,daCam->Dest.y,daCam->Dest.z, 0,0,1);

    //glPushMatrix();

    //DrawScene(State[Indice]);

    CKMesh *daMesh;
//    Emitter *daEmit;
    glPushMatrix();

    // CKMesh
    daMesh=m_Scene->FirstMesh;
    while(daMesh!=NULL)
    {
        DrawMesh(daMesh,1,m_Scene->FrameInd);
        daMesh=daMesh->Next;
    }

    // particules
/*
    daEmit=m_Scene->FirstEmit;
    while (daEmit!=NULL)
    {
        DrawEmit(daEmit);
        daEmit=daEmit->Next;
    }
    //glPopMatrix();
*/

    glPopMatrix();
/*
    glGetIntegerv(GL_VIEWPORT,viewport[Indice]);
    glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix[Indice]);
    glGetDoublev(GL_PROJECTION_MATRIX,projmatrix[Indice]);
*/

    //glFinish();
/*
    //SwapBuffers(wglGetCurrentDC());
	if (m_Scene->ViewType[Indice]==9)
	{
		char temp[20];
		strcpy(temp,GetName(Indice));
		font->Draw(8, scEnd.y-20, temp);
	}
	else
	{
		font->Draw(8, scEnd.y-20, "CKCamera");
	}
*/
}


void  CKOGLRenderer::DrawCamera(CKCamera * daCam)
{
    double length;

    length = daCam->GetLength();



    //if (Primitive==1)
    {
        if (daCam->Source.Selected)
            glColor4f(1,0.75f,0.75f,1);
        else
            glColor4f(0.75f,0.75f,0.75f,1);

        glPointSize(4);
        glBegin(GL_POINTS);
        glVertex3f(daCam->Source.x,daCam->Source.y,daCam->Source.z);
        glEnd();

        if (daCam->Dest.Selected)
            glColor4f(1,0.75f,0.75f,1);
        else
            glColor4f(0.75f,0.75f,0.75f,1);

        glPointSize(4);
        glBegin(GL_POINTS);
        glVertex3f(daCam->Dest.x,daCam->Dest.y,daCam->Dest.z);
        glEnd();
    }

    if ( (daCam->Source.Selected)&&(daCam->Dest.Selected) )
            glColor4f(1,0.75f,0.75f,1);
        else
            glColor4f(0.75f,0.75f,0.75f,1);
    
    glPointSize(1);

    glPushMatrix();

//    glMultMatrixd(daCam->InverseModel);
	//daCam->InverseModel->GLMult();
	glMultMatrixd(daCam->InverseModel->mat);


    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, -1.0*length);

    glEnd();

    //glMultMatrixd(daCam->InverseProj);
	//daCam->InverseProj->GLMult();
	glMultMatrixd(daCam->InverseProj->mat);

    glBegin(GL_LINES);

    glVertex3i(1, 1, 1);
    glVertex3i(-1, 1, 1);
    glVertex3i(-1, 1, 1);
    glVertex3i(-1, -1, 1);
    glVertex3i(-1, -1, 1);
    glVertex3i(1, -1, 1);
    glVertex3i(1, -1, 1);
    glVertex3i(1, 1, 1);

    glVertex3i(1, 1, -1);
    glVertex3i(1, 1, 1);
    glVertex3i(-1, 1, -1);
    glVertex3i(-1, 1, 1);
    glVertex3i(-1, -1, -1);
    glVertex3i(-1, -1, 1);
    glVertex3i(1, -1, -1);
    glVertex3i(1, -1, 1);

    glVertex3i(1, 1, -1);
    glVertex3i(-1, 1, -1);
    glVertex3i(-1, 1, -1);
    glVertex3i(-1, -1, -1);
    glVertex3i(-1, -1, -1);
    glVertex3i(1, -1, -1);
    glVertex3i(1, -1, -1);
    glVertex3i(1, 1, -1);

    glEnd();

    glPopMatrix();

}

void CKOGLRenderer::Project(Vertex * vt, Vertex * dst, int ViewInd)
{
	double realy;

	realy=0;
	double tmp1,tmp2,tmp3;

    gluProject(vt->x,vt->y-realy,vt->z,mvmatrix[ViewInd], projmatrix[ViewInd], viewport[ViewInd], &tmp1,&tmp2,&tmp3);
	dst->x=tmp1;
	dst->y=tmp2;
	dst->z=tmp3;
}

void CKOGLRenderer::Project(int ViewNb,float x,float y,float z,double &dx,double &dy,double &dz)
{
    gluProject(x,y,z,mvmatrix[ViewNb], projmatrix[ViewNb], viewport[ViewNb], &dx,&dy,&dz);
}

void CKOGLRenderer::DrawShape(CKShape * daS)
{
    CKShape *DrawShape;
    CKSegment *DrawSegment;


    glDisable(GL_DEPTH_TEST);

	DrawShape=daS;//m_Scene->FirstShape;

    //while (DrawShape!=NULL)
    //{
        DrawSegment=DrawShape->FirstSegment;
        glBegin(GL_LINES);

        while(DrawSegment!=NULL)
        {

            if ((DrawSegment->SegSelected)||(DrawShape->Selected))
                glColor4f(1,0,1,1);
            else
                glColor4f(0,0,1,1);

            glVertex3f(DrawSegment->Dot.x,DrawSegment->Dot.y,DrawSegment->Dot.z);

            if ((DrawSegment->Next!=NULL)&&(DrawSegment->Next!=DrawShape->FirstSegment))
                glVertex3f(DrawSegment->Next->Dot.x,DrawSegment->Next->Dot.y,DrawSegment->Next->Dot.z);


            DrawSegment=DrawSegment->Next;

            if (DrawSegment==DrawShape->FirstSegment)
            {
                glVertex3f(DrawSegment->Dot.x,DrawSegment->Dot.y,DrawSegment->Dot.z);
                break;
            }

        }
        glEnd();

        // ticks

        if (Primitive==1)
        {
		    glPointSize(4);

            glBegin(GL_POINTS);

		    DrawSegment=DrawShape->FirstSegment;
            while(DrawSegment!=NULL)
            {

                if (DrawSegment->Dot.Selected)
                    glColor4f(1,0,1,1);
                else
                    glColor4f(0,0,1,1);

				glVertex3f(DrawSegment->Dot.x,DrawSegment->Dot.y,DrawSegment->Dot.z);
            
                DrawSegment=DrawSegment->Next;

                if (DrawSegment==DrawShape->FirstSegment)
                {
                    break;
                }

            }
            glEnd();
        }

        //DrawShape=DrawShape->Next;
	if (daS->DrawSpline)
	{
		glColor4ub(219,219,102,255);

		Vertex tmpspl;
		double avspl=(100.0f/((double)daS->Count*10.0f));
		glBegin(GL_LINE_STRIP);

		for (double ech=0;ech<=100.0f;ech++/*=avspl*/)
		{
			tmpspl=daS->GetSpline(ech);
			glVertex3f(tmpspl.x,tmpspl.y,tmpspl.z);
			

		}
		glEnd();


		glPointSize(3);
		glBegin(GL_POINTS);

		for (ech=0;ech<=100.0f;ech++/*=avspl*/)
		{
			tmpspl=daS->GetSpline(ech);
			glVertex3f(tmpspl.x,tmpspl.y,tmpspl.z);
			

		}
		glEnd();
	}



    //}
	glEnable(GL_DEPTH_TEST);
}





void  CKOGLRenderer::DrawSelection(void)
{
    CKShape *DrawShape;
    CKSegment *DrawSegment;

	glDisable(GL_DEPTH_TEST);
    DrawShape=m_Scene->Sel;
	if (DrawShape!=NULL)
	{

		glPushMatrix();

		

		glColor4f(0.5,0,0,0.5);
		
		
		glBlendFunc(GL_SRC_COLOR,GL_DST_COLOR);
		glEnable(GL_BLEND);

		glDisable(GL_CULL_FACE);


		glBegin(GL_TRIANGLE_FAN);

		DrawSegment=DrawShape->FirstSegment;
		while(DrawSegment!=NULL)
		{
			glVertex3f(DrawSegment->Dot.x,DrawSegment->Dot.y,DrawSegment->Dot.z);

			DrawSegment=DrawSegment->Next;

			if (DrawSegment==DrawShape->FirstSegment)
			{
				glVertex3f(DrawSegment->Dot.x,DrawSegment->Dot.y,DrawSegment->Dot.z);
				break;
			}

		}
		glEnd();

		glEnable(GL_CULL_FACE);

		glDisable(GL_BLEND);

		//glLineStipple(4,0xAAAA);

		glColor4f(1,0,0,1);

		glBegin(GL_LINE_STRIP);
		DrawSegment=DrawShape->FirstSegment;

		while(DrawSegment!=NULL)
		{
			glVertex3f(DrawSegment->Dot.x,DrawSegment->Dot.y,DrawSegment->Dot.z);

			DrawSegment=DrawSegment->Next;

			if (DrawSegment==DrawShape->FirstSegment)
			{
				glVertex3f(DrawSegment->Dot.x,DrawSegment->Dot.y,DrawSegment->Dot.z);
				break;
			}

		}
		glEnd();

		//glDisable(GL_LINE_STIPPLE);
		

		glPopMatrix();
	}

	glEnable(GL_DEPTH_TEST);
}

void  CKOGLRenderer::DrawMeshPolyWire(CKMesh * daO)
{
    int i,j;

	glDisable(GL_DEPTH_TEST);

	for (i=0;i<daO->nb2poly;i++)
	{
		glBegin(GL_LINE_LOOP);
		for (j=0;j<daO->pl[i].nb2vert;j++)
		{
			if  ((daO->pl[i].Selected ) || (daO->Selected )) //&&(Primitive==3)))
				glColor4f(1,0,0,1);
			else
				glColor3ubv((const unsigned char*)&daO->Color);

			glVertex3f(daO->pv[daO->pl[i].nbvert[j]].x,daO->pv[daO->pl[i].nbvert[j]].y,daO->pv[daO->pl[i].nbvert[j]].z);
		}
		glEnd();
	}

	glEnable(GL_DEPTH_TEST);
}

void CKOGLRenderer::DrawMeshPolyWireDot(CKMesh * daO)
{
    int i;

	glDisable(GL_DEPTH_TEST);

	glPointSize(4);
	
	glBegin(GL_POINTS);
	for (i=0;i<daO->nb2vert;i++)
	{
		if  (daO->pv[i].Selected )
		{
			glColor4f(1,0,0,1);
			glVertex3f(daO->pv[i].x,daO->pv[i].y,daO->pv[i].z);
		}
	}
	glEnd();
	glPointSize(1);
	glEnable(GL_DEPTH_TEST);
}

void CKOGLRenderer::DrawMeshPolyFlatShaded(CKMesh * daO)
{
	int i,j;
	daO->CalcAllPlanes();
	//if (daO->nbTexCanals==0)
	{
		
		GLfloat mat_spec[]={0.1f,0.1f,1.0f,1.0f};
		GLfloat mat_amb[4];
		GLfloat mat_Shin[]={1.0f};

		GLfloat light_pos[]={1000013,1000022,1000031,0};
		GLfloat light_pos2[]={-1000025,-1000037,-1000013,0};
		GLfloat white_light[]={1.0,1.0,1.0,1.0};
		if (daO->Selected)
		{
			mat_amb[0]=1.0f;
			mat_amb[1]=0;
			mat_amb[2]=0;

		mat_spec[0]=1.0f;
		mat_spec[1]=0.0f;
		mat_spec[2]=0.0f;
		}
		else
		{
			mat_amb[0]=(float)(daO->Color.bRed)/256.0f;
			mat_amb[1]=(float)(daO->Color.bGreen)/256.0f;
			mat_amb[2]=(float)(daO->Color.bBlue)/256.0f;

		mat_spec[0]=(float)(daO->Color.bRed)/256.0f;
		mat_spec[1]=(float)(daO->Color.bGreen)/256.0f;
		mat_spec[2]=(float)(daO->Color.bBlue)/256.0f;
		}

		GLfloat white_light2[]={0.5,0.5,0.5,0.5};

		glShadeModel(GL_SMOOTH);

		
		glMaterialfv(GL_FRONT,GL_SPECULAR,mat_spec);
		glMaterialfv(GL_FRONT,GL_SHININESS,mat_Shin);

		glLightfv(GL_LIGHT0,GL_POSITION,light_pos);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,white_light);
		glLightfv(GL_LIGHT0,GL_SPECULAR,white_light);

		glLightfv(GL_LIGHT1,GL_POSITION,light_pos2);
		glLightfv(GL_LIGHT1,GL_DIFFUSE,white_light2);
		glLightfv(GL_LIGHT1,GL_SPECULAR,white_light2);
		
		

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);

		//glColor4f(1,0,0,0);
		for (i=0;i<daO->nb2poly;i++)
		{
			glBegin(GL_POLYGON);
			for (j=0;j<daO->pl[i].nb2vert;j++)
			{
				//glTexCoord2f(daO->puv[0][daO->pl[i].Tex[0][j]].u,daO->puv[0][daO->pl[i].Tex[0][j]].v);
				glNormal3f(daO->pl[i].Normale.x,daO->pl[i].Normale.y,daO->pl[i].Normale.z);
				glVertex3f(daO->pv[daO->pl[i].nbvert[j]].x,daO->pv[daO->pl[i].nbvert[j]].y,daO->pv[daO->pl[i].nbvert[j]].z);
			}
			glEnd();
		}

		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHTING);
/*
		glColor4f(0,0,0,0);
		for (i=0;i<daO->nb2poly;i++)
		{
			glBegin(GL_LINE_LOOP);
			for (j=0;j<daO->pl[i].nb2vert;j++)
			{
				//glTexCoord2f(daO->puv[0][daO->pl[i].Tex[0][j]].u,daO->puv[0][daO->pl[i].Tex[0][j]].v);
				//glNormal3f(daO->pl[i].Normale.x,daO->pl[i].Normale.y,daO->pl[i].Normale.z);
				glVertex3f(daO->pv[daO->pl[i].nbvert[j]].x,daO->pv[daO->pl[i].nbvert[j]].y,daO->pv[daO->pl[i].nbvert[j]].z);
			}
			glEnd();
		}
		*/
		

	}
}


void  CKOGLRenderer::DrawMeshPolyMapped(CKMesh * daO)
{
    int i,j;


	if (daO->nbTexCanals==1)
	{

		
		glEnable(GL_TEXTURE_2D);
		


		if (daO->nbTexCoords[0]!=0)
		{
			
			for (i=0;i<daO->nb2poly;i++)
			{

				if  ((daO->pl[i].Selected ) || (daO->Selected )) //&&(Primitive==3)))
					glColor4f(1,0.3f,0.3f,1);
				else
					glColor4f(1,1,1,1);

				glEnable(GL_TEXTURE_2D);

				if (daO->pl[i].Maps[0])
				{
					if (daO->pl[i].Maps[0]->TexID==-1)
						daO->pl[i].Maps[0]->Load();
					else
						daO->pl[i].Maps[0]->Bind();
				}
				else
				{
					if (daO->Tex1->TexID==-1)
						daO->Tex1->Load();
					else
						daO->Tex1->Bind();
				}

				glBegin(GL_POLYGON);
				for (j=0;j<daO->pl[i].nb2vert;j++)
				{
					glTexCoord2f(daO->puv[0][daO->pl[i].Tex[0][j]].u,daO->puv[0][daO->pl[i].Tex[0][j]].v);
					glVertex3f(daO->pv[daO->pl[i].nbvert[j]].x,daO->pv[daO->pl[i].nbvert[j]].y,daO->pv[daO->pl[i].nbvert[j]].z);
				}
				glEnd();

				glDisable(GL_TEXTURE_2D);
			}
			

/*
			
			glEnable(GL_VERTEX_ARRAY);
			glEnable(GL_TEXTURE_COORD_ARRAY);
			glVertexPointer(3,GL_FLOAT,sizeof(Vertex),(&daO->Opv[0].x));
			glTexCoordPointer(2,GL_FLOAT,sizeof(UVCoords),(&daO->TexInd[0][0].u));
    		glDrawElements(GL_TRIANGLES,(daO->nbIndices),GL_UNSIGNED_INT,daO->Indices);
			glDisable(GL_TEXTURE_COORD_ARRAY);
			glDisable(GL_VERTEX_ARRAY);

  */
		}
		else
		{
			// no tex coords;
			DrawMeshPolyWire(daO);

		}

		glDisable(GL_TEXTURE_2D);
	}
	if (daO->nbTexCanals==2)
	{
		glEnable(GL_TEXTURE_2D);

		if (daO->Tex1!=NULL)
		{
			if (daO->Tex1->TexID==-1)
				daO->Tex1->Load();

			glActiveTextureARB(GL_TEXTURE0_ARB); 
			glEnable(GL_TEXTURE_2D);
			daO->Tex1->Bind();

		}
		
		if (daO->Tex2!=NULL)
		{
			if (daO->Tex2->TexID==-1)
				daO->Tex2->Load();

			glActiveTextureARB(GL_TEXTURE1_ARB);
			glEnable(GL_TEXTURE_2D);
			daO->Tex2->Bind();
		}

		for (i=0;i<daO->nb2poly;i++)
		{

			if (daO->pl[i].Maps[0]!=NULL)
			{
				if (daO->pl[i].Maps[0]->TexID==-1)
					daO->pl[i].Maps[0]->Load();

				glActiveTextureARB(GL_TEXTURE0_ARB); 
				glEnable(GL_TEXTURE_2D);
				daO->pl[i].Maps[0]->Bind();

			}
			
			if (daO->pl[i].Maps[1]!=NULL)
			{
				if (daO->pl[i].Maps[1]->TexID==-1)
					daO->pl[i].Maps[1]->Load();

				glActiveTextureARB(GL_TEXTURE1_ARB);
				glEnable(GL_TEXTURE_2D);
				daO->pl[i].Maps[1]->Bind();
			}

			if  ((daO->pl[i].Selected ) || (daO->Selected )) //&&(Primitive==3)))
				glColor4f(1,0.3f,0.3f,1);
			else
				glColor4f(1,1,1,1);

			glBegin(GL_POLYGON);
			for (j=0;j<daO->pl[i].nb2vert;j++)
			{
				glMultiTexCoord2fARB(GL_TEXTURE0_ARB,daO->puv[0][daO->pl[i].Tex[0][j]].u,daO->puv[0][daO->pl[i].Tex[0][j]].v);
				glMultiTexCoord2fARB(GL_TEXTURE1_ARB,daO->puv[1][daO->pl[i].Tex[1][j]].u,daO->puv[1][daO->pl[i].Tex[1][j]].v);
				glVertex3f(daO->pv[daO->pl[i].nbvert[j]].x,daO->pv[daO->pl[i].nbvert[j]].y,daO->pv[daO->pl[i].nbvert[j]].z);
			}
			glEnd();
		}

		//
		
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glDisable(GL_TEXTURE_2D);
		
		glActiveTextureARB(GL_TEXTURE0_ARB);
		glDisable(GL_TEXTURE_2D);

		glDisable(GL_TEXTURE_2D);

	}
}


void CKOGLRenderer::DrawMeshPolyMappedOutLined(CKMesh * daO)
{
    int i,j;

	if (daO->nbTexCanals==1)
	{

		
		glEnable(GL_TEXTURE_2D);
		


		if (daO->nbTexCoords[0]!=0)
		{
			
			for (i=0;i<daO->nb2poly;i++)
			{

				if  ((daO->pl[i].Selected ) || (daO->Selected )) //&&(Primitive==3)))
					glColor4f(1,0.3f,0.3f,1);
				else
					glColor4f(1,1,1,1);

				glEnable(GL_TEXTURE_2D);

				if (daO->pl[i].Maps[0])
				{
					if (daO->pl[i].Maps[0]->TexID==-1)
						daO->pl[i].Maps[0]->Load();
					else
						daO->pl[i].Maps[0]->Bind();
				}
				else
				{
					if (daO->Tex1->TexID==-1)
						daO->Tex1->Load();
					else
						daO->Tex1->Bind();
				}

				glBegin(GL_POLYGON);
				for (j=0;j<daO->pl[i].nb2vert;j++)
				{
					glTexCoord2f(daO->puv[0][daO->pl[i].Tex[0][j]].u,daO->puv[0][daO->pl[i].Tex[0][j]].v);
					glVertex3f(daO->pv[daO->pl[i].nbvert[j]].x,daO->pv[daO->pl[i].nbvert[j]].y,daO->pv[daO->pl[i].nbvert[j]].z);
				}
				glEnd();

				glDisable(GL_TEXTURE_2D);
				//glDisable(GL_DEPTH_TEST);
				glColor4f(1,1,1,1);
				//glPolygonMode(GL_FRONT_AND_BACK,GL_LINES);

				// par polygon
				glBegin(GL_LINE_LOOP);
				for (j=0;j<daO->pl[i].nb2vert;j++)
				{
					glTexCoord2f(daO->puv[0][daO->pl[i].Tex[0][j]].u,daO->puv[0][daO->pl[i].Tex[0][j]].v);
					glVertex3f(daO->pv[daO->pl[i].nbvert[j]].x,daO->pv[daO->pl[i].nbvert[j]].y,daO->pv[daO->pl[i].nbvert[j]].z);
				}
				glEnd();

				glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
				//glEnable(GL_DEPTH_TEST);

				
			}
			

/*
			
			glEnable(GL_VERTEX_ARRAY);
			glEnable(GL_TEXTURE_COORD_ARRAY);
			glVertexPointer(3,GL_FLOAT,sizeof(Vertex),(&daO->Opv[0].x));
			glTexCoordPointer(2,GL_FLOAT,sizeof(UVCoords),(&daO->TexInd[0][0].u));
    		glDrawElements(GL_TRIANGLES,(daO->nbIndices),GL_UNSIGNED_INT,daO->Indices);
			glDisable(GL_TEXTURE_COORD_ARRAY);
			glDisable(GL_VERTEX_ARRAY);

  */
		}
		else
		{
			// no tex coords;
			DrawMeshPolyWire(daO);

		}

		glDisable(GL_TEXTURE_2D);
	}
	if (daO->nbTexCanals==2)
	{
		if (daO->Tex1->TexID==-1)
			daO->Tex1->Load();
			
		if (daO->Tex2->TexID==-1)
			daO->Tex2->Load();

		glEnable(GL_TEXTURE_2D);

		glActiveTextureARB(GL_TEXTURE0_ARB); 
		glEnable(GL_TEXTURE_2D);
		daO->Tex1->Bind();

		
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glEnable(GL_TEXTURE_2D);
		daO->Tex2->Bind();


		for (i=0;i<daO->nb2poly;i++)
		{

			if  ((daO->pl[i].Selected ) || (daO->Selected )) //&&(Primitive==3)))
				glColor4f(1,0.3f,0.3f,1);
			else
				glColor4f(1,1,1,1);

			glBegin(GL_POLYGON);
			for (j=0;j<daO->pl[i].nb2vert;j++)
			{
				glMultiTexCoord2fARB(GL_TEXTURE0_ARB,daO->puv[0][daO->pl[i].Tex[0][j]].u,daO->puv[0][daO->pl[i].Tex[0][j]].v);
				glMultiTexCoord2fARB(GL_TEXTURE1_ARB,daO->puv[1][daO->pl[i].Tex[1][j]].u,daO->puv[1][daO->pl[i].Tex[1][j]].v);
				glVertex3f(daO->pv[daO->pl[i].nbvert[j]].x,daO->pv[daO->pl[i].nbvert[j]].y,daO->pv[daO->pl[i].nbvert[j]].z);
			}
			glEnd();
		}

		//
		
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glDisable(GL_TEXTURE_2D);
		
		glActiveTextureARB(GL_TEXTURE0_ARB);
		glDisable(GL_TEXTURE_2D);

		glDisable(GL_TEXTURE_2D);

	}


}

void CKOGLRenderer::DrawMesh(CKMesh * daO,int daState,int FrameInd)
{
    int More;

    glPushMatrix();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

    //daO->matrix->GLMult();
	glMultMatrixd(daO->matrix->mat);

    More=FrameInd*daO->nb2vert;

    if (daState==0)
    {

        if (daO->Selected&&(Primitive==3))
            glColor4f(1,0,0,1);
        else
            glColor3ubv((const unsigned char*)&daO->Color);

        DrawMeshPolyWire(daO);
		if (Primitive==1) DrawMeshPolyWireDot(daO);
    }
    else
	if (daState==1)
	{
		DrawMeshPolyFlatShaded(daO);
	}
	else
    {
		if (daState==3)
		{
			DrawMeshPolyMappedOutLined(daO);
		}
		else
		{
			DrawMeshPolyMapped(daO);
		}
    }

	// Draw centroid
	if (GetCentroid())
	{
		//glColor3ub(m_Option->GetCentoid()->
		glColor3ub(m_Option->GetCentroid()->bBlue,m_Option->GetCentroid()->bGreen,m_Option->GetCentroid()->bRed);

		Vertex ObjCenter=daO->Min+(daO->Max-daO->Min)/2;
		float iidx=(m_Scene->ViewSize[FrameInd].x/40);

		glBegin(GL_LINES);
		glVertex3f(iidx+ObjCenter.x,iidx+ObjCenter.y,iidx+ObjCenter.z);
		glVertex3f(-iidx+ObjCenter.x,-iidx+ObjCenter.y,-iidx+ObjCenter.z);

		glVertex3f(iidx+ObjCenter.x,iidx+ObjCenter.y,-iidx+ObjCenter.z);
		glVertex3f(-iidx+ObjCenter.x,-iidx+ObjCenter.y,iidx+ObjCenter.z);

		glVertex3f(-iidx+ObjCenter.x,iidx+ObjCenter.y,-iidx+ObjCenter.z);
		glVertex3f(iidx+ObjCenter.x,-iidx+ObjCenter.y,iidx+ObjCenter.z);

		glVertex3f(iidx+ObjCenter.x,-iidx+ObjCenter.y,-iidx+ObjCenter.z);
		glVertex3f(-iidx+ObjCenter.x,iidx+ObjCenter.y,iidx+ObjCenter.z);

		glEnd();	// --
	}


    glPopMatrix();
}

void  CKOGLRenderer::DrawBone(Vertex Node,CKBone *daBone,bool IsDot,bool IsRoot)
{

    CKBone *daBone2;

    if (IsDot)
	{

		glVertex3f(Node.x,Node.y,Node.z);
	}
	else
	{
        if (!IsRoot)
        {
            //glPushMatrix();
            glPushMatrix();

	        if (daBone->Pos.Selected)
                glColor4f(0.8f,0.8f,0,0.8f);
            else
                glColor4f(0,0.8f,0,0.8f);


            glTranslatef(Node.x,Node.y,Node.z);
            double Length=::Pythagore3D(Node,*daBone->AbsPos);
            glScalef(Length/20,Length/20,Length/20);
            glCallList(2);
            glPopMatrix();


            glBegin(GL_LINES);
            glVertex3f(Node.x,Node.y,Node.z-(Length/20));
            glVertex3f(daBone->AbsPos->x,daBone->AbsPos->y,daBone->AbsPos->z);

            glVertex3f(Node.x,Node.y,Node.z+(Length/20));
            glVertex3f(daBone->AbsPos->x,daBone->AbsPos->y,daBone->AbsPos->z);

            glVertex3f(Node.x,Node.y-(Length/20),Node.z);
            glVertex3f(daBone->AbsPos->x,daBone->AbsPos->y,daBone->AbsPos->z);

            glVertex3f(Node.x,Node.y+(Length/20),Node.z);
            glVertex3f(daBone->AbsPos->x,daBone->AbsPos->y,daBone->AbsPos->z);

            glVertex3f(Node.x-(Length/20),Node.y,Node.z);
            glVertex3f(daBone->AbsPos->x,daBone->AbsPos->y,daBone->AbsPos->z);

            glVertex3f(Node.x+(Length/20),Node.y,Node.z);
            glVertex3f(daBone->AbsPos->x,daBone->AbsPos->y,daBone->AbsPos->z);

            glEnd();

            //glPopMatrix();

            glBegin(GL_LINES);
		    glVertex3f(Node.x,Node.y,Node.z);
		    glVertex3f(daBone->AbsPos->x,daBone->AbsPos->y,daBone->AbsPos->z);
		    glEnd();
        }
        else
        {
            //Is root


            //glPushMatrix();

            glPushMatrix();
            glTranslatef(Node.x,Node.y,Node.z);
            double Length=::Pythagore3D(Node,*daBone->AbsPos);
            glScalef(Length/20,Length/20,Length/20);
            glCallList(2);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(daBone->AbsPos->x,daBone->AbsPos->y,daBone->AbsPos->z);
            glScalef(Length/20,Length/20,Length/20);
            glCallList(2);
            glPopMatrix();



            glBegin(GL_LINES);
            glVertex3f(Node.x,Node.y,Node.z-(Length/20));
            glVertex3f(daBone->AbsPos->x,daBone->AbsPos->y,daBone->AbsPos->z-(Length/20));

            glVertex3f(Node.x,Node.y,Node.z+(Length/20));
            glVertex3f(daBone->AbsPos->x,daBone->AbsPos->y,daBone->AbsPos->z+(Length/20));

            glVertex3f(Node.x,Node.y-(Length/20),Node.z);
            glVertex3f(daBone->AbsPos->x,daBone->AbsPos->y-(Length/20),daBone->AbsPos->z);

            glVertex3f(Node.x,Node.y+(Length/20),Node.z);
            glVertex3f(daBone->AbsPos->x,daBone->AbsPos->y+(Length/20),daBone->AbsPos->z);

            glVertex3f(Node.x-(Length/20),Node.y,Node.z);
            glVertex3f(daBone->AbsPos->x-(Length/20),daBone->AbsPos->y,daBone->AbsPos->z);

            glVertex3f(Node.x+(Length/20),Node.y,Node.z);
            glVertex3f(daBone->AbsPos->x+(Length/20),daBone->AbsPos->y,daBone->AbsPos->z);

            glEnd();

            //glPopMatrix();

            glBegin(GL_LINES);
		    glVertex3f(Node.x,Node.y,Node.z);
		    glVertex3f(daBone->AbsPos->x,daBone->AbsPos->y,daBone->AbsPos->z);
		    glEnd();

        }

	}

    daBone2=daBone->FirstBone;
    while(daBone2!=NULL)
    {
        DrawBone((*daBone->AbsPos),daBone2,IsDot,false);

        daBone2=daBone2->Next;
    }
}

void  CKOGLRenderer::DrawSkeleton(CKSkeleton *daSkel)
{
	Vertex yop;

	if (daSkel->RootPos.Selected)
        glColor4f(1,1,0,1);
    else
        glColor4f(0,1,0,1);

	DrawBone(daSkel->RootPos,daSkel->bone,false,true);
}

void CKOGLRenderer::DrawHandles(CKHandles *Handles,int ActiveView,Vertex &HandMin,Vertex &HandMax)
{
	if (ActiveView!=m_Scene->Active)
	{

		
		glColor3ub(m_Option->HandlesRoundColor()->bBlue,m_Option->HandlesRoundColor()->bGreen,m_Option->HandlesRoundColor()->bRed);


		glBegin(GL_LINES);
		for (int i=0;i<48;i++)
		{
			glVertex3f(Handles->DrawHanks[i].x,Handles->DrawHanks[i].y,Handles->DrawHanks[i].z);
		}

		glEnd();

		
	
		return;
	}
	if (Handles->CalculateHandles) 
	{
		Handles->CalcHandles(m_Scene,m_Scene->Active,HandMin,HandMax);
	}
	int i;
	glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
/*
	GLint vPort[4];

	glGetIntegerv(GL_VIEWPORT, vPort);
	glOrtho( m_Scene->ViewStart[ActiveView].x,vPort[2]+m_Scene->ViewStart[ActiveView].x, m_Scene->ViewStart[ActiveView].y, vPort[3]+m_Scene->ViewStart[ActiveView].y, -1, 1);
*/
	//glGetIntegerv(GL_VIEWPORT, vPort);
	if (m_Scene->FullScreen)
		glOrtho( 0,viewport[ActiveView][2], 0, viewport[ActiveView][3], -1, 1);
	else
		glOrtho( m_Scene->ViewStart[ActiveView].x,viewport[ActiveView][2]+m_Scene->ViewStart[ActiveView].x, m_Scene->ViewStart[ActiveView].y, viewport[ActiveView][3]+m_Scene->ViewStart[ActiveView].y, -1, 1);
	




	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();


	glDisable(GL_DEPTH_TEST);

	glColor3ub(m_Option->HandlesColor()->bBlue,m_Option->HandlesColor()->bGreen,m_Option->HandlesColor()->bRed);
	glPointSize(8);

	
	glBegin(GL_POINTS);

	glVertex2dv(&Handles->a2DHandles[4].x);
	glVertex2dv(&Handles->a2DHandles[4+SELTESSELATE].x);
	glVertex2dv(&Handles->a2DHandles[4+(SELTESSELATE*2)].x);
	glVertex2dv(&Handles->a2DHandles[4+(SELTESSELATE*3)].x);

	glVertex2dv(&Handles->a2DHandles[0].x);
	glVertex2dv(&Handles->a2DHandles[SELTESSELATE].x);
	glVertex2dv(&Handles->a2DHandles[(SELTESSELATE*2)].x);
	glVertex2dv(&Handles->a2DHandles[(SELTESSELATE*3)].x);

	glVertex2dv(&Handles->a2DHandles[(SELTESSELATE*4)].x);

	//glVertex2f(MinPt.x-10,MinPt.y-10);

	glEnd();

		
	glColor3ub(m_Option->HandlesRoundColor()->bBlue,m_Option->HandlesRoundColor()->bGreen,m_Option->HandlesRoundColor()->bRed);

	glLineStipple(4,0xAAAA);
	glEnable(GL_LINE_STIPPLE);

	for (i=0;i<3;i++)
	{
		glBegin(GL_LINE_STRIP);
		for (int j=0;j<=SELTESSELATE;j++)
		{
			glVertex2d(Handles->a2DHandles[j+(i*SELTESSELATE)].x,Handles->a2DHandles[j+(i*SELTESSELATE)].y);
		}
	}
	for (int j=0;j<SELTESSELATE;j++)
	{
		glVertex2d(Handles->a2DHandles[j+(i*SELTESSELATE)].x,Handles->a2DHandles[j+(i*SELTESSELATE)].y);
	}
	glVertex2d(Handles->a2DHandles[0].x,Handles->a2DHandles[0].y);
	glEnd();


	glDisable(GL_LINE_STIPPLE);

	glPointSize(1);

	glEnable(GL_DEPTH_TEST);

	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();   
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

}

void CKOGLRenderer::Render()
{
	int i;
    i=0;


	if (m_Scene!=NULL)
	{

    if (m_Scene->FullScreen)
    {
            if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_ORTHO) 
				DrawView(m_Scene->ViewPos[m_Scene->Active],m_Scene->ViewNg[m_Scene->Active],m_Scene->ViewSize[m_Scene->Active],m_Scene->ViewStart[m_Scene->Active],m_Scene->ViewEnd[m_Scene->Active],m_Scene->Active);
			else 
			if ((m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_PERSPECTIVE)||(m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_CAMERA)) 
				DrawViewCamera(m_Scene->ViewPos[m_Scene->Active],m_Scene->ViewNg[m_Scene->Active],m_Scene->ViewSize[m_Scene->Active],m_Scene->ViewStart[m_Scene->Active],m_Scene->ViewEnd[m_Scene->Active],m_Scene->Active);
			else 
			if (m_Scene->ViewType[m_Scene->Active]==VIEWTYPE_UV) 
				DrawUV(m_Scene->ViewPos[m_Scene->Active],m_Scene->ViewNg[m_Scene->Active],m_Scene->ViewSize[m_Scene->Active],m_Scene->ViewStart[m_Scene->Active],m_Scene->ViewEnd[m_Scene->Active],m_Scene->Active);
	}
	else
	{

		for (i=0;i<4;i++)
		{
            if (m_Scene->ViewType[i]==VIEWTYPE_ORTHO) 
				DrawView(m_Scene->ViewPos[i],m_Scene->ViewNg[i],m_Scene->ViewSize[i],m_Scene->ViewStart[i],m_Scene->ViewEnd[i],i);
			else 
			if ((m_Scene->ViewType[i]==VIEWTYPE_PERSPECTIVE)||(m_Scene->ViewType[i]==VIEWTYPE_CAMERA)) 
				DrawViewCamera(m_Scene->ViewPos[i],m_Scene->ViewNg[i],m_Scene->ViewSize[i],m_Scene->ViewStart[i],m_Scene->ViewEnd[i],i);
			else 
			if (m_Scene->ViewType[i]==VIEWTYPE_UV) 
				DrawUV(m_Scene->ViewPos[i],m_Scene->ViewNg[i],m_Scene->ViewSize[i],m_Scene->ViewStart[i],m_Scene->ViewEnd[i],i);
        }
    }
	}
}

void CKOGLRenderer::RenderOne(int ViewNb)
{
    if (m_Scene->ViewType[ViewNb]==0) 
		DrawView(m_Scene->ViewPos[ViewNb],m_Scene->ViewNg[ViewNb],m_Scene->ViewSize[ViewNb],m_Scene->ViewStart[ViewNb],m_Scene->ViewEnd[ViewNb],(ViewNb));
    else 
	if ((m_Scene->ViewType[ViewNb]==VIEWTYPE_PERSPECTIVE)||(m_Scene->ViewType[ViewNb]==VIEWTYPE_CAMERA)) 
		DrawViewCamera(m_Scene->ViewPos[ViewNb],m_Scene->ViewNg[ViewNb],m_Scene->ViewSize[ViewNb],m_Scene->ViewStart[ViewNb],m_Scene->ViewEnd[ViewNb],(ViewNb));
	else 
	if (m_Scene->ViewType[ViewNb]==VIEWTYPE_UV) 
		DrawUV(m_Scene->ViewPos[ViewNb],m_Scene->ViewNg[ViewNb],m_Scene->ViewSize[ViewNb],m_Scene->ViewStart[ViewNb],m_Scene->ViewEnd[ViewNb],(ViewNb));
}


void CKOGLRenderer::DrawPatch(CKPatch *pPatch,int State)
{
	int i,j;
	
	glPushMatrix();
	
	glColor4f(1,1,1,1);
	glPointSize(1);
	
	if (pPatch->pts!=NULL)
	{
		glEnable(GL_TEXTURE_2D);
		if (pPatch->Tex1->TexID==-1)
			pPatch->Tex1->Load();
		else
			pPatch->Tex1->Bind();
		
		if (pPatch->puv[0]!=NULL)
		{
			glPolygonMode(GL_BACK,GL_LINE);

			for (int k=0;k<pPatch->nb2patch;k++)
			//int k=1;
			{
				int decal=k*((pPatch->Tesselate + 1)*(pPatch->Tesselate + 1));
				for (j=0;j<pPatch->Tesselate;j++)
				{
					glBegin(GL_TRIANGLE_STRIP);
					for (i=0;i<((pPatch->Tesselate + 1)*2);i++)
					{
						glTexCoord2f(pPatch->puv[0][pPatch->strips[j][i]+decal].u,pPatch->puv[0][pPatch->strips[j][i]+decal].v);
						glVertex3f(pPatch->pts[pPatch->strips[j][i]+decal].x,pPatch->pts[pPatch->strips[j][i]+decal].y,pPatch->pts[pPatch->strips[j][i]+decal].z);
					}
					glEnd();
				}
			}

			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

			for (int k=0;k<pPatch->nb2patch;k++)
			{

				for (j=0;j<pPatch->Tesselate;j++)
				{
					glBegin(GL_TRIANGLE_STRIP);
					for (i=0;i<((pPatch->Tesselate + 1)*2);i++)
					{
						glTexCoord2f(0,0);
						glVertex3f(pPatch->pts[pPatch->strips[j][i]].x,pPatch->pts[pPatch->strips[j][i]].y,pPatch->pts[pPatch->strips[j][i]].z);
					}
					glEnd();
				}
			}

			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

		}
		

		
		glDisable(GL_TEXTURE_2D);
	}
	
	if (pPatch->pv!=NULL)
	{
	
		glPointSize(5);
		glBegin(GL_POINTS);
/*
		for (i=0;i<3;i++)
		{
			for (j=0;j<3;j++)
			{
				if (pv[CtrlsPt[i*3+j]].Selected)
					glColor4f(1,0,1,1);
				else
					glColor4f(0,0,1,1);
				
				glVertex3f(pv[CtrlsPt[i*3+j]].x,pv[CtrlsPt[i*3+j]].y,pv[CtrlsPt[i*3+j]].z);
			}
		}
		*/
		for (i=0;i<pPatch->nb2patch*9;i++)
		{
				if (pPatch->pv[pPatch->CtrlsPt[i]].Selected)
					glColor4f(1,0,1,1);
				else
					glColor4f(0,0,1,1);
				
				glVertex3f(pPatch->pv[pPatch->CtrlsPt[i]].x,pPatch->pv[pPatch->CtrlsPt[i]].y,pPatch->pv[pPatch->CtrlsPt[i]].z);
		}
		
		glEnd();
	}
	
	glPopMatrix();
}


void CKOGLRenderer::DrawSkyBox(CKSkyBox *pSB,CKCamera *pCamera, unsigned int iFOV, float fAspect)
{
	////////////////////////////////////////////////////////////////////////
	// Draw the skybox
	////////////////////////////////////////////////////////////////////////
	glDisable(GL_CULL_FACE);
	static int iDisplayList = -1;
	
	glPushMatrix();
    //glRotatef(90,0,1,0);
	
	// Rotate the skybox to fit the players view
	//pCamera->RotateWorld();
    glLoadIdentity();
	
	//pCamera->UndoTranslate();
	gluLookAt(pCamera->Source.x, pCamera->Source.y,pCamera->Source.z, pCamera->Dest.x,pCamera->Dest.y,pCamera->Dest.z, 0, 0, 1);
    glTranslatef((float)pCamera->Source.x,(float)pCamera->Source.y,(float)pCamera->Source.z);
	
    glScalef(1000,1000,fAspect*1000);
	
    //glDisable(GL_DEPTH_TEST);
	glColor4f(1,1,1,1);
	
    // -- Layer 1 ----------------------------------------------
	glEnable(GL_TEXTURE_2D);

	// Front
	if (pSB->Layer1[1]->TexID!=-1)
    {
        pSB->Layer1[1]->Bind();
		
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(12.0f, -12.0f, -12.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(12.0f, -12.0f, 12.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-12.0f, -12.0f, 12.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-12.0f, -12.0f, -12.0f);
		glEnd();
    }
	
	// Back
	if (pSB->Layer1[0]->TexID!=-1)
    {
		
		pSB->Layer1[0]->Bind();
		
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-12.0f, 12.0f, -12.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-12.0f, 12.0f, 12.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(12.0f, 12.0f, 12.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(12.0f, 12.0f, -12.0f);
		glEnd();
    }
	
	// Up
	if (pSB->Layer1[2]->TexID!=-1)
    {
		
		pSB->Layer1[2]->Bind();
		
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(12.0f, -12.0f, 12.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(12.0f, 12.0f, 12.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-12.0f, 12.0f, 12.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-12.0f, -12.0f, 12.0f);
		glEnd();
    }
	// Down
	if (pSB->Layer1[3]->TexID!=-1)
    {
		
		pSB->Layer1[3]->Bind();
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(12.0f, -12.0f, -12.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(12.0f, 12.0f, -12.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-12.0f, 12.0f, -12.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-12.0f, -12.0f, -12.0f);
		glEnd();
    }
	
	// Right
	if (pSB->Layer1[5]->TexID!=-1)
    {
		
		pSB->Layer1[5]->Bind();
		
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(12.0f, 12.0f, -12.0f); 
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(12.0f, 12.0f, 12.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(12.0f, -12.0f, 12.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(12.0f, -12.0f, -12.0f);
		glEnd();
    }
	// Left
	
	if (pSB->Layer1[4]->TexID!=-1)
    {
		
		pSB->Layer1[4]->Bind();
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-12.0f, -12.0f, -12.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-12.0f, -12.0f, 12.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-12.0f, 12.0f, 12.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-12.0f, 12.0f, -12.0f);
		glEnd();
    }    
	
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_COLOR, GL_ONE);
    //glColor4f(1,1,1,0.7);
	/*
	if (Sky1->TexID!=-1)
    {
		
		
		Sky1->Bind();
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR			);
		
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glBegin(GL_QUADS);
		glTexCoord2f((1.0f+Sky1pos)*10, 0.0f);
		glVertex3f(500.0f, -500.0f, 9.0f);
		glTexCoord2f((1.0f+Sky1pos)*10, 10.0f);
		glVertex3f(500.0f, 50.0f, 9.0f);
		glTexCoord2f((0.0f+Sky1pos)*10, 10.0f);
		glVertex3f(-500.0f, 50.0f, 9.0f);
		glTexCoord2f((0.0f+Sky1pos)*10, 0.0f);
		glVertex3f(-500.0f, -500.0f, 9.0f);
		glEnd();
		
        glDisable(GL_BLEND);
    }
	
	if (Sky2->TexID!=-1)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR			);
		
		Sky2->Bind();
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glBegin(GL_QUADS);
		glTexCoord2f((1.0f+Sky2pos)*10, 0.0f);
		glVertex3f(500.0f, -500.0f, 9.0f);
		glTexCoord2f((1.0f+Sky2pos)*10, 10.0f);
		glVertex3f(500.0f, 50.0f, 9.0f);
		glTexCoord2f((0.0f+Sky2pos)*10, 10.0f);
		glVertex3f(-500.0f, 50.0f, 9.0f);
		glTexCoord2f((0.0f+Sky2pos)*10, 0.0f);
		glVertex3f(-500.0f, -500.0f, 9.0f);
		glEnd();
		
		
        glDisable(GL_BLEND);
    }
	
    Sky1pos+=Sky1av;
    Sky2pos+=Sky2av;
	
    
	
	
    // -- Layer 2 ----------------------------------------------
	if (Layer2[1]->TexID!=-1)
    {
		
		Layer2[1]->Bind();
        if (Layer2[1]->ComputeAlpha)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        }
        else 
            glDisable(GL_BLEND);
		
		
		
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10.0f, -10.0f, -10.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10.0f, -10.0f, 10.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-10.0f, -10.0f, 10.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-10.0f, -10.0f, -10.0f);
		glEnd();
    }
	// Back
	if (Layer2[0]->TexID!=-1)
    {
		
		Layer2[0]->Bind();
		if (Layer2[0]->ComputeAlpha)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        }
        else 
            glDisable(GL_BLEND);
		
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-10.0f, 10.0f, -10.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-10.0f, 10.0f, 10.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(10.0f, 10.0f, 10.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(10.0f, 10.0f, -10.0f);
		glEnd();
    }
	// Up
	if (Layer2[2]->TexID!=-1)
    {
		
		Layer2[2]->Bind();
		if (Layer2[2]->ComputeAlpha)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        }
        else 
            glDisable(GL_BLEND);
		
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10.0f, -10.0f, 10.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10.0f, 10.0f, 10.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-10.0f, 10.0f, 10.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-10.0f, -10.0f, 10.0f);
		glEnd();
    }
	
	// Down
	if (Layer2[3]->TexID!=-1)
    {
		
		Layer2[3]->Bind();
		if (Layer2[3]->ComputeAlpha)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        }
        else 
            glDisable(GL_BLEND);
		
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10.0f, -10.0f, -10.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10.0f, 10.0f, -10.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-10.0f, 10.0f, -10.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-10.0f, -10.0f, -10.0f);
		glEnd();
    }
	
	// Right
	if (Layer2[5]->TexID!=-1)
    {
		
		Layer2[5]->Bind();
		if (Layer2[5]->ComputeAlpha)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        }
        else 
            glDisable(GL_BLEND);
		
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10.0f, 10.0f, -10.0f); 
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10.0f, 10.0f, 10.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(10.0f, -10.0f, 10.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(10.0f, -10.0f, -10.0f);
		glEnd();
    }
	
	// Left
	if (Layer2[4]->TexID!=-1)
    {
		
        if (Layer2[4]->ComputeAlpha)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        }
        else 
            glDisable(GL_BLEND);
		
		Layer2[4]->Bind();
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-10.0f, -10.0f, -10.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-10.0f, -10.0f, 10.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-10.0f, 10.0f, 10.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-10.0f, 10.0f, -10.0f);
		glEnd();
    }
	
    glDisable(GL_BLEND);
	*/
	glPopMatrix();
	
    glEnable(GL_DEPTH_TEST);

	glDisable(GL_CULL_FACE);

	glDisable(GL_TEXTURE_2D);
}


// Set CKCamera matrix in OpenGL
void CKOGLRenderer::SetCamera(CKCamera *pCam)
{
	float phi, teta;
	float x2, y2, z2;
	double aspect;


	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
    glLoadIdentity();

	aspect = pCam->ResoX;
    aspect/=pCam->ResoY;

    Vertex c;

    c=pCam->Source-pCam->Dest;
    pCam->Length=sqrt(fabs(c.x*c.x+c.y*c.y)+c.z*c.z);


    gluPerspective( pCam->Fov, aspect, 1, pCam->Length);

    glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

    glLoadIdentity();


	if ((pCam->angle_a==0)&&(pCam->angle_b==0)&&(pCam->m_speed==0))
	{
		gluLookAt(pCam->Source.x, pCam->Source.y,pCam->Source.z, pCam->Dest.x,pCam->Dest.y,pCam->Dest.z, 0, 0, 1);
	}
	else
	{

		phi = (float)((-pCam->angle_a * PI)/180);
		teta = (float)((pCam->angle_b * PI)/180);

		x2 = (float)(-cos(phi)*sin(teta));
		y2 = (float)(-sin(phi));
		z2 = (float)(cos(phi)*cos(teta));

		// First, rotate CKCamera
		
		glRotatef(-pCam->angle_a, 1, 0, 0);
		glRotatef(-pCam->angle_b, 0, 1, 0);

		gluLookAt(pCam->Source.x, pCam->Source.y,pCam->Source.z, pCam->Dest.x,pCam->Dest.y,pCam->Dest.z, 0, 0, 1);

;

		//pCam->modelview->GetFrom(GL_MODELVIEW_MATRIX);
		glGetDoublev(GL_MODELVIEW_MATRIX,pCam->modelview->mat);

		Vertex temp(0,0,-pCam->Length);

		pCam->modelview->MultVectorByMatrix2((Vertex*)&temp,(Vertex*)&pCam->Dest);
		pCam->Dest+=pCam->Source;
	
		glLoadIdentity();


        double m_speed2=(pCam->m_speed*pCam->Length)/10;
        /*
		// Calculate new coordinates of CKCamera
		Source.x = Source.x + x2*m_speed2;
		Source.y = Source.y + y2*m_speed2;
		Source.z = Source.z + z2*m_speed2;

		Dest.x = Dest.x + x2*m_speed2;
		Dest.y = Dest.y + y2*m_speed2;
		Dest.z = Dest.z + z2*m_speed2;
        */
		gluLookAt(pCam->Source.x, pCam->Source.y,pCam->Source.z, pCam->Dest.x,pCam->Dest.y,pCam->Dest.z, 0, 0, 1);



		pCam->angle_a=0;
		pCam->angle_b=0;

	}


	//pCam->modelview->GetFrom(GL_MODELVIEW_MATRIX);
	glGetDoublev(GL_MODELVIEW_MATRIX,pCam->modelview->mat);
	//pCam->projection->GetFrom(GL_PROJECTION_MATRIX);
	glGetDoublev(GL_PROJECTION_MATRIX,pCam->projection->mat);


	pCam->modelview->InvertMatrix(pCam->InverseModel);
	pCam->projection->InvertMatrix(pCam->InverseProj);

	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();

	glMatrixMode( GL_PROJECTION );
	glPopMatrix();

	glMatrixMode( GL_MODELVIEW );

	pCam->Min=pCam->Source;
	pCam->Min.GetMinOf(pCam->Dest);

	pCam->Max=pCam->Source;
	pCam->Max.GetMinOf(pCam->Dest);
}


bool CKOGLRenderer::LoadTexture(CString FileName,void *TexID,int &SizeX,int &SizeY)
{
	unsigned int *TexPtr=(unsigned int *)TexID;

	if ((*TexPtr)==-1)
	{
		if (!FileName.IsEmpty())
		{
			CKImage img;
			img.LoadFile(FileName);
			SizeX=img.GetWidth();
			SizeY=img.GetHeight();

			img.Dither(IMG_TYPE_COL24,true);

			glEnable(GL_TEXTURE_2D);
			glGenTextures(1, TexPtr);
			glBindTexture(GL_TEXTURE_2D, (*TexPtr));
    
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

			LPBITMAPINFOHEADER BmInfo=(LPBITMAPINFOHEADER)GlobalLock(img.m_hDib);

			LPBITMAPINFO bi=(LPBITMAPINFO)BmInfo;
			if (BmInfo!=NULL)
			{
				int nColors = BmInfo->biClrUsed ? BmInfo->biClrUsed : 0x1FF & (1 << BmInfo->biBitCount);


				const byte* bits = (byte*)BmInfo+BmInfo->biSize+nColors*sizeof(RGBQUAD);

                    

			//            int nScanWidth = WIDTHBYTES(BmInfo->biWidth * BmInfo->biBitCount);
				unsigned char tmpbits;
				BYTE *dabits=(BYTE*)bits;

				//if (!img.UseBGR)
				{
					for( int y=0; y<BmInfo->biHeight; y++)
					{
						//destbyte=(unsigned char*)dest->Bitmap->ScanLine[Desty-y-1];
						for(int x=0; x<BmInfo->biWidth; x++)
						{
							tmpbits=(*dabits);
							(*dabits)=(*(dabits+2));
							(*(dabits+2))=tmpbits;

							dabits+=3;

						}
					}
				}

				int err=gluBuild2DMipmaps(GL_TEXTURE_2D, 3, BmInfo->biWidth, BmInfo->biHeight, GL_RGB, GL_UNSIGNED_BYTE, bits);
            
			}
		}
	}
	return true;
}

void CKOGLRenderer::BindTexture(void *TexID)
{
	unsigned int *TexPtr=(unsigned int *)TexID;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,(*TexPtr));
}

void CKOGLRenderer::FreeTexture(void *TexID)
{
	glEnable(GL_TEXTURE_2D);
	glDeleteTextures(1,(unsigned int *)TexID);
	(*((unsigned int *)TexID))=-1;
}
	
void CKOGLRenderer::DirectRender(Vertex *Verts,UVCoords *UVs,int *Indices,DWORD RenderType,int iNbIndex,float R,float G,float B,float A)
{
	unsigned int mTypesd[]={GL_POINTS,GL_LINE_STRIP,GL_LINE_LOOP,GL_LINES,GL_TRIANGLE_STRIP,
		GL_TRIANGLE_FAN,GL_TRIANGLES,GL_QUAD_STRIP,GL_QUADS,GL_POLYGON};

	glColor4f(R,G,B,A);
	if (Verts!=NULL)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3,GL_FLOAT,sizeof(Vertex),&Verts->x);
		//glIndexPointer(GL_INT,0,Indices);
		if (UVs!=NULL) glTexCoordPointer(2,GL_FLOAT,4/*sizeof(UVCoords)*/,&UVs->u);
		//glDrawArrays(mTypesd[RenderType],0,iNbIndex);
		glDrawElements(mTypesd[RenderType],iNbIndex,GL_UNSIGNED_INT,Indices);
		glDisableClientState(GL_VERTEX_ARRAY);
 	}
}

