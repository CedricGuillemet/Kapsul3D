#ifdef KOGLRENDERER_EXPORTS
#define KOGLRENDERER_API __declspec(dllexport)
#else
#define KOGLRENDERER_API __declspec(dllimport)
#endif

KOGLRENDERER_API CKOGLRenderer* CreateInterface(HWND WindowHandle);
KOGLRENDERER_API void DeleteInterface(CKOGLRenderer* Interface);