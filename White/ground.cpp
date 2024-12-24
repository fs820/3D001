//----------------------------------------
//
//ポリゴン表示処理[ground.cpp]
//Author fuma sato
//
//----------------------------------------

#include"ground.h"
#include"camera.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGround=NULL;//バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureGround = NULL;
Ground g_aGround[GROUND_MAX];

//----------------------
//ポリゴンの初期化処理
//----------------------
void InitGround(void)
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
		&g_pVtxBuffGround,
		NULL
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		GROUND_TEX,
		&g_pTextureGround
	);

	int nCntGround;
	for (nCntGround = 0; nCntGround < GROUND_MAX; nCntGround++)
	{
		g_aGround[nCntGround].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGround[nCntGround].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGround[nCntGround].bAlpha = false;
		g_aGround[nCntGround].bUse = false;
	}
	//1つ目

	g_pVtxBuffGround->Lock(0,0,(void**)&pVtx,0);

	//座標設定
	pVtx[0].pos = D3DXVECTOR3(g_aGround[nCntGround].pos.x - GROUND_WIDTH * 0.5f, g_aGround[nCntGround].pos.y + GROUND_HEIGHT, g_aGround[nCntGround].pos.z + GROUND_Z * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(g_aGround[nCntGround].pos.x + GROUND_WIDTH * 0.5f, g_aGround[nCntGround].pos.y + GROUND_HEIGHT, g_aGround[nCntGround].pos.z + GROUND_Z * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(g_aGround[nCntGround].pos.x - GROUND_WIDTH * 0.5f, g_aGround[nCntGround].pos.y, g_aGround[nCntGround].pos.z - GROUND_Z * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(g_aGround[nCntGround].pos.x + GROUND_WIDTH * 0.5f, g_aGround[nCntGround].pos.y, g_aGround[nCntGround].pos.z - GROUND_Z * 0.5f);

	//nor
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(GROUND_WIDTH / GROUND_WIDTH_DEF, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, GROUND_Z / GROUND_Z_DEF);
	pVtx[3].tex = D3DXVECTOR2(GROUND_WIDTH / GROUND_WIDTH_DEF, GROUND_Z / GROUND_Z_DEF);

	g_pVtxBuffGround->Unlock();
}

//-------------------
//ポリゴン終了処理
//-------------------
void UninitGround(void)
{
	//テクスチャの破棄
	if (g_pTextureGround != NULL)
	{
		g_pTextureGround->Release();
		g_pTextureGround = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffGround != NULL)
	{
		g_pVtxBuffGround->Release();
		g_pVtxBuffGround = NULL;
	}
}

//-------------------
//ポリゴン更新処理
//-------------------
void UpdateGround(void)
{

}

//-------------------
//ポリゴン描画処理
//-------------------
void DrawGround(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATRIX mtxRot, mtxTrans;//計算マトリックス

    //デバイスの取得
	pDevice = GetDevice();

	int nCntGround;
	for (nCntGround = 0; nCntGround < GROUND_MAX; nCntGround++)
	{
		if (g_aGround[nCntGround].bUse && !g_aGround[nCntGround].bAlpha)
		{
			//マトリックス初期化
			D3DXMatrixIdentity(&g_aGround[nCntGround].mtxWorld);

			//向きの反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aGround[nCntGround].rot.y, g_aGround[nCntGround].rot.x, g_aGround[nCntGround].rot.z);
			D3DXMatrixMultiply(&g_aGround[nCntGround].mtxWorld, &g_aGround[nCntGround].mtxWorld, &mtxRot);

			//位置の計算
			D3DXMatrixTranslation(&mtxTrans, g_aGround[nCntGround].pos.x, g_aGround[nCntGround].pos.y, g_aGround[nCntGround].pos.z);
			D3DXMatrixMultiply(&g_aGround[nCntGround].mtxWorld, &g_aGround[nCntGround].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aGround[nCntGround].mtxWorld);

			//頂点バッファ
			pDevice->SetStreamSource(0, g_pVtxBuffGround, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureGround);

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

//----------
//設定
//----------
void SetGround(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntGround;
	for (nCntGround = 0; nCntGround < GROUND_MAX; nCntGround++)
	{
		if (!g_aGround[nCntGround].bUse)
		{
			g_aGround[nCntGround].pos = pos;
			g_aGround[nCntGround].rot = rot;
			g_aGround[nCntGround].bAlpha = false;
			g_aGround[nCntGround].bUse = true;
			break;
		}
	}
}