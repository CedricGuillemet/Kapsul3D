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
#include <stdio.h>
#include "quat.h"

/*
=============
Reset
=============
   Reset the quat to the multiplcation identity.
*/
void quat_t::Reset(void)
{
	w = 1.0f;
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

/*
=============
Normalize
=============
   Normalize the quat.
*/
void quat_t::Normalize(void)
{
	float dot = (x * x) + (y * y) + (z * z) + (w * w);

   if (dot == 0.0f)
      return;

   float scale = 1.0f / (float) sqrt(dot);

   x *= scale;
   y *= scale;
   z *= scale;
   w *= scale;
}

/*
=============
Multiply
=============
   Multiply two quats.
   
   this = lhs * rhs
*/
void quat_t::Multiply(const quat_t &lhs, const quat_t &rhs)
{
   float tx, ty, tz, tw;

   tw = (lhs.w * rhs.w) - (lhs.x * rhs.x) - (lhs.y * rhs.y) - (lhs.z * rhs.z);
   tx = (lhs.w * rhs.x) + (lhs.x * rhs.w) + (lhs.y * rhs.z) - (lhs.z * rhs.y);
   ty = (lhs.w * rhs.y) + (lhs.y * rhs.w) + (lhs.z * rhs.x) - (lhs.x * rhs.z);
   tz = (lhs.w * rhs.z) + (lhs.z * rhs.w) + (lhs.x * rhs.y) - (lhs.y * rhs.x);
      
   x = tx;
   y = ty;
   z = tz;
   w = tw;
}

/*
=============
ToMatrix
=============
   Convert the quat to a matrix. Gamasutra.
*/
void quat_t::ToMatrix(matrix_t &mat)
{
   float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

   x2 = x + x;
   y2 = y + y; 
   z2 = z + z;

   xx = x * x2;
   xy = x * y2;
   xz = x * z2;
   yy = y * y2;
   yz = y * z2;
   zz = z * z2;
   wx = w * x2;
   wy = w * y2;
   wz = w * z2;


   mat[0][0] = 1.0f - (yy + zz);
   mat[0][1] = xy - wz;
   mat[0][2] = xz + wy;
   mat[0][3] = 0.0f;
   mat[1][0] = xy + wz;
   mat[1][1] = 1.0f - (xx + zz);
   mat[1][2] = yz - wx;
   mat[1][3] = 0.0f;
   mat[2][0] = xz - wy;
   mat[2][1] = yz + wx;
   mat[2][2] = 1.0f - (xx + yy);
   mat[2][3] = 0.0f;
   mat[3][0] = 0;
   mat[3][1] = 0;
   mat[3][2] = 0;
   mat[3][3] = 1;
}

/*
=============
MatrixToQuat
=============
   Convert the passed matrix to a quat.  Gamasutra.
*/
void quat_t::MatrixToQuat(matrix_t &mat)
{
   float tr, s, q[4];
   int i, j, k;
   int nxt[3] = {1, 2, 0};

   tr = mat[0][0] + mat[1][1] + mat[2][2];

   if (tr > 0.0)
   {
      s = (float) sqrt(tr + 1.0f);
      w = s / 2.0f;
      s = 0.5f / s;
      x = (mat[2][1] - mat[1][2]) * s;
      y = (mat[0][2] - mat[2][0]) * s;
      z = (mat[1][0] - mat[0][1]) * s;
   }
   else
   {		
      i = 0;
      
      if (mat[1][1] > mat[0][0])
         i = 1;
   
      if (mat[2][2] > mat[i][i])
         i = 2;
   
      j = nxt[i];
      k = nxt[j];

      s = (float) sqrt((mat[i][i] - (mat[j][j] + mat[k][k])) + 1.0f);
      
      q[i] = s * 0.5f;
            
      if (s != 0.0f)
         s = 0.5f / s;

      q[3] = (mat[k][j] - mat[j][k]) * s;
      q[j] = (mat[j][i] + mat[i][j]) * s;
      q[k] = (mat[k][i] + mat[i][k]) * s;

	   x = q[0];
	   y = q[1];
	   z = q[2];
	   w = q[3];
   }
}

/*
=============
AxisAngleToQuat
=============
   Convert an axis and a rotation angle to a quat.
*/
void quat_t::AxisAngleToQuat(const vec3_t &axis, float angle)
{
   float sin_a = -mLibSin(angle / 2.0f);
   vec3_t t(axis);

   t.Normalize();

   x = t[0] * sin_a;
   y = t[1] * sin_a;
   z = t[2] * sin_a;
   w = mLibCos(angle / 2.0f);
}

/*
=============
EulerToQuat
=============
   Convert 3 euler angles to a quat.
*/
void quat_t::EulerToQuat(float x, float y, float z)
{
   quat_t qx, qy, qz, temp;

   qx.x = mLibSin(x / 2.0f);
   qx.w = mLibCos(x / 2.0f);

   qy.y = mLibSin(y / 2.0f);
   qy.w = mLibCos(y / 2.0f);

   qz.z = mLibSin(z / 2.0f);
   qz.w = mLibCos(z / 2.0f);

   temp.Multiply(qy, qz);
   Multiply(qx, temp);
}

/*
=============
Slerp
=============
   Spherical linear interpolation between from and to.  Gamasutra.
*/
void quat_t::Slerp(float t, const quat_t &from, const quat_t &to)
{
   float to1[4];
   float omega, cosom, sinom, scale0, scale1;

   cosom = from.x * to.x + from.y * to.y + from.z * to.z + from.w * to.w;

   // adjust signs (if necessary)
   if (cosom < 0.0f)
   {
      cosom  = -cosom; 
      to1[0] = -to.x;
      to1[1] = -to.y;
      to1[2] = -to.z;
      to1[3] = -to.w;
   }
   else 
   {
      to1[0] = to.x;
      to1[1] = to.y;
      to1[2] = to.z;
      to1[3] = to.w;
   }

   // calculate coefficients
   if ((1.0f - cosom) > mLibEpsilon)
   {
      // standard case (slerp)
      omega = (float) acos(cosom);
      sinom = (float) sin(omega);
      scale0 = (float) sin((1.0 - t) * omega) / sinom;
      scale1 = (float) sin(t * omega) / sinom;
   }
   else
   {        
      // "from" and "to" quaternions are very close 
      //  ... so we can do a linear interpolation
      scale0 = 1.0f - t;
      scale1 = t;
   }

   // calculate final values
   x = (scale0 * from.x) + (scale1 * to1[0]);
   y = (scale0 * from.y) + (scale1 * to1[1]);
   z = (scale0 * from.z) + (scale1 * to1[2]);
   w = (scale0 * from.w) + (scale1 * to1[3]);
}
