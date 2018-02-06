// Kapsul Core Library
// Copyright © 1999 - 2001, Cédric Guillemet
//
// Contact: lacrapul@club-internet.fr
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#if !defined(AFX_PRIVATEDATA_H__77F31080_3AC5_490C_A918_1F154BFA29DB__INCLUDED_)
#define AFX_PRIVATEDATA_H__77F31080_3AC5_490C_A918_1F154BFA29DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Kapsul3D.h"

class __declspec( dllexport ) CPrivateData  
{
public:
	void * Allocate(int Size);
	CPrivateData(CPrivateData *daPrev,CPrivateData *daNext);
	virtual ~CPrivateData();

    CPrivateData *Next,*Prev;
    int AllocatedByte;
    void *lpBits;
    char *Name;

};

#endif // !defined(AFX_PRIVATEDATA_H__77F31080_3AC5_490C_A918_1F154BFA29DB__INCLUDED_)
