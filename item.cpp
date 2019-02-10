//=============================================================================
//
// アイテム処理 [item.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "item.h"
#include "shadow.h"
#include "input.h"
#include "player.h"
#include "enemy.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_ROTATE_ITEM		(D3DX_PI * 0.025f)			// 回転速度
#define	ITEM_RADIUS				(10.0f)						// 半径

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureItem[ITEMTYPE_MAX];	// テクスチャ読み込み場所
LPD3DXMESH			g_pMeshItem[ITEMTYPE_MAX];			// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXMatBuffItem[ITEMTYPE_MAX];	// メッシュのマテリアル情報を格納
DWORD				g_aNumMatItem[ITEMTYPE_MAX];			// 属性情報の総数

D3DXMATRIX			g_mtxWorldItem;				// ワールドマトリックス

ITEM				g_aItem[MAX_ITEM];			// アイテムワーク

bool g_dropItem;//落下するか

bool g_dropReady;//落下するアイテムはもう設置したか

int g_itemIndex;//落下するアイテムのインデクス

const char *c_aFileNameItem[ITEMTYPE_MAX] =
{
	"data/MODEL/coin.x",			// コイン
	"data/MODEL/iceBlock.x",		// アイスブロック
	//"data/MODEL/item002.x"		// タイマー
};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for(int nCntItemType = 0; nCntItemType < ITEMTYPE_MAX; nCntItemType++)
	{
		g_pD3DTextureItem[nCntItemType] = NULL;
		g_pMeshItem[nCntItemType] = NULL;
		g_pD3DXMatBuffItem[nCntItemType] = NULL;

		// Xファイルの読み込み
		if(FAILED(D3DXLoadMeshFromX(c_aFileNameItem[nCntItemType],
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_pD3DXMatBuffItem[nCntItemType],
									NULL,
									&g_aNumMatItem[nCntItemType],
									&g_pMeshItem[nCntItemType])))
		{
			//return E_FAIL;//コインが次のステージに残すbug
		}

#if 0
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,									// デバイスへのポインタ
									TEXTURE_ITEM,						// ファイルの名前
									&g_pD3DTextureItem[nCntItemType]);	// 読み込むメモリー
