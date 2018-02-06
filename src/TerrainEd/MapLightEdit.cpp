// MapLightEdit.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "TerrainEd.h"
#include "MapLightEdit.h"
#include "TerrainEdDlg.h"
#include "Terra.h"
#include "TerraTex.h"
/////////////////////////////////////////////////////////////////////////////
// CMapLightEdit dialog
extern CTerrainEdDlg *MainWind;
extern CTerra m_Terra;
extern CTerraLight m_Lightt;
extern CTerraTex m_Texture;
CKImage Img1,Img2,Img3,Img4,Img5,Img6,Img7,Img8;
CKImage DetailTex,WaterTex;
CKSkyBox daSkyb;
    char SkyBoxName[ _MAX_PATH ];
    char SkyBoxTitle[ _MAX_PATH ];
//CTexture DetailMap;

CMapLightEdit::CMapLightEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CMapLightEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMapLightEdit)
	//}}AFX_DATA_INIT
}


void CMapLightEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMapLightEdit)
	DDX_Control(pDX, IDC_WATER, m_WaterBmp);
	DDX_Control(pDX, IDC_SUN, m_Sun);
	DDX_Control(pDX, IDC_LIGHT, m_Light);
	DDX_Control(pDX, IDC_ANGLE, m_Angle);
	DDX_Control(pDX, IDC_DETAIL, m_Detail);
	DDX_Control(pDX, IDC_SLOP, m_Slop);
	DDX_Control(pDX, IDC_SLIDER9, m_Slid8);
	DDX_Control(pDX, IDC_SLIDER8, m_Slid4);
	DDX_Control(pDX, IDC_SLIDER7, m_Slid7);
	DDX_Control(pDX, IDC_SLIDER6, m_Slid3);
	DDX_Control(pDX, IDC_SLIDER5, m_Slid6);
	DDX_Control(pDX, IDC_SLIDER4, m_Slid2);
	DDX_Control(pDX, IDC_SLIDER3, m_Slid5);
	DDX_Control(pDX, IDC_BTTEX8, m_Tex8);
	DDX_Control(pDX, IDC_BTTEX7, m_Tex4);
	DDX_Control(pDX, IDC_BTTEX6, m_Tex7);
	DDX_Control(pDX, IDC_BTTEX5, m_Tex3);
	DDX_Control(pDX, IDC_BTTEX4, m_Tex6);
	DDX_Control(pDX, IDC_BTTEX3, m_Tex2);
	DDX_Control(pDX, IDC_BTTEX2, m_Tex5);
	DDX_Control(pDX, IDC_SCROLLBAR10, m_ScrollX2);
	DDX_Control(pDX, IDC_SCROLLBAR8, m_ScrollY2);
	DDX_Control(pDX, IDC_SCROLLBAR9, m_ScrollX1);
	DDX_Control(pDX, IDC_SCROLLBAR7, m_ScrollY1);
	DDX_Control(pDX, IDC_SLIDER2, m_Slid1);
	DDX_Control(pDX, IDC_BTTEX1, m_Tex1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMapLightEdit, CDialog)
	//{{AFX_MSG_MAP(CMapLightEdit)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTTEX1, OnBttex1)
	ON_BN_CLICKED(IDC_BTTEX2, OnBttex2)
	ON_BN_CLICKED(IDC_BTTEX3, OnBttex3)
	ON_BN_CLICKED(IDC_BTTEX4, OnBttex4)
	ON_BN_CLICKED(IDC_BTTEX5, OnBttex5)
	ON_BN_CLICKED(IDC_BTTEX6, OnBttex6)
	ON_BN_CLICKED(IDC_BTTEX7, OnBttex7)
	ON_BN_CLICKED(IDC_BTTEX8, OnBttex8)
	ON_WM_PAINT()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLOP, OnReleasedcaptureSlop)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SUN, OnReleasedcaptureSun)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_LIGHT, OnReleasedcaptureLight)
	ON_BN_CLICKED(IDC_DETAIL, OnDetail)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_ANGLE, OnReleasedcaptureAngle)
	ON_BN_CLICKED(IDC_BLURLIGHT, OnBlurlight)
	ON_BN_CLICKED(IDC_SAVEMAP, OnSavemap)
	ON_BN_CLICKED(IDC_WATER, OnWater)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapLightEdit message handlers

