//=============================================================================
//
// �A�C�e������ [item.cpp]
// Author : ���p�j
//
//=============================================================================
#include "item.h"
#include "shadow.h"
#include "input.h"
#include "player.h"
#include "enemy.h"
#include "timer.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VALUE_ROTATE_ITEM		(D3DX_PI * 0.025f)			// ��]���x
#define	ITEM_RADIUS				(10.0f)						// ���a

#define	ITEMLOGO_SIZE_X			(65.0f)							// ���C�t�̐����̕�
#define	ITEMLOGO_SIZE_Y			(65.0f)							// ���C�t�̐����̍���

#define	ITEMLOGO_POS_X			(20.0f)							// ���C�t�̕\����ʒu�w���W
#define	ITEMLOGO_POS_Y			(95.0f)							// ���C�t�̕\����ʒu�x���W

#define	DROP_TIME				(420)							// �����A�C�e���̊Ԋu���ԁ@1�b��60
#define	DROP_HIGHT				(1800.0f)						// �����A�C�e���̏�������
#define	DROP_SPEED				(15.0f)							// �����A�C�e���̗������x


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexItemLogo(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureItem[ITEMTYPE_MAX];	// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pMeshItem[ITEMTYPE_MAX];			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXMatBuffItem[ITEMTYPE_MAX];	// ���b�V���̃}�e���A�������i�[
DWORD				g_aNumMatItem[ITEMTYPE_MAX];			// �������̑���

D3DXMATRIX			g_mtxWorldItem;				// ���[���h�}�g���b�N�X

ITEM				g_aItem[MAX_ITEM];			// �A�C�e�����[�N

bool g_dropItem;//�A�C�e���������邩

bool g_dropReady;//��������A�C�e���͂�������������

int g_itemIndex;//��������A�C�e���̃C���f�N�X

LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffItemLogo = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^



const char *c_aFileNameItem[ITEMTYPE_MAX] =
{
	"data/MODEL/coin.x",			// �R�C��
	"data/MODEL/iceBlock.x",		// �A�C�X�u���b�N

};

//=============================================================================
// ����������
//=============================================================================
HRESULT InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	MakeVertexItemLogo(pDevice);

	for(int nCntItemType = 0; nCntItemType < ITEMTYPE_MAX; nCntItemType++)
	{
		g_pD3DTextureItem[nCntItemType] = NULL;
		g_pMeshItem[nCntItemType] = NULL;
		g_pD3DXMatBuffItem[nCntItemType] = NULL;

		// X�t�@�C���̓ǂݍ���
		if(FAILED(D3DXLoadMeshFromX(c_aFileNameItem[nCntItemType],
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_pD3DXMatBuffItem[nCntItemType],
									NULL,
									&g_aNumMatItem[nCntItemType],
									&g_pMeshItem[nCntItemType])))
		{
			//return E_FAIL;//�R�C�������̃X�e�[�W�Ɏc��bug
		}

#if 0
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,									// �f�o�C�X�ւ̃|�C���^
									TEXTURE_ITEM,						// �t�@�C���̖��O
									&g_pD3DTextureItem[nCntItemType]);	// �ǂݍ��ރ������[
#endif
	}

	for(int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].fRadius = 0.0f;
		g_aItem[nCntItem].nIdxShadow = -1;
		g_aItem[nCntItem].nType = ITEMTYPE_COIN;
		g_aItem[nCntItem].bUse = false;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitItem(void)
{
	for(int nCntItemType = 0; nCntItemType < ITEMTYPE_MAX; nCntItemType++)
	{
		SAFE_RELEASE(g_pD3DTextureItem[nCntItemType]);
		SAFE_RELEASE(g_pMeshItem[nCntItemType]);
		SAFE_RELEASE(g_pD3DXMatBuffItem[nCntItemType]);

	}

	SAFE_RELEASE(g_pD3DVtxBuffItemLogo);

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateItem(void)
{

#ifdef _DEBUG
	if (GetKeyboardPress(DIK_3))
	{
		g_dropItem = true;
	}
#endif

	if ((GetTimer() % DROP_TIME == 0)&&(GetTimer() != 0))
	{
		g_dropItem = true;
	}

	
	DropItem();
	


	for(int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if(g_aItem[nCntItem].bUse)
		{
			g_aItem[nCntItem].rot.y += VALUE_ROTATE_ITEM;//���t���[������]4.5�x
			if(g_aItem[nCntItem].rot.y > D3DX_PI)
			{
				g_aItem[nCntItem].rot.y -= D3DX_PI * 2.0f;
			}

			// �e�̈ʒu�ݒ�
			SetPositionShadow(g_aItem[nCntItem].nIdxShadow, D3DXVECTOR3(g_aItem[nCntItem].pos.x, 0.1f, g_aItem[nCntItem].pos.z));

			float fSizeX = 20.0f + (g_aItem[nCntItem].pos.y - 10.0f) * 0.05f;
			if(fSizeX < 20.0f)
			{
				fSizeX = 20.0f;
			}
			float fSizeY = 20.0f + (g_aItem[nCntItem].pos.y - 10.0f) * 0.05f;
			if(fSizeY < 20.0f)
			{
				fSizeY = 20.0f;
			}

			SetVertexShadow(g_aItem[nCntItem].nIdxShadow, fSizeX, fSizeY);

			float colA = (200.0f - (g_aItem[nCntItem].pos.y - 10.0f)) / 400.0f;
			if(colA < 0.0f)
			{
				colA = 0.0f;
			}
			SetColorShadow(g_aItem[nCntItem].nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));
		}
	}


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;

	D3DMATERIAL9 matDef;
	pDevice->GetMaterial(&matDef);

	for(int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if(g_aItem[nCntItem].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldItem);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aItem[nCntItem].rot.y, g_aItem[nCntItem].rot.x, g_aItem[nCntItem].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldItem, &g_mtxWorldItem, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y, g_aItem[nCntItem].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldItem, &g_mtxWorldItem, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldItem);

			D3DXMATERIAL *pD3DXMat = (D3DXMATERIAL*)g_pD3DXMatBuffItem[g_aItem[nCntItem].nType]->GetBufferPointer();

			for(int nCntMat = 0; nCntMat < (int)g_aNumMatItem[g_aItem[nCntItem].nType]; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);//�|�C���^�[���z��ɂȂ�

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pD3DTextureItem[g_aItem[nCntItem].nType]);

				// �`��
				g_pMeshItem[g_aItem[nCntItem].nType]->DrawSubset(nCntMat);
			}
		}
	}
	
	pDevice->SetMaterial(&matDef);

	//�A�C�e��UI�̕`��
	{
		//�v���C���[�̕�
		if (GetPlayer()->holdItem != ITEMTYPE_COIN)
		{
			if (GetPlayer()->holdItem == ITEMTYPE_ICEBLOCK)
			{
				//���_�o�b�t�@�̒��g�𖄂߂�
				VERTEX_2D *pVtx;

				// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
				g_pD3DVtxBuffItemLogo->Lock(0, 0, (void**)&pVtx, 0);

				// ���_���W�̐ݒ�
				pVtx[0].vtx = D3DXVECTOR3(ITEMLOGO_POS_X, ITEMLOGO_POS_Y, 0.0f);
				pVtx[1].vtx = D3DXVECTOR3(ITEMLOGO_POS_X + ITEMLOGO_SIZE_X, ITEMLOGO_POS_Y, 0.0f);
				pVtx[2].vtx = D3DXVECTOR3(ITEMLOGO_POS_X, ITEMLOGO_POS_Y + ITEMLOGO_SIZE_Y, 0.0f);
				pVtx[3].vtx = D3DXVECTOR3(ITEMLOGO_POS_X + ITEMLOGO_SIZE_X, ITEMLOGO_POS_Y + ITEMLOGO_SIZE_Y, 0.0f);

				// ���_�f�[�^���A�����b�N����
				g_pD3DVtxBuffItemLogo->Unlock();


				//ItemLogo�̕`��
				// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
				pDevice->SetStreamSource(0, g_pD3DVtxBuffItemLogo, 0, sizeof(VERTEX_2D));

				// ���_�t�H�[�}�b�g�̐ݒ�
				pDevice->SetFVF(FVF_VERTEX_2D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);

				// �|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
			}
		}

		//�G�l�~�[�̕�
		if (GetEnemy()->holdItem != ITEMTYPE_COIN)
		{
			if (GetEnemy()->holdItem == ITEMTYPE_ICEBLOCK)
			{
				//���_�o�b�t�@�̒��g�𖄂߂�
				VERTEX_2D *pVtx;

				// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
				g_pD3DVtxBuffItemLogo->Lock(0, 0, (void**)&pVtx, 0);

				// ���_���W�̐ݒ�
				pVtx[0].vtx = D3DXVECTOR3(SCREEN_WIDTH - ITEMLOGO_POS_X - ITEMLOGO_SIZE_X, ITEMLOGO_POS_Y, 0.0f);
				pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH - ITEMLOGO_POS_X, ITEMLOGO_POS_Y, 0.0f);
				pVtx[2].vtx = D3DXVECTOR3(SCREEN_WIDTH - ITEMLOGO_POS_X - ITEMLOGO_SIZE_X, ITEMLOGO_POS_Y + ITEMLOGO_SIZE_Y, 0.0f);
				pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH - ITEMLOGO_POS_X, ITEMLOGO_POS_Y + ITEMLOGO_SIZE_Y, 0.0f);

				// ���_�f�[�^���A�����b�N����
				g_pD3DVtxBuffItemLogo->Unlock();


				//ItemLogo�̕`��
				// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
				pDevice->SetStreamSource(0, g_pD3DVtxBuffItemLogo, 0, sizeof(VERTEX_2D));

				// ���_�t�H�[�}�b�g�̐ݒ�
				pDevice->SetFVF(FVF_VERTEX_2D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);

				// �|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
			}
		}
	}
}

