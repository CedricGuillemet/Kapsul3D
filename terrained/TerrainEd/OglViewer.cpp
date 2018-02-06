// OglViewer.cpp : implementation file
//

#include "stdafx.h"
#include "TerrainEd.h"
#include "OglViewer.h"

#include <gl/gl.h>
#include <gl/glu.h>
//#include <gl/glut.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include <headers.h>
#include "scenegraph.h"
#include "Terra.h"
extern CSkyBox daSkyb;
extern CImage DetailTex;
extern PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
extern PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB;
extern PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB;

/////////////////////////////////////////////////////////////////////////////
// COglViewer

extern "C" 
{
int nAvgFrames = -1;
CTexture *tertex;
CTexture *pTexSkyBox[5];
//CSkyBox csb;
Camera *VCam;
}
extern int WaterTexID;
extern CTerra m_Terra;
extern int daWaterLevel;

extern Object *daTrees[1024];
extern Object *daLeaf[1024];
extern Vertex Pos[1024];
extern Desk *dk;
extern CTexture *m_ecorce;
extern CTexture *m_feuille;


COglViewer::COglViewer()
{
    moving=false;
    IsAvancing=false;
}

COglViewer::~COglViewer()
{
}


BEGIN_MESSAGE_MAP(COglViewer, CWnd)
	//{{AFX_MSG_MAP(COglViewer)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SETCURSOR()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_ENTERIDLE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COglViewer message handlers

void COglViewer::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
// prepare a semaphore
	static BOOL 	bBusy = FALSE;
// use the semaphore to enter this critic section
	if(bBusy) return;
	bBusy = TRUE;

// specify the target DeviceContext of the subsequent OGL calls
	wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);

// clear background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// call the virtual drawing procedure (to be overridden by user)
	//OnDrawGL();
    
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);

  glShadeModel(GL_SMOOTH);




    glClearColor(0,0,0,0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode( GL_PROJECTION );
    glLoadIdentity();



	//glOrtho( -20,20,-20,20,-100.0,100);
    gluPerspective(60, 1, 0.1, 1000000.0);

    glMatrixMode( GL_MODELVIEW );

	glLoadIdentity();







        
        glEnable(GL_TEXTURE_2D);
		
        


	glActiveTextureARB(GL_TEXTURE0_ARB); 
	glEnable(GL_TEXTURE_2D);
    tertex->Bind();
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glDisable(GL_TEXTURE_2D);
	glActiveTextureARB(GL_TEXTURE0_ARB); 
	glEnable(GL_TEXTURE_2D);


    VCam->LookAt();
    daSkyb.Draw(VCam,60,1);

    glDisable(GL_CULL_FACE);
//    csb.Draw(VCam,60,1);
    
	glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);

    
	glActiveTextureARB(GL_TEXTURE0_ARB); 
	glEnable(GL_TEXTURE_2D);
    tertex->Bind();
    if (DetailTex.TexId!=-1)
    {
        glActiveTextureARB(GL_TEXTURE1_ARB);
	    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,DetailTex.TexId);
    }
    //tertex->Bind();
    
    //DetailTex
    RenderScene();


    if (WaterTexID!=-1)
    {
	    glActiveTextureARB(GL_TEXTURE1_ARB);
	    glDisable(GL_TEXTURE_2D);
	    glActiveTextureARB(GL_TEXTURE0_ARB); 
	    glEnable(GL_TEXTURE_2D);


        glBindTexture(GL_TEXTURE_2D,WaterTexID);
        glTranslatef(0,0,daWaterLevel);
	    RenderWater();
        glTranslatef(0,0,-daWaterLevel);
    }
    // draw trees


    //glScalef(100,100,100);
/*
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glScalef(1000,1000,1000);
*/
    Object *daO;


    int More=0;

    //glTranslatef(0,0,-64);
