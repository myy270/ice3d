//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 麦英泳
//
//=============================================================================

#include "player.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "effect.h"
#include "item.h"
#include "score.h"
#include "sound.h"
#include "debugproc.h"
#include "timer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	BODY_PLAYER		"data/MODEL/bearBody.x"			// 読み込むモデル名
#define	HEAD_PLAYER		"data/MODEL/bearHead.x"			// 読み込むモデル名
#define	HAND_PLAYER		"data/MODEL/bearHand.x"			// 読み込むモデル名
#define	LEG_PLAYER		"data/MODEL/bearLeg.x"			// 読み込むモデル名
#define	ICE_BLOCK		"data/MODEL/iceBlock.x"			// 読み込むモデル名

#define	PLAYER_RADIUS		(15.0f)						// 半径		//煙のエフェクトの位置や、アイテムとの当たる距離 と関係ある

#define	VALUE_MOVE_PLAYER	(0.195f)					// 移動量
#define	RATE_MOVE_PLAYER	(0.025f)					// 移動抵抗力の係数		※小さければ小さいほど、滑りやすい

#define	VALUE_ROTATE_PLAYER	(D3DX_PI * 0.025f)			// 回転量	4.5度相当
#define	RATE_ROTATE_PLAYER	(0.10f)						// 回転速度係数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

void Movement();
void AreaCollision();
void Drag();
void Shadow();
void Jet();
void ItemCollision();
void UseIceblock();
void Frozen();
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer;		// テクスチャ読み込み場所
PLAYER				g_player;					// プレイヤー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_player.motion.motionData = GetMotionWalk();
	g_player.motion.numKey = 4;
	g_player.motion.use = false;
	g_player.motion.motionTime = 0.0f;
	g_player.motion.cancelTime = 0.0f;


	g_player.part[0].partFile = (char *)BODY_PLAYER;		//体　//根である親は一番先にしなければならない
	g_player.part[1].partFile = (char *)HEAD_PLAYER;		//頭
	g_player.part[2].partFile = (char *)HAND_PLAYER;		//左手
	g_player.part[3].partFile = (char *)HAND_PLAYER;		//右手
	g_player.part[4].partFile = (char *)LEG_PLAYER;			//左足
	g_player.part[5].partFile = (char *)LEG_PLAYER;			//右足
	g_player.part[6].partFile = (char *)ICE_BLOCK;			//氷

	//パーツの情報の設定
	for (int i = 0; i < PART_MAX_PLAYER; i++)				//パーツ番号
	{
		// Xファイルの読み込み
		if(FAILED(D3DXLoadMeshFromX(g_player.part[i].partFile,
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_player.part[i].pMatBuff,
									NULL,
									&g_player.part[i].nNumMat,
									&g_player.part[i].pMesh)))
		{
			return E_FAIL;
		}

		switch (i)
		{
		case 0:
		{//体
			g_player.part[i].srt.scl = D3DXVECTOR3(1.5f, 1.5f, 1.5f);			//スケールのxyz必ず同じように
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(0.0f, 22.4f, 0.0f);			//足が地面に触れるように調整する

			g_player.part[i].parent = NULL;										//体の親はNULLにする
			break;
		}
		case 1:
		{//頭
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(0.0f, 6.5f, 0.0f);			//関節の位置に移動する

			g_player.part[i].parent = &g_player.part[0];						//体を親にする
			break;
		}
		case 2:
		{//左手
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(5.0f, 5.0f, 0.0f);			//関節の位置に移動する

			g_player.part[i].parent = &g_player.part[0];						//体を親にする
			break;
		}
		case 3:
		{//右手
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(-5.0f, 5.0f, 0.0f);			//関節の位置に移動する

			g_player.part[i].parent = &g_player.part[0];						//体を親にする
			break;
		}
		case 4:
		{//左足
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(3.064f, -4.873f, -0.409f);	//関節の位置に移動する

			g_player.part[i].parent = &g_player.part[0];						//体を親にする
			break;
		}
		case 5:
		{//右足
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(-3.064f, -4.873f, -0.409f);	//関節の位置に移動する

			g_player.part[i].parent = &g_player.part[0];						//体を親にする
			break;
		}
		default:
		{//アイスブロック
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			g_player.part[i].parent = &g_player.part[0];						//体を親にする
			break;
		}

		}//switch end

		if (i == 6)
		{//アイスブロックは最初表示しない
			g_player.part[i].use = false;
		}
		else
		{
			g_player.part[i].use = true;			
		}
	}

	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.fRadius = PLAYER_RADIUS;

	// 影を設定 ※体(part[0])を基準に
	g_player.nIdxShadow = SetShadow(g_player.part[0].srt.pos, g_player.fRadius * 2.0f, g_player.fRadius * 2.0f);	//影の大きさが変わらない

	g_player.holdItem = ITEMTYPE_COIN;
	g_player.state = NORMAL;
	g_player.frozenTime = 0;

