#include "Sky.h"

#pragma warning( disable : 4244 )
#pragma warning( disable : 4305 )

#include <windows.h>
#include <gl/GL.h>
#include <thigs/thigs.h>
#include <thigs/Light.h>

#include <thigs/Texture.h>

static const double PI = 3.141592653589;

Sky::Sky() : facets(24), radius(45.0f), height(20.0f) {

  vertices = new Vec3<float>[(facets+1)*2];
  tex_coords = new Vec2<float>[(facets+1)*2];

  for (int i=0; i<=facets; ++i) {

    float t = 1.0f/facets*i;

    float s = sinf(PI*2.0f*t);
    float c = cosf(PI*2.0f*t);

    vertices[i*2] = Vec3<float>(c*radius, s*radius, 0.0f);
    vertices[i*2+1] = Vec3<float>(c*radius, s*radius, height);

    float tc = t * 4;

    tex_coords[i*2] = Vec2<float>(tc, 0.0f);
    tex_coords[i*2+1] = Vec2<float>(tc, 0.99f);
  }
}

Sky::~Sky() {

  delete [] vertices;
  delete [] tex_coords;
}


void Sky::setNightTexture(const Ptr<Texture>& t) {

  night_texture = t;
  night_texture->repeatHorizontal(true);
}

void Sky::setDayTexture(const Ptr<Texture>& t) {

  day_texture = t;
  day_texture->repeatHorizontal(true);
}

void Sky::setDay(bool d) {

  day = d;
}


void Sky::draw(WeakPtr<GLContext>& context) {

  Light::disableLighting();
  if (day) {
    color(Vec4<float>(1.0, 1.0, 1.0, 1.0));
    if (day_texture) day_texture->apply(context);
  } else {
    //color(Vec4<float>(1.0, 1.0, 1.0, 1.0));
    color(Vec4<float>(0.5, 0.5, 0.5, 1.0));
    if (night_texture) night_texture->apply(context);
  }    
  
  glBegin(GL_TRIANGLE_STRIP);

  for (int i=0; i<(facets+1); ++i) {

    texCoord(tex_coords[i*2]);
    vertex(vertices[i*2]);

    texCoord(tex_coords[i*2+1]);
    vertex(vertices[i*2+1]);
  }
  glEnd();

  Texture::disable(context);
  if (day) {
    color(Vec3<unsigned char>(25, 60, 105));
    //    color(Vec3<unsigned char>(8, 46, 102));
  } else {
    color(Vec3<unsigned char>(12, 30, 52));
    //    color(Vec3<unsigned char>(4, 23, 51));
  }

  glBegin(GL_POLYGON);
  for (i=facets-1; i>=0; --i) {
    vertex(vertices[i*2+1]);
  }
  glEnd();
}

