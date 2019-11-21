//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : ���p�j
//
//=============================================================================
#include "score.h"
#include "camera.h"
#include "title.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_NUM			"data/TEXTURE/numberList.png"										// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_FRAME		"data/TEXTURE/frame_score.png"										// �ǂݍ��ރe�N�X�`���t�@�C����

#define	NUM_WIDTH			FIT_WIDTH(35)														// �X�R�A�̒P�̂̐����̕�
#define	NUM_HEIGHT			FIT_HEIGHT(50)														// �X�R�A�̒P�̂̐����̍���
#define	NUM_INTERVAL		FIT_WIDTH(0)														// �X�R�A�̐����̕\���Ԋu
#define	NUM_PLACE			(5)																	// �X�R�A�̐����̌���
#define	NUM_ALL_WIDTH		NUM_WIDTH * NUM_PLACE + NUM_INTERVAL * (NUM_PLACE - 1)				// �X�R�A�̑S���̐����̕�

#define	MARGIN_LEFT			FIT_WIDTH(20.0f)													// ���� �X�R�A�̐擪�̐����ƃE�B���h�E�̍����̋���
#define	MARGIN_RIGHT		FIT_WIDTH(20.0f)													// �E�� �X�R�A�̍Ō�̐����ƃE�B���h�E�̉E���̋���
#define	MARGIN_TOP			FIT_HEIGHT(30.0f)													// �X�R�A�̐����ƃE�B���h�E�̏㉏�̋���

#define	NUM_POS_X			MARGIN_LEFT															// ���� �X�R�A�̐擪�̐����̍��㒸�_��X���W
#define	NUM_POS_X2			(SCREEN_WIDTH - MARGIN_RIGHT - NUM_ALL_WIDTH)						// �E�� �X�R�A�̐擪�̐����̍��㒸�_��X���W
#define	NUM_POS_Y			MARGIN_TOP															// �X�R�A�̐����̍��㒸�_��Y���W

#define	PADDING_LEFT		FIT_WIDTH(15)														// �X�R�A�̐����ƃt���[���̍��Ԋu
#define	PADDING_RIGHT		FIT_WIDTH(15)														// �X�R�A�̐����ƃt���[���̉E�Ԋu
#define	PADDING_TOP			FIT_HEIGHT(25)														// �X�R�A�̐����ƃt���[���̏�Ԋu
#define	PADDING_BOTTOM		FIT_HEIGHT(5)														// �X�R�A�̐����ƃt���[���̉��Ԋu

#define	FRAME_POS_X			NUM_POS_X - PADDING_LEFT											// ���� �X�R�A�̃t���[���̍��㒸�_��X���W
#define	FRAME_POS_X2		NUM_POS_X2 - PADDING_LEFT											// �E��	�X�R�A�̃t���[���̍��㒸�_��X���W
#define	FRAME_POS_Y			NUM_POS_Y - PADDING_TOP												// �X�R�A�̃t���[���̍��㒸�_��Y���W

#define	FRAME_WIDTH			NUM_ALL_WIDTH + PADDING_LEFT + PADDING_RIGHT						// �X�R�A�̃t���[���̕�
#define	FRAME_HEIGHT		NUM_HEIGHT + PADDING_TOP + PADDING_BOTTOM							// �X�R�A�̃t���[���̍���

#define SCORE_MAX			(int)(powf(10.0f, (float)NUM_PLACE) - 1)							// �X�R�A�̍ő�l

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9			g_pD3DTextureScore[2] = {};		// [0]:�����̃e�N�X�`���\�@[1]:�g�̃e�N�X�`���\

LPDIRECT3DVERTEXBUFFER9		g_pD3DVtxBuffScore = NULL;		// ���X�R�A�̒��_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9		g_pD3DVtxBuffScore2 = NULL;		// �E�X�R�A�̒��_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^ 

int							g_score;						// ���̃X�R�A
int							g_score2;						// �E�̃X�R�A

