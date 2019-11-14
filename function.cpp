//=============================================================================
//
// ���ʂ̋@�\ [function.cpp]
// Author : ���p�j
//
//=============================================================================
#include "function.h"

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
void Interpolation(int partNum, PART *part, const SRT *srt1, const SRT *srt2, float rate);
void Interpolation(int partNum, PART *part, const SRT *srt2, float rate);

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
// ���[�V�������鏈��
// user:�g�p��
// motion:MOTION�\���̂̏��
//=============================================================================
void Motion(PLAYER& user,MOTION& motion)
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

		if (user.state != FROZEN)
		{
			motion.cancelTime += dt;//0�ԃL�[�t���[����time���g��
		}

		if (motion.cancelTime > 1.0f)//�ő厞�Ԃ𒴂�����
		{
			motion.cancelTime = 1.0f;//�ő�ő厞�Ԃɂ���
		}

		Interpolation(PART_MAX_PLAYER - 1, &user.part[0], motion.motionData[i].srtWork, motion.cancelTime);

	}
	else
	{//���[�V�������Ă���ꍇ
		motion.cancelTime = 0.0f;	//���Z�b�g

		Interpolation(PART_MAX_PLAYER - 1, &user.part[0], motion.motionData[i].srtWork, motion.motionData[i + 1].srtWork, motion.motionTime - i);

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
void Interpolation(int partNum, PART *part, const SRT *srt1, const SRT *srt2, float rate)
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
void Interpolation(int partNum, PART *part, const SRT *srt2, float rate)
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
// �e�q�֌W�����p�[�c�̕`��
// player:�Ώ�
// pD3DTexture:�e�N�X�`���\
// numPart:�p�[�c��
//=============================================================================
void DrawPart(LPDIRECT3DDEVICE9 pDevice,PLAYER& player, LPDIRECT3DTEXTURE9 pD3DTexture, int numPart)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;
	D3DXMATERIAL *pD3DXMat;			// �}�e���A�����ɑ΂���|�C���^

	D3DMATERIAL9 matDef;			// �f�t�H���g�̃}�e���A��
	pDevice->GetMaterial(&matDef);	// �f�t�H���g�̃}�e���A�����擾

	for (int i = 0; i < numPart; i++)//�p�[�c�ԍ�
	{
		if (player.part[i].use)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, player.part[i].srt.scl.x,
				player.part[i].srt.scl.y,
				player.part[i].srt.scl.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, player.part[i].srt.rot.y,
				player.part[i].srt.rot.x,
				player.part[i].srt.rot.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, player.part[i].srt.pos.x,
				player.part[i].srt.pos.y,
				player.part[i].srt.pos.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

			//�e�����݂���ꍇ�͐e�̃��[���h�}�g���N�X������
			if (player.part[i].parent)
			{
				D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &player.part[i].parent->mtxWorld);
			}

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

			//���[���h�}�g���N�X��ۑ�
			player.part[i].mtxWorld = mtxWorld;

			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)player.part[i].pMatBuff->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)player.part[i].nNumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, pD3DTexture);		//���e�N�X�`���\���Ȃ��Ă��K�v�B�������Ȃ��ƁA���̑O�̃e�N�X�`���\���\���Ă��܂�

				// �`��
				player.part[i].pMesh->DrawSubset(nCntMat);
			}
		}
	}

	pDevice->SetMaterial(&matDef);// �}�e���A�����f�t�H���g�ɖ߂�

}