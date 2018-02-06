// DirectInput8.h: interface for the CKDirectInput8 class.
// Created by: Brad Blake	bradleyb@graduatecentre.com
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRECTINPUT8_H__C7F3B7B1_FF8E_4F74_8A80_10A7E827F1B8__INCLUDED_)
#define AFX_DIRECTINPUT8_H__C7F3B7B1_FF8E_4F74_8A80_10A7E827F1B8__INCLUDED_

#include <d3dx8.h>
#include <dinput.h>
#include <dxutil.h>


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define KEYDOWN(name, key) (name[key] & 0x80)
#define KEYUP(name, key) (!(name[key] & 0x80))

#define USEKEYBOARD	0x00000001L
#define USEMOUSE	0x00000002L
#define USEJOYSTICK	0x00000004L

////////////////////////////////////////////////////////////
//Cursor vertex structure for Direct3D
struct CV2D_T1D
{
	D3DXVECTOR4 p;
	DWORD diffuse;
	float tu;
	float tv;
};
#define D3DFVF_CV2D_T1D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX0)

inline CV2D_T1D InitCV2D_T1D(D3DXVECTOR4 p, D3DCOLOR diffuse, float tu, float tv)
{
	CV2D_T1D v;
	v.p = p;
	v.diffuse = diffuse;
	v.tu = tu;
	v.tv = tv;

	return v;
}
////////////////////////////////////////////////////////////

class KAPSUL_DESC CKDirectInput8  
{
public:
	//Set cursor hot spot
	void SetHotSpot(POINT hspot);

	//8 Element Array, TRUE if Button [n] is up
	BOOL* m_bMouseUp;

	//Mouse Position
	POINT* m_pMousePos;

	//Cursor HotSpot
	POINT* m_pHotSpot;

	//DI Device Objects
	LPDIRECTINPUTDEVICE8 m_pDIJoy;
	LPDIRECTINPUTDEVICE8 m_pDIKeybrd;
	LPDIRECTINPUTDEVICE8 m_pDIMouse;

	//Device State Buffers
	DIJOYSTATE2 m_js;
	DIMOUSESTATE2 m_MouseState;
	char buffer[256];
	DWORD m_dwElements;

	//DI Object
	LPDIRECTINPUT8 m_pDI;

	//Cursor Vertex Buffer
	LPDIRECT3DVERTEXBUFFER8 m_pVB;

	//Cursor Texture
	LPDIRECT3DTEXTURE8 m_pCursorTex;

	//DI Device Capabilities
	DIDEVCAPS m_DIDevCaps;

	//Initialize Direct Input
	HRESULT InitDI(HWND hWnd, HINSTANCE hInstance, DWORD ToUse);

	//Overridable Input Processing Methods
	virtual HRESULT ProcessMouse();
	virtual HRESULT ProcessKB();
	virtual HRESULT ProcessJoy();

	//Check if Mouse Buttons Up
	BOOL MButtonUp(BYTE button);
	BOOL AllMouseUp();

	//Release and Delete DI Objects
	void DIShutdown();

	//Required for D3D Framework
	HRESULT InitDeviceObjects(LPDIRECT3DDEVICE8 pd3dDevice, TCHAR* pCursorFile = NULL);
	HRESULT DrawMouse(LPDIRECT3DDEVICE8 pd3dDevice);
	HRESULT DeleteDeviceObjects();
	HRESULT InvalidateDeviceObjects();
	HRESULT RestoreDeviceObjects(LPDIRECT3DDEVICE8 pd3dDevice);

	//Construction/Destruction
	CKDirectInput8();
	virtual ~CKDirectInput8();

protected:
	//Mouse Handle
	HANDLE m_hMouse;
	HRESULT hr;

private:
	//Joystick callbacks
	friend BOOL __stdcall EnumAxesCallback( const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext );
	friend BOOL __stdcall EnumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance, VOID* pContext );	
};

//Global CKDirectInput8 Instance
extern CKDirectInput8* g_pDI8;

#endif // !defined(AFX_DIRECTINPUT8_H__C7F3B7B1_FF8E_4F74_8A80_10A7E827F1B8__INCLUDED_)
