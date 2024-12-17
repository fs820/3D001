//---------------------------------------
//
//ポリゴン表示処理の定義・宣言[meshwall.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _MESHWALL_H_
#define _MESHWALL_H_

#include"main.h"
#include"game.h"

#define MESHWALL_TEX "data\\TEXTURE\\wall000.jpg"
#define MESHWALL_MAX (256)
#define MESHWALL_WIDTH (1000.0f)
#define MESHWALL_HEIGHT (1000.0f)
#define MESHWALL_Z (0.0f)
#define MESHWALL_WIDTH_DEF (100.0f)
#define MESHWALL_HEIGHT_DEF (100.0f)
#define MESHWALL_Z_DEF (0.0f)
#define MESHWALL_XNUM (16)
#define MESHWALL_YNUM (16)
#define VT_MAX_MESH_WALL ((MESHWALL_XNUM + 1) * (MESHWALL_YNUM + 1))
#define INDEX_NUM_WALL (((MESHWALL_XNUM+1)*2)*MESHWALL_YNUM+(MESHWALL_YNUM-1)*2)
#define POLYGON_NUM_WALL (MESHWALL_XNUM*MESHWALL_YNUM*2+(MESHWALL_YNUM-1)*4)
#define WALL_ALPHA_MESH (0.3f)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scale;
	D3DXMATRIX mtxWorld;
	bool bAlpha;
	bool bUse;
}MeshWall;

void InitMeshWall(void);//ポリゴンの初期化処理
void UninitMeshWall(void);//ポリゴンの終了処理
void UpdateMeshWall(void);//ポリゴンの更新処理
void DrawMeshWall(void);//ポリゴンの描画処理
void DrawAlphaMeshWall(void);//ポリゴンの描画処理
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale);
MeshWall* GetMeshWall(void);
void CollisionMeshWall(void);

#endif _MESHWALL_H_