//=============================================================================
//
// ���ʂ̋@�\ [function.cpp]
// Author : ���p�j
//
//=============================================================================
#include "function.h"

#include "shadow.h"
#include "camera.h"
#include "input.h"
#include "timer.h"
#include "item.h"
#include "debugproc.h"
#include "effect.h"
#include "score.h"
#include "player.h"
#include "enemy.h"
#include "sound.h"
#include "title.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//�������[�V�����̃f�[�^
KEY g_motionWalk[] =
{
	{
		15,
		{
			{// part 0
				D3DXVECTOR3(1.5000f,1.5000f,1.5000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,22.4000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,6.5000f,0.0000f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(5.0000f,5.0000f,0.0000f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,3.1416f,0.0000f),//R
				D3DXVECTOR3(-5.0000f,5.0000f,0.0000f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-3.0640f,-4.8730f,-0.4090f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(1.5000f,1.5000f,1.5000f),//S
				D3DXVECTOR3(-0.0385f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,22.4000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,6.5000f,0.0000f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(1.4923f,0.0000f,0.0000f),//R
				D3DXVECTOR3(5.0000f,5.0000f,0.0000f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.7069f,3.1416f,0.0000f),//R
				D3DXVECTOR3(-5.0000f,5.0000f,0.0000f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-1.0854f,0.0000f,0.0000f),//R
				D3DXVECTOR3(3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.9425f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-3.0640f,-4.8730f,-0.4090f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(1.5000f,1.5000f,1.5000f),//S
				D3DXVECTOR3(-0.0385f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,22.4000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,6.5000f,0.0000f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-0.8639f,0.0000f,0.0000f),//R
				D3DXVECTOR3(5.0000f,5.0000f,0.0000f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-1.0996f,3.1416f,0.0000f),//R
				D3DXVECTOR3(-5.0000f,5.0000f,0.0000f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.9425f,0.0000f,0.0000f),//R
				D3DXVECTOR3(3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-1.0854f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-3.0640f,-4.8730f,-0.4090f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(1.5000f,1.5000f,1.5000f),//S
				D3DXVECTOR3(-0.0385f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,22.4000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,6.5000f,0.0000f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(1.4923f,0.0000f,0.0000f),//R
				D3DXVECTOR3(5.0000f,5.0000f,0.0000f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.7069f,3.1416f,0.0000f),//R
				D3DXVECTOR3(-5.0000f,5.0000f,0.0000f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-1.0854f,0.0000f,0.0000f),//R
				D3DXVECTOR3(3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.9425f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-3.0640f,-4.8730f,-0.4090f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void Interpolation(int partNum, XMODEL *part, const SRT *srt1, const SRT *srt2, float rate);
void Interpolation(int partNum, XMODEL *part, const SRT *srt2, float rate);

//=============================================================================
// ���_�̍쐬
// FVF_VERTEX_3D�̎��A������vtx�͉��̖������Ȃ�
// num:��`�̐�
//=============================================================================
HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice, DWORD FVF, LPDIRECT3DVERTEXBUFFER9& vtxBuff, D3DXVECTOR3 vtx, float width, float height, 
																											D3DCOLOR diffuse, int num)
{
	if (FVF == FVF_VERTEX_2D)
	{
		// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * num,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
			D3DUSAGE_WRITEONLY,				// ���_�o�b�t�@�̎g�p�@�@
			FVF_VERTEX_2D,					// �g�p���钸�_�t�H�[�}�b�g
			D3DPOOL_MANAGED,				// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
			&vtxBuff,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
			NULL)))							// NULL�ɐݒ�
		{
			return E_FAIL;
		}
	}
	else if (FVF == FVF_VERTEX_3D)
	{
		// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * num,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
			D3DUSAGE_WRITEONLY,				// ���_�o�b�t�@�̎g�p�@�@
			FVF_VERTEX_3D,					// �g�p���钸�_�t�H�[�}�b�g
			D3DPOOL_MANAGED,				// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
			&vtxBuff,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
			NULL)))							// NULL�ɐݒ�
		{
			return E_FAIL;
		}
	}

	//���_�o�b�t�@�̒��g�𖄂߂�
	for (int i = 0; i < num; i++)
	{
		// ���_���W�̐ݒ�
		SetVtxDataVtx(vtxBuff, FVF, vtx, width, height, i);

		if (FVF == FVF_VERTEX_2D)
		{
			// RHW�̐ݒ�
			SetVtxDataRHW(vtxBuff, 1.0f, i);
		}
		else if (FVF == FVF_VERTEX_3D)
		{
			// �m�[�}���̐ݒ�
			SetVtxDataNor(vtxBuff, D3DXVECTOR3(0.0f, 1.0f, 0.0f), i);
		}

		// ���ˌ��̐ݒ�
		SetVtxDataCor(vtxBuff, FVF, diffuse, i);

		// �e�N�X�`�����W�̐ݒ�
		SetVtxDataTex(vtxBuff, FVF, D3DXVECTOR2(0.0f, 0.0f),1.0f,1.0f, i);

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
		for (int nCntPlace = 0; nCntPlace < numPlace + 1; nCntPlace++)		//nCntPlace�͐����̍�����n�߂�Y����
		{
			if (nCntPlace < numPlace)
			{//	�X�R�A�̐���

				// ���_���W�̐ݒ�
				SetVtxDataVtx(vtxBuff, FVF_VERTEX_2D, D3DXVECTOR3(numPos.x + nCntPlace * (numWidth + numInterval), numPos.y, 0.0f), numWidth, numHeight, nCntPlace);

				//�e�N�X�`���\���W�̐ݒ�	�����l�A���ƂŕύX����
				SetVtxDataTex(vtxBuff, FVF_VERTEX_2D, D3DXVECTOR2(0.0f, 0.0f), 0.1f, 1.0f, nCntPlace);
			}
			else
			{//�X�R�A�̃t���[��

				// ���_���W�̐ݒ�
				SetVtxDataVtx(vtxBuff, FVF_VERTEX_2D, framePos, frameWidth, frameHeight, nCntPlace);

				//�e�N�X�`���\���W�̐ݒ�
				SetVtxDataTex(vtxBuff, FVF_VERTEX_2D, D3DXVECTOR2(0.0f, 0.0f), 1.0f, 1.0f, nCntPlace);
			}

			// rhw�̐ݒ�
			SetVtxDataRHW(vtxBuff, 1.0f, nCntPlace);

			// ���ˌ��̐ݒ�
			SetVtxDataCor(vtxBuff, FVF_VERTEX_2D, diffuse, nCntPlace);

		}
	}

	return S_OK;
}

//=============================================================================
// ���b�V���t�B�[���h�̒��_�o�b�t�@�̍쐬
// numVertex: ���_�̐��A
// numBlockH�F�������̃u���b�N�̐��AnumBlockV:�c�����̃u���b�N�̐�
// blockSizeH:�������̃u���b�N�̃T�C�Y�AblockSizeV:�c�����̃u���b�N�̃T�C�Y
// type:�e�N�X�`���\�̓\���
//=============================================================================
HRESULT MakeVertexMesh(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9& vtxBuff,int numVertex,
												int numBlockH, int numBlockV,
												float blockSizeH, float blockSizeV, D3DCOLOR col, MAPPINGTYPE type)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * numVertex,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,					// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,						// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&vtxBuff,							// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))								// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	float texSizeH;		//���e�N�X�`���\���W
	float texSizeV;		//�c�e�N�X�`���\���W

	// �e�N�X�`���\���W
	if (type == MAPPINGTYPE_ONE)
	{//�e�N�X�`���[���ꖇ�ɕ`�悷��ꍇ
		texSizeH = 1.0f / numBlockH;
		texSizeV = 1.0f / numBlockV;

	}
	else if(type == MAPPINGTYPE_ALL)
	{//�e�N�X�`���[���d���ɕ`�悷��ꍇ
		texSizeH = 1.0f;
		texSizeV = 1.0f;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < (numBlockV + 1); i++)
		{
			for (int j = 0; j < (numBlockH + 1); j++)
			{
				int idx = i * (numBlockH + 1) + j;

				// ���_���W�̐ݒ�@�����ʒu��XOZ����
				pVtx[idx].vtx.x = -(numBlockH / 2.0f) * blockSizeH + j * blockSizeH;
				pVtx[idx].vtx.y = 0.0f;
				pVtx[idx].vtx.z = (numBlockV / 2.0f) * blockSizeV - i * blockSizeV;

				// �@���̐ݒ�	�m�[�}���͏�ɂ���
				pVtx[idx].nor = D3DXVECTOR3(0.0f, 1.0, 0.0f);

				// ���ˌ��̐ݒ�
				pVtx[idx].diffuse = col;

				// �e�N�X�`�����W�̐ݒ�
				pVtx[idx].tex.x = texSizeH * j;
				pVtx[idx].tex.y = texSizeV * i;
			}
		}

		// ���_�f�[�^���A�����b�N����
		vtxBuff->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���b�V���t�B�[���h�̃C���f�b�N�X�o�b�t�@�̍쐬
// numIndex: �C���f�b�N�X�̐��A
// numBlockH�F�������̃u���b�N�̐��AnumBlockV:�c�����̃u���b�N�̐�
//=============================================================================
HRESULT MakeIndexMesh(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DINDEXBUFFER9& idxBuff, int numIndex,int numBlockH, int numBlockV)
{
	// �I�u�W�F�N�g�̃C���f�b�N�X�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * numIndex,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,					// ���_�o�b�t�@�̎g�p�@�@
		D3DFMT_INDEX16,						// �g�p����C���f�b�N�X�t�H�[�}�b�g
		D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&idxBuff,							// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))								// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//�C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�
		WORD *pIdx;

		// �C���f�b�N�X�f�[�^�͈̔͂����b�N���A�C���f�b�N�X�o�b�t�@�ւ̃|�C���^���擾
		idxBuff->Lock(0, 0, (void**)&pIdx, 0);

		int nCntIdx = 0;
		for (int i = 0; i < numBlockV; i++)
		{//�����ŁA���_�`��̏��Ԃ��킩��悤�ɂȂ�
			if (i > 0)//�ŏ��̏z�����A���s���Ȃ�
			{// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
				pIdx[nCntIdx] = (i + 1) * (numBlockH + 1);
				nCntIdx++;
			}

			for (int nCntVtxX = 0; nCntVtxX < (numBlockH + 1); nCntVtxX++)
			{
				pIdx[nCntIdx] = (i + 1) * (numBlockH + 1) + nCntVtxX;
				nCntIdx++;
				pIdx[nCntIdx] = i * (numBlockH + 1) + nCntVtxX;
				nCntIdx++;
			}

			if (i < (numBlockV - 1))//�Ō�̏z�����A���s���Ȃ�
			{// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
				pIdx[nCntIdx] = i * (numBlockH + 1) + numBlockH;
				nCntIdx++;
			}
		}

		// �C���f�b�N�X�f�[�^���A�����b�N����
		idxBuff->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_�̍��W���Z�b�g
// vtx:���㒸�_�̍��W�@width,height:�͈�	index:��`�|���S���̔ԍ�
//=============================================================================
void SetVtxDataVtx(LPDIRECT3DVERTEXBUFFER9 vtxBuff, DWORD FVF, D3DXVECTOR3 vtx, float width, float height, int index)
{
	if (FVF == FVF_VERTEX_2D)
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
	else if (FVF == FVF_VERTEX_3D)
	{
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx = pVtx + index * NUM_VERTEX;

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-width / 2, 0.0f, height / 2);
		pVtx[1].vtx = D3DXVECTOR3(width / 2, 0.0f, height / 2);
		pVtx[2].vtx = D3DXVECTOR3(-width / 2, 0.0f, -height / 2);
		pVtx[3].vtx = D3DXVECTOR3(width / 2, 0.0f, -height / 2);

		// ���_�f�[�^���A�����b�N����
		vtxBuff->Unlock();
	}

}

//=============================================================================
// ���_��RHW���Z�b�g
// 	index:��`�|���S���̔ԍ�
//=============================================================================
void SetVtxDataRHW(LPDIRECT3DVERTEXBUFFER9 vtxBuff, float rhw, int index)
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
// ���_�̃m�[�}�����Z�b�g
// index:��`�|���S���̔ԍ�
//=============================================================================
void SetVtxDataNor(LPDIRECT3DVERTEXBUFFER9 vtxBuff, D3DXVECTOR3 nor, int index)
{
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx = pVtx + index * NUM_VERTEX;

	// ���ˌ��̐ݒ�
	pVtx[0].nor =
	pVtx[1].nor =
	pVtx[2].nor =
	pVtx[3].nor = nor;

	// ���_�f�[�^���A�����b�N����
	vtxBuff->Unlock();
}

//=============================================================================
// ���_�̐F���Z�b�g
// diffuse:���_�̐F	index:��`�|���S���̔ԍ�
//=============================================================================
void SetVtxDataCor(LPDIRECT3DVERTEXBUFFER9 vtxBuff, DWORD FVF, D3DCOLOR diffuse, int index)
{
	if (FVF == FVF_VERTEX_2D)
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
	else if(FVF == FVF_VERTEX_3D)
	{
		VERTEX_3D *pVtx;

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

}

//=============================================================================
// ���_�̃e�N�X�`�����W���Z�b�g
// tex:���㒸�_�̃e�N�X�`�����W�@width,height:�͈�	index:��`�|���S���̔ԍ�
//=============================================================================
void SetVtxDataTex(LPDIRECT3DVERTEXBUFFER9 vtxBuff, DWORD FVF, D3DXVECTOR2 tex, float width, float height, int index)
{
	if (FVF == FVF_VERTEX_2D)
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
	else if (FVF == FVF_VERTEX_3D)
	{
		VERTEX_3D *pVtx;

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

}

//=============================================================================
// ���_�̃e�N�X�`�����W���Z�b�g(�A�������̏ꍇ)
// numSet:��A�̐����@numPlace:���̐����̌���
//=============================================================================
void SetVtxDataTexNum(LPDIRECT3DVERTEXBUFFER9 vtxBuff,int numSet, int numPlace)
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
		SetVtxDataTex(vtxBuff, FVF_VERTEX_2D, D3DXVECTOR2(num * 0.1f, 0.0f), 0.1f, 1.0f, i);
	}

}

//=============================================================================
//�@�|���S����`�悷�鏈��
// index:�`��J�n�̃C���f�b�N�X
//=============================================================================
void DrawPolygon(LPDIRECT3DDEVICE9 pDevice, DWORD FVF, LPDIRECT3DVERTEXBUFFER9 vtxBuff, LPDIRECT3DTEXTURE9 tex, int index)
{
	if (FVF == FVF_VERTEX_2D)
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_2D));
	}
	else if (FVF == FVF_VERTEX_3D)
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));
	}

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, tex);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (index * NUM_VERTEX), NUM_POLYGON);
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

