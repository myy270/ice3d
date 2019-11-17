//=============================================================================
//
// コインとアイスブロックの処理、凍結アイテムUIの処理 [item.cpp]	
// Author : 麦英泳
//
//=============================================================================
#include "item.h"
#include "shadow.h"
#include "input.h"
#include "player.h"
#include "enemy.h"
#include "timer.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	ITEM_RADIUS				(10.0f)										// アイテムの半径	//影の大きさ、アイテムとの当たる距離 と関係ある

#define	ITEMUI_WIDTH			FIT_WIDTH(65.0f)							// アイテムUIの幅
#define	ITEMUI_HEIGHT			FIT_HEIGHT(65.0f)							// アイテムUIの高さ

#define	ITEMUI_POS_X			FIT_WIDTH(20.0f)							// 左のアイテムUIの表示基準位置Ｘ座標
#define	ITEMUI_POS_Y			FIT_HEIGHT(95.0f)							// 左のアイテムUIの表示基準位置Ｙ座標

#define	ITEMUI_POS_X2			SCREEN_WIDTH - ITEMUI_POS_X - ITEMUI_WIDTH	// 右のアイテムUIの表示基準位置Ｘ座標

#define	DROP_TIME				(420)										// アイテムの落下間隔時間　単位：フレーム
#define	DROP_HIGHT				(1800.0f)									// 落下アイテムの初期高さ
#define	DROP_SPEED				(15.0f)										// 落下アイテムの落下速度

#define	HEIGHT_FROMLAND_ITEM	(15.0f)										// アイテムの滞空高さ
#define	NUM_COIN				(99)										// コインの数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

int SetItem(D3DXVECTOR3 pos, ITEMTYPE nType = ITEMTYPE_COIN, bool shadowUsable = true);
void DropItem();

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH			g_pMeshItem[ITEMTYPE_MAX];				// ID3DXMeshインターフェイスへのポインタ	[0]:コイン　[1]:アイスブロック
LPD3DXBUFFER		g_pD3DXMatBuffItem[ITEMTYPE_MAX];		// メッシュのマテリアル情報を格納
DWORD				g_aNumMatItem[ITEMTYPE_MAX];			// マテリアル情報の総数

ITEM				g_aItem[MAX_ITEM];			// アイテムワーク

bool g_isDropItem;		//アイテム落下するか

bool g_isReadyToDrop;	//落下するアイテムはもう生成したか

int g_dropItemIndex;	//落下するアイテムのインデクス

LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffItemUI = NULL;		// 左のアイテムUIの頂点バッファインターフェースへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffItemUI2 = NULL;	// 右のアイテムUIの頂点バッファインターフェースへのポインタ

