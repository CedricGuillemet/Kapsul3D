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

#ifndef CKBoneH
#define CKBoneH

#include "Kapsul3D.h"

class KAPSUL_DESC CKBoneAttach
{
public:
    int OriginIndex;
    Vertex *Origin;
    Vertex OriginVal;

	CKBoneAttach *Prev,*Next;
	double Weight;

	CKBoneAttach(CKBoneAttach *daPrev,CKBoneAttach *daNext) 
	{ 
		Prev=daPrev;
		Next=daNext;
		Weight=0;

	};
	~CKBoneAttach() { };

};

class KAPSUL_DESC CKBone
{

public:

    Vertex Pos;
	Vertex Rot;
	double Distance;
	int DistType;

	Vertex *AbsPos;

	CKMatrix *curMatrix,*matrix;
    
    Vertex Root;    // uniquement si CKBoneSrc=-1;
    Vertex OriginRoot;

    CKBone    *FirstBone,*NextBone; // parent
    CKBone    *Next,*Prev;
	CKBone	*Parent;

    CKBoneAttach **Attached;
    int     nb2VertAttach;
    int     nb2VertAttachStart;
    int     nb2VertAttachAv;

    double  ngxOrigin,ngyOrigin;


    // coord. absolues
    Vertex Hand;    // pour tous
    Vertex OriginHand;
    Vertex OriginVal;

    // coord. polaires
    double longueur;


	CKBoneAttach *FirstBA,*NextBA;
//	KeyFrame *KF;
    bool Selected;

	//char * Name;
	CString Name;
	int Tag;

public:
	
    CKBone(CKBone *daPrev,CKBone *daNext);
    ~CKBone();
    //void AddAttachedVert(void);
    void DeleteAttachedVert(void);
    //void AddVert(Vertex * Origin, double ngx, double ngy, double Length, int VertIndex);
    void ComputeBoneX(Vertex DaCent, double dang);
    void ComputeBoneY(Vertex DaCent, double dang);
    void ComputeBoneZ(Vertex DaCent, double dang);
	void AddVert(Vertex *Origin,int Index,double Weight);
	void DelAttached(void);
	void IsCopyOf(CKBone *cmpt);
};
//---------------------------------------------------------------------------
#endif
