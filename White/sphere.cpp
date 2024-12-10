//----------------------------------------
//
//ポリゴン表示処理[sphere.cpp]
//Author fuma sato
//
//----------------------------------------

#include"sphere.h"
#include"camera.h"
#include"effect.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSphere = NULL;//バッファのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSphere = NULL;//インデックスバッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureSphere[2] = { NULL };
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
		sizeof(VERTEX_3D) * VT_MAX_SP * SPHERE_MAX,
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

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * INDEX_SP_NUM * SPHERE_MAX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSphere,
		NULL
	);

	int nCntSphere, nCntSphere2, nCntSphere3;
	for (nCntSphere = 0; nCntSphere < SPHERE_MAX; nCntSphere++)
	{
		g_aSphere[nCntSphere].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSphere[nCntSphere].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSphere[nCntSphere].bUse = false;
	}
	//1つ目

	g_pVtxBuffSphere->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntSphere = 0; nCntSphere < SPHERE_MAX; nCntSphere++)
	{//球の数

		//極頂点
		pVtx[0].pos = D3DXVECTOR3(g_aSphere[nCntSphere].pos.x, g_aSphere[nCntSphere].pos.y + SPHERE_RADIUS, g_aSphere[nCntSphere].pos.z);

		D3DXVECTOR3 npos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), dpos = D3DXVECTOR3(g_aSphere[nCntSphere].pos.x, g_aSphere[nCntSphere].pos.y + SPHERE_RADIUS, g_aSphere[nCntSphere].pos.z);
		D3DXVec3Normalize(&npos, &dpos);
		pVtx[0].nor = -npos;

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

		pVtx[0].tex = D3DXVECTOR2((float)(((((SPHERE_RADIUS + SPHERE_RADIUS) * D3DX_PI) / SPHERE_WIDTH_DEF) / SPHERE_HNUM)), (float)((((SPHERE_RADIUS + SPHERE_RADIUS) * D3DX_PI * 0.5f) / SPHERE_HEIGHT_DEF) / SPHERE_VNUM));

		for (nCntSphere2 = 0; nCntSphere2 < SPHERE_VNUM/* - 1*/; nCntSphere2++)
		{//1枚分のZ軸のループ
			for (nCntSphere3 = 0; nCntSphere3 < SPHERE_HNUM + 1; nCntSphere3++)
			{//1枚分のX軸のループ

				//円形の角度
				float fangleH = (360.0f / SPHERE_HNUM) * nCntSphere3 * (D3DX_PI / 180.0f), fangleV = (SPHERE_ANG / SPHERE_VNUM) * (nCntSphere2 + 1) * (D3DX_PI / 180.0f);

				//座標設定
				pVtx[nCntSphere2 * (SPHERE_HNUM + 1) + nCntSphere3 + 1].pos = D3DXVECTOR3(g_aSphere[nCntSphere].pos.x + sinf(fangleH) * sinf(fangleV) * SPHERE_RADIUS, g_aSphere[nCntSphere].pos.y + cosf(fangleV) * SPHERE_RADIUS, g_aSphere[nCntSphere].pos.z + cosf(fangleH) * sinf(fangleV) * SPHERE_RADIUS);

				//nor
				D3DXVECTOR3 npos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), dpos = D3DXVECTOR3(g_aSphere[nCntSphere].pos.x + sinf(fangleH) * sinf(fangleV) * SPHERE_RADIUS, g_aSphere[nCntSphere].pos.y + cosf(fangleV) * SPHERE_RADIUS, g_aSphere[nCntSphere].pos.z + cosf(fangleH) * sinf(fangleV) * SPHERE_RADIUS);
				D3DXVec3Normalize(&npos, &dpos);
				pVtx[nCntSphere2 * (SPHERE_HNUM + 1) + nCntSphere3 + 1].nor = -npos;

				//カラー
				pVtx[nCntSphere2 * (SPHERE_HNUM + 1) + nCntSphere3 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

				//テクスチャ
				pVtx[nCntSphere2 * (SPHERE_HNUM + 1) + nCntSphere3 + 1].tex = D3DXVECTOR2((float)(((((SPHERE_RADIUS + SPHERE_RADIUS) * D3DX_PI) / SPHERE_WIDTH_DEF) / SPHERE_HNUM) * nCntSphere3), (float)((((SPHERE_RADIUS + SPHERE_RADIUS) * D3DX_PI * 0.5f) / SPHERE_HEIGHT_DEF) / SPHERE_VNUM) * nCntSphere2);
			}
		}

		////極頂点
		//pVtx[VT_MAX_SP - 1].pos = D3DXVECTOR3(g_aSphere[nCntSphere].pos.x, g_aSphere[nCntSphere].pos.y - SPHERE_RADIUS, g_aSphere[nCntSphere].pos.z);

		//npos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), dpos = D3DXVECTOR3(g_aSphere[nCntSphere].pos.x, g_aSphere[nCntSphere].pos.y - SPHERE_RADIUS, g_aSphere[nCntSphere].pos.z);
		//D3DXVec3Normalize(&npos, &dpos);
		//pVtx[VT_MAX_SP - 1].nor = npos;

		//pVtx[VT_MAX_SP - 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

		//pVtx[VT_MAX_SP - 1].tex = D3DXVECTOR2((float)(((((SPHERE_RADIUS + SPHERE_RADIUS) * D3DX_PI) / SPHERE_WIDTH_DEF) / SPHERE_HNUM)), (float)((((SPHERE_RADIUS + SPHERE_RADIUS) * D3DX_PI * 0.5f) / SPHERE_HEIGHT_DEF) / SPHERE_VNUM));

		pVtx += VT_MAX_SP;
	}

	g_pVtxBuffSphere->Unlock();

	WORD* pIdx;
	g_pIdxBuffSphere->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntSphere = 0; nCntSphere < SPHERE_MAX; nCntSphere++)
	{//球の数
		pIdx[0] = 0;
		for (nCntSphere2 = 1; nCntSphere2 < SPHERE_HNUM + 2; nCntSphere2++)
		{//FAN部分
			pIdx[nCntSphere2] = SPHERE_HNUM + 2 - nCntSphere2;
		}
		for (nCntSphere2 = SPHERE_HNUM + 2; nCntSphere2 < INDEX_SP_NUM - (SPHERE_VNUM - 2) * 2/* - SPHERE_HNUM*/; nCntSphere2++)
		{//STRIP部分
			if ((nCntSphere2 - (SPHERE_HNUM + 2)) % (((SPHERE_HNUM + 1) * 2)) == 0 && (nCntSphere2 - (SPHERE_HNUM + 2)) != 0)
			{//縮退ポリゴン
				//インデックス指定
				pIdx[nCntSphere2 - 2 + (((nCntSphere2 - (SPHERE_HNUM + 2)) / ((SPHERE_HNUM + 1) * 2)) * 2)] = (SPHERE_HNUM + 1) - (SPHERE_HNUM + 1) * (((nCntSphere2 - (SPHERE_HNUM + 2)) - 1) % 2) + (((nCntSphere2 - (SPHERE_HNUM + 2)) - 1) / 2) + 1;

				//インデックス指定
				pIdx[nCntSphere2 - 1 + (((nCntSphere2 - (SPHERE_HNUM + 2)) / ((SPHERE_HNUM + 1) * 2)) * 2)] = (SPHERE_HNUM + 1) - (SPHERE_HNUM + 1) * ((nCntSphere2 - (SPHERE_HNUM + 2)) % 2) + ((nCntSphere2 - (SPHERE_HNUM + 2)) / 2) + 1;
			}

			//インデックス指定
			pIdx[nCntSphere2 + (((nCntSphere2 - (SPHERE_HNUM + 2)) / ((SPHERE_HNUM + 1) * 2)) * 2)] = (SPHERE_HNUM + 1) - (SPHERE_HNUM + 1) * ((nCntSphere2 - (SPHERE_HNUM + 2)) % 2) + ((nCntSphere2 - (SPHERE_HNUM + 2)) / 2) + 1;
		}

		//for (nCntSphere2 = 1; nCntSphere2 < SPHERE_HNUM + 2; nCntSphere2++)
		//{//FAN部分
		//	pIdx[INDEX_SP_NUM - nCntSphere2] = VT_MAX_SP - (nCntSphere2 + 1);
		//}
		//pIdx[INDEX_SP_NUM - (SPHERE_HNUM + 2)] = VT_MAX_SP - 1;

		pIdx += INDEX_SP_NUM;
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

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureSphere[1]);

			//極ポリゴンの描画
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLEFAN,//タイプ
				0,
				0,
				SPHERE_HNUM + 2,//頂点数
				nCntSphere * INDEX_SP_NUM,
				SPHERE_HNUM//ポリゴンの個数
			);

			pDevice->SetTexture(0, g_pTextureSphere[0]);

			//ポリゴンの描画
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLESTRIP,//タイプ
				0,
				0,
				VT_MAX_SP - (SPHERE_HNUM + 2)/* * 2*/,//頂点数
				nCntSphere * INDEX_SP_NUM + SPHERE_HNUM + 2,
				POLYGON_SP_NUM - SPHERE_HNUM/* * 2*///ポリゴンの個数
			);

			//pDevice->SetTexture(0, g_pTextureSphere[1]);

			////極ポリゴンの描画
			//pDevice->DrawIndexedPrimitive
			//(
			//	D3DPT_TRIANGLEFAN,//タイプ
			//	0,
			//	0,
			//	SPHERE_HNUM + 2,//頂点数
			//	nCntSphere * INDEX_SP_NUM + INDEX_SP_NUM - (SPHERE_HNUM + 2),
			//	SPHERE_HNUM//ポリゴンの個数
			//);
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