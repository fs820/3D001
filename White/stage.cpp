//----------------------------------------
//
//モデル表示処理[stage.cpp]
//Author fuma sato
//
//----------------------------------------

#include"stage.h"
#include"camera.h"
#include"input.h"
#include"shadow.h"
#include"player.h"

//グローバル変数宣言
Stage g_aStage[STAGE_MAX] = {};
//----------------------
//ポリゴンの初期化処理
//----------------------
void InitStage(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ

	//デバイスの取得
	pDevice = GetDevice();

	int nCntStage, nCntTex;
	for (nCntStage = 0; nCntStage < STAGE_MAX; nCntStage++)
	{
		g_aStage[nCntStage].pMesh = NULL;
		g_aStage[nCntStage].pBuffMat = NULL;
		for (nCntTex = 0; nCntTex < TEXTURE_MAX; nCntTex++)
		{
			g_aStage[nCntStage].apTexture[nCntTex] = NULL;
		}
		g_aStage[nCntStage].dwNumMat = 0;
		g_aStage[nCntStage].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aStage[nCntStage].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aStage[nCntStage].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aStage[nCntStage].fLength = 0.0f;
		g_aStage[nCntStage].fAngle = 0.0f;
		g_aStage[nCntStage].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aStage[nCntStage].nIdxShadow = -1;
		g_aStage[nCntStage].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aStage[nCntStage].vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aStage[nCntStage].nNumVtx = 0;
		g_aStage[nCntStage].sizeFVF = 0;
		g_aStage[nCntStage].pVtxBuff = NULL;
		g_aStage[nCntStage].bUse = false;
	}
}

//-------------------
//ポリゴン終了処理
//-------------------
void UninitStage(void)
{
	int nCntStage;
	unsigned int nCntTex;
	for (nCntStage = 0; nCntStage < STAGE_MAX; nCntStage++)
	{
		for (nCntTex = 0; nCntTex < g_aStage[nCntStage].dwNumMat; nCntTex++)
		{
			if (g_aStage[nCntStage].apTexture[nCntTex] != NULL)
			{
				g_aStage[nCntStage].apTexture[nCntTex]->Release();
				g_aStage[nCntStage].apTexture[nCntTex] = NULL;
			}
		}
		//メッシュの破棄
		if (g_aStage[nCntStage].pMesh != NULL)
		{
			g_aStage[nCntStage].pMesh->Release();
			g_aStage[nCntStage].pMesh = NULL;
		}
		//マテリアルの破棄
		if (g_aStage[nCntStage].pBuffMat != NULL)
		{
			g_aStage[nCntStage].pBuffMat->Release();
			g_aStage[nCntStage].pBuffMat = NULL;
		}
	}
}

//-------------------
//ポリゴン更新処理
//-------------------
void UpdateStage(void)
{

}

//-------------------
//ポリゴン描画処理
//-------------------
void DrawStage(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//計算マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	int nCntStage;
	for (nCntStage = 0; nCntStage < STAGE_MAX; nCntStage++)
	{
		if (g_aStage[nCntStage].bUse)
		{
			//マトリックス初期化
			D3DXMatrixIdentity(&g_aStage[nCntStage].mtxWorld);

			//大きさの反映
			D3DXMatrixScaling(&mtxScale, g_aStage[nCntStage].scale.x, g_aStage[nCntStage].scale.y, g_aStage[nCntStage].scale.z);
			D3DXMatrixMultiply(&g_aStage[nCntStage].mtxWorld, &g_aStage[nCntStage].mtxWorld, &mtxScale);

			//向きの反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aStage[nCntStage].rot.y, g_aStage[nCntStage].rot.x, g_aStage[nCntStage].rot.z);
			D3DXMatrixMultiply(&g_aStage[nCntStage].mtxWorld, &g_aStage[nCntStage].mtxWorld, &mtxRot);

			//位置の反映
			D3DXMatrixTranslation(&mtxTrans, g_aStage[nCntStage].pos.x, g_aStage[nCntStage].pos.y, g_aStage[nCntStage].pos.z);
			D3DXMatrixMultiply(&g_aStage[nCntStage].mtxWorld, &g_aStage[nCntStage].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aStage[nCntStage].mtxWorld);

			//現在のマテリアル取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_aStage[nCntStage].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aStage[nCntStage].dwNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				//テクスチャ
				pDevice->SetTexture(0, g_aStage[nCntStage].apTexture[nCntMat]);

				//モデル描画
				g_aStage[nCntStage].pMesh->DrawSubset(nCntMat);
			}

			pDevice->SetMaterial(&matDef);
		}
	}
}

