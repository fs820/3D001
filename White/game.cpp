//------------------------------------------
//
//ゲームメインの処理[game.cpp]
//Author fuma sato
//
//------------------------------------------

#include"game.h"
#include"input.h"
#include"player.h"
#include"ground.h"
#include"wall.h"
#include"shadow.h"
#include"billboard.h"
#include"bullet.h"
#include"explosion.h"
#include"effect.h"
#include"particle.h"
#include"stage.h"
#include"file.h"
#include"meshfield.h"
#include"cylinder.h"
#include"sphere.h"
#include"model.h"
#include"meshwall.h"
#include"line.h"
#include"snowball.h"

#define SELECT_WIDTH (512)
#define SELECT_HEIGHT (128)

typedef enum
{
	SELECT_RESTART = 0,
	SELECT_RETRY,
	SELECT_BACK,
	SELECT_EXIT,
	SELECT_MAX,
}SELECT;

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureGame[SELECT_MAX] = { NULL };//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGame = NULL;//バッファのポインタ
GAMESTATE g_gameState = GAMESTATE_NONE;
int g_nCounterGameState = 0;
int g_BossNumber = 0;//どのボスか
bool g_bClear = false;

//--------------------
//初期化処理
//--------------------
void InitGame(void)
{
	InitModel();
	InitShadow();
	InitStage();
	InitGround();
	InitMeshField();
	InitLine();
	InitCylinder();
	InitSphere();
	InitSnowBall();
	InitWall();
	InitMeshWall();
	InitPlayer();//プレイヤー
	InitBullet();
	InitExplosion();
	InitEffect();
	InitParticle();
	InitBillboard();

	//空間
	SetMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetCylinder(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetSphere(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//石
	SetSnowBall(D3DXVECTOR3(0.0f, SNOWBALL_RADIUS, 1500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	//ステージ
	LoadStage();

	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	VERTEX_2D* pVtx;//頂点情報ポインタ
	D3DXVECTOR3 posSelect;//スコアの位置

	//デバイスの取得
	pDevice = GetDevice();

	//バッファーの設定
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * VT_MAX * SELECT_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGame,
		NULL
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		0,
		&g_apTextureGame[0]
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		0,
		&g_apTextureGame[1]
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		0,
		&g_apTextureGame[2]
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		0,
		&g_apTextureGame[3]
	);


	g_gameState = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
	posSelect = D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2-SELECT_HEIGHT*1.5f,0.0f);
	g_bClear = false;

	g_pVtxBuffGame->Lock(0, 0, (void**)&pVtx, 0);//プレイヤーバッファのロック

	for (int i = 0; i < SELECT_MAX; i++)
	{
		//座標設定
		pVtx[0].pos = D3DXVECTOR3(posSelect.x - SELECT_WIDTH / 2, posSelect.y - SELECT_HEIGHT / 2 + i * SELECT_HEIGHT, posSelect.z);
		pVtx[1].pos = D3DXVECTOR3(posSelect.x + SELECT_WIDTH / 2, posSelect.y - SELECT_HEIGHT / 2 + i * SELECT_HEIGHT, posSelect.z);
		pVtx[2].pos = D3DXVECTOR3(posSelect.x - SELECT_WIDTH / 2, posSelect.y + SELECT_HEIGHT / 2 + i * SELECT_HEIGHT, posSelect.z);
		pVtx[3].pos = D3DXVECTOR3(posSelect.x + SELECT_WIDTH / 2, posSelect.y + SELECT_HEIGHT / 2 + i * SELECT_HEIGHT, posSelect.z);

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

	g_pVtxBuffGame->Unlock();//プレイヤーバッファのアンロック
}

//------------------
//終了処理
//------------------
void UninitGame(void)
{
	g_gameState = GAMESTATE_NONE;

	UninitParticle();
	UninitEffect();
	UninitExplosion();
	UninitBullet();
	UninitBillboard();
	UninitMeshWall();
	UninitWall();
	UninitCylinder();
	UninitSnowBall();
	UninitSphere();
	UninitLine();
	UninitGround();
	UninitMeshField();
	UninitPlayer();//プレイヤー
	UninitStage();
	UninitShadow();
	UninitModel();
}

//--------------
//更新処理
//--------------
void UpdateGame(void)
{
	UpdateModel();
	UpdateShadow();
	UpdateStage();
	UpdateGround();
	UpdatePlayer();//プレイヤー
	UpdateWall();
	UpdateMeshWall();
	UpdateMeshField();
	UpdateLine();
	UpdateCylinder();
	UpdateSphere();
	UpdateSnowBall();
	UpdateBillboard();
	UpdateBullet();
	UpdateExplosion();
	UpdateEffect();
	UpdateParticle();
}

//-------------------
//描画処理
//-------------------
void DrawGame(void)
{
	DrawModel();
	DrawLine();
	DrawGround();
	DrawMeshField();
	DrawWall();
	DrawCylinder();
	DrawSphere();
	DrawShadow();
	DrawStage();
	DrawMeshWall();
	DrawBillboard();
	DrawEffect();
	DrawBullet();
	DrawExplosion();
	DrawSnowBall();
	DrawPlayer();//プレイヤー
	DrawAlphaWall();

	if(g_gameState==GAMESTATE_PAUSE)
	{
		LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ

        //デバイスの取得
		pDevice = GetDevice();

		//頂点バッファ
		pDevice->SetStreamSource(0, g_pVtxBuffGame, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		for (int i = 0; i < SELECT_MAX; i++)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureGame[i]);

			//背景の描画
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,//タイプ
				i*VT_MAX,//始まりの番号
				2//ポリゴンの個数
			);
		}
	}
}

//----------------------
//ゲーム状態切替
//----------------------
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//-----------------------
//ゲーム状態取得
//-----------------------
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//---------------------------
//どのボスか
//---------------------------
void SetBossNumber(int Boss)
{
	g_BossNumber = Boss;
}

//---------------------------
//ボス取得	
//---------------------------
int GetBossNumber(void)
{
	return g_BossNumber;
}

//---------------------
//クリア取得
//---------------------
bool GetClear(void)
{
	return g_bClear;
}