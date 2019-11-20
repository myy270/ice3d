﻿/*******************************************************************************
* タイトル:		入力処理[input.cpp]
* プログラム名:
* 作成者:		GP11A341 33 麦英泳
* 作成日:		2018/08/17
*******************************************************************************/
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define	NUM_KEY_MAX			(256)

#define	NUM_BUTTON_MAX		(32)

#define	REPEAT_TIME			(40)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

HRESULT InitKeyboard(HWND hWnd);
void UninitKeyboard(void);
HRESULT UpdateKeyboard(void);

HRESULT InitializeMouse(HWND hWnd);			// マウスの初期化
void UninitMouse();							// マウスの終了処理
HRESULT UpdateMouse();						// マウスの更新処理

HRESULT InitializePad(HWND hWnd);			// ゲームパッド初期化
void UpdatePad(void);
void UninitPad(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//キーボード
LPDIRECTINPUT8					g_pDInput = NULL;								// IDirectInput8インターフェースへのポインタ
LPDIRECTINPUTDEVICE8			g_pDIDevKeyboard = NULL;						// IDirectInputDevice8インターフェースへのポインタ(キーボード)
BYTE							g_keyState[NUM_KEY_MAX];						// キーボードの状態を受け取るワーク
BYTE							g_keyStateTrigger[NUM_KEY_MAX];					// キーボードの状態を受け取るワーク
BYTE							g_keyStateRepeat[NUM_KEY_MAX];					// キーボードの状態を受け取るワーク
BYTE							g_keyStateRelease[NUM_KEY_MAX];					// キーボードの状態を受け取るワーク
int								g_keyStateRepeatCnt[NUM_KEY_MAX];				// キーボードのリピートカウンタ

//マウス
static LPDIRECTINPUTDEVICE8		g_pMouse = NULL;								// マウスデバイス

static DIMOUSESTATE2			g_mouseState;									// マウスのダイレクトな状態
static DIMOUSESTATE2			g_mouseTrigger;									// 押された瞬間だけON

//ゲームパッド
static LPDIRECTINPUTDEVICE8		pGamePad[GAMEPADMAX] = {NULL,NULL,NULL,NULL};	// ゲームパッドデバイス

static DWORD					g_padState[GAMEPADMAX];							// ゲームパッド情報（複数対応）
static DWORD					g_padTrigger[GAMEPADMAX];
static DWORD					g_padRelease[GAMEPADMAX];
static int						g_padCount = 0;									// 検出したゲームパッドの数

DWORD							g_padRepeat[GAMEPADMAX];
int								g_padRepeatCnt[GAMEPADMAX][NUM_BUTTON_MAX];


//=============================================================================
// 入力処理の初期化
//=============================================================================
HRESULT InitInput(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	if(!g_pDInput)
	{
		// DirectInputオブジェクトの作成
		hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
									IID_IDirectInput8, (void**)&g_pDInput, NULL);
	}

	// キーボードの初期化
	InitKeyboard(hWnd);

 	// マウスの初期化
	InitializeMouse(hWnd);
	
	// ゲームパッドの初期化
	InitializePad(hWnd);

	return S_OK;
}

//=============================================================================
// 入力処理の終了処理
//=============================================================================
void UninitInput(void)
{
	// キーボードの終了処理
	UninitKeyboard();

	// マウスの終了処理
	UninitMouse();

	// ゲームパッドの終了処理
	UninitPad();

	SAFE_RELEASE(g_pDInput);

}

//=============================================================================
// 入力処理の更新処理
//=============================================================================
void UpdateInput(void)
{
	// キーボードの更新
	UpdateKeyboard();
	
	// マウスの更新
	UpdateMouse();
	
	// ゲームパッドの更新
	UpdatePad();

}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//キーボード

