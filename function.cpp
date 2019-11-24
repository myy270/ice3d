//=============================================================================
//
// 共通の機能 [function.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "function.h"

#include "shadow.h"
#include "camera.h"
#include "input.h"
#include "timer.h"
#include "item.h"
#include "debugproc.h"
#include "effect.h"
#include "score.h"
#include "player.h"
#include "enemy.h"
#include "sound.h"
#include "title.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//歩くモーションのデータ
KEY g_motionWalk[] =
{
	{
		15,
		{
			{// part 0
				D3DXVECTOR3(1.5000f,1.5000f,1.5000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,22.4000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,6.5000f,0.0000f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(5.0000f,5.0000f,0.0000f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,3.1416f,0.0000f),//R
				D3DXVECTOR3(-5.0000f,5.0000f,0.0000f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-3.0640f,-4.8730f,-0.4090f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(1.5000f,1.5000f,1.5000f),//S
				D3DXVECTOR3(-0.0385f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,22.4000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,6.5000f,0.0000f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(1.4923f,0.0000f,0.0000f),//R
				D3DXVECTOR3(5.0000f,5.0000f,0.0000f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.7069f,3.1416f,0.0000f),//R
				D3DXVECTOR3(-5.0000f,5.0000f,0.0000f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-1.0854f,0.0000f,0.0000f),//R
				D3DXVECTOR3(3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.9425f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-3.0640f,-4.8730f,-0.4090f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(1.5000f,1.5000f,1.5000f),//S
				D3DXVECTOR3(-0.0385f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,22.4000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,6.5000f,0.0000f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-0.8639f,0.0000f,0.0000f),//R
				D3DXVECTOR3(5.0000f,5.0000f,0.0000f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-1.0996f,3.1416f,0.0000f),//R
				D3DXVECTOR3(-5.0000f,5.0000f,0.0000f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.9425f,0.0000f,0.0000f),//R
				D3DXVECTOR3(3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-1.0854f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-3.0640f,-4.8730f,-0.4090f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(1.5000f,1.5000f,1.5000f),//S
				D3DXVECTOR3(-0.0385f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,22.4000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,6.5000f,0.0000f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(1.4923f,0.0000f,0.0000f),//R
				D3DXVECTOR3(5.0000f,5.0000f,0.0000f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.7069f,3.1416f,0.0000f),//R
				D3DXVECTOR3(-5.0000f,5.0000f,0.0000f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-1.0854f,0.0000f,0.0000f),//R
				D3DXVECTOR3(3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.9425f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-3.0640f,-4.8730f,-0.4090f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void Interpolation(int partNum, XMODEL *part, const SRT *srt1, const SRT *srt2, float rate);
void Interpolation(int partNum, XMODEL *part, const SRT *srt2, float rate);

//=============================================================================
// 頂点の作成
// FVF_VERTEX_3Dの時、引数のvtxは何の役割もない
// num:矩形の数
//=============================================================================
HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice, DWORD FVF, LPDIRECT3DVERTEXBUFFER9& vtxBuff, D3DXVECTOR3 vtx, float width, float height, 
																											D3DCOLOR diffuse, int num)
{
	if (FVF == FVF_VERTEX_2D)
	{
		// オブジェクトの頂点バッファを生成
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * num,	// 頂点データ用に確保するバッファサイズ(バイト単位)
			D3DUSAGE_WRITEONLY,				// 頂点バッファの使用法　
			FVF_VERTEX_2D,					// 使用する頂点フォーマット
			D3DPOOL_MANAGED,				// リソースのバッファを保持するメモリクラスを指定
			&vtxBuff,						// 頂点バッファインターフェースへのポインタ
			NULL)))							// NULLに設定
		{
			return E_FAIL;
		}
	}
	else if (FVF == FVF_VERTEX_3D)
	{
		// オブジェクトの頂点バッファを生成
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * num,	// 頂点データ用に確保するバッファサイズ(バイト単位)
			D3DUSAGE_WRITEONLY,				// 頂点バッファの使用法　
			FVF_VERTEX_3D,					// 使用する頂点フォーマット
			D3DPOOL_MANAGED,				// リソースのバッファを保持するメモリクラスを指定
			&vtxBuff,						// 頂点バッファインターフェースへのポインタ
			NULL)))							// NULLに設定
		{
			return E_FAIL;
		}
	}

	//頂点バッファの中身を埋める
	for (int i = 0; i < num; i++)
	{
		// 頂点座標の設定
		SetVtxDataVtx(vtxBuff, FVF, vtx, width, height, i);

		if (FVF == FVF_VERTEX_2D)
		{
			// RHWの設定
			SetVtxDataRHW(vtxBuff, 1.0f, i);
		}
		else if (FVF == FVF_VERTEX_3D)
		{
			// ノーマルの設定
			SetVtxDataNor(vtxBuff, D3DXVECTOR3(0.0f, 1.0f, 0.0f), i);
		}

		// 反射光の設定
		SetVtxDataCor(vtxBuff, FVF, diffuse, i);

		// テクスチャ座標の設定
		SetVtxDataTex(vtxBuff, FVF, D3DXVECTOR2(0.0f, 0.0f),1.0f,1.0f, i);

	}

	return S_OK;
}

//=============================================================================
// 数字とフレームの頂点の作成
// numPlace:数字の桁数　
// numPos:先頭の数字の左上頂点の座標	numWidth:単体の数字の幅		numHeight:単体の数字の高さ	numInterval:数字の表示間隔
// framePos:フレームの左上頂点の座標	frameWidth:フレームの幅		frameHeight:フレームの高さ
//	diffuse:全体の色
//=============================================================================
HRESULT MakeVertexNumFrame(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9& vtxBuff, int numPlace, 
												D3DXVECTOR3 numPos, float numWidth, float numHeight,float numInterval,
												D3DXVECTOR3 framePos, float frameWidth, float frameHeight,
												D3DCOLOR diffuse)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * (numPlace + 1),	//+1 はフレームを含むこと
		D3DUSAGE_WRITEONLY,				// 頂点バッファの使用法　
		FVF_VERTEX_2D,					// 使用する頂点フォーマット
		D3DPOOL_MANAGED,				// リソースのバッファを保持するメモリクラスを指定
		&vtxBuff,						// 頂点バッファインターフェースへのポインタ
		NULL)))							// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める		
		for (int nCntPlace = 0; nCntPlace < numPlace + 1; nCntPlace++)		//nCntPlaceは数字の左から始める添え字
		{
			if (nCntPlace < numPlace)
			{//	スコアの数字

				// 頂点座標の設定
				SetVtxDataVtx(vtxBuff, FVF_VERTEX_2D, D3DXVECTOR3(numPos.x + nCntPlace * (numWidth + numInterval), numPos.y, 0.0f), numWidth, numHeight, nCntPlace);

				//テクスチャ―座標の設定	初期値、あとで変更する
				SetVtxDataTex(vtxBuff, FVF_VERTEX_2D, D3DXVECTOR2(0.0f, 0.0f), 0.1f, 1.0f, nCntPlace);
			}
			else
			{//スコアのフレーム

				// 頂点座標の設定
				SetVtxDataVtx(vtxBuff, FVF_VERTEX_2D, framePos, frameWidth, frameHeight, nCntPlace);

				//テクスチャ―座標の設定
				SetVtxDataTex(vtxBuff, FVF_VERTEX_2D, D3DXVECTOR2(0.0f, 0.0f), 1.0f, 1.0f, nCntPlace);
			}

			// rhwの設定
			SetVtxDataRHW(vtxBuff, 1.0f, nCntPlace);

			// 反射光の設定
			SetVtxDataCor(vtxBuff, FVF_VERTEX_2D, diffuse, nCntPlace);

		}
	}

	return S_OK;
}

