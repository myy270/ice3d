//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
// Author : ���p�j
//
//=============================================================================
#include "fade.h"
#include "scene.h"
#include "timer.h"
#include "score.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	FADE_RATE				(0.02f)									// �t�F�[�h�̃A���t�@�l�ω���
#define	DEFAULT_FADETYPE		(FADE_IN)								// �f�t�H���g�̃t�F�[�h�̏��
#define	FADE_COLOR				(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))		// �t�F�[�h�̖��̐F

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureFade = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffFade = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
FADETYPE				g_fade;						// �t�F�[�h�̏��
D3DXCOLOR				g_colorFade;				// �t�F�[�h�̖��̐F


//=============================================================================
// ����������
//=============================================================================
HRESULT InitFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_fade = DEFAULT_FADETYPE;						// �Q�[�����J���Ƃ��A�t�F�[�h�C������B

	g_colorFade = FADE_COLOR;

	// ���_���̍쐬
	MakeVertex(pDevice, FVF_VERTEX_2D, g_pD3DVtxBuffFade, D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
	SetVtxDataCor(g_pD3DVtxBuffFade, FVF_VERTEX_2D, g_colorFade);		// �F���Đݒ�

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitFade(void)
{
	SAFE_RELEASE(g_pD3DTextureFade);
	SAFE_RELEASE(g_pD3DVtxBuffFade);

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFade(void)
{
	if(g_fade != FADE_NONE)
	{// �t�F�[�h������
		if(g_fade == FADE_OUT)
		{// �t�F�[�h�A�E�g����
			g_colorFade.a += FADE_RATE;						// ���l�����Z���ĉ�ʂ������Ă���

			if(g_colorFade.a >= 1.0f)
			{// �t�F�[�h�A�E�g�����̎�	
				g_colorFade.a = 1.0f;

				SetFade(FADE_IN);							// �t�F�[�h�C�������ɐ؂�ւ�
				
				// ���̃V�[���̐ݒ�
				SCENE scene = GetScene();					// ���݂̃V�[�����擾
				scene = (SCENE)((scene + 1) % SCENE_MAX);	// �V�[�����P�i�߂�@//int����scene�ɃL���X�g����K�v����
				SetScene(scene);							// �V�[����ݒ�

				if (scene == SCENE_RESULT)
				{//���U���g��ʂ���
					CompareScore();							// �X�R�A���r����
				}
			}

		}
		else if(g_fade == FADE_IN)
		{// �t�F�[�h�C������
			g_colorFade.a -= FADE_RATE;						// ���l�����Z���ĉ�ʂ𕂂��オ�点��

			if(g_colorFade.a <= 0.0f)
			{// �t�F�[�h�C�������̎�				
				g_colorFade.a = 0.0f;

				SetFade(FADE_NONE);
			}
		}
			
		SetVtxDataCor(g_pD3DVtxBuffFade, FVF_VERTEX_2D, g_colorFade);			// �F���Đݒ�
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DrawPolygon(pDevice, FVF_VERTEX_2D, g_pD3DVtxBuffFade, g_pD3DTextureFade);
}

//=============================================================================
// �t�F�[�h�̏�Ԃ̐ݒ�
//=============================================================================
void SetFade(FADETYPE fade)
{
	g_fade = fade;
}

//=============================================================================
// �t�F�[�h�̏�Ԃ̎擾
//=============================================================================
FADETYPE GetFade(void)
{
	return g_fade;
}

