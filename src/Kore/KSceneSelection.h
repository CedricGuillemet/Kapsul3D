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

#ifndef CKSceneSelectionH
#define CKSceneSelectionH

#include "Kapsul3D.h"

class KAPSUL_DESC CKSceneSelection : public CKSceneBase
{
    public:
        // -- Links ------------------------------------------------------------
        //int nbSect;
        //double *Sec;
    public:
		//CKSceneSelection *m_Scene;      
		double m_Precision;
        // -- Constructors/Destructors -----------------------------------------

        CKSceneSelection();
        ~CKSceneSelection();

        // -- Tools ------------------------------------------------------------

        MYPOINT Get2D(Vertex daVert);
		//Vertex GetIsoCoord(MYPOINT pt,int ViewInd);

        bool IsVertInBuf(Vertex *daVert);
        Vertex GetCenterOfSel(Vertex *daMin=NULL,Vertex *daMax=NULL);
        bool RemoveVert(Vertex *daVert);
        CKSegment *Collapse(CKShape *daShp,Vertex *daVert);           

        // -- To Buffer --------------------------------------------------------

		CKPatch *GetPatchByTriangle(int X,int Y,bool SelectIt);
		// Single

		void SingleMesh(CKMesh *daObj,bool AddIt);
		void SingleShape(CKShape *daShp,bool AddIt);
		void RecSingleSkeleton(CKSkeleton *daSkel,CKBone *daBone,bool AddIt);
		void SingleSkeleton(CKSkeleton *daSkel,bool AddIt);
		void SinglePatch(CKPatch *daPatch,bool AddIt);
		void SingleEntity(CKEntity *daEnt,bool AddIt);
		void SingleCamera(CKCamera *daCam,bool AddIt);

        // CKCamera

		bool SelectCam(int dx,int dy,int X,int Y,CKShape *daSh,bool AddIt,bool Crossing,int TypeSel,int WholeSelect);
        bool SingleMeshByTriangle(int X,int Y,bool AddIt);
		bool SingleObjEdge(int X,int Y,bool AddIt);
		CKMesh *IsOverSelectedMesh(int X,int Y);
		CKMesh *GetMeshByTriangle(int X,int Y,bool SelectIt=true,int *FaceNb=NULL);

        // CKMesh
		bool SelectMesh(int dx,int dy,int X,int Y,CKShape *daSh,bool AddIt,bool Crossing,int TypeSel,int WholeSelect);

		// patch
		bool SelectPatch(int dx,int dy,int X,int Y,CKShape *daSh,bool AddIt,bool Crossing,int TypeSel,int WholeSelect);

        // CKSkeleton

        bool SingleSkel(int X,int Y,bool AddIt);
        bool CircleSkel(int dx,int dy,int X,int Y,bool AddIt,bool Crossing);
        bool QuadSkel(int dx,int dy,int X,int Y,bool AddIt,bool Crossing);
        bool FenceSkel(int dx,int dy,int X,int Y,CKShape *daSh,bool AddIt,bool Crossing);

        void RecIsAllSkelInCircle(CKBone *daBone,int dx,int dy,int X,int Y,double Length,bool *AllIn,bool *OneIn);
        void IsAllSkelInCircle(CKSkeleton *daSkel,int dx,int dy,int X,int Y,double Length,bool *AllIn,bool *OneIn);

        void RecIsAllSkelInQuad(CKBone *daBone,int dx,int dy,int X,int Y,bool *AllIn,bool *OneIn);
        void IsAllSkelInQuad(CKSkeleton *daSkel,int dx,int dy,int X,int Y,bool *AllIn,bool *OneIn);

        void IsAllSkelInFence(CKBone *daBone,int dx,int dy,int X,int Y,CKShape *daSh,bool *AllIn,bool *OneIn);
        void IsAllSkelInFence(CKSkeleton *daSkel,int dx,int dy,int X,int Y,CKShape *daSh,bool *AllIn,bool *OneIn);

        // CKBone

        bool RecSingleSkel(CKBone *daBone,bool AddIt);
        bool RecCircleSkel(CKBone *daBone,int dx,int dy,int X,int Y,bool AddIt,bool Crossing);
        bool RecQuadSkel(CKBone *daBone,int dx,int dy,int X,int Y,bool AddIt,bool Crossing);
        bool RecFenceSkel(CKBone *daBone,int dx,int dy,int X,int Y,CKShape *daSh,bool AddIt,bool Crossing);

		bool RecSelectBone(CKBone *daBone,CKSkeleton *daSkel,MYPOINT &spt,MYPOINT &spt2,double Length,CKShape *daSh,bool AddIt,bool Crossing,int TypeSel,int WholeSelect);
		bool SelectBone(int dx,int dy,int X,int Y,CKShape *daSh,bool AddIt,bool Crossing,int TypeSel,int WholeSelect);

        // CKShape
		bool SelectShape(int dx,int dy,int X,int Y,CKShape *daSh,bool AddIt,bool Crossing,int TypeSel,int WholeSelect);
		bool SelectEntity(int dx,int dy,int X,int Y,CKShape *daSh,bool AddIt,bool Crossing,int TypeSel,int WholeSelect);

		bool SelectUV(int dx,int dy,int X,int Y,CKShape *daSh,bool AddIt,bool Crossing,int TypeSel,int WholeSelect);
		void UnSelectUV(bool daSelVal);
        // -- Get single -------------------------------------------------------

        CKCamera *GetCamera(int X,int Y);
        CKCamera *GetCamera(int X,int Y,bool IsTarget);
        CKMesh *GetMesh(int X,int Y);
		CKEntity *GetEntity(int X,int Y);
		CKPatch *GetPatch(int X,int Y);
        CKShape *GetShape(int X,int Y);
        CKBone *RecurseGetBone(int X,int Y,Vertex Node,CKBone *daBone,MYPOINT daclick);
//        CKBone *GetCKSkeleton(int X,int Y);
        CKBone *GetBone(int X,int Y);
        Vertex *GetShapeVert(int X,int Y);
        Vertex *GetObjVert(int X,int Y,int &VertInd);
		CKSkeleton *GetSkeleton(int X,int Y);


		void GetShapeSeg(CKShape **DstShp,CKSegment **DstSeg,CKSegment *Else,int X,int Y);
		void GetShapeVert(CKShape **DstShp,CKSegment **DstSeg,CKSegment *Else,int X,int Y);
		void GetStartShapeVert(CKShape **DstShp,CKSegment **DstSeg,CKSegment *Else,int X,int Y);
		void GetEndShapeVert(CKShape **DstShp,CKSegment **DstSeg,CKSegment *Else,int X,int Y);
        // -- Unselect ---------------------------------------------------------



        void UnSelectCamera(bool daSelVal);
        void UnSelectMesh(bool daSelVal);
        void UnSelectShape(bool daSelVal);
        void RecUnSelectSkeleton(CKBone *daBone,bool daSelVal);
        void UnSelectSkeleton(bool daSelVal);
        void UnSelectEntity(bool daSelVal);
        void UnSelectAll(bool daSelVal);
		void UnSelectPatch(bool daSelVal);


		void SelectAll(void);
		virtual void UpdateSmthSel(void);

		virtual void SelectedToUVBuffer(int Layer);
		virtual void UpdateMinMaxUVBuf(void);
};
//---------------------------------------------------------------------------
#endif
