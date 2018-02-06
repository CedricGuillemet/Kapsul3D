#ifndef thigs_INCLUDED
#define thigs_INCLUDED

#include <math.h>

#pragma function(sqrt,sin,cos) // remove when service pack 3 is available

#include <GL/gl.h>

#include <thigs/Vec2.h>
#include <thigs/Vec3.h>
#include <thigs/Vec4.h>


inline void vertex(const Vec2<double>& v) {glVertex2dv(&v[0]);}
inline void vertex(const Vec2<float>& v)  {glVertex2fv(&v[0]);}
inline void vertex(const Vec2<int>& v)    {glVertex2iv(&v[0]);}
inline void vertex(const Vec2<short>& v)  {glVertex2sv(&v[0]);}

inline void vertex(const Vec3<double>& v) {glVertex3dv(&v[0]);}
inline void vertex(const Vec3<float>& v)  {glVertex3fv(&v[0]);}
inline void vertex(const Vec3<int>& v)    {glVertex3iv(&v[0]);}
inline void vertex(const Vec3<short>& v)  {glVertex3sv(&v[0]);}

inline void vertex(const Vec4<double>& v) {glVertex4dv(&v[0]);}
inline void vertex(const Vec4<float>& v)  {glVertex4fv(&v[0]);}
inline void vertex(const Vec4<int>& v)    {glVertex4iv(&v[0]);}
inline void vertex(const Vec4<short>& v)  {glVertex4sv(&v[0]);}

inline void color(const Vec3<double>& v) {glColor3dv(&v[0]);}
inline void color(const Vec3<float>& v)  {glColor3fv(&v[0]);}
inline void color(const Vec3<signed int>& v)    {glColor3iv(&v[0]);}
inline void color(const Vec3<signed short>& v)  {glColor3sv(&v[0]);}
inline void color(const Vec3<signed char>& v)  {glColor3bv(&v[0]);}
inline void color(const Vec3<unsigned int>& v)    {glColor3uiv(&v[0]);}
inline void color(const Vec3<unsigned short>& v)  {glColor3usv(&v[0]);}
inline void color(const Vec3<unsigned char>& v)  {glColor3ubv(&v[0]);}

inline void color(const Vec4<double>& v) {glColor4dv(&v[0]);}
inline void color(const Vec4<float>& v)  {glColor4fv(&v[0]);}
inline void color(const Vec4<signed int>& v)    {glColor4iv(&v[0]);}
inline void color(const Vec4<signed short>& v)  {glColor4sv(&v[0]);}
inline void color(const Vec4<signed char>& v)  {glColor4bv(&v[0]);}
inline void color(const Vec4<unsigned int>& v)    {glColor4uiv(&v[0]);}
inline void color(const Vec4<unsigned short>& v)  {glColor4usv(&v[0]);}
inline void color(const Vec4<unsigned char>& v)  {glColor4ubv(&v[0]);}

inline void normal(const Vec3<double>& v) {glNormal3dv(&v[0]);}
inline void normal(const Vec3<float>& v)  {glNormal3fv(&v[0]);}
inline void normal(const Vec3<int>& v)    {glNormal3iv(&v[0]);}
inline void normal(const Vec3<short>& v)  {glNormal3sv(&v[0]);}

inline void texCoord(double v) {glTexCoord1d(v);}
inline void texCoord(float v)  {glTexCoord1f(v);}
inline void texCoord(int v)    {glTexCoord1i(v);}
inline void texCoord(short v)  {glTexCoord1s(v);}

inline void texCoord(const Vec2<double>& v) {glTexCoord2dv(&v[0]);}
inline void texCoord(const Vec2<float>& v)  {glTexCoord2fv(&v[0]);}
inline void texCoord(const Vec2<int>& v)    {glTexCoord2iv(&v[0]);}
inline void texCoord(const Vec2<short>& v)  {glTexCoord2sv(&v[0]);}

inline void texCoord(const Vec3<double>& v) {glTexCoord3dv(&v[0]);}
inline void texCoord(const Vec3<float>& v)  {glTexCoord3fv(&v[0]);}
inline void texCoord(const Vec3<int>& v)    {glTexCoord3iv(&v[0]);}
inline void texCoord(const Vec3<short>& v)  {glTexCoord3sv(&v[0]);}

