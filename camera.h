//=============================================================================
//
// �J�������� [camera.h]
// Author : ���p�j
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);

void SetCamera(void);

D3DXVECTOR3 GetRotCamera(void);
D3DXMATRIX GetMtxView(void);

//�ǐՎ��̎��_�̍������Z�b�g
void SetChaseHightP(float hight);

//�J�����̎��_�ƒ����_�̋������Z�b�g
void SetLengthIntervalCamera(float length);

CAMERA_MODE GetCameraMode();
void SetCameraMode(CAMERA_MODE val);
void SetPlayMode(PLAY_MODE val);
PLAY_MODE GetPlayMode();

bool GetCutScene();

void WinScene();

#endif