OBJECT						g_winner;						// ����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �X�R�A�̏�����
	g_score = 0;
	g_score2 = 0;

	g_winner = OBJECT_NULL;	

	// ���X�R�A�́@���_���̍쐬
	MakeVertexNumFrame(pDevice, g_pD3DVtxBuffScore, NUM_PLACE,
		D3DXVECTOR3(NUM_POS_X, NUM_POS_Y, 0.0f), NUM_WIDTH, NUM_HEIGHT, NUM_INTERVAL,
		D3DXVECTOR3(FRAME_POS_X, FRAME_POS_Y, 0.0f), FRAME_WIDTH, FRAME_HEIGHT,
		D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f));	//�I�����W

	// �E�X�R�A�́@���_���̍쐬
	MakeVertexNumFrame(pDevice, g_pD3DVtxBuffScore2, NUM_PLACE,
		D3DXVECTOR3(NUM_POS_X2, NUM_POS_Y, 0.0f), NUM_WIDTH, NUM_HEIGHT, NUM_INTERVAL,
		D3DXVECTOR3(FRAME_POS_X2, FRAME_POS_Y, 0.0f), FRAME_WIDTH, FRAME_HEIGHT,
		D3DCOLOR_RGBA(255, 170, 192, 255));	//�s���N
		

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_NUM,				// �t�@�C���̖��O
								&g_pD3DTextureScore[0]);	// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_FRAME,				// �t�@�C���̖��O
								&g_pD3DTextureScore[1]);	// �ǂݍ��ރ������[

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	SAFE_RELEASE(g_pD3DTextureScore[0]);
	SAFE_RELEASE(g_pD3DTextureScore[1]);
	SAFE_RELEASE(g_pD3DVtxBuffScore);
	SAFE_RELEASE(g_pD3DVtxBuffScore2);

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{
	//�����̃e�N�X�`���\���X�V
	SetVtxDataTexNum(g_pD3DVtxBuffScore, g_score, NUM_PLACE);
	SetVtxDataTexNum(g_pD3DVtxBuffScore2, g_score2, NUM_PLACE);

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���̃X�R�A
	DrawPolygon(pDevice, g_pD3DVtxBuffScore, g_pD3DTextureScore[0], 0, NUM_PLACE - 1);

	DrawPolygon(pDevice, g_pD3DVtxBuffScore, g_pD3DTextureScore[1], NUM_PLACE, NUM_PLACE);

	//�E�̃X�R�A
	DrawPolygon(pDevice, g_pD3DVtxBuffScore2, g_pD3DTextureScore[0], 0, NUM_PLACE - 1);

	DrawPolygon(pDevice, g_pD3DVtxBuffScore2, g_pD3DTextureScore[1], NUM_PLACE, NUM_PLACE);

}

//=============================================================================
// �X�R�A�̕ύX
//=============================================================================
void ChangeScore(OBJECT obj,int value)
{
	int* ptr;

	if (obj == OBJECT_PLAYER)
	{
		ptr = &g_score;
	}
	else
	{
		ptr = &g_score2;
	}

	*ptr += value;

	if(*ptr < 0)
	{
		*ptr = 0;
	}
	else if(*ptr > SCORE_MAX)
	{
		*ptr = SCORE_MAX;
	}

}

//=============================================================================
// �X�R�A�̔�r
//=============================================================================
void CompareScore()
{
	if (g_winner == OBJECT_NULL)
	{
		if (g_score >= g_score2)
		{//�v���C���[���ꍇ
			g_winner = OBJECT_PLAYER;
		}
		else
		{//�v���C���[������ꍇ
			g_winner = OBJECT_ENEMY;
		}

		if ((GetPlayMode() == PLAY_MODE_SINGLE) && (g_winner == OBJECT_ENEMY))
		{//AI�����ꍇ
			StopSound(SOUND_LABEL_BGM000, false);				//BGM���~
			PlaySound(SOUND_LABEL_SE_GAMEOVER, false, true);	//�Q�[���I�[�o�[�����Đ�
		}
		else
		{//�v���C���[(1p��2p)�����ꍇ
			SetCameraMode(CAMERA_MODE_CUTSCENE);				//�J�b�g�V�[������	

			StopSound(SOUND_LABEL_BGM000, false);				//BGM���~
			PlaySound(SOUND_LABEL_SE_WIN, false, true);			//�������Đ�
		}
	}

}

//=============================================================================
// ���҂��Q�b�g
//=============================================================================
OBJECT GetWinner()
{
	return g_winner;
}