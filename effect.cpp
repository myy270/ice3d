//=============================================================================
//
// エフェクト処理 [effect.cpp]
// Author : 麦英泳
// 
//=============================================================================
#include "effect.h"
#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_EFFECT			"data/TEXTURE/effect000.jpg"	// 読み込むテクスチャファイル名

#define	MAX_EFFECT				(4096)							// エフェクト最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

LPDIRECT3DTEXTURE9		g_pD3DTextureEffect = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEffect = NULL;		// 頂点バッファインターフェースへのポインタ

EFFECT					g_aEffect[MAX_EFFECT];			// エフェクトワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報の作成
	//ここのサイズ、色の情報入れなくてもいい、どうせ後、上書きされる
	MakeVertex(pDevice, FVF_VERTEX_3D, g_pD3DVtxBuffEffect, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f,D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), MAX_EFFECT);


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_EFFECT,			// ファイルの名前
								&g_pD3DTextureEffect);	// 読み込むメモリー

	//デフォルト値をセット
	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].rot = D3DXVECTOR3(-D3DX_PI * 0.5f, 0.0f, 0.0f);	//生成されたポリゴンはXOZ平面にあるので、XOY平面に回転する必要ある
		g_aEffect[nCntEffect].bUse = false;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect(void)
{
	SAFE_RELEASE(g_pD3DTextureEffect);
	SAFE_RELEASE(g_pD3DVtxBuffEffect);

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect(void)
{
	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if(g_aEffect[nCntEffect].bUse)
		{
			//移動する
			g_aEffect[nCntEffect].pos.x += g_aEffect[nCntEffect].move.x;
			g_aEffect[nCntEffect].pos.z += g_aEffect[nCntEffect].move.z;

			//アルファ値を減衰する
			g_aEffect[nCntEffect].col.a -= g_aEffect[nCntEffect].nDecAlpha;
			if(g_aEffect[nCntEffect].col.a <= 0.0f)
			{
				g_aEffect[nCntEffect].col.a = 0.0f;
			}
			SetVtxDataCor(g_pD3DVtxBuffEffect, FVF_VERTEX_3D, g_aEffect[nCntEffect].col, nCntEffect);

			//時間をカウントダウン
			g_aEffect[nCntEffect].nTimer--;
			if(g_aEffect[nCntEffect].nTimer <= 0)
			{
				g_aEffect[nCntEffect].bUse = false;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxRot,mtxTemp, mtxTranslate, g_mtxWorldEffect;

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);				// パーティクル同士のお互いに、遮らないなうに
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);					//ビルボードはライティングの影響を受けない

	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if(g_aEffect[nCntEffect].bUse)
		{
			// マトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldEffect);
			D3DXMatrixIdentity(&mtxTemp);

			// ビューマトリックスを取得
			mtxView = GetMtxView();

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEffect[nCntEffect].rot.y, g_aEffect[nCntEffect].rot.x, g_aEffect[nCntEffect].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldEffect, &g_mtxWorldEffect, &mtxRot);

			//カメラの回転を相殺して、いつもカメラに向かうように
			mtxTemp._11 = mtxView._11;
			mtxTemp._12 = mtxView._21;
			mtxTemp._13 = mtxView._31;
			mtxTemp._21 = mtxView._12;
			mtxTemp._22 = mtxView._22;
			mtxTemp._23 = mtxView._32;
			mtxTemp._31 = mtxView._13;
			mtxTemp._32 = mtxView._23;
			mtxTemp._33 = mtxView._33;
			D3DXMatrixMultiply(&g_mtxWorldEffect, &g_mtxWorldEffect, &mtxTemp);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_aEffect[nCntEffect].pos.x, g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldEffect, &g_mtxWorldEffect, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldEffect);

			DrawPolygon(pDevice, FVF_VERTEX_3D, g_pD3DVtxBuffEffect, g_pD3DTextureEffect, nCntEffect);

		}
	}

	// 各パラメーターのデフォルト値に戻る
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//=============================================================================
// エフェクトの設定
//=============================================================================
int SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fSizeX, float fSizeY, int nTimer)
{
	int nIdxEffect = -1;

	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if(!g_aEffect[nCntEffect].bUse)
		{
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].move = move;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fSizeX = fSizeX;
			g_aEffect[nCntEffect].fSizeY = fSizeY;
			g_aEffect[nCntEffect].nTimer = nTimer;
			g_aEffect[nCntEffect].nDecAlpha = col.a / nTimer;	//重要!!!
			g_aEffect[nCntEffect].bUse = true;

			// 頂点座標の設定
			SetVtxDataVtx(g_pD3DVtxBuffEffect, FVF_VERTEX_3D, D3DXVECTOR3(0.0f, 0.0f, 0.0f), fSizeX, fSizeY, nCntEffect);

			// 頂点カラーの設定
			SetVtxDataCor(g_pD3DVtxBuffEffect, FVF_VERTEX_3D, g_aEffect[nCntEffect].col, nCntEffect);

			nIdxEffect = nCntEffect;

			break;
		}
	}

	return nIdxEffect;
}
