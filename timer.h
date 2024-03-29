//=============================================================================
//
// タイマー処理 [timer.h]
// Author : 麦英泳
//
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include "function.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

HRESULT InitTimer(int second = 50);
void UninitTimer(void);
void UpdateTimer(void);
void DrawTimer(void);

void SetEnableTimer(bool b);
void SetTimer(int second);
int GetTimer();
bool IsTimeEnd();

#endif
