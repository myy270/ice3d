//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author : ���p�j
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TITLE_BG		"data/TEXTURE/TITLE_BG.jpg"				// �^�C�g����ʂ̔w�i
#define	TEXTURE_TITLE_LOGO		"data/TEXTURE/TITLE_LOGO.png"			// �^�C�g�����S
#define	TEXTURE_PRESS_START		"data/TEXTURE/PRESS_START.png"			// �^�C�g����ʂ́uPRESS START�v���S
#define	TEXTURE_MENU_1P2P		"data/TEXTURE/MENU_1P2P.png"			// 1p2p�I�����j���[


#define	TITLE_LOGO_WIDTH		TEXTURE_WIDTH(640,0.7f)					// �^�C�g�����S�̕�
#define	TITLE_LOGO_HEIGHT		TEXTURE_HEIGHT(640,0.7f)				// �^�C�g�����S�̍���
#define	TITLE_LOGO_POS_X		TEXTURE_CENTER_X(TITLE_LOGO_WIDTH)		// �^�C�g�����S�̍��㒸�_��X���W
#define	TITLE_LOGO_POS_Y		(SCREEN_HEIGHT * 0.05f)					// �^�C�g�����S�̍��㒸�_��Y���W

#define	PRESS_START_WIDTH		TEXTURE_WIDTH(289,1.3f) 				// �uPRESS START�v���S�̕�
#define	PRESS_START_HEIGHT		TEXTURE_HEIGHT(145,1.3f) 				// �uPRESS START�v���S�̍���
#define	PRESS_START_POS_X		TEXTURE_CENTER_X(PRESS_START_WIDTH)		// �uPRESS START�v���S�̍��㒸�_��X���W
#define	PRESS_START_POS_Y		(SCREEN_HEIGHT * 0.7f)					// �uPRESS START�v���S�̍��㒸�_��Y���W

#define	MENU_1P2P_WIDTH			TEXTURE_WIDTH(1660,0.35f)				// 1p2p�I�����j���[�̕�			
#define	MENU_1P2P_HEIGHT		TEXTURE_HEIGHT(576,0.35f) 				// 1p2p�I�����j���[�̍���
#define	MENU_1P2P_POS_X			TEXTURE_CENTER_X(MENU_1P2P_WIDTH)		// 1p2p�I�����j���[�̍��㒸�_��X���W
#define	MENU_1P2P_POS_Y			(SCREEN_HEIGHT * 0.6f)					// 1p2p�I�����j���[�̍��㒸�_��Y���W

#define	DELTA_TITLE_LOGO_ALPHA	(0.005f)								// �^�C�g�����S�̃t�F�[�h�C���̃A���t�@�ω��l

#define	COUNT_APPEAR_START		(60)									// �uPRESS START�v���S���߂ďo������܂ł̑҂�����
#define	INTERVAL_DISP_START		(60)									// �uPRESS START�v���S�̓_������
#define	INTERVAL_UNDISP_START	(20)									// �uPRESS START�v���S�̏�������

#define	INDEX_MAX_MENU_1P2P		(2)										// 1p2p�I�����j���[�̍ő區�ڐ�
#define	CURSOR_RATE				(0.1735f)								// �J�[�\���̈ʒu�䗦
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

HRESULT MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9& vtxBuff, D3DXVECTOR3 vec,float width,float height,float alpha);

void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff, D3DXVECTOR3 vtx, float width, float height);
void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff, D3DCOLOR diffuse);
void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff, D3DXVECTOR2 tex, float width, float height);

void DrawPolygon(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9 vtxBuff, LPDIRECT3DTEXTURE9 tex);

void TitleEffect(void);
void Menu1P2P(void);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTitleBG = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffTitleBG = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

LPDIRECT3DTEXTURE9		g_pD3DTextureTitleLogo = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffTitleLogo = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

LPDIRECT3DTEXTURE9		g_pD3DTextureStart = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffStart = NULL;			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

LPDIRECT3DTEXTURE9		g_pD3DTextureMenu1P2P = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffMenu1P2P = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^


float					g_fAlphaTitleLogo;					// �^�C�g�����S�̃��l
int						g_nCountAppearStart;				// �uPRESS START�v���S���߂ďo������܂ł̃J�E���g����
int						g_nCountDispStart;					// �uPRESS START�v���S���߂ďo�����Ă���A�_�ŗp�̃J�E���g����
bool					g_bDispStart;						// �uPRESS START�v���S��\�����邩�ǂ���

bool					g_bDispMenu1P2P;					//1p2p�I�����j���[��\�����邩�ǂ���
int						g_nCursorIdx;						//�J�[�\���C���f�N�X(1p2p�I���̓������L�^���邽��)
bool					g_bChosedMenu1P2P;					//1p2p�I�����j���[��I���������ǂ���



