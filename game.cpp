//=============================================================================
//
// �Q�[����ʏ��� [game.cpp]
// Author : ���p�j
//
//=============================================================================
#include "game.h"
#include "light.h"
#include "camera.h"
#include "meshfield.h"
#include "meshwall.h"
#include "player.h"
#include "enemy.h"
#include "shadow.h"
#include "effect.h"
#include "timer.h"
#include "score.h"
#include "item.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


//=============================================================================
// ����������
//=============================================================================
HRESULT InitGame(void)
{
	// ���C�g�̏�����
	InitLight();

	// �J�����̏�����
	InitCamera();

	InitMeshField();

	InitMeshWall();

	// �e�̏�����
	InitShadow();

	// �v���C���[�̏�����
	InitPlayer();

	InitEnemy();

	// �G�t�F�N�g�̏�����
	InitEffect();

	// �^�C�}�[�̏�����
	InitTimer();		//�f�t�H���g50

	// �X�R�A�̏�����
	InitScore();

	// �A�C�e���̏�����
	InitItem();
	for(int nCntCoin = 0; nCntCoin < 99; nCntCoin++)
	{
		float fPosX, fPosY, fPosZ;

		fPosX = (float)(rand() % 12000) / 10.0f - 600.0f;//-600.0f~600.0f
		//fPosY = (float)(rand() % 1400) / 10.0f + 10.0f;//10.0f~150.0f
		fPosY = 15.0f;
		fPosZ = (float)(rand() % 12000) / 10.0f - 600.0f;
		SetItem(D3DXVECTOR3(fPosX, fPosY, fPosZ),  D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_COIN, true);
	}

	// BGM�Đ� ������loop�ł���ɂ���!�@�����
	//PlaySound(SOUND_LABEL_BGM000, XAUDIO2_LOOP_INFINITE);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{
	// �J�����̏I������
	UninitCamera();

	// �n�ʂ̏I������
	UninitMeshField();

	// �ǂ̏I������
	UninitMeshWall();

	// �e�̏I������
	UninitShadow();

	// �v���C���[�̏I������
	UninitPlayer();

	UninitEnemy();

	// �G�t�F�g�̏I������
	UninitEffect();

	// �^�C�}�[�̏I������
	UninitTimer();

	// �X�R�A�̏I������
	UninitScore();

	// �A�C�e���̏I������
	UninitItem();

	// BGM��~ !!�����
	StopSound(SOUND_LABEL_BGM000);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	// �J���������̍X�V
	UpdateCamera();

	// �n�ʏ����̍X�V
	UpdateMeshField();

	// �Ǐ����̍X�V
	UpdateMeshWall();

	// �e�����̍X�V
	UpdateShadow();

	// �v���C���[�����̍X�V
	UpdatePlayer();

	UpdateEnemy();

	// �G�t�F�N�g�����̍X�V
	UpdateEffect();

	// �^�C�}�[�����̍X�V
	UpdateTimer();

	// �X�R�A�����̍X�V
	UpdateScore();

	// �A�C�e�������̍X�V
	UpdateItem();


}

//=============================================================================
// �`�揈�� �`�揇����
//=============================================================================
void DrawGame(void)
{
	// �J�����̐ݒ�
	SetCamera();

	// �n�ʏ����̕`��
	DrawMeshField();

	// �e�����̕`��
	DrawShadow();

	// �v���C���[�����̕`��
	DrawPlayer();

	DrawEnemy();

	// �A�C�e�������̕`��
	DrawItem();

	// �G�t�F�N�g�����̕`��
	DrawEffect();

	// �Ǐ����̕`��
	DrawMeshWall();

	// �^�C�}�[�����̕`��
	DrawTimer();

	// �X�R�A�����̕`��
	DrawScore();
}