void CMapLightEdit::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{

	if ( (pScrollBar==&m_ScrollY1)&&(nSBCode==SB_THUMBTRACK) )
    {
        pScrollBar->SetScrollPos(nPos,TRUE);
        m_Lightt.Draw(GetDC()->m_hDC,CRect(320,138,256,256),DIB_DRAW_SETPALETTE,CRect(m_ScrollX1.GetScrollPos(),m_ScrollY1.GetScrollPos(),m_ScrollX1.GetScrollPos()+256,m_ScrollY1.GetScrollPos()+256));
    }
    else
	if ( (pScrollBar==&m_ScrollY2)&&(nSBCode==SB_THUMBTRACK) )
    {
        pScrollBar->SetScrollPos(nPos,TRUE);
        m_Texture.Draw(GetDC()->m_hDC,CRect(320,412,256,256),DIB_DRAW_SETPALETTE,CRect(m_ScrollX2.GetScrollPos(),m_ScrollY2.GetScrollPos(),m_ScrollX2.GetScrollPos()+256,m_ScrollY2.GetScrollPos()+256));
    }
	else
	if (nSBCode==SB_ENDSCROLL)
    {

        m_Slid1.SetPos(0);

        if (m_Slid2.GetPos()>m_Slid3.GetPos()) m_Slid2.SetPos(m_Slid3.GetPos());
        if (m_Slid3.GetPos()<m_Slid3.GetPos()) m_Slid3.SetPos(m_Slid2.GetPos());
        if (m_Slid3.GetPos()>m_Slid4.GetPos()) m_Slid3.SetPos(m_Slid4.GetPos());

        m_Slid1.SetSelection(0,m_Slid2.GetPos());
        m_Slid2.SetSelection(m_Slid2.GetPos(),m_Slid3.GetPos());
        m_Slid3.SetSelection(m_Slid3.GetPos(),m_Slid4.GetPos());
        m_Slid4.SetSelection(m_Slid4.GetPos(),255);

        m_Slid1.Invalidate(FALSE);
        m_Slid2.Invalidate(FALSE);
        m_Slid3.Invalidate(FALSE);
        m_Slid4.Invalidate(FALSE);

        m_Slid5.SetPos(0);

        if (m_Slid6.GetPos()>m_Slid7.GetPos()) m_Slid6.SetPos(m_Slid7.GetPos());
        if (m_Slid7.GetPos()<m_Slid7.GetPos()) m_Slid7.SetPos(m_Slid6.GetPos());
        if (m_Slid7.GetPos()>m_Slid8.GetPos()) m_Slid7.SetPos(m_Slid8.GetPos());

        m_Slid5.SetSelection(0,m_Slid6.GetPos());
        m_Slid6.SetSelection(m_Slid6.GetPos(),m_Slid7.GetPos());
        m_Slid7.SetSelection(m_Slid7.GetPos(),m_Slid8.GetPos());
        m_Slid8.SetSelection(m_Slid8.GetPos(),255);

        m_Slid5.Invalidate(FALSE);
        m_Slid6.Invalidate(FALSE);
        m_Slid7.Invalidate(FALSE);
        m_Slid8.Invalidate(FALSE);
        GenerateTexMap();
        m_Texture.Draw(GetDC()->m_hDC,CRect(320,412,256,256),DIB_DRAW_SETPALETTE,CRect(m_ScrollX2.GetScrollPos(),m_ScrollY2.GetScrollPos(),m_ScrollX2.GetScrollPos()+256,m_ScrollY2.GetScrollPos()+256));
		DrawViews();
    }

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CMapLightEdit::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if ( (pScrollBar==&m_ScrollX1)&&(nSBCode==SB_THUMBTRACK) )
    {
        pScrollBar->SetScrollPos(nPos,TRUE);
        m_Lightt.Draw(GetDC()->m_hDC,CRect(320,138,256,256),DIB_DRAW_SETPALETTE,CRect(m_ScrollX1.GetScrollPos(),m_ScrollY1.GetScrollPos(),m_ScrollX1.GetScrollPos()+256,m_ScrollY1.GetScrollPos()+256));
    }
    else
	if ( (pScrollBar==&m_ScrollX2)&&(nSBCode==SB_THUMBTRACK) )
    {
        pScrollBar->SetScrollPos(nPos,TRUE);
        m_Texture.Draw(GetDC()->m_hDC,CRect(320,412,256,256),DIB_DRAW_SETPALETTE,CRect(m_ScrollX2.GetScrollPos(),m_ScrollY2.GetScrollPos(),m_ScrollX2.GetScrollPos()+256,m_ScrollY2.GetScrollPos()+256));
    }
    else
    {
        
    }
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CMapLightEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    SCROLLINFO sinfo;
    
    sinfo.nMin=0;
    sinfo.nMax=512;
    sinfo.nPage=256;
    sinfo.nPos=0;
    sinfo.cbSize=sizeof(sinfo);
    sinfo.fMask=SIF_PAGE|SIF_POS|SIF_RANGE;
    m_ScrollY1.SetScrollInfo(&sinfo);

    sinfo.nMin=0;
    sinfo.nMax=512;
    sinfo.nPage=256;
    sinfo.nPos=0;
    sinfo.cbSize=sizeof(sinfo);
    sinfo.fMask=SIF_PAGE|SIF_POS|SIF_RANGE;
    m_ScrollX1.SetScrollInfo(&sinfo);

    sinfo.nMin=0;
    sinfo.nMax=512;
    sinfo.nPage=256;
    sinfo.nPos=0;
    sinfo.cbSize=sizeof(sinfo);
    sinfo.fMask=SIF_PAGE|SIF_POS|SIF_RANGE;
    m_ScrollX2.SetScrollInfo(&sinfo);

    sinfo.nMin=0;
    sinfo.nMax=512;
    sinfo.nPage=256;
    sinfo.nPos=0;
    sinfo.cbSize=sizeof(sinfo);
    sinfo.fMask=SIF_PAGE|SIF_POS|SIF_RANGE;
    m_ScrollY2.SetScrollInfo(&sinfo);
	

    m_Slid1.SetRange(0,255);	
    m_Slid2.SetRange(0,255);
    m_Slid3.SetRange(0,255);
    m_Slid4.SetRange(0,255);

    m_Slid5.SetRange(0,255);	
    m_Slid6.SetRange(0,255);
    m_Slid7.SetRange(0,255);
    m_Slid8.SetRange(0,255);

    m_Slid1.SetPos(0);
    m_Slid2.SetPos(64);
    m_Slid3.SetPos(128);
    m_Slid4.SetPos(192);
    m_Slid5.SetPos(0);
    m_Slid6.SetPos(64);
    m_Slid7.SetPos(128);
    m_Slid8.SetPos(192);


    m_Slop.SetRange(0,180);
    m_Slop.SetPos(45);

//60,12,255

    m_Sun.SetRange(0,255);
    m_Light.SetRange(0,255);
    m_Angle.SetRange(0,90);

    m_Sun.SetPos(255);
    m_Light.SetPos(12);
    m_Angle.SetPos(60);


    if (m_Slid2.GetPos()>m_Slid3.GetPos()) m_Slid2.SetPos(m_Slid3.GetPos());
    if (m_Slid3.GetPos()<m_Slid3.GetPos()) m_Slid3.SetPos(m_Slid2.GetPos());
    if (m_Slid3.GetPos()>m_Slid4.GetPos()) m_Slid3.SetPos(m_Slid4.GetPos());


    if (m_Slid6.GetPos()>m_Slid7.GetPos()) m_Slid6.SetPos(m_Slid7.GetPos());
    if (m_Slid7.GetPos()<m_Slid7.GetPos()) m_Slid7.SetPos(m_Slid6.GetPos());
    if (m_Slid7.GetPos()>m_Slid8.GetPos()) m_Slid7.SetPos(m_Slid8.GetPos());



    m_Slid1.SetSelection(0,m_Slid2.GetPos());
    m_Slid2.SetSelection(m_Slid2.GetPos(),m_Slid3.GetPos());
    m_Slid3.SetSelection(m_Slid3.GetPos(),m_Slid4.GetPos());
    m_Slid4.SetSelection(m_Slid4.GetPos(),255);

    m_Slid5.SetSelection(0,m_Slid2.GetPos());
    m_Slid6.SetSelection(m_Slid2.GetPos(),m_Slid3.GetPos());
    m_Slid7.SetSelection(m_Slid3.GetPos(),m_Slid4.GetPos());
    m_Slid8.SetSelection(m_Slid4.GetPos(),255);

    m_Slid1.Invalidate(FALSE);
    m_Slid2.Invalidate(FALSE);
    m_Slid3.Invalidate(FALSE);
    m_Slid4.Invalidate(FALSE);

    m_Slid5.Invalidate(FALSE);
    m_Slid6.Invalidate(FALSE);
    m_Slid7.Invalidate(FALSE);
    m_Slid8.Invalidate(FALSE);


    Img1.LoadFile("textures\\under-water.jpg");
    Img2.LoadFile("textures\\LAND-Sandly.TGA");
    Img3.LoadFile("textures\\Texture2.tga");
    Img4.LoadFile("textures\\ROCK-Lined.TGA");

    Img5.LoadFile("textures\\under-water.jpg");
    Img6.LoadFile("textures\\LAND-Sandly.TGA");
    Img7.LoadFile("textures\\Texture2.tga");
    Img8.LoadFile("textures\\ROCK-Lined.TGA");


    Img1.Draw(GetDC()->m_hDC,CRect(600,8+32,128,128));	
    m_Tex1.SetWindowText("under-water.jpg");

    Img2.Draw(GetDC()->m_hDC,CRect(600,156+32,128,128));	
    m_Tex2.SetWindowText("LAND-Sandly.TGA");

    Img3.Draw(GetDC()->m_hDC,CRect(600,304+32,128,128));	
    m_Tex3.SetWindowText("Texture2.tga");

    Img4.Draw(GetDC()->m_hDC,CRect(600,452+32,128,128));	
    m_Tex4.SetWindowText("ROCK-Lined.TGA");


    Img5.Draw(GetDC()->m_hDC,CRect(600,8+32,128,128));	
    m_Tex5.SetWindowText("under-water.jpg");

    Img6.Draw(GetDC()->m_hDC,CRect(600,156+32,128,128));	
    m_Tex6.SetWindowText("LAND-Sandly.TGA");

    Img7.Draw(GetDC()->m_hDC,CRect(600,304+32,128,128));	
    m_Tex7.SetWindowText("Texture2.tga");

    Img8.Draw(GetDC()->m_hDC,CRect(600,452+32,128,128));	
    m_Tex8.SetWindowText("ROCK-Lined.TGA");

    GenerateTexMap();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMapLightEdit::OnClose() 
{
    MainWind->m_LightWin.SetCheck(MainWind->m_LightWin.GetCheck()?0:1);
    MainWind->OnLightwin();
	
//	CDialog::OnClose();
}

void CMapLightEdit::OnBttex1() 
{
    if (Img1.Load(m_hWnd)) 
    {
        char title[MAX_PATH];
        //Img1.Draw(GetDC()->m_hDC,CRect(600,8+32,128,128));	
		_splitpath(Img1.FileName, NULL, NULL, title, NULL);
        m_Tex1.SetWindowText(title);
        GenerateTexMap();
        Invalidate(FALSE);
    }
	
}

void CMapLightEdit::OnBttex2() 
{
    if (Img5.Load(m_hWnd)) 
    {
        char title[MAX_PATH];
        //Img1.Draw(GetDC()->m_hDC,CRect(600,8,128,128));	
		_splitpath(Img5.FileName, NULL, NULL, title, NULL);
        m_Tex5.SetWindowText(title);
        GenerateTexMap();
        Invalidate(FALSE);
    }
	
}

void CMapLightEdit::OnBttex3() 
{
    if (Img2.Load(m_hWnd)) 
    {
        char title[MAX_PATH];
        //Img1.Draw(GetDC()->m_hDC,CRect(600,8,128,128));	
		_splitpath(Img2.FileName, NULL, NULL, title, NULL);
        m_Tex2.SetWindowText(title);
        GenerateTexMap();
        Invalidate(FALSE);
    }
	
}

void CMapLightEdit::OnBttex4() 
{
    if (Img6.Load(m_hWnd)) 
    {
        char title[MAX_PATH];
        //Img1.Draw(GetDC()->m_hDC,CRect(600,8,128,128));	
		_splitpath(Img6.FileName, NULL, NULL, title, NULL);
        m_Tex6.SetWindowText(title);
        GenerateTexMap();
        Invalidate(FALSE);
    }
	
}

void CMapLightEdit::OnBttex5() 
{
    if (Img7.Load(m_hWnd)) 
    {
        char title[MAX_PATH];
        //Img1.Draw(GetDC()->m_hDC,CRect(600,8,128,128));	
		_splitpath(Img7.FileName, NULL, NULL, title, NULL);
        m_Tex3.SetWindowText(title);
        GenerateTexMap();
        Invalidate(FALSE);
    }
	
}

void CMapLightEdit::OnBttex6() 
{
    if (Img3.Load(m_hWnd)) 
    {
        char title[MAX_PATH];
        //Img1.Draw(GetDC()->m_hDC,CRect(600,8,128,128));	
		_splitpath(Img3.FileName, NULL, NULL, title, NULL);
        m_Tex7.SetWindowText(title);
        GenerateTexMap();
        Invalidate(FALSE);
    }
	
}

void CMapLightEdit::OnBttex7() 
{
    if (Img8.Load(m_hWnd)) 
    {
        char title[MAX_PATH];
        //Img1.Draw(GetDC()->m_hDC,CRect(600,8,128,128));	
		_splitpath(Img8.FileName, NULL, NULL, title, NULL);
        m_Tex4.SetWindowText(title);
        GenerateTexMap();
        Invalidate(FALSE);
    }
	
}

void CMapLightEdit::OnBttex8() 
{
    if (Img4.Load(m_hWnd)) 
    {
        char title[MAX_PATH];
        //Img1.Draw(GetDC()->m_hDC,CRect(600,8,128,128));	
		_splitpath(Img4.FileName, NULL, NULL, title, NULL);
        m_Tex8.SetWindowText(title);
        GenerateTexMap();
        Invalidate(FALSE);
    }
	
}

void CMapLightEdit::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
    Img1.Draw(dc.m_hDC,CRect(24,58+32,128,128));	
    Img2.Draw(dc.m_hDC,CRect(24,208+32,128,128));	
    Img3.Draw(dc.m_hDC,CRect(24,358+32,128,128));
    Img4.Draw(dc.m_hDC,CRect(24,508+32,128,128));	

    Img5.Draw(dc.m_hDC,CRect(180,58+32,128,128));	
    Img6.Draw(dc.m_hDC,CRect(180,208+32,128,128));	
    Img7.Draw(dc.m_hDC,CRect(180,358+32,128,128));
    Img8.Draw(dc.m_hDC,CRect(180,508+32,128,128));	

    m_Texture.Draw(GetDC()->m_hDC,CRect(320,380+32,256,256),DIB_DRAW_SETPALETTE,CRect(m_ScrollX2.GetScrollPos(),m_ScrollY2.GetScrollPos(),m_ScrollX2.GetScrollPos()+256,m_ScrollY2.GetScrollPos()+256));
    m_Lightt.Draw(GetDC()->m_hDC,CRect(320,106+32,256,256),DIB_DRAW_SETPALETTE,CRect(m_ScrollX1.GetScrollPos(),m_ScrollY1.GetScrollPos(),m_ScrollX1.GetScrollPos()+256,m_ScrollY1.GetScrollPos()+256));
}


