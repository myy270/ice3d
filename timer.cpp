//=============================================================================
//
// タイマー処理 [timer.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "timer.h"
#include "fade.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_NUM				"data/TEXTURE/number000.png"									// タイマーの数字
#define	TEXTURE_FRAME			"data/TEXTURE/frame_timer.png"									// タイマーの枠

#define	NUM_WIDTH				FIT_WIDTH(35)													// タイマーの単体の数字の幅
#define	NUM_HEIGHT				FIT_HEIGHT(50)													// タイマーの単体の数字の高さ
#define	NUM_INTERVAL			FIT_WIDTH(0)													// タイマーの数字の表示間隔
#define	NUM_PLACE				(3)																// タイマーの数字（単位：秒）の桁数
#define	NUM_ALL_WIDTH			NUM_WIDTH * NUM_PLACE + NUM_INTERVAL * (NUM_PLACE - 1)			// タイマーの全部の数字の幅
#define	NUM_POS_X				TEXTURE_CENTER_X(NUM_ALL_WIDTH)									// タイマーの先頭の数字の左上頂点のX座標
#define	NUM_POS_Y				FIT_HEIGHT(25.0f)												// タイマーの先頭の数字の左上頂点のY座標

#define	PADDING_LEFT			FIT_WIDTH(17.5)													// タイマーの数字とフレームの左間隔
#define	PADDING_RIGHT			FIT_WIDTH(17.5)													// タイマーの数字とフレームの右間隔
#define	PADDING_TOP				FIT_HEIGHT(25)													// タイマーの数字とフレームの上間隔
#define	PADDING_BOTTOM			FIT_HEIGHT(5)													// タイマーの数字とフレームの下間隔

#define	FRAME_POS_X				NUM_POS_X - PADDING_LEFT										// タイマーのフレームの左上頂点のX座標
#define	FRAME_POS_Y				NUM_POS_Y - PADDING_TOP											// タイマーのフレームの左上頂点のY座標
#define	FRAME_WIDTH				NUM_ALL_WIDTH + PADDING_LEFT + PADDING_RIGHT					// タイマーのフレームの幅
#define	FRAME_HEIGHT			NUM_HEIGHT + PADDING_TOP + PADDING_BOTTOM						// タイマーのフレームの高さ

#define TIME_MAX				(int)(powf(10.0f, (float)NUM_PLACE) - 1)						// タイマーの最大値	単位は秒

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTimer[2] = {NULL, NULL};		// [0]:タイマーの数字のテクスチャ―　[1]:タイマーの枠のテクスチャ―
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffTimer = NULL;					// 頂点バッファインターフェースへのポインタ
				
int						g_nTimerCount;								// タイマーのカウント		単位はフレーム
bool					g_bEnableTimer;								// タイマー動作ON/OFF
bool					g_bTimeEnd;								// 時間が終わったかどうか
//=============================================================================
// 初期化処理
// second:タイマーの初期設定時間	単位は秒
//=============================================================================
HRESULT InitTimer(int second)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (second > TIME_MAX)		//最大値を超えれば
	{
		second = TIME_MAX;		//最大値になる
	}


	g_nTimerCount = second * FPS;	//秒単位からフレーム単位に転化


	g_bEnableTimer = true;

	g_bTimeEnd = false;

	// 頂点情報の作成
	MakeVertexNumFrame(pDevice, g_pD3DVtxBuffTimer, NUM_PLACE,
		D3DXVECTOR3(NUM_POS_X, NUM_POS_Y, 0.0f), NUM_WIDTH, NUM_HEIGHT, NUM_INTERVAL,
		D3DXVECTOR3(FRAME_POS_X, FRAME_POS_Y, 0.0f), FRAME_WIDTH, FRAME_HEIGHT,
		D3DCOLOR_RGBA(0, 255, 255, 255));	//シアン


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_NUM,			// ファイルの名前
								&g_pD3DTextureTimer[0]);	// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_FRAME,			// ファイルの名前
								&g_pD3DTextureTimer[1]);	// 読み込むメモリー

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTimer(void)
{
	SAFE_RELEASE(g_pD3DTextureTimer[0]);
	SAFE_RELEASE(g_pD3DTextureTimer[1]);
	SAFE_RELEASE(g_pD3DVtxBuffTimer);

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTimer(void)
{

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_SUBTRACT))		//テンキーのマイナス
	{
		g_nTimerCount = 5 * FPS;	//開発者機能、タイマーの時間を5秒にする
	}
#endif

	if(g_bEnableTimer)
	{
		g_nTimerCount--;			//毎フレームにカウントダウン
	}

	if (g_nTimerCount < 0)
	{
		g_nTimerCount = 0;
	}

	if ((g_nTimerCount <= 0) && (g_bTimeEnd == false))
	{
		g_bTimeEnd = true;	//時間が終わった

		SetFade(FADE_OUT);		//リザルト画面へフェード
	}

	int count = g_nTimerCount + 59;			//残り0.5秒としても、画面上には1秒として表示するための役割
	count = count / FPS;					//フレーム単位から秒単位に転化する

	SetVtxData(g_pD3DVtxBuffTimer, count, NUM_PLACE);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DrawPolygon(pDevice, g_pD3DVtxBuffTimer, g_pD3DTextureTimer[0], 0, NUM_PLACE - 1);

	DrawPolygon(pDevice, g_pD3DVtxBuffTimer, g_pD3DTextureTimer[1], NUM_PLACE, NUM_PLACE);
}

//=============================================================================
// 時間停止などの機能
//=============================================================================
void SetEnableTimer(bool b)
{
	g_bEnableTimer = b;
}

//=============================================================================
//  時間を再セットの機能
//=============================================================================
void SetTimer(int second)
{
	g_nTimerCount = second * FPS;	//秒数*フレーム
}

//=============================================================================
// 時間のフレーム単位の量をゲット
//=============================================================================
int GetTimer()
{
	return g_nTimerCount;
}

//=============================================================================
// 時間終わったかどうか
//=============================================================================
bool IsTimeEnd()
{
	return g_bTimeEnd;
}
