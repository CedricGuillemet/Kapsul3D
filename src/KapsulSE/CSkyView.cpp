// TestSt.cpp : implementation file
//

#include "stdafx.h"
#include "CSkyView.h"
//#include "gl/glut.h"
//#include "TestSt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CSkyView, CButton)

//extern OGLView *View;
//extern Desk *CurrentDesk;
/////////////////////////////////////////////////////////////////////////////
// CSkyView

CSkyView::CSkyView()
{
	m_pCDC=NULL;
    ngx=0;
    ngy=0;
    moving=false;
    VCam=new CKCamera(NULL,NULL);
    cb=new CKSkyBox;
}

CSkyView::~CSkyView()
{
}


BEGIN_MESSAGE_MAP(CSkyView, CButton)
	//{{AFX_MSG_MAP(CSkyView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSkyView::OnPaint() 
{
	/*
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
		
        


    VCam->LookAt();


    cb->Draw(VCam,60,1);

	glFinish();
	SwapBuffers(m_pCDC->GetSafeHdc());
	bBusy = FALSE;
	*/
}

void CSkyView::OnSize(UINT nType, int cx, int cy) 
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

void CSkyView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (moving)
    {
        ngx=point.x-mypt.x;
        ngy=point.y-mypt.y;

	    VCam->SetMouse(point.x,point.y,640,480);
        VCam->SetCamera();
        //DrawViews();

        //Invalidate(TRUE);
        OnPaint();

    }
	
	CWnd::OnMouseMove(nFlags, point);
}

void CSkyView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	moving=true;
    mypt=point;
    SetCapture();
	
	VCam->SetMousePos();
	VCam->BeginMove();

	CWnd::OnLButtonDown(nFlags, point);
}

void CSkyView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	moving=false;
    ReleaseCapture();
	
	VCam->EndDraw();

	CWnd::OnLButtonUp(nFlags, point);
}

int CSkyView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

BOOL CSkyView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

// these styles are meant for a use of this class in a MDI application
	cs.lpszClass = AfxRegisterWndClass(CS_OWNDC | CS_HREDRAW | CS_VREDRAW);
	
	return CWnd::PreCreateWindow(cs);
}

void CSkyView::OnDestroy() 
{
	CWnd::OnDestroy();
	
    wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);
	if (m_hRC!=NULL) ::wglDeleteContext(m_hRC);
	CPalette palDefault;
	palDefault.CreateStockObject(DEFAULT_PALETTE);
	m_pCDC->SelectPalette(&palDefault, FALSE);
	if(m_pCDC) delete m_pCDC;
	
}

BOOL CSkyView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
    /*
	ASSERT(m_hMouseCursor!=NULL);
	::SetCursor(m_hMouseCursor);
	*/
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

BOOL CSkyView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return TRUE;
}
