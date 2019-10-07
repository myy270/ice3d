//=============================================================================
//
// ���C������ [main.cpp]
// Author : ���p�j
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "sound.h"
#include "debugproc.h"


#include "win.h"
#include "fps.h"
#include "scene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT Init(HINSTANCE hInstance, int nCmdShow);
void Uninit(void);
void Update(void);
void Draw(void);

void Pause(bool& b);
void Retire(void);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************


//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG		msg;
	bool	rest = false;			//true:�|�[�Y	false:�|�[�Y�ł͂Ȃ�

	// ����������
	if(FAILED(Init(hInstance, nCmdShow)))
	{
		return -1;
	}

	// ���b�Z�[�W���[�v
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE ))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`(���o)
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			if(UpdateFPS())			//���s���x�𐧌�����i�܂�AFPS�����b�N����j
			{
				// ���͍X�V
				UpdateInput();

				//�|�[�Y����
				Pause(rest);

				if (!rest)
				{
					// �X�V����
					Update();

					// �`�揈��
					Draw();
				}
						
			}
		}
	}
	
	// �I������
	Uninit();

	return (int)msg.wParam;		//����ł���΁A���̒l��0
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HINSTANCE hInstance, int nCmdShow)
{
	// �E�B���h�E���쐬
	HWND hWnd = InitWindow(hInstance, nCmdShow);

	// DX����������
	if (FAILED(InitDX(hWnd, true)))
	{
		return E_FAIL;
	}

	InitFPS();

	// ���͏����̏�����
	InitInput(hInstance, hWnd);

	// �f�o�b�O�\�������̏�����
	InitDebugProc();

	// �t�F�[�h�̏�����
	InitFade();

	// �T�E���h�̏�����
	InitSound(hWnd);

	// �Q�[���N����̍ŏ��̃V�[����ݒ肵�ď���������
	SetScene(FIRST_SCENE);


	// �E�C���h�E�̕\��(�����������̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	UnitFPS();

	UninitWindow();

	UninitDX();

	UninitTitle();
	UninitGame();
	UninitResult();

	// �t�F�[�h�̏I������
	UninitFade();

	// �T�E���h�̏I������
	UninitSound();

	// ���͏����̏I������
	UninitInput();

	// �f�o�b�O�\�������̏I������
	UninitDebugProc();

}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	//�^�C�g����ʂɖ߂锻��
	Retire();

	UpdateDebugProc();

	ShowFPS();

	switch(GetScene())
	{
	case SCENE_TITLE:		// �^�C�g����ʂ̍X�V
		UpdateTitle();
		break;

	case SCENE_GAME:			// �Q�[����ʂ̍X�V
		UpdateGame();
		break;

	case SCENE_RESULT:		// ���U���g��ʂ̍X�V

		UpdateGame();		//�Q�[����ʂ�ێ�����

		UpdateResult();	
		break;
	}

	// �t�F�[�h�����̍X�V
	UpdateFade();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	LPDIRECT3DDEVICE9 g_pD3DDevice = GetDevice();

	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (GetScene())
		{
		case SCENE_TITLE:		// �^�C�g����ʂ̕`��
			DrawTitle();
			break;

		case SCENE_GAME:		// �Q�[����ʂ̕`��
			DrawGame();
			break;

		case SCENE_RESULT:		// ���U���g��ʂ̕`��

			DrawGame();			//�Q�[����ʂ�ێ�����

			DrawResult();
			break;
		}

		// �t�F�[�h�`��
		DrawFade();

		// �f�o�b�O�\�������̕`��
		DrawDebugProc();


		// Direct3D�ɂ��`��̏I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}


//=============================================================================
// �|�[�Y����
//=============================================================================
void Pause(bool& b)
{
	//�|�[�Yor�|�[�Y����
	if (GetScene() == SCENE_GAME)
	{
		if (GetKeyboardTrigger(DIK_F3) ||
			(IsButtonPress(0, BUTTON_SHARE) && IsButtonTrigger(0, BUTTON_OPTIONS)) ||
			(IsButtonTrigger(0, BUTTON_SHARE) && IsButtonPress(0, BUTTON_OPTIONS)))
		{
			b = !b;
		}
	}

}

//=============================================================================
// �����I�Ƀ^�C�g����ʂɖ߂锻��
//=============================================================================
void Retire(void)
{
	if (GetKeyboardTrigger(DIK_F4) ||
		(IsButtonPress(0, BUTTON_L3) && IsButtonTrigger(0, BUTTON_R3)) ||
		(IsButtonTrigger(0, BUTTON_L3) && IsButtonPress(0, BUTTON_R3)))
	{		
		SetScene(SCENE_TITLE);
	}

}

