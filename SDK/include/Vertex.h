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
class __declspec( dllexport ) Vertex
{
// Members
public:
    float vx,vy,vz;
    /*int Index;,BoolStat;*/
    bool Selected;
public:
    inline virtual ~Vertex();
    inline double GetDistance(Vertex pt);
    inline bool GetSelected() const;
    inline void SetSelected(bool selected);
    inline Vertex();
    inline Vertex(double davx,double davy,double davz);
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
		return (float)sqrt(vx*vx+vy*vy+vz*vz);
	}

	float Mag2(){
		return vx*vx+vy*vy+vz*vz;
	}

	Vertex Norm(){
		float mag=Mag();
		float rmag=(mag>0.0f)?(1.0f/mag):0.0f;
		return Vertex(vx*rmag, vy*rmag, vz*rmag);
	}
*/
    inline void SetNextPower2(void);
    inline int NextPow2(int Number);

};

inline void Vertex::SetNextPower2(void)
{
    if (vx<0) vx=-NextPow2((int)-vx);
        else vx=NextPow2((int)vx);
    if (vy<0) vy=-NextPow2((int)-vy);
        else vy=NextPow2((int)vy);
    if (vz<0) vz=-NextPow2((int)-vz);
        else vz=NextPow2((int)vz);
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
	return a.vx*b.vx+a.vy*b.vy+a.vz*b.vz;
}
/*
inline Vertex operator+(Vertex &a, Vertex &b){
	return Vertex(a.vx+b.vx, a.vy+b.vy, a.vz+b.vz);
}

inline Vertex operator-(Vertex &a, Vertex &b){
	return Vertex(a.vx-b.vx, a.vy-b.vy, a.vz-b.vz);
}

inline Vertex operator*(Vertex &a, float s){
	return Vertex(a.vx*s, a.vy*s, a.vz*s);
}
*/
/*
inline Vertex operator%(Vertex &a, Vertex &b){
	return Vertex(
		a.vy*b.vz-a.vz*b.vy,
		a.vz*b.vx-a.vx*b.vz,
		a.vx*b.vy-a.vy*b.vx);
}
*/


inline Vertex::~Vertex()
{

}

inline Vertex::Vertex()
{
    //BoolStat=0;
    vx=0;
    vy=0;
    vz=0;
    Selected=false;
}

inline Vertex::Vertex(double davx,double davy,double davz)
{
    //BoolStat=0;
    vx=davx;
    vy=davy;
    vz=davz;
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
    return ((cmpt.vx==vx)&&(cmpt.vy==vy)&&(cmpt.vz==vz));
}


inline bool Vertex::operator !=(Vertex cmpt)
{
    return ((cmpt.vx!=vx)||(cmpt.vy!=vy)||(cmpt.vz!=vz));
}

inline Vertex Vertex::operator + (Vertex cmpt)
{
    Vertex tmp;

    tmp.vx=vx+cmpt.vx;
    tmp.vy=vy+cmpt.vy;
    tmp.vz=vz+cmpt.vz;

    return tmp;
}

inline Vertex Vertex::operator -(Vertex cmpt)
{
    Vertex tmp;

    tmp.vx=vx-cmpt.vx;
    tmp.vy=vy-cmpt.vy;
    tmp.vz=vz-cmpt.vz;

    return tmp;

}

inline Vertex Vertex::operator *(int cmpt)
{
    Vertex tmp;

    tmp.vx=vx*cmpt;
    tmp.vy=vy*cmpt;
    tmp.vz=vz*cmpt;

    return tmp;
}

inline Vertex Vertex::operator *(double cmpt)
{
    Vertex tmp;

    tmp.vx=vx*cmpt;
    tmp.vy=vy*cmpt;
    tmp.vz=vz*cmpt;

    return tmp;
}

inline Vertex Vertex::operator *(Vertex cmpt)
{
    Vertex tmp;

    tmp.vx=vx*cmpt.vx;
    tmp.vy=vy*cmpt.vy;
    tmp.vz=vz*cmpt.vz;

    return tmp;
}


inline void Vertex::operator +=(Vertex cmpt)
{
    vx+=cmpt.vx;
    vy+=cmpt.vy;
    vz+=cmpt.vz;
}


inline void Vertex::operator *=(Vertex cmpt)
{
    vx*=cmpt.vx;
    vy*=cmpt.vy;
    vz*=cmpt.vz;
}

inline void Vertex::operator /=(int cmpt)
{
    vx/=cmpt;
    vy/=cmpt;
    vz/=cmpt;
}

