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

#ifndef _VERTEX_H
#define _VERTEX_H

#include "Kapsul3D.h"

#pragma pack(1)
typedef struct KAPSUL_DESC Vertex
{
// Members
public:
    float x,y,z;
    /*int Index;,BoolStat;*/
    bool Selected;
public:
    inline double GetDistance(Vertex pt);
    inline bool GetSelected() const;
    inline void SetSelected(bool selected);
    inline Vertex();
    inline Vertex(double dax,double day,double daz);
    inline bool operator ==(Vertex cmpt);

    inline bool operator !=(Vertex cmpt);
    inline Vertex operator +(Vertex cmpt);
    inline Vertex operator -(Vertex cmpt);
    inline Vertex operator *(int cmpt);
	inline Vertex operator *(double cmpt);
    inline Vertex operator *(Vertex cmpt);
    inline void operator -=(Vertex cmpt);
    inline void operator +=(Vertex cmpt);
    inline void operator *=(Vertex cmpt);
    //inline void operator *=(double cmpt);
    inline void operator /=(int cmpt);
    inline Vertex operator /(double cmpt);
    //inline void operator =(double cmpt);

    inline void operator =(Vertex cmpt);
    inline Vertex RotVect(Vertex Vect,double ng);
    inline bool IsEquivalentTo(Vertex cmpt);

	inline void Snap(Vertex SnapVal);

    inline void GetMinOf(Vertex vert);
    inline void GetMaxOf(Vertex vert);
	inline double Normalize(void);
    inline double Dot(Vertex &pVec);
    inline void Cross(Vertex &p, Vertex &q);
/*
    float Mag(){
		return (float)sqrt(x*x+y*y+z*z);
	}

	float Mag2(){
		return x*x+y*y+z*z;
	}

	Vertex Norm(){
		float mag=Mag();
		float rmag=(mag>0.0f)?(1.0f/mag):0.0f;
		return Vertex(x*rmag, y*rmag, z*rmag);
	}
*/
    inline void SetNextPower2(void);
    inline int NextPow2(int Number);

} Vertex;

inline void Vertex::SetNextPower2(void)
{
    if (x<0) x=-NextPow2((int)-x);
        else x=NextPow2((int)x);
    if (y<0) y=-NextPow2((int)-y);
        else y=NextPow2((int)y);
    if (z<0) z=-NextPow2((int)-z);
        else z=NextPow2((int)z);
}

inline int Vertex::NextPow2(int Number)
{
    if (Number==0) return Number;

    unsigned int RetVal = 1;
    __asm    
    {
        mov eax, Number
        sub eax, 1
        xor ecx, ecx
        bsr ecx, eax
        inc ecx
        shl RetVal, cl
    }
    return(RetVal);
}


/*
inline float operator*(Vertex &a, Vertex &b){
	return a.x*b.x+a.y*b.y+a.z*b.z;
}
/*
inline Vertex operator+(Vertex &a, Vertex &b){
	return Vertex(a.x+b.x, a.y+b.y, a.z+b.z);
}

inline Vertex operator-(Vertex &a, Vertex &b){
	return Vertex(a.x-b.x, a.y-b.y, a.z-b.z);
}

inline Vertex operator*(Vertex &a, float s){
	return Vertex(a.x*s, a.y*s, a.z*s);
}
*/
/*
inline Vertex operator%(Vertex &a, Vertex &b){
	return Vertex(
		a.y*b.z-a.z*b.y,
		a.z*b.x-a.x*b.z,
		a.x*b.y-a.y*b.x);
}
*/


inline Vertex::Vertex()
{
    //BoolStat=0;
    x=0;
    y=0;
    z=0;
    Selected=false;
}

inline Vertex::Vertex(double dax,double day,double daz)
{
    //BoolStat=0;
    x=dax;
    y=day;
    z=daz;
    Selected=false;

}

inline double Vertex::GetDistance(Vertex pt)
{
    double value;

    value=0;

    return value;
}

