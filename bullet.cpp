//=============================================================================
//
// �e���� [bullet.cpp]
// Author : ���p�j
//
//=============================================================================
#include "bullet.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "effect.h"
#include "explosion.h"
#include "player.h"
#include "life.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_BULLET			"data/TEXTURE/bullet000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	BULLET_SIZE_X			(50.0f)							// �r���{�[�h�̕�
#define	BULLET_SIZE_Y			(50.0f)							// �r���{�[�h�̍���
//#define	VALUE_MOVE_BULLET		(2.0f)							// �ړ����x

#define	MAX_BULLET				(128)							// �r���{�[�h�ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ��]
	D3DXVECTOR3 scale;		// �X�P�[��
	D3DXVECTOR3 move;		// �ړ���
	float fSizeX;			// ��
	float fSizeY;			// ����
	int nTimer;				// �^�C�}�[
	int nIdxShadow;			// �eID
	bool bUse;				// �g�p���Ă��邩�ǂ���
} BULLET;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice);
void SetVertexBullet(int nIdxBullet, float fSizeX, float fSizeY);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBullet = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffBullet = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

D3DXMATRIX				g_mtxWorldBullet;				// ���[���h�}�g���b�N�X

BULLET					g_aBullet[MAX_BULLET];			// �e���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̍쐬
	MakeVertexBullet(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_BULLET,				// �t�@�C���̖��O
								&g_pD3DTextureBullet);	// �ǂݍ��ރ������[

	for(int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{//�ǂ����������x�ݒu���邩��A�����͂ǂ��ł�����
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aBullet[nCntBullet].fSizeX = BULLET_SIZE_X;
		g_aBullet[nCntBullet].fSizeY = BULLET_SIZE_Y;
		g_aBullet[nCntBullet].nTimer = 0;
		g_aBullet[nCntBullet].bUse = false;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	SAFE_RELEASE(g_pD3DTextureBullet);
	SAFE_RELEASE(g_pD3DVtxBuffBullet);

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	PLAYER *pPlayer;
	D3DXVECTOR3 rotCamera;

	// �v���C���[���擾
	pPlayer = GetPlayer();

	// �J�����̉�]���擾
	rotCamera = GetRotCamera();

	for(int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if(g_aBullet[nCntBullet].bUse)
		{
			//�e�̈ʒu���X�V����
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
			g_aBullet[nCntBullet].pos.z += g_aBullet[nCntBullet].move.z;

			g_aBullet[nCntBullet].nTimer--;
			if(g_aBullet[nCntBullet].nTimer <= 0)
			{
				//DeleteBullet(nCntBullet);
				DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				g_aBullet[nCntBullet].bUse = false;
			}
			else
			{
				// �e�̈ʒu�X�V
				SetPositionShadow(g_aBullet[nCntBullet].nIdxShadow, D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, 0.1f, g_aBullet[nCntBullet].pos.z));

				// �G�t�F�N�g�̐ݒ�
				SetEffect(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.50f), 16.0f, 16.0f, 30);//��
				SetEffect(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.05f, 0.85f, 0.65f, 0.30f), 12.0f, 12.0f, 30);//�V�A��
				SetEffect(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.05f, 0.45f, 0.45f, 0.20f), 6.0f, 6.0f, 30);//�V�A��


				if (g_aBullet[nCntBullet].pos.x < -640.0f
					|| g_aBullet[nCntBullet].pos.x > 640.0f
					|| g_aBullet[nCntBullet].pos.z < -640.0f
					|| g_aBullet[nCntBullet].pos.z > 640.0f)
				{
					// �����̐���
					SetExplosion(g_aBullet[nCntBullet].pos, 40.0f, 40.0f);//��̈������ȗ�����

					DeleteBullet(nCntBullet);

					// SE�Đ�
					PlaySound(SOUND_LABEL_SE_EXPLOSION);
				}

				float fSizeX = 8.0f + (g_aBullet[nCntBullet].pos.y - 4.0f) * 0.05f;
				if (fSizeX < 8.0f)
				{
					fSizeX = 8.0f;
				}
				float fSizeY = 8.0f + (g_aBullet[nCntBullet].pos.y - 4.0f) * 0.05f;
				if (fSizeY < 8.0f)
				{
					fSizeY = 8.0f;
				}

				SetVertexShadow(g_aBullet[nCntBullet].nIdxShadow, fSizeX, fSizeY);//�e�̑傫����ݒ�

				float colA = (200.0f - (g_aBullet[nCntBullet].pos.y - 4.0f)) / 400.0f;
				if (colA < 0.0f)
				{
					colA = 0.0f;
				}
				SetColorShadow(g_aBullet[nCntBullet].nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));//�e�̓����l��ݒ�
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxScale,mtxTranslate;

	// ���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for(int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if(g_aBullet[nCntBullet].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldBullet);

			// �r���[�}�g���b�N�X���擾
			mtxView = GetMtxView();

			g_mtxWorldBullet._11 = mtxView._11;
			g_mtxWorldBullet._12 = mtxView._21;
			g_mtxWorldBullet._13 = mtxView._31;
			g_mtxWorldBullet._21 = mtxView._12;
			g_mtxWorldBullet._22 = mtxView._22;
			g_mtxWorldBullet._23 = mtxView._32;
			g_mtxWorldBullet._31 = mtxView._13;
			g_mtxWorldBullet._32 = mtxView._23;
			g_mtxWorldBullet._33 = mtxView._33;

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, g_aBullet[nCntBullet].scale.x, g_aBullet[nCntBullet].scale.y, g_aBullet[nCntBullet].scale.z);
			D3DXMatrixMultiply(&g_mtxWorldBullet, &g_mtxWorldBullet, &mtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldBullet, &g_mtxWorldBullet, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBullet);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffBullet, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureBullet);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntBullet * 4), NUM_POLYGON);//�������𒍈ӂ���
		}
	}

	// ���C�e�B���O��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_BULLET,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,							// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,								// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,							// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffBullet,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))										// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pVtx += 4)
		{
			// ���_���W�̐ݒ�@���ʂ��Ԉ���Ă�@�ǂ����������x�ݒu���邩��A�����͂ǂ��ł�����
			pVtx[0].vtx = D3DXVECTOR3(-BULLET_SIZE_X / 2, -BULLET_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(BULLET_SIZE_X / 2, -BULLET_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-BULLET_SIZE_X / 2, BULLET_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(BULLET_SIZE_X / 2, BULLET_SIZE_Y / 2, 0.0f);

			// �@���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffBullet->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBullet(int nIdxBullet, float fSizeX, float fSizeY)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxBullet * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffBullet->Unlock();
	}
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
int SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nTimer)
{
	int nIdxBullet = -1;

	for(int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if(!g_aBullet[nCntBullet].bUse)
		{
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aBullet[nCntBullet].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].fSizeX = fSizeX;
			g_aBullet[nCntBullet].fSizeY = fSizeY;
			g_aBullet[nCntBullet].nTimer = nTimer;
			g_aBullet[nCntBullet].bUse = true;

			// �e�̐ݒ�
			g_aBullet[nCntBullet].nIdxShadow = SetShadow(pos, 8.0f, 8.0f);		// �e�̐ݒ�

			// ���_���W�̐ݒ�
			SetVertexBullet(nCntBullet, fSizeX, fSizeY);

			nIdxBullet = nCntBullet;

			break;
		}
	}

	return nIdxBullet;
}

//=============================================================================
// �e�̍폜
//=============================================================================
void DeleteBullet(int nIdxBullet)
{
	if(nIdxBullet >= 0 && nIdxBullet < MAX_BULLET)
	{
		DeleteShadow(g_aBullet[nIdxBullet].nIdxShadow);
		g_aBullet[nIdxBullet].bUse = false;
	}
}

