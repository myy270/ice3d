//=============================================================================
//
// �e���� [shadow.cpp]
// Author : ���p�j
// 
//=============================================================================
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SHADOW		"data/TEXTURE/shadow000.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define	MAX_SHADOW			(MAX_ITEM + 2)					// �e�ő吔 (�A�C�e���ő吔 + �v���C���[�ƃG�l�~�[�̐�)

#define	HEIGHT_FROMLAND_SHADOW			(0.1f)				// �e�̑؋󍂂�

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureShadow = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffShadow = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

SHADOW					g_aShadow[MAX_SHADOW];			// �e���[�N
//=============================================================================
// ����������
//=============================================================================
HRESULT InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�����̃T�C�Y�A����Ȃ��Ă������A�ǂ�����A�㏑�������
	MakeVertex(pDevice, FVF_VERTEX_3D, g_pD3DVtxBuffShadow, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 
																			D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), MAX_SHADOW);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SHADOW,				// �t�@�C���̖��O
								&g_pD3DTextureShadow);		// �ǂݍ��ރ������[

	//�f�t�H���g�l���Z�b�g
	for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].bUse = false;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitShadow(void)
{
	SAFE_RELEASE(g_pD3DTextureShadow);
	SAFE_RELEASE(g_pD3DVtxBuffShadow);

}

//=============================================================================
// �e�̈ʒu���X�V�A�ʒu�̍����ɂ��A�傫���Ɠ����x��ω�����
// size:�e�̎l�ӂ̒��� �܂�A���f���̒��a
// farFromLand:���f���̐��펞�̑؋󍂂�
//=============================================================================
void UpdateShadow(int nIdxShadow, D3DXVECTOR3 pos, float farFromLand)
{
	if (nIdxShadow >= 0 && nIdxShadow < MAX_SHADOW)
	{
		g_aShadow[nIdxShadow].pos = D3DXVECTOR3(pos.x, HEIGHT_FROMLAND_SHADOW, pos.z);

		//�����ɂ��A�e�̑傫�����ω�����	//������΍����قǑ傫��
		float fSize = g_aShadow[nIdxShadow].size + (pos.y - farFromLand) * 0.05f;

		if (pos.y < 0.0f)
		{//�n�ʈȉ��ɍs���Ƃ�
			fSize = 0.0f;
		}

		//�e�̑傫�����X�V
		SetVtxDataVtx(g_pD3DVtxBuffShadow, FVF_VERTEX_3D, D3DXVECTOR3(0.0f, 0.0f, 0.0f), fSize, fSize, nIdxShadow);

		//�����ɂ��A�e�̓����x���ω�����	//������΍����قǓ����I
		float colA = 0.5f - (pos.y - farFromLand) / 400.0f;

		if (colA < 0.0f)
		{
			colA = 0.0f;
		}
		if (pos.y < 0.0f)
		{//�n�ʈȉ��ɍs���Ƃ�
			colA = 0.0f;
		}

		//�e�̓����x���X�V
		SetVtxDataCor(g_pD3DVtxBuffShadow, FVF_VERTEX_3D, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA), nIdxShadow);
	}


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
			
	D3DXMATRIX mtxTranslate, g_mtxWorldShadow;				// ���[���h�}�g���b�N�X

	// ���Z����
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);		// ���� = �]����(DEST) - �]����(SRC)
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);					// ZBUFFER�ɍX�V���Ȃ��@���̕����Ղ�Ȃ��悤��
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);				// Z��r�Ȃ�	�e���ǂɉf�邽�߂�

	for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if(g_aShadow[nCntShadow].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldShadow);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldShadow);

			DrawPolygon(pDevice, FVF_VERTEX_3D, g_pD3DVtxBuffShadow, g_pD3DTextureShadow, nCntShadow);

		}
	}

	// �e�p�����[�^�[�̃f�t�H���g�l�ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);				// ���� = �]����(SRC) + �]����(DEST)
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);				// Z��r����

}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
int SetShadow(D3DXVECTOR3 pos, float fSize)
{
	int nIdxShadow = -1;

	for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if(!g_aShadow[nCntShadow].bUse)
		{
			g_aShadow[nCntShadow].size = fSize;
			g_aShadow[nCntShadow].pos = pos;
			g_aShadow[nCntShadow].bUse = true;

			//�傫���𔽉f����
			SetVtxDataVtx(g_pD3DVtxBuffShadow, FVF_VERTEX_3D, D3DXVECTOR3(0.0f, 0.0f, 0.0f), fSize, fSize, nCntShadow);

			nIdxShadow = nCntShadow;

			break;
		}
	}

	return nIdxShadow;
}

//=============================================================================
// �e�̍폜
//=============================================================================
void DeleteShadow(int nIdxShadow)
{
	if(nIdxShadow >= 0 && nIdxShadow < MAX_SHADOW)
	{
		g_aShadow[nIdxShadow].bUse = false;
	}
}
