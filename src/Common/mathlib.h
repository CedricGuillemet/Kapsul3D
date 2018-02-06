/*
   Copyright (C) 2000 Nate Miller nathanm@uci.edu

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
      (10/02/00)
         - added an mLib prefix to everyting, makes more sense now
   TODO  
      - the #define and static const is ick.  need to change it
*/
#ifndef __MATHLIBH__
#define __MATHLIBH__

#include <math.h>

#ifndef uint
typedef unsigned int uint;
#endif

#define mLibFab(a)    (a >= 0 ? a : -a) 
#define mLibMax(a, b) (a > b ? a : b)
#define mLibMin(a, b) (a < b ? a : b)

static const double mLibPi = 3.14159265358979323846264338327950288419716939937510f;
static const float  mLibEpsilon = 1.0e-05f;
static const double mLibTwoPi = 2 * mLibPi;
static const double mLibPiDivTwo = mLibPi / 2;
static const double mLibDTR = (mLibPi / 180.0f);

static double mLibDegToRad(float angle)
 {return angle * mLibDTR;}
static float mLibCos(float angle)
 {return (float) cos(angle * mLibDTR);}
static float mLibSin(float angle)
 {return (float) sin(angle * mLibDTR);}

#include "vector.h"
#include "matrix.h"

#endif