#pragma warning( disable : 4786 )

#include "GLContext.h"

#include <util/util.h>


#include <strstream>
using std::istrstream;
using std::ostrstream;

GLContext::~GLContext() {}

GLContext::GLContext()
  : extension_string(0),

    active_texture_enum(GL_TEXTURE0_ARB),

    glMultiTexCoord1dARB(0),
    glMultiTexCoord1dvARB(0),
    glMultiTexCoord1fARB(0),
    glMultiTexCoord1fvARB(0),
    glMultiTexCoord1iARB(0),
    glMultiTexCoord1ivARB(0),
    glMultiTexCoord1sARB(0),
    glMultiTexCoord1svARB(0),

    glMultiTexCoord2dARB(0),
    glMultiTexCoord2dvARB(0),
    glMultiTexCoord2fARB(0),
    glMultiTexCoord2fvARB(0),
    glMultiTexCoord2iARB(0),
    glMultiTexCoord2ivARB(0),
    glMultiTexCoord2sARB(0),
    glMultiTexCoord2svARB(0),

    glMultiTexCoord3dARB(0),
    glMultiTexCoord3dvARB(0),
    glMultiTexCoord3fARB(0),
    glMultiTexCoord3fvARB(0),
    glMultiTexCoord3iARB(0),
    glMultiTexCoord3ivARB(0),
    glMultiTexCoord3sARB(0),
    glMultiTexCoord3svARB(0),

    glMultiTexCoord4dARB(0),
    glMultiTexCoord4dvARB(0),
    glMultiTexCoord4fARB(0),
    glMultiTexCoord4fvARB(0),
    glMultiTexCoord4iARB(0),
    glMultiTexCoord4ivARB(0),
    glMultiTexCoord4sARB(0),
    glMultiTexCoord4svARB(0),

    glBlendColorARB(0),

    glActiveTextureARB(0),
    glClientActiveTextureARB(0) {

}

void GLContext::init_extension_string() {

  const char* s = reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS));

  if (s==0) throw GLError("glGetString");

  istrstream in(s);

  while (!in.eof()) {

    string ext;
    in >> ext;
    extensions.insert(ext);
  }

#if 0
  {
    ostrstream out;
    for (Extensions::iterator i = extensions.begin();
	 i != extensions.end();
	 ++i) {

      out << *i << "\n";
    }
    out << '\000';
    char* s = out.str();
    showInfo(s);
    delete [] s;
  }
#endif
}


bool GLContext::isExtensionSupported(const string& ext) {

  Extensions::iterator i = extensions.find(ext);

  return (i!=extensions.end());
}


void GLContext::activeTexture(GLenum t) {

  if (t!=active_texture_enum) {

    active_texture_enum = t;
    if (glActiveTextureARB==0) 
      throw(GLUnsupported("glActiveTextureARB"));
    
    (*glActiveTextureARB)(t);
  }
}

void GLContext::clientActiveTexture(GLenum t) {

  if (glClientActiveTextureARB==0) 
    throw(GLUnsupported("glClientActiveTextureARB"));

  (*glClientActiveTextureARB)(t);
}


