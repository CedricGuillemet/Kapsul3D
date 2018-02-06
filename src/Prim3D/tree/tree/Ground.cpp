#include "Ground.h"

#pragma warning( disable : 4244 )
#pragma warning( disable : 4305 )

#include <windows.h>
#include <gl/GL.h>
#include <thigs/thigs.h>

#include <thigs/Light.h>
#include <thigs/Texture.h>
#include <thigs/Random.h>

Ground::Ground(float s) 
  : size(s), 
    res(10), 
    day(false) {

  vertices = new Vec3f[(res+1)*(res+1)];
  normals = new Vec3f[(res+1)*(res+1)];
  texcoords = new Vec2f[(res+1)*(res+1)];
  colors = new Vec3f[(res+1)*(res+1)];

  material.front_ambient=Vec4<float>(0.5, 0.5, 0.5, 1.0);
  material.front_diffuse=Vec4<float>(1.0, 1.0, 1.0, 1.0);

  build();
}

Ground::~Ground() {

  delete [] vertices;
  delete [] normals;
  delete [] texcoords;
  delete [] colors;
}

void Ground::setTexture(const Ptr<Texture>& t) {

  texture = t;
  texture->repeatHorizontal(true);
  texture->repeatVertical(true);
}

void Ground::setDay(bool d) {

  day = d;
}

void Ground::draw(WeakPtr<GLContext>& context) {

  glEnable(GL_DEPTH_TEST);
  color(Vec4<float>(1.0, 1.0, 1.0, 1.0));
  material.apply();
  if (texture) texture->apply(context);

  if (day) {
    drawDay();
  } else {
    drawNight();
  }
}


void Ground::drawNight() {
  drawColoredGround();
}

#if 1
void Ground::drawDay() {

  for (int i = -4; i<=4; ++i) {

    for (int j = -4; j<=4; ++j) {

      glPushMatrix();
      glTranslatef(float(j) * size, float(i) * size, 0.0);
      //      drawGround();
      drawGround();
      glPopMatrix();
    }
  }
}

#else
void Ground::drawDay() {

  glPushMatrix();
  glScalef(5.0f, 5.0f, 2.0f);
  drawGround();
  glPopMatrix();
}
#endif

void Ground::build() {

  Random random;

  for (int j=0; j<res+1; ++j) {

    float y = float(j)/float(res) * 2.0f - 1.0f;
    float py = y * size / 2.0f;
    float t = (float(j) / float(res));

    for (int i=0; i<res+1; ++i) {

      float pz = (random-0.5) * 0.04 * size;

      float x = float(i)/float(res) * 2.0f - 1.0f;
      float px = x * size / 2.0f;
      float s = (float(i) / float(res));

      int k = index(j,i);
      vertices[k] = Vec3f(px,py,pz);
      texcoords[k] = Vec2f(s,t);

      float r2 = (x*x+y*y);
      if (r2>1.0) r2 = 0.0;
      else r2 = 1.0-r2;
      colors[k] = Vec3f(r2, r2, r2);
    }
  }

  /* wrap edge */

  for (j=0; j<res; j++) {
    
    vertices[index(res,j)][2] = vertices[index(0,j)][2];
    vertices[index(j,res)][2] = vertices[index(j,0)][2];
  }

  vertices[index(res,res)][2] = vertices[index(0,0)][2];

  int step = size / float(res);

  for (j=0; j<res+1; ++j) {

    for (int i = 0; i<res+1; ++i) {

      Vec3f v1(0.0, 
	       step, 
	       vertices[wrapIndex(j+1, i)][2] - vertices[wrapIndex(j-1,i)][2]);
      Vec3f v2(step, 
	       0.0, 
	       vertices[wrapIndex(j, i+1)][2] - vertices[wrapIndex(j,i-1)][2]);

      Vec3f n = normalize(cross(v2,v1));

      normals[index(j,i)] = n;
    }
  }

  for (j=0; j<res; j++) {

    normals[index(j,res)] = normals[index(j,0)];
    normals[index(res,j)] = normals[index(0,j)];
  }

  normals[index(res,res)] = normals[index(0,0)];
}


void Ground::drawGround() {

  for (int j = 0; j<res; ++j) {

    glBegin(GL_TRIANGLE_STRIP);

    for (int i = 0; i<res+1; ++i) {

      int i1 = index(j+1,i);
      int i2 = index(j,i);

      texCoord(texcoords[i1]);
      normal(normals[i1]);
      vertex(vertices[i1]);

      texCoord(texcoords[i2]);
      normal(normals[i2]);
      vertex(vertices[i2]);
    }
    glEnd();
  }
}

void Ground::drawColoredGround() {

  glEnable(GL_COLOR_MATERIAL);

  for (int j = 0; j<res; ++j) {

    glBegin(GL_TRIANGLE_STRIP);

    for (int i = 0; i<res+1; ++i) {

      int i1 = index(j+1,i);
      int i2 = index(j,i);

      texCoord(texcoords[i1]);
      normal(normals[i1]);
      color(colors[i1]);
      vertex(vertices[i1]);

      texCoord(texcoords[i2]);
      normal(normals[i2]);
      color(colors[i2]);
      vertex(vertices[i2]);
    }
    glEnd();
  }
}


int Ground::getPolygonCount() {

  if (day) {
    return res * res * 2 * 9*9;
  } else {
    return res * res * 2;
  }
}
