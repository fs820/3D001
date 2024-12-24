//---------------------------------------
//
//スコア処理[ui.cpp]
//Author fuma sato
//
//---------------------------------------

#include"ui.h"

LPDIRECT3DTEXTURE9 g_pTextureUi[UI_MAX] = { NULL };//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUi = NULL;//バッファのポインタ
Ui g_aUi[UI_MAX];
//-------------------------
//ポリゴンの初期化処理
//-------------------------
void InitUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	VERTEX_2D* pVtx;//頂点情報ポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//バッファーの設定
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * VT_MAX * UI_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffUi,
		NULL
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		UI_TEX,
		&g_pTextureUi[0]
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		UI_TEX2,
		&g_pTextureUi[1]
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		UI_TEX3,
		&g_pTextureUi[2]
	);

	for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
	{
		g_aUi[nCnt].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.25f,0.0f);
		g_aUi[nCnt].nLife = UI_LIFE;
		g_aUi[nCnt].bUse = false;
	}

	g_pVtxBuffUi->Lock(0, 0, (void**)&pVtx, 0);//プレイヤーバッファのロック

	for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
	{
		//座標設定
		pVtx[0].pos.x = g_aUi[nCnt].pos.x - UI_WIDTH * 0.5f;
		pVtx[0].pos.y = g_aUi[nCnt].pos.y - UI_HEIGHT * 0.5f;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_aUi[nCnt].pos.x + UI_WIDTH * 0.5f;
		pVtx[1].pos.y = g_aUi[nCnt].pos.y - UI_HEIGHT * 0.5f;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_aUi[nCnt].pos.x - UI_WIDTH * 0.5f;
		pVtx[2].pos.y = g_aUi[nCnt].pos.y + UI_HEIGHT * 0.5f;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_aUi[nCnt].pos.x + UI_WIDTH * 0.5f;
		pVtx[3].pos.y = g_aUi[nCnt].pos.y + UI_HEIGHT * 0.5f;
		pVtx[3].pos.z = 0.0f;

		//rhw
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

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

		pVtx += VT_MAX;
	}

	g_pVtxBuffUi->Unlock();//プレイヤーバッファのアンロック
}

//--------------------------
//ポリゴンの終了処理
//--------------------------
void UninitUi(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
	{
		if (g_pTextureUi[nCnt] != NULL)
		{
			g_pTextureUi[nCnt]->Release();
			g_pTextureUi[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffUi != NULL)
	{
		g_pVtxBuffUi->Release();
		g_pVtxBuffUi = NULL;
	}
}

//--------------------------
//ポリゴンの更新処理
//--------------------------
void UpdateUi(void)
{
	VERTEX_2D* pVtx;//頂点情報ポインタ

	for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
	{
		if (g_aUi[nCnt].bUse)
		{
			g_pVtxBuffUi->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += nCnt * VT_MAX;//ポリゴン1つ分進める
			BYTE alpha = (BYTE)(((float)g_aUi[nCnt].nLife) / ((float)UI_LIFE) * 255.0f);
			pVtx[0].col = (pVtx[0].col & 0x00FFFFFF) | (alpha << 24);
			pVtx[1].col = (pVtx[1].col & 0x00FFFFFF) | (alpha << 24);
			pVtx[2].col = (pVtx[2].col & 0x00FFFFFF) | (alpha << 24);
			pVtx[3].col = (pVtx[3].col & 0x00FFFFFF) | (alpha << 24);

			g_pVtxBuffUi->Unlock();//バッファのアンロック

			g_aUi[nCnt].nLife--;

			if (g_aUi[nCnt].nLife <= 0)
			{
				g_aUi[nCnt].bUse = false;
			}
		}
	}
}

//----------------------------
//ポリゴンの描画処理
//----------------------------
void DrawUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファ
	pDevice->SetStreamSource(0, g_pVtxBuffUi, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
	{
		if (g_aUi[nCnt].bUse)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureUi[nCnt]);

			//背景の描画
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,//タイプ
				VT_MAX * nCnt,//始まりの番号
				2//ポリゴンの個数
			);
		}
	}
}

//-----------------------
//タイム更新
//-----------------------
void SetUi(int Number)
{
	for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
	{
		if (!g_aUi[nCnt].bUse)
		{
			g_aUi[Number].nLife = UI_LIFE;
			g_aUi[Number].bUse = true;
		}
	}
}