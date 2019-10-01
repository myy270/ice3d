//=============================================================================
//
// �G�l�~�[���� [enemy.cpp]
// Author : ���p�j
//
//=============================================================================
#include "player.h"
#include "enemy.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "bullet.h"
#include "effect.h"
#include "item.h"
#include "score.h"
#include "sound.h"
#include "debugproc.h"
#include "timer.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	BODY_ENEMY		"data/MODEL/bearBodyPink.x"	// �ǂݍ��ރ��f����
#define	HEAD_ENEMY		"data/MODEL/bearHeadPink.x"	// �ǂݍ��ރ��f����
#define	HAND_ENEMY		"data/MODEL/bearHandPink.x"	// �ǂݍ��ރ��f����
#define	LEG_ENEMY		"data/MODEL/bearLegPink.x"	// �ǂݍ��ރ��f����
#define	ICE_BLOCK		"data/MODEL/iceBlock.x"		// �ǂݍ��ރ��f����



#define	ENEMY_RADIUS		(15.0f)						// ���a

#define	VALUE_MOVE_ENEMY	(0.195f)					// �ړ����x
#define	RATE_MOVE_ENEMY	(0.025f)						// �ړ������W��

#define	VALUE_ROTATE_ENEMY	(D3DX_PI * 0.025f)			// ��]���x 4.5�x
#define	RATE_ROTATE_ENEMY	(0.10f)						// ��]�����W��

#define	VALUE_MOVE_BULLET_ENEMY	(7.5f)						// �e�̈ړ����x

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

static void AnimeWalk();
void AI();
int AI2();
int AI3();

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureEnemy;		// �e�N�X�`���ǂݍ��ݏꏊ
ENEMY				g_enemy;					// �G�l�~�[���[�N

static int g_conId = 0;//�R���g���[��ID
 
static float g_motionTime = 0.0f;// �A�j���[�V�����S�̎���
static int g_keyMax;
static bool g_animeState = 0;
 
static float g_cancelTime = 0.0f;// �ŏ���Ԃɖ߂鎞��

bool g_up;//AI�s��
bool g_down;//AI�s��
bool g_left;//AI�s��
bool g_right;//AI�s��

bool g_ai;//AI���[�h

