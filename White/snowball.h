//---------------------------------------
//
//ポリゴン表示処理の定義・宣言[snowball.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _SNOWBALL_H_
#define _SNOWBALL_H_

#include"main.h"

#define SNOWBALL_TEX "data\\TEXTURE\\yuki000.png"//テクスチャ
#define SNOWBALL_TEX2 "data\\TEXTURE\\yuki001.png"//テクスチャ
#define SNOWBALL_MAX (64)//球の数
#define SNOWBALL_RADIUS (50.0f)//半径
#define SNOWBALL_WIDTH_DEF (8.0f)//テクスチャサイズ
#define SNOWBALL_HEIGHT_DEF (8.0f)//テクスチャサイズ
#define SNOWBALL_HNUM (64)//H分割数
#define SNOWBALL_VNUM (64)//V分割数
#define SNOWBALL_ANG (180.0f)//半球全球切替
#define SNOWBALL_NUM (10)

////半球
//#define VT_MAX_SP ((SPHERE_HNUM + 1) * SPHERE_VNUM+1)//横の頂点数*縦のライン数(極を抜かす)+極 (半球)
//#define INDEX_SP_NUM (((SPHERE_HNUM+1)*2)*SPHERE_VNUM+(SPHERE_VNUM-2)*2-SPHERE_HNUM)//横の頂点数*2列**縦のライン数(極を抜かす)+縮退ポリゴン-極の不要分
//#define POLYGON_SP_NUM (SPHERE_HNUM*SPHERE_VNUM*2+(SPHERE_VNUM-2)*4-SPHERE_HNUM)//全体の分割*2*縮退ポリゴン-極の不要分
//全球
#define VT_MAX_SB ((SNOWBALL_HNUM + 1) * (SNOWBALL_VNUM-1)+2)//横の頂点数*縦のライン数(2極を抜かす)+2極 (全球)
#define INDEX_SB_NUM (((SNOWBALL_HNUM+1)*2)*(SNOWBALL_VNUM-2)+(SNOWBALL_VNUM-3)*2+(SNOWBALL_HNUM+2)*2)//横の頂点数*2列**縦のライン数(2極を抜かす)+縮退ポリゴン+2極
#define POLYGON_SB_NUM (SNOWBALL_HNUM*(SNOWBALL_VNUM-2)*2+(SNOWBALL_VNUM-3)*4+SNOWBALL_HNUM*2)//横の分割*2*縮退ポリゴン+2極

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scale;
	D3DXMATRIX mtxWorld;
	bool bUse;
}SnowBall;

void InitSnowBall(void);//初期化処理
void UninitSnowBall(void);//終了処理
void UpdateSnowBall(void);//更新処理
void DrawSnowBall(void);//描画処理
void SetSnowBall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale);//設定処理
SnowBall* GetSnowBall(void);
void CollisionSnowBall(D3DXVECTOR3 pos, float Length);

#endif _SNOWBALL_H_