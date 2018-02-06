HINSTANCE TmpInst;
extern HINSTANCE g_Inst;

void PushDLLResource(void)
{
	TmpInst=AfxGetResourceHandle();
	AfxSetResourceHandle(g_Inst);
}

void PopDLLResource(void)
{
	AfxSetResourceHandle(TmpInst);
}
