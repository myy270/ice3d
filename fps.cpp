//=============================================================================
//
// fps���b�N�̋@�\ [fps.cpp]
// Author : ���p�j
//
//=============================================================================
#include "fps.h"
#include "debugproc.h"

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
#ifdef _DEBUG
//FPS�\���֘A
int		g_nFPS;				// 1�b�̃t���[�����iFPS�j
int		g_nFrameCount;		// �t���[�����J�E���^�[
DWORD	g_dwFPSLastTime;	// �O��FPS���v�Z����Ƃ��̎���
#endif

DWORD	g_dwExecLastTime;	// �O�񏈗����s���Ƃ��̎���
DWORD	g_dwCurrentTime;	// ���݂̎���

//=============================================================================
// ����������
//=============================================================================
void InitFPS(void)
{
	timeBeginPeriod(1);				// �^�C�}�[�̍ŏ����x��1�~���b�ɂ���

#ifdef _DEBUG
	//FPS�\���֘A
	g_nFPS = 0;
	g_nFrameCount = 0;
	g_dwFPSLastTime = timeGetTime();
#endif

	g_dwExecLastTime = timeGetTime();
	
}

//=============================================================================
// �I������
//=============================================================================
void UnitFPS(void)
{
	timeEndPeriod(1);				// �^�C�}�[�̍ŏ����x��߂�
}

//=============================================================================
// �X�V����
//=============================================================================
bool UpdateFPS(void)
{
	g_dwCurrentTime = timeGetTime();

#ifdef _DEBUG
	//FPS�\���֘A
	if ((g_dwCurrentTime - g_dwFPSLastTime) >= 500)								// 0.5�b���ƂɁAFPS���X�V����
	{
		g_nFPS = g_nFrameCount * 1000 / (g_dwCurrentTime - g_dwFPSLastTime);	//1�b�̃t���[�����iFPS�j�Ɋ��Z����
		g_nFrameCount = 0;
		g_dwFPSLastTime = g_dwCurrentTime;
		
	}
#endif

	//FPS���b�N�@�\
	if ((g_dwCurrentTime - g_dwExecLastTime) >= (1000 / FPS))					//1�b�i1000�~���b�j�̂��������̊Ԋu�ŏ������s��
	{
		g_dwExecLastTime = g_dwCurrentTime;
		
#ifdef _DEBUG
		//FPS�\���֘A
		g_nFrameCount++;	
#endif
		
		return true;
	}
	else
	{
		return false;
	}
}

//=============================================================================
// FPS��\��
//=============================================================================
void ShowFPS(void)
{
#ifdef _DEBUG
	//FPS�\���֘A
	PrintDebugProc("FPS:%d\n", g_nFPS);		//FPS��\��
#endif
}



