//=============================================================================
//
// 影処理 [shadow.cpp]
// Author : 麦英泳
// 
//=============================================================================
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SHADOW		"data/TEXTURE/shadow000.jpg"	// 読み込むテクスチャファイル名

#define	MAX_SHADOW			(128)							// 影最大数
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureShadow = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffShadow = NULL;		// 頂点バッファインターフェースへのポインタ

SHADOW					g_aShadow[MAX_SHADOW];			// 影ワーク
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	MakeVertex(pDevice, FVF_VERTEX_3D, g_pD3DVtxBuffShadow, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 
																			D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), MAX_SHADOW);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_SHADOW,				// ファイルの名前
								&g_pD3DTextureShadow);		// 読み込むメモリー

	for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{//デフォルト値
		g_aShadow[nCntShadow].size = 0.0f;
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
		g_aShadow[nCntShadow].bUse = false;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitShadow(void)
{
	SAFE_RELEASE(g_pD3DTextureShadow);
	SAFE_RELEASE(g_pD3DVtxBuffShadow);

}

//=============================================================================
// 影の位置を更新、位置の高さにより、大きさと透明度を変化する
// size:影の四辺の長さ つまり、モデルの直径
// farFromLand:モデルの正常時の滞空高さ
//=============================================================================
void UpdateShadow(int nIdxShadow, D3DXVECTOR3 pos, float farFromLand)
{
	if (nIdxShadow >= 0 && nIdxShadow < MAX_SHADOW)
	{
		g_aShadow[nIdxShadow].pos = D3DXVECTOR3(pos.x, 0.1f, pos.z);
	}

	//高さにより、影の大きさが変化する	//高ければ高いほど大きい
	float fSize = g_aShadow[nIdxShadow].size + (pos.y - farFromLand) * 0.05f;

	if (pos.y < 0.0f)
	{//地面以下に行くとき
		fSize = 0.0f;
	}

	//影の大きさを更新
	SetVtxDataVtx(g_pD3DVtxBuffShadow, FVF_VERTEX_3D, D3DXVECTOR3(0.0f, 0.0f, 0.0f), fSize, fSize , nIdxShadow);

	//高さにより、影の透明度が変化する	//高ければ高いほど透明的
	float colA = 0.5f - (pos.y - farFromLand) / 400.0f;

	if (colA < 0.0f)
	{
		colA = 0.0f;
	}
	if (pos.y < 0.0f)
	{//地面以下に行くとき
		colA = 0.0f;
	}

	////影の透明度を更新
	SetVtxDataCor(g_pD3DVtxBuffShadow, FVF_VERTEX_3D, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA), nIdxShadow);

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
			
	D3DXMATRIX mtxTranslate, g_mtxWorldShadow;				// ワールドマトリックス

	// 減算合成
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);		// 結果 = 転送先(DEST) - 転送元(SRC)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
//	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);			// Z比較なし

//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if(g_aShadow[nCntShadow].bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldShadow);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldShadow);

			// 頂点バッファをレンダリングパイプラインに設定
			pDevice->SetStreamSource(0, g_pD3DVtxBuffShadow, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureShadow);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntShadow * 4), NUM_POLYGON);
		}
	}

	// 通常ブレンド
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);				// 結果 = 転送元(SRC) + 転送先(DEST)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);				// Z比較あり

//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
}

//=============================================================================
// 影の設定
//=============================================================================
int SetShadow(D3DXVECTOR3 pos, float fSize)
{
	int nIdxShadow = -1;

	for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if(!g_aShadow[nCntShadow].bUse)
		{
			g_aShadow[nCntShadow].size = fSize;
			g_aShadow[nCntShadow].pos = pos;
			g_aShadow[nCntShadow].bUse = true;

			//大きさを反映する
			SetVtxDataVtx(g_pD3DVtxBuffShadow, FVF_VERTEX_3D, D3DXVECTOR3(0.0f, 0.0f, 0.0f), fSize, fSize, nCntShadow);

			nIdxShadow = nCntShadow;

			break;
		}
	}

	return nIdxShadow;
}

//=============================================================================
// 影の削除
//=============================================================================
void DeleteShadow(int nIdxShadow)
{
	if(nIdxShadow >= 0 && nIdxShadow < MAX_SHADOW)
	{
		g_aShadow[nIdxShadow].bUse = false;
	}
}
