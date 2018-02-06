// OptionsEditing.cpp : implementation file
//

#include "stdafx.h"
#include "kapsulSE.h"

//#include "memmgr/mmgr.h"

#include "OptionsEditing.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsEditing dialog
extern CKapsulApp theApp;
extern CKOption *KOption;
extern CKLocalization loc;
COptionsEditing::COptionsEditing(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsEditing::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionsEditing)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COptionsEditing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsEditing)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsEditing, CDialog)
	//{{AFX_MSG_MAP(COptionsEditing)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsEditing message handlers

BOOL COptionsEditing::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	RECT rc;
	int szAv=0,clAv=0,iAv=0,fAv=0,cbAv=0,iOther=0,cblAv=0,blAv=0;
	char value[256];

	GetClientRect(&rc);

	m_Oi.Create(rc,this,8858,WS_CHILD|WS_VISIBLE);
	

	init init;
	tree_parser parser("options.xml");

	if (!parser) 
	{
		MessageBox("Error parsing file");
		return 1;
	}
	
	node &root = parser.get_root_node();

	node::const_iterator child(root.begin()), child_end(root.end());
	for (; child != child_end; ++child) 
	{
		if (child->is_text()) continue;


		if (strcmp(child->get_name() ,"Options")==0)
		{
			node::const_iterator child2(child->begin()), child_end(child->end());
			for (; child2 != child_end; ++child2) 
			{
				if (child2->is_text()) continue;
					
				if (strcmp(child2->get_name() ,"Group")==0)
				{
			
					// param name
					child2->get_attr("value",value);
					int ddInd=loc.OptGroupGetID(value);
					CString grpName;
					if (ddInd!=0)
					{
						grpName=loc.GetString(ddInd+2000,value);
					}
					else
						grpName=value;

					CObjectInspector::CProperty *pProp;

					m_Oi.AddProperty (pProp = new CObjectInspector::CProperty(grpName));
					pProp->Expand ();

					node::const_iterator child3(child2->begin()), child_end(child2->end());
					for (; child3 != child_end; ++child3) 
					{
						if (child3->is_text()) continue;

						if (strcmp(child3->get_name() ,"Groupvalues")==0)
						{
							char Name[256];
							child3->get_attr("name",Name);

							CString NameLoc;
							int locnb=KOption->FindByName(Name);
							if (locnb!=-1)
							{
								NameLoc=loc.GetString(1001+locnb);
							}
							else
							{
								NameLoc=Name;
							}

							child3->get_attr("type",value);
							int Type=m_Oi.GetParamType(value);

							if (Type == 4)
							{
								// combo,masked & slider
								char tempcbl[64];
								int valAv=0;

								sprintf(tempcbl,"value%d",valAv);
								while(child3->get_attr(tempcbl,value))
								{
									m_cbListProp[cblAv].AddTail(value);
									valAv++;
									sprintf(tempcbl,"value%d",valAv);
								}

								//cblAv++;
							}else
							if (Type == 5 || Type == 6)
							{
								// masked & slider
								char tempcbl[64];
								int valAv=0;

								sprintf(tempcbl,"value%d",valAv);
								while(child3->get_attr(tempcbl,value))
								{
									m_initProp[iOther].AddTail(value);
									valAv++;
									sprintf(tempcbl,"value%d",valAv);
								}
								//iOther++;
							}

							switch(Type)
							{
							case 0:
								m_szProp[szAv]=KOption->GetString(Name);
								pProp->AddProperty (new CObjectInspector::CProperty(NameLoc, &m_szProp[szAv++]));
								break;
							case 1:
								m_iProp[iAv]=KOption->GetInt(Name);
								pProp->AddProperty (new CObjectInspector::CProperty(NameLoc, &m_iProp[iAv++]));
								break;
							case 2:
								m_clProp[clAv]=KOption->GetColor(Name);
								pProp->AddProperty (new CObjectInspector::CProperty(NameLoc, &m_clProp[clAv++]));
								break;
							case 3:
								//m_iProp[iAv]=KOption->GetFloat(NameLoc);
								pProp->AddProperty (new CObjectInspector::CProperty(NameLoc, &m_fProp[fAv++]));
								break;
							case 4:
								pProp->AddProperty (new CObjectInspector::CProperty(NameLoc, &m_cbProp[cbAv], &m_cbListProp[cbAv] , -1, CBS_DROPDOWNLIST));
								cbAv++;
								break;
							case 5:	//MASKED	
								pProp->AddProperty (new CObjectInspector::CProperty(NameLoc, m_initProp[iOther].GetAt(m_initProp[iOther].FindIndex(0)).GetBuffer(1)));
								iOther++;
								break;
							case 6:	//SLIDER
								m_iProp[iAv]=KOption->GetInt(Name);
								pProp->AddProperty (new CObjectInspector::CProperty(NameLoc, &m_iProp[iAv++],
									atoi(m_initProp[iOther].GetAt(m_initProp[iOther].FindIndex(0)).GetBuffer(1)),atoi(m_initProp[iOther].GetAt(m_initProp[iOther].FindIndex(1)).GetBuffer(1)),false));//INT_MIN,INT_MAX,false));
								iOther++;
								break;
							case 7:	//MEMO
								pProp->AddProperty (new CObjectInspector::CProperty(NameLoc, &m_szProp[szAv++])); 
								break;
							case 8:	//FBROWSER
								m_szProp[szAv]=KOption->GetString(Name);
								pProp->AddProperty (new CObjectInspector::CProperty(NameLoc, &m_szProp[szAv],m_szProp[szAv++]));
								break;
							case 9: // boolean
								m_blProp[blAv]=KOption->GetBool(Name);
								pProp->AddProperty (new CObjectInspector::CProperty(NameLoc, &m_blProp[blAv++]));
								break;
							}

							if (Type == 4)
							{
								cblAv++;
							}
							else
							if (Type == 5 || Type == 6)
							{
								// masked & slider
								iOther++;
							}
						}
					}
				}
			}
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionsEditing::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}


void COptionsEditing::ValidateOptions(void)
{
	/*
	int COption::FindByName(char *Name)
{
	int i;
	for (i=0;i<NB_OPTIONS;i++)
	{
		// Search IS NOT case-sensitive
		if (StrCmpI(Name,OptValues[i].Name)==0)
		{
			return i;
		}
	}
	return -1;
}
*/
	for (vector<CObjectInspector::CProperty*>::iterator i = m_Oi.m_PropertyList.begin(); i != m_Oi.m_PropertyList.end(); i++)
	{
		for (vector<CObjectInspector::CProperty*>::iterator j = (*i)->m_Childs.begin(); j != (*i)->m_Childs.end(); j++)
		{
			KOption->ReadUserFileValue(CString((*j)->GetName()).GetBuffer(1),CString((*j)->GetValueAsText()).GetBuffer(1));
		}
	}
}