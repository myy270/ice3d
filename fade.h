//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : ���p�j
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "function.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);

void SetFade(FADETYPE fade);
FADETYPE GetFade(void);

#endif
