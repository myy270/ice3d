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

void ChangeScore(int value);//�G��
void ChangeScore2(int value);//�v���C���[��

void compScore(); //�v���C���[���ꍇtrue 

OBJECT GetWinner();
#endif
