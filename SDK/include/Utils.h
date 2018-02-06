#if !defined UTILS_CPP
#define UTILS_CPP

void __declspec(dllexport) LStatus(char *format, ...);
void __declspec(dllexport) RStatus(char *format, ...);
void __declspec(dllexport) SetStatusHWND(HWND hwnd,CWnd *_wndRedraw);
void __declspec(dllexport) SetPluginActive(void);
void __declspec(dllexport) SetFuncPtr(int *_daPtr,bool *_Crossing,bool *_Centered,bool *_Snap,COption *_KOption);
void __declspec(dllexport) DrawViews(void);
void __declspec(dllexport) SetPointer(HCURSOR cursor);
bool __declspec(dllexport) GetSnap(void);
bool __declspec(dllexport) GetCentered(void);
bool __declspec(dllexport) GetCrossing(void);
void __declspec(dllexport) SetButtonPtr(int *_daPtr);
int __declspec(dllexport) GetButton();

long __declspec(dllexport) GetGOption();
HWND __declspec(dllexport) GetMainFrame();

void __declspec(dllexport) SetLib(LibContainer *Lib);

#endif