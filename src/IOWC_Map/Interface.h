#ifdef KOGLRENDERER_EXPORTS
#define KOGLRENDERER_API __declspec(dllexport)
#else
#define KOGLRENDERER_API __declspec(dllimport)
#endif

KOGLRENDERER_API CKIOWC_Map* CreateFileInterface(HWND WindowHandle);
KOGLRENDERER_API void DeleteFileInterface(CKIOWC_Map* Interface);