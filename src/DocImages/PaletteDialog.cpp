// PaletteDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CImageDemo.h"
#include "PaletteDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "PaletteWnd.h"
#include "ColorChooser.h"

/////////////////////////////////////////////////////////////////////////////
// CPaletteDialog dialog


CPaletteDialog::CPaletteDialog(CWnd* pParent /*=NULL*/)
	: CSnapDialog(CPaletteDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPaletteDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPaletteDialog::DoDataExchange(CDataExchange* pDX)
{
	CSnapDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPaletteDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPaletteDialog, CSnapDialog)
	//{{AFX_MSG_MAP(CPaletteDialog)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	//}}AFX_MSG_MAP
	ON_MESSAGE(CCN_COLOR_CHANGED, OnColorChanged)
	ON_MESSAGE(WM_FO_SELECTBULLETTYPEOK, OnGColorChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaletteDialog message handlers
	CPaletteWnd	m_wnd;
	CColorChooser*	m_pwndChooser;
	COLORREF		m_crCurr;

BOOL CPaletteDialog::OnInitDialog() 
{
	CSnapDialog::OnInitDialog();
	
	m_pwndChooser = new CColorChooser(CPoint(5,5), this, 5141);
	
	CRect theRect;
	GetDlgItem(IDC_COLORPICKER)->GetWindowRect( &theRect );
	ScreenToClient(&theRect);	
	m_wndBulleted.Create(WS_CHILD|WS_VISIBLE|WS_EX_CLIENTEDGE,theRect,this,IDC_COLORPICKER,1);

	GetDlgItem(IDC_COLORWELL)->GetWindowRect( &theRect );
	ScreenToClient(&theRect);	
	m_wndWell.Create(WS_CHILD|WS_VISIBLE|WS_EX_CLIENTEDGE,theRect,this,IDC_COLORWELL,1);

	GetDlgItem(IDC_COLORSLIDER)->GetWindowRect( &theRect );
	ScreenToClient(&theRect);	
	m_wndSlider.Create(WS_CHILD|WS_VISIBLE|WS_EX_CLIENTEDGE,theRect,this,IDC_COLORSLIDER,1);
	
	m_wndBulleted.pNotifyWnd = &m_wndSlider;
	m_wndBulleted.pNotifyWellWnd = &m_wndWell;

	m_wndBulleted.SetDataValue(modes_hsv_hue | modes_reverse);
	m_wndSlider.SetDataValue(modes_hsv_hue | modes_reverse);
	m_wndSlider.pNotifyWnd = &m_wndBulleted;
	m_wndWell.pNotifyWnd = &m_wndBulleted;

	CheckRadioButton(IDC_RADIO1,IDC_RADIO6,IDC_RADIO4);
	m_wndBulleted.SetColor((COLORREF*)&m_crCurr);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPaletteDialog::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	COLORREF	old_color;

	old_color = m_wndBulleted.GetColor();
	m_wndBulleted.SetDataValue(modes_rgb_red | modes_reverse);
	m_wndSlider.SetDataValue(modes_rgb_red | modes_reverse);
	m_wndBulleted.SetColor(old_color);

}

void CPaletteDialog::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	COLORREF	old_color;

	old_color = m_wndBulleted.GetColor();
	m_wndBulleted.SetDataValue(modes_rgb_green | modes_reverse);
	m_wndSlider.SetDataValue(modes_rgb_green | modes_reverse);
	m_wndBulleted.SetColor(old_color);
}

void CPaletteDialog::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	COLORREF	old_color;

	old_color = m_wndBulleted.GetColor();
	m_wndBulleted.SetDataValue(modes_rgb_blue | modes_reverse);
	m_wndSlider.SetDataValue(modes_rgb_blue | modes_reverse);
	m_wndBulleted.SetColor(old_color);
}

void CPaletteDialog::OnRadio4() 
{
	// TODO: Add your control notification handler code here
	COLORREF	old_color;

	old_color = m_wndBulleted.GetColor();
	m_wndBulleted.SetDataValue(modes_hsv_hue | modes_reverse);
	m_wndSlider.SetDataValue(modes_hsv_hue | modes_reverse);
	m_wndBulleted.SetColor(old_color);
}

void CPaletteDialog::OnRadio5() 
{
	// TODO: Add your control notification handler code here
	COLORREF	old_color;

	old_color = m_wndBulleted.GetColor();
	m_wndBulleted.SetDataValue(modes_hsv_sat | modes_reverse);
	m_wndSlider.SetDataValue(modes_hsv_sat | modes_reverse);
	m_wndBulleted.SetColor(old_color);
}

void CPaletteDialog::OnRadio6() 
{
	COLORREF	old_color;

	old_color = m_wndBulleted.GetColor();
	// TODO: Add your control notification handler code here
	m_wndBulleted.SetDataValue(modes_hsv_value | modes_reverse);
	m_wndSlider.SetDataValue(modes_hsv_value | modes_reverse);
	m_wndBulleted.SetColor(old_color);
}

LRESULT CPaletteDialog::OnColorChanged(WPARAM wParam, LPARAM lParam)
{
	//m_crCurr = lParam;

	m_wndBulleted.SetColor((COLORREF*)lParam);
	RedrawWindow();
	return 0;
}

void CPaletteDialog::OnGColorChanged(UINT wParam, LONG lParam)
{
	m_pwndChooser->SetCurrentColorValues(m_wndBulleted.GetColor());
	m_pwndChooser->Invalidate(FALSE);
}
