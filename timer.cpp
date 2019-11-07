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
#define	TEXTURE_NUM_TIMER		"data/TEXTURE/number000.png"	// タイマーの数字
#define	TEXTURE_FRAME_TIMER		"data/TEXTURE/frame_timer.png"	// タイマーの枠

#define	NUM_WIDTH				FIT_WIDTH(35)													// タイマーの単体の数字の幅
#define	NUM_HEIGHT				FIT_HEIGHT(50)													// タイマーの単体の数字の高さ
#define	NUM_INTERVAL			FIT_WIDTH(0)													// タイマーの数字の表示間隔
#define	NUM_PLACE				(3)																// タイマーの数字の桁数
#define	NUM_ALL_WIDTH			NUM_WIDTH * NUM_PLACE + NUM_INTERVAL * (NUM_PLACE - 1)			// タイマーの全部の数字の幅
#define	NUM_POS_X				TEXTURE_CENTER_X(NUM_ALL_WIDTH)									// 一番左の数字の左上頂点のX座標
#define	NUM_POS_Y				SCREEN_HEIGHT * 0.035f											// 一番左の数字の左上頂点のY座標

#define	TIMER_PADDING_LEFT		FIT_WIDTH(17.5)													// タイマーの数字とフレームの左間隔
#define	TIMER_PADDING_RIGHT		FIT_WIDTH(17.5)													// タイマーの数字とフレームの右間隔
#define	TIMER_PADDING_TOP		FIT_HEIGHT(25)													// タイマーの数字とフレームの上間隔
#define	TIMER_PADDING_BOTTOM	FIT_HEIGHT(5)													// タイマーの数字とフレームの下間隔
#define	TIMER_POS_X				NUM_POS_X - TIMER_PADDING_LEFT									// タイマーのフレームの左上頂点のX座標
#define	TIMER_POS_Y				NUM_POS_Y - TIMER_PADDING_TOP									// タイマーのフレームの左上頂点のY座標
#define	TIMER_WIDTH				NUM_ALL_WIDTH + TIMER_PADDING_LEFT + TIMER_PADDING_RIGHT		// タイマーの幅
#define	TIMER_HEIGHT			NUM_HEIGHT + TIMER_PADDING_TOP + TIMER_PADDING_BOTTOM			// タイマーの高さ

#define SECOND_MAX				(int)(powf(10.0f, (float)NUM_PLACE) - 1)						//タイマーの最大値	単位は秒

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice);
void SetTextureTimer(int idx, int number);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTimer[2] = {NULL, NULL};		// [0]:タイマーの数字のテクスチャ―　[1]:タイマーの枠のテクスチャ―
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffTimer = NULL;					// 頂点バッファインターフェースへのポインタ
				
int						g_nTimerCount;								// タイマーのカウント		単位はフレーム
bool					g_bEnableTimer;								// タイマー動作ON/OFF
bool					g_bClockOver;								// 時間が終わるかどうか
//=============================================================================
// 初期化処理
// second:タイマーの初期設定時間	単位は秒
//=============================================================================
HRESULT InitTimer(int second)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (second > SECOND_MAX)		//最大値を超えれば
	{
		second = SECOND_MAX;		//最大値になる
	}


	g_nTimerCount = second * FPS;


	g_bEnableTimer = true;

	g_bClockOver = false;

	// 頂点情報の作成
	MakeVertexTimer(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_NUM_TIMER,			// ファイルの名前
								&g_pD3DTextureTimer[0]);	// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_FRAME_TIMER,			// ファイルの名前
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
	if (GetKeyboardTrigger(DIK_SUBTRACT))
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

	if ((g_nTimerCount <= 0) && (g_bClockOver == false))
	{
		g_bClockOver = true;	//時間が終わった

		SetFade(FADE_OUT);		//リザルト画面へフェード
	}

	//タイマーの各桁の数字を求める
	for(int i = 0; i < NUM_PLACE; i++)			//iは数字の左から始まる添え字
	{
		int count = g_nTimerCount + 59;			//例えば、残り0.5秒としても、画面上には1秒として表示するための役割
		count = count / FPS;					//フレーム単位から秒単位に転化する
		
		//タイマーのの各桁の数字を左から計算する
		int number = (count % (int)(powf(10.0f, (float)(NUM_PLACE - i))))	//指している桁の左部分を捨てて、残りの部分をとる;	例えば、count = 123, NUM_PLACE = 3 , i = 1,ここの分子 = 23
						/ (int)(powf(10.0f, (float)(NUM_PLACE - i - 1)));	//例えば、count = 123, NUM_PLACE = 3 ,i = 1,ここの分母 = 10

		//その桁に対応のテクスチャをセット
		SetTextureTimer(i, number);
	}
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
// 頂点の作成
//=============================================================================
HRESULT MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice)
{

	MakeVertex(pDevice, g_pD3DVtxBuffTimer, NUM_PLACE + 1);		//+1 はタイマーのフレームを含むこと

	{//頂点バッファの中身を埋める		
		for(int nCntPlace = 0; nCntPlace <= NUM_PLACE; nCntPlace++)		//nCntPlaceは数字の左から始める添え字
		{
			if (nCntPlace < NUM_PLACE)
			{//	タイマーの数字
				
				// 頂点座標の設定
				SetVtxData(g_pD3DVtxBuffTimer, D3DXVECTOR3(NUM_POS_X + nCntPlace * (NUM_WIDTH + NUM_INTERVAL), NUM_POS_Y, 0.0f), NUM_WIDTH, NUM_HEIGHT, nCntPlace);

				//テクスチャ―座標の設定	初期値、あとで変更する
				SetVtxData(g_pD3DVtxBuffTimer, D3DXVECTOR2(0.0f, 0.0f), 0.1f, 1.0f, nCntPlace);
			}
			else
			{//タイマーのフレーム

				// 頂点座標の設定
				SetVtxData(g_pD3DVtxBuffTimer, D3DXVECTOR3(TIMER_POS_X, TIMER_POS_Y, 0.0f), TIMER_WIDTH, TIMER_HEIGHT, nCntPlace);

				//テクスチャ―座標の設定
				SetVtxData(g_pD3DVtxBuffTimer, D3DXVECTOR2(0.0f, 0.0f), 1.0f, 1.0f, nCntPlace);
			}

			// rhwの設定
			SetVtxData(g_pD3DVtxBuffTimer, 1.0f, nCntPlace);

			// 反射光の設定		シアン色にする
			SetVtxData(g_pD3DVtxBuffTimer, D3DCOLOR_RGBA(0, 255, 255, 255), nCntPlace);


		}
	}

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
// idx:数字の左から始まる添え字
// number:この桁の数字
//=============================================================================
void SetTextureTimer(int idx, int number)
{
	//安全のために
	if (idx >= NUM_PLACE)
	{
		return;
	}

	SetVtxData(g_pD3DVtxBuffTimer, D3DXVECTOR2(number * 0.1f, 0.0f), 0.1f, 1.0f, idx);

}

//=============================================================================
// 
//=============================================================================
void SetEnableTimer(bool b)
{
	g_bEnableTimer = b;
}

//=============================================================================
// 
//=============================================================================
void SetTimer(int second)
{
	g_nTimerCount = second * FPS;	//秒数*フレーム
}

//=============================================================================
// 
//=============================================================================
int GetTimer()
{
	return g_nTimerCount;
}

//=============================================================================
// 
//=============================================================================
bool IsClockOver()
{
	return g_bClockOver;
}
