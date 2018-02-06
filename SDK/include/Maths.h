
//---------------------------------------------------------------------------
#ifndef MathsH
#define MathsH
//#include "Kapsul3D.h"
/*
#include "Option.h"
#include "Vertex.h"
#include <math.h>
#include <stdlib.h>
/*
class Math
{

    public:
    //bool ComprisIn(double binf, double bsupp,double val);
*/
/*
#ifdef __PLUGINS__
	extern "C" {
#endif
	*/
    extern __declspec( dllexport ) double Interpolate(MYPOINT pt1,MYPOINT pt2,double x);
    extern __declspec( dllexport ) void QSortSeg(SegSort *list,int nb2SegList);
    extern __declspec( dllexport ) int IsInSort(const void * elt1, const void * elt2);
    extern __declspec( dllexport ) double SegDistance(MYPOINT sdeb,MYPOINT sfin,MYPOINT spt);
    extern __declspec( dllexport ) Vertex ng3d(Vertex v1,Vertex v2);
    extern __declspec( dllexport ) double Pythagore(double a,double b);
    extern __declspec( dllexport ) double Pythagore3D(Vertex a,Vertex b);
    extern __declspec( dllexport ) void QSortDouble(double *daTab,int nb2double);
    extern __declspec( dllexport ) double ng(double x1,double y1,double x2,double y2);
    //Option KapsulOpt;

//    String LigneCDE;
    extern __declspec( dllexport ) float RandomNum();
    extern __declspec( dllexport ) void RotationToDirection(float pitch,float yaw,Vertex *direction);
    extern __declspec( dllexport ) double Normalize(Vertex &vector);
    extern __declspec( dllexport ) bool InvertMatrix(double src[16], double inverse[16]);
    extern __declspec( dllexport ) void Identity(double m[16]);
    extern __declspec( dllexport ) double DotProduct(Vertex *v1, Vertex *v2);
    extern __declspec( dllexport ) Vertex CrossProduct(Vertex *v1, Vertex *v2);
    extern __declspec( dllexport ) uint log2(uint val);
/*
#ifdef __PLUGINS__
	}
#endif
	*/
/*
    Math();
    ~Math();
};
*/

//---------------------------------------------------------------------------
#endif
