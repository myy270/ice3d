//=============================================================================
//
// サウンド処理 [sound.cpp]
// Author : 麦英泳
//
//=============================================================================
#include <xaudio2.h>			// DXサウンド関連のライブラリー

#include "sound.h"
#include "debugproc.h"
#include "input.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

//*****************************************************************************
// グローバル変数
//*****************************************************************************

IXAudio2				*g_pXAudio2 = NULL;							// XAudio2オブジェクトへのインターフェイス
IXAudio2MasteringVoice	*g_pMasteringVoice = NULL;					// マスターボイス
IXAudio2SourceVoice		*g_apSourceVoice[SOUND_LABEL_MAX] = {};		// ソースボイス
BYTE					*g_apDataAudio[SOUND_LABEL_MAX] = {};		// オーディオデータ
DWORD					g_aSizeAudio[SOUND_LABEL_MAX] = {};			// オーディオデータサイズ

XAUDIO2_VOICE_STATE		g_xa2state;

// 各音素材のパラメータ		enum SOUND_LABEL と合わせて並ぶ
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
// 初期化
//=============================================================================
HRESULT InitSound(HWND hWnd)
{
	HRESULT hr;

	// COMライブラリの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2オブジェクトの作成
	hr = XAudio2Create(&g_pXAudio2, 0);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2オブジェクトの作成に失敗！", "警告！", MB_ICONWARNING);

		// COMライブラリの終了処理
		CoUninitialize();
		return E_FAIL;
	}
	
	// マスターボイスの生成
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "マスターボイスの生成に失敗！", "警告！", MB_ICONWARNING);

		if(g_pXAudio2)
		{
			// XAudio2オブジェクトの開放
			g_pXAudio2->Release();
			g_pXAudio2 = NULL;
		}

		// COMライブラリの終了処理
		CoUninitialize();

return E_FAIL;
	}

	// サウンドデータの初期化
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// バッファのクリア
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// サウンドデータファイルの生成
		hFile = CreateFile(g_aParam[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(1)", "警告！", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// ファイルポインタを先頭に移動
			MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(2)", "警告！", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// WAVEファイルのチェック
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		if (dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(3)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// フォーマットチェック
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "フォーマットチェックに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "フォーマットチェックに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// オーディオデータ読み込み
		hr = CheckChunk(hFile, 'atad', &g_aSizeAudio[nCntSound], &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		g_apDataAudio[nCntSound] = (BYTE*)malloc(g_aSizeAudio[nCntSound]);
		hr = ReadChunkData(hFile, g_apDataAudio[nCntSound], g_aSizeAudio[nCntSound], dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// ソースボイスの生成
		hr = g_pXAudio2->CreateSourceVoice(&g_apSourceVoice[nCntSound], &(wfx.Format));
		if (FAILED(hr))
		{
			MessageBox(hWnd, "ソースボイスの生成に失敗！", "警告！", MB_ICONWARNING);
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
// 更新処理
//=============================================================================
void UpdateSound()
{
	////テスト
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
// 終了処理
//=============================================================================
void UninitSound(void)
{
	// 一時停止
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound])
		{
			// 一時停止
			g_apSourceVoice[nCntSound]->Stop(0);
	
			// ソースボイスの破棄
			g_apSourceVoice[nCntSound]->DestroyVoice();
			g_apSourceVoice[nCntSound] = NULL;
	
			// オーディオデータの開放
			free(g_apDataAudio[nCntSound]);
			g_apDataAudio[nCntSound] = NULL;
		}
	}
	
	// マスターボイスの破棄
	g_pMasteringVoice->DestroyVoice();
	g_pMasteringVoice = NULL;
	
	if(g_pXAudio2)
	{
		// XAudio2オブジェクトの開放
		g_pXAudio2->Release();
		g_pXAudio2 = NULL;
	}
	
	// COMライブラリの終了処理
	CoUninitialize();
}

//=============================================================================
// 音楽を再生
// isLoop:true ループする。		false ループしない　
// isEncore:true 再生している音を再生しようとする場合、最初から再生。　	false 再生（一時停止のところからの再生もできる）
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

	// 状態取得
	g_apSourceVoice[label]->GetState(&g_xa2state);

	if (isEncore)
	{
		if (g_xa2state.BuffersQueued != 0)						//BuffersQueuedは再生中の音を含むバッファ中の音の数
		{//バッファに音ある場合
			g_apSourceVoice[label]->Stop(0);					// 一時停止

			// オーディオバッファの削除
			//再生中の音は影響受けなくて、削除されなくて今回の再生終わるまで、再生し続ける。
			//一時停止の音は影響受けて、削除されて停止になる。バッファ中のまだ再生してない待ち音は全部削除される（たぶん、一時停止の音は実質上待ち音になった）
			g_apSourceVoice[label]->FlushSourceBuffers();		//実質上、ほぼg_xa2state.BuffersQueued = 0	
															
		}													
	}

	if (isEncore || (g_xa2state.BuffersQueued == 0))
	{//最初から再生する場合、あるいは、この音まだ登録していない場合
		// オーディオバッファの登録
		g_apSourceVoice[label]->SubmitSourceBuffer(&buffer);	//実質上、BuffersQueued++		BuffersQueuedの最大限は64

	}

	// 再生
	g_apSourceVoice[label]->Start(0);							//BuffersQueued > 0の時、音を再生。音が終わったら、 BuffersQueued--。BuffersQueuedが0になるまで、ずっとバックグラウンドで再生し続ける

	g_aParam[label].isSoloTempStop = false;


	return S_OK;
}

//=============================================================================
// 一括一時停止された音楽を再生
// 一括一時停止後に、ペアで使う
//=============================================================================
HRESULT PlaySoundAll()
{
	for (int i = 0; i < SOUND_LABEL_MAX; i++)
	{
		// 状態取得
		g_apSourceVoice[i]->GetState(&g_xa2state);

		if (g_xa2state.BuffersQueued != 0)
		{//一括停止の時、再生してる音か一時停止される音か
			if (g_aParam[i].isSoloTempStop == false)
			{//再生してる音なら
				// 再生
				g_apSourceVoice[i]->Start(0);
			}
		}

	}

	return S_OK;
}

//=============================================================================
// 音楽を停止
// tempStop:true 一時停止　　false 停止
//=============================================================================
void StopSound(SOUND_LABEL label, bool isTempStop)
{
	// 状態取得
	g_apSourceVoice[label]->GetState(&g_xa2state);

	if(g_xa2state.BuffersQueued != 0)								
	{// 再生中		
		g_apSourceVoice[label]->Stop(0);						// 一時停止

		g_aParam[label].isSoloTempStop = true;

		if(!isTempStop)
		{
			// オーディオバッファの削除
			g_apSourceVoice[label]->FlushSourceBuffers();		//一時停止の上に、これを使うと、停止になる

		}
	}

}

//=============================================================================
// すべての音楽を一括停止
// tempStop:true 一時停止　　false 停止
//=============================================================================
void StopSoundALL(bool isTempStop)
{
	for (int i = 0;i < SOUND_LABEL_MAX; i++)
	{
		// 状態取得
		g_apSourceVoice[i]->GetState(&g_xa2state);

		if (g_xa2state.BuffersQueued != 0)
		{		
			g_apSourceVoice[i]->Stop(0);						// 一時停止

			if (!isTempStop)
			{
				// オーディオバッファの削除
				g_apSourceVoice[i]->FlushSourceBuffers();		//一時停止の上に、これを使うと、停止になる

			}
		}
	}

}

//=============================================================================
// チャンクのチェック
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
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
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
// チャンクデータの読み込み
//=============================================================================
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}

