//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : ���p�j
//
//=============================================================================

#include "player.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "effect.h"
#include "item.h"
#include "score.h"
#include "sound.h"
#include "debugproc.h"
#include "timer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	BODY_PLAYER		"data/MODEL/bearBody.x"			// �ǂݍ��ރ��f����
#define	HEAD_PLAYER		"data/MODEL/bearHead.x"			// �ǂݍ��ރ��f����
#define	HAND_PLAYER		"data/MODEL/bearHand.x"			// �ǂݍ��ރ��f����
#define	LEG_PLAYER		"data/MODEL/bearLeg.x"			// �ǂݍ��ރ��f����
#define	ICE_BLOCK		"data/MODEL/iceBlock.x"			// �ǂݍ��ރ��f����

#define	PLAYER_RADIUS		(15.0f)						// ���a		//���̃G�t�F�N�g�̈ʒu��A�A�C�e���Ƃ̓����鋗�� �Ɗ֌W����

#define	VALUE_MOVE_PLAYER	(0.195f)					// �ړ���
#define	RATE_MOVE_PLAYER	(0.025f)					// �ړ���R�͂̌W��		����������Ώ������قǁA����₷��

#define	VALUE_ROTATE_PLAYER	(D3DX_PI * 0.025f)			// ��]��	4.5�x����
#define	RATE_ROTATE_PLAYER	(0.10f)						// ��]���x�W��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

void Movement();
void AreaCollision();
void Drag();
void Shadow();
void Jet();
void ItemCollision();
void UseIceblock();
void Frozen();
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer;		// �e�N�X�`���ǂݍ��ݏꏊ
PLAYER				g_player;					// �v���C���[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_player.motion.motionData = GetMotionWalk();
	g_player.motion.numKey = 4;
	g_player.motion.use = false;
	g_player.motion.motionTime = 0.0f;
	g_player.motion.cancelTime = 0.0f;


	g_player.part[0].partFile = (char *)BODY_PLAYER;		//�́@//���ł���e�͈�Ԑ�ɂ��Ȃ���΂Ȃ�Ȃ�
	g_player.part[1].partFile = (char *)HEAD_PLAYER;		//��
	g_player.part[2].partFile = (char *)HAND_PLAYER;		//����
	g_player.part[3].partFile = (char *)HAND_PLAYER;		//�E��
	g_player.part[4].partFile = (char *)LEG_PLAYER;			//����
	g_player.part[5].partFile = (char *)LEG_PLAYER;			//�E��
	g_player.part[6].partFile = (char *)ICE_BLOCK;			//�X

	//�p�[�c�̏��̐ݒ�
	for (int i = 0; i < PART_MAX_PLAYER; i++)				//�p�[�c�ԍ�
	{
		// X�t�@�C���̓ǂݍ���
		if(FAILED(D3DXLoadMeshFromX(g_player.part[i].partFile,
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_player.part[i].pMatBuff,
									NULL,
									&g_player.part[i].nNumMat,
									&g_player.part[i].pMesh)))
		{
			return E_FAIL;
		}

		switch (i)
		{
		case 0:
		{//��
			g_player.part[i].srt.scl = D3DXVECTOR3(1.5f, 1.5f, 1.5f);			//�X�P�[����xyz�K�������悤��
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(0.0f, 22.4f, 0.0f);			//�����n�ʂɐG���悤�ɒ�������

			g_player.part[i].parent = NULL;										//�̂̐e��NULL�ɂ���
			break;
		}
		case 1:
		{//��
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(0.0f, 6.5f, 0.0f);			//�֐߂̈ʒu�Ɉړ�����

			g_player.part[i].parent = &g_player.part[0];						//�̂�e�ɂ���
			break;
		}
		case 2:
		{//����
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(5.0f, 5.0f, 0.0f);			//�֐߂̈ʒu�Ɉړ�����

			g_player.part[i].parent = &g_player.part[0];						//�̂�e�ɂ���
			break;
		}
		case 3:
		{//�E��
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(-5.0f, 5.0f, 0.0f);			//�֐߂̈ʒu�Ɉړ�����

			g_player.part[i].parent = &g_player.part[0];						//�̂�e�ɂ���
			break;
		}
		case 4:
		{//����
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(3.064f, -4.873f, -0.409f);	//�֐߂̈ʒu�Ɉړ�����

			g_player.part[i].parent = &g_player.part[0];						//�̂�e�ɂ���
			break;
		}
		case 5:
		{//�E��
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(-3.064f, -4.873f, -0.409f);	//�֐߂̈ʒu�Ɉړ�����

			g_player.part[i].parent = &g_player.part[0];						//�̂�e�ɂ���
			break;
		}
		default:
		{//�A�C�X�u���b�N
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			g_player.part[i].parent = &g_player.part[0];						//�̂�e�ɂ���
			break;
		}

		}//switch end

		if (i == 6)
		{//�A�C�X�u���b�N�͍ŏ��\�����Ȃ�
			g_player.part[i].use = false;
		}
		else
		{
			g_player.part[i].use = true;			
		}
	}

	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.fRadius = PLAYER_RADIUS;

	// �e��ݒ� ����(part[0])�����
	g_player.nIdxShadow = SetShadow(g_player.part[0].srt.pos, g_player.fRadius * 2.0f, g_player.fRadius * 2.0f);	//�e�̑傫�����ς��Ȃ�

	g_player.holdItem = ITEMTYPE_COIN;
	g_player.state = NORMAL;
	g_player.frozenTime = 0;

