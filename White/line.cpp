//----------------------------------------
//
//ポリゴン表示処理[line.cpp]
//Author fuma sato
//
//----------------------------------------

#include"line.h"
#include"player.h"
#include"ui.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLine = NULL;//バッファのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffLine = NULL;//インデックスバッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureLine = NULL;
Line g_aLine[LINE_MAX];

//----------------------
//ポリゴンの初期化処理
//----------------------
void InitLine(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	VERTEX_3D* pVtx;//頂点情報ポインタ

	//デバイスの取得
	pDevice = GetDevice();

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * VT_MAX_LINE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLine,
		NULL
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		LINE_TEX,
		&g_pTextureLine
	);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * INDEX_NUM_LINE,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffLine,
		NULL
	);

	int nCntLine, nCntLine2;
	for (nCntLine = 0; nCntLine < LINE_MAX; nCntLine++)
	{
		g_aLine[nCntLine].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLine[nCntLine].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLine[nCntLine].fLength = sqrtf(LINE_WIDTH * LINE_WIDTH + LINE_Z * LINE_Z) / 2.0f;//対角線の長さ
		g_aLine[nCntLine].fAngle = atan2f(LINE_WIDTH, LINE_Z);//角度
		g_aLine[nCntLine].bUse = false;
	}
	//1つ目

	g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLine = 0; nCntLine< LINE_ZNUM + 1; nCntLine++)
	{//1枚分のZ軸のループ
		for (nCntLine2 = 0; nCntLine2 < LINE_XNUM + 1; nCntLine2++)
		{//1枚分のX軸のループ
			//座標設定
			pVtx[nCntLine * (LINE_XNUM + 1) + nCntLine2].pos = D3DXVECTOR3(-LINE_WIDTH * 0.5f + (LINE_WIDTH / LINE_XNUM) * nCntLine2, LINE_HEIGHT, LINE_Z * 0.5f - (LINE_Z / LINE_ZNUM) * nCntLine);

			//nor
			pVtx[nCntLine * (LINE_XNUM + 1) + nCntLine2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//カラー
			pVtx[nCntLine * (LINE_XNUM + 1) + nCntLine2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ
			pVtx[nCntLine * (LINE_XNUM + 1) + nCntLine2].tex = D3DXVECTOR2(((LINE_WIDTH / LINE_WIDTH_DEF) / LINE_XNUM) * nCntLine2, ((LINE_Z / LINE_Z_DEF) / LINE_ZNUM) * nCntLine);
		}
	}

	g_pVtxBuffLine->Unlock();

	WORD* pIdx;
	g_pIdxBuffLine->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntLine = 0; nCntLine < INDEX_NUM_LINE - (LINE_ZNUM - 1) * 2; nCntLine++)
	{
		if (nCntLine % ((LINE_XNUM + 1) * 2) == 0 && nCntLine != 0)
		{
			//インデックス指定
			pIdx[nCntLine - 2 + ((nCntLine / ((LINE_XNUM + 1) * 2)) * 2)] = (LINE_XNUM + 1) - (LINE_XNUM + 1) * ((nCntLine - 1) % 2) + ((nCntLine - 1) / 2);
			//インデックス指定
			pIdx[nCntLine - 1 + ((nCntLine / ((LINE_XNUM + 1) * 2)) * 2)] = (LINE_XNUM + 1) - (LINE_XNUM + 1) * (nCntLine % 2) + (nCntLine / 2);
		}

		//インデックス指定
		pIdx[nCntLine + ((nCntLine / ((LINE_XNUM + 1) * 2)) * 2)] = (LINE_XNUM + 1) - (LINE_XNUM + 1) * (nCntLine % 2) + (nCntLine / 2);
	}

	g_pIdxBuffLine->Unlock();
}

