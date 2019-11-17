//=============================================================================
//
// �e���� [shadow.h]
// Author : ���p�j
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "function.h"
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitShadow(void);
void UninitShadow(void);
void UpdateShadow(int nIdxShadow, D3DXVECTOR3 pos, float farFromLand);
void DrawShadow(void);

int SetShadow(D3DXVECTOR3 pos, float fSize);
void DeleteShadow(int nIdxShadow);


#endif
