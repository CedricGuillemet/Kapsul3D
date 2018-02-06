// PaintZone.cpp : implementation file
//

#include "stdafx.h"
#include <Math.h>

//#include "memmgr/mmgr.h"

#include "PaintZone.h"


#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaintZone

CPaintZone::CPaintZone()
{
    Size1=128;
    Size2=128;
}

CPaintZone::~CPaintZone()
{
}


BEGIN_MESSAGE_MAP(CPaintZone, CStatic)
	//{{AFX_MSG_MAP(CPaintZone)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaintZone message handlers

void CPaintZone::OnPaint() 
{
    int i,j;
    COLORREF inten,inten2;
    int r,g,b;

	CPaintDC dc(this); // device context for painting
	

	RECT rc;

    HPEN WhitePen = CreatePen(PS_SOLID,300,RGB(128,128,128));	//Valid values color

	HPEN OldPen = (HPEN)SelectObject(dc,WhitePen);


    GetClientRect(&rc);
    rc.right--;
    rc.bottom--;
    rc.right&=0xfffe;
    rc.bottom&=0xfffe;

    HBRUSH hbr;
    hbr=(HBRUSH)COLOR_WINDOW;
    //::FillRect(dc.m_hDC,&rc,hbr);

    inten=dc.GetPixel(CPoint(1,1));

    for (i=0;i<=(rc.right/2);i++)
    {
        for (j=0;j<=(rc.bottom/2);j++)
        {
            double dx,dy;
            dx=(i-(rc.right/2));
            dx*=512;
            dx/=rc.right;

            dy=(j-(rc.bottom/2));
            dy*=512;
            dy/=rc.bottom;

            double Len=sqrt(dx*dx+dy*dy);
            if (Len<=Size1)
            {
                dc.SetPixel(CPoint(i,rc.bottom-j),RGB(0,0,0));
                dc.SetPixel(CPoint(rc.right-i,rc.bottom-j),RGB(0,0,0));
                dc.SetPixel(CPoint(rc.right-i,j),RGB(0,0,0));
                dc.SetPixel(CPoint(i,j),RGB(0,0,0));
            }

            if ((Len>Size1)&&(Len<=Size2))
            {
                r=(int)((Len-Size1)*(inten&255))/(Size2-Size1);//(inten&255);
                
                g=(int)(((Len-Size1)*((inten>>8)&255))/(Size2-Size1));

                b=(int)(((Len-Size1)*((inten>>16)&255))/(Size2-Size1));

                inten2=(r&255)+((g&255)<<8)+((b&255)<<16);
                
                dc.SetPixel(CPoint(i,j),inten2);
                dc.SetPixel(CPoint(rc.right-i,rc.bottom-j),inten2);
                dc.SetPixel(CPoint(i,rc.bottom-j),inten2);
                dc.SetPixel(CPoint(rc.right-i,j),inten2);

            }

            if (Len>Size2)
            {
                dc.SetPixel(CPoint(i,j),inten);
                dc.SetPixel(CPoint(rc.right-i,rc.bottom-j),inten);
                dc.SetPixel(CPoint(i,rc.bottom-j),inten);
                dc.SetPixel(CPoint(rc.right-i,j),inten);
            }
        }
    }

    //memset(Brush,0,32*32);
    for (i=0;i<32;i++)
    {
        for (j=0;j<32;j++)
        {
            double Len=sqrt(i*i+j*j)*8;
            if (Len<=Size1)
            {
                Brush[i][j]=255;
            }

            if ((Len>Size1)&&(Len<=Size2))
            {
                r=(int)((Len-Size1)*255)/(Size2-Size1);//(inten&255);
                Brush[i][j]=(255-r);

            }

            if (Len>Size2)
            {
                Brush[i][j]=0;
            }
        }
    }
}

void CPaintZone::SetVal(int s1, int s2)
{
    Size1=s1;
    Size2=s2;
    Invalidate(FALSE);
}
