// ModDiag.cpp : implementation file
//

#include "stdafx.h"

#include "Explode.h"
#include "Extrud.h"
#include "Lathe.h"
#include "Path.h"
#include "Spherize.h"
#include "UVParam.h"
#include "Normals.h"
#include "SubDiv.h"
#include "CalcTex.h"
#include "uvmapperdiag.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CRollupCtrl *m_wndRollupCtrl;
/////////////////////////////////////////////////////////////////////////////
// CModDiag dialog

CModifier m_Modify;
CExplode m_Explode;
CExtrud m_Extrud;
CLathe m_Lathe;
CPath m_Path;
CSpherize m_Spherize;
CUVParam m_UVParam;
CNormals m_Normals;
CSubdiv m_SubDiv;
CFractalize m_Fractalize;
CDivide m_Divide;
CCalcTex m_CalcTex;
CUVMapperDiag m_Mapper;
CPrecalcLight m_Lightmap;

CModDiag::CModDiag(CWnd* pParent /*=NULL*/)
	: CDialog(CModDiag::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModDiag)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CModDiag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModDiag)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModDiag, CDialog)
	//{{AFX_MSG_MAP(CModDiag)
	ON_BN_CLICKED(IDC_OBSP, OnObsp)
	ON_BN_CLICKED(IDC_ODIVIDE, OnOdivide)
	ON_BN_CLICKED(IDC_OEXPLODE, OnOexplode)
	ON_BN_CLICKED(IDC_OEXTRUD, OnOextrud)
	ON_BN_CLICKED(IDC_OFRACTALIZE, OnOfractalize)
	ON_BN_CLICKED(IDC_OLATHE, OnOlathe)
	ON_BN_CLICKED(IDC_ONORMALS, OnOnormals)
	ON_BN_CLICKED(IDC_OPATH, OnOpath)
	ON_BN_CLICKED(IDC_OSPHERIZE, OnOspherize)
	ON_BN_CLICKED(IDC_OTESSELATE, OnOtesselate)
	ON_BN_CLICKED(IDC_OUVMAPPING, OnOuvmapping)
	ON_BN_CLICKED(IDC_LIGHTMAP, OnLightmap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModDiag message handlers
void CModDiag::HideAllPages()
{
	m_Modify.ShowWindow(SW_HIDE);
	m_Normals.ShowWindow(SW_HIDE);
	m_Explode.ShowWindow(SW_HIDE);
	m_Extrud.ShowWindow(SW_HIDE);
	m_Lathe.ShowWindow(SW_HIDE);
	m_Path.ShowWindow(SW_HIDE);
	m_Spherize.ShowWindow(SW_HIDE);
	m_UVParam.ShowWindow(SW_HIDE);
	m_SubDiv.ShowWindow(SW_HIDE);
	m_Fractalize.ShowWindow(SW_HIDE);
	m_Divide.ShowWindow(SW_HIDE);
	m_CalcTex.ShowWindow(SW_HIDE);
	m_Mapper.ShowWindow(SW_HIDE);
	m_Lightmap.ShowWindow(SW_HIDE);

	m_wndRollupCtrl->RemoveAllPages();
}

BOOL CModDiag::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Modify.Create(MAKEINTRESOURCE(IDD_MODIFIER),m_wndRollupCtrl);
	m_Normals.Create(MAKEINTRESOURCE(IDD_NORMALS),m_wndRollupCtrl);
	m_Explode.Create(MAKEINTRESOURCE(IDD_EXPLODE),m_wndRollupCtrl);
	m_Extrud.Create(MAKEINTRESOURCE(IDD_EXTRUD),m_wndRollupCtrl);
	m_Lathe.Create(MAKEINTRESOURCE(IDD_LATHE),m_wndRollupCtrl);
	m_Path.Create(MAKEINTRESOURCE(IDD_PATH),m_wndRollupCtrl);
	m_Spherize.Create(MAKEINTRESOURCE(IDD_SPHERIZE),m_wndRollupCtrl);
	m_UVParam.Create(MAKEINTRESOURCE(IDD_UVPARAM),m_wndRollupCtrl);
	m_SubDiv.Create(MAKEINTRESOURCE(IDD_SUBDIVIDE),m_wndRollupCtrl);
	m_Fractalize.Create(MAKEINTRESOURCE(IDD_FRACTALIZE),m_wndRollupCtrl);
	m_Divide.Create(MAKEINTRESOURCE(IDD_DIVIDE),m_wndRollupCtrl);
	m_CalcTex.Create(MAKEINTRESOURCE(IDD_CALCTEX),m_wndRollupCtrl);
	m_Mapper.Create(MAKEINTRESOURCE(IDD_UVEDIT),m_wndRollupCtrl);
	m_Lightmap.Create(MAKEINTRESOURCE(IDD_PRECALC),m_wndRollupCtrl);

	return TRUE;  
}


