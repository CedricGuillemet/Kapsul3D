// LightParam.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "LightParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLightParam dialog


CLightParam::CLightParam(CWnd* pParent /*=NULL*/)
	: CDialog(CLightParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLightParam)
	//}}AFX_DATA_INIT
}


void CLightParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLightParam)
	DDX_Control(pDX, IDC_SLIDRADIUS, m_SlidRadius);
	DDX_Control(pDX, IDC_TEXTRADIUS, m_TextRadius);
	DDX_Control(pDX, IDC_COL, m_Color);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLightParam, CDialog)
	//{{AFX_MSG_MAP(CLightParam)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_COLOR, OnColor)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLightParam message handlers
//extern "C" CLight *CurrentLight;
double tmpradius;
void CLightParam::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (nSBCode==SB_ENDSCROLL)
	{
		m_SlidRadius.SetPos(50);
		/*
		if (CurrentLight!=NULL)
			tmpradius=CurrentLight->Radius;
			*/
	}
	else
	{
		/*
		if (CurrentLight!=NULL)
		{
			double factor;

			if (m_SlidRadius.GetPos()<50)
				factor=((((double)m_SlidRadius.GetPos())/50)*0.5)+0.5;
			else
				factor=(((double)m_SlidRadius.GetPos()-50)/50)+1;
			CurrentLight->Radius=tmpradius*factor;
			SetText(CurrentLight->Radius);
			DrawViews();
		}
		*/
	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CLightParam::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_SlidRadius.SetRange(0,100);
	m_SlidRadius.SetPos(50);

	/*
	m_Spin1.SetBuddy(&m_Radius);
	m_Spin1.SetRange(1.0f, 90.0f);
	m_Spin1.SetPos(1.0f);
	m_Spin1.SetDelta(1.0f);
	
	m_Spin2.SetBuddy(&m_Radius);
	m_Spin2.SetRange(1.0f, 90.0f);
	m_Spin2.SetPos(1.0f);
	m_Spin2.SetDelta(1.0f);
*/
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLightParam::OnOK() 
{
}

void CLightParam::OnCancel() 
{
}

void CLightParam::OnColor() 
{
	// TODO: Add your control notification handler code here
/*
	if (CurrentLight!=NULL)
	{
		CColorDialog cd(RGB(CurrentLight->r,CurrentLight->g,CurrentLight->b),CC_FULLOPEN,this);

		if (cd.DoModal()==IDOK)
		{
			int dacol=cd.GetColor();
			CurrentLight->r=dacol&0xff;
			CurrentLight->g=(dacol>>8)&0xff;
			CurrentLight->b=(dacol>>16)&0xff;
			Invalidate(FALSE);
		}
	}
	*/
}

void CLightParam::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	/*
	if (CurrentLight!=NULL)	
	{
		
		RECT rc;
		m_Color.GetWindowRect(&rc);
		ScreenToClient(&rc);
		dc.FillRect(&rc,&CBrush(RGB(CurrentLight->r,CurrentLight->g,CurrentLight->b)));

	}
	*/
	// Do not call CDialog::OnPaint() for painting messages
}

void CLightParam::SetText(double RadVal)
{
	char temp[64];
	sprintf(temp,"%5.2f",RadVal);
	m_TextRadius.SetWindowText(temp);	
}