// UndoRedo.h: interface for the CKUndoRedo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNDOREDO_H__331C3EB3_1FCE_4C9A_8440_5E7A0DD38911__INCLUDED_)
#define AFX_UNDOREDO_H__331C3EB3_1FCE_4C9A_8440_5E7A0DD38911__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "KScenePlugin.h"
class KAPSUL_DESC CKUndoRedo  
{
public:
	CString PlugName;
	CKUndoRedo *Prev,*Next;
	CKScene *m_Scene;
	CKUndoRedoEntry *Entries;
	int nbEntries;
	CKScenePlugin *gen;
	int UndoType;
public:
	void CommitAllAfter(void);
	void CommitAllPrev(CKScenePlugin *gen);
	void SetPrevEntry(int Indice,CKObjectBase *pEntry);
	void SetAfterEntry(int Indice,CKObjectBase *pEntry);
	CKUndoRedoEntry * GetEntry(int Indice);
	
	CKUndoRedo(CString _PlugName,CKScene *pScene,int _nbEntries,CKUndoRedo *_Prev,CKUndoRedo *_Next);
	virtual ~CKUndoRedo();

};

#endif // !defined(AFX_UNDOREDO_H__331C3EB3_1FCE_4C9A_8440_5E7A0DD38911__INCLUDED_)
