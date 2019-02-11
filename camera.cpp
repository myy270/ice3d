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

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VIEW_ANGLE			(D3DXToRadian(45.0f))	// 視野角
#define	VIEW_NEAR_Z			(10.0f)					// ビュー平面のNearZ値
#define	VIEW_FAR_Z			(10000.0f)				// ビュー平面のFarZ値
#define	VALUE_MOVE_CAMERA	(2.0f)					// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)		// カメラの回転量

#define	INTERVAL_CAMERA_R	(0.0f)					// モデルの視線の先までの距離(プレイヤーと注視点の距離) カメラブレの原因の一つ
#define	RATE_CHASE_CAMERA_P	(0.35f)					// カメラの視点への補正係数
#define	RATE_CHASE_CAMERA_R	(0.20f)					// カメラの注視点への補正係数

#define	CHASE_HEIGHT_P		(1900.0f)				// 追跡時の視点の高さ
#define	CHASE_HEIGHT_R		(10.0f)					// 追跡時の注視点の高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DXVECTOR3		g_posCameraP;				// カメラの視点
D3DXVECTOR3		g_posCameraR;				// カメラの注視点
D3DXVECTOR3		g_posCameraU;				// カメラの上方向
D3DXVECTOR3		g_posCameraPDest;			// カメラの視点の目的位置（予想する位置）
D3DXVECTOR3		g_posCameraRDest;			// カメラの注視点の目的位置
D3DXVECTOR3		g_rotCamera;				// カメラの回転
float			g_fLengthIntervalCamera;	// カメラの視点と注視点の距離
float			g_fLengthIntervalPlayer;	// プレイヤーと注視点の距離
D3DXMATRIX		g_mtxView;					// ビューマトリックス
D3DXMATRIX		g_mtxProjection;			// プロジェクションマトリックス

float g_chaseHightP;// 追跡時の視点の高さ

float fov;
//=============================================================================
// カメラの初期化
//=============================================================================
HRESULT InitCamera(void)
{
	g_chaseHightP = CHASE_HEIGHT_P;
	g_posCameraP = D3DXVECTOR3(0.0f, 100.0f, -300.0f);
	g_posCameraR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_posCameraU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_posCameraPDest = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
	g_posCameraRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float vx,vz;
	vx = g_posCameraP.x - g_posCameraR.x;
	vz = g_posCameraP.z - g_posCameraR.z;
	g_fLengthIntervalCamera = sqrtf(vx * vx + vz * vz);//= g_posCameraP.z
	g_fLengthIntervalPlayer = INTERVAL_CAMERA_R;

	return S_OK;
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void UninitCamera(void)
{
}

//=============================================================================
// カメラの更新処理　UpdateCamera()がUpdatePlayer()の前にある
//=============================================================================
void UpdateCamera(void)
{
	D3DXVECTOR3 posPlayer;
	D3DXVECTOR3 rotPlayer;
	D3DXVECTOR3 movePlayer;
	float fLength;

	// モデルの現在の位置取得
	posPlayer = GetPositionPlayer();

	// モデルの現在の向き取得
	rotPlayer = GetRotationPlayer();

	// モデルの前回の移動量取得
	movePlayer = GetMovePlayer();

#ifdef _DEBUG
	if (GetKeyboardPress(DIK_Q))
	{// Y軸左回転
		g_rotCamera.y -= VALUE_ROTATE_CAMERA;
		if (g_rotCamera.y > D3DX_PI)
		{
			g_rotCamera.y -= D3DX_PI * 2.0f;
		}
		if (g_rotCamera.y < -D3DX_PI)
		{
			g_rotCamera.y += D3DX_PI * 2.0f;
		}
	}

	if (GetKeyboardPress(DIK_E))
	{// Y軸右回転
		g_rotCamera.y += VALUE_ROTATE_CAMERA;
		if (g_rotCamera.y > D3DX_PI)
		{
			g_rotCamera.y -= D3DX_PI * 2.0f;
		}
		if (g_rotCamera.y < -D3DX_PI)
		{
			g_rotCamera.y += D3DX_PI * 2.0f;
		}
	}

	if (GetKeyboardPress(DIK_R))
	{//zoom
		g_fLengthIntervalCamera -= VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_F))
	{//zoom
		g_fLengthIntervalCamera += VALUE_MOVE_CAMERA;
	}

	/*if (GetKeyboardTrigger(DIK_O))
	{
		fov += 0.01f;
	}

	if (GetKeyboardTrigger(DIK_P))
	{
		fov -= 0.01f;
	}*/

	if (GetKeyboardPress(DIK_G))
	{
		g_chaseHightP -= VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_H))
	{
		g_chaseHightP += VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_J))
	{
		g_fLengthIntervalCamera -= VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_K))
	{
		g_fLengthIntervalCamera += VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_L))
	{
		g_fLengthIntervalPlayer -= VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_SEMICOLON))
	{
		g_fLengthIntervalPlayer += VALUE_MOVE_CAMERA;
	}
