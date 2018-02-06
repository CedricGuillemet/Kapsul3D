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

#ifndef _CAMERA_H
#define _CAMERA_H

#include "Kapsul3D.h"

class __declspec( dllexport ) Camera
{


public:
    
    Vertex Source;
    Vertex Dest;
    int ResoX,ResoY;
    double Length;
    double Fov;

    char *Name;
    bool Selected;

    bool    SrcSelected,DstSelected;

    float angle_a, angle_b; 
    float old_angle_a, old_angle_b; 
    float m_speed;

	int OldMx,OldMy;
	Vertex newpos;
	POINT p;
	unsigned int Unique;

    // matrix

    Matrix *projection,*modelview,*InverseModel,*InverseProj;

    // linked list

    Camera *Next,*Prev;

public:
	void LookAt(void);
    virtual ~Camera();
    Camera(Camera *daPrev,Camera *daNext);
	Camera(void);
    //void Compute(void);
    void SetSource(Vertex daSource);
    void SetDest(Vertex daDest);
    double GetLength(void);
	void SetCamera();
	void SetMouse(int mx, int my, int WinWidth, int WinHeight);
	void Move();
	void UndoTranslate(void);
	void SetMousePos(void);
	void BeginMove(void);
	void EndDraw(void);
	Vertex GetMaxOf();
	Vertex GetMinOf();
    void Run(double Percent);
    void operator =(Camera *cmpt);
	void IsCopyOf(Camera *cmpt);


};

#endif
