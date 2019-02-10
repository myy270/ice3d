//=============================================================================
//
// アイテム処理 [item.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_ITEM				(128)						// アイテム最大数

//**************************************
// 種類
//**************************************
enum
{
	ITEMTYPE_COIN = 0,		// コイン
	ITEMTYPE_ICEBLOCK = 1,		// アイスブロック

	//ITEMTYPE_LIFE,			// ライフ
	//ITEMTYPE_TIMER,			// タイマー
	ITEMTYPE_MAX
};

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// 現在の位置
	D3DXVECTOR3 rot;		// 現在の向き
	float fRadius;			// 半径
	int nIdxShadow;			// 影ID
	int nType;				// 種類
	bool bUse;				// 使用しているかどうか
} ITEM;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
int SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType = ITEMTYPE_COIN);
void DeleteItem(int nIdxItem);
ITEM *GetItem(void);

void Freeze(void);

void DropItem();
#endif
