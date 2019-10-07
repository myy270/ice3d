//=============================================================================
//
// フェード処理 [fade.h]
// Author : 麦英泳
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "function.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);

void SetFade(FADETYPE fade);
FADETYPE GetFade(void);

#endif
