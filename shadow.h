//=============================================================================
//
// 影処理 [shadow.h]
// Author : 麦英泳
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "function.h"
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitShadow(void);
void UninitShadow(void);
void UpdateShadow(int nIdxShadow, D3DXVECTOR3 pos, float farFromLand);
void DrawShadow(void);

int SetShadow(D3DXVECTOR3 pos, float fSize);
void DeleteShadow(int nIdxShadow);


#endif
