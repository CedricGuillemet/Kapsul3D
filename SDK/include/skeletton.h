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

#ifndef skelettonH
#define skelettonH

#include "Kapsul3D.h"

class __declspec( dllexport ) Skeletton
{

public:
    Vertex  RootPos;
    Bone    *bone;
    int     nbbone;
    int     nbboneAv;
    int     nbboneStart;

    Bone    *FirstBone,*NextBone;

    char	*Name;
    char	*ObjName;
    int     ObjIndex;

//    Math    *Maths;
    Skeletton *Next,*Prev;
    Object *daObj;
	unsigned int Unique;

    bool    Selected;

    Bone **pbs;
    int BoneCount;

public:
    Skeletton(Skeletton *daPrev=NULL,Skeletton *daNext=NULL);
    ~Skeletton();
    Bone * AddBone(Bone *Parent);

	void RotateX(Bone * BoneIndex,Vertex dacent,double dang);
	void RotateY(Bone * BoneIndex,Vertex dacent,double dang);
	void RotateZ(Bone * BoneIndex,Vertex dacent,double dang);
	Vertex IKMoveBone(Bone *BoneIndex, Vertex Position);

	bool RecurseAlreadyAttached(Bone *daBone,Vertex *vt);
	bool AlreadyAttached(Vertex *vt);
	void Del(Bone *daBa);


	void RecBuildMatrix(Bone *daBone,Vertex Origin);
	void BuildMatrix(int FrameDest);

	void RecBuildBase(Bone *daBone,Vertex Origin);
	void BuildBase(void);
	void DeformVert(Bone *daBone,int FrameDest);

	Vertex GetMinOf(void);
	Vertex GetMaxOf(void);
	Vertex GetMinOfBone(Bone *daBone);
	Vertex GetMaxOfBone(Bone *daBone);

	void GenerateBoneName(Bone *daBone);

    void DelBone(Bone *daBone);
    void DelSelectedBones(Bone *daBone);

	Bone *FindBone(char *BoneName);
	void IsCopyOf(Skeletton *cmpt);
};
//---------------------------------------------------------------------------
#endif
