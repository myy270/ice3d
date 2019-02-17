//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : ���p�j
//
//=============================================================================
#include "score.h"
#include "player.h"
#include "camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_FRAME_SCORE	"data/TEXTURE/frame_score.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	SCORE_SIZE_X		(35.0f)							// �X�R�A�̐����̕�
#define	SCORE_SIZE_Y		(50.0f)							// �X�R�A�̐����̍���
#define	SCORE_INTERVAL_X	(0.0f)							// �X�R�A�̐����̕\���Ԋu

#define	NUM_PLACE			(5)								// �X�R�A�̌���

#define	SCORE_POS_X			(SCREEN_WIDTH - (SCORE_INTERVAL_X + SCORE_SIZE_X) * NUM_PLACE - 20.0f)	// �G�̃X�R�A�̕\����ʒu�w���W 20�͈ʒu���J����
#define	SCORE_POS_Y			(25.0f)																	// �X�R�A�̕\����ʒu�x���W

#define	SCORE_POS_X2		(20.0f)// �v���C���[�̃X�R�A

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);// �G��
void SetTextureScore(int idx, int number);// �G��

HRESULT MakeVertexScore2(LPDIRECT3DDEVICE9 pDevice);// �v���C���[��
void SetTextureScore2(int idx, int number);// �v���C���[��

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureScore[2] = {};	// �e�N�X�`���ւ̃|�C���^

LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffScore = NULL;		// �G�̒��_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffScore2 = NULL;		// �v���C���[�̒��_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

int						g_score;						// �G�̃X�R�A

int						g_score2;						// �v���C���[�̃X�R�A

