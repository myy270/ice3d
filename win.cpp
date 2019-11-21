//=============================================================================
//
// ウィンドウの処理 [win.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "win.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define CLASS_NAME		"AppClass"					// ウインドウのクラス名

#ifdef _DEBUG
#define WINDOW_NAME		"ICE3D(debug)"				// ウインドウのキャプション名
#else
#define WINDOW_NAME		"ICE3D(release)"			// ウインドウのキャプション名
#endif

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

WNDCLASSEX g_wcex;

//=============================================================================
// 初期化処理	//ウィンドウを作る
//=============================================================================
HWND InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	// ウィンドウクラスを作る
	g_wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,						// callback関数
		0,
		0,
		hInstance,
		NULL,							// ウィンドウのアイコンの設定
		LoadCursor(NULL, IDC_ARROW),	// カーソルの設定
		(HBRUSH)(COLOR_WINDOWFRAME),	// 背景色の設定
		NULL,
		CLASS_NAME,						// ウインドウのクラス名
		NULL							// ウィンドウ最小化後のアイコンの設定
	};

	// ウィンドウクラスの登録
	RegisterClassEx(&g_wcex);

	// ウィンドウの作成
	HWND hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		100,																					// ウィンドウの初期位置x
		0,																						// ウィンドウの初期位置y
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,										// ウィンドウのサイズx
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	// ウィンドウのサイズy
		NULL,
		NULL,
		hInstance,
		NULL);

	return hWnd;


}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWindow(void)
{
	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, g_wcex.hInstance);

}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:			//ウインドウ右上のＸアイコンをクリックするなど、ウィンドウを破棄するメッセージがあったら
		PostQuitMessage(0);		
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:					// [ESC]キーが押された
			DestroyWindow(hWnd);		// ウィンドウを破棄するよう指示する
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}