//-----------
//配置
//-----------
void SetStage(char* name, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ
	int nCntStage, nCntTex;
	//デバイスの取得
	pDevice = GetDevice();

	for (nCntStage = 0; nCntStage < STAGE_MAX; nCntStage++)
	{
		if (!g_aStage[nCntStage].bUse)
		{
			//Xファイル読み込み
			D3DXLoadMeshFromX
			(
				name,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_aStage[nCntStage].pBuffMat,
				NULL,
				&g_aStage[nCntStage].dwNumMat,
				&g_aStage[nCntStage].pMesh
			);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_aStage[nCntStage].pBuffMat->GetBufferPointer();

			for (nCntTex = 0; nCntTex < (int)g_aStage[nCntStage].dwNumMat; nCntTex++)
			{
				if (pMat[nCntTex].pTextureFilename != NULL)
				{//テクスチャがある
					//テクスチャの読み込み
					D3DXCreateTextureFromFile
					(
						pDevice,
						pMat[nCntTex].pTextureFilename,
						&g_aStage[nCntStage].apTexture[nCntTex]
					);
				}
			}

			//頂点数
			g_aStage[nCntStage].nNumVtx = g_aStage[nCntStage].pMesh->GetNumVertices();
			//頂点サイズ
			g_aStage[nCntStage].sizeFVF = D3DXGetFVFVertexSize(g_aStage[nCntStage].pMesh->GetFVF());
			//頂点バッファの取得
			g_aStage[nCntStage].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_aStage[nCntStage].pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < g_aStage[nCntStage].nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_aStage[nCntStage].pVtxBuff;

				if (vtx.x > g_aStage[nCntStage].vtxMax.x)
				{
					g_aStage[nCntStage].vtxMax.x = vtx.x;
				}
				if (vtx.x < g_aStage[nCntStage].vtxMin.x)
				{
					g_aStage[nCntStage].vtxMin.x = vtx.x;
				}
				if (vtx.y > g_aStage[nCntStage].vtxMax.y)
				{
					g_aStage[nCntStage].vtxMax.y = vtx.y;
				}
				if (vtx.y < g_aStage[nCntStage].vtxMin.y)
				{
					g_aStage[nCntStage].vtxMin.y = vtx.y;
				}
				if (vtx.z > g_aStage[nCntStage].vtxMax.z)
				{
					g_aStage[nCntStage].vtxMax.z = vtx.z;
				}
				if (vtx.z < g_aStage[nCntStage].vtxMin.z)
				{
					g_aStage[nCntStage].vtxMin.z = vtx.z;
				}

				g_aStage[nCntStage].pVtxBuff += g_aStage[nCntStage].sizeFVF;
			}

			g_aStage[nCntStage].pos = pos;
			g_aStage[nCntStage].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aStage[nCntStage].rot = rot;
			g_aStage[nCntStage].scale = scale;
			g_aStage[nCntStage].vtxMax.x *= g_aStage[nCntStage].scale.x;
			g_aStage[nCntStage].vtxMax.y *= g_aStage[nCntStage].scale.y;
			g_aStage[nCntStage].vtxMax.z *= g_aStage[nCntStage].scale.z;
			g_aStage[nCntStage].vtxMin.x *= g_aStage[nCntStage].scale.x;
			g_aStage[nCntStage].vtxMin.y *= g_aStage[nCntStage].scale.y;
			g_aStage[nCntStage].vtxMin.z *= g_aStage[nCntStage].scale.z;

			g_aStage[nCntStage].fLength = sqrtf((g_aStage[nCntStage].vtxMax.x - g_aStage[nCntStage].vtxMin.x) * (g_aStage[nCntStage].vtxMax.x - g_aStage[nCntStage].vtxMin.x) + (g_aStage[nCntStage].vtxMax.z - g_aStage[nCntStage].vtxMin.z) * (g_aStage[nCntStage].vtxMax.z - g_aStage[nCntStage].vtxMin.z)) / 2.0f;
			g_aStage[nCntStage].fAngle = atan2f((g_aStage[nCntStage].vtxMax.x - g_aStage[nCntStage].vtxMin.x), (g_aStage[nCntStage].vtxMax.z - g_aStage[nCntStage].vtxMin.z));//角度

			g_aStage[nCntStage].nIdxShadow = SetShadow(g_aStage[nCntStage].pos, g_aStage[nCntStage].rot);
			g_aStage[nCntStage].bUse = true;
			break;
		}
	}
}

