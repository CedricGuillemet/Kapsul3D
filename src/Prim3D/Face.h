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

#ifndef _FACE_H
#define _FACE_H

#include "Kapsul3D.h"

class Face
{

private:


protected:

public:
    int *nbvert;
    bool Selected;
    int Tex[4][3];
public:
    virtual ~Face();
    bool GetSelected() const;
    void SetSelected(bool selected);
    Face();
    Face::Face(int v1,int v2,int v3);
    void operator =(Face cmpt);
};


#endif
