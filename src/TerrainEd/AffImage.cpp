// AffImage.cpp : implementation file
//

#include "stdafx.h"
#include "Terra.h"

#include "TerrainEd.h"
#include "AffImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "TerrainEdDlg.h"

extern CTerra m_Terra;
extern bool TerrainModified;
/////////////////////////////////////////////////////////////////////////////
// CAffImage
extern int daWaterLevel;

CAffImage::CAffImage()
{
    m_img=&m_Terra;
    PosX=0;
    PosY=0;
    m_Down=false;

}

CAffImage::~CAffImage()
{
}


BEGIN_MESSAGE_MAP(CAffImage, CWnd)
	//{{AFX_MSG_MAP(CAffImage)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAffImage message handlers

void CAffImage::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
    RECT rc;
    
    GetClientRect(&rc);

    if (m_img!=NULL)
    {
        m_img->Draw(dc.m_hDC,&rc,DIB_DRAW_SETPALETTE,CRect(PosX,PosY,PosX+rc.right,PosY+rc.bottom));

    }
}

void CAffImage::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    if (m_Down)
    {
        point.x+=PosX;
        point.y+=PosY;
        PaintIt(point,daFact);
        Invalidate(FALSE);
    }
	CWnd::OnMouseMove(nFlags, point);
}

void CAffImage::PaintIt(CPoint point,int Factor)
{
    int r;
    DWORD val;

    for (int i=0;i<32;i++)
    {
        for (int j=0;j<32;j++)
        {
            if ( ((point.x-j)>=0)&&((point.x-j)<512)&&((512-(point.y-i))>=0)&&((512-(point.y-i))<512) )
            {
                val=m_img->GetPix(point.x-j,512-(point.y-i),((BYTE*)BmDest)+sizeof(BITMAPINFOHEADER));
                r=(val&255)+(((float)m_Zone->Brush[j][i]*m_Strengh)/256.0f)*Factor;
                if (r>255) r=255;
                if (r<0) r=0;
                val=r;//((char)(((255.0f/(float)daWaterLevel)*(float)r))<<16)+r;
                m_img->SetPix2(point.x-j,512-(point.y-i),r,((BYTE*)BmDest)+sizeof(BITMAPINFOHEADER));
            }

            if ( ((point.x+j+1)>=0)&&((point.x+j+1)<512)&&((512-(point.y-i))>=0)&&((512-(point.y-i))<512) )
            {
                val=m_img->GetPix(point.x+j+1,512-(point.y-i),((BYTE*)BmDest)+sizeof(BITMAPINFOHEADER));
                r=(val&255)+(((float)m_Zone->Brush[j][i]*m_Strengh)/256.0f)*Factor;
                if (r>255) r=255;
                if (r<0) r=0;
                val=((r<=daWaterLevel)?(((char)(((255.0f/(float)daWaterLevel)*(float)r))<<16)+r):((r<<16)+r));
                m_img->SetPix2(point.x+j+1,512-(point.y-i),r,((BYTE*)BmDest)+sizeof(BITMAPINFOHEADER));
            }

            if ( ((point.x+j+1)>=0)&&((point.x+j+1)<512)&&((512-(point.y+i+1))>=0)&&((512-(point.y+i+1))<512) )
            {
                val=m_img->GetPix(point.x+j+1,512-(point.y+i+1),((BYTE*)BmDest)+sizeof(BITMAPINFOHEADER));
                r=(val&255)+(((float)m_Zone->Brush[j][i]*m_Strengh)/256.0f)*Factor;
                if (r>255) r=255;
                if (r<0) r=0;
                val=((char)(((255.0f/(float)daWaterLevel)*(float)r))<<16)+r;
                m_img->SetPix2(point.x+j+1,512-(point.y+i+1),r,((BYTE*)BmDest)+sizeof(BITMAPINFOHEADER));
            }

            if ( ((point.x-j)>=0)&&((point.x+j+1)<512)&&((512-(point.y+i+1))>=0)&&((512-(point.y+i+1))<512) )
            {
                val=m_img->GetPix(point.x-j,512-(point.y+i+1),((BYTE*)BmDest)+sizeof(BITMAPINFOHEADER));
                r=(val&255)+(((float)m_Zone->Brush[j][i]*m_Strengh)/256.0f)*Factor;
                if (r>255) r=255;
                if (r<0) r=0;
                val=((char)(((255.0f/(float)daWaterLevel)*(float)r))<<16)+r;
                m_img->SetPix2(point.x-j,512-(point.y+i+1),r,((BYTE*)BmDest)+sizeof(BITMAPINFOHEADER));
            }
            
        }
    }

}
void CAffImage::OnLButtonDown(UINT nFlags, CPoint point) 
{
	BmDest = (LPBITMAPINFOHEADER)GlobalLock(m_img->m_hDib);
    SetCapture();
    m_Down=true;
    daFact=1;

    point.x+=PosX;
    point.y+=PosY;

    PaintIt(point,daFact);

    Invalidate(FALSE);
	
	CWnd::OnLButtonDown(nFlags, point);
}

void CAffImage::OnLButtonUp(UINT nFlags, CPoint point) 
{
    ReleaseCapture();
	GlobalUnlock(m_img->m_hDib);
	m_Down=false;
    CTerrainEdDlg *Ptr;
    Ptr=(CTerrainEdDlg*)GetParent();
	TerrainModified=true;
	DrawViews();
//    Ptr->OnReleasedcaptureAngle(NULL, &tmp);
	CWnd::OnLButtonUp(nFlags, point);
}

void CAffImage::OnRButtonDown(UINT nFlags, CPoint point) 
{
    SetCapture();
    BmDest = (LPBITMAPINFOHEADER)GlobalLock(m_img->m_hDib);


    m_Down=true;
    daFact=-1;

    point.x+=PosX;
    point.y+=PosY;

    PaintIt(point,daFact);
    Invalidate(FALSE);
	
	CWnd::OnRButtonDown(nFlags, point);
}

void CAffImage::OnRButtonUp(UINT nFlags, CPoint point) 
{
    ReleaseCapture();
    m_Down=false;
	
    GlobalUnlock(m_img->m_hDib);
	CWnd::OnRButtonUp(nFlags, point);
}

BOOL CAffImage::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return FALSE;//CWnd::OnEraseBkgnd(pDC);
}
