// KLocalization.h: interface for the CKLocalization class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KLOCALIZATION_H__6E3361D1_80C2_4156_B3FA_3E7ACC7489C4__INCLUDED_)
#define AFX_KLOCALIZATION_H__6E3361D1_80C2_4156_B3FA_3E7ACC7489C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>
using std::vector;

class LangString
{
	public:
		LangString(int Numb,CString Val) 
		{
			Number=Numb;
			Value=Val;
		};
		~LangString() {};
		int Number;
		CString Value;

};
class LangStrings
{
public:
	LangStrings(int _LangID,CString _LangName) 
	{
		Key=_LangID;
		LangName=_LangName;
		nbString=0;
	};
	~LangStrings() {};
	vector<LangString*> LocStrings;
	LANGID Key;
	CString LangName;
	int nbString;
};

class KAPSUL_DESC CKLocalization  
{
	vector<LangStrings*> m_LangStrings;
	LANGID CurrentLang;
	int	LanguageCount;
	int CurrentLanguage;

public:
	CKLocalization();
	virtual ~CKLocalization();
	bool ReadXmlStringFile(CString Path);
	LANGID GetLangID();
	CString GetString(int Key,CString Default="");
	int GetStringCount(void);
	void EraseList(void);
	int GetIDFromString(CString tocomp);
	int MenuFindPopupID(CString popupname);
	int OptGroupGetID(CString popupname);
	int GetLanguageCount(void);
	CString GetLanguageName(int LngNb);
	int GetCurrentLangInd(void);

};

#endif // !defined(AFX_KLOCALIZATION_H__6E3361D1_80C2_4156_B3FA_3E7ACC7489C4__INCLUDED_)
