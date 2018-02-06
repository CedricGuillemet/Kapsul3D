#ifndef Light_INCLUDED
#define Light_INCLUDED

#include <thigs/Vec3.h>
#include <thigs/Vec4.h>

struct Light {

  Light();
  ~Light();

  void apply();
  void disable();
  static void disableLighting();

  void setPosition(const Vec4<float>&);
  void setPosition(const Vec3<float>&);
  void setPosition(float x, float y, float z, float w=1.0);

  void setDirection(const Vec3<float>&);
  void setDirection(float x, float y, float z);

  void setAmbient(const Vec4<float>&);
  void setAmbient(float r, float g, float b, float a=1.0f);

  void setDiffuse(const Vec4<float>&);
  void setDiffuse(float r, float g, float b, float a=1.0f);

  void setSpecular(const Vec4<float>&);
  void setSpecular(float r, float g, float b, float a=1.0f);

  void setSpotExponent(float);
  void setSpotCutoff(float);
  void setConstantAttenuation(float);
  void setLinearAttenuation(float);
  void setQuadraticAttenuation(float);
  void setAttenuation(float constant, float linear, float quadratic);
  

  static void setLocalViewer(bool);
  static void setTwoSided(bool);
  static void setGlobalAmbient(const Vec4<float>&);

 private:

  void allocate();
  void free();

  static Vec4<float> global_ambient;
  static bool local_viewer;
  static bool two_sided;

  Vec4<float> position;
  Vec3<float> direction;
  Vec4<float> ambient;
  Vec4<float> diffuse;
  Vec4<float> specular;
  float spot_exponent;
  float spot_cutoff;
  float c_attenuation;
  float l_attenuation;
  float q_attenuation;

  static bool global_ambient_dirty;
  static bool local_viewer_dirty;
  static bool two_sided_dirty;

  bool position_dirty;
  bool direction_dirty;
  bool ambient_dirty;
  bool diffuse_dirty;
  bool specular_dirty;
  bool spot_exponent_dirty;
  bool spot_cutoff_dirty;
  bool c_attenuation_dirty;
  bool l_attenuation_dirty;
  bool q_attenuation_dirty;

  int index;

  static bool light_pool[8];
};

struct OutOfLights {};  // thrown if out of lights

#endif
