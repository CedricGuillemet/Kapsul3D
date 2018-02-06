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

#ifndef ShapeH
#define ShapeH

#include "Kapsul3D.h"

class __declspec( dllexport ) Shape
{
    private:
        // style
        //int     Style;
        void    DoAdd();

    public:
        bool    Selected;
	    char	*Name;

        int     Count;
		unsigned int Unique;

        // liked list
        Segment *NextSegment,*FirstSegment;
        Shape   *Next,*Prev;

        // Path deform
    	Object *Obj;
		//unsigned int Unique;


    public:

    Shape(Shape *daPrev=NULL,Shape *daNext=NULL);
    ~Shape();
    // ajout

    void    AddSegment(Vertex *daDot);
    void    AddSegment(double X,double Y,double Z);
    void    AddSegment(Vertex daDot);    
    // Set
    void    SetSegment(Vertex *daDot);
    void    SetSegment(double X,double Y,double Z);

    void    SetStyle(int daStyle);
    void    IsQuad(Vertex Corner1, Vertex Corner2,Vertex Corner3,Vertex Corner4);
    void    IsCircle(int nbDots,Vertex *Dots);
    bool    IsInside(Vertex Dot);
    void    DelAll(void);
    void    DelSeg(Segment *Seg);
    void    Close(void);
    Vertex  GetMinOf(void);
    Vertex  GetMaxOf(void);
	bool GenerateObject(Shape *daShp);
    double GetLength(void);
    double GetLength(int nb);

	// insertion
	Segment * InsertSegment(Segment *Seg,Vertex daDot);
	Segment * InsertSegment(Segment *Seg,double X,double Y,double Z);

	Segment * InsertAtFirst(Vertex daDot);
	Segment * InsertAtFirst(double X,double Y,double Z);

	// to surface
    /*
	int Delaunay(int N, double* x, double* y, int& numTriangles, TriangleList*& triangle);
	bool ToSurface(Desk *dk,OGLView *View);
    */
	bool IsVertInShape(Vertex daVert,OGLView *View);

    Vertex GetSpline(double percent);
    int GetCount(void);
	void IsCopyOf(Shape *cmpt);
};
//---------------------------------------------------------------------------
#endif
 