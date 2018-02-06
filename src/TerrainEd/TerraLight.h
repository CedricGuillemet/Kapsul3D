// TerraLight.h: interface for the CTerraLight class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TERRALIGHT_H__6DC32FB5_4686_4704_85A6_526830E92AB5__INCLUDED_)
#define AFX_TERRALIGHT_H__6DC32FB5_4686_4704_85A6_526830E92AB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Terra.h"

class CTerraLight : public CKImage  
{
public:
	void GenerateLight(CTerra *pTerrain,double dAngle,BYTE bAmbiantVal,BYTE bSunVal);
	CTerraLight();
	virtual ~CTerraLight();

};

#endif // !defined(AFX_TERRALIGHT_H__6DC32FB5_4686_4704_85A6_526830E92AB5__INCLUDED_)