inline void texCoord(const Vec4<double>& v) {glTexCoord4dv(&v[0]);}
inline void texCoord(const Vec4<float>& v)  {glTexCoord4fv(&v[0]);}
inline void texCoord(const Vec4<int>& v)    {glTexCoord4iv(&v[0]);}
inline void texCoord(const Vec4<short>& v)  {glTexCoord4sv(&v[0]);}


inline void multMatrix(const Vec4< Vec4<double> >& m) {
  glMultMatrixd(&m[0][0]);
}
inline void multMatrix(const Vec4< Vec4<float> >& m) {
  glMultMatrixf(&m[0][0]);
}

inline void loadMatrix(const Vec4< Vec4<double> >& m) {
  glLoadMatrixd(&m[0][0]);
}
inline void loadMatrix(const Vec4< Vec4<float> >& m) {
  glLoadMatrixf(&m[0][0]);
}

static const Vec4< Vec4<double> > ident_matrix_d =
Vec4< Vec4 <double> >( Vec4<double>(1.0, 0.0, 0.0, 0.0),
		       Vec4<double>(0.0, 1.0, 0.0, 0.0),
		       Vec4<double>(0.0, 0.0, 1.0, 0.0),
		       Vec4<double>(0.0, 0.0, 0.0, 1.0) );



static const Vec4< Vec4<float> > ident_matrix_f =
Vec4< Vec4 <float> >( Vec4<float>(1.0f, 0.0f, 0.0f, 0.0f),
		      Vec4<float>(0.0f, 1.0f, 0.0f, 0.0f),
		      Vec4<float>(0.0f, 0.0f, 1.0f, 0.0f),
		      Vec4<float>(0.0f, 0.0f, 0.0f, 1.0f) );




/* XXX untested */

template <class T>
inline Vec4< Vec4<T> > operator*(const Vec4< Vec4<T> >& a, 
				 const Vec4< Vec4<T> >& b) {

  Vec4< Vec4<T> > result;
  
  for (int i=0; i<4; ++i) {

    for (int j=0; j<4; ++j) {

      double s = 0;
      for (int k=0; k<4; ++k) {

	s += a[i][k] * b[k][j];
      }
      result[i][j] = s;
    }
  }
  return result;
}


template <class T>
inline Vec4< Vec4<T> > transpose(const Vec4< Vec4<T> >& m) {

  Vec4< Vec4<T> > result;
  for (int i=0; i<4; i++) {
    for (int j=0; j<4; j++) {
      result[j][i] = m[i][j];
    }
  }
  return result;
}


template <class T>
inline Vec4<T> mult(const Vec4<T>& v, const Vec4< Vec4<T> > m) {

  return Vec4<T>(v[0]*m[0][0] + v[1]*m[1][0] + v[2]*m[2][0] + v[3]*m[3][0],
		 v[0]*m[0][1] + v[1]*m[1][1] + v[2]*m[2][1] + v[3]*m[3][1],
		 v[0]*m[0][2] + v[1]*m[1][2] + v[2]*m[2][2] + v[3]*m[3][2],
		 v[0]*m[0][3] + v[1]*m[1][3] + v[2]*m[2][3] + v[3]*m[3][3]);
}

template <class T>
inline Vec3<T> transformPoint(const Vec3<T>& v, const Vec4< Vec4<T> > m) {

  return Vec3<T>(v[0]*m[0][0] + v[1]*m[1][0] + v[2]*m[2][0] + m[3][0],
		 v[0]*m[0][1] + v[1]*m[1][1] + v[2]*m[2][1] + m[3][1],
		 v[0]*m[0][2] + v[1]*m[1][2] + v[2]*m[2][2] + m[3][2]);
}

template <class T>
inline Vec3<T> transformNormal(const Vec3<T>& v, const Vec4< Vec4<T> > m) {

  return Vec3<T>(v[0]*m[0][0] + v[1]*m[1][0] + v[2]*m[2][0],
		 v[0]*m[0][1] + v[1]*m[1][1] + v[2]*m[2][1],
		 v[0]*m[0][2] + v[1]*m[1][2] + v[2]*m[2][2]);
}


struct Singular {};

