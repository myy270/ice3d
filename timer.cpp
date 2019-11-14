//=============================================================================
//
// �^�C�}�[���� [timer.cpp]
// Author : ���p�j
//
//=============================================================================
#include "timer.h"
#include "fade.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_NUM				"data/TEXTURE/number000.png"									// �^�C�}�[�̐���
#define	TEXTURE_FRAME			"data/TEXTURE/frame_timer.png"									// �^�C�}�[�̘g

#define	NUM_WIDTH				FIT_WIDTH(35)													// �^�C�}�[�̒P�̂̐����̕�
#define	NUM_HEIGHT				FIT_HEIGHT(50)													// �^�C�}�[�̒P�̂̐����̍���
#define	NUM_INTERVAL			FIT_WIDTH(0)													// �^�C�}�[�̐����̕\���Ԋu
#define	NUM_PLACE				(3)																// �^�C�}�[�̐����i�P�ʁF�b�j�̌���
#define	NUM_ALL_WIDTH			NUM_WIDTH * NUM_PLACE + NUM_INTERVAL * (NUM_PLACE - 1)			// �^�C�}�[�̑S���̐����̕�
#define	NUM_POS_X				TEXTURE_CENTER_X(NUM_ALL_WIDTH)									// �^�C�}�[�̐擪�̐����̍��㒸�_��X���W
#define	NUM_POS_Y				FIT_HEIGHT(25.0f)												// �^�C�}�[�̐擪�̐����̍��㒸�_��Y���W

#define	PADDING_LEFT			FIT_WIDTH(17.5)													// �^�C�}�[�̐����ƃt���[���̍��Ԋu
#define	PADDING_RIGHT			FIT_WIDTH(17.5)													// �^�C�}�[�̐����ƃt���[���̉E�Ԋu
#define	PADDING_TOP				FIT_HEIGHT(25)													// �^�C�}�[�̐����ƃt���[���̏�Ԋu
#define	PADDING_BOTTOM			FIT_HEIGHT(5)													// �^�C�}�[�̐����ƃt���[���̉��Ԋu

#define	FRAME_POS_X				NUM_POS_X - PADDING_LEFT										// �^�C�}�[�̃t���[���̍��㒸�_��X���W
#define	FRAME_POS_Y				NUM_POS_Y - PADDING_TOP											// �^�C�}�[�̃t���[���̍��㒸�_��Y���W
#define	FRAME_WIDTH				NUM_ALL_WIDTH + PADDING_LEFT + PADDING_RIGHT					// �^�C�}�[�̃t���[���̕�
#define	FRAME_HEIGHT			NUM_HEIGHT + PADDING_TOP + PADDING_BOTTOM						// �^�C�}�[�̃t���[���̍���

#define TIME_MAX				(int)(powf(10.0f, (float)NUM_PLACE) - 1)						// �^�C�}�[�̍ő�l	�P�ʂ͕b

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTimer[2] = {NULL, NULL};		// [0]:�^�C�}�[�̐����̃e�N�X�`���\�@[1]:�^�C�}�[�̘g�̃e�N�X�`���\
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffTimer = NULL;					// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
				
int						g_nTimerCount;								// �^�C�}�[�̃J�E���g		�P�ʂ̓t���[��
bool					g_bEnableTimer;								// �^�C�}�[����ON/OFF
bool					g_bTimeEnd;								// ���Ԃ��I��������ǂ���
//=============================================================================
// ����������
// second:�^�C�}�[�̏����ݒ莞��	�P�ʂ͕b
//=============================================================================
HRESULT InitTimer(int second)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (second > TIME_MAX)		//�ő�l�𒴂����
	{
		second = TIME_MAX;		//�ő�l�ɂȂ�
	}


	g_nTimerCount = second * FPS;	//�b�P�ʂ���t���[���P�ʂɓ]��


	g_bEnableTimer = true;

	g_bTimeEnd = false;

	// ���_���̍쐬
	MakeVertexNumFrame(pDevice, g_pD3DVtxBuffTimer, NUM_PLACE,
		D3DXVECTOR3(NUM_POS_X, NUM_POS_Y, 0.0f), NUM_WIDTH, NUM_HEIGHT, NUM_INTERVAL,
		D3DXVECTOR3(FRAME_POS_X, FRAME_POS_Y, 0.0f), FRAME_WIDTH, FRAME_HEIGHT,
		D3DCOLOR_RGBA(0, 255, 255, 255));	//�V�A��


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_NUM,			// �t�@�C���̖��O
								&g_pD3DTextureTimer[0]);	// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_FRAME,			// �t�@�C���̖��O
								&g_pD3DTextureTimer[1]);	// �ǂݍ��ރ������[

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTimer(void)
{
	SAFE_RELEASE(g_pD3DTextureTimer[0]);
	SAFE_RELEASE(g_pD3DTextureTimer[1]);
	SAFE_RELEASE(g_pD3DVtxBuffTimer);

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTimer(void)
{

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_SUBTRACT))		//�e���L�[�̃}�C�i�X
	{
		g_nTimerCount = 5 * FPS;	//�J���ҋ@�\�A�^�C�}�[�̎��Ԃ�5�b�ɂ���
	}
#endif

	if(g_bEnableTimer)
	{
		g_nTimerCount--;			//���t���[���ɃJ�E���g�_�E��
	}

	if (g_nTimerCount < 0)
	{
		g_nTimerCount = 0;
	}

	if ((g_nTimerCount <= 0) && (g_bTimeEnd == false))
	{
		g_bTimeEnd = true;	//���Ԃ��I�����

		SetFade(FADE_OUT);		//���U���g��ʂփt�F�[�h
	}

	int count = g_nTimerCount + 59;			//�c��0.5�b�Ƃ��Ă��A��ʏ�ɂ�1�b�Ƃ��ĕ\�����邽�߂̖���
	count = count / FPS;					//�t���[���P�ʂ���b�P�ʂɓ]������

	SetVtxData(g_pD3DVtxBuffTimer, count, NUM_PLACE);
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DrawPolygon(pDevice, g_pD3DVtxBuffTimer, g_pD3DTextureTimer[0], 0, NUM_PLACE - 1);

	DrawPolygon(pDevice, g_pD3DVtxBuffTimer, g_pD3DTextureTimer[1], NUM_PLACE, NUM_PLACE);
}

//=============================================================================
// ���Ԓ�~�Ȃǂ̋@�\
//=============================================================================
void SetEnableTimer(bool b)
{
	g_bEnableTimer = b;
}

//=============================================================================
//  ���Ԃ��ăZ�b�g�̋@�\
//=============================================================================
void SetTimer(int second)
{
	g_nTimerCount = second * FPS;	//�b��*�t���[��
}

//=============================================================================
// ���Ԃ̃t���[���P�ʂ̗ʂ��Q�b�g
//=============================================================================
int GetTimer()
{
	return g_nTimerCount;
}

//=============================================================================
// ���ԏI��������ǂ���
//=============================================================================
bool IsTimeEnd()
{
	return g_bTimeEnd;
}
