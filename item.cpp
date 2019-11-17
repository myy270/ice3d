//=============================================================================
//
// �R�C���ƃA�C�X�u���b�N�̏����A�����A�C�e��UI�̏��� [item.cpp]	
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
#define	ITEM_RADIUS				(10.0f)										// �A�C�e���̔��a	//�e�̑傫���A�A�C�e���Ƃ̓����鋗�� �Ɗ֌W����

#define	ITEMUI_WIDTH			FIT_WIDTH(65.0f)							// �A�C�e��UI�̕�
#define	ITEMUI_HEIGHT			FIT_HEIGHT(65.0f)							// �A�C�e��UI�̍���

#define	ITEMUI_POS_X			FIT_WIDTH(20.0f)							// ���̃A�C�e��UI�̕\����ʒu�w���W
#define	ITEMUI_POS_Y			FIT_HEIGHT(95.0f)							// ���̃A�C�e��UI�̕\����ʒu�x���W

#define	ITEMUI_POS_X2			SCREEN_WIDTH - ITEMUI_POS_X - ITEMUI_WIDTH	// �E�̃A�C�e��UI�̕\����ʒu�w���W

#define	DROP_TIME				(420)										// �A�C�e���̗����Ԋu���ԁ@�P�ʁF�t���[��
#define	DROP_HIGHT				(1800.0f)									// �����A�C�e���̏�������
#define	DROP_SPEED				(15.0f)										// �����A�C�e���̗������x

#define	HEIGHT_FROMLAND_ITEM	(15.0f)										// �A�C�e���̑؋󍂂�
#define	NUM_COIN				(99)										// �R�C���̐�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

int SetItem(D3DXVECTOR3 pos, ITEMTYPE nType = ITEMTYPE_COIN, bool shadowUsable = true);
void DropItem();

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH			g_pMeshItem[ITEMTYPE_MAX];				// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^	[0]:�R�C���@[1]:�A�C�X�u���b�N
LPD3DXBUFFER		g_pD3DXMatBuffItem[ITEMTYPE_MAX];		// ���b�V���̃}�e���A�������i�[
DWORD				g_aNumMatItem[ITEMTYPE_MAX];			// �}�e���A�����̑���

ITEM				g_aItem[MAX_ITEM];			// �A�C�e�����[�N

bool g_isDropItem;		//�A�C�e���������邩

bool g_isReadyToDrop;	//��������A�C�e���͂�������������

int g_dropItemIndex;	//��������A�C�e���̃C���f�N�X

LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffItemUI = NULL;		// ���̃A�C�e��UI�̒��_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffItemUI2 = NULL;	// �E�̃A�C�e��UI�̒��_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