//=============================================================================
// メッシュフィールドの頂点バッファの作成
// numVertex: 頂点の数、
// numBlockH：横方向のブロックの数、numBlockV:縦方向のブロックの数
// blockSizeH:横方向のブロックのサイズ、blockSizeV:縦方向のブロックのサイズ
// type:テクスチャ―の貼り方
//=============================================================================
HRESULT MakeVertexMesh(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9& vtxBuff,int numVertex,
												int numBlockH, int numBlockV,
												float blockSizeH, float blockSizeV, D3DCOLOR col, MAPPINGTYPE type)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * numVertex,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,					// 頂点バッファの使用法　
		FVF_VERTEX_3D,						// 使用する頂点フォーマット
		D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
		&vtxBuff,							// 頂点バッファインターフェースへのポインタ
		NULL)))								// NULLに設定
	{
		return E_FAIL;
	}

	float texSizeH;		//横テクスチャ―座標
	float texSizeV;		//縦テクスチャ―座標

	// テクスチャ―座標
	if (type == MAPPINGTYPE_ONE)
	{//テクスチャーを一枚に描画する場合
		texSizeH = 1.0f / numBlockH;
		texSizeV = 1.0f / numBlockV;

	}
	else if(type == MAPPINGTYPE_ALL)
	{//テクスチャーを重複に描画する場合
		texSizeH = 1.0f;
		texSizeV = 1.0f;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < (numBlockV + 1); i++)
		{
			for (int j = 0; j < (numBlockH + 1); j++)
			{
				int idx = i * (numBlockH + 1) + j;

				// 頂点座標の設定　初期位置はXOZ平面
				pVtx[idx].vtx.x = -(numBlockH / 2.0f) * blockSizeH + j * blockSizeH;
				pVtx[idx].vtx.y = 0.0f;
				pVtx[idx].vtx.z = (numBlockV / 2.0f) * blockSizeV - i * blockSizeV;

				// 法線の設定	ノーマルは上にさす
				pVtx[idx].nor = D3DXVECTOR3(0.0f, 1.0, 0.0f);

				// 反射光の設定
				pVtx[idx].diffuse = col;

				// テクスチャ座標の設定
				pVtx[idx].tex.x = texSizeH * j;
				pVtx[idx].tex.y = texSizeV * i;
			}
		}

		// 頂点データをアンロックする
		vtxBuff->Unlock();
	}

	return S_OK;
}

//=============================================================================
// メッシュフィールドのインデックスバッファの作成
// numIndex: インデックスの数、
// numBlockH：横方向のブロックの数、numBlockV:縦方向のブロックの数
//=============================================================================
HRESULT MakeIndexMesh(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DINDEXBUFFER9& idxBuff, int numIndex,int numBlockH, int numBlockV)
{
	// オブジェクトのインデックスバッファを生成
	if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * numIndex,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,					// 頂点バッファの使用法　
		D3DFMT_INDEX16,						// 使用するインデックスフォーマット
		D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
		&idxBuff,							// インデックスバッファインターフェースへのポインタ
		NULL)))								// NULLに設定
	{
		return E_FAIL;
	}

	{//インデックスバッファの中身を埋める
		WORD *pIdx;

		// インデックスデータの範囲をロックし、インデックスバッファへのポインタを取得
		idxBuff->Lock(0, 0, (void**)&pIdx, 0);

		int nCntIdx = 0;
		for (int i = 0; i < numBlockV; i++)
		{//ここで、頂点描画の順番がわかるようになる
			if (i > 0)//最初の循環だけ、実行しない
			{// 縮退ポリゴンのためのダブりの設定
				pIdx[nCntIdx] = (i + 1) * (numBlockH + 1);
				nCntIdx++;
			}

			for (int nCntVtxX = 0; nCntVtxX < (numBlockH + 1); nCntVtxX++)
			{
				pIdx[nCntIdx] = (i + 1) * (numBlockH + 1) + nCntVtxX;
				nCntIdx++;
				pIdx[nCntIdx] = i * (numBlockH + 1) + nCntVtxX;
				nCntIdx++;
			}

			if (i < (numBlockV - 1))//最後の循環だけ、実行しない
			{// 縮退ポリゴンのためのダブりの設定
				pIdx[nCntIdx] = i * (numBlockH + 1) + numBlockH;
				nCntIdx++;
			}
		}

		// インデックスデータをアンロックする
		idxBuff->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点の座標をセット
// vtx:左上頂点の座標　width,height:範囲	index:矩形ポリゴンの番号
//=============================================================================
void SetVtxDataVtx(LPDIRECT3DVERTEXBUFFER9 vtxBuff, DWORD FVF, D3DXVECTOR3 vtx, float width, float height, int index)
{
	if (FVF == FVF_VERTEX_2D)
	{
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx = pVtx + index * NUM_VERTEX;

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(vtx.x, vtx.y, vtx.z);
		pVtx[1].vtx = D3DXVECTOR3(vtx.x + width, vtx.y, vtx.z);
		pVtx[2].vtx = D3DXVECTOR3(vtx.x, vtx.y + height, vtx.z);
		pVtx[3].vtx = D3DXVECTOR3(vtx.x + width, vtx.y + height, vtx.z);

		// 頂点データをアンロックする
		vtxBuff->Unlock();
	}
	else if (FVF == FVF_VERTEX_3D)
	{
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx = pVtx + index * NUM_VERTEX;

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-width / 2, 0.0f, height / 2);
		pVtx[1].vtx = D3DXVECTOR3(width / 2, 0.0f, height / 2);
		pVtx[2].vtx = D3DXVECTOR3(-width / 2, 0.0f, -height / 2);
		pVtx[3].vtx = D3DXVECTOR3(width / 2, 0.0f, -height / 2);

		// 頂点データをアンロックする
		vtxBuff->Unlock();
	}

}

