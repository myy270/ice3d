//=============================================================================
//
// �T�E���h���� [sound.cpp]
// Author : ���p�j
//
//=============================================================================
#include <xaudio2.h>			// DX�T�E���h�֘A�̃��C�u�����[

#include "sound.h"
#include "debugproc.h"
#include "input.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

IXAudio2				*g_pXAudio2 = NULL;							// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
IXAudio2MasteringVoice	*g_pMasteringVoice = NULL;					// �}�X�^�[�{�C�X
IXAudio2SourceVoice		*g_apSourceVoice[SOUND_LABEL_MAX] = {};		// �\�[�X�{�C�X
BYTE					*g_apDataAudio[SOUND_LABEL_MAX] = {};		// �I�[�f�B�I�f�[�^
DWORD					g_aSizeAudio[SOUND_LABEL_MAX] = {};			// �I�[�f�B�I�f�[�^�T�C�Y

XAUDIO2_VOICE_STATE		g_xa2state;

// �e���f�ނ̃p�����[�^		enum SOUND_LABEL �ƍ��킹�ĕ���
SOUND_PARAM g_aParam[SOUND_LABEL_MAX] =
{
	{"data/BGM/bgm000.wav", false},	
	{"data/SE/coin000.wav", false},	
	{"data/SE/draw.wav", false},
	{"data/SE/pause.wav", false},
	{"data/SE/cursor_move.wav", false},
	{"data/SE/cursor_yes.wav", false},
	{"data/SE/title_start.wav", false},
	{"data/SE/time_end.wav", false},
	{"data/SE/use_iceblock.wav", false},
	{"data/SE/iceblock_drop.wav", false},
	{"data/SE/get_iceblock.wav", false},
	{"data/SE/opening.wav", false},
	{"data/SE/time_warning.wav", false},
	{"data/SE/win.wav", false},
	{"data/SE/gameover.wav", false},
	{"data/SE/retire.wav", false},
	{"data/SE/draw.wav", false}

	
};

//=============================================================================
// ������
//=============================================================================
HRESULT InitSound(HWND hWnd)
{
	HRESULT hr;

	// COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&g_pXAudio2, 0);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// COM���C�u�����̏I������
		CoUninitialize();
		return E_FAIL;
	}
	
	// �}�X�^�[�{�C�X�̐���
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�}�X�^�[�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);

		if(g_pXAudio2)
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			g_pXAudio2->Release();
			g_pXAudio2 = NULL;
		}

		// COM���C�u�����̏I������
		CoUninitialize();