//=============================================================================
// キーボードの初期化
//=============================================================================
HRESULT InitKeyboard(HWND hWnd)
{
	HRESULT hr;

	// デバイスオブジェクトを作成
	hr = g_pDInput->CreateDevice(GUID_SysKeyboard, &g_pDIDevKeyboard, NULL);
	if(FAILED(hr) || g_pDIDevKeyboard == NULL)
	{
		MessageBox(hWnd, "キーボードがねぇ！", "警告！", MB_ICONWARNING);
		return hr;
	}

	// データフォーマットを設定
	hr = g_pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）	//これを消すと、ウィンドウがフォーカスされていない時も操作できる
#ifndef _DEBUG
	hr = g_pDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}
#endif
	// キーボードへのアクセス権を獲得(入力制御開始)
	g_pDIDevKeyboard->Acquire();

	return S_OK;
}

//=============================================================================
// キーボードの終了処理
//=============================================================================
void UninitKeyboard(void)
{
	SAFE_RELEASE(g_pDIDevKeyboard);

}

//=============================================================================
// キーボードの更新
//=============================================================================
HRESULT UpdateKeyboard(void)
{
	HRESULT hr;
	BYTE keyStateOld[256];

	// 前回のデータを保存
	memcpy(keyStateOld, g_keyState, NUM_KEY_MAX);

	// デバイスからデータを取得
	hr = g_pDIDevKeyboard->GetDeviceState(sizeof(g_keyState), g_keyState);
	if(SUCCEEDED(hr))
	{
		for(int cnt = 0; cnt < NUM_KEY_MAX; cnt++)
		{
			g_keyStateTrigger[cnt] = (keyStateOld[cnt] ^ g_keyState[cnt]) & g_keyState[cnt];//前回と同じなら、0
			g_keyStateRelease[cnt] = (keyStateOld[cnt] ^ g_keyState[cnt]) & ~g_keyState[cnt];
			g_keyStateRepeat[cnt] = g_keyStateTrigger[cnt];

			if(g_keyState[cnt])
			{
				g_keyStateRepeatCnt[cnt]++;
				if(g_keyStateRepeatCnt[cnt] >= REPEAT_TIME)
				{
					g_keyStateRepeat[cnt] = g_keyState[cnt];
				}
			}
			else
			{
				g_keyStateRepeatCnt[cnt] = 0;
			}
		}
	}
	else
	{
		// キーボードへのアクセス権を取得
		g_pDIDevKeyboard->Acquire();
	}

	return S_OK;
}

