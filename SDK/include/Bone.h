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

#ifndef BoneH
#define BoneH

#include "Kapsul3D.h"

class __declspec( dllexport ) BoneAttach
{
public:
    int OriginIndex;
    Vertex *Origin;
    Vertex OriginVal;

	BoneAttach *Prev,*Next;
	double Weight;

	BoneAttach(BoneAttach *daPrev,BoneAttach *daNext) 
	{ 
		Prev=daPrev;
		Next=daNext;
		Weight=0;

	};
	~BoneAttach() { };

};

class __declspec( dllexport ) Bone
{

public:

    Vertex Pos;
	Vertex Rot;

	Vertex *AbsPos;

	Matrix *curMatrix,*matrix;
    
    Vertex Root;    // uniquement si BoneSrc=-1;
    Vertex OriginRoot;

    Bone    *FirstBone,*NextBone; // parent
    Bone    *Next,*Prev;
	Bone	*Parent;

    BoneAttach **Attached;
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


	BoneAttach *FirstBA,*NextBA;
//	KeyFrame *KF;
    bool Selected;

	char * Name;

public:
	
    Bone(Bone *daPrev,Bone *daNext);
    ~Bone();
    //void AddAttachedVert(void);
    void DeleteAttachedVert(void);
    //void AddVert(Vertex * Origin, double ngx, double ngy, double Length, int VertIndex);
    void ComputeBoneX(Vertex DaCent, double dang);
    void ComputeBoneY(Vertex DaCent, double dang);
    void ComputeBoneZ(Vertex DaCent, double dang);
	void AddVert(Vertex *Origin,int Index,double Weight);
	void DelAttached(void);
	void IsCopyOf(Bone *cmpt);
};
//---------------------------------------------------------------------------
#endif