static KEY g_anime[] =
{
	{
		15,
		{
			{// part 0
				D3DXVECTOR3(1.5000f,1.5000f,1.5000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,22.4000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,6.5000f,0.0000f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(5.0000f,5.0000f,0.0000f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,3.1416f,0.0000f),//R
				D3DXVECTOR3(-5.0000f,5.0000f,0.0000f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-3.0640f,-4.8730f,-0.4090f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(1.5000f,1.5000f,1.5000f),//S
				D3DXVECTOR3(-0.0385f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,22.4000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,6.5000f,0.0000f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(1.4923f,0.0000f,0.0000f),//R
				D3DXVECTOR3(5.0000f,5.0000f,0.0000f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.7069f,3.1416f,0.0000f),//R
				D3DXVECTOR3(-5.0000f,5.0000f,0.0000f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-1.0854f,0.0000f,0.0000f),//R
				D3DXVECTOR3(3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.9425f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-3.0640f,-4.8730f,-0.4090f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(1.5000f,1.5000f,1.5000f),//S
				D3DXVECTOR3(-0.0385f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,22.4000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,6.5000f,0.0000f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-0.8639f,0.0000f,0.0000f),//R
				D3DXVECTOR3(5.0000f,5.0000f,0.0000f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-1.0996f,3.1416f,0.0000f),//R
				D3DXVECTOR3(-5.0000f,5.0000f,0.0000f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.9425f,0.0000f,0.0000f),//R
				D3DXVECTOR3(3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-1.0854f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-3.0640f,-4.8730f,-0.4090f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(1.5000f,1.5000f,1.5000f),//S
				D3DXVECTOR3(-0.0385f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,22.4000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,6.5000f,0.0000f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(1.4923f,0.0000f,0.0000f),//R
				D3DXVECTOR3(5.0000f,5.0000f,0.0000f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.7069f,3.1416f,0.0000f),//R
				D3DXVECTOR3(-5.0000f,5.0000f,0.0000f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-1.0854f,0.0000f,0.0000f),//R
				D3DXVECTOR3(3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.9425f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-3.0640f,-4.8730f,-0.4090f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

};



//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(void)
{
	

	if (GetPlayMode() == PLAY_MODE_SINGLE)
	{
		g_ai = true;
	}
	else if (GetPlayMode() == PLAY_MODE_DOUBLE)
	{
		g_ai = false;
	}




	g_keyMax = sizeof(g_anime) / sizeof(KEY);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_enemy.part[0].partFile = (char *)BODY_ENEMY;//�e�͈�Ԑ�ɂ��Ȃ���΂Ȃ�Ȃ�
	g_enemy.part[1].partFile = (char *)HEAD_ENEMY;//(const char *)����(char *)�ɕϊ�
	g_enemy.part[2].partFile = (char *)HAND_ENEMY;//����
	g_enemy.part[3].partFile = (char *)HAND_ENEMY;//�E��
	g_enemy.part[4].partFile = (char *)LEG_ENEMY;//����
	g_enemy.part[5].partFile = (char *)LEG_ENEMY;//�E��

	g_enemy.part[6].partFile = (char *)ICE_BLOCK;//�X

	for (int i = 0; i < PART_MAX_ENEMY; i++)//�p�[�c�ԍ�
	{
		// X�t�@�C���̓ǂݍ���
		if(FAILED(D3DXLoadMeshFromX(g_enemy.part[i].partFile,
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_enemy.part[i].pMatBuff,
									NULL,
									&g_enemy.part[i].nNumMat,
									&g_enemy.part[i].pMesh)))
		{
			return E_FAIL;
		}

		switch (i)
		{
		case 0:
		{//��
			g_enemy.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);//xyz�K�������悤��
			g_enemy.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_enemy.part[i].srt.pos = D3DXVECTOR3(90.0f, 22.4000f, 0.0f);//�����n�ʂɐG���悤�A15.0

			g_enemy.part[i].parent = NULL;//�̂̐e��NULL�ɂ���
			break;
		}
		case 1:
		{//��
			g_enemy.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_enemy.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_enemy.part[i].srt.pos = D3DXVECTOR3(0.0f, 6.5f, 0.0f);

			g_enemy.part[i].parent = &g_enemy.part[0];//�̂�e�ɂ���
			break;
		}
		case 2:
		{//����
			g_enemy.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_enemy.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_enemy.part[i].srt.pos = D3DXVECTOR3(5.0f, 5.0f, 0.0f);

			g_enemy.part[i].parent = &g_enemy.part[0];//�̂�e�ɂ���
			break;
		}
		case 3:
		{//�E��
			g_enemy.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_enemy.part[i].srt.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
			g_enemy.part[i].srt.pos = D3DXVECTOR3(-5.0f, 5.0f, 0.0f);

			g_enemy.part[i].parent = &g_enemy.part[0];//�̂�e�ɂ���
			break;
		}
		case 4:
		{//����
			g_enemy.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_enemy.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_enemy.part[i].srt.pos = D3DXVECTOR3(3.064f, -4.873f, -0.409f);

			g_enemy.part[i].parent = &g_enemy.part[0];//�̂�e�ɂ���
			break;
		}
		case 5:
		{//�E��
			g_enemy.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_enemy.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_enemy.part[i].srt.pos = D3DXVECTOR3(-3.064f, -4.873f, -0.409f);

			g_enemy.part[i].parent = &g_enemy.part[0];//�̂�e�ɂ���
			break;
		}

		default:
		{
			g_enemy.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_enemy.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_enemy.part[i].srt.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			g_enemy.part[i].parent = &g_enemy.part[0];//�̂�e�ɂ���
			break;
		}

		}

		if (i != 6)
		{
			g_enemy.part[i].use = true;
		}
		else
		{
			g_enemy.part[i].use = false;
		}
	}

	g_enemy.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_enemy.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_enemy.fRadius = ENEMY_RADIUS;
	// �e��ݒ� //�̂����
	g_enemy.nIdxShadow = SetShadow(g_enemy.part[0].srt.pos, g_enemy.fRadius * 2.0f, g_enemy.fRadius * 2.0f);


	g_enemy.holdItem = ITEMTYPE_COIN;
	g_enemy.state = NORMAL;
	g_enemy.stateTime = 0;

#if 0
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_ENEMY,		// �t�@�C���̖��O
								&g_pD3DTextureEnemy);	// �ǂݍ��ރ������[
#endif

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	for (int i = 0; i < PART_MAX_ENEMY; i++)//�p�[�c�ԍ�
	{
		SAFE_RELEASE(g_enemy.part[i].pMesh);
		SAFE_RELEASE(g_enemy.part[i].pMatBuff);

	}

	SAFE_RELEASE(g_pD3DTextureEnemy);

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_ADD))
	{//AI���[�h�̐ؑց@�����A�V���O�����[�h�ƃ_�u�����[�h�̐ؑ�
		g_ai = !g_ai;
		g_left = g_right = g_up = g_down = 0;
		SetPlayMode((PLAY_MODE)!GetPlayMode());

		if (GetPlayMode() == PLAY_MODE_DOUBLE)
		{
			SetCameraMode(CAMERA_MODE_FAR);

		}
	}
#endif

	if (g_ai)
	{
		AI3();
	}
	

	{
		D3DXVECTOR3 rotCamera;
		float fDiffRotY;

		// �J�����̌����擾
		rotCamera = GetRotCamera();

		g_animeState = 0;//�^����Ԃ����Z�b�g


		if ((GetTimeOut() == 0) && (g_enemy.state != FROZEN))
		{//�ړ�
			if (g_ai ? g_left : GetKeyboardPress(DIK_LEFT) || IsButtonPress(1, BUTTON_LEFT) || IsButtonPress(1, BUTTON_LSTICK_LEFT))
			{
				g_animeState = 1;//������Ԃɂ���

				if (g_ai ? g_up : GetKeyboardPress(DIK_UP) || IsButtonPress(1, BUTTON_UP) || IsButtonPress(1, BUTTON_LSTICK_UP))
				{// ���O�ړ�
					g_enemy.move.x -= sinf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_ENEMY;
					g_enemy.move.z -= cosf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_ENEMY;

					g_enemy.rotDest.y = rotCamera.y + D3DX_PI * 0.75f;
				}
				else if (g_ai ? g_down : GetKeyboardPress(DIK_DOWN) || IsButtonPress(1, BUTTON_DOWN) || IsButtonPress(1, BUTTON_LSTICK_DOWN))
				{// ����ړ�
					g_enemy.move.x -= sinf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;
					g_enemy.move.z -= cosf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;

					g_enemy.rotDest.y = rotCamera.y + D3DX_PI * 0.25f;
				}
				else
				{// ���ړ�
					g_enemy.move.x -= sinf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_ENEMY;
					g_enemy.move.z -= cosf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_ENEMY;

					g_enemy.rotDest.y = rotCamera.y + D3DX_PI * 0.50f;
				}
			}
			else if (g_ai ? g_right : GetKeyboardPress(DIK_RIGHT) || IsButtonPress(1, BUTTON_RIGHT) || IsButtonPress(1, BUTTON_LSTICK_RIGHT))
			{
				g_animeState = 1;//������Ԃɂ���

				if (g_ai ? g_up : GetKeyboardPress(DIK_UP) || IsButtonPress(1, BUTTON_UP) || IsButtonPress(1, BUTTON_LSTICK_UP))
				{// �E�O�ړ�
					g_enemy.move.x -= sinf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_ENEMY;
					g_enemy.move.z -= cosf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_ENEMY;

					g_enemy.rotDest.y = rotCamera.y - D3DX_PI * 0.75f;
				}
				else if (g_ai ? g_down : GetKeyboardPress(DIK_DOWN) || IsButtonPress(1, BUTTON_DOWN) || IsButtonPress(1, BUTTON_LSTICK_DOWN))
				{// �E��ړ�
					g_enemy.move.x -= sinf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;
					g_enemy.move.z -= cosf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;

					g_enemy.rotDest.y = rotCamera.y - D3DX_PI * 0.25f;
				}
				else
				{// �E�ړ�
					g_enemy.move.x -= sinf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_ENEMY;
					g_enemy.move.z -= cosf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_ENEMY;

					g_enemy.rotDest.y = rotCamera.y - D3DX_PI * 0.50f;
				}
			}
			else if (g_ai ? g_up : GetKeyboardPress(DIK_UP) || IsButtonPress(1, BUTTON_UP) || IsButtonPress(1, BUTTON_LSTICK_UP))
			{
				g_animeState = 1;//������Ԃɂ���

				// �O�ړ�
				g_enemy.move.x -= sinf(D3DX_PI + rotCamera.y) * VALUE_MOVE_ENEMY;
				g_enemy.move.z -= cosf(D3DX_PI + rotCamera.y) * VALUE_MOVE_ENEMY;

				g_enemy.rotDest.y = D3DX_PI + rotCamera.y;
			}
			else if (g_ai ? g_down : GetKeyboardPress(DIK_DOWN) || IsButtonPress(1, BUTTON_DOWN) || IsButtonPress(1, BUTTON_LSTICK_DOWN))
			{
				g_animeState = 1;//������Ԃɂ���

				// ��ړ�
				g_enemy.move.x -= sinf(rotCamera.y) * VALUE_MOVE_ENEMY;
				g_enemy.move.z -= cosf(rotCamera.y) * VALUE_MOVE_ENEMY;

				g_enemy.rotDest.y = rotCamera.y;
			}

		}

		AnimeWalk();

		// �ړI�̊p�x�܂ł̍���
		fDiffRotY = g_enemy.rotDest.y - g_enemy.part[0].srt.rot.y;//�̂����
		if (fDiffRotY > D3DX_PI)
		{
			fDiffRotY -= D3DX_PI * 2.0f;
		}
		if (fDiffRotY < -D3DX_PI)
		{
			fDiffRotY += D3DX_PI * 2.0f;
		}

		// �ړI�̊p�x�܂Ŋ�����������@�i�X�ړI�̊p�x�ɕω�����
		g_enemy.part[0].srt.rot.y += fDiffRotY * RATE_ROTATE_ENEMY;//�̂ɔ��f
		if (g_enemy.part[0].srt.rot.y > D3DX_PI)
		{
			g_enemy.part[0].srt.rot.y -= D3DX_PI * 2.0f;
		}
		if (g_enemy.part[0].srt.rot.y < -D3DX_PI)
		{
			g_enemy.part[0].srt.rot.y += D3DX_PI * 2.0f;
		}

		/// �ʒu�ړ��𔽉f
		g_enemy.part[0].srt.pos.x += g_enemy.move.x;//�̂ɔ��f
		g_enemy.part[0].srt.pos.y += g_enemy.move.y;
		g_enemy.part[0].srt.pos.z += g_enemy.move.z;

		//�ړ��͈́@//�̂����
		{
			if (g_enemy.part[0].srt.pos.x < -630.0f)
			{
				g_enemy.part[0].srt.pos.x = -630.0f;
			}
			if (g_enemy.part[0].srt.pos.x > 630.0f)
			{
				g_enemy.part[0].srt.pos.x = 630.0f;
			}
			if (g_enemy.part[0].srt.pos.y < 10.0f)
			{
				g_enemy.part[0].srt.pos.y = 10.0f;
			}
			if (g_enemy.part[0].srt.pos.y > 150.0f)
			{
				g_enemy.part[0].srt.pos.y = 150.0f;
			}
			if (g_enemy.part[0].srt.pos.z > 630.0f)
			{
				g_enemy.part[0].srt.pos.z = 630.0f;
			}
			if (g_enemy.part[0].srt.pos.z < -630.0f)
			{
				g_enemy.part[0].srt.pos.z = -630.0f;
			}
		}

		// �ړ��ʂɊ�����������@�^���G�l���M�[���ꕔ�����ĕۑ�����A���̃t���[���Ɏg��
		//���̕����C�R�[�����̃t���[���Ɋl���̉^���G�l���M�[�̏ꍇ�A���x���ő�(6.05f)�ɂȂ��āA���������^���ɂȂ�
		g_enemy.move.x += (0.0f - g_enemy.move.x) * RATE_MOVE_ENEMY;//�����Ag_enemy.move.x = g_enemy.move.x * (1 - RATE_MOVE_ENEMY;)
		g_enemy.move.y += (0.0f - g_enemy.move.y) * RATE_MOVE_ENEMY;
		g_enemy.move.z += (0.0f - g_enemy.move.z) * RATE_MOVE_ENEMY;

	}

// �e����
#ifdef _DEBUG
	if (0)
	{
		if ((GetTimeOut() == 0) && (g_enemy.state != FROZEN))
		{
			if (GetKeyboardTrigger(DIK_NUMPAD1))
			{
				D3DXVECTOR3 pos;
				D3DXVECTOR3 move;

				//�̂����
				pos.x = g_enemy.part[0].srt.pos.x - sinf(g_enemy.part[0].srt.rot.y) * g_enemy.fRadius;//��s�@�����̕ӂ�ɐݒ�
				pos.y = g_enemy.part[0].srt.pos.y;
				pos.z = g_enemy.part[0].srt.pos.z - cosf(g_enemy.part[0].srt.rot.y) * g_enemy.fRadius;

				//��]�p�x���v���X�̎��A���v���
				//sinf�Acosf�̕��������傤�ǈړ��ʂ̕����Ƒ�������A������-sinf�A-cosf
				move.x = -sinf(g_enemy.part[0].srt.rot.y) * VALUE_MOVE_BULLET_ENEMY;//�̂����
				move.y = 0.0f;
				move.z = -cosf(g_enemy.part[0].srt.rot.y) * VALUE_MOVE_BULLET_ENEMY;

				SetBullet(pos, move, 4.0f, 4.0f, 60 * 4);

				// SE�Đ�
				PlaySound(SOUND_LABEL_SE_SHOT);
			}
		}
	}
#endif

	// �e�̈ʒu�ݒ�
	{//�̂����
		SetPositionShadow(g_enemy.nIdxShadow, D3DXVECTOR3(g_enemy.part[0].srt.pos.x, 0.1f, g_enemy.part[0].srt.pos.z));
		//�����ɂ��A�e�̃T�C�Y���ω�����
		float fSizeX = 20.0f + (g_enemy.part[0].srt.pos.y - 10.0f) * 0.05f;
		if(fSizeX < 20.0f)
		{
			fSizeX = 20.0f;
		}
		float fSizeY = 20.0f + (g_enemy.part[0].srt.pos.y - 10.0f) * 0.05f;
		if(fSizeY < 20.0f)
		{
			fSizeY = 20.0f;
		}

		SetVertexShadow(g_enemy.nIdxShadow, fSizeX, fSizeY);
		//�����ɂ��A�e�̓����x���ω�����
		float colA = (200.0f - (g_enemy.part[0].srt.pos.y - 10.0f)) / 400.0f;
		if(colA < 0.0f)
		{
			colA = 0.0f;
		}
		SetColorShadow(g_enemy.nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));
	}

	//�ړ�������1���傫���ꍇ�A�W�F�b�g�̉�����
	if((g_enemy.move.x * g_enemy.move.x
	+ g_enemy.move.y * g_enemy.move.y
	+ g_enemy.move.z * g_enemy.move.z) > 1.0f)
	{
		D3DXVECTOR3 pos;
		//�̂����
		pos.x = g_enemy.part[0].srt.pos.x + sinf(g_enemy.part[0].srt.rot.y) * g_enemy.fRadius;//��s�@�����̕ӂ�ɐݒ�
		pos.y = g_enemy.part[0].srt.pos.y + 2.0f;
		pos.z = g_enemy.part[0].srt.pos.z + cosf(g_enemy.part[0].srt.rot.y) * g_enemy.fRadius;

		// �G�t�F�N�g�̐ݒ�
		SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DXCOLOR(0.85f, 0.05f, 0.65f, 0.50f), 14.0f, 14.0f, 20);//��
		SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DXCOLOR(0.65f, 0.85f, 0.05f, 0.30f), 10.0f, 10.0f, 20);//��
		SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DXCOLOR(0.45f, 0.45f, 0.05f, 0.15f), 5.0f, 5.0f, 20);//��
	}

	// �A�C�e���Ƃ̓����蔻��
	{
		ITEM *pItem;

		// �A�C�e�����擾
		pItem = GetItem();
		for(int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
		{
			if(pItem->bUse == true)
			{
				float fLength;

				//�o�E���f�B���O�T�[�N�� BC //�̂����
				fLength = (g_enemy.part[0].srt.pos.x - pItem->pos.x) * (g_enemy.part[0].srt.pos.x - pItem->pos.x)
							+ (g_enemy.part[0].srt.pos.y - pItem->pos.y) * (g_enemy.part[0].srt.pos.y - pItem->pos.y)
							+ (g_enemy.part[0].srt.pos.z - pItem->pos.z) * (g_enemy.part[0].srt.pos.z - pItem->pos.z);
				if(fLength < (g_enemy.fRadius + pItem->fRadius) * (g_enemy.fRadius + pItem->fRadius))
				{
					if (g_enemy.holdItem && (pItem->nType != ITEMTYPE_COIN))
					{//���\�A�C�e�������Ă���ꍇ�A�ق��̌��\�A�C�e���ɂ͍s���Ȃ�

					}
					else
					{
						if (pItem->nType == ITEMTYPE_ICEBLOCK)
						{
							g_enemy.holdItem = ITEMTYPE_ICEBLOCK;

						}
						else if (pItem->nType == ITEMTYPE_COIN)
						{
							// �X�R�A���Z
							ChangeScore(100);

							// SE�Đ�
							PlaySound(SOUND_LABEL_SE_COIN);
						}

						// �A�C�e������
						DeleteItem(nCntItem);
					}
				}
			}
		}
	}


	if ((GetTimeOut() == 0) && (g_enemy.state != FROZEN))
	{//�����A�C�e�����g��
		if (g_ai)
		{
			if ((g_enemy.holdItem == ITEMTYPE_ICEBLOCK))
			{//AI�͓����A�C�e�����E������A�����g��				
				Freeze(OBJECT_PLAYER);

			}
		}
		else 
		{
			if (GetKeyboardTrigger(DIK_NUMPAD1) || IsButtonTrigger(1, BUTTON_CIRCLE))
			{
				Freeze(OBJECT_PLAYER);
			}
		}	
	}

	//�������
	if (g_enemy.state == FROZEN)
	{
		if (g_enemy.stateTime == 0)
		{
			g_enemy.state = NORMAL;
			g_enemy.part[6].use = false;
		}
		else
		{
			g_enemy.stateTime--;
			g_enemy.part[6].use = true;

		}
	}

	//PrintDebugProc("�G�l�~�[////////////////////\n");
	//PrintDebugProc("�R���g���[���̃p�[�c�ԍ��F%d \n", g_conId);

	//PrintDebugProc("[S�F(%f : %f : %f)]\n", g_enemy.part[g_conId].srt.scl.x, 
	//										g_enemy.part[g_conId].srt.scl.y, 
	//										g_enemy.part[g_conId].srt.scl.z);

	//PrintDebugProc("[R�F(%f : %f : %f)]\n", g_enemy.part[g_conId].srt.rot.x, 
	//										g_enemy.part[g_conId].srt.rot.y, 
	//										g_enemy.part[g_conId].srt.rot.z);

	//PrintDebugProc("[T�F(%f : %f : %f)]\n", g_enemy.part[g_conId].srt.pos.x, 
	//										g_enemy.part[g_conId].srt.pos.y, 
	//										g_enemy.part[g_conId].srt.pos.z);

	//PrintDebugProc("�ړI�����F%f \n", g_enemy.rotDest.y);

	

	//PrintDebugProc("up �F%d \n", g_up);
	//PrintDebugProc("down �F%d \n", g_down);
	//PrintDebugProc("left �F%d \n", g_left);
	//PrintDebugProc("right �F%d \n", g_right);
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;
	D3DXMATERIAL *pD3DXMat;

	D3DMATERIAL9 matDef;
	pDevice->GetMaterial(&matDef);// �f�t�H���g�̃}�e���A�����擾

	for (int i = 0; i < PART_MAX_ENEMY; i++)//�p�[�c�ԍ�
	{
		if (g_enemy.part[i].use)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, g_enemy.part[i].srt.scl.x,
				g_enemy.part[i].srt.scl.y,
				g_enemy.part[i].srt.scl.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_enemy.part[i].srt.rot.y,
				g_enemy.part[i].srt.rot.x,
				g_enemy.part[i].srt.rot.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_enemy.part[i].srt.pos.x,
				g_enemy.part[i].srt.pos.y,
				g_enemy.part[i].srt.pos.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

			//�e�����݂���ꍇ�͐e�̃��[���h�}�g���N�X������
			if (g_enemy.part[i].parent)
			{
				D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &g_enemy.part[i].parent->mtxWorld);
			}

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)g_enemy.part[i].pMatBuff->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_enemy.part[i].nNumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pD3DTextureEnemy);

				// �`��
				g_enemy.part[i].pMesh->DrawSubset(nCntMat);
			}
			g_enemy.part[i].mtxWorld = mtxWorld;//���[���h�}�g���N�X��ۑ�
		}
	}

	pDevice->SetMaterial(&matDef);// �}�e���A�����f�t�H���g�ɖ߂�
}

