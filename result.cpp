//=============================================================================
//
// ���U���g��ʏ��� [result.cpp]
// Author : ���p�j
//
//=============================================================================
#include "result.h"
#include "input.h"
#include "fade.h"
#include "score.h"
#include "title.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_RESULT_WIN			"data/TEXTURE/win_logo.png"				//���@�e�N�X�`���t�@�C����
#define	TEXTURE_RESULT_GAMEOVER		"data/TEXTURE/gameover_logo.png"		//�Q�[���I�[�o�[�@�e�N�X�`���t�@�C����
#define	TEXTURE_RESULT_DRAW			"data/TEXTURE/draw_logo.png"			//���������@�e�N�X�`���t�@�C����

#define	RESULT_LOGO_POS_X			(SCREEN_WIDTH * 0.19f)					// ���U���g���S�̈ʒu(X���W)
#define	RESULT_LOGO_POS_Y			(SCREEN_HEIGHT * 0.65f)					// ���U���g���S�̈ʒu(Y���W)
#define	RESULT_LOGO_WIDTH			FIT_WIDTH(800)							// ���U���g���S�̕�
#define	RESULT_LOGO_HEIGHT			FIT_HEIGHT(200)							// ���U���g���S�̍���

#define	COUNT_APPERA_RESULT			(60)									// ���U���g���S�o���܂ł̑҂�����	

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9		g_pD3DVtxBuffResultLogo = NULL;			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

//�e�N�X�`���t�@�C�����̔z��
const char* g_aTextureFile[] =
{
	TEXTURE_RESULT_WIN,
	TEXTURE_RESULT_GAMEOVER,
	TEXTURE_RESULT_DRAW
	
};

//�e�N�X�`���t�@�C���̐�
const int g_nNumTexture = sizeof(g_aTextureFile) / sizeof(const char*);	

LPDIRECT3DTEXTURE9			g_pD3DTextureResultLogo[g_nNumTexture];		// �e�N�X�`���ւ̃|�C���^�̔z��

int							g_nCountAppearResult = 0;					// �o���܂ł̑҂�����
float						g_fAlphaResult = 0.0f;						// ���U���g���S�̃��l

//=============================================================================
// ����������
//=============================================================================
HRESULT InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nCountAppearResult = 0;
	g_fAlphaResult = 0.0f;

	// ���_���̍쐬
	MakeVertex(pDevice, FVF_VERTEX_2D, g_pD3DVtxBuffResultLogo, D3DXVECTOR3(RESULT_LOGO_POS_X, RESULT_LOGO_POS_Y, 0.0f), RESULT_LOGO_WIDTH, RESULT_LOGO_HEIGHT);

	// �e�N�X�`���̓ǂݍ���
	for (int i = 0;i < g_nNumTexture;i++)
	{
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			g_aTextureFile[i],									// �t�@�C���̖��O
			&g_pD3DTextureResultLogo[i]);						// �ǂݍ��ރ������[
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitResult(void)
{	
	SAFE_RELEASE(g_pD3DVtxBuffResultLogo);

	for (int i = 0; i < g_nNumTexture; i++)
	{
		SAFE_RELEASE(g_pD3DTextureResultLogo[i]);
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResult(void)
{
	g_nCountAppearResult++;

	//��莞�Ԍ�ɁA���S�������オ��n�߂�
	if(g_nCountAppearResult >= COUNT_APPERA_RESULT)
	{
		if(g_fAlphaResult < 1.0f)
		{
			g_fAlphaResult += 0.05f;

			if(g_fAlphaResult > 1.0f)
			{
				g_fAlphaResult = 1.0f;
			}

		}
	}

	if (GetFade() == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTrigger(0, BUTTON_OPTIONS))
		{
			if (g_fAlphaResult < 1.0f)
			{//���S�̕����オ�����������
				g_fAlphaResult = 1.0f;
			}
			else
			{//�t�F�[�h�A�E�g���ăV�[����؂�ւ���				
				SetFade(FADE_OUT);

				PlaySound(SOUND_LABEL_SE_RETIRE, false, true);		//�^�C�g����ʂɖ߂鉹���Đ�
			}
		}

	}

	// �A���t�@�l�̍X�V
	SetVtxDataCor(g_pD3DVtxBuffResultLogo, FVF_VERTEX_2D, D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResult));

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPDIRECT3DTEXTURE9 texture;

	//���ʂɂ���ăe�N�X�`���\��ݒ�
	if (GetPlayMode() == PLAY_MODE_SINGLE)
	{
		if (GetWinner() == OBJECT_PLAYER)
		{
			texture = g_pD3DTextureResultLogo[0];
		}
		else if (GetWinner() == OBJECT_ENEMY)
		{
			texture = g_pD3DTextureResultLogo[1];
		}
		else
		{//���������̏ꍇ
			texture = g_pD3DTextureResultLogo[2];
		}
	}
	else
	{
		if ((GetWinner() == OBJECT_PLAYER))
		{
			texture = g_pD3DTextureResultLogo[0];
		}
		else if (GetWinner() == OBJECT_ENEMY)
		{
			texture = g_pD3DTextureResultLogo[0];
		}
		else
		{//���������̏ꍇ
			texture = g_pD3DTextureResultLogo[2];
		}
	}

	DrawPolygon(pDevice, FVF_VERTEX_2D, g_pD3DVtxBuffResultLogo, texture);

}