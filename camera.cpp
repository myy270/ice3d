//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "camera.h"
#include "player.h"
#include "input.h"
#include "debugproc.h"
#include "enemy.h"
#include "score.h"
#include "title.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VIEW_ANGLE				(D3DXToRadian(45.0f))	// 視野角
#define	VIEW_NEAR_Z				(10.0f)					// ビュー平面のNearZ値
#define	VIEW_FAR_Z				(10000.0f)				// ビュー平面のFarZ値

#define	VALUE_MOVE_CAMERA		(2.0f)					// カメラの移動量
#define	VALUE_ROTATE_CAMERA		(D3DX_PI * 0.01f)		// カメラの回転量

#define	CHASE_HEIGHT_NEAR		(400.0f)				// 追跡時の視点の高さ
#define	CHASE_HEIGHT_FAR		(1700.0f)				// 追跡時の視点の高さ
#define	CHASE_HEIGHT_CUTSCENE	(100.0f)				// 追跡時の視点の高さ

#define	RADIUS_NEAR				(400.0f)				// 視点と注視点のxoz面の距離
#define	RADIUS_FAR				(300.0f)				// 視点と注視点のxoz面の距離
#define	RADIUS_CUTSCENE			(200.0f)				// 視点と注視点のxoz面の距離

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

void SwitchCameraMode();
void CameraChase();
void Chase(D3DXVECTOR3 target);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DXVECTOR3		g_cameraPos;				// カメラの視点
D3DXVECTOR3		g_cameraAt;					// カメラの注視点
D3DXVECTOR3		g_cameraUp;					// カメラの上方向

D3DXVECTOR3		g_rotCamera;				// カメラの回転		.yだけ使う
float			g_fLengthIntervalCamera;	// カメラの視点と注視点のXOZ面の距離
float			g_fChaseHeight;				// 追跡時の視点の高さ

D3DXMATRIX		g_mtxView;					// ビューマトリックス
D3DXMATRIX		g_mtxProjection;			// プロジェクションマトリックス

CAMERA_MODE		g_cameraMode;

//=============================================================================
// カメラの初期化
//=============================================================================
HRESULT InitCamera(void)
{
	//初期カメラモードを設定
	if (GetPlayMode() == PLAY_MODE_SINGLE)
	{
		g_cameraMode = CAMERA_MODE_NEAR;
		g_fChaseHeight = CHASE_HEIGHT_NEAR;
		g_fLengthIntervalCamera = RADIUS_NEAR;

	}
	else if (GetPlayMode() == PLAY_MODE_DOUBLE)
	{
		g_cameraMode = CAMERA_MODE_FAR;
		g_fChaseHeight = CHASE_HEIGHT_FAR;
		g_fLengthIntervalCamera = RADIUS_FAR;
	}

	g_cameraUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//=============================================================================
// カメラの更新処理　UpdateCamera()はUpdatePlayer()の前に置く
//=============================================================================
void UpdateCamera(void)
{	
#ifdef _DEBUG
	//開発者機能	カメラを弄る
	if (GetKeyboardPress(DIK_Q))
	{// Y軸左回転
		g_rotCamera.y -= VALUE_ROTATE_CAMERA;
	}
	if (GetKeyboardPress(DIK_E))
	{// Y軸右回転
		g_rotCamera.y += VALUE_ROTATE_CAMERA;
	}

	LimitRot(g_rotCamera.y);

	if (GetKeyboardPress(DIK_G))
	{//zoom
		g_fLengthIntervalCamera -= VALUE_MOVE_CAMERA;
	}
	if (GetKeyboardPress(DIK_H))
	{//zoom
		g_fLengthIntervalCamera += VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_J))
	{// 追跡時の視点の高さ
		g_fChaseHeight -= VALUE_MOVE_CAMERA;
	}
	if (GetKeyboardPress(DIK_K))
	{// 追跡時の視点の高さ
		g_fChaseHeight += VALUE_MOVE_CAMERA;
	}
#endif

	if ((GetPlayMode() == PLAY_MODE_SINGLE) && (GetKeyboardTrigger(DIK_LSHIFT) || IsButtonTrigger(0, BUTTON_CROSS)))
	{//シングルモードの場合、遠近カメラが切換できる
		SwitchCameraMode();
	}

	//カメラモードに応じて、パラメーターを設定
	{//これを消すと、開発者機能でカメラを自由に調整できる
		if (g_cameraMode == CAMERA_MODE_NEAR)
		{
			g_fChaseHeight = CHASE_HEIGHT_NEAR;
			g_fLengthIntervalCamera = RADIUS_NEAR;
		}
		else if (g_cameraMode == CAMERA_MODE_FAR)
		{
			g_fChaseHeight = CHASE_HEIGHT_FAR;
			g_fLengthIntervalCamera = RADIUS_FAR;
		}
		else if (g_cameraMode == CAMERA_MODE_CUTSCENE)
		{//勝利時のカットシーン
			g_fChaseHeight = CHASE_HEIGHT_CUTSCENE;
			g_fLengthIntervalCamera = RADIUS_CUTSCENE;
		}
	}

}

