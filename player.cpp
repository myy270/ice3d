//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : ���p�j
//
//=============================================================================
#include "player.h"
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
#define	BODY_PLAYER		"data/MODEL/bearBody.x"	// �ǂݍ��ރ��f����
#define	HEAD_PLAYER		"data/MODEL/bearHead.x"	// �ǂݍ��ރ��f����
#define	HAND_PLAYER		"data/MODEL/bearHand.x"	// �ǂݍ��ރ��f����
#define	LEG_PLAYER		"data/MODEL/bearLeg.x"	// �ǂݍ��ރ��f����
#define	ICE_BLOCK		"data/MODEL/iceBlock.x"		// �ǂݍ��ރ��f����



#define	PLAYER_RADIUS		(15.0f)						// ���a

#define	VALUE_MOVE_PLAYER	(0.195f)					// �ړ����x
#define	RATE_MOVE_PLAYER	(0.025f)					// �ړ������W��

#define	VALUE_ROTATE_PLAYER	(D3DX_PI * 0.025f)			// ��]���x 4.5�x
#define	RATE_ROTATE_PLAYER	(0.10f)						// ��]�����W��

#define	VALUE_MOVE_BULLET	(7.5f)						// �e�̈ړ����x

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void WriteAnime();
void AnimeWalk();


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer;		// �e�N�X�`���ǂݍ��ݏꏊ
PLAYER				g_player;					// �v���C���[���[�N

int g_mode = MODE_EDIT;//�ҏS���[�h���ǂ���
int g_conId = 0;//�R���g���[��ID

float g_motionTime = 0.0f;	// �A�j���[�V�����S�̎���
int g_keyMax;				//�L�[�t���[���̐�
bool g_animeState = 0;		//�������ǂ���

float g_cancelTime = 0.0f;// �ŏ���Ԃɖ߂鎞��


KEY g_anime[] =
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
HRESULT InitPlayer(void)
{
	

	g_keyMax = sizeof(g_anime) / sizeof(KEY);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_player.part[0].partFile = (char *)BODY_PLAYER;//�e�͈�Ԑ�ɂ��Ȃ���΂Ȃ�Ȃ�
	g_player.part[1].partFile = (char *)HEAD_PLAYER;//(const char *)����(char *)�ɕϊ�
	g_player.part[2].partFile = (char *)HAND_PLAYER;//����
	g_player.part[3].partFile = (char *)HAND_PLAYER;//�E��
	g_player.part[4].partFile = (char *)LEG_PLAYER;//����
	g_player.part[5].partFile = (char *)LEG_PLAYER;//�E��

	g_player.part[6].partFile = (char *)ICE_BLOCK;//�X

	for (int i = 0; i < PART_MAX; i++)//�p�[�c�ԍ�
	{
		// X�t�@�C���̓ǂݍ���
		if(FAILED(D3DXLoadMeshFromX(g_player.part[i].partFile,
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_player.part[i].pMatBuff,
									NULL,
									&g_player.part[i].nNumMat,
									&g_player.part[i].pMesh)))
		{
			return E_FAIL;
		}

		switch (i)
		{//�����l pos.y�͑����n�ʂɐG���悤�Ȑ��l
		case 0:
		{//��
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);//xyz�K�������悤��
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(0.0f, 22.4f, 0.0f);//�����n�ʂɐG���悤�A15.0

			g_player.part[i].parent = NULL;//�̂̐e��NULL�ɂ���
			break;
		}
		case 1:
		{//��
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(0.0f, 6.5f, 0.0f);

			g_player.part[i].parent = &g_player.part[0];//�̂�e�ɂ���
			break;
		}
		case 2:
		{//����
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(5.0f, 5.0f, 0.0f);

			g_player.part[i].parent = &g_player.part[0];//�̂�e�ɂ���
			break;
		}
		case 3:
		{//�E��
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(-5.0f, 5.0f, 0.0f);

			g_player.part[i].parent = &g_player.part[0];//�̂�e�ɂ���
			break;
		}
		case 4:
		{//����
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(3.064f, -4.873f, -0.409f);

			g_player.part[i].parent = &g_player.part[0];//�̂�e�ɂ���
			break;
		}
		case 5:
		{//�E��
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(-3.064f, -4.873f, -0.409f);

			g_player.part[i].parent = &g_player.part[0];//�̂�e�ɂ���
			break;
		}

		default:
		{
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			g_player.part[i].parent = &g_player.part[0];//�̂�e�ɂ���
			break;
		}

		}

		if (i != 6)
		{
			g_player.part[i].use = true;
		}
		else
		{
			g_player.part[i].use = false;
		}
	}

	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.fRadius = PLAYER_RADIUS;
	// �e��ݒ� //�̂����
	g_player.nIdxShadow = SetShadow(g_player.part[0].srt.pos, g_player.fRadius * 2.0f, g_player.fRadius * 2.0f);


	g_player.holdItem = ITEMTYPE_COIN;
	g_player.state = NORMAL;
	g_player.stateTime = 0;

