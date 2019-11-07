//=============================================================================
//
// 共通の機能 [function.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "function.h"


//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9& vtxBuff, D3DXVECTOR3 vtx, float width, float height)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
											D3DUSAGE_WRITEONLY,				// 頂点バッファの使用法　
											FVF_VERTEX_2D,					// 使用する頂点フォーマット
											D3DPOOL_MANAGED,				// リソースのバッファを保持するメモリクラスを指定
											&vtxBuff,						// 頂点バッファインターフェースへのポインタ
											NULL)))							// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める

		// 頂点座標の設定
		SetVtxData(vtxBuff, D3DXVECTOR3(vtx.x, vtx.y, vtx.z), width, height);

		// RHW用
		SetVtxData(vtxBuff, 1.0f);

		// 反射光の設定
		SetVtxData(vtxBuff, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// テクスチャ座標の設定
		SetVtxData(vtxBuff, D3DXVECTOR2(0.0f, 0.0f),1.0f,1.0f);

	}

	return S_OK;
}


//=============================================================================
// 頂点の作成	(1つ以上の矩形の頂点を格納する場合、初期設定なし)
// num:矩形の数
//=============================================================================
HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9& vtxBuff, int num)
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

	return S_OK;
}

//=============================================================================
// 頂点の座標をセット
// vtx:左上頂点の座標　width,height:範囲	index:矩形ポリゴンの番号
//=============================================================================
void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff, D3DXVECTOR3 vtx, float width, float height, int index)
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



//=============================================================================
// 頂点のRHWをセット
// 	index:矩形ポリゴンの番号
//=============================================================================
void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff, float rhw, int index)
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
// 頂点の色をセット
// diffuse:頂点の色	index:矩形ポリゴンの番号
//=============================================================================
void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff, D3DCOLOR diffuse, int index)
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

//=============================================================================
// 頂点のテクスチャ座標をセット
// tex:左上頂点のテクスチャ座標　width,height:範囲	index:矩形ポリゴンの番号
//=============================================================================
void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff, D3DXVECTOR2 tex, float width, float height, int index)
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




//=============================================================================
//　ポリゴンを描画する処理
//=============================================================================
void DrawPolygon(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9 vtxBuff, LPDIRECT3DTEXTURE9 tex)
{
	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, tex);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
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