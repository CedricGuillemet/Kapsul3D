// KSlid.cpp : implementation file
//

#include "stdafx.h"

//#include "memmgr/mmgr.h"

#include "KSlid.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKSlid
bool daErase=false;
CKSlid::CKSlid()
{
    IsDouble=true;
    Pos1=128;
    Pos2=128;

    Min1=0;
    Min2=0;

    NewPos1=128;
    NewPos2=128;

    Max1=255;
    Max2=255;

    P1Track=false;
    P2Track=false;
}

CKSlid::~CKSlid()
{
}


BEGIN_MESSAGE_MAP(CKSlid, CWnd)
	//{{AFX_MSG_MAP(CKSlid)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKSlid message handlers

void CKSlid::OnPaint() 
{
    CPaintDC dc(this); // device context for painting


    RECT rc;

    GetClientRect(&rc);

    HBRUSH hbr2;
    hbr2=GetSysColorBrush(COLOR_MENU);

    CBrush cbr2;
    LOGBRUSH lb,lb1,lb2;

    cbr2.CreateSysColorBrush(COLOR_MENU);
    cbr2.GetLogBrush(&lb);
    cbr2.DeleteObject();

//    DeleteObject(cbr2);
    cbr2.CreateSysColorBrush(COLOR_3DHILIGHT);
    cbr2.GetLogBrush(&lb1);
    cbr2.DeleteObject();

    DeleteObject(cbr2);
    cbr2.CreateSysColorBrush(COLOR_3DDKSHADOW);

    cbr2.GetLogBrush(&lb2);
    cbr2.DeleteObject();

    //dc.SelectObject(&cbr2);

    ::FillRect(dc.m_hDC,&rc,hbr2);


    if (IsDouble)
    {
        //dc.FillRect(CRect(rc.left+4,rc.top+(rc.bottom-2)/2,rc.right-4,(rc.top+(rc.bottom-2)/2)+2),&CBrush(RGB(0,0,0)));

        if (Pos1==Min1)
            Pos1A=0;
        else
        {
            Pos1A=(float)(rc.right-rc.left-9);
            Pos1A/=(Max1-Min1);
            Pos1A*=(Pos1-Min1);
        }

        CPen hl,dl;
        hl.CreatePen(PS_SOLID,1,&lb1);//(1,1,&lb1,PS_SOLID),dl(1,1,&lb2,PS_SOLID);
        dl.CreatePen(PS_SOLID,1,&lb2);

        Pos1A+=rc.left+4;

        CPoint pts[5];

        

        pts[0].x=(long)Pos1A;
        pts[0].y=(rc.top+(rc.bottom-2)/2)-1;


        pts[1].x=(long)(Pos1A-4);
        pts[1].y=(rc.top+(rc.bottom-2)/4);

        pts[2].x=(long)(Pos1A-4);
        pts[2].y=(rc.top+1);

        pts[3].x=(long)(Pos1A+4);
        pts[3].y=(rc.top+1);

        pts[4].x=(long)(Pos1A+4);
        pts[4].y=(rc.top+(rc.bottom-2)/4);


        dc.SelectObject(&hl);
        dc.MoveTo(pts[0]);
        dc.LineTo(pts[1]);
        dc.LineTo(pts[2]);
        dc.LineTo(pts[3]);
        dc.LineTo(pts[4]);


        dc.SelectObject(&dl);
        dc.MoveTo(pts[3]);
        dc.LineTo(pts[4]);
        dc.LineTo(pts[0]);
        
        //
        dc.SelectObject(&dl);
        dc.MoveTo(rc.left+4,(rc.top+(rc.bottom-2)/2)+2);
        dc.LineTo(rc.left+4,rc.top+(rc.bottom-2)/2-1);
        dc.LineTo(rc.right-4,rc.top+(rc.bottom-2)/2-1);

        dc.SelectObject(&hl);
        dc.MoveTo(rc.right-4,rc.top+(rc.bottom-2)/2-1);
        dc.LineTo(rc.right-4,(rc.top+(rc.bottom-2)/2)+2);
        dc.LineTo(rc.left+4,(rc.top+(rc.bottom-2)/2)+2);
        

        //dc.Polygon(pts,5);


        if (Pos2==Min2)
            Pos2A=0;
        else
        {
            Pos2A=(float)(rc.right-rc.left-9);
            Pos2A/=(Max2-Min2);
            Pos2A*=(Pos2-Min2);
        }


        Pos2A+=rc.left+4;


        pts[0].x=(long)Pos2A;
        pts[0].y=(long)((rc.top+(rc.bottom-2)/2)+2);

        pts[1].x=(long)(Pos2A-4);
        pts[1].y=(long)((rc.top+(rc.bottom-2)/1.5)+2);

        pts[2].x=(long)(Pos2A-4);
        pts[2].y=(long)(rc.bottom-1);

        pts[3].x=(long)(Pos2A+4);
        pts[3].y=(long)(rc.bottom-1);

        pts[4].x=(long)(Pos2A+4);
        pts[4].y=(long)((rc.top+(rc.bottom-2)/1.5)+2);


        dc.SelectObject(&hl);
        dc.MoveTo(pts[0]);
        dc.LineTo(pts[1]);
        dc.LineTo(pts[2]);
        dc.LineTo(pts[3]);
        dc.LineTo(pts[4]);


        dc.SelectObject(&dl);
        dc.MoveTo(pts[3]);
        dc.LineTo(pts[4]);
        dc.LineTo(pts[0]);

    }
    else
    {

    }}

