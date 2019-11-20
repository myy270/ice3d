//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : ���p�j
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "function.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

HRESULT InitSound(HWND hWnd);
void UpdateSound();
void UninitSound(void);

HRESULT PlaySound(SOUND_LABEL label, bool isLoop, bool isEncore = false);
void StopSound(SOUND_LABEL label, bool isTempStop = true);

void StopSoundALL(bool isTempStop = true);
HRESULT PlaySoundAll();

#endif
