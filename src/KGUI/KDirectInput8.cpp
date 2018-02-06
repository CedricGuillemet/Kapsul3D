// DirectInput8.cpp: implementation of the CKDirectInput8 class.
// Created by: Brad Blake	bradleyb@graduatecentre.com
//////////////////////////////////////////////////////////////////////

// Include PCH here if required
#include "stdafx.h"
//#include "DirectInput8.h"
#include "KDirectInput8.h"
// Global Instance
CKDirectInput8* g_pDI8 = NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKDirectInput8::CKDirectInput8()
{
	g_pDI8			= this;
	m_pDI			= NULL;
	m_pDIKeybrd		= NULL;
	m_pDIMouse		= NULL;
	m_pDIJoy		= NULL;
	m_pMousePos		= new POINT;
	m_pMousePos->x	= 0l;
	m_pMousePos->y	= 0l;
	m_pHotSpot		= new POINT;
	m_pHotSpot->x	= 0l;
	m_pHotSpot->y	= 0l;
	m_pVB			= NULL;
	m_pCursorTex	= NULL;
	m_dwElements	= 16;
	m_bMouseUp		= new BOOL[8];
	for(int i=0; i<8; i++)
		m_bMouseUp[i] = TRUE;

}

CKDirectInput8::~CKDirectInput8()
{
	DIShutdown();
	SAFE_DELETE(m_pMousePos);
	SAFE_DELETE(m_pHotSpot);
	SAFE_DELETE(m_pCursorTex);
	SAFE_DELETE_ARRAY(m_bMouseUp);
}

