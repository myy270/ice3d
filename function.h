//=============================================================================
//
// 共通の機能 [function.h]
// Author : 麦英泳
//
//=============================================================================
#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <d3dx9.h>						// DX関連のライブラリー
#include "dx.h"

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************

#if 1	// [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル"に対象ライブラリを設定する]
#pragma comment (lib, "d3d9.lib")		//DX関係
#pragma comment (lib, "d3dx9.lib")		//DX関係
#pragma comment (lib, "dinput8.lib")	//DXのinput関係
#pragma comment (lib, "dxguid.lib")		//DXのinput関係
#pragma comment (lib, "winmm.lib")		//time関係
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************

// ２Ｄポリゴン頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// ３Ｄポリゴン頂点フォーマット( 頂点座標[3D] / 法線 / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define SCREEN_WIDTH	(1280)				// 実際のウインドウの幅(int型必須)
#define SCREEN_HEIGHT	(720)				// 実際のウインドウの高さ(int型必須)

#define DESIGN_SCREEN_WIDTH		(1280.0f)			// 設計するときのウインドウの幅(小数点必須)
#define DESIGN_SCREEN_HEIGHT	(720.0f)			// 設計するときのウインドウの高さ(小数点必須)

#define TEXTURE_AUTOFIT_WIDTH			(SCREEN_WIDTH  / DESIGN_SCREEN_WIDTH)			// 画面サイズに応じての幅の調整比率
#define TEXTURE_AUTOFIT_HEIGHT			(SCREEN_HEIGHT / DESIGN_SCREEN_HEIGHT)			// 画面サイズに応じての高さの調整比率

#define FIT_WIDTH(width)		((width) * TEXTURE_AUTOFIT_WIDTH)		// 調整後の幅の計算式  (width:リソースの幅)
#define FIT_HEIGHT(height)		((height) * TEXTURE_AUTOFIT_HEIGHT)		// 調整後の高さの計算式  (height:リソースの高さ)

#define TEXTURE_CENTER_X(width)			((SCREEN_WIDTH - (width)) / 2.0f)				// 画面の横方向の真中におくようにポリゴンの左上頂点のX座標	(width:テクスチャの調整後の幅)
#define TEXTURE_CENTER_Y(height)		((SCREEN_HEIGHT - (height)) / 2.0f)				// 画面の縦方向の真中におくようにポリゴンの左上頂点のY座標	(height:テクスチャの調整後の高さ)


#define	NUM_VERTEX		(4)		// 頂点数
#define	NUM_POLYGON		(2)		// ポリゴン数

#define SAFE_RELEASE(ptr)		{ if(ptr) { (ptr)->Release(); (ptr) = NULL; } }		//オブジェクトの解放


#define PART_MAX			(7)		// パーツの数(アイスブロックを含む)

#define	FPS	(60)

#define	FIRST_SCENE		(SCENE_GAME)		//最初の画面

#define	BODY_PLAYER		"data/MODEL/bearBody.x"			// 読み込むモデル名
#define	HEAD_PLAYER		"data/MODEL/bearHead.x"			// 読み込むモデル名
#define	HAND_PLAYER		"data/MODEL/bearHand.x"			// 読み込むモデル名
#define	LEG_PLAYER		"data/MODEL/bearLeg.x"			// 読み込むモデル名
#define	ICE_BLOCK		"data/MODEL/iceBlock.x"			// 読み込むモデル名

#define	BODY_ENEMY		"data/MODEL/bearBodyPink.x"		// 読み込むモデル名
#define	HEAD_ENEMY		"data/MODEL/bearHeadPink.x"		// 読み込むモデル名
#define	HAND_ENEMY		"data/MODEL/bearHandPink.x"		// 読み込むモデル名
#define	LEG_ENEMY		"data/MODEL/bearLegPink.x"		// 読み込むモデル名

#define	RADIUS_BEAR			(15.0f)						// 熊モデルの半径	//影の大きさ、煙のエフェクトの位置や、アイテムとの当たる距離 と関係ある

#define	VALUE_MOVE			(0.195f)					// 移動量
#define	RATE_MOVE_PLAYER	(0.025f)					// 移動抵抗力の係数		※小さければ小さいほど、滑りやすい

#define	VALUE_ROTATE		(D3DX_PI * 0.025f)			// 回転量	4.5度相当
#define	RATE_ROTATE			(0.10f)						// 回転速度係数

#define	HEIGHT_FROMLAND		(22.4f)						// 体パーツの地面からの高さ(srt.pos.y)

#define	MAX_ITEM			(128)						// アイテムの最大数



//*****************************************************************************
// 列挙型定義
//*****************************************************************************

// フェードの状態
enum FADETYPE
{
	FADE_NONE = 0,			// フェード処理なしの状態
	FADE_IN,				// フェードイン処理
	FADE_OUT,				// フェードアウト処理
	FADE_MAX
};

// ゲーム画面
enum SCENE
{
	SCENE_TITLE,			// タイトル画面
	SCENE_GAME,				// ゲーム画面
	SCENE_RESULT,			// リザルト画面
	SCENE_MAX				// デフォルト値(なにもない状態、SetScene()を使わないとダメ)
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
	PLAY_MODE_SINGLE,		//一つのプレイヤー
	PLAY_MODE_DOUBLE,		//二つのプレイヤー
	PLAY_MODE_MAX
};

enum STATE			//異常状態を記録
{
	NORMAL,			//異常状態無し
	FROZEN,			//凍結状態
	STATE_MAX
};

