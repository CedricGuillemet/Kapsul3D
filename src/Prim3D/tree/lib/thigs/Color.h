#ifndef Color_INCLUDED
#define Color_INCLUDED

#define NOMINMAX
#pragma warning( disable : 4244 ) 

typedef unsigned long ulong;

#include <thigs/Vec4.h>

struct RGBA;

struct HSVA {

  HSVA(const Vec4<float>& v)
    : hue(v[0]), saturation(v[1]), value(v[2]), alpha(v[3]) {}
  HSVA(float h, float s, float v, float a=1.0)
    : hue(h), saturation(s), value(v), alpha(a) {}
  HSVA(const RGBA&);

  //  operator Vec4<float>();

  float hue;
  float saturation;
  float value;
  float alpha;
};


struct RGBA {

  RGBA(const Vec4<float>& v) 
    : red(v[0]), green(v[1]), blue(v[2]), alpha(v[3]) {}
  RGBA(float r, float g, float b, float a = 1.0) 
    : red(r), green(g), blue(b), alpha(a) {}
  RGBA(const HSVA&);

  //  operator Vec4<float>();

  float red;
  float green;
  float blue;
  float alpha;
};


struct PackedRGBA {

  PackedRGBA() : color(0x00000000) {}

  PackedRGBA(ulong r, ulong g, ulong b, ulong a) {

    if (r>255) r=255;
    if (g>255) g=255;
    if (b>255) b=255;
    if (a>255) a=255;
    color = r | (g << 8) | (b << 16) | (a << 24);
  }

  PackedRGBA(const PackedRGBA& c) : color(c.color) {}
  PackedRGBA(unsigned long c) : color(c) {}
  operator unsigned long() {return color;}

  inline unsigned long red() const   {return (color & 0x000000ff);}
  inline unsigned long green() const {return (color & 0x0000ff00) >> 8;}
  inline unsigned long blue() const  {return (color & 0x00ff0000) >> 16;}
  inline unsigned long alpha() const {return (color & 0xff000000) >> 24;}

  inline PackedRGBA& setRed(ulong r) {
    color = (color & 0xffffff00) | (r & 0x000000ff);
    return *this;
  }

  inline PackedRGBA& setGreen(ulong g) {
    color = (color & 0xffff00ff) | ((g & 0x000000ff) << 8);
    return *this;
  }

  inline PackedRGBA& setBlue(ulong b) {
    color = (color & 0xff00ffff) | ((b & 0x000000ff) << 16);
    return *this;
  }

  inline PackedRGBA& setAlpha(ulong a) {
    color = (color & 0x00ffffff) | ((a & 0x000000ff) << 24);
    return *this;
  }


  inline unsigned long operator[](int i) {
    switch(i) {
    case 0:
      return red();
    case 1:
      return green();
    case 2:
      return blue();
    case 3:
      return alpha();
    }
    return 0x00000000;  // should abort?
  }

  unsigned long color;
};


inline PackedRGBA operator+(const PackedRGBA& a, const PackedRGBA& b) {

  ulong red = a.red() + b.red();
  ulong green = a.green() + b.green();
  ulong blue = a.blue() + b.blue();
  ulong alpha = a.alpha() + b.alpha();
  
  return PackedRGBA(red, green, blue, alpha);
}

inline PackedRGBA operator*(const PackedRGBA& c, double u) {

  ulong red = c.red() * u;
  ulong green = c.green() * u;
  ulong blue = c.blue() * u;
  ulong alpha = c.alpha() * u;
  
  return PackedRGBA(red, green, blue, alpha);
}


#endif


