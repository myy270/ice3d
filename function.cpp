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

		// ���_���W�̐ݒ�
		SetVtxData(vtxBuff, D3DXVECTOR3(vtx.x, vtx.y, vtx.z), width, height);

		// RHW�p
		SetVtxData(vtxBuff, 1.0f);

		// ���ˌ��̐ݒ�
		SetVtxData(vtxBuff, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// �e�N�X�`�����W�̐ݒ�
		SetVtxData(vtxBuff, D3DXVECTOR2(0.0f, 0.0f),1.0f,1.0f);

	}

	return S_OK;
}

//=============================================================================
// �����ƃt���[���̒��_�̍쐬
// numPlace:�����̌����@
// numPos:�擪�̐����̍��㒸�_�̍��W	numWidth:�P�̂̐����̕�		numHeight:�P�̂̐����̍���	numInterval:�����̕\���Ԋu
// framePos:�t���[���̍��㒸�_�̍��W	frameWidth:�t���[���̕�		frameHeight:�t���[���̍���
//	diffuse:�S�̂̐F
//=============================================================================
HRESULT MakeVertexNumFrame(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9& vtxBuff, int numPlace, 
												D3DXVECTOR3 numPos, float numWidth, float numHeight,float numInterval,
												D3DXVECTOR3 framePos, float frameWidth, float frameHeight,
												D3DCOLOR diffuse)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * (numPlace + 1),	//+1 �̓t���[�����܂ނ���
		D3DUSAGE_WRITEONLY,				// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,					// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&vtxBuff,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))							// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�		
		for (int nCntPlace = 0; nCntPlace <= numPlace; nCntPlace++)		//nCntPlace�͐����̍�����n�߂�Y����
		{
			if (nCntPlace < numPlace)
			{//	�X�R�A�̐���

				// ���_���W�̐ݒ�
				SetVtxData(vtxBuff, D3DXVECTOR3(numPos.x + nCntPlace * (numWidth + numInterval), numPos.y, 0.0f), numWidth, numHeight, nCntPlace);

				//�e�N�X�`���\���W�̐ݒ�	�����l�A���ƂŕύX����
				SetVtxData(vtxBuff, D3DXVECTOR2(0.0f, 0.0f), 0.1f, 1.0f, nCntPlace);
			}
			else
			{//�X�R�A�̃t���[��

				// ���_���W�̐ݒ�
				SetVtxData(vtxBuff, framePos, frameWidth, frameHeight, nCntPlace);

				//�e�N�X�`���\���W�̐ݒ�
				SetVtxData(vtxBuff, D3DXVECTOR2(0.0f, 0.0f), 1.0f, 1.0f, nCntPlace);
			}

			// rhw�̐ݒ�
			SetVtxData(vtxBuff, 1.0f, nCntPlace);

			// ���ˌ��̐ݒ�
			SetVtxData(vtxBuff, diffuse, nCntPlace);


		}
	}

	return S_OK;
}


//=============================================================================
// ���_�̍��W���Z�b�g
// vtx:���㒸�_�̍��W�@width,height:�͈�	index:��`�|���S���̔ԍ�
//=============================================================================
void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff, D3DXVECTOR3 vtx, float width, float height, int index)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx = pVtx + index * NUM_VERTEX;

	// ���_���W�̐ݒ�
	pVtx[0].vtx = D3DXVECTOR3(vtx.x, vtx.y, vtx.z);
	pVtx[1].vtx = D3DXVECTOR3(vtx.x + width, vtx.y, vtx.z);
	pVtx[2].vtx = D3DXVECTOR3(vtx.x, vtx.y + height, vtx.z);
	pVtx[3].vtx = D3DXVECTOR3(vtx.x + width, vtx.y + height, vtx.z);

	// ���_�f�[�^���A�����b�N����
	vtxBuff->Unlock();
}



//=============================================================================
// ���_��RHW���Z�b�g
// 	index:��`�|���S���̔ԍ�
//=============================================================================
void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff, float rhw, int index)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx = pVtx + index * NUM_VERTEX;

	// ���ˌ��̐ݒ�
	pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = rhw;

	// ���_�f�[�^���A�����b�N����
	vtxBuff->Unlock();
}

//=============================================================================
// ���_�̐F���Z�b�g
// diffuse:���_�̐F	index:��`�|���S���̔ԍ�
//=============================================================================
void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff, D3DCOLOR diffuse, int index)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx = pVtx + index * NUM_VERTEX;

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
// tex:���㒸�_�̃e�N�X�`�����W�@width,height:�͈�	index:��`�|���S���̔ԍ�
//=============================================================================
void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff, D3DXVECTOR2 tex, float width, float height, int index)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx = pVtx + index * NUM_VERTEX;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(tex.x, tex.y);
	pVtx[1].tex = D3DXVECTOR2(tex.x + width, tex.y);
	pVtx[2].tex = D3DXVECTOR2(tex.x, tex.y + height);
	pVtx[3].tex = D3DXVECTOR2(tex.x + width, tex.y + height);

	// ���_�f�[�^���A�����b�N����
	vtxBuff->Unlock();
}

//=============================================================================
// ���_�̃e�N�X�`�����W���Z�b�g(�A�������̏ꍇ)
// numSet:��A�̐����@numPlace:���̐����̌���
//=============================================================================
void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff,int numSet, int numPlace)
{
	//�^�C�}�[�̊e���̐��������߂�
	for(int i = 0; i < numPlace; i++)			//i�͐����̍�����n�܂�Y����
	{
		int num;	//�e���̒P�̂̐���

		//�e���̐�����������v�Z����
		num = (numSet % (int)(powf(10.0f, (float)(numPlace - i))))			//�w���Ă��錅�̍��������̂ĂāA�c��̕������Ƃ�;	�Ⴆ�΁AnumSet = 123, numPlace = 3 , i = 1�̏ꍇ,���q = 23
						/ (int)(powf(10.0f, (float)(numPlace - i - 1)));	//�Ⴆ�΁Acount = 123, NUM_PLACE = 3 ,i = 1�̏ꍇ,���� = 10
																			//����num = 2,�܂�Y����1�̎w���Ă��錅�̐��������߂���

		//���̌��̐����ɑΉ�����e�N�X�`�����Z�b�g(�e�N�X�`���\���W�̕ύX�ɂ��)
		SetVtxData(vtxBuff, D3DXVECTOR2(num * 0.1f, 0.0f), 0.1f, 1.0f, i);
	}

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

//=============================================================================
//�@�|���S����`�悷�鏈��	�i�A���ɒ��_��`�悷��ꍇ)
//  index:��`�|���S���̔ԍ�
//=============================================================================
void DrawPolygon(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9 vtxBuff, LPDIRECT3DTEXTURE9 tex,int indexStart, int indexEnd)
{
	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, tex);

	for (int i = indexStart; i <= indexEnd; i++)
	{
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * NUM_VERTEX, NUM_POLYGON);
	}

}
