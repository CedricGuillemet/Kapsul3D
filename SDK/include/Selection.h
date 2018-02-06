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

#ifndef SelectionH
#define SelectionH

#include "Kapsul3D.h"

class __declspec( dllexport ) Selection
{
    public:

        // -- Links ------------------------------------------------------------

        int nbSect;
        double *Sec;


    public:

		Desk *dk;      
		OGLView *View;


        // -- Constructors/Destructors -----------------------------------------

        Selection(void*dadk,void *daView);
        ~Selection();


        // -- Tools ------------------------------------------------------------

        MYPOINT Get2D(Vertex daVert);
        bool IsVertInBuf(Vertex *daVert);
        Vertex GetCenterOfSel(Vertex *daMin=NULL,Vertex *daMax=NULL);
        //bool IsVertInShape(Vertex daVert,Shape *daSh);
        bool RemoveVert(Vertex *daVert);
        Segment *Collapse(Shape *daShp,Vertex *daVert);           
        // -- To Buffer --------------------------------------------------------

        // Camera
/*
        bool SingleCamera(int X,int Y,bool AddIt);
        bool CircleCam(int dx,int dy,int X,int Y,bool AddIt,bool Crossing);
        bool QuadCam(int dx,int dy,int X,int Y,bool AddIt,bool Crossing);
        bool FenceCam(int dx,int dy,int X,int Y,Shape *daSh,bool AddIt,bool Crossing);
		*/
		bool SelectCam(int dx,int dy,int X,int Y,Shape *daSh,bool AddIt,bool Crossing,int TypeSel,int WholeSelect);

/*
        bool SingleCameraVert(int X,int Y,bool AddIt);
        bool CircleCamVert(int dx,int dy,int X,int Y,bool AddIt,bool Crossing);
        bool QuadCamVert(int dx,int dy,int X,int Y,bool AddIt,bool Crossing);
        bool FenceCamVert(int dx,int dy,int X,int Y,Shape *daSh,bool AddIt,bool Crossing);
		*/
        // Object
/*
        bool SingleObject(int X,int Y,bool AddIt);
        bool CircleObject(int dx,int dy,int X,int Y,bool Crossing,bool AddIt);
        bool QuadObject(int dx,int dy,int X,int Y,bool Crossing,bool AddIt);
        bool FenceObject(int dx,int dy,int X,int Y,Shape *daSh,bool Crossing,bool AddIt);
		*/
        void SingleObject(Object *daObj,bool AddIt);
//void Selection::SelectObject(Object *daObj,bool daSelVal)
        bool SingleObjectByTriangle(int X,int Y,bool AddIt);
        
		bool SingleObjEdge(int X,int Y,bool AddIt);
		Object *IsOverSelectedObject(int X,int Y);
		Object *GetObjectByTriangle(int X,int Y,bool SelectIt=true);

        // Object Vert
/*
        bool SingleObjVert(int X,int Y,bool AddIt);
        bool CircleObjVert(int dx,int dy,int X,int Y,bool AddIt);
        bool QuadObjVert(int dx,int dy,int X,int Y,bool AddIt);
        bool FenceObjVert(int dx,int dy,int X,int Y,Shape *daSh,bool AddIt);

        // Object Face

        bool CircleObjFace(int dx,int dy,int X,int Y,bool Crossing,bool AddIt);
        bool QuadObjFace(int dx,int dy,int X,int Y,bool Crossing,bool AddIt);
        bool FenceObjFace(int dx,int dy,int X,int Y,Shape *daSh,bool Crossing,bool AddIt);
*/
		bool SelectObject(int dx,int dy,int X,int Y,Shape *daSh,bool AddIt,bool Crossing,int TypeSel,int WholeSelect);

        // Light
/*
        bool SingleLight(int X,int Y,bool AddIt);
        bool CircleLight(int dx,int dy,int X,int Y,bool AddIt,bool Crossing);
        bool QuadLight(int dx,int dy,int X,int Y,bool AddIt,bool Crossing);
        bool FenceLight(int dx,int dy,int X,int Y,Shape *daSh,bool AddIt,bool Crossing);

        bool SingleLightVert(int X,int Y,bool AddIt);
        bool CircleLightVert(int dx,int dy,int X,int Y,bool AddIt,bool Crossing);
        bool QuadLightVert(int dx,int dy,int X,int Y,bool AddIt,bool Crossing);
        bool FenceLightVert(int dx,int dy,int X,int Y,Shape *daSh,bool AddIt,bool Crossing);
*/
		bool SelectLight(int dx,int dy,int X,int Y,Shape *daSh,bool AddIt,bool Crossing,int TypeSel,int WholeSelect);

		// patch
		bool SinglePatchVert(int X,int Y,bool AddIt);
		bool SinglePatchEdge(int X,int Y,bool AddIt);
		bool CirclePatchVert(int dx,int dy,int X,int Y,bool AddIt);
		bool QuadPatchVert(int dx,int dy,int X,int Y,bool AddIt);
		bool FencePatchVert(int dx,int dy,int X,int Y,Shape *daSh,bool AddIt);

        // Skeletton

        bool SingleSkel(int X,int Y,bool AddIt);
        bool CircleSkel(int dx,int dy,int X,int Y,bool AddIt,bool Crossing);
        bool QuadSkel(int dx,int dy,int X,int Y,bool AddIt,bool Crossing);
        bool FenceSkel(int dx,int dy,int X,int Y,Shape *daSh,bool AddIt,bool Crossing);
        bool RecCircleBone(Bone *daBone,int dx,int dy,int X,int Y,bool AddIt,bool Crossing,double Length);
        bool RecQuadBone(Bone *daBone,int dx,int dy,int X,int Y,bool AddIt,bool Crossing);
        bool RecFenceBone(Bone *daBone,int dx,int dy,int X,int Y,Shape *daSh,bool AddIt,bool Crossing);