void CKSlid::OnLButtonUp(UINT nFlags, CPoint point) 
{
	P1Track=false;
    P2Track=false;
    ReleaseCapture();

	CWnd::OnLButtonUp(nFlags, point);
}

void CKSlid::OnLButtonDown(UINT nFlags, CPoint point) 
{
    RECT rc;
    GetClientRect(&rc);

	if ( (point.x>=(Pos1A-4)) &&
        (point.x<=(Pos1A+4)) &&
        (point.y>=(rc.top+1)) &&
        (point.y<=((rc.top+(rc.bottom-2)/2)-1)) )
    {
        P1Track=true;
        TrackPT=point;
        SetCapture();
    }
    else
        
	if ( (point.x>=(Pos2A-4)) &&
        (point.x<=(Pos2A+4)) &&
        (point.y>=((rc.top+(rc.bottom-2)/2)+2)) &&
        (point.y<=(rc.bottom-1)) )
    {
        P2Track=true;
        TrackPT=point;
        SetCapture();
    }
        
	
	CWnd::OnLButtonDown(nFlags, point);
}

void CKSlid::OnMouseMove(UINT nFlags, CPoint point) 
{
    RECT rc;

    GetClientRect(&rc);

	if (P1Track)
    {
        NewPos1=(float)(point.x-TrackPT.x)-4-rc.left+TrackPT.x;
        NewPos1*=(Max1-Min1);
        NewPos1/=(rc.right-rc.left-8);

        if (NewPos1>Max1) NewPos1=(float)Max1;
        if (NewPos1<Min1) NewPos1=(float)Min1;

        Pos1=(int)NewPos1;

    }

	if (P2Track)
    {
        NewPos2=(float)(point.x-TrackPT.x)-4-rc.left+TrackPT.x;
        NewPos2*=(Max2-Min2);
        NewPos2/=(rc.right-rc.left-8);

        if (NewPos2>Max2) NewPos2=(float)Max2;
        if (NewPos2<Min2) NewPos2=(float)Min2;
        Pos2=(int)NewPos2;

    }
    if (P2Track||P1Track) 
    {
        Invalidate(FALSE);
        GetParent()->SendMessage(WM_HSCROLL,0,0);
    }
    
	CWnd::OnMouseMove(nFlags, point);
}

void CKSlid::SetRange1(int _min1, int _max1)
{
    Min1=_min1;
    Max1=_max1;
}

void CKSlid::SetRange2(int _min2, int _max2)
{
    Min2=_min2;
    Max2=_max2;
}

int CKSlid::GetPos1()
{
    return Pos1;
}

int CKSlid::GetPos2()
{
    return Pos2;
}


void CKSlid::SetPos1(int val)
{
    Pos1=val;
    Invalidate(false);
}

void CKSlid::SetPos2(int val)
{
    Pos2=val;
    Invalidate(false);
}