template <class T>
inline Vec4< Vec4<T> > invert(const Vec4< Vec4<T> > from) {

  Vec4< Vec4<T> > to;

  T wtemp[4][8];
  T m0,m1,m2,m3,s;
  T *r0,*r1,*r2,*r3, *rtemp;

  r0 = wtemp[0];
  r1 = wtemp[1];
  r2 = wtemp[2];
  r3 = wtemp[3];
  r0[0] = from[0][0];             /* build up [A][I]      */
  r0[1] = from[0][1];
  r0[2] = from[0][2];
  r0[3] = from[0][3];
  r0[4] = 1.0;
  r0[5] = 0.0;
  r0[6] = 0.0;
  r0[7] = 0.0;
  r1[0] = from[1][0];
  r1[1] = from[1][1];
  r1[2] = from[1][2];
  r1[3] = from[1][3];
  r1[4] = 0.0;
  r1[5] = 1.0;
  r1[6] = 0.0;
  r1[7] = 0.0;
  r2[0] = from[2][0];
  r2[1] = from[2][1];
  r2[2] = from[2][2];
  r2[3] = from[2][3];
  r2[4] = 0.0;
  r2[5] = 0.0;
  r2[6] = 1.0;
  r2[7] = 0.0;
  r3[0] = from[3][0];
  r3[1] = from[3][1];
  r3[2] = from[3][2];
  r3[3] = from[3][3];
  r3[4] = 0.0;
  r3[5] = 0.0;
  r3[6] = 0.0;
  r3[7] = 1.0;
  
  if (r0[0] == 0.0) {             /* swap rows if needed          */
    if (r1[0] == 0.0) {
      if (r2[0] == 0.0) {
	if (r3[0] == 0.0) throw Singular();
	rtemp = r0;
	r0 = r3;
	r3 = rtemp;
      } else {
	rtemp = r0;
	r0 = r2;
	r2 = rtemp;
      }
    } else {
      rtemp = r0;
      r0 = r1;
      r1 = rtemp;
    }
  }
  m1 = r1[0]/r0[0];               /* eliminate first variable     */
  m2 = r2[0]/r0[0];
  m3 = r3[0]/r0[0];
  s = r0[1];
  r1[1] = r1[1] - m1 * s;
  r2[1] = r2[1] - m2 * s;
  r3[1] = r3[1] - m3 * s;
  s = r0[2];
  r1[2] = r1[2] - m1 * s;
  r2[2] = r2[2] - m2 * s;
  r3[2] = r3[2] - m3 * s;
  s = r0[3];
  r1[3] = r1[3] - m1 * s;
  r2[3] = r2[3] - m2 * s;
  r3[3] = r3[3] - m3 * s;
  s = r0[4];
  if (s != 0.0) {
    r1[4] = r1[4] - m1 * s;
    r2[4] = r2[4] - m2 * s;
    r3[4] = r3[4] - m3 * s;
  }
  s = r0[5];
  if (s != 0.0) {
    r1[5] = r1[5] - m1 * s;
    r2[5] = r2[5] - m2 * s;
    r3[5] = r3[5] - m3 * s;
  }
  s = r0[6];
  if (s != 0.0) {
    r1[6] = r1[6] - m1 * s;
    r2[6] = r2[6] - m2 * s;
    r3[6] = r3[6] - m3 * s;
  }
  s = r0[7];
  if (s != 0.0) {
    r1[7] = r1[7] - m1 * s;
    r2[7] = r2[7] - m2 * s;
    r3[7] = r3[7] - m3 * s;
  }

  if (r1[1] == 0.0) {             /* swap rows if needed          */
    if (r2[1] == 0.0) {
      if (r3[1] == 0.0) throw Singular();
      rtemp = r1;
      r1 = r3;
      r3 = rtemp;
    } else {
      rtemp = r1;
      r1 = r2;
      r2 = rtemp;
    }
  }
  m2 = r2[1]/r1[1];               /* eliminate second variable    */
  m3 = r3[1]/r1[1];
  r2[2] = r2[2] - m2 * r1[2];
  r3[2] = r3[2] - m3 * r1[2];
  r3[3] = r3[3] - m3 * r1[3];
  r2[3] = r2[3] - m2 * r1[3];
  s = r1[4];
  if (s != 0.0) {
    r2[4] = r2[4] - m2 * s;
    r3[4] = r3[4] - m3 * s;
  }
  s = r1[5];
  if (s != 0.0) {
    r2[5] = r2[5] - m2 * s;
    r3[5] = r3[5] - m3 * s;
  }
  s = r1[6];
  if (s != 0.0) {
    r2[6] = r2[6] - m2 * s;
    r3[6] = r3[6] - m3 * s;
  }
  s = r1[7];
  if (s != 0.0) {
    r2[7] = r2[7] - m2 * s;
    r3[7] = r3[7] - m3 * s;
  }

  if (r2[2] == 0.0) {             /* swap last 2 rows if needed   */
    if (r3[2] == 0.0) throw Singular();
    rtemp = r2;
    r2 = r3;
    r3 = rtemp;
  }
  m3 = r3[2]/r2[2];               /* eliminate third variable     */
  r3[3] = r3[3] - m3 * r2[3];
  r3[4] = r3[4] - m3 * r2[4];
  r3[5] = r3[5] - m3 * r2[5];
  r3[6] = r3[6] - m3 * r2[6];
  r3[7] = r3[7] - m3 * r2[7];

  if (r3[3] == 0.0) throw Singular();
  s = 1.0/r3[3];          /* now back substitute row 3    */
  r3[4] = r3[4] * s;
  r3[5] = r3[5] * s;
  r3[6] = r3[6] * s;
  r3[7] = r3[7] * s;

  m2 = r2[3];                     /* now back substitute row 2    */
  s = 1.0/r2[2];
  r2[4] = s * (r2[4] - r3[4] * m2);
  r2[5] = s * (r2[5] - r3[5] * m2);
  r2[6] = s * (r2[6] - r3[6] * m2);
  r2[7] = s * (r2[7] - r3[7] * m2);
  m1 = r1[3];
  r1[4] = (r1[4] - r3[4] * m1);
  r1[5] = (r1[5] - r3[5] * m1);
  r1[6] = (r1[6] - r3[6] * m1);
  r1[7] = (r1[7] - r3[7] * m1);
  m0 = r0[3];
  r0[4] = (r0[4] - r3[4] * m0);
  r0[5] = (r0[5] - r3[5] * m0);
  r0[6] = (r0[6] - r3[6] * m0);
  r0[7] = (r0[7] - r3[7] * m0);

  m1 = r1[2];                     /* now back substitute row 1    */
  s = 1.0/r1[1];
  r1[4] = s * (r1[4] - r2[4] * m1);
  r1[5] = s * (r1[5] - r2[5] * m1);
  r1[6] = s * (r1[6] - r2[6] * m1);
  r1[7] = s * (r1[7] - r2[7] * m1);
  m0 = r0[2];
  r0[4] = (r0[4] - r2[4] * m0);
  r0[5] = (r0[5] - r2[5] * m0);
  r0[6] = (r0[6] - r2[6] * m0);
  r0[7] = (r0[7] - r2[7] * m0);

  m0 = r0[1];                     /* now back substitute row 0    */
  s = 1.0/r0[0];
  r0[4] = s * (r0[4] - r1[4] * m0);
  r0[5] = s * (r0[5] - r1[5] * m0);
  r0[6] = s * (r0[6] - r1[6] * m0);
  r0[7] = s * (r0[7] - r1[7] * m0);

  to[0][0] = r0[4];               /* copy results back            */
  to[0][1] = r0[5];
  to[0][2] = r0[6];
  to[0][3] = r0[7];
  to[1][0] = r1[4];
  to[1][1] = r1[5];
  to[1][2] = r1[6];
  to[1][3] = r1[7];
  to[2][0] = r2[4];
  to[2][1] = r2[5];
  to[2][2] = r2[6];
  to[2][3] = r2[7];
  to[3][0] = r3[4];
  to[3][1] = r3[5];
  to[3][2] = r3[6];
  to[3][3] = r3[7];

  return to;
}