void CMapLightEdit::GenerateTexMap(void)
{
    
    MAPSINFO mapsinfo[16];

    if ((strlen(Img1.FileName)>0)&&(strlen(Img2.FileName)>0)&&(strlen(Img3.FileName)>0)&&(strlen(Img4.FileName)>0))
    {


        mapsinfo[0].img=&Img1;
        mapsinfo[0].iStart=0;
        mapsinfo[0].iEnd=m_Slid2.GetPos();
        mapsinfo[0].iSizeX=Img1.GetWidth();
        mapsinfo[0].iSizeY=Img1.GetHeight();
        LPBITMAPINFOHEADER BiInfo1=(LPBITMAPINFOHEADER)GlobalLock(Img1.m_hDib);
        mapsinfo[0].lpBits = ((BYTE*)BiInfo1)+sizeof(BITMAPINFOHEADER);
        mapsinfo[0].SlopMin=0;
        mapsinfo[0].SlopMax=((float)m_Slop.GetPos()/256.0f);

        mapsinfo[1].img=&Img5;
        mapsinfo[1].iStart=m_Slid2.GetPos();
        mapsinfo[1].iEnd=m_Slid3.GetPos();
        mapsinfo[1].iSizeX=Img2.GetWidth();
        mapsinfo[1].iSizeY=Img2.GetHeight();
        LPBITMAPINFOHEADER BiInfo2=(LPBITMAPINFOHEADER)GlobalLock(Img2.m_hDib);
        mapsinfo[1].lpBits = ((BYTE*)BiInfo2)+sizeof(BITMAPINFOHEADER);
        mapsinfo[1].SlopMin=0;
        mapsinfo[1].SlopMax=((float)m_Slop.GetPos()/256.0f);

        mapsinfo[2].img=&Img2;
        mapsinfo[2].iStart=m_Slid3.GetPos();
        mapsinfo[2].iEnd=m_Slid4.GetPos();
        mapsinfo[2].iSizeX=Img3.GetWidth();
        mapsinfo[2].iSizeY=Img3.GetHeight();
        LPBITMAPINFOHEADER BiInfo3=(LPBITMAPINFOHEADER)GlobalLock(Img3.m_hDib);
        mapsinfo[2].lpBits = ((BYTE*)BiInfo3)+sizeof(BITMAPINFOHEADER);
        mapsinfo[2].SlopMin=0;
        mapsinfo[2].SlopMax=((float)m_Slop.GetPos()/256.0f);

        mapsinfo[3].img=&Img6;
        mapsinfo[3].iStart=m_Slid4.GetPos();
        mapsinfo[3].iEnd=255;
        mapsinfo[3].iSizeX=Img4.GetWidth();
        mapsinfo[3].iSizeY=Img4.GetHeight();
        LPBITMAPINFOHEADER BiInfo4=(LPBITMAPINFOHEADER)GlobalLock(Img4.m_hDib);
        mapsinfo[3].lpBits = ((BYTE*)BiInfo4)+sizeof(BITMAPINFOHEADER);
        mapsinfo[3].SlopMin=0;
        mapsinfo[3].SlopMax=((float)m_Slop.GetPos()/256.0f);


        mapsinfo[4].img=&Img7;
        mapsinfo[4].iStart=0;
        mapsinfo[4].iEnd=m_Slid6.GetPos();
        mapsinfo[4].iSizeX=Img5.GetWidth();
        mapsinfo[4].iSizeY=Img5.GetHeight();
        LPBITMAPINFOHEADER BiInfo5=(LPBITMAPINFOHEADER)GlobalLock(Img5.m_hDib);
        mapsinfo[4].lpBits = ((BYTE*)BiInfo5)+sizeof(BITMAPINFOHEADER);
        mapsinfo[4].SlopMax=1;
        mapsinfo[4].SlopMin=((float)m_Slop.GetPos()/256.0f);

        mapsinfo[5].img=&Img3;
        mapsinfo[5].iStart=m_Slid6.GetPos();
        mapsinfo[5].iEnd=m_Slid7.GetPos();
        mapsinfo[5].iSizeX=Img6.GetWidth();
        mapsinfo[5].iSizeY=Img6.GetHeight();
        LPBITMAPINFOHEADER BiInfo6=(LPBITMAPINFOHEADER)GlobalLock(Img6.m_hDib);
        mapsinfo[5].lpBits = ((BYTE*)BiInfo6)+sizeof(BITMAPINFOHEADER);
        mapsinfo[5].SlopMax=1;
        mapsinfo[5].SlopMin=((float)m_Slop.GetPos()/256.0f);

        mapsinfo[6].img=&Img8;
        mapsinfo[6].iStart=m_Slid7.GetPos();
        mapsinfo[6].iEnd=m_Slid8.GetPos();
        mapsinfo[6].iSizeX=Img7.GetWidth();
        mapsinfo[6].iSizeY=Img7.GetHeight();
        LPBITMAPINFOHEADER BiInfo7=(LPBITMAPINFOHEADER)GlobalLock(Img7.m_hDib);
        mapsinfo[6].lpBits = ((BYTE*)BiInfo7)+sizeof(BITMAPINFOHEADER);
        mapsinfo[6].SlopMax=1;
        mapsinfo[6].SlopMin=((float)m_Slop.GetPos()/256.0f);

        mapsinfo[7].img=&Img4;
        mapsinfo[7].iStart=m_Slid8.GetPos();
        mapsinfo[7].iEnd=255;
        mapsinfo[7].iSizeX=Img8.GetWidth();
        mapsinfo[7].iSizeY=Img8.GetHeight();
        LPBITMAPINFOHEADER BiInfo8=(LPBITMAPINFOHEADER)GlobalLock(Img8.m_hDib);
        mapsinfo[7].lpBits = ((BYTE*)BiInfo8)+sizeof(BITMAPINFOHEADER);
        mapsinfo[7].SlopMax=1;
        mapsinfo[7].SlopMin=((float)m_Slop.GetPos()/256.0f);

        m_Texture.GenerateMap(mapsinfo,(CTerra*)&m_Terra,&m_Lightt);
		DrawViews();
       // m_Texture.Draw(GetDC()->m_hDC,CRect(280,300,256,256),DIB_DRAW_SETPALETTE,CRect(MapPosX,MapPosY,MapPosX+256,MapPosY+256));

/*
        GlobalLock(BiInfo4);
        GlobalLock(BiInfo3);
        GlobalLock(BiInfo2);
        GlobalLock(BiInfo1);
        */
    }

}

