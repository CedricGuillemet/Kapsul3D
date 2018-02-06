#ifndef Vec2_INCLUDED
#define Vec2_INCLUDED

#include <assert.h>
#include <math.h>

#pragma function(sqrt) // remove when service pack 3 is installed

template <class T>
struct Vec2 {

  Vec2() {}
  Vec2(const T& x, const T& y) {
    v[0]=x; v[1]=y;
  }

  inline T& operator[](int i) {
    assert((i>=0)&&(i<2)); 
    return v[i];
  }

  inline const T& operator[](int i) const {
    assert((i>=0)&&(i<2));
    return v[i];
  }

  inline Vec2<T>& operator*=(const T& s) {
    v[0] *= s;
    v[1] *= s;
    return *this;
  }

  inline Vec2<T>& operator/=(const T& s) {
    v[0] /= s;
    v[1] /= s;
    return *this;
  }

  inline Vec2<T>& operator+=(const Vec2<T>& that) {
    v[0] += that.v[0];
    v[1] += that.v[1];
    return *this;
  }

  inline Vec2<T>& operator-=(const Vec2<T>& that) {
    v[0] -= that.v[0];
    v[1] -= that.v[1];
    return *this;
  }

  inline void set(const T& a, const T& b) {
    v[0] = a;
    v[1] = b;
  }

 private:

  T v[2];
  
  friend inline bool operator==(const Vec2<T>& a, const Vec2<T>&);
  friend inline bool operator!=(const Vec2<T>& a, const Vec2<T>&);
  friend inline Vec2<T> operator*(const Vec2<T>&, const T&);
  friend inline Vec2<T> operator/(const Vec2<T>&, const T&);
  friend inline Vec2<T> operator+(const Vec2<T>&, const Vec2<T>&);
  friend inline Vec2<T> operator-(const Vec2<T>&, const Vec2<T>&);
  friend inline Vec2<T> operator-(const Vec2<T>&);
  friend inline T dot(const Vec2<T>&, const Vec2<T>&);
};


template <class T>
inline bool operator==(const Vec2<T>& a, const Vec2<T>& b) {
  return
    (a.v[0]==b.v[0]) && 
    (a.v[1]==b.v[1]);
}

template <class T>
inline bool operator!=(const Vec2<T>& a, const Vec2<T>& b) {
  return !(a==b);
}

template <class T>
inline Vec2<T> operator*(const Vec2<T>& v, const T& s) {
  return Vec2<T>(v.v[0]*s,
		 v.v[1]*s);
}

template <class T>
inline Vec2<T> operator*(const T& s, const Vec2<T>& v) {
  return Vec2<T>(s*v[0],
		 s*v[1]);
}

template <class T>
inline Vec2<T> operator/(const Vec2<T>& v, const T& s) {
  return Vec2<T>(v.v[0]/s,
		 v.v[1]/s);
}

template <class T>
inline Vec2<T> operator+(const Vec2<T>& a, const Vec2<T>& b) {
  return Vec2<T>(a.v[0]+b.v[0],
		 a.v[1]+b.v[1]);
}

template <class T>
inline Vec2<T> operator-(const Vec2<T>& a, const Vec2<T>& b) {
  return Vec2<T>(a.v[0]-b.v[0],
		 a.v[1]-b.v[1]);
}

template <class T>
inline Vec2<T> operator-(const Vec2<T>& v) {
  return Vec2<T>(-v.v[0],
		 -v.v[1]);
}

template <class T>
inline T dot(const Vec2<T>& a, const Vec2<T>& b) {
  return (a.v[0]*b.v[0] + 
	  a.v[1]*b.v[1]);
}


inline double length(const Vec2<double>& v) {
  return sqrt(dot(v, v));
}

inline float length(const Vec2<float>& v) {
  return sqrtf(dot(v, v));
}

inline long double length(const Vec2<long double>& v) {
  return sqrtl(dot(v, v));
}

template <class T>
inline Vec2<T> normalize(const Vec2<T>& v) {
    return v / length(v);
}

typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d;
typedef Vec2<signed int> Vec2i;
typedef Vec2<signed short> Vec2s;
typedef Vec2<signed char> Vec2b;

#endif
