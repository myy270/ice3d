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
#define	TEXTURE_NUM_TIMER		"data/TEXTURE/number000.png"	// �^�C�}�[�̐���
#define	TEXTURE_FRAME_TIMER		"data/TEXTURE/frame_timer.png"	// �^�C�}�[�̘g

#define	NUM_WIDTH				FIT_WIDTH(35)													// �^�C�}�[�̒P�̂̐����̕�
#define	NUM_HEIGHT				FIT_HEIGHT(50)													// �^�C�}�[�̒P�̂̐����̍���
#define	NUM_INTERVAL			FIT_WIDTH(0)													// �^�C�}�[�̐����̕\���Ԋu
#define	NUM_PLACE				(3)																// �^�C�}�[�̐����̌���
#define	NUM_ALL_WIDTH			NUM_WIDTH * NUM_PLACE + NUM_INTERVAL * (NUM_PLACE - 1)			// �^�C�}�[�̑S���̐����̕�
#define	NUM_POS_X				TEXTURE_CENTER_X(NUM_ALL_WIDTH)									// ��ԍ��̐����̍��㒸�_��X���W
#define	NUM_POS_Y				SCREEN_HEIGHT * 0.035f											// ��ԍ��̐����̍��㒸�_��Y���W

#define	TIMER_PADDING_LEFT		FIT_WIDTH(17.5)													// �^�C�}�[�̐����ƃt���[���̍��Ԋu
#define	TIMER_PADDING_RIGHT		FIT_WIDTH(17.5)													// �^�C�}�[�̐����ƃt���[���̉E�Ԋu
#define	TIMER_PADDING_TOP		FIT_HEIGHT(25)													// �^�C�}�[�̐����ƃt���[���̏�Ԋu
#define	TIMER_PADDING_BOTTOM	FIT_HEIGHT(5)													// �^�C�}�[�̐����ƃt���[���̉��Ԋu
#define	TIMER_POS_X				NUM_POS_X - TIMER_PADDING_LEFT									// �^�C�}�[�̃t���[���̍��㒸�_��X���W
#define	TIMER_POS_Y				NUM_POS_Y - TIMER_PADDING_TOP									// �^�C�}�[�̃t���[���̍��㒸�_��Y���W
#define	TIMER_WIDTH				NUM_ALL_WIDTH + TIMER_PADDING_LEFT + TIMER_PADDING_RIGHT		// �^�C�}�[�̕�
#define	TIMER_HEIGHT			NUM_HEIGHT + TIMER_PADDING_TOP + TIMER_PADDING_BOTTOM			// �^�C�}�[�̍���

#define SECOND_MAX				(int)(powf(10.0f, (float)NUM_PLACE) - 1)						//�^�C�}�[�̍ő�l	�P�ʂ͕b

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice);
void SetTextureTimer(int idx, int number);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTimer[2] = {NULL, NULL};		// [0]:�^�C�}�[�̐����̃e�N�X�`���\�@[1]:�^�C�}�[�̘g�̃e�N�X�`���\
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffTimer = NULL;					// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
				
