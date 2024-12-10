//------------------------------------------
//
//シューティングゲームプログラムのメインの処理の定義・宣言[main.h]
//Author fuma sato
//
//------------------------------------------

#ifndef _MAIN_H_
#define _MAIN_H_

#define DIRECTINPUT_VERSION 0x0800
#include<windows.h>
#include<stdio.h>
#include<time.h>
#include <strsafe.h>
#include"d3dx9.h"
#include"dinput.h" // 入力に必要なファイル
#include"Xinput.h" // Xinput(パッド処理)
#include"xaudio2.h"

// ライブラリのリンク
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")
#pragma comment(lib,"uuid.lib")

// マクロ定義
#define FPS (1000/60) // 更新スピード
#define UP_TIME (1) // テクスチャスピード

// 名前
#define CLASS_NAME "WindowClass" // クラス名
#define WINDOW_NAME "White" // ウインドウ名
#define DATA_FILE "data\\DATA\\data.bin"//スコア保存用ファイル
#define STAGE_FILE "data\\DATA\\stage.txt"
#define MODEL_FILE "data\\DATA\\model.txt"
#define WALL_FILE "data\\DATA\\wall.txt"
#define LINE_FILE "data\\DATA\\line.txt"
#define BILL_FILE "data\\DATA\\bill.txt"

// 大きさ
#define SCREEN_WIDTH (1280) // 幅
#define SCREEN_HEIGHT (720) // 高さ

// 頂点
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1) // 頂点フォーマット
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1) // 頂点フォーマット
#define VT_MAX (4)//頂点数
#define UV_DEF (1.0f) // テクスチャのデフォルトのサイズ

// コントローラー
#define	ELE_CON "GP30X-Dinput"//学校支給コントローラ
#define PS_CON "Wireless Controller"//プレステ4
#define NIN_CON "Pro Controller"//プロコン

//デバッグ用
#define FPS_TIME (500)
#define FONT_SIZE (20)

// 頂点情報の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos; // 座標
	float rhw;       // 座標変換係数(1.0f)
	D3DCOLOR col;    // カラー
	D3DXVECTOR2 tex; // テクスチャ座標
} VERTEX_2D;

// 頂点情報の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos; // 座標
	D3DXVECTOR3 nor; //法線ベクトル
	D3DCOLOR col;    // カラー
	D3DXVECTOR2 tex; // テクスチャ座標
} VERTEX_3D;

// 画面の種類
typedef enum
{
	MODE_TITLE = 0,//タイトル
	MODE_DEMO,//デモ
	MODE_TUTO,//チュートリアル
	MODE_PLAYSELECT,//プレイセレクト
	MODE_GAME,//ゲーム
	MODE_VS,//バーサス
	MODE_RESULT,//リザルト
	MODE_RANK,//ランキング
	MODE_OPTION,//オプション
	MODE_MAX//モード数
} MODE;

// プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam); // ウインドウプロシージャ
HRESULT Init(HINSTANCE hInstanse, HWND hWnd, BOOL bWindow = TRUE); // 初期化処理
void Uninit(void); // 終了処理
void Update(void); // 更新処理
void Draw(void); // 描画処理
LPDIRECT3DDEVICE9 GetDevice(void); // デバイスの取得
void SetMode(MODE mode);//モード設定
MODE GetMode(void);//モード取得
HWND GethWnd(void);//ハンドル取得
HINSTANCE GethInstanse(void);//インスタンス取得

void ConfineCursorToWindow(HWND hwnd);//カーソル制御
void ReleaseCursor(void);//カーソル制御解除

//デバッグ用
void DrawDebug(void);

#endif // _MAIN_H_