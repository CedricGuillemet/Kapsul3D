/*
   Copyright (C) 2001 Nate Miller nathanm@uci.edu

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

   See gpl.txt for more information regarding the GNU General Public License.
*/
#include "matrix.h"

/*
=============
Multiply
=============
   this = lhs * rhs

   lhs or rhs can be equal to this since all results are stored in a temporary
matrix.
*/
void matrix_t::Multiply(const matrix_t &lhs, const matrix_t &rhs)
{
   matrix_t t;

   t.m[0][0] = rhs.m[0][0] * lhs.m[0][0] + rhs.m[0][1] * lhs.m[1][0] + 
               rhs.m[0][2] * lhs.m[2][0] + rhs.m[0][3] * lhs.m[3][0];
   t.m[1][0] = rhs.m[1][0] * lhs.m[0][0] + rhs.m[1][1] * lhs.m[1][0] + 
               rhs.m[1][2] * lhs.m[2][0] + rhs.m[1][3] * lhs.m[3][0];
   t.m[2][0] = rhs.m[2][0] * lhs.m[0][0] + rhs.m[2][1] * lhs.m[1][0] + 
               rhs.m[2][2] * lhs.m[2][0] + rhs.m[2][3] * lhs.m[3][0];
   t.m[3][0] = rhs.m[3][0] * lhs.m[0][0] + rhs.m[3][1] * lhs.m[1][0] + 
               rhs.m[3][2] * lhs.m[2][0] + rhs.m[3][3] * lhs.m[3][0];
   t.m[0][1] = rhs.m[0][0] * lhs.m[0][1] + rhs.m[0][1] * lhs.m[1][1] + 
               rhs.m[0][2] * lhs.m[2][1] + rhs.m[0][3] * lhs.m[3][1];
   t.m[1][1] = rhs.m[1][0] * lhs.m[0][1] + rhs.m[1][1] * lhs.m[1][1] + 
               rhs.m[1][2] * lhs.m[2][1] + rhs.m[1][3] * lhs.m[3][1];
   t.m[2][1] = rhs.m[2][0] * lhs.m[0][1] + rhs.m[2][1] * lhs.m[1][1] + 
               rhs.m[2][2] * lhs.m[2][1] + rhs.m[2][3] * lhs.m[3][1];
   t.m[3][1] = rhs.m[3][0] * lhs.m[0][1] + rhs.m[3][1] * lhs.m[1][1] + 
               rhs.m[3][2] * lhs.m[2][1] + rhs.m[3][3] * lhs.m[3][1];
   t.m[0][2] = rhs.m[0][0] * lhs.m[0][2] + rhs.m[0][1] * lhs.m[1][2] + 
               rhs.m[0][2] * lhs.m[2][2] + rhs.m[0][3] * lhs.m[3][2];
   t.m[1][2] = rhs.m[1][0] * lhs.m[0][2] + rhs.m[1][1] * lhs.m[1][2] + 
               rhs.m[1][2] * lhs.m[2][2] + rhs.m[1][3] * lhs.m[3][2];
   t.m[2][2] = rhs.m[2][0] * lhs.m[0][2] + rhs.m[2][1] * lhs.m[1][2] + 
               rhs.m[2][2] * lhs.m[2][2] + rhs.m[2][3] * lhs.m[3][2];
   t.m[3][2] = rhs.m[3][0] * lhs.m[0][2] + rhs.m[3][1] * lhs.m[1][2] + 
               rhs.m[3][2] * lhs.m[2][2] + rhs.m[3][3] * lhs.m[3][2];
   t.m[0][3] = rhs.m[0][0] * lhs.m[0][3] + rhs.m[0][1] * lhs.m[1][3] + 
               rhs.m[0][2] * lhs.m[2][3] + rhs.m[0][3] * lhs.m[3][3];
   t.m[1][3] = rhs.m[1][0] * lhs.m[0][3] + rhs.m[1][1] * lhs.m[1][3] + 
               rhs.m[1][2] * lhs.m[2][3] + rhs.m[1][3] * lhs.m[3][3];
   t.m[2][3] = rhs.m[2][0] * lhs.m[0][3] + rhs.m[2][1] * lhs.m[1][3] + 
               rhs.m[2][2] * lhs.m[2][3] + rhs.m[2][3] * lhs.m[3][3];
   t.m[3][3] = rhs.m[3][0] * lhs.m[0][3] + rhs.m[3][1] * lhs.m[1][3] +
               rhs.m[3][2] * lhs.m[2][3] + rhs.m[3][3] * lhs.m[3][3];
   Set(t);
}

/*
=============
Multiply
=============
   Multiply a vector through a matrix.
   
   dest can be equal to source since a temp vector is used.
*/
void matrix_t::Multiply(const vec3_t &src, vec3_t &dest)
{
   vec3_t t;
   
   t[0] = m[0][0] * src[0] + m[1][0] * src[1] + m[2][0] * src[2] + m[3][0];
   t[1] = m[0][1] * src[0] + m[1][1] * src[1] + m[2][1] * src[2] + m[3][1];
   t[2] = m[0][2] * src[0] + m[1][2] * src[1] + m[2][2] * src[2] + m[3][2];

   dest.Set(t);
}

/*
=============
Rotate
=============
   Rotate this matrix a la OpenGL glRotate().  The formulas for this code were
taken from the OpenGL man pages.  
   
   The effect of this call is : this = this * rotation.
*/
void matrix_t::Rotate(float angle, const vec3_t &vec)
{
   matrix_t ret;
   float c = mLibCos(angle);
   float s = mLibSin(angle);
   float mc = 1.0f - c;
   float x = vec[0];
   float y = vec[1];
   float z = vec[2];

   ret.m[0][0] = (x * x * mc) + c;
   ret.m[0][1] = (y * x * mc) + (z * s);
   ret.m[0][2] = (x * z * mc) - (y * s);

   ret.m[1][0] = (x * y * mc) - (z * s);
   ret.m[1][1] = (y * y * mc) + c;
   ret.m[1][2] = (y * z * mc) + (x * s);

   ret.m[2][0] = (x * z * mc) + (y * s);
   ret.m[2][1] = (y * z * mc) - (x * s);
   ret.m[2][2] = (z * z * mc) + c;

   Multiply(*this, ret);
}

/*
=============
Translate
=============
   Translate the matrix.
   
   The effect of this call is : this = this * translation.
*/
void matrix_t::Translate(const vec3_t &vec)
{
   matrix_t t;

   t.m[3][0] = vec[0];
   t.m[3][1] = vec[1];
   t.m[3][2] = vec[2];
   
   Multiply(*this, t);
}

/*
=============
Translate
=============
   Translate the matrix.
   
   The effect of this call is : this = this * translation.
*/
void matrix_t::Translate(float x, float y, float z)
{
   matrix_t t;

   t.m[3][0] = x;
   t.m[3][1] = y;
   t.m[3][2] = z;
   
   Multiply(*this, t);
}