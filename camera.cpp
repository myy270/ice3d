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

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VIEW_ANGLE			(D3DXToRadian(45.0f))	// ����p
#define	VIEW_NEAR_Z			(10.0f)					// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z			(10000.0f)				// �r���[���ʂ�FarZ�l
#define	VALUE_MOVE_CAMERA	(2.0f)					// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)		// �J�����̉�]��

#define	INTERVAL_CAMERA_R	(0.0f)					// ���f���̎����̐�܂ł̋���(�v���C���[�ƒ����_�̋���) �J�����u���̌����̈��
#define	RATE_CHASE_CAMERA_P	(0.35f)					// �J�����̎��_�ւ̕␳�W��
#define	RATE_CHASE_CAMERA_R	(0.20f)					// �J�����̒����_�ւ̕␳�W��

#define	CHASE_HEIGHT_P		(1900.0f)				// �ǐՎ��̎��_�̍���
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
D3DXVECTOR3		g_posCameraPDest;			// �J�����̎��_�̖ړI�ʒu�i�\�z����ʒu�j
D3DXVECTOR3		g_posCameraRDest;			// �J�����̒����_�̖ړI�ʒu
D3DXVECTOR3		g_rotCamera;				// �J�����̉�]
float			g_fLengthIntervalCamera;	// �J�����̎��_�ƒ����_�̋���
float			g_fLengthIntervalPlayer;	// �v���C���[�ƒ����_�̋���
D3DXMATRIX		g_mtxView;					// �r���[�}�g���b�N�X
D3DXMATRIX		g_mtxProjection;			// �v���W�F�N�V�����}�g���b�N�X

float g_chaseHightP;// �ǐՎ��̎��_�̍���

float fov;
//=============================================================================
// �J�����̏�����
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
	float fLength;

	// ���f���̌��݂̈ʒu�擾
	posPlayer = GetPositionPlayer();

	// ���f���̌��݂̌����擾
	rotPlayer = GetRotationPlayer();

	// ���f���̑O��̈ړ��ʎ擾
	movePlayer = GetMovePlayer();

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


	// ���_�̖ړI�ʒu
	//�O��A�v���C���[�ړ��̋���
	fLength = sqrtf(movePlayer.x * movePlayer.x + movePlayer.z * movePlayer.z) * 6.0f;//
	
	//posPlayer�̓����͂����ƃv���C���[�ɒǂ�������
    //- sinf(g_rotCamera.y)��-����]�̕��������߂�G - sin(rotPlayer.y) * fLength�͉^�����鎞�A���炩���߈ʒu���J����i�s��p�Ȃ����j
	g_posCameraPDest.x = posPlayer.x - sinf(g_rotCamera.y) * g_fLengthIntervalCamera - sinf(rotPlayer.y) * fLength;//���́Asin(rotPlayer.y) * fLength = movePlayer.x  * 6.0f
	g_posCameraPDest.y = posPlayer.y + g_chaseHightP;
	//- cosf(g_rotCamera.y)��-���ŏ��̃J�������_�����߂�
	g_posCameraPDest.z = posPlayer.z - cosf(g_rotCamera.y) * g_fLengthIntervalCamera - cosf(rotPlayer.y) * fLength;

	// �����_�̖ړI�ʒu�@g_fLengthIntervalPlayer�̈Ӗ��́A��s�@�����̈�苗���ɒ����_��ݒu����
	fLength = g_fLengthIntervalPlayer + sqrtf(movePlayer.x * movePlayer.x + movePlayer.z * movePlayer.z) * 6.0f;
	g_posCameraRDest.x = posPlayer.x - sinf(rotPlayer.y) * fLength;
	g_posCameraRDest.y = posPlayer.y - CHASE_HEIGHT_R;
	g_posCameraRDest.z = posPlayer.z - cosf(rotPlayer.y) * fLength;

	// ���_�̕␳�@���炩���ߊJ����ʒu��␳����
	g_posCameraP.x += (g_posCameraPDest.x - g_posCameraP.x) * RATE_CHASE_CAMERA_P;
	g_posCameraP.y = g_posCameraPDest.y;
	g_posCameraP.z += (g_posCameraPDest.z - g_posCameraP.z) * RATE_CHASE_CAMERA_P;

	// �����_�̕␳
	g_posCameraR.x += (g_posCameraRDest.x - g_posCameraR.x) * RATE_CHASE_CAMERA_R;
	g_posCameraR.y += (g_posCameraRDest.y - g_posCameraR.y) * RATE_CHASE_CAMERA_R;
	g_posCameraR.z += (g_posCameraRDest.z - g_posCameraR.z) * RATE_CHASE_CAMERA_R;




	PrintDebugProc("\n");
	PrintDebugProc("\n");
	PrintDebugProc("\n");
	/*PrintDebugProc("fov:%f\n", VIEW_ANGLE + fov);*/

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

	PrintDebugProc("LengthIntervalPlayer:%f\n", g_fLengthIntervalPlayer);

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