//=============================================================================
//�@���b�V����`�悷��
//  pos:�|���S���\���ʒu�̒��S���W�Arot:�|���S���̉�]��
//  numVertex:���_��	numPolygon:�|���S����
//=============================================================================
void DrawPolygonMesh(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9 vtxBuff, LPDIRECT3DINDEXBUFFER9 idxBuff, 
															D3DXVECTOR3 pos, D3DXVECTOR3 rot,LPDIRECT3DTEXTURE9 tex,
															int numVertex, int numPolygon)
{
	D3DXMATRIX mtxRot, mtxTranslate, mtxWorldField;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorldField);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxWorldField, &mtxWorldField, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorldField, &mtxWorldField, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorldField);

	// ���_�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@�������_�����O�p�C�v���C���ɐݒ� indices��index�̕���
	pDevice->SetIndices(idxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, tex);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, numVertex, 0, numPolygon);

}

//=============================================================================
// ��]�ʂ̒���
// ���ʁF��]�ʂ��i-Pi,Pi�j�͈̔͂ɂȂ�
// radian:���W�A���P��
//=============================================================================
void LimitRot(float& radian)
{
	while (1)
	{
		if (radian > D3DX_PI)
		{
			radian -= D3DX_PI * 2.0f;
		}
		else if (radian < -D3DX_PI)
		{
			radian += D3DX_PI * 2.0f;
		}
		else
		{
			break;
		}
	}
}

