//----------------------------------------
//
//ポリゴン表示処理[bullet.cpp]
//Author fuma sato
//
//----------------------------------------

#include"bullet.h"
#include"camera.h"
#include"shadow.h"
#include"explosion.h"
#include"effect.h"
#include"particle.h"
#include"wall.h"
#include"meshwall.h"
#include"meshfield.h"
#include"stage.h"
#include"sound.h"
#include"hitshere.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;//バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;
Bullet g_aBullet[BULLET_MAX];

//----------------------
//ポリゴンの初期化処理
//----------------------
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	VERTEX_3D* pVtx;//頂点情報ポインタ

	//デバイスの取得
	pDevice = GetDevice();

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * VT_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		BULLET_TEX,
		&g_pTextureBullet
	);

	int nCntBullet;
	for (nCntBullet = 0; nCntBullet < BULLET_MAX; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].bUse = false;
		g_aBullet[nCntBullet].nIdxShadow = -1;
	}
	//1つ目


	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	//座標設定
	pVtx[0].pos = D3DXVECTOR3(-BULLET_WIDTH * 0.5f, BULLET_HEIGHT * 0.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BULLET_WIDTH * 0.5f, BULLET_HEIGHT * 0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-BULLET_WIDTH * 0.5f, -BULLET_HEIGHT * 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BULLET_WIDTH * 0.5f, -BULLET_HEIGHT * 0.5f, 0.0f);

	//nor
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffBullet->Unlock();
}

//-------------------
//ポリゴン終了処理
//-------------------
void UninitBullet(void)
{
	//テクスチャの破棄
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//-------------------
//ポリゴン更新処理
//-------------------
void UpdateBullet(void)
{
	int nCntBullet;
	for (nCntBullet = 0; nCntBullet < BULLET_MAX; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse)
		{
			g_aBullet[nCntBullet].nLife--;

			D3DXVec3Normalize(&g_aBullet[nCntBullet].dir, &g_aBullet[nCntBullet].dir);

			g_aBullet[nCntBullet].move.x = g_aBullet[nCntBullet].dir.x * BULLET_SPEED;
			g_aBullet[nCntBullet].move.y = g_aBullet[nCntBullet].dir.y * BULLET_SPEED;
			g_aBullet[nCntBullet].move.z = g_aBullet[nCntBullet].dir.z * BULLET_SPEED;

			g_aBullet[nCntBullet].posOld = g_aBullet[nCntBullet].pos;

			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			CollisionWallB();

			SetEffect(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.1f, 0.5f, 0.4f, 0.1f), g_aBullet[nCntBullet].scale, 1000, EFFECT_TYPE_NORMAL);

			if (g_aBullet[nCntBullet].nLife < 0)
			{
				g_aBullet[nCntBullet].bUse = false;
				NullShadow(g_aBullet[nCntBullet].nIdxShadow);
				SetParticle(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].scale);
				PlaySound(SOUND_LABEL_EXPLOSION);
			}
			SetPositionShadow(g_aBullet[nCntBullet].nIdxShadow, g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].scale, BULLET_HEIGHT);

			SetHitShere(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].scale * BULLET_WIDTH * 0.5f*2.0f, 2, PLAYER);
		}
	}
}