inline void Vertex::operator -=(Vertex cmpt)
{
    vx-=cmpt.vx;
    vy-=cmpt.vy;
    vz-=cmpt.vz;
}

inline Vertex Vertex::operator /(double cmpt)
{
    Vertex value;
    value.vx=vx/cmpt;
    value.vy=vy/cmpt;
    value.vz=vz/cmpt;
    return value;
}

/*
inline void Vertex::operator =(double cmpt)
{
    vx=cmpt;
    vy=cmpt;
    vz=cmpt;
}
*/
inline void Vertex::operator =(Vertex cmpt)
{
    vx=cmpt.vx;
    vy=cmpt.vy;
    vz=cmpt.vz;

}
/*
inline void Vertex::operator *=(double cmpt)
{
    vx*=cmpt;
    vy*=cmpt;
    vz*=cmpt;
}
*/

// -- Rotation du vertex Axe arbitraire ----------------------------------------

inline Vertex Vertex::RotVect(Vertex Vect,double ng)
{
    Vertex value;
    double nx2,ny2,nz2;
    double m1,m2,m3,m4,m5,m6,m7,m8,m9;

    nx2=(Vect.vx*Vect.vx);
    ny2=(Vect.vy*Vect.vy);
    nz2=(Vect.vz*Vect.vz);

    m1=(nx2+((1-nx2)*cos(ng)));
    m2=((Vect.vx*Vect.vy*(1-cos(ng)))-(Vect.vz*sin(ng)));
    m3=((Vect.vx*Vect.vz*(1-cos(ng)))+(Vect.vy*sin(ng)));
    m4=((Vect.vx*Vect.vy*(1-cos(ng)))+(Vect.vz*sin(ng)));
    m5=(ny2+((1-ny2)*cos(ng)));
    m6=((Vect.vy*Vect.vz*(1-cos(ng)))-(Vect.vx*sin(ng)));
    m7=((Vect.vx*Vect.vz*(1-cos(ng)))-(Vect.vy*sin(ng)));
    m8=((Vect.vy*Vect.vz*(1-cos(ng)))+(Vect.vx*sin(ng)));
    m9=(nz2+((1-nz2)*cos(ng)));

    value.vx=vx*m1+vy*m2+vz*m3;
    value.vy=vx*m4+vy*m5+vz*m6;
    value.vz=vx*m7+vy*m8+vz*m9;

    return value;
}

inline bool Vertex::IsEquivalentTo(Vertex cmpt)
{

    return ( (fabs(cmpt.vx-vx)<0.0000001) && (fabs(cmpt.vy-vy)<0.0000001) && (fabs(cmpt.vz-vz)<0.0000001) );

}

inline void Vertex::GetMinOf(Vertex vert)
{
    if (vx>vert.vx) vx=vert.vx;
    if (vy>vert.vy) vy=vert.vy;
    if (vz>vert.vz) vz=vert.vz;
}

inline void Vertex::GetMaxOf(Vertex vert)
{
    if (vx<vert.vx) vx=vert.vx;
    if (vy<vert.vy) vy=vert.vy;
    if (vz<vert.vz) vz=vert.vz;
}

inline void Vertex::Snap(Vertex SnapVal)
{
	int temp;

	temp=int(vx/SnapVal.vx);
	temp*=int(SnapVal.vx);
	vx=temp;

	temp=int(vy/SnapVal.vy);
	temp*=int(SnapVal.vy);
	vy=temp;

	temp=int(vz/SnapVal.vz);
	temp*=int(SnapVal.vz);
	vz=temp;


}

inline double Vertex::Normalize(void)
{
    double length;

    length = sqrt(vx*vx+vy*vy+vz*vz);
    vx /= length;
    vy /= length;
    vz /= length;

    return length;
}

inline double Vertex::Dot(Vertex &pVec)
{
    return vx * pVec.vx + vy * pVec.vy + vz * pVec.vz;
}

inline void Vertex::Cross(Vertex &p, Vertex &q)
{
	vx = p.vy * q.vz - p.vz * q.vy;
	vy = p.vz * q.vx - p.vx * q.vz;
	vz = p.vx * q.vy - p.vy * q.vx;
}


class __declspec( dllexport ) UVCoords
{
public:
	inline UVCoords(){};
	inline ~UVCoords(){};
    float u,v;
};

class __declspec( dllexport ) GLColor
{
public:
	inline GLColor() {};
	inline ~GLColor() {};
    unsigned char r,g,b;
};
#pragma pack(4)

#endif
