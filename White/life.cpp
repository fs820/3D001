//---------------------------------------
//
//スコア処理[Life.cpp]
//Author fuma sato
//
//---------------------------------------

#include"Life.h"
#include"camera.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;//バッファのポインタ
Life g_aLife[LIFE_MAX];
//-------------------------
//ポリゴンの初期化処理
//-------------------------
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	VERTEX_3D* pVtx;//頂点情報ポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//バッファーの設定
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * VT_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL
	);

	for (int nCnt = 0; nCnt < LIFE_MAX; nCnt++)
	{
		g_aLife[nCnt].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_aLife[nCnt].scale = D3DXVECTOR3(1.0f, 1.0f,1.0f);
		g_aLife[nCnt].bUse = false;
	}

	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);//プレイヤーバッファのロック

	//座標設定
	pVtx[0].pos = D3DXVECTOR3(-LIFE_WIDTH * 0.5f, LIFE_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(LIFE_WIDTH * 0.5f, LIFE_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-LIFE_WIDTH * 0.5f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(LIFE_WIDTH * 0.5f, 0.0f, 0.0f);

	//nor
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	//テクスチャ
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffLife->Unlock();//プレイヤーバッファのアンロック
}

//--------------------------
//ポリゴンの終了処理
//--------------------------
void UninitLife(void)
{
	//頂点バッファの破棄
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

//--------------------------
//ポリゴンの更新処理
//--------------------------
void UpdateLife(void)
{

}

//----------------------------
//ポリゴンの描画処理
//----------------------------
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATRIX mtxScale, mtxTrans;//計算マトリックス

	//デバイスの取得
	pDevice = GetDevice();

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Zテストオフ
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (int nCnt = 0; nCnt < LIFE_MAX; nCnt++)
	{
		if (g_aLife[nCnt].bUse)
		{
			//マトリックス初期化
			D3DXMatrixIdentity(&g_aLife[nCnt].mtxWorld);

			//ビューマトリックス取得
			D3DXMATRIX mtxView;
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//カメラの逆行列を設定
			g_aLife[nCnt].mtxWorld._11 = mtxView._11;
			g_aLife[nCnt].mtxWorld._12 = mtxView._21;
			g_aLife[nCnt].mtxWorld._13 = mtxView._31;
			g_aLife[nCnt].mtxWorld._21 = mtxView._12;
			g_aLife[nCnt].mtxWorld._22 = mtxView._22;
			g_aLife[nCnt].mtxWorld._23 = mtxView._32;
			g_aLife[nCnt].mtxWorld._31 = mtxView._13;
			g_aLife[nCnt].mtxWorld._32 = mtxView._23;
			g_aLife[nCnt].mtxWorld._33 = mtxView._33;

			//大きさの反映
			D3DXMatrixScaling(&mtxScale, g_aLife[nCnt].scale.x, g_aLife[nCnt].scale.y, g_aLife[nCnt].scale.z);
			D3DXMatrixMultiply(&g_aLife[nCnt].mtxWorld, &g_aLife[nCnt].mtxWorld, &mtxScale);

			//位置の計算
			D3DXMatrixTranslation(&mtxTrans, g_aLife[nCnt].pos.x, g_aLife[nCnt].pos.y, g_aLife[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aLife[nCnt].mtxWorld, &g_aLife[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aLife[nCnt].mtxWorld);

			//頂点バッファ
			pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, NULL);

			//背景の描画
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,//タイプ
				0,//始まりの番号
				2//ポリゴンの個数
			);
		}
	}

	//Zテストオン
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//-----------------------
//ゲージセット
//-----------------------
int LinkLife(void)
{
	for (int nCnt = 0; nCnt < LIFE_MAX; nCnt++)
	{
		if (!g_aLife[nCnt].bUse)
		{
			g_aLife[nCnt].bUse = true;
			return nCnt;
		}
	}

	return -1;
}

//-----------------------
//ゲージセット
//-----------------------
void NullLife(int Indx)
{
	g_aLife[Indx].bUse = false;
}

//-----------------------
//ゲージ更新
//-----------------------
void SetLife(D3DXVECTOR3 pos, float Life, int Indx)
{
	if (g_aLife[Indx].bUse)
	{
		Camera* pCamera = GetCamera();

		g_aLife[Indx].pos = pos;
		g_aLife[Indx].pos.x -= sinf(pCamera->rot.y + D3DX_PI * 0.5f) * LIFE_WIDTH * (1.0f - Life) * 0.5f;
		g_aLife[Indx].pos.y += LIFE_SPACE;
		g_aLife[Indx].pos.z -= cosf(pCamera->rot.y + D3DX_PI * 0.5f) * LIFE_WIDTH * (1.0f - Life) * 0.5f;
		g_aLife[Indx].scale.x = Life;
		g_aLife[Indx].scale.x = max(0.0f, min(1.0f, g_aLife[Indx].scale.x));
		g_aLife[Indx].scale.z = Life;
		g_aLife[Indx].scale.z = max(0.0f, min(1.0f, g_aLife[Indx].scale.x));
	}
}