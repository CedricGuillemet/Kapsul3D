#include "Picture.h"

#include <thigs/thigs.h>

Picture::Picture(const Ptr<Texture>& t) 
  : texture(t), left(0.0f), right(1.0f), bottom(0.0f), top(1.0f) {}

void Picture::setPos(float l, float r, float b, float t) {

  left = l;
  right = r;
  bottom = b;
  top = t;
}

void Picture::draw(WeakPtr<GLContext>& context) {

  color(Vec4f(1.0f, 1.0f, 1.0f, 1.0f));

  if (texture) texture->apply(context);

  glBegin(GL_POLYGON);

  texCoord(Vec2f(0.0f, 0.0f));
  vertex(Vec2f(left, bottom));

  texCoord(Vec2f(1.0f, 0.0f));
  vertex(Vec2f(right, bottom));

  texCoord(Vec2f(1.0f, 1.0f));
  vertex(Vec2f(right, top));

  texCoord(Vec2f(0.0f, 1.0f));
  vertex(Vec2f(left, top));

  glEnd();
}
