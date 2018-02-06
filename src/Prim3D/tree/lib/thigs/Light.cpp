#include "Light.h"

#include <windows.h>
#include <gl/GL.h>

static const int num_lights = 8;

bool Light::global_ambient_dirty(false);
bool Light::local_viewer_dirty(false);
bool Light::two_sided_dirty(false);

Vec4<float> Light::global_ambient;
bool Light::local_viewer;
bool Light::two_sided;

static GLenum light_enum[8] = {
  GL_LIGHT0,
  GL_LIGHT1,
  GL_LIGHT2,
  GL_LIGHT3,
  GL_LIGHT4,
  GL_LIGHT5,
  GL_LIGHT6,
  GL_LIGHT7
};
  

bool Light::light_pool[8] = {
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false
};


Light::Light()
  : index(-1),
    position_dirty(false),
    direction_dirty(false),
    ambient_dirty(false),
    diffuse_dirty(false),
    specular_dirty(false),
    spot_exponent_dirty(false),
    spot_cutoff_dirty(false),
    c_attenuation_dirty(false),
    l_attenuation_dirty(false),
    q_attenuation_dirty(false) {
}

void Light::allocate() {

  if (index==-1) {
    int i(0);
    while ((i<num_lights) && (light_pool[i]==true)) ++i;
    if (i==num_lights) throw OutOfLights();
    index = i;
    light_pool[i] = true;
    glEnable(light_enum[index]);
  }
}

void Light::free() {

  if (index != -1) {
    light_pool[index] = false;
    glDisable(light_enum[index]);
    index = -1;
  }
}

Light::~Light() {

  free();
}


void Light::apply() {

  glEnable(GL_LIGHTING);
  allocate();

  if (local_viewer_dirty) {
    local_viewer_dirty = false;
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, local_viewer?1:0);
  }

  if (two_sided_dirty) {
    two_sided_dirty = false;
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, two_sided?1:0);
  }

  if (position_dirty) {
    position_dirty = false;
    glLightfv(light_enum[index], GL_POSITION, &position[0]);
  }
  if (direction_dirty) {
    direction_dirty = false;
    glLightfv(light_enum[index], GL_SPOT_DIRECTION, &direction[0]);
  }
  if (ambient_dirty) {
    ambient_dirty = false;
    glLightfv(light_enum[index], GL_AMBIENT, &ambient[0]);
  }
  if (diffuse_dirty) {
    diffuse_dirty = false;
    glLightfv(light_enum[index], GL_DIFFUSE, &diffuse[0]);
  }
  if (specular_dirty) {
    specular_dirty = false;
    glLightfv(light_enum[index], GL_SPECULAR, &specular[0]);
  }
  if (spot_exponent_dirty) {
    spot_exponent_dirty = false;
    glLightf(light_enum[index], GL_SPOT_EXPONENT, spot_exponent);
  }
  if (spot_cutoff_dirty) {
    spot_cutoff_dirty = false;
    glLightf(light_enum[index], GL_SPOT_CUTOFF, spot_cutoff);
  }
  if (c_attenuation_dirty) {
    c_attenuation_dirty = false;
    glLightf(light_enum[index], GL_CONSTANT_ATTENUATION, c_attenuation);
  }
  if (l_attenuation_dirty) {
    l_attenuation_dirty = false;
    glLightf(light_enum[index], GL_LINEAR_ATTENUATION, l_attenuation);
  }
  if (q_attenuation_dirty) {
    q_attenuation_dirty = false;
    glLightf(light_enum[index], GL_QUADRATIC_ATTENUATION, q_attenuation);
  }
  if (global_ambient_dirty) {
    global_ambient_dirty = false;
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, &ambient[0]);
  }
}

void Light::setPosition(const Vec4<float>& p) {
  position_dirty = true;
  position = p;
}

void Light::setPosition(const Vec3<float>& p) {
  position_dirty = true;
  position = Vec4<float>(p[0], p[1], p[2], 1.0);
}

void Light::setPosition(float x, float y, float z, float w) {
  position_dirty = true;
  position = Vec4<float>(x, y, z, w);
}

void Light::setDirection(const Vec3<float>& d) {
  direction_dirty = true;
  direction = d;
}

void Light::setDirection(float x, float y, float z) {
  direction_dirty = true;
  direction = Vec3<float>(x, y, z);
}

void Light::setAmbient(const Vec4<float>& a) {

  ambient_dirty = true;
  ambient = a;
}

void Light::setAmbient(float r, float g, float b, float a) {

  ambient_dirty = true;
  ambient = Vec4<float>(r,g,b,a);
}

void Light::setDiffuse(const Vec4<float>& d) {

  diffuse_dirty = true;
  diffuse = d;
}

void Light::setDiffuse(float r, float g, float b, float a) {

  diffuse_dirty = true;
  diffuse = Vec4<float>(r,g,b,a);
}

void Light::setSpecular(const Vec4<float>& s) {

  specular_dirty = true;
  specular = s;
}

void Light::setSpecular(float r, float g, float b, float a) {

  specular_dirty = true;
  specular = Vec4<float>(r,g,b,a);
}


void Light::setSpotExponent(float e) {
  assert(e>=0 && e<=128.0);
  spot_exponent_dirty = true;
  spot_exponent = e;
}


void Light::setSpotCutoff(float c) {
  assert((c==180) || (c>=0) && (c<=90));
  spot_cutoff_dirty = true;
  spot_cutoff = c;
}


void Light::setConstantAttenuation(float c) {
  c_attenuation_dirty = true;
  c_attenuation = c;
}

void Light::setLinearAttenuation(float l) {
  l_attenuation_dirty = true;
  l_attenuation = l;
}

void Light::setQuadraticAttenuation(float q) {
  q_attenuation_dirty = true;
  q_attenuation = q;
}


void Light::setAttenuation(float c, float l, float q) {

  setConstantAttenuation(c);
  setLinearAttenuation(l);
  setQuadraticAttenuation(q);
}

void Light::setLocalViewer(bool l) {
  local_viewer_dirty = true;
  local_viewer = l;
}


void Light::setTwoSided(bool t) {
  two_sided_dirty = true;
  two_sided = t;
}


void Light::setGlobalAmbient(const Vec4<float>& a) {

  global_ambient_dirty = true;
  global_ambient = a;
}


void Light::disable() {
  free();
}


void Light::disableLighting() {

  glDisable(GL_LIGHTING);
}