//=============================================================================
// �G�l�~�[���擾
//=============================================================================
ENEMY *GetEnemy(void)
{
	return &g_enemy;
}

//=============================================================================
// �ʒu�擾
//=============================================================================
D3DXVECTOR3 GetPositionEnemy(void)
{
	return g_enemy.part[0].srt.pos;//�̂����
}

//=============================================================================
// �����擾
//=============================================================================
D3DXVECTOR3 GetRotationEnemy(void)
{
	return g_enemy.part[0].srt.rot;//�̂����
}

//=============================================================================
// �ړI�̌����擾
//=============================================================================
D3DXVECTOR3 GetRotationDestEnemy(void)
{
	return g_enemy.rotDest;
}

//=============================================================================
// �ړ��ʎ擾
//=============================================================================
D3DXVECTOR3 GetMoveEnemy(void)
{
	return g_enemy.move;
}


void AnimeWalk()
{

	//�A�j���[�V���� 
	int i = (int)g_motionTime;  //���݂̃L�[�t���[���i���o�[

	//loop�ł���悤��
	if (i > g_keyMax - 2)//�ő�L�[�t���[���i���o�[�𒴂�����
	{
		i = 1;
		g_motionTime = 1.0f;
	}

	float dt = 1.0f / g_anime[i].frame;//��Ԃ̊Ԋu����

	g_motionTime += dt;

	if (g_motionTime > g_keyMax - 1.0f)//�ő厞�Ԃ𒴂�����
	{
		g_motionTime = g_keyMax - 1.0f;//�ő厞�Ԃɂ���
	}

	if (g_motionTime - i > 1.0f) //�덷���C���@�z���1.0�𒴂�����
	{
		i++;//���̃L�[�t���[���ɓ���
	}

	if (g_animeState == 0)
	{
		g_motionTime = 0.0f;	//���Z�b�g
		i = (int)g_motionTime;	//�d�v

		if (g_enemy.state != FROZEN)
		{
			g_cancelTime += dt;//0�ԃL�[�t���[����time���g��
		}

		if (g_cancelTime > 1.0f)//�ő厞�Ԃ𒴂�����
		{
			g_cancelTime = 1.0f;//�ő�ő厞�Ԃɂ���
		}

		//�ڑ��̕�Ԃ́@[i] * 1.0�ł��A[i + 1] * 0.0�ł͂Ȃ�
		for (int j = 0; j < 6; j++)//�p�[�c�ԍ�
		{//�ŏ���Ԃɖ߂�
			// Scale
			g_enemy.part[j].srt.scl.x = g_enemy.part[j].srt.scl.x +		
				(g_anime[0].key[j].scl.x - g_enemy.part[j].srt.scl.x)	
				* g_cancelTime;											

			g_enemy.part[j].srt.scl.y =g_enemy.part[j].srt.scl.y +		
				(g_anime[0].key[j].scl.y -g_enemy.part[j].srt.scl.y)	
				* g_cancelTime;											

			g_enemy.part[j].srt.scl.z =g_enemy.part[j].srt.scl.z +		
				(g_anime[0].key[j].scl.z -g_enemy.part[j].srt.scl.z)	
				* g_cancelTime;											

			// Rotation
			g_enemy.part[j].srt.rot.x =g_enemy.part[j].srt.rot.x +		
				(g_anime[0].key[j].rot.x -g_enemy.part[j].srt.rot.x)	
				* g_cancelTime;											

			//g_enemy.part[j].srt.rot.y =g_enemy.part[j].srt.rot.y +	
			//	(g_anime[0].key[j].rot.y -g_enemy.part[j].srt.rot.y)	
			//	* g_cancelTime;											

			g_enemy.part[j].srt.rot.z =g_enemy.part[j].srt.rot.z +		
				(g_anime[0].key[j].rot.z -g_enemy.part[j].srt.rot.z)	
				* g_cancelTime;											

			// Position
			//g_enemy.part[j].srt.pos.x =g_enemy.part[j].srt.pos.x +	
			//	(g_anime[0].key[j].pos.x -g_enemy.part[j].srt.pos.x)	
			//	* g_cancelTime;											

			//g_enemy.part[j].srt.pos.y =g_enemy.part[j].srt.pos.y +	
			//	(g_anime[0].key[j].pos.y -g_enemy.part[j].srt.pos.y)	
			//	* g_cancelTime;											

			//g_enemy.part[j].srt.pos.z =g_enemy.part[j].srt.pos.z +	
			//	(g_anime[0].key[j].pos.z -g_enemy.part[j].srt.pos.z)	
			//	* g_cancelTime;											
		}

	}
	else
	{
		g_cancelTime = 0.0f;	//���Z�b�g

		//�ڑ��̕�Ԃ́@[i] * 1.0�ł��A[i + 1] * 0.0�ł͂Ȃ�
		for (int j = 0; j < 6; j++)//�p�[�c�ԍ�
		{
			// Scale
			g_enemy.part[j].srt.scl.x = g_anime[i].key[j].scl.x +				// �O�̃L�[�t���[���ʒu
				(g_anime[i + 1].key[j].scl.x - g_anime[i].key[j].scl.x)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

			g_enemy.part[j].srt.scl.y = g_anime[i].key[j].scl.y +				// �O�̃L�[�t���[���ʒu
				(g_anime[i + 1].key[j].scl.y - g_anime[i].key[j].scl.y)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

			g_enemy.part[j].srt.scl.z = g_anime[i].key[j].scl.z +				// �O�̃L�[�t���[���ʒu
				(g_anime[i + 1].key[j].scl.z - g_anime[i].key[j].scl.z)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

			// Rotation
			g_enemy.part[j].srt.rot.x = g_anime[i].key[j].rot.x +				// �O�̃L�[�t���[���ʒu
				(g_anime[i + 1].key[j].rot.x - g_anime[i].key[j].rot.x)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

			//g_enemy.part[j].srt.rot.y = g_anime[i].key[j].rot.y +				// �O�̃L�[�t���[���ʒu
			//	(g_anime[i + 1].key[j].rot.y - g_anime[i].key[j].rot.y)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
			//	* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

			g_enemy.part[j].srt.rot.z = g_anime[i].key[j].rot.z +				// �O�̃L�[�t���[���ʒu
				(g_anime[i + 1].key[j].rot.z - g_anime[i].key[j].rot.z)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

			// Position
			//g_enemy.part[j].srt.pos.x = g_anime[i].key[j].pos.x +				// �O�̃L�[�t���[���ʒu
			//	(g_anime[i + 1].key[j].pos.x - g_anime[i].key[j].pos.x)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
			//	* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

			//g_enemy.part[j].srt.pos.y = g_anime[i].key[j].pos.y +				// �O�̃L�[�t���[���ʒu
			//	(g_anime[i + 1].key[j].pos.y - g_anime[i].key[j].pos.y)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
			//	* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

			//g_enemy.part[j].srt.pos.z = g_anime[i].key[j].pos.z +				// �O�̃L�[�t���[���ʒu
			//	(g_anime[i + 1].key[j].pos.z - g_anime[i].key[j].pos.z)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
			//	* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������
		}

	}

}


