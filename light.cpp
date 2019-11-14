//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : ���p�j
//
//=============================================================================
#include "light.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void SetDirectionalLight(LPDIRECT3DDEVICE9 pDevice, D3DLIGHT9& light, int idx, D3DCOLORVALUE color, D3DXVECTOR3 vec);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DLIGHT9 g_aLight[3];				// ���C�g�̃��[�N

//=============================================================================
// ���C�g�̏���������
//=============================================================================
HRESULT InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	SetDirectionalLight(pDevice, g_aLight[0], 0, D3DXCOLOR(0.60f, 0.60f, 0.60f, 1.0f),	D3DXVECTOR3(0.20f, -0.60f, 0.80f));		//�E����Ɏw��

	SetDirectionalLight(pDevice, g_aLight[1], 1, D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f), D3DXVECTOR3(-0.20f, 1.00f, -0.50f));		//����O�Ɏw��

	SetDirectionalLight(pDevice, g_aLight[2], 2, D3DXCOLOR(0.25f, 0.25f, 0.25f, 1.0f), D3DXVECTOR3(0.80f, 0.10f, 0.50f));		//�E���Ɏw��

	// ���C�e�B���O���[�h
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	return S_OK;
}

//=============================================================================
// Directional���C�g�̐ݒ�
//=============================================================================
void SetDirectionalLight(LPDIRECT3DDEVICE9 pDevice,D3DLIGHT9& light, int idx, D3DCOLORVALUE color, D3DXVECTOR3 vec)
{
	// D3DLIGHT9�\���̂�0�ŃN���A����
	ZeroMemory(&light, sizeof(D3DLIGHT9));

	// ���C�g�̃^�C�v�̐ݒ�
	light.Type = D3DLIGHT_DIRECTIONAL;

	// �g�U���̐ݒ�
	light.Diffuse = color;

	// �����̐ݒ�
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vec);//�x�N�g���𐳋K��

	// ���C�g�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(idx, &light);

	// ���C�g�̐ݒ�
	pDevice->LightEnable(idx, TRUE);
}