inline Vec4<double> quat(const Vec3<double>& axis, double angle) {

  Vec4<double> q;

  double length = sin(angle/2.0);

  double r =
    axis[0]*axis[0]+
    axis[1]*axis[1]+
    axis[2]*axis[2];

  if (r==0.0) {
    q = Vec4<double>(0.0,0.0,0.0,1.0);
  } else {

    q = Vec4<double>(axis[0]*length, 
		     axis[1]*length,
		     axis[2]*length, 
		     cos(angle/2.0));
  }

  return q;
}

// assumes axis is normalized

inline Vec4<float> quat(const Vec3<float>& axis, float angle) {

  Vec4<float> q;

  float length = sinf(angle/2.0f);

  if (dot(axis,axis)==0.0) {
    q = Vec4<float>(0.0,0.0,0.0,1.0);
  } else {

    q = Vec4<float>(axis[0]*length, 
		    axis[1]*length,
		    axis[2]*length, 
		    cosf(angle/2.0));
  }

  return q;
}


template <class T>
inline Vec4< Vec4<T> > rotate(const Vec3<T>& axis, T angle) {

  Vec4<T> q = quat(axis, angle);

  T x = q[0];
  T y = q[1];
  T z = q[2];
  T w = q[3];
  return Vec4< Vec4<T> >
    (Vec4<T>(1.0 + 2.0 * (-y*y - z*z),
	     2.0 * ( x*y + w*z),
	     2.0 * ( x*z - w*y),
	     0.0),
     Vec4<T>(2.0 * ( x*y - w*z),
	     1.0 + 2.0 * (-x*x - z*z),
	     2.0 * ( y*z + w*x),
	     0.0),
     Vec4<T>(2.0 * ( x*z + w*y),
	     2.0 * ( y*z - w*x),
	     1.0 + 2.0 * (-x*x - y*y),
	     0.0),

     Vec4<T>(0.0, 0.0, 0.0, 1.0));
}


