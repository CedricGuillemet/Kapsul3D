// DumpInfos.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "CityDiag.h"
#include <vector>

using std::vector;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCityDiag dialog
extern "C" vector<Assigns> ass;
extern "C" Object *obase,*omedian[5],*oend;
extern "C" Desk *dk;

extern "C" void GenBuilding(void);

CCityDiag::CCityDiag(CWnd* pParent /*=NULL*/)
	: CDialog(CCityDiag::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCityDiag)
	//}}AFX_DATA_INIT
}


void CCityDiag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCityDiag)
	DDX_Control(pDX, IDC_MAPDIRS, m_MapsDir);
	DDX_Control(pDX, IDC_SHAPENAME, m_ShapeName);
	DDX_Control(pDX, IDC_MEDIAN, m_Median);
	DDX_Control(pDX, IDC_END, m_End);
	DDX_Control(pDX, IDC_BASE, m_Base);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCityDiag, CDialog)
	//{{AFX_MSG_MAP(CCityDiag)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_GETSHAPE, OnGetshape)
	ON_BN_CLICKED(IDC_NEW, OnNew)
	ON_BN_CLICKED(IDC_GENERATE, OnGenerate)
	ON_BN_CLICKED(IDC_PLUS, OnPlus)
	ON_BN_CLICKED(IDC_MOINS, OnMoins)
	ON_BN_CLICKED(IDC_BASE, OnBase)
	ON_BN_CLICKED(IDC_END, OnEnd)
	ON_BN_CLICKED(IDC_MEDIAN, OnMedian)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

extern "C" int obj,objvert,objface,camera,shape,segment,spot,omni,skeletton,bone,emitter;
/////////////////////////////////////////////////////////////////////////////
// CCityDiag message handlers

void CCityDiag::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

}

BOOL CCityDiag::OnInitDialog() 
{
	CDialog::OnInitDialog();
/*	
	if (KOption.GetnbMapDir()>0)
    {
        SendDlgItemMessage(hDlg,IDC_MAPDIRS,CB_RESETCONTENT,0,0);

        for (int i=0;i<KOption.GetnbMapDir();i++)
        {
			m_MapsDir.AddString(KOption.GetMapDir(i));
        }
		m_MapsDir.SetCurSel(0);

    }
*/	
	    srand( (unsigned)time( NULL ) );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCityDiag::OnOK( )
{

}

void CCityDiag::OnCancel( )
{

}

void CCityDiag::OnGetshape() 
{
	// TODO: Add your control notification handler code here
	
}

void CCityDiag::OnNew() 
{
	int i;

    srand( (unsigned)rand() );
    obase=new Object(dk,NULL,NULL);
	obase->OptimDirty=false;
    for (i=0;i<5;i++)
	{
        omedian[i]=new Object(dk,NULL,NULL);
		omedian[i]->OptimDirty=false;
	}

    oend=new Object(dk,NULL,NULL);
	oend->OptimDirty=false;


    GenBuilding();
    DrawViews();
}

void CCityDiag::OnGenerate() 
{
	int i;
    dk->AddObject(obase);
	dk->NextObject->OptimDirty=false;
    for (i=0;i<5;i++)
	{
        dk->AddObject(omedian[i]);
		dk->NextObject->OptimDirty=false;
	}

    dk->AddObject(oend);
	dk->NextObject->OptimDirty=false;
}

void CCityDiag::OnPlus() 
{
	// TODO: Add your control notification handler code here
	
}

void CCityDiag::OnMoins() 
{
	// TODO: Add your control notification handler code here
	
}

void CCityDiag::OnBase() 
{
	if (m_Base.GetCheck()==BST_CHECKED)
        ass[ass.size()-1].UseBase=true;
    else
        ass[ass.size()-1].UseBase=false;
}

void CCityDiag::OnEnd() 
{
	if (m_End.GetCheck()==BST_CHECKED)
        ass[ass.size()-1].UseEnd=true;
    else
        ass[ass.size()-1].UseEnd=false;	
}

void CCityDiag::OnMedian() 
{
	if (m_Median.GetCheck()==BST_CHECKED)
        ass[ass.size()-1].UseMedian=true;
    else
        ass[ass.size()-1].UseMedian=false;	
}