//=============================================================================
// ���[�V�����f�[�^���Q�b�g
//=============================================================================
KEY* GetMotionWalk()
{
	return g_motionWalk;
}

//=============================================================================
// X�t�@�C���̃��f���̕`��i�e�q�֌W�����p�[�c�̕`����ł���j
// model:�Ώۃ��f���̃|�C���^
// numPart:���f���̐�
//=============================================================================
void DrawXMODEL(LPDIRECT3DDEVICE9 pDevice, XMODEL* model, int numPart)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;
	D3DXMATERIAL *pD3DXMat;			// �}�e���A�����ɑ΂���|�C���^

	D3DMATERIAL9 matDef;			// �f�t�H���g�̃}�e���A��
	pDevice->GetMaterial(&matDef);	// �f�t�H���g�̃}�e���A�����擾

	for (int i = 0; i < numPart; i++)//�p�[�c�ԍ�
	{
		if (model[i].use)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, model[i].srt.scl.x,
				model[i].srt.scl.y,
				model[i].srt.scl.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, model[i].srt.rot.y,
				model[i].srt.rot.x,
				model[i].srt.rot.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, model[i].srt.pos.x,
				model[i].srt.pos.y,
				model[i].srt.pos.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

			//�e�����݂���ꍇ�͐e�̃��[���h�}�g���N�X������
			if (model[i].parent)
			{
				D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &model[i].parent->mtxWorld);
			}

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

			//���[���h�}�g���N�X��ۑ�
			model[i].mtxWorld = mtxWorld;

			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)model[i].pMatBuff->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)model[i].nNumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);		//���e�N�X�`���\���Ȃ��Ă��K�v�B�������Ȃ��ƁA���̑O�̃e�N�X�`���\���\���Ă��܂�

				// �`��
				model[i].pMesh->DrawSubset(nCntMat);
			}
		}
	}

	pDevice->SetMaterial(&matDef);// �}�e���A�����f�t�H���g�ɖ߂�

}

