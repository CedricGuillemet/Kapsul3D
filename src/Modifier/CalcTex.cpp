// CalcTex.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "CalcTex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalcTex dialog


CCalcTex::CCalcTex(CWnd* pParent /*=NULL*/)
	: CDialog(CCalcTex::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalcTex)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCalcTex::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalcTex)
	DDX_Control(pDX, IDC_MAPSPHERICAL, m_MapSphere);
	DDX_Control(pDX, IDC_MAPPLANAR, m_MapPlanar);
	DDX_Control(pDX, IDC_MAPCYL, m_MapCyl);
	DDX_Control(pDX, IDC_MAPCUBE, m_MapCube);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCalcTex, CDialog)
	//{{AFX_MSG_MAP(CCalcTex)
	ON_BN_CLICKED(IDC_MAPCUBE, OnMapcube)
	ON_BN_CLICKED(IDC_MAPCYL, OnMapcyl)
	ON_BN_CLICKED(IDC_MAPPLANAR, OnMapplanar)
	ON_BN_CLICKED(IDC_MAPSPHERICAL, OnMapspherical)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalcTex message handlers

void CCalcTex::OnMapcube() 
{
	if (m_MapCube.GetCheck())
	{
		m_MapSphere.SetCheck(0);
		m_MapCyl.SetCheck(0);
		m_MapPlanar.SetCheck(0);
		m_Plugin->m_KUVEdit.ApplyMapMesh=&m_Plugin->m_KUVEdit.CubeMap;
		m_Plugin->m_KUVEdit.ApplyMapMesh2=&m_Plugin->m_KUVEdit.CubeMap2;
		//m_MapCube.SetCheck(0);
		m_Plugin->m_KUVEdit.TypeMap=1;
		m_Plugin->LastAction=ACTION_MAPPINGEDIT;
	}
	else
		m_Plugin->m_KUVEdit.TypeMap=0;
	DrawViews();
}

void CCalcTex::OnMapcyl() 
{
	if (m_MapCyl.GetCheck())
	{
		m_MapSphere.SetCheck(0);
		//m_MapCyl.SetCheck(0);
		m_MapPlanar.SetCheck(0);
		m_MapCube.SetCheck(0);
		m_Plugin->m_KUVEdit.TypeMap=2;
		m_Plugin->m_KUVEdit.ApplyMapMesh=&m_Plugin->m_KUVEdit.CylMap;
		m_Plugin->m_KUVEdit.ApplyMapMesh2=&m_Plugin->m_KUVEdit.CylMap2;
		m_Plugin->LastAction=ACTION_MAPPINGEDIT;
	}
	else
		m_Plugin->m_KUVEdit.TypeMap=0;
	DrawViews();
}

void CCalcTex::OnMapplanar() 
{
	if (m_MapPlanar.GetCheck())
	{
		m_MapSphere.SetCheck(0);
		m_MapCyl.SetCheck(0);
		//m_MapPlanar.SetCheck(0);
		m_MapCube.SetCheck(0);
		m_Plugin->m_KUVEdit.TypeMap=3;
		m_Plugin->m_KUVEdit.ApplyMapMesh=&m_Plugin->m_KUVEdit.PlanarMap;
		m_Plugin->m_KUVEdit.ApplyMapMesh2=&m_Plugin->m_KUVEdit.PlanarMap2;
		m_Plugin->LastAction=ACTION_MAPPINGEDIT;
	}
	else
		m_Plugin->m_KUVEdit.TypeMap=0;
	DrawViews();
}

void CCalcTex::OnMapspherical() 
{
	if (m_MapSphere.GetCheck())
	{
		//m_MapSphere.SetCheck(0);
		m_MapCyl.SetCheck(0);
		m_MapPlanar.SetCheck(0);
		m_MapCube.SetCheck(0);
		m_Plugin->m_KUVEdit.TypeMap=4;
		m_Plugin->m_KUVEdit.ApplyMapMesh=&m_Plugin->m_KUVEdit.SphereMap;
		m_Plugin->m_KUVEdit.ApplyMapMesh2=&m_Plugin->m_KUVEdit.SphereMap2;
		m_Plugin->LastAction=ACTION_MAPPINGEDIT;
	}
	else
		m_Plugin->m_KUVEdit.TypeMap=0;
	DrawViews();
}
