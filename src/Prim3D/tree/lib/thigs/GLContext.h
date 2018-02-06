#ifndef GLContext_INCLUDED
#define GLContext_INCLUDED

#ifdef _WIN32
#include <windows.h>
#endif

#include <set>
using std::set;

#include <string>
using std::string;

#include <thigs/Vec2.h>
#include <thigs/Vec3.h>
#include <thigs/Vec4.h>

#pragma warning( disable : 4786 )

#include <GL/gl.h>

struct GLContext {

  GLContext();
  virtual ~GLContext();

  virtual void grab() = 0;
  virtual void release() = 0;
  virtual void swapBuffers() = 0;

  bool isExtensionSupported(const string&);

 private:

  const char* extension_string;
  typedef set<string> Extensions;
  Extensions extensions;

 protected:

  /* to be called by implementation's constructor after a context has
     been built */

  void init_extension_string();

  /* to be initialized by implementation */

  PFNGLMULTITEXCOORD1DARBPROC  glMultiTexCoord1dARB;
  PFNGLMULTITEXCOORD1DVARBPROC glMultiTexCoord1dvARB;
  PFNGLMULTITEXCOORD1FARBPROC  glMultiTexCoord1fARB;
  PFNGLMULTITEXCOORD1FVARBPROC glMultiTexCoord1fvARB;
  PFNGLMULTITEXCOORD1IARBPROC  glMultiTexCoord1iARB;
  PFNGLMULTITEXCOORD1IVARBPROC glMultiTexCoord1ivARB;
  PFNGLMULTITEXCOORD1SARBPROC  glMultiTexCoord1sARB;
  PFNGLMULTITEXCOORD1SVARBPROC glMultiTexCoord1svARB;

  PFNGLMULTITEXCOORD2DARBPROC  glMultiTexCoord2dARB;
  PFNGLMULTITEXCOORD2DVARBPROC glMultiTexCoord2dvARB;
  PFNGLMULTITEXCOORD2FARBPROC  glMultiTexCoord2fARB;
  PFNGLMULTITEXCOORD2FVARBPROC glMultiTexCoord2fvARB;
  PFNGLMULTITEXCOORD2IARBPROC  glMultiTexCoord2iARB;
  PFNGLMULTITEXCOORD2IVARBPROC glMultiTexCoord2ivARB;
  PFNGLMULTITEXCOORD2SARBPROC  glMultiTexCoord2sARB;
  PFNGLMULTITEXCOORD2SVARBPROC glMultiTexCoord2svARB;

  PFNGLMULTITEXCOORD3DARBPROC  glMultiTexCoord3dARB;
  PFNGLMULTITEXCOORD3DVARBPROC glMultiTexCoord3dvARB;
  PFNGLMULTITEXCOORD3FARBPROC  glMultiTexCoord3fARB;
  PFNGLMULTITEXCOORD3FVARBPROC glMultiTexCoord3fvARB;
  PFNGLMULTITEXCOORD3IARBPROC  glMultiTexCoord3iARB;
  PFNGLMULTITEXCOORD3IVARBPROC glMultiTexCoord3ivARB;
  PFNGLMULTITEXCOORD3SARBPROC  glMultiTexCoord3sARB;
  PFNGLMULTITEXCOORD3SVARBPROC glMultiTexCoord3svARB;

  PFNGLMULTITEXCOORD4DARBPROC  glMultiTexCoord4dARB;
  PFNGLMULTITEXCOORD4DVARBPROC glMultiTexCoord4dvARB;
  PFNGLMULTITEXCOORD4FARBPROC  glMultiTexCoord4fARB;
  PFNGLMULTITEXCOORD4FVARBPROC glMultiTexCoord4fvARB;
  PFNGLMULTITEXCOORD4IARBPROC  glMultiTexCoord4iARB;
  PFNGLMULTITEXCOORD4IVARBPROC glMultiTexCoord4ivARB;
  PFNGLMULTITEXCOORD4SARBPROC  glMultiTexCoord4sARB;
  PFNGLMULTITEXCOORD4SVARBPROC glMultiTexCoord4svARB;

  PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
  PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB;

  PFNGLBLENDCOLOREXTPROC glBlendColorARB;

 public:

  inline void multiTexCoord(GLenum t, double c1) {
    (*glMultiTexCoord1dARB)(t, c1);}
  inline void multiTexCoord(GLenum t, float c1) {
    (*glMultiTexCoord1fARB)(t, c1);}
  inline void multiTexCoord(GLenum t, int c1) {
    (*glMultiTexCoord1iARB)(t, c1);}
  inline void multiTexCoord(GLenum t, short c1) {
    (*glMultiTexCoord1sARB)(t, c1);}

