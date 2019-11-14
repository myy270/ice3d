//=============================================================================
//
// ゲーム画面処理 [game.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "game.h"
#include "light.h"
#include "camera.h"
#include "meshfield.h"
#include "meshwall.h"
#include "player.h"
#include "enemy.h"
#include "shadow.h"
#include "effect.h"
#include "timer.h"
#include "score.h"
#include "item.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGame(void)
{
	// ライトの初期化
	InitLight();

	// カメラの初期化
	InitCamera();

	InitMeshField();

	InitMeshWall();

	// 影の初期化
	InitShadow();

	// プレイヤーの初期化
	InitPlayer();

	InitEnemy();

	// エフェクトの初期化
	InitEffect();

	// タイマーの初期化
	InitTimer();		//デフォルト50

	// スコアの初期化
	InitScore();

	// アイテムの初期化
	InitItem();
	for(int nCntCoin = 0; nCntCoin < 99; nCntCoin++)
	{
		float fPosX, fPosY, fPosZ;

		fPosX = (float)(rand() % 12000) / 10.0f - 600.0f;//-600.0f~600.0f
		//fPosY = (float)(rand() % 1400) / 10.0f + 10.0f;//10.0f~150.0f
		fPosY = 15.0f;
		fPosZ = (float)(rand() % 12000) / 10.0f - 600.0f;
		SetItem(D3DXVECTOR3(fPosX, fPosY, fPosZ),  D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_COIN, true);
	}

	// BGM再生 ちゃんとloopできるにする!　元の罠
	//PlaySound(SOUND_LABEL_BGM000, XAUDIO2_LOOP_INFINITE);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	// カメラの終了処理
	UninitCamera();

	// 地面の終了処理
	UninitMeshField();

	// 壁の終了処理
	UninitMeshWall();

	// 影の終了処理
	UninitShadow();

	// プレイヤーの終了処理
	UninitPlayer();

	UninitEnemy();

	// エフェトの終了処理
	UninitEffect();

	// タイマーの終了処理
	UninitTimer();

	// スコアの終了処理
	UninitScore();

	// アイテムの終了処理
	UninitItem();

	// BGM停止 !!元の罠
	StopSound(SOUND_LABEL_BGM000);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
	// カメラ処理の更新
	UpdateCamera();

	// 地面処理の更新
	UpdateMeshField();

	// 壁処理の更新
	UpdateMeshWall();

	// 影処理の更新
	UpdateShadow();

	// プレイヤー処理の更新
	UpdatePlayer();

	UpdateEnemy();

	// エフェクト処理の更新
	UpdateEffect();

	// タイマー処理の更新
	UpdateTimer();

	// スコア処理の更新
	UpdateScore();

	// アイテム処理の更新
	UpdateItem();


}

//=============================================================================
// 描画処理 描画順注意
//=============================================================================
void DrawGame(void)
{
	// カメラの設定
	SetCamera();

	// 地面処理の描画
	DrawMeshField();

	// 影処理の描画
	DrawShadow();

	// プレイヤー処理の描画
	DrawPlayer();

	DrawEnemy();

	// アイテム処理の描画
	DrawItem();

	// エフェクト処理の描画
	DrawEffect();

	// 壁処理の描画
	DrawMeshWall();

	// タイマー処理の描画
	DrawTimer();

	// スコア処理の描画
	DrawScore();
}