//アイテムのXファイルのパス
const char *c_aFileNameItem[ITEMTYPE_MAX] =
{
	"data/MODEL/coin.x",			// コイン
	"data/MODEL/iceBlock.x",		// アイスブロック

};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//UIの頂点を作成
	MakeVertex(pDevice, FVF_VERTEX_2D, g_pD3DVtxBuffItemUI, D3DXVECTOR3(ITEMUI_POS_X, ITEMUI_POS_Y, 0.0f), ITEMUI_WIDTH, ITEMUI_HEIGHT);
	SetVtxDataCor(g_pD3DVtxBuffItemUI, FVF_VERTEX_2D, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));		//シアン色にする

	MakeVertex(pDevice, FVF_VERTEX_2D, g_pD3DVtxBuffItemUI2, D3DXVECTOR3(ITEMUI_POS_X2, ITEMUI_POS_Y, 0.0f), ITEMUI_WIDTH, ITEMUI_HEIGHT);
	SetVtxDataCor(g_pD3DVtxBuffItemUI2, FVF_VERTEX_2D, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));	//シアン色にする

	// Xファイルの読み込み
	for(int nCntItemType = 0; nCntItemType < ITEMTYPE_MAX; nCntItemType++)
	{	
		if(FAILED(D3DXLoadMeshFromX(c_aFileNameItem[nCntItemType],
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_pD3DXMatBuffItem[nCntItemType],
									NULL,
									&g_aNumMatItem[nCntItemType],
									&g_pMeshItem[nCntItemType])))
		{
			return E_FAIL;
		}
	}

	//ITEM構造体の初期化
	for(int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aItem[nCntItem].srt.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].parent = NULL;
		g_aItem[nCntItem].use = false;

		g_aItem[nCntItem].fRadius = ITEM_RADIUS;
		g_aItem[nCntItem].nIdxShadow = -1;
		g_aItem[nCntItem].nType = ITEMTYPE_COIN;
	}

	//コインの設置
	for (int nCntCoin = 0; nCntCoin < NUM_COIN; nCntCoin++)
	{
		float fPosX, fPosY, fPosZ;
		fPosX = (float)(rand() % 12000) / 10.0f - 600.0f;//-600.0f~600.0f
		fPosY = HEIGHT_FROMLAND_ITEM;
		fPosZ = (float)(rand() % 12000) / 10.0f - 600.0f;

		SetItem(D3DXVECTOR3(fPosX, fPosY, fPosZ), ITEMTYPE_COIN, true);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitItem(void)
{
	for(int nCntItemType = 0; nCntItemType < ITEMTYPE_MAX; nCntItemType++)
	{
		SAFE_RELEASE(g_pMeshItem[nCntItemType]);
		SAFE_RELEASE(g_pD3DXMatBuffItem[nCntItemType]);

	}

	SAFE_RELEASE(g_pD3DVtxBuffItemUI);
	SAFE_RELEASE(g_pD3DVtxBuffItemUI2);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateItem(void)
{

#ifdef _DEBUG
	//開発者機能
	if (GetKeyboardPress(DIK_MULTIPLY))		//テンキーのアスタリスク*
	{
		g_isDropItem = true;
	}
#endif

	//一定時間後、アイスブロックが自動的に落下する
	if ((GetTimer() % DROP_TIME == 0)&&(GetTimer() > 0))	//時間終了する場合は、落下しない
	{
		g_isDropItem = true;
	}

	//落下処理
	DropItem();
	
	//アイテムの向きと影を更新
	for(int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if(g_aItem[nCntItem].use)
		{
			g_aItem[nCntItem].srt.rot.y += VALUE_ROTATE;	//毎フレーム自回転

			LimitRot(g_aItem[nCntItem].srt.rot.y);

			//影を更新
			UpdateShadow(g_aItem[nCntItem].nIdxShadow, g_aItem[nCntItem].srt.pos, HEIGHT_FROMLAND_ITEM);
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//アイテムの描画
	for (int i = 0; i < MAX_ITEM; i++)//パーツ番号
	{
		DrawXMODEL(pDevice, g_aItem + i, 1);
	}

	//凍結アイテムUIの描画	
	//左の方
	if (GetPlayer()->holdItem == ITEMTYPE_ICEBLOCK)
	{
		DrawPolygon(pDevice, g_pD3DVtxBuffItemUI, NULL);			
	}
	//右の方
	if (GetEnemy()->holdItem == ITEMTYPE_ICEBLOCK)
	{
		DrawPolygon(pDevice, g_pD3DVtxBuffItemUI2, NULL);
	}
			
}

//=============================================================================
// アイテムの設定
//=============================================================================
int SetItem(D3DXVECTOR3 pos, ITEMTYPE nType, bool shadowUsable)
{
	int itemIndex = -1;		//エラーコード

	for(int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if(!g_aItem[nCntItem].use)
		{
			g_aItem[nCntItem].srt.pos = pos;
			g_aItem[nCntItem].nType = nType;
			g_aItem[nCntItem].use = true;

			g_aItem[nCntItem].pMesh = g_pMeshItem[g_aItem[nCntItem].nType];
			g_aItem[nCntItem].pMatBuff = g_pD3DXMatBuffItem[g_aItem[nCntItem].nType];
			g_aItem[nCntItem].nNumMat = g_aNumMatItem[g_aItem[nCntItem].nType];

			if (shadowUsable)
			{
				// 影の設定
				g_aItem[nCntItem].nIdxShadow = SetShadow(g_aItem[nCntItem].srt.pos, g_aItem[nCntItem].fRadius * 2.0f);
			}
		
			itemIndex = nCntItem;

			break;
		}
	}

	return itemIndex;
}

//=============================================================================
// アイテムの削除
//=============================================================================
void DeleteItem(int nIdxItem)
{
	if(nIdxItem >= 0 && nIdxItem < MAX_ITEM)
	{
		DeleteShadow(g_aItem[nIdxItem].nIdxShadow);
		g_aItem[nIdxItem].use = false;
	}
}
 
//=============================================================================
// アイテムの取得
//=============================================================================
ITEM *GetItem(void)
{
	return &g_aItem[0];
}

//=============================================================================
// 凍結アイテムの落下する処理
//=============================================================================
void DropItem()
{
	if (g_isDropItem)
	{
		if (!g_isReadyToDrop)
		{
			float fPosX, fPosY, fPosZ;
			fPosX = (float)(rand() % 12000) / 10.0f - 600.0f;//-600.0f~600.0f
			fPosY = DROP_HIGHT;								//落下の高さ
			fPosZ = (float)(rand() % 12000) / 10.0f - 600.0f;//-600.0f~600.0f

			g_dropItemIndex = SetItem(D3DXVECTOR3(fPosX, fPosY, fPosZ), ITEMTYPE_ICEBLOCK, false);

			g_isReadyToDrop = true;
		}

		if (g_dropItemIndex != -1)
		{
			(GetItem() + g_dropItemIndex)->srt.pos.y -= DROP_SPEED;

			if ((GetItem() + g_dropItemIndex)->srt.pos.y <= HEIGHT_FROMLAND_ITEM)
			{//アイテムの着地高さ
				(GetItem() + g_dropItemIndex)->srt.pos.y = HEIGHT_FROMLAND_ITEM;

				g_isDropItem = false;
				g_isReadyToDrop = false;
			}
		}
		
	}
}
