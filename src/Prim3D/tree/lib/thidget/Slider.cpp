#include "Slider.h"

#pragma warning( disable : 4305 ) 


Slider::Slider(float mn, float mx, float init) 
  : minimum(mn), maximum(mx), value(init), mouse_down(false) {

  rod_color = Vec3<float>(0.2, 0.1, 0.8);
  knob_color = Vec3<float>(1.0, 0.2, 0.4);
  build_colors();
}

static int rod_geom[6][2] = {
  {4, 7},
  {4, 9},
  {2, 9},
  {4, 11},
  {2, 11},
  {4, 13}
};

void Slider::build_rod() {


  float scale = (top-bottom)/20.0;

  for (int i=0; i<6; ++i) {

    float x = rod_geom[i][0]*scale;
    float y = rod_geom[i][1]*scale + bottom;

    rod_vertices[i] = Vec2<float>(x+left, y);
    rod_vertices[i+6] = Vec2<float>(right-x, y);

  };


}

void Slider::build_colors() {

  {
    Vec3<float> white(1.0, 1.0, 1.0);
    Vec3<float> dark = rod_color / 3.0f;
    Vec3<float> medium = rod_color;

    rod_colors[0] = dark;
    rod_colors[1] = medium;
    rod_colors[2] = dark;
    rod_colors[3] = white;
    rod_colors[4] = dark;
    rod_colors[5] = medium;

    rod_colors[6] = dark;
    rod_colors[7] = medium;
    rod_colors[8] = medium;
    rod_colors[9] = white;
    rod_colors[10] = medium;
    rod_colors[11] = medium;
  }

  {
    Vec3<float> white(1.0, 1.0, 1.0);
    Vec3<float> medium_dark = knob_color / 2.0f;
    Vec3<float> dark = knob_color / 3.0f;
    Vec3<float> medium = knob_color;
    Vec3<float> light = (white + knob_color)/2.0f;


    knob_colors[0] = dark;
    knob_colors[1] = light;
    knob_colors[2] = white;
    knob_colors[3] = medium_dark;
    knob_colors[4] = medium;
  }
}


static int knob_polys[5][4] = {
  {0, 1, 3, 2},
  {2, 3, 5, 4},
  {4, 5, 7, 6},
  {6, 7, 1, 0},
  {1, 3, 5, 7}
};

static int knob_geom[8][2] = {
  {0, 2},
  {0, 6},
  {-4, 10},
  {-2, 10},
  {0, 18},
  {0, 14},
  {4, 10},
  {2, 10}
};


void Slider::build_knob() {

  float scale = (top-bottom)/20.0;
  float length = (right-left)/scale;

  float n = (value - minimum)/(maximum-minimum);
  knob_pos = 4 + (length-8) * n;

  for (int i=0; i<8; ++i) {

    float x = (knob_geom[i][0]+knob_pos)*scale+left;
    float y = knob_geom[i][1]*scale+bottom;
    knob_vertices[i] = Vec2<float>(x, y);

  }
}


void Slider::setPos(float l, float r, float b, float t) {

  left = l;
  right = r;
  bottom = b; 
  top = t;

  build_knob();
  build_rod();
}


void Slider::setThunk(const Thunk1<float>& t) {

  thunk = t;
  thunk(value);
}


void Slider::draw(WeakPtr<GLContext>&) {

  //  if (focus==false) return;

  glBegin(GL_TRIANGLE_STRIP);
  for (int i=0; i<6; ++i) {

    color(rod_colors[i]);
    vertex(rod_vertices[i]);
  }
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);
  for (int j=6; j<12; ++j) {

    color(rod_colors[j]);
    vertex(rod_vertices[j]);
  }
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);

  color(rod_colors[0]);
  vertex(rod_vertices[0]);

  color(rod_colors[6]);
  vertex(rod_vertices[6]);

  color(rod_colors[1]);
  vertex(rod_vertices[1]);

  color(rod_colors[7]);
  vertex(rod_vertices[7]);

  color(rod_colors[3]);
  vertex(rod_vertices[3]);
  
  color(rod_colors[9]);
  vertex(rod_vertices[9]);

  color(rod_colors[5]);
  vertex(rod_vertices[5]);

  color(rod_colors[11]);
  vertex(rod_vertices[11]);

  glEnd();

  glBegin(GL_QUADS);
  for (int k=0; k<5; ++k) {

    color(knob_colors[k]);
    for (int m=0; m<4; ++m) {
      vertex(knob_vertices[knob_polys[k][m]]);
    }
  }
  glEnd();
}

  
bool Slider::mouse(float x, float y) {

  if (mouse_down) {

    float scale = (top-bottom)/20.0;

    float n = (x-left-4*scale) / (right-left-8*scale);
    value = n * (maximum-minimum) + minimum;
    if (value>maximum) value = maximum;
    if (value<minimum) value = minimum;
    thunk(value);
    build_knob();
    return true;

  }

  focus = ((x>left) && 
	   (x<right) && 
	   (y>bottom) && 
	   (y<top));

  return focus;
}


void Slider::click(bool state) {

  mouse_down = state;
}
