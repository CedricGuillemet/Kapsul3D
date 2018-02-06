// TimeTracker.cpp : implementation file
//

#include "stdafx.h"
#include "TimeTracker.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeTracker

CTimeTracker::CTimeTracker()
{

	Factor=0.020000001f;
    StartTime=0;
    TimePos=1.22f;
    DecalX=150;
    nbRows=5;
    Rows[0]=TEXT("Test 1");
    Rows[1]="Test 2";
    Rows[2]="Effects";
    Rows[3]="Sound 1";
    Rows[4]="Sound 2";
    MovingPos=false;

    te[0].Length=4.2;
    te[0].Start=2.1;
    te[0].Type=0;
    te[0].Row=1;
    
    te[1].Length=6.8;
    te[1].Start=3.1;
    te[1].Type=1;
    te[1].Row=3;
    nb2te=2;

    MovingTe=false;
    StartStretch=false;
    EndStretch=false;


}

CTimeTracker::~CTimeTracker()
{
}


BEGIN_MESSAGE_MAP(CTimeTracker, CWnd)
	//{{AFX_MSG_MAP(CTimeTracker)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTimeTracker message handlers

void CTimeTracker::PaintKey(double Start,double Length,int y,int Type) 
{
    CPen plight,pdark;
    CBrush brush1;

    switch(Type)
    {
    case 0:
        pdark.CreatePen(PS_SOLID,1,RGB(80,40,80));
        brush1.CreateSolidBrush(RGB(220,180,220));
        plight.CreatePen(PS_SOLID,1,RGB(250,200,250));
        break;
    case 1:
        pdark.CreatePen(PS_SOLID,1,RGB(125,80,80));
        brush1.CreateSolidBrush(RGB(200,50,50));
        plight.CreatePen(PS_SOLID,1,RGB(220,120,120));

        break;
    case 2:
        break;
    }
    //CDC *myDC=GetDC();
    /*
	    CMemDC memDC(GetDC());
	    CMemDC * myDC = & memDC;
*/
    double x=(Start-StartTime)/Factor;
    double sx=Length/Factor;

    if (x<0)
    {
        sx-=(-x);
        x=0;
    }

    if (x+sx>(Right-DecalX))
    {
        sx-=(x+sx-(Right-DecalX));
    }
    myDC->SelectObject(&plight);
    myDC->MoveTo(x+sx+DecalX,y);
    myDC->LineTo(x+DecalX,y);
    myDC->LineTo(x+DecalX,y+12);

    myDC->SelectObject(&pdark);
    myDC->MoveTo(x+DecalX,y+12);
    myDC->LineTo(x+sx+DecalX,y+12);
    myDC->LineTo(x+sx+DecalX,y);

    myDC->SelectObject(&brush1);
    myDC->FillRect(CRect(x+1+DecalX,y+1,x+sx+DecalX,y+12),&brush1);
    
    plight.DeleteObject();
    pdark.DeleteObject();
    brush1.DeleteObject();

}
void CTimeTracker::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
        RECT rc;
        GetClientRect(&rc);
        double avTime;
        CBrush brush1(RGB(255,50,50));
        int i;


		

        CMemDC memDC(GetDC());


        Down=rc.bottom;
        Right=rc.right;
        
	    myDC = & memDC;

        CFont minifont,minifont2;

        minifont.CreateFont(12,6,0,0,0,FALSE,FALSE,FALSE,0,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"DEFAULT");
        minifont2.CreateFont(14,7,0,0,700,FALSE,FALSE,FALSE,0,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"DEFAULT");

    myDC->MoveTo(DecalX,30);
    myDC->LineTo(Right,30);
    CPen myPen,myPen2,myPen3,myPen4,myPen5,myPen6;
    myPen.CreatePen(PS_SOLID,1,RGB(80,80,80));
    myPen2.CreatePen(PS_SOLID,1,RGB(200,200,200));

    myPen3.CreatePen(PS_SOLID,1,RGB(125,80,80));
    myPen4.CreatePen(PS_SOLID,1,RGB(200,50,50));
    myPen5.CreatePen(PS_SOLID,1,RGB(200,120,150));

    myPen6.CreatePen(PS_SOLID,1,RGB(0,0,0));

    myDC->SelectObject(&myPen);

    myDC->MoveTo(DecalX,29);
    myDC->LineTo(Right,29);

    myDC->MoveTo(DecalX-1,29);
    myDC->LineTo(DecalX-1,Down);

    myDC->SelectObject(&myPen6);
    //myDC->Rectangle(CRect(0,0,rc.right,rc.bottom));//,&CBrush(RGB(255,255,255)));
    brush1.DeleteObject();
    brush1.CreateSolidBrush(RGB(255,255,255));