//=============================================================================
//�����o�[�ϐ��ɒl�������鏈�� 
//=============================================================================
HRESULT Character::Init(OBJECT object)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	motion.motionData = GetMotionWalk();
	motion.numKey = 4;
	motion.use = false;
	motion.motionTime = 0.0f;
	motion.cancelTime = 0.0f;

	if (object == OBJECT_PLAYER)
	{
		part[0].partFile = (char *)BODY_PLAYER;		//�́@//���ł���e�͈�Ԑ�ɂ��Ȃ���΂Ȃ�Ȃ�
		part[1].partFile = (char *)HEAD_PLAYER;		//��
		part[2].partFile = (char *)HAND_PLAYER;		//����
		part[3].partFile = (char *)HAND_PLAYER;		//�E��
		part[4].partFile = (char *)LEG_PLAYER;		//����
		part[5].partFile = (char *)LEG_PLAYER;		//�E��
	}
	else if (object == OBJECT_ENEMY)
	{
		part[0].partFile = (char *)BODY_ENEMY;
		part[1].partFile = (char *)HEAD_ENEMY;
		part[2].partFile = (char *)HAND_ENEMY;
		part[3].partFile = (char *)HAND_ENEMY;
		part[4].partFile = (char *)LEG_ENEMY;
		part[5].partFile = (char *)LEG_ENEMY;
	}

	part[6].partFile = (char *)ICE_BLOCK;			//�A�C�X�u���b�N

	//�p�[�c�̏��̐ݒ�
	for (int i = 0; i < PART_MAX; i++)				//�p�[�c�ԍ�
	{
		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(part[i].partFile,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&part[i].pMatBuff,
			NULL,
			&part[i].nNumMat,
			&part[i].pMesh)))
		{
			return E_FAIL;
		}

		switch (i)
		{
		case 0:
		{//��
			part[i].srt.scl = D3DXVECTOR3(1.5f, 1.5f, 1.5f);			//�X�P�[����xyz�K�������悤��
			part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			part[i].srt.pos = D3DXVECTOR3(0.0f, 22.4f, 0.0f);			//�����n�ʂɐG���悤�ɒ�������

			if (object == OBJECT_ENEMY)
			{
				part[i].srt.pos.x = 90.0f;
			}

			part[i].parent = NULL;										//�̂̐e��NULL�ɂ���
			break;
		}
		case 1:
		{//��
			part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			part[i].srt.pos = D3DXVECTOR3(0.0f, 6.5f, 0.0f);			//�֐߂̈ʒu�Ɉړ�����

			part[i].parent = &part[0];									//�̂�e�ɂ���
			break;
		}
		case 2:
		{//����
			part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			part[i].srt.pos = D3DXVECTOR3(5.0f, 5.0f, 0.0f);			//�֐߂̈ʒu�Ɉړ�����

			part[i].parent = &part[0];									//�̂�e�ɂ���
			break;
		}
		case 3:
		{//�E��
			part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			part[i].srt.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
			part[i].srt.pos = D3DXVECTOR3(-5.0f, 5.0f, 0.0f);			//�֐߂̈ʒu�Ɉړ�����

			part[i].parent = &part[0];									//�̂�e�ɂ���
			break;
		}
		case 4:
		{//����
			part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			part[i].srt.pos = D3DXVECTOR3(3.064f, -4.873f, -0.409f);	//�֐߂̈ʒu�Ɉړ�����

			part[i].parent = &part[0];									//�̂�e�ɂ���
			break;
		}
		case 5:
		{//�E��
			part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			part[i].srt.pos = D3DXVECTOR3(-3.064f, -4.873f, -0.409f);	//�֐߂̈ʒu�Ɉړ�����

			part[i].parent = &part[0];									//�̂�e�ɂ���
			break;
		}
		default:
		{//�A�C�X�u���b�N
			part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			part[i].srt.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			part[i].parent = &part[0];									//�̂�e�ɂ���
			break;
		}

		}//switch end

		if (i == 6)
		{//�A�C�X�u���b�N�͍ŏ��\�����Ȃ�
			part[i].use = false;
		}
		else
		{
			part[i].use = true;
		}
	}

	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	fRadius = RADIUS_BEAR;

	// �e��ݒ� ����(part[0])�����
	nIdxShadow = SetShadow(part[0].srt.pos, fRadius * 2.0f);	//BUG�e�̑傫���͕ς��Ȃ�

	holdItem = ITEMTYPE_NULL;
	state = NORMAL;
	frozenTime = 0;

	if ((object == OBJECT_ENEMY) && (GetPlayMode() == PLAY_MODE_SINGLE))
	{
		useAI = true;
	}
	else
	{
		useAI = false;
	}

	upAI	= false;
	downAI	= false;
	leftAI	= false;
	rightAI = false;

	objectType = object;

	return S_OK;
}

//=============================================================================
//AI�֘A�̐��䏈��
//=============================================================================
void Character::AIControl()
{
	if (objectType == OBJECT_ENEMY)
	{
#ifdef _DEBUG
		//�J���ҋ@�\
		if (GetKeyboardTrigger(DIK_ADD))		//�e���L�[�̃v���X+
		{//AI���[�h�̐ؑ�
			useAI = !useAI;									//AI���[�h�̐ؑ�

			upAI = downAI = leftAI = rightAI = false;		//���Z�b�g
		}
#endif
	}

	if (useAI)
	{
		AI(AI_TYPE);
	}

}

