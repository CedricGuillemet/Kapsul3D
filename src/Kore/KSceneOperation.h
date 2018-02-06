// KSceneOperation.h: interface for the CKSceneOperation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KSCENEOPERATION_H__31D82FCC_3E5A_47E5_8F0A_4EAD1E2362F6__INCLUDED_)
#define AFX_KSCENEOPERATION_H__31D82FCC_3E5A_47E5_8F0A_4EAD1E2362F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Kapsul3D.h"

class CKSceneOperation : public CKSceneSelection  
{
public:
	CKSceneOperation();
	virtual ~CKSceneOperation();

	bool TaperBuf(double Facteur,int Sens,MYPOINT &Min,MYPOINT &Max,MYPOINT &Center);
	bool SquizBuf(double Facteur,int Sens,MYPOINT &Min,MYPOINT &Max,MYPOINT &Center);
	bool BendBuf(double ngb,int Sens,MYPOINT &Min,MYPOINT &Max,MYPOINT &Center);

	void SelectedToUVBuffer(int Layer);
	void EnableUVSelectionUpdate(bool Enable);
	void TranslateUVBuf(CKPlan *dap,MYPOINT Trans);
	void UpdateUVBuf(void);
	void RotateUVBuf(CKPlan *dap,MYPOINT Center,float angle);
	void ScaleUVBuf(CKPlan *dap,MYPOINT Center,MYPOINT ScaleVal);
	void UpdateMinMaxUVBuf(void);
	bool BendUVBuf(double ngb,int Sens,MYPOINT center);
	bool SquizUVBuf(double Facteur,int Sens,MYPOINT center);
	bool TaperUVBuf(double Facteur,int Sens,MYPOINT center);
	void DeleteAll(void);
	void DeleteSelected(void);
};

#endif // !defined(AFX_KSCENEOPERATION_H__31D82FCC_3E5A_47E5_8F0A_4EAD1E2362F6__INCLUDED_)