#if 0	//�e�N�X�`���\����
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_PLAYER,			// �t�@�C���̖��O
								&g_pD3DTexturePlayer);	// �ǂݍ��ރ������[
#endif

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	for (int i = 0; i < PART_MAX_PLAYER; i++)	//i:�p�[�c�ԍ�
	{
		SAFE_RELEASE(g_player.part[i].pMesh);
		SAFE_RELEASE(g_player.part[i].pMatBuff);	
	}

	SAFE_RELEASE(g_pD3DTexturePlayer);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	Movement();

	//�������[�V��������
	Motion(g_player, g_player.motion);

	AreaCollision();

	Drag();

	Shadow();

	Jet();
	
	ItemCollision();

	UseIceblock();

	Frozen();

	PrintDebugProc("�ړI�����F%f \n\n", g_player.rotDest.y);
	PrintDebugProc("���݂̌����F%f \n\n", g_player.part[0].srt.rot.y);
	PrintDebugProc("�ړ��ʁF%f %f %f \n\n", g_player.move.x, g_player.move.y, g_player.move.z);
}									  

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DrawPart(pDevice, g_player, g_pD3DTexturePlayer, PART_MAX_PLAYER);

}

//=============================================================================
// �v���C���[���擾
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_player;
}

//=============================================================================
// �ʒu�擾
//=============================================================================
D3DXVECTOR3 GetPositionPlayer(void)
{
	return g_player.part[0].srt.pos;//��(part[0])�����
}