//=============================================================================
// 頂点のRHWをセット
// 	index:矩形ポリゴンの番号
//=============================================================================
void SetVtxDataRHW(LPDIRECT3DVERTEXBUFFER9 vtxBuff, float rhw, int index)
{
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx = pVtx + index * NUM_VERTEX;

	// 反射光の設定
	pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = rhw;

	// 頂点データをアンロックする
	vtxBuff->Unlock();
}

//=============================================================================
// 頂点のノーマルをセット
// index:矩形ポリゴンの番号
//=============================================================================
void SetVtxDataNor(LPDIRECT3DVERTEXBUFFER9 vtxBuff, D3DXVECTOR3 nor, int index)
{
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx = pVtx + index * NUM_VERTEX;

	// 反射光の設定
	pVtx[0].nor =
	pVtx[1].nor =
	pVtx[2].nor =
	pVtx[3].nor = nor;

	// 頂点データをアンロックする
	vtxBuff->Unlock();
}

//=============================================================================
// 頂点の色をセット
// diffuse:頂点の色	index:矩形ポリゴンの番号
//=============================================================================
void SetVtxDataCor(LPDIRECT3DVERTEXBUFFER9 vtxBuff, DWORD FVF, D3DCOLOR diffuse, int index)
{
	if (FVF == FVF_VERTEX_2D)
	{
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx = pVtx + index * NUM_VERTEX;

		// 反射光の設定
		pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = diffuse;

		// 頂点データをアンロックする
		vtxBuff->Unlock();

	}
	else if(FVF == FVF_VERTEX_3D)
	{
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx = pVtx + index * NUM_VERTEX;

		// 反射光の設定
		pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = diffuse;

		// 頂点データをアンロックする
		vtxBuff->Unlock();
	}

}

//=============================================================================
// 頂点のテクスチャ座標をセット
// tex:左上頂点のテクスチャ座標　width,height:範囲	index:矩形ポリゴンの番号
//=============================================================================
void SetVtxDataTex(LPDIRECT3DVERTEXBUFFER9 vtxBuff, DWORD FVF, D3DXVECTOR2 tex, float width, float height, int index)
{
	if (FVF == FVF_VERTEX_2D)
	{
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx = pVtx + index * NUM_VERTEX;

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(tex.x, tex.y);
		pVtx[1].tex = D3DXVECTOR2(tex.x + width, tex.y);
		pVtx[2].tex = D3DXVECTOR2(tex.x, tex.y + height);
		pVtx[3].tex = D3DXVECTOR2(tex.x + width, tex.y + height);

		// 頂点データをアンロックする
		vtxBuff->Unlock();

	}
	else if (FVF == FVF_VERTEX_3D)
	{
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx = pVtx + index * NUM_VERTEX;

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(tex.x, tex.y);
		pVtx[1].tex = D3DXVECTOR2(tex.x + width, tex.y);
		pVtx[2].tex = D3DXVECTOR2(tex.x, tex.y + height);
		pVtx[3].tex = D3DXVECTOR2(tex.x + width, tex.y + height);

		// 頂点データをアンロックする
		vtxBuff->Unlock();
	}

}

//=============================================================================
// 頂点のテクスチャ座標をセット(連続数字の場合)
// numSet:一連の数字　numPlace:その数字の桁数
//=============================================================================
void SetVtxDataTexNum(LPDIRECT3DVERTEXBUFFER9 vtxBuff,int numSet, int numPlace)
{
	//タイマーの各桁の数字を求める
	for(int i = 0; i < numPlace; i++)			//iは数字の左から始まる添え字
	{
		int num;	//各桁の単体の数字

		//各桁の数字を左から計算する
		num = (numSet % (int)(powf(10.0f, (float)(numPlace - i))))			//指している桁の左部分を捨てて、残りの部分をとる;	例えば、numSet = 123, numPlace = 3 , i = 1の場合,分子 = 23
						/ (int)(powf(10.0f, (float)(numPlace - i - 1)));	//例えば、count = 123, NUM_PLACE = 3 ,i = 1の場合,分母 = 10
																			//結果num = 2,つまり添え字1の指している桁の数字が求められる

		//その桁の数字に対応するテクスチャをセット(テクスチャ―座標の変更により)
		SetVtxDataTex(vtxBuff, FVF_VERTEX_2D, D3DXVECTOR2(num * 0.1f, 0.0f), 0.1f, 1.0f, i);
	}

}

//=============================================================================
//　ポリゴンを描画する処理
// index:描画開始のインデックス
//=============================================================================
void DrawPolygon(LPDIRECT3DDEVICE9 pDevice, DWORD FVF, LPDIRECT3DVERTEXBUFFER9 vtxBuff, LPDIRECT3DTEXTURE9 tex, int index)
{
	if (FVF == FVF_VERTEX_2D)
	{
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_2D));
	}
	else if (FVF == FVF_VERTEX_3D)
	{
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));
	}

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF);

	// テクスチャの設定
	pDevice->SetTexture(0, tex);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (index * NUM_VERTEX), NUM_POLYGON);
}

