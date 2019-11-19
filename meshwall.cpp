//=============================================================================
//
// ���b�V���ǂ̏��� [meshwall.cpp]
// Author : ���p�j
//
//=============================================================================
#include "meshwall.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_MESHWALL		(128)							// �ǂ̑���
#define	TEXTURE_FILENAME	"data/TEXTURE/ice2.png"			// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

HRESULT MakeMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
						int numBlockH, int numBlockV, float sizeBlockH, float sizeBlockV, D3DXCOLOR col, MAPPINGTYPE type);

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

struct MESH_WALL
{
	LPDIRECT3DVERTEXBUFFER9 pD3DVtxBuff;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	pD3DIdxBuff;		// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

	D3DXVECTOR3 pos;							// �|���S���\���ʒu�̒��S���W
	D3DXVECTOR3 rot;							// �|���S���̉�]��

	int numVertex;								// �����_��	
	int numVertexIndex;							// ���C���f�b�N�X��
	int numPolygon;								// ���|���S����

};

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureMeshWall = NULL;		// �e�N�X�`���ǂݍ��ޏꏊ

MESH_WALL			g_aMeshWall[MAX_MESHWALL];			// ���b�V���ǃ��[�N
int					g_nNumMeshWall;						// ���b�V���ǂ̐�

//=============================================================================
// ����������
//=============================================================================
HRESULT InitMeshWall()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nNumMeshWall = 0;

	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
							TEXTURE_FILENAME,			// �t�@�C���̖��O
							&g_pD3DTextureMeshWall);	// �ǂݍ��ރ������[
 
	// �ǂ̏�����	�����ԗv���ӁA��鏇�� �� �`�揇��
	//�k�ǂ̒n��
	MakeMeshWall(D3DXVECTOR3(0.0f, 0.0f, 1280.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									48, 16, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAPPINGTYPE_ALL);
	//��ǂ̒n��
	MakeMeshWall(D3DXVECTOR3(0.0f, 0.0f, -1280.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									48, 16, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAPPINGTYPE_ALL);
	//���ǂ̒n��
	MakeMeshWall(D3DXVECTOR3(-1280.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									16, 16, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAPPINGTYPE_ALL);
	//���ǂ̒n��
	MakeMeshWall(D3DXVECTOR3(1280.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									16, 16, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAPPINGTYPE_ALL);

	//�k��
	MakeMeshWall(D3DXVECTOR3(0.0f, 0.0f, 640.0f), D3DXVECTOR3(-D3DX_PI * 0.50f, 0.0f, 0.0f),
									16, 4, 80.0f, 80.0f,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAPPINGTYPE_ALL);
	//���
	MakeMeshWall(D3DXVECTOR3(0.0f, 0.0f, -640.0f), D3DXVECTOR3(D3DX_PI * 0.50f, 0.0f, 0.0f),
									16, 4, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAPPINGTYPE_ALL);
	//����
	MakeMeshWall(D3DXVECTOR3(-640.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI * 0.50f, -D3DX_PI * 0.50f, 0.0f),
									16, 4, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAPPINGTYPE_ALL);
	//����
	MakeMeshWall(D3DXVECTOR3(640.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI * 0.50f, D3DX_PI * 0.50f, 0.0f),
									16, 4, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAPPINGTYPE_ALL);

	//�k�ǂ̔w��
	MakeMeshWall(D3DXVECTOR3(0.0f, 0.0f, -640.0f), D3DXVECTOR3(-D3DX_PI * 0.50f, 0.0f, 0.0f),
		16, 4, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), MAPPINGTYPE_ALL);
	//��ǂ̔w��
	MakeMeshWall(D3DXVECTOR3(0.0f, 0.0f, 640.0f), D3DXVECTOR3(D3DX_PI * 0.50f, 0.0f, 0.0f),
		16, 4, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), MAPPINGTYPE_ALL);
	//���ǂ̔w��
	MakeMeshWall(D3DXVECTOR3(640.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI * 0.50f, -D3DX_PI * 0.50f, 0.0f),
		16, 4, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), MAPPINGTYPE_ALL);
	//���ǂ̔w��
	MakeMeshWall(D3DXVECTOR3(-640.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI * 0.50f, D3DX_PI * 0.50f, 0.0f),
		16, 4, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), MAPPINGTYPE_ALL);


	//�k�ǂ̉���
	MakeMeshWall(D3DXVECTOR3(0.0f, 160.0f, 1280.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									48, 16, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), MAPPINGTYPE_ALL);
	//��ǂ̉���
	MakeMeshWall(D3DXVECTOR3(0.0f, 160.0f, -1280.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									48, 16, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), MAPPINGTYPE_ALL);
	//���ǂ̉���
	MakeMeshWall(D3DXVECTOR3(-1280.0f, 160.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									16, 16, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), MAPPINGTYPE_ALL);
	//���ǂ̉���
	MakeMeshWall(D3DXVECTOR3(1280.0f, 160.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									16, 16, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), MAPPINGTYPE_ALL);

	return S_OK;
}

//=============================================================================
// �ǂ̍쐬
// pos:�|���S���\���ʒu�̒��S���W�Arot:�|���S���̉�]��
// numVertex: ���_�̐�
// numBlockH�F�������̃u���b�N�̐��AnumBlockV:�c�����̃u���b�N�̐�
// blockSizeH:�������̃u���b�N�̃T�C�Y�AblockSizeV:�c�����̃u���b�N�̃T�C�Y
// type:�e�N�X�`���\�̓\���
//=============================================================================
HRESULT MakeMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
					int numBlockH, int numBlockV, float sizeBlockH, float sizeBlockV, D3DXCOLOR col, MAPPINGTYPE type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	MESH_WALL *pMesh;

	if (g_nNumMeshWall >= MAX_MESHWALL)
	{
		return E_FAIL;
	}

	pMesh = &g_aMeshWall[g_nNumMeshWall];

	g_nNumMeshWall++;

	pMesh->pos = pos;
	pMesh->rot = rot;

	pMesh->numVertex = (numBlockH + 1) * (numBlockV + 1);
	pMesh->numVertexIndex = (numBlockH + 1) * 2 * numBlockV + (numBlockV - 1) * 2;
	pMesh->numPolygon = pMesh->numVertexIndex - 2;

	//���_�o�b�t�@�̍쐬
	MakeVertexMesh(pDevice, pMesh->pD3DVtxBuff, pMesh->numPolygon, numBlockH, numBlockV, sizeBlockH, sizeBlockV, col, type);

	//�C���f�b�N�X�o�b�t�@�̍쐬
	MakeIndexMesh(pDevice, pMesh->pD3DIdxBuff, pMesh->numVertexIndex, numBlockH, numBlockV);


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshWall(void)
{
	for(int i = 0; i < g_nNumMeshWall; i++)
	{
		SAFE_RELEASE(g_aMeshWall[i].pD3DVtxBuff);
		SAFE_RELEASE(g_aMeshWall[i].pD3DIdxBuff);
	}

	SAFE_RELEASE(g_pD3DTextureMeshWall);

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshWall(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	MESH_WALL *pMesh;

	// ���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for(int i = 0; i < g_nNumMeshWall; i++)
	{
		pMesh = &g_aMeshWall[i];

		DrawPolygonMesh(pDevice, pMesh->pD3DVtxBuff, pMesh->pD3DIdxBuff,
			pMesh->pos, pMesh->rot, g_pD3DTextureMeshWall,
			pMesh->numVertex, pMesh->numPolygon);
	}

	// ���C�e�B���O��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

