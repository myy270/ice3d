//=============================================================================
//
// �G�l�~�[���� [enemy.h]
// Author : ���p�j
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "function.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

Character *GetEnemy(void);
D3DXVECTOR3 GetPositionEnemy(void);

#endif