//-------------------
//ポリゴン描画処理
//-------------------
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATRIX mtxScale, mtxTrans;//計算マトリックス

	//デバイスの取得
	pDevice = GetDevice();
	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//アルファテストオン
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	int nCntBullet;
	for (nCntBullet = 0; nCntBullet < BULLET_MAX; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse)
		{
			//マトリックス初期化
			D3DXMatrixIdentity(&g_aBullet[nCntBullet].mtxWorld);

			//ビューマトリックス取得
			D3DXMATRIX mtxView;
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//カメラの逆行列を設定
			g_aBullet[nCntBullet].mtxWorld._11 = mtxView._11;
			g_aBullet[nCntBullet].mtxWorld._12 = mtxView._21;
			g_aBullet[nCntBullet].mtxWorld._13 = mtxView._31;
			g_aBullet[nCntBullet].mtxWorld._21 = mtxView._12;
			g_aBullet[nCntBullet].mtxWorld._22 = mtxView._22;
			g_aBullet[nCntBullet].mtxWorld._23 = mtxView._32;
			g_aBullet[nCntBullet].mtxWorld._31 = mtxView._13;
			g_aBullet[nCntBullet].mtxWorld._32 = mtxView._23;
			g_aBullet[nCntBullet].mtxWorld._33 = mtxView._33;

			//大きさの反映
			D3DXMatrixScaling(&mtxScale, g_aBullet[nCntBullet].scale.x, g_aBullet[nCntBullet].scale.y, g_aBullet[nCntBullet].scale.z);
			D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorld, &g_aBullet[nCntBullet].mtxWorld, &mtxScale);

			//位置の計算
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorld, &g_aBullet[nCntBullet].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].mtxWorld);

			//頂点バッファ
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBullet);

			//ポリゴンの描画
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,//タイプ
				0,//始まりの番号
				2//ポリゴンの個数
			);
		}
	}

	//アルファテストオフ
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//----------
//設定
//----------
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 dir, D3DXVECTOR3 scale)
{
	int nCntBullet;
	for (nCntBullet = 0; nCntBullet < BULLET_MAX; nCntBullet++)
	{
		if (!g_aBullet[nCntBullet].bUse)
		{
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].pos.y += WALL_HEIGHT_DEF * scale.y;
			g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aBullet[nCntBullet].dir = dir;
			g_aBullet[nCntBullet].scale = scale;
			g_aBullet[nCntBullet].nLife = BULEET_LIFE;
			g_aBullet[nCntBullet].bUse = true;
			g_aBullet[nCntBullet].nIdxShadow = SetShadow(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].dir);
			break;
		}
	}
}