//------------------------------
//位置取得
//------------------------------
Stage* GetStage(void)
{
	return &g_aStage[0];
}

//------------------------------
//当たり判定
//------------------------------
bool CollisionStage(Stage** pStage)
{
	bool bRanding = false;
	Player* pPlayer = GetPlayer();
	D3DXVECTOR3 aPos[8] = {}, Stagevec = {}, Posvec = {}, PosOldvec = {}, movevec = {}, Norvec = {}, Dovec = {}, Hit = {};
	int nCntStage;
	float StageCross, PosCross;
	for (nCntStage = 0; nCntStage < STAGE_MAX; nCntStage++)
	{//壁の数
		if (g_aStage[nCntStage].bUse)
		{//使っている透明でない壁
			aPos[0] = D3DXVECTOR3(g_aStage[nCntStage].pos.x + sinf(g_aStage[nCntStage].rot.y - g_aStage[nCntStage].fAngle) * g_aStage[nCntStage].fLength, g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y, g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y - g_aStage[nCntStage].fAngle) * g_aStage[nCntStage].fLength);
			aPos[1] = D3DXVECTOR3(g_aStage[nCntStage].pos.x + sinf(g_aStage[nCntStage].rot.y - (D3DX_PI - g_aStage[nCntStage].fAngle)) * g_aStage[nCntStage].fLength, g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y, g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y - (D3DX_PI - g_aStage[nCntStage].fAngle)) * g_aStage[nCntStage].fLength);
			aPos[2] = D3DXVECTOR3(g_aStage[nCntStage].pos.x + sinf(g_aStage[nCntStage].rot.y - (D3DX_PI + g_aStage[nCntStage].fAngle)) * g_aStage[nCntStage].fLength, g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y, g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y - (D3DX_PI + g_aStage[nCntStage].fAngle)) * g_aStage[nCntStage].fLength);
			aPos[3] = D3DXVECTOR3(g_aStage[nCntStage].pos.x + sinf(g_aStage[nCntStage].rot.y + g_aStage[nCntStage].fAngle) * g_aStage[nCntStage].fLength, g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y, g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + g_aStage[nCntStage].fAngle) * g_aStage[nCntStage].fLength);
			aPos[4] = D3DXVECTOR3(g_aStage[nCntStage].pos.x + sinf(g_aStage[nCntStage].rot.y + D3DX_PI * -0.5f) * g_aStage[nCntStage].fLength, g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y, g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + D3DX_PI * -0.5f) * g_aStage[nCntStage].fLength);
			aPos[5] = D3DXVECTOR3(g_aStage[nCntStage].pos.x + sinf(g_aStage[nCntStage].rot.y + D3DX_PI * 0.5f) * g_aStage[nCntStage].fLength, g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y, g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + D3DX_PI * 0.5f) * g_aStage[nCntStage].fLength);
			aPos[6] = D3DXVECTOR3(g_aStage[nCntStage].pos.x + sinf(g_aStage[nCntStage].rot.y + D3DX_PI * -0.5f) * g_aStage[nCntStage].fLength, g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y, g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + D3DX_PI * -0.5f) * g_aStage[nCntStage].fLength);
			aPos[7] = D3DXVECTOR3(g_aStage[nCntStage].pos.x + sinf(g_aStage[nCntStage].rot.y + D3DX_PI * 0.5f) * g_aStage[nCntStage].fLength, g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y, g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + D3DX_PI * 0.5f) * g_aStage[nCntStage].fLength);

			Stagevec = aPos[1] - aPos[0];//壁のベクトル
			Posvec = pPlayer->pos - aPos[0];//壁に対するプレイヤーのベクトル
			PosOldvec = pPlayer->posOld - aPos[0];//壁に対するプレイヤーの旧ベクトル
			movevec = pPlayer->pos - pPlayer->posOld;//プレイヤーの移動ベクトル
			if ((Stagevec.z * Posvec.x) - (Stagevec.x * Posvec.z) <= 0.0f && (Stagevec.z * PosOldvec.x) - (Stagevec.x * PosOldvec.z) >= 0.0f && pPlayer->pos.y < g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y && pPlayer->pos.y + pPlayer->aModel[1].pos.y + pPlayer->aModel[1].vtxMax.y > g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y)
			{//左
				StageCross = (Stagevec.z * movevec.x) - (Stagevec.x * movevec.z);
				PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
				PosCross /= StageCross;
				if (PosCross >= -0.01f && PosCross < 1.01f)
				{
					Hit = aPos[0] + Stagevec * PosCross;
					movevec = pPlayer->pos - Hit;//プレイヤーの移動ベクトル
					Norvec = D3DXVECTOR3(Stagevec.z, Stagevec.y, -Stagevec.x);
					D3DXVec3Normalize(&Norvec, &Norvec);
					Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
					pPlayer->pos += Dovec * 1.1f;
				}
			}

			Stagevec = aPos[2] - aPos[1];//壁のベクトル
			Posvec = pPlayer->pos - aPos[1];//壁に対するプレイヤーのベクトル
			PosOldvec = pPlayer->posOld - aPos[1];//壁に対するプレイヤーの旧ベクトル
			movevec = pPlayer->pos - pPlayer->posOld;//プレイヤーの移動ベクトル
			if ((Stagevec.z * Posvec.x) - (Stagevec.x * Posvec.z) <= 0.0f && (Stagevec.z * PosOldvec.x) - (Stagevec.x * PosOldvec.z) >= 0.0f && pPlayer->pos.y < g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y && pPlayer->pos.y + pPlayer->aModel[1].pos.y + pPlayer->aModel[1].vtxMax.y > g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y)
			{//手前
				StageCross = (Stagevec.z * movevec.x) - (Stagevec.x * movevec.z);
				PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
				PosCross /= StageCross;
				if (PosCross >= -0.01f && PosCross < 1.01f)
				{
					Hit = aPos[1] + Stagevec * PosCross;
					movevec = pPlayer->pos - Hit;//プレイヤーの移動ベクトル
					Norvec = D3DXVECTOR3(Stagevec.z, Stagevec.y, -Stagevec.x);
					D3DXVec3Normalize(&Norvec, &Norvec);
					Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
					pPlayer->pos += Dovec * 1.1f;
				}
			}

			Stagevec = aPos[3] - aPos[2];//壁のベクトル
			Posvec = pPlayer->pos - aPos[2];//壁に対するプレイヤーのベクトル
			PosOldvec = pPlayer->posOld - aPos[2];//壁に対するプレイヤーの旧ベクトル
			movevec = pPlayer->pos - pPlayer->posOld;//プレイヤーの移動ベクトル
			if ((Stagevec.z * Posvec.x) - (Stagevec.x * Posvec.z) <= 0.0f && (Stagevec.z * PosOldvec.x) - (Stagevec.x * PosOldvec.z) >= 0.0f && pPlayer->pos.y < g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y && pPlayer->pos.y + pPlayer->aModel[1].pos.y + pPlayer->aModel[1].vtxMax.y > g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y)
			{//右
				StageCross = (Stagevec.z * movevec.x) - (Stagevec.x * movevec.z);
				PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
				PosCross /= StageCross;
				if (PosCross >= -0.01f && PosCross < 1.01f)
				{
					Hit = aPos[2] + Stagevec * PosCross;
					movevec = pPlayer->pos - Hit;//プレイヤーの移動ベクトル
					Norvec = D3DXVECTOR3(Stagevec.z, Stagevec.y, -Stagevec.x);
					D3DXVec3Normalize(&Norvec, &Norvec);
					Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
					pPlayer->pos += Dovec * 1.1f;
				}
			}

			Stagevec = aPos[0] - aPos[3];//壁のベクトル
			Posvec = pPlayer->pos - aPos[3];//壁に対するプレイヤーのベクトル
			PosOldvec = pPlayer->posOld - aPos[3];//壁に対するプレイヤーの旧ベクトル
			movevec = pPlayer->pos - pPlayer->posOld;//プレイヤーの移動ベクトル
			if ((Stagevec.z * Posvec.x) - (Stagevec.x * Posvec.z) <= 0.0f && (Stagevec.z * PosOldvec.x) - (Stagevec.x * PosOldvec.z) >= 0.0f && pPlayer->pos.y < g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y && pPlayer->pos.y + pPlayer->aModel[1].pos.y + pPlayer->aModel[1].vtxMax.y > g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y)
			{//奥
				StageCross = (Stagevec.z * movevec.x) - (Stagevec.x * movevec.z);
				PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
				PosCross /= StageCross;
				if (PosCross >= -0.01f && PosCross < 1.01f)
				{
					Hit = aPos[3] + Stagevec * PosCross;
					movevec = pPlayer->pos - Hit;//プレイヤーの移動ベクトル
					Norvec = D3DXVECTOR3(Stagevec.z, Stagevec.y, -Stagevec.x);
					D3DXVec3Normalize(&Norvec, &Norvec);
					Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
					pPlayer->pos += Dovec * 1.1f;
				}
			}

			Stagevec = aPos[5] - aPos[4];//壁のベクトル
			Posvec = pPlayer->pos - aPos[4];//壁に対するプレイヤーのベクトル
			PosOldvec = pPlayer->posOld - aPos[4];//壁に対するプレイヤーの旧ベクトル
			movevec = pPlayer->pos - pPlayer->posOld;//プレイヤーの移動ベクトル
			if ((Stagevec.x * Posvec.y) - (Stagevec.y * Posvec.x) <= 0.0f && (Stagevec.x * PosOldvec.y) - (Stagevec.y * PosOldvec.x) >= 0.0f && pPlayer->pos.z + pPlayer->aModel[1].pos.z + pPlayer->aModel[1].vtxMin.z < g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + D3DX_PI * 0.5f) * g_aStage[nCntStage].fLength && pPlayer->pos.z + pPlayer->aModel[1].pos.z + pPlayer->aModel[1].vtxMax.z > g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + D3DX_PI * -0.5f) * g_aStage[nCntStage].fLength)
			{//上
				StageCross = (Stagevec.x * movevec.y) - (Stagevec.y * movevec.x);
				PosCross = (Posvec.x * movevec.y) - (Posvec.y * movevec.x);
				PosCross /= StageCross;
				if (PosCross >= -0.01f && PosCross < 1.01f)
				{
					Hit = aPos[4] + Stagevec * PosCross;
					movevec = pPlayer->pos - Hit;//プレイヤーの移動ベクトル
					Norvec = D3DXVECTOR3(Stagevec.y, -Stagevec.x, Stagevec.z);
					D3DXVec3Normalize(&Norvec, &Norvec);
					Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.y * Norvec.y));
					pPlayer->pos += Dovec * 1.001f;
					pPlayer->move.y = 0.0f;
					bRanding = true;
					if (pPlayer->motionType == MOTIONTYPE_JUMP)
					{
						pPlayer->motionType = MOTIONTYPE_LANDING;
					}
					if (pStage != NULL)
					{
						*pStage = &g_aStage[nCntStage];
					}
				}
			}

			Stagevec = aPos[7] - aPos[6];//壁のベクトル
			Posvec = pPlayer->pos - aPos[6];//壁に対するプレイヤーのベクトル
			PosOldvec = pPlayer->posOld - aPos[6];//壁に対するプレイヤーの旧ベクトル
			movevec = pPlayer->pos - pPlayer->posOld;//プレイヤーの移動ベクトル
			if ((Stagevec.x * Posvec.y) - (Stagevec.y * Posvec.x) <= 0.0f && (Stagevec.x * PosOldvec.y) - (Stagevec.y * PosOldvec.x) >= 0.0f && pPlayer->pos.z + pPlayer->aModel[1].pos.z + pPlayer->aModel[1].vtxMin.z < g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + D3DX_PI * 0.5f) * g_aStage[nCntStage].fLength && pPlayer->pos.z + pPlayer->aModel[1].pos.z + pPlayer->aModel[1].vtxMax.z > g_aStage[nCntStage].pos.z + cosf(g_aStage[nCntStage].rot.y + D3DX_PI * -0.5f) * g_aStage[nCntStage].fLength)
			{//下
				StageCross = (Stagevec.x * movevec.y) - (Stagevec.y * movevec.x);
				PosCross = (Posvec.x * movevec.y) - (Posvec.y * movevec.x);
				PosCross /= StageCross;
				if (PosCross >= -0.01f && PosCross < 1.01f)
				{
					Hit = aPos[6] + Stagevec * PosCross;
					movevec = pPlayer->pos - Hit;//プレイヤーの移動ベクトル
					Norvec = D3DXVECTOR3(Stagevec.y, -Stagevec.x, Stagevec.z);
					D3DXVec3Normalize(&Norvec, &Norvec);
					Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.y * Norvec.y));
					pPlayer->pos += Dovec * 1.001f;
					pPlayer->move.y = 0.0f;
				}
			}
		}
	}
	return bRanding;
}