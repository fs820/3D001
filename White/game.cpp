//------------------------------------------
//
//ゲームメインの処理[game.cpp]
//Author fuma sato
//
//------------------------------------------

#include"game.h"
#include"input.h"
#include"player.h"
#include"Dog.h"
#include"Crow.h"
#include"ground.h"
#include"wall.h"
#include"bullet.h"
#include"explosion.h"
#include"effect.h"
#include"particle.h"
#include"model.h"
#include"pause.h"
#include"time.h"
#include"fade.h"
#include"sound.h"
#include"score.h"
#include"camera.h"
#include"life.h"
#include"hitshere.h"
#include"snow.h"
#include"ui.h"

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

//グローバル変数
GAMESTATE g_gameState = GAMESTATE_NONE;
int g_nCounterGameState = 0;
int g_GameTime = 0;
bool g_bSnow = false;
bool g_bClear = false;
//--------------------
//初期化処理
//--------------------
void InitGame(void)
{
	InitModel();
	InitShadow();
	InitLife();
	InitStage();
	InitMeshField();
	InitLine();
	InitCylinder();
	InitSphere();
	InitSnowBall();
	InitMeshWall();
	InitPlayer();//プレイヤー
	InitDog();
	InitCrow();
	InitBullet();
	InitEffect();
	InitParticle();
	InitSnow();
	InitBillboard();
	InitTime();
	InitUi();
	InitHitShere();

	//空間
	SetMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetCylinder(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetSphere(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//ステージ
	LoadStage();	

	//カメラ
	GameCamera();

	D3DXVECTOR3 posScore;//スコアの位置
	g_gameState = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
	g_GameTime = 0;
	g_bSnow = false;
	g_bClear = false;

	PlaySound(SOUND_LABEL_BGM);

	SetUi(0);
}

//------------------
//終了処理
//------------------
void UninitGame(void)
{
	g_gameState = GAMESTATE_NONE;
	EndSound();

	UninitHitShere();
	UninitUi();
	UninitTime();
	UninitSnow();
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
	UninitCrow();
	UninitDog();
	UninitPlayer();//プレイヤー
	UninitStage();
	UninitLife();
	UninitShadow();
	UninitModel();
}

//--------------
//更新処理
//--------------
void UpdateGame(void)
{
	if (GetKeyboradTrigger(DIK_P) == true || GetJoykeyTrigger(JOYKEY_START, CONTROLLER_MAX) == true || GetMouseTrigger(MOUSE_SENTER) == true)
	{
		FADE fade;
		fade = GetFade();
		if (fade == FADE_NONE)
		{
			Pause(SOUND_LABEL_BGM);
		}
	}
	for (int i = 0; i < ControllerNum(CONTYPE_D); i++)
	{
		if (!strcmp(ControllerName((CONTROLLER)i), ELE_CON))
		{
			if (GetdJoykeyTrigger(ELEKEY_START, (CONTROLLER)i))
			{
				Pause(SOUND_LABEL_BGM);
			}
		}
		else if (!strcmp(ControllerName((CONTROLLER)i), PS_CON))
		{
			if (GetdJoykeyTrigger(PSKEY_START, (CONTROLLER)i))
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					Pause(SOUND_LABEL_BGM);
				}
			}
		}
		else if (!strcmp(ControllerName((CONTROLLER)i), NIN_CON))
		{
			if (GetdJoykeyTrigger(NINKEY_＋, (CONTROLLER)i))
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					Pause(SOUND_LABEL_BGM);
				}
			}
		}
		else if (!IsXInputControllerConnected((CONTROLLER)i) && IsDirectInputControllerConnected((CONTROLLER)i))
		{
			if (GetdJoykeyTrigger(DKEY_START, (CONTROLLER)i))
			{
				Pause(SOUND_LABEL_BGM);
			}
		}
	}
	
	if (!bPause())
	{
		Player* pPlayer;

		pPlayer = GetPlayer();

		switch (g_gameState)
		{
		case GAMESTATE_NORMAL:
			g_GameTime++;
			SetTime((float)(g_GameTime / (float)FRAME));
			if (g_GameTime / FRAME >= TIME_LIMIT)
			{
				g_gameState = GAMESTATE_END;
				g_bClear = true;
			}
			else if (pPlayer->state == PLAYERSTATE_DIE)
			{
				g_gameState = GAMESTATE_END;
				g_bClear = false;
			}
			if ((g_GameTime / FRAME) % (int)(TIME_LIMIT * 0.1f) == 0 && (g_GameTime % FRAME) == 0)
			{
				float RotRand = (((float)(rand() % 201) / 100.0f) - 1.0f) * D3DX_PI, LengthRand = (float)(rand() % 30001)/10.0f;
				SetDog(D3DXVECTOR3(sinf(RotRand) * LengthRand, 0.0f, cosf(RotRand) * LengthRand));
			}
			if ((g_GameTime / FRAME) % (int)(TIME_LIMIT * 0.2f) == 0 && (g_GameTime % FRAME) == 0 && (float)(g_GameTime / FRAME) / (float)TIME_LIMIT >= 0.5f)
			{
				float RotRand = (((float)(rand() % 201) / 100.0f) - 1.0f) * D3DX_PI, LengthRand = (float)(rand() % 30001) / 10.0f;
				SetCrow(D3DXVECTOR3(sinf(RotRand) * LengthRand, 0.0f, cosf(RotRand) * LengthRand));
			}
			if ((g_GameTime / FRAME) == TIME_LIMIT * 0.5f && (g_GameTime % FRAME) == 0)
			{
				SetSnow(D3DXVECTOR3(0.0f, 1000.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
			}
			if ((g_GameTime / FRAME) % (int)(TIME_LIMIT * 0.6f) == 0 && (g_GameTime % FRAME) == 0)
			{
				g_bSnow = true;
				for (int nCnt = 0; nCnt < SNOWBALL_NUM; nCnt++)
				{
					float RotRand = (((float)(rand() % 201) / 100.0f) - 1.0f) * D3DX_PI, LengthRand = (float)(rand() % 30001) / 10.0f;
					SetSnowBall(D3DXVECTOR3(D3DXVECTOR3(sinf(RotRand) * LengthRand, SNOWBALL_RADIUS, cosf(RotRand) * LengthRand)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
				}
				SetUi(2);
			}
			if ((g_GameTime / FRAME) % (int)(TIME_LIMIT * 0.75f) == 0 && (g_GameTime % FRAME) == 0)
			{
				SetSnow(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}
			break;
		case GAMESTATE_END:
			g_nCounterGameState++;
			if (g_nCounterGameState >= INTER)
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					//サウンド
					StopSound(SOUND_LABEL_BGM4);
					//切替
					SetFade(MODE_RESULT);
				}
			}
			break;
		}

		UpdateModel();
		UpdateShadow();
		UpdateLife();
		UpdateStage();
		UpdateGround();
		UpdatePlayer();//プレイヤー
		UpdateDog();
		UpdateCrow();
		UpdateHitShere();
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
		UpdateSnow();
		UpdateUi();
	}
}

//-------------------
//描画処理
//-------------------
void DrawGame(void)
{
	DrawModel();
	DrawGround();
	DrawMeshField();
	DrawLine();
	DrawWall();
	DrawCylinder();
	DrawSphere();
	DrawShadow();
	DrawStage();
	DrawBillboard();
	DrawMeshWall();
	DrawEffect();
	DrawBullet();
	DrawExplosion();
	DrawSnowBall();
	DrawPlayer();//プレイヤー
	DrawDog();
	DrawCrow();
	DrawHitShere();
	DrawAlphaWall();
	DrawAlphaMeshWall();
	DrawLife();
	DrawTime();
	DrawUi();
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

//-----------------------
//スノー取得
//-----------------------
bool GetbSnow(void)
{
	return g_bSnow;
}

//---------------------
//クリア取得
//---------------------
bool GetClear(void)
{
	return g_bClear;
}

//---------------------
//クリア取得
//---------------------
int GetClearTime(void)
{
	int H = (((g_GameTime / FRAME) * (int)(HOUR * ((float)MINUTE / (float)TIME_LIMIT))) / MINUTE) * 100;
	int M = ((g_GameTime / FRAME) * (int)(HOUR * ((float)MINUTE / (float)TIME_LIMIT))) % MINUTE;
	return H + M;
}

//---------------------
//クリア取得
//---------------------
int GetTime(void)
{
	return g_GameTime / FRAME;
}

//---------------------
//時間初期化
//---------------------
void TimeReset(void)
{
	g_GameTime = 0;
}