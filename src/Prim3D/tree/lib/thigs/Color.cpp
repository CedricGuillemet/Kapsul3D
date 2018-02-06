#include "Color.h"

#include <math.h>

template <class T>
static T min(T a, T b) {

  if (a<b) return a;
  return b;
}

template <class T>
static T max(T a, T b) {

  if (a>b) return a;
  return b;
}


#if 0
HSVA::operator Vec4<float>() {

  return Vec4<float>(hue, saturation, value, alpha);
}


RGBA::operator Vec4<float>() {

  return Vec4<float>(red, green, blue, alpha);
}
#endif


static inline float clamp(float x) {
  if (x>1.0f) return 1.0f;
  if (x<0.0f) return 0.0f;
  return x;
}


RGBA::RGBA(const HSVA& hsva) {

  alpha = hsva.alpha;

  float hue = hsva.hue - floor(hsva.hue);
  float sat = clamp(hsva.saturation);
  float val = clamp(hsva.value);

  float hh = hue*6.0;

  int i = (int)hh;

  hh -= i;

  float p = val*(1-sat);
  float q = val*(1-sat*hh);
  float t = val*(1-(sat*(1-hh)));

  switch (i) {
  case 0:
    red=val; green=t; blue=p;
    break;

  case 1:
    red=q; green=val; blue=p;
    break;

  case 2:
    red=p; green=val; blue=t;
    break;

  case 3:
    red=p; green=q; blue=val;
    break;

  case 4:
    red=t; green=p; blue=val;
    break;

  case 5:
    red=val; green=p; blue=q;
    break;
  }
}


HSVA::HSVA(const RGBA& rgba) {

  alpha = rgba.alpha;

  float red = rgba.red;
  float green = rgba.green;
  float blue = rgba.blue;

  float maxc = max(red,max(green,blue));
  float minc = min(red,max(green,blue));

  float d = maxc-minc;

  value = maxc;

  if (maxc != 0.0) {
    saturation = d/maxc;
  } else {
    saturation=0.0;
  }

  if (saturation != 0.0) {

    float rc = (maxc-red)/d;
    float gc = (maxc-green)/d;
    float bc = (maxc-blue)/d;

    if (red==maxc) hue = bc-gc;
    else if (green==maxc) hue = 2 + rc - bc;
    else if (blue==maxc) hue = 4 + gc - rc;

    hue /= 6.0;
    if (hue<0.0) hue += 1.0;
  }
}


    
