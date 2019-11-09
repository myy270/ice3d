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
		for (int nCntPlace = 0; nCntPlace <= numPlace; nCntPlace++)		//nCntPlaceは数字の左から始める添え字
		{
			if (nCntPlace < numPlace)
			{//	スコアの数字

				// 頂点座標の設定
				SetVtxData(vtxBuff, D3DXVECTOR3(numPos.x + nCntPlace * (numWidth + numInterval), numPos.y, 0.0f), numWidth, numHeight, nCntPlace);

				//テクスチャ―座標の設定	初期値、あとで変更する
				SetVtxData(vtxBuff, D3DXVECTOR2(0.0f, 0.0f), 0.1f, 1.0f, nCntPlace);
			}
			else
			{//スコアのフレーム

				// 頂点座標の設定
				SetVtxData(vtxBuff, framePos, frameWidth, frameHeight, nCntPlace);

				//テクスチャ―座標の設定
				SetVtxData(vtxBuff, D3DXVECTOR2(0.0f, 0.0f), 1.0f, 1.0f, nCntPlace);
			}

			// rhwの設定
			SetVtxData(vtxBuff, 1.0f, nCntPlace);

			// 反射光の設定
			SetVtxData(vtxBuff, diffuse, nCntPlace);

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
// 頂点のテクスチャ座標をセット(連続数字の場合)
// numSet:一連の数字　numPlace:その数字の桁数
//=============================================================================
void SetVtxData(LPDIRECT3DVERTEXBUFFER9 vtxBuff,int numSet, int numPlace)
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
		SetVtxData(vtxBuff, D3DXVECTOR2(num * 0.1f, 0.0f), 0.1f, 1.0f, i);
	}

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

