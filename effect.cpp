//=============================================================================
//
// �G�t�F�N�g���� [effect.cpp]
// Author : ���p�j
// 
//=============================================================================
#include "effect.h"
#include "camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_EFFECT			"data/TEXTURE/effect000.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define	MAX_EFFECT				(4096)							// �G�t�F�N�g�ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

LPDIRECT3DTEXTURE9		g_pD3DTextureEffect = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEffect = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

EFFECT					g_aEffect[MAX_EFFECT];			// �G�t�F�N�g���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̍쐬
	//�����̃T�C�Y�A�F�̏�����Ȃ��Ă������A�ǂ�����A�㏑�������
	MakeVertex(pDevice, FVF_VERTEX_3D, g_pD3DVtxBuffEffect, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f,D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), MAX_EFFECT);


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_EFFECT,			// �t�@�C���̖��O
								&g_pD3DTextureEffect);	// �ǂݍ��ރ������[

	//�f�t�H���g�l���Z�b�g
	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].rot = D3DXVECTOR3(-D3DX_PI * 0.5f, 0.0f, 0.0f);	//�������ꂽ�|���S����XOZ���ʂɂ���̂ŁAXOY���ʂɉ�]����K�v����
		g_aEffect[nCntEffect].bUse = false;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect(void)
{
	SAFE_RELEASE(g_pD3DTextureEffect);
	SAFE_RELEASE(g_pD3DVtxBuffEffect);

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect(void)
{
	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if(g_aEffect[nCntEffect].bUse)
		{
			//�ړ�����
			g_aEffect[nCntEffect].pos.x += g_aEffect[nCntEffect].move.x;
			g_aEffect[nCntEffect].pos.z += g_aEffect[nCntEffect].move.z;

			//�A���t�@�l����������
			g_aEffect[nCntEffect].col.a -= g_aEffect[nCntEffect].nDecAlpha;
			if(g_aEffect[nCntEffect].col.a <= 0.0f)
			{
				g_aEffect[nCntEffect].col.a = 0.0f;
			}
			SetVtxDataCor(g_pD3DVtxBuffEffect, FVF_VERTEX_3D, g_aEffect[nCntEffect].col, nCntEffect);

			//���Ԃ��J�E���g�_�E��
			g_aEffect[nCntEffect].nTimer--;
			if(g_aEffect[nCntEffect].nTimer <= 0)
			{
				g_aEffect[nCntEffect].bUse = false;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxRot,mtxTemp, mtxTranslate, g_mtxWorldEffect;

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);				// �p�[�e�B�N�����m�̂��݂��ɁA�Ղ�Ȃ��Ȃ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);					//�r���{�[�h�̓��C�e�B���O�̉e�����󂯂Ȃ�

	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if(g_aEffect[nCntEffect].bUse)
		{
			// �}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldEffect);
			D3DXMatrixIdentity(&mtxTemp);

			// �r���[�}�g���b�N�X���擾
			mtxView = GetMtxView();

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEffect[nCntEffect].rot.y, g_aEffect[nCntEffect].rot.x, g_aEffect[nCntEffect].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldEffect, &g_mtxWorldEffect, &mtxRot);

			//�J�����̉�]�𑊎E���āA�����J�����Ɍ������悤��
			mtxTemp._11 = mtxView._11;
			mtxTemp._12 = mtxView._21;
			mtxTemp._13 = mtxView._31;
			mtxTemp._21 = mtxView._12;
			mtxTemp._22 = mtxView._22;
			mtxTemp._23 = mtxView._32;
			mtxTemp._31 = mtxView._13;
			mtxTemp._32 = mtxView._23;
			mtxTemp._33 = mtxView._33;
			D3DXMatrixMultiply(&g_mtxWorldEffect, &g_mtxWorldEffect, &mtxTemp);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_aEffect[nCntEffect].pos.x, g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldEffect, &g_mtxWorldEffect, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldEffect);

			DrawPolygon(pDevice, FVF_VERTEX_3D, g_pD3DVtxBuffEffect, g_pD3DTextureEffect, nCntEffect);

		}
	}

	// �e�p�����[�^�[�̃f�t�H���g�l�ɖ߂�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//=============================================================================
// �G�t�F�N�g�̐ݒ�
//=============================================================================
int SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fSizeX, float fSizeY, int nTimer)
{
	int nIdxEffect = -1;

	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if(!g_aEffect[nCntEffect].bUse)
		{
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].move = move;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fSizeX = fSizeX;
			g_aEffect[nCntEffect].fSizeY = fSizeY;
			g_aEffect[nCntEffect].nTimer = nTimer;
			g_aEffect[nCntEffect].nDecAlpha = col.a / nTimer;	//�d�v!!!
			g_aEffect[nCntEffect].bUse = true;

			// ���_���W�̐ݒ�
			SetVtxDataVtx(g_pD3DVtxBuffEffect, FVF_VERTEX_3D, D3DXVECTOR3(0.0f, 0.0f, 0.0f), fSizeX, fSizeY, nCntEffect);

			// ���_�J���[�̐ݒ�
			SetVtxDataCor(g_pD3DVtxBuffEffect, FVF_VERTEX_3D, g_aEffect[nCntEffect].col, nCntEffect);

			nIdxEffect = nCntEffect;

			break;
		}
	}

	return nIdxEffect;
}
