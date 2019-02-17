//=============================================================================
//
// �J�������� [camera.cpp]
// Author : ���p�j
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
// �}�N����`
//*****************************************************************************
#define	VIEW_ANGLE			(D3DXToRadian(45.0f))	// ����p
#define	VIEW_NEAR_Z			(10.0f)					// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z			(10000.0f)				// �r���[���ʂ�FarZ�l
#define	VALUE_MOVE_CAMERA	(2.0f)					// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)		// �J�����̉�]��

#define	RATE_CHASE_CAMERA_P	(0.35f)					// �J�����̎��_�ւ̕␳�W��
#define	RATE_CHASE_CAMERA_R	(0.20f)					// �J�����̒����_�ւ̕␳�W��

#define	CHASE_HEIGHT_P_NEAR		(1000.0f)				// �ǐՎ��̎��_�̍���
#define	CHASE_HEIGHT_P_FAR		(1700.0f)				// �ǐՎ��̎��_�̍���

#define	RADIUS_NEAR		(400.0f)				// ���_�ƒ����_��xoz�ʂ̋���
#define	RADIUS_FAR		(300.0f)				// ���_�ƒ����_��xoz�ʂ̋���


#define	CHASE_HEIGHT_R		(10.0f)					// �ǐՎ��̒����_�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DXVECTOR3		g_posCameraP;				// �J�����̎��_
D3DXVECTOR3		g_posCameraR;				// �J�����̒����_
D3DXVECTOR3		g_posCameraU;				// �J�����̏����

D3DXVECTOR3		g_rotCamera;				// �J�����̉�]
float			g_fLengthIntervalCamera;	// �J�����̎��_�ƒ����_�̋���
D3DXMATRIX		g_mtxView;					// �r���[�}�g���b�N�X
D3DXMATRIX		g_mtxProjection;			// �v���W�F�N�V�����}�g���b�N�X

float g_chaseHightP;// �ǐՎ��̎��_�̍���

CAMERA_MODE g_cameraMode;

PLAY_MODE g_playMode;

bool g_cutScene;//�J�b�g�V�[�����ǂ���

