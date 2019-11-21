//=============================================================================
//
// �E�B���h�E�̏��� [win.cpp]
// Author : ���p�j
//
//=============================================================================
#include "win.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define CLASS_NAME		"AppClass"					// �E�C���h�E�̃N���X��

#ifdef _DEBUG
#define WINDOW_NAME		"ICE3D(debug)"				// �E�C���h�E�̃L���v�V������
#else
#define WINDOW_NAME		"ICE3D(release)"			// �E�C���h�E�̃L���v�V������
#endif

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

WNDCLASSEX g_wcex;

//=============================================================================
// ����������	//�E�B���h�E�����
//=============================================================================
HWND InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	// �E�B���h�E�N���X�����
	g_wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,						// callback�֐�
		0,
		0,
		hInstance,
		NULL,							// �E�B���h�E�̃A�C�R���̐ݒ�
		LoadCursor(NULL, IDC_ARROW),	// �J�[�\���̐ݒ�
		(HBRUSH)(COLOR_WINDOWFRAME),	// �w�i�F�̐ݒ�
		NULL,
		CLASS_NAME,						// �E�C���h�E�̃N���X��
		NULL							// �E�B���h�E�ŏ�����̃A�C�R���̐ݒ�
	};

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&g_wcex);

	// �E�B���h�E�̍쐬
	HWND hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		100,																					// �E�B���h�E�̏����ʒux
		0,																						// �E�B���h�E�̏����ʒuy
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,										// �E�B���h�E�̃T�C�Yx
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	// �E�B���h�E�̃T�C�Yy
		NULL,
		NULL,
		hInstance,
		NULL);

	return hWnd;


}

//=============================================================================
// �I������
//=============================================================================
void UninitWindow(void)
{
	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, g_wcex.hInstance);

}

//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:			//�E�C���h�E�E��̂w�A�C�R�����N���b�N����ȂǁA�E�B���h�E��j�����郁�b�Z�[�W����������
		PostQuitMessage(0);		
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:					// [ESC]�L�[�������ꂽ
			DestroyWindow(hWnd);		// �E�B���h�E��j������悤�w������
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}