OBJECT g_winner;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitScore(void)
{


	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_winner = OBJECT_MAX;

	// �X�R�A�̏�����
	g_score = 0;
	g_score2 = 0;
	
	// ���_���̍쐬
	MakeVertexScore(pDevice);

	MakeVertexScore2(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SCORE,			// �t�@�C���̖��O
								&g_pD3DTextureScore[0]);	// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_FRAME_SCORE,		// �t�@�C���̖��O
								&g_pD3DTextureScore[1]);	// �ǂݍ��ރ������[

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	if(g_pD3DTextureScore[0] != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureScore[0]->Release();
		g_pD3DTextureScore[0] = NULL;
	}

	if(g_pD3DTextureScore[1] != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureScore[1]->Release();
		g_pD3DTextureScore[1] = NULL;
	}

	if(g_pD3DVtxBuffScore != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffScore->Release();
		g_pD3DVtxBuffScore = NULL;
	}

	if (g_pD3DVtxBuffScore2 != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffScore2->Release();
		g_pD3DVtxBuffScore2 = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{
	for(int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		int number;
		//�ォ��F������; (NUM_PLACE - nCntPlace)�̌���F������;�@
		//���q��(g_score % (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace))))�̌��ʂ�(NUM_PLACE - nCntPlace)�̌��ȍ~�̐����ł���
		// % �� / �������ƌ�������
		number = (g_score % (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace)))) / (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace - 1)));
		SetTextureScore(nCntPlace, number);


		//�v���C���[��
		number = (g_score2 % (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace)))) / (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace - 1)));
		SetTextureScore2(nCntPlace, number);

	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pD3DVtxBuffScore, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureScore[0]);

	// �|���S���̕`��
	for(int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
	}

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureScore[1]);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (NUM_PLACE * 4), NUM_POLYGON);

	

	//�v���C���[��
	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffScore2, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureScore[0]);

	// �|���S���̕`��
	for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
	}

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureScore[1]);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (NUM_PLACE * 4), NUM_POLYGON);

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (NUM_VERTEX * NUM_PLACE + 4),	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��) +4�̓t���[���̒��_
												D3DUSAGE_WRITEONLY,								// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_2D,									// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,								// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffScore,							// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))											// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += 4)
		{//�����̒��_
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * (SCORE_SIZE_X + SCORE_INTERVAL_X), SCORE_POS_Y, 0.0f);//1 2 3 4 5 6 7 8 �̊i�� �
			pVtx[1].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * (SCORE_INTERVAL_X + SCORE_SIZE_X) + SCORE_SIZE_X, SCORE_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * (SCORE_SIZE_X + SCORE_INTERVAL_X), SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * (SCORE_INTERVAL_X + SCORE_SIZE_X) + SCORE_SIZE_X, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);

			// rhw�̐ݒ�
			pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DCOLOR_RGBA(255, 170, 192, 255);//�s���N
			pVtx[1].diffuse = D3DCOLOR_RGBA(255, 170, 192, 255);
			pVtx[2].diffuse = D3DCOLOR_RGBA(255, 170, 192, 255);
			pVtx[3].diffuse = D3DCOLOR_RGBA(255, 170, 192, 255);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		}

		{//�t���[���̒��_
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(SCORE_POS_X - 15, SCORE_POS_Y-25, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(SCORE_POS_X + (SCORE_INTERVAL_X + SCORE_SIZE_X) * NUM_PLACE + 15, SCORE_POS_Y - 25, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(SCORE_POS_X - 15, SCORE_POS_Y + 55, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(SCORE_POS_X + (SCORE_INTERVAL_X + SCORE_SIZE_X) * NUM_PLACE + 15, SCORE_POS_Y + 55, 0.0f);

			// rhw�̐ݒ�
			pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DCOLOR_RGBA(255, 170, 192, 255);//�s���N
			pVtx[1].diffuse = D3DCOLOR_RGBA(255, 170, 192, 255);
			pVtx[2].diffuse = D3DCOLOR_RGBA(255, 170, 192, 255);
			pVtx[3].diffuse = D3DCOLOR_RGBA(255, 170, 192, 255);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffScore->Unlock();
	}

	return S_OK;
}

HRESULT MakeVertexScore2(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (NUM_VERTEX * NUM_PLACE + 4),	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��) +4�̓t���[���̒��_
												D3DUSAGE_WRITEONLY,								// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_2D,									// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,								// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffScore2,							// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))											// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{
		//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffScore2->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += 4)
		{//�����̒��_
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(SCORE_POS_X2 + nCntPlace * (SCORE_SIZE_X + SCORE_INTERVAL_X), SCORE_POS_Y, 0.0f);//1 2 3 4 5 6 7 8 �̊i�� �
			pVtx[1].vtx = D3DXVECTOR3(SCORE_POS_X2 + nCntPlace * (SCORE_INTERVAL_X + SCORE_SIZE_X) + SCORE_SIZE_X, SCORE_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(SCORE_POS_X2 + nCntPlace * (SCORE_SIZE_X + SCORE_INTERVAL_X), SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(SCORE_POS_X2 + nCntPlace * (SCORE_INTERVAL_X + SCORE_SIZE_X) + SCORE_SIZE_X, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);

			// rhw�̐ݒ�
			pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);//�I�����W
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		}

		{//�t���[���̒��_
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(SCORE_POS_X2 - 15, SCORE_POS_Y-25, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(SCORE_POS_X2 + (SCORE_INTERVAL_X + SCORE_SIZE_X) * NUM_PLACE + 15, SCORE_POS_Y - 25, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(SCORE_POS_X2 - 15, SCORE_POS_Y + 55, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(SCORE_POS_X2 + (SCORE_INTERVAL_X + SCORE_SIZE_X) * NUM_PLACE + 15, SCORE_POS_Y + 55, 0.0f);

			// rhw�̐ݒ�
			pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);//�I�����W
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffScore2->Unlock();
	}

	return S_OK;
}


//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureScore(int idx, int number)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pD3DVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (idx * 4);

	// ���_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(number * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(number * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 1.0f);

	// ���_�f�[�^���A�����b�N����
	g_pD3DVtxBuffScore->Unlock();
}

void SetTextureScore2(int idx, int number)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pD3DVtxBuffScore2->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (idx * 4);

	// ���_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(number * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(number * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 1.0f);

	// ���_�f�[�^���A�����b�N����
	g_pD3DVtxBuffScore2->Unlock();
}
//=============================================================================
// �X�R�A�̕ύX
//=============================================================================
void ChangeScore(int value)
{
	g_score += value;
	if(g_score < 0)
	{
		g_score = 0;
	}
	else if(g_score >= (int)(powf(10.0f, (float)NUM_PLACE )))//���̂���@!!!�@�
	{
		g_score = (int)(powf(10.0f, (float)NUM_PLACE)) - 1;
	}
}

//�v���C���[��
void ChangeScore2(int value)
{
	g_score2 += value;
	if (g_score2 < 0)
	{
		g_score2 = 0;
	}
	else if (g_score2 >= (int)(powf(10.0f, (float)NUM_PLACE)))//���̂���@!!!�@�
	{
		g_score2 = (int)(powf(10.0f, (float)NUM_PLACE)) - 1;
	}

}

void compScore()
{
	if (g_score2 >= g_score)
	{//�v���C���[���ꍇ

		WinScene();//�J�b�g�V�[������
		g_winner = OBJECT_PLAYER;
	}
	else
	{//�v���C���[������

		if (GetPlayMode() == PLAY_MODE_DOUBLE)
		{//2p�̏ꍇ�A2p�ɃJ�b�g�V�[��
			WinScene();//�J�b�g�V�[������
			g_winner = OBJECT_ENEMY;
		}


	}

}

OBJECT GetWinner()
{
	return g_winner;

}