//-------------------
//ポリゴン終了処理
//-------------------
void UninitLine(void)
{
	//テクスチャの破棄
	if (g_pTextureLine != NULL)
	{
		g_pTextureLine->Release();
		g_pTextureLine = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffLine != NULL)
	{
		g_pVtxBuffLine->Release();
		g_pVtxBuffLine = NULL;
	}
	//インデックスバッファの破棄
	if (g_pIdxBuffLine != NULL)
	{
		g_pIdxBuffLine->Release();
		g_pIdxBuffLine = NULL;
	}
}

//-------------------
//ポリゴン更新処理
//-------------------
void UpdateLine(void)
{
	if (!GetbSnow())
	{
		HitLine();
	}
}

//-------------------
//ポリゴン描画処理
//-------------------
void DrawLine(void)
{
	if (!GetbSnow())
	{
		LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
		D3DXMATRIX mtxScale, mtxRot, mtxTrans;//計算マトリックス

		//デバイスの取得
		pDevice = GetDevice();

		int nCntLine;
		for (nCntLine = 0; nCntLine < LINE_MAX; nCntLine++)
		{
			if (g_aLine[nCntLine].bUse)
			{
				//マトリックス初期化
				D3DXMatrixIdentity(&g_aLine[nCntLine].mtxWorld);

				//大きさの反映
				D3DXMatrixScaling(&mtxScale, g_aLine[nCntLine].scale.x, g_aLine[nCntLine].scale.y, g_aLine[nCntLine].scale.z);
				D3DXMatrixMultiply(&g_aLine[nCntLine].mtxWorld, &g_aLine[nCntLine].mtxWorld, &mtxScale);

				//向きの反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aLine[nCntLine].rot.y, g_aLine[nCntLine].rot.x, g_aLine[nCntLine].rot.z);
				D3DXMatrixMultiply(&g_aLine[nCntLine].mtxWorld, &g_aLine[nCntLine].mtxWorld, &mtxRot);

				//位置の計算
				D3DXMatrixTranslation(&mtxTrans, g_aLine[nCntLine].pos.x, g_aLine[nCntLine].pos.y, g_aLine[nCntLine].pos.z);
				D3DXMatrixMultiply(&g_aLine[nCntLine].mtxWorld, &g_aLine[nCntLine].mtxWorld, &mtxTrans);

				//ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_aLine[nCntLine].mtxWorld);

				//頂点バッファ
				pDevice->SetStreamSource(0, g_pVtxBuffLine, 0, sizeof(VERTEX_3D));

				//インデックスバッファをデータストリームに設定
				pDevice->SetIndices(g_pIdxBuffLine);

				//頂点フォーマットの設定
				pDevice->SetFVF(FVF_VERTEX_3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureLine);

				//ポリゴンの描画
				pDevice->DrawIndexedPrimitive
				(
					D3DPT_TRIANGLESTRIP,//タイプ
					0,
					0,
					VT_MAX_LINE,//頂点数
					0,
					POLYGON_NUM_LINE//ポリゴンの個数
				);
			}
		}
	}
}

//----------
//設定
//----------
void SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale)
{
	int nCntLine;
	for (nCntLine = 0; nCntLine < LINE_MAX; nCntLine++)
	{
		if (!g_aLine[nCntLine].bUse)
		{
			g_aLine[nCntLine].pos = pos;
			g_aLine[nCntLine].rot = rot;
			g_aLine[nCntLine].scale = scale;
			g_aLine[nCntLine].fAngle = atan2f((LINE_WIDTH * g_aLine[nCntLine].scale.x), (LINE_Z * g_aLine[nCntLine].scale.z));//角度
			g_aLine[nCntLine].fLength = sqrtf((LINE_WIDTH * g_aLine[nCntLine].scale.x) * (LINE_WIDTH * g_aLine[nCntLine].scale.x) + (LINE_Z * g_aLine[nCntLine].scale.z) * (LINE_Z * g_aLine[nCntLine].scale.z)) / 2.0f;//対角線の長さ
			g_aLine[nCntLine].bUse = true;
			break;
		}
	}
}

