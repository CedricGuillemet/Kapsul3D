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
/*
   WORKLOG

   TODO
      - make this a more full featured class

   SOURCES
      - http://www.gamasutra.com/features/19980703/quaternions_01.htm
      - http://skal.planet-d.net/demo/matrixfaq.htm
*/
#ifndef __QUATH__
#define __QUATH__

#include "mathlib.h"

struct quat_t
{
   quat_t() {Reset();}

   void Reset(void);
   void Normalize(void);

   void Multiply(const quat_t &lhs, const quat_t &rhs);

   void ToMatrix(matrix_t &mat);
   void MatrixToQuat(matrix_t &mat);
   void AxisAngleToQuat(const vec3_t &axis, float angle);
   void EulerToQuat(float x, float y, float z);

   void Slerp(float t, const quat_t &from, const quat_t &to);

protected:
   float x;
   float y;
   float z;
   float w;
};

#endif