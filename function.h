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

#define SCREEN_WIDTH	(1280)				// ウインドウの幅
#define SCREEN_HEIGHT	(720)				// ウインドウの高さ
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)	// ウインドウの中心Ｘ座標
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	// ウインドウの中心Ｙ座標

#define	NUM_VERTEX		(4)		// 頂点数
#define	NUM_POLYGON		(2)		// ポリゴン数

#define SAFE_RELEASE(ptr)		{ if(ptr) { (ptr)->Release(); (ptr) = NULL; } }		//オブジェクトの解放

#define PART_MAX	(7)			// プレイヤーパーツ数
#define PART_MAX_ENEMY	(7)		// 敵パーツの数

#define	FPS	(60)

#define	FIRST_SCENE		(SCENE_TITLE)		//最初の画面

//*****************************************************************************
// 列挙型定義
//*****************************************************************************

//ゲームの画面
enum SCENE
{				
	SCENE_TITLE,				// タイトル画面
	SCENE_GAME,					// ゲーム画面
	SCENE_RESULT,				// リザルト画面
	SCENE_MAX					// デフォルト(なにもない状態、SetScene()を使わないとダメ)
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
	PLAY_MODE_SINGLE,//一つのプレイヤー
	PLAY_MODE_DOUBLE,//二つのプレイヤー
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
	char *partFile;
	//xファイル情報
	LPD3DXBUFFER		pMatBuff;			// メッシュのマテリアル情報を格納
	DWORD				nNumMat;			// マテリアル情報の総数
	LPD3DXMESH			pMesh;				// ID3DXMeshインターフェイスへのポインタ

	SRT			srt;		//Scaling Rotation Translation
	D3DXMATRIX	mtxWorld;
	PART		*parent;
	bool		use;
};

enum ITEMTYPE
{
	ITEMTYPE_COIN,		// コイン
	ITEMTYPE_ICEBLOCK,		// アイスブロック

	ITEMTYPE_MAX
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
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


#endif




