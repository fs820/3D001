//----------------------------------------
//
//ポリゴン表示処理[wall.cpp]
//Author fuma sato
//
//----------------------------------------

#include"wall.h"
#include"camera.h"
#include"player.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;//バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;
Wall g_aWall[WALL_MAX];

//----------------------
//ポリゴンの初期化処理
//----------------------
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	VERTEX_3D* pVtx;//頂点情報ポインタ

	//デバイスの取得
	pDevice = GetDevice();

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * VT_MAX * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		WALL_TEX,
		&g_pTextureWall
	);

	int nCntWall;
	for (nCntWall = 0; nCntWall < WALL_MAX; nCntWall++)
	{
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].bAlpha = false;
		g_aWall[nCntWall].bUse = false;
	}
	//1つ目


	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < 2; nCntWall++)
	{
		//座標設定
		pVtx[0].pos = D3DXVECTOR3(-WALL_WIDTH * 0.5f, WALL_HEIGHT, WALL_Z * 0.5f);
		pVtx[1].pos = D3DXVECTOR3(WALL_WIDTH * 0.5f, WALL_HEIGHT, WALL_Z * 0.5f);
		pVtx[2].pos = D3DXVECTOR3(-WALL_WIDTH * 0.5f, 0.0f, -WALL_Z * 0.5f);
		pVtx[3].pos = D3DXVECTOR3(WALL_WIDTH * 0.5f, 0.0f, -WALL_Z * 0.5f);

		//nor
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - nCntWall * (1.0f - WALL_ALPHA));
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - nCntWall * (1.0f - WALL_ALPHA));
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - nCntWall * (1.0f - WALL_ALPHA));
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - nCntWall * (1.0f - WALL_ALPHA));

		//テクスチャ
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(WALL_WIDTH/ WALL_WIDTH_DEF, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, WALL_HEIGHT / WALL_HEIGHT_DEF);
		pVtx[3].tex = D3DXVECTOR2(WALL_WIDTH / WALL_WIDTH_DEF, WALL_HEIGHT / WALL_HEIGHT_DEF);

		pVtx += VT_MAX;
	}

	g_pVtxBuffWall->Unlock();
}

//-------------------
//ポリゴン終了処理
//-------------------
void UninitWall(void)
{
	//テクスチャの破棄
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//-------------------
//ポリゴン更新処理
//-------------------
void UpdateWall(void)
{
	//当たり判定
	CollisionWall();
}

//-------------------
//ポリゴン描画処理
//-------------------
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATRIX mtxRot, mtxTrans;//計算マトリックス

	//デバイスの取得
	pDevice = GetDevice();

	int nCntWall;
	for (nCntWall = 0; nCntWall < WALL_MAX; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse && !g_aWall[nCntWall].bAlpha)
		{
			//マトリックス初期化
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);

			//向きの反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxRot);

			//位置の計算
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);

			//頂点バッファ
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureWall);

			//ポリゴンの描画
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,//タイプ
				0,//始まりの番号
				2//ポリゴンの個数
			);
		}
	}
}

//-------------------
//ポリゴン描画処理
//-------------------
void DrawAlphaWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATRIX mtxRot, mtxTrans;//計算マトリックス

	//デバイスの取得
	pDevice = GetDevice();

	int nCntWall;
	for (nCntWall = 0; nCntWall < WALL_MAX; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse && g_aWall[nCntWall].bAlpha)
		{
			//マトリックス初期化
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);

			//向きの反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxRot);

			//位置の計算
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);

			//頂点バッファ
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureWall);

			//ポリゴンの描画
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,//タイプ
				VT_MAX,//始まりの番号
				2//ポリゴンの個数
			);
		}
	}
}

