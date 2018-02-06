// Animate.cpp : implementation file
//

#include "stdafx.h"
//#include "memmgr/mmgr.h"

#include "KapsulSE.h"
#include "Animate.h"


#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimate dialog


CAnimate::CAnimate(CWnd* pParent /*=NULL*/)
	: CDialog(CAnimate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnimate)
	//}}AFX_DATA_INIT
}


void CAnimate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnimate)
	DDX_Control(pDX, IDC_SCROLLBAR1, sb2);
	DDX_Control(pDX, IDC_SCROLLBAR2, sb1);
	DDX_Control(pDX, IDC_SPIN1, m_FrameSpin);
	DDX_Control(pDX, IDC_EDIT1, m_FrameNb);
	DDX_Control(pDX, IDC_SLASH, m_Slash);
	DDX_Control(pDX, IDC_KILLKF, m_KillFrame);
	DDX_Control(pDX, IDC_SLIDER, m_Slider);
	DDX_Control(pDX, IDC_PREVKEY, m_PrevKey);
	DDX_Control(pDX, IDC_PREVFRAME, m_PrevFrame);
	DDX_Control(pDX, IDC_PLAYSTOP, m_Play);
	DDX_Control(pDX, IDC_PAUSE, m_Pause);
	DDX_Control(pDX, IDC_NEXTKEY, m_NextKey);
	DDX_Control(pDX, IDC_NEXTFRAME, m_NextFrame);
	DDX_Control(pDX, IDC_NBFRAMES, m_NbFrames);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAnimate, CDialog)
	//{{AFX_MSG_MAP(CAnimate)
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_PREVFRAME, OnPrevframe)
	ON_BN_CLICKED(IDC_PLAYSTOP, OnPlaystop)
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	ON_BN_CLICKED(IDC_NEXTFRAME, OnNextframe)
	ON_BN_CLICKED(IDC_KILLKF, OnKillkf)
	ON_BN_CLICKED(IDC_PREVKEY, OnPrevkey)
	ON_BN_CLICKED(IDC_NEXTKEY, OnNextkey)
	ON_BN_CLICKED(IDC_NBFRAMES, OnNbframes)
	ON_WM_VSCROLL()
	ON_WM_TIMER()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimate message handlers

void CAnimate::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

    RECT rc;

    GetClientRect(&rc);
	
    if (m_KillFrame.m_hWnd!=NULL)
    {
	    m_KillFrame.MoveWindow(rc.right-30,8,24,20,TRUE);
	    m_PrevKey.MoveWindow(rc.right-174,8,24,20,TRUE);

	    m_PrevFrame.MoveWindow(rc.right-150,8,24,20,TRUE);
	    m_Play.MoveWindow(rc.right-126,8,24,20,TRUE);
	    m_Pause.MoveWindow(rc.right-102,8,24,20,TRUE);
	    m_NextKey.MoveWindow(rc.right-54,8,24,20,TRUE);
	    m_NextFrame.MoveWindow(rc.right-78,8,24,20,TRUE);
	    m_NbFrames.MoveWindow(rc.right-78,29,72,20,TRUE);
    
	    m_FrameNb.MoveWindow(rc.right-174,29,72,20,TRUE);
	    m_FrameSpin.MoveWindow(rc.right-102,29,12,20,TRUE);
	    m_Slash.MoveWindow(rc.right-90,29,10,20,TRUE);

        m_Slider.MoveWindow(0,8,rc.right-178,30,TRUE);
		m_TimeTracker.MoveWindow(2,50,cx-20,cy-74);

		int DecalX=rc.left+150;    

		sb1.MoveWindow(DecalX,cy-24,cx-DecalX-18,18,TRUE);
		sb2.MoveWindow(rc.right-18,rc.top+80,18,cy-80-24,TRUE);

    }
}