//=============================================================================
// カメラの設定処理
// UpdatePlayer()の後に置く
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// カメラ追跡の設定
	CameraChase();							//プレイヤーの最新の位置情報を使うために、SetCamera()はUpdatePlayer()の後に置く

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_mtxView, 
						&g_cameraPos,		// カメラの視点
						&g_cameraAt,		// カメラの注視点
						&g_cameraUp);		// カメラの上方向

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_mtxProjection,
								VIEW_ANGLE,										// 視野角
								((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT),	// アスペクト比
								VIEW_NEAR_Z,									// ビュー平面のNearZ値
								VIEW_FAR_Z);									// ビュー平面のFarZ値

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxProjection);


	//デバッグ用出力情報
	PrintDebugProc("[camera pos：(%f : %f : %f)]\n", g_cameraPos.x,
		g_cameraPos.y,
		g_cameraPos.z);
	PrintDebugProc("[camera at：(%f : %f : %f)]\n", g_cameraAt.x,
		g_cameraAt.y,
		g_cameraAt.z);

	PrintDebugProc("\n");
	PrintDebugProc("[camera rot：(%f : %f : %f)]\n", g_rotCamera.x,
		g_rotCamera.y,
		g_rotCamera.z);
	PrintDebugProc("\n");
	PrintDebugProc("chaseHightP:%f\n", g_fChaseHeight);
	PrintDebugProc("\n");
	PrintDebugProc("LengthIntervalCamera:%f\n", g_fLengthIntervalCamera);
	PrintDebugProc("\n");

}

//=============================================================================
// カメラの向きの取得
// プレイヤーの向き調整用
//=============================================================================
D3DXVECTOR3 GetRotCamera(void)
{
	return g_rotCamera;
}

//=============================================================================
// ビューマトリックスの取得
// ビルボードであるeffect用
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	return g_mtxView;
}

//=============================================================================
// カメラモードをセット
//=============================================================================
void SetCameraMode(CAMERA_MODE mode)
{
	g_cameraMode = mode;
}

//=============================================================================
// カメラ遠近2モード間の切り替え
//=============================================================================
void SwitchCameraMode()
{
	if ((g_cameraMode == CAMERA_MODE_NEAR) || (g_cameraMode == CAMERA_MODE_CUTSCENE))
	{
		g_cameraMode = CAMERA_MODE_FAR;
	}
	else if (g_cameraMode == CAMERA_MODE_FAR)
	{
		g_cameraMode = CAMERA_MODE_NEAR;
	}

}

//=============================================================================
// カメラ追跡の設定
//=============================================================================
void CameraChase()
{
	if (GetPlayMode() == PLAY_MODE_SINGLE)
	{
		if ((g_cameraMode == CAMERA_MODE_NEAR) || (g_cameraMode == CAMERA_MODE_CUTSCENE))
		{
			Chase(GetPositionPlayer());				//プレイヤーを追跡する
		}
		else if (g_cameraMode == CAMERA_MODE_FAR)
		{
			Chase(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	//(0.0f, 0.0f, 0.0f)を注視点にする
		}
	}
	else if (GetPlayMode() == PLAY_MODE_DOUBLE)
	{
		if (g_cameraMode == CAMERA_MODE_CUTSCENE)
		{
			if (GetWinner() == OBJECT_PLAYER)
			{
				Chase(GetPositionPlayer());			//プレイヤーを注視点にする
			}
			else if (GetWinner() == OBJECT_ENEMY)
			{
				Chase(GetPositionEnemy());			//エネミーを注視点にする
			}
		}
		else if (g_cameraMode == CAMERA_MODE_FAR)
		{
			Chase(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	//(0.0f, 0.0f, 0.0f)を注視点にする
		}
	}

}

//=============================================================================
// カメラは、あるポイントを追跡する
// データをカメラの変数に反映する
//=============================================================================
void Chase(D3DXVECTOR3 target)
{
	// 視点の位置
	g_cameraPos.x = target.x - sinf(g_rotCamera.y) * g_fLengthIntervalCamera;	//- sinf(g_rotCamera.y)の-が回転の方向を決める
	g_cameraPos.y = target.y + g_fChaseHeight;
	g_cameraPos.z = target.z - cosf(g_rotCamera.y) * g_fLengthIntervalCamera;	//- cosf(g_rotCamera.y)の-が最初カメラの向きを決める

	// 注視点の位置
	g_cameraAt = target;

}