#ifdef KAPSUL_EXPORTS
#define KAPSUL_EXPORTS_API __declspec(dllexport)
#else
#define KAPSUL_EXPORTS_API __declspec(dllimport)
#endif

KAPSUL_EXPORTS_API CKPluginSkeleton* CreateSceneInterface();
KAPSUL_EXPORTS_API void DeleteSceneInterface(CKPluginSkeleton* Interface);

class DllInstanceSwitcher;

#define SWITCH_RESOURCE  DllInstanceSwitcher __SwitchInstance;
