//------------------------------------------
//
//�Q�[�����C���̏���[game.cpp]
//Author fuma sato
//
//------------------------------------------

#include"game.h"
#include"input.h"
#include"player.h"
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

//�O���[�o���ϐ�
GAMESTATE g_gameState = GAMESTATE_NONE;
int g_nCounterGameState = 0;
int g_GameTime = 0;
bool g_bClear = false;
//--------------------
//����������
//--------------------
void InitGame(void)
{
	InitModel();
	InitShadow();
	InitStage();
	InitMeshField();
	InitLine();
	InitCylinder();
	InitSphere();
	InitSnowBall();
	InitMeshWall();
	InitPlayer();//�v���C���[
	InitBullet();
	InitEffect();
	InitParticle();
	InitBillboard();
	InitTime();
	InitScore();

	//���
	SetMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetCylinder(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetSphere(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//��
	SetSnowBall(D3DXVECTOR3(0.0f, SNOWBALL_RADIUS, 1500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	//�X�e�[�W
	LoadStage();

	SetScore(0, true);

	//�J����
	GameCamera();

	D3DXVECTOR3 posScore;//�X�R�A�̈ʒu
	g_gameState = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
	g_GameTime = 0;
	g_bClear = false;

	PlaySound(SOUND_LABEL_BGM);
}

//------------------
//�I������
//------------------
void UninitGame(void)
{
	g_gameState = GAMESTATE_NONE;
	EndSound();

	UninitScore();
	UninitTime();
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
	UninitPlayer();//�v���C���[
	UninitStage();
	UninitShadow();
	UninitModel();
}

//--------------
//�X�V����
//--------------
void UpdateGame(void)
{
	if (GetKeyboradTrigger(DIK_RETURN) == true || GetJoykeyTrigger(JOYKEY_A, CONTROLLER_MAX) == true || GetJoykeyTrigger(JOYKEY_START, CONTROLLER_MAX) == true || GetMouseTrigger(MOUSE_SENTER) == true)
	{
		FADE fade;
		fade = GetFade();
		if (fade == FADE_NONE)
		{
			Pause();
		}
	}
	for (int i = 0; i < ControllerNum(CONTYPE_D); i++)
	{
		if (!strcmp(ControllerName((CONTROLLER)i), ELE_CON))
		{
			if (GetdJoykeyTrigger(ELEKEY_A, (CONTROLLER)i) || GetdJoykeyTrigger(ELEKEY_START, (CONTROLLER)i))
			{
				Pause();
			}
		}
		else if (!strcmp(ControllerName((CONTROLLER)i), PS_CON))
		{
			if (GetdJoykeyTrigger(PSKEY_CI, (CONTROLLER)i) || GetdJoykeyTrigger(PSKEY_START, (CONTROLLER)i))
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					Pause();
				}
			}
		}
		else if (!strcmp(ControllerName((CONTROLLER)i), NIN_CON))
		{
			if (GetdJoykeyTrigger(NINKEY_A, (CONTROLLER)i) || GetdJoykeyTrigger(NINKEY_�{, (CONTROLLER)i))
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					Pause();
				}
			}
		}
		else if (!IsXInputControllerConnected((CONTROLLER)i) && IsDirectInputControllerConnected((CONTROLLER)i))
		{
			if (GetdJoykeyTrigger(DKEY_A, (CONTROLLER)i) || GetdJoykeyTrigger(DKEY_START, (CONTROLLER)i))
			{
				Pause();
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
			break;
		case GAMESTATE_END:
			g_nCounterGameState++;
			if (g_nCounterGameState >= INTER)
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					//�T�E���h
					StopSound(SOUND_LABEL_BGM4);
					//�ؑ�
					SetFade(MODE_RESULT);
				}
			}
			break;
		}

		UpdateModel();
		UpdateShadow();
		UpdateStage();
		UpdateGround();
		UpdatePlayer();//�v���C���[
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
		UpdateScore();
		AddScore((int)(10000.0f * ((float)(rand() % 101) / 100.0f)));
	}
}

//-------------------
//�`�揈��
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
	DrawPlayer();//�v���C���[
	DrawAlphaWall();
	DrawAlphaMeshWall();
	DrawTime();
	DrawScore();
}

//----------------------
//�Q�[����Ԑؑ�
//----------------------
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//-----------------------
//�Q�[����Ԏ擾
//-----------------------
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//---------------------
//�N���A�擾
//---------------------
bool GetClear(void)
{
	return g_bClear;
}