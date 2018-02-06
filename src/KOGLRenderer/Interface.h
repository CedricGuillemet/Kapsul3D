#ifdef KOGLRENDERER_EXPORTS
#define KOGLRENDERER_API __declspec(dllexport)
#else
#define KOGLRENDERER_API __declspec(dllimport)
#endif

KOGLRENDERER_API CKOGLRenderer* CreateRenderInterface(CKScene *Scene);
KOGLRENDERER_API void DeleteRenderInterface(CKOGLRenderer* Interface);