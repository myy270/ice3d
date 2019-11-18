//=============================================================================
//
// フェード処理 [fade.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "fade.h"
#include "scene.h"
#include "timer.h"
#include "score.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	FADE_RATE				(0.02f)									// フェードのアルファ値変化量
#define	DEFAULT_FADETYPE		(FADE_IN)								// デフォルトのフェードの状態
#define	FADE_COLOR				(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))		// フェードの幕の色

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureFade = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffFade = NULL;	// 頂点バッファインターフェースへのポインタ
FADETYPE				g_fade;						// フェードの状態
D3DXCOLOR				g_colorFade;				// フェードの幕の色


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_fade = DEFAULT_FADETYPE;						// ゲームを開くとき、フェードインする。

	g_colorFade = FADE_COLOR;

	// 頂点情報の作成
	MakeVertex(pDevice, FVF_VERTEX_2D, g_pD3DVtxBuffFade, D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
	SetVtxDataCor(g_pD3DVtxBuffFade, FVF_VERTEX_2D, g_colorFade);		// 色を再設定

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFade(void)
{
	SAFE_RELEASE(g_pD3DTextureFade);
	SAFE_RELEASE(g_pD3DVtxBuffFade);

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFade(void)
{
	if(g_fade != FADE_NONE)
	{// フェード処理中
		if(g_fade == FADE_OUT)
		{// フェードアウト処理
			g_colorFade.a += FADE_RATE;						// α値を加算して画面を消していく

			if(g_colorFade.a >= 1.0f)
			{// フェードアウト完成の時	
				g_colorFade.a = 1.0f;

				SetFade(FADE_IN);							// フェードイン処理に切り替え
				
				// 次のシーンの設定
				SCENE scene = GetScene();					// 現在のシーンを取得
				scene = (SCENE)((scene + 1) % SCENE_MAX);	// シーンを１つ進める　//intからsceneにキャストする必要ある
				SetScene(scene);							// シーンを設定

				if (scene == SCENE_RESULT)
				{//リザルト画面だと
					CompareScore();							// スコアを比較する
				}
			}

		}
		else if(g_fade == FADE_IN)
		{// フェードイン処理
			g_colorFade.a -= FADE_RATE;						// α値を減算して画面を浮き上がらせる

			if(g_colorFade.a <= 0.0f)
			{// フェードイン完成の時				
				g_colorFade.a = 0.0f;

				SetFade(FADE_NONE);
			}
		}
			
		SetVtxDataCor(g_pD3DVtxBuffFade, FVF_VERTEX_2D, g_colorFade);			// 色を再設定
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DrawPolygon(pDevice, FVF_VERTEX_2D, g_pD3DVtxBuffFade, g_pD3DTextureFade);
}

//=============================================================================
// フェードの状態の設定
//=============================================================================
void SetFade(FADETYPE fade)
{
	g_fade = fade;
}

//=============================================================================
// フェードの状態の取得
//=============================================================================
FADETYPE GetFade(void)
{
	return g_fade;
}

