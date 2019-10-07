//=============================================================================
//
// ���ʂ̋@�\ [function.cpp]
// Author : ���p�j
//
//=============================================================================
#include "function.h"


//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9& vtxBuff, D3DXVECTOR3 vtx, float width, float height)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
											D3DUSAGE_WRITEONLY,				// ���_�o�b�t�@�̎g�p�@�@
											FVF_VERTEX_2D,					// �g�p���钸�_�t�H�[�}�b�g
											D3DPOOL_MANAGED,				// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
											&vtxBuff,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
											NULL)))							// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(vtx.x, vtx.y, vtx.z);
		pVtx[1].vtx = D3DXVECTOR3(vtx.x + width, vtx.y, vtx.z);
		pVtx[2].vtx = D3DXVECTOR3(vtx.x, vtx.y + height, vtx.z);
		pVtx[3].vtx = D3DXVECTOR3(vtx.x + width, vtx.y + height, vtx.z);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		vtxBuff->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_�̍��W���Z�b�g
// vtx:���㒸�_�̍��W�@width,height:�͈�
//=============================================================================
void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff, D3DXVECTOR3 vtx, float width, float height)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].vtx = D3DXVECTOR3(vtx.x, vtx.y, vtx.z);
	pVtx[1].vtx = D3DXVECTOR3(vtx.x + width, vtx.y, vtx.z);
	pVtx[2].vtx = D3DXVECTOR3(vtx.x, vtx.y + height, vtx.z);
	pVtx[3].vtx = D3DXVECTOR3(vtx.x + width, vtx.y + height, vtx.z);

	// ���_�f�[�^���A�����b�N����
	vtxBuff->Unlock();
}

//=============================================================================
// ���_�̐F���Z�b�g
// diffuse:���_�̐F
//=============================================================================
void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff, D3DCOLOR diffuse)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���ˌ��̐ݒ�
	pVtx[0].diffuse =
	pVtx[1].diffuse =
	pVtx[2].diffuse =
	pVtx[3].diffuse = diffuse;

	// ���_�f�[�^���A�����b�N����
	vtxBuff->Unlock();
}

//=============================================================================
// ���_�̃e�N�X�`�����W���Z�b�g
// tex:���㒸�_�̃e�N�X�`�����W�@width,height:�͈�
//=============================================================================
void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff, D3DXVECTOR2 tex, float width, float height)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(tex.x, tex.y);
	pVtx[1].tex = D3DXVECTOR2(tex.x + width, tex.y);
	pVtx[2].tex = D3DXVECTOR2(tex.x, tex.y + height);
	pVtx[3].tex = D3DXVECTOR2(tex.x + width, tex.y + height);

	// ���_�f�[�^���A�����b�N����
	vtxBuff->Unlock();
}

//=============================================================================
//�@�|���S����`�悷�鏈��
//=============================================================================
void DrawPolygon(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9 vtxBuff, LPDIRECT3DTEXTURE9 tex)
{
	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, tex);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}