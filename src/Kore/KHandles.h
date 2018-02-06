// KHandles.h: interface for the CKHandles class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KHANDLES_H__4C45D24B_F3B4_4D58_821A_22091801A97F__INCLUDED_)
#define AFX_KHANDLES_H__4C45D24B_F3B4_4D58_821A_22091801A97F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SELTESSELATE 8

class KAPSUL_DESC CKHandles  
{
public:
	CKHandles();
	virtual ~CKHandles();

	MYPOINT a2DHandles[(SELTESSELATE+1)*4+1];
	MYPOINT spt[8],MinPt,MaxPt;
	Vertex CurHookMaxSel,CurHookMinSel;

	bool CalculateHandles;
	void CalcHandles(CKScene *m_Scene,int ActiveView,Vertex HandMin,Vertex HandMax);
	void RotateHandles(float degs,int ActiveView);
	void DrawHandles(CKScene *m_Scene,int ActiveView,Vertex HandMin,Vertex HandMax);
	void Get2DCenter(int ActiveView,MYPOINT &Center);
	int GetHandle(CKScene *m_Scene,int X,int Y);
	MYPOINT ta2DHandles[10];
	Vertex *DrawHanks,*Hanks;

	void TranslateHandles(MYPOINT trans,int ActiveView);
	void ScaleHandles(int Corner,MYPOINT ScaleVal,int ActiveView);
	void BendBuf(int Corner,double ngb,int Sens);
	void SquizBuf(int Corner,double Facteur,int Sens);
	void TaperBuf(int Corner,double Facteur,int Sens);
};

#endif // !defined(AFX_KHANDLES_H__4C45D24B_F3B4_4D58_821A_22091801A97F__INCLUDED_)
