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
int		g_nFPS;			// 1�b�̃t���[�����iFPS�j
int		g_nFrameCount;	// �t���[�����J�E���^�[
DWORD	dwFPSLastTime;	// �O��FPS���v�Z����Ƃ��̎���
#endif

DWORD	dwExecLastTime;	// �O�񏈗����s���Ƃ��̎���
DWORD	dwCurrentTime;	// ���݂̎���


void InitFPS(void)
{
	timeBeginPeriod(1);				// �^�C�}�[�̍ŏ����x��1�~���b�ɂ���

#ifdef _DEBUG
	//FPS�\���֘A
	g_nFPS = 0;
	g_nFrameCount = 0;
	dwFPSLastTime = timeGetTime();
#endif

	dwExecLastTime = timeGetTime();
	

}

bool UpdateFPS(void)
{
	dwCurrentTime = timeGetTime();

#ifdef _DEBUG
	//FPS�\���֘A
	if ((dwCurrentTime - dwFPSLastTime) >= 500)								// 0.5�b���ƂɁAFPS���X�V����
	{
		g_nFPS = g_nFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);	//1�b�̃t���[�����iFPS�j�Ɋ��Z����
		g_nFrameCount = 0;
		dwFPSLastTime = dwCurrentTime;
		
	}
#endif

	//FPS���b�N�@�\
	if ((dwCurrentTime - dwExecLastTime) >= (1000 / FPS))					//1�b�i1000�~���b�j�̂��������̊Ԋu�ŏ������s��
	{
		dwExecLastTime = dwCurrentTime;
		
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


void ShowFPS(void)
{
#ifdef _DEBUG
	//FPS�\���֘A
	PrintDebugProc("FPS:%d\n", g_nFPS);		//FPS��\��
#endif
}



void UnitFPS(void)
{
	timeEndPeriod(1);				// �^�C�}�[�̍ŏ����x��߂�
}