//----------------------
//当たり判定
//----------------------
void HitLine(void)
{
	Player* pPlayer = GetPlayer();
	D3DXVECTOR3 aPos[4] = {}, Fieldvec = {}, Posvec = {};
	int nCntLine;
	bool OnLine = false;
	for (nCntLine = 0; nCntLine < LINE_MAX; nCntLine++)
	{//地面の数
		if (g_aLine[nCntLine].bUse)
		{//使っている線
			aPos[0] = D3DXVECTOR3(g_aLine[nCntLine].pos.x + sinf(g_aLine[nCntLine].rot.y - g_aLine[nCntLine].fAngle) * g_aLine[nCntLine].fLength, g_aLine[nCntLine].pos.y, g_aLine[nCntLine].pos.z + cosf(g_aLine[nCntLine].rot.y - g_aLine[nCntLine].fAngle) * g_aLine[nCntLine].fLength);
			aPos[1] = D3DXVECTOR3(g_aLine[nCntLine].pos.x + sinf(g_aLine[nCntLine].rot.y + g_aLine[nCntLine].fAngle) * g_aLine[nCntLine].fLength, g_aLine[nCntLine].pos.y, g_aLine[nCntLine].pos.z + cosf(g_aLine[nCntLine].rot.y + g_aLine[nCntLine].fAngle) * g_aLine[nCntLine].fLength);
			aPos[2] = D3DXVECTOR3(g_aLine[nCntLine].pos.x + sinf(g_aLine[nCntLine].rot.y - (D3DX_PI + g_aLine[nCntLine].fAngle)) * g_aLine[nCntLine].fLength, g_aLine[nCntLine].pos.y, g_aLine[nCntLine].pos.z + cosf(g_aLine[nCntLine].rot.y - (D3DX_PI + g_aLine[nCntLine].fAngle)) * g_aLine[nCntLine].fLength);
			aPos[3] = D3DXVECTOR3(g_aLine[nCntLine].pos.x + sinf(g_aLine[nCntLine].rot.y - (D3DX_PI - g_aLine[nCntLine].fAngle)) * g_aLine[nCntLine].fLength, g_aLine[nCntLine].pos.y, g_aLine[nCntLine].pos.z + cosf(g_aLine[nCntLine].rot.y - (D3DX_PI - g_aLine[nCntLine].fAngle)) * g_aLine[nCntLine].fLength);

			Fieldvec = aPos[1] - aPos[0];//壁のベクトル
			Posvec = pPlayer->pos - aPos[0];//壁に対するプレイヤーのベクトル
			if ((Fieldvec.z * Posvec.x) - (Fieldvec.x * Posvec.z) >= 0.0f)
			{//線上
				Fieldvec = aPos[2] - aPos[1];//壁のベクトル
				Posvec = pPlayer->pos - aPos[1];//壁に対するプレイヤーのベクトル
				if ((Fieldvec.z * Posvec.x) - (Fieldvec.x * Posvec.z) >= 0.0f)
				{//線上
					Fieldvec = aPos[3] - aPos[2];//壁のベクトル
					Posvec = pPlayer->pos - aPos[2];//壁に対するプレイヤーのベクトル
					if ((Fieldvec.z * Posvec.x) - (Fieldvec.x * Posvec.z) >= 0.0f)
					{//線上
						Fieldvec = aPos[0] - aPos[3];//壁のベクトル
						Posvec = pPlayer->pos - aPos[3];//壁に対するプレイヤーのベクトル
						if ((Fieldvec.z * Posvec.x) - (Fieldvec.x * Posvec.z) >= 0.0f)
						{//線上
							OnLine = true;
						}
					}
				}
			}
		}
	}

	if (!OnLine && !pPlayer->bJump)
	{
		pPlayer->nLife--;
		SetUi(1);
	}
}