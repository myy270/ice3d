//=============================================================================
//
// メッシュ地面の処理 [meshfield.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "meshfield.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_FILENAME	"data/TEXTURE/ice.bm"											// 読み込むテクスチャファイル名

#define	POS_FIELD			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))									// メッシュフィールドの中心座標
#define	ROT_FIELD			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))									// メッシュフィールドの回転量
#define	NUM_BLOCK_H			(16)															//横方向のブロックの数
#define	NUM_BLOCK_V			(16)															//縦方向のブロックの数
#define	SIZE_BLOCK_H		(80.0f)															//横方向のブロックのサイズ
#define	SIZE_BLOCK_V		(80.0f)															//縦方向のブロックのサイズ

#define	NUM_VERTEX_FIELD	((NUM_BLOCK_H + 1) * (NUM_BLOCK_V + 1))							// 総頂点数
#define	NUM_VERTEXINDEX		((NUM_BLOCK_H + 1) * 2 * NUM_BLOCK_V + (NUM_BLOCK_V - 1) * 2)	// 総インデックス数 (頂点描画順番から導き出す法則)
#define	NUM_POLYGON_FIELD	(NUM_VERTEXINDEX - 2)											// 総ポリゴン数(退縮ポリゴンを含む）

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9			g_pD3DTextureField;			// テクスチャ読み込む場所
LPDIRECT3DVERTEXBUFFER9		g_pD3DVtxBuffField;			// 頂点バッファインターフェースへのポインタ
LPDIRECT3DINDEXBUFFER9		g_pD3DIdxBuffField;			// インデックスバッファインターフェースへのポインタ

HRESULT InitMeshField()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_FILENAME,		// ファイルの名前
								&g_pD3DTextureField);	// 読み込むメモリー

	//頂点バッファの作成
	MakeVertexMesh(pDevice, g_pD3DVtxBuffField, NUM_VERTEX_FIELD, NUM_BLOCK_H, NUM_BLOCK_V,
										SIZE_BLOCK_H, SIZE_BLOCK_V, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAPPINGTYPE_ONE);

	//インデックスバッファの作成
	MakeIndexMesh(pDevice, g_pD3DIdxBuffField, NUM_VERTEXINDEX, NUM_BLOCK_H, NUM_BLOCK_V);

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshField(void)
{
	SAFE_RELEASE(g_pD3DTextureField);
	SAFE_RELEASE(g_pD3DVtxBuffField);
	SAFE_RELEASE(g_pD3DIdxBuffField);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshField(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ライティングを無効に
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	DrawPolygonMesh(pDevice, g_pD3DVtxBuffField, g_pD3DIdxBuffField,
		POS_FIELD, ROT_FIELD, g_pD3DTextureField,
		NUM_VERTEX_FIELD, NUM_POLYGON_FIELD);

	// ライティングを有効に
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}