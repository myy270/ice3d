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
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_SE_SHOT,		// �e���ˉ�
	SOUND_LABEL_SE_EXPLOSION,	// ������
	SOUND_LABEL_SE_COIN,		// �Փˉ�0
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label, int LoopCount = 0);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
