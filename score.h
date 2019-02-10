//=============================================================================
//
// スコア処理 [score.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void ChangeScore(int value);//敵の
void ChangeScore2(int value);//プレイヤーの

bool compScore(); //プレイヤー勝つ場合true 
#endif