  inline void multiTexCoord(GLenum t, double c1, double c2) {
    (*glMultiTexCoord2dARB)(t, c1, c2);}
  inline void multiTexCoord(GLenum t, float c1, float c2) {
    (*glMultiTexCoord2fARB)(t, c1, c2);}
  inline void multiTexCoord(GLenum t, int c1, int c2) {
    (*glMultiTexCoord2iARB)(t, c1, c2);}
  inline void multiTexCoord(GLenum t, short c1, short c2) {
    (*glMultiTexCoord2sARB)(t, c1, c2);}

  inline void multiTexCoord(GLenum t, double c1, double c2, double c3) {
    (*glMultiTexCoord3dARB)(t, c1, c2, c3);}
  inline void multiTexCoord(GLenum t, float c1, float c2, float c3) {
    (*glMultiTexCoord3fARB)(t, c1, c2, c3);}
  inline void multiTexCoord(GLenum t, int c1, int c2, int c3) {
    (*glMultiTexCoord3iARB)(t, c1, c2, c3);}
  inline void multiTexCoord(GLenum t, short c1, short c2, short c3) {
    (*glMultiTexCoord3sARB)(t, c1, c2, c3);}

  inline void multiTexCoord(GLenum t, double c1, double c2, double c3, double c4) {
    (*glMultiTexCoord4dARB)(t, c1, c2, c3, c4);}
  inline void multiTexCoord(GLenum t, float c1, float c2, float c3, float c4) {
    (*glMultiTexCoord4fARB)(t, c1, c2, c3, c4);}
  inline void multiTexCoord(GLenum t, int c1, int c2, int c3, int c4) {
    (*glMultiTexCoord4iARB)(t, c1, c2, c3, c4);}
  inline void multiTexCoord(GLenum t, short c1, short c2, short c3, short c4) {
    (*glMultiTexCoord4sARB)(t, c1, c2, c3, c4);
  }

  inline void multiTexCoord(GLenum t, const Vec2d& v) {
    (*glMultiTexCoord2dvARB)(t, &v[0]);}
  inline void multiTexCoord(GLenum t, const Vec2f& v) {
    (*glMultiTexCoord2fvARB)(t, &v[0]);}
  inline void multiTexCoord(GLenum t, const Vec2s& v) {
    (*glMultiTexCoord2svARB)(t, &v[0]);}
  inline void multiTexCoord(GLenum t, const Vec2i& v) {
    (*glMultiTexCoord2ivARB)(t, &v[0]);}

  inline void multiTexCoord(GLenum t, const Vec3d& v) {
    (*glMultiTexCoord3dvARB)(t, &v[0]);}
  inline void multiTexCoord(GLenum t, const Vec3f& v) {
    (*glMultiTexCoord3fvARB)(t, &v[0]);}
  inline void multiTexCoord(GLenum t, const Vec3s& v) {
    (*glMultiTexCoord3svARB)(t, &v[0]);}
  inline void multiTexCoord(GLenum t, const Vec3i& v) {
    (*glMultiTexCoord3ivARB)(t, &v[0]);}

  inline void multiTexCoord(GLenum t, const Vec4d& v) {
    (*glMultiTexCoord4dvARB)(t, &v[0]);}
  inline void multiTexCoord(GLenum t, const Vec4f& v) {
    (*glMultiTexCoord4fvARB)(t, &v[0]);}
  inline void multiTexCoord(GLenum t, const Vec4s& v) {
    (*glMultiTexCoord4svARB)(t, &v[0]);}
  inline void multiTexCoord(GLenum t, const Vec4i& v) {
    (*glMultiTexCoord4ivARB)(t, &v[0]);}

  void activeTexture(GLenum);
  GLenum active_texture_enum;
  void clientActiveTexture(GLenum);

  inline void blendColor(GLclampf red,
			 GLclampf green,
			 GLclampf blue,
			 GLclampf alpha) {
    (*glBlendColorARB)(red,green,blue,alpha);
  }
};

struct GLError {

  GLError(const char* m) : message(m) {}
  GLError(const string& m) : message(m) {}

  string message;
};

struct GLUnsupported {

  GLUnsupported(const char* m) : message(m) {}
  GLUnsupported(const string& m) : message(m) {}

  string message;
};


#endif
