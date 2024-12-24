//---------------------------------------
//
//モデル表示処理の定義・宣言[Dog.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _DOG_H_
#define _DOG_H_

#include"main.h"
#include"player.h"
#include"stage.h"
#include"model.h"

#define MAX_DOG (128)
#define DOG_BODY_NAME "data\\MODEL\\Dogmodel\\00_Dog_Body.x"
#define DOG_HEAD_NAME "data\\MODEL\\Dogmodel\\01_Dog_Head.x"
#define DOG_RIGHTFRONTFOOT_NAME "data\\MODEL\\Dogmodel\\02_Dog_RightFrontFoot.x"
#define DOG_LEFTFRONTFOOT_NAME "data\\MODEL\\Dogmodel\\03_Dog_LeftFrontFoot.x"
#define DOG_RIGHTBACKFOOT_NAME "data\\MODEL\\Dogmodel\\04_Dog_RightBackFoot.x"
#define DOG_LEFTBACKFOOT_NAME "data\\MODEL\\Dogmodel\\05_Dog_LeftBackFoot.x"
#define MAX_MODEL_DOG (16)
#define NUM_MODEL_DOG (6)
#define MAX_KEY_DOG (16)
#define NUM_KEY_DOG (8)
#define MAX_MOTION_DOG (16)
#define NUM_MOTION_DOG (5)
#define SPEED_DOG (2.0f)
#define SPEED_DOG_DEF (0.0f)
#define JUMP_DOG (20.0f)
#define JUMP_INA_DOG (0.9f)
#define DOG_INA (0.1f)
#define ROT_SPEED_DOG (0.1f)
#define SCALE_SPEED_DOG (0.2f)
#define SCALE_MIN_DOG (0.5f)
#define SCALE_MAX_DOG (10.0f)
#define START_Z_DOG (-1500.0f)
#define DOG_LIFE (300)
#define BLEND_FRAME_DOG (10.0f)
#define TRACK_INA_DOG (0.6f)
#define DOG_SIZE (50.0f)
#define DOG_ATTACK_SPACE (100.0f)

//プレイヤー状態の列挙型定義
typedef enum
{
	DOGSTATE_APPEAR = 0,//復活状態
	DOGSTATE_NORMAL,//通常
	DOGSTATE_DAMAGE,//ダメージ
	DOGSTATE_DIE,//死
	DOGSTATE_MAX//数
}DOGSTATE;

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
	DOGSTATE state;
	D3DXMATRIX mtxWorld;
	int nIdxShadow;
	int nIdxLife;
	Model aModel[MAX_MODEL_DOG];
	int nNumModel;
	MOTION_INFO aMotionInfo[MAX_MOTION_DOG];
	int nNumMotion;
	MOTIONTYPE motionType;
	bool bLoopMotion;
	int nNumKey;
	int nKey;
	int nCounterMotion;
	Stage* pStage;
	bool bUse;
}Dog;

void InitDog(void);//ポリゴンの初期化処理
void UninitDog(void);//ポリゴンの終了処理
void UpdateDog(void);//ポリゴンの更新処理
void DrawDog(void);//ポリゴンの描画処理
Dog* GetDog(void);
void SetDog(D3DXVECTOR3 pos);

void UpdateDogMotion(int nNumber);

#endif _DOG_H_