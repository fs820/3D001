//------------------------------------------
//
//ランキングの処理[rank.cpp]
//Author fuma sato
//
//------------------------------------------

#include"rank.h"
#include"game.h"
#include"input.h"
#include"fade.h"
#include"sound.h"
#include"score.h"
#include"file.h"
#include"cursor.h"
#include"pause.h"
#include"camera.h"

#include"shadow.h"
#include"billboard.h"
#include"stage.h"
#include"file.h"
#include"meshfield.h"
#include"cylinder.h"
#include"sphere.h"
#include"meshwall.h"
#include"line.h"
#include"snowball.h"

#define NUMBER_WIDTH (64)
#define NUMBER_HEIGHT (750)
#define RANK_MAX (2)
#define RANK_TIME (600)
#define NUMBER_SEPAESE (20)

LPDIRECT3DTEXTURE9 g_apTextureRank[RANK_MAX] = { NULL };//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;//バッファのポインタ
int g_nNewDataRank;
bool g_bRankin = false;

//--------------------
//初期化処理
//--------------------
void InitRank(void)
{
	InitShadow();
	InitStage();
	InitMeshField();
	InitLine();
	InitCylinder();
	InitSphere();
	InitSnowBall();
	InitMeshWall();
	InitBillboard();

	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	VERTEX_2D* pVtx;//頂点情報ポインタ
	D3DXVECTOR3 posScore;//スコアの位置
	D3DXVECTOR3 posScoreDef;//スコアの位置
	int nScore[MAX_DATA+1] = { 0 };
	int aPosTexUr[MAX_DATA+1][SCORE_MAX];
	int* pData;

	//デバイスの取得
	pDevice = GetDevice();

	//バッファーの設定
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * VT_MAX * (SCORE_MAX*MAX_DATA+1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NUMBER,
		&g_apTextureRank[0]
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_RANK,
		&g_apTextureRank[1]
	);

	//過去のスコアの取得
	pData = LoadFile();
	for (int i = 0; i < MAX_DATA; i++,pData++)
	{
		nScore[i] = *pData;
	}

	//今回のスコアの取得
	nScore[MAX_DATA] = GetClearTime();
	pData = Soat(&nScore[0]);
	for (int i = 0; i < MAX_DATA; i++, pData++)
	{
		nScore[i] = *pData;
	}
	//セーブ処理
	SaveFile(&nScore[0]);

	//表示準備
	for (int i = 0; i < MAX_DATA; i++)
	{
		if (nScore[i] == GetClearTime()&&nScore[i]!=0)
		{
			g_nNewDataRank = i;
			g_bRankin=true;
			break;
		}
		else if (i==MAX_DATA-1)
		{
			g_nNewDataRank = 99;
			g_bRankin = false;
		}
	}
	for (int i = 0; i < MAX_DATA; i++)
	{
		for (int i2 = 0; i2 < 2; i2++)
		{
			aPosTexUr[i][i2] = Digit(nScore[i], i2);
		}
		aPosTexUr[i][2] = 10;
		for (int i2 = 3; i2 < 5; i2++)
		{
			aPosTexUr[i][i2] = Digit(nScore[i], i2 - 1);
		}
	}

	TimeReset();
	posScore = D3DXVECTOR3(SCREEN_WIDTH / 2 - (SCORE_WIDTH / SCORE_MAX) * (SCORE_MAX / 2), SCORE_HEIGHT, 0.0f);
	posScoreDef = posScore;

	//空間
	SetMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetCylinder(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetSphere(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//石
	SetSnowBall(D3DXVECTOR3(0.0f, SNOWBALL_RADIUS, 1500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	//ステージ
	LoadStage();

	//カメラ
	ViewCamera();

	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);//プレイヤーバッファのロック

	for (int i = 0; i < MAX_DATA; i++)
	{
		for (int i2 = 0; i2 < SCORE_MAX; i2++)
		{
			//座標設定
			pVtx[0].pos = D3DXVECTOR3(posScore.x - (SCORE_WIDTH / SCORE_MAX) / 2, posScore.y - SCORE_HEIGHT / 2, posScore.z);
			pVtx[1].pos = D3DXVECTOR3(posScore.x + (SCORE_WIDTH / SCORE_MAX) / 2, posScore.y - SCORE_HEIGHT / 2, posScore.z);
			pVtx[2].pos = D3DXVECTOR3(posScore.x - (SCORE_WIDTH / SCORE_MAX) / 2, posScore.y + SCORE_HEIGHT / 2, posScore.z);
			pVtx[3].pos = D3DXVECTOR3(posScore.x + (SCORE_WIDTH / SCORE_MAX) / 2, posScore.y + SCORE_HEIGHT / 2, posScore.z);

			//rhw
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			if (i == 0)
			{
				//カラー
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			}
			else if (i == g_nNewDataRank)
			{
				//カラー
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			}
			else
			{
				//カラー
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}

			//テクスチャ
			pVtx[0].tex = D3DXVECTOR2(UV_DEF / U_MAX_S * aPosTexUr[i][i2], UV_DEF / V_MAX_S * (aPosTexUr[i][i2] / U_MAX_S));
			pVtx[1].tex = D3DXVECTOR2(UV_DEF / U_MAX_S * aPosTexUr[i][i2] + UV_DEF / U_MAX_S, UV_DEF / V_MAX_S * (aPosTexUr[i][i2] / U_MAX_S));
			pVtx[2].tex = D3DXVECTOR2(UV_DEF / U_MAX_S * aPosTexUr[i][i2], UV_DEF / V_MAX_S * (aPosTexUr[i][i2] / U_MAX_S) + UV_DEF / V_MAX_S);
			pVtx[3].tex = D3DXVECTOR2(UV_DEF / U_MAX_S * aPosTexUr[i][i2] + UV_DEF / U_MAX_S, UV_DEF / V_MAX_S * (aPosTexUr[i][i2] / U_MAX_S) + UV_DEF / V_MAX_S);

			posScore.x += SCORE_WIDTH / SCORE_MAX;
			pVtx += VT_MAX;
		}
		posScore = posScoreDef;
		posScore.y += SCORE_HEIGHT * (i+1);
	}

	//座標設定
	pVtx[0].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - SCORE_WIDTH / 2 - NUMBER_WIDTH- NUMBER_SEPAESE, SCREEN_HEIGHT / 2 - NUMBER_HEIGHT / 2- NUMBER_SEPAESE/2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - SCORE_WIDTH / 2- NUMBER_SEPAESE, SCREEN_HEIGHT / 2 - NUMBER_HEIGHT / 2- NUMBER_SEPAESE/2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - SCORE_WIDTH / 2 - NUMBER_WIDTH- NUMBER_SEPAESE, SCREEN_HEIGHT / 2 + NUMBER_HEIGHT / 2- NUMBER_SEPAESE/2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2) - SCORE_WIDTH / 2- NUMBER_SEPAESE, SCREEN_HEIGHT / 2 + NUMBER_HEIGHT / 2- NUMBER_SEPAESE/2, 0.0f);

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

	g_pVtxBuffRank->Unlock();//プレイヤーバッファのアンロック
	PlaySound(SOUND_LABEL_BGM6);
	if (g_bRankin)
	{
		if (g_nNewDataRank==0)
		{
			PlaySound(SOUND_LABEL_BEST);
		}
		else
		{
			PlaySound(SOUND_LABEL_RANKIN);
		}
	}
	else
	{
		PlaySound(SOUND_LABEL_NORANKIN);
	}
}

//--------------------
//終了処理
//--------------------
void UninitRank(void)
{
	//サウンド
	EndSound();

	UninitShadow();
	UninitStage();
	UninitMeshField();
	UninitLine();
	UninitCylinder();
	UninitSphere();
	UninitSnowBall();
	UninitMeshWall();
	UninitBillboard();

	//テクスチャの破棄
	for (int i = 0; i < RANK_MAX; i++)
	{
		if (g_apTextureRank[i] != NULL)
		{
			g_apTextureRank[i]->Release();
			g_apTextureRank[i] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}
}

//--------------------
//更新処理
//--------------------
void UpdateRank(void)
{
	VERTEX_2D* pVtx;//頂点情報ポインタ
	static int nRankTime = 0;

	if (nRankTime % RANK_TIME == 0 && nRankTime != 0)
	{
		nRankTime = 0;
		FADE fade;
		fade = GetFade();
		if (fade == FADE_NONE)
		{
			//サウンド
			StopSound(SOUND_LABEL_BGM6);
			//切替
			SetFade(MODE_TITLE);
		}
	}

	if (GetKeyboradTrigger(DIK_RETURN) == true || GetJoykeyTrigger(JOYKEY_A, CONTROLLER_MAX) == true || GetJoykeyTrigger(JOYKEY_START, CONTROLLER_MAX) == true || GetMouseTrigger(MOUSE_LEFT) == true)
	{
		nRankTime = 0;
		FADE fade;
		fade = GetFade();
		if (fade == FADE_NONE)
		{
			Pause(SOUND_LABEL_BGM6);
		}
	}
	for (int i = 0; i < ControllerNum(CONTYPE_D); i++)
	{
		if (!strcmp(ControllerName((CONTROLLER)i), ELE_CON))
		{
			if (GetdJoykeyTrigger(ELEKEY_A, (CONTROLLER)i) || GetdJoykeyTrigger(ELEKEY_START, (CONTROLLER)i))
			{
				Pause(SOUND_LABEL_BGM6);
			}
		}
		else if (!strcmp(ControllerName((CONTROLLER)i), PS_CON))
		{
			if (GetdJoykeyTrigger(PSKEY_CI, (CONTROLLER)i) || GetdJoykeyTrigger(PSKEY_START, (CONTROLLER)i))
			{
				nRankTime = 0;
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					Pause(SOUND_LABEL_BGM6);
				}
			}
		}
		else if (!strcmp(ControllerName((CONTROLLER)i), NIN_CON))
		{
			if (GetdJoykeyTrigger(NINKEY_A, (CONTROLLER)i) || GetdJoykeyTrigger(NINKEY_＋, (CONTROLLER)i))
			{
				nRankTime = 0;
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					Pause(SOUND_LABEL_BGM6);
				}
			}
		}
		else if (!IsXInputControllerConnected((CONTROLLER)i) && IsDirectInputControllerConnected((CONTROLLER)i))
		{
			if (GetdJoykeyTrigger(DKEY_A, (CONTROLLER)i) || GetdJoykeyTrigger(DKEY_START, (CONTROLLER)i))
			{
				Pause(SOUND_LABEL_BGM6);
			}
		}
	}

	if (g_bRankin)
	{
		static float Color = 0.0f;
		static float Speed = COLOR_SPEED;
		Color += Speed;
		if (Color >= 1.0f || Color <= 0.0f)
		{
			Speed = -Speed;
		}
		g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);//プレイヤーバッファのロック
		pVtx += VT_MAX * g_nNewDataRank * MAX_DATA;

		for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
		{
			//カラー
			pVtx[0].col = D3DXCOLOR(Color, Color, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(Color, Color, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(Color, Color, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(Color, Color, 1.0f, 1.0f);

			pVtx += VT_MAX;
		}
	}

	g_pVtxBuffRank->Unlock();//プレイヤーバッファのアンロック

	if (!bPause())
	{
		nRankTime++;

		UpdateShadow();
		UpdateStage();
		UpdateMeshField();
		UpdateLine();
		UpdateCylinder();
		UpdateSphere();
		UpdateSnowBall();
		UpdateMeshWall();
		UpdateBillboard();
	}
}

//--------------------
//描画処理
//--------------------
void DrawRank(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ

	DrawMeshField();
	DrawLine();
	DrawCylinder();
	DrawSphere();
	DrawShadow();
	DrawStage();
	DrawBillboard();
	DrawMeshWall();
	DrawSnowBall();
	DrawAlphaMeshWall();

//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファ
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntData = 0; nCntData < MAX_DATA; nCntData++)
	{
		for (int nCntScore = 0; nCntScore < SCORE_MAX; nCntScore++)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureRank[0]);

			//背景の描画
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,//タイプ
				(nCntData * SCORE_MAX + nCntScore) * VT_MAX,//始まりの番号
				2//ポリゴンの個数
			);
		}
	}

	//テクスチャの設定
	pDevice->SetTexture(0, g_apTextureRank[1]);

	//背景の描画
	pDevice->DrawPrimitive
	(
		D3DPT_TRIANGLESTRIP,//タイプ
		VT_MAX * SCORE_MAX * MAX_DATA,//始まりの番号
		2//ポリゴンの個数
	);
}