//----------
//設定
//----------
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntWall;
	for (nCntWall = 0; nCntWall < WALL_MAX; nCntWall++)
	{
		if (!g_aWall[nCntWall].bUse)
		{
			g_aWall[nCntWall].pos = pos;
			g_aWall[nCntWall].rot = rot;
			g_aWall[nCntWall].bAlpha = false;
			g_aWall[nCntWall].bUse = true;
			break;
		}
	}

	for (nCntWall = 0; nCntWall < WALL_MAX; nCntWall++)
	{
		if (!g_aWall[nCntWall].bUse)
		{
			g_aWall[nCntWall].pos = pos;
			g_aWall[nCntWall].rot = rot;
			g_aWall[nCntWall].rot.y += D3DX_PI;
			//正規化
			if (g_aWall[nCntWall].rot.y > D3DX_PI)
			{
				g_aWall[nCntWall].rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_aWall[nCntWall].rot.y < -D3DX_PI)
			{
				g_aWall[nCntWall].rot.y += D3DX_PI * 2.0f;
			}
			g_aWall[nCntWall].bAlpha = true;
			g_aWall[nCntWall].bUse = true;
			break;
		}
	}
}

//-----------------
//情報取得
//-----------------
Wall* GetWall(void)
{
	return &g_aWall[0];
}

//----------------------
//当たり判定
//----------------------
void CollisionWall(void)
{
	Player* pPlayer = GetPlayer();
	D3DXVECTOR3 aPos[2] = {}, Wallvec = {}, Posvec = {}, PosOldvec = {}, movevec = {}, Norvec = {}, Dovec = {}, Hit = {};
	int nCntWall;
	float WallCross, PosCross;
	for (nCntWall = 0; nCntWall < WALL_MAX; nCntWall++)
	{//壁の数
		if (g_aWall[nCntWall].bUse && !g_aWall[nCntWall].bAlpha)
		{//使っている透明でない壁
			aPos[0] = D3DXVECTOR3(g_aWall[nCntWall].pos.x + WALL_WIDTH * 0.5f * sinf(g_aWall[nCntWall].rot.y + D3DX_PI * -0.5f), g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z + WALL_WIDTH * 0.5f * cosf(g_aWall[nCntWall].rot.y + D3DX_PI * -0.5f));
			aPos[1] = D3DXVECTOR3(g_aWall[nCntWall].pos.x + WALL_WIDTH * 0.5f * sinf(g_aWall[nCntWall].rot.y + D3DX_PI * 0.5f), g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z + WALL_WIDTH * 0.5f * cosf(g_aWall[nCntWall].rot.y + D3DX_PI * 0.5f));
			Wallvec = aPos[1] - aPos[0];//壁のベクトル
			Posvec = pPlayer->pos - aPos[0];//壁に対するプレイヤーのベクトル
			PosOldvec = pPlayer->posOld - aPos[0];//壁に対するプレイヤーの旧ベクトル
			movevec = pPlayer->pos - pPlayer->posOld;//プレイヤーの移動ベクトル
			if ((Wallvec.z * Posvec.x) - (Wallvec.x * Posvec.z) <= WALL_COLL_SPASE && (Wallvec.z * PosOldvec.x) - (Wallvec.x * PosOldvec.z) >= WALL_COLL_SPASE && pPlayer->pos.y < g_aWall[nCntWall].pos.y + WALL_HEIGHT && pPlayer->pos.y + pPlayer->aModel[1].pos.y + pPlayer->aModel[1].vtxMax.y > g_aWall[nCntWall].pos.y)
			{//壁の外側
				WallCross = (Wallvec.z * movevec.x) - (Wallvec.x * movevec.z);
				PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
				PosCross /= WallCross;
				if (PosCross >= -0.01f&& PosCross < 1.01f)
				{
					Hit = aPos[0] + Wallvec * PosCross;
					movevec = pPlayer->pos - Hit;//プレイヤーの移動ベクトル
					Norvec = D3DXVECTOR3(Wallvec.z, Wallvec.y, -Wallvec.x);
					D3DXVec3Normalize(&Norvec, &Norvec);
					Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
					pPlayer->pos += Dovec * 1.95f;
				}
			}
		}
	}
}