//=============================================================================
// �A�C�e���̐ݒ�
//=============================================================================
int SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType,bool shadow)
{
	int itemIndex = -1;
	for(int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if(!g_aItem[nCntItem].bUse)
		{
			g_aItem[nCntItem].pos = pos;
			g_aItem[nCntItem].rot = rot;
			g_aItem[nCntItem].fRadius = ITEM_RADIUS;
			g_aItem[nCntItem].nType = nType;
			g_aItem[nCntItem].bUse = true;

			if (shadow)
			{
				// �e�̐ݒ�
				g_aItem[nCntItem].nIdxShadow = SetShadow(g_aItem[nCntItem].pos, g_aItem[nCntItem].fRadius * 2.0f, g_aItem[nCntItem].fRadius * 2.0f);
			}

			itemIndex = nCntItem;
			break;
		}
	}
	return itemIndex;
}

//=============================================================================
// �A�C�e���̍폜
//=============================================================================
void DeleteItem(int nIdxItem)
{
	if(nIdxItem >= 0 && nIdxItem < MAX_ITEM)
	{
		DeleteShadow(g_aItem[nIdxItem].nIdxShadow);
		g_aItem[nIdxItem].bUse = false;
	}
}

//=============================================================================
// �A�C�e���̎擾
//=============================================================================
ITEM *GetItem(void)
{
	return &g_aItem[0];
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexItemLogo(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,							// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,								// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,							// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffItemLogo,							// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))										// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffItemLogo->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntPlace = 0; nCntPlace < 1; nCntPlace++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(ITEMLOGO_POS_X, ITEMLOGO_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(ITEMLOGO_POS_X + ITEMLOGO_SIZE_X, ITEMLOGO_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(ITEMLOGO_POS_X, ITEMLOGO_POS_Y + ITEMLOGO_SIZE_Y, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(ITEMLOGO_POS_X + ITEMLOGO_SIZE_X, ITEMLOGO_POS_Y + ITEMLOGO_SIZE_Y, 0.0f);

			// rhw�̐ݒ�
			pVtx[0].rhw =
				pVtx[1].rhw =
				pVtx[2].rhw =
				pVtx[3].rhw = 1.0f;

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffItemLogo->Unlock();
	}

	return S_OK;
}


