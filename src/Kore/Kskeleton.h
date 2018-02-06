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

#ifndef CKSkeletonH
#define CKSkeletonH

#include "Kapsul3D.h"
#include <vector>
using std::vector;

class KAPSUL_DESC CKSkeleton : public CKObjectBase
{

public:
    Vertex  RootPos;
    CKBone    *bone;
    int     nbbone;
    int     nbboneAv;
    int     nbboneStart;

    CKBone    *FirstBone,*NextBone;

    CString ObjName;
    int     ObjIndex;

    CKSkeleton *Next,*Prev;
    CKMesh *m_Mesh;

    CKBone **pbs;
    int BoneCount;


public:
    CKSkeleton(CKSkeleton *daPrev=NULL,CKSkeleton *daNext=NULL);
    ~CKSkeleton();
    CKBone * AddBone(CKBone *Parent);

	void RotateX(CKBone * BoneIndex,Vertex dacent,double dang);
	void RotateY(CKBone * BoneIndex,Vertex dacent,double dang);
	void RotateZ(CKBone * BoneIndex,Vertex dacent,double dang);
	Vertex IKMoveBone(CKBone *BoneIndex, Vertex Position);

	bool RecurseAlreadyAttached(CKBone *daBone,Vertex *vt);
	bool AlreadyAttached(Vertex *vt);
	void Del(CKBone *daBa);


	void RecBuildMatrix(CKBone *daBone,Vertex Origin);
	void BuildMatrix(int FrameDest);

	void RecBuildBase(CKBone *daBone,Vertex Origin);
	void BuildBase(void);
	void DeformVert(CKBone *daBone,int FrameDest);

	Vertex GetMinOf(void);
	Vertex GetMaxOf(void);
	Vertex GetMinOfBone(CKBone *daBone);
	Vertex GetMaxOfBone(CKBone *daBone);

	void GenerateBoneName(CKBone *daBone);

    void DelBone(CKBone *daBone);
    void DelSelectedBones(CKBone *daBone);

	CKBone *FindBone(CString BoneName);
	void IsCopyOf(CKSkeleton *cmpt);
	void UpdateSkel(void);

	void ComputeDistFromPoint(Vertex &pt);
	vector<CKBone*> LinBones;

};
//---------------------------------------------------------------------------
#endif