int						g_nTimerCount;								// �^�C�}�[�̃J�E���g		�P�ʂ̓t���[��
bool					g_bEnableTimer;								// �^�C�}�[����ON/OFF
bool					g_bClockOver;								// ���Ԃ��I��邩�ǂ���
//=============================================================================
// ����������
// second:�^�C�}�[�̏����ݒ莞��	�P�ʂ͕b
//=============================================================================
HRESULT InitTimer(int second)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (second > SECOND_MAX)		//�ő�l�𒴂����
	{
		second = SECOND_MAX;		//�ő�l�ɂȂ�
	}


	g_nTimerCount = second * FPS;


	g_bEnableTimer = true;

	g_bClockOver = false;

	// ���_���̍쐬
	MakeVertexTimer(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_NUM_TIMER,			// �t�@�C���̖��O
								&g_pD3DTextureTimer[0]);	// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_FRAME_TIMER,			// �t�@�C���̖��O
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
	if (GetKeyboardTrigger(DIK_SUBTRACT))
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

	if ((g_nTimerCount <= 0) && (g_bClockOver == false))
	{
		g_bClockOver = true;	//���Ԃ��I�����

		SetFade(FADE_OUT);		//���U���g��ʂփt�F�[�h
	}

	//�^�C�}�[�̊e���̐��������߂�
	for(int i = 0; i < NUM_PLACE; i++)			//i�͐����̍�����n�܂�Y����
	{
		int count = g_nTimerCount + 59;			//�Ⴆ�΁A�c��0.5�b�Ƃ��Ă��A��ʏ�ɂ�1�b�Ƃ��ĕ\�����邽�߂̖���
		count = count / FPS;					//�t���[���P�ʂ���b�P�ʂɓ]������
		
		//�^�C�}�[�̂̊e���̐�����������v�Z����
		int number = (count % (int)(powf(10.0f, (float)(NUM_PLACE - i))))	//�w���Ă��錅�̍��������̂ĂāA�c��̕������Ƃ�;	�Ⴆ�΁Acount = 123, NUM_PLACE = 3 , i = 1,�����̕��q = 23
						/ (int)(powf(10.0f, (float)(NUM_PLACE - i - 1)));	//�Ⴆ�΁Acount = 123, NUM_PLACE = 3 ,i = 1,�����̕��� = 10

		//���̌��ɑΉ��̃e�N�X�`�����Z�b�g
		SetTextureTimer(i, number);
	}
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
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice)
{

	MakeVertex(pDevice, g_pD3DVtxBuffTimer, NUM_PLACE + 1);		//+1 �̓^�C�}�[�̃t���[�����܂ނ���

	{//���_�o�b�t�@�̒��g�𖄂߂�		
		for(int nCntPlace = 0; nCntPlace <= NUM_PLACE; nCntPlace++)		//nCntPlace�͐����̍�����n�߂�Y����
		{
			if (nCntPlace < NUM_PLACE)
			{//	�^�C�}�[�̐���
				
				// ���_���W�̐ݒ�
				SetVtxData(g_pD3DVtxBuffTimer, D3DXVECTOR3(NUM_POS_X + nCntPlace * (NUM_WIDTH + NUM_INTERVAL), NUM_POS_Y, 0.0f), NUM_WIDTH, NUM_HEIGHT, nCntPlace);

				//�e�N�X�`���\���W�̐ݒ�	�����l�A���ƂŕύX����
				SetVtxData(g_pD3DVtxBuffTimer, D3DXVECTOR2(0.0f, 0.0f), 0.1f, 1.0f, nCntPlace);
			}
			else
			{//�^�C�}�[�̃t���[��

				// ���_���W�̐ݒ�
				SetVtxData(g_pD3DVtxBuffTimer, D3DXVECTOR3(TIMER_POS_X, TIMER_POS_Y, 0.0f), TIMER_WIDTH, TIMER_HEIGHT, nCntPlace);

				//�e�N�X�`���\���W�̐ݒ�
				SetVtxData(g_pD3DVtxBuffTimer, D3DXVECTOR2(0.0f, 0.0f), 1.0f, 1.0f, nCntPlace);
			}

			// rhw�̐ݒ�
			SetVtxData(g_pD3DVtxBuffTimer, 1.0f, nCntPlace);

			// ���ˌ��̐ݒ�		�V�A���F�ɂ���
			SetVtxData(g_pD3DVtxBuffTimer, D3DCOLOR_RGBA(0, 255, 255, 255), nCntPlace);


		}
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
// idx:�����̍�����n�܂�Y����
// number:���̌��̐���
//=============================================================================
void SetTextureTimer(int idx, int number)
{
	//���S�̂��߂�
	if (idx >= NUM_PLACE)
	{
		return;
	}

	SetVtxData(g_pD3DVtxBuffTimer, D3DXVECTOR2(number * 0.1f, 0.0f), 0.1f, 1.0f, idx);

}

//=============================================================================
// 
//=============================================================================
void SetEnableTimer(bool b)
{
	g_bEnableTimer = b;
}

//=============================================================================
// 
//=============================================================================
void SetTimer(int second)
{
	g_nTimerCount = second * FPS;	//�b��*�t���[��
}

//=============================================================================
// 
//=============================================================================
int GetTimer()
{
	return g_nTimerCount;
}

//=============================================================================
// 
//=============================================================================
bool IsClockOver()
{
	return g_bClockOver;
}