#endif
	}

	for(int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].fRadius = 0.0f;
		g_aItem[nCntItem].nIdxShadow = -1;
		g_aItem[nCntItem].nType = ITEMTYPE_COIN;
		g_aItem[nCntItem].bUse = false;
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
		if(g_pD3DTextureItem[nCntItemType] != NULL)
		{// テクスチャの開放
			g_pD3DTextureItem[nCntItemType]->Release();
			g_pD3DTextureItem[nCntItemType] = NULL;
		}

		if(g_pMeshItem[nCntItemType] != NULL)
		{// メッシュの開放
			g_pMeshItem[nCntItemType]->Release();
			g_pMeshItem[nCntItemType] = NULL;
		}

		if(g_pD3DXMatBuffItem[nCntItemType] != NULL)
		{// マテリアルの開放
			g_pD3DXMatBuffItem[nCntItemType]->Release();
			g_pD3DXMatBuffItem[nCntItemType] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateItem(void)
{
	if (GetKeyboardTrigger(DIK_3))
	{
		g_dropItem = true;
	}

	DropItem();
	


	for(int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if(g_aItem[nCntItem].bUse)
		{
			g_aItem[nCntItem].rot.y += VALUE_ROTATE_ITEM;//毎フレーム自回転4.5度
			if(g_aItem[nCntItem].rot.y > D3DX_PI)
			{
				g_aItem[nCntItem].rot.y -= D3DX_PI * 2.0f;
			}

			// 影の位置設定
			SetPositionShadow(g_aItem[nCntItem].nIdxShadow, D3DXVECTOR3(g_aItem[nCntItem].pos.x, 0.1f, g_aItem[nCntItem].pos.z));

			float fSizeX = 20.0f + (g_aItem[nCntItem].pos.y - 10.0f) * 0.05f;
			if(fSizeX < 20.0f)
			{
				fSizeX = 20.0f;
			}
			float fSizeY = 20.0f + (g_aItem[nCntItem].pos.y - 10.0f) * 0.05f;
			if(fSizeY < 20.0f)
			{
				fSizeY = 20.0f;
			}

			SetVertexShadow(g_aItem[nCntItem].nIdxShadow, fSizeX, fSizeY);

			float colA = (200.0f - (g_aItem[nCntItem].pos.y - 10.0f)) / 400.0f;
			if(colA < 0.0f)
			{
				colA = 0.0f;
			}
			SetColorShadow(g_aItem[nCntItem].nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;

	D3DMATERIAL9 matDef;
	pDevice->GetMaterial(&matDef);

	for(int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if(g_aItem[nCntItem].bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldItem);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aItem[nCntItem].rot.y, g_aItem[nCntItem].rot.x, g_aItem[nCntItem].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldItem, &g_mtxWorldItem, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y, g_aItem[nCntItem].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldItem, &g_mtxWorldItem, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldItem);

			D3DXMATERIAL *pD3DXMat = (D3DXMATERIAL*)g_pD3DXMatBuffItem[g_aItem[nCntItem].nType]->GetBufferPointer();

			for(int nCntMat = 0; nCntMat < (int)g_aNumMatItem[g_aItem[nCntItem].nType]; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);//ポインターが配列になる

				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTextureItem[g_aItem[nCntItem].nType]);

				// 描画
				g_pMeshItem[g_aItem[nCntItem].nType]->DrawSubset(nCntMat);
			}
		}
	}
	
	{// マテリアルをデフォルトに戻す
		D3DXMATERIAL mat;

		mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		//pDevice->SetMaterial(&mat.MatD3D);
	}
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// アイテムの設定
//=============================================================================
int SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	int itemIndex = -1;
	for(int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if(!g_aItem[nCntItem].bUse)
		{
			g_aItem[nCntItem].pos = pos;
			g_aItem[nCntItem].rot = rot;
			g_aItem[nCntItem].fRadius = ITEM_RADIUS;
			g_aItem[nCntItem].nType = nType;
			g_aItem[nCntItem].bUse = true;

			// 影の設定
			g_aItem[nCntItem].nIdxShadow = SetShadow(g_aItem[nCntItem].pos, g_aItem[nCntItem].fRadius * 2.0f, g_aItem[nCntItem].fRadius * 2.0f);

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
		g_aItem[nIdxItem].bUse = false;
	}
}

//=============================================================================
// アイテムの取得
//=============================================================================
ITEM *GetItem(void)
{
	return &g_aItem[0];
}


void Freeze(void)
{
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		if (GetEnemy()->state == NORMAL)
		{
			GetEnemy()->state = FROZEN;
			GetEnemy()->stateTime = 180;//3秒
		}
	}

}

void DropItem()
{

	if (g_dropItem)
	{
		if (!g_dropReady)
		{
			float fPosX, fPosY, fPosZ;

			fPosX = (float)(rand() % 12000) / 10.0f - 600.0f;//-600.0f~600.0f
			fPosY = 950.0f;
			fPosZ = (float)(rand() % 12000) / 10.0f - 600.0f;
			g_itemIndex = SetItem(D3DXVECTOR3(fPosX, fPosY, fPosZ), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_ICEBLOCK);
			g_dropReady = true;
		}
		else
		{
			if (g_itemIndex != -1)
			{
				(GetItem() + g_itemIndex)->pos.y -= 15.0f;

				if ((GetItem() + g_itemIndex)->pos.y <= 15.0f)
				{
					(GetItem() + g_itemIndex)->pos.y = 15.0f;

					g_dropItem = false;
					g_dropReady = false;
				}
			}
		}
	}

}



