//=============================================================================
//
// ���ʂ̋@�\ [function.h]
// Author : ���p�j
//
//=============================================================================
#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <d3dx9.h>						// DX�֘A�̃��C�u�����[
#include "dx.h"

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************

#if 1	// [������"0"�ɂ����ꍇ�A"�\���v���p�e�B" -> "�����J" -> "����" -> "�ǉ��̈ˑ��t�@�C��"�ɑΏۃ��C�u������ݒ肷��]
#pragma comment (lib, "d3d9.lib")		//DX�֌W
#pragma comment (lib, "d3dx9.lib")		//DX�֌W
#pragma comment (lib, "dinput8.lib")	//DX��input�֌W
#pragma comment (lib, "dxguid.lib")		//DX��input�֌W
#pragma comment (lib, "winmm.lib")		//time�֌W
#endif

//*****************************************************************************
// �}�N����`
//*****************************************************************************

// �Q�c�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// �R�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@�� / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define SCREEN_WIDTH	(1280)				// ���ۂ̃E�C���h�E�̕�(int�^�K�{)
#define SCREEN_HEIGHT	(720)				// ���ۂ̃E�C���h�E�̍���(int�^�K�{)

#define DESIGN_SCREEN_WIDTH		(1280.0f)			// �݌v����Ƃ��̃E�C���h�E�̕�(�����_�K�{)
#define DESIGN_SCREEN_HEIGHT	(720.0f)			// �݌v����Ƃ��̃E�C���h�E�̍���(�����_�K�{)

#define TEXTURE_AUTOFIT_WIDTH			(SCREEN_WIDTH  / DESIGN_SCREEN_WIDTH)			// ��ʃT�C�Y�ɉ����Ă̕��̒����䗦
#define TEXTURE_AUTOFIT_HEIGHT			(SCREEN_HEIGHT / DESIGN_SCREEN_HEIGHT)			// ��ʃT�C�Y�ɉ����Ă̍����̒����䗦

#define TEXTURE_WIDTH(width,rate)		((width) * (rate) * TEXTURE_AUTOFIT_WIDTH)		// �e�N�X�`���̒�����̕��̌v�Z��  (width:���\�[�X�̕�,rate:�g�k��)
#define TEXTURE_HEIGHT(height,rate)		((height) * (rate) * TEXTURE_AUTOFIT_HEIGHT)	// �e�N�X�`���̒�����̍����̌v�Z��  (height:���\�[�X�̍���,rate:�g�k��)

#define TEXTURE_CENTER_X(width)			((SCREEN_WIDTH - (width)) / 2.0f)				// ��ʂ̉������̐^���ɂ����悤�Ƀe�N�X�`���̍���X���W  (width:�e�N�X�`���̒�����̕�)
#define TEXTURE_CENTER_Y(height)		((SCREEN_HEIGHT - (height)) / 2.0f)				// ��ʂ̏c�����̐^���ɂ����悤�Ƀe�N�X�`���̍���Y���W  (height:�e�N�X�`���̒�����̍���)


#define	NUM_VERTEX		(4)		// ���_��
#define	NUM_POLYGON		(2)		// �|���S����

#define SAFE_RELEASE(ptr)		{ if(ptr) { (ptr)->Release(); (ptr) = NULL; } }		//�I�u�W�F�N�g�̉��

#define PART_MAX		(7)		// �v���C���[�p�[�c��
#define PART_MAX_ENEMY	(7)		// �G�p�[�c�̐�

#define	FPS	(60)

#define	FIRST_SCENE		(SCENE_TITLE)		//�ŏ��̉��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9& vtxBuff, D3DXVECTOR3 vec, float width, float height);

void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff, D3DXVECTOR3 vtx, float width, float height);
void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff, D3DCOLOR diffuse);
void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff, D3DXVECTOR2 tex, float width, float height);

void DrawPolygon(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9 vtxBuff, LPDIRECT3DTEXTURE9 tex);

//*****************************************************************************
// �񋓌^��`
//*****************************************************************************

// �t�F�[�h�̏��
enum FADETYPE
{
	FADE_NONE = 0,			// �t�F�[�h�����Ȃ��̏��
	FADE_IN,				// �t�F�[�h�C������
	FADE_OUT,				// �t�F�[�h�A�E�g����
	FADE_MAX
};

// �Q�[�����
enum SCENE
{				
	SCENE_TITLE,			// �^�C�g�����
	SCENE_GAME,				// �Q�[�����
	SCENE_RESULT,			// ���U���g���
	SCENE_MAX				// �f�t�H���g�l(�Ȃɂ��Ȃ���ԁASetScene()���g��Ȃ��ƃ_��)
};

enum OBJECT
{
	OBJECT_PLAYER,
	OBJECT_ENEMY,
	OBJECT_MAX
};

enum CAMERA_MODE
{
	CAMERA_MODE_NEAR,
	CAMERA_MODE_FAR,
	CAMERA_MODE_MAX
};

enum PLAY_MODE
{
	PLAY_MODE_SINGLE,		//��̃v���C���[
	PLAY_MODE_DOUBLE,		//��̃v���C���[
	PLAY_MODE_MAX
};

enum STATE
{
	NORMAL,
	FROZEN,
	STATE_MAX
};

enum PART_ID
{
	BODY,
	HEAD,
	HAND,
	LEG,
	PART_ID_MAX
};

enum APPLIMODE
{
	MODE_PLAY,
	MODE_EDIT,
	APPLIMODE_MAX
};

enum ITEMTYPE
{
	ITEMTYPE_COIN,			// �R�C��
	ITEMTYPE_ICEBLOCK,		// �A�C�X�u���b�N

	ITEMTYPE_MAX
};

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

// ��L�Q�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
struct VERTEX_2D
{
	D3DXVECTOR3 vtx;		// ���_���W
	float rhw;				// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
};

// ��L�R�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
struct VERTEX_3D
{
	D3DXVECTOR3 vtx;		// ���_���W
	D3DXVECTOR3 nor;		// �@���x�N�g��
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
};

struct SRT
{
	D3DXVECTOR3 scl;		// �g��k��	
	D3DXVECTOR3 rot;		// ���݂̌���
	D3DXVECTOR3 pos;		// ���݂̈ʒu
};

//�L�[�t���[���̒�`
struct KEY
{
	int			frame;			//���̃L�[�t���[���̑��t���[����
	SRT			key[PART_MAX];	//�L�[�t���[���̃f�[�^
};

struct PART
{
	char *partFile;							//x�t�@�C�����
	LPD3DXBUFFER		pMatBuff;			// ���b�V���̃}�e���A�������i�[
	DWORD				nNumMat;			// �}�e���A�����̑���
	LPD3DXMESH			pMesh;				// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^

	SRT			srt;						//Scaling Rotation Translation
	D3DXMATRIX	mtxWorld;
	PART		*parent;
	bool		use;
};

struct PLAYER
{
	D3DXVECTOR3 move;		// �ړ���
	D3DXVECTOR3 rotDest;	// �ړI�̌���
	float fRadius;			// ���a
	int nIdxShadow;			// �eID
	PART part[PART_MAX];

	ITEMTYPE holdItem;

	STATE state;
	int stateTime;
};

#endif



