//----------------------------------------
//
//ポリゴン表示処理[meshfield.cpp]
//Author fuma sato
//
//----------------------------------------

#include"meshfield.h"
#include"player.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;//バッファのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;//インデックスバッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;
MeshField g_aMeshField[MESHFIELD_MAX];

//----------------------
//ポリゴンの初期化処理
//----------------------
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	VERTEX_3D* pVtx;//頂点情報ポインタ

	//デバイスの取得
	pDevice = GetDevice();

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * VT_MAX_MESH * MESHFIELD_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		MESHFIELD_TEX,
		&g_pTextureMeshField
	);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * INDEX_NUM * MESHFIELD_MAX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL
	);

	int nCntMeshField, nCntMeshField2, nCntMeshField3;
	for (nCntMeshField = 0; nCntMeshField < MESHFIELD_MAX; nCntMeshField++)
	{
		g_aMeshField[nCntMeshField].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshField[nCntMeshField].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshField[nCntMeshField].bAlpha = false;
		g_aMeshField[nCntMeshField].bUse = false;
	}
	//1つ目


	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntMeshField = 0; nCntMeshField < MESHFIELD_MAX; nCntMeshField++)
	{//メッシュフィールド数
		for (nCntMeshField2 = 0; nCntMeshField2 < MESHFIELD_ZNUM + 1; nCntMeshField2++)
		{//1枚分のZ軸のループ
			for (nCntMeshField3 = 0; nCntMeshField3 < MESHFIELD_XNUM + 1; nCntMeshField3++)
			{//1枚分のX軸のループ
				//座標設定
				pVtx[nCntMeshField2 * (MESHFIELD_XNUM + 1) + nCntMeshField3].pos = D3DXVECTOR3(g_aMeshField[nCntMeshField].pos.x - MESHFIELD_WIDTH * 0.5f + (MESHFIELD_WIDTH / MESHFIELD_XNUM) * nCntMeshField3, g_aMeshField[nCntMeshField].pos.y + MESHFIELD_HEIGHT, g_aMeshField[nCntMeshField].pos.z + MESHFIELD_Z * 0.5f - (MESHFIELD_Z / MESHFIELD_ZNUM) * nCntMeshField2);

				//nor
				pVtx[nCntMeshField2 * (MESHFIELD_XNUM + 1) + nCntMeshField3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				//カラー
				pVtx[nCntMeshField2 * (MESHFIELD_XNUM + 1) + nCntMeshField3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//テクスチャ
				pVtx[nCntMeshField2 * (MESHFIELD_XNUM + 1) + nCntMeshField3].tex = D3DXVECTOR2(((MESHFIELD_WIDTH / MESHFIELD_WIDTH_DEF) / MESHFIELD_XNUM) * nCntMeshField3, ((MESHFIELD_Z / MESHFIELD_Z_DEF) / MESHFIELD_ZNUM) * nCntMeshField2);
			}
		}
		pVtx += VT_MAX_MESH;
	}

	g_pVtxBuffMeshField->Unlock();

	WORD* pIdx;
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntMeshField = 0; nCntMeshField < MESHFIELD_MAX; nCntMeshField++)
	{
		for (nCntMeshField2 = 0; nCntMeshField2 < INDEX_NUM - (MESHFIELD_ZNUM - 1) * 2; nCntMeshField2++)
		{
			if (nCntMeshField2 % ((MESHFIELD_XNUM + 1) * 2) == 0 && nCntMeshField2 != 0)
			{
				//インデックス指定
				pIdx[nCntMeshField2 - 2 + ((nCntMeshField2 / ((MESHFIELD_XNUM + 1) * 2)) * 2)] = (MESHFIELD_XNUM + 1) - (MESHFIELD_XNUM + 1) * ((nCntMeshField2 - 1) % 2) + ((nCntMeshField2 - 1) / 2);
				//インデックス指定
				pIdx[nCntMeshField2 - 1 + ((nCntMeshField2 / ((MESHFIELD_XNUM + 1) * 2)) * 2)] = (MESHFIELD_XNUM + 1) - (MESHFIELD_XNUM + 1) * (nCntMeshField2 % 2) + (nCntMeshField2 / 2);
			}

			//インデックス指定
			pIdx[nCntMeshField2 + ((nCntMeshField2 / ((MESHFIELD_XNUM + 1) * 2)) * 2)] = (MESHFIELD_XNUM + 1) - (MESHFIELD_XNUM + 1) * (nCntMeshField2 % 2) + (nCntMeshField2 / 2);
		}
		pIdx += INDEX_NUM;
	}

	g_pIdxBuffMeshField->Unlock();
}

