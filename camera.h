//=============================================================================
//
// カメラ処理 [camera.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);

void SetCamera(void);

D3DXVECTOR3 GetRotCamera(void);
D3DXMATRIX GetMtxView(void);

//追跡時の視点の高さをセット
void SetChaseHightP(float hight);

//カメラの視点と注視点の距離をセット
void SetLengthIntervalCamera(float length);

#endif
