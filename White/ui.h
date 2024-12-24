//---------------------------------------
//
//スコア処理の定義・宣言[ui.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _UI_H_
#define _UI_H_

#include"main.h"

#define UI_TEX "data\\TEXTURE\\いきのびろ.png"
#define UI_TEX2 "data\\TEXTURE\\白線に乗れ.png"
#define UI_TEX3 "data\\TEXTURE\\雪だ.png"
#define UI_MAX (3)//テクスチャ数
#define UI_WIDTH (640.0f)//サイズ
#define UI_HEIGHT (128.0f)//サイズ
#define UI_LIFE (120)

typedef struct
{
	D3DXVECTOR3 pos;
	int nLife;
	bool bUse;
}Ui;

//プロトタイプ宣言
void InitUi(void);//スコアの初期化処理
void UninitUi(void);//スコアの終了処理
void UpdateUi(void);//スコアの更新処理
void DrawUi(void);//スコアの描画処理
void SetUi(int Number);

#endif _UI_H_