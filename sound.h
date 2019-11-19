//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : ���p�j
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "function.h"
#include <xaudio2.h>					// DX�T�E���h�֘A�̃��C�u�����[

// �T�E���h�t�@�C��
typedef enum
{
	SOUND_LABEL_BGM000,			// BGM
	SOUND_LABEL_SE_COIN,		// �R�C���Ƃ̏Փˉ�
	SOUND_LABEL_SE_TEST,
	SOUND_LABEL_MAX,

} SOUND_LABEL;

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
