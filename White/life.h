//---------------------------------------
//
//体力ゲージの定義・宣言[life.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _LIFE_H_
#define _LIFE_H_

#include"main.h"

#define LIFE_MAX (64)
#define LIFE_WIDTH (160.0f)//サイズ
#define LIFE_HEIGHT (10.0f)//サイズ
#define LIFE_SPACE (50.0f)//隙間

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 scale;
	D3DXMATRIX mtxWorld;
	bool bUse;
}Life;

//プロトタイプ宣言
void InitLife(void);//スコアの初期化処理
void UninitLife(void);//スコアの終了処理
void UpdateLife(void);//スコアの更新処理
void DrawLife(void);//スコアの描画処理
int LinkLife(void);
void NullLife(int Indx);
void SetLife(D3DXVECTOR3 pos, float Life, int Indx);//設定

#endif _LIFE_H_
