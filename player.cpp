//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "player.h"
#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Character				g_player;					// プレイヤーのクラス

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	return g_player.Init(OBJECT_PLAYER);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	for (int i = 0; i < PART_MAX; i++)	//i:パーツ番号
	{
		SAFE_RELEASE(g_player.part[i].pMesh);
		SAFE_RELEASE(g_player.part[i].pMatBuff);	
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	g_player.AIControl();

	g_player.Movement();

	//歩くモーション処理
	Motion(g_player, g_player.motion);

	g_player.AreaCollision();

	g_player.Drag();

	g_player.Shadow();

	g_player.Jet();
	
	g_player.ItemCollision();

	g_player.UseIceblock();

	g_player.Frozen();

	PrintDebugProc("目的向き：%f \n\n", g_player.rotDest.y);
	PrintDebugProc("現在の向き：%f \n\n", g_player.part[0].srt.rot.y);
	PrintDebugProc("移動量：%f %f %f \n\n", g_player.move.x, g_player.move.y, g_player.move.z);

}									  

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DrawPart(pDevice, g_player, PART_MAX);

}

//=============================================================================
// プレイヤーを取得
//=============================================================================
Character *GetPlayer(void)
{
	return &g_player;
}

//=============================================================================
// 位置取得
//=============================================================================
D3DXVECTOR3 GetPositionPlayer(void)
{
	return g_player.part[0].srt.pos;//体(part[0])を基準に
}
