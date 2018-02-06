// entsDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "ents.h"
#include "resource.h"
#include "entsDlg.h"

/*
#include "init.h"
#include "tree_parser.h"
#include "node.h"
*/

#include <iostream>
#include <sstream>
#include <strstream>
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int GetParamType(char *ParamTypeName)
{
	if (strcmp(ParamTypeName,"string")==0) return 0;
	if (strcmp(ParamTypeName,"integer")==0) return 1;
	if (strcmp(ParamTypeName,"color")==0) return 2;
	if (strcmp(ParamTypeName,"float")==0) return 3;
	if (strcmp(ParamTypeName,"combo")==0) return 4;
	return -1;
}

vector<CEntityType*> m_EntsType;
/////////////////////////////////////////////////////////////////////////////
// CEntsDlg dialog

CEntsDlg::CEntsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEntsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEntsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEntsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEntsDlg)
	DDX_Control(pDX, IDC_EDT1, m_Edit);
	DDX_Control(pDX, IDC_CB1, m_List);
	DDX_Control(pDX, IDC_OI, m_OI);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEntsDlg, CDialog)
	//{{AFX_MSG_MAP(CEntsDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_CB1, OnSelchangeCb1)
	ON_NOTIFY(OIVN_ITEMCHANGED, IDC_OI, OnNotifyProp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEntsDlg message handlers

BOOL CEntsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	//CString alls="",alls2="";
	char value[256];
	int cblAv=0;

	CEntityParam *CurPar;
	CEntityGroup *CurGrp;
	CEntityType *CurType;

	ResetAllValues();

	//m_OI.Create(CRect(10,10,100,200),this,25147,WS_CHILD|WS_VISIBLE);

//	CObjectInspector::CProperty *pProp;

	// Prepare control's appearance
	m_szBorderStyle		   = "bsLowered";
	m_bHotTrack			   = false;
	m_b3dFocus			   = false;
	m_szValueHeader		   = _T("Value");
	m_szPropertyHeader	   = _T("Property");
	m_clBackColor		   = ::GetSysColor(COLOR_BTNFACE);
	m_clVTColor			   = RGB(200,200,200);
	m_clPTColor			   = (COLORREF)0;
	m_clGridLineColor	   = RGB(80,80,80);
	m_nMinPropertyColWidth = 50;
	m_nMinValueColWidth    = 50;
	m_clFocusLineColor     = RGB(200,200,200);
	m_nStyle			   = 1;


	init init;
	tree_parser parser("entities.xml");

	if (!parser) 
	{
		//std::cerr << argv[0] << ": error parsing XML file\r\n";
		MessageBox("Error parsing file");
		return 1;
	}
	
	node &root = parser.get_root_node();

	node::const_iterator child(root.begin()), child_end(root.end());
	for (; child != child_end; ++child) 
	{
		if (child->is_text()) continue;


		if (strcmp(child->get_name() ,"Entity")==0)
		{
			node::const_iterator child2(child->begin()), child_end(child->end());
			for (; child2 != child_end; ++child2) 
			{
				if (child2->is_text()) continue;

				if (strcmp(child2->get_name() ,"desc")==0)
				{
					child2->get_attr("value",value);
					m_List.AddString(value);
					CurType=new CEntityType(value);
					m_EntsType.insert(m_EntsType.end(),CurType);



				}
					
				if (strcmp(child2->get_name() ,"Group")==0)
				{
					

					// param name
					child2->get_attr("value",value);

					CurGrp=new CEntityGroup(value);
					CurType->m_Groups.insert(CurType->m_Groups.end(),CurGrp);

					node::const_iterator child3(child2->begin()), child_end(child2->end());
					for (; child3 != child_end; ++child3) 
					{
						if (child3->is_text()) continue;

						if (strcmp(child3->get_name() ,"Groupvalues")==0)
						{
							child3->get_attr("name",value);
							CurPar=new CEntityParam(value,1);
							CurGrp->m_Params.insert(CurGrp->m_Params.end(),CurPar);

							child3->get_attr("type",value);
							CurPar->Type=GetParamType(value);

							if (CurPar->Type==4)
							{
								// combo
								char tempcbl[64];
								int valAv=0;

								sprintf(tempcbl,"value%d",valAv);
								while(child3->get_attr(tempcbl,value))
								{
									m_cbListProp[cblAv].AddTail(value);
									valAv++;
									sprintf(tempcbl,"value%d",valAv);
								}
								cblAv++;
							}
						}
					}
				}
			}
		}
	}
	UpdatePropList(m_EntsType[0]);
	m_List.SetCurSel(0);

//	m_Edit.SetWindowText(alls2);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEntsDlg::UpdatePropList(CEntityType *daTyp)
{
	CObjectInspector::CProperty *pProp;

	//m_OI.SetRedraw(FALSE);

	//m_OI.CleanUp();
	m_OI.m_PropertyList.clear();
	int szAv=0,clAv=0,iAv=0,fAv=0,cbAv=0;

	for (vector<CEntityGroup*>::iterator i = daTyp->m_Groups.begin(); i != daTyp->m_Groups.end(); i++)
	{
		m_OI.AddProperty (pProp = new CObjectInspector::CProperty((*i)->Name));
		pProp->Expand ();

		for (vector<CEntityParam*>::iterator j = (*i)->m_Params.begin(); j != (*i)->m_Params.end(); j++)
		{
			switch((*j)->Type)
			{
			case 0:
				pProp->AddProperty (new CObjectInspector::CProperty((*j)->Name, &m_szProp[szAv++]));
				break;
			case 1:
				pProp->AddProperty (new CObjectInspector::CProperty((*j)->Name, &m_iProp[iAv++]));
				break;
			case 2:
				pProp->AddProperty (new CObjectInspector::CProperty((*j)->Name, &m_clProp[clAv++]));
				break;
			case 3:
				pProp->AddProperty (new CObjectInspector::CProperty((*j)->Name, &m_fProp[fAv++]));
				break;
			case 4:
				pProp->AddProperty (new CObjectInspector::CProperty((*j)->Name, &m_cbProp[cbAv], &m_cbListProp[cbAv] , -1, CBS_DROPDOWNLIST));
				cbAv++;
				break;
			}
		}
	}
	//m_OI.SetRedraw(TRUE);
}

void CEntsDlg::OnPaint() 
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
HCURSOR CEntsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEntsDlg::OnSelchangeCb1() 
{
	ResetAllValues();
	UpdatePropList(m_EntsType[m_List.GetCurSel()]);	
}

void CEntsDlg::ResetAllValues(void)
{
	for (int i=0;i<20;i++)
	{
		m_szProp[i]="";
		m_fProp[i]=0;
		m_iProp[i]=0;
		m_clProp[i]=0;
		m_cbProp[i]="";
		m_cbListProp[i].RemoveAll();
	}
}

void CEntsDlg::BuildXmlProps(CString &EntProp)
{
	EntProp="<?xml version=\"1.0\" standalone=\"yes\"?>\r\n"
					"<body>\r\n"
					"<Entity \r\n";
	
	for (vector<CObjectInspector::CProperty*>::iterator i = m_OI.m_PropertyList.begin(); i != m_OI.m_PropertyList.end(); i++)
	{

		for (vector<CObjectInspector::CProperty*>::iterator j = (*i)->m_Childs.begin(); j != (*i)->m_Childs.end(); j++)
		{
			EntProp+=(*j)->GetName();
			EntProp+="=\"";
			EntProp+=(*j)->GetValueAsText();
			EntProp+="\"\r\n ";
		}
	}

	EntProp+="/>\r\n</body>";
}



void CEntsDlg::OnNotifyProp(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString tmp;
	BuildXmlProps(tmp);
	m_Edit.SetWindowText(tmp);
	
}