/*
    m_ecorce->Bind();

	glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);
    glBegin(GL_TRIANGLES);


    
    for (int j=0;j<128;j++)
    {
        daO=daTrees[j];

        for (int i=0;i<daO->nb2faces;i++)
        {
            Vertex tmp;

            tmp=(*daO->pv[daO->pf[i]->nbvert[0]]/10.0f)+Pos[j];

            glTexCoord2f(daO->pv[daO->pf[i]->nbvert[0]]->u,daO->pv[daO->pf[i]->nbvert[0]]->v);
            glVertex3f(tmp.vx,tmp.vy,tmp.vz);

            tmp=(*daO->pv[daO->pf[i]->nbvert[1]]/10.0f)+Pos[j];
            glTexCoord2f(daO->pv[daO->pf[i]->nbvert[1]]->u,daO->pv[daO->pf[i]->nbvert[1]]->v);
            glVertex3f(tmp.vx,tmp.vy,tmp.vz);


            tmp=(*daO->pv[daO->pf[i]->nbvert[2]]/10.0f)+Pos[j];
            glTexCoord2f(daO->pv[daO->pf[i]->nbvert[2]]->u,daO->pv[daO->pf[i]->nbvert[2]]->v);
            glVertex3f(tmp.vx,tmp.vy,tmp.vz);
        }
    }

    glEnd();

    m_feuille->Bind();


    glAlphaFunc(GL_GREATER ,0.5f);
    glEnable(GL_ALPHA_TEST);

glBegin(GL_TRIANGLES);

    for (j=0;j<128;j++)
    {
        daO=daLeaf[j];

        for (int i=0;i<daO->nb2faces;i++)
        {
            Vertex tmp;

            tmp=(*daO->pv[daO->pf[i]->nbvert[0]]/10.0f)+Pos[j];

            glTexCoord2f(daO->pv[daO->pf[i]->nbvert[0]]->u,daO->pv[daO->pf[i]->nbvert[0]]->v);
            glVertex3f(tmp.vx,tmp.vy,tmp.vz);

            tmp=(*daO->pv[daO->pf[i]->nbvert[1]]/10.0f)+Pos[j];
            glTexCoord2f(daO->pv[daO->pf[i]->nbvert[1]]->u,daO->pv[daO->pf[i]->nbvert[1]]->v);
            glVertex3f(tmp.vx,tmp.vy,tmp.vz);


            tmp=(*daO->pv[daO->pf[i]->nbvert[2]]/10.0f)+Pos[j];
            glTexCoord2f(daO->pv[daO->pf[i]->nbvert[2]]->u,daO->pv[daO->pf[i]->nbvert[2]]->v);
            glVertex3f(tmp.vx,tmp.vy,tmp.vz);
        }
    }

    glDisable(GL_ALPHA_TEST);

    glEnd();

*/
	glFinish();
	SwapBuffers(m_pCDC->GetSafeHdc());
	bBusy = FALSE;
}

void COglViewer::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);

	if ( 0 < cx && 0 < cy )
	{
		m_ClientRect.right = cx;
		m_ClientRect.bottom = cy;
		m_dAspectRatio=double(cx)/double(cy);

		wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);
        
	    glViewport(0,0,cx,cy);
    }
}

void COglViewer::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (moving)
    {
        ngx=point.x-mypt.x;
        ngy=point.y-mypt.y;

	    VCam->SetMouse(point.x,point.y,640,480);
        VCam->SetCamera();
//        DrawViews();

        //Invalidate(TRUE);
        OnPaint();

    }
	
	CWnd::OnMouseMove(nFlags, point);
}

void COglViewer::OnLButtonDown(UINT nFlags, CPoint point) 
{
	moving=true;
    mypt=point;
    SetCapture();
	
	VCam->SetMousePos();
	VCam->BeginMove();

	CWnd::OnLButtonDown(nFlags, point);
}

void COglViewer::OnLButtonUp(UINT nFlags, CPoint point) 
{
	moving=false;
    ReleaseCapture();
	
	VCam->EndDraw();

	CWnd::OnLButtonUp(nFlags, point);
}

