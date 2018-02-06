#if !defined(RESSWITCH_H_)
#define RESSWITCH_H_

extern "C" AFX_EXTENSION_MODULE ExtensionDLL;


class DllInstanceSwitcher
{
public:
    DllInstanceSwitcher()
    {
        m_hInst = AfxGetResourceHandle();
        AfxSetResourceHandle(ExtensionDLL.hResource);
    }

    ~DllInstanceSwitcher()
    {
        AfxSetResourceHandle(m_hInst);
    }

private:
    HINSTANCE m_hInst;
};

#define SWITCH_RESOURCE  DllInstanceSwitcher __SwitchInstance;

#endif