//=============================================================================
//　ポリゴンを描画する処理	（連続に頂点を描画する場合)
//  index:矩形ポリゴンの番号
//=============================================================================
void DrawPolygon(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9 vtxBuff, LPDIRECT3DTEXTURE9 tex,int indexStart, int indexEnd)
{
	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, tex);

	for (int i = indexStart; i <= indexEnd; i++)
	{
		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * NUM_VERTEX, NUM_POLYGON);
	}

}

//=============================================================================
//　メッシュを描画する
//  pos:ポリゴン表示位置の中心座標、rot:ポリゴンの回転量
//  numVertex:頂点数	numPolygon:ポリゴン数
//=============================================================================
void DrawPolygonMesh(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9 vtxBuff, LPDIRECT3DINDEXBUFFER9 idxBuff, 
															D3DXVECTOR3 pos, D3DXVECTOR3 rot,LPDIRECT3DTEXTURE9 tex,
															int numVertex, int numPolygon)
{
	D3DXMATRIX mtxRot, mtxTranslate, mtxWorldField;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorldField);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxWorldField, &mtxWorldField, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorldField, &mtxWorldField, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorldField);

	// 頂点バッファをレンダリングパイプラインに設定
	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));

	// インデックスバッファをレンダリングパイプラインに設定 indicesはindexの複数
	pDevice->SetIndices(idxBuff);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, tex);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, numVertex, 0, numPolygon);

}

//=============================================================================
// 回転量の調整
// 効果：回転量が（-Pi,Pi）の範囲になる
// radian:ラジアン単位
//=============================================================================
void LimitRot(float& radian)
{
	while (1)
	{
		if (radian > D3DX_PI)
		{
			radian -= D3DX_PI * 2.0f;
		}
		else if (radian < -D3DX_PI)
		{
			radian += D3DX_PI * 2.0f;
		}
		else
		{
			break;
		}
	}
}

//=============================================================================
// モーションデータをゲット
//=============================================================================
KEY* GetMotionWalk()
{
	return g_motionWalk;
}

//=============================================================================
// Xファイルのモデルの描画（親子関係を持つパーツの描画もできる）
// model:対象モデルのポインタ
// numPart:モデルの数
//=============================================================================
void DrawXMODEL(LPDIRECT3DDEVICE9 pDevice, XMODEL* model, int numPart)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;
	D3DXMATERIAL *pD3DXMat;			// マテリアル情報に対するポインタ

	D3DMATERIAL9 matDef;			// デフォルトのマテリアル
	pDevice->GetMaterial(&matDef);	// デフォルトのマテリアルを取得

	for (int i = 0; i < numPart; i++)//パーツ番号
	{
		if (model[i].use)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&mtxWorld);

			// スケールを反映
			D3DXMatrixScaling(&mtxScl, model[i].srt.scl.x,
				model[i].srt.scl.y,
				model[i].srt.scl.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, model[i].srt.rot.y,
				model[i].srt.rot.x,
				model[i].srt.rot.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, model[i].srt.pos.x,
				model[i].srt.pos.y,
				model[i].srt.pos.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

			//親が存在する場合は親のワールドマトリクスを合成
			if (model[i].parent)
			{
				D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &model[i].parent->mtxWorld);
			}

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

			//ワールドマトリクスを保存
			model[i].mtxWorld = mtxWorld;

			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)model[i].pMatBuff->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)model[i].nNumMat; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, NULL);		//※テクスチャ―がなくても必要。そうしないと、この前のテクスチャ―が貼ってしまう

				// 描画
				model[i].pMesh->DrawSubset(nCntMat);
			}
		}
	}

	pDevice->SetMaterial(&matDef);// マテリアルをデフォルトに戻す

}

//=============================================================================
//メンバー変数に値を代入する処理 
//=============================================================================
HRESULT Character::Init(OBJECT object)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	motion.motionData = GetMotionWalk();
	motion.numKey = 4;
	motion.use = false;
	motion.motionTime = 0.0f;
	motion.cancelTime = 0.0f;

	if (object == OBJECT_PLAYER)
	{
		part[0].partFile = (char *)BODY_PLAYER;		//体　//根である親は一番先にしなければならない
		part[1].partFile = (char *)HEAD_PLAYER;		//頭
		part[2].partFile = (char *)HAND_PLAYER;		//左手
		part[3].partFile = (char *)HAND_PLAYER;		//右手
		part[4].partFile = (char *)LEG_PLAYER;		//左足
		part[5].partFile = (char *)LEG_PLAYER;		//右足
	}
	else if (object == OBJECT_ENEMY)
	{
		part[0].partFile = (char *)BODY_ENEMY;
		part[1].partFile = (char *)HEAD_ENEMY;
		part[2].partFile = (char *)HAND_ENEMY;
		part[3].partFile = (char *)HAND_ENEMY;
		part[4].partFile = (char *)LEG_ENEMY;
		part[5].partFile = (char *)LEG_ENEMY;
	}

	part[6].partFile = (char *)ICE_BLOCK;			//アイスブロック

	//パーツの情報の設定
	for (int i = 0; i < PART_MAX; i++)				//パーツ番号
	{
		// Xファイルの読み込み
		if (FAILED(D3DXLoadMeshFromX(part[i].partFile,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&part[i].pMatBuff,
			NULL,
			&part[i].nNumMat,
			&part[i].pMesh)))
		{
			return E_FAIL;
		}

		switch (i)
		{
		case 0:
		{//体
			part[i].srt.scl = D3DXVECTOR3(1.5f, 1.5f, 1.5f);			//スケールのxyz必ず同じように
			part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			part[i].srt.pos = D3DXVECTOR3(0.0f, 22.4f, 0.0f);			//足が地面に触れるように調整する

			if (object == OBJECT_ENEMY)
			{
				part[i].srt.pos.x = 90.0f;
			}

			part[i].parent = NULL;										//体の親はNULLにする
			break;
		}
		case 1:
		{//頭
			part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			part[i].srt.pos = D3DXVECTOR3(0.0f, 6.5f, 0.0f);			//関節の位置に移動する

			part[i].parent = &part[0];									//体を親にする
			break;
		}
		case 2:
		{//左手
			part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			part[i].srt.pos = D3DXVECTOR3(5.0f, 5.0f, 0.0f);			//関節の位置に移動する

			part[i].parent = &part[0];									//体を親にする
			break;
		}
		case 3:
		{//右手
			part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			part[i].srt.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
			part[i].srt.pos = D3DXVECTOR3(-5.0f, 5.0f, 0.0f);			//関節の位置に移動する

			part[i].parent = &part[0];									//体を親にする
			break;
		}
		case 4:
		{//左足
			part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			part[i].srt.pos = D3DXVECTOR3(3.064f, -4.873f, -0.409f);	//関節の位置に移動する

			part[i].parent = &part[0];									//体を親にする
			break;
		}
		case 5:
		{//右足
			part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			part[i].srt.pos = D3DXVECTOR3(-3.064f, -4.873f, -0.409f);	//関節の位置に移動する

			part[i].parent = &part[0];									//体を親にする
			break;
		}
		default:
		{//アイスブロック
			part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			part[i].srt.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			part[i].parent = &part[0];									//体を親にする
			break;
		}

		}//switch end

		if (i == 6)
		{//アイスブロックは最初表示しない
			part[i].use = false;
		}
		else
		{
			part[i].use = true;
		}
	}

	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	fRadius = RADIUS_BEAR;

	// 影を設定 ※体(part[0])を基準に
	nIdxShadow = SetShadow(part[0].srt.pos, fRadius * 2.0f);	//BUG影の大きさは変わらない

	holdItem = ITEMTYPE_NULL;
	state = NORMAL;
	frozenTime = 0;

	if ((object == OBJECT_ENEMY) && (GetPlayMode() == PLAY_MODE_SINGLE))
	{
		useAI = true;
	}
	else
	{
		useAI = false;
	}

	upAI	= false;
	downAI	= false;
	leftAI	= false;
	rightAI = false;

	objectType = object;

	return S_OK;
}

