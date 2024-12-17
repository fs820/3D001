//---------------------------------------
//
//スコア処理[time.cpp]
//Author fuma sato
//
//---------------------------------------

#include"Time.h"
#include"game.h"

LPDIRECT3DTEXTURE9 g_pTextureTime[TIME_MAX] = { NULL };//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;//バッファのポインタ
Time g_aTime[TIME_MAX];
//-------------------------
//ポリゴンの初期化処理
//-------------------------
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	VERTEX_2D* pVtx;//頂点情報ポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//バッファーの設定
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * VT_MAX * TIME_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		TIME_TEX,
		&g_pTextureTime[0]
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		TIME_TEX2,
		&g_pTextureTime[1]
	);

	for (int nCnt = 0; nCnt < TIME_MAX; nCnt++)
	{
		g_aTime[nCnt].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, TIME_HEIGHT / 2, 0.0f);
		g_aTime[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * -0.57f);
	}

	g_aTime[0].fLength = sqrtf(TIME_WIDTH * TIME_WIDTH + TIME_HEIGHT * TIME_HEIGHT) / 2.0f;//対角線の長さ
	g_aTime[0].fAngle = atan2f(TIME_WIDTH, TIME_HEIGHT);//角度
	g_aTime[1].fLength = sqrtf((TIME_WIDTH2 * 0.5f) * (TIME_WIDTH2 * 0.5f) + TIME_HEIGHT2 * TIME_HEIGHT2);//対角線の長さ
	g_aTime[1].fAngle = atan2f(TIME_WIDTH2 * 0.5f, TIME_HEIGHT2);//角度

	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);//プレイヤーバッファのロック

	//座標設定
	pVtx[0].pos.x = g_aTime[0].pos.x + sinf(g_aTime[0].rot.z - (D3DX_PI - g_aTime[0].fAngle)) * g_aTime[0].fLength;
	pVtx[0].pos.y = g_aTime[0].pos.y + cosf(g_aTime[0].rot.z - (D3DX_PI - g_aTime[0].fAngle)) * g_aTime[0].fLength;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_aTime[0].pos.x + sinf(g_aTime[0].rot.z - (D3DX_PI + g_aTime[0].fAngle)) * g_aTime[0].fLength;
	pVtx[1].pos.y = g_aTime[0].pos.y + cosf(g_aTime[0].rot.z - (D3DX_PI + g_aTime[0].fAngle)) * g_aTime[0].fLength;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_aTime[0].pos.x + sinf(g_aTime[0].rot.z - g_aTime[0].fAngle) * g_aTime[0].fLength;
	pVtx[2].pos.y = g_aTime[0].pos.y + cosf(g_aTime[0].rot.z - g_aTime[0].fAngle) * g_aTime[0].fLength;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_aTime[0].pos.x + sinf(g_aTime[0].rot.z + g_aTime[0].fAngle) * g_aTime[0].fLength;
	pVtx[3].pos.y = g_aTime[0].pos.y + cosf(g_aTime[0].rot.z + g_aTime[0].fAngle) * g_aTime[0].fLength;
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

	//座標設定
	pVtx[0].pos.x = g_aTime[1].pos.x + sinf(g_aTime[1].rot.z - (D3DX_PI - g_aTime[1].fAngle)) * g_aTime[1].fLength;
	pVtx[0].pos.y = g_aTime[1].pos.y + cosf(g_aTime[1].rot.z - (D3DX_PI - g_aTime[1].fAngle)) * g_aTime[1].fLength;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_aTime[1].pos.x + sinf(g_aTime[1].rot.z - (D3DX_PI + g_aTime[1].fAngle)) * g_aTime[1].fLength;
	pVtx[1].pos.y = g_aTime[1].pos.y + cosf(g_aTime[1].rot.z - (D3DX_PI + g_aTime[1].fAngle)) * g_aTime[1].fLength;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_aTime[1].pos.x + sinf(g_aTime[1].rot.z - D3DX_PI * 0.5f) * g_aTime[1].fLength;
	pVtx[2].pos.y = g_aTime[1].pos.y + cosf(g_aTime[1].rot.z - D3DX_PI * 0.5f) * g_aTime[1].fLength;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_aTime[1].pos.x + sinf(g_aTime[1].rot.z + D3DX_PI * 0.5f) * g_aTime[1].fLength;
	pVtx[3].pos.y = g_aTime[1].pos.y + cosf(g_aTime[1].rot.z + D3DX_PI * 0.5f) * g_aTime[1].fLength;
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

	g_pVtxBuffTime->Unlock();//プレイヤーバッファのアンロック
}

//--------------------------
//ポリゴンの終了処理
//--------------------------
void UninitTime(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < TIME_MAX; nCnt++)
	{
		if (g_pTextureTime[nCnt] != NULL)
		{
			g_pTextureTime[nCnt]->Release();
			g_pTextureTime[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//--------------------------
//ポリゴンの更新処理
//--------------------------
void UpdateTime(void)
{

}

//----------------------------
//ポリゴンの描画処理
//----------------------------
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファ
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < TIME_MAX; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTime[nCnt]);

		//背景の描画
		pDevice->DrawPrimitive
		(
			D3DPT_TRIANGLESTRIP,//タイプ
			VT_MAX * nCnt,//始まりの番号
			2//ポリゴンの個数
		);
	}
}

//-----------------------
//タイム更新
//-----------------------
void SetTime(float Time)
{
	VERTEX_2D* pVtx;//頂点情報ポインタ

	Time /= (float)TIME_LIMIT;

	g_aTime[1].rot.z = -(D3DX_PI * 2.0f) * Time;

	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);//プレイヤーバッファのロック
	pVtx += VT_MAX;

	//座標設定
	pVtx[0].pos.x = g_aTime[1].pos.x + sinf(g_aTime[1].rot.z - (D3DX_PI - g_aTime[1].fAngle)) * g_aTime[1].fLength;
	pVtx[0].pos.y = g_aTime[1].pos.y + cosf(g_aTime[1].rot.z - (D3DX_PI - g_aTime[1].fAngle)) * g_aTime[1].fLength;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_aTime[1].pos.x + sinf(g_aTime[1].rot.z - (D3DX_PI + g_aTime[1].fAngle)) * g_aTime[1].fLength;
	pVtx[1].pos.y = g_aTime[1].pos.y + cosf(g_aTime[1].rot.z - (D3DX_PI + g_aTime[1].fAngle)) * g_aTime[1].fLength;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_aTime[1].pos.x + sinf(g_aTime[1].rot.z - D3DX_PI * 0.5f) * TIME_WIDTH2 * 0.5f;
	pVtx[2].pos.y = g_aTime[1].pos.y + cosf(g_aTime[1].rot.z - D3DX_PI * 0.5f) * TIME_WIDTH2 * 0.5f;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_aTime[1].pos.x + sinf(g_aTime[1].rot.z + D3DX_PI * 0.5f) * TIME_WIDTH2 * 0.5f;
	pVtx[3].pos.y = g_aTime[1].pos.y + cosf(g_aTime[1].rot.z + D3DX_PI * 0.5f) * TIME_WIDTH2 * 0.5f;
	pVtx[3].pos.z = 0.0f;

	g_pVtxBuffTime->Unlock();//プレイヤーバッファのアンロック
}