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
#define	VIEW_ANGLE				(D3DXToRadian(45.0f))	// ����p
#define	VIEW_NEAR_Z				(10.0f)					// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z				(10000.0f)				// �r���[���ʂ�FarZ�l

#define	VALUE_MOVE_CAMERA		(2.0f)					// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA		(D3DX_PI * 0.01f)		// �J�����̉�]��

#define	CHASE_HEIGHT_NEAR		(400.0f)				// �ǐՎ��̎��_�̍���
#define	CHASE_HEIGHT_FAR		(1700.0f)				// �ǐՎ��̎��_�̍���
#define	CHASE_HEIGHT_CUTSCENE	(100.0f)				// �ǐՎ��̎��_�̍���

#define	RADIUS_NEAR				(400.0f)				// ���_�ƒ����_��xoz�ʂ̋���
#define	RADIUS_FAR				(300.0f)				// ���_�ƒ����_��xoz�ʂ̋���
#define	RADIUS_CUTSCENE			(200.0f)				// ���_�ƒ����_��xoz�ʂ̋���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

void SwitchCameraMode();
void CameraChase();
void Chase(D3DXVECTOR3 target);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DXVECTOR3		g_cameraPos;				// �J�����̎��_
D3DXVECTOR3		g_cameraAt;					// �J�����̒����_
D3DXVECTOR3		g_cameraUp;					// �J�����̏����

D3DXVECTOR3		g_rotCamera;				// �J�����̉�]		.y�����g��
float			g_fLengthIntervalCamera;	// �J�����̎��_�ƒ����_��XOZ�ʂ̋���
float			g_fChaseHeight;				// �ǐՎ��̎��_�̍���

D3DXMATRIX		g_mtxView;					// �r���[�}�g���b�N�X
D3DXMATRIX		g_mtxProjection;			// �v���W�F�N�V�����}�g���b�N�X

CAMERA_MODE		g_cameraMode;

//=============================================================================
// �J�����̏�����
//=============================================================================
HRESULT InitCamera(void)
{
	//�����J�������[�h��ݒ�
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
// �J�����̍X�V�����@UpdateCamera()��UpdatePlayer()�̑O�ɒu��
//=============================================================================
void UpdateCamera(void)
{	
#ifdef _DEBUG
	//�J���ҋ@�\	�J������M��
	if (GetKeyboardPress(DIK_Q))
	{// Y������]
		g_rotCamera.y -= VALUE_ROTATE_CAMERA;
	}
	if (GetKeyboardPress(DIK_E))
	{// Y���E��]
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
	{// �ǐՎ��̎��_�̍���
		g_fChaseHeight -= VALUE_MOVE_CAMERA;
	}
	if (GetKeyboardPress(DIK_K))
	{// �ǐՎ��̎��_�̍���
		g_fChaseHeight += VALUE_MOVE_CAMERA;
	}
#endif

	if ((GetPlayMode() == PLAY_MODE_SINGLE) && (GetKeyboardTrigger(DIK_LSHIFT) || IsButtonTrigger(0, BUTTON_CROSS)))
	{//�V���O�����[�h�̏ꍇ�A���߃J�������؊��ł���
		SwitchCameraMode();
	}

	//�J�������[�h�ɉ����āA�p�����[�^�[��ݒ�
	{//����������ƁA�J���ҋ@�\�ŃJ���������R�ɒ����ł���
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
		{//�������̃J�b�g�V�[��
			g_fChaseHeight = CHASE_HEIGHT_CUTSCENE;
			g_fLengthIntervalCamera = RADIUS_CUTSCENE;
		}
	}

}

//=============================================================================
// �J�����̐ݒ菈��
// UpdatePlayer()�̌�ɒu��
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �J�����ǐՂ̐ݒ�
	CameraChase();							//�v���C���[�̍ŐV�̈ʒu�����g�����߂ɁASetCamera()��UpdatePlayer()�̌�ɒu��

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_mtxView, 
						&g_cameraPos,		// �J�����̎��_
						&g_cameraAt,		// �J�����̒����_
						&g_cameraUp);		// �J�����̏����

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


	//�f�o�b�O�p�o�͏��
	PrintDebugProc("[camera pos�F(%f : %f : %f)]\n", g_cameraPos.x,
		g_cameraPos.y,
		g_cameraPos.z);
	PrintDebugProc("[camera at�F(%f : %f : %f)]\n", g_cameraAt.x,
		g_cameraAt.y,
		g_cameraAt.z);

	PrintDebugProc("\n");
	PrintDebugProc("[camera rot�F(%f : %f : %f)]\n", g_rotCamera.x,
		g_rotCamera.y,
		g_rotCamera.z);
	PrintDebugProc("\n");
	PrintDebugProc("chaseHightP:%f\n", g_fChaseHeight);
	PrintDebugProc("\n");
	PrintDebugProc("LengthIntervalCamera:%f\n", g_fLengthIntervalCamera);
	PrintDebugProc("\n");

}

//=============================================================================
// �J�����̌����̎擾
// �v���C���[�̌��������p
//=============================================================================
D3DXVECTOR3 GetRotCamera(void)
{
	return g_rotCamera;
}

//=============================================================================
// �r���[�}�g���b�N�X�̎擾
// �r���{�[�h�ł���effect�p
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	return g_mtxView;
}

//=============================================================================
// �J�������[�h���Z�b�g
//=============================================================================
void SetCameraMode(CAMERA_MODE mode)
{
	g_cameraMode = mode;
}

//=============================================================================
// �J��������2���[�h�Ԃ̐؂�ւ�
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
// �J�����ǐՂ̐ݒ�
//=============================================================================
void CameraChase()
{
	if (GetPlayMode() == PLAY_MODE_SINGLE)
	{
		if ((g_cameraMode == CAMERA_MODE_NEAR) || (g_cameraMode == CAMERA_MODE_CUTSCENE))
		{
			Chase(GetPositionPlayer());				//�v���C���[��ǐՂ���
		}
		else if (g_cameraMode == CAMERA_MODE_FAR)
		{
			Chase(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	//(0.0f, 0.0f, 0.0f)�𒍎��_�ɂ���
		}
	}
	else if (GetPlayMode() == PLAY_MODE_DOUBLE)
	{
		if (g_cameraMode == CAMERA_MODE_CUTSCENE)
		{
			if (GetWinner() == OBJECT_PLAYER)
			{
				Chase(GetPositionPlayer());			//�v���C���[�𒍎��_�ɂ���
			}
			else if (GetWinner() == OBJECT_ENEMY)
			{
				Chase(GetPositionEnemy());			//�G�l�~�[�𒍎��_�ɂ���
			}
		}
		else if (g_cameraMode == CAMERA_MODE_FAR)
		{
			Chase(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	//(0.0f, 0.0f, 0.0f)�𒍎��_�ɂ���
		}
	}

}

//=============================================================================
// �J�����́A����|�C���g��ǐՂ���
// �f�[�^���J�����̕ϐ��ɔ��f����
//=============================================================================
void Chase(D3DXVECTOR3 target)
{
	// ���_�̈ʒu
	g_cameraPos.x = target.x - sinf(g_rotCamera.y) * g_fLengthIntervalCamera;	//- sinf(g_rotCamera.y)��-����]�̕��������߂�
	g_cameraPos.y = target.y + g_fChaseHeight;
	g_cameraPos.z = target.z - cosf(g_rotCamera.y) * g_fLengthIntervalCamera;	//- cosf(g_rotCamera.y)��-���ŏ��J�����̌��������߂�

	// �����_�̈ʒu
	g_cameraAt = target;

}