//=============================================================================
//�ʒu�ƌ����̍X�V����
//=============================================================================
void Movement()
{
	D3DXVECTOR3 rotCamera;		//�J�����̌���
	float fDiffRotY;			//�ړI�̊p�x�܂ł̍���

	// �J�����̌����擾
	rotCamera = GetRotCamera();

	//�^����Ԃ����Z�b�g
	g_player.motion.use = false;

	//���Ԃ��I����Ă��Ȃ��A��������Ԃł͂Ȃ��ꍇ�A�ړ��ł����ԂɂȂ�
	if ((IsTimeEnd() == false) && (g_player.state != FROZEN))
	{//�ړ�			���O�t���[���̉^���ʂ��c���Ă��邩��A��������
		if (GetKeyboardPress(DIK_A) || IsButtonPress(0, BUTTON_LEFT) || IsButtonPress(0, BUTTON_LSTICK_LEFT))
		{
			g_player.motion.use = true;//������Ԃɂ���

			if (GetKeyboardPress(DIK_W) || IsButtonPress(0, BUTTON_UP) || IsButtonPress(0, BUTTON_LSTICK_UP))
			{// ���O�ړ�
				g_player.move.x -= sinf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y + D3DX_PI * 0.75f;
			}
			else if (GetKeyboardPress(DIK_S) || IsButtonPress(0, BUTTON_DOWN) || IsButtonPress(0, BUTTON_LSTICK_DOWN))
			{// ����ړ�
				g_player.move.x -= sinf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y + D3DX_PI * 0.25f;
			}
			else
			{// ���ړ�
				g_player.move.x -= sinf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y + D3DX_PI * 0.50f;
			}
		}
		else if (GetKeyboardPress(DIK_D) || IsButtonPress(0, BUTTON_RIGHT) || IsButtonPress(0, BUTTON_LSTICK_RIGHT))
		{
			g_player.motion.use = true;//������Ԃɂ���

			if (GetKeyboardPress(DIK_W) || IsButtonPress(0, BUTTON_UP) || IsButtonPress(0, BUTTON_LSTICK_UP))
			{// �E�O�ړ�
				g_player.move.x -= sinf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y - D3DX_PI * 0.75f;
			}
			else if (GetKeyboardPress(DIK_S) || IsButtonPress(0, BUTTON_DOWN) || IsButtonPress(0, BUTTON_LSTICK_DOWN))
			{// �E��ړ�
				g_player.move.x -= sinf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y - D3DX_PI * 0.25f;
			}
			else
			{// �E�ړ�
				g_player.move.x -= sinf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y - D3DX_PI * 0.50f;
			}
		}
		else if (GetKeyboardPress(DIK_W) || IsButtonPress(0, BUTTON_UP) || IsButtonPress(0, BUTTON_LSTICK_UP))
		{
			g_player.motion.use = true;//������Ԃɂ���

			// �O�ړ�
			g_player.move.x -= sinf(D3DX_PI + rotCamera.y) * VALUE_MOVE_PLAYER;
			g_player.move.z -= cosf(D3DX_PI + rotCamera.y) * VALUE_MOVE_PLAYER;

			g_player.rotDest.y = rotCamera.y + D3DX_PI;		// - D3DX_PI�ɂȂ�ƁA�t�̕����ɉ�]����
		}
		else if (GetKeyboardPress(DIK_S) || IsButtonPress(0, BUTTON_DOWN) || IsButtonPress(0, BUTTON_LSTICK_DOWN))
		{
			g_player.motion.use = true;//������Ԃɂ���

			// ��ړ�
			g_player.move.x -= sinf(rotCamera.y) * VALUE_MOVE_PLAYER;
			g_player.move.z -= cosf(rotCamera.y) * VALUE_MOVE_PLAYER;

			g_player.rotDest.y = rotCamera.y;
		}
	}

#ifdef _DEBUG		
	//�J���ҋ@�\
	if (GetKeyboardPress(DIK_T))
	{// �㏸
		g_player.move.y += VALUE_MOVE_PLAYER;
	}
	else if (GetKeyboardPress(DIK_Y))
	{// ���~
		g_player.move.y -= VALUE_MOVE_PLAYER;
	}

	if (GetKeyboardPress(DIK_U))
	{// ����]
		g_player.rotDest.y -= VALUE_ROTATE_PLAYER;
	}
	else if (GetKeyboardPress(DIK_I))
	{// �E��]
		g_player.rotDest.y += VALUE_ROTATE_PLAYER;
	}
#endif

	LimitRot(g_player.rotDest.y);									//���ۂ͂Ȃ��Ă��������A�������߂��Ⴍ����ɂȂ�

	// �ړI�̊p�x�܂ł̍���
	fDiffRotY = g_player.rotDest.y - g_player.part[0].srt.rot.y;	//��(part[0])�����

	LimitRot(fDiffRotY);											// �d�v! �߂������ɉ�]�ł���悤��

	// ��]�ʂ��(part[0])�ɔ��f
	g_player.part[0].srt.rot.y += fDiffRotY * RATE_ROTATE_PLAYER;	// �ړI�̊p�x�܂Ŋ�����������@�i�X�ړI�̊p�x�ɕω�����

	LimitRot(g_player.part[0].srt.rot.y);							//���ۂ͂Ȃ��Ă��������A�������߂��Ⴍ����ɂȂ�

	/// �ړ��ʂ��(part[0])�ɔ��f
	g_player.part[0].srt.pos.x += g_player.move.x;
	g_player.part[0].srt.pos.y += g_player.move.y;
	g_player.part[0].srt.pos.z += g_player.move.z;

}

