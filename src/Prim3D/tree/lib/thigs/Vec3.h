#ifndef Vec3_INCLUDED
#define Vec3_INCLUDED

#include <assert.h>
#include <math.h>

#pragma function(sqrt) // remove when service pack 3 is installed

template <class T>
struct Vec3 {

  Vec3() {}
  Vec3(const T& x, const T& y, const T& z) {
    v[0]=x; v[1]=y; v[2]=z;
  }

  inline T& operator[](int i) {
    assert((i>=0)&&(i<3)); 
    return v[i];
  }

  inline const T& operator[](int i) const {
    assert((i>=0)&&(i<3));
    return v[i];
  }

  inline Vec3<T>& operator*=(const T& s) {
    v[0] *= s;
    v[1] *= s;
    v[2] *= s;
    return *this;
  }

  inline Vec3<T>& operator/=(const T& s) {
    v[0] /= s;
    v[1] /= s;
    v[2] /= s;
    return *this;
  }

  inline Vec3<T>& operator+=(const Vec3<T>& that) {
    v[0] += that.v[0];
    v[1] += that.v[1];
    v[2] += that.v[2];
    return *this;
  }

  inline Vec3<T>& operator-=(const Vec3<T>& that) {
    v[0] -= that.v[0];
    v[1] -= that.v[1];
    v[2] -= that.v[2];
    return *this;
  }

  inline void set(const T& a, const T& b, const T& c) {
    v[0] = a;
    v[1] = b;
    v[2] = c;
  }

 private:

  T v[3];


  friend inline bool operator==(const Vec3<T>&, const Vec3<T>&);
  friend inline bool operator!=(const Vec3<T>&, const Vec3<T>&);

  friend inline Vec3<T> operator*(const Vec3<T>&, const T&);
  friend inline Vec3<T> operator/(const Vec3<T>&, const T&);
  friend inline Vec3<T> operator+(const Vec3<T>&, const Vec3<T>&);
  friend inline Vec3<T> operator-(const Vec3<T>&, const Vec3<T>&);
  friend inline Vec3<T> operator-(const Vec3<T>&);
  friend inline T dot(const Vec3<T>&, const Vec3<T>&);
  friend inline Vec3<T> cross(const Vec3<T>&, const Vec3<T>&);
};

template <class T>
inline bool operator==(const Vec3<T>& a, const Vec3<T>& b) {
  return
    (a.v[0]==b.v[0]) && 
    (a.v[1]==b.v[1]) && 
    (a.v[2]==b.v[2]);
}

template <class T>
inline bool operator!=(const Vec3<T>& a, const Vec3<T>& b) {
  return !(a==b);
}

template <class T>
inline Vec3<T> operator*(const Vec3<T>& v, const T& s) {
  return Vec3<T>(v.v[0]*s,
		 v.v[1]*s,
		 v.v[2]*s);
}

template <class T>
inline Vec3<T> operator*(const T& s, const Vec3<T>& v) {
  return Vec3<T>(s*v[0],
		 s*v[1],
		 s*v[2]);
}

template <class T>
inline Vec3<T> operator/(const Vec3<T>& v, const T& s) {
  return Vec3<T>(v.v[0]/s,
		 v.v[1]/s,
		 v.v[2]/s);
}

template <class T>
inline Vec3<T> operator+(const Vec3<T>& a, const Vec3<T>& b) {
  return Vec3<T>(a.v[0]+b.v[0],
		 a.v[1]+b.v[1],
		 a.v[2]+b.v[2]);
}

template <class T>
inline Vec3<T> operator-(const Vec3<T>& a, const Vec3<T>& b) {
  return Vec3<T>(a.v[0]-b.v[0],
		 a.v[1]-b.v[1],
		 a.v[2]-b.v[2]);
}

template <class T>
inline Vec3<T> operator-(const Vec3<T>& v) {
  return Vec3<T>(-v.v[0],
		 -v.v[1],
		 -v.v[2]);
}

template <class T>
inline T dot(const Vec3<T>& a, const Vec3<T>& b) {
  return (a.v[0]*b.v[0] + 
	  a.v[1]*b.v[1] +
	  a.v[2]*b.v[2]);
}


template <class T>
inline Vec3<T> cross(const Vec3<T>& a, const Vec3<T>& b) {

  return Vec3<T>(a[1]*b[2] - a[2]*b[1],
		 a[2]*b[0] - a[0]*b[2],
		 a[0]*b[1] - a[1]*b[0]);
}


inline double length(const Vec3<double>& v) {
  return sqrt(dot(v, v));
}

inline float length(const Vec3<float>& v) {
  return sqrtf(dot(v, v));
}

inline long double length(const Vec3<long double>& v) {
  return sqrtl(dot(v, v));
}


template <class T>
inline Vec3<T> normalize(const Vec3<T>& v) {
  return v / length(v);
}


typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;
typedef Vec3<signed int> Vec3i;
typedef Vec3<signed short> Vec3s;
typedef Vec3<signed char> Vec3b;

#endif
