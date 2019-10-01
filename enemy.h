//=============================================================================
//
// �G�l�~�[���� [enemy.h]
// Author : ���p�j
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "function.h"
#include "item.h"



//*****************************************************************************
// �\���̒�`
//*****************************************************************************

struct ENEMY
{
	D3DXVECTOR3 move;		// �ړ���
	D3DXVECTOR3 rotDest;	// �ړI�̌���
	float fRadius;			// ���a
	int nIdxShadow;			// �eID
	PART part[PART_MAX_ENEMY];

	ITEMTYPE holdItem;

	STATE state;
	int stateTime;
};


//*****************************************************************************
// �v���g�^�C�v�錾
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
