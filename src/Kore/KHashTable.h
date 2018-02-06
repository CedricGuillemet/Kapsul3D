// KHashTable.h: interface for the CKHashTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KHASHTABLE_H__2435DDD9_9095_4204_A1BB_E14C1013043A__INCLUDED_)
#define AFX_KHASHTABLE_H__2435DDD9_9095_4204_A1BB_E14C1013043A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;
/*
enum
{
	HASH_STRING,
	HASH_FLOAT,
	HASH_DOUBLE,
	HASH_DWORD,
	HASH_INT
};
*/
class KAPSUL_DESC CKHashEntry
{
public:
	CString vals,m_Name;
	DWORD valdw;
	//int Type;
public:
	CKHashEntry() { };
	CKHashEntry(CString Name) { m_Name=Name; };
	~CKHashEntry() { };
	inline void SetEntry(CString Value) { vals=Value;  };
	inline void SetEntry(float Value) {vals.Format("%f",Value); };
	//inline void SetEntry(double Value) {vald=Value; Type=HASH_DOUBLE; };
	inline void SetEntry(DWORD Value) {vals.Format("%x",Value); };
	inline void SetEntry(int Value) {vals.Format("%d",Value); };

	inline CString GetName(void) {return m_Name; };
	inline CString GetString(void) {return vals; };
	inline float GetFloat(void) { return atof(vals); };
	//inline double GetDouble(void) { sscanf(vals,"%f",&valf); return vald; };
	inline DWORD GetDWord(void) { sscanf(vals,"%x",&valdw); return valdw; };
	inline int GetInt(void) { return atoi(vals); };
	//inline int GetType(void) { return Type ; };

	inline void operator =(CKHashEntry khe)
	{
		vals=khe.GetString();
		m_Name=khe.GetName();
		valdw=khe.GetDWord();
	}

};


class KAPSUL_DESC CKHashTable  
{
private:
	vector <CKHashEntry*> m_Entries;
	inline CKHashEntry* FindEntry(CString Name);
	CKHashEntry* tmpEnt;
public:
	CKHashTable();
	virtual ~CKHashTable();
	void SetEntry(CString Name,CString Value);
	void SetEntry(CString Name,float Value);
	void SetEntry(CString Name,double Value);
	void SetEntry(CString Name,DWORD Value);
	void SetEntry(CString Name,int Value);

	CString GetString(CString Name);
	float GetFloat(CString Name);
	double GetDouble(CString Name);
	DWORD GetDWord(CString Name);
	int GetInt(CString Name);

	void WriteToDisk(FILE *fp,void *pObj=NULL,int PlugType=0);
	void ReadFromDisk(FILE *fp,void *pObj=NULL,int PlugType=0);
	void WriteToDisk(CString FileName,void *pObj=NULL,int PlugType=0);
	void ReadFromDisk(CString FileName,void *pObj=NULL,int PlugType=0);

	bool ReadHash(CString strRead,CString &dName,CString &dValue);
	void SetReadValue(CString dName,CString dValue);

	inline int GetNbEntries(void) { return m_Entries.size(); };
	inline CKHashEntry* GetEntry(int nb) { return m_Entries[nb]; };

	inline void IsCopyOf(CKHashTable &kht);
	bool EntryExists(CString Name);
	
	void EraseAll(void);

};

#endif // !defined(AFX_KHASHTABLE_H__2435DDD9_9095_4204_A1BB_E14C1013043A__INCLUDED_)
