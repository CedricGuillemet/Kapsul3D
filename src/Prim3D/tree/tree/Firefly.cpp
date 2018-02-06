#include "Firefly.h"

#pragma warning( disable : 4244 )
#pragma warning( disable : 4305 )

#include <stdlib.h>
#include <math.h>
#include <windows.h>

#include <GL/gl.h>
#include <thigs/thigs.h>
#include <thigs/Texture.h>
#include <thigs/Light.h>


static double random() {

  static double a = 16807.0;
  static double m = 2147483647.0;
  static double seed = 1.0;

  double t = a * seed;
  seed = t - m * floor(t/m);

  return seed/m;
}

template <class T>
T abs(T a) {

  if (a<0) return -a;
  return a;
}

Firefly::Firefly() 
  : hsva(random(), 0.4, 1.0), 
    c(1, 1, 1, 1),
    pos(0, 0, 3.0),
    vel(0, 0, 0),
    range(8) {
  
}

void Firefly::move(float dt) {

  hsva.hue = hsva.hue+0.01;
  if (hsva.hue>1.0) hsva.hue -= 1.0;
  RGBA rgba(hsva);
  c = Vec4<float>(rgba.red, rgba.green, rgba.blue, rgba.alpha);

  static unsigned int s=0;
  srand(s++);
  float r1 = random()*2.0f-1.0f;
  float r2 = random()*2.0f-1.0f;
  float r3 = random()*2.0f-1.0f;
  Vec3<float> r(r1, r2, r3);

  Vec3<float> home(-pos[0], -pos[1], -pos[2]+range/2.0);
  vel = vel + home*0.005f + r*0.08f;

  vel = vel * 0.97f;

  pos = pos + (vel * 0.5f);

  if (pos[2]<0.5) pos[2]=0.5;
}


void Firefly::draw(WeakPtr<GLContext>& context) {

  Texture::disable(context);
  Light::disableLighting();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDepthMask(false);

  glBegin(GL_TRIANGLE_FAN);

  color(c);
  vertex(pos);

  int n = 10;
  float s = 0.2;

  for (int i=0; i<n; ++i) {

    float x = (random()-0.5)*s;
    float y = (random()-0.5)*s;
    float z = (random()-0.5)*s;
    Vec3<float> v(x, y, z);

    glColor4f(c[0], c[1], c[2], 0.0);
    vertex(pos+v);
  }

  glEnd();

  glDisable(GL_BLEND);
  glDepthMask(true);
}