//-------------------
//ポリゴン終了処理
//-------------------
void UninitMeshField(void)
{
	//テクスチャの破棄
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}
	//インデックスバッファの破棄
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//-------------------
//ポリゴン更新処理
//-------------------
void UpdateMeshField(void)
{
	CollisionMeshField();
}

//-------------------
//ポリゴン描画処理
//-------------------
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATRIX mtxRot, mtxTrans;//計算マトリックス

	//デバイスの取得
	pDevice = GetDevice();

	int nCntMeshField;
	for (nCntMeshField = 0; nCntMeshField < MESHFIELD_MAX; nCntMeshField++)
	{
		if (g_aMeshField[nCntMeshField].bUse && !g_aMeshField[nCntMeshField].bAlpha)
		{
			//マトリックス初期化
			D3DXMatrixIdentity(&g_aMeshField[nCntMeshField].mtxWorld);

			//向きの反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshField[nCntMeshField].rot.y, g_aMeshField[nCntMeshField].rot.x, g_aMeshField[nCntMeshField].rot.z);
			D3DXMatrixMultiply(&g_aMeshField[nCntMeshField].mtxWorld, &g_aMeshField[nCntMeshField].mtxWorld, &mtxRot);

			//位置の計算
			D3DXMatrixTranslation(&mtxTrans, g_aMeshField[nCntMeshField].pos.x, g_aMeshField[nCntMeshField].pos.y, g_aMeshField[nCntMeshField].pos.z);
			D3DXMatrixMultiply(&g_aMeshField[nCntMeshField].mtxWorld, &g_aMeshField[nCntMeshField].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshField[nCntMeshField].mtxWorld);

			//頂点バッファ
			pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

			//インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_pIdxBuffMeshField);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureMeshField);

			//ポリゴンの描画
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLESTRIP,//タイプ
				0,
				0,
				VT_MAX_MESH,//頂点数
				nCntMeshField * INDEX_NUM,
				POLYGON_NUM//ポリゴンの個数
			);
		}
	}
	for (nCntMeshField = 0; nCntMeshField < MESHFIELD_MAX; nCntMeshField++)
	{
		if (g_aMeshField[nCntMeshField].bUse && g_aMeshField[nCntMeshField].bAlpha)
		{
			//マトリックス初期化
			D3DXMatrixIdentity(&g_aMeshField[nCntMeshField].mtxWorld);

			//向きの反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshField[nCntMeshField].rot.y, g_aMeshField[nCntMeshField].rot.x, g_aMeshField[nCntMeshField].rot.z);
			D3DXMatrixMultiply(&g_aMeshField[nCntMeshField].mtxWorld, &g_aMeshField[nCntMeshField].mtxWorld, &mtxRot);

			//位置の計算
			D3DXMatrixTranslation(&mtxTrans, g_aMeshField[nCntMeshField].pos.x, g_aMeshField[nCntMeshField].pos.y, g_aMeshField[nCntMeshField].pos.z);
			D3DXMatrixMultiply(&g_aMeshField[nCntMeshField].mtxWorld, &g_aMeshField[nCntMeshField].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshField[nCntMeshField].mtxWorld);

			//インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_pIdxBuffMeshField);

			//頂点バッファ
			pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureMeshField);

			//ポリゴンの描画
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLESTRIP,//タイプ
				0,
				0,
				VT_MAX_MESH,//頂点数
				nCntMeshField * INDEX_NUM,
				POLYGON_NUM//ポリゴンの個数
			);
		}
	}
}