return E_FAIL;
	}

	// �T�E���h�f�[�^�̏�����
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// �o�b�t�@�̃N���A
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// �T�E���h�f�[�^�t�@�C���̐���
		hFile = CreateFile(g_aParam[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// �t�@�C���|�C���^��擪�Ɉړ�
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// WAVE�t�@�C���̃`�F�b�N
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		if (dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �t�H�[�}�b�g�`�F�b�N
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �I�[�f�B�I�f�[�^�ǂݍ���
		hr = CheckChunk(hFile, 'atad', &g_aSizeAudio[nCntSound], &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		g_apDataAudio[nCntSound] = (BYTE*)malloc(g_aSizeAudio[nCntSound]);
		hr = ReadChunkData(hFile, g_apDataAudio[nCntSound], g_aSizeAudio[nCntSound], dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �\�[�X�{�C�X�̐���
		hr = g_pXAudio2->CreateSourceVoice(&g_apSourceVoice[nCntSound], &(wfx.Format));
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�\�[�X�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = g_aSizeAudio[nCntSound];
		buffer.pAudioData = g_apDataAudio[nCntSound];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = 0;

	}

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSound()
{
	////�e�X�g
	//g_apSourceVoice[SOUND_LABEL_SE_TEST]->GetState(&g_xa2state);
	//PrintDebugProc("BuffersQueued[SOUND_LABEL_SE_TEST]:%d \n\n\n", g_xa2state.BuffersQueued);


	if (GetKeyboardTrigger(DIK_Z))
	{
		PlaySound(SOUND_LABEL_SE_TEST, false, true);
	}
	//if (GetKeyboardTrigger(DIK_X))
	//{
	//	StopSound(SOUND_LABEL_SE_TEST, false);
	//}
}

//=============================================================================
// �I������
//=============================================================================
void UninitSound(void)
{
	// �ꎞ��~
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound])
		{
			// �ꎞ��~
			g_apSourceVoice[nCntSound]->Stop(0);
	
			// �\�[�X�{�C�X�̔j��
			g_apSourceVoice[nCntSound]->DestroyVoice();
			g_apSourceVoice[nCntSound] = NULL;
	
			// �I�[�f�B�I�f�[�^�̊J��
			free(g_apDataAudio[nCntSound]);
			g_apDataAudio[nCntSound] = NULL;
		}
	}
	
	// �}�X�^�[�{�C�X�̔j��
	g_pMasteringVoice->DestroyVoice();
	g_pMasteringVoice = NULL;
	
	if(g_pXAudio2)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		g_pXAudio2->Release();
		g_pXAudio2 = NULL;
	}
	
	// COM���C�u�����̏I������
	CoUninitialize();
}

//=============================================================================
// ���y���Đ�
// isLoop:true ���[�v����B		false ���[�v���Ȃ��@
// isEncore:true �Đ����Ă��鉹���Đ����悤�Ƃ���ꍇ�A�ŏ�����Đ��B�@	false �Đ��i�ꎞ��~�̂Ƃ��납��̍Đ����ł���j
//=============================================================================
HRESULT PlaySound(SOUND_LABEL label, bool isLoop ,bool isEncore)
{
	XAUDIO2_BUFFER buffer;

	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_aSizeAudio[label];
	buffer.pAudioData = g_apDataAudio[label];
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	if (isLoop)
	{
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	}
	else
	{
		buffer.LoopCount = XAUDIO2_NO_LOOP_REGION;
	}

	// ��Ԏ擾
	g_apSourceVoice[label]->GetState(&g_xa2state);

	if (isEncore)
	{
		if (g_xa2state.BuffersQueued != 0)						//BuffersQueued�͍Đ����̉����܂ރo�b�t�@���̉��̐�
		{//�o�b�t�@�ɉ�����ꍇ
			g_apSourceVoice[label]->Stop(0);					// �ꎞ��~

			// �I�[�f�B�I�o�b�t�@�̍폜
			//�Đ����̉��͉e���󂯂Ȃ��āA�폜����Ȃ��č���̍Đ��I���܂ŁA�Đ���������B
			//�ꎞ��~�̉��͉e���󂯂āA�폜����Ē�~�ɂȂ�B�o�b�t�@���̂܂��Đ����ĂȂ��҂����͑S���폜�����i���Ԃ�A�ꎞ��~�̉��͎�����҂����ɂȂ����j
			g_apSourceVoice[label]->FlushSourceBuffers();		//������A�ق�g_xa2state.BuffersQueued = 0	
															
		}													
	}

	if (isEncore || (g_xa2state.BuffersQueued == 0))
	{//�ŏ�����Đ�����ꍇ�A���邢�́A���̉��܂��o�^���Ă��Ȃ��ꍇ
		// �I�[�f�B�I�o�b�t�@�̓o�^
		g_apSourceVoice[label]->SubmitSourceBuffer(&buffer);	//������ABuffersQueued++		BuffersQueued�̍ő����64

	}

	// �Đ�
	g_apSourceVoice[label]->Start(0);							//BuffersQueued > 0�̎��A�����Đ��B�����I�������A BuffersQueued--�BBuffersQueued��0�ɂȂ�܂ŁA�����ƃo�b�N�O���E���h�ōĐ���������

	g_aParam[label].isSoloTempStop = false;


	return S_OK;
}

//=============================================================================
// �ꊇ�ꎞ��~���ꂽ���y���Đ�
// �ꊇ�ꎞ��~��ɁA�y�A�Ŏg��
//=============================================================================
HRESULT PlaySoundAll()
{
	for (int i = 0; i < SOUND_LABEL_MAX; i++)
	{
		// ��Ԏ擾
		g_apSourceVoice[i]->GetState(&g_xa2state);

		if (g_xa2state.BuffersQueued != 0)
		{//�ꊇ��~�̎��A�Đ����Ă鉹���ꎞ��~����鉹��
			if (g_aParam[i].isSoloTempStop == false)
			{//�Đ����Ă鉹�Ȃ�
				// �Đ�
				g_apSourceVoice[i]->Start(0);
			}
		}

	}

	return S_OK;
}

//=============================================================================
// ���y���~
// tempStop:true �ꎞ��~�@�@false ��~
//=============================================================================
void StopSound(SOUND_LABEL label, bool isTempStop)
{
	// ��Ԏ擾
	g_apSourceVoice[label]->GetState(&g_xa2state);

	if(g_xa2state.BuffersQueued != 0)								
	{// �Đ���		
		g_apSourceVoice[label]->Stop(0);						// �ꎞ��~

		g_aParam[label].isSoloTempStop = true;

		if(!isTempStop)
		{
			// �I�[�f�B�I�o�b�t�@�̍폜
			g_apSourceVoice[label]->FlushSourceBuffers();		//�ꎞ��~�̏�ɁA������g���ƁA��~�ɂȂ�

		}
	}

}

//=============================================================================
// ���ׂẲ��y���ꊇ��~
// tempStop:true �ꎞ��~�@�@false ��~
//=============================================================================
void StopSoundALL(bool isTempStop)
{
	for (int i = 0;i < SOUND_LABEL_MAX; i++)
	{
		// ��Ԏ擾
		g_apSourceVoice[i]->GetState(&g_xa2state);

		if (g_xa2state.BuffersQueued != 0)
		{		
			g_apSourceVoice[i]->Stop(0);						// �ꎞ��~

			if (!isTempStop)
			{
				// �I�[�f�B�I�o�b�t�@�̍폜
				g_apSourceVoice[i]->FlushSourceBuffers();		//�ꎞ��~�̏�ɁA������g���ƁA��~�ɂȂ�

			}
		}
	}

}

//=============================================================================
// �`�����N�̃`�F�b�N
//=============================================================================
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;
	
	if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if(dwChunkType == format)
		{
			*pChunkSize         = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if(dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}
	
	return S_OK;
}

//=============================================================================
// �`�����N�f�[�^�̓ǂݍ���
//=============================================================================
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}

