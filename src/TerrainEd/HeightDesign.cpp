// HeightDesign.cpp : implementation file
//

#include "stdafx.h"
#include "TerrainEd.h"
#include "HeightDesign.h"
#include "TerrainEdDlg.h"
#include "rfHillTerrain.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CTerrainEdDlg *MainWind;
extern CTerra m_Terra;
extern int daWaterLevel;
extern CTerraTex m_Texture;
extern CTerraLight m_Lightt;
extern bool TerrainModified;

/////////////////////////////////////////////////////////////////////////////
// CHeightDesign dialog


CHeightDesign::CHeightDesign(CWnd* pParent /*=NULL*/)
	: CDialog(CHeightDesign::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHeightDesign)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHeightDesign::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHeightDesign)
	DDX_Control(pDX, IDC_WATER, m_WaterLevel);
	DDX_Control(pDX, IDC_SLIDER1, m_Strength);
	DDX_Control(pDX, IDC_PZ, m_PaintZone);
	DDX_Control(pDX, IDC_SCROLLBAR2, m_ScrollX);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_ScrollY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHeightDesign, CDialog)
	//{{AFX_MSG_MAP(CHeightDesign)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_GENERATE, OnGenerate)
	ON_BN_CLICKED(IDC_GENERATE2, OnGenerate2)
	ON_BN_CLICKED(IDC_GENERATE3, OnGenerate3)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_WATER, OnReleasedcaptureWater)
	ON_BN_CLICKED(IDC_BLURLIGHTMAP2, OnBlurlightmap2)
	ON_BN_CLICKED(IDC_IMPORT, OnImport)
	ON_BN_CLICKED(IDC_EXPORT, OnExport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHeightDesign message handlers

void CHeightDesign::Init()
{
	RECT rc;

	SCROLLINFO sinfo;
    
    sinfo.nMin=0;
    sinfo.nMax=m_Height.m_img->GetHeight();
    sinfo.nPage=rc.bottom;
    sinfo.cbSize=sizeof(sinfo);
    sinfo.fMask=SIF_PAGE|SIF_RANGE;
    m_ScrollY.SetScrollInfo(&sinfo);

    sinfo.nMin=0;
    sinfo.nMax=m_Height.m_img->GetWidth();
    sinfo.nPage=rc.right;
    sinfo.cbSize=sizeof(sinfo);
    sinfo.fMask=SIF_PAGE|SIF_RANGE;
    m_ScrollX.SetScrollInfo(&sinfo);

    m_Height.PosX=m_ScrollX.GetScrollPos();
    m_Height.PosY=m_ScrollY.GetScrollPos();
    m_Height.Invalidate(FALSE);

    m_WaterLevel.SetRange(0,255);
    m_WaterLevel.SetPos(daWaterLevel);
}


void CHeightDesign::OnSize(UINT nType, int cx, int cy) 
{
    
	CDialog::OnSize(nType, cx, cy);
	
    RECT rc;

    GetClientRect(&rc);

	m_ScrollX.MoveWindow(rc.left,rc.bottom-16,rc.right-16,16,TRUE);
	m_ScrollY.MoveWindow(rc.right-16,rc.top+88,16,rc.bottom-104);

    m_Height.MoveWindow(rc.left,rc.top+88,rc.right-16,rc.bottom-104,FALSE);

    


}

void CHeightDesign::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CHeightDesign::OnClose() 
{
    /*
    CTerrainEdDlg *ptr;


    ptr=(CTerrainEdDlg *)GetParent();
    */
    MainWind->m_HeightWinBt.SetCheck(MainWind->m_HeightWinBt.GetCheck()?0:1);
    MainWind->OnHeightwin();    
//	CDialog::OnClose();
}

BOOL CHeightDesign::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    RECT rc;

    GetClientRect(&rc);

    m_Height.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,CRect(rc.left,rc.top+88,rc.right-16,rc.bottom-16),this,5414);
    m_Height.m_Zone=&m_PaintZone;
	m_Height.m_img=&m_Terra;

	Init();