//----------
//設定
//----------
void SetMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntMeshField;
	for (nCntMeshField = 0; nCntMeshField < MESHFIELD_MAX; nCntMeshField++)
	{
		if (!g_aMeshField[nCntMeshField].bUse)
		{
			g_aMeshField[nCntMeshField].pos = pos;
			g_aMeshField[nCntMeshField].rot = rot;
			g_aMeshField[nCntMeshField].bAlpha = false;
			g_aMeshField[nCntMeshField].bUse = true;
			break;
		}
	}
}

//----------------------
//当たり判定
//----------------------
void CollisionMeshField(void)
{
	Player* pPlayer = GetPlayer();
	D3DXVECTOR3 aPos[2] = {}, Fieldvec = {}, Posvec = {}, PosOldvec = {}, movevec = {}, Norvec = {}, Dovec = {}, Hit = {};
	int nCntMeshField;
	float FieldCross, PosCross;
	for (nCntMeshField = 0; nCntMeshField < MESHFIELD_MAX; nCntMeshField++)
	{//地面の数
		if (g_aMeshField[nCntMeshField].bUse && !g_aMeshField[nCntMeshField].bAlpha)
		{//使っている透明でない壁
			aPos[0] = D3DXVECTOR3(g_aMeshField[nCntMeshField].pos.x + MESHFIELD_WIDTH * 0.5f * sinf(g_aMeshField[nCntMeshField].rot.z + D3DX_PI * -0.5f), g_aMeshField[nCntMeshField].pos.y + MESHFIELD_WIDTH * 0.5f * cosf(g_aMeshField[nCntMeshField].rot.z + D3DX_PI * 0.5f), g_aMeshField[nCntMeshField].pos.z);
			aPos[1] = D3DXVECTOR3(g_aMeshField[nCntMeshField].pos.x + MESHFIELD_WIDTH * 0.5f * sinf(g_aMeshField[nCntMeshField].rot.z + D3DX_PI * 0.5f), g_aMeshField[nCntMeshField].pos.y + MESHFIELD_WIDTH * 0.5f * cosf(g_aMeshField[nCntMeshField].rot.z + D3DX_PI * -0.5f), g_aMeshField[nCntMeshField].pos.z);
			Fieldvec = aPos[1] - aPos[0];//壁のベクトル
			Posvec = pPlayer->pos - aPos[0];//壁に対するプレイヤーのベクトル
			PosOldvec = pPlayer->posOld - aPos[0];//壁に対するプレイヤーの旧ベクトル
			movevec = pPlayer->pos - pPlayer->posOld;//プレイヤーの移動ベクトル
			if ((Fieldvec.x * Posvec.y) - (Fieldvec.y * Posvec.x) <= 0.0f && (Fieldvec.x * PosOldvec.y) - (Fieldvec.y * PosOldvec.x) >= 0.0f && pPlayer->pos.z < g_aMeshField[nCntMeshField].pos.z + MESHFIELD_WIDTH * 0.5f && pPlayer->pos.z + pPlayer->aModel[1].pos.z + pPlayer->aModel[1].vtxMax.z > g_aMeshField[nCntMeshField].pos.z - MESHFIELD_WIDTH * 0.5f)
			{//地面の下
				FieldCross = (Fieldvec.x * movevec.y) - (Fieldvec.y * movevec.x);
				PosCross = (Posvec.x * movevec.y) - (Posvec.y * movevec.x);
				PosCross /= FieldCross;
				if (PosCross >= -0.01f && PosCross < 1.01f)
				{
					Hit = aPos[0] + Fieldvec * PosCross;
					movevec = pPlayer->pos - Hit;//プレイヤーの移動ベクトル
					Norvec = D3DXVECTOR3(Fieldvec.y, -Fieldvec.x, Fieldvec.z);
					D3DXVec3Normalize(&Norvec, &Norvec);
					Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.y * Norvec.y));
					pPlayer->pos += Dovec * 1.001f;
					pPlayer->move.y = 0.0f;
					pPlayer->move.y = 0.0f;
					pPlayer->bJump = false;
				}
			}
		}
	}
}