/************************************************************************/
//Method:	InitDI
//Purpose:	Initialize Direct Input
/************************************************************************/
HRESULT CKDirectInput8::InitDI(HWND hWnd, HINSTANCE hInstance, DWORD ToUse)
{	
	// Create The DI Object
	if(FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, 
        IID_IDirectInput8, (void**)&m_pDI, NULL))) 
		return E_FAIL;
	
	/************************************************************************/
	//Set up keyboard input
	if(ToUse & USEKEYBOARD)
	{
		if(FAILED(m_pDI->CreateDevice(GUID_SysKeyboard, &m_pDIKeybrd, NULL)))
			return E_FAIL;

		if(FAILED(m_pDIKeybrd->SetDataFormat(&c_dfDIKeyboard)))
			return E_FAIL;

		if(FAILED(m_pDIKeybrd->SetCooperativeLevel(hWnd, 
					   DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
			return E_FAIL;

		if (m_pDIKeybrd) m_pDIKeybrd->Acquire(); 
	}
	/************************************************************************/

	/************************************************************************/
	//Set up mouse input
	if(ToUse & USEMOUSE)
	{
		if(FAILED(m_pDI->CreateDevice(GUID_SysMouse, &m_pDIMouse, NULL)))
			return E_FAIL;

		if(FAILED(m_pDIMouse->SetDataFormat(&c_dfDIMouse2)))
			return E_FAIL;

		if(FAILED(m_pDIMouse->SetCooperativeLevel(hWnd, 
					   DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
			return E_FAIL;

		m_hMouse = CreateEvent(0,0,0,0);

		if (m_hMouse == NULL)
		{
			DIShutdown();
			return 0;
		}

		hr = m_pDIMouse->SetEventNotification(m_hMouse);

		if (FAILED(hr))
		{
			DIShutdown();
			return 0;
		}

		//initialize input buffer
		DIPROPDWORD dipdw; 
		
		dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		dipdw.diph.dwObj        = 0;
		dipdw.diph.dwHow        = DIPH_DEVICE;
		dipdw.dwData            = 16;

		hr = m_pDIMouse->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

		if (FAILED(hr))
		{
			DIShutdown();
			return 0;
		}

		if (m_pDIMouse) m_pDIMouse->Acquire();
	}
	/************************************************************************/

	/************************************************************************/
	//Set up Joystick input (Only the first joy)
	if(ToUse & USEJOYSTICK)
	{
		if( FAILED(m_pDI->EnumDevices( DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY ) ) )
			return E_FAIL;

		if( FAILED(m_pDIJoy->SetDataFormat( &c_dfDIJoystick2 ) ) )
			return E_FAIL;

		if( FAILED(m_pDIJoy->SetCooperativeLevel( hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND ) ) )
			return E_FAIL;

		m_DIDevCaps.dwSize = sizeof(DIDEVCAPS);
		if ( FAILED(m_pDIJoy->GetCapabilities(&m_DIDevCaps) ) )
			return E_FAIL;

		if ( FAILED(m_pDIJoy->EnumObjects( EnumAxesCallback, (VOID*)hWnd, DIDFT_AXIS ) ) )
			return E_FAIL;

		if(m_pDIJoy) m_pDIJoy->Acquire();
	}
	/************************************************************************/

	return S_OK;
}

/************************************************************************/
//Method:	ProcessKB()
//Purpose:	Capture Keyboard Input
/************************************************************************/
HRESULT CKDirectInput8::ProcessKB()
{
	//Check for keyboard input and fill buffer
	hr = m_pDIKeybrd->GetDeviceState(sizeof(buffer),(LPVOID)&buffer); 
    if FAILED(hr) 
    { 
         m_pDIKeybrd->Acquire();
         return E_FAIL; 
    }

	return S_OK;       
}

/************************************************************************/
//Method:	ProcessMouse
//Purpose:	Capture Mouse Input
/************************************************************************/
HRESULT CKDirectInput8::ProcessMouse()
{
	//Check for mouse input and fill buffer
	hr = m_pDIMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &m_MouseState);
	if(hr == DIERR_INPUTLOST)
	{
		m_pDIMouse->Acquire();
		return E_FAIL;
	}

	return S_OK;
}

/************************************************************************/
//Method:	ProcessJoy
//Purpose:	Capture Joystick Input
/************************************************************************/
HRESULT CKDirectInput8::ProcessJoy()
{
	//Get joystick state and fill buffer
    if(FAILED(m_pDIJoy->Poll()))  
    {
        while( m_pDIJoy->Acquire() == DIERR_INPUTLOST ) 
        {}

        return E_FAIL; 
    }

    if( FAILED(m_pDIJoy->GetDeviceState( sizeof(DIJOYSTATE2), &m_js ) ) )
        return E_FAIL;

	return S_OK;
}

/************************************************************************/
//Method:	DIShutdown()
//Purpose:	Cleanup Objects
/************************************************************************/
void CKDirectInput8::DIShutdown()
{
	SAFE_DELETE(m_pVB);

	if (m_pDI)
	{
		if (m_pDIKeybrd)
		{
			m_pDIKeybrd->Unacquire();
			m_pDIKeybrd->Release();
			m_pDIKeybrd = NULL;
		}

		if (m_pDIMouse)
		{
			m_pDIMouse->Unacquire();
			m_pDIMouse->Release();
			m_pDIMouse = NULL;
		}
		if (m_pDIJoy)
		{
			m_pDIJoy->Unacquire();
			m_pDIJoy->Release();
			m_pDIJoy = NULL;
		}
		m_pDI->Release();
		m_pDI = NULL;
	}
	
}

/************************************************************************/
//Method:	RestoreDeviceObjects
//Purpose:	Set Up Mouse Cursor Vertex Buffer
/************************************************************************/
HRESULT CKDirectInput8::RestoreDeviceObjects(LPDIRECT3DDEVICE8 pd3dDevice)
{
	/*
	V2D_T1D Vertices[] =
	{
		//Mouse cursor - 0
		InitCV2D_T1D(D3DXVECTOR4(   0.0f,  20.0f,  0.0f, 1.0f), 0xffffffff, 0.0f, 1.0f),
		InitCV2D_T1D(D3DXVECTOR4(   0.0f,   0.0f,  0.0f, 1.0f), 0xffffffff, 0.0f, 0.0f),
		InitCV2D_T1D(D3DXVECTOR4(  10.0f,  20.0f,  0.0f, 1.0f), 0xffffffff, 1.0f, 1.0f),
		InitCV2D_T1D(D3DXVECTOR4(  10.0f,   0.0f,  0.0f, 1.0f), 0xffffffff, 1.0f, 0.0f),

	};

	if( FAILED( pd3dDevice->CreateVertexBuffer( 4*sizeof(CV2D_T1D), 0, D3DFVF_CV2D_T1D, D3DPOOL_DEFAULT, &m_pVB ) ) )
    {
        return E_FAIL;
    }

	VOID* pVertices;
    if( FAILED( m_pVB->Lock( 0, sizeof(Vertices), (BYTE**)&pVertices, 0 ) ) )
        return E_FAIL;
    memcpy( pVertices, Vertices, sizeof(Vertices) );
    m_pVB->Unlock();
*/
	return S_OK;
}

/************************************************************************/
//Method:	InvalidateDeviceObjects
//Purpose:	Release Device Dependant Objects
/************************************************************************/
HRESULT CKDirectInput8::InvalidateDeviceObjects()
{
	SAFE_RELEASE(m_pVB);

	return S_OK;
}

/************************************************************************/
//Method:	DeleteDeviceObjects
//Purpose:	Delete Device Dependant Objects
/************************************************************************/
HRESULT CKDirectInput8::DeleteDeviceObjects()
{
	SAFE_RELEASE(m_pCursorTex);
	SAFE_DELETE(m_pCursorTex);

	return S_OK;
}

/************************************************************************/
//Method:	DrawMouse
//Purpose:	Render The Mouse Cursor
/************************************************************************/
HRESULT CKDirectInput8::DrawMouse(LPDIRECT3DDEVICE8 pd3dDevice)
{
	pd3dDevice->SetStreamSource( 0, m_pVB, sizeof(CV2D_T1D) );
	pd3dDevice->SetVertexShader( D3DFVF_CV2D_T1D );
	pd3dDevice->SetTexture(0, m_pCursorTex);
	
	//Draw Cursor
	CV2D_T1D* pVertices;
	if(FAILED(m_pVB->Lock(0, 4*sizeof(CV2D_T1D), (BYTE**)&pVertices, 0)))
		return E_FAIL;
	pVertices[0].p.x = (( float)m_pMousePos->x)          - m_pHotSpot->x;
	pVertices[0].p.y = (((float)m_pMousePos->y) + 20.0f) - m_pHotSpot->y;
	pVertices[1].p.x = (( float)m_pMousePos->x)          - m_pHotSpot->x;
	pVertices[1].p.y = (( float)m_pMousePos->y)          - m_pHotSpot->y;
	pVertices[2].p.x = (((float)m_pMousePos->x) + 10.0f) - m_pHotSpot->x;
	pVertices[2].p.y = (((float)m_pMousePos->y) + 20.0f) - m_pHotSpot->y;
	pVertices[3].p.x = (((float)m_pMousePos->x) + 10.0f) - m_pHotSpot->x;
	pVertices[3].p.y = (( float)m_pMousePos->y)          - m_pHotSpot->y;
	m_pVB->Unlock();
	pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2);

	return S_OK;
}

/************************************************************************/
//Method:	InitDeviceObjects
//Purpose:	Initialize Device Dependant Objects
/************************************************************************/
HRESULT CKDirectInput8::InitDeviceObjects(LPDIRECT3DDEVICE8 pd3dDevice, TCHAR* pCursorFile)
{
	/*
	if(pCursorFile != NULL)
	D3DXCreateTextureFromFile(pd3dDevice, pCursorFile, &m_pCursorTex);
*/
	return S_OK;
}

/************************************************************************/
//Method:	AllMouseUp
//Purpose:	Determine If All Mouse Buttons Are Up
/************************************************************************/
BOOL CKDirectInput8::AllMouseUp()
{
	if(!m_MouseState.rgbButtons[0] &&
	   !m_MouseState.rgbButtons[1] &&
	   !m_MouseState.rgbButtons[2] &&
	   !m_MouseState.rgbButtons[3] &&
	   !m_MouseState.rgbButtons[4] &&
	   !m_MouseState.rgbButtons[5] &&
	   !m_MouseState.rgbButtons[6] &&
	   !m_MouseState.rgbButtons[7])
	   return TRUE;

	return FALSE;
}

/************************************************************************/
//Method:	MButtonUp
//Purpose:	Determine If A Specified Mouse Button Is Up
/************************************************************************/
BOOL CKDirectInput8::MButtonUp(BYTE button)
{
	if(!m_MouseState.rgbButtons[button])
		return TRUE;

	return FALSE;
}

/************************************************************************/
//Method:	EnumAxesCallback
//Purpose:	Joystick Axes Enumeration Callback
/************************************************************************/
BOOL __stdcall EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext)
{
	HWND hDlg = (HWND)pContext;

    DIPROPRANGE diprg; 
    diprg.diph.dwSize       = sizeof(DIPROPRANGE); 
    diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
    diprg.diph.dwHow        = DIPH_BYID; 
    diprg.diph.dwObj        = pdidoi->dwType; // Specify the enumerated axis
    diprg.lMin              = -1000; 
    diprg.lMax              = +1000; 
    
	// Set the range for the axis
	if( FAILED( g_pDI8->m_pDIJoy->SetProperty( DIPROP_RANGE, &diprg.diph ) ) )
		return DIENUM_STOP;

    return DIENUM_CONTINUE;
}

/************************************************************************/
//Method:	EnumJoysticksCallback
//Purpose:	Joystick Enumeration Callback
/************************************************************************/
BOOL __stdcall EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext)
{
	HRESULT hr;

    hr = g_pDI8->m_pDI->CreateDevice( pdidInstance->guidInstance, &g_pDI8->m_pDIJoy, NULL );

    if( FAILED(hr) ) 
        return DIENUM_CONTINUE;

    return DIENUM_STOP;
}

/************************************************************************/
//Method:	SetHotSpot
//Purpose:	Set the hotspot offset for the cursor
/************************************************************************/
void CKDirectInput8::SetHotSpot(POINT hspot)
{
	m_pHotSpot->x = hspot.x;
	m_pHotSpot->y = hspot.y;
}
