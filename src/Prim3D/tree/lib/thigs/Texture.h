#ifndef Texture_INCLUDED
#define Texture_INCLUDED

#pragma warning( disable : 4786 )

#include <windows.h>
#include <GL/gl.h>

#include <list>
using std::list;

#include <ptr/Ptr.h>
#include <thigs/Image.h>
#include <thigs/GLContext.h>
#include <window/GLWindow.h>

struct Texture {

  Texture(const Ptr<Image>&);
  ~Texture();

  void repeatHorizontal(bool r) {repeat_horizontal = r;}
  void repeatVertical(bool r) {repeat_vertical = r;}

  enum GenMode {NONE, SPHERE, DP};
  void genMode(GenMode);

  enum EnvMode {MODULATE, DECAL, BLEND, REPLACE};
  void envMode(EnvMode);

  void apply(WeakPtr<GLContext>&, GLenum target=GL_TEXTURE0_ARB);
  static void disable(WeakPtr<GLContext>&, GLenum target=GL_TEXTURE0_ARB);
  static void disableTextures(WeakPtr<GLContext>&);

 private:

  bool repeat_horizontal;
  bool repeat_vertical;

  typedef Ptr<Image> ImagePtr;
  typedef list<ImagePtr> Images;
  Images images;

  EnvMode env_mode;
  GenMode gen_mode;
  unsigned int texture_name;

  // should be indexed by context

  static bool enabled[32];
  static unsigned int current_textures[32];
  static EnvMode current_env_modes[32];
  static GenMode current_gen_modes[32];
  static int max_texture_targets;
};

#endif

