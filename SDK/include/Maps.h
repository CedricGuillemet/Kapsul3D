// Maps.h: interface for the CMaps class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPS_H__DCCAF4D8_F3E4_4727_8EDA_BAAA26EDCBD1__INCLUDED_)
#define AFX_MAPS_H__DCCAF4D8_F3E4_4727_8EDA_BAAA26EDCBD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Kapsul3D.h"

class CMaps  
{
public:
	CMaps();
	virtual ~CMaps();

    CImage *FirstImg,*NextImg;

    CImage *AddMap(char *MapName);
    CImage *AlreadyIn(char *MapName);

};

#endif // !defined(AFX_MAPS_H__DCCAF4D8_F3E4_4727_8EDA_BAAA26EDCBD1__INCLUDED_)
