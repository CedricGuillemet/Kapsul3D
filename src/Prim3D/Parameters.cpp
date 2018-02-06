// Parameters.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Parameters.h"
#include "modprim3D.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParameters dialog

IMPLEMENT_DYNCREATE(CParameters, CDialog)

CParameters::CParameters(CWnd* pParent /*=NULL*/)
	: CDialog(CParameters::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParameters)
	//}}AFX_DATA_INIT
}


void CParameters::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParameters)
	DDX_Control(pDX, IDC_SPIN5, m_Spin3);
	DDX_Control(pDX, IDC_EDIT4, m_Edit3);
	DDX_Control(pDX, IDC_SPIN2, m_Spin2);
	DDX_Control(pDX, IDC_SPIN1, m_Spin1);
	DDX_Control(pDX, IDC_EDIT3, m_Edit2);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_AUTOUV, m_AutoUV);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParameters, CDialog)
	//{{AFX_MSG_MAP(CParameters)
	ON_BN_CLICKED(IDC_AUTOUV, OnAutouv)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParameters message handlers

BOOL CParameters::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	/*
	m_Spin1.SetBuddy(&m_Edit1);
	m_Spin1.SetRange(0.10f, 100.0f);
	m_Spin1.SetPos(1.0f);
	m_Spin1.SetDelta(0.1f);

	m_Spin2.SetBuddy(&m_Edit2);
	m_Spin2.SetRange(0.10f, 100.0f);
	m_Spin2.SetPos(1.0f);
	m_Spin2.SetDelta(0.1f);
*/
	//m_Spin1.SetRange(
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CParameters::SetParams(bool B1Enabled,bool B2Enabled,float B1Min,float B1Max,float B2Min,float B2Max,float B1Delta,float B2Delta,float B1Pos,float B2Pos,
							bool B3Enabled,float B3Min,float B3Max,float B3Delta,float B3Pos)
{
	/*
    m_Spin1.EnableWindow(B1Enabled);
    m_Spin2.EnableWindow(B2Enabled);

	m_Spin1.SetRange(B1Min,B1Max);
	m_Spin1.SetPos(B1Pos);
//	m_Spin1.SetDelta(B1Delta);

	m_Spin2.SetRange(B2Min,B2Max);
	m_Spin2.SetPos(B2Pos);

	SetText1(m_Spin1.GetPos());
	SetText2(m_Spin2.GetPos());

//	m_Spin2.SetDelta(B2Delta);
*/

	m_Spin1.SetBuddy(&m_Edit1);
	m_Spin1.SetRange(B1Min, B1Max);
	m_Spin1.SetPos(B1Pos);
	m_Spin1.SetDelta(B1Delta);	
	m_Spin1.EnableWindow(B1Enabled);
	m_Edit1.EnableWindow(B1Enabled);

	m_Spin2.SetBuddy(&m_Edit2);
	m_Spin2.SetRange(B2Min, B2Max);
	m_Spin2.SetPos(B2Pos);
	m_Spin2.SetDelta(B2Delta);	
	m_Spin2.EnableWindow(B2Enabled);
	m_Edit2.EnableWindow(B2Enabled);

	m_Spin3.SetBuddy(&m_Edit3);
	m_Spin3.SetRange(B3Min, B3Max);
	m_Spin3.SetPos(B3Pos);
	m_Spin3.SetDelta(B3Delta);	
	m_Spin3.EnableWindow(B3Enabled);
	m_Edit3.EnableWindow(B3Enabled);
}

void CParameters::OnOK( )
{

}

void CParameters::OnCancel( )
{

}

void CParameters::OnAutouv() 
{
	m_Plugin->GNeedTexRecalc=(m_AutoUV.GetCheck()==1);
	if (m_Plugin->CurrentMesh!=NULL)
	{
		m_Plugin->CurrentMesh->SetAutoTexRecalc(m_Plugin->GNeedTexRecalc);
	}
}

void CParameters::SetAutoUV(bool _checked)
{
	m_AutoUV.SetCheck((_checked?1:0));
}
void CParameters::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{

    switch(m_Plugin->TypeEdit)
    {
        //case IDC_CUBE:
    case 7:
        
        break;
        //case IDC_HEMIS:
    case 10:
        m_Plugin->nbSegHemis=(int)m_Spin1.GetPos();
        break;
        //case IDC_SPHERE:
    case 4:
        m_Plugin->nbSegSphere=(int)m_Spin1.GetPos();
        break;
        //case IDC_GRID:
    case 3:
        m_Plugin->nbSeg1Grid=(int)m_Spin1.GetPos();
        m_Plugin->nbSeg2Grid=(int)m_Spin2.GetPos();
        break;
        //case IDC_TORUS:
    case 8:
        m_Plugin->nbSeg1Torus=(int)m_Spin1.GetPos();
        m_Plugin->nbSeg2Torus=(int)m_Spin2.GetPos();
        break;
        //case IDC_STAIRS:
        //    break;
        //case IDC_CYLINDER:
    case 5:
        m_Plugin->nbSeg1Cylinder=(int)m_Spin1.GetPos();
        m_Plugin->nbSeg2Cylinder=(int)m_Spin2.GetPos();
        break;
        //case IDC_CONE:
    case 6:
        m_Plugin->nbSeg1Cone=(int)m_Spin1.GetPos();
        m_Plugin->nbSeg2Cone=(int)m_Spin2.GetPos();
        break;
        //case IDC_TUBE:
    case 9:
        m_Plugin->nbSeg1Tube=(int)m_Spin1.GetPos();
        m_Plugin->nbSeg2Tube=(int)m_Spin2.GetPos();
        break;
		// patch
	case 12: 
        m_Plugin->nbSeg1Patch=(int)m_Spin1.GetPos();
        m_Plugin->nbSeg2Patch=(int)m_Spin2.GetPos();
		break;
	case 14:
	case 13:
		m_Plugin->nbSegStairs=(int)m_Spin1.GetPos();
		break;
		// 3D grid
	case 15:
        m_Plugin->nbSeg13DGrid=(int)m_Spin1.GetPos();
        m_Plugin->nbSeg23DGrid=(int)m_Spin2.GetPos();
		m_Plugin->nbSeg33DGrid=(int)m_Spin3.GetPos();
		break;
    }
	
	m_Plugin->UpdateCurrentPrimitive();
        
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