//�A�C�e����X�t�@�C���̃p�X
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

	//UI�̒��_���쐬
	MakeVertex(pDevice, FVF_VERTEX_2D, g_pD3DVtxBuffItemUI, D3DXVECTOR3(ITEMUI_POS_X, ITEMUI_POS_Y, 0.0f), ITEMUI_WIDTH, ITEMUI_HEIGHT);
	SetVtxDataCor(g_pD3DVtxBuffItemUI, FVF_VERTEX_2D, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));		//�V�A���F�ɂ���

	MakeVertex(pDevice, FVF_VERTEX_2D, g_pD3DVtxBuffItemUI2, D3DXVECTOR3(ITEMUI_POS_X2, ITEMUI_POS_Y, 0.0f), ITEMUI_WIDTH, ITEMUI_HEIGHT);
	SetVtxDataCor(g_pD3DVtxBuffItemUI2, FVF_VERTEX_2D, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));	//�V�A���F�ɂ���

	// X�t�@�C���̓ǂݍ���
	for(int nCntItemType = 0; nCntItemType < ITEMTYPE_MAX; nCntItemType++)
	{	
		if(FAILED(D3DXLoadMeshFromX(c_aFileNameItem[nCntItemType],
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_pD3DXMatBuffItem[nCntItemType],
									NULL,
									&g_aNumMatItem[nCntItemType],
									&g_pMeshItem[nCntItemType])))
		{
			return E_FAIL;
		}
	}

	//ITEM�\���̂̏�����
	for(int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aItem[nCntItem].srt.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].parent = NULL;
		g_aItem[nCntItem].use = false;

		g_aItem[nCntItem].fRadius = ITEM_RADIUS;
		g_aItem[nCntItem].nIdxShadow = -1;
		g_aItem[nCntItem].nType = ITEMTYPE_COIN;
	}

	//�R�C���̐ݒu
	for (int nCntCoin = 0; nCntCoin < NUM_COIN; nCntCoin++)
	{
		float fPosX, fPosY, fPosZ;
		fPosX = (float)(rand() % 12000) / 10.0f - 600.0f;//-600.0f~600.0f
		fPosY = HEIGHT_FROMLAND_ITEM;
		fPosZ = (float)(rand() % 12000) / 10.0f - 600.0f;

		SetItem(D3DXVECTOR3(fPosX, fPosY, fPosZ), ITEMTYPE_COIN, true);
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
		SAFE_RELEASE(g_pMeshItem[nCntItemType]);
		SAFE_RELEASE(g_pD3DXMatBuffItem[nCntItemType]);

	}

	SAFE_RELEASE(g_pD3DVtxBuffItemUI);
	SAFE_RELEASE(g_pD3DVtxBuffItemUI2);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateItem(void)
{

#ifdef _DEBUG
	//�J���ҋ@�\
	if (GetKeyboardPress(DIK_MULTIPLY))		//�e���L�[�̃A�X�^���X�N*
	{
		g_isDropItem = true;
	}
#endif

	//��莞�Ԍ�A�A�C�X�u���b�N�������I�ɗ�������
	if ((GetTimer() % DROP_TIME == 0)&&(GetTimer() > 0))	//���ԏI������ꍇ�́A�������Ȃ�
	{
		g_isDropItem = true;
	}

	//��������
	DropItem();
	
	//�A�C�e���̌����Ɖe���X�V
	for(int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if(g_aItem[nCntItem].use)
		{
			g_aItem[nCntItem].srt.rot.y += VALUE_ROTATE;	//���t���[������]

			LimitRot(g_aItem[nCntItem].srt.rot.y);

			//�e���X�V
			UpdateShadow(g_aItem[nCntItem].nIdxShadow, g_aItem[nCntItem].srt.pos, HEIGHT_FROMLAND_ITEM);
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�A�C�e���̕`��
	for (int i = 0; i < MAX_ITEM; i++)//�p�[�c�ԍ�
	{
		DrawXMODEL(pDevice, g_aItem + i, 1);
	}

	//�����A�C�e��UI�̕`��	
	//���̕�
	if (GetPlayer()->holdItem == ITEMTYPE_ICEBLOCK)
	{
		DrawPolygon(pDevice, g_pD3DVtxBuffItemUI, NULL);			
	}
	//�E�̕�
	if (GetEnemy()->holdItem == ITEMTYPE_ICEBLOCK)
	{
		DrawPolygon(pDevice, g_pD3DVtxBuffItemUI2, NULL);
	}
			
}

//=============================================================================
// �A�C�e���̐ݒ�
//=============================================================================
int SetItem(D3DXVECTOR3 pos, ITEMTYPE nType, bool shadowUsable)
{
	int itemIndex = -1;		//�G���[�R�[�h

	for(int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if(!g_aItem[nCntItem].use)
		{
			g_aItem[nCntItem].srt.pos = pos;
			g_aItem[nCntItem].nType = nType;
			g_aItem[nCntItem].use = true;

			g_aItem[nCntItem].pMesh = g_pMeshItem[g_aItem[nCntItem].nType];
			g_aItem[nCntItem].pMatBuff = g_pD3DXMatBuffItem[g_aItem[nCntItem].nType];
			g_aItem[nCntItem].nNumMat = g_aNumMatItem[g_aItem[nCntItem].nType];

			if (shadowUsable)
			{
				// �e�̐ݒ�
				g_aItem[nCntItem].nIdxShadow = SetShadow(g_aItem[nCntItem].srt.pos, g_aItem[nCntItem].fRadius * 2.0f);
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
		g_aItem[nIdxItem].use = false;
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
// �����A�C�e���̗������鏈��
//=============================================================================
void DropItem()
{
	if (g_isDropItem)
	{
		if (!g_isReadyToDrop)
		{
			float fPosX, fPosY, fPosZ;
			fPosX = (float)(rand() % 12000) / 10.0f - 600.0f;//-600.0f~600.0f
			fPosY = DROP_HIGHT;								//�����̍���
			fPosZ = (float)(rand() % 12000) / 10.0f - 600.0f;//-600.0f~600.0f

			g_dropItemIndex = SetItem(D3DXVECTOR3(fPosX, fPosY, fPosZ), ITEMTYPE_ICEBLOCK, false);

			g_isReadyToDrop = true;
		}

		if (g_dropItemIndex != -1)
		{
			(GetItem() + g_dropItemIndex)->srt.pos.y -= DROP_SPEED;

			if ((GetItem() + g_dropItemIndex)->srt.pos.y <= HEIGHT_FROMLAND_ITEM)
			{//�A�C�e���̒��n����
				(GetItem() + g_dropItemIndex)->srt.pos.y = HEIGHT_FROMLAND_ITEM;

				g_isDropItem = false;
				g_isReadyToDrop = false;
			}
		}
		
	}
}
