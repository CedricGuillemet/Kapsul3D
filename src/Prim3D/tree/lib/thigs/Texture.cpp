#include "Texture.h"

#include <strstream>
using std::istrstream;
using std::ostrstream;

#include <util/util.h>


unsigned int Texture::current_textures[32] = {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
};

bool Texture::enabled[32] = {
  false, false, false, false, false, false, false, false, 
  false, false, false, false, false, false, false, false, 
  false, false, false, false, false, false, false, false, 
  false, false, false, false, false, false, false, false, 
};

Texture::GenMode Texture::current_gen_modes[32] = {
  Texture::NONE, Texture::NONE, Texture::NONE, Texture::NONE,
  Texture::NONE, Texture::NONE, Texture::NONE, Texture::NONE,
  Texture::NONE, Texture::NONE, Texture::NONE, Texture::NONE,
  Texture::NONE, Texture::NONE, Texture::NONE, Texture::NONE,
  Texture::NONE, Texture::NONE, Texture::NONE, Texture::NONE,
  Texture::NONE, Texture::NONE, Texture::NONE, Texture::NONE,
  Texture::NONE, Texture::NONE, Texture::NONE, Texture::NONE,
  Texture::NONE, Texture::NONE, Texture::NONE, Texture::NONE,
};

Texture::EnvMode Texture::current_env_modes[32] = {
  Texture::MODULATE, Texture::MODULATE, Texture::MODULATE, Texture::MODULATE,
  Texture::MODULATE, Texture::MODULATE, Texture::MODULATE, Texture::MODULATE,
  Texture::MODULATE, Texture::MODULATE, Texture::MODULATE, Texture::MODULATE,
  Texture::MODULATE, Texture::MODULATE, Texture::MODULATE, Texture::MODULATE,
  Texture::MODULATE, Texture::MODULATE, Texture::MODULATE, Texture::MODULATE,
  Texture::MODULATE, Texture::MODULATE, Texture::MODULATE, Texture::MODULATE,
  Texture::MODULATE, Texture::MODULATE, Texture::MODULATE, Texture::MODULATE,
  Texture::MODULATE, Texture::MODULATE, Texture::MODULATE, Texture::MODULATE,
};


int Texture::max_texture_targets=-1;


Texture::Texture(const Ptr<Image>& i) 
  : texture_name(0), 
    repeat_horizontal(false),
    repeat_vertical(false),
    gen_mode(NONE),
    env_mode(MODULATE) {

  Ptr<Image> image(i->powerOfTwo());

  while(image) {

    images.push_back(image);
    image = image->mip();
  }

}


Texture::~Texture() {

  // XXX assumes valid OpenGL context

  if (texture_name!=0) {
    glDeleteTextures(1, &texture_name);
  }
}

void Texture::envMode(EnvMode e) {

  env_mode = e;
}

void Texture::genMode(GenMode e) {

  gen_mode = e;
}

void Texture::disable(WeakPtr<GLContext>& context, GLenum target) {

  int t = target-GL_TEXTURE0_ARB;
  if (t<0 || t>=max_texture_targets) {
    ostrstream out;
    out << "GL_TEXTURE" << t << "_ARB" << '\000';
    char* s = out.str();
    string message(s);
    delete [] s;    
    throw GLUnsupported(message);
  }

  context->activeTexture(target);
  glDisable(GL_TEXTURE_2D);
  enabled[t] = false;
}

void Texture::disableTextures(WeakPtr<GLContext>& context) {

  // max_texture_targets may be -1, but that means no textures are
  // enabled yet anyway

  for (int i=0; i<max_texture_targets; ++i) {

    if (enabled[i]) {
      context->activeTexture(GL_TEXTURE0_ARB+i);
      glDisable(GL_TEXTURE_2D);
      enabled[i] = false;
    }
  }
}


void Texture::apply(WeakPtr<GLContext>& context, GLenum target) {

  checkGLError("entering Texture::apply");

  if (max_texture_targets==-1) {
    glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB, &max_texture_targets);
  }
  int e = glGetError();

  if (e==GL_INVALID_ENUM) {
    max_texture_targets=1;
  } else {
    assert(e==0);
  }

  int t = target-GL_TEXTURE0_ARB;
  if (t<0 || t>=max_texture_targets) {
    ostrstream out;
    out << "Unsupported: " << "GL_TEXTURE" << t << "_ARB" << '\000';
    char* s = out.str();
    string message(s);
    delete [] s;
    throw GLUnsupported(message);
  }

  context->activeTexture(target);

  if (!enabled[t]) {

    glEnable(GL_TEXTURE_2D);
    enabled[t] = true;
  }

  if (texture_name!=0) {

    if (current_textures[t]==texture_name) return;

    glBindTexture(GL_TEXTURE_2D, texture_name);
    checkGLError("glBindTexture");
    current_textures[t] = texture_name;

  } else {

    glGenTextures(1, &texture_name);
    checkGLError("glGenTextures");
    glBindTexture(GL_TEXTURE_2D, texture_name);
    checkGLError("glBindTexture");
    current_textures[t] = texture_name;

    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

    int j=0;
    for (Images::const_iterator i = images.begin();
	 i != images.end();
	 ++i, ++j) {

      glTexImage2D(GL_TEXTURE_2D, j, GL_RGBA8, 
		   (*i)->width(),
		   (*i)->height(),
		   0,
		   GL_RGBA, GL_UNSIGNED_BYTE, (**i)[0]);

      checkGLError("glTexImage2D");
    }


    glTexParameterf(GL_TEXTURE_2D, 
		    GL_TEXTURE_WRAP_S, 
		    repeat_horizontal?GL_REPEAT:GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, 
		    GL_TEXTURE_WRAP_T, 
		    repeat_vertical?GL_REPEAT:GL_CLAMP);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    checkGLError("glTexParameterf");

  }

  if (env_mode != current_env_modes[t]) {

    current_env_modes[t] = env_mode;

    switch(env_mode) {

    case MODULATE:
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
      break;

    case DECAL:
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
      break;

    case BLEND:
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
      break;

    case REPLACE:
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
      break;
    }
    checkGLError("glTexEnvf");
  }

  if (gen_mode != current_gen_modes[t]) {

    current_gen_modes[t] = gen_mode;

    switch(gen_mode) {

    case NONE:
      glDisable(GL_TEXTURE_GEN_S);
      glDisable(GL_TEXTURE_GEN_T);
      glDisable(GL_TEXTURE_GEN_R);
      break;

    case SPHERE:
      glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
      checkGLError("glTexGeni");
      glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
      checkGLError("glTexGeni");
      glEnable(GL_TEXTURE_GEN_S);
      glEnable(GL_TEXTURE_GEN_T);
      glDisable(GL_TEXTURE_GEN_R);
      break;

    case DP:
      glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_NV);
      checkGLError("glTexGeni(GL_S,REFLECTION)");
      glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_NV);
      checkGLError("glTexGeni(GL_T,REFLECTION)");
      glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_NV);
      checkGLError("glTexGeni(GL_R,REFLECTION)");
      glEnable(GL_TEXTURE_GEN_S);
      glEnable(GL_TEXTURE_GEN_T);
      glEnable(GL_TEXTURE_GEN_R);
      break;
    }
  }
}
