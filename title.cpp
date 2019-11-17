//=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TITLE_BG		"data/TEXTURE/TITLE_BG.jpg"				// タイトル画面の背景
#define	TEXTURE_TITLE_LOGO		"data/TEXTURE/TITLE_LOGO.png"			// タイトルロゴ
#define	TEXTURE_PRESS_START		"data/TEXTURE/PRESS_START.png"			// タイトル画面の「PRESS START」ロゴ
#define	TEXTURE_MENU_1P2P		"data/TEXTURE/MENU_1P2P.png"			// 1p2p選択メニュー


#define	TITLE_LOGO_WIDTH		FIT_WIDTH(640 * 0.7f)					// タイトルロゴの幅
#define	TITLE_LOGO_HEIGHT		FIT_HEIGHT(640 * 0.7f)				// タイトルロゴの高さ
#define	TITLE_LOGO_POS_X		TEXTURE_CENTER_X(TITLE_LOGO_WIDTH)		// タイトルロゴの左上頂点のX座標
#define	TITLE_LOGO_POS_Y		(SCREEN_HEIGHT * 0.05f)					// タイトルロゴの左上頂点のY座標

#define	PRESS_START_WIDTH		FIT_WIDTH(289 * 1.3f) 				// 「PRESS START」ロゴの幅
#define	PRESS_START_HEIGHT		FIT_HEIGHT(145 * 1.3f) 				// 「PRESS START」ロゴの高さ
#define	PRESS_START_POS_X		TEXTURE_CENTER_X(PRESS_START_WIDTH)		// 「PRESS START」ロゴの左上頂点のX座標
#define	PRESS_START_POS_Y		(SCREEN_HEIGHT * 0.7f)					// 「PRESS START」ロゴの左上頂点のY座標

#define	MENU_1P2P_WIDTH			FIT_WIDTH(1660 * 0.35f)					// 1p2p選択メニューの幅			
#define	MENU_1P2P_HEIGHT		FIT_HEIGHT(576 * 0.35f) 				// 1p2p選択メニューの高さ
#define	MENU_1P2P_POS_X			TEXTURE_CENTER_X(MENU_1P2P_WIDTH)		// 1p2p選択メニューの左上頂点のX座標
#define	MENU_1P2P_POS_Y			(SCREEN_HEIGHT * 0.6f)					// 1p2p選択メニューの左上頂点のY座標

#define	DELTA_TITLE_LOGO_ALPHA	(0.005f)								// タイトルロゴのフェードインのアルファ変化値

#define	COUNT_APPEAR_START		(60)									// 「PRESS START」ロゴ初めて出現するまでの待ち時間
#define	INTERVAL_DISP_START		(60)									// 「PRESS START」ロゴの点灯時間
#define	INTERVAL_UNDISP_START	(20)									// 「PRESS START」ロゴの消灯時間

#define	INDEX_MAX_MENU_1P2P		(2)										// 1p2p選択メニューの最大項目数
#define	CURSOR_RATE				(0.1735f)								// カーソルのテクスチャ―X座標
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