//=============================================================================
// �G���A�R���W��������
//=============================================================================
void AreaCollision()
{
	//�ړ��͈͂�ݒ肷��@����(part[0])�����
	if (g_player.part[0].srt.pos.x < -630.0f)
	{
		g_player.part[0].srt.pos.x = -630.0f;
	}
	if (g_player.part[0].srt.pos.x > 630.0f)
	{
		g_player.part[0].srt.pos.x = 630.0f;
	}
	//if (g_player.part[0].srt.pos.y < 10.0f)
	//{
	//	g_player.part[0].srt.pos.y = 10.0f;
	//}
	//if (g_player.part[0].srt.pos.y > 150.0f)
	//{
	//	g_player.part[0].srt.pos.y = 150.0f;
	//}
	if (g_player.part[0].srt.pos.z > 630.0f)
	{
		g_player.part[0].srt.pos.z = 630.0f;
	}
	if (g_player.part[0].srt.pos.z < -630.0f)
	{
		g_player.part[0].srt.pos.z = -630.0f;
	}
	
}

//=============================================================================
// �ړ���R�͂̏���
//=============================================================================
void Drag()
{
	// �^���G�l���M�[���ꕔ�����āi��R�͂̂��߁j�ۑ�����A���̃t���[���Ɏg��(�����̎d�g��)
	//�����̕����C�R�[�����̃t���[���Ɋl���̉^���G�l���M�[�̏ꍇ�A���x���ő�(7.8f)�ɂȂ��āA���������^���ɂȂ�
	g_player.move.x = g_player.move.x * (1 - RATE_MOVE_PLAYER);
	g_player.move.y = g_player.move.y * (1 - RATE_MOVE_PLAYER);
	g_player.move.z = g_player.move.z * (1 - RATE_MOVE_PLAYER);

}

//=============================================================================
// �e�̈ʒu�A�傫���A�����x�̍X�V
//=============================================================================
void Shadow()
{//��(part[0])�����

	//�e�̈ʒu���X�V
	SetPositionShadow(g_player.nIdxShadow, D3DXVECTOR3(g_player.part[0].srt.pos.x, 0.1f, g_player.part[0].srt.pos.z));

	//�����ɂ��A�e�̑傫�����ω�����
	float fSize = 20.0f + (g_player.part[0].srt.pos.y - 10.0f) * 0.05f;
	if (fSize < 20.0f)
	{
		fSize = 20.0f;
	}
	//�e�̑傫�����X�V
	SetVertexShadow(g_player.nIdxShadow, fSize, fSize);

	//�����ɂ��A�e�̓����x���ω�����
	float colA = 0.5f - (g_player.part[0].srt.pos.y - 10.0f) / 400.0f;
	if (colA < 0.0f)
	{
		colA = 0.0f;
	}
	//�e�̓����x���X�V
	SetColorShadow(g_player.nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));

}