void CMapLightEdit::OnReleasedcaptureSlop(NMHDR* pNMHDR, LRESULT* pResult) 
{
    GenerateTexMap();
    Invalidate(FALSE);
	
	*pResult = 0;
}

void CMapLightEdit::OnReleasedcaptureSun(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_Lightt.GenerateLight(&m_Terra,m_Angle.GetPos(),m_Light.GetPos(),m_Sun.GetPos());
    GenerateTexMap();
    Invalidate(FALSE);

	*pResult = 0;
}

void CMapLightEdit::OnReleasedcaptureLight(NMHDR* pNMHDR, LRESULT* pResult) 
{
    m_Lightt.GenerateLight(&m_Terra,m_Angle.GetPos(),m_Light.GetPos(),m_Sun.GetPos());
    GenerateTexMap();
    Invalidate(FALSE);
	
	*pResult = 0;
}

void CMapLightEdit::OnDetail() 
{
    if (DetailTex.Load(m_hWnd)) 
    {
        char title[MAX_PATH];
        //DetailMap.FileName,
		_splitpath(DetailTex.FileName, NULL, NULL, title, NULL);
        m_Detail.SetWindowText(title);
    }
}

void CMapLightEdit::OnReleasedcaptureAngle(NMHDR* pNMHDR, LRESULT* pResult) 
{
    m_Lightt.GenerateLight(&m_Terra,m_Angle.GetPos(),m_Light.GetPos(),m_Sun.GetPos());
    GenerateTexMap();
    Invalidate(FALSE);

	*pResult = 0;
}

void CMapLightEdit::OnBlurlight() 
{
    m_Lightt.Effect24MatrixFilter(FILTER_BLUR_MEAN_7x7);
    GenerateTexMap();
    Invalidate(FALSE);
}

void CMapLightEdit::OnSavemap() 
{
    m_Texture.Save(this->m_hWnd);
}
void CMapLightEdit::OnWater() 
{
    if (WaterTex.Load(m_hWnd)) 
    {
        char title[MAX_PATH];
        //DetailMap.FileName,
		_splitpath(WaterTex.FileName, NULL, NULL, title, NULL);
        m_WaterBmp.SetWindowText(title);
    }
	
}
