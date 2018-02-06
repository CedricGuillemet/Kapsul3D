#ifdef KIOFILE_EXPORTS
#define KIOFILE_API __declspec(dllexport)
#else
#define KIOFILE_API __declspec(dllimport)
#endif

KIOFILE_API CKIoFile* CreateFileInterface(HWND WindowHandle);
KIOFILE_API void DeleteFileInterface(CKIoFile* Interface);