int COglViewer::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    int         n;

	m_pCDC= new CClientDC(this);

	static PIXELFORMATDESCRIPTOR pfd = 
	{
        sizeof(PIXELFORMATDESCRIPTOR),	// size of this pfd
        1,								// version number
        PFD_DRAW_TO_WINDOW |			// support window
        PFD_SUPPORT_OPENGL |			// support OpenGL
        PFD_DOUBLEBUFFER,				// double buffered
        PFD_TYPE_RGBA,                  // RGBA type
        32,                             // 24-bit color depth
        0, 0, 0, 0, 0, 0,               // color bits ignored
        0,                              // no alpha buffer
        0,                              // shift bit ignored
        0,                              // no accumulation buffer
        0, 0, 0, 0,                     // accum bits ignored
        16,                             // 32-bit z-buffer
        0,                              // no stencil buffer
        0,                              // no auxiliary buffer
        PFD_MAIN_PLANE,                 // main layer
        0,                              // reserved
        0, 0, 0                         // layer masks ignored
    };

    ASSERT(m_pCDC != NULL);
    int pixelformat;
	if ( (pixelformat = ChoosePixelFormat(m_pCDC->GetSafeHdc(), &pfd)) == 0 )
    {
        return FALSE;
    }

	if (SetPixelFormat(m_pCDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
    {
        pixelformat = 1;	
		if (DescribePixelFormat(m_pCDC->GetSafeHdc(), pixelformat, sizeof(PIXELFORMATDESCRIPTOR), &pfd)==0)
		{
			return FALSE;
		}
    }

	
    n=::GetPixelFormat(m_pCDC->GetSafeHdc());
    ::DescribePixelFormat(m_pCDC->GetSafeHdc(),n,sizeof(pfd),&pfd);

    m_hRC = wglCreateContext(m_pCDC->GetSafeHdc());

    wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);
	glClearColor(0.f,0.f,0.f,1.0f );
	glClearDepth(1.0f);
	
	return 0;
}

BOOL COglViewer::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

// these styles are meant for a use of this class in a MDI application
	cs.lpszClass = AfxRegisterWndClass(CS_OWNDC | CS_HREDRAW | CS_VREDRAW);
	
	return CWnd::PreCreateWindow(cs);
}

void COglViewer::OnDestroy() 
{
	CWnd::OnDestroy();
	
    wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);
	if (m_hRC!=NULL) ::wglDeleteContext(m_hRC);
	CPalette palDefault;
	palDefault.CreateStockObject(DEFAULT_PALETTE);
	m_pCDC->SelectPalette(&palDefault, FALSE);
	if(m_pCDC) delete m_pCDC;
	
}

BOOL COglViewer::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	ASSERT(m_hMouseCursor!=NULL);
	::SetCursor(m_hMouseCursor);
	
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

BOOL COglViewer::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return TRUE;
}

void COglViewer::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	IsAvancing=true;

    if (nChar==69)
    {
    Vertex Av=VCam->Dest-VCam->Source;
    VCam->Source+=Av/100;
    VCam->Dest+=Av/100;
    }

    if (nChar==68)
    {
    Vertex Av=VCam->Dest-VCam->Source;
    VCam->Source-=Av/100;
    VCam->Dest-=Av/100;
    }
    
    double dah=m_Terra.FindHeightAt(VCam->Source.vx,VCam->Source.vy)+0.5;
    if (VCam->Source.vz<dah) VCam->Source.vz=dah;
    VCam->SetCamera();

    

    Invalidate(FALSE);
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void COglViewer::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	IsAvancing=false;
	CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void COglViewer::OnEnterIdle(UINT nWhy, CWnd* pWho) 
{
	CWnd::OnEnterIdle(nWhy, pWho);
	
	if (IsAvancing)
    {

        Vertex Av=VCam->Dest-VCam->Source;
        VCam->Source+=Av/10;
        VCam->Dest+=Av/10;
        VCam->SetCamera();
    }
	
}
