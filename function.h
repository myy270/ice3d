//=============================================================================
//
// ���ʂ̋@�\ [function.h]
// Author : ���p�j
//
//=============================================================================
#ifndef _FUNCTION_H_
#define _FUNCTION_H_

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
#define	FVF_VERTEX_2D			(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// �R�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@�� / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_3D			(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define SCREEN_WIDTH			(1280)						// ���ۂ̃E�C���h�E�̕�(int�^�K�{)
#define SCREEN_HEIGHT			(720)						// ���ۂ̃E�C���h�E�̍���(int�^�K�{)

#define DESIGN_SCREEN_WIDTH		(1280.0f)					// �݌v����Ƃ��̃E�C���h�E�̕�(�����_�K�{)
#define DESIGN_SCREEN_HEIGHT	(720.0f)					// �݌v����Ƃ��̃E�C���h�E�̍���(�����_�K�{)

#define TEXTURE_AUTOFIT_WIDTH			(SCREEN_WIDTH  / DESIGN_SCREEN_WIDTH)			// ��ʃT�C�Y�ɉ����Ă̕��̒����䗦
#define TEXTURE_AUTOFIT_HEIGHT			(SCREEN_HEIGHT / DESIGN_SCREEN_HEIGHT)			// ��ʃT�C�Y�ɉ����Ă̍����̒����䗦

#define FIT_WIDTH(width)				((width) * TEXTURE_AUTOFIT_WIDTH)				// ������̕��̌v�Z��  (width:���\�[�X�̕�)
#define FIT_HEIGHT(height)				((height) * TEXTURE_AUTOFIT_HEIGHT)				// ������̍����̌v�Z��  (height:���\�[�X�̍���)

#define TEXTURE_CENTER_X(width)			((SCREEN_WIDTH - (width)) / 2.0f)				// ��ʂ̉������̐^���ɂ����悤�Ƀ|���S���̍��㒸�_��X���W	(width:�e�N�X�`���̒�����̕�)
#define TEXTURE_CENTER_Y(height)		((SCREEN_HEIGHT - (height)) / 2.0f)				// ��ʂ̏c�����̐^���ɂ����悤�Ƀ|���S���̍��㒸�_��Y���W	(height:�e�N�X�`���̒�����̍���)


#define	NUM_VERTEX				(4)		// ���_��
#define	NUM_POLYGON				(2)		// �|���S����

#define SAFE_RELEASE(ptr)		{ if(ptr) { (ptr)->Release(); (ptr) = NULL; } }		//�I�u�W�F�N�g�̉��


#define PART_MAX				(7)								// �p�[�c�̐�(�A�C�X�u���b�N���܂�)

#define	FPS						(60)							// ���b�N���ꂽFPS

#define	FIRST_SCENE				(SCENE_TITLE)					// �v���O�����N�����̍ŏ��̉��		//�����[�X���̐ݒ�l�� SCENE_TITLE

#define	BODY_PLAYER				"data/MODEL/bearBody.x"			// �ǂݍ��ރ��f����
#define	HEAD_PLAYER				"data/MODEL/bearHead.x"			// �ǂݍ��ރ��f����
#define	HAND_PLAYER				"data/MODEL/bearHand.x"			// �ǂݍ��ރ��f����
#define	LEG_PLAYER				"data/MODEL/bearLeg.x"			// �ǂݍ��ރ��f����
#define	ICE_BLOCK				"data/MODEL/iceBlock.x"			// �ǂݍ��ރ��f����

#define	BODY_ENEMY				"data/MODEL/bearBodyPink.x"		// �ǂݍ��ރ��f����
#define	HEAD_ENEMY				"data/MODEL/bearHeadPink.x"		// �ǂݍ��ރ��f����
#define	HAND_ENEMY				"data/MODEL/bearHandPink.x"		// �ǂݍ��ރ��f����
#define	LEG_ENEMY				"data/MODEL/bearLegPink.x"		// �ǂݍ��ރ��f����

#define	RADIUS_BEAR				(15.0f)							// �F���f���̔��a	//�e�̑傫���A���̃G�t�F�N�g�̈ʒu��A�A�C�e���Ƃ̓����鋗�� �Ɗ֌W����

#define	VALUE_MOVE_BEAR			(0.195f)						// �ړ���
#define	RATE_MOVE_BEAR			(0.025f)						// �ړ���R�͂̌W��		����������Ώ������قǁA����₷��

#define	VALUE_ROTATE_BEAR		(D3DX_PI * 0.025f)				// ��]��	4.5�x����
#define	RATE_ROTATE_BEAR		(0.10f)							// ��]���x�W��

#define	HEIGHT_FROMLAND_BEAR	(22.4f)							// �̃p�[�c�̒n�ʂ���̍���(part[0].srt.pos.y�̃f�t�H���g�l)

#define	MAX_ITEM				(128)							// �A�C�e���̏��

