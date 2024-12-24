//----------------------------------------
//
//ポリゴン表示処理[sphere.cpp]
//Author fuma sato
//
//----------------------------------------

#include"sphere.h"
#include"camera.h"
#include"effect.h"
#include"game.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSphere = NULL;//バッファのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSphere = NULL;//インデックスバッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureSphere[3] = { NULL };
Sphere g_aSphere[SPHERE_MAX];

//----------------------
//ポリゴンの初期化処理
//----------------------
void InitSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	VERTEX_3D* pVtx;//頂点情報ポインタ

	//デバイスの取得
	pDevice = GetDevice();

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * VT_MAX_SP,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSphere,
		NULL
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		SPHERE_TEX,
		&g_pTextureSphere[0]
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		SPHERE_TEX2,
		&g_pTextureSphere[1]
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		SPHERE_TEX3,
		&g_pTextureSphere[2]
	);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * INDEX_SP_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSphere,
		NULL
	);

	int nCntSphere, nCntSphere2;
	for (nCntSphere = 0; nCntSphere < SPHERE_MAX; nCntSphere++)
	{
		g_aSphere[nCntSphere].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSphere[nCntSphere].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSphere[nCntSphere].bUse = false;
	}
	//1つ目

	g_pVtxBuffSphere->Lock(0, 0, (void**)&pVtx, 0);

	//極頂点
	pVtx[0].pos = D3DXVECTOR3(0.0f, SPHERE_RADIUS, 0.0f);

	D3DXVECTOR3 npos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), dpos = D3DXVECTOR3(0.0f, SPHERE_RADIUS, 0.0f);
	npos = npos - dpos;
	D3DXVec3Normalize(&npos, &npos);
	pVtx[0].nor = npos;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

	pVtx[0].tex = D3DXVECTOR2((float)(((((SPHERE_RADIUS + SPHERE_RADIUS) * D3DX_PI) / SPHERE_WIDTH_DEF) / SPHERE_HNUM)), (float)((((SPHERE_RADIUS + SPHERE_RADIUS) * D3DX_PI * 0.5f) / SPHERE_HEIGHT_DEF) / SPHERE_VNUM));

	for (nCntSphere = 0; nCntSphere < SPHERE_VNUM; nCntSphere++)
	{//1枚分のZ軸のループ
		for (nCntSphere2 = 0; nCntSphere2 < SPHERE_HNUM + 1; nCntSphere2++)
		{//1枚分のX軸のループ

			//円形の角度
			float fangleH = (360.0f / SPHERE_HNUM) * nCntSphere2 * (D3DX_PI / 180.0f), fangleV = (SPHERE_ANG / SPHERE_VNUM) * (nCntSphere + 1) * (D3DX_PI / 180.0f);

			//座標設定
			pVtx[nCntSphere * (SPHERE_HNUM + 1) + nCntSphere2 + 1].pos = D3DXVECTOR3(sinf(fangleH) * sinf(fangleV) * SPHERE_RADIUS, cosf(fangleV) * SPHERE_RADIUS, cosf(fangleH) * sinf(fangleV) * SPHERE_RADIUS);

			//nor
			D3DXVECTOR3 npos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), dpos = D3DXVECTOR3(sinf(fangleH) * sinf(fangleV) * SPHERE_RADIUS, cosf(fangleV) * SPHERE_RADIUS, cosf(fangleH) * sinf(fangleV) * SPHERE_RADIUS);
			npos = npos - dpos;
			D3DXVec3Normalize(&npos, &npos);
			pVtx[nCntSphere * (SPHERE_HNUM + 1) + nCntSphere2 + 1].nor = npos;

			//カラー
			pVtx[nCntSphere * (SPHERE_HNUM + 1) + nCntSphere2 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

			//テクスチャ
			pVtx[nCntSphere * (SPHERE_HNUM + 1) + nCntSphere2 + 1].tex = D3DXVECTOR2((float)(((((SPHERE_RADIUS + SPHERE_RADIUS) * D3DX_PI) / SPHERE_WIDTH_DEF) / SPHERE_HNUM) * nCntSphere2), (float)((((SPHERE_RADIUS + SPHERE_RADIUS) * D3DX_PI * 0.5f) / SPHERE_HEIGHT_DEF) / SPHERE_VNUM) * nCntSphere);
		}
	}

	g_pVtxBuffSphere->Unlock();

	WORD* pIdx;
	g_pIdxBuffSphere->Lock(0, 0, (void**)&pIdx, 0);

	pIdx[0] = 0;
	for (nCntSphere = 1; nCntSphere < SPHERE_HNUM + 2; nCntSphere++)
	{//FAN部分
		pIdx[nCntSphere] = SPHERE_HNUM + 2 - nCntSphere;
	}
	for (nCntSphere = SPHERE_HNUM + 2; nCntSphere < INDEX_SP_NUM - (SPHERE_VNUM - 2) * 2; nCntSphere++)
	{//STRIP部分
		if ((nCntSphere - (SPHERE_HNUM + 2)) % (((SPHERE_HNUM + 1) * 2)) == 0 && (nCntSphere - (SPHERE_HNUM + 2)) != 0)
		{//縮退ポリゴン
			//インデックス指定
			pIdx[nCntSphere - 2 + (((nCntSphere - (SPHERE_HNUM + 2)) / ((SPHERE_HNUM + 1) * 2)) * 2)] = (SPHERE_HNUM + 1) - (SPHERE_HNUM + 1) * (((nCntSphere - (SPHERE_HNUM + 2)) - 1) % 2) + (((nCntSphere - (SPHERE_HNUM + 2)) - 1) / 2) + 1;

			//インデックス指定
			pIdx[nCntSphere - 1 + (((nCntSphere - (SPHERE_HNUM + 2)) / ((SPHERE_HNUM + 1) * 2)) * 2)] = (SPHERE_HNUM + 1) - (SPHERE_HNUM + 1) * ((nCntSphere - (SPHERE_HNUM + 2)) % 2) + ((nCntSphere - (SPHERE_HNUM + 2)) / 2) + 1;
		}

		//インデックス指定
		pIdx[nCntSphere + (((nCntSphere - (SPHERE_HNUM + 2)) / ((SPHERE_HNUM + 1) * 2)) * 2)] = (SPHERE_HNUM + 1) - (SPHERE_HNUM + 1) * ((nCntSphere - (SPHERE_HNUM + 2)) % 2) + ((nCntSphere - (SPHERE_HNUM + 2)) / 2) + 1;
	}

	g_pIdxBuffSphere->Unlock();
}