#if 0	//テクスチャ―無し
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_PLAYER,			// ファイルの名前
								&g_pD3DTexturePlayer);	// 読み込むメモリー
#endif

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	for (int i = 0; i < PART_MAX_PLAYER; i++)	//i:パーツ番号
	{
		SAFE_RELEASE(g_player.part[i].pMesh);
		SAFE_RELEASE(g_player.part[i].pMatBuff);	
	}

	SAFE_RELEASE(g_pD3DTexturePlayer);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	Movement();

	//歩くモーション処理
	Motion(g_player, g_player.motion);

	AreaCollision();

	Drag();

	Shadow();

	Jet();
	
	ItemCollision();

	UseIceblock();

	Frozen();

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

	DrawPart(pDevice, g_player, g_pD3DTexturePlayer, PART_MAX_PLAYER);

}

//=============================================================================
// プレイヤーを取得
//=============================================================================
PLAYER *GetPlayer(void)
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

//=============================================================================
//位置と向きの更新処理
//=============================================================================
void Movement()
{
	D3DXVECTOR3 rotCamera;		//カメラの向き
	float fDiffRotY;			//目的の角度までの差分

	// カメラの向き取得
	rotCamera = GetRotCamera();

	//運動状態をリセット
	g_player.motion.use = false;

	//時間が終わっていない、かつ凍結状態ではない場合、移動できる状態になる
	if ((IsTimeEnd() == false) && (g_player.state != FROZEN))
	{//移動			※前フレームの運動量が残っているから、慣性ある
		if (GetKeyboardPress(DIK_A) || IsButtonPress(0, BUTTON_LEFT) || IsButtonPress(0, BUTTON_LSTICK_LEFT))
		{
			g_player.motion.use = true;//動く状態にする

			if (GetKeyboardPress(DIK_W) || IsButtonPress(0, BUTTON_UP) || IsButtonPress(0, BUTTON_LSTICK_UP))
			{// 左前移動
				g_player.move.x -= sinf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y + D3DX_PI * 0.75f;
			}
			else if (GetKeyboardPress(DIK_S) || IsButtonPress(0, BUTTON_DOWN) || IsButtonPress(0, BUTTON_LSTICK_DOWN))
			{// 左後移動
				g_player.move.x -= sinf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y + D3DX_PI * 0.25f;
			}
			else
			{// 左移動
				g_player.move.x -= sinf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y + D3DX_PI * 0.50f;
			}
		}
		else if (GetKeyboardPress(DIK_D) || IsButtonPress(0, BUTTON_RIGHT) || IsButtonPress(0, BUTTON_LSTICK_RIGHT))
		{
			g_player.motion.use = true;//動く状態にする

			if (GetKeyboardPress(DIK_W) || IsButtonPress(0, BUTTON_UP) || IsButtonPress(0, BUTTON_LSTICK_UP))
			{// 右前移動
				g_player.move.x -= sinf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y - D3DX_PI * 0.75f;
			}
			else if (GetKeyboardPress(DIK_S) || IsButtonPress(0, BUTTON_DOWN) || IsButtonPress(0, BUTTON_LSTICK_DOWN))
			{// 右後移動
				g_player.move.x -= sinf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y - D3DX_PI * 0.25f;
			}
			else
			{// 右移動
				g_player.move.x -= sinf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y - D3DX_PI * 0.50f;
			}
		}
		else if (GetKeyboardPress(DIK_W) || IsButtonPress(0, BUTTON_UP) || IsButtonPress(0, BUTTON_LSTICK_UP))
		{
			g_player.motion.use = true;//動く状態にする

			// 前移動
			g_player.move.x -= sinf(D3DX_PI + rotCamera.y) * VALUE_MOVE_PLAYER;
			g_player.move.z -= cosf(D3DX_PI + rotCamera.y) * VALUE_MOVE_PLAYER;

			g_player.rotDest.y = rotCamera.y + D3DX_PI;		// - D3DX_PIになると、逆の方向に回転する
		}
		else if (GetKeyboardPress(DIK_S) || IsButtonPress(0, BUTTON_DOWN) || IsButtonPress(0, BUTTON_LSTICK_DOWN))
		{
			g_player.motion.use = true;//動く状態にする

			// 後移動
			g_player.move.x -= sinf(rotCamera.y) * VALUE_MOVE_PLAYER;
			g_player.move.z -= cosf(rotCamera.y) * VALUE_MOVE_PLAYER;

			g_player.rotDest.y = rotCamera.y;
		}
	}

#ifdef _DEBUG		
	//開発者機能
	if (GetKeyboardPress(DIK_T))
	{// 上昇
		g_player.move.y += VALUE_MOVE_PLAYER;
	}
	else if (GetKeyboardPress(DIK_Y))
	{// 下降
		g_player.move.y -= VALUE_MOVE_PLAYER;
	}

	if (GetKeyboardPress(DIK_U))
	{// 左回転
		g_player.rotDest.y -= VALUE_ROTATE_PLAYER;
	}
	else if (GetKeyboardPress(DIK_I))
	{// 右回転
		g_player.rotDest.y += VALUE_ROTATE_PLAYER;
	}
#endif

	LimitRot(g_player.rotDest.y);									//実際はなくてもいいが、数字がめちゃくちゃになる

	// 目的の角度までの差分
	fDiffRotY = g_player.rotDest.y - g_player.part[0].srt.rot.y;	//体(part[0])を基準に

	LimitRot(fDiffRotY);											// 重要! 近い方向に回転できるように

	// 回転量を体(part[0])に反映
	g_player.part[0].srt.rot.y += fDiffRotY * RATE_ROTATE_PLAYER;	// 目的の角度まで慣性をかける　段々目的の角度に変化する

	LimitRot(g_player.part[0].srt.rot.y);							//実際はなくてもいいが、数字がめちゃくちゃになる

	/// 移動量を体(part[0])に反映
	g_player.part[0].srt.pos.x += g_player.move.x;
	g_player.part[0].srt.pos.y += g_player.move.y;
	g_player.part[0].srt.pos.z += g_player.move.z;

}

