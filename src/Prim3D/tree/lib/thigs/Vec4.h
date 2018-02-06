#ifndef Vec4_INCLUDED
#define Vec4_INCLUDED

#include <assert.h>
#include <math.h>

#pragma function(sqrt) // remove when service pack 3 is installed

template <class T>
struct Vec4 {

  Vec4() {}
  Vec4(const T& x, const T& y, const T& z, const T& w) {
    v[0]=x; v[1]=y; v[2]=z; v[3] = w;
  }

  inline T& operator[](int i) {
    assert((i>=0)&&(i<4)); 
    return v[i];
  }

  inline const T& operator[](int i) const {
    assert((i>=0)&&(i<4));
    return v[i];
  }

  inline Vec4<T>& operator*=(const T& s) {
    v[0] *= s;
    v[1] *= s;
    v[2] *= s;
    v[3] *= s;
    return *this;
  }

  inline Vec4<T>& operator/=(const T& s) {
    v[0] /= s;
    v[1] /= s;
    v[2] /= s;
    v[3] /= s;
    return *this;
  }

  inline Vec4<T>& operator+=(const Vec4<T>& that) {
    v[0] += that.v[0];
    v[1] += that.v[1];
    v[2] += that.v[2];
    v[3] += that.v[3];
    return *this;
  }

  inline Vec4<T>& operator-=(const Vec4<T>& that) {
    v[0] -= that.v[0];
    v[1] -= that.v[1];
    v[2] -= that.v[2];
    v[3] -= that.v[3];
    return *this;
  }

  inline void set(const T& a, const T& b, const T& c, const T& d) {
    v[0] = a;
    v[1] = b;
    v[2] = c;
    v[3] = d;
  }

 private:

  T v[4];

  friend inline bool operator==(const Vec4<T>&, const Vec4<T>&);
  friend inline bool operator!=(const Vec4<T>&, const Vec4<T>&);

  friend inline Vec4<T> operator*(const Vec4<T>&, const T&);
  friend inline Vec4<T> operator/(const Vec4<T>&, const T&);
  friend inline Vec4<T> operator+(const Vec4<T>&, const Vec4<T>&);
  friend inline Vec4<T> operator-(const Vec4<T>&, const Vec4<T>&);

  friend inline Vec4<T> operator-(const Vec4<T>&);

  friend inline T dot(const Vec4<T>&, const Vec4<T>&);
};


template <class T>
inline bool operator==(const Vec4<T>& a, const Vec4<T>& b) {
  return
    (a.v[0]==b.v[0]) && 
    (a.v[1]==b.v[1]) && 
    (a.v[2]==b.v[2]) && 
    (a.v[3]==b.v[3]);
}

template <class T>
inline bool operator!=(const Vec4<T>& a, const Vec4<T>& b) {
  return !(a==b);
}


template <class T>
inline Vec4<T> operator*(const Vec4<T>& v, const T& s) {
  return Vec4<T>(v.v[0]*s,
		 v.v[1]*s,
		 v.v[2]*s,
		 v.v[3]*s);
}

template <class T>
inline Vec4<T> operator*(const T& s, const Vec4<T>& v) {
  return Vec4<T>(s*v[0],
		 s*v[1],
		 s*v[2],
		 s*v[3]);
}

template <class T>
inline Vec4<T> operator/(const Vec4<T>& v, const T& s) {
  return Vec4<T>(v.v[0]/s,
		 v.v[1]/s,
		 v.v[2]/s,
		 v.v[3]/s);
}

template <class T>
inline Vec4<T> operator+(const Vec4<T>& a, const Vec4<T>& b) {
  return Vec4<T>(a.v[0]+b.v[0],
		 a.v[1]+b.v[1],
		 a.v[2]+b.v[2],
		 a.v[3]+b.v[3]);
}

template <class T>
inline Vec4<T> operator-(const Vec4<T>& a, const Vec4<T>& b) {
  return Vec4<T>(a.v[0]-b.v[0],
		 a.v[1]-b.v[1],
		 a.v[2]-b.v[2],
		 a.v[3]-b.v[3]);
}

template <class T>
inline Vec4<T> operator-(const Vec4<T>& v) {
  return Vec4<T>(-v.v[0],
		 -v.v[1],
		 -v.v[2],
		 -v.v[3]);
}

template <class T>
inline T dot(const Vec4<T>& a, const Vec4<T>& b) {
  return (a.v[0]*b.v[0] + 
	  a.v[1]*b.v[1] +
	  a.v[2]*b.v[2] +
	  a.v[3]*b.v[3]);
}


inline double length(const Vec4<double>& v) {
  return sqrt(dot(v, v));
}

inline float length(const Vec4<float>& v) {
  return sqrtf(dot(v, v));
}

inline long double length(const Vec4<long double>& v) {
  return sqrtl(dot(v, v));
}

template <class T>
inline Vec4<T> normalize(const Vec4<T>& v) {
  return v / length(v);
}

typedef Vec4<float> Vec4f;
typedef Vec4<double> Vec4d;
typedef Vec4<signed int> Vec4i;
typedef Vec4<signed short> Vec4s;
typedef Vec4<signed char> Vec4b;

typedef Vec4<Vec4<double> > Mat4x4d;
typedef Vec4<Vec4<float> > Mat4x4f;

#endif