//    myDC->Rectangle(CRect(0,0,rc.right,rc.bottom));//,&CBrush(RGB(255,255,255)));
    myDC->FillSolidRect(&rc, GetSysColor(COLOR_BTNFACE));

    myDC->SelectObject(&myPen);
    myDC->FillRect(CRect(DecalX,31,Right,Down),&CBrush(RGB(255,255,255)));
    myDC->SetBkMode(TRANSPARENT);

    brush1.DeleteObject();
    brush1.CreateSolidBrush(RGB(255,50,50));


    for(avTime=StartTime;avTime<(StartTime+((Right-DecalX)*Factor));avTime+=Factor)
    {
        myDC->SelectObject(&myPen);

        //
        double avTime2=avTime-StartTime;

        int tmp=(avTime*100);
        if ( (tmp%1000)==0) 
        {
            
            myDC->MoveTo(avTime2/Factor+DecalX,12);
            myDC->LineTo(avTime2/Factor+DecalX,30);

            myDC->SelectObject(&minifont2);
            CString daVal;
            daVal.Format("%.2f",avTime);

            myDC->TextOut(avTime2/Factor+2+DecalX,12,daVal);

            myDC->FillRect(CRect(avTime2/Factor+DecalX,31,DecalX+(avTime2/Factor)+(0.110f)/Factor,Down),&CBrush(RGB(255,230,230)));

        }
        else
        if ( (tmp%100)==0) 
        {
            myDC->MoveTo(avTime2/Factor+DecalX,12);
            myDC->LineTo(avTime2/Factor+DecalX,30);

            myDC->SelectObject(&minifont);
            CString daVal;
            daVal.Format("%.2f",avTime);

            myDC->TextOut(avTime2/Factor+2+DecalX,14,daVal);

            
            myDC->FillRect(CRect(avTime2/Factor+DecalX,31,DecalX+(avTime2/Factor)+(0.110f)/Factor,Down),&CBrush(RGB(240,240,240)));

        }
        else
        if ((tmp%10)==0) 
        {
            myDC->MoveTo(avTime2/Factor+DecalX,26);
            myDC->LineTo(avTime2/Factor+DecalX,30);

        }


        if ((tmp%10)==0) 
        {
            myDC->SelectObject(&myPen2);

            myDC->MoveTo(avTime2/Factor+DecalX,31);
            myDC->LineTo(avTime2/Factor+DecalX,Down);
        }

    }


    myDC->SelectObject(&myPen2);
    myDC->MoveTo(DecalX-1,Down);
    myDC->LineTo(Right,Down);

    for (i=46;i<(Down);i+=16)
    {
        myDC->MoveTo(DecalX,i);
        myDC->LineTo(Right,i);
    }

    for (i=0;i<nb2te;i++)
    {
        PaintKey(te[i].Start,te[i].Length,30+(16*te[i].Row)+2,te[i].Type);
    }



    
    if (TimePos>=StartTime)
    {
        int x=((TimePos-StartTime)/Factor);
    


        myDC->SelectObject(&brush1);
        POINT pts[3];
        pts[0].x=x-7+DecalX;
        pts[0].y=0;
        pts[1].x=x+7+DecalX;
        pts[1].y=0;
        pts[2].x=x+DecalX;
        pts[2].y=10;
        myDC->Polygon(pts,3);

        brush1.DeleteObject();


        myDC->SelectObject(&myPen5);
        myDC->MoveTo(x+DecalX,0);
        myDC->LineTo(x-7+DecalX,0);
        myDC->LineTo(x+DecalX,10);
        myDC->SelectObject(&myPen3);
        myDC->MoveTo(x+DecalX,0);
        myDC->LineTo(x+7+DecalX,0);
        myDC->LineTo(x+DecalX,10);




        myDC->SelectObject(&myPen5);
        myDC->MoveTo(x-1+DecalX,31);
        myDC->LineTo(x-1+DecalX,Down);
        myDC->SelectObject(&myPen4);
        myDC->MoveTo(x+DecalX,31);
        myDC->LineTo(x+DecalX,Down);
        myDC->SelectObject(&myPen3);
        myDC->MoveTo(x+1+DecalX,31);
        myDC->LineTo(x+1+DecalX,Down);
    }

        // Rows
        brush1.DeleteObject();
        brush1.CreateSolidBrush(RGB(255,255,255));

        myDC->SelectObject(&myPen);
        myDC->SelectObject(&brush1);
        myDC->SelectObject(&minifont2);

        myDC->Rectangle(CRect(0,30,DecalX,Down+1));
        for (i=0;i<nbRows;i++)
        {
            myDC->Rectangle(CRect(0,(i*16)+30,DecalX,(i*16)+46+1));
            myDC->TextOut(2,(i*16)+32,Rows[i]);

        }
        
        brush1.DeleteObject();


        myPen.DeleteObject();
        myPen2.DeleteObject();
        myPen3.DeleteObject();
        myPen4.DeleteObject();
        myPen5.DeleteObject();
        myPen6.DeleteObject();

        minifont.DeleteObject();
        minifont2.DeleteObject();
        /*
        sb1.Invalidate(FALSE);
        sb2.Invalidate(FALSE);
        */
}