void Freeze(OBJECT target)
{
	if (target == OBJECT_ENEMY)
	{
		if (GetPlayer()->holdItem == ITEMTYPE_ICEBLOCK)
		{
			if (GetEnemy()->state == NORMAL)
			{
				GetEnemy()->state = FROZEN;
				GetEnemy()->stateTime = 180;//3�b

				GetPlayer()->holdItem = ITEMTYPE_COIN;
			}

		}
	}
	else if (target == OBJECT_PLAYER)
	{
		if (GetEnemy()->holdItem == ITEMTYPE_ICEBLOCK)
		{
			if (GetPlayer()->state == NORMAL)
			{
				GetPlayer()->state = FROZEN;
				GetPlayer()->stateTime = 180;//3�b

				GetEnemy()->holdItem = ITEMTYPE_COIN;
			}

		}
	}
	
}

void DropItem()
{

	if (g_dropItem)
	{
		if (!g_dropReady)
		{
			float fPosX, fPosY, fPosZ;

			fPosX = (float)(rand() % 12000) / 10.0f - 600.0f;//-600.0f~600.0f
			fPosY = DROP_HIGHT;//�A�C�e���̓�������
			fPosZ = (float)(rand() % 12000) / 10.0f - 600.0f;
			g_itemIndex = SetItem(D3DXVECTOR3(fPosX, fPosY, fPosZ), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_ICEBLOCK, false);
			g_dropReady = true;
		}
		else
		{
			if (g_itemIndex != -1)
			{
				(GetItem() + g_itemIndex)->pos.y -= DROP_SPEED;

				if ((GetItem() + g_itemIndex)->pos.y <= 15.0f)
				{//�A�C�e���̒��n����
					(GetItem() + g_itemIndex)->pos.y = 15.0f;

					g_dropItem = false;
					g_dropReady = false;
				}
			}
		}
	}

}

