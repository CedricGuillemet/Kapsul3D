// tpackshadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "kapsul3D.h"
#include "FileTreeCtrl.h"
#include "kfiledialog2.h"

#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKFileDialog2 dialog
//CPakFile pak;

#pragma comment( lib, "zlib")

static int CALLBACK List_SortFiles(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

CKFileDialog2::CKFileDialog2(CWnd* pParent /*=NULL*/)
	: CDialog(CKFileDialog2::IDD, pParent)
{
//	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	IsForSaving=false;
	BtOkStr="Open";
}

void CKFileDialog2::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKFileDialog2)
    DDX_Control(pDX, IDC_LIST_THUMB, m_ListFile);
    DDX_Control(pDX, IDC_DETAILS, m_ListDetails);
    DDX_Control(pDX, IDC_LISTICONS, m_ListList);
    DDX_Control(pDX, IDC_LARGEICONS, m_ListLargeIcons);
    DDX_Control(pDX, IDC_BACK, m_Back);
    DDX_Control(pDX, IDC_UP, m_Up);
    DDX_Control(pDX, IDC_BTOK, m_BtOK);
    DDX_Control(pDX, IDC_BTCANCEL, m_BtCancel);
	DDX_Control(pDX, IDC_FILENAME, m_FileName);
	DDX_Control(pDX, IDC_EXTENSIONS, m_Extensions);
	DDX_Control(pDX, IDC_STATICFN, m_StatFN);
	DDX_Control(pDX, IDC_STATICEXT, m_StatExt);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CKFileDialog2, CDialog)
	//{{AFX_MSG_MAP(CKFileDialog2)	
    ON_BN_CLICKED(IDC_DETAILS, OnBnClickedDetails)
    ON_BN_CLICKED(IDC_LISTICONS, OnBnClickedList)
    ON_BN_CLICKED(IDC_LARGEICONS, OnBnClickedLargeicons)
    ON_BN_CLICKED(IDC_NEWREP, OnBnClickedNewrep)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BACK, OnBnClickedBack)
	ON_BN_CLICKED(IDC_UP, OnBnClickedUp)
	ON_BN_CLICKED(IDC_BTCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTOK, OnBnClickedOk)
	ON_WM_CLOSE()
	ON_WM_GETMINMAXINFO()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_NOTIFY(TVN_SELCHANGED, 100, OnTvnSelchangedTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


HINSTANCE ghInstDLL;
BOOL CKFileDialog2::OnInitDialog()
{
	CDialog::OnInitDialog();
	ghInstDLL=AfxGetInstanceHandle();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//CPakFile fp;
    m_ListDetails.SetFlat(TRUE);
    m_ListList.SetFlat(TRUE);
    m_ListLargeIcons.SetFlat(TRUE);
    m_Back.SetFlat(TRUE);
    m_Up.SetFlat(TRUE);

    m_ListDetails.SetBitmaps(LoadBitmap(ghInstDLL,MAKEINTRESOURCE(IDB_DETAILS)),RGB(255,255,255));
    m_ListList.SetBitmaps(LoadBitmap(ghInstDLL,MAKEINTRESOURCE(IDB_LIST)),RGB(255,255,255));
    m_ListLargeIcons.SetBitmaps(LoadBitmap(ghInstDLL,MAKEINTRESOURCE(IDB_LARGEICONS)),RGB(255,255,255));

    m_Back.SetBitmaps(LoadBitmap(ghInstDLL,MAKEINTRESOURCE(IDB_BACK)),RGB(255,255,255));
    m_Up.SetBitmaps(LoadBitmap(ghInstDLL,MAKEINTRESOURCE(IDB_UP)),RGB(255,255,255));

	m_TreeCtl .Create(WS_VISIBLE | WS_CHILD | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS, CRect(8,10,210,310), this, 100);
	m_ListFile.InsertColumn(0,"Name",LVCFMT_LEFT,140);
	m_ListFile.InsertColumn(1,"Size",LVCFMT_RIGHT,60);
	m_ListFile.InsertColumn(2,"Type",LVCFMT_LEFT,60);
	m_ListFile.InsertColumn(3,"Modified",LVCFMT_LEFT,100);
    m_ListFile.Init();
	

	for (int i=0;i<XTensions.size();i++)
	{
		m_Extensions.AddString(XTensions[i].ExtDesc);

	}
	m_Extensions.SetCurSel(0);
	ExtInd=0;
	
	CString RegSection="OpenSaveDialog";

	if (m_ListFile.m_strImageDir.IsEmpty())
		m_ListFile.m_strImageDir=AfxGetApp()->GetProfileString(RegSection,"DefPath","c:\\");

	m_ListFile.GetImageFileNames();	// gather the image file names
	m_ListFile.DrawThumbnails();
	m_TreeCtl.SetSelectedPath(m_ListFile.m_strImageDir,true);

	m_BtOK.SetWindowText(BtOkStr);

	WINDOWPLACEMENT wp;
	
	wp.length=sizeof(WINDOWPLACEMENT);

	wp.flags=AfxGetApp()->GetProfileInt (RegSection,"flags",-1);
	wp.showCmd=AfxGetApp()->GetProfileInt (RegSection,"showCmd",0);
	wp.ptMinPosition.x=AfxGetApp()->GetProfileInt (RegSection,"ptMinPositionx",0);
	wp.ptMinPosition.y=AfxGetApp()->GetProfileInt (RegSection,"ptMinPositiony",0);
	wp.ptMaxPosition.x=AfxGetApp()->GetProfileInt (RegSection,"ptMaxPositionx",0);
	wp.ptMaxPosition.y=AfxGetApp()->GetProfileInt (RegSection,"ptMaxPositiony",0);
	wp.rcNormalPosition.left=AfxGetApp()->GetProfileInt (RegSection,"rcNormalPositionl",0);
	wp.rcNormalPosition.right=AfxGetApp()->GetProfileInt (RegSection,"rcNormalPositionr",300);
	wp.rcNormalPosition.top=AfxGetApp()->GetProfileInt (RegSection,"rcNormalPositiont",0);
	wp.rcNormalPosition.bottom=AfxGetApp()->GetProfileInt (RegSection,"rcNormalPositionb",300);

    if (wp.flags!=-1)
    {
	    SetWindowPlacement(&wp);
		int typeaff=AfxGetApp()->GetProfileInt (RegSection,"ListType",0);
		switch (typeaff)
		{
		case 0:
			OnBnClickedLargeicons();
			break;
		case 1:
			OnBnClickedList();
			break;
		case 2:
			OnBnClickedDetails();
			break;
		}
		m_ListFile.SetColumnWidth(0,AfxGetApp()->GetProfileInt (RegSection,"Col0",140));
		m_ListFile.SetColumnWidth(1,AfxGetApp()->GetProfileInt (RegSection,"Col1",60));
		m_ListFile.SetColumnWidth(2,AfxGetApp()->GetProfileInt (RegSection,"Col2",60));
		m_ListFile.SetColumnWidth(3,AfxGetApp()->GetProfileInt (RegSection,"Col3",100));
	}

	// -> We set our window title
	SetWindowText(BtOkStr);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKFileDialog2::OnPaint() 
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
HCURSOR CKFileDialog2::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CKFileDialog2::OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    CString dap=m_TreeCtl.GetSelectedPath();
    if (!(dap.GetAt(dap.GetLength()-1)=='\\'))
        dap+="\\";

	BackList.push_back(dap);

    m_ListFile.m_strImageDir=dap;
    
    m_ListFile.GetImageFileNames();	// gather the image file names
	m_ListFile.DrawThumbnails();
	m_ListFile.SortItems(List_SortFiles,NULL);

    *pResult = 0;
}

void CKFileDialog2::ChangeFileStyle(DWORD dwView)
{
    DWORD dwStyle=::GetWindowLong(m_ListFile.m_hWnd,GWL_STYLE);
    if ((dwStyle&LVS_TYPEMASK) !=dwView)
        ::SetWindowLong(m_ListFile.m_hWnd,GWL_STYLE,(dwStyle&~LVS_TYPEMASK)|dwView);
}

void CKFileDialog2::OnBnClickedDetails()
{
    m_ListDetails.SetCheck(BST_CHECKED);
    m_ListList.SetCheck(BST_UNCHECKED);
    m_ListLargeIcons.SetCheck(BST_UNCHECKED);
    //m_ListThumbnails.SetCheck(BST_UNCHECKED);
    ChangeFileStyle(LVS_REPORT);
    m_ListFile.m_TypeView=2;
}

void CKFileDialog2::OnBnClickedList()
{
    m_ListDetails.SetCheck(BST_UNCHECKED);
    m_ListList.SetCheck(BST_CHECKED);
    m_ListLargeIcons.SetCheck(BST_UNCHECKED);
    //m_ListThumbnails.SetCheck(BST_UNCHECKED);
    ChangeFileStyle(LVS_LIST);
    m_ListFile.m_TypeView=1;
}

void CKFileDialog2::OnBnClickedBack()
{
 if(BackList.size() >= 2)
 {
  m_ListFile.m_strImageDir=BackList[BackList.size()-2];
  BackList.pop_back();
  m_ListFile.GetImageFileNames();	// gather the image file names
  m_ListFile.DrawThumbnails();
  m_TreeCtl.SetSelectedPath(m_ListFile.m_strImageDir,false);
  BackList.pop_back();
 }
}

void CKFileDialog2::OnBnClickedLargeicons()
{
    m_ListDetails.SetCheck(BST_UNCHECKED);
    m_ListList.SetCheck(BST_UNCHECKED);
    m_ListLargeIcons.SetCheck(BST_CHECKED);
    //m_ListThumbnails.SetCheck(BST_UNCHECKED);
    ChangeFileStyle(LVS_ICON);
    m_ListFile.m_TypeView=0;

}

void CKFileDialog2::OnBnClickedUp()
{
 /* Fixed : Now broswe even to root (i.e. to c:\\ )*/
 m_ListFile.m_strImageDir.SetAt(m_ListFile.m_strImageDir.GetLength()-1,0);

 int iFoundLSlash = m_ListFile.m_strImageDir.Find('\\'); 
 if(m_ListFile.m_strImageDir.ReverseFind('\\') > iFoundLSlash 
	 || iFoundLSlash < m_ListFile.m_strImageDir.GetLength())
 {
  CString NewStr = m_ListFile.m_strImageDir.Mid(0,m_ListFile.m_strImageDir.ReverseFind('\\'));
  NewStr+="\\";
  m_ListFile.m_strImageDir = NewStr;
  m_ListFile.GetImageFileNames();	
  m_ListFile.DrawThumbnails();
  m_TreeCtl.SetSelectedPath(m_ListFile.m_strImageDir,false);
 }
}

void CKFileDialog2::OnBnClickedNewrep()
{
    // TODO: Add your control notification handler code here
	AfxMessageBox("Not yet implemented.");
}


void CKFileDialog2::OnSize( UINT nType, int cx, int cy )
{
	
	if (IsWindow(m_TreeCtl))
	{
		m_TreeCtl .SetWindowPos(NULL,8,10,cx*0.33f,cy-20,SWP_NOZORDER);

		m_ListFile.SetWindowPos(NULL,cx*0.33+16,38,cx*0.66f-16,cy-16-90,SWP_NOZORDER);

		m_BtOK.SetWindowPos(NULL,cx-88,cy-65,88,30,SWP_NOZORDER);
		m_BtCancel.SetWindowPos(NULL,cx-88,cy-35,88,30,SWP_NOZORDER);

		m_StatFN.SetWindowPos(NULL,cx*0.33+16,cy-65,60,25,SWP_NOZORDER);
		m_StatExt.SetWindowPos(NULL,cx*0.33+16,cy-35,60,25,SWP_NOZORDER);
		m_FileName.SetWindowPos(NULL,cx*0.33+16+60,cy-65,cx-(cx*0.33+16+60)-92,22,SWP_NOZORDER);
		m_Extensions.SetWindowPos(NULL,cx*0.33+16+60,cy-35,cx-(cx*0.33+16+60)-92,23,SWP_NOZORDER|SWP_FRAMECHANGED);
		//m_Extensions.MoveWindow(cx*0.33+16+60,cy-35,cx-(cx*0.33+16+60)-92,23);//,SWP_NOZORDER);

		int dx=cx*0.33+16+cx*0.66f-(7*24+10);
		m_Back.SetWindowPos(NULL,dx+(24),10,24,24,SWP_NOZORDER);
		m_Up.SetWindowPos(NULL,dx+(24*2),10,24,24,SWP_NOZORDER);
		m_ListLargeIcons.SetWindowPos(NULL,dx+(24*4),10,24,24,SWP_NOZORDER);
		m_ListList.SetWindowPos(NULL,dx+(24*5),10,24,24,SWP_NOZORDER);
		m_ListDetails.SetWindowPos(NULL,dx+(24*6),10,24,24,SWP_NOZORDER);

		m_Back.Invalidate(false);
		m_Up.Invalidate(false);
		m_ListLargeIcons.Invalidate(false);
		m_ListList.Invalidate(false);
		m_ListDetails.Invalidate(false);

		m_StatFN.Invalidate(false);
		m_StatExt.Invalidate(false);
		m_BtOK.Invalidate(false);
		m_BtCancel.Invalidate(false);
	}
	
}


void CKFileDialog2::SetSaveUsage(void)
{

}

void CKFileDialog2::SetExtensionsList(CString ExtList)
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

//"Images files|jpg;gif;tga;bmp;png;pcx|C/C++ files|c;h;cpp|All files||"
void CKFileDialog2::SetTypes(CString Types)
{
	int i;
	bool extval=false;

	CString extname="";

	for (i=0;i<Types.GetLength();i++)
	{
		if (Types[i]!='|')
		{
			if (!extval)
				extname+=Types[i];
			else
			{
				// ext lists
				if (Types[i]!=';')
				{
					extname+=Types[i];
				}
				else
				{
					if (extname!="")
					{
						XTensions[XTensions.size()-1].Wilds.push_back(extname);
						extname="";
					}
				}
			}
		}
		else
		{
			if (!extval)
			{
				if (extname!="")
				{
					XTensions.push_back(extname);
					extname="";
				}
			}
			else
			{
				if (extname!="")
				{
					XTensions[XTensions.size()-1].Wilds.push_back(extname);
					extname="";
				}
			}
			extval=!extval;
		}
	}
}

void CKFileDialog2::SetInitialDir(CString InitialDir)
{
	/* Fixed backlist : now broswe to root dir too*/
	m_ListFile.m_strImageDir = InitialDir;
	BackList.push_back(InitialDir);
}

void CKFileDialog2::IsForOpen()
{
	IsForSaving=false;
	BtOkStr="Open";
}

void CKFileDialog2::IsForSave()
{
	IsForSaving=true;
	BtOkStr="Save";
}
/*
void CKFileDialog2::OnSelchangeExts()
{
	ExtInd=m_Extensions.GetCurSel();
    m_ListFile.GetImageFileNames();	// gather the image file names
	m_ListFile.DrawThumbnails();
}
*/
void CKFileDialog2::OnBnClickedCancel()
{
	OnClose();
	CDialog::OnCancel();
}

void CKFileDialog2::OnBnClickedOk()
{
	OnClose();
	CString filth;
	OpenedFile=m_ListFile.m_strImageDir;
	m_FileName.GetWindowText(filth);//m_ListFile.SelectedFile;
	if (filth.IsEmpty()) return;
	OpenedFile+=filth;
		
	CKFile myfile;

	if (IsForSaving)
	{
		if (myfile.Exist(OpenedFile))
		{
			if (MessageBox("This file already exits.\nOverwrite?","Existing file.",MB_YESNO|MB_ICONQUESTION)==IDYES)
			{
				CDialog::OnOK();
			}
			else
			{
			}
		}
		else
			CDialog::OnOK();
	}
	else
	{
		if (!myfile.Exist(OpenedFile))
		{
			MessageBox("This file doesn't exits!","Non existing file.",MB_OK|MB_ICONSTOP);
		}
		else
			CDialog::OnOK();
	}
}

void CKFileDialog2::OnClose() 
{
	WINDOWPLACEMENT wp;
	CString RegSection="OpenSaveDialog";

	wp.length=sizeof(WINDOWPLACEMENT);
	GetWindowPlacement(&wp);

	AfxGetApp()->WriteProfileInt(RegSection,"flags",wp.flags);
	AfxGetApp()->WriteProfileInt(RegSection,"showCmd",wp.showCmd);
	AfxGetApp()->WriteProfileInt(RegSection,"ptMinPositionx",wp.ptMinPosition.x);
	AfxGetApp()->WriteProfileInt(RegSection,"ptMinPositiony",wp.ptMinPosition.y);
	AfxGetApp()->WriteProfileInt(RegSection,"ptMaxPositionx",wp.ptMaxPosition.x);
	AfxGetApp()->WriteProfileInt(RegSection,"ptMaxPositiony",wp.ptMaxPosition.y);
	AfxGetApp()->WriteProfileInt(RegSection,"rcNormalPositionl",wp.rcNormalPosition.left);
	AfxGetApp()->WriteProfileInt(RegSection,"rcNormalPositionr",wp.rcNormalPosition.right);
	AfxGetApp()->WriteProfileInt(RegSection,"rcNormalPositiont",wp.rcNormalPosition.top);
	AfxGetApp()->WriteProfileInt(RegSection,"rcNormalPositionb",wp.rcNormalPosition.bottom);
	AfxGetApp()->WriteProfileInt(RegSection,"ListType",m_ListFile.m_TypeView);

	AfxGetApp()->WriteProfileInt(RegSection,"Col0",m_ListFile.GetColumnWidth(0));
	AfxGetApp()->WriteProfileInt(RegSection,"Col1",m_ListFile.GetColumnWidth(1));
	AfxGetApp()->WriteProfileInt(RegSection,"Col2",m_ListFile.GetColumnWidth(2));
	AfxGetApp()->WriteProfileInt(RegSection,"Col3",m_ListFile.GetColumnWidth(3));
	AfxGetApp()->WriteProfileString(RegSection,"DefPath",m_ListFile.m_strImageDir);
}

void CKFileDialog2::OnDestroy()
{
	CDialog::OnDestroy();

	BackList.clear();
	XTensions.clear(); 
	BtOkStr.Empty();
	OpenedFile.Empty();
}

void CKFileDialog2::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI)
{
	// We prevent user from making window too little
	lpMMI->ptMinTrackSize.x = 480;
	lpMMI->ptMinTrackSize.y = 300;
	
	CDialog::OnGetMinMaxInfo(lpMMI);
}

/*
 Custom sorting func  
*/
static int CALLBACK List_SortFiles(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
 // return -1 if 1st should go before 2nd. 1 otherwise. 0 if equals
 CKThumbListView* pListCtrl = (CKThumbListView*)lParamSort;

 LVITEM itmFirst,itmSecond;
 
 itmFirst.iItem = lParam1;
 itmSecond.iItem = lParam2;

 pListCtrl->GetItem(&itmFirst);
 pListCtrl->GetItem(&itmSecond);


 CString strItem1 = pListCtrl->GetItemText(lParam1, 0);
 CString strItem2 = pListCtrl->GetItemText(lParam2, 0);

 return 0;
}

