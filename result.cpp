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
#include "camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_RESULT_WIN		"data/TEXTURE/win_logo.png"			// ���� �e�N�X�`���t�@�C����
#define	TEXTURE_RESULT_GAMEOVER	"data/TEXTURE/gameover_logo.png"	// ������ �e�N�X�`���t�@�C����

#define	RESULT_LOGO_POS_X	(SCREEN_WIDTH * 0.19f)					// ���U���g���S�̈ʒu(X���W)
#define	RESULT_LOGO_POS_Y	(SCREEN_HEIGHT * 0.65f)					// ���U���g���S�̈ʒu(Y���W)
#define	RESULT_LOGO_WIDTH	FIT_WIDTH(800)							// ���U���g���S�̕�
#define	RESULT_LOGO_HEIGHT	FIT_HEIGHT(240)							// ���U���g���S�̍���

#define	COUNT_APPERA_RESULT	(60)									// ���U���g���S�o���܂ł̑҂�����	

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffResultLogo = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

LPDIRECT3DTEXTURE9		g_pD3DTextureResultLogo = NULL;		// ���� �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureResultLogo2 = NULL;	// ������ �e�N�X�`���ւ̃|�C���^

int						g_nCountAppearResult = 0;			// �o���܂ł̑҂�����
float					g_fAlphaResult = 0.0f;				// ���U���g���S�̃��l

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
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_RESULT_WIN,			// �t�@�C���̖��O
								&g_pD3DTextureResultLogo);	// �ǂݍ��ރ������[

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_RESULT_GAMEOVER,	// �t�@�C���̖��O
								&g_pD3DTextureResultLogo2);	// �ǂݍ��ރ������[

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitResult(void)
{	
	SAFE_RELEASE(g_pD3DVtxBuffResultLogo);
	SAFE_RELEASE(g_pD3DTextureResultLogo);
	SAFE_RELEASE(g_pD3DTextureResultLogo2);
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

			if(g_fAlphaResult >= 1.0f)
			{
				g_fAlphaResult = 1.0f;
			}

		}
	}

	// �A���t�@�l�̍X�V
	SetVtxDataCor(g_pD3DVtxBuffResultLogo, FVF_VERTEX_2D, D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResult));

	// Enter����������A�t�F�[�h�A�E�g���ăV�[����؂�ւ���
	if(GetKeyboardTrigger(DIK_RETURN) || IsButtonTrigger(0, BUTTON_OPTIONS))
	{
		SetFade(FADE_OUT);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if ((GetPlayMode() == PLAY_MODE_SINGLE) && (GetWinner() != OBJECT_PLAYER))
	{//1p���[�h�Ńv���C���[������ꍇ
		DrawPolygon(pDevice, g_pD3DVtxBuffResultLogo, g_pD3DTextureResultLogo2);
	}
	else
	{
		DrawPolygon(pDevice, g_pD3DVtxBuffResultLogo, g_pD3DTextureResultLogo);
	}
}