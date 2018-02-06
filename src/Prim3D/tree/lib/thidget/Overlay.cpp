#include "Overlay.h"


Overlay::Overlay() : current_thidget(-1) {}

void Overlay::addThidget(const Ptr<Thidget>& thidget) {

  thidgets.push_back(thidget);
}

void Overlay::setOrtho(int w, int h, float l, float r, float b, float t) {

  width = w;
  height = h;
  left = l;
  right = r;
  bottom = b;
  top = t;
}

void Overlay::click(bool state) {

  assert (current_thidget!=-1);

  thidgets[current_thidget]->click(state);
}

bool Overlay::mouse(int x, int y) {

  float local_x = float(x)/float(width) * (right-left) + left;
  float local_y = (1.0-float(y)/float(height)) * (top-bottom) + bottom;

  if ((current_thidget != -1) &&
      (thidgets[current_thidget]->mouse(local_x, local_y))) {
    return true;
  }

  current_thidget = -1;

  for (int i = 0; i<thidgets.size(); ++i) {

    if (thidgets[i]->mouse(local_x, local_y)) {
      current_thidget = i;
      return true;
    }
  }
  return false;
}


void Overlay::draw(WeakPtr<GLContext>& context) {

  if (thidgets.size()==0) return;

  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_CULL_FACE);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(left, right, bottom, top, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  for (Thidgets::iterator i=thidgets.begin();
       i != thidgets.end();
       ++i) {

    (*i)->draw(context);
  }

  glDisable(GL_BLEND);

}