//���E�㉺�𓙊m����
void AI()
{
	int random;

	//���E�𔻒f
	random = rand() % 3;

	if (random == 0)
	{
		g_left = 1;
		g_right = 0;
	}
	else if (random == 1)
	{
		g_left = 0;
		g_right = 1;
	}
	else if (random == 2)
	{
		g_left = 0;
		g_right = 0;
	}

	//�㉺�𔻒f
	random = rand() % 3;

	if (random == 0)
	{
		g_up = 1;
		g_down = 0;
	}
	else if (random == 1)
	{
		g_up = 0;
		g_down = 1;
	}
	else if (random == 2)
	{
		g_up = 0;
		g_down = 0;
	}
}

//��ԋ߂��R�C���Ɍ�����
int AI2()
{
	ITEM *item = GetItem();

	D3DXVECTOR3 vec;//��Ɨp
	float disBuff = 0;//�A�C�e���Ƃ̋���
	float dis = 9999999;//��ԋ߂�����
	int result = -1;//������ԋ߂��R�C���̔ԍ�

	//������ԋ߂��R�C���̔ԍ����擾
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, item++)
	{
		if ((item->bUse)&&(item->nType == ITEMTYPE_COIN))
		{
			vec = item->pos - g_enemy.part[0].srt.pos;
			disBuff = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

			if (disBuff < dis)
			{
				dis = disBuff;
				result = nCntItem;
			}			
		}
	}

	if (result != -1)
	{
		item = GetItem();//���Z�b�g
		vec = (item + result)->pos - g_enemy.part[0].srt.pos;

		if (vec.x < 0)
		{
			g_left = 1;
			g_right = 0;
		}
		else if (vec.x == 0)
		{
			g_left = 0;
			g_right = 0;
		}
		else if (vec.x > 0)
		{
			g_left = 0;
			g_right = 1;
		}

		if (vec.z < 0)
		{
			g_up = 0;
			g_down = 1;
		}
		else if (vec.z == 0)
		{
			g_up = 0;
			g_down = 0;
		}
		else if (vec.z > 0)
		{
			g_up = 1;
			g_down = 0;
		}

	}
	else
	{
		g_left = g_right = g_up = g_down = 0;//�~�܂�
	}

	PrintDebugProc("������ԋ߂��R�C���̔ԍ� �F%d \n\n", result);

	return result;
	
}


