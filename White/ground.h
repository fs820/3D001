//---------------------------------------
//
//ポリゴン表示処理の定義・宣言[ground.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _GROUND_H_
#define _GROUND_H_

#include"main.h"
#include"game.h"

#define GROUND_TEX "data\\TEXTURE\\field000.jpg"
#define GROUND_MAX (64)
#define GROUND_WIDTH (1000.0f)
#define GROUND_HEIGHT (0.0f)
#define GROUND_Z (1000.0f)
#define GROUND_WIDTH_DEF (45.4f)
#define GROUND_HEIGHT_DEF (0.0f)
#define GROUND_Z_DEF (34.0f)
#define GROUND_ALPHA (0.3f)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	bool bAlpha;
	bool bUse;
}Ground;

void InitGround(void);//ポリゴンの初期化処理
void UninitGround(void);//ポリゴンの終了処理
void UpdateGround(void);//ポリゴンの更新処理
void DrawGround(void);//ポリゴンの描画処理
void SetGround(D3DXVECTOR3 pos,D3DXVECTOR3 rot);

#endif _GROUND_H_