inline bool Vertex::GetSelected() const
{
    return Selected;
}

inline void Vertex::SetSelected(bool selected)
{
    Selected = selected;
}

inline bool Vertex::operator ==(Vertex cmpt)
{
    return ((cmpt.x==x)&&(cmpt.y==y)&&(cmpt.z==z));
}


inline bool Vertex::operator !=(Vertex cmpt)
{
    return ((cmpt.x!=x)||(cmpt.y!=y)||(cmpt.z!=z));
}

inline Vertex Vertex::operator + (Vertex cmpt)
{
    Vertex tmp;

    tmp.x=x+cmpt.x;
    tmp.y=y+cmpt.y;
    tmp.z=z+cmpt.z;

    return tmp;
}

inline Vertex Vertex::operator -(Vertex cmpt)
{
    Vertex tmp;

    tmp.x=x-cmpt.x;
    tmp.y=y-cmpt.y;
    tmp.z=z-cmpt.z;

    return tmp;

}

inline Vertex Vertex::operator *(int cmpt)
{
    Vertex tmp;

    tmp.x=x*cmpt;
    tmp.y=y*cmpt;
    tmp.z=z*cmpt;

    return tmp;
}

inline Vertex Vertex::operator *(double cmpt)
{
    Vertex tmp;

    tmp.x=x*cmpt;
    tmp.y=y*cmpt;
    tmp.z=z*cmpt;

    return tmp;
}

inline Vertex Vertex::operator *(Vertex cmpt)
{
    Vertex tmp;

    tmp.x=x*cmpt.x;
    tmp.y=y*cmpt.y;
    tmp.z=z*cmpt.z;

    return tmp;
}


inline void Vertex::operator +=(Vertex cmpt)
{
    x+=cmpt.x;
    y+=cmpt.y;
    z+=cmpt.z;
}


inline void Vertex::operator *=(Vertex cmpt)
{
    x*=cmpt.x;
    y*=cmpt.y;
    z*=cmpt.z;
}

inline void Vertex::operator /=(int cmpt)
{
    x/=cmpt;
    y/=cmpt;
    z/=cmpt;
}

inline void Vertex::operator -=(Vertex cmpt)
{
    x-=cmpt.x;
    y-=cmpt.y;
    z-=cmpt.z;
}

inline Vertex Vertex::operator /(double cmpt)
{
    Vertex value;
    value.x=x/cmpt;
    value.y=y/cmpt;
    value.z=z/cmpt;
    return value;
}

/*
inline void Vertex::operator =(double cmpt)
{
    x=cmpt;
    y=cmpt;
    z=cmpt;
}
*/
inline void Vertex::operator =(Vertex cmpt)
{
    x=cmpt.x;
    y=cmpt.y;
    z=cmpt.z;

}
/*
inline void Vertex::operator *=(double cmpt)
{
    x*=cmpt;
    y*=cmpt;
    z*=cmpt;
}
*/

// -- Rotation du vertex Axe arbitraire ----------------------------------------

inline Vertex Vertex::RotVect(Vertex Vect,double ng)
{
    Vertex value;
    double nx2,ny2,nz2;
    double m1,m2,m3,m4,m5,m6,m7,m8,m9;

    nx2=(Vect.x*Vect.x);
    ny2=(Vect.y*Vect.y);
    nz2=(Vect.z*Vect.z);

    m1=(nx2+((1-nx2)*cos(ng)));
    m2=((Vect.x*Vect.y*(1-cos(ng)))-(Vect.z*sin(ng)));
    m3=((Vect.x*Vect.z*(1-cos(ng)))+(Vect.y*sin(ng)));
    m4=((Vect.x*Vect.y*(1-cos(ng)))+(Vect.z*sin(ng)));
    m5=(ny2+((1-ny2)*cos(ng)));
    m6=((Vect.y*Vect.z*(1-cos(ng)))-(Vect.x*sin(ng)));
    m7=((Vect.x*Vect.z*(1-cos(ng)))-(Vect.y*sin(ng)));
    m8=((Vect.y*Vect.z*(1-cos(ng)))+(Vect.x*sin(ng)));
    m9=(nz2+((1-nz2)*cos(ng)));

    value.x=x*m1+y*m2+z*m3;
    value.y=x*m4+y*m5+z*m6;
    value.z=x*m7+y*m8+z*m9;

    return value;
}

