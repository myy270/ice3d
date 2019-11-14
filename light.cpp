//=============================================================================
//
// ライト処理 [light.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "light.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void SetDirectionalLight(LPDIRECT3DDEVICE9 pDevice, D3DLIGHT9& light, int idx, D3DCOLORVALUE color, D3DXVECTOR3 vec);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DLIGHT9 g_aLight[3];				// ライトのワーク

//=============================================================================
// ライトの初期化処理
//=============================================================================
HRESULT InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	SetDirectionalLight(pDevice, g_aLight[0], 0, D3DXCOLOR(0.60f, 0.60f, 0.60f, 1.0f),	D3DXVECTOR3(0.20f, -0.60f, 0.80f));		//右下後に指す

	SetDirectionalLight(pDevice, g_aLight[1], 1, D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f), D3DXVECTOR3(-0.20f, 1.00f, -0.50f));		//左上前に指す

	SetDirectionalLight(pDevice, g_aLight[2], 2, D3DXCOLOR(0.25f, 0.25f, 0.25f, 1.0f), D3DXVECTOR3(0.80f, 0.10f, 0.50f));		//右上後に指す

	// ライティングモード
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	return S_OK;
}

//=============================================================================
// Directionalライトの設定
//=============================================================================
void SetDirectionalLight(LPDIRECT3DDEVICE9 pDevice,D3DLIGHT9& light, int idx, D3DCOLORVALUE color, D3DXVECTOR3 vec)
{
	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory(&light, sizeof(D3DLIGHT9));

	// ライトのタイプの設定
	light.Type = D3DLIGHT_DIRECTIONAL;

	// 拡散光の設定
	light.Diffuse = color;

	// 方向の設定
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vec);//ベクトルを正規化

	// ライトをレンダリングパイプラインに設定
	pDevice->SetLight(idx, &light);

	// ライトの設定
	pDevice->LightEnable(idx, TRUE);
}
