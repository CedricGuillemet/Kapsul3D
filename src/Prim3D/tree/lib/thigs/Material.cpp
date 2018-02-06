#include "Material.h"

#include <windows.h>
#include <gl/GL.h>

#pragma warning( disable : 4305 ) 


Material::Material() 
  : front_ambient(Vec4<float>(0.2, 0.2, 0.2, 1.0)),
    front_diffuse(Vec4<float>(0.8, 0.8, 0.8, 1.0)),
    front_specular(Vec4<float>(0.0, 0.0, 0.0, 1.0)),
    front_emission(Vec4<float>(0.0, 0.0, 0.0, 1.0)),
    front_shininess(0),
    back_ambient(Vec4<float>(0.2, 0.2, 0.2, 1.0)),
    back_diffuse(Vec4<float>(0.8, 0.8, 0.8, 1.0)),
    back_specular(Vec4<float>(0.0, 0.0, 0.0, 1.0)),
    back_emission(Vec4<float>(0.0, 0.0, 0.0, 1.0)),
    back_shininess(0),
    side(FRONT) {
}
		   



Material* Material::current_material = 0;

void Material::apply() {

  if (current_material == this) return;

  current_material = this;

  switch (side) {

  case FRONT:
    glMaterialfv(GL_FRONT, GL_AMBIENT, &front_ambient[0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &front_diffuse[0]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, &front_specular[0]);
    glMaterialfv(GL_FRONT, GL_EMISSION, &front_emission[0]);
    glMaterialf(GL_FRONT, GL_SHININESS, front_shininess);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, false);
    break;

  case BACK:
    glMaterialfv(GL_BACK, GL_AMBIENT, &back_ambient[0]);
    glMaterialfv(GL_BACK, GL_DIFFUSE, &back_diffuse[0]);
    glMaterialfv(GL_BACK, GL_SPECULAR, &back_specular[0]);
    glMaterialfv(GL_BACK, GL_EMISSION, &back_emission[0]);
    glMaterialf(GL_BACK, GL_SHININESS, back_shininess);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, false);
    break;

  case BOTH:
    glMaterialfv(GL_FRONT, GL_AMBIENT, &front_ambient[0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &front_diffuse[0]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, &front_specular[0]);
    glMaterialfv(GL_FRONT, GL_EMISSION, &front_emission[0]);
    glMaterialf(GL_FRONT, GL_SHININESS, front_shininess);
    glMaterialfv(GL_BACK, GL_AMBIENT, &back_ambient[0]);
    glMaterialfv(GL_BACK, GL_DIFFUSE, &back_diffuse[0]);
    glMaterialfv(GL_BACK, GL_SPECULAR, &back_specular[0]);
    glMaterialfv(GL_BACK, GL_EMISSION, &back_emission[0]);
    glMaterialf(GL_BACK, GL_SHININESS, back_shininess);
    glDisable(GL_CULL_FACE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, true);
    break;
  }
}


