#ifdef KAPSUL_EXPORTS
#define KAPSUL_EXPORTS_API __declspec(dllexport)
#else
#define KAPSUL_EXPORTS_API __declspec(dllimport)
#endif

KAPSUL_EXPORTS_API CKPluginShape* CreateSceneInterface();
KAPSUL_EXPORTS_API void DeleteSceneInterface(CKPluginShape* Interface);

class DllInstanceSwitcher;

#define SWITCH_RESOURCE  DllInstanceSwitcher __SwitchInstance;
