//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 麦英泳
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "function.h"

//*****************************************************************************
// 列挙型定義
//*****************************************************************************

// g_aParam[SOUND_LABEL_MAX]のパスと対応して並ぶ
enum SOUND_LABEL
{
	SOUND_LABEL_BGM000,				// BGM
	SOUND_LABEL_SE_COIN,			// コインを拾う効果音
	SOUND_LABEL_SE_TEST,			// テスト音
	SOUND_LABEL_SE_PAUSE,			// ポーズ音
	SOUND_LABEL_SE_CURORMOVE,		// カーソルの移動音
	SOUND_LABEL_SE_CURORYES,		// カーソルの決定音
	SOUND_LABEL_SE_TITLESTART,		// タイトル画面にスタートボタンを押した音
	SOUND_LABEL_SE_TIMEEND,			// タイマー終わった音
	SOUND_LABEL_SE_USEICEBLOCK,		// 凍結アイテムを使う音
	SOUND_LABEL_SE_ICEBLOCKDROP,	// 凍結アイテムが落下する音
	SOUND_LABEL_SE_GETICEBLOCK,		// 凍結アイテムを拾う効果音
	SOUND_LABEL_SE_OPENING,			// オープニング音
	SOUND_LABEL_SE_TIMEWARNING,		// タイムウォーニング音
	SOUND_LABEL_SE_WIN,				// 勝利音
	SOUND_LABEL_SE_GAMEOVER,		// ゲームオーバー音
	SOUND_LABEL_SE_RETIRE,			// タイトル画面に戻る音 
	SOUND_LABEL_SE_DRAW,			// 引き分けの音 

	SOUND_LABEL_MAX,

};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

HRESULT InitSound(HWND hWnd);
void UpdateSound();
void UninitSound(void);

HRESULT PlaySound(SOUND_LABEL label, bool isLoop, bool isEncore = true);
void StopSound(SOUND_LABEL label, bool isTempStop = true);

void StopSoundALL(bool isTempStop = true);
HRESULT PlaySoundAll();

#endif