void CModDiag::UnSetPlugin(void)
{
	m_Modify.m_Clipper.SetCheck(0);
//	m_Plugin->TypeEdit=0;
}



void CModDiag::OnOK( )
{

}

void CModDiag::OnCancel( )
{

}
void CModDiag::OnObsp() 
{
	HideAllPages();
	m_Modify.ShowWindow(SW_SHOWNORMAL);
	m_wndRollupCtrl->InsertPage("BSP/CSG",&m_Modify,false);
	m_wndRollupCtrl->ExpandPage(0,TRUE);
}

void CModDiag::OnOdivide() 
{
	HideAllPages();
	m_Divide.ShowWindow(SW_SHOWNORMAL);
	m_wndRollupCtrl->InsertPage("Divide",&m_Divide,false);
	m_wndRollupCtrl->ExpandPage(0,TRUE);
}

void CModDiag::OnOexplode() 
{
	HideAllPages();
	m_Explode.ShowWindow(SW_SHOWNORMAL);
	m_wndRollupCtrl->InsertPage("Explode",&m_Explode,false);
	m_wndRollupCtrl->ExpandPage(0,TRUE);
}

void CModDiag::OnOextrud() 
{
	HideAllPages();
	m_Extrud.ShowWindow(SW_SHOWNORMAL);
	m_wndRollupCtrl->InsertPage("Extrud",&m_Extrud,false);
	m_wndRollupCtrl->ExpandPage(0,TRUE);
}

void CModDiag::OnOfractalize() 
{
	HideAllPages();
	m_Fractalize.ShowWindow(SW_SHOWNORMAL);
	m_wndRollupCtrl->InsertPage("Fractalize",&m_Fractalize,false);
	m_wndRollupCtrl->ExpandPage(0,TRUE);	
}

void CModDiag::OnOlathe() 
{
	HideAllPages();
	m_Lathe.ShowWindow(SW_SHOWNORMAL);
	m_UVParam.ShowWindow(SW_SHOWNORMAL);
	m_wndRollupCtrl->InsertPage("Lathe",&m_Lathe,false);
	m_wndRollupCtrl->InsertPage("UV",&m_UVParam,false);
	m_wndRollupCtrl->ExpandPage(0,TRUE);	
	m_wndRollupCtrl->ExpandPage(1,TRUE);	
}

void CModDiag::OnOnormals() 
{
	HideAllPages();
	m_Normals.ShowWindow(SW_SHOWNORMAL);
	m_wndRollupCtrl->InsertPage("Normals",&m_Normals,false);
	m_wndRollupCtrl->ExpandPage(0,TRUE);	
}

void CModDiag::OnOpath() 
{
	HideAllPages();
	m_Path.ShowWindow(SW_SHOWNORMAL);
	m_UVParam.ShowWindow(SW_SHOWNORMAL);
	m_wndRollupCtrl->InsertPage("Path",&m_Path,false);
	m_wndRollupCtrl->InsertPage("UV",&m_UVParam,false);
	m_wndRollupCtrl->ExpandPage(0,TRUE);	
	m_wndRollupCtrl->ExpandPage(1,TRUE);	
}

void CModDiag::OnOspherize() 
{
	HideAllPages();
	m_Spherize.ShowWindow(SW_SHOWNORMAL);
	m_wndRollupCtrl->InsertPage("Spherize",&m_Spherize,false);
	m_wndRollupCtrl->ExpandPage(0,TRUE);	
}

void CModDiag::OnOtesselate() 
{
	HideAllPages();
	m_SubDiv.ShowWindow(SW_SHOWNORMAL);
	m_wndRollupCtrl->InsertPage("Tesselate",&m_SubDiv,false);
	m_wndRollupCtrl->ExpandPage(0,TRUE);	
}

void CModDiag::OnOuvmapping() 
{
	
	HideAllPages();
	m_CalcTex.ShowWindow(SW_SHOWNORMAL);
	m_Mapper.ShowWindow(SW_SHOWNORMAL);
	m_UVParam.ShowWindow(SW_SHOWNORMAL);
	m_wndRollupCtrl->InsertPage("UV Scheme",&m_CalcTex,false);
	m_wndRollupCtrl->InsertPage("UV Edit",&m_Mapper,false);
	m_wndRollupCtrl->InsertPage("UV Scale",&m_UVParam,false);
	m_wndRollupCtrl->ExpandPage(0,TRUE);	
	m_wndRollupCtrl->ExpandPage(1,TRUE);
	m_wndRollupCtrl->ExpandPage(2,TRUE);
}

void CModDiag::OnLightmap() 
{
	HideAllPages();
	m_Lightmap.ShowWindow(SW_SHOWNORMAL);
	m_wndRollupCtrl->InsertPage("Lightmaps",&m_Lightmap,false);
	m_wndRollupCtrl->ExpandPage(0,TRUE);
	
}