//=============================================================================
// キーボードのプレス状態を取得
//=============================================================================
bool GetKeyboardPress(int key)
{
	return (g_keyState[key] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのトリガー状態を取得
//=============================================================================
bool GetKeyboardTrigger(int key)
{
	return (g_keyStateTrigger[key] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのリピート状態を取得
//=============================================================================
bool GetKeyboardRepeat(int key)
{
	return (g_keyStateRepeat[key] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのリリ－ス状態を取得
//=============================================================================
bool GetKeyboardRelease(int key)
{
	return (g_keyStateRelease[key] & 0x80) ? true : false;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//マウス

//=============================================================================
// マウスの初期化
//=============================================================================
HRESULT InitializeMouse(HWND hWnd)
{
	HRESULT result;
	// デバイス作成
	result = g_pDInput->CreateDevice(GUID_SysMouse,&g_pMouse,NULL);
	if(FAILED(result) || g_pMouse==NULL)
	{
		MessageBox(hWnd,"No mouse","Warning",MB_OK | MB_ICONWARNING);
		return result;
	}
	// データフォーマット設定
	result = g_pMouse->SetDataFormat(&c_dfDIMouse2);
	if(FAILED(result))
	{
		MessageBox(hWnd,"Can't setup mouse","Warning",MB_OK | MB_ICONWARNING);
		return result;
	}
	// 他のアプリと協調モードに設定			//ウィンドウがフォーカスされていないとき、操作できるかどうかの設定
	result = g_pMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(result))
	{
		MessageBox(hWnd,"Mouse mode error","Warning",MB_OK | MB_ICONWARNING);
		return result;
	}
	
	// デバイスの設定
	DIPROPDWORD prop;
	
	prop.diph.dwSize = sizeof(prop);
	prop.diph.dwHeaderSize = sizeof(prop.diph);
	prop.diph.dwObj = 0;
	prop.diph.dwHow = DIPH_DEVICE;
	prop.dwData = DIPROPAXISMODE_REL;		// マウスの移動値　相対値

	result = g_pMouse->SetProperty(DIPROP_AXISMODE,&prop.diph);
	if(FAILED(result))
	{
		MessageBox(hWnd,"Mouse property error","Warning",MB_OK | MB_ICONWARNING);
		return result;	
	}
	
	// アクセス権を得る
	g_pMouse->Acquire();
	return result;
}

//=============================================================================
// マウスの終了処理
//=============================================================================
void UninitMouse()
{
	if(g_pMouse)
	{
		g_pMouse->Unacquire();
		g_pMouse->Release();
		g_pMouse = NULL;
	}

}

//=============================================================================
// マウスの更新処理
//=============================================================================
HRESULT UpdateMouse()
{
	HRESULT result;
	// 前回の値保存
	DIMOUSESTATE2 lastMouseState = g_mouseState;
	// データ取得
	result = g_pMouse->GetDeviceState(sizeof(g_mouseState),&g_mouseState);
	if(SUCCEEDED(result))
	{
		g_mouseTrigger.lX = g_mouseState.lX;
		g_mouseTrigger.lY = g_mouseState.lY;
		g_mouseTrigger.lZ = g_mouseState.lZ;
		// マウスのボタン状態
		for(int i=0;i<8;i++)
		{
			g_mouseTrigger.rgbButtons[i] = ((lastMouseState.rgbButtons[i] ^
				g_mouseState.rgbButtons[i]) & g_mouseState.rgbButtons[i]);
		}
	}
	else	// 取得失敗
	{
		// アクセス権を得てみる
		result = g_pMouse->Acquire();
	}
	return result;
	
}

//=============================================================================
// マウスのキーの押す状態を取得
//=============================================================================
BOOL IsMouseLeftPress(void)
{
	return (BOOL)(g_mouseState.rgbButtons[0] & 0x80);	// 押されたときに立つビットを検査
}

BOOL IsMouseLeftTrigger(void)
{
	return (BOOL)(g_mouseTrigger.rgbButtons[0] & 0x80);
}

BOOL IsMouseRightPress(void)
{
	return (BOOL)(g_mouseState.rgbButtons[1] & 0x80);
}

BOOL IsMouseRightTrigger(void)
{
	return (BOOL)(g_mouseTrigger.rgbButtons[1] & 0x80);
}

BOOL IsMouseCenterPress(void)
{
	return (BOOL)(g_mouseState.rgbButtons[2] & 0x80);
}

BOOL IsMouseCenterTrigger(void)
{
	return (BOOL)(g_mouseTrigger.rgbButtons[2] & 0x80);
}

//=============================================================================
// マウスの移動状態を取得
//=============================================================================
long GetMouseX(void)
{
	return g_mouseState.lX;
}

long GetMouseY(void)
{
	return g_mouseState.lY;
}

long GetMouseZ(void)
{
	return g_mouseState.lZ;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//ゲームパッド

//=============================================================================
// コールバック関数
//=============================================================================
BOOL CALLBACK SearchGamePadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID )
{
	HRESULT result;

	result = g_pDInput->CreateDevice(lpddi->guidInstance, &pGamePad[g_padCount++], NULL);
	return DIENUM_CONTINUE;	// 次のデバイスを列挙

}

//=============================================================================
// ゲームパッドの初期化
//=============================================================================
HRESULT InitializePad(HWND hWnd)			// ゲームパッド初期化
{
	HRESULT		result;
	int			i;

	g_padCount = 0;
	// ゲームパッドを探す
	g_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACK)SearchGamePadCallback, NULL, DIEDFL_ATTACHEDONLY);
	// セットしたコールバック関数が、ゲームパッドを発見した数だけ呼ばれる。

	for ( i=0 ; i<g_padCount ; i++ ) 
	{
		// ジョイスティック用のデータ・フォーマットを設定
		result = pGamePad[i]->SetDataFormat(&c_dfDIJoystick);
		if ( FAILED(result) )
			return false; // データフォーマットの設定に失敗

		// モードを設定（フォアグラウンド＆非排他モード）	//ウィンドウがフォーカスされていないとき、操作できるかどうかの設定
		//result = pGamePad[i]->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		//if (FAILED(result))
		//{
		//	MessageBox(hWnd, "ゲームパッドの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);

		//	return false; // モードの設定に失敗
		//}
					
		//ジョイスティック入力制御開始
		pGamePad[i]->Acquire();
	}
		
	return true;

}

//=============================================================================
// ゲームパッドの終了処理
//=============================================================================
void UninitPad(void)
{
	for (int i=0 ; i<GAMEPADMAX ; i++) 
	{
		if ( pGamePad[i] )
		{
			pGamePad[i]->Unacquire();
			pGamePad[i]->Release();
			pGamePad[i] = NULL;
		}
	}

}

//=============================================================================
// ゲームパッドの更新処理
//=============================================================================
void UpdatePad(void)
{
	HRESULT			result;
	DIJOYSTATE2		dijs;
	int				i;

	for ( i=0 ; i<g_padCount ; i++ ) 
	{
		DWORD lastPadState;
		lastPadState = g_padState[i];
		g_padState[i] = 0x00000000l;	// 初期化

		result = pGamePad[i]->Poll();	// ジョイスティックにポールをかける
		if ( FAILED(result) ) 
		{
			result = pGamePad[i]->Acquire();
			while ( result == DIERR_INPUTLOST )
				result = pGamePad[i]->Acquire();
		}

		result = pGamePad[i]->GetDeviceState(sizeof(DIJOYSTATE), &dijs);	// デバイス状態を読み取る
		if ( result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED ) 
		{
			result = pGamePad[i]->Acquire();
			while ( result == DIERR_INPUTLOST )
				result = pGamePad[i]->Acquire();
		}

		// ３２の各ビットに意味を持たせ、ボタン押下に応じてビットをオンにする

		//* left stick 
		//* y-axis (forward)
		if ( dijs.lY < 32767 - LSTICK_OFFSET)					g_padState[i] |= BUTTON_LSTICK_UP;
		//* y-axis (backward)
		if ( dijs.lY > 32767 + LSTICK_OFFSET)					g_padState[i] |= BUTTON_LSTICK_DOWN;
		//* x-axis (left)
		if ( dijs.lX < 32767 - LSTICK_OFFSET)					g_padState[i] |= BUTTON_LSTICK_LEFT;
		//* x-axis (right)
		if ( dijs.lX > 32767 + LSTICK_OFFSET)					g_padState[i] |= BUTTON_LSTICK_RIGHT;

		//* right stick
		if ( dijs.lRz < 32767 - RSTICK_OFFSET)					g_padState[i] |= BUTTON_RSTICK_UP;
		//* 													  
		if ( dijs.lRz > 32767 + RSTICK_OFFSET)					g_padState[i] |= BUTTON_RSTICK_DOWN;
		//* 													  
		if ( dijs.lZ  < 32767 - RSTICK_OFFSET)					g_padState[i] |= BUTTON_RSTICK_LEFT;
		//* 													  
		if ( dijs.lZ  > 32767 + RSTICK_OFFSET)					g_padState[i] |= BUTTON_RSTICK_RIGHT;

		//* 十字方向キー
		if ((dijs.rgdwPOV[0] == 0) || (dijs.rgdwPOV[0] == 4500) || (dijs.rgdwPOV[0] == 31500))			g_padState[i] |= BUTTON_UP;
		//* 													  
		if ((dijs.rgdwPOV[0] == 13500) || (dijs.rgdwPOV[0] == 18000) || (dijs.rgdwPOV[0] == 22500))		g_padState[i] |= BUTTON_DOWN;
		//* 													  
		if ((dijs.rgdwPOV[0] == 22500) || (dijs.rgdwPOV[0] == 27000) || (dijs.rgdwPOV[0] == 31500))		g_padState[i] |= BUTTON_LEFT;
		//* 													  
		if ((dijs.rgdwPOV[0] == 4500) || (dijs.rgdwPOV[0] == 9000) || (dijs.rgdwPOV[0] == 13500))		g_padState[i] |= BUTTON_RIGHT;


		if ( dijs.rgbButtons[0] & 0x80 )	g_padState[i] |= BUTTON_SQUARE;
		if ( dijs.rgbButtons[1] & 0x80 )	g_padState[i] |= BUTTON_CROSS;
		if ( dijs.rgbButtons[2] & 0x80 )	g_padState[i] |= BUTTON_CIRCLE;
		if ( dijs.rgbButtons[3] & 0x80 )	g_padState[i] |= BUTTON_TRIANGLE;
		if ( dijs.rgbButtons[4] & 0x80 )	g_padState[i] |= BUTTON_L1;
		if ( dijs.rgbButtons[5] & 0x80 )	g_padState[i] |= BUTTON_R1;
		if ( dijs.rgbButtons[6] & 0x80 )	g_padState[i] |= BUTTON_L2;
		if ( dijs.rgbButtons[7] & 0x80 )	g_padState[i] |= BUTTON_R2;
		if ( dijs.rgbButtons[8] & 0x80 )	g_padState[i] |= BUTTON_SHARE;
		if ( dijs.rgbButtons[9] & 0x80 )	g_padState[i] |= BUTTON_OPTIONS;
		if ( dijs.rgbButtons[10] & 0x80)	g_padState[i] |= BUTTON_L3;
		if ( dijs.rgbButtons[11] & 0x80)	g_padState[i] |= BUTTON_R3;
		if ( dijs.rgbButtons[12] & 0x80)	g_padState[i] |= BUTTON_PS;
		if ( dijs.rgbButtons[13] & 0x80)	g_padState[i] |= BUTTON_TOUCHPAD;

		// Trigger設定
		g_padTrigger[i] = ((lastPadState ^ g_padState[i])	// 前回と違っていて
						& g_padState[i]);					// しかも今ONのやつ

		// Release設定
		g_padRelease[i] = (lastPadState ^ g_padState[i]) & ~g_padState[i];
		
		//Repeat設定
		g_padRepeat[i] = g_padTrigger[i];

		for (int cnt = 0; cnt < NUM_BUTTON_MAX; cnt++)
		{
			DWORD buff = g_padState[i] & (DWORD)(1 * powf(2.0f, (float)cnt));
		
			if (buff)
			{
				g_padRepeatCnt[i][cnt]++;
				if (g_padRepeatCnt[i][cnt] >= REPEAT_TIME)
				{
					g_padRepeat[i] = g_padRepeat[i] | buff;
				}
			}
			else
			{
				g_padRepeatCnt[i][cnt] = 0;
				
			}
		}

	}

}

//=============================================================================
// ゲームパッドのボタンの押す状態を取得
//=============================================================================
BOOL IsButtonPress(int padNo,DWORD button)
{
	return (button & g_padState[padNo]);
}

BOOL IsButtonTrigger(int padNo,DWORD button)
{
	return (button & g_padTrigger[padNo]);
}

BOOL IsButtonRelease(int padNo, DWORD button)
{
	return (button & g_padRelease[padNo]);
}

BOOL IsButtonRepeat(int padNo, DWORD button)
{
	return (button & g_padRepeat[padNo]);
}