void CTimeTracker::OnMouseMove(UINT nFlags, CPoint point) 
{
RECT rc;
    GetClientRect(&rc);
    // cursor
    /*
    AfxGetApp()->LoadStandardCursor(IDC_ARROW);

        for (int i=0;i<nb2te;i++)
        {
            double pos=StartTime+((point.x-DecalX)*Factor);
            int daRow=((point.y-30)/16);

            if ( ( (fabs(te[i].Start-pos)/Factor) <3) && (te[i].Row==daRow) )
            {
                AfxGetApp()->LoadStandardCursor(IDC_SIZEWE);
                break;
            }

            if ( ( (fabs(te[i].Start+te[i].Length-pos)/Factor) <3) &&(te[i].Row==daRow) )
            {
                AfxGetApp()->LoadStandardCursor(IDC_SIZENS);
                break;
            }

            if ( (te[i].Start<=pos)&&((te[i].Start+te[i].Length)>=pos)&&(te[i].Row==daRow) )
            {
                AfxGetApp()->LoadStandardCursor(IDC_SIZEALL);
                break;
            }
        }
*/
    // move
        if ((point.x>=DecalX)&&(point.x<=rc.right-20)&&(point.y>=0)&&(point.y<=30)&&(MovingPos))
        {
            TimePos=point.x-DecalX;
            TimePos*=Factor;
            TimePos+=StartTime;
            Invalidate(FALSE);
        }
        else
    {
        if (MovingTe)
        {
            te[teInd].Start+=(((double)point.x-(double)Remem.x)*Factor);
            if (te[teInd].Start<=0) te[teInd].Start=0;
            Remem.x=point.x;
            Invalidate(FALSE);
        }
        else
        {
            if (StartStretch)
            {
                double tmp=StartTime+((point.x-DecalX)*Factor);//(((double)point.x-(double)Remem.x)*Factor);
                //tmp-=fmod(tmp,0.1f);
                //if (tmp>(te[teInd].Length-0.1f)) tmp=(te[teInd].Length-0.1f);
                //if ((te[teInd].Start+tmp)<=0) te[teInd].Start=0;
                //else
                {
                    te[teInd].Start+=tmp;
                    te[teInd].Length-=tmp;
                }
                
                Remem.x=point.x;
/*
                te[teInd].Length=((int)(te[teInd].Length*10.0f));
                te[teInd].Length/=10;
/*
                te[teInd].Start=((int)(te[teInd].Start*10.0f));
                te[teInd].Start/=10;
*/
                //te[teInd].Start-=fabs(fmod(te[teInd].Start,0.1f));
                Invalidate(FALSE);
            }
            else
            {
                if (EndStretch)
                {
                    double tmp=tmp=te[teInd].Start+StartTime+((point.x-DecalX)*Factor);//(((double)point.x-(double)Remem.x)*Factor);
                    //tmp-=fmod(tmp,0.1f);
                    if (tmp<(0.1f)) tmp=0.1f;


                    te[teInd].Length=tmp;
                
                    te[teInd].Length=((int)(te[teInd].Length*10.0f));
                    te[teInd].Length=te[teInd].Length/10.0f;

                    //Remem.x=point.x;
                    Invalidate(FALSE);
                }
            }
        }
    }
	CWnd::OnMouseMove(nFlags, point);
}