BOOL CAnimate::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_KillFrame.SetIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_KILLKF)));
	m_PrevKey.SetIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_PREVKF)));
	m_PrevFrame.SetIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_PREVFRAME)));
	m_Play.SetIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_PLAY)));
	m_Pause.SetIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_PAUSE)));
	m_NextKey.SetIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_NEXTKF)));
	m_NextFrame.SetIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_NEXTFRAME)));
    m_Slider.SetRange(0,99);
    /*
	m_NbFrames.SetIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_KILLKF));
	m_FrameNb.SetIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_KILLKF));
	*/
	m_FrameSpin.SetBuddy(&m_FrameNb);
	m_FrameSpin.SetRange(0, 99.0f);
	m_FrameSpin.SetPos(0);

	RECT rc;

	GetClientRect(&rc);
	
	m_TimeTracker.Create(CRect(2,55,rc.right-24,rc.bottom-30),this,5114);
	m_TimeTracker.ShowWindow(SW_SHOWNORMAL);
//	m_FrameSpin.SetDelta(1);

    sb1.SetScrollRange(0,28800);
    sb1.SetScrollPos(0);
    
    sb2.SetScrollRange(0,128);
    sb2.SetScrollPos(0);

    IsPlaying=false;
    
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAnimate::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
    if (pScrollBar==(CScrollBar*)&m_Slider)
    {
        if (nSBCode!=SB_ENDSCROLL)
	        m_FrameSpin.SetPos(m_Slider.GetPos());

    }
	else
	{
		int CurPos;

		CurPos=pScrollBar->GetScrollPos();
		switch (nSBCode)
		{
		case SB_THUMBTRACK:
			CurPos=nPos;
			m_TimeTracker.StartTime=(double)CurPos;
			m_TimeTracker.Invalidate(FALSE);
			break;
		case SB_ENDSCROLL:
			break;
		case SB_LINELEFT:
			CurPos--;
			if (CurPos<0) CurPos=0;
			m_TimeTracker.StartTime=(double)CurPos;
			m_TimeTracker.Invalidate(FALSE);
			break;
		case SB_LINERIGHT:
			CurPos++;
			if (CurPos>28800) CurPos=28800;
			m_TimeTracker.StartTime=(double)CurPos;
			m_TimeTracker.Invalidate(FALSE);
			break;
		}

		pScrollBar->SetScrollPos(CurPos);
    

	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CAnimate::OnPrevframe() 
{
	// TODO: Add your control notification handler code here
	
}

void CAnimate::OnPlaystop() 
{
	if (IsPlaying)
    {
        m_Play.SetIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_PLAY)));
		KillTimer(1);
        IsPlaying=false;
    }
    else
    {
        m_Play.SetIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_STOP)));
        SetTimer(1,40,NULL);
        IsPlaying=true;
    }
	
}

void CAnimate::OnPause() 
{
	// TODO: Add your control notification handler code here
	
}

void CAnimate::OnNextframe() 
{
	// TODO: Add your control notification handler code here
	
}

void CAnimate::OnKillkf() 
{
	// TODO: Add your control notification handler code here
	
}

void CAnimate::OnPrevkey() 
{
	// TODO: Add your control notification handler code here
	
}

void CAnimate::OnNextkey() 
{
	// TODO: Add your control notification handler code here
	
}

void CAnimate::OnNbframes() 
{
    char szTemp[50];
    m_nbf.nbFrames=m_Slider.GetRangeMax();
    m_nbf.Rescal=true;

	m_nbf.DoModal();

    m_Slider.SetRange(0,m_nbf.nbFrames);
    m_FrameSpin.SetRange(0, m_nbf.nbFrames);
    m_FrameSpin.SetPos(m_Slider.GetPos());
    m_Slider.SetPos(m_Slider.GetPos());
    Invalidate(TRUE);
    sprintf(szTemp,"%d",m_nbf.nbFrames);
    m_NbFrames.SetWindowText(szTemp);
    m_Slider.SetFocus();
}

void CAnimate::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	
    m_Slider.SetPos(m_FrameSpin.GetPos());
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CAnimate::OnTimer(UINT nIDEvent) 
{
	m_Slider.SetPos(m_Slider.GetPos()+1);
	m_FrameSpin.SetPos(m_Slider.GetPos());

	CDialog::OnTimer(nIDEvent);
}

void CAnimate::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnChar(nChar, nRepCnt, nFlags);
}

void CAnimate::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CAnimate::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CAnimate::OnOK( )
{

}

void CAnimate::OnCancel( )
{

}
