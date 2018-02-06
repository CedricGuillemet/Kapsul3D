// TScrollDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "TScroll.h"

//#include "memmgr/mmgr.h"

#include "TScrollDlg.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "CoolDialogBar.h"
/////////////////////////////////////////////////////////////////////////////
// CTScrollDlg dialog

CTScrollDlg::CTScrollDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTScrollDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTScrollDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTScrollDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTScrollDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTScrollDlg, CDialog)
	//{{AFX_MSG_MAP(CTScrollDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
    ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTScrollDlg message handlers

BOOL CTScrollDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	RECT rc;

	GetClientRect(&rc);
	// TODO: Add extra initialization here
	//cool.Create(CRect(rc.right-8,0,rc.right,rc.bottom),this,1124);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTScrollDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTScrollDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTScrollDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
    /*
	CCoolDialogBar*tmp=(CCoolDialogBar*)GetParent();
	
	
	if (!tmp->IsFloating())
	{
		if (m_Cont.m_hWnd!=NULL) m_Cont.MoveWindow(1,1,cx-30,cy-4,TRUE);
		if (m_cs.m_hWnd!=NULL) m_cs.MoveWindow(cx-28,1,10,cy-4,TRUE);

	}
	else
	{
		if (m_Cont.m_hWnd!=NULL) m_Cont.MoveWindow(1,1,cx-22,cy-4,TRUE);
		if (m_cs.m_hWnd!=NULL) m_cs.MoveWindow(cx-20,1,10,cy-4,TRUE);
	}
	*/
}

void CTScrollDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    /*
	RECT rc;
	CRect *rec;
	GetClientRect(&rc);

	CCoolDialogBar*tmp=(CCoolDialogBar*)GetParent();
	
	
	if (!tmp->IsFloating())
	{
		rec=new CRect(rc.right-28,0,rc.right-10,rc.bottom);
	}
	else
	{
		rec=new CRect(rc.right-20,0,rc.right-10,rc.bottom);
	}	//rc.left+=rc.right-8;

	if (rec->PtInRect(point)) 
		m_cs.OnMouseMove(nFlags,point);
        */
	CDialog::OnMouseMove(nFlags, point);
}

void CTScrollDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
    /*
	// TODO: Add your message handler code here and/or call default
	RECT rc;
	CRect *rec;
	GetClientRect(&rc);

	CCoolDialogBar*tmp=(CCoolDialogBar*)GetParent();
	
	
	if (!tmp->IsFloating())
	{
		rec=new CRect(rc.right-28,0,rc.right-10,rc.bottom);
	}
	else
	{
		rec=new CRect(rc.right-20,0,rc.right-10,rc.bottom);
	}
	//rc.left+=rc.right-8;

	if (rec->PtInRect(point)) 
		m_cs.OnLButtonDown(nFlags,point);
	*/
	CDialog::OnLButtonDown(nFlags, point);
}

void CTScrollDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
    /*
	// TODO: Add your message handler code here and/or call default
	RECT rc;
	CRect *rec;
	GetClientRect(&rc);

	CCoolDialogBar*tmp=(CCoolDialogBar*)GetParent();
	
	
	if (!tmp->IsFloating())
	{
		rec=new CRect(rc.right-28,0,rc.right-10,rc.bottom);
	}
	else
	{
		rec=new CRect(rc.right-20,0,rc.right-10,rc.bottom);
	}	//rc.left+=rc.right-8;

	if (rec->PtInRect(point)) 
		m_cs.OnLButtonUp(nFlags,point);
	*/
	CDialog::OnLButtonUp(nFlags, point);
}


extern CKScenePlugin *GCurPlug;
HWND daPlug;
void CTScrollDlg::SetPlug(HWND dahwnd,CWnd *Parent) 
{
	if (daPlug!=NULL)
		::DestroyWindow(daPlug);

	daPlug=dahwnd;

	RECT rc;
	//CWnd daw(dahwnd);

    GetClientRect(&rc);

    if (GCurPlug!=NULL)
    {
        GCurPlug->ReSize(rc.right,rc.bottom-8);
    }

    GetClientRect(&rc);
    MoveWindow(0,0,rc.right,rc.bottom,TRUE);

	::GetClientRect(dahwnd,&rc);
    /*
    if (height!=0)
        tbSize=height+8;
    else
	    tbSize=rc.bottom+8;

	tbPos=0;
	*/
	GetClientRect(&rc);

	//tbLength=rc.bottom;

	Invalidate(TRUE);
}

void CTScrollDlg::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
    CDialog::OnKeyDown( nChar,nRepCnt,nFlags);
}

void CTScrollDlg::OnCancel( )
{

}
