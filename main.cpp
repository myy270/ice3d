//=============================================================================
//
// メイン処理 [main.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "sound.h"
#include "debugproc.h"


#include "win.h"
#include "fps.h"
#include "scene.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT Init(HINSTANCE hInstance, int nCmdShow);
void Uninit(void);
void Update(void);
void Draw(void);

void Pause(bool& b);
void Retire(void);

//*****************************************************************************
// グローバル変数:
//*****************************************************************************


//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG		msg;
	bool	rest = false;			//true:ポーズ	false:ポーズではない

	// 初期化処理
	if(FAILED(Init(hInstance, nCmdShow)))
	{
		return -1;
	}

	// メッセージループ
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE ))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ(送出)
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			if(UpdateFPS())			//実行速度を制限する（つまり、FPSをロックする）
			{
				// 入力更新
				UpdateInput();

				//ポーズ判定
				Pause(rest);

				if (!rest)
				{
					// 更新処理
					Update();

					// 描画処理
					Draw();
				}
						
			}
		}
	}
	
	// 終了処理
	Uninit();

	return (int)msg.wParam;		//正常であれば、この値は0
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, int nCmdShow)
{
	// ウィンドウを作成
	HWND hWnd = InitWindow(hInstance, nCmdShow);

	// DX初期化処理
	if (FAILED(InitDX(hWnd, true)))
	{
		return E_FAIL;
	}

	InitFPS();

	// 入力処理の初期化
	InitInput(hInstance, hWnd);

	// デバッグ表示処理の初期化
	InitDebugProc();

	// フェードの初期化
	InitFade();

	// サウンドの初期化
	InitSound(hWnd);

	// ゲーム起動後の最初のシーンを設定して初期化する
	SetScene(FIRST_SCENE);


	// ウインドウの表示(初期化処理の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	UnitFPS();

	UninitWindow();

	UninitDX();

	UninitTitle();
	UninitGame();
	UninitResult();

	// フェードの終了処理
	UninitFade();

	// サウンドの終了処理
	UninitSound();

	// 入力処理の終了処理
	UninitInput();

	// デバッグ表示処理の終了処理
	UninitDebugProc();

}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	//タイトル画面に戻る判定
	Retire();

	UpdateDebugProc();

	ShowFPS();

	switch(GetScene())
	{
	case SCENE_TITLE:		// タイトル画面の更新
		UpdateTitle();
		break;

	case SCENE_GAME:			// ゲーム画面の更新
		UpdateGame();
		break;

	case SCENE_RESULT:		// リザルト画面の更新

		UpdateGame();		//ゲーム画面を保持する

		UpdateResult();	
		break;
	}

	// フェード処理の更新
	UpdateFade();
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	LPDIRECT3DDEVICE9 g_pD3DDevice = GetDevice();

	// バックバッファ＆Ｚバッファのクリア
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3Dによる描画の開始
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (GetScene())
		{
		case SCENE_TITLE:		// タイトル画面の描画
			DrawTitle();
			break;

		case SCENE_GAME:		// ゲーム画面の描画
			DrawGame();
			break;

		case SCENE_RESULT:		// リザルト画面の描画

			DrawGame();			//ゲーム画面を保持する

			DrawResult();
			break;
		}

		// フェード描画
		DrawFade();

		// デバッグ表示処理の描画
		DrawDebugProc();


		// Direct3Dによる描画の終了
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}


//=============================================================================
// ポーズ判定
//=============================================================================
void Pause(bool& b)
{
	//ポーズorポーズ解除
	if (GetScene() == SCENE_GAME)
	{
		if (GetKeyboardTrigger(DIK_F3) ||
			(IsButtonPress(0, BUTTON_SHARE) && IsButtonTrigger(0, BUTTON_OPTIONS)) ||
			(IsButtonTrigger(0, BUTTON_SHARE) && IsButtonPress(0, BUTTON_OPTIONS)))
		{
			b = !b;
		}
	}

}

//=============================================================================
// 強制的にタイトル画面に戻る判定
//=============================================================================
void Retire(void)
{
	if (GetKeyboardTrigger(DIK_F4) ||
		(IsButtonPress(0, BUTTON_L3) && IsButtonTrigger(0, BUTTON_R3)) ||
		(IsButtonTrigger(0, BUTTON_L3) && IsButtonPress(0, BUTTON_R3)))
	{		
		SetScene(SCENE_TITLE);
	}

}

