// Entity.cpp: implementation of the CKEntity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
unsigned int E_Unique=0;

/*
CKEntity::CKEntity()
{
	
	m_Scene=pScene;
	Prev=daPrev;
	Next=daNext;
//	m_ProcessIt=m_daProc;
	Hided=false;
	CompilData=NULL;
	Unique=E_Unique++;
	Selected=false;
	Tag=0;
	EntType=daEntType;
}
*/
CKEntity::CKEntity()
{
	m_Scene=NULL;
	Prev=NULL;
	Next=NULL;
	//m_ProcessIt=NULL;
	Hided=false;
	CompilData=NULL;
	Unique=E_Unique++;
	Selected=false;
	Tag=0;
	EntType="";
}
CKEntity::~CKEntity()
{
}

void CKEntity::SelectSingle(bool SelectFlag)
{
}

void CKEntity::OwnerDraw(int iState,int iWichone)
{
}

void CKEntity::Update()
{
}

bool CKEntity::GetSingle(int X,int Y,CKRenderer *pRenderer)
{
	return false;
}

void CKEntity::Select(CKSelectionInfos &SelInfos)
{
}

void CKEntity::Unselect()
{
}

void CKEntity::LMouseDown(int X,int Y,Vertex &Pos)
{
}

void CKEntity::RMouseDown(int X,int Y,Vertex &Pos)
{
}

void CKEntity::LMouseUp(int X,int Y,Vertex &Pos)
{
}

void CKEntity::RMouseUp(int X,int Y,Vertex &Pos)
{
}

void CKEntity::MouseMove(int X,int Y,Vertex &Pos)
{
}


void CKEntity::KeyDown(BYTE ckey)
{
}

void CKEntity::KeyUp(BYTE ckey)
{
}

bool CKEntity::CreatingStatus()
{
	return false;
}

void CKEntity::SetProperties()
{
}

void CKEntity::GetProperties()
{
}

