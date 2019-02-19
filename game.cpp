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
#include "bullet.h"
#include "effect.h"
#include "explosion.h"
#include "life.h"
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

	// �n�ʂ̏�����
	InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 16, 16, 80.0f, 80.0f);//1280*1280

	// �ǂ̏����� 

	//�k�ǂ̒n��
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, 640.0f), D3DXVECTOR3(D3DX_PI * 0.50f, 0.0f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 48, 16, 80.0f, 80.0f);
	//��ǂ̒n��
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, -640.0f), D3DXVECTOR3(D3DX_PI * 0.50f, D3DX_PI, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 48, 16, 80.0f, 80.0f);
	//���ǂ̒n�ʁ@�����v��]90�x
	InitMeshWall(D3DXVECTOR3(-640.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.50f, 0.0f, D3DX_PI * 0.50f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 16, 80.0f, 80.0f);
	//���ǂ̒n�ʁ@���v��]90�x
	InitMeshWall(D3DXVECTOR3(640.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.50f, D3DX_PI * 0.50f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 16, 80.0f, 80.0f);

	//�k��
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, 640.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);
	//��ǁ@���v��]180�x
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, -640.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);
	//���ǁ@�����v��]90�x
	InitMeshWall(D3DXVECTOR3(-640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.50f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);
	//���ǁ@���v��]90�x
	InitMeshWall(D3DXVECTOR3(640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.50f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);


	//�k�ǂ̉���
	InitMeshWall(D3DXVECTOR3(0.0f, 160.0f, 640.0f), D3DXVECTOR3(D3DX_PI * 0.50f, 0.0f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 48, 16, 80.0f, 80.0f);
	////��ǂ̉���
	InitMeshWall(D3DXVECTOR3(0.0f, 160.0f, -640.0f), D3DXVECTOR3(D3DX_PI * 0.50f, D3DX_PI, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 48, 16, 80.0f, 80.0f);
	////���ǂ̉���@�����v��]90�x
	InitMeshWall(D3DXVECTOR3(-640.0f, 160.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.50f, 0.0f, D3DX_PI * 0.50f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 16, 16, 80.0f, 80.0f);
	////���ǂ̉���@���v��]90�x
	InitMeshWall(D3DXVECTOR3(640.0f, 160.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.50f, D3DX_PI * 0.50f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 16, 16, 80.0f, 80.0f);

	//��(�����p)
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, 640.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(-640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.50f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.50f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, -640.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);

	// �e�̏�����
	InitShadow();

	// �v���C���[�̏�����
	InitPlayer();

	InitEnemy();

	// �e�̏�����
	InitBullet();

	// �����̏�����
	InitExplosion();

	// �G�t�F�N�g�̏�����
	InitEffect();

	// ���C�t�̏�����
	InitLife();

	// �^�C�}�[�̏�����
	InitTimer();
	ResetTimer(500);

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
	PlaySound(SOUND_LABEL_BGM000, XAUDIO2_LOOP_INFINITE);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{
	// ���C�g�̏I������
	UninitLight();

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

	// �e�̏I������
	UninitBullet();

	// �����̏I������
	UninitExplosion();

	// �G�t�F�g�̏I������
	UninitEffect();

	// ���C�t�̏I������
	UninitLife();

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
	// ���C�g�����̍X�V
	UpdateLight();

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

	// �e�����̍X�V
	UpdateBullet();

	// ���������̍X�V
	UpdateExplosion();

	// �G�t�F�N�g�����̍X�V
	UpdateEffect();

	// ���C�t�����̍X�V
	UpdateLife();

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

	// �e�����̕`��
	DrawBullet();

	// �Ǐ����̕`��
	DrawMeshWall();

	// ���������̕`��
	DrawExplosion();

	// �G�t�F�N�g�����̕`��
	DrawEffect();

	// ���C�t�����̕`��
	//DrawLife();

	// �^�C�}�[�����̕`��
	DrawTimer();

	// �X�R�A�����̕`��
	DrawScore();
}