inline bool Vertex::IsEquivalentTo(Vertex cmpt)
{

    return ( (fabs(cmpt.x-x)<0.0000001) && (fabs(cmpt.y-y)<0.0000001) && (fabs(cmpt.z-z)<0.0000001) );

}

inline void Vertex::GetMinOf(Vertex vert)
{
    if (x>vert.x) x=vert.x;
    if (y>vert.y) y=vert.y;
    if (z>vert.z) z=vert.z;
}

inline void Vertex::GetMaxOf(Vertex vert)
{
    if (x<vert.x) x=vert.x;
    if (y<vert.y) y=vert.y;
    if (z<vert.z) z=vert.z;
}

inline void Vertex::Snap(Vertex SnapVal)
{
	double temp;
	float v1;

	// X
	if (x>0)
	{
		temp=floor(x/SnapVal.x)*SnapVal.x;
		v1=fmod(x,SnapVal.x);
		if (v1<4)
			x=temp;
		else
		//if (v1>4)
			x=temp+SnapVal.x;

	}
	else
	{
		temp=ceil(x/SnapVal.x)*SnapVal.x;
		v1=fmod(x,SnapVal.x);
		if (v1<-4)
			x=temp-SnapVal.x;
		else
		//if (v1>-4)
			x=temp;

	}
	// Y

	if (y>0)
	{
		temp=floor(y/SnapVal.y)*SnapVal.y;
		v1=fmod(y,SnapVal.y);
		if (v1<4)
			y=temp;
		else
		//if (v1>4)
			y=temp+SnapVal.y;

	}
	else
	{
		temp=ceil(y/SnapVal.y)*SnapVal.y;
		v1=fmod(y,SnapVal.y);
		if (v1<-4)
			y=temp-SnapVal.y;
		else
		//if (v1>-4)
			y=temp;

	}

	// Z
	if (z>0)
	{
		temp=floor(z/SnapVal.z)*SnapVal.z;
		v1=fmod(z,SnapVal.z);
		if (v1<4)
			z=temp;
		else
		//if (v1>4)
			z=temp+SnapVal.z;

	}
	else
	{
		temp=ceil(z/SnapVal.z)*SnapVal.z;
		v1=fmod(z,SnapVal.z);
		if (v1<-4)
			z=temp-SnapVal.z;
		else
		//if (v1>-4)
			z=temp;

	}
}

inline double Vertex::Normalize(void)
{
    double length;

    length = sqrt(x*x+y*y+z*z);
	if (length)
	{
		x /= length;
		y /= length;
		z /= length;
	}

    return length;
}

inline double Vertex::Dot(Vertex &pVec)
{
    return x * pVec.x + y * pVec.y + z * pVec.z;
}

inline void Vertex::Cross(Vertex &p, Vertex &q)
{
	x = p.y * q.z - p.z * q.y;
	y = p.z * q.x - p.x * q.z;
	z = p.x * q.y - p.y * q.x;
}


class KAPSUL_DESC UVCoords
{
public:
	inline UVCoords(){};
	inline ~UVCoords(){};
    float u,v;
};

class KAPSUL_DESC UVCoordsEdit
{
public:
	inline UVCoordsEdit(){};
	inline ~UVCoordsEdit(){};
    float u,v;
	CKMesh *daMesh;
	int PuvInd;
	bool Selected;
};

class KAPSUL_DESC GLColor
{
public:
	inline GLColor() {};
	inline ~GLColor() {};
    unsigned char r,g,b;
};
#pragma pack(4)

#endif
