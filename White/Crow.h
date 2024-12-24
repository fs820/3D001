//---------------------------------------
//
//モデル表示処理の定義・宣言[Crow.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _CROW_H_
#define _CROW_H_

#include"main.h"
#include"player.h"
#include"stage.h"
#include"model.h"

#define MAX_CROW (128)
#define CROW_BODY_NAME "data\\MODEL\\Crowmodel\\00_Crow_Body000.x"
#define CROW_HEAD_NAME "data\\MODEL\\Crowmodel\\01_Crow_Head000.x"
#define CROW_BILL_NAME "data\\MODEL\\Crowmodel\\02_Crow_Bill000.x"
#define CROW_RIGHTWING_NAME "data\\MODEL\\Crowmodel\\03_Crow_RightWing000.x"
#define CROW_LEFTWING_NAME "data\\MODEL\\Crowmodel\\04_Crow_LeftWing000.x"
#define CROW_RIGHTFOOT_NAME "data\\MODEL\\Crowmodel\\05_Crow_RightFoot000.x"
#define CROW_LEFTFOOT_NAME "data\\MODEL\\Crowmodel\\06_Crow_LeftFoot000.x"
#define MAX_MODEL_CROW (16)
#define NUM_MODEL_CROW (7)
#define MAX_KEY_CROW (16)
#define NUM_KEY_CROW (8)
#define MAX_MOTION_CROW (16)
#define NUM_MOTION_CROW (5)
#define SPEED_CROW (5.0f)
#define SPEED_CROW_DEF (0.0f)
#define JUMP_CROW (20.0f)
#define JUMP_INA_CROW (0.9f)
#define CROW_INA (0.1f)
#define ROT_SPEED_CROW (0.1f)
#define SCALE_SPEED_CROW (0.2f)
#define SCALE_MIN_CROW (0.5f)
#define SCALE_MAX_CROW (10.0f)
#define START_Z_CROW (-1500.0f)
#define CROW_LIFE (500)
#define BLEND_FRAME_CROW (10.0f)
#define TRACK_INA_CROW (1.0f)
#define CROW_SIZE (50.0f)
#define CROW_ATTACK_SPACE (50.0f)

//プレイヤー状態の列挙型定義
typedef enum
{
	CROWSTATE_APPEAR = 0,//復活状態
	CROWSTATE_NORMAL,//通常
	CROWSTATE_DAMAGE,//ダメージ
	CROWSTATE_DIE,//死
	CROWSTATE_MAX//数
}CROWSTATE;

//プレイヤー構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 Destrot;
	D3DXVECTOR3 scale;
	bool bJump;
	int nLife;
	CROWSTATE state;
	D3DXMATRIX mtxWorld;
	int nIdxShadow;
	int nIdxLife;
	Model aModel[MAX_MODEL_CROW];
	int nNumModel;
	MOTION_INFO aMotionInfo[MAX_MOTION_CROW];
	int nNumMotion;
	MOTIONTYPE motionType;
	bool bLoopMotion;
	int nNumKey;
	int nKey;
	int nCounterMotion;
	Stage* pStage;
	bool bUse;
}Crow;

void InitCrow(void);//ポリゴンの初期化処理
void UninitCrow(void);//ポリゴンの終了処理
void UpdateCrow(void);//ポリゴンの更新処理
void DrawCrow(void);//ポリゴンの描画処理
Crow* GetCrow(void);
void SetCrow(D3DXVECTOR3 pos);

void UpdateCrowMotion(int nNumber);

#endif _CORW_H_