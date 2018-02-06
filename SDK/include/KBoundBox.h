// KBoundBox.h: interface for the CKBoundBox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KBOUNDBOX_H__BFBE3871_A6FB_4822_A1C2_41A206605495__INCLUDED_)
#define AFX_KBOUNDBOX_H__BFBE3871_A6FB_4822_A1C2_41A206605495__INCLUDED_
#include "Vertex.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*
bool Mgc::TestIntersection (const Segment3& rkSegment, const Box3& rkBox)
{
    Real fAWdU[3], fADdU[3], fAWxDdU[3], fRhs;
    Vector3 kSDir = 0.5f*rkSegment.Direction();
    Vector3 kSCen = rkSegment.Origin() + kSDir;

    Vector3 kDiff = kSCen - rkBox.Center();

    fAWdU[0] = Math::FAbs(kSDir.Dot(rkBox.Axis(0)));
    fADdU[0] = Math::FAbs(kDiff.Dot(rkBox.Axis(0)));
    fRhs = rkBox.Extent(0) + fAWdU[0];
    if ( fADdU[0] > fRhs )
        return false;

    fAWdU[1] = Math::FAbs(kSDir.Dot(rkBox.Axis(1)));
    fADdU[1] = Math::FAbs(kDiff.Dot(rkBox.Axis(1)));
    fRhs = rkBox.Extent(1) + fAWdU[1];
    if ( fADdU[1] > fRhs )
        return false;

    fAWdU[2] = Math::FAbs(kSDir.Dot(rkBox.Axis(2)));
    fADdU[2] = Math::FAbs(kDiff.Dot(rkBox.Axis(2)));
    fRhs = rkBox.Extent(2) + fAWdU[2];
    if ( fADdU[2] > fRhs )
        return false;

    Vector3 kWxD = kSDir.Cross(kDiff);

    fAWxDdU[0] = Math::FAbs(kWxD.Dot(rkBox.Axis(0)));
    fRhs = rkBox.Extent(1)*fAWdU[2] + rkBox.Extent(2)*fAWdU[1];
    if ( fAWxDdU[0] > fRhs )
        return false;

    fAWxDdU[1] = Math::FAbs(kWxD.Dot(rkBox.Axis(1)));
    fRhs = rkBox.Extent(0)*fAWdU[2] + rkBox.Extent(2)*fAWdU[0];
    if ( fAWxDdU[1] > fRhs )
        return false;

    fAWxDdU[2] = Math::FAbs(kWxD.Dot(rkBox.Axis(2)));
    fRhs = rkBox.Extent(0)*fAWdU[1] + rkBox.Extent(1)*fAWdU[0];
    if ( fAWxDdU[2] > fRhs )
        return false;

    return true;
}
//----------------------------------------------------------------------------
*/
/*
#define rDOT(v1,v2) (v1.vx*v2.vx+v1.vy*v2.vy+v1.vz*v2.vz)

bool Mgc::TestIntersection (/*const Ray3& rkRay, const Box3& rkBox Vertex rOrig,Vertex rDir)
{
    double fWdU[3], fAWdU[3], fDdU[3], fADdU[3], fAWxDdU[3], fRhs;

    Vertex kDiff = rOrig - rkBox.Center();

    fWdU[0] = rDOT(rOrig,Vertex(1,0,0));
    fAWdU[0] = fabsbs(fWdU[0]);
    fDdU[0] = rDOT(kDiff,Vertex(1,0,0));
    fADdU[0] = fabs(fDdU[0]);
    if ( fADdU[0] > rkBox.Extent(0) && fDdU[0]*fWdU[0] >= 0.0f )
        return false;

    fWdU[1] = rkRay.Direction().Dot(rkBox.Axis(1));
    fAWdU[1] = Math::FAbs(fWdU[1]);
    fDdU[1] = kDiff.Dot(rkBox.Axis(1));
    fADdU[1] = Math::FAbs(fDdU[1]);
    if ( fADdU[1] > rkBox.Extent(1) && fDdU[1]*fWdU[1] >= 0.0f )
        return false;

    fWdU[2] = rkRay.Direction().Dot(rkBox.Axis(2));
    fAWdU[2] = Math::FAbs(fWdU[2]);
    fDdU[2] = kDiff.Dot(rkBox.Axis(2));
    fADdU[2] = Math::FAbs(fDdU[2]);
    if ( fADdU[2] > rkBox.Extent(2) && fDdU[2]*fWdU[2] >= 0.0f )
        return false;

    Vector3 kWxD = rkRay.Direction().Cross(kDiff);

    fAWxDdU[0] = Math::FAbs(kWxD.Dot(rkBox.Axis(0)));
    fRhs = rkBox.Extent(1)*fAWdU[2] + rkBox.Extent(2)*fAWdU[1];
    if ( fAWxDdU[0] > fRhs )
        return false;

    fAWxDdU[1] = Math::FAbs(kWxD.Dot(rkBox.Axis(1)));
    fRhs = rkBox.Extent(0)*fAWdU[2] + rkBox.Extent(2)*fAWdU[0];
    if ( fAWxDdU[1] > fRhs )
        return false;

    fAWxDdU[2] = Math::FAbs(kWxD.Dot(rkBox.Axis(2)));
    fRhs = rkBox.Extent(0)*fAWdU[1] + rkBox.Extent(1)*fAWdU[0];
    if ( fAWxDdU[2] > fRhs )
        return false;

    return true;
}
*/
/*
//----------------------------------------------------------------------------
bool Mgc::TestIntersection (const Line3& rkLine, const Box3& rkBox)
{
    Real fAWdU[3], fAWxDdU[3], fRhs;

    Vector3 kDiff = rkLine.Origin() - rkBox.Center();
    Vector3 kWxD = rkLine.Direction().Cross(kDiff);

    fAWdU[1] = Math::FAbs(rkLine.Direction().Dot(rkBox.Axis(1)));
    fAWdU[2] = Math::FAbs(rkLine.Direction().Dot(rkBox.Axis(2)));
    fAWxDdU[0] = Math::FAbs(kWxD.Dot(rkBox.Axis(0)));
    fRhs = rkBox.Extent(1)*fAWdU[2] + rkBox.Extent(2)*fAWdU[1];
    if ( fAWxDdU[0] > fRhs )
        return false;

    fAWdU[0] = Math::FAbs(rkLine.Direction().Dot(rkBox.Axis(0)));
    fAWxDdU[1] = Math::FAbs(kWxD.Dot(rkBox.Axis(1)));
    fRhs = rkBox.Extent(0)*fAWdU[2] + rkBox.Extent(2)*fAWdU[0];
    if ( fAWxDdU[1] > fRhs )
        return false;

    fAWxDdU[2] = Math::FAbs(kWxD.Dot(rkBox.Axis(2)));
    fRhs = rkBox.Extent(0)*fAWdU[1] + rkBox.Extent(1)*fAWdU[0];
    if ( fAWxDdU[2] > fRhs )
        return false;

    return true;
}
*/

