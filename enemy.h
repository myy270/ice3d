//=============================================================================
//
// エネミー処理 [enemy.h]
// Author : 麦英泳
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "function.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

Character *GetEnemy(void);
D3DXVECTOR3 GetPositionEnemy(void);

#endif
