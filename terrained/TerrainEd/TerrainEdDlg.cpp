// TerrainEdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TerrainEd.h"
#include "TerrainEdDlg.h"
#include "OglViewer.h"
#include "../Prim3D/tree/tree/tree.h"
#include "rfHillTerrain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CTerraTex m_Texture;
CTerra m_Terra;
CTerraLight m_Lightt;
//CSkyBoxEd m_SkyBox;


int daWaterLevel=64;

extern Object *daTrees[1024];
extern Object *daLeaf[1024];
//extern Vertex Pos[1024];
extern Desk *dk;

CTerrainEdDlg *MainWind;
/////////////////////////////////////////////////////////////////////////////
// CTerrainEdDlg dialog

CTerrainEdDlg::CTerrainEdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTerrainEdDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTerrainEdDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTerrainEdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTerrainEdDlg)
	DDX_Control(pDX, IDC_LIGHTWIN, m_LightWin);
	DDX_Control(pDX, IDC_HEIGHTWIN, m_HeightWinBt);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_SIZELAND, m_SizeLand);
	DDX_Control(pDX, IDC_GENERATE, m_Strips);
}

BEGIN_MESSAGE_MAP(CTerrainEdDlg, CDialog)
	//{{AFX_MSG_MAP(CTerrainEdDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_HEIGHTWIN, OnHeightwin)
	ON_BN_CLICKED(IDC_LIGHTWIN, OnLightwin)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_GENERATE, OnBnClickedGenerate)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTerrainEdDlg message handlers

BOOL CTerrainEdDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
    MainWind=this;
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	

    m_Terra.InitRaw(1024,1024);
	m_Terra.GenerateFractal();

    m_Lightt.InitRaw(1024,1024);
    m_Lightt.GenerateLight(&m_Terra, 60,12,255);

    //m_Lightt.Effect24MatrixFilter(FILTER_BLUR_MEAN_7x7);
    m_Texture.InitRaw(1024,1024);

/*
    m_SkyBox.Create(IDD_SKYBOX,this);
    m_SkyBox.ShowWindow(SW_HIDE);
*/
    htDesign.Create(IDD_HEIGHTDESIGN,this);
    htDesign.ShowWindow(SW_HIDE);

    mlDesign.Create(IDD_MAPEDIT,this);
    htDesign.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTerrainEdDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
        CPaintDC dc(this); // device context for painting

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTerrainEdDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTerrainEdDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CTerrainEdDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
 
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CTerrainEdDlg::GenerateTrees(int Min,int Max,int dens,CTerra *dater)
{
	/*
    int x,y;
    bool SetIt;
    int av=0;

    LPBITMAPINFOHEADER BiTerrain=(LPBITMAPINFOHEADER)GlobalLock(dater->m_hDib);
    LPBITMAPINFOHEADER BiTrees=(LPBITMAPINFOHEADER)GlobalLock(m_Trees.m_hDib);

    BYTE *lpBitsTer = ((BYTE*)BiTerrain)+sizeof(BITMAPINFOHEADER);
    BYTE *lpBitsTrees = ((BYTE*)BiTrees)+sizeof(BITMAPINFOHEADER);

    BYTE *lpBitsTer2,*lpBitsTrees2;

    memset(lpBitsTrees,0,1024*1024*3);

    for (int i=0;i<dens;i++)
    {
        SetIt=false;
        av=0;
        while ((!SetIt)&&(av<100))
        {
            x=rand()&1023;
            y=rand()&1023;
            lpBitsTer2=lpBitsTer;
            lpBitsTer2+=(y*1024*3)+(x*3);

            if ( ((*lpBitsTer2)>Min) && ((*lpBitsTer2)<Max) )
                SetIt=true;
            av++;
        }

        if (SetIt)
        {
            Pos[i].vx=x;
            Pos[i].vy=y;
            Pos[i].vz=m_Terra.FindHeightAt(x,y);

            lpBitsTrees2=lpBitsTrees;
            lpBitsTrees2+=(y*1024*3)+(x*3);

            (*lpBitsTrees2++)=255;
            (*lpBitsTrees2++)=255;
            (*lpBitsTrees2++)=255;
        }
    }


    GlobalUnlock(dater->m_hDib);
    GlobalUnlock(m_Trees.m_hDib);
*/
}

void CTerrainEdDlg::OnHeightwin() 
{
    if (m_HeightWinBt.GetCheck()!=0)
        htDesign.ShowWindow(SW_SHOWNORMAL);        
    else
        htDesign.ShowWindow(SW_HIDE);
}

void CTerrainEdDlg::OnLightwin() 
{
    if (m_LightWin.GetCheck()!=0)
        mlDesign.ShowWindow(SW_SHOWNORMAL);        
    else
        mlDesign.ShowWindow(SW_HIDE);
}

extern "C" void BuildObject(void);

void CTerrainEdDlg::OnBnClickedGenerate()
{
	BuildObject();
}
