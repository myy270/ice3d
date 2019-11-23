//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : ���p�j
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "function.h"

//*****************************************************************************
// �񋓌^��`
//*****************************************************************************

// g_aParam[SOUND_LABEL_MAX]�̃p�X�ƑΉ����ĕ���
enum SOUND_LABEL
{
	SOUND_LABEL_BGM000,				// BGM
	SOUND_LABEL_SE_COIN,			// �R�C�����E�����ʉ�
	SOUND_LABEL_SE_TEST,			// �e�X�g��
	SOUND_LABEL_SE_PAUSE,			// �|�[�Y��
	SOUND_LABEL_SE_CURORMOVE,		// �J�[�\���̈ړ���
	SOUND_LABEL_SE_CURORYES,		// �J�[�\���̌��艹
	SOUND_LABEL_SE_TITLESTART,		// �^�C�g����ʂɃX�^�[�g�{�^������������
	SOUND_LABEL_SE_TIMEEND,			// �^�C�}�[�I�������
	SOUND_LABEL_SE_USEICEBLOCK,		// �����A�C�e�����g����
	SOUND_LABEL_SE_ICEBLOCKDROP,	// �����A�C�e�����������鉹
	SOUND_LABEL_SE_GETICEBLOCK,		// �����A�C�e�����E�����ʉ�
	SOUND_LABEL_SE_OPENING,			// �I�[�v�j���O��
	SOUND_LABEL_SE_TIMEWARNING,		// �^�C���E�H�[�j���O��
	SOUND_LABEL_SE_WIN,				// ������
	SOUND_LABEL_SE_GAMEOVER,		// �Q�[���I�[�o�[��
	SOUND_LABEL_SE_RETIRE,			// �^�C�g����ʂɖ߂鉹 
	SOUND_LABEL_SE_DRAW,			// ���������̉� 

	SOUND_LABEL_MAX,

};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

HRESULT InitSound(HWND hWnd);
void UpdateSound();
void UninitSound(void);

HRESULT PlaySound(SOUND_LABEL label, bool isLoop, bool isEncore = true);
void StopSound(SOUND_LABEL label, bool isTempStop = true);

void StopSoundALL(bool isTempStop = true);
HRESULT PlaySoundAll();

#endif
