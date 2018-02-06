#ifndef Ground_INCLUDED
#define Ground_INCLUDED

#include <windows.h>
#include <ptr/Ptr.h>

#include <thigs/Texture.h>
#include <thigs/Vec3.h>
#include <thigs/Material.h>
#include <thigs/GLContext.h>

struct Ground {

  Ground(float size);
  ~Ground();

  void setTexture(const Ptr<Texture>&);
  void setDay(bool);

  void draw(WeakPtr<GLContext>&);
  void drawNight();
  void drawDay();
  void drawColoredGround();
  void drawGround();
  void build();

  int getPolygonCount();

  float size;
  int res;

  bool day;

  Material material;
  Ptr<Texture> texture;

  Vec3f* vertices;
  Vec3f* normals;
  Vec2f* texcoords;
  Vec3f* colors; // for dieoff

  inline int index(int y, int x) {
    return y*(res+1)+x;
  }
    
  inline int wrapIndex(int y, int x) {
    while(y>res) y -= res;
    while(y<0) y += res;

    while(x>res) x -= res;
    while(x<0) x += res;

    return y*(res+1)+x;
  }
    
};

#endif
