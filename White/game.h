//------------------------------------------
//
//ゲームメインの処理の定義・宣言[game.h]
//Author fuma sato
//
//------------------------------------------

#ifndef _GAME_H_
#define _GAME_H_

#include"main.h"

#define INTER (60)//終了猶予
#define GAME_WALL (3000.0f)//大人の壁
#define GRAVITY (-1.2f)//重力
#define TEXTURE_NUMBER "data\\TEXTURE\\number000.png"
#define TIME_LIMIT (60)
#define FRAME (60)

//ゲーム状態の列挙型定義
typedef enum
{
	GAMESTATE_NONE=0,//ゲームでない
	GAMESTATE_NORMAL,//ゲーム中
	GAMESTATE_PAUSE,//ポーズ中
	GAMESTATE_END,//終了
	GAMESTATE_MAX//数
}GAMESTATE;

//オブジェクトタイプの列挙型定義
typedef enum
{
	TYPE_NORMAL = 0,
	TYPE_WHITE,
	TYPE_BLACK,
	TYPE_MAX
}WHITE_TYPE;

void InitGame(void);//ゲームの初期化処理
void UninitGame(void);//ゲームの終了処理
void UpdateGame(void);//ゲームの更新処理
void DrawGame(void);//ゲームの描画処理
void SetGameState(GAMESTATE state);//ゲームの状態設定
GAMESTATE GetGameState(void);//ゲーム状態取得
bool GetClear(void);

#endif _GAME_H_