//=============================================================================
// �J�����̏�����
//=============================================================================
HRESULT InitCamera(void)
{
	g_cutScene = false;

	g_cameraMode = CAMERA_MODE_FAR;//�f�t�H���g�ݒ�


	if (GetCursorIdx() == 0)
	{
		g_playMode = PLAY_MODE_SINGLE;//�f�t�H���g�ݒ�

	}
	else if (GetCursorIdx() == 1)
	{
		g_playMode = PLAY_MODE_DOUBLE;//�f�t�H���g�ݒ�

	}


	if (g_cameraMode == CAMERA_MODE_NEAR)
	{
		g_chaseHightP = CHASE_HEIGHT_P_NEAR;		
	}
	else if (g_cameraMode == CAMERA_MODE_FAR)
	{
		g_chaseHightP = CHASE_HEIGHT_P_FAR;
	}

	g_posCameraP = D3DXVECTOR3(0.0f, 100.0f, - RADIUS_FAR);
	g_posCameraR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_posCameraU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	g_rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float vx,vz;
	vx = g_posCameraP.x - g_posCameraR.x;
	vz = g_posCameraP.z - g_posCameraR.z;
	g_fLengthIntervalCamera = sqrtf(vx * vx + vz * vz);//= g_posCameraP.z

	return S_OK;
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{
}

//=============================================================================
// �J�����̍X�V�����@UpdateCamera()��UpdatePlayer()�̑O�ɂ���
//=============================================================================
void UpdateCamera(void)
{
	D3DXVECTOR3 posPlayer;
	D3DXVECTOR3 rotPlayer;
	D3DXVECTOR3 movePlayer;

	// ���f���̌��݂̈ʒu�擾
	posPlayer = GetPositionPlayer();

	//�J�������[�h�ϊ�
	{
		if (GetKeyboardTrigger(DIK_LSHIFT)&&(g_playMode == PLAY_MODE_SINGLE))
		{//�V���O�����[�h�����A�J�����̐ؑ։\�ɂ���

			g_cameraMode = (CAMERA_MODE)!g_cameraMode;

		}

		if (g_cameraMode == CAMERA_MODE_NEAR)
		{
			g_chaseHightP = CHASE_HEIGHT_P_NEAR;
			g_fLengthIntervalCamera = RADIUS_NEAR;

			if (g_cutScene)
			{//�������̃J�b�g�V�[��
				g_chaseHightP = 100.0f;
				g_fLengthIntervalCamera = 200.0f;
			}

		}
		else if (g_cameraMode == CAMERA_MODE_FAR)
		{
			g_chaseHightP = CHASE_HEIGHT_P_FAR;
			g_fLengthIntervalCamera = RADIUS_FAR;
		}

	}

#ifdef _DEBUG
	if (GetKeyboardPress(DIK_Q))
	{// Y������]
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
	{// Y���E��]
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

	if (GetKeyboardPress(DIK_G))
	{//zoom
		g_fLengthIntervalCamera -= VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_H))
	{//zoom
		g_fLengthIntervalCamera += VALUE_MOVE_CAMERA;
	}


	if (GetKeyboardPress(DIK_J))
	{// �ǐՎ��̎��_�̍���
		g_chaseHightP -= VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_K))
	{// �ǐՎ��̎��_�̍���
		g_chaseHightP += VALUE_MOVE_CAMERA;
	}

#endif


	if (g_cameraMode == CAMERA_MODE_NEAR)
	{
		// ���_�̖ړI�ʒu
		g_posCameraP.x = posPlayer.x - sinf(g_rotCamera.y) * g_fLengthIntervalCamera;
		g_posCameraP.y = posPlayer.y + g_chaseHightP;
		g_posCameraP.z = posPlayer.z - cosf(g_rotCamera.y) * g_fLengthIntervalCamera;

		// �����_�̖ړI�ʒu
		g_posCameraR.x = posPlayer.x;
		g_posCameraR.y = posPlayer.y;
		g_posCameraR.z = posPlayer.z;

		if (GetWinner() == OBJECT_ENEMY)
		{
			// ���_�̖ړI�ʒu
			g_posCameraP.x = GetPositionEnemy().x - sinf(g_rotCamera.y) * g_fLengthIntervalCamera;
			g_posCameraP.y = GetPositionEnemy().y + g_chaseHightP;
			g_posCameraP.z = GetPositionEnemy().z - cosf(g_rotCamera.y) * g_fLengthIntervalCamera;

			// �����_�̖ړI�ʒu
			g_posCameraR.x = GetPositionEnemy().x;
			g_posCameraR.y = GetPositionEnemy().y;
			g_posCameraR.z = GetPositionEnemy().z;

		}

	}
	else if (g_cameraMode == CAMERA_MODE_FAR)
	{
		// ���_�̖ړI�ʒu 
		g_posCameraP.x = -sinf(g_rotCamera.y) * g_fLengthIntervalCamera; //- sinf(g_rotCamera.y)��-����]�̕��������߂�G
		g_posCameraP.y = g_chaseHightP;
		g_posCameraP.z = -cosf(g_rotCamera.y) * g_fLengthIntervalCamera;//- cosf(g_rotCamera.y)��-���ŏ��J�����̌��������߂�

		// �����_�̖ړI�ʒu
		g_posCameraR.x = 0.0f;
		g_posCameraR.y = 0.0f;
		g_posCameraR.z = 0.0f;

	}



	PrintDebugProc("\n");
	PrintDebugProc("\n");
	PrintDebugProc("\n");

	PrintDebugProc("[camera pos�F(%f : %f : %f)]\n", g_posCameraP.x,
											g_posCameraP.y, 
											g_posCameraP.z);
		
	PrintDebugProc("[camera at�F(%f : %f : %f)]\n", g_posCameraR.x,
											g_posCameraR.y, 
											g_posCameraR.z);

	PrintDebugProc("\n");

	PrintDebugProc("chaseHightP:%f\n", g_chaseHightP);

	PrintDebugProc("\n");

	PrintDebugProc("LengthIntervalCamera:%f\n", g_fLengthIntervalCamera);

	PrintDebugProc("\n");

}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_mtxView, 
						&g_posCameraP,		// �J�����̎��_
						&g_posCameraR,		// �J�����̒����_
						&g_posCameraU);		// �J�����̏����

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);


	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_mtxProjection,
								VIEW_ANGLE,										// ����p
								((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT),	// �A�X�y�N�g��
								VIEW_NEAR_Z,									// �r���[���ʂ�NearZ�l
								VIEW_FAR_Z);									// �r���[���ʂ�FarZ�l

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxProjection);
}

//=============================================================================
// �J�����̌����̎擾
//=============================================================================
D3DXVECTOR3 GetRotCamera(void)
{
	return g_rotCamera;
}

//=============================================================================
// �r���[�}�g���b�N�X�̎擾
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

CAMERA_MODE GetCameraMode()
{
	 return g_cameraMode;
}

void SetCameraMode(CAMERA_MODE val)
{
	g_cameraMode = val;
}

void SetPlayMode(PLAY_MODE val)
{
	g_playMode = val;
}

PLAY_MODE GetPlayMode()
{
	return g_playMode;
}

bool GetCutScene()
{
	return g_cutScene;
}


void WinScene()
{//�J�b�g�V�[��
	if (!g_cutScene)
	{//�������̑���ʂ͕K���J�b�g�V�[��
		SetCameraMode(CAMERA_MODE_NEAR);
		SetChaseHightP(100.0f);
		SetLengthIntervalCamera(200.0f);

		g_cutScene = true;
	}

}