//=============================================================================
// エリアコリジョン処理
//=============================================================================
void AreaCollision()
{
	//移動範囲を設定する　※体(part[0])を基準に
	if (g_player.part[0].srt.pos.x < -630.0f)
	{
		g_player.part[0].srt.pos.x = -630.0f;
	}
	if (g_player.part[0].srt.pos.x > 630.0f)
	{
		g_player.part[0].srt.pos.x = 630.0f;
	}
	//if (g_player.part[0].srt.pos.y < 10.0f)
	//{
	//	g_player.part[0].srt.pos.y = 10.0f;
	//}
	//if (g_player.part[0].srt.pos.y > 150.0f)
	//{
	//	g_player.part[0].srt.pos.y = 150.0f;
	//}
	if (g_player.part[0].srt.pos.z > 630.0f)
	{
		g_player.part[0].srt.pos.z = 630.0f;
	}
	if (g_player.part[0].srt.pos.z < -630.0f)
	{
		g_player.part[0].srt.pos.z = -630.0f;
	}
	
}

//=============================================================================
// 移動抵抗力の処理
//=============================================================================
void Drag()
{
	// 運動エネルギーを一部損して（抵抗力のため）保存する、次のフレームに使う(慣性の仕組み)
	//※損の部分イコール次のフレームに獲得の運動エネルギーの場合、速度が最大(7.8f)になって、等速直線運動になる
	g_player.move.x = g_player.move.x * (1 - RATE_MOVE_PLAYER);
	g_player.move.y = g_player.move.y * (1 - RATE_MOVE_PLAYER);
	g_player.move.z = g_player.move.z * (1 - RATE_MOVE_PLAYER);

}