#define	NUM_COIN				(99)							// �����R�C���̐�	//�����[�X���̐ݒ�l�� 99

#define AI_TYPE					(1)								// AI�̎��			//�����[�X���̐ݒ�l�� 1

#define LIMIT_TIME				(999)							// ��������			//�����[�X���̐ݒ�l�� 50

#define BOOL_DEBUG_UI			(false)							// �f�o�b�O���̕\�����ǂ���

//*****************************************************************************
// �񋓌^��`
//*****************************************************************************

// �t�F�[�h�̏��
enum FADETYPE
{
	FADE_NONE,				// �t�F�[�h�����Ȃ��̏��
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
	SCENE_MAX
};

enum OBJECT
{
	OBJECT_PLAYER,
	OBJECT_ENEMY,
	OBJECT_MAX,

	OBJECT_NULL				//	�f�t�H���g�l�A�I�u�W�F�N�g�����̈Ӗ�
};

enum CAMERA_MODE
{
	CAMERA_MODE_NEAR,
	CAMERA_MODE_FAR,
	CAMERA_MODE_CUTSCENE,
	CAMERA_MODE_MAX
};

//��l���[�h����l���[�h��
enum PLAY_MODE
{
	PLAY_MODE_SINGLE,		//��̃v���C���[
	PLAY_MODE_DOUBLE,		//��̃v���C���[
	PLAY_MODE_MAX,

	PLAY_MODE_NULL			//�f�t�H���g�l
};

//�ُ��Ԃ��L�^
enum STATE
{
	NORMAL,					//�ُ��Ԗ���
	FROZEN,					//�������
	STATE_MAX
};

enum ITEMTYPE
{
	ITEMTYPE_COIN,			// �R�C��
	ITEMTYPE_ICEBLOCK,		// �����A�C�e��(�A�C�X�u���b�N)
	ITEMTYPE_MAX,

	ITEMTYPE_NULL			// �f�t�H���g�l�A�A�C�e�������̈Ӗ�
};

enum MAPPINGTYPE
{
	MAPPINGTYPE_ONE,		// ���b�V���ɁA�e�N�X�`���[���ꖇ�ɓ\��
	MAPPINGTYPE_ALL			// ���b�V���ɁA�e�N�X�`���[���d���ɓ\��

};



//*****************************************************************************
// �\���̒�`
//*****************************************************************************

// ��L�Q�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
struct VERTEX_2D
{
	D3DXVECTOR3		vtx;		// ���_���W
	float			rhw;		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR		diffuse;	// ���ˌ�
	D3DXVECTOR2		tex;		// �e�N�X�`�����W
};

// ��L�R�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
struct VERTEX_3D
{
	D3DXVECTOR3		vtx;		// ���_���W
	D3DXVECTOR3		nor;		// �@���x�N�g��
	D3DCOLOR		diffuse;	// ���ˌ�
	D3DXVECTOR2		tex;		// �e�N�X�`�����W
};

struct SRT
{
	D3DXVECTOR3		scl;		// �g��k��	
	D3DXVECTOR3		rot;		// ���݂̌���
	D3DXVECTOR3		pos;		// ���݂̈ʒu
};

//�L�[�t���[��
struct KEY
{
	int		frame;					//���̃L�[�t���[�����玟�̃L�[�t���[���܂ł̑��t���[����
	SRT		srtWork[PART_MAX];		//���̃L�[�t���[���ɂ����Ă̊e�p�[�c��SRT
};

//X�t�@�C���̃��f��
struct XMODEL
{
	char			*partFile;		// x�t�@�C�����
	LPD3DXBUFFER	pMatBuff;		// ���b�V���̃}�e���A�������i�[
	DWORD			nNumMat;		// �}�e���A�����̑���
	LPD3DXMESH		pMesh;			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^

	SRT				srt;			// ���f����srt
	D3DXMATRIX		mtxWorld;		// �����̑����[���h�}�g���b�N�X
	XMODEL			*parent;		// �e�Ɏw���|�C���^
	bool			use;			// �`�悷�邩�ǂ���
};

//���[�V����
struct MOTION
{
	const	KEY* motionData;		// ���[�V�����f�[�^
	int		numKey;					// ���[�V�����f�[�^�̃L�[�t���[���̐�
	bool	use;					// ���[�V�������Ă��邩�ǂ���
	float	motionTime;				// ���[�V�������Ă鎞�̑S�̎���
	float	cancelTime;				// ���[�V�������Ă�r���Œ��~���鎞�A�ŏ���Ԃɖ߂鎞��
};

//�v���C���[�ƃG�l�~�[�̃N���X
class Character
{
public: 
	XMODEL			part[PART_MAX];		//���f�����
	D3DXVECTOR3		move;				// �ړ���
	D3DXVECTOR3		rotDest;			// �ړI�̌���
	float			fRadius;			// ���a

