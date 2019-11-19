//=============================================================================
//
// メッシュ壁の処理 [meshwall.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "meshwall.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_MESHWALL		(128)							// 壁の総数
#define	TEXTURE_FILENAME	"data/TEXTURE/ice2.png"			// 読み込むテクスチャファイル名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

HRESULT MakeMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
						int numBlockH, int numBlockV, float sizeBlockH, float sizeBlockV, D3DXCOLOR col, MAPPINGTYPE type);

//*****************************************************************************
// 構造体定義
//*****************************************************************************

struct MESH_WALL
{
	LPDIRECT3DVERTEXBUFFER9 pD3DVtxBuff;		// 頂点バッファインターフェースへのポインタ
	LPDIRECT3DINDEXBUFFER9	pD3DIdxBuff;		// インデックスバッファインターフェースへのポインタ

	D3DXVECTOR3 pos;							// ポリゴン表示位置の中心座標
	D3DXVECTOR3 rot;							// ポリゴンの回転量

	int numVertex;								// 総頂点数	
	int numVertexIndex;							// 総インデックス数
	int numPolygon;								// 総ポリゴン数

};

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureMeshWall = NULL;		// テクスチャ読み込む場所

MESH_WALL			g_aMeshWall[MAX_MESHWALL];			// メッシュ壁ワーク
int					g_nNumMeshWall;						// メッシュ壁の数

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitMeshWall()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nNumMeshWall = 0;

	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
							TEXTURE_FILENAME,			// ファイルの名前
							&g_pD3DTextureMeshWall);	// 読み込むメモリー
 
	// 壁の初期化	※順番要注意、作る順番 ＝ 描画順番
	//北壁の地面
	MakeMeshWall(D3DXVECTOR3(0.0f, 0.0f, 1280.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									48, 16, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAPPINGTYPE_ALL);
	//南壁の地面
	MakeMeshWall(D3DXVECTOR3(0.0f, 0.0f, -1280.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									48, 16, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAPPINGTYPE_ALL);
	//西壁の地面
	MakeMeshWall(D3DXVECTOR3(-1280.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									16, 16, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAPPINGTYPE_ALL);
	//東壁の地面
	MakeMeshWall(D3DXVECTOR3(1280.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									16, 16, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAPPINGTYPE_ALL);

	//北壁
	MakeMeshWall(D3DXVECTOR3(0.0f, 0.0f, 640.0f), D3DXVECTOR3(-D3DX_PI * 0.50f, 0.0f, 0.0f),
									16, 4, 80.0f, 80.0f,D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAPPINGTYPE_ALL);
	//南壁
	MakeMeshWall(D3DXVECTOR3(0.0f, 0.0f, -640.0f), D3DXVECTOR3(D3DX_PI * 0.50f, 0.0f, 0.0f),
									16, 4, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAPPINGTYPE_ALL);
	//西壁
	MakeMeshWall(D3DXVECTOR3(-640.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI * 0.50f, -D3DX_PI * 0.50f, 0.0f),
									16, 4, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAPPINGTYPE_ALL);
	//東壁
	MakeMeshWall(D3DXVECTOR3(640.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI * 0.50f, D3DX_PI * 0.50f, 0.0f),
									16, 4, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAPPINGTYPE_ALL);

	//北壁の背面
	MakeMeshWall(D3DXVECTOR3(0.0f, 0.0f, -640.0f), D3DXVECTOR3(-D3DX_PI * 0.50f, 0.0f, 0.0f),
		16, 4, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), MAPPINGTYPE_ALL);
	//南壁の背面
	MakeMeshWall(D3DXVECTOR3(0.0f, 0.0f, 640.0f), D3DXVECTOR3(D3DX_PI * 0.50f, 0.0f, 0.0f),
		16, 4, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), MAPPINGTYPE_ALL);
	//西壁の背面
	MakeMeshWall(D3DXVECTOR3(640.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI * 0.50f, -D3DX_PI * 0.50f, 0.0f),
		16, 4, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), MAPPINGTYPE_ALL);
	//東壁の背面
	MakeMeshWall(D3DXVECTOR3(-640.0f, 0.0f, 0.0f), D3DXVECTOR3(-D3DX_PI * 0.50f, D3DX_PI * 0.50f, 0.0f),
		16, 4, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), MAPPINGTYPE_ALL);


	//北壁の屋根
	MakeMeshWall(D3DXVECTOR3(0.0f, 160.0f, 1280.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									48, 16, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), MAPPINGTYPE_ALL);
	//南壁の屋根
	MakeMeshWall(D3DXVECTOR3(0.0f, 160.0f, -1280.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									48, 16, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), MAPPINGTYPE_ALL);
	//西壁の屋根
	MakeMeshWall(D3DXVECTOR3(-1280.0f, 160.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									16, 16, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), MAPPINGTYPE_ALL);
	//東壁の屋根
	MakeMeshWall(D3DXVECTOR3(1280.0f, 160.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									16, 16, 80.0f, 80.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), MAPPINGTYPE_ALL);

	return S_OK;
}

//=============================================================================
// 壁の作成
// pos:ポリゴン表示位置の中心座標、rot:ポリゴンの回転量
// numVertex: 頂点の数
// numBlockH：横方向のブロックの数、numBlockV:縦方向のブロックの数
// blockSizeH:横方向のブロックのサイズ、blockSizeV:縦方向のブロックのサイズ
// type:テクスチャ―の貼り方
//=============================================================================
HRESULT MakeMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
					int numBlockH, int numBlockV, float sizeBlockH, float sizeBlockV, D3DXCOLOR col, MAPPINGTYPE type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	MESH_WALL *pMesh;

	if (g_nNumMeshWall >= MAX_MESHWALL)
	{
		return E_FAIL;
	}

	pMesh = &g_aMeshWall[g_nNumMeshWall];

	g_nNumMeshWall++;

	pMesh->pos = pos;
	pMesh->rot = rot;

	pMesh->numVertex = (numBlockH + 1) * (numBlockV + 1);
	pMesh->numVertexIndex = (numBlockH + 1) * 2 * numBlockV + (numBlockV - 1) * 2;
	pMesh->numPolygon = pMesh->numVertexIndex - 2;

	//頂点バッファの作成
	MakeVertexMesh(pDevice, pMesh->pD3DVtxBuff, pMesh->numPolygon, numBlockH, numBlockV, sizeBlockH, sizeBlockV, col, type);

	//インデックスバッファの作成
	MakeIndexMesh(pDevice, pMesh->pD3DIdxBuff, pMesh->numVertexIndex, numBlockH, numBlockV);


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshWall(void)
{
	for(int i = 0; i < g_nNumMeshWall; i++)
	{
		SAFE_RELEASE(g_aMeshWall[i].pD3DVtxBuff);
		SAFE_RELEASE(g_aMeshWall[i].pD3DIdxBuff);
	}

	SAFE_RELEASE(g_pD3DTextureMeshWall);

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshWall(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	MESH_WALL *pMesh;

	// ライティングを無効に
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for(int i = 0; i < g_nNumMeshWall; i++)
	{
		pMesh = &g_aMeshWall[i];

		DrawPolygonMesh(pDevice, pMesh->pD3DVtxBuff, pMesh->pD3DIdxBuff,
			pMesh->pos, pMesh->rot, g_pD3DTextureMeshWall,
			pMesh->numVertex, pMesh->numPolygon);
	}

	// ライティングを有効に
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

