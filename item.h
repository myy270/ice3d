//=============================================================================
//
// �A�C�e������ [item.h]
// Author : ���p�j
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_ITEM				(128)						// �A�C�e���ő吔

//**************************************
// ���
//**************************************
enum ITEMTYPE
{
	ITEMTYPE_COIN,		// �R�C��
	ITEMTYPE_ICEBLOCK,		// �A�C�X�u���b�N

	ITEMTYPE_MAX
};

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// ���݂̈ʒu
	D3DXVECTOR3 rot;		// ���݂̌���
	float fRadius;			// ���a
	int nIdxShadow;			// �eID
	int nType;				// ���
	bool bUse;				// �g�p���Ă��邩�ǂ���
} ITEM;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
int SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType = ITEMTYPE_COIN, bool shadow = true);
void DeleteItem(int nIdxItem);
ITEM *GetItem(void);

void Freeze(OBJECT target);

void DropItem();

#endif