//=============================================================================
//AI関連の制御処理
//=============================================================================
void Character::AIControl()
{
	if (objectType == OBJECT_ENEMY)
	{
#ifdef _DEBUG
		//開発者機能
		if (GetKeyboardTrigger(DIK_ADD))		//テンキーのプラス+
		{//AIモードの切替
			useAI = !useAI;									//AIモードの切替

			upAI = downAI = leftAI = rightAI = false;		//リセット
		}
#endif
	}

	if (useAI)
	{
		AI(AI_TYPE);
	}

}

//=============================================================================
//type = 0:一番近いコインに向かって移動するAIの処理
//type = 1など:一番近いアイテム(コインを含む)に向かって移動するAIの処理
//=============================================================================
int Character::AI(int type)
{
	ITEM *item = GetItem();

	D3DXVECTOR3 vec;				//作業用
	float dis = 0.0f;				//アイテムとの距離
	float disNear = 99999999.0f;	//一番近い距離
	int tagetNo = -1;				//距離が一番近いアイテムの番号

	//一番近いアイテムの番号を検索する
	for (int i = 0; i < MAX_ITEM; i++, item++)
	{
		if (type == 0)
		{//一番近いコインの番号を取得する仕様
			if ((item->use) && (item->nType == ITEMTYPE_COIN))
			{
				//アイテムとのベクトルを求める
				vec = item->srt.pos - part[0].srt.pos;

				//アイテムとの距離を求める
				dis = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

				if (dis < disNear)
				{//この距離が今まで一番小さい場合、記録する
					disNear = dis;
					tagetNo = i;
				}
			}
		}
		else
		{//一番近いアイテムの番号を取得する仕様
			if ((item->use))
			{
				//アイテムとのベクトルを求める
				vec = item->srt.pos - part[0].srt.pos;

				//アイテムとの距離を求める
				dis = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

				if (dis < disNear)
				{//この距離が今まで一番小さい場合
					if ((item->nType == ITEMTYPE_ICEBLOCK) && (holdItem == ITEMTYPE_ICEBLOCK))
					{//このアイテムが凍結アイテム、且つ、すでに凍結アイテムを持っている場合、無視する

					}
					else
					{//記録する
						disNear = dis;
						tagetNo = i;
					}
				}
			}
		}
	}

	//一番近いアイテムに向かうように、移動方向を更新
	if (tagetNo != -1)
	{
		item = GetItem();		//ポインタをリセット

		vec = (item + tagetNo)->srt.pos - part[0].srt.pos;	//今の位置からアイテム位置までのベクトル

		//左右を判断
		if (vec.x < 0)
		{//左方向へ
			leftAI = 1;
			rightAI = 0;
		}
		else if (vec.x == 0)
		{//右方向へ
			leftAI = 0;
			rightAI = 0;
		}
		else if (vec.x > 0)
		{//左右方向なし
			leftAI = 0;
			rightAI = 1;
		}

		//上下を判断
		if (vec.z < 0)
		{//上方向へ
			upAI = 0;
			downAI = 1;
		}
		else if (vec.z == 0)
		{//下方向へ
			upAI = 0;
			downAI = 0;
		}
		else if (vec.z > 0)
		{//上下方向なし
			upAI = 1;
			downAI = 0;
		}

	}
	else
	{//コインがない場合
		leftAI = rightAI = upAI = downAI = 0;//止まる
	}

	//PrintDebugProc("AI(type %d)の一番近いアイテムの番号 ：%d \n\n", type, tagetNo);

	return tagetNo;

}