/*
    SCROLLINFO sinfo;
    
    sinfo.nMin=0;
    sinfo.nMax=512;
    sinfo.nPage=rc.bottom;
    sinfo.nPos=0;
    sinfo.cbSize=sizeof(sinfo);
    sinfo.fMask=SIF_PAGE|SIF_POS|SIF_RANGE;
    m_ScrollY.SetScrollInfo(&sinfo);

    sinfo.nMin=0;
    sinfo.nMax=512;
    sinfo.nPage=rc.right;
    sinfo.nPos=0;
    sinfo.cbSize=sizeof(sinfo);
    sinfo.fMask=SIF_PAGE|SIF_POS|SIF_RANGE;
    m_ScrollX.SetScrollInfo(&sinfo);

    m_dbls.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,CRect(60,10,160,35),this,124);
    m_dbls.SetRange1(0,255);
    m_dbls.SetRange2(0,255);
    m_dbls.SetPos1(128);
    m_dbls.SetPos2(128);

    m_Strength.SetRange(0,255);
    m_Strength.SetPos(32);
    m_Height.m_Strengh=(float)m_Strength.GetPos();
*/
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHeightDesign::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if ( (pScrollBar==&m_ScrollX)&&(nSBCode==SB_THUMBTRACK) )
    {
        m_Height.PosX=nPos;
        m_Height.Invalidate(FALSE);
        pScrollBar->SetScrollPos(nPos,TRUE);
    }
	else
    {
        m_PaintZone.SetVal(m_dbls.GetPos1(),m_dbls.GetPos2());
        m_Height.m_Strengh=(float)m_Strength.GetPos();
    }
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CHeightDesign::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if ( (pScrollBar==&m_ScrollY)&&(nSBCode==SB_THUMBTRACK) )
    {
        m_Height.PosY=nPos;
        m_Height.Invalidate(FALSE);
        pScrollBar->SetScrollPos(nPos,TRUE);
    }
	
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CHeightDesign::OnGenerate() 
{
    m_Terra.GenerateFractal();
    m_Lightt.GenerateLight(&m_Terra, 60,12,255);
    Invalidate(false);
}

void CHeightDesign::OnGenerate2() 
{
	HillTerrain hill(512,10.0,60.0,4000,1,true,rand());

    hill.Generate();

    
    LPBITMAPINFOHEADER BiDest=(LPBITMAPINFOHEADER)GlobalLock(m_Terra.m_hDib);			
    BYTE *lpBits = ((BYTE*)BiDest)+sizeof(BITMAPINFOHEADER);





    for( int x = 0; x < hill.GetSize(); ++x )
    {
        for( int y = 0; y < hill.GetSize(); ++y )
        {
            float z = hill.GetCell( x, y )*255;
            m_Terra.SetPix2(x,y,z,lpBits);
        }
    }
    m_Lightt.GenerateLight(&m_Terra, 60,12,255);
    Invalidate(false);
    GlobalUnlock(m_Terra.m_hDib);	
	TerrainModified=true;
	DrawViews();
}

void CHeightDesign::OnGenerate3() 
{
	HillTerrain hill(512,10.0,60.0,4000,1,false,rand());

    hill.Generate();

    
    LPBITMAPINFOHEADER BiDest=(LPBITMAPINFOHEADER)GlobalLock(m_Terra.m_hDib);			
    BYTE *lpBits = ((BYTE*)BiDest)+sizeof(BITMAPINFOHEADER);





    for( int x = 0; x < hill.GetSize(); ++x )
    {
        for( int y = 0; y < hill.GetSize(); ++y )
        {
            float z = hill.GetCell( x, y )*255;
            m_Terra.SetPix2(x,y,z,lpBits);
        }
    }

    GlobalUnlock(m_Terra.m_hDib);	
    m_Lightt.GenerateLight(&m_Terra, 60,12,255);
	Invalidate(false);
	TerrainModified=true;
	DrawViews();
}

void CHeightDesign::OnReleasedcaptureWater(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_Terra.ReEvaluateWater(m_WaterLevel.GetPos());
    daWaterLevel=m_WaterLevel.GetPos();
    m_Lightt.GenerateLight(&m_Terra, 60,12,255);
    Invalidate(FALSE);	
	TerrainModified=true;
	DrawViews();
	
	*pResult = 0;
}

void CHeightDesign::OnBlurlightmap2() 
{
    m_Terra.Effect24MatrixFilter(FILTER_BLUR_MEAN_7x7);
    daWaterLevel=m_WaterLevel.GetPos();
    m_Lightt.GenerateLight(&m_Terra, 60,12,255);
    Invalidate(FALSE);	
	TerrainModified=true;
	DrawViews();
	
}

void CHeightDesign::OnImport() 
{
    m_Terra.Load(this->m_hWnd);	
	Init();
	m_Lightt.InitRaw(m_Terra.GetWidth(),m_Terra.GetHeight());
    m_Texture.InitRaw(m_Terra.GetWidth(),m_Terra.GetHeight());
	TerrainModified=true;
	DrawViews();
}

void CHeightDesign::OnExport() 
{
    m_Terra.Save(this->m_hWnd);	
}
