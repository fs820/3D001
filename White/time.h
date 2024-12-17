//---------------------------------------
//
//スコア処理の定義・宣言[time.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _TIME_H_
#define _TIME_H_

#include"main.h"

#define TIME_TEX "data\\TEXTURE\\Time.png"
#define TIME_TEX2 "data\\TEXTURE\\TimeMaster.png"
#define TIME_MAX (2)//テクスチャ数
#define TIME_WIDTH (160.0f)//サイズ
#define TIME_HEIGHT (120.0f)//サイズ
#define TIME_WIDTH2 (75.0f)//サイズ
#define TIME_HEIGHT2 (75.0f)//サイズ

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	float fLength;
	float fAngle;
}Time;

//プロトタイプ宣言
void InitTime(void);//スコアの初期化処理
void UninitTime(void);//スコアの終了処理
void UpdateTime(void);//スコアの更新処理
void DrawTime(void);//スコアの描画処理
void SetTime(float Time);

#endif _Time_H_