#if 0
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_PLAYER,		// �t�@�C���̖��O
								&g_pD3DTexturePlayer);	// �ǂݍ��ރ������[
#endif

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	for (int i = 0; i < PART_MAX; i++)//�p�[�c�ԍ�
	{
		if (g_player.part[i].pMesh != NULL)
		{// ���b�V���̊J��
			g_player.part[i].pMesh->Release();
			g_player.part[i].pMesh = NULL;
		}

		if (g_player.part[i].pMatBuff != NULL)
		{// �}�e���A���̊J��
			g_player.part[i].pMatBuff->Release();
			g_player.part[i].pMatBuff = NULL;
		}
	}

	if (g_pD3DTexturePlayer != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePlayer->Release();
		g_pD3DTexturePlayer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
#ifdef _DEBUG
	//���[�h�̓���
	if (GetKeyboardPress(DIK_1))
	{
		g_mode = MODE_PLAY;
	}
	if (GetKeyboardPress(DIK_2))
	{
		g_mode = MODE_EDIT;
	}

	//�R���g���[��ID�̓���
	if (GetKeyboardPress(DIK_NUMPAD0))
	{
		g_conId = 0;
	}
	else if (GetKeyboardPress(DIK_NUMPAD1))
	{
		g_conId = 1;
	}
	else if (GetKeyboardPress(DIK_NUMPAD2))
	{
		g_conId = 2;
	}
	else if (GetKeyboardPress(DIK_NUMPAD3))
	{
		g_conId = 3;
	}
	else if (GetKeyboardPress(DIK_NUMPAD4))
	{
		g_conId = 4;
	}
	else if (GetKeyboardPress(DIK_NUMPAD5))
	{
		g_conId = 5;
	}
#endif





	switch (g_mode)
	{
	case MODE_PLAY:
	{
		//�A�j���[�V���� 
		int i = (int)g_motionTime;  //���݂̃L�[�t���[���i���o�[

		//if (i > g_keyMax - 2)//�ő�L�[�t���[���i���o�[�𒴂�����
		//{
		//	i = g_keyMax - 2;//�ő�L�[�t���[���i���o�[�ɂ���
		//}

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
			g_motionTime = g_keyMax - 1.0f;//�ő�ő厞�Ԃɂ���
		}

		if (g_motionTime - i > 1.0f) //�덷���C���@�z���1.0�𒴂�����
		{
			i++;//���̃L�[�t���[���ɓ���
		}

		//if (GetKeyboardPress(DIK_SPACE))
		//{
		//	g_motionTime = 0.0f;	//���Z�b�g
		//	i = (int)g_motionTime;	//�d�v
		//}

		if (1)
		{
			//�ڑ��̕�Ԃ́@[i] * 1.0�ł��A[i + 1] * 0.0�ł͂Ȃ�
			for (int j = 0; j < PART_MAX; j++)//�p�[�c�ԍ�
			{
				// Scale
				g_player.part[j].srt.scl.x = g_anime[i].key[j].scl.x +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].scl.x - g_anime[i].key[j].scl.x)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				g_player.part[j].srt.scl.y = g_anime[i].key[j].scl.y +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].scl.y - g_anime[i].key[j].scl.y)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				g_player.part[j].srt.scl.z = g_anime[i].key[j].scl.z +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].scl.z - g_anime[i].key[j].scl.z)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				// Rotation
				g_player.part[j].srt.rot.x = g_anime[i].key[j].rot.x +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].rot.x - g_anime[i].key[j].rot.x)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				g_player.part[j].srt.rot.y = g_anime[i].key[j].rot.y +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].rot.y - g_anime[i].key[j].rot.y)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				g_player.part[j].srt.rot.z = g_anime[i].key[j].rot.z +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].rot.z - g_anime[i].key[j].rot.z)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				// Position
				g_player.part[j].srt.pos.x = g_anime[i].key[j].pos.x +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].pos.x - g_anime[i].key[j].pos.x)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				g_player.part[j].srt.pos.y = g_anime[i].key[j].pos.y +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].pos.y - g_anime[i].key[j].pos.y)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

				g_player.part[j].srt.pos.z = g_anime[i].key[j].pos.z +				// �O�̃L�[�t���[���ʒu
					(g_anime[i + 1].key[j].pos.z - g_anime[i].key[j].pos.z)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
					* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������
			}
		}

		break;
	}

	case MODE_EDIT:
	{
		D3DXVECTOR3 rotCamera;
		float fDiffRotY;

		// �J�����̌����擾
		rotCamera = GetRotCamera();

		g_animeState = 0;//�^����Ԃ����Z�b�g

		if((GetTimeOut() == 0) && (g_player.state != FROZEN))
		{//�ړ�
			if (GetKeyboardPress(DIK_A))
			{
				g_animeState = 1;//������Ԃɂ���

				if (GetKeyboardPress(DIK_W))
				{// ���O�ړ�
					g_player.move.x -= sinf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_PLAYER;
					g_player.move.z -= cosf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_PLAYER;

					g_player.rotDest.y = rotCamera.y + D3DX_PI * 0.75f;
				}
				else if (GetKeyboardPress(DIK_S))
				{// ����ړ�
					g_player.move.x -= sinf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
					g_player.move.z -= cosf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;

					g_player.rotDest.y = rotCamera.y + D3DX_PI * 0.25f;
				}
				else
				{// ���ړ�
					g_player.move.x -= sinf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_PLAYER;
					g_player.move.z -= cosf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_PLAYER;

					g_player.rotDest.y = rotCamera.y + D3DX_PI * 0.50f;
				}
			}
			else if (GetKeyboardPress(DIK_D))
			{
				g_animeState = 1;//������Ԃɂ���

				if (GetKeyboardPress(DIK_W))
				{// �E�O�ړ�
					g_player.move.x -= sinf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_PLAYER;
					g_player.move.z -= cosf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_PLAYER;

					g_player.rotDest.y = rotCamera.y - D3DX_PI * 0.75f;
				}
				else if (GetKeyboardPress(DIK_S))
				{// �E��ړ�
					g_player.move.x -= sinf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
					g_player.move.z -= cosf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;

					g_player.rotDest.y = rotCamera.y - D3DX_PI * 0.25f;
				}
				else
				{// �E�ړ�
					g_player.move.x -= sinf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_PLAYER;
					g_player.move.z -= cosf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_PLAYER;

					g_player.rotDest.y = rotCamera.y - D3DX_PI * 0.50f;
				}
			}
			else if (GetKeyboardPress(DIK_W))
			{
				g_animeState = 1;//������Ԃɂ���

				// �O�ړ�
				g_player.move.x -= sinf(D3DX_PI + rotCamera.y) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(D3DX_PI + rotCamera.y) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = D3DX_PI + rotCamera.y;
			}
			else if (GetKeyboardPress(DIK_S))
			{
				g_animeState = 1;//������Ԃɂ���

				// ��ړ�
				g_player.move.x -= sinf(rotCamera.y) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y;
			}

			if (GetKeyboardPress(DIK_T))
			{// �㏸
				g_player.move.y += VALUE_MOVE_PLAYER;
			}
			if (GetKeyboardPress(DIK_Y))
			{// ���~
				g_player.move.y -= VALUE_MOVE_PLAYER;
			}

			if (GetKeyboardPress(DIK_U))
			{// ����]
				g_player.rotDest.y -= VALUE_ROTATE_PLAYER;
				if (g_player.rotDest.y < -D3DX_PI)
				{
					g_player.rotDest.y += D3DX_PI * 2.0f;
				}
			}
			if (GetKeyboardPress(DIK_I))
			{// �E��]
				g_player.rotDest.y += VALUE_ROTATE_PLAYER;
				if (g_player.rotDest.y > D3DX_PI)
				{
					g_player.rotDest.y -= D3DX_PI * 2.0f;
				}
			}

		}

#ifdef _DEBUG
		//�p�[�c�̕ό`
		//x����]
		if (GetKeyboardPress(DIK_Z))
			{
				g_player.part[g_conId].srt.rot.x += VALUE_ROTATE_PLAYER;
				if (g_player.part[g_conId].srt.rot.x > D3DX_PI)
				{
					g_player.part[g_conId].srt.rot.x -= D3DX_PI * 2.0f;
				}

			}
		else if (GetKeyboardPress(DIK_X))
			{
				g_player.part[g_conId].srt.rot.x -= VALUE_ROTATE_PLAYER;
				if (g_player.part[g_conId].srt.rot.x < -D3DX_PI)
				{
					g_player.part[g_conId].srt.rot.x += D3DX_PI * 2.0f;
				}
			}

		//y����]
		if (GetKeyboardPress(DIK_C))
			{
				g_player.part[g_conId].srt.rot.y += VALUE_ROTATE_PLAYER;
				if (g_player.part[g_conId].srt.rot.y > D3DX_PI)
				{
					g_player.part[g_conId].srt.rot.y -= D3DX_PI * 2.0f;
				}

			}
		else if (GetKeyboardPress(DIK_V))
			{
				g_player.part[g_conId].srt.rot.y -= VALUE_ROTATE_PLAYER;
				if (g_player.part[g_conId].srt.rot.y < -D3DX_PI)
				{
					g_player.part[g_conId].srt.rot.y += D3DX_PI * 2.0f;
				}
			}

		//z����]
		if (GetKeyboardPress(DIK_B))
			{
				g_player.part[g_conId].srt.rot.z += VALUE_ROTATE_PLAYER;
				if (g_player.part[g_conId].srt.rot.z > D3DX_PI)
				{
					g_player.part[g_conId].srt.rot.z -= D3DX_PI * 2.0f;
				}

			}
		else if (GetKeyboardPress(DIK_N))
			{
				g_player.part[g_conId].srt.rot.z -= VALUE_ROTATE_PLAYER;
				if (g_player.part[g_conId].srt.rot.z < -D3DX_PI)
				{
					g_player.part[g_conId].srt.rot.z += D3DX_PI * 2.0f;
				}
			}
#endif

		AnimeWalk();


		// �ړI�̊p�x�܂ł̍���
		fDiffRotY = g_player.rotDest.y - g_player.part[0].srt.rot.y;//�̂����
		if (fDiffRotY > D3DX_PI)
		{
			fDiffRotY -= D3DX_PI * 2.0f;
		}
		if (fDiffRotY < -D3DX_PI)
		{
			fDiffRotY += D3DX_PI * 2.0f;
		}

		// �ړI�̊p�x�܂Ŋ�����������@�i�X�ړI�̊p�x�ɕω�����
		g_player.part[0].srt.rot.y += fDiffRotY * RATE_ROTATE_PLAYER;//�̂ɔ��f
		if (g_player.part[0].srt.rot.y > D3DX_PI)
		{
			g_player.part[0].srt.rot.y -= D3DX_PI * 2.0f;
		}
		if (g_player.part[0].srt.rot.y < -D3DX_PI)
		{
			g_player.part[0].srt.rot.y += D3DX_PI * 2.0f;
		}

		/// �ʒu�ړ��𔽉f
		g_player.part[0].srt.pos.x += g_player.move.x;//�̂ɔ��f
		g_player.part[0].srt.pos.y += g_player.move.y;
		g_player.part[0].srt.pos.z += g_player.move.z;

		//�ړ��͈́@//�̂����
		{
			if (g_player.part[0].srt.pos.x < -630.0f)
			{
				g_player.part[0].srt.pos.x = -630.0f;
			}
			if (g_player.part[0].srt.pos.x > 630.0f)
			{
				g_player.part[0].srt.pos.x = 630.0f;
			}
			if (g_player.part[0].srt.pos.y < 10.0f)
			{
				g_player.part[0].srt.pos.y = 10.0f;
			}
			if (g_player.part[0].srt.pos.y > 150.0f)
			{
				g_player.part[0].srt.pos.y = 150.0f;
			}
			if (g_player.part[0].srt.pos.z > 630.0f)
			{
				g_player.part[0].srt.pos.z = 630.0f;
			}
			if (g_player.part[0].srt.pos.z < -630.0f)
			{
				g_player.part[0].srt.pos.z = -630.0f;
			}
		}

		// �ړ��ʂɊ�����������@�^���G�l���M�[���ꕔ�����ĕۑ�����A���̃t���[���Ɏg��
		//���̕����C�R�[�����̃t���[���Ɋl���̉^���G�l���M�[�̏ꍇ�A���x���ő�(6.05f)�ɂȂ��āA���������^���ɂȂ�
		g_player.move.x += (0.0f - g_player.move.x) * RATE_MOVE_PLAYER;//�����Ag_player.move.x = g_player.move.x * (1 - RATE_MOVE_PLAYER;)
		g_player.move.y += (0.0f - g_player.move.y) * RATE_MOVE_PLAYER;
		g_player.move.z += (0.0f - g_player.move.z) * RATE_MOVE_PLAYER;

		break;
	}

	}//switch end