//=============================================================================
// ����������
//=============================================================================
HRESULT InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_fAlphaTitleLogo = 0.0f;
	g_nCountAppearStart = 0;
	g_nCountDispStart = 0;
	g_bDispStart = false;

	g_bDispMenu1P2P = false;
	g_nCursorIdx = 0;
	g_bChosedMenu1P2P = false;

	// ���_���̍쐬
	// �^�C�g����ʂ̔w�i
	MakeVertexTitle(pDevice, g_pD3DVtxBuffTitleBG, D3DXVECTOR3(0.0f,0.0f,0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f);
	// �^�C�g�����S
	MakeVertexTitle(pDevice, g_pD3DVtxBuffTitleLogo, D3DXVECTOR3(TITLE_LOGO_POS_X, TITLE_LOGO_POS_Y, 0.0f), TITLE_LOGO_WIDTH, TITLE_LOGO_HEIGHT, 0.0f);
	// �^�C�g����ʂ́uPRESS START�v���S
	MakeVertexTitle(pDevice, g_pD3DVtxBuffStart, D3DXVECTOR3(PRESS_START_POS_X, PRESS_START_POS_Y, 0.0f), PRESS_START_WIDTH, PRESS_START_HEIGHT, 1.0f);
	// 1p2p�I�����j���[
	MakeVertexTitle(pDevice, g_pD3DVtxBuffMenu1P2P, D3DXVECTOR3(MENU_1P2P_POS_X, MENU_1P2P_POS_Y, 0.0f), MENU_1P2P_WIDTH, MENU_1P2P_HEIGHT, 1.0f);


	// �e�N�X�`���̓ǂݍ���
	// �^�C�g����ʂ̔w�i
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_TITLE_BG,			// �t�@�C���̖��O
								&g_pD3DTextureTitleBG);		// �ǂݍ��ރ������[
	// �^�C�g�����S
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_TITLE_LOGO,			// �t�@�C���̖��O
								&g_pD3DTextureTitleLogo);	// �ǂݍ��ރ������[
	// �^�C�g����ʂ́uPRESS START�v���S
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_PRESS_START,		// �t�@�C���̖��O
								&g_pD3DTextureStart);		// �ǂݍ��ރ������[
	// 1p2p�I�����j���[
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_MENU_1P2P,			// �t�@�C���̖��O
								&g_pD3DTextureMenu1P2P);	// �ǂݍ��ރ������[


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitle(void)
{
	SAFE_RELEASE(g_pD3DTextureTitleBG);
	SAFE_RELEASE(g_pD3DVtxBuffTitleBG);
	SAFE_RELEASE(g_pD3DTextureTitleLogo);
	SAFE_RELEASE(g_pD3DVtxBuffTitleLogo);
	SAFE_RELEASE(g_pD3DTextureStart);
	SAFE_RELEASE(g_pD3DVtxBuffStart);
	SAFE_RELEASE(g_pD3DTextureMenu1P2P);
	SAFE_RELEASE(g_pD3DVtxBuffMenu1P2P);

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle(void)
{
	TitleEffect();
	
	Menu1P2P();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�^�C�g����ʂ̔w�i��`��
	DrawPolygon(pDevice, g_pD3DVtxBuffTitleBG, g_pD3DTextureTitleBG);

	if (!g_bDispMenu1P2P)
	{
		//�^�C�g�����S��`��
		DrawPolygon(pDevice, g_pD3DVtxBuffTitleLogo, g_pD3DTextureTitleLogo);

		if (g_bDispStart == true)
		{
			//�uPRESS START�v���S��`��
			DrawPolygon(pDevice, g_pD3DVtxBuffStart, g_pD3DTextureStart);
		}
	}
	else
	{//1p2p�I�����j���[�̕`��
		if (g_nCursorIdx == 0)
		{//�J�[�\����1P���ڂ��w���Ă���Ƃ�
			//���_�o�b�t�@�̓��e���Đݒ肷��
			SetVtxData(g_pD3DVtxBuffMenu1P2P, D3DXVECTOR3(MENU_1P2P_POS_X, MENU_1P2P_POS_Y, 0.0f), MENU_1P2P_WIDTH, MENU_1P2P_HEIGHT / 2);
			SetVtxData(g_pD3DVtxBuffMenu1P2P, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetVtxData(g_pD3DVtxBuffMenu1P2P, D3DXVECTOR2(0.0f, 0.0f), 1.0f, 0.5f);

			//1p���ڂ�`��
			DrawPolygon(pDevice, g_pD3DVtxBuffMenu1P2P, g_pD3DTextureMenu1P2P);

			//���_�o�b�t�@�̓��e���Đݒ肷��
			SetVtxData(g_pD3DVtxBuffMenu1P2P, D3DXVECTOR3(MENU_1P2P_POS_X + MENU_1P2P_WIDTH * CURSOR_RATE, MENU_1P2P_POS_Y + MENU_1P2P_HEIGHT / 2, 0.0f), MENU_1P2P_WIDTH * (1 - CURSOR_RATE), MENU_1P2P_HEIGHT / 2);
			SetVtxData(g_pD3DVtxBuffMenu1P2P, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			SetVtxData(g_pD3DVtxBuffMenu1P2P, D3DXVECTOR2(CURSOR_RATE, 0.5f), (1.0f - CURSOR_RATE), 0.5f);

			//2p���ڂ�`��
			DrawPolygon(pDevice, g_pD3DVtxBuffMenu1P2P, g_pD3DTextureMenu1P2P);			
		}
		else if (g_nCursorIdx == 1)
		{//�J�[�\����2P���ڂ��w���Ă���Ƃ�
			//���_�o�b�t�@�̓��e���Đݒ肷��
			SetVtxData(g_pD3DVtxBuffMenu1P2P, D3DXVECTOR3(MENU_1P2P_POS_X + MENU_1P2P_WIDTH * CURSOR_RATE, MENU_1P2P_POS_Y, 0.0f), MENU_1P2P_WIDTH * (1 - CURSOR_RATE), MENU_1P2P_HEIGHT / 2);
			SetVtxData(g_pD3DVtxBuffMenu1P2P, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			SetVtxData(g_pD3DVtxBuffMenu1P2P, D3DXVECTOR2(CURSOR_RATE, 0.0f), (1.0f - CURSOR_RATE), 0.5f);

			//1p���ڂ�`��
			DrawPolygon(pDevice, g_pD3DVtxBuffMenu1P2P, g_pD3DTextureMenu1P2P);

			//���_�o�b�t�@�̓��e���Đݒ肷��
			SetVtxData(g_pD3DVtxBuffMenu1P2P, D3DXVECTOR3(MENU_1P2P_POS_X, MENU_1P2P_POS_Y + MENU_1P2P_HEIGHT / 2, 0.0f), MENU_1P2P_WIDTH, MENU_1P2P_HEIGHT / 2);
			SetVtxData(g_pD3DVtxBuffMenu1P2P, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SetVtxData(g_pD3DVtxBuffMenu1P2P, D3DXVECTOR2(0.0f, 0.5f), 1.0f, 0.5f);

			//2p���ڂ�`��
			DrawPolygon(pDevice, g_pD3DVtxBuffMenu1P2P, g_pD3DTextureMenu1P2P);
		}
	}
}

//=============================================================================
// ���_�̍쐬
// vtx:���㒸�_�̍��W�@width:�|���S���̕��@height:�|���S���̍����@alpha:���_�̃A���t�@�l
//=============================================================================
HRESULT MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9& vtxBuff, D3DXVECTOR3 vtx, float width, float height, float alpha)
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
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(vtx.x, vtx.y, vtx.z);
		pVtx[1].vtx = D3DXVECTOR3(vtx.x + width, vtx.y, vtx.z);
		pVtx[2].vtx = D3DXVECTOR3(vtx.x, vtx.y + height, vtx.z);
		pVtx[3].vtx = D3DXVECTOR3(vtx.x + width, vtx.y + height, vtx.z);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		vtxBuff->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_�̍��W���Z�b�g
// vtx:���㒸�_�̍��W�@width,height:�͈�
//=============================================================================
void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff, D3DXVECTOR3 vtx, float width, float height)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].vtx = D3DXVECTOR3(vtx.x, vtx.y, vtx.z);
	pVtx[1].vtx = D3DXVECTOR3(vtx.x + width, vtx.y, vtx.z);
	pVtx[2].vtx = D3DXVECTOR3(vtx.x, vtx.y + height, vtx.z);
	pVtx[3].vtx = D3DXVECTOR3(vtx.x + width, vtx.y + height, vtx.z);

	// ���_�f�[�^���A�����b�N����
	vtxBuff->Unlock();
}

