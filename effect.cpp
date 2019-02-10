//=============================================================================
//
// �G�t�F�N�g���� [effect.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "effect.h"
#include "input.h"
#include "camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_EFFECT			"data/TEXTURE/effect000.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	EFFECT_SIZE_X			(50.0f)							// �r���{�[�h�̕�
#define	EFFECT_SIZE_Y			(50.0f)							// �r���{�[�h�̍���
#define	VALUE_MOVE_EFFECT		(2.0f)							// �ړ����x

#define	MAX_EFFECT				(4096)							// �G�t�F�N�g�ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ��]
	D3DXVECTOR3 scale;		// �X�P�[��
	D3DXVECTOR3 move;		// �ړ���
	D3DXCOLOR col;			// �F
	float fSizeX;			// ��
	float fSizeY;			// ����
	int nTimer;				// �^�C�}�[
	float nDecAlpha;		// �����l
	bool bUse;				// �g�p���Ă��邩�ǂ���
} EFFECT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);
void SetVertexEffect(int nIdxEffect, float fSizeX, float fSizeY);
void SetColorEffect(int nIdxEffect, D3DXCOLOR col);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEffect = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEffect = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

D3DXMATRIX				g_mtxWorldEffect;				// ���[���h�}�g���b�N�X

EFFECT					g_aEffect[MAX_EFFECT];			// �G�t�F�N�g���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̍쐬
	MakeVertexEffect(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_EFFECT,			// �t�@�C���̖��O
								&g_pD3DTextureEffect);	// �ǂݍ��ރ������[

	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fSizeX = EFFECT_SIZE_X;
		g_aEffect[nCntEffect].fSizeY = EFFECT_SIZE_Y;
		g_aEffect[nCntEffect].nTimer = 0;
		g_aEffect[nCntEffect].bUse = false;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect(void)
{
	if(g_pD3DTextureEffect != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureEffect->Release();
		g_pD3DTextureEffect = NULL;
	}

	if(g_pD3DVtxBuffEffect != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffEffect->Release();
		g_pD3DVtxBuffEffect = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect(void)
{
	D3DXVECTOR3 rotCamera;

	// �J�����̉�]���擾
	rotCamera = GetRotCamera();

	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if(g_aEffect[nCntEffect].bUse)
		{
			g_aEffect[nCntEffect].pos.x += g_aEffect[nCntEffect].move.x;
			g_aEffect[nCntEffect].pos.z += g_aEffect[nCntEffect].move.z;

			g_aEffect[nCntEffect].col.a -= g_aEffect[nCntEffect].nDecAlpha;//��������
			if(g_aEffect[nCntEffect].col.a <= 0.0f)
			{
				g_aEffect[nCntEffect].col.a = 0.0f;
			}
			SetColorEffect(nCntEffect,g_aEffect[nCntEffect].col);

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
	D3DXMATRIX mtxView,mtxScale,mtxTranslate;

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// ���f�X�e�B�l�[�V�����J���[�̎w��
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);			// Z��r�Ȃ�

//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O���� ����main�ɏ����Ă���
//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@���� default
//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@���� default

	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if(g_aEffect[nCntEffect].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldEffect);

			// �r���[�}�g���b�N�X���擾
			mtxView = GetMtxView();

			g_mtxWorldEffect._11 = mtxView._11;
			g_mtxWorldEffect._12 = mtxView._21;
			g_mtxWorldEffect._13 = mtxView._31;
			g_mtxWorldEffect._21 = mtxView._12;
			g_mtxWorldEffect._22 = mtxView._22;
			g_mtxWorldEffect._23 = mtxView._32;
			g_mtxWorldEffect._31 = mtxView._13;
			g_mtxWorldEffect._32 = mtxView._23;
			g_mtxWorldEffect._33 = mtxView._33;

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, g_aEffect[nCntEffect].scale.x, g_aEffect[nCntEffect].scale.y, g_aEffect[nCntEffect].scale.z);
			D3DXMatrixMultiply(&g_mtxWorldEffect, &g_mtxWorldEffect, &mtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_aEffect[nCntEffect].pos.x, g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldEffect, &g_mtxWorldEffect, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldEffect);

			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureEffect);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntEffect * 4), NUM_POLYGON);

			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);				// Z��r����

//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_EFFECT,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,							// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,								// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,							// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffEffect,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))										// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-EFFECT_SIZE_X / 2, -EFFECT_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(EFFECT_SIZE_X / 2, -EFFECT_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-EFFECT_SIZE_X / 2, EFFECT_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(EFFECT_SIZE_X / 2, EFFECT_SIZE_Y / 2, 0.0f);

			// �@���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffEffect->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEffect(int nIdxEffect, float fSizeX, float fSizeY)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxEffect * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffEffect->Unlock();
	}
}

//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorEffect(int nIdxEffect, D3DXCOLOR col)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxEffect * 4);

		// ���_���W�̐ݒ�
		pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = col;

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffEffect->Unlock();
	}
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
			g_aEffect[nCntEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEffect[nCntEffect].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_aEffect[nCntEffect].move = move;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fSizeX = fSizeX;
			g_aEffect[nCntEffect].fSizeY = fSizeY;
			g_aEffect[nCntEffect].nTimer = nTimer;
			g_aEffect[nCntEffect].nDecAlpha = col.a / nTimer;//�d�v!!!
			g_aEffect[nCntEffect].bUse = true;

			// ���_���W�̐ݒ�
			SetVertexEffect(nCntEffect, fSizeX, fSizeY);

			// ���_�J���[�̐ݒ�
			SetColorEffect(nCntEffect,g_aEffect[nCntEffect].col);

			nIdxEffect = nCntEffect;

			break;
		}
	}

	return nIdxEffect;
}
