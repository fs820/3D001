//---------------------------------------
//
//ポリゴン表示処理の定義・宣言[sphere.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _SPHERE_H_
#define _SPHERE_H_

#include"main.h"

#define SPHERE_TEX "data\\TEXTURE\\sky000.jpg"//テクスチャ
#define SPHERE_TEX2 "data\\TEXTURE\\sky001.jpg"//テクスチャ
#define SPHERE_TEX3 "data\\TEXTURE\\sky002.jpg"//テクスチャ
#define SPHERE_MAX (64)//球の数
#define SPHERE_RADIUS (5000.0f)//半径
#define SPHERE_WIDTH_DEF (42000.0f)//テクスチャサイズ
#define SPHERE_HEIGHT_DEF (15200.0f)//テクスチャサイズ
#define SPHERE_HNUM (64)//H分割数
#define SPHERE_VNUM (32)//V分割数
#define SPHERE_ANG (90.0f)//半球全球切替

//半球
#define VT_MAX_SP ((SPHERE_HNUM + 1) * SPHERE_VNUM+1)//横の頂点数*縦のライン数(極を抜かす)+極 (半球)
#define INDEX_SP_NUM (((SPHERE_HNUM+1)*2)*SPHERE_VNUM+(SPHERE_VNUM-2)*2-SPHERE_HNUM)//横の頂点数*2列**縦のライン数(極を抜かす)+縮退ポリゴン-極の不要分
#define POLYGON_SP_NUM (SPHERE_HNUM*SPHERE_VNUM*2+(SPHERE_VNUM-2)*4-SPHERE_HNUM)//全体の分割*2*縮退ポリゴン-極の不要分

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	bool bUse;
}Sphere;

void InitSphere(void);//初期化処理
void UninitSphere(void);//終了処理
void UpdateSphere(void);//更新処理
void DrawSphere(void);//描画処理
void SetSphere(D3DXVECTOR3 pos, D3DXVECTOR3 rot);//設定処理

#endif _SPHERE_H_