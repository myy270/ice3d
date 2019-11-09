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

#define PART_MAX		(7)		// プレイヤーパーツ数
#define PART_MAX_ENEMY	(7)		// 敵パーツの数

#define	FPS	(60)

#define	FIRST_SCENE		(SCENE_GAME)		//最初の画面

//*****************************************************************************
// 列挙型定義
//*****************************************************************************
enum MAPPINGTYPE
{
	MAPPINGTYPE_ONE,			// テクスチャーを一枚に描画する
	MAPPINGTYPE_ALL,			// テクスチャーを重複に描画する

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

enum OBJECT		//
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
	ITEMTYPE_COIN,			// コイン
	ITEMTYPE_ICEBLOCK,		// アイスブロック

	ITEMTYPE_MAX
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

//キーフレームの定義
struct KEY
{
	int			frame;			//このキーフレームの総フレーム数
	SRT			key[PART_MAX];	//キーフレームのデータ
};

struct PART
{
	char *partFile;							//xファイル情報
	LPD3DXBUFFER		pMatBuff;			// メッシュのマテリアル情報を格納
	DWORD				nNumMat;			// マテリアル情報の総数
	LPD3DXMESH			pMesh;				// ID3DXMeshインターフェイスへのポインタ

	SRT			srt;						//Scaling Rotation Translation
	D3DXMATRIX	mtxWorld;
	PART		*parent;
	bool		use;
};

struct PLAYER
{
	D3DXVECTOR3 move;		// 移動量
	D3DXVECTOR3 rotDest;	// 目的の向き
	float fRadius;			// 半径
	int nIdxShadow;			// 影ID
	PART part[PART_MAX];

	ITEMTYPE holdItem;

	STATE state;
	int stateTime;
};

#endif




