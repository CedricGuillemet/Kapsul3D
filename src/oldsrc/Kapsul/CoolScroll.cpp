// CoolScroll.cpp : implementation file
//

#include "stdafx.h"
//#include "TScroll.h"
#include "CoolScroll.h"
#include "resource.h"
#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCoolScroll

CCoolScroll::CCoolScroll()
{
	tbSize=100;
	tbPos=20;
	tbLength=50;
	Moving=FALSE;
	daPlug=NULL;
}

CCoolScroll::~CCoolScroll()
{
}


BEGIN_MESSAGE_MAP(CCoolScroll, CStatic)
	//{{AFX_MSG_MAP(CCoolScroll)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCoolScroll message handlers

void CCoolScroll::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	//PAINTSTRUCT ps;

	//BeginPaint(&ps);
	
	// TODO: Add your message handler code here

	RECT rc;


    // -- Temp






	::GetClientRect(daPlug,&rc);
	tbSize=rc.bottom+8;
    
    //RECT rcg;

    
    //tbPos=rc.top;

	if ((tbPos+tbSize)>tbLength) 
	{
		//tbPos=0;
		RECT rc;
		::GetClientRect(daPlug,&rc);
		//::MoveWindow(daPlug,0,0,rc.right,rc.bottom,TRUE);
	}
	
	GetParent()->GetClientRect(&rc);

	tbLength=rc.bottom;




    // Temp ---

	GetClientRect(&rc);
	float lnth=(tbLength+tbPos);
	lnth*=((float)rc.bottom/(float)tbSize);


	float ast=tbPos;
	
	ast*=((float)rc.bottom/(float)tbSize);

	
	
	dc.FillRect(CRect(rc),&CBrush(RGB(0,0,120)));
	if (tbLength<tbSize) dc.FillRect(CRect(1,ast,5,lnth),&CBrush(RGB(120,120,255)));

	

	//SetCursor(LoadCursor(NULL, IDC_WAIT));
	// Do not call CWnd::OnPaint() for painting messages
	//EndPaint(&ps);
}

extern GenericLib *gen;

void CCoolScroll::OnSize(UINT nType, int cx, int cy) 
{
	RECT rc;

	CStatic::OnSize(nType, cx, cy);
	//Invalidate(TRUE);

	::GetClientRect(daPlug,&rc);
	tbSize=rc.bottom+8;


//	if (cy>tbLength) 
	{

		
		//CWnd daw(dahwnd);

		//tbPos=0;

		if ((tbPos+tbSize)>tbLength) 
		{
			tbPos=0;
			RECT rc;
			::GetClientRect(daPlug,&rc);
			::MoveWindow(daPlug,0,0,rc.right,rc.bottom,TRUE);
		}
		
		GetParent()->GetClientRect(&rc);

		tbLength=rc.bottom;

		Invalidate(TRUE);

	}


	tbPos=0;
	::GetClientRect(daPlug,&rc);

	::MoveWindow(daPlug,0,0,rc.right,rc.bottom,TRUE);

	// TODO: Add your message handler code here
	
}

void CCoolScroll::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (tbLength<tbSize) 
	{
		Moving=TRUE;
		SetCapture();
		clpt=point;

		RECT rc;
		GetClientRect(&rc);
		tbPos2=tbPos;

		clVal=(int)(point.y*(rc.bottom/tbSize));
		CStatic::OnLButtonDown(nFlags, point);
		::SetCursor(LoadCursor(AfxGetInstanceHandle(),(LPCTSTR)IDC_HANDOPEN));
	}
}

void CCoolScroll::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	Moving=FALSE;
	ReleaseCapture();
	CStatic::OnLButtonUp(nFlags, point);
	::SetCursor(LoadCursor(AfxGetInstanceHandle(),(LPCTSTR)IDC_HANDCLOSE));
}

void CCoolScroll::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (Moving==TRUE)
	{
		RECT rc;
		GetClientRect(&rc);

		float cva,cva2;
		cva=tbPos2;
		cva2=tbSize;
		cva2/=rc.bottom;//);
		cva2*=(point.y-clpt.y);
		cva+=cva2;
		clVal=(int)cva;

		if (clVal<0) clVal=0;
		if ((clVal+tbLength)>tbSize) clVal=tbSize-tbLength;
		

		tbPos=clVal;
		Invalidate(FALSE);
		//OnPaint();
		::SetCursor(LoadCursor(AfxGetInstanceHandle(),(LPCTSTR)IDC_HANDOPEN));

		//RECT rc;
		
		::GetClientRect(daPlug,&rc);
		::MoveWindow(daPlug,0,-tbPos,rc.right,rc.bottom,TRUE);
	}
	else
	{
		::SetCursor(LoadCursor(AfxGetInstanceHandle(),(LPCTSTR)IDC_HANDCLOSE));
	}
	Invalidate(TRUE);

	CStatic::OnMouseMove(nFlags, point);
}

BOOL CCoolScroll::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if (Moving==TRUE)
		::SetCursor(LoadCursor(AfxGetInstanceHandle(),(LPCTSTR)IDC_HANDOPEN));
	else
		::SetCursor(LoadCursor(AfxGetInstanceHandle(),(LPCTSTR)IDC_HANDCLOSE));

	return FALSE;
	//return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

extern GenericLib *gen;
void CCoolScroll::SetPlug(HWND dahwnd,CWnd *Parent) 
{
    int height;
	//::DestroyWindow(daPlug);

	daPlug=dahwnd;

	RECT rc;
	//CWnd daw(dahwnd);

    Parent->GetClientRect(&rc);

    if (gen!=NULL)
    {
        height=gen->Process(KM_MOVEWINDOW,rc.right,rc.bottom-8);
    }

    GetParent()->GetClientRect(&rc);
    GetParent()->MoveWindow(0,0,rc.right,rc.bottom,TRUE);

	::GetClientRect(dahwnd,&rc);
    
    if (height!=0)
        tbSize=height+8;
    else
	    tbSize=rc.bottom+8;

	tbPos=0;
	
	Parent->GetClientRect(&rc);

	tbLength=rc.bottom;

	Invalidate(TRUE);
}
