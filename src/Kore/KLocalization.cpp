// KLocalization.cpp: implementation of the CKLocalization class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "kore.h"
#include "KLocalization.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKLocalization::CKLocalization()
{
	//CurrentLang=GetUserDefaultLangID();
	LanguageCount=0;
	CurrentLanguage=-1;
}

CKLocalization::~CKLocalization()
{

}

bool CKLocalization::ReadXmlStringFile(CString Path)
{
	char value[256];
	init init;

	tree_parser parser(Path);

	if (!parser) 
	{
		//std::cerr << argv[0] << ": error parsing XML file\r\n";
		MessageBox(NULL,"Localization.xml file not found.","Error parsing file",MB_ICONERROR|MB_OK);
		return false;
	}
	
	node &root = parser.get_root_node();

	node::const_iterator child(root.begin()), child_end(root.end());
	for (; child != child_end; ++child) 
	{
		if (child->is_text()) continue;

		if (strcmp(child->get_name() ,"Country")==0)
		{
			child->get_attr("ID",value);
			int ID;
			sscanf(value,"%x",&ID);
			child->get_attr("IDString",value);

			LangStrings *ls=new LangStrings(ID,CString(value));
			m_LangStrings.insert(m_LangStrings.end(),ls);

			LanguageCount++;

			node::const_iterator child2(child->begin()), child_end(child->end());
			for (; child2 != child_end; ++child2) 
			{
				if (child2->is_text()) continue;

				if (strcmp(child2->get_name() ,"String")==0)
				{
					child2->get_attr("ID",value);
					sscanf(value,"%d",&ID);
					child2->get_attr("IDString",value);
					CString tmpstr=value;
					tmpstr.Replace("\\t","\t");
					tmpstr.Replace("\\r","\r");
					ls->LocStrings.insert(ls->LocStrings.end(),new LangString(ID,tmpstr));
					ls->nbString++;
				}
			}
		}
	}

	// try to set the best language
	vector<LangStrings*>::iterator i;
	int tmpLang=GetUserDefaultLangID();

	CurrentLanguage=0;
	for (i = m_LangStrings.begin(); i != m_LangStrings.end(); i++)
	{
		if ((*i)->Key==tmpLang)
		{
			CurrentLang=(*i)->Key;
			return true;
		}
		CurrentLanguage++;
	}

	// try to set english
	CurrentLanguage=0;
	for (i = m_LangStrings.begin(); i != m_LangStrings.end(); i++)
	{
		if ((*i)->LangName.CompareNoCase("ENGLISH")==0)
		{
			CurrentLang=(*i)->Key;
			return true;
		}
		CurrentLanguage++;
	}


	return true;
}

LANGID CKLocalization::GetLangID()
{
	return CurrentLang;
}

CString CKLocalization::GetString(int Key,CString Default)
{
	for (vector<LangStrings*>::iterator i = m_LangStrings.begin(); i != m_LangStrings.end(); i++)
	{
		if ((*i)->Key==CurrentLang)
		{
			for (vector<LangString*>::iterator j = (*i)->LocStrings.begin(); j != (*i)->LocStrings.end(); j++)
			{
				if ((*j)->Number==Key)
				{
					return (*j)->Value;
				}
			}
		}
	}
	return Default;
}

int CKLocalization::GetStringCount(void)
{ 
	for (vector<LangStrings*>::iterator i = m_LangStrings.begin(); i != m_LangStrings.end(); i++)
	{
		if ((*i)->Key==CurrentLang)
		{
			return (*i)->nbString;
		}
	}
	return 0;
}
void CKLocalization::EraseList(void)
{
	m_LangStrings.erase(m_LangStrings.begin(),m_LangStrings.end());
	
}
int CKLocalization::GetIDFromString(CString tocomp)
{
	for (vector<LangStrings*>::iterator i = m_LangStrings.begin(); i != m_LangStrings.end(); i++)
	{
		if ((*i)->Key==CurrentLang)
		{
			for (vector<LangString*>::iterator j = (*i)->LocStrings.begin(); j != (*i)->LocStrings.end(); j++)
			{
				if ((*j)->Value==tocomp)
				{
					return (*j)->Number;
				}
			}
		}
	}
	return 0;
}

// Hacks starts here

CString PopupNames[16]={"&File","&Edit","Select","Mode","Entity","&View","Config",
"Type","Render Mode","Skybox","Grid","Build","Tools","&Window","&Help","Localization"};

CString OptGroupNames[9]={"Colors","Automatic brush color","Edit","Logs","Fly","Undos","Entities",
"Misc","Autosave",};

int CKLocalization::MenuFindPopupID(CString popupname)
{
	for (int i=0;i<16;i++)
	{
		if (PopupNames[i]==popupname) return (i+1);
	}
	return 0;
}

int CKLocalization::OptGroupGetID(CString popupname)
{
	for (int i=0;i<9;i++)
	{
		if (OptGroupNames[i]==popupname) return (i+1);
	}
	return 0;
}

int CKLocalization::GetLanguageCount(void)
{
	return LanguageCount;
}

CString CKLocalization::GetLanguageName(int LngNb)
{
	if ((LngNb>=0)&&(LngNb<LanguageCount))
	{
		return m_LangStrings[LngNb]->LangName;

	}
	return "UnknownLanguage";
}

int CKLocalization::GetCurrentLangInd(void)
{
	return CurrentLanguage;
}
