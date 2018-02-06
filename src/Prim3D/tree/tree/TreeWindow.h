#ifndef TreeWindow_INCLUDED
#define TreeWindow_INCLUDED

#include <windows.h>

#include <ptr/Ptr.h>
#include <GL/gl.h>

#include <window/GLWindow.h>
#include <window/WindowClass.h>

#include <thigs/Light.h>
#include <thigs/Image.h>
#include <thigs/Texture.h>

#include <thidget/Overlay.h>
#include <thidget/Slider.h>
#include <thidget/Picture.h>

#include <time.h>

#include "Tree.h"
#include "Sky.h"
#include "Ground.h"
#include "Firefly.h"

static const int max_lights = 8;

struct TreePos {

  TreePos(float nx, float ny, float a) : angle(a), x(nx), y(ny) {}

  float x;
  float y;
  float angle;
  Firefly fireflies[max_lights];
};


struct TreeWindow : GLWindow {

  TreeWindow(const Ptr<WindowClass>&, const string& app_name, bool fullscreen);

  ~TreeWindow();

  virtual LRESULT CALLBACK callback(HWND, UINT, WPARAM, LPARAM);

  virtual void mouse(int x, int y);
  virtual void leftMouse(bool);
  virtual void rightMouse(bool);
  virtual void init();

  void setDay();
  void setNight(int fireflies);

  Void setThreshhold(const float&);

  void setOneFrame();

  void setBench(bool, int, bool, int);

  void reshapeViewport(GLsizei width, GLsizei height);
  Void draw();

  WeakPtr<GLContext> context;

private:

  float threshhold;

  bool one_frame;

  bool day;

  Light daylight;

  int light_count;
  Light lights[max_lights];
  Tree tree;
  Sky sky;
  Ground ground;
  float ground_size;
  Overlay overlay;
  bool overlay_focus;
  Ptr<Slider> leaf_size_slider;
  Ptr<Slider> branch_size_slider;
  Ptr<Slider> threshhold_slider;
  Ptr<Slider> twist_slider;
  Ptr<Slider> branch_slider;
  Ptr<Slider> branch_bias_slider;
  Ptr<Slider> branch_noise_slider;

  int leaf_texture_index;

  vector< Ptr<Texture> > leaf_textures;
  vector< Ptr<Texture> > leaf_back_textures;

  Ptr<Texture> bark_texture;
  Ptr<Texture> sky_day_texture;
  Ptr<Texture> sky_night_texture;
  Ptr<Texture> ground_texture;

  Ptr<Texture> label_depth_texture;
  Ptr<Texture> label_balance_texture;
  Ptr<Texture> label_twist_texture;
  Ptr<Texture> label_spread_texture;
  Ptr<Texture> label_leaf_size_texture;
  Ptr<Texture> label_branch_size_texture;
  Ptr<Texture> label_character_texture;
  Ptr<Texture> logo_texture;

  Ptr<Picture> depth_picture;
  Ptr<Picture> balance_picture;
  Ptr<Picture> twist_picture;
  Ptr<Picture> spread_picture;
  Ptr<Picture> leaf_size_picture;
  Ptr<Picture> branch_size_picture;
  Ptr<Picture> character_picture;
  Ptr<Picture> logo_picture;


  Thunk0<> task;

  int x, y;
  bool left_mouse;

  bool forward, backward, up, down, left, right;

  Vec3<float> eye;
  float heading, pitch;
  float dh, dp;

  DWORD last_t;
  float dt; // in seconds
  float velocity;

  int width, height;

  bool overlay_flag;
  bool wireframe_flag;

  int time_frames;
  int frame_count;
  DWORD last_time;
  int elapsed;

  bool test_flag;
  bool fill_test;
  bool tl_test;
  int framecounter;
  double Timer;

  clock_t start_timer, end_timer;

  Void tick();

  typedef vector<TreePos> TreePoses;
  TreePoses tree_poses;
  bool addTree();
  void subtractTree();

 public:

  void sendResults();
  void getFillPath();
  void getTLPath();
};

#endif



