//=============================================================================
//
// スコア処理 [score.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "score.h"
#include "camera.h"
#include "title.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_NUM			"data/TEXTURE/numberList.png"										// 読み込むテクスチャファイル名
#define	TEXTURE_FRAME		"data/TEXTURE/frame_score.png"										// 読み込むテクスチャファイル名

#define	NUM_WIDTH			FIT_WIDTH(35)														// スコアの単体の数字の幅
#define	NUM_HEIGHT			FIT_HEIGHT(50)														// スコアの単体の数字の高さ
#define	NUM_INTERVAL		FIT_WIDTH(0)														// スコアの数字の表示間隔
#define	NUM_PLACE			(5)																	// スコアの数字の桁数
#define	NUM_ALL_WIDTH		NUM_WIDTH * NUM_PLACE + NUM_INTERVAL * (NUM_PLACE - 1)				// スコアの全部の数字の幅

#define	MARGIN_LEFT			FIT_WIDTH(20.0f)													// 左の スコアの先頭の数字とウィンドウの左縁の距離
#define	MARGIN_RIGHT		FIT_WIDTH(20.0f)													// 右の スコアの最後の数字とウィンドウの右縁の距離
#define	MARGIN_TOP			FIT_HEIGHT(30.0f)													// スコアの数字とウィンドウの上縁の距離

#define	NUM_POS_X			MARGIN_LEFT															// 左の スコアの先頭の数字の左上頂点のX座標
#define	NUM_POS_X2			(SCREEN_WIDTH - MARGIN_RIGHT - NUM_ALL_WIDTH)						// 右の スコアの先頭の数字の左上頂点のX座標
#define	NUM_POS_Y			MARGIN_TOP															// スコアの数字の左上頂点のY座標

#define	PADDING_LEFT		FIT_WIDTH(15)														// スコアの数字とフレームの左間隔
#define	PADDING_RIGHT		FIT_WIDTH(15)														// スコアの数字とフレームの右間隔
#define	PADDING_TOP			FIT_HEIGHT(25)														// スコアの数字とフレームの上間隔
#define	PADDING_BOTTOM		FIT_HEIGHT(5)														// スコアの数字とフレームの下間隔

#define	FRAME_POS_X			NUM_POS_X - PADDING_LEFT											// 左の スコアのフレームの左上頂点のX座標
#define	FRAME_POS_X2		NUM_POS_X2 - PADDING_LEFT											// 右の	スコアのフレームの左上頂点のX座標
#define	FRAME_POS_Y			NUM_POS_Y - PADDING_TOP												// スコアのフレームの左上頂点のY座標

#define	FRAME_WIDTH			NUM_ALL_WIDTH + PADDING_LEFT + PADDING_RIGHT						// スコアのフレームの幅
#define	FRAME_HEIGHT		NUM_HEIGHT + PADDING_TOP + PADDING_BOTTOM							// スコアのフレームの高さ

#define SCORE_MAX			(int)(powf(10.0f, (float)NUM_PLACE) - 1)							// スコアの最大値

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9			g_pD3DTextureScore[2] = {};		// [0]:数字のテクスチャ―　[1]:枠のテクスチャ―

LPDIRECT3DVERTEXBUFFER9		g_pD3DVtxBuffScore = NULL;		// 左スコアの頂点バッファインターフェースへのポインタ
LPDIRECT3DVERTEXBUFFER9		g_pD3DVtxBuffScore2 = NULL;		// 右スコアの頂点バッファインターフェースへのポインタ 

int							g_score;						// 左のスコア
int							g_score2;						// 右のスコア