void CTimeTracker::OnLButtonUp(UINT nFlags, CPoint point) 
{
	MovingPos=false;
    MovingTe=false;
    EndStretch=false;
    StartStretch=false;
	ReleaseCapture();

	CWnd::OnLButtonUp(nFlags, point);
}

void CTimeTracker::OnLButtonDown(UINT nFlags, CPoint point) 
{
RECT rc;
    GetClientRect(&rc);

        if ((point.x>=DecalX)&&(point.x<=rc.right-20)&&(point.y>=0)&&(point.y<=30))
        {
            TimePos=point.x-DecalX;
            TimePos*=Factor;
            TimePos+=StartTime;
            Invalidate(FALSE);
            MovingPos=true;
			SetCapture();
        }
        else
    {
        for (int i=0;i<nb2te;i++)
        {
            double pos=StartTime+((point.x-DecalX)*Factor);
            int daRow=((point.y-30)/16);

            if ( ( (fabs(te[i].Start-pos)/Factor) <3) && (te[i].Row==daRow) )
            {
                StartStretch=true;
                teInd=i;
                Remem.x=point.x;
				SetCapture();
                break;
            }

            if ( ( (fabs(te[i].Start+te[i].Length-pos)/Factor) <3) &&(te[i].Row==daRow) )
            {
                EndStretch=true;
                teInd=i;
                Remem.x=point.x;
				SetCapture();
                break;
            }

            if ( (te[i].Start<=pos)&&((te[i].Start+te[i].Length)>=pos)&&(te[i].Row==daRow) )
            {
                MovingTe=true;
                teInd=i;
                Remem.x=point.x;
				SetCapture();
                break;
            }
        }
    }
	CWnd::OnLButtonDown(nFlags, point);
}

void CTimeTracker::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
    double pos=StartTime+((point.x-DecalX)*Factor);
    int daRow=((point.y-30)/16);

    if (daRow>=0)
    {
        te[nb2te].Length=2;
        te[nb2te].Row=daRow;
        te[nb2te].Start=pos;
        te[nb2te].Type=0;
        nb2te++;

        Invalidate(FALSE);
    }
	CWnd::OnLButtonDblClk(nFlags, point);
}

BOOL CTimeTracker::Create( const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS, rect, pParentWnd, nID, pContext);
}