//=============================================================================
//位置と向きの更新処理
//=============================================================================
void Character::Movement()
{
	int upKey;					//キーボードのコントロールキー
	int downKey;
	int leftKey;
	int rightKey;	
	int padNo;					//コントローラー番号

	D3DXVECTOR3 rotCamera;		//カメラの向き
	float fDiffRotY;			//目的の角度までの差分

	if (objectType == OBJECT_PLAYER)
	{
		upKey = DIK_W;
		downKey = DIK_S;
		leftKey = DIK_A;
		rightKey = DIK_D;

		padNo = 0;
	}
	else if (objectType == OBJECT_ENEMY)
	{
		upKey = DIK_UP;
		downKey = DIK_DOWN;
		leftKey = DIK_LEFT;
		rightKey = DIK_RIGHT;

		padNo = 1;
	}

	// カメラの向き取得
	rotCamera = GetRotCamera();						//そのため、UpdatePlayer()はUpdateCamera()の後に置く

	if (objectType == OBJECT_ENEMY)
	{
		rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//エネミーの向きはカメラの回転と無関係である
	}

	//モーション状態をリセット
	motion.use = false;

	//時間が終わっていない、かつ凍結状態ではない場合、移動できる状態になる
	if ((IsTimeEnd() == false) && (state != FROZEN))
	{//移動			※前フレームの運動量が残っているから、慣性ある
		if (useAI ? leftAI : GetKeyboardPress(leftKey) || IsButtonPress(padNo, BUTTON_LEFT) || IsButtonPress(padNo, BUTTON_LSTICK_LEFT))
		{
			motion.use = true;//モーション状態にする

			if (useAI ? upAI : GetKeyboardPress(upKey) || IsButtonPress(padNo, BUTTON_UP) || IsButtonPress(padNo, BUTTON_LSTICK_UP))
			{// 左前移動
				move.x -= sinf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_BEAR;
				move.z -= cosf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_BEAR;

				rotDest.y = rotCamera.y + D3DX_PI * 0.75f;
			}
			else if (useAI ? downAI : GetKeyboardPress(downKey) || IsButtonPress(padNo, BUTTON_DOWN) || IsButtonPress(padNo, BUTTON_LSTICK_DOWN))
			{// 左後移動
				move.x -= sinf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_BEAR;
				move.z -= cosf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_BEAR;

				rotDest.y = rotCamera.y + D3DX_PI * 0.25f;
			}
			else
			{// 左移動
				move.x -= sinf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_BEAR;
				move.z -= cosf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_BEAR;

				rotDest.y = rotCamera.y + D3DX_PI * 0.50f;
			}
		}
		else if (useAI ? rightAI : GetKeyboardPress(rightKey) || IsButtonPress(padNo, BUTTON_RIGHT) || IsButtonPress(padNo, BUTTON_LSTICK_RIGHT))
		{
			motion.use = true;//モーション状態にする

			if (useAI ? upAI : GetKeyboardPress(upKey) || IsButtonPress(padNo, BUTTON_UP) || IsButtonPress(padNo, BUTTON_LSTICK_UP))
			{// 右前移動
				move.x -= sinf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_BEAR;
				move.z -= cosf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_BEAR;

				rotDest.y = rotCamera.y - D3DX_PI * 0.75f;
			}
			else if (useAI ? downAI : GetKeyboardPress(downKey) || IsButtonPress(padNo, BUTTON_DOWN) || IsButtonPress(padNo, BUTTON_LSTICK_DOWN))
			{// 右後移動
				move.x -= sinf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_BEAR;
				move.z -= cosf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_BEAR;

				rotDest.y = rotCamera.y - D3DX_PI * 0.25f;
			}
			else
			{// 右移動
				move.x -= sinf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_BEAR;
				move.z -= cosf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_BEAR;

				rotDest.y = rotCamera.y - D3DX_PI * 0.50f;
			}
		}
		else if (useAI ? upAI : GetKeyboardPress(upKey) || IsButtonPress(padNo, BUTTON_UP) || IsButtonPress(padNo, BUTTON_LSTICK_UP))
		{
			motion.use = true;//モーション状態にする

			// 前移動
			move.x -= sinf(D3DX_PI + rotCamera.y) * VALUE_MOVE_BEAR;
			move.z -= cosf(D3DX_PI + rotCamera.y) * VALUE_MOVE_BEAR;

			rotDest.y = rotCamera.y + D3DX_PI;		// - D3DX_PIになると、逆の方向に回転する
		}
		else if (useAI ? downAI : GetKeyboardPress(downKey) || IsButtonPress(padNo, BUTTON_DOWN) || IsButtonPress(padNo, BUTTON_LSTICK_DOWN))
		{
			motion.use = true;//モーション状態にする

			// 後移動
			move.x -= sinf(rotCamera.y) * VALUE_MOVE_BEAR;
			move.z -= cosf(rotCamera.y) * VALUE_MOVE_BEAR;

			rotDest.y = rotCamera.y;
		}
	}

	if (objectType == OBJECT_PLAYER)
	{
#ifdef _DEBUG		
		//開発者機能
		if (GetKeyboardPress(DIK_T))
		{// 上昇
			move.y += VALUE_MOVE_BEAR;
		}
		else if (GetKeyboardPress(DIK_Y))
		{// 下降
			move.y -= VALUE_MOVE_BEAR;
		}

		if (GetKeyboardPress(DIK_U))
		{// 左回転
			rotDest.y -= VALUE_ROTATE_BEAR;
		}
		else if (GetKeyboardPress(DIK_I))
		{// 右回転
			rotDest.y += VALUE_ROTATE_BEAR;
		}
#endif
	}

	LimitRot(rotDest.y);									//実際はなくてもいいが、数字がめちゃくちゃになる

	// 目的の角度までの差分
	fDiffRotY = rotDest.y - part[0].srt.rot.y;				//体(part[0])を基準に

	LimitRot(fDiffRotY);									// 重要! 近い方向に回転できるように

	// 回転量を体(part[0])に反映
	part[0].srt.rot.y += fDiffRotY * RATE_ROTATE_BEAR;			// 目的の角度まで慣性をかける　段々目的の角度に変化する

	LimitRot(part[0].srt.rot.y);							//実際はなくてもいいが、数字がめちゃくちゃになる

	/// 移動量を体(part[0])に反映
	part[0].srt.pos.x += move.x;
	part[0].srt.pos.y += move.y;
	part[0].srt.pos.z += move.z;

}

