//=============================================================================
//
// ���b�V���n�ʂ̏��� [meshfield.cpp]
// Author : ���p�j
//
//=============================================================================
#include "meshfield.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_FILENAME	"data/TEXTURE/ice.bm"											// �ǂݍ��ރe�N�X�`���t�@�C����

#define	POS_FIELD			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))									// ���b�V���t�B�[���h�̒��S���W
#define	ROT_FIELD			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))									// ���b�V���t�B�[���h�̉�]��
#define	NUM_BLOCK_H			(16)															//�������̃u���b�N�̐�
#define	NUM_BLOCK_V			(16)															//�c�����̃u���b�N�̐�
#define	SIZE_BLOCK_H		(80.0f)															//�������̃u���b�N�̃T�C�Y
#define	SIZE_BLOCK_V		(80.0f)															//�c�����̃u���b�N�̃T�C�Y

#define	NUM_VERTEX_FIELD	((NUM_BLOCK_H + 1) * (NUM_BLOCK_V + 1))							// �����_��
#define	NUM_VERTEXINDEX		((NUM_BLOCK_H + 1) * 2 * NUM_BLOCK_V + (NUM_BLOCK_V - 1) * 2)	// ���C���f�b�N�X�� (���_�`�揇�Ԃ��瓱���o���@��)
#define	NUM_POLYGON_FIELD	(NUM_VERTEXINDEX - 2)											// ���|���S����(�ޏk�|���S�����܂ށj

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9			g_pD3DTextureField;			// �e�N�X�`���ǂݍ��ޏꏊ
LPDIRECT3DVERTEXBUFFER9		g_pD3DVtxBuffField;			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9		g_pD3DIdxBuffField;			// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

HRESULT InitMeshField()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_FILENAME,		// �t�@�C���̖��O
								&g_pD3DTextureField);	// �ǂݍ��ރ������[

	//���_�o�b�t�@�̍쐬
	MakeVertexMesh(pDevice, g_pD3DVtxBuffField, NUM_VERTEX_FIELD, NUM_BLOCK_H, NUM_BLOCK_V,
										SIZE_BLOCK_H, SIZE_BLOCK_V, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAPPINGTYPE_ONE);

	//�C���f�b�N�X�o�b�t�@�̍쐬
	MakeIndexMesh(pDevice, g_pD3DIdxBuffField, NUM_VERTEXINDEX, NUM_BLOCK_H, NUM_BLOCK_V);

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void UninitMeshField(void)
{
	SAFE_RELEASE(g_pD3DTextureField);
	SAFE_RELEASE(g_pD3DVtxBuffField);
	SAFE_RELEASE(g_pD3DIdxBuffField);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshField(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	DrawPolygonMesh(pDevice, g_pD3DVtxBuffField, g_pD3DIdxBuffField,
		POS_FIELD, ROT_FIELD, g_pD3DTextureField,
		NUM_VERTEX_FIELD, NUM_POLYGON_FIELD);

	// ���C�e�B���O��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}