typedef float F32;

struct Point
{
    F32 x,y,z;
};

struct Box
{
    Point min,max;
};


class __declspec(dllexport) CKBoundBox  
{
public:
    Vertex ptb;
	Vertex pta;
    Vertex len;
public:
	inline CKBoundBox(Vertex _a,Vertex _b,Vertex _c)
    {
        pta=_a;
        ptb=_b;
        len=_c;
    }

	inline CKBoundBox(Vertex _a,Vertex _b)
    {
        pta=_a;
        ptb=_b;
    }

	inline CKBoundBox(void)
    {
    }

	inline virtual ~CKBoundBox()
    {
    }

    inline bool Intersect(const Vertex &start, const Vertex &end, double *time)
    {
        float st,et,fst = 0,fet = 1;
        float const *bmin = &pta.vx;
        float const *bmax = &ptb.vx;
        float const *si = &start.vx;
        float const *ei = &end.vx;

        // x
        if (*si < *ei) 
        {
            if (*si > *bmax || *ei < *bmin)
                return false;
            F32 di = *ei - *si;
            st = (*si < *bmin)? (*bmin - *si) / di: 0;
            et = (*ei > *bmax)? (*bmax - *si) / di: 1;
        }
        else 
        {
            if (*ei > *bmax || *si < *bmin)
                return false;
            F32 di = *ei - *si;
            st = (*si > *bmax)? (*bmax - *si) / di: 0;
            et = (*ei < *bmin)? (*bmin - *si) / di: 1;
        }
        
        if (st > fst) fst = st;
        if (et < fet) fet = et;
        if (fet < fst)
            return false;

        // y
        bmin = &pta.vy;
        bmax = &ptb.vy;
        si = &start.vy;
        ei = &end.vy;

        if (*si < *ei) 
        {
            if (*si > *bmax || *ei < *bmin)
                return false;
            F32 di = *ei - *si;
            st = (*si < *bmin)? (*bmin - *si) / di: 0;
            et = (*ei > *bmax)? (*bmax - *si) / di: 1;
        }
        else 
        {
            if (*ei > *bmax || *si < *bmin)
                return false;
            F32 di = *ei - *si;
            st = (*si > *bmax)? (*bmax - *si) / di: 0;
            et = (*ei < *bmin)? (*bmin - *si) / di: 1;
        }
        
        if (st > fst) fst = st;
        if (et < fet) fet = et;
        if (fet < fst)
            return false;

        // z
        bmin = &pta.vz;
        bmax = &ptb.vz;
        si = &start.vz;
        ei = &end.vz;

        if (*si < *ei) 
        {
            if (*si > *bmax || *ei < *bmin)
                return false;
            F32 di = *ei - *si;
            st = (*si < *bmin)? (*bmin - *si) / di: 0;
            et = (*ei > *bmax)? (*bmax - *si) / di: 1;
        }
        else 
        {
            if (*ei > *bmax || *si < *bmin)
                return false;
            F32 di = *ei - *si;
            st = (*si > *bmax)? (*bmax - *si) / di: 0;
            et = (*ei < *bmin)? (*bmin - *si) / di: 1;
        }
        
        if (st > fst) fst = st;
        if (et < fet) fet = et;
        if (fet < fst)
            return false;

        *time = fst;
        return true;
    }

