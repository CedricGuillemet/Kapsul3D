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

#ifndef _MATRIX_H
#define _MATRIX_H

#include "Kapsul3D.h"

class __declspec( dllexport ) Matrix
{

public:
    double mat[16];

	inline Matrix();
	inline ~Matrix();
	inline bool InvertMatrix(Matrix *Dest);
	inline void Identity();
	inline void MultVectorByMatrix(Vertex *v,Vertex *result);
	inline void MultMatrix(Matrix *b,Matrix *product);
	inline void GetFrom(unsigned int pname);
	inline void GLMult(void);
	inline void MultVectorByMatrix2(Vertex *v,Vertex *result);
    inline void Translate(Vertex tr);
    inline void operator =(Matrix *cmpt);
    inline Matrix(double m1,double m2,double m3,double m4,double m5,double m6,double m7,double m8,
               double m9,double m10,double m11,double m12,double m13,double m14,double m15,double m16);

	inline void RotateX(float angle);
	inline void RotateY(float angle);
	inline void RotateZ(float angle);
	inline void gluLookAt( double eyex, double eyey, double eyez,
                         double centerx, double centery, double centerz,
                         double upx, double upy, double upz );
    inline Vertex operator*(Vertex vec);

};


inline Matrix::Matrix()
{
}

inline Matrix::Matrix(double m1,double m2,double m3,double m4,double m5,double m6,double m7,double m8,
               double m9,double m10,double m11,double m12,double m13,double m14,double m15,double m16)
{
	//mat=new double [16];
    mat[0]=m1;
    mat[1]=m2;
    mat[2]=m3;
    mat[3]=m4;
    mat[4]=m5;
    mat[5]=m6;
    mat[6]=m7;
    mat[7]=m8;
    mat[8]=m9;
    mat[9]=m10;
    mat[10]=m11;
    mat[11]=m12;
    mat[12]=m13;
    mat[13]=m14;
    mat[14]=m15;
    mat[15]=m16;

}

inline Matrix::~Matrix()
{
}


inline Vertex Matrix::operator*(Vertex vec)
{
   return Vertex(
    vec.vx * mat[0] + vec.vy * mat[4] + vec.vz * mat[8] + mat[12],
    vec.vx * mat[1] + vec.vy * mat[5] + vec.vz * mat[9] + mat[13],
    vec.vx * mat[2] + vec.vy * mat[6] + vec.vz * mat[10] + mat[14]);
}

inline Vertex operator*(Vertex vec, Matrix &mat)
{
   return Vertex(mat * vec);
}


inline bool Matrix::InvertMatrix(Matrix *Dest)
{
    double t;
    int i, j, k, swap;
    double tmp[4][4];

    //Identity(Dest);
	Dest->Identity();

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            tmp[i][j] = mat[i*4+j];
        }
    }

    for (i = 0; i < 4; i++) {
        /* look for largest element in column. */
        swap = i;
        for (j = i + 1; j < 4; j++) {
            if (fabs(tmp[j][i]) > fabs(tmp[i][i])) {
                swap = j;
            }
        }

        if (swap != i) {
            /* swap rows. */
            for (k = 0; k < 4; k++) {
                t = tmp[i][k];
                tmp[i][k] = tmp[swap][k];
                tmp[swap][k] = t;

                t = Dest->mat[i*4+k];
                Dest->mat[i*4+k] = Dest->mat[swap*4+k];
                Dest->mat[swap*4+k] = t;
            }
        }

        if (tmp[i][i] == 0) {
        /* no non-zero pivot.  the matrix is singular, which
           shouldn't happen.  This means the user gave us a bad
            matrix. */
            return false;
        }

        t = tmp[i][i];
        for (k = 0; k < 4; k++) {
            tmp[i][k] /= t;
            Dest->mat[i*4+k] /= t;
        }
        for (j = 0; j < 4; j++) {
            if (j != i) {
                t = tmp[j][i];
                for (k = 0; k < 4; k++) {
                    tmp[j][k] -= tmp[i][k]*t;
                    Dest->mat[j*4+k] -= Dest->mat[i*4+k]*t;
                }
            }
        }
    }
    return true;
}



inline void Matrix::Identity()
{
    mat[0+4*0] = 1; mat[0+4*1] = 0; mat[0+4*2] = 0; mat[0+4*3] = 0;
    mat[1+4*0] = 0; mat[1+4*1] = 1; mat[1+4*2] = 0; mat[1+4*3] = 0;
    mat[2+4*0] = 0; mat[2+4*1] = 0; mat[2+4*2] = 1; mat[2+4*3] = 0;
    mat[3+4*0] = 0; mat[3+4*1] = 0; mat[3+4*2] = 0; mat[3+4*3] = 1;
}

inline void Matrix::MultVectorByMatrix(Vertex *v,Vertex *result)
{
	result->vx = (mat[0] * v->vx) +
			   (mat[4] * v->vy) +	
			   (mat[8] * v->vz)  +mat[12];
	result->vy = (mat[1] * v->vx) +
			   (mat[5] * v->vy) +	
			   (mat[9] * v->vz)  +mat[13];
	result->vz = (mat[2] * v->vx) +
			   (mat[6] * v->vy) +	
			   (mat[10] * v->vz)  +mat[14];
}

