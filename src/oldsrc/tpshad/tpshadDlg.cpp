// tpackshadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tpshad.h"
#include "tpshadDlg.h"
#include "PakFile.h"
#include "KFile.h"
#include "FileTreeCtrl.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtpackshadDlg dialog
CPakFile pak;

#pragma comment( lib, "zlib")

CtpackshadDlg::CtpackshadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CtpackshadDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtpackshadDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_FILELIST, m_FileListCtl);
    DDX_Control(pDX, IDC_LIST_THUMB, m_ListFile);
    DDX_Control(pDX, IDC_NEWREP, m_NewRep);
    DDX_Control(pDX, IDC_DETAILS, m_ListDetails);
    DDX_Control(pDX, IDC_LIST, m_ListList);
    DDX_Control(pDX, IDC_LARGEICONS, m_ListLargeIcons);
    DDX_Control(pDX, IDC_THUMBNAILS, m_ListThumbnails);
    DDX_Control(pDX, IDC_BACK, m_Back);
    DDX_Control(pDX, IDC_UP, m_Up);
}

BEGIN_MESSAGE_MAP(CtpackshadDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_NOTIFY(TVN_SELCHANGED, 100, OnTvnSelchangedTree)
    ON_BN_CLICKED(IDC_DETAILS, OnBnClickedDetails)
    ON_BN_CLICKED(IDC_LIST, OnBnClickedList)
    ON_BN_CLICKED(IDC_LARGEICONS, OnBnClickedLargeicons)
    ON_BN_CLICKED(IDC_NEWREP, OnBnClickedNewrep)
    ON_BN_CLICKED(IDC_THUMBNAILS, OnBnClickedThumbnails)
    ON_BN_CLICKED(IDC_PREVIEW, OnBnClickedPreview)
END_MESSAGE_MAP()



BOOL CtpackshadDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CPakFile fp;
    //MessageBox("Start");
    /*
    fp.SetArchive("d:\\pak0.zip");
    char *temp=(char*)malloc(fp.GetFileSize("scripts\\sfx.shader"));
    fp.LoadFile("scripts\\sfx.shader",temp);
    free(temp);
*/
    m_NewRep.SetFlat(TRUE);
    m_ListDetails.SetFlat(TRUE);
    m_ListList.SetFlat(TRUE);
    m_ListLargeIcons.SetFlat(TRUE);
    m_ListThumbnails.SetFlat(TRUE);
    m_Back.SetFlat(TRUE);
    m_Up.SetFlat(TRUE);

    m_ListDetails.SetBitmaps(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_DETAILS)),RGB(255,255,255));
    m_ListList.SetBitmaps(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_LIST)),RGB(255,255,255));
    m_ListLargeIcons.SetBitmaps(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_LARGEICONS)),RGB(255,255,255));
    m_ListThumbnails.SetBitmaps(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_THUMBNAILS)),RGB(255,255,255));

    m_NewRep.SetBitmaps(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_NEWREP)),RGB(255,255,255));
    m_Back.SetBitmaps(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BACK)),RGB(255,255,255));
    m_Up.SetBitmaps(LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_UP)),RGB(255,255,255));
    
   // CKFile afp;
/*
    char temp[]={"Test de + plouf"};
    afp.SetResource("e:\\tpack.zip");
    afp.fopen("DOS4GW.EXE","wb");
    afp.fread(temp,strlen(temp));
    afp.fwrite(temp,strlen(temp));
    afp.fclose();
*/
    /*
    afp.SetResource("d:\\pak0.zip");
    afp.fopen("DOS4GW.EXE","wb");
    afp.fclose();
*/

//    m_TreeCtl = (CTreeFileCtrl*)this->GetDlgItem(IDC_BROWSE_TREE);
m_TreeCtl .Create(WS_VISIBLE | WS_CHILD | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS, CRect(8,35,210,300), this, 100);
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

void CtpackshadDlg::OnPaint() 
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
HCURSOR CtpackshadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CtpackshadDlg::OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
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

void CtpackshadDlg::ChangeFileStyle(DWORD dwView)
{
    DWORD dwStyle=::GetWindowLong(m_ListFile.m_hWnd,GWL_STYLE);
    if ((dwStyle&LVS_TYPEMASK) !=dwView)
        ::SetWindowLong(m_ListFile.m_hWnd,GWL_STYLE,(dwStyle&~LVS_TYPEMASK)|dwView);
}

void CtpackshadDlg::OnBnClickedDetails()
{
    m_ListDetails.SetCheck(BST_CHECKED);
    m_ListList.SetCheck(BST_UNCHECKED);
    m_ListLargeIcons.SetCheck(BST_UNCHECKED);
    m_ListThumbnails.SetCheck(BST_UNCHECKED);
    ChangeFileStyle(LVS_REPORT);
    m_ListFile.m_TypeView=2;
}

void CtpackshadDlg::OnBnClickedList()
{
    m_ListDetails.SetCheck(BST_UNCHECKED);
    m_ListList.SetCheck(BST_CHECKED);
    m_ListLargeIcons.SetCheck(BST_UNCHECKED);
    m_ListThumbnails.SetCheck(BST_UNCHECKED);
    ChangeFileStyle(LVS_LIST);
    m_ListFile.m_TypeView=1;
}

void CtpackshadDlg::OnBnClickedLargeicons()
{
    m_ListDetails.SetCheck(BST_UNCHECKED);
    m_ListList.SetCheck(BST_UNCHECKED);
    m_ListLargeIcons.SetCheck(BST_CHECKED);
    m_ListThumbnails.SetCheck(BST_UNCHECKED);
    ChangeFileStyle(LVS_ICON);
    m_ListFile.m_TypeView=0;

}

void CtpackshadDlg::OnBnClickedThumbnails()
{
    m_ListDetails.SetCheck(BST_UNCHECKED);
    m_ListList.SetCheck(BST_UNCHECKED);
    m_ListLargeIcons.SetCheck(BST_UNCHECKED);
    m_ListThumbnails.SetCheck(BST_CHECKED);
    m_ListFile.m_TypeView=3;
}

void CtpackshadDlg::OnBnClickedNewrep()
{
    // TODO: Add your control notification handler code here
}


void CtpackshadDlg::OnBnClickedPreview()
{
    
}