        void RecIsAllSkelInCircle(Bone *daBone,int dx,int dy,int X,int Y,double Length,bool *AllIn,bool *OneIn);
        void IsAllSkelInCircle(Skeletton *daSkel,int dx,int dy,int X,int Y,double Length,bool *AllIn,bool *OneIn);

        void RecIsAllSkelInQuad(Bone *daBone,int dx,int dy,int X,int Y,bool *AllIn,bool *OneIn);
        void IsAllSkelInQuad(Skeletton *daSkel,int dx,int dy,int X,int Y,bool *AllIn,bool *OneIn);

        void IsAllSkelInFence(Bone *daBone,int dx,int dy,int X,int Y,Shape *daSh,bool *AllIn,bool *OneIn);
        void IsAllSkelInFence(Skeletton *daSkel,int dx,int dy,int X,int Y,Shape *daSh,bool *AllIn,bool *OneIn);

        // Bone

        bool SingleBone(int X,int Y,bool AddIt);
        bool CircleBone(int dx,int dy,int X,int Y,bool AddIt,bool Crossing);
        bool QuadBone(int dx,int dy,int X,int Y,bool AddIt,bool Crossing);
        bool FenceBone(int dx,int dy,int X,int Y,Shape *daSh,bool AddIt,bool Crossing);
        bool RecSingleSkel(Bone *daBone,bool AddIt);
        bool RecCircleSkel(Bone *daBone,int dx,int dy,int X,int Y,bool AddIt,bool Crossing);
        bool RecQuadSkel(Bone *daBone,int dx,int dy,int X,int Y,bool AddIt,bool Crossing);
        bool RecFenceSkel(Bone *daBone,int dx,int dy,int X,int Y,Shape *daSh,bool AddIt,bool Crossing);
/*
        // Emitter
        bool SingleEmit(int X,int Y,bool AddIt);
        bool CircleEmit(int dx,int dy,int X,int Y,bool AddIt);
        bool QuadEmit(int dx,int dy,int X,int Y,bool AddIt);
        bool FenceEmit(int dx,int dy,int X,int Y,Shape *daSh,bool AddIt);
*/
        // Shape

        bool SingleShape(int X,int Y,bool AddIt);
        bool CircleShape(int dx,int dy,int X,int Y,bool AddIt,bool Crossing);
        bool QuadShape(int dx,int dy,int X,int Y,bool AddIt,bool Crossing);
        bool FenceShape(int dx,int dy,int X,int Y,Shape *daSh,bool AddIt,bool Crossing);

        // Shape Seg

        bool SingleShapeSeg(int X,int Y,bool AddIt);
        bool CircleShapeSeg(int dx,int dy,int X,int Y,bool AddIt,bool Crossing);
        bool QuadShapeSeg(int dx,int dy,int X,int Y,bool AddIt,bool Crossing);
        bool FenceShapeSeg(int dx,int dy,int X,int Y,Shape *daSh,bool AddIt,bool Crossing);

        // Shape Vert

        bool SingleShapeVert(int X,int Y,bool AddIt);
        bool CircleShapeVert(int dx,int dy,int X,int Y,bool AddIt);
        bool QuadShapeVert(int dx,int dy,int X,int Y,bool AddIt);
        bool FenceShapeVert(int dx,int dy,int X,int Y,Shape *daSh,bool AddIt);

        // -- Get single -------------------------------------------------------

        Camera *GetCamera(int X,int Y);
        Camera *GetCamera(int X,int Y,bool IsTarget);
        Object *GetObject(int X,int Y);
        Shape *GetShape(int X,int Y);
//        Emitter *GetEmitter(int X,int Y);
        Bone *RecurseGetBone(int X,int Y,Vertex Node,Bone *daBone,MYPOINT daclick);
//        Bone *GetSkeletton(int X,int Y);
        Bone *GetBone(int X,int Y);
        CLight *GetLight(int X,int Y);
        Vertex *GetShapeVert(int X,int Y);
        Vertex *GetObjVert(int X,int Y,int &VertInd);
		Skeletton *GetSkeletton(int X,int Y);


		void GetShapeSeg(Shape **DstShp,Segment **DstSeg,Segment *Else,int X,int Y);
		void GetShapeVert(Shape **DstShp,Segment **DstSeg,Segment *Else,int X,int Y);
		void GetStartShapeVert(Shape **DstShp,Segment **DstSeg,Segment *Else,int X,int Y);
		void GetEndShapeVert(Shape **DstShp,Segment **DstSeg,Segment *Else,int X,int Y);
        // -- Unselect ---------------------------------------------------------



        void UnSelectCamera(bool daSelVal);
        void UnSelectObject(bool daSelVal);
        //void UnSelectEmitter(bool daSelVal);
        void UnSelectShape(bool daSelVal);
        void RecUnSelectSkeletton(Bone *daBone,bool daSelVal);
        void UnSelectSkeletton(bool daSelVal);
        void UnSelectLights(bool daSelVal);
        void UnSelectAll(bool daSelVal);
		void UnSelectPatch(bool daSelVal);


		//char co[10000];
};
//---------------------------------------------------------------------------
#endif
