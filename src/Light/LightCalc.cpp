// CLightCalc.cpp: implementation of the CLightCalc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LightCalc.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define EPSILON 0.000001
/*
#define CROSS(dest,v1,v2) \
          dest[0]=v1[1]*v2[2]-v1[2]*v2[1]; \
          dest[1]=v1[2]*v2[0]-v1[0]*v2[2]; \
          dest[2]=v1[0]*v2[1]-v1[1]*v2[0];
#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])
#define SUB(dest,v1,v2) \
          dest[0]=v1[0]-v2[0]; \
          dest[1]=v1[1]-v2[1]; \
          dest[2]=v1[2]-v2[2]; 
*/
#define CROSS(dest,v1,v2) \
          dest.x=v1.y*v2.z-v1.z*v2.y; \
          dest.y=v1.z*v2.x-v1.x*v2.z; \
          dest.z=v1.x*v2.y-v1.y*v2.x;
#define DOT(v1,v2) (v1.x*v2.x+v1.y*v2.y+v1.z*v2.z)
#define SUB(dest,v1,v2) \
          dest.x=v1.x-v2.x; \
          dest.y=v1.y-v2.y; \
          dest.z=v1.z-v2.z; 

#define dot(u,v)   ((u).x * (v).x + (u).y * (v).y + (u).z * (v).z)
#define norm(v)    sqrt(dot(v,v))  // norm = length of vector
#define d(u,v)     norm(u-v)       


extern "C" CKScene *GScene;
extern CKPolygon *CurrentPolygon;
//CalcIntersectionPoint(fRayStart, fRayEnd, fIntersectionOut, m_Normal, m_Vertices[0]);

#define TEST_CULL
void CalcIntersectionPoint(Vertex & fRayStart, Vertex & fRayEnd, Vertex & fIntersectionOut,
									  Vertex & fNormal, Vertex & fPlaneVertex)
{
	// Calculates the point on which the ray would intersect with the passed triangle's plane.

	//         (a - r) * u
	// t = r + ----------- * (s - r)
	//         (s - r) * u

	/*
	// This variation maybe useful if you have a precalculated fD

	float fD = DOT(fNormal, fPlaneVertex);
	float fRay[3] = { fRayEnd[x] - fRayStart[x], fRayEnd[y] - fRayStart[y], fRayEnd[z] - fRayStart[z] };
	float fT = - (DOT(fNormal, fRayStart) - fD) / DOT(fNormal, fRay);

	fIntersectionOut[x] = fRayStart[x] + (fRay[x] * fT);
	fIntersectionOut[y] = fRayStart[y] + (fRay[y] * fT);
	fIntersectionOut[z] = fRayStart[z] + (fRay[z] * fT);
	*/

	Vertex fRay = Vertex( fRayEnd.x - fRayStart.x, fRayEnd.y - fRayStart.y, fRayEnd.z - fRayStart.z );
	Vertex fDiff = Vertex( fPlaneVertex.x - fRayStart.x, 
		fPlaneVertex.y - fRayStart.y, fPlaneVertex.z - fRayStart.z );
	float fT = DOT(fNormal, fDiff) / DOT(fNormal, fRay);

	fIntersectionOut.x = fRayStart.x + (fRay.x * fT);
	fIntersectionOut.y = fRayStart.y + (fRay.y * fT);
	fIntersectionOut.z = fRayStart.z + (fRay.z * fT);

}

static Vertex edge1, edge2, tvec, pvec, qvec;
static double det,inv_det;



CLightCalc::CLightCalc()
{
    
}

CLightCalc::~CLightCalc()
{

}

double CLightCalc::dist_Point_to_Segment( Vertex &P, Vertex &S0,Vertex &S1,int &type,double &d)
{
    Vertex v = S1 - S0;
    Vertex w = P - S0;
    d=0;

    double c1 = dot(w,v);
    if ( c1 <= 0 )
    {
        type=0;
        return d(P, S0); // before
    }

    double c2 = dot(v,v);
    if ( c2 <= c1 )
    {
        type=1;
        return d(P, S1); // after
    }

    double b = c1 / c2;
    Vertex Pb = S0;
    Pb.x+= v.x*b;
    Pb.y+= v.y*b;
    Pb.z+= v.z*b;
    type=2;
    d=b;
    return d(P, Pb); //inside
}

void CLightCalc::AddLight(float factor,BYTE &R,BYTE &G,BYTE &B,CLight *dalight)
{
    int tmp;

    tmp=R+dalight->r*factor;
    if (tmp>255) R=255;
        else R=tmp;
    
    tmp=G+dalight->g*factor;
    if (tmp>255) G=255;
        else G=tmp;

    tmp=B+dalight->b*factor;
    if (tmp>255) B=255;
        else B=tmp;
}

inline void CLightCalc::ComputeLumelSpot(Vertex &lumel, CLight *dalight, BYTE &R, BYTE &G, BYTE &B)
{
    int type;
    double d;
    float fact;
    double darad,darad2;

    double dist=dist_Point_to_Segment(lumel,dalight->Source,dalight->Target,type,d);

    // inside cone

    if (type==2)
    {
        darad=(d*dalight->Length)*dalight->tanRad1;
        darad2=(d*dalight->Length)*dalight->tanRad2;

        if (dist<=darad2)
        {
            AddLight(1,R,G,B,dalight);
            return;
        }
        if ((dist>=darad2)&&(dist<=darad))
        {
            if ((darad2==darad)||(dist==darad2))
                fact=1;
            else
                fact=1-(dist-darad2)/(darad-darad2);

            AddLight(fact,R,G,B,dalight);
            return;
        }
    }
    else
    {
        // inside globe

        if (type==1)
        {
            double darad=dalight->Length*dalight->tanRad1;
            double darad2=dalight->Length*dalight->tanRad2;
            if (dist<=darad2)
            {
                AddLight(1,R,G,B,dalight);
                return ;
            }
            if ((dist>=darad2)&&(dist<=darad))
            {
                if ((darad2==darad)||(dist==darad2))
                    fact=1;
                else
                    fact=1-(dist-darad2)/(darad-darad2);

                AddLight(fact,R,G,B,dalight);
                return;
            }

        }
    }
}

