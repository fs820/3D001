//---------------------------------------
//
//パーティクル表示処理の定義・宣言[snow.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _SNOW_H_
#define _SNOW_H_

#include"main.h"

#define SNOW_NUM (5)//フレーム発生数
#define SNOW_SPASE (3000)

void InitSnow(void);//パーティクルの初期化処理
void UninitSnow(void);//パーティクルの終了処理
void UpdateSnow(void);//パーティクルの更新処理
void SetSnow(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//パーティクル設定

#endif _SNOW_H_