//-------------------
//ポリゴン終了処理
//-------------------
void UninitSphere(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureSphere[nCnt] != NULL)
		{
			g_pTextureSphere[nCnt]->Release();
			g_pTextureSphere[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffSphere != NULL)
	{
		g_pVtxBuffSphere->Release();
		g_pVtxBuffSphere = NULL;
	}
	//インデックスバッファの破棄
	if (g_pIdxBuffSphere != NULL)
	{
		g_pIdxBuffSphere->Release();
		g_pIdxBuffSphere = NULL;
	}
}

//-------------------
//ポリゴン更新処理
//-------------------
void UpdateSphere(void)
{
	VERTEX_3D* pVtx;//頂点情報ポインタ
	static float nCntTex;
	int nCntSphere, nCntSphere2;

	g_pVtxBuffSphere->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2((float)(((((SPHERE_RADIUS + SPHERE_RADIUS) * D3DX_PI) / SPHERE_WIDTH_DEF) / SPHERE_HNUM)) + nCntTex, (float)((((SPHERE_RADIUS + SPHERE_RADIUS) * D3DX_PI * 0.5f) / SPHERE_HEIGHT_DEF) / SPHERE_VNUM));

	for (nCntSphere = 0; nCntSphere < SPHERE_VNUM; nCntSphere++)
	{//1枚分のZ軸のループ
		for (nCntSphere2 = 0; nCntSphere2 < SPHERE_HNUM + 1; nCntSphere2++)
		{//1枚分のX軸のループ
			//テクスチャ
			pVtx[nCntSphere * (SPHERE_HNUM + 1) + nCntSphere2 + 1].tex = D3DXVECTOR2((float)(((((SPHERE_RADIUS + SPHERE_RADIUS) * D3DX_PI) / SPHERE_WIDTH_DEF) / SPHERE_HNUM) * nCntSphere2) + nCntTex, (float)((((SPHERE_RADIUS + SPHERE_RADIUS) * D3DX_PI * 0.5f) / SPHERE_HEIGHT_DEF) / SPHERE_VNUM) * nCntSphere);
		}
	}

	g_pVtxBuffSphere->Unlock();
	nCntTex += 0.0001f;
}