	int				nIdxShadow;			// �eID

	ITEMTYPE		holdItem;			//�����Ă���A�C�e��
	STATE			state;				//�ُ��Ԃ̏��
	int				frozenTime;			//������Ԃ̎c�莞��

	MOTION			motion;				//�������[�V����

	OBJECT			objectType;			//�v���C���[���G�l�~�[��

	bool			upAI;				//AI�s�� ��
	bool			downAI;				//AI�s�� ��
	bool			leftAI;				//AI�s�� ��
	bool			rightAI;			//AI�s�� �E

	bool			useAI;				//AI���[�h���ǂ���

	//�����o�[�֐�==========================

	HRESULT Init(OBJECT object);

	void AIControl();
	int  AI(int type = 1);

	void Movement();
	void Motion(MOTION& motion);
	void AreaCollision();
	void Drag();
	void Jet();
	void ItemCollision();

	void UseIceblock();
	void Freeze(Character* target);

	void Frozen();

	void UpdateCharacter();
};

//�A�C�e��
struct ITEM : public XMODEL
{
	float		fRadius;		// ���a
	int			nIdxShadow;		// �eID
	ITEMTYPE	nType;			// �A�C�e�����
};

//�V���h�[
struct SHADOW
{
	float			size;		// �e�̋�`�|���S���̕ӂ̒���
	D3DXVECTOR3		pos;		// �ʒu
	bool			bUse;		// �g�p���Ă��邩�ǂ���
};

//�G�t�F�N�g
struct EFFECT
{
	D3DXVECTOR3		pos;		// �ʒu
	D3DXVECTOR3		rot;		// ��]
	D3DXVECTOR3		move;		// �ړ���
	D3DXCOLOR		col;		// �F
	float			fSizeX;		// ��
	float			fSizeY;		// ����
	int				nTimer;		// �^�C�}�[
	float			nDecAlpha;	// �A���t�@�l�̌����l
	bool			bUse;		// �g�p���Ă��邩�ǂ���
};

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

//�T�E���h�p�����[�^
struct SOUND_PARAM
{
	const char *pFilename;		// �t�@�C����
	bool isSoloTempStop;		// �P�Ƃňꎞ��~���ꂽ���Ƃ��邩�ǂ���

};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice, DWORD FVF, LPDIRECT3DVERTEXBUFFER9& vtxBuff, D3DXVECTOR3 vtx, float width, float height,
	D3DCOLOR diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), int num = 1);

HRESULT MakeVertexNumFrame(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9& vtxBuff, int numPlace,
	D3DXVECTOR3 numPos, float numWidth, float numHeight, float numInterval,
	D3DXVECTOR3 framePos, float frameWidth, float frameHeight,
	D3DCOLOR diffuse = D3DCOLOR_RGBA(255, 255, 255, 255));

HRESULT MakeVertexMesh(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9& vtxBuff, int numVertex,
	int numBlockH, int numBlockV,
	float blockSizeH, float blockSizeV, D3DCOLOR col, MAPPINGTYPE type);

HRESULT MakeIndexMesh(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DINDEXBUFFER9& idxBuff, int numIndex, int numBlockX, int numBlockZ);

void SetVtxDataVtx(LPDIRECT3DVERTEXBUFFER9 vtxBuff, DWORD FVF, D3DXVECTOR3 vtx, float width, float height, int index = 0);
void SetVtxDataRHW(LPDIRECT3DVERTEXBUFFER9 vtxBuff, float rhw, int index = 0);
void SetVtxDataNor(LPDIRECT3DVERTEXBUFFER9 vtxBuff, D3DXVECTOR3 nor, int index = 0);
void SetVtxDataCor(LPDIRECT3DVERTEXBUFFER9 vtxBuff, DWORD FVF, D3DCOLOR diffuse, int index = 0);
void SetVtxDataTex(LPDIRECT3DVERTEXBUFFER9 vtxBuff, DWORD FVF, D3DXVECTOR2 tex, float width, float height, int index = 0);

void SetVtxDataTexNum(LPDIRECT3DVERTEXBUFFER9 vtxBuff, int numSet, int numPlace);

void DrawPolygon(LPDIRECT3DDEVICE9 pDevice, DWORD FVF, LPDIRECT3DVERTEXBUFFER9 vtxBuff, LPDIRECT3DTEXTURE9 tex, int index = 0);
void DrawPolygon(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9 vtxBuff, LPDIRECT3DTEXTURE9 tex, int indexStart, int indexEnd);

void DrawPolygonMesh(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9 vtxBuff, LPDIRECT3DINDEXBUFFER9 idxBuff,
	D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPDIRECT3DTEXTURE9 tex,
	int numVertex, int numPolygon);

void LimitRot(float& radian);

KEY* GetMotionWalk();

void DrawXMODEL(LPDIRECT3DDEVICE9 pDevice, XMODEL* model, int numPart);

#endif