//=============================================================================
//type = 0:��ԋ߂��R�C���Ɍ������Ĉړ�����AI�̏���
//type = 1�Ȃ�:��ԋ߂��A�C�e��(�R�C�����܂�)�Ɍ������Ĉړ�����AI�̏���
//=============================================================================
int Character::AI(int type)
{
	ITEM *item = GetItem();

	D3DXVECTOR3 vec;				//��Ɨp
	float dis = 0.0f;				//�A�C�e���Ƃ̋���
	float disNear = 99999999.0f;	//��ԋ߂�����
	int tagetNo = -1;				//��������ԋ߂��A�C�e���̔ԍ�

	//��ԋ߂��A�C�e���̔ԍ�����������
	for (int i = 0; i < MAX_ITEM; i++, item++)
	{
		if (type == 0)
		{//��ԋ߂��R�C���̔ԍ����擾����d�l
			if ((item->use) && (item->nType == ITEMTYPE_COIN))
			{
				//�A�C�e���Ƃ̃x�N�g�������߂�
				vec = item->srt.pos - part[0].srt.pos;

				//�A�C�e���Ƃ̋��������߂�
				dis = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

				if (dis < disNear)
				{//���̋��������܂ň�ԏ������ꍇ�A�L�^����
					disNear = dis;
					tagetNo = i;
				}
			}
		}
		else
		{//��ԋ߂��A�C�e���̔ԍ����擾����d�l
			if ((item->use))
			{
				//�A�C�e���Ƃ̃x�N�g�������߂�
				vec = item->srt.pos - part[0].srt.pos;

				//�A�C�e���Ƃ̋��������߂�
				dis = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

				if (dis < disNear)
				{//���̋��������܂ň�ԏ������ꍇ
					if ((item->nType == ITEMTYPE_ICEBLOCK) && (holdItem == ITEMTYPE_ICEBLOCK))
					{//���̃A�C�e���������A�C�e���A���A���łɓ����A�C�e���������Ă���ꍇ�A��������

					}
					else
					{//�L�^����
						disNear = dis;
						tagetNo = i;
					}
				}
			}
		}
	}

	//��ԋ߂��A�C�e���Ɍ������悤�ɁA�ړ��������X�V
	if (tagetNo != -1)
	{
		item = GetItem();		//�|�C���^�����Z�b�g

		vec = (item + tagetNo)->srt.pos - part[0].srt.pos;	//���̈ʒu����A�C�e���ʒu�܂ł̃x�N�g��

		//���E�𔻒f
		if (vec.x < 0)
		{//��������
			leftAI = 1;
			rightAI = 0;
		}
		else if (vec.x == 0)
		{//�E������
			leftAI = 0;
			rightAI = 0;
		}
		else if (vec.x > 0)
		{//���E�����Ȃ�
			leftAI = 0;
			rightAI = 1;
		}

		//�㉺�𔻒f
		if (vec.z < 0)
		{//�������
			upAI = 0;
			downAI = 1;
		}
		else if (vec.z == 0)
		{//��������
			upAI = 0;
			downAI = 0;
		}
		else if (vec.z > 0)
		{//�㉺�����Ȃ�
			upAI = 1;
			downAI = 0;
		}

	}
	else
	{//�R�C�����Ȃ��ꍇ
		leftAI = rightAI = upAI = downAI = 0;//�~�܂�
	}

	//PrintDebugProc("AI(type %d)�̈�ԋ߂��A�C�e���̔ԍ� �F%d \n\n", type, tagetNo);

	return tagetNo;

}