//=============================================================================
// ���_�̐F���Z�b�g
// diffuse:���_�̐F
//=============================================================================
void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff, D3DCOLOR diffuse)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

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
// tex:���㒸�_�̃e�N�X�`�����W�@width,height:�͈�
//=============================================================================
void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff, D3DXVECTOR2 tex, float width, float height)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(tex.x, tex.y);
	pVtx[1].tex = D3DXVECTOR2(tex.x + width, tex.y);
	pVtx[2].tex = D3DXVECTOR2(tex.x, tex.y + height);
	pVtx[3].tex = D3DXVECTOR2(tex.x + width, tex.y + height);

	// ���_�f�[�^���A�����b�N����
	vtxBuff->Unlock();
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
//�^�C�g����ʂ̉��o����
//=============================================================================
void TitleEffect(void)
{
	//�^�C�g�����S�̃t�F�[�h�C�� �� �uPRESS START�v���S�̓_��
	if (g_fAlphaTitleLogo < 1.0f)
	{//�^�C�g�����S���t�F�[�h�C�������
		g_fAlphaTitleLogo += DELTA_TITLE_LOGO_ALPHA;			//���t���[���ɃA���t�@�l�𑝉����āA�t�F�[�h�C��������
		if (g_fAlphaTitleLogo >= 1.0f)
		{
			g_fAlphaTitleLogo = 1.0f;
		}

		SetVtxData(g_pD3DVtxBuffTitleLogo, D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaTitleLogo));	//�A���t�@�l���Z�b�g����
	}
	else
	{//�t�F�[�h�C������������
		if (g_nCountAppearStart < COUNT_APPEAR_START)		//�uCOUNT_APPEAR_START�v�t���[����҂�
		{
			g_nCountAppearStart++;
		}
		else
		{//�҂��I�������A�uPRESS START�v���S��_�ł�����
			g_nCountDispStart = (g_nCountDispStart + 1) % (INTERVAL_DISP_START + INTERVAL_UNDISP_START);			//�_�ł�����悤�ɃJ�E���g����
			if (g_nCountDispStart < INTERVAL_DISP_START)
			{
				g_bDispStart = true;			//�J�E���g���u0�v����uINTERVAL_DISP_START�v�܂ł̊Ԃɓ_������
			}
			else
			{
				g_bDispStart = false;			//�J�E���g���uINTERVAL_DISP_START�v����uINTERVAL_UNDISP_START�v�܂ł̊Ԃɏ�������
			}

		}
	}

	//�^�C�g�����S�̃t�F�[�h�C���̃X�L�b�v �� 1p2p�I�����j���[�Ɉڂ�����
	if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTrigger(0, BUTTON_OPTIONS))
	{
		if (g_fAlphaTitleLogo < 1.0f)
		{//�^�C�g�����S���t�F�[�h�C�����Ă��鎞
			g_fAlphaTitleLogo = 1.0f;						// �t�F�[�h�C����������Ԃɂ�����

			SetVtxData(g_pD3DVtxBuffTitleLogo, D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaTitleLogo));	//�A���t�@�l���Z�b�g����

			g_nCountAppearStart = COUNT_APPEAR_START;	//�uPRESS START�v���S��_�ŏ�Ԃɂ�����
		}
		else
		{//�^�C�g�����S���t�F�[�h�C������������			
			g_bDispMenu1P2P = true;						//1p2p�I�����j���[��\������
		}
	}

}

