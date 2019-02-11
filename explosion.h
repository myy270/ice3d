//=============================================================================
//
// �������� [explosion.h]
// Author : ���p�j
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//**************************************
// ���
//**************************************
enum
{
	EXPLOSIONTYPE_BULLET_PLAYER = 0,	// �v���C���[�̒e�̔���
	EXPLOSIONTYPE_BULLET_ENEMY,			// �G�̒e�̔���
	EXPLOSIONTYPE_MAX
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);

int SetExplosion(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType = EXPLOSIONTYPE_BULLET_PLAYER);//�������f�t�H���g������@

#endif