#endif


	// 視点の目的位置
	//前回、プレイヤー移動の距離
	fLength = sqrtf(movePlayer.x * movePlayer.x + movePlayer.z * movePlayer.z) * 6.0f;//
	
	//posPlayerの導入はずっとプレイヤーに追いかける
    //- sinf(g_rotCamera.y)の-が回転の方向を決める； - sin(rotPlayer.y) * fLengthは運動する時、あらかじめ位置を開ける（不器用なやり方）
	g_posCameraPDest.x = posPlayer.x - sinf(g_rotCamera.y) * g_fLengthIntervalCamera - sinf(rotPlayer.y) * fLength;//実は、sin(rotPlayer.y) * fLength = movePlayer.x  * 6.0f
	g_posCameraPDest.y = posPlayer.y + g_chaseHightP;
	//- cosf(g_rotCamera.y)の-が最初のカメラ視点を決める
	g_posCameraPDest.z = posPlayer.z - cosf(g_rotCamera.y) * g_fLengthIntervalCamera - cosf(rotPlayer.y) * fLength;

	// 注視点の目的位置　g_fLengthIntervalPlayerの意味は、飛行機向きの一定距離に注視点を設置する
	fLength = g_fLengthIntervalPlayer + sqrtf(movePlayer.x * movePlayer.x + movePlayer.z * movePlayer.z) * 6.0f;
	g_posCameraRDest.x = posPlayer.x - sinf(rotPlayer.y) * fLength;
	g_posCameraRDest.y = posPlayer.y - CHASE_HEIGHT_R;
	g_posCameraRDest.z = posPlayer.z - cosf(rotPlayer.y) * fLength;

	// 視点の補正　あらかじめ開ける位置を補正する
	g_posCameraP.x += (g_posCameraPDest.x - g_posCameraP.x) * RATE_CHASE_CAMERA_P;
	g_posCameraP.y = g_posCameraPDest.y;
	g_posCameraP.z += (g_posCameraPDest.z - g_posCameraP.z) * RATE_CHASE_CAMERA_P;

	// 注視点の補正
	g_posCameraR.x += (g_posCameraRDest.x - g_posCameraR.x) * RATE_CHASE_CAMERA_R;
	g_posCameraR.y += (g_posCameraRDest.y - g_posCameraR.y) * RATE_CHASE_CAMERA_R;
	g_posCameraR.z += (g_posCameraRDest.z - g_posCameraR.z) * RATE_CHASE_CAMERA_R;




	PrintDebugProc("\n");
	PrintDebugProc("\n");
	PrintDebugProc("\n");
	/*PrintDebugProc("fov:%f\n", VIEW_ANGLE + fov);*/

	PrintDebugProc("[camera pos：(%f : %f : %f)]\n", g_posCameraP.x,
											g_posCameraP.y, 
											g_posCameraP.z);
	
	PrintDebugProc("[camera at：(%f : %f : %f)]\n", g_posCameraR.x,
											g_posCameraR.y, 
											g_posCameraR.z);

	PrintDebugProc("\n");

	PrintDebugProc("chaseHightP:%f\n", g_chaseHightP);

	PrintDebugProc("\n");

	PrintDebugProc("LengthIntervalCamera:%f\n", g_fLengthIntervalCamera);

	PrintDebugProc("\n");

	PrintDebugProc("LengthIntervalPlayer:%f\n", g_fLengthIntervalPlayer);

	PrintDebugProc("\n");
}

//=============================================================================
// カメラの設定処理
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_mtxView, 
						&g_posCameraP,		// カメラの視点
						&g_posCameraR,		// カメラの注視点
						&g_posCameraU);		// カメラの上方向

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
}

//=============================================================================
// カメラの向きの取得
//=============================================================================
D3DXVECTOR3 GetRotCamera(void)
{
	return g_rotCamera;
}

//=============================================================================
// ビューマトリックスの取得
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	return g_mtxView;
}


void SetChaseHightP(float hight)
{
	g_chaseHightP = hight;
}

void SetLengthIntervalCamera(float length)
{
	g_fLengthIntervalCamera = length;
}