enum ITEMTYPE
{
	ITEMTYPE_COIN,			// コイン	//他のアイテムを持っていない時のデフォルト値
	ITEMTYPE_ICEBLOCK,		// 凍結アイテム(アイスブロック)

	ITEMTYPE_MAX
};

enum MAPPINGTYPE
{
	MAPPINGTYPE_ONE,			// テクスチャーを一枚に描画する
	MAPPINGTYPE_ALL,			// テクスチャーを重複に描画する

};

//*****************************************************************************
// 構造体定義
//*****************************************************************************

// 上記２Ｄポリゴン頂点フォーマットに合わせた構造体を定義
struct VERTEX_2D
{
	D3DXVECTOR3 vtx;		// 頂点座標
	float rhw;				// テクスチャのパースペクティブコレクト用
	D3DCOLOR diffuse;		// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
};

// 上記３Ｄポリゴン頂点フォーマットに合わせた構造体を定義
struct VERTEX_3D
{
	D3DXVECTOR3 vtx;		// 頂点座標
	D3DXVECTOR3 nor;		// 法線ベクトル
	D3DCOLOR diffuse;		// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
};

struct SRT
{
	D3DXVECTOR3 scl;		// 拡大縮小	
	D3DXVECTOR3 rot;		// 現在の向き
	D3DXVECTOR3 pos;		// 現在の位置
};

//キーフレーム
struct KEY
{
	int			frame;					//このキーフレームから次のキーフレームまでの総フレーム数
	SRT			srtWork[PART_MAX];		//このキーフレームにおいての各パーツのSRT
};

//Xファイルのモデル
struct XMODEL
{
	char *partFile;							// xファイル情報
	LPD3DXBUFFER		pMatBuff;			// メッシュのマテリアル情報を格納
	DWORD				nNumMat;			// マテリアル情報の総数
	LPD3DXMESH			pMesh;				// ID3DXMeshインターフェイスへのポインタ

	SRT			srt;						// モデルのsrt
	D3DXMATRIX	mtxWorld;
	XMODEL		*parent;
	bool		use;
};

//モーション
struct MOTION
{
	const KEY* motionData;		// モーションデータ
	int numKey;					// モーションデータのキーフレームの数
	bool use;					// モーションしているかどうか
	float motionTime;			// モーションしてる時の全体時間
	float cancelTime;			// モーションしてる途中で中止する時、最初状態に戻る時間
};

//プレイヤーとエネミーのクラス
class Character
{
public: 
	XMODEL part[PART_MAX];
	D3DXVECTOR3 move;		// 移動量
	D3DXVECTOR3 rotDest;	// 目的の向き
	float fRadius;			// 半径

	int nIdxShadow;			// 影ID

	ITEMTYPE holdItem;		//持っているアイテム
	STATE state;			//異常状態の情報
	int frozenTime;			//凍結状態の残り時間

	MOTION motion;			//歩くモーション

	OBJECT objectType;		//プレイヤーかエネミーか

	bool upAI;				//AI行動 上
	bool downAI;			//AI行動 下
	bool leftAI;			//AI行動 左
	bool rightAI;			//AI行動 右

	bool useAI;				//AIモードかどうか

	//メンバー関数==========================

	HRESULT Init(OBJECT object);
	void AIControl();
	int  AI(int type = 1);
	void Movement();
	void AreaCollision();
	void Drag();

	void Jet();
	void ItemCollision();
	void UseIceblock();
	void Freeze(Character* target);
	void Frozen();


};

//アイテム
struct ITEM : public XMODEL
{
	float		fRadius;		// 半径
	int			nIdxShadow;		// 影ID
	ITEMTYPE	nType;			// アイテム種類
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9& vtxBuff, D3DXVECTOR3 vec, float width, float height);

HRESULT MakeVertexNumFrame(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9& vtxBuff, int numPlace,
	D3DXVECTOR3 numPos, float numWidth, float numHeight, float numInterval,
	D3DXVECTOR3 framePos, float frameWidth, float frameHeight,
	D3DCOLOR diffuse = D3DCOLOR_RGBA(255, 255, 255, 255));

HRESULT MakeVertexMesh(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9& vtxBuff, int numVertex,
	int numBlockH, int numBlockV,
	float blockSizeH, float blockSizeV, D3DCOLOR col, MAPPINGTYPE type);

HRESULT MakeIndexMesh(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DINDEXBUFFER9& idxBuff, int numIndex, int numBlockX, int numBlockZ);

void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff, D3DXVECTOR3 vtx, float width, float height, int index = 0);
void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff, float rhw, int index = 0);
void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff, D3DCOLOR diffuse, int index = 0);
void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff, D3DXVECTOR2 tex, float width, float height, int index = 0);

void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff, int numSet, int numPlace);

void DrawPolygon(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9 vtxBuff, LPDIRECT3DTEXTURE9 tex);
void DrawPolygon(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9 vtxBuff, LPDIRECT3DTEXTURE9 tex, int indexStart, int indexEnd);

void DrawPolygonMesh(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9 vtxBuff, LPDIRECT3DINDEXBUFFER9 idxBuff,
	D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPDIRECT3DTEXTURE9 tex,
	int numVertex, int numPolygon);

void LimitRot(float& radian);

KEY* GetMotionWalk();

void Motion(Character& user, MOTION& motion);

void DrawXMODEL(LPDIRECT3DDEVICE9 pDevice, XMODEL* model, int numPart);

void Shadow(int nIdxShadow, D3DXVECTOR3 pos);

#endif


