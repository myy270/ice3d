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
#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_RESULT_WIN		"data/TEXTURE/win_logo.png"			// 勝つ テクスチャファイル名
#define	TEXTURE_RESULT_GAMEOVER	"data/TEXTURE/gameover_logo.png"	// 負ける テクスチャファイル名

#define	RESULT_LOGO_POS_X	(SCREEN_WIDTH * 0.19f)					// リザルトロゴの位置(X座標)
#define	RESULT_LOGO_POS_Y	(SCREEN_HEIGHT * 0.65f)					// リザルトロゴの位置(Y座標)
#define	RESULT_LOGO_WIDTH	FIT_WIDTH(800)							// リザルトロゴの幅
#define	RESULT_LOGO_HEIGHT	FIT_HEIGHT(240)							// リザルトロゴの高さ

#define	COUNT_APPERA_RESULT	(60)									// リザルトロゴ出現までの待ち時間	

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffResultLogo = NULL;		// 頂点バッファインターフェースへのポインタ

LPDIRECT3DTEXTURE9		g_pD3DTextureResultLogo = NULL;		// 勝つ テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureResultLogo2 = NULL;	// 負ける テクスチャへのポインタ

int						g_nCountAppearResult = 0;			// 出現までの待ち時間
float					g_fAlphaResult = 0.0f;				// リザルトロゴのα値

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
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_RESULT_WIN,			// ファイルの名前
								&g_pD3DTextureResultLogo);	// 読み込むメモリー

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_RESULT_GAMEOVER,	// ファイルの名前
								&g_pD3DTextureResultLogo2);	// 読み込むメモリー

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{	
	SAFE_RELEASE(g_pD3DVtxBuffResultLogo);
	SAFE_RELEASE(g_pD3DTextureResultLogo);
	SAFE_RELEASE(g_pD3DTextureResultLogo2);
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

			if(g_fAlphaResult >= 1.0f)
			{
				g_fAlphaResult = 1.0f;
			}

		}
	}

	// アルファ値の更新
	SetVtxDataCor(g_pD3DVtxBuffResultLogo, FVF_VERTEX_2D, D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResult));

	// Enterを押したら、フェードアウトしてシーンを切り替える
	if(GetKeyboardTrigger(DIK_RETURN) || IsButtonTrigger(0, BUTTON_OPTIONS))
	{
		SetFade(FADE_OUT);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if ((GetPlayMode() == PLAY_MODE_SINGLE) && (GetWinner() != OBJECT_PLAYER))
	{//1pモードでプレイヤー負ける場合
		DrawPolygon(pDevice, g_pD3DVtxBuffResultLogo, g_pD3DTextureResultLogo2);
	}
	else
	{
		DrawPolygon(pDevice, g_pD3DVtxBuffResultLogo, g_pD3DTextureResultLogo);
	}
}