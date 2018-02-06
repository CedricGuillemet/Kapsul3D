#ifdef KOGLRENDERER_EXPORTS
#define KOGLRENDERER_API __declspec(dllexport)
#else
#define KOGLRENDERER_API __declspec(dllimport)
#endif

KOGLRENDERER_API CKIomd2* CreateFileInterface();
KOGLRENDERER_API void DeleteFileInterface(CKIomd2* Interface);