inline void CLightCalc::ComputeLumelOmni(Vertex &lumel, CLight *dalight, BYTE &R, BYTE &G, BYTE &B)
{
    float fact;

    double v1,v2,v3;
    v1=(dalight->Source.x-lumel.x);
    v1*=v1;
    v2=(dalight->Source.y-lumel.y);
    v2*=v2;
    v3=(dalight->Source.z-lumel.z);
    v3*=v3;

    double dist=sqrt(v1+v2+v3);


    if (dist<=dalight->Radius2)
    {
        AddLight(1,R,G,B,dalight);
        return;
    }
    if ((dist>=dalight->Radius2)&&(dist<=dalight->Radius))
    {
        if ((dalight->Radius2==dalight->Radius)||(dist==dalight->Radius2))
            fact=1;
        else
            fact=1-(dist-dalight->Radius2)/(dalight->Radius-dalight->Radius2);

        AddLight(fact,R,G,B,dalight);
        return;
    }
}

void CLightCalc::CalcLightmap(Vertex &Origin, Vertex &scx, Vertex &scy, BYTE *lpBits,int sx,int sy, CLight *dalight)
{
    int i,j,k,l;
    Vertex orig2,orig3;
    bool Intersect;
	CKMesh *daMesh;

    
    orig3=Origin;
    
    
    ro=dalight->Source;
    
    if (dalight->Type==0)
    {
        // omni
        for (i=0;i<sy;i++)
        {
            orig2=orig3;
            
            for (j=0;j<sx;j++)
            {
                
                rd=(dalight->Source-orig2);

                //radial=sqrt(rd.x*rd.x+rd.y*rd.y+rd.z*rd.z);
                double v1=(dalight->Source.x-orig2.x);
                v1*=v1;
                double v2=(dalight->Source.y-orig2.y);
                v2*=v2;
                double v3=(dalight->Source.z-orig2.z);
                v3*=v3;
            
                double dist=sqrt(v1+v2+v3);

                if (dist<=dalight->Radius)
                {
                
                    Intersect=false;
					for (daMesh=GScene->FirstMesh;(daMesh!=NULL);daMesh=daMesh->Next)
					{
						for (k=0;(k<daMesh->nb2poly);k++)
						{
							for (l=0;(l<daMesh->pl[k].nb2vert-2);l++)
							{
								if (&daMesh->pl[k]!=CurrentPolygon)
								{
									if (CurrentPolygon->GetDist(dalight->Source)<0)
										goto finished;

									
									if (intersect_triangle(ro,rd,daMesh->pv[daMesh->pl[k].nbvert[0]],
										daMesh->pv[daMesh->pl[k].nbvert[l+1]],
										daMesh->pv[daMesh->pl[k].nbvert[l+2]],&t,&u,&v))

									{
										//DMPOutputString(" %5.2f \r\n",t);

										if ((t>-0.99)&&(t<0))
										{
											
											Intersect=true;
											l=(daMesh->pl[k].nb2vert-2);
											k=daMesh->nb2poly;
											goto finished;
										}

									}
									
								}
							}
						}
					}
					

                    if (!Intersect)
                        ComputeLumelOmni(orig2,dalight,lpBits[(i*sx*3)+(j*3)],lpBits[(i*sx*3)+(j*3)+1],lpBits[(i*sx*3)+(j*3)+2]);
finished:;
                }
                
                orig2+=scx;
            }
            orig3+=scy;
        }
    }
    else
    {
        // spot
        
        for (i=0;i<sy;i++)
        {
            orig2=orig3;
            
            for (j=0;j<sx;j++)
            {
                rd=(dalight->Source-orig2);
                
                Intersect=false;
				for (daMesh=GScene->FirstMesh;(daMesh!=NULL)&&(!Intersect);daMesh=daMesh->Next)
				{
					for (k=0;(k<daMesh->nb2poly)&&(!Intersect);k++)
					{
						for (l=0;(l<daMesh->pl[k].nb2vert-2)&&(!Intersect);l++)
						{
							if (intersect_triangle(ro,rd,daMesh->pv[daMesh->pl[k].nbvert[0]],
								daMesh->pv[daMesh->pl[k].nbvert[l+1]],
								daMesh->pv[daMesh->pl[k].nbvert[l+2]],&t,&u,&v))
							{
								if ((t<=0)&&(t>-1))
								{
									Intersect=true;
									l=(daMesh->pl[k].nb2vert-2);
									k=daMesh->nb2poly;
									//daMesh=NULL;
									break;
								}
							}
						}
					}
				}
                
                if (!Intersect)
                    ComputeLumelSpot(orig2,dalight,lpBits[(i*sx*3)+(j*3)],lpBits[(i*sx*3)+(j*3)+1],lpBits[(i*sx*3)+(j*3)+2]);
                
                orig2+=scx;
            }
            orig3+=scy;
        }
    }
}
