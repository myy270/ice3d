//=============================================================================
//
// DirectXの処理 [dx.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "dx.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
LPDIRECT3D9 g_pD3D = NULL;						// Direct3Dオブジェクト
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;		// Deviceオブジェクト(描画に必要)

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitDX(HWND hWnd, BOOL bWindow)
{		
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);	// Direct3Dオブジェクトの作成

	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	
	// 現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));						// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;					// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;					// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;					// カラーモードの指定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;				// 映像信号に同期してフリップする
	d3dpp.Windowed = bWindow;								// ウィンドウモード
	d3dpp.EnableAutoDepthStencil = TRUE;					// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;				// デプスバッファとして16bitを使う

	if (bWindow)
	{// ウィンドウモード
		d3dpp.FullScreen_RefreshRateInHz = 0;								// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;			// インターバル
	}
	else
	{// フルスクリーンモード
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;			// インターバル
	}

	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
									D3DDEVTYPE_HAL,
									hWnd,
									D3DCREATE_HARDWARE_VERTEXPROCESSING,
									&d3dpp, &g_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
										D3DDEVTYPE_HAL,
										hWnd,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&d3dpp, &g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
											D3DDEVTYPE_REF,
											hWnd,
											D3DCREATE_SOFTWARE_VERTEXPROCESSING,
											&d3dpp, &g_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// レンダリングステートパラメータの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);					// 裏面をカリング
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);							// Zバッファを使用
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);					// αブレンドを行う
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// αソースカラーの指定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// αデスティネーションカラーの指定
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);					//頂点法線の自動正規化を有効にするには TRUE

	// サンプラーステートパラメータの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);		// テクスチャアドレッシング方法(U値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);		// テクスチャアドレッシング方法(V値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);		// テクスチャ縮小フィルタモードを設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);		// テクスチャ拡大フィルタモードを設定

	// テクスチャステージステートパラメータの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);		// アルファブレンディング処理
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		// 最初のアルファ引数
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);		// ２番目のアルファ引数

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitDX(void)
{
	SAFE_RELEASE(g_pD3D);
	SAFE_RELEASE(g_pD3DDevice);
}

//=============================================================================
// デバイスの取得
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}