// �e����
#ifdef _DEBUG
	if (0)
	{
		if ((GetTimeOut() == 0) && (g_player.state != FROZEN))
		{
			if (GetKeyboardTrigger(DIK_SPACE))
			{
				D3DXVECTOR3 pos;
				D3DXVECTOR3 move;

				//�̂����
				pos.x = g_player.part[0].srt.pos.x - sinf(g_player.part[0].srt.rot.y) * g_player.fRadius;//��s�@�����̕ӂ�ɐݒ�
				pos.y = g_player.part[0].srt.pos.y;
				pos.z = g_player.part[0].srt.pos.z - cosf(g_player.part[0].srt.rot.y) * g_player.fRadius;

				//��]�p�x���v���X�̎��A���v���
				//sinf�Acosf�̕��������傤�ǈړ��ʂ̕����Ƒ�������A������-sinf�A-cosf
				move.x = -sinf(g_player.part[0].srt.rot.y) * VALUE_MOVE_BULLET;//�̂����
				move.y = 0.0f;
				move.z = -cosf(g_player.part[0].srt.rot.y) * VALUE_MOVE_BULLET;

				SetBullet(pos, move, 4.0f, 4.0f, 60 * 4);

				// SE�Đ�
				PlaySound(SOUND_LABEL_SE_SHOT);
			}
		}
	}
