//=============================================================================
//
// エネミー処理 [enemy.h]
// Author : 麦英泳
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"


#define PART_MAX_ENEMY	(6)		// パーツの数

//*****************************************************************************
// 構造体定義
//*****************************************************************************

struct ENEMY
{
	D3DXVECTOR3 move;		// 移動量
	D3DXVECTOR3 rotDest;	// 目的の向き
	float fRadius;			// 半径
	int nIdxShadow;			// 影ID
	PART part[PART_MAX_ENEMY];

};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
ENEMY *GetEnemy(void);

D3DXVECTOR3 GetPositionEnemy(void);
D3DXVECTOR3 GetRotationEnemy(void);
D3DXVECTOR3 GetRotationDestEnemy(void);
D3DXVECTOR3 GetMoveEnemy(void);

#endif
