//=============================================================================
//
// リザルト画面処理 [result.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "result.h"
#include "input.h"
#include "fade.h"
#include "score.h"
#include "title.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_RESULT_WIN			"data/TEXTURE/win_logo.png"				//勝つ　テクスチャファイル名
#define	TEXTURE_RESULT_GAMEOVER		"data/TEXTURE/gameover_logo.png"		//ゲームオーバー　テクスチャファイル名
#define	TEXTURE_RESULT_DRAW			"data/TEXTURE/draw_logo.png"			//引き分け　テクスチャファイル名

#define	RESULT_LOGO_POS_X			(SCREEN_WIDTH * 0.19f)					// リザルトロゴの位置(X座標)
#define	RESULT_LOGO_POS_Y			(SCREEN_HEIGHT * 0.65f)					// リザルトロゴの位置(Y座標)
#define	RESULT_LOGO_WIDTH			FIT_WIDTH(800)							// リザルトロゴの幅
#define	RESULT_LOGO_HEIGHT			FIT_HEIGHT(200)							// リザルトロゴの高さ

#define	COUNT_APPERA_RESULT			(60)									// リザルトロゴ出現までの待ち時間	

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9		g_pD3DVtxBuffResultLogo = NULL;			// 頂点バッファインターフェースへのポインタ

//テクスチャファイル名の配列
const char* g_aTextureFile[] =
{
	TEXTURE_RESULT_WIN,
	TEXTURE_RESULT_GAMEOVER,
	TEXTURE_RESULT_DRAW
	
};

//テクスチャファイルの数
const int g_nNumTexture = sizeof(g_aTextureFile) / sizeof(const char*);	

LPDIRECT3DTEXTURE9			g_pD3DTextureResultLogo[g_nNumTexture];		// テクスチャへのポインタの配列

int							g_nCountAppearResult = 0;					// 出現までの待ち時間
float						g_fAlphaResult = 0.0f;						// リザルトロゴのα値

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nCountAppearResult = 0;
	g_fAlphaResult = 0.0f;

	// 頂点情報の作成
	MakeVertex(pDevice, FVF_VERTEX_2D, g_pD3DVtxBuffResultLogo, D3DXVECTOR3(RESULT_LOGO_POS_X, RESULT_LOGO_POS_Y, 0.0f), RESULT_LOGO_WIDTH, RESULT_LOGO_HEIGHT);

	// テクスチャの読み込み
	for (int i = 0;i < g_nNumTexture;i++)
	{
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			g_aTextureFile[i],									// ファイルの名前
			&g_pD3DTextureResultLogo[i]);						// 読み込むメモリー
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{	
	SAFE_RELEASE(g_pD3DVtxBuffResultLogo);

	for (int i = 0; i < g_nNumTexture; i++)
	{
		SAFE_RELEASE(g_pD3DTextureResultLogo[i]);
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResult(void)
{
	g_nCountAppearResult++;

	//一定時間後に、ロゴが浮き上がり始める
	if(g_nCountAppearResult >= COUNT_APPERA_RESULT)
	{
		if(g_fAlphaResult < 1.0f)
		{
			g_fAlphaResult += 0.05f;

			if(g_fAlphaResult > 1.0f)
			{
				g_fAlphaResult = 1.0f;
			}

		}
	}

	if (GetFade() == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTrigger(0, BUTTON_OPTIONS))
		{
			if (g_fAlphaResult < 1.0f)
			{//ロゴの浮き上がりを完成する
				g_fAlphaResult = 1.0f;
			}
			else
			{//フェードアウトしてシーンを切り替える				
				SetFade(FADE_OUT);

				PlaySound(SOUND_LABEL_SE_RETIRE, false, true);		//タイトル画面に戻る音を再生
			}
		}

	}

	// アルファ値の更新
	SetVtxDataCor(g_pD3DVtxBuffResultLogo, FVF_VERTEX_2D, D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResult));

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPDIRECT3DTEXTURE9 texture;

	//結果によってテクスチャ―を設定
	if (GetPlayMode() == PLAY_MODE_SINGLE)
	{
		if (GetWinner() == OBJECT_PLAYER)
		{
			texture = g_pD3DTextureResultLogo[0];
		}
		else if (GetWinner() == OBJECT_ENEMY)
		{
			texture = g_pD3DTextureResultLogo[1];
		}
		else
		{//引き分けの場合
			texture = g_pD3DTextureResultLogo[2];
		}
	}
	else
	{
		if ((GetWinner() == OBJECT_PLAYER))
		{
			texture = g_pD3DTextureResultLogo[0];
		}
		else if (GetWinner() == OBJECT_ENEMY)
		{
			texture = g_pD3DTextureResultLogo[0];
		}
		else
		{//引き分けの場合
			texture = g_pD3DTextureResultLogo[2];
		}
	}

	DrawPolygon(pDevice, FVF_VERTEX_2D, g_pD3DVtxBuffResultLogo, texture);

}