//----------------------------
//当たり判定
//----------------------------
void CollisionWallB(void)
{
	Wall* pWall = GetWall();
	MeshWall* pMeshWall = GetMeshWall();
	MeshField* pMeshField = GetMeshField();
	Stage* pStage = GetStage();
	D3DXVECTOR3 aPos[4] = {}, Wallvec = {}, Posvec = {}, PosOldvec = {}, movevec = {}, Norvec = {}, Dovec = {}, Hit = {};
	int nCntBullet, nCntWall;
	float WallCross, PosCross;
	for (nCntBullet = 0; nCntBullet < BULLET_MAX; nCntBullet++)
	{//バレット数
		if (g_aBullet[nCntBullet].bUse)
		{//使ってる弾
			pWall = GetWall();
			for (nCntWall = 0; nCntWall < WALL_MAX; nCntWall++, pWall++)
			{//壁の数
				if (pWall->bUse && !pWall->bAlpha)
				{//使っている透明でない壁
					aPos[0] = D3DXVECTOR3(pWall->pos.x + WALL_WIDTH * 0.5f * sinf(pWall->rot.y + D3DX_PI * -0.5f), pWall->pos.y, pWall->pos.z + WALL_WIDTH * 0.5f * cosf(pWall->rot.y + D3DX_PI * -0.5f));
					aPos[1] = D3DXVECTOR3(pWall->pos.x + WALL_WIDTH * 0.5f * sinf(pWall->rot.y + D3DX_PI * 0.5f), pWall->pos.y, pWall->pos.z + WALL_WIDTH * 0.5f * cosf(pWall->rot.y + D3DX_PI * 0.5f));
					Wallvec = aPos[1] - aPos[0];//壁のベクトル
					Posvec = g_aBullet[nCntBullet].pos - aPos[0];//壁に対するプレイヤーのベクトル
					PosOldvec = g_aBullet[nCntBullet].posOld - aPos[0];//壁に対するプレイヤーの旧ベクトル
					movevec = g_aBullet[nCntBullet].pos - g_aBullet[nCntBullet].posOld;//プレイヤーの移動ベクトル
					if ((Wallvec.z * Posvec.x) - (Wallvec.x * Posvec.z) < WALL_COLL_SPASE && (Wallvec.z * PosOldvec.x) - (Wallvec.x * PosOldvec.z) >= WALL_COLL_SPASE && g_aBullet[nCntBullet].pos.y - BULLET_HEIGHT * 0.5f < pWall->pos.y + WALL_HEIGHT && g_aBullet[nCntBullet].pos.y + BULLET_HEIGHT * 0.5f > pWall->pos.y)
					{//壁の外側
						WallCross = (Wallvec.z * movevec.x) - (Wallvec.x * movevec.z);
						PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
						PosCross /= WallCross;
						if (PosCross >= -0.01f && PosCross < 1.01f)
						{
							aPos[0].y += g_aBullet[nCntBullet].posOld.y;
							Hit = aPos[0] + Wallvec * PosCross;
							movevec = g_aBullet[nCntBullet].pos - Hit;//プレイヤーの移動ベクトル
							Norvec = D3DXVECTOR3(Wallvec.z, Wallvec.y, -Wallvec.x);
							D3DXVec3Normalize(&Norvec, &Norvec);
							Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
							g_aBullet[nCntBullet].dir = movevec + Dovec * 2.0f;
						}
					}
				}
			}
			pMeshWall = GetMeshWall();
			for (nCntWall = 0; nCntWall < MESHWALL_MAX; nCntWall++, pMeshWall++)
			{//壁の数
				if (pMeshWall->bUse && !pMeshWall->bAlpha)
				{//使っている透明でない壁
					aPos[0] = D3DXVECTOR3(pMeshWall->pos.x + WALL_WIDTH * 0.5f * pMeshWall->scale.x * sinf(pMeshWall->rot.y + D3DX_PI * -0.5f), pMeshWall->pos.y, pMeshWall->pos.z + WALL_WIDTH * 0.5f * pMeshWall->scale.z * cosf(pMeshWall->rot.y + D3DX_PI * -0.5f));
					aPos[1] = D3DXVECTOR3(pMeshWall->pos.x + WALL_WIDTH * 0.5f * pMeshWall->scale.x * sinf(pMeshWall->rot.y + D3DX_PI * 0.5f), pMeshWall->pos.y, pMeshWall->pos.z + WALL_WIDTH * 0.5f * pMeshWall->scale.z * cosf(pMeshWall->rot.y + D3DX_PI * 0.5f));
					Wallvec = aPos[1] - aPos[0];//壁のベクトル
					Posvec = g_aBullet[nCntBullet].pos - aPos[0];//壁に対するプレイヤーのベクトル
					PosOldvec = g_aBullet[nCntBullet].posOld - aPos[0];//壁に対するプレイヤーの旧ベクトル
					movevec = g_aBullet[nCntBullet].pos - g_aBullet[nCntBullet].posOld;//プレイヤーの移動ベクトル
					if ((Wallvec.z * Posvec.x) - (Wallvec.x * Posvec.z) < WALL_COLL_SPASE && (Wallvec.z * PosOldvec.x) - (Wallvec.x * PosOldvec.z) >= WALL_COLL_SPASE && g_aBullet[nCntBullet].pos.y - BULLET_HEIGHT * 0.5f < pMeshWall->pos.y + WALL_HEIGHT * pMeshWall->scale.y && g_aBullet[nCntBullet].pos.y + BULLET_HEIGHT * 0.5f > pMeshWall->pos.y)
					{//壁の外側
						WallCross = (Wallvec.z * movevec.x) - (Wallvec.x * movevec.z);
						PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
						PosCross /= WallCross;
						if (PosCross >= -0.01f && PosCross < 1.01f)
						{
							aPos[0].y += g_aBullet[nCntBullet].posOld.y;
							Hit = aPos[0] + Wallvec * PosCross;
							movevec = g_aBullet[nCntBullet].pos - Hit;//プレイヤーの移動ベクトル
							Norvec = D3DXVECTOR3(Wallvec.z, Wallvec.y, -Wallvec.x);
							D3DXVec3Normalize(&Norvec, &Norvec);
							Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
							g_aBullet[nCntBullet].dir = movevec + Dovec * 2.0f;
						}
					}
				}
			}
			pMeshField = GetMeshField();
			for (nCntWall = 0; nCntWall < MESHFIELD_MAX; nCntWall++, pMeshField++)
			{//壁の数
				if (pMeshField->bUse && !pMeshField->bAlpha)
				{//使っている透明でない壁
					aPos[0] = D3DXVECTOR3(pMeshField->pos.x + MESHFIELD_WIDTH * 0.5f * sinf(pMeshField->rot.z + D3DX_PI * -0.5f), pMeshField->pos.y + MESHFIELD_WIDTH * 0.5f * cosf(pMeshField->rot.z + D3DX_PI * 0.5f), pMeshField->pos.z);
					aPos[1] = D3DXVECTOR3(pMeshField->pos.x + MESHFIELD_WIDTH * 0.5f * sinf(pMeshField->rot.z + D3DX_PI * 0.5f), pMeshField->pos.y + MESHFIELD_WIDTH * 0.5f * cosf(pMeshField->rot.z + D3DX_PI * -0.5f), pMeshField->pos.z);
					Wallvec = aPos[1] - aPos[0];//壁のベクトル
					Posvec = g_aBullet[nCntBullet].pos - aPos[0];//壁に対するプレイヤーのベクトル
					PosOldvec = g_aBullet[nCntBullet].posOld - aPos[0];//壁に対するプレイヤーの旧ベクトル
					movevec = g_aBullet[nCntBullet].pos - g_aBullet[nCntBullet].posOld;//プレイヤーの移動ベクトル
					if ((Wallvec.x * Posvec.y) - (Wallvec.y * Posvec.x) < WALL_COLL_SPASE && (Wallvec.x * PosOldvec.y) - (Wallvec.y * PosOldvec.x) >= WALL_COLL_SPASE && g_aBullet[nCntBullet].pos.z - BULLET_WIDTH * 0.5f < pMeshField->pos.z + MESHFIELD_WIDTH * 0.5f && g_aBullet[nCntBullet].pos.z + BULLET_WIDTH * 0.5f > pMeshField->pos.z - MESHFIELD_WIDTH * 0.5f)
					{//壁の外側
						WallCross = (Wallvec.x * movevec.y) - (Wallvec.y * movevec.x);
						PosCross = (Posvec.x * movevec.y) - (Posvec.y * movevec.x);
						PosCross /= WallCross;
						if (PosCross >= -0.01f && PosCross < 1.01f)
						{
							aPos[0].z += g_aBullet[nCntBullet].posOld.z;
							Hit = aPos[0] + Wallvec * PosCross;
							movevec = g_aBullet[nCntBullet].pos - Hit;//プレイヤーの移動ベクトル
							Norvec = D3DXVECTOR3(Wallvec.y, -Wallvec.x, Wallvec.z);
							D3DXVec3Normalize(&Norvec, &Norvec);
							Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.y * Norvec.y));
							g_aBullet[nCntBullet].dir = movevec + Dovec * 2.0f;
						}
					}
				}
			}
			pStage = GetStage();
			for (nCntWall = 0; nCntWall < STAGE_MAX; nCntWall++, pStage++)
			{//壁の数
				if (pStage->bUse)
				{//使っている透明でない壁
					aPos[0] = D3DXVECTOR3(pStage->pos.x + sinf(pStage->rot.y - pStage->fAngle) * pStage->fLength, pStage->pos.y + pStage->vtxMin.y, pStage->pos.z + cosf(pStage->rot.y - pStage->fAngle) * pStage->fLength);
					aPos[1] = D3DXVECTOR3(pStage->pos.x + sinf(pStage->rot.y - (D3DX_PI - pStage->fAngle)) * pStage->fLength, pStage->pos.y + pStage->vtxMin.y, pStage->pos.z + cosf(pStage->rot.y - (D3DX_PI - pStage->fAngle)) * pStage->fLength);
					aPos[2] = D3DXVECTOR3(pStage->pos.x + sinf(pStage->rot.y - (D3DX_PI + pStage->fAngle)) * pStage->fLength, pStage->pos.y + pStage->vtxMin.y, pStage->pos.z + cosf(pStage->rot.y - (D3DX_PI + pStage->fAngle)) * pStage->fLength);
					aPos[3] = D3DXVECTOR3(pStage->pos.x + sinf(pStage->rot.y + pStage->fAngle) * pStage->fLength, pStage->pos.y + pStage->vtxMin.y, pStage->pos.z + cosf(pStage->rot.y + pStage->fAngle) * pStage->fLength);

					Wallvec = aPos[1] - aPos[0];//壁のベクトル
					Posvec = g_aBullet[nCntBullet].pos - aPos[0];//壁に対するプレイヤーのベクトル
					PosOldvec = g_aBullet[nCntBullet].posOld - aPos[0];//壁に対するプレイヤーの旧ベクトル
					movevec = g_aBullet[nCntBullet].pos - g_aBullet[nCntBullet].posOld;//プレイヤーの移動ベクトル
					if ((Wallvec.z * Posvec.x) - (Wallvec.x * Posvec.z) < WALL_COLL_SPASE && (Wallvec.z * PosOldvec.x) - (Wallvec.x * PosOldvec.z) >= WALL_COLL_SPASE && g_aBullet[nCntBullet].pos.y - BULLET_HEIGHT * 0.5f < pStage->pos.y + pStage->vtxMax.y * pStage->scale.y && g_aBullet[nCntBullet].pos.y + BULLET_HEIGHT * 0.5f > pStage->pos.y + pStage->vtxMin.y)
					{//壁の外側
						WallCross = (Wallvec.z * movevec.x) - (Wallvec.x * movevec.z);
						PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
						PosCross /= WallCross;
						if (PosCross >= -0.01f && PosCross < 1.01f)
						{
							aPos[0].y += g_aBullet[nCntBullet].posOld.y;
							Hit = aPos[0] + Wallvec * PosCross;
							movevec = g_aBullet[nCntBullet].pos - Hit;//プレイヤーの移動ベクトル
							Norvec = D3DXVECTOR3(Wallvec.z, Wallvec.y, -Wallvec.x);
							D3DXVec3Normalize(&Norvec, &Norvec);
							Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
							g_aBullet[nCntBullet].dir = movevec + Dovec * 2.0f;
						}
					}

					Wallvec = aPos[2] - aPos[1];//壁のベクトル
					Posvec = g_aBullet[nCntBullet].pos - aPos[1];//壁に対するプレイヤーのベクトル
					PosOldvec = g_aBullet[nCntBullet].posOld - aPos[1];//壁に対するプレイヤーの旧ベクトル
					movevec = g_aBullet[nCntBullet].pos - g_aBullet[nCntBullet].posOld;//プレイヤーの移動ベクトル
					if ((Wallvec.z * Posvec.x) - (Wallvec.x * Posvec.z) < WALL_COLL_SPASE && (Wallvec.z * PosOldvec.x) - (Wallvec.x * PosOldvec.z) >= WALL_COLL_SPASE && g_aBullet[nCntBullet].pos.y - BULLET_HEIGHT * 0.5f < pStage->pos.y + pStage->vtxMax.y * pStage->scale.y && g_aBullet[nCntBullet].pos.y + BULLET_HEIGHT * 0.5f > pStage->pos.y + pStage->vtxMin.y)
					{//壁の外側
						WallCross = (Wallvec.z * movevec.x) - (Wallvec.x * movevec.z);
						PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
						PosCross /= WallCross;
						if (PosCross >= -0.01f && PosCross < 1.01f)
						{
							aPos[1].y += g_aBullet[nCntBullet].posOld.y;
							Hit = aPos[1] + Wallvec * PosCross;
							movevec = g_aBullet[nCntBullet].pos - Hit;//プレイヤーの移動ベクトル
							Norvec = D3DXVECTOR3(Wallvec.z, Wallvec.y, -Wallvec.x);
							D3DXVec3Normalize(&Norvec, &Norvec);
							Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
							g_aBullet[nCntBullet].dir = movevec + Dovec * 2.0f;
						}
					}

					Wallvec = aPos[3] - aPos[2];//壁のベクトル
					Posvec = g_aBullet[nCntBullet].pos - aPos[2];//壁に対するプレイヤーのベクトル
					PosOldvec = g_aBullet[nCntBullet].posOld - aPos[2];//壁に対するプレイヤーの旧ベクトル
					movevec = g_aBullet[nCntBullet].pos - g_aBullet[nCntBullet].posOld;//プレイヤーの移動ベクトル
					if ((Wallvec.z * Posvec.x) - (Wallvec.x * Posvec.z) < WALL_COLL_SPASE && (Wallvec.z * PosOldvec.x) - (Wallvec.x * PosOldvec.z) >= WALL_COLL_SPASE && g_aBullet[nCntBullet].pos.y - BULLET_HEIGHT * 0.5f < pStage->pos.y + pStage->vtxMax.y * pStage->scale.y && g_aBullet[nCntBullet].pos.y + BULLET_HEIGHT * 0.5f > pStage->pos.y + pStage->vtxMin.y)
					{//壁の外側
						WallCross = (Wallvec.z * movevec.x) - (Wallvec.x * movevec.z);
						PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
						PosCross /= WallCross;
						if (PosCross >= -0.01f && PosCross < 1.01f)
						{
							aPos[2].y += g_aBullet[nCntBullet].posOld.y;
							Hit = aPos[2] + Wallvec * PosCross;
							movevec = g_aBullet[nCntBullet].pos - Hit;//プレイヤーの移動ベクトル
							Norvec = D3DXVECTOR3(Wallvec.z, Wallvec.y, -Wallvec.x);
							D3DXVec3Normalize(&Norvec, &Norvec);
							Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
							g_aBullet[nCntBullet].dir = movevec + Dovec * 2.0f;
						}
					}

					Wallvec = aPos[0] - aPos[3];//壁のベクトル
					Posvec = g_aBullet[nCntBullet].pos - aPos[3];//壁に対するプレイヤーのベクトル
					PosOldvec = g_aBullet[nCntBullet].posOld - aPos[3];//壁に対するプレイヤーの旧ベクトル
					movevec = g_aBullet[nCntBullet].pos - g_aBullet[nCntBullet].posOld;//プレイヤーの移動ベクトル
					if ((Wallvec.z * Posvec.x) - (Wallvec.x * Posvec.z) < WALL_COLL_SPASE && (Wallvec.z * PosOldvec.x) - (Wallvec.x * PosOldvec.z) >= WALL_COLL_SPASE && g_aBullet[nCntBullet].pos.y - BULLET_HEIGHT * 0.5f < pStage->pos.y + pStage->vtxMax.y * pStage->scale.y && g_aBullet[nCntBullet].pos.y + BULLET_HEIGHT * 0.5f > pStage->pos.y + pStage->vtxMin.y)
					{//壁の外側
						WallCross = (Wallvec.z * movevec.x) - (Wallvec.x * movevec.z);
						PosCross = (Posvec.z * movevec.x) - (Posvec.x * movevec.z);
						PosCross /= WallCross;
						if (PosCross >= -0.01f && PosCross < 1.01f)
						{
							aPos[3].y += g_aBullet[nCntBullet].posOld.y;
							Hit = aPos[3] + Wallvec * PosCross;
							movevec = g_aBullet[nCntBullet].pos - Hit;//プレイヤーの移動ベクトル
							Norvec = D3DXVECTOR3(Wallvec.z, Wallvec.y, -Wallvec.x);
							D3DXVec3Normalize(&Norvec, &Norvec);
							Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.z * Norvec.z));
							g_aBullet[nCntBullet].dir = movevec + Dovec * 2.0f;
						}
					}
				}
			}
		}
	}
}