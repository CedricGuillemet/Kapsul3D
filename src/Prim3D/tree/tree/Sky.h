#ifndef Sky_INCLUDED
#define Sky_INCLUDED

#include <windows.h>
#include <ptr/Ptr.h>

#include <thigs/Vec2.h>
#include <thigs/Vec3.h>

#include <thigs/Texture.h>
#include <thigs/GLContext.h>

struct Sky {

  Sky();
  ~Sky();

  void setDay(bool);
  void setNightTexture(const Ptr<Texture>&);
  void setDayTexture(const Ptr<Texture>&);

  void draw(WeakPtr<GLContext>&);

  int facets;
  float radius;
  float height;

  Vec3<float>* vertices;
  Vec2<float>* tex_coords;

  Ptr<Texture> night_texture;
  Ptr<Texture> day_texture;

  bool day;

};

#endif