#endif

	// �e�̈ʒu�ݒ�
	{//�̂����
		SetPositionShadow(g_player.nIdxShadow, D3DXVECTOR3(g_player.part[0].srt.pos.x, 0.1f, g_player.part[0].srt.pos.z));
		//�����ɂ��A�e�̃T�C�Y���ω�����
		float fSizeX = 20.0f + (g_player.part[0].srt.pos.y - 10.0f) * 0.05f;
		if(fSizeX < 20.0f)
		{
			fSizeX = 20.0f;
		}
		float fSizeY = 20.0f + (g_player.part[0].srt.pos.y - 10.0f) * 0.05f;
		if(fSizeY < 20.0f)
		{
			fSizeY = 20.0f;
		}

		SetVertexShadow(g_player.nIdxShadow, fSizeX, fSizeY);
		//�����ɂ��A�e�̓����x���ω�����
		float colA = (200.0f - (g_player.part[0].srt.pos.y - 10.0f)) / 400.0f;
		if(colA < 0.0f)
		{
			colA = 0.0f;
		}
		SetColorShadow(g_player.nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));
	}

	//�ړ�������1���傫���ꍇ�A�W�F�b�g�̉�����
	if((g_player.move.x * g_player.move.x
	+ g_player.move.y * g_player.move.y
	+ g_player.move.z * g_player.move.z) > 1.0f)
	{
		D3DXVECTOR3 pos;
		//�̂����
		pos.x = g_player.part[0].srt.pos.x + sinf(g_player.part[0].srt.rot.y) * g_player.fRadius;//��s�@�����̕ӂ�ɐݒ�
		pos.y = g_player.part[0].srt.pos.y + 2.0f;
		pos.z = g_player.part[0].srt.pos.z + cosf(g_player.part[0].srt.rot.y) * g_player.fRadius;

		// �G�t�F�N�g�̐ݒ�
		SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DXCOLOR(0.85f, 0.15f, 0.0f, 0.50f), 14.0f, 14.0f, 20);//�I�����W
		SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DXCOLOR(0.15f, 0.75f, 0.0f, 0.30f), 10.0f, 10.0f, 20);//��
		SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DXCOLOR(0.0f, 0.10f, 0.0f, 0.15f), 5.0f, 5.0f, 20);//��
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
				fLength = (g_player.part[0].srt.pos.x - pItem->pos.x) * (g_player.part[0].srt.pos.x - pItem->pos.x)
							+ (g_player.part[0].srt.pos.y - pItem->pos.y) * (g_player.part[0].srt.pos.y - pItem->pos.y)
							+ (g_player.part[0].srt.pos.z - pItem->pos.z) * (g_player.part[0].srt.pos.z - pItem->pos.z);
				if(fLength < (g_player.fRadius + pItem->fRadius) * (g_player.fRadius + pItem->fRadius))
				{
					if (g_player.holdItem && (pItem->nType != ITEMTYPE_COIN))
					{//�A�C�e�������Ă���ꍇ�A�ق��̃A�C�e�����E���Ȃ�

					}
					else
					{
						if (pItem->nType == ITEMTYPE_ICEBLOCK)
						{
							g_player.holdItem = ITEMTYPE_ICEBLOCK;
						}
						else if(pItem->nType == ITEMTYPE_COIN)
						{
							// �X�R�A���Z
							ChangeScore2(100);

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


	if ((GetTimeOut() == 0) && (g_player.state != FROZEN))
	{
		if (GetKeyboardTrigger(DIK_SPACE))
		{//�����A�C�e�����g��
			Freeze(OBJECT_ENEMY);
		}
	}

	//�������
	if (g_player.state == FROZEN)
	{
		if (g_player.stateTime == 0)
		{
			g_player.state = NORMAL;
			g_player.part[6].use = false;
		}
		else
		{
			g_player.stateTime--;
			g_player.part[6].use = true;

		}
	}

//�^�����������o��
#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_F2))
	{
		WriteAnime();
	}
#endif

	PrintDebugProc("�R���g���[���̃p�[�c�ԍ��F%d \n\n", g_conId);

	PrintDebugProc("[S�F(%f : %f : %f)]\n", g_player.part[g_conId].srt.scl.x, 
											g_player.part[g_conId].srt.scl.y, 
											g_player.part[g_conId].srt.scl.z);

	PrintDebugProc("[R�F(%f : %f : %f)]\n", g_player.part[g_conId].srt.rot.x, 
											g_player.part[g_conId].srt.rot.y, 
											g_player.part[g_conId].srt.rot.z);

	PrintDebugProc("[T�F(%f : %f : %f)]\n\n", g_player.part[g_conId].srt.pos.x, 
											g_player.part[g_conId].srt.pos.y, 
											g_player.part[g_conId].srt.pos.z);

	PrintDebugProc("�ړI�����F%f \n\n", g_player.rotDest.y);

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;
	D3DXMATERIAL *pD3DXMat;

	D3DMATERIAL9 matDef;
	pDevice->GetMaterial(&matDef);// �f�t�H���g�̃}�e���A�����擾

	for (int i = 0; i < PART_MAX; i++)//�p�[�c�ԍ�
	{
		if (g_player.part[i].use)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, g_player.part[i].srt.scl.x,
				g_player.part[i].srt.scl.y,
				g_player.part[i].srt.scl.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.part[i].srt.rot.y,
				g_player.part[i].srt.rot.x,
				g_player.part[i].srt.rot.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_player.part[i].srt.pos.x,
				g_player.part[i].srt.pos.y,
				g_player.part[i].srt.pos.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

			//�e�����݂���ꍇ�͐e�̃��[���h�}�g���N�X������
			if (g_player.part[i].parent)
			{
				D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &g_player.part[i].parent->mtxWorld);
			}

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)g_player.part[i].pMatBuff->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_player.part[i].nNumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pD3DTexturePlayer);

				// �`��
				g_player.part[i].pMesh->DrawSubset(nCntMat);
			}
			g_player.part[i].mtxWorld = mtxWorld;//���[���h�}�g���N�X��ۑ�
		}
	}
	pDevice->SetMaterial(&matDef);// �}�e���A�����f�t�H���g�ɖ߂�
}