    inline bool Intersect(const Vertex &Center,const double &Radius)
    {
        if ( sqrt( (pta.vx-Center.vx)*(pta.vx-Center.vx) +
            (pta.vy-Center.vy)*(pta.vy-Center.vy) +
            (pta.vz-Center.vz)*(pta.vz-Center.vz) ) <=Radius) return true;

        if ( sqrt( (ptb.vx-Center.vx)*(ptb.vx-Center.vx) +
            (pta.vy-Center.vy)*(pta.vy-Center.vy) +
            (pta.vz-Center.vz)*(pta.vz-Center.vz) ) <=Radius) return true;

        if ( sqrt( (pta.vx-Center.vx)*(pta.vx-Center.vx) +
            (ptb.vy-Center.vy)*(ptb.vy-Center.vy) +
            (pta.vz-Center.vz)*(pta.vz-Center.vz) ) <=Radius) return true;

        if ( sqrt( (ptb.vx-Center.vx)*(ptb.vx-Center.vx) +
            (ptb.vy-Center.vy)*(ptb.vy-Center.vy) +
            (pta.vz-Center.vz)*(pta.vz-Center.vz) ) <=Radius) return true;

        if ( sqrt( (pta.vx-Center.vx)*(pta.vx-Center.vx) +
            (pta.vy-Center.vy)*(pta.vy-Center.vy) +
            (ptb.vz-Center.vz)*(ptb.vz-Center.vz) ) <=Radius) return true;

        if ( sqrt( (ptb.vx-Center.vx)*(ptb.vx-Center.vx) +
            (pta.vy-Center.vy)*(pta.vy-Center.vy) +
            (ptb.vz-Center.vz)*(ptb.vz-Center.vz) ) <=Radius) return true;

        if ( sqrt( (pta.vx-Center.vx)*(pta.vx-Center.vx) +
            (ptb.vy-Center.vy)*(ptb.vy-Center.vy) +
            (ptb.vz-Center.vz)*(ptb.vz-Center.vz) ) <=Radius) return true;

        if ( sqrt( (ptb.vx-Center.vx)*(ptb.vx-Center.vx) +
            (ptb.vy-Center.vy)*(ptb.vy-Center.vy) +
            (ptb.vz-Center.vz)*(ptb.vz-Center.vz) ) <=Radius) return true;

        return false;
    }

};

#endif // !defined(AFX_KBOUNDBOX_H__BFBE3871_A6FB_4822_A1C2_41A206605495__INCLUDED_)