template <class T>
inline Vec4< Vec4<T> > translate(const Vec3<T>& vec) {

  return Vec4< Vec4<T> >
    (Vec4<T>(1.0, 0.0, 0.0, 0.0),
     Vec4<T>(0.0, 1.0, 0.0, 0.0),
     Vec4<T>(0.0, 0.0, 1.0, 0.0),
     Vec4<T>(vec[0], vec[1], vec[2], 1.0));
}



template <class T>
inline Vec4< Vec4<T> > translate(T x, T y, T z) {

  return Vec4< Vec4<T> >
    (Vec4<T>(1.0, 0.0, 0.0, 0.0),
     Vec4<T>(0.0, 1.0, 0.0, 0.0),
     Vec4<T>(0.0, 0.0, 1.0, 0.0),
     Vec4<T>(x, y, z, 1.0));
}



template <class T>
inline Vec4< Vec4<T> > scale(T x, T y, T z) {

  return Vec4< Vec4<T> >
    (Vec4<T>(     x,    0.0,    0.0, 0.0),
     Vec4<T>(   0.0,      y,    0.0, 0.0),
     Vec4<T>(   0.0,    0.0,      z, 0.0),
     Vec4<T>(   0.0,    0.0,    0.0, 1.0));
}



template <class T>
inline Vec4< Vec4<T> > scale(const Vec3<T>& vec) {

  return Vec4< Vec4<T> >
    (Vec4<T>(vec[0],    0.0,    0.0, 0.0),
     Vec4<T>(   0.0, vec[1],    0.0, 0.0),
     Vec4<T>(   0.0,    0.0, vec[2], 0.0),
     Vec4<T>(   0.0,    0.0,    0.0, 1.0));
}


inline Vec4< Vec4<double> > scale(double s) {

  return Vec4< Vec4<double> >
    (Vec4<double>(     s,    0.0,    0.0, 0.0),
     Vec4<double>(   0.0,      s,    0.0, 0.0),
     Vec4<double>(   0.0,    0.0,      s, 0.0),
     Vec4<double>(   0.0,    0.0,    0.0, 1.0));
}

inline Vec4< Vec4<float> > scale(float s) {

  return Vec4< Vec4<float> >
    (Vec4<float>(     s,    0.0,    0.0, 0.0),
     Vec4<float>(   0.0,      s,    0.0, 0.0),
     Vec4<float>(   0.0,    0.0,      s, 0.0),
     Vec4<float>(   0.0,    0.0,    0.0, 1.0));
}


template <class T>
inline Vec4< Vec4<T> > frustum(T left,
			       T right,
			       T bottom,
			       T top, 
			       T near,
			       T far) {

  T c1 = (2.0*near)/(right-left);
  T c2 = (2.0*near)/(top-bottom);

  T a = (right+left)/(right-left);
  T b = (top+bottom)/(top-bottom);
  T c = -(far+near)/(far-near);
  T d = -(2*far*near)/(far-near);

  return Vec4< Vec4<T> >
    (Vec4<T>( c1, 0.0, a, 0.0),
     Vec4<T>(0.0,  c2, b, 0.0),
     Vec4<T>(  a,   b, c, -1.0),
     Vec4<T>(0.0, 0.0, d, 0));
}

#endif