//=============================================================================
// モーションする処理
// motion:MOTION構造体の情報
//=============================================================================
void Character::Motion(MOTION& motion)
{
	int i = (int)motion.motionTime;  //現在のキーフレームナンバー

	//loopできるように
	if (i > motion.numKey - 2)//最大キーフレームナンバーを超えたら
	{
		motion.motionTime = 1.0f;
		i = (int)motion.motionTime;
	}

	float dt = 1.0f / motion.motionData[i].frame;//補間の間隔時間

	motion.motionTime += dt;

	if (motion.motionTime > motion.numKey - 1.0f)//最大時間を超えたら
	{
		motion.motionTime = motion.numKey - 1.0f;//最大時間にする
	}

	if (motion.motionTime - i > 1.0f) //誤差を修正　想定の1.0を超えたら
	{
		i++;//次のキーフレームに入る
	}

	if (motion.use == false)
	{//モーションしていない場合、途中のモーションからデフォルト状態に戻る
		motion.motionTime = 0.0f;	//リセット
		i = (int)motion.motionTime;	//重要

		if (state != FROZEN)
		{
			motion.cancelTime += dt;//0番キーフレームのtimeを使う
		}

		if (motion.cancelTime > 1.0f)//最大時間を超えたら
		{
			motion.cancelTime = 1.0f;//最大最大時間にする
		}

		Interpolation(PART_MAX - 1, &part[0], motion.motionData[i].srtWork, motion.cancelTime);

	}
	else
	{//モーションしている場合
		motion.cancelTime = 0.0f;	//リセット

		Interpolation(PART_MAX - 1, &part[0], motion.motionData[i].srtWork, motion.motionData[i + 1].srtWork, motion.motionTime - i);

	}

}

//=============================================================================
// 補間処理
// partNum:パーツの数
// part:出力する先の0番目のパーツ
// srt1:始点のsrt
// srt2:終点のsrt
// rate:始点から終点までの比率	(0～1.0)
//=============================================================================
void Interpolation(int partNum, XMODEL *part, const SRT *srt1, const SRT *srt2, float rate)
{
	for (int j = 0; j < partNum; j++)//パーツ番号
	{
		//// Scale
		//part[j].srt.scl.x = srt1[j].scl.x + (srt2[j].scl.x - srt1[j].scl.x) * rate;

		//part[j].srt.scl.y = srt1[j].scl.y + (srt2[j].scl.y - srt1[j].scl.y) * rate;

		//part[j].srt.scl.z = srt1[j].scl.z + (srt2[j].scl.z - srt1[j].scl.z) * rate;

		// Rotation
		part[j].srt.rot.x = srt1[j].rot.x + (srt2[j].rot.x - srt1[j].rot.x) * rate;

		//part[j].srt.rot.y = srt1[j].rot.y + (srt2[j].rot.y - srt1[j].rot.y) * rate;							

		//part[j].srt.rot.z = srt1[j].rot.z + (srt2[j].rot.z - srt1[j].rot.z) * rate;							

		// Position
		//part[j].srt.pos.x = srt1[j].pos.x + (srt2[j].pos.x - srt1[j].pos.x) * rate;							

		//part[j].srt.pos.y = srt1[j].pos.y + (srt2[j].pos.y - srt1[j].pos.y) * rate;							

		//part[j].srt.pos.z = srt1[j].pos.z + (srt2[j].pos.z - srt1[j].pos.z) * rate;							
	}

}

//=============================================================================
// 補間処理		(出力する先のデータを始点にする場合)
// partNum:パーツの数
// part:出力する先の0番目のパーツ
// srt2:終点のsrt
// rate:始点から終点までの比率	(0～1.0)
//=============================================================================
void Interpolation(int partNum, XMODEL *part, const SRT *srt2, float rate)
{
	for (int j = 0; j < partNum; j++)//パーツ番号
	{
		// Scale
		//part[j].srt.scl.x = part[j].srt.scl.x + (srt2[j].scl.x - part[j].srt.scl.x) * rate;

		//part[j].srt.scl.y = part[j].srt.scl.y + (srt2[j].scl.y - part[j].srt.scl.y) * rate;

		//part[j].srt.scl.z = part[j].srt.scl.z + (srt2[j].scl.z - part[j].srt.scl.z) * rate;

		// Rotation
		part[j].srt.rot.x = part[j].srt.rot.x + (srt2[j].rot.x - part[j].srt.rot.x) * rate;

		//part[j].srt.rot.y = part[j].srt.rot.y + (srt2[j].rot.y - part[j].srt.rot.y) * rate;							

		//part[j].srt.rot.z = part[j].srt.rot.z + (srt2[j].rot.z - part[j].srt.rot.z) * rate;							

		// Position
		//part[j].srt.pos.x = part[j].srt.pos.x + (srt2[j].pos.x - part[j].srt.pos.x) * rate;							

		//part[j].srt.pos.y = part[j].srt.pos.y + (srt2[j].pos.y - part[j].srt.pos.y) * rate;							

		//part[j].srt.pos.z = part[j].srt.pos.z + (srt2[j].pos.z - part[j].srt.pos.z) * rate;							
	}
}

//=============================================================================
// エリアコリジョン処理
//=============================================================================
void Character::AreaCollision()
{
	//移動範囲を設定する　※体(part[0])を基準に
	if (part[0].srt.pos.x < -630.0f)
	{
		part[0].srt.pos.x = -630.0f;
	}
	if (part[0].srt.pos.x > 630.0f)
	{
		part[0].srt.pos.x = 630.0f;
	}
	//if (part[0].srt.pos.y < HEIGHT_FROMLAND_BEAR)
	//{
	//	part[0].srt.pos.y = HEIGHT_FROMLAND_BEAR;
	//}
	//if (part[0].srt.pos.y > 150.0f)
	//{
	//	part[0].srt.pos.y = 150.0f;
	//}
	if (part[0].srt.pos.z > 630.0f)
	{
		part[0].srt.pos.z = 630.0f;
	}
	if (part[0].srt.pos.z < -630.0f)
	{
		part[0].srt.pos.z = -630.0f;
	}

}

//=============================================================================
// 移動抵抗力の処理
//=============================================================================
void Character::Drag()
{
	// 運動エネルギーを一部損して（抵抗力のため）保存する、次のフレームに使う(慣性の仕組み)
	//※損の部分イコール次のフレームに獲得の運動エネルギーの場合、速度が最大(7.8f)になって、等速直線運動になる
	move.x = move.x * (1 - RATE_MOVE_BEAR);
	move.y = move.y * (1 - RATE_MOVE_BEAR);
	move.z = move.z * (1 - RATE_MOVE_BEAR);

}

