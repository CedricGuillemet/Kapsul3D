// tpackshadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tpshad.h"
#include "kfiledialog.h"
//#include "PakFile.h"
//#include "KFile.h"
#include "FileTreeCtrl.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKFileDialog dialog
CPakFile pak;

#pragma comment( lib, "zlib")

CKFileDialog::CKFileDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CKFileDialog::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKFileDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_FILELIST, m_FileListCtl);
    DDX_Control(pDX, IDC_LIST_THUMB, m_ListFile);
    DDX_Control(pDX, IDC_NEWREP, m_NewRep);
    DDX_Control(pDX, IDC_DETAILS, m_ListDetails);
    DDX_Control(pDX, IDC_LIST, m_ListList);
    DDX_Control(pDX, IDC_LARGEICONS, m_ListLargeIcons);
    DDX_Control(pDX, IDC_BACK, m_Back);
    DDX_Control(pDX, IDC_UP, m_Up);
    DDX_Control(pDX, IDC_BTOK, m_BtOK);
    DDX_Control(pDX, IDC_BTCANCEL, m_BtCancel);
	DDX_Control(pDX, IDC_FILENAME, m_FileName);
	DDX_Control(pDX, IDC_EXTENSIONS, m_Extensions);
	DDX_Control(pDX, IDC_STATICFN, m_StatFN);
	DDX_Control(pDX, IDC_STATICEXT, m_StatExt);
	DDX_Control(pDX, IDC_SYNCH_FOLDERS,m_SynchFolder);

}

BEGIN_MESSAGE_MAP(CKFileDialog, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_NOTIFY(TVN_SELCHANGED, 100, OnTvnSelchangedTree)
    ON_BN_CLICKED(IDC_DETAILS, OnBnClickedDetails)
    ON_BN_CLICKED(IDC_LIST, OnBnClickedList)
    ON_BN_CLICKED(IDC_LARGEICONS, OnBnClickedLargeicons)
    ON_BN_CLICKED(IDC_NEWREP, OnBnClickedNewrep)
	ON_WM_SIZE()
END_MESSAGE_MAP()



BOOL CKFileDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CPakFile fp;
    m_NewRep.SetFlat(TRUE);
    m_ListDetails.SetFlat(TRUE);
    m_ListList.SetFlat(TRUE);
    m_ListLargeIcons.SetFlat(TRUE);
    m_Back.SetFlat(TRUE);
    m_Up.SetFlat(TRUE);

    m_ListDetails.SetBitmaps(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_DETAILS)),RGB(255,255,255));
    m_ListList.SetBitmaps(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_LIST)),RGB(255,255,255));
    m_ListLargeIcons.SetBitmaps(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_LARGEICONS)),RGB(255,255,255));

    m_NewRep.SetBitmaps(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_NEWREP)),RGB(255,255,255));
    m_Back.SetBitmaps(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BACK)),RGB(255,255,255));
    m_Up.SetBitmaps(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_UP)),RGB(255,255,255));

	m_TreeCtl .Create(WS_VISIBLE | WS_CHILD | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS, CRect(8,10,210,310), this, 100);
	m_ListFile.InsertColumn(0,"Name",LVCFMT_LEFT,200);
	m_ListFile.InsertColumn(1,"Size",LVCFMT_RIGHT,100);
	m_ListFile.InsertColumn(2,"Type",LVCFMT_LEFT,100);
	m_ListFile.InsertColumn(3,"Modified",LVCFMT_LEFT,100);
    m_ListFile.Init();
    OnBnClickedLargeicons();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKFileDialog::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CKFileDialog::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CKFileDialog::OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    CString dap=m_TreeCtl.GetSelectedPath();
    m_FileListCtl.SetWindowText(dap);
    if (!(dap.GetAt(dap.GetLength()-1)=='\\'))
        dap+="\\";

    m_ListFile.m_strImageDir=dap;
    
    m_ListFile.GetImageFileNames();	// gather the image file names
	m_ListFile.DrawThumbnails();


    *pResult = 0;
}

void CKFileDialog::ChangeFileStyle(DWORD dwView)
{
    DWORD dwStyle=::GetWindowLong(m_ListFile.m_hWnd,GWL_STYLE);
    if ((dwStyle&LVS_TYPEMASK) !=dwView)
        ::SetWindowLong(m_ListFile.m_hWnd,GWL_STYLE,(dwStyle&~LVS_TYPEMASK)|dwView);
}

void CKFileDialog::OnBnClickedDetails()
{
    m_ListDetails.SetCheck(BST_CHECKED);
    m_ListList.SetCheck(BST_UNCHECKED);
    m_ListLargeIcons.SetCheck(BST_UNCHECKED);
    //m_ListThumbnails.SetCheck(BST_UNCHECKED);
    ChangeFileStyle(LVS_REPORT);
    m_ListFile.m_TypeView=2;
}