void TitleEffect(void);
void Menu1P2P(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTitleBG = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffTitleBG = NULL;		// 頂点バッファインターフェースへのポインタ

LPDIRECT3DTEXTURE9		g_pD3DTextureTitleLogo = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffTitleLogo = NULL;		// 頂点バッファインターフェースへのポインタ

LPDIRECT3DTEXTURE9		g_pD3DTextureStart = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffStart = NULL;			// 頂点バッファインターフェースへのポインタ

LPDIRECT3DTEXTURE9		g_pD3DTextureMenu1P2P = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffMenu1P2P = NULL;		// 頂点バッファインターフェースへのポインタ


float					g_fAlphaTitleLogo;					// タイトルロゴのα値
int						g_nCountAppearStart;				// 「PRESS START」ロゴ初めて出現するまでのカウント時間
int						g_nCountDispStart;					// 「PRESS START」ロゴ初めて出現してから、点滅用のカウント時間
bool					g_bDispStart;						// 「PRESS START」ロゴを表示するかどうか

bool					g_bDispMenu1P2P;					//1p2p選択メニューを表示するかどうか
int						g_nCursorIdx;						//カーソルインデクス(1p2p選択の答えを記録するため)
bool					g_bChosedMenu1P2P;					//1p2p選択メニューを選択したかどうか


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_fAlphaTitleLogo = 0.0f;
	g_nCountAppearStart = 0;
	g_nCountDispStart = 0;
	g_bDispStart = false;

	g_bDispMenu1P2P = false;
	g_nCursorIdx = 0;
	g_bChosedMenu1P2P = false;

	// 頂点情報の作成
	// タイトル画面の背景
	MakeVertex(pDevice, FVF_VERTEX_2D, g_pD3DVtxBuffTitleBG, D3DXVECTOR3(0.0f,0.0f,0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);

	// タイトルロゴ
	MakeVertex(pDevice, FVF_VERTEX_2D, g_pD3DVtxBuffTitleLogo, D3DXVECTOR3(TITLE_LOGO_POS_X, TITLE_LOGO_POS_Y, 0.0f), TITLE_LOGO_WIDTH, TITLE_LOGO_HEIGHT);
	// タイトルロゴのアルファ値を0にする
	SetVtxDataCor(g_pD3DVtxBuffTitleLogo, FVF_VERTEX_2D, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	// タイトル画面の「PRESS START」ロゴ
	MakeVertex(pDevice, FVF_VERTEX_2D, g_pD3DVtxBuffStart, D3DXVECTOR3(PRESS_START_POS_X, PRESS_START_POS_Y, 0.0f), PRESS_START_WIDTH, PRESS_START_HEIGHT);

	// 1p2p選択メニュー
	MakeVertex(pDevice, FVF_VERTEX_2D, g_pD3DVtxBuffMenu1P2P, D3DXVECTOR3(MENU_1P2P_POS_X, MENU_1P2P_POS_Y, 0.0f), MENU_1P2P_WIDTH, MENU_1P2P_HEIGHT);


	// テクスチャの読み込み
	// タイトル画面の背景
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_TITLE_BG,			// ファイルの名前
								&g_pD3DTextureTitleBG);		// 読み込むメモリー
	// タイトルロゴ
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_TITLE_LOGO,			// ファイルの名前
								&g_pD3DTextureTitleLogo);	// 読み込むメモリー
	// タイトル画面の「PRESS START」ロゴ
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_PRESS_START,		// ファイルの名前
								&g_pD3DTextureStart);		// 読み込むメモリー
	// 1p2p選択メニュー
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_MENU_1P2P,			// ファイルの名前
								&g_pD3DTextureMenu1P2P);	// 読み込むメモリー


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
	SAFE_RELEASE(g_pD3DTextureTitleBG);
	SAFE_RELEASE(g_pD3DVtxBuffTitleBG);
	SAFE_RELEASE(g_pD3DTextureTitleLogo);
	SAFE_RELEASE(g_pD3DVtxBuffTitleLogo);
	SAFE_RELEASE(g_pD3DTextureStart);
	SAFE_RELEASE(g_pD3DVtxBuffStart);
	SAFE_RELEASE(g_pD3DTextureMenu1P2P);
	SAFE_RELEASE(g_pD3DVtxBuffMenu1P2P);

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{
	TitleEffect();
	
	Menu1P2P();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//タイトル画面の背景を描画
	DrawPolygon(pDevice, FVF_VERTEX_2D, g_pD3DVtxBuffTitleBG, g_pD3DTextureTitleBG);

	if (!g_bDispMenu1P2P)
	{
		//タイトルロゴを描画
		DrawPolygon(pDevice, FVF_VERTEX_2D, g_pD3DVtxBuffTitleLogo, g_pD3DTextureTitleLogo);

		if (g_bDispStart == true)
		{
			//「PRESS START」ロゴを描画
			DrawPolygon(pDevice, FVF_VERTEX_2D, g_pD3DVtxBuffStart, g_pD3DTextureStart);
		}
	}
	else
	{//1p2p選択メニューの描画
		if (g_nCursorIdx == 0)
		{//カーソルが1P項目を指しているとき
			//頂点バッファの内容を再設定する
			SetVtxDataVtx(g_pD3DVtxBuffMenu1P2P, FVF_VERTEX_2D, D3DXVECTOR3(MENU_1P2P_POS_X, MENU_1P2P_POS_Y, 0.0f), MENU_1P2P_WIDTH, MENU_1P2P_HEIGHT / 2);
			SetVtxDataCor(g_pD3DVtxBuffMenu1P2P, FVF_VERTEX_2D, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetVtxDataTex(g_pD3DVtxBuffMenu1P2P, FVF_VERTEX_2D, D3DXVECTOR2(0.0f, 0.0f), 1.0f, 0.5f);

			//1p項目を描画
			DrawPolygon(pDevice, FVF_VERTEX_2D, g_pD3DVtxBuffMenu1P2P, g_pD3DTextureMenu1P2P);

			//頂点バッファの内容を再設定する
			SetVtxDataVtx(g_pD3DVtxBuffMenu1P2P, FVF_VERTEX_2D, D3DXVECTOR3(MENU_1P2P_POS_X + MENU_1P2P_WIDTH * CURSOR_RATE, MENU_1P2P_POS_Y + MENU_1P2P_HEIGHT / 2, 0.0f), MENU_1P2P_WIDTH * (1 - CURSOR_RATE), MENU_1P2P_HEIGHT / 2);
			SetVtxDataCor(g_pD3DVtxBuffMenu1P2P, FVF_VERTEX_2D, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			SetVtxDataTex(g_pD3DVtxBuffMenu1P2P, FVF_VERTEX_2D, D3DXVECTOR2(CURSOR_RATE, 0.5f), (1.0f - CURSOR_RATE), 0.5f);

			//2p項目を描画
			DrawPolygon(pDevice, FVF_VERTEX_2D, g_pD3DVtxBuffMenu1P2P, g_pD3DTextureMenu1P2P);
		}
		else if (g_nCursorIdx == 1)
		{//カーソルが2P項目を指しているとき
			//頂点バッファの内容を再設定する
			SetVtxDataVtx(g_pD3DVtxBuffMenu1P2P, FVF_VERTEX_2D, D3DXVECTOR3(MENU_1P2P_POS_X + MENU_1P2P_WIDTH * CURSOR_RATE, MENU_1P2P_POS_Y, 0.0f), MENU_1P2P_WIDTH * (1 - CURSOR_RATE), MENU_1P2P_HEIGHT / 2);
			SetVtxDataCor(g_pD3DVtxBuffMenu1P2P, FVF_VERTEX_2D, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			SetVtxDataTex(g_pD3DVtxBuffMenu1P2P, FVF_VERTEX_2D, D3DXVECTOR2(CURSOR_RATE, 0.0f), (1.0f - CURSOR_RATE), 0.5f);

			//1p項目を描画
			DrawPolygon(pDevice, FVF_VERTEX_2D, g_pD3DVtxBuffMenu1P2P, g_pD3DTextureMenu1P2P);

			//頂点バッファの内容を再設定する
			SetVtxDataVtx(g_pD3DVtxBuffMenu1P2P, FVF_VERTEX_2D, D3DXVECTOR3(MENU_1P2P_POS_X, MENU_1P2P_POS_Y + MENU_1P2P_HEIGHT / 2, 0.0f), MENU_1P2P_WIDTH, MENU_1P2P_HEIGHT / 2);
			SetVtxDataCor(g_pD3DVtxBuffMenu1P2P, FVF_VERTEX_2D, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetVtxDataTex(g_pD3DVtxBuffMenu1P2P, FVF_VERTEX_2D, D3DXVECTOR2(0.0f, 0.5f), 1.0f, 0.5f);

			//2p項目を描画
			DrawPolygon(pDevice, FVF_VERTEX_2D, g_pD3DVtxBuffMenu1P2P, g_pD3DTextureMenu1P2P);
		}
	}
}

//=============================================================================
//タイトル画面の演出処理
//=============================================================================
void TitleEffect(void)
{
	//タイトルロゴのフェードイン と 「PRESS START」ロゴの点滅
	if (g_fAlphaTitleLogo < 1.0f)
	{//タイトルロゴがフェードインする間
		g_fAlphaTitleLogo += DELTA_TITLE_LOGO_ALPHA;			//毎フレームにアルファ値を増加して、フェードインさせる
		if (g_fAlphaTitleLogo >= 1.0f)
		{
			g_fAlphaTitleLogo = 1.0f;
		}

		SetVtxDataCor(g_pD3DVtxBuffTitleLogo, FVF_VERTEX_2D, D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaTitleLogo));	//アルファ値をセットする
	}
	else
	{//フェードイン完成した後
		if (g_nCountAppearStart < COUNT_APPEAR_START)		//「COUNT_APPEAR_START」フレームを待つ
		{
			g_nCountAppearStart++;
		}
		else
		{//待ち終わったら、「PRESS START」ロゴを点滅させる
			g_nCountDispStart = (g_nCountDispStart + 1) % (INTERVAL_DISP_START + INTERVAL_UNDISP_START);			//点滅させるようにカウントする
			if (g_nCountDispStart < INTERVAL_DISP_START)
			{
				g_bDispStart = true;			//カウントが「0」から「INTERVAL_DISP_START」までの間に点灯する
			}
			else
			{
				g_bDispStart = false;			//カウントが「INTERVAL_DISP_START」から「INTERVAL_UNDISP_START」までの間に消灯する
			}

		}
	}

	//タイトルロゴのフェードインのスキップ と 1p2p選択メニューに移す処理
	if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTrigger(0, BUTTON_OPTIONS))
	{
		if (g_fAlphaTitleLogo < 1.0f)
		{//タイトルロゴがフェードインしている時
			g_fAlphaTitleLogo = 1.0f;						// フェードインを完成状態にさせる

			SetVtxDataCor(g_pD3DVtxBuffTitleLogo, FVF_VERTEX_2D, D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaTitleLogo));	//アルファ値をセットする

			g_nCountAppearStart = COUNT_APPEAR_START;	//「PRESS START」ロゴを点滅状態にさせる
		}
		else
		{//タイトルロゴがフェードイン完成した時			
			g_bDispMenu1P2P = true;						//1p2p選択メニューを表示する
		}
	}

}

//=============================================================================
// 1p2p選択メニューの処理
//=============================================================================
void Menu1P2P(void)
{
	//カーソル移動と選択
	if (g_bDispMenu1P2P)
	{//1p2p選択メニューが表示されているとき
		if (!g_bChosedMenu1P2P)
		{//1p2p選択メニューがまだ選択されていないとき
			if (GetKeyboardRepeat(DIK_W) || IsButtonRepeat(0, BUTTON_UP) || IsButtonRepeat(0, BUTTON_LSTICK_UP))
			{//カーソルを上移動
				g_nCursorIdx = g_nCursorIdx - 1;

				if (g_nCursorIdx < 0)
				{
					g_nCursorIdx = INDEX_MAX_MENU_1P2P - 1;
				}
			}
			else if (GetKeyboardRepeat(DIK_S) || IsButtonRepeat(0, BUTTON_DOWN) || IsButtonRepeat(0, BUTTON_LSTICK_DOWN))
			{//カーソルを下移動
				g_nCursorIdx = (g_nCursorIdx + 1) % INDEX_MAX_MENU_1P2P;
			}

			if (GetKeyboardTrigger(DIK_SPACE) || IsButtonTrigger(0, BUTTON_CIRCLE))
			{//メニューの項目を選択
				SetFade(FADE_OUT);
				g_bChosedMenu1P2P = true;
			}
		}
	}
}

//=============================================================================
// 1p2p選択の答えをゲット
//=============================================================================
int GetCursorIdx(void)
{
	return g_nCursorIdx;
}
