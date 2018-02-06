// UndoRedo.h: interface for the CUndoRedo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNDOREDO_H__331C3EB3_1FCE_4C9A_8440_5E7A0DD38911__INCLUDED_)
#define AFX_UNDOREDO_H__331C3EB3_1FCE_4C9A_8440_5E7A0DD38911__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class __declspec( dllexport ) CUndoRedo  
{
public:
	char *PlugName;
	CUndoRedo *Prev,*Next;
	Desk *dk;
	CUndoRedoEntry *Entries;
	int nbEntries;
	GenericLib *gen;
	int UndoType;
public:
	void CommitAllAfter(void);
	void CommitAllPrev(void);
	void SetPrevEntry(int Indice,int Type,void *Entry);
	void SetAfterEntry(int Indice,int Type,void *Entry);
	CUndoRedoEntry * GetEntry(int Indice);
	
	CUndoRedo(char *_PlugName,Desk *_dk,int _nbEntries,CUndoRedo *_Prev,CUndoRedo *_Next);
	virtual ~CUndoRedo();

};

#endif // !defined(AFX_UNDOREDO_H__331C3EB3_1FCE_4C9A_8440_5E7A0DD38911__INCLUDED_)