//=============================================================================
// 影の位置、大きさ、透明度の更新
//=============================================================================
void Shadow()
{//体(part[0])を基準に

	//影の位置を更新
	SetPositionShadow(g_player.nIdxShadow, D3DXVECTOR3(g_player.part[0].srt.pos.x, 0.1f, g_player.part[0].srt.pos.z));

	//高さにより、影の大きさが変化する
	float fSize = 20.0f + (g_player.part[0].srt.pos.y - 10.0f) * 0.05f;
	if (fSize < 20.0f)
	{
		fSize = 20.0f;
	}
	//影の大きさを更新
	SetVertexShadow(g_player.nIdxShadow, fSize, fSize);

	//高さにより、影の透明度が変化する
	float colA = 0.5f - (g_player.part[0].srt.pos.y - 10.0f) / 400.0f;
	if (colA < 0.0f)
	{
		colA = 0.0f;
	}
	//影の透明度を更新
	SetColorShadow(g_player.nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));

}

//=============================================================================
// 煙のエフェクト
//=============================================================================
void Jet()
{
	//移動距離が1より大きい場合、煙のエフェクトが出る
	if ((g_player.move.x * g_player.move.x
		+ g_player.move.y * g_player.move.y
		+ g_player.move.z * g_player.move.z) > 1.0f)
	{
		D3DXVECTOR3 pos;
		//体(part[0])を基準に
		pos.x = g_player.part[0].srt.pos.x + sinf(g_player.part[0].srt.rot.y) * g_player.fRadius;	//尾部の辺りに設定
		pos.y = 3.0f;
		pos.z = g_player.part[0].srt.pos.z + cosf(g_player.part[0].srt.rot.y) * g_player.fRadius;

		// エフェクトの設定
		SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.85f, 0.15f, 0.0f, 0.50f), 14.0f, 14.0f, 20);//赤
		SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.15f, 0.75f, 0.0f, 0.30f), 10.0f, 10.0f, 20);//緑
		SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.0f, 0.10f, 0.0f, 0.15f), 5.0f, 5.0f, 20);//緑
	}

}

//=============================================================================
// アイテムとの当たり判定
//=============================================================================
void ItemCollision()
{
	ITEM *pItem;

	// アイテムを取得
	pItem = GetItem();

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	{
		if (pItem->bUse == true)
		{
			float fLength;		//プレイヤーとアイテムの距離

			//バウンディングサークル BC //体(part[0])を基準に
			fLength = (g_player.part[0].srt.pos.x - pItem->pos.x) * (g_player.part[0].srt.pos.x - pItem->pos.x)
				+ (g_player.part[0].srt.pos.y - pItem->pos.y) * (g_player.part[0].srt.pos.y - pItem->pos.y)
				+ (g_player.part[0].srt.pos.z - pItem->pos.z) * (g_player.part[0].srt.pos.z - pItem->pos.z);

			if (fLength < (g_player.fRadius + pItem->fRadius) * (g_player.fRadius + pItem->fRadius))
			{//取得できる範囲内であれば
				if ((g_player.holdItem == ITEMTYPE_ICEBLOCK) && (pItem->nType == ITEMTYPE_ICEBLOCK))
				{//アイスブロックを持っている場合、他のアイスブロックは取得できない

				}
				else
				{
					if (pItem->nType == ITEMTYPE_ICEBLOCK)
					{
						g_player.holdItem = ITEMTYPE_ICEBLOCK;
					}
					else if (pItem->nType == ITEMTYPE_COIN)
					{
						// スコア加算
						ChangeScore(OBJECT_PLAYER, 100);

						// コインを拾う効果音
						//PlaySound(SOUND_LABEL_SE_COIN);
					}

					// アイテム消去
					DeleteItem(nCntItem);

				}
			}
		}
	}
}

//=============================================================================
//凍結アイテムを使う
//=============================================================================
void UseIceblock()
{	
	if ((IsTimeEnd() == 0) && (g_player.state != FROZEN))
	{
		if (GetKeyboardTrigger(DIK_SPACE) || IsButtonTrigger(0, BUTTON_CIRCLE))
		{
			Freeze(OBJECT_ENEMY);
		}
	}

}

//=============================================================================
//凍結状態になる時の処理
//=============================================================================
void Frozen()
{
	if (g_player.state == FROZEN)
	{
		if (g_player.frozenTime == 0)
		{
			g_player.state = NORMAL;		//凍結状態を解除
			g_player.part[6].use = false;	//身に纏うアイスブロックを消える
		}
		else
		{
			g_player.frozenTime--;			//凍結状態の残り時間をカウントダウン
			g_player.part[6].use = true;	//身に纏うアイスブロックを表示する

		}
	}

}
