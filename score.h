//=============================================================================
//
// �X�R�A���� [score.h]
// Author : ���p�j
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "function.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void ChangeScore(OBJECT obj, int value);
void CompareScore();
OBJECT GetWinner();

#endif
