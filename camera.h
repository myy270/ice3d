//=============================================================================
//
// �J�������� [camera.h]
// Author : ���p�j
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "function.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCamera(void);
void UpdateCamera(void);

void SetCamera(void);
D3DXVECTOR3 GetRotCamera(void);
D3DXMATRIX GetMtxView(void);
void SetCameraMode(CAMERA_MODE mode);

#endif