//=============================================================================
// �v���C���[���擾
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_player;
}

//=============================================================================
// �ʒu�擾
//=============================================================================
D3DXVECTOR3 GetPositionPlayer(void)
{
	return g_player.part[0].srt.pos;//�̂����
}

//=============================================================================
// �����擾
//=============================================================================
D3DXVECTOR3 GetRotationPlayer(void)
{
	return g_player.part[0].srt.rot;//�̂����
}

//=============================================================================
// �ړI�̌����擾
//=============================================================================
D3DXVECTOR3 GetRotationDestPlayer(void)
{
	return g_player.rotDest;
}

//=============================================================================
// �ړ��ʎ擾
//=============================================================================
D3DXVECTOR3 GetMovePlayer(void)
{
	return g_player.move;
}

// �A�j�������o��
void WriteAnime()
{
	FILE *fp;
	fp = fopen("anime.txt", "a+");//"a+"�͏������݂̃��[�h�B�t�@�C�����Ȃ��ƁA�����ɍ쐬
	if (fp == NULL)
	{
		return;
	}
		
	//\t�@�����^�u
	fprintf(fp, "\t{\n");
	fprintf(fp, "\t\t60,\n");//60�t���[��
	fprintf(fp, "\t\t{\n");

	for (int i = 0; i < PART_MAX; i++)
	{
		fprintf(fp, "\t\t\t{// part %d\n", i);
		fprintf(fp, "\t\t\t\tD3DXVECTOR3(%.4ff,%.4ff,%.4ff),//S\n", g_player.part[i].srt.scl.x,
																	g_player.part[i].srt.scl.y,
																	g_player.part[i].srt.scl.z);
																				  
		fprintf(fp, "\t\t\t\tD3DXVECTOR3(%.4ff,%.4ff,%.4ff),//R\n", g_player.part[i].srt.rot.x,
																	g_player.part[i].srt.rot.y,
																	g_player.part[i].srt.rot.z);
																				  
		fprintf(fp, "\t\t\t\tD3DXVECTOR3(%.4ff,%.4ff,%.4ff),//T\n", g_player.part[i].srt.pos.x,
																	g_player.part[i].srt.pos.y,
																	g_player.part[i].srt.pos.z);

		fprintf(fp, "\t\t\t},\n");
		fprintf(fp, "\n");
	}
	fprintf(fp, "\t\t}\n");
	fprintf(fp, "\t},///////////////////////////////////////////////////////////////////////////////////\n");
	fprintf(fp, "\n");

	fclose(fp);
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

		if (g_player.state != FROZEN)
		{
			g_cancelTime += dt;//0�ԃL�[�t���[����time���g��
		}

		if (g_cancelTime > 1.0f)//�ő厞�Ԃ𒴂�����
		{
			g_cancelTime = 1.0f;//�ő�ő厞�Ԃɂ���
		}

		//�ڑ��̕�Ԃ́@[i] * 1.0�ł��A[i + 1] * 0.0�ł͂Ȃ�
		for (int j = 0; j < 6; j++)//�p�[�c�ԍ�
		{//�ŏ��̃L�[�̏�Ԃɖ߂�
			// Scale
			g_player.part[j].srt.scl.x = g_player.part[j].srt.scl.x +	
				(g_anime[0].key[j].scl.x - g_player.part[j].srt.scl.x)	
				* g_cancelTime;											

			g_player.part[j].srt.scl.y = g_player.part[j].srt.scl.y +	
				(g_anime[0].key[j].scl.y - g_player.part[j].srt.scl.y)	
				* g_cancelTime;											

			g_player.part[j].srt.scl.z = g_player.part[j].srt.scl.z +	
				(g_anime[0].key[j].scl.z - g_player.part[j].srt.scl.z)	
				* g_cancelTime;											

			// Rotation
			g_player.part[j].srt.rot.x = g_player.part[j].srt.rot.x +	
				(g_anime[0].key[j].rot.x - g_player.part[j].srt.rot.x)	
				* g_cancelTime;											

			//g_player.part[j].srt.rot.y = g_player.part[j].srt.rot.y +	
			//	(g_anime[0].key[j].rot.y - g_player.part[j].srt.rot.y)	
			//	* g_cancelTime;											

			g_player.part[j].srt.rot.z = g_player.part[j].srt.rot.z +	
				(g_anime[0].key[j].rot.z - g_player.part[j].srt.rot.z)	
				* g_cancelTime;											

			// Position
			//g_player.part[j].srt.pos.x = g_player.part[j].srt.pos.x +	
			//	(g_anime[0].key[j].pos.x - g_player.part[j].srt.pos.x)	
			//	* g_cancelTime;											

			//g_player.part[j].srt.pos.y = g_player.part[j].srt.pos.y +	
			//	(g_anime[0].key[j].pos.y - g_player.part[j].srt.pos.y)	
			//	* g_cancelTime;											

			//g_player.part[j].srt.pos.z = g_player.part[j].srt.pos.z +	
			//	(g_anime[0].key[j].pos.z - g_player.part[j].srt.pos.z)	
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
			g_player.part[j].srt.scl.x = g_anime[i].key[j].scl.x +				// �O�̃L�[�t���[���ʒu
				(g_anime[i + 1].key[j].scl.x - g_anime[i].key[j].scl.x)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

			g_player.part[j].srt.scl.y = g_anime[i].key[j].scl.y +				// �O�̃L�[�t���[���ʒu
				(g_anime[i + 1].key[j].scl.y - g_anime[i].key[j].scl.y)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

			g_player.part[j].srt.scl.z = g_anime[i].key[j].scl.z +				// �O�̃L�[�t���[���ʒu
				(g_anime[i + 1].key[j].scl.z - g_anime[i].key[j].scl.z)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

			// Rotation
			g_player.part[j].srt.rot.x = g_anime[i].key[j].rot.x +				// �O�̃L�[�t���[���ʒu
				(g_anime[i + 1].key[j].rot.x - g_anime[i].key[j].rot.x)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

			//g_player.part[j].srt.rot.y = g_anime[i].key[j].rot.y +				// �O�̃L�[�t���[���ʒu
			//	(g_anime[i + 1].key[j].rot.y - g_anime[i].key[j].rot.y)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
			//	* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

			g_player.part[j].srt.rot.z = g_anime[i].key[j].rot.z +				// �O�̃L�[�t���[���ʒu
				(g_anime[i + 1].key[j].rot.z - g_anime[i].key[j].rot.z)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
				* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

			// Position
			//g_player.part[j].srt.pos.x = g_anime[i].key[j].pos.x +				// �O�̃L�[�t���[���ʒu
			//	(g_anime[i + 1].key[j].pos.x - g_anime[i].key[j].pos.x)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
			//	* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

			//g_player.part[j].srt.pos.y = g_anime[i].key[j].pos.y +				// �O�̃L�[�t���[���ʒu
			//	(g_anime[i + 1].key[j].pos.y - g_anime[i].key[j].pos.y)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
			//	* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������

			//g_player.part[j].srt.pos.z = g_anime[i].key[j].pos.z +				// �O�̃L�[�t���[���ʒu
			//	(g_anime[i + 1].key[j].pos.z - g_anime[i].key[j].pos.z)			// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
			//	* (g_motionTime - i);											// �Ɂ@�S�̃A�j�����Ԃ̏����_�ȉ��̊�����������
		}

	}

}




