//=============================================================================
//
// �v���C���[���� [player.h]
// Author : ���p�j
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "function.h"
#include "item.h"




//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);

D3DXVECTOR3 GetPositionPlayer(void);
D3DXVECTOR3 GetRotationPlayer(void);
D3DXVECTOR3 GetRotationDestPlayer(void);
D3DXVECTOR3 GetMovePlayer(void);



#endif
