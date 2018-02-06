#include "WGLContext.h"

HGLRC WGLContext::current_context = 0;

WGLContext::WGLContext(HWND window_handle) : hwnd(window_handle) {

  hdc = GetDC(hwnd);
  assert(hdc);

  PIXELFORMATDESCRIPTOR pfd;
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);  //  size of this pfd 
  pfd.nVersion = 1;		                    // version number 
  pfd.dwFlags = 
    PFD_DRAW_TO_WINDOW |   // support window 
    PFD_SUPPORT_OPENGL |   // support OpenGL 
    PFD_DOUBLEBUFFER,      // double buffered 
    PFD_TYPE_RGBA;         // RGBA type 

  pfd.iPixelType = PFD_TYPE_RGBA;


  pfd.dwLayerMask = PFD_MAIN_PLANE;    // main layer     
  pfd.cColorBits = 24;                 // 24-bit color depth 
  pfd.cDepthBits = 32;
  pfd.cAccumBits = 0;
  pfd.cStencilBits = 0;

  pfd.cRedBits = 8;
  pfd.cGreenBits = 8;
  pfd.cBlueBits = 8;
  pfd.cAlphaBits = 0;

  pfd.cRedShift = 0;
  pfd.cGreenShift = 0;
  pfd.cBlueShift = 0;
  pfd.cAlphaShift = 0;

  pfd.cAccumRedBits = 0;
  pfd.cAccumGreenBits = 0;
  pfd.cAccumBlueBits = 0;
  pfd.cAccumAlphaBits = 0;

  int  pixel_format = ChoosePixelFormat(hdc, &pfd);
  assert(pixel_format);

  int success = SetPixelFormat(hdc, pixel_format, &pfd);
  assert(success);
  
  hglrc = wglCreateContext(hdc);
  assert(hglrc);

  grab();
  init_extension_string();

  glActiveTextureARB = reinterpret_cast<PFNGLACTIVETEXTUREARBPROC>(wglGetProcAddress("glActiveTextureARB"));
  glClientActiveTextureARB = reinterpret_cast<PFNGLCLIENTACTIVETEXTUREARBPROC>(wglGetProcAddress("glClientActiveTextureARB"));

  glMultiTexCoord1dARB = reinterpret_cast<PFNGLMULTITEXCOORD1DARBPROC>(wglGetProcAddress("glMultiTexCoord1dARB"));
  glMultiTexCoord1dvARB = reinterpret_cast<PFNGLMULTITEXCOORD1DVARBPROC>(wglGetProcAddress("glMultiTexCoord1dvARB"));
  glMultiTexCoord1fARB = reinterpret_cast<PFNGLMULTITEXCOORD1FARBPROC>(wglGetProcAddress("glMultiTexCoord1fARB"));
  glMultiTexCoord1fvARB = reinterpret_cast<PFNGLMULTITEXCOORD1FVARBPROC>(wglGetProcAddress("glMultiTexCoord1fvARB"));
  glMultiTexCoord1iARB = reinterpret_cast<PFNGLMULTITEXCOORD1IARBPROC>(wglGetProcAddress("glMultiTexCoord1iARB"));
  glMultiTexCoord1ivARB = reinterpret_cast<PFNGLMULTITEXCOORD1IVARBPROC>(wglGetProcAddress("glMultiTexCoord1ivARB"));
  glMultiTexCoord1sARB = reinterpret_cast<PFNGLMULTITEXCOORD1SARBPROC>(wglGetProcAddress("glMultiTexCoord1sARB"));
  glMultiTexCoord1svARB = reinterpret_cast<PFNGLMULTITEXCOORD1SVARBPROC>(wglGetProcAddress("glMultiTexCoord1svARB"));

  glMultiTexCoord2dARB = reinterpret_cast<PFNGLMULTITEXCOORD2DARBPROC>(wglGetProcAddress("glMultiTexCoord2dARB"));
  glMultiTexCoord2dvARB = reinterpret_cast<PFNGLMULTITEXCOORD2DVARBPROC>(wglGetProcAddress("glMultiTexCoord2dvARB"));
  glMultiTexCoord2fARB = reinterpret_cast<PFNGLMULTITEXCOORD2FARBPROC>(wglGetProcAddress("glMultiTexCoord2fARB"));
  glMultiTexCoord2fvARB = reinterpret_cast<PFNGLMULTITEXCOORD2FVARBPROC>(wglGetProcAddress("glMultiTexCoord2fvARB"));
  glMultiTexCoord2iARB = reinterpret_cast<PFNGLMULTITEXCOORD2IARBPROC>(wglGetProcAddress("glMultiTexCoord2iARB"));
  glMultiTexCoord2ivARB = reinterpret_cast<PFNGLMULTITEXCOORD2IVARBPROC>(wglGetProcAddress("glMultiTexCoord2ivARB"));
  glMultiTexCoord2sARB = reinterpret_cast<PFNGLMULTITEXCOORD2SARBPROC>(wglGetProcAddress("glMultiTexCoord2sARB"));
  glMultiTexCoord2svARB = reinterpret_cast<PFNGLMULTITEXCOORD2SVARBPROC>(wglGetProcAddress("glMultiTexCoord2svARB"));

  glMultiTexCoord3dARB = reinterpret_cast<PFNGLMULTITEXCOORD3DARBPROC>(wglGetProcAddress("glMultiTexCoord3dARB"));
  glMultiTexCoord3dvARB = reinterpret_cast<PFNGLMULTITEXCOORD3DVARBPROC>(wglGetProcAddress("glMultiTexCoord3dvARB"));
  glMultiTexCoord3fARB = reinterpret_cast<PFNGLMULTITEXCOORD3FARBPROC>(wglGetProcAddress("glMultiTexCoord3fARB"));
  glMultiTexCoord3fvARB = reinterpret_cast<PFNGLMULTITEXCOORD3FVARBPROC>(wglGetProcAddress("glMultiTexCoord3fvARB"));
  glMultiTexCoord3iARB = reinterpret_cast<PFNGLMULTITEXCOORD3IARBPROC>(wglGetProcAddress("glMultiTexCoord3iARB"));
  glMultiTexCoord3ivARB = reinterpret_cast<PFNGLMULTITEXCOORD3IVARBPROC>(wglGetProcAddress("glMultiTexCoord3ivARB"));
  glMultiTexCoord3sARB = reinterpret_cast<PFNGLMULTITEXCOORD3SARBPROC>(wglGetProcAddress("glMultiTexCoord3sARB"));
  glMultiTexCoord3svARB = reinterpret_cast<PFNGLMULTITEXCOORD3SVARBPROC>(wglGetProcAddress("glMultiTexCoord3svARB"));

  glMultiTexCoord4dARB = reinterpret_cast<PFNGLMULTITEXCOORD4DARBPROC>(wglGetProcAddress("glMultiTexCoord4dARB"));
  glMultiTexCoord4dvARB = reinterpret_cast<PFNGLMULTITEXCOORD4DVARBPROC>(wglGetProcAddress("glMultiTexCoord4dvARB"));
  glMultiTexCoord4fARB = reinterpret_cast<PFNGLMULTITEXCOORD4FARBPROC>(wglGetProcAddress("glMultiTexCoord4fARB"));
  glMultiTexCoord4fvARB = reinterpret_cast<PFNGLMULTITEXCOORD4FVARBPROC>(wglGetProcAddress("glMultiTexCoord4fvARB"));
  glMultiTexCoord4iARB = reinterpret_cast<PFNGLMULTITEXCOORD4IARBPROC>(wglGetProcAddress("glMultiTexCoord4iARB"));
  glMultiTexCoord4ivARB = reinterpret_cast<PFNGLMULTITEXCOORD4IVARBPROC>(wglGetProcAddress("glMultiTexCoord4ivARB"));
  glMultiTexCoord4sARB = reinterpret_cast<PFNGLMULTITEXCOORD4SARBPROC>(wglGetProcAddress("glMultiTexCoord4sARB"));
  glMultiTexCoord4svARB = reinterpret_cast<PFNGLMULTITEXCOORD4SVARBPROC>(wglGetProcAddress("glMultiTexCoord4svARB"));

  typedef void (APIENTRY * PFNGLBLENDCOLOREXTPROC) (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
  glBlendColorARB = reinterpret_cast<PFNGLBLENDCOLOREXTPROC>(wglGetProcAddress("glBlendColorARB"));

}

void WGLContext::grab() {

  if (current_context!=hglrc) {
    current_context = hglrc;
    wglMakeCurrent (hdc, hglrc);
  }
}


void WGLContext::release() {
  if (current_context != 0) {
    current_context = 0;
    wglMakeCurrent(hdc, 0);
  }
}


WGLContext::~WGLContext() {

  release();
  wglDeleteContext(hglrc);
  ReleaseDC(hwnd, hdc);
}

void WGLContext::swapBuffers() {

  SwapBuffers(hdc);
}