//=============================================================================
// 煙のエフェクト
//=============================================================================
void Character::Jet()
{
	D3DXVECTOR3 pos;		//作業用

	//移動距離が1より大きい場合、煙のエフェクトが出る
	if ((move.x * move.x
		+ move.y * move.y
		+ move.z * move.z) > 1.0f)
	{		
		//体(part[0])を基準に
		pos.x = part[0].srt.pos.x + sinf(part[0].srt.rot.y) * fRadius;	//尾部の辺りに設定
		pos.y = part[0].srt.pos.y - 19.4f;								//足元のところに設定
		pos.z = part[0].srt.pos.z + cosf(part[0].srt.rot.y) * fRadius;	//尾部の辺りに設定

		// エフェクトの設定
		if (objectType == OBJECT_PLAYER)
		{
			SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.85f, 0.15f, 0.0f, 0.50f), 14.0f, 14.0f, 20);	//赤
			SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.15f, 0.75f, 0.0f, 0.30f), 10.0f, 10.0f, 20);	//緑
			SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.0f, 0.10f, 0.0f, 0.15f), 5.0f, 5.0f, 20);		//緑
		}
		if (objectType == OBJECT_ENEMY)
		{
			SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.85f, 0.05f, 0.65f, 0.50f), 14.0f, 14.0f, 20);	//紫
			SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.65f, 0.85f, 0.05f, 0.30f), 10.0f, 10.0f, 20);	//黄
			SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.45f, 0.45f, 0.05f, 0.15f), 5.0f, 5.0f, 20);		//黄
		}
	}

}

//=============================================================================
// アイテムとの当たり判定
//=============================================================================
void Character::ItemCollision()
{
	ITEM *pItem;

	// アイテムを取得
	pItem = GetItem();

	if (!IsTimeEnd())
	{//時間が終わっていない限り、アイテムを取得できる
		for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
		{
			if (pItem->use == true)
			{
				float fLength;		//自身とアイテムの距離

				//バウンディングサークルBC //体(part[0])を基準に
				fLength = (part[0].srt.pos.x - pItem->srt.pos.x) * (part[0].srt.pos.x - pItem->srt.pos.x)
					+ (part[0].srt.pos.y - pItem->srt.pos.y) * (part[0].srt.pos.y - pItem->srt.pos.y)
					+ (part[0].srt.pos.z - pItem->srt.pos.z) * (part[0].srt.pos.z - pItem->srt.pos.z);

				if (fLength < (fRadius + pItem->fRadius) * (fRadius + pItem->fRadius))
				{//取得できる範囲内であれば
					if ((holdItem == ITEMTYPE_ICEBLOCK) && (pItem->nType == ITEMTYPE_ICEBLOCK))
					{//アイスブロックを持っている場合、他のアイスブロックは取得できない

					}
					else
					{
						if (pItem->nType == ITEMTYPE_ICEBLOCK)
						{
							holdItem = ITEMTYPE_ICEBLOCK;

							// 凍結アイテムを拾う効果音を再生
							PlaySound(SOUND_LABEL_SE_GETICEBLOCK, false, true);
						
						}
						else if (pItem->nType == ITEMTYPE_COIN)
						{
							// スコア加算
							ChangeScore(objectType, 100);

							// コインを拾う効果音を再生
							PlaySound(SOUND_LABEL_SE_COIN, false, true);
						}

						// アイテム消去
						DeleteItem(nCntItem);

						break;		//1フレームに、１個しか取得できない
					}
					
				}
			}
		}
	}

}

//=============================================================================
//凍結アイテムを使う
//=============================================================================
void Character::UseIceblock()
{
	int key;					//キーボードのコントロールキー
	int padNo;					//コントローラー番号
	Character* target;			//狙う目標

	if (objectType == OBJECT_PLAYER)
	{
		key = DIK_SPACE;
		padNo = 0;
		target = GetEnemy();
	}
	else
	{
		key = DIK_NUMPAD1;
		padNo = 1;
		target = GetPlayer();
	}

	//時間が終わっていない、且つ凍結状態ではない、且つ凍結アイテムを持っている場合、凍結アイテムを使用可能になる
	if ((IsTimeEnd() == false) && (state != FROZEN) && (holdItem == ITEMTYPE_ICEBLOCK))
	{
		if ((useAI) || (GetKeyboardTrigger(key) || IsButtonTrigger(padNo, BUTTON_CIRCLE)))
		{//AIモードでは凍結アイテムを拾ったら、直ぐ使う	
			Freeze(target);
		}
	}

}

//=============================================================================
// 凍結アイテムの効果
//=============================================================================
void Character::Freeze(Character* target)
{
	if (target->state != FROZEN)		//相手が凍結状態ではない場合
	{
		target->state = FROZEN;			//相手を凍結状態にさせる
		target->frozenTime = 180;		//3秒間
		holdItem = ITEMTYPE_NULL;		//自分の凍結アイテムが消耗される

		PlaySound(SOUND_LABEL_SE_USEICEBLOCK, false, true);		// 凍結アイテムを使う音を再生
	}
}

//=============================================================================
//凍結状態になった時の処理
//=============================================================================
void Character::Frozen()
{
	if (state == FROZEN)
	{
		if (frozenTime > 0)
		{
			frozenTime--;			//凍結状態の残り時間をカウントダウン
			part[6].use = true;		//身に纏うアイスブロックを表示する
		}
		else
		{
			state = NORMAL;			//凍結状態を解除
			part[6].use = false;	//身に纏うアイスブロックを消える
		}
	}
}

//=============================================================================
//プレイヤー、エネミーの更新処理のまとめ
//=============================================================================
void Character::UpdateCharacter()
{
	AIControl();

	Movement();

	//歩くモーション処理
	Motion(motion);

	AreaCollision();

	Drag();

	UpdateShadow(nIdxShadow, part[0].srt.pos, HEIGHT_FROMLAND_BEAR);

	Jet();

	ItemCollision();

	UseIceblock();

	Frozen();

}