//=============================================================================
//�ʒu�ƌ����̍X�V����
//=============================================================================
void Character::Movement()
{
	int upKey;					//�L�[�{�[�h�̃R���g���[���L�[
	int downKey;
	int leftKey;
	int rightKey;	
	int padNo;					//�R���g���[���[�ԍ�

	D3DXVECTOR3 rotCamera;		//�J�����̌���
	float fDiffRotY;			//�ړI�̊p�x�܂ł̍���

	if (objectType == OBJECT_PLAYER)
	{
		upKey = DIK_W;
		downKey = DIK_S;
		leftKey = DIK_A;
		rightKey = DIK_D;

		padNo = 0;
	}
	else if (objectType == OBJECT_ENEMY)
	{
		upKey = DIK_UP;
		downKey = DIK_DOWN;
		leftKey = DIK_LEFT;
		rightKey = DIK_RIGHT;

		padNo = 1;
	}

	// �J�����̌����擾
	rotCamera = GetRotCamera();						//���̂��߁AUpdatePlayer()��UpdateCamera()�̌�ɒu��

	if (objectType == OBJECT_ENEMY)
	{
		rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�G�l�~�[�̌����̓J�����̉�]�Ɩ��֌W�ł���
	}

	//���[�V������Ԃ����Z�b�g
	motion.use = false;

	//���Ԃ��I����Ă��Ȃ��A��������Ԃł͂Ȃ��ꍇ�A�ړ��ł����ԂɂȂ�
	if ((IsTimeEnd() == false) && (state != FROZEN))
	{//�ړ�			���O�t���[���̉^���ʂ��c���Ă��邩��A��������
		if (useAI ? leftAI : GetKeyboardPress(leftKey) || IsButtonPress(padNo, BUTTON_LEFT) || IsButtonPress(padNo, BUTTON_LSTICK_LEFT))
		{
			motion.use = true;//���[�V������Ԃɂ���

			if (useAI ? upAI : GetKeyboardPress(upKey) || IsButtonPress(padNo, BUTTON_UP) || IsButtonPress(padNo, BUTTON_LSTICK_UP))
			{// ���O�ړ�
				move.x -= sinf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_BEAR;
				move.z -= cosf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_BEAR;

				rotDest.y = rotCamera.y + D3DX_PI * 0.75f;
			}
			else if (useAI ? downAI : GetKeyboardPress(downKey) || IsButtonPress(padNo, BUTTON_DOWN) || IsButtonPress(padNo, BUTTON_LSTICK_DOWN))
			{// ����ړ�
				move.x -= sinf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_BEAR;
				move.z -= cosf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_BEAR;

				rotDest.y = rotCamera.y + D3DX_PI * 0.25f;
			}
			else
			{// ���ړ�
				move.x -= sinf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_BEAR;
				move.z -= cosf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_BEAR;

				rotDest.y = rotCamera.y + D3DX_PI * 0.50f;
			}
		}
		else if (useAI ? rightAI : GetKeyboardPress(rightKey) || IsButtonPress(padNo, BUTTON_RIGHT) || IsButtonPress(padNo, BUTTON_LSTICK_RIGHT))
		{
			motion.use = true;//���[�V������Ԃɂ���

			if (useAI ? upAI : GetKeyboardPress(upKey) || IsButtonPress(padNo, BUTTON_UP) || IsButtonPress(padNo, BUTTON_LSTICK_UP))
			{// �E�O�ړ�
				move.x -= sinf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_BEAR;
				move.z -= cosf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_BEAR;

				rotDest.y = rotCamera.y - D3DX_PI * 0.75f;
			}
			else if (useAI ? downAI : GetKeyboardPress(downKey) || IsButtonPress(padNo, BUTTON_DOWN) || IsButtonPress(padNo, BUTTON_LSTICK_DOWN))
			{// �E��ړ�
				move.x -= sinf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_BEAR;
				move.z -= cosf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_BEAR;

				rotDest.y = rotCamera.y - D3DX_PI * 0.25f;
			}
			else
			{// �E�ړ�
				move.x -= sinf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_BEAR;
				move.z -= cosf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_BEAR;

				rotDest.y = rotCamera.y - D3DX_PI * 0.50f;
			}
		}
		else if (useAI ? upAI : GetKeyboardPress(upKey) || IsButtonPress(padNo, BUTTON_UP) || IsButtonPress(padNo, BUTTON_LSTICK_UP))
		{
			motion.use = true;//���[�V������Ԃɂ���

			// �O�ړ�
			move.x -= sinf(D3DX_PI + rotCamera.y) * VALUE_MOVE_BEAR;
			move.z -= cosf(D3DX_PI + rotCamera.y) * VALUE_MOVE_BEAR;

			rotDest.y = rotCamera.y + D3DX_PI;		// - D3DX_PI�ɂȂ�ƁA�t�̕����ɉ�]����
		}
		else if (useAI ? downAI : GetKeyboardPress(downKey) || IsButtonPress(padNo, BUTTON_DOWN) || IsButtonPress(padNo, BUTTON_LSTICK_DOWN))
		{
			motion.use = true;//���[�V������Ԃɂ���

			// ��ړ�
			move.x -= sinf(rotCamera.y) * VALUE_MOVE_BEAR;
			move.z -= cosf(rotCamera.y) * VALUE_MOVE_BEAR;

			rotDest.y = rotCamera.y;
		}
	}

	if (objectType == OBJECT_PLAYER)
	{
#ifdef _DEBUG		
		//�J���ҋ@�\
		if (GetKeyboardPress(DIK_T))
		{// �㏸
			move.y += VALUE_MOVE_BEAR;
		}
		else if (GetKeyboardPress(DIK_Y))
		{// ���~
			move.y -= VALUE_MOVE_BEAR;
		}

		if (GetKeyboardPress(DIK_U))
		{// ����]
			rotDest.y -= VALUE_ROTATE_BEAR;
		}
		else if (GetKeyboardPress(DIK_I))
		{// �E��]
			rotDest.y += VALUE_ROTATE_BEAR;
		}
#endif
	}

	LimitRot(rotDest.y);									//���ۂ͂Ȃ��Ă��������A�������߂��Ⴍ����ɂȂ�

	// �ړI�̊p�x�܂ł̍���
	fDiffRotY = rotDest.y - part[0].srt.rot.y;				//��(part[0])�����

	LimitRot(fDiffRotY);									// �d�v! �߂������ɉ�]�ł���悤��

	// ��]�ʂ��(part[0])�ɔ��f
	part[0].srt.rot.y += fDiffRotY * RATE_ROTATE_BEAR;			// �ړI�̊p�x�܂Ŋ�����������@�i�X�ړI�̊p�x�ɕω�����

	LimitRot(part[0].srt.rot.y);							//���ۂ͂Ȃ��Ă��������A�������߂��Ⴍ����ɂȂ�

	/// �ړ��ʂ��(part[0])�ɔ��f
	part[0].srt.pos.x += move.x;
	part[0].srt.pos.y += move.y;
	part[0].srt.pos.z += move.z;

}

//=============================================================================
// ���[�V�������鏈��
// motion:MOTION�\���̂̏��
//=============================================================================
void Character::Motion(MOTION& motion)
{
	int i = (int)motion.motionTime;  //���݂̃L�[�t���[���i���o�[

	//loop�ł���悤��
	if (i > motion.numKey - 2)//�ő�L�[�t���[���i���o�[�𒴂�����
	{
		motion.motionTime = 1.0f;
		i = (int)motion.motionTime;
	}

	float dt = 1.0f / motion.motionData[i].frame;//��Ԃ̊Ԋu����

	motion.motionTime += dt;

	if (motion.motionTime > motion.numKey - 1.0f)//�ő厞�Ԃ𒴂�����
	{
		motion.motionTime = motion.numKey - 1.0f;//�ő厞�Ԃɂ���
	}

	if (motion.motionTime - i > 1.0f) //�덷���C���@�z���1.0�𒴂�����
	{
		i++;//���̃L�[�t���[���ɓ���
	}

	if (motion.use == false)
	{//���[�V�������Ă��Ȃ��ꍇ�A�r���̃��[�V��������f�t�H���g��Ԃɖ߂�
		motion.motionTime = 0.0f;	//���Z�b�g
		i = (int)motion.motionTime;	//�d�v

		if (state != FROZEN)
		{
			motion.cancelTime += dt;//0�ԃL�[�t���[����time���g��
		}

		if (motion.cancelTime > 1.0f)//�ő厞�Ԃ𒴂�����
		{
			motion.cancelTime = 1.0f;//�ő�ő厞�Ԃɂ���
		}

		Interpolation(PART_MAX - 1, &part[0], motion.motionData[i].srtWork, motion.cancelTime);

	}
	else
	{//���[�V�������Ă���ꍇ
		motion.cancelTime = 0.0f;	//���Z�b�g

		Interpolation(PART_MAX - 1, &part[0], motion.motionData[i].srtWork, motion.motionData[i + 1].srtWork, motion.motionTime - i);

	}

}

