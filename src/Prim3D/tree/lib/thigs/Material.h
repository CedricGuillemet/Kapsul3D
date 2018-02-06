#ifndef Material_INCLUDED
#define Material_INCLUDED

#include <thigs/Vec4.h>

struct Material {

  Material();

  enum Side {FRONT, BACK, BOTH} side;

  Vec4<float> front_ambient;
  Vec4<float> front_diffuse;
  Vec4<float> front_specular;
  Vec4<float> front_emission;
  float front_shininess;

  Vec4<float> back_ambient;
  Vec4<float> back_diffuse;
  Vec4<float> back_specular;
  Vec4<float> back_emission;
  float back_shininess;

  void apply();

  static Material* current_material;
};

#endif
