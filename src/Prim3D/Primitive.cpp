// Primitive.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Primitive.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "PrimDiag.h"
#include "headers.h"
extern "C" int TypeEdit;
extern "C" Object *CurrentObj,*LeafObj;
/////////////////////////////////////////////////////////////////////////////
// CPrimitive dialog

IMPLEMENT_DYNCREATE(CPrimitive, CDialog)

extern CMapping m_Mapping;
extern CParameters m_Parameters;
extern CPrimitive m_Primitive;
extern CTreeParam m_TreeParam;


CPrimitive::CPrimitive(CWnd* pParent /*=NULL*/)
	: CDialog(CPrimitive::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrimitive)
	//}}AFX_DATA_INIT
}


void CPrimitive::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrimitive)
	DDX_Control(pDX, IDC_PATCH, m_Patch);
	DDX_Control(pDX, IDC_CONE2, m_Cone2);
	DDX_Control(pDX, IDC_TUBE2, m_Tube2);
	DDX_Control(pDX, IDC_TREE2, m_Tree2);
	DDX_Control(pDX, IDC_TORUS2, m_Torus2);
	DDX_Control(pDX, IDC_SPHERE2, m_Sphere2);
	DDX_Control(pDX, IDC_HEMIS2, m_Hemis2);
	DDX_Control(pDX, IDC_GRID2, m_Grid2);
	DDX_Control(pDX, IDC_CYLINDER2, m_Cylinder2);
	DDX_Control(pDX, IDC_CUBE2, m_Cube2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrimitive, CDialog)
	//{{AFX_MSG_MAP(CPrimitive)
	ON_BN_CLICKED(IDC_CONE2, OnCone2)
	ON_BN_CLICKED(IDC_CUBE2, OnCube2)
	ON_BN_CLICKED(IDC_CYLINDER2, OnCylinder2)
	ON_BN_CLICKED(IDC_GRID2, OnGrid2)
	ON_BN_CLICKED(IDC_HEMIS2, OnHemis2)
	ON_BN_CLICKED(IDC_SPHERE2, OnSphere2)
	ON_BN_CLICKED(IDC_TORUS2, OnTorus2)
	ON_BN_CLICKED(IDC_TREE2, OnTree2)
	ON_BN_CLICKED(IDC_TUBE2, OnTube2)
	ON_BN_CLICKED(IDC_PATCH, OnPatch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrimitive message handlers
extern "C" CPrimDiag *BrowserDiagHWND;
extern "C" CRollupCtrl *m_wndRollupCtrl;
extern "C" int TypeEdit;
extern "C" int nbSegHemis,nbSegSphere,nbSeg1Grid,nbSeg2Grid,nbSeg1Torus,nbSeg2Torus;
extern "C" int nbSeg1Cylinder,nbSeg2Cylinder,nbSeg1Cone,nbSeg2Cone,nbSeg1Tube,nbSeg2Tube,nbSeg1Patch,nbSeg2Patch;

void CPrimitive::OnCone2() 
{
    m_Cone2.SetCheck(1);
	m_Tube2.SetCheck(0);
	m_Tree2.SetCheck(0);
	m_Torus2.SetCheck(0);
	m_Sphere2.SetCheck(0);
	m_Hemis2.SetCheck(0);
	m_Grid2.SetCheck(0);
	m_Cylinder2.SetCheck(0);
	m_Cube2.SetCheck(0);
	m_Patch.SetCheck(0);

    m_wndRollupCtrl->EnablePage(1,TRUE);
    m_wndRollupCtrl->EnablePage(2,FALSE);

    m_wndRollupCtrl->ExpandPage(0,TRUE);
    m_wndRollupCtrl->ExpandPage(1,TRUE);
    m_wndRollupCtrl->ExpandPage(3,TRUE);

    SetPluginActive();
    TypeEdit=6;
    CurrentObj=NULL;
    m_Parameters.SetParams(true,true,1,200,3,200,1,1,nbSeg1Cone,nbSeg2Cone);
}

void CPrimitive::OnCube2() 
{
    m_Cone2.SetCheck(0);
	m_Tube2.SetCheck(0);
	m_Tree2.SetCheck(0);
	m_Torus2.SetCheck(0);
	m_Sphere2.SetCheck(0);
	m_Hemis2.SetCheck(0);
	m_Grid2.SetCheck(0);
	m_Cylinder2.SetCheck(0);
	m_Cube2.SetCheck(1);
	m_Patch.SetCheck(0);
    m_wndRollupCtrl->EnablePage(1,TRUE);
    m_wndRollupCtrl->EnablePage(2,FALSE);

    m_wndRollupCtrl->ExpandPage(0,TRUE);
    m_wndRollupCtrl->ExpandPage(1,TRUE);
    m_wndRollupCtrl->ExpandPage(3,TRUE);

    SetPluginActive();
    TypeEdit=7;
    CurrentObj=NULL;
	
    m_Parameters.SetParams(false,false,0,0,0,0,0,0,0,0);
}

void CPrimitive::OnCylinder2() 
{
    m_Cone2.SetCheck(0);
	m_Tube2.SetCheck(0);
	m_Tree2.SetCheck(0);
	m_Torus2.SetCheck(0);
	m_Sphere2.SetCheck(0);
	m_Hemis2.SetCheck(0);
	m_Grid2.SetCheck(0);
	m_Cylinder2.SetCheck(1);
	m_Cube2.SetCheck(0);
	m_Patch.SetCheck(0);
    m_wndRollupCtrl->EnablePage(1,TRUE);
    m_wndRollupCtrl->EnablePage(2,FALSE);

    m_wndRollupCtrl->ExpandPage(0,TRUE);
    m_wndRollupCtrl->ExpandPage(1,TRUE);
    m_wndRollupCtrl->ExpandPage(3,TRUE);

    SetPluginActive();
    TypeEdit=5;
    CurrentObj=NULL;
	
    m_Parameters.SetParams(true,true,1,200,3,200,1,1,nbSeg1Cylinder,nbSeg2Cylinder);
}

void CPrimitive::OnGrid2() 
{
    m_Cone2.SetCheck(0);
	m_Tube2.SetCheck(0);
	m_Tree2.SetCheck(0);
	m_Torus2.SetCheck(0);
	m_Sphere2.SetCheck(0);
	m_Hemis2.SetCheck(0);
	m_Grid2.SetCheck(1);
	m_Cylinder2.SetCheck(0);
	m_Cube2.SetCheck(0);
	m_Patch.SetCheck(0);
    m_wndRollupCtrl->EnablePage(1,TRUE);
    m_wndRollupCtrl->EnablePage(2,FALSE);

    m_wndRollupCtrl->ExpandPage(0,TRUE);
    m_wndRollupCtrl->ExpandPage(1,TRUE);
    m_wndRollupCtrl->ExpandPage(3,TRUE);

    SetPluginActive();
    TypeEdit=3;
    CurrentObj=NULL;
	
    m_Parameters.SetParams(true,true,1,200,1,200,1,1,nbSeg1Grid,nbSeg2Grid);
}

void CPrimitive::OnHemis2() 
{
    m_Cone2.SetCheck(0);
	m_Tube2.SetCheck(0);
	m_Tree2.SetCheck(0);
	m_Torus2.SetCheck(0);
	m_Sphere2.SetCheck(0);
	m_Hemis2.SetCheck(1);
	m_Grid2.SetCheck(0);
	m_Cylinder2.SetCheck(0);
	m_Cube2.SetCheck(0);
	m_Patch.SetCheck(0);
    m_wndRollupCtrl->EnablePage(1,TRUE);
    m_wndRollupCtrl->EnablePage(2,FALSE);

    m_wndRollupCtrl->ExpandPage(0,TRUE);
    m_wndRollupCtrl->ExpandPage(1,TRUE);
    m_wndRollupCtrl->ExpandPage(3,TRUE);

    SetPluginActive();
    TypeEdit=10;
    CurrentObj=NULL;
	
    m_Parameters.SetParams(true,false,3,200,0,0,1,0,nbSegHemis,0);
}

void CPrimitive::OnSphere2() 
{
	m_Cone2.SetCheck(0);
	m_Tube2.SetCheck(0);
	m_Tree2.SetCheck(0);
	m_Torus2.SetCheck(0);
	m_Sphere2.SetCheck(1);
	m_Hemis2.SetCheck(0);
	m_Grid2.SetCheck(0);
	m_Cylinder2.SetCheck(0);
	m_Cube2.SetCheck(0);
	m_Patch.SetCheck(0);
    m_wndRollupCtrl->EnablePage(1,TRUE);
    m_wndRollupCtrl->EnablePage(2,FALSE);

    m_wndRollupCtrl->ExpandPage(0,TRUE);
    m_wndRollupCtrl->ExpandPage(1,TRUE);
    m_wndRollupCtrl->ExpandPage(3,TRUE);

    SetPluginActive();
    TypeEdit=4;
    CurrentObj=NULL;

    m_Parameters.SetParams(true,false,3,200,0,0,1,0,nbSegSphere,0);
    
}

void CPrimitive::OnTorus2() 
{
    m_Cone2.SetCheck(0);
	m_Tube2.SetCheck(0);
	m_Tree2.SetCheck(0);
	m_Torus2.SetCheck(1);
	m_Sphere2.SetCheck(0);
	m_Hemis2.SetCheck(0);
	m_Grid2.SetCheck(0);
	m_Cylinder2.SetCheck(0);
	m_Cube2.SetCheck(0);
	m_Patch.SetCheck(0);

    m_wndRollupCtrl->EnablePage(1,TRUE);
    m_wndRollupCtrl->EnablePage(2,FALSE);

    m_wndRollupCtrl->ExpandPage(0,TRUE);
    m_wndRollupCtrl->ExpandPage(1,TRUE);
    m_wndRollupCtrl->ExpandPage(3,TRUE);

    

    SetPluginActive();
    TypeEdit=8;
    CurrentObj=NULL;
	
    m_Parameters.SetParams(true,true,1,200,3,200,1,1,nbSeg1Torus,nbSeg2Torus);
}

void CPrimitive::OnTree2() 
{
    m_Cone2.SetCheck(0);
	m_Tube2.SetCheck(0);
	m_Tree2.SetCheck(1);
	m_Torus2.SetCheck(0);
	m_Sphere2.SetCheck(0);
	m_Hemis2.SetCheck(0);
	m_Grid2.SetCheck(0);
	m_Cylinder2.SetCheck(0);
	m_Cube2.SetCheck(0);
	m_Patch.SetCheck(0);

    m_wndRollupCtrl->EnablePage(1,FALSE);
    m_wndRollupCtrl->EnablePage(2,TRUE);

    m_wndRollupCtrl->ExpandPage(0,TRUE);
    m_wndRollupCtrl->ExpandPage(1,FALSE);
    m_wndRollupCtrl->ExpandPage(2,TRUE);
    m_wndRollupCtrl->ExpandPage(3,TRUE);


    SetPluginActive();
    TypeEdit=11;
    CurrentObj=NULL;
	LeafObj=NULL;
}

void CPrimitive::OnTube2() 
{
    m_Cone2.SetCheck(0);
	m_Tube2.SetCheck(1);
	m_Tree2.SetCheck(0);
	m_Torus2.SetCheck(0);
	m_Sphere2.SetCheck(0);
	m_Hemis2.SetCheck(0);
	m_Grid2.SetCheck(0);
	m_Cylinder2.SetCheck(0);
	m_Cube2.SetCheck(0);
	m_Patch.SetCheck(0);
    m_wndRollupCtrl->EnablePage(1,TRUE);
    m_wndRollupCtrl->EnablePage(2,FALSE);

    m_wndRollupCtrl->ExpandPage(0,TRUE);
    m_wndRollupCtrl->ExpandPage(1,TRUE);
    m_wndRollupCtrl->ExpandPage(3,TRUE);

    SetPluginActive();
    TypeEdit=9;
    LeafObj=NULL;
	m_Parameters.SetParams(true,true,1,200,3,200,1,1,nbSeg1Tube,nbSeg2Tube);
}

BOOL CPrimitive::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    m_Cone2.SetCheck(0);
	m_Tube2.SetCheck(0);
	m_Tree2.SetCheck(0);
	m_Torus2.SetCheck(0);
	m_Sphere2.SetCheck(0);
	m_Hemis2.SetCheck(1);
	m_Grid2.SetCheck(0);
	m_Cylinder2.SetCheck(0);
	m_Cube2.SetCheck(0);
	m_Patch.SetCheck(0);
    m_wndRollupCtrl->EnablePage(1,TRUE);
    m_wndRollupCtrl->EnablePage(2,FALSE);

    m_wndRollupCtrl->ExpandPage(0,TRUE);
    m_wndRollupCtrl->ExpandPage(1,TRUE);
    m_wndRollupCtrl->ExpandPage(3,TRUE);

    SetPluginActive();
    OnHemis2();
    

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrimitive::UnSetPlugin(void)
{
    m_Cone2.SetCheck(0);
	m_Tube2.SetCheck(0);
	m_Tree2.SetCheck(0);
	m_Torus2.SetCheck(0);
	m_Sphere2.SetCheck(0);
	m_Hemis2.SetCheck(0);
	m_Grid2.SetCheck(0);
	m_Cylinder2.SetCheck(0);
	m_Cube2.SetCheck(0);
	m_Patch.SetCheck(0);
/*
    m_wndRollupCtrl->EnablePage(1,TRUE);
    m_wndRollupCtrl->EnablePage(2,FALSE);
    m_wndRollupCtrl->EnablePage(3,TRUE);
/*
    m_wndRollupCtrl->ExpandPage(0,TRUE);
    m_wndRollupCtrl->ExpandPage(1,TRUE);
    m_wndRollupCtrl->ExpandPage(3,TRUE);
    */
}


void CPrimitive::OnOK( )
{

}

void CPrimitive::OnCancel( )
{

}
void CPrimitive::OnPatch() 
{
    m_Cone2.SetCheck(0);
	m_Tube2.SetCheck(0);
	m_Tree2.SetCheck(0);
	m_Torus2.SetCheck(0);
	m_Sphere2.SetCheck(0);
	m_Hemis2.SetCheck(0);
	m_Grid2.SetCheck(0);
	m_Cylinder2.SetCheck(0);
	m_Cube2.SetCheck(0);
	m_Patch.SetCheck(1);
    m_wndRollupCtrl->EnablePage(1,TRUE);
    m_wndRollupCtrl->EnablePage(2,FALSE);

    m_wndRollupCtrl->ExpandPage(0,TRUE);
    m_wndRollupCtrl->ExpandPage(1,TRUE);
    m_wndRollupCtrl->ExpandPage(3,TRUE);

    SetPluginActive();
    TypeEdit=12;
    LeafObj=NULL;
	m_Parameters.SetParams(true,true,1,20,1,20,1,1,nbSeg1Patch,nbSeg2Patch);	
}