//-------------------
//ポリゴン描画処理
//-------------------
void DrawSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATRIX mtxRot, mtxTrans;//計算マトリックス

	//デバイスの取得
	pDevice = GetDevice();

	int nCntSphere;
	for (nCntSphere = 0; nCntSphere < SPHERE_MAX; nCntSphere++)
	{
		if (g_aSphere[nCntSphere].bUse)
		{
			//マトリックス初期化
			D3DXMatrixIdentity(&g_aSphere[nCntSphere].mtxWorld);

			//向きの反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aSphere[nCntSphere].rot.y, g_aSphere[nCntSphere].rot.x, g_aSphere[nCntSphere].rot.z);
			D3DXMatrixMultiply(&g_aSphere[nCntSphere].mtxWorld, &g_aSphere[nCntSphere].mtxWorld, &mtxRot);

			//位置の計算
			D3DXMatrixTranslation(&mtxTrans, g_aSphere[nCntSphere].pos.x, g_aSphere[nCntSphere].pos.y, g_aSphere[nCntSphere].pos.z);
			D3DXMatrixMultiply(&g_aSphere[nCntSphere].mtxWorld, &g_aSphere[nCntSphere].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aSphere[nCntSphere].mtxWorld);

			//頂点バッファ
			pDevice->SetStreamSource(0, g_pVtxBuffSphere, 0, sizeof(VERTEX_3D));

			//インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_pIdxBuffSphere);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			if (GetbSnow())
			{
				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureSphere[2]);

				//極ポリゴンの描画
				pDevice->DrawIndexedPrimitive
				(
					D3DPT_TRIANGLEFAN,//タイプ
					0,
					0,
					SPHERE_HNUM + 2,//頂点数
					0,
					SPHERE_HNUM//ポリゴンの個数
				);

				pDevice->SetTexture(0, g_pTextureSphere[2]);

				//ポリゴンの描画
				pDevice->DrawIndexedPrimitive
				(
					D3DPT_TRIANGLESTRIP,//タイプ
					0,
					0,
					VT_MAX_SP - (SPHERE_HNUM + 2),//頂点数
					SPHERE_HNUM + 2,
					POLYGON_SP_NUM - SPHERE_HNUM//ポリゴンの個数
				);
			}
			else
			{
				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureSphere[1]);

				//極ポリゴンの描画
				pDevice->DrawIndexedPrimitive
				(
					D3DPT_TRIANGLEFAN,//タイプ
					0,
					0,
					SPHERE_HNUM + 2,//頂点数
					0,
					SPHERE_HNUM//ポリゴンの個数
				);

				pDevice->SetTexture(0, g_pTextureSphere[0]);

				//ポリゴンの描画
				pDevice->DrawIndexedPrimitive
				(
					D3DPT_TRIANGLESTRIP,//タイプ
					0,
					0,
					VT_MAX_SP - (SPHERE_HNUM + 2),//頂点数
					SPHERE_HNUM + 2,
					POLYGON_SP_NUM - SPHERE_HNUM//ポリゴンの個数
				);
			}
		}
	}
}

//----------
//設定
//----------
void SetSphere(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntSphere;
	for (nCntSphere = 0; nCntSphere < SPHERE_MAX; nCntSphere++)
	{//球の数
		if (!g_aSphere[nCntSphere].bUse)
		{//使用していない
			//有効化
			g_aSphere[nCntSphere].pos = pos;
			g_aSphere[nCntSphere].rot = rot;
			g_aSphere[nCntSphere].bUse = true;
			break;
		}
	}
}