//=============================================================================
// ���̃G�t�F�N�g
//=============================================================================
void Jet()
{
	//�ړ�������1���傫���ꍇ�A���̃G�t�F�N�g���o��
	if ((g_player.move.x * g_player.move.x
		+ g_player.move.y * g_player.move.y
		+ g_player.move.z * g_player.move.z) > 1.0f)
	{
		D3DXVECTOR3 pos;
		//��(part[0])�����
		pos.x = g_player.part[0].srt.pos.x + sinf(g_player.part[0].srt.rot.y) * g_player.fRadius;	//�����̕ӂ�ɐݒ�
		pos.y = 3.0f;
		pos.z = g_player.part[0].srt.pos.z + cosf(g_player.part[0].srt.rot.y) * g_player.fRadius;

		// �G�t�F�N�g�̐ݒ�
		SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.85f, 0.15f, 0.0f, 0.50f), 14.0f, 14.0f, 20);//��
		SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.15f, 0.75f, 0.0f, 0.30f), 10.0f, 10.0f, 20);//��
		SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.0f, 0.10f, 0.0f, 0.15f), 5.0f, 5.0f, 20);//��
	}

}

//=============================================================================
// �A�C�e���Ƃ̓����蔻��
//=============================================================================
void ItemCollision()
{
	ITEM *pItem;

	// �A�C�e�����擾
	pItem = GetItem();

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	{
		if (pItem->bUse == true)
		{
			float fLength;		//�v���C���[�ƃA�C�e���̋���

			//�o�E���f�B���O�T�[�N�� BC //��(part[0])�����
			fLength = (g_player.part[0].srt.pos.x - pItem->pos.x) * (g_player.part[0].srt.pos.x - pItem->pos.x)
				+ (g_player.part[0].srt.pos.y - pItem->pos.y) * (g_player.part[0].srt.pos.y - pItem->pos.y)
				+ (g_player.part[0].srt.pos.z - pItem->pos.z) * (g_player.part[0].srt.pos.z - pItem->pos.z);

			if (fLength < (g_player.fRadius + pItem->fRadius) * (g_player.fRadius + pItem->fRadius))
			{//�擾�ł���͈͓��ł����
				if ((g_player.holdItem == ITEMTYPE_ICEBLOCK) && (pItem->nType == ITEMTYPE_ICEBLOCK))
				{//�A�C�X�u���b�N�������Ă���ꍇ�A���̃A�C�X�u���b�N�͎擾�ł��Ȃ�

				}
				else
				{
					if (pItem->nType == ITEMTYPE_ICEBLOCK)
					{
						g_player.holdItem = ITEMTYPE_ICEBLOCK;
					}
					else if (pItem->nType == ITEMTYPE_COIN)
					{
						// �X�R�A���Z
						ChangeScore(OBJECT_PLAYER, 100);

						// �R�C�����E�����ʉ�
						//PlaySound(SOUND_LABEL_SE_COIN);
					}

					// �A�C�e������
					DeleteItem(nCntItem);

				}
			}
		}
	}
}

//=============================================================================
//�����A�C�e�����g��
//=============================================================================
void UseIceblock()
{	
	if ((IsTimeEnd() == 0) && (g_player.state != FROZEN))
	{
		if (GetKeyboardTrigger(DIK_SPACE) || IsButtonTrigger(0, BUTTON_CIRCLE))
		{
			Freeze(OBJECT_ENEMY);
		}
	}

}

//=============================================================================
//������ԂɂȂ鎞�̏���
//=============================================================================
void Frozen()
{
	if (g_player.state == FROZEN)
	{
		if (g_player.frozenTime == 0)
		{
			g_player.state = NORMAL;		//������Ԃ�����
			g_player.part[6].use = false;	//�g�ɓZ���A�C�X�u���b�N��������
		}
		else
		{
			g_player.frozenTime--;			//������Ԃ̎c�莞�Ԃ��J�E���g�_�E��
			g_player.part[6].use = true;	//�g�ɓZ���A�C�X�u���b�N��\������

		}
	}

}
