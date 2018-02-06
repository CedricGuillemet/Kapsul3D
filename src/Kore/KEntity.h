// Entity.h: interface for the CKEntity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENTITY_H__08EA7388_6215_4C12_A69F_0D56A05DD15B__INCLUDED_)
#define AFX_ENTITY_H__08EA7388_6215_4C12_A69F_0D56A05DD15B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Kapsul3D.h"
#include "KHashTable.h"
class CKEntity;

//class CKSelectionInfos;
typedef struct
{
	int dx,dy,X,Y;
	CKShape *daSh;
	bool AddIt,Crossing;
	int TypeSel,WholeSelect;
	MYPOINT spt,spt2;
    double Length;
	CKRenderer *m_Renderer;
	int Active;
} CKSelectionInfos;


class KAPSUL_DESC CKEntity : public CKObjectBase
{
public:
	CKEntity();
	virtual ~CKEntity();
	//void UpdateDLLLink(void);

	virtual void SelectSingle(bool SelectFlag);
	virtual void OwnerDraw(int iState,int iWichone);

	virtual void Update();
	virtual bool GetSingle(int X,int Y,CKRenderer *pRenderer);
	virtual void Select(CKSelectionInfos &SelInfos);
	virtual void Unselect();

	virtual bool CreatingStatus();

	virtual void SetProperties();
	virtual void GetProperties();

    virtual void LMouseDown(int X,int Y,Vertex &Pos);
    virtual void RMouseDown(int X,int Y,Vertex &Pos);
    virtual void LMouseUp(int X,int Y,Vertex &Pos);
    virtual void RMouseUp(int X,int Y,Vertex &Pos);
    virtual void MouseMove(int X,int Y,Vertex &Pos);

	virtual void KeyDown(BYTE ckey);
	virtual void KeyUp(BYTE ckey);

	

public:
	CKEntity *Prev,*Next;
	CKEntity *PrevSameType,*NextSameType;
	void *CompilData;

	CString EntType;

	inline void IsCopyOf(CKEntity *daEnt)
	{
		CompilData=NULL;
		Unique=daEnt->Unique;
		Hided=daEnt->Hided;
		EntType=daEnt->EntType;
		m_Table.IsCopyOf(daEnt->m_Table);
		m_Scene=daEnt->m_Scene;
		SelectSingle(true);
		Selected=true;
	}
};

#endif // !defined(AFX_ENTITY_H__08EA7388_6215_4C12_A69F_0D56A05DD15B__INCLUDED_)
