//=============================================================================
//
// �^�C�}�[���� [timer.h]
// Author : ���p�j
//
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include "function.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

HRESULT InitTimer(int second);
void UninitTimer(void);
void UpdateTimer(void);
void DrawTimer(void);

void SetEnableTimer(bool b);
void SetTimer(int second = 999);
int GetTimer();
bool IsClockOver();

#endif