void CKFileDialog::OnBnClickedList()
{
    m_ListDetails.SetCheck(BST_UNCHECKED);
    m_ListList.SetCheck(BST_CHECKED);
    m_ListLargeIcons.SetCheck(BST_UNCHECKED);
    //m_ListThumbnails.SetCheck(BST_UNCHECKED);
    ChangeFileStyle(LVS_LIST);
    m_ListFile.m_TypeView=1;
}

void CKFileDialog::OnBnClickedLargeicons()
{
    m_ListDetails.SetCheck(BST_UNCHECKED);
    m_ListList.SetCheck(BST_UNCHECKED);
    m_ListLargeIcons.SetCheck(BST_CHECKED);
    //m_ListThumbnails.SetCheck(BST_UNCHECKED);
    ChangeFileStyle(LVS_ICON);
    m_ListFile.m_TypeView=0;

}

void CKFileDialog::OnBnClickedNewrep()
{
    // TODO: Add your control notification handler code here
}


void CKFileDialog::OnSize( UINT nType, int cx, int cy )
{
	/*
	if (IsWindow(m_TreeCtl))
	{
		m_TreeCtl .SetWindowPos(NULL,8,10,cx*0.33f,cy-20,SWP_NOZORDER);
		m_FileListCtl.SetWindowPos(NULL,cx*0.33+16,10,cx*0.66f-(7*24+10),22,SWP_NOZORDER);

		m_ListFile.SetWindowPos(NULL,cx*0.33+16,38,cx*0.66f-16,cy-16-90,SWP_NOZORDER);

		m_BtOK.SetWindowPos(NULL,cx-88,cy-65,88,30,SWP_NOZORDER);
		m_BtCancel.SetWindowPos(NULL,cx-88,cy-35,88,30,SWP_NOZORDER);

		m_StatFN.SetWindowPos(NULL,cx*0.33+16,cy-65,60,25,SWP_NOZORDER);
		m_StatExt.SetWindowPos(NULL,cx*0.33+16,cy-35,60,25,SWP_NOZORDER);
		m_FileName.SetWindowPos(NULL,cx*0.33+16+60,cy-65,cx-(cx*0.33+16+60)-92,22,SWP_NOZORDER);
		m_Extensions.SetWindowPos(NULL,cx*0.33+16+60,cy-35,cx-(cx*0.33+16+60)-92,23,SWP_NOZORDER|SWP_FRAMECHANGED);
		//m_Extensions.MoveWindow(cx*0.33+16+60,cy-35,cx-(cx*0.33+16+60)-92,23);//,SWP_NOZORDER);

		int dx=cx*0.33+16+cx*0.66f-(7*24+10);
		m_SynchFolder.SetWindowPos(NULL,dx,10,24,24,SWP_NOZORDER);
		m_Back.SetWindowPos(NULL,dx+(24),10,24,24,SWP_NOZORDER);
		m_Up.SetWindowPos(NULL,dx+(24*2),10,24,24,SWP_NOZORDER);
		m_NewRep.SetWindowPos(NULL,dx+(24*3),10,24,24,SWP_NOZORDER);
		m_ListLargeIcons.SetWindowPos(NULL,dx+(24*4),10,24,24,SWP_NOZORDER);
		m_ListList.SetWindowPos(NULL,dx+(24*5),10,24,24,SWP_NOZORDER);
		m_ListDetails.SetWindowPos(NULL,dx+(24*6),10,24,24,SWP_NOZORDER);

		m_SynchFolder.Invalidate(false);
		m_Back.Invalidate(false);
		m_Up.Invalidate(false);
		m_NewRep.Invalidate(false);
		m_ListLargeIcons.Invalidate(false);
		m_ListList.Invalidate(false);
		m_ListDetails.Invalidate(false);

		m_StatFN.Invalidate(false);
		m_StatExt.Invalidate(false);
		m_BtOK.Invalidate(false);
		m_BtCancel.Invalidate(false);
	}
	*/
}


void CKFileDialog::SetSaveUsage(void)
{

}

void CKFileDialog::SetExtensionsList(CString ExtList)
{
	int i;
	bool extval;

	CString extname="";

	for (i=0;i<ExtList.GetLength();i++)
	{
		if (ExtList[i]!='|')
		{
			extname+=ExtList[i];
		}
		else
		{
			if (!extval)
			{
				/*
				if (extname!="")
					m_Extensions.AddString(extname);
					*/
			}
			extval=!extval;
		}
	}
}