//=============================================================================
// ��ԏ���
// partNum:�p�[�c�̐�
// part:�o�͂�����0�Ԗڂ̃p�[�c
// srt1:�n�_��srt
// srt2:�I�_��srt
// rate:�n�_����I�_�܂ł̔䗦	(0�`1.0)
//=============================================================================
void Interpolation(int partNum, XMODEL *part, const SRT *srt1, const SRT *srt2, float rate)
{
	for (int j = 0; j < partNum; j++)//�p�[�c�ԍ�
	{
		//// Scale
		//part[j].srt.scl.x = srt1[j].scl.x + (srt2[j].scl.x - srt1[j].scl.x) * rate;

		//part[j].srt.scl.y = srt1[j].scl.y + (srt2[j].scl.y - srt1[j].scl.y) * rate;

		//part[j].srt.scl.z = srt1[j].scl.z + (srt2[j].scl.z - srt1[j].scl.z) * rate;

		// Rotation
		part[j].srt.rot.x = srt1[j].rot.x + (srt2[j].rot.x - srt1[j].rot.x) * rate;

		//part[j].srt.rot.y = srt1[j].rot.y + (srt2[j].rot.y - srt1[j].rot.y) * rate;							

		//part[j].srt.rot.z = srt1[j].rot.z + (srt2[j].rot.z - srt1[j].rot.z) * rate;							

		// Position
		//part[j].srt.pos.x = srt1[j].pos.x + (srt2[j].pos.x - srt1[j].pos.x) * rate;							

		//part[j].srt.pos.y = srt1[j].pos.y + (srt2[j].pos.y - srt1[j].pos.y) * rate;							

		//part[j].srt.pos.z = srt1[j].pos.z + (srt2[j].pos.z - srt1[j].pos.z) * rate;							
	}

}

//=============================================================================
// ��ԏ���		(�o�͂����̃f�[�^���n�_�ɂ���ꍇ)
// partNum:�p�[�c�̐�
// part:�o�͂�����0�Ԗڂ̃p�[�c
// srt2:�I�_��srt
// rate:�n�_����I�_�܂ł̔䗦	(0�`1.0)
//=============================================================================
void Interpolation(int partNum, XMODEL *part, const SRT *srt2, float rate)
{
	for (int j = 0; j < partNum; j++)//�p�[�c�ԍ�
	{
		// Scale
		//part[j].srt.scl.x = part[j].srt.scl.x + (srt2[j].scl.x - part[j].srt.scl.x) * rate;

		//part[j].srt.scl.y = part[j].srt.scl.y + (srt2[j].scl.y - part[j].srt.scl.y) * rate;

		//part[j].srt.scl.z = part[j].srt.scl.z + (srt2[j].scl.z - part[j].srt.scl.z) * rate;

		// Rotation
		part[j].srt.rot.x = part[j].srt.rot.x + (srt2[j].rot.x - part[j].srt.rot.x) * rate;

		//part[j].srt.rot.y = part[j].srt.rot.y + (srt2[j].rot.y - part[j].srt.rot.y) * rate;							

		//part[j].srt.rot.z = part[j].srt.rot.z + (srt2[j].rot.z - part[j].srt.rot.z) * rate;							

		// Position
		//part[j].srt.pos.x = part[j].srt.pos.x + (srt2[j].pos.x - part[j].srt.pos.x) * rate;							

		//part[j].srt.pos.y = part[j].srt.pos.y + (srt2[j].pos.y - part[j].srt.pos.y) * rate;							

		//part[j].srt.pos.z = part[j].srt.pos.z + (srt2[j].pos.z - part[j].srt.pos.z) * rate;							
	}
}

//=============================================================================
// �G���A�R���W��������
//=============================================================================
void Character::AreaCollision()
{
	//�ړ��͈͂�ݒ肷��@����(part[0])�����
	if (part[0].srt.pos.x < -630.0f)
	{
		part[0].srt.pos.x = -630.0f;
	}
	if (part[0].srt.pos.x > 630.0f)
	{
		part[0].srt.pos.x = 630.0f;
	}
	//if (part[0].srt.pos.y < HEIGHT_FROMLAND_BEAR)
	//{
	//	part[0].srt.pos.y = HEIGHT_FROMLAND_BEAR;
	//}
	//if (part[0].srt.pos.y > 150.0f)
	//{
	//	part[0].srt.pos.y = 150.0f;
	//}
	if (part[0].srt.pos.z > 630.0f)
	{
		part[0].srt.pos.z = 630.0f;
	}
	if (part[0].srt.pos.z < -630.0f)
	{
		part[0].srt.pos.z = -630.0f;
	}

}

//=============================================================================
// �ړ���R�͂̏���
//=============================================================================
void Character::Drag()
{
	// �^���G�l���M�[���ꕔ�����āi��R�͂̂��߁j�ۑ�����A���̃t���[���Ɏg��(�����̎d�g��)
	//�����̕����C�R�[�����̃t���[���Ɋl���̉^���G�l���M�[�̏ꍇ�A���x���ő�(7.8f)�ɂȂ��āA���������^���ɂȂ�
	move.x = move.x * (1 - RATE_MOVE_BEAR);
	move.y = move.y * (1 - RATE_MOVE_BEAR);
	move.z = move.z * (1 - RATE_MOVE_BEAR);

}