OBJECT						g_winner;						// 勝者

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// スコアの初期化
	g_score = 0;
	g_score2 = 0;

	g_winner = OBJECT_NULL;	

	// 左スコアの　頂点情報の作成
	MakeVertexNumFrame(pDevice, g_pD3DVtxBuffScore, NUM_PLACE,
		D3DXVECTOR3(NUM_POS_X, NUM_POS_Y, 0.0f), NUM_WIDTH, NUM_HEIGHT, NUM_INTERVAL,
		D3DXVECTOR3(FRAME_POS_X, FRAME_POS_Y, 0.0f), FRAME_WIDTH, FRAME_HEIGHT,
		D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f));	//オレンジ

	// 右スコアの　頂点情報の作成
	MakeVertexNumFrame(pDevice, g_pD3DVtxBuffScore2, NUM_PLACE,
		D3DXVECTOR3(NUM_POS_X2, NUM_POS_Y, 0.0f), NUM_WIDTH, NUM_HEIGHT, NUM_INTERVAL,
		D3DXVECTOR3(FRAME_POS_X2, FRAME_POS_Y, 0.0f), FRAME_WIDTH, FRAME_HEIGHT,
		D3DCOLOR_RGBA(255, 170, 192, 255));	//ピンク
		

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_NUM,				// ファイルの名前
								&g_pD3DTextureScore[0]);	// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_FRAME,				// ファイルの名前
								&g_pD3DTextureScore[1]);	// 読み込むメモリー

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	SAFE_RELEASE(g_pD3DTextureScore[0]);
	SAFE_RELEASE(g_pD3DTextureScore[1]);
	SAFE_RELEASE(g_pD3DVtxBuffScore);
	SAFE_RELEASE(g_pD3DVtxBuffScore2);

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{
	//数字のテクスチャ―を更新
	SetVtxDataTexNum(g_pD3DVtxBuffScore, g_score, NUM_PLACE);
	SetVtxDataTexNum(g_pD3DVtxBuffScore2, g_score2, NUM_PLACE);

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//左のスコア
	DrawPolygon(pDevice, g_pD3DVtxBuffScore, g_pD3DTextureScore[0], 0, NUM_PLACE - 1);

	DrawPolygon(pDevice, g_pD3DVtxBuffScore, g_pD3DTextureScore[1], NUM_PLACE, NUM_PLACE);

	//右のスコア
	DrawPolygon(pDevice, g_pD3DVtxBuffScore2, g_pD3DTextureScore[0], 0, NUM_PLACE - 1);

	DrawPolygon(pDevice, g_pD3DVtxBuffScore2, g_pD3DTextureScore[1], NUM_PLACE, NUM_PLACE);

}

//=============================================================================
// スコアの変更
//=============================================================================
void ChangeScore(OBJECT obj,int value)
{
	int* ptr;

	if (obj == OBJECT_PLAYER)
	{
		ptr = &g_score;
	}
	else
	{
		ptr = &g_score2;
	}

	*ptr += value;

	if(*ptr < 0)
	{
		*ptr = 0;
	}
	else if(*ptr > SCORE_MAX)
	{
		*ptr = SCORE_MAX;
	}

}

//=============================================================================
// スコアの比較
//=============================================================================
void CompareScore()
{
	if (g_winner == OBJECT_NULL)
	{
		if (g_score >= g_score2)
		{//プレイヤー勝つ場合
			g_winner = OBJECT_PLAYER;
		}
		else
		{//プレイヤー負ける場合
			g_winner = OBJECT_ENEMY;
		}

		if ((GetPlayMode() == PLAY_MODE_SINGLE) && (g_winner == OBJECT_ENEMY))
		{//AIが勝つ場合
			StopSound(SOUND_LABEL_BGM000, false);				//BGMを停止
			PlaySound(SOUND_LABEL_SE_GAMEOVER, false, true);	//ゲームオーバー音を再生
		}
		else
		{//プレイヤー(1pか2p)が勝つ場合
			SetCameraMode(CAMERA_MODE_CUTSCENE);				//カットシーンする	

			StopSound(SOUND_LABEL_BGM000, false);				//BGMを停止
			PlaySound(SOUND_LABEL_SE_WIN, false, true);			//勝つ音を再生
		}
	}

}

//=============================================================================
// 勝者をゲット
//=============================================================================
OBJECT GetWinner()
{
	return g_winner;
}