//��ԋ߂��R�C���Ɍ�������A�A�C�e�����E���ɍs����
int AI3()
{
	ITEM *item = GetItem();

	D3DXVECTOR3 vec;//��Ɨp
	float disBuff = 0;//�A�C�e���Ƃ̋���
	float dis = 9999999;//��ԋ߂�����
	int result = -1;//������ԋ߂��R�C���̔ԍ�

	//������ԋ߂��R�C���̔ԍ����擾
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, item++)
	{
		if ((item->bUse))
		{
			vec = item->pos - g_enemy.part[0].srt.pos;
			disBuff = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

			if (disBuff < dis)
			{
				if ((item->nType == ITEMTYPE_ICEBLOCK)&&(g_enemy.holdItem == ITEMTYPE_ICEBLOCK))
				{

				}
				else
				{
					dis = disBuff;
					result = nCntItem;
				}
			}
		}
	}

	if (result != -1)
	{
		item = GetItem();//���Z�b�g
		vec = (item + result)->pos - g_enemy.part[0].srt.pos;

		if (vec.x < 0)
		{
			g_left = 1;
			g_right = 0;
		}
		else if (vec.x == 0)
		{
			g_left = 0;
			g_right = 0;
		}
		else if (vec.x > 0)
		{
			g_left = 0;
			g_right = 1;
		}

		if (vec.z < 0)
		{
			g_up = 0;
			g_down = 1;
		}
		else if (vec.z == 0)
		{
			g_up = 0;
			g_down = 0;
		}
		else if (vec.z > 0)
		{
			g_up = 1;
			g_down = 0;
		}

	}
	else
	{
		g_left = g_right = g_up = g_down = 0;//�~�܂�
	}


	PrintDebugProc("������ԋ߂��R�C���̔ԍ� �F%d \n\n", result);

	return result;

}