//=============================================================================
// ���̃G�t�F�N�g
//=============================================================================
void Character::Jet()
{
	D3DXVECTOR3 pos;		//��Ɨp

	//�ړ�������1���傫���ꍇ�A���̃G�t�F�N�g���o��
	if ((move.x * move.x
		+ move.y * move.y
		+ move.z * move.z) > 1.0f)
	{		
		//��(part[0])�����
		pos.x = part[0].srt.pos.x + sinf(part[0].srt.rot.y) * fRadius;	//�����̕ӂ�ɐݒ�
		pos.y = part[0].srt.pos.y - 19.4f;								//�����̂Ƃ���ɐݒ�
		pos.z = part[0].srt.pos.z + cosf(part[0].srt.rot.y) * fRadius;	//�����̕ӂ�ɐݒ�

		// �G�t�F�N�g�̐ݒ�
		if (objectType == OBJECT_PLAYER)
		{
			SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.85f, 0.15f, 0.0f, 0.50f), 14.0f, 14.0f, 20);	//��
			SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.15f, 0.75f, 0.0f, 0.30f), 10.0f, 10.0f, 20);	//��
			SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.0f, 0.10f, 0.0f, 0.15f), 5.0f, 5.0f, 20);		//��
		}
		if (objectType == OBJECT_ENEMY)
		{
			SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.85f, 0.05f, 0.65f, 0.50f), 14.0f, 14.0f, 20);	//��
			SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.65f, 0.85f, 0.05f, 0.30f), 10.0f, 10.0f, 20);	//��
			SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.45f, 0.45f, 0.05f, 0.15f), 5.0f, 5.0f, 20);		//��
		}
	}

}

//=============================================================================
// �A�C�e���Ƃ̓����蔻��
//=============================================================================
void Character::ItemCollision()
{
	ITEM *pItem;

	// �A�C�e�����擾
	pItem = GetItem();

	if (!IsTimeEnd())
	{//���Ԃ��I����Ă��Ȃ�����A�A�C�e�����擾�ł���
		for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
		{
			if (pItem->use == true)
			{
				float fLength;		//���g�ƃA�C�e���̋���

				//�o�E���f�B���O�T�[�N��BC //��(part[0])�����
				fLength = (part[0].srt.pos.x - pItem->srt.pos.x) * (part[0].srt.pos.x - pItem->srt.pos.x)
					+ (part[0].srt.pos.y - pItem->srt.pos.y) * (part[0].srt.pos.y - pItem->srt.pos.y)
					+ (part[0].srt.pos.z - pItem->srt.pos.z) * (part[0].srt.pos.z - pItem->srt.pos.z);

				if (fLength < (fRadius + pItem->fRadius) * (fRadius + pItem->fRadius))
				{//�擾�ł���͈͓��ł����
					if ((holdItem == ITEMTYPE_ICEBLOCK) && (pItem->nType == ITEMTYPE_ICEBLOCK))
					{//�A�C�X�u���b�N�������Ă���ꍇ�A���̃A�C�X�u���b�N�͎擾�ł��Ȃ�

					}
					else
					{
						if (pItem->nType == ITEMTYPE_ICEBLOCK)
						{
							holdItem = ITEMTYPE_ICEBLOCK;

							// �����A�C�e�����E�����ʉ����Đ�
							PlaySound(SOUND_LABEL_SE_GETICEBLOCK, false, true);
						
						}
						else if (pItem->nType == ITEMTYPE_COIN)
						{
							// �X�R�A���Z
							ChangeScore(objectType, 100);

							// �R�C�����E�����ʉ����Đ�
							PlaySound(SOUND_LABEL_SE_COIN, false, true);
						}

						// �A�C�e������
						DeleteItem(nCntItem);

						break;		//1�t���[���ɁA�P�����擾�ł��Ȃ�
					}
					
				}
			}
		}
	}

}

//=============================================================================
//�����A�C�e�����g��
//=============================================================================
void Character::UseIceblock()
{
	int key;					//�L�[�{�[�h�̃R���g���[���L�[
	int padNo;					//�R���g���[���[�ԍ�
	Character* target;			//�_���ڕW

	if (objectType == OBJECT_PLAYER)
	{
		key = DIK_SPACE;
		padNo = 0;
		target = GetEnemy();
	}
	else
	{
		key = DIK_NUMPAD1;
		padNo = 1;
		target = GetPlayer();
	}

	//���Ԃ��I����Ă��Ȃ��A��������Ԃł͂Ȃ��A�������A�C�e���������Ă���ꍇ�A�����A�C�e�����g�p�\�ɂȂ�
	if ((IsTimeEnd() == false) && (state != FROZEN) && (holdItem == ITEMTYPE_ICEBLOCK))
	{
		if ((useAI) || (GetKeyboardTrigger(key) || IsButtonTrigger(padNo, BUTTON_CIRCLE)))
		{//AI���[�h�ł͓����A�C�e�����E������A�����g��	
			Freeze(target);
		}
	}

}

//=============================================================================
// �����A�C�e���̌���
//=============================================================================
void Character::Freeze(Character* target)
{
	if (target->state != FROZEN)		//���肪������Ԃł͂Ȃ��ꍇ
	{
		target->state = FROZEN;			//����𓀌���Ԃɂ�����
		target->frozenTime = 180;		//3�b��
		holdItem = ITEMTYPE_NULL;		//�����̓����A�C�e�������Ղ����

		PlaySound(SOUND_LABEL_SE_USEICEBLOCK, false, true);		// �����A�C�e�����g�������Đ�
	}
}

//=============================================================================
//������ԂɂȂ������̏���
//=============================================================================
void Character::Frozen()
{
	if (state == FROZEN)
	{
		if (frozenTime > 0)
		{
			frozenTime--;			//������Ԃ̎c�莞�Ԃ��J�E���g�_�E��
			part[6].use = true;		//�g�ɓZ���A�C�X�u���b�N��\������
		}
		else
		{
			state = NORMAL;			//������Ԃ�����
			part[6].use = false;	//�g�ɓZ���A�C�X�u���b�N��������
		}
	}
}

//=============================================================================
//�v���C���[�A�G�l�~�[�̍X�V�����̂܂Ƃ�
//=============================================================================
void Character::UpdateCharacter()
{
	AIControl();

	Movement();

	//�������[�V��������
	Motion(motion);

	AreaCollision();

	Drag();

	UpdateShadow(nIdxShadow, part[0].srt.pos, HEIGHT_FROMLAND_BEAR);

	Jet();

	ItemCollision();

	UseIceblock();

	Frozen();

}
