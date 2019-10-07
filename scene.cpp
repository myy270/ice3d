#include "scene.h"
//=============================================================================
//
// 画面遷移処理 [scene.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "scene.h"

#include "title.h"
#include "game.h"
#include "result.h"

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
SCENE	g_scene = SCENE_MAX;		// ゲームシーン（ゲーム画面）


void SetScene(SCENE scene)
{
	g_scene = scene;

	switch (g_scene)
	{
	case SCENE_TITLE:
		// ゲーム画面の終了処理
		UninitGame();

		// リザルト画面の終了処理
		UninitResult();

		// タイトル画面の初期化
		InitTitle();

		break;

	case SCENE_GAME:
		// タイトル画面の終了処理
		UninitTitle();

		// ゲーム画面の初期化
		InitGame();

		break;

	case SCENE_RESULT:
		// リザルト画面の初期化
		InitResult();

		break;
	}
}


//=============================================================================
// シーンの取得
//=============================================================================
SCENE GetScene(void)
{
	return g_scene;
}