//=============================================================================
// 1p2p�I�����j���[�̏���
//=============================================================================
void Menu1P2P(void)
{
	//�J�[�\���ړ��ƑI��
	if (g_bDispMenu1P2P)
	{//1p2p�I�����j���[���\������Ă���Ƃ�
		if (!g_bChosedMenu1P2P)
		{//1p2p�I�����j���[���܂��I������Ă��Ȃ��Ƃ�
			if (GetKeyboardRepeat(DIK_W) || IsButtonRepeat(0, BUTTON_UP) || IsButtonRepeat(0, BUTTON_LSTICK_UP))
			{//�J�[�\������ړ�
				g_nCursorIdx = g_nCursorIdx - 1;

				if (g_nCursorIdx < 0)
				{
					g_nCursorIdx = INDEX_MAX_MENU_1P2P - 1;
				}
			}
			else if (GetKeyboardRepeat(DIK_S) || IsButtonRepeat(0, BUTTON_DOWN) || IsButtonRepeat(0, BUTTON_LSTICK_DOWN))
			{//�J�[�\�������ړ�
				g_nCursorIdx = (g_nCursorIdx + 1) % INDEX_MAX_MENU_1P2P;
			}

			if (GetKeyboardTrigger(DIK_SPACE) || IsButtonTrigger(0, BUTTON_CIRCLE))
			{//���j���[�̍��ڂ�I��
				SetFade(FADE_OUT);
				g_bChosedMenu1P2P = true;
			}
		}
	}
}

//=============================================================================
// 1p2p�I���̓������Q�b�g
//=============================================================================
int GetCursorIdx(void)
{
	return g_nCursorIdx;
}
