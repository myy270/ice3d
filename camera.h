//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 麦英泳
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "function.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCamera(void);
void UpdateCamera(void);

void SetCamera(void);
D3DXVECTOR3 GetRotCamera(void);
D3DXMATRIX GetMtxView(void);
void SetCameraMode(CAMERA_MODE mode);

#endif
