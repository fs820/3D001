//---------------------------------------
//
//ライトの定義・宣言[light.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _LIGHT_H_
#define _LIGHT_H_

#include"main.h"

#define LIGHT_MAX (16)

void InitLight(void);//初期化処理
void UninitLight(void);//終了処理
void UpdateLight(void);//更新処理
float GetLightAngle(void);

#endif _LIGHT_H_