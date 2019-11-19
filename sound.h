//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 麦英泳
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "function.h"
#include <xaudio2.h>					// DXサウンド関連のライブラリー

// サウンドファイル
typedef enum
{
	SOUND_LABEL_BGM000,			// BGM
	SOUND_LABEL_SE_COIN,		// コインとの衝突音
	SOUND_LABEL_SE_TEST,
	SOUND_LABEL_MAX,

} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UpdateSound();
void UninitSound(void);

HRESULT PlaySound(SOUND_LABEL label, bool isLoop, bool isEncore = false);
void StopSound(SOUND_LABEL label, bool isTempStop = true);

void StopSoundALL(bool isTempStop = true);
HRESULT PlaySoundAll();

#endif
