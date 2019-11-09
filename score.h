//=============================================================================
//
// スコア処理 [score.h]
// Author : 麦英泳
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "function.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void ChangeScore(OBJECT obj, int value);
void CompareScore();
OBJECT GetWinner();

#endif