inline void Matrix::MultVectorByMatrix2(Vertex *v,Vertex *result)
{
	result->vx = (mat[0] * v->vx) +
			   (mat[1] * v->vy) +	
			   (mat[2] * v->vz)  +mat[3];
	result->vy = (mat[4] * v->vx) +
			   (mat[5] * v->vy) +	
			   (mat[6] * v->vz)  +mat[7];
	result->vz = (mat[8] * v->vx) +
			   (mat[9] * v->vy) +	
			   (mat[10] * v->vz)  +mat[11];
}

inline void Matrix::MultMatrix(Matrix *b,Matrix *product)
{
   int i;

#define A(row,col)  b->mat[(col<<2)+row]
#define B(row,col)  product->mat[(col<<2)+row]
#define P(row,col)  mat[(col<<2)+row]

   for (i = 0; i < 4; i++) {
      double ai0=A(i,0),  ai1=A(i,1),  ai2=A(i,2),  ai3=A(i,3);
      P(i,0) = ai0 * B(0,0) + ai1 * B(1,0) + ai2 * B(2,0) + ai3 * B(3,0);
      P(i,1) = ai0 * B(0,1) + ai1 * B(1,1) + ai2 * B(2,1) + ai3 * B(3,1);
      P(i,2) = ai0 * B(0,2) + ai1 * B(1,2) + ai2 * B(2,2) + ai3 * B(3,2);
      P(i,3) = ai0 * B(0,3) + ai1 * B(1,3) + ai2 * B(2,3) + ai3 * B(3,3);
   }

#undef A
#undef B
#undef P
}

inline void Matrix::GetFrom(unsigned int pname)
{
	glGetDoublev(pname,mat);
}

inline void Matrix::GLMult(void)
{
    glMultMatrixd(mat);
}

inline void Matrix::Translate(Vertex tr)
{
    mat[0+4*0] = 1; mat[0+4*1] = 0; mat[0+4*2] = 0; mat[0+4*3]+=tr.vx;
    mat[1+4*0] = 0; mat[1+4*1] = 1; mat[1+4*2] = 0; mat[1+4*3]+=tr.vy;
    mat[2+4*0] = 0; mat[2+4*1] = 0; mat[2+4*2] = 1; mat[2+4*3]+=tr.vz;
    mat[3+4*0] = 0; mat[3+4*1] = 0; mat[3+4*2] = 0; mat[3+4*3] = 1;

}

inline void Matrix::operator =(Matrix *cmpt)
{
    memcpy(mat,cmpt->mat,sizeof(double)*16);
}

inline void Matrix::RotateX(float angle)
{
   float c = (float)cos(angle);
   float s = (float)sin(angle);

   mat[5] = c;   
   mat[6] = s;
   mat[9] = -s;  
   mat[10] = c;   
}

inline void Matrix::RotateY(float angle)
{
   float c = (float)cos(angle);
   float s = (float)sin(angle);

   mat[0] = c;   
   mat[2] = -s;
   mat[8] = s;  
   mat[10] = c;
}

inline void Matrix::RotateZ(float angle)
{
   float c = (float)cos(angle);
   float s = (float)sin(angle);

   mat[0] = c;   
   mat[1] = s;
   mat[4] = -s;  
   mat[5] = c;
}


inline void Matrix::gluLookAt( double eyex, double eyey, double eyez,
                         double centerx, double centery, double centerz,
                         double upx, double upy, double upz )
{
   //double m[16];
   double x[3], y[3], z[3];
   double mag;

   /* Make rotation matrix */

   /* Z vector */
   z[0] = eyex - centerx;
   z[1] = eyey - centery;
   z[2] = eyez - centerz;
   mag = sqrt( z[0]*z[0] + z[1]*z[1] + z[2]*z[2] );
   if (mag) {  /* mpichler, 19950515 */
      z[0] /= mag;
      z[1] /= mag;
      z[2] /= mag;
   }

   /* Y vector */
   y[0] = upx;
   y[1] = upy;
   y[2] = upz;

   /* X vector = Y cross Z */
   x[0] =  y[1]*z[2] - y[2]*z[1];
   x[1] = -y[0]*z[2] + y[2]*z[0];
   x[2] =  y[0]*z[1] - y[1]*z[0];

   /* Recompute Y = Z cross X */
   y[0] =  z[1]*x[2] - z[2]*x[1];
   y[1] = -z[0]*x[2] + z[2]*x[0];
   y[2] =  z[0]*x[1] - z[1]*x[0];

   /* mpichler, 19950515 */
   /* cross product gives area of parallelogram, which is < 1.0 for
    * non-perpendicular unit-length vectors; so normalize x, y here
    */

   mag = sqrt( x[0]*x[0] + x[1]*x[1] + x[2]*x[2] );
   if (mag) {
      x[0] /= mag;
      x[1] /= mag;
      x[2] /= mag;
   }

   mag = sqrt( y[0]*y[0] + y[1]*y[1] + y[2]*y[2] );
   if (mag) {
      y[0] /= mag;
      y[1] /= mag;
      y[2] /= mag;
   }

#define M(row,col)  mat[col*4+row]
   M(0,0) = x[0];  M(0,1) = x[1];  M(0,2) = x[2];  M(0,3) = 0.0;
   M(1,0) = y[0];  M(1,1) = y[1];  M(1,2) = y[2];  M(1,3) = 0.0;
   M(2,0) = z[0];  M(2,1) = z[1];  M(2,2) = z[2];  M(2,3) = 0.0;
   M(3,0) = 0.0;   M(3,1) = 0.0;   M(3,2) = 0.0;   M(3,3) = 1.0;
#undef M
}
#endif