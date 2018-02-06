// Entity.h: interface for the CKEntity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CKEntityParticle_H__08EA7388_6215_4C12_A69F_0D56A05DD15B__INCLUDED_)
#define AFX_CKEntityParticle_H__08EA7388_6215_4C12_A69F_0D56A05DD15B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Kapsul3D.h"
#include "emitter.h"

class CKEntityParticle : public CKEntity  
{
public:
	CKEntityParticle();
	virtual ~CKEntityParticle();

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

private:
	
	Emitter m_Emit;
	//CString xmlDatas,tmpxml;
	MYPOINT spt,spt2;
	//CKSelectionInfos *CurSel;
//CKDrawScene *GDrawScene;
	bool daAddIt;
	MYPOINT sdeb;
	
};

#endif // !defined(AFX_ENTITY_H__08EA7388_6215_4C12_A69F_0D56A05DD15B__INCLUDED_)
