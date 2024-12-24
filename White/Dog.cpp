//----------------------------------------
//
//モデル表示処理[Dog.cpp]
//Author fuma sato
//
//----------------------------------------

#include"Dog.h"
#include"game.h"
#include"shadow.h"
#include"camera.h"
#include"input.h"
#include"bullet.h"
#include"file.h"
#include"particle.h"
#include"life.h"
#include"hitshere.h"

//グローバル変数宣言
Dog g_aDog[MAX_DOG];

static MOTION_INFO g_Motion[] =
{
	true,
	2,
	{
	   {
		  80,
		  {
			 {
				 0.0f,-0.2f,0.0f,-1.63f,0.0f,0.0f
			 },
			 {
				 0.0f,0.0f,0.0f,-0.38f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,-1.1f,0.0f
			 },
			  {
			   0.0f,0.0f,0.0f,0.0f,1.1f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,1.45f,0.22f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,1.45f,-0.22f,0.0f
			 }
		  }
	   },
	   {
		  80,
		  {
			 {
			   0.0f,0.0f,0.0f,-1.57f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.06f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,-1.32f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,1.32f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,1.45f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,1.45f,0.0f,0.0f
			 }
		  }
	   }
	},
	true,
	4,
	{
	   {
		  5,
		  {
			 {
				 0.0f,18.3f,0.0f,-1.57f,0.0f,0.0f
			 },
			 {
				 0.0f,0.0f,0.0f,0.06f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,-1.23f,-0.75f
			 },
			 {
			   0.0f,0.0f,0.0f,1.23f,0.0f,-0.31f
			 },
			 {
			   0.0f,0.0f,0.0f,1.29f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.28f,0.0f,0.0f
			 }
		  }
	   },
	   {
		  15,
		  {
			 {
			   0.0f,1.8f,0.0f,-1.73f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.06f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,-1.23f,-0.75f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,1.23f,-0.31f
			 },
			 {
			   0.0f,0.0f,0.0f,1.29f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.28f,0.0f,0.0f
			 }
		  }
	   },
	   {
		  5,
		  {
			 {
				 0.0f,18.3f,0.0f,-1.57f,0.0f,0.0f
			 },
			 {
				 0.0f,0.0f,0.0f,0.06f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,-1.23f,0.31f
			 },
			  {
			   0.0f,0.0f,0.0f,0.0f,1.23f,1.38f
			 },
			 {
			   0.0f,0.0f,0.0f,0.28f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,1.51f,0.0f,0.0f
			 }
		  }
	   },
	   {
		  15,
		  {
			 {
			   0.0f,7.0f,0.0f,-1.79f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,0.0f,-1.23f,0.31f
			 },
			 {
			   0.0f,0.0f,0.0f,-0.41f,1.23f,1.38f
			 },
			 {
			   0.0f,0.0f,0.0f,0.25f,0.0f,0.0f
			 },
			 {
			   0.0f,0.0f,0.0f,1.51f,0.0f,0.0f
			 }
		  }
	   }
	},
	false,
	8,
	{
	   {
		   10,
		   {
				{
					0.0f,-0.2f,-16.9f,-1.19f,0.0f,0.0f
				},
				{
					0.0f,0.0f,0.0f,0.25f,0.0f,0.63f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-1.1f,-1.13f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,1.1f,1.13f
				},
				{
				  0.0f,0.0f,0.0f,0.44f,0.22f,-1.41f
				},
				{
				  0.0f,0.0f,0.0f,0.63f,-0.22f,0.0f
				}
	       }
	   },
	   {
		   5,
		   {
				{
					0.0f,-0.2f,-16.9f,-1.13f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.44f,0.0f,0.69f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-1.1f,-1.13f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,1.1f,1.13f
				},
				{
				  0.0f,0.0f,0.0f,0.35f,0.22f,-1.41f
				},
				{
				  0.0f,0.0f,0.0f,0.51f,-0.22f,2.14f
                }
		   }
	   },
	   {
		   20,
		   {
				{
					0.0f,-0.2f,-16.9f,-1.44f,0.0f,0.0f
				},
				{
					0.0f,0.0f,0.0f,-0.66f,0.0f,-0.69f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-1.1f,-0.66f
				},
				 {
				  0.0f,0.0f,0.0f,0.0f,1.1f,-0.69f
				},
				{
				  0.0f,0.0f,0.0f,0.88f,0.22f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.88f,-0.22f,0.0f
				}
		   }
	   },
	   {
		   5,
		   {
				{
					0.0f,-0.2f,-16.9f,-1.5f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.98f,0.0f,-0.91f
				},
				{
				  0.0f,0.0f,0.0f,-0.09f,-1.1f,-0.66f
				},
				{
				  0.0f,0.0f,0.0f,-0.09f,1.1f,0.69f
				},
				{
				  0.0f,0.0f,0.0f,1.04f,0.22f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.98f,-0.22f,0.0f
				}
		   }
	   },
	   {
		   10,
		   {
				{
					0.0f,-0.2f,-16.9f,-1.19f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.0f,-0.6f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-1.1f,-1.13f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,1.1f,1.13f
				},
				{
				  0.0f,0.0f,0.0f,0.44f,0.22f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-0.22f,0.0f
				}
		   }
	   },
			   {
		   5,
		   {
				{
					0.0f,-0.2f,-16.9f,-1.13f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.13f,0.0f,-0.6f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-1.1f,-1.41f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,1.1f,1.41f
				},
				{
				  0.0f,0.0f,0.0f,0.35f,0.22f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.48f,-0.22f,0.0f
				}
		   }
		},
			   {
		   20,
		   {
				{
					0.0f,-0.2f,-16.9f,-1.44f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.66f,1.01f,0.82f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-1.1f,-0.66f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,1.1f,0.69f
				},
				{
				  0.0f,0.0f,0.0f,0.88f,0.22f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.88f,-0.22f,0.0f
				}
		   }
		},
	   {
		   10,
		   {
				{
					0.0f,-0.2f,-16.9f,-1.5f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.95f,1.01f,1.01f
				},
				{
				  0.0f,0.0f,0.0f,-0.09f,-1.1f,-0.66f
				},
				{
				  0.0f,0.0f,0.0f,-0.16f,1.1f,0.69f
				},
				{
				  0.0f,0.0f,0.0f,1.04f,0.22f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,1.04f,-0.22f,0.0f
				}
		   }
	   }
	},
	false,
	4,
	   {
		  {
			 5,
			 {
				{
					0.0f,0.0f,0.0f,-1.63f,0.0f,0.0f
				},
				{
					0.0f,0.0f,0.0f,-0.25f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-0.88f,0.19f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.88f,-0.19f
				},
				{
				  0.0f,0.0f,0.0f,1.92f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,1.92f,0.0f,0.0f
				}
			 }
		  },
		  {
			 15,
			 {
				{
				  0.0f,0.0f,0.0f,-0.97f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.03f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-1.82f,-1.45f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,0.88f,1.45f
				},
				{
				  0.0f,0.0f,0.0f,0.6f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.6f,0.0f,0.0f
				}
			 }
		  },
		  {
			 10,
			 {
				{
					0.0f,0.0f,0.0f,-1.7f,0.0f,0.0f
				},
				{
					0.0f,0.0f,0.0f,0.57f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.6f,-1.82f,-1.45f
				},
				 {
				  0.0f,0.0f,0.0f,0.6f,1.88f,1.45f
				},
				{
				  0.0f,0.0f,0.0f,-0.22f,0.0f,-0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.22f,0.0f,0.0f
				}
			 }
		  },
		  {
			 5,
			 {
				{
				  0.0f,0.0f,0.0f,-2.01f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,-0.16f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.0f,-1.82f,-1.13f
				},
				{
				  0.0f,0.0f,0.0f,-0.09f,1.88f,1.13f
				},
				{
				  0.0f,0.0f,0.0f,0.47f,0.0f,0.0f
				},
				{
				  0.0f,0.0f,0.0f,0.47f,0.0f,0.0f
				}
			 }
		  }
	   },
	   false,
		  2,
		  {
			 {
				3,
				{
				   {
					   0.0f,16.1f,0.0f,-2.1f,0.0f,0.0f
				   },
				   {
					   0.0f,0.0f,0.0f,-0.16f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,0.0f,-1.82f,-1.13f
				   },
					{
					 0.0f,0.0f,0.0f,-0.09f,1.88f,1.13f
				   },
				   {
					 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
				   }
				}
			 },
			 {
				10,
				{
				   {
					 0.0f,8.7f,0.0f,-1.85f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,0.28f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,0.35f,-1.88f,-0.19f
				   },
				   {
					 0.0f,0.0f,0.0f,0.35f,1.88f,0.19f
				   },
				   {
					 0.0f,0.0f,0.0f,1.29f,0.0f,0.0f
				   },
				   {
					 0.0f,0.0f,0.0f,1.29f,0.0f,0.0f
				   }
				}
			 }
		  }
};

//----------------------
//ポリゴンの初期化処理
//----------------------
void InitDog(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_DOG; nCnt++)
	{
		g_aDog[nCnt].pos = D3DXVECTOR3(0.0f, 0.1f, START_Z_DOG);
		g_aDog[nCnt].posOld = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
		g_aDog[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aDog[nCnt].rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
		g_aDog[nCnt].Destrot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
		g_aDog[nCnt].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aDog[nCnt].bJump = false;
		g_aDog[nCnt].nLife = DOG_LIFE;
		g_aDog[nCnt].state = DOGSTATE_NORMAL;
		g_aDog[nCnt].nIdxShadow = -1;
		g_aDog[nCnt].nIdxLife = -1;
		g_aDog[nCnt].pStage = NULL;

		g_aDog[nCnt].bLoopMotion = false;
		g_aDog[nCnt].motionType = MOTIONTYPE_NEUTRAL;
		g_aDog[nCnt].nCounterMotion = 0;
		g_aDog[nCnt].nKey = -1;
		g_aDog[nCnt].nNumKey = 0;
		g_aDog[nCnt].nNumMotion = NUM_MOTION_DOG;
		g_aDog[nCnt].bUse = false;


		LoadModel();

		//Xファイル読み込み
		D3DXLoadMeshFromX
		(
			DOG_BODY_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aDog[nCnt].aModel[0].pBuffMat,
			NULL,
			&g_aDog[nCnt].aModel[0].dwNumMat,
			&g_aDog[nCnt].aModel[0].pMesh
		);

		//Xファイル読み込み
		D3DXLoadMeshFromX
		(
			DOG_HEAD_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aDog[nCnt].aModel[1].pBuffMat,
			NULL,
			&g_aDog[nCnt].aModel[1].dwNumMat,
			&g_aDog[nCnt].aModel[1].pMesh
		);

		//Xファイル読み込み
		D3DXLoadMeshFromX
		(
			DOG_RIGHTFRONTFOOT_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aDog[nCnt].aModel[2].pBuffMat,
			NULL,
			&g_aDog[nCnt].aModel[2].dwNumMat,
			&g_aDog[nCnt].aModel[2].pMesh
		);

		//Xファイル読み込み
		D3DXLoadMeshFromX
		(
			DOG_LEFTFRONTFOOT_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aDog[nCnt].aModel[3].pBuffMat,
			NULL,
			&g_aDog[nCnt].aModel[3].dwNumMat,
			&g_aDog[nCnt].aModel[3].pMesh
		);

		//Xファイル読み込み
		D3DXLoadMeshFromX
		(
			DOG_RIGHTBACKFOOT_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aDog[nCnt].aModel[4].pBuffMat,
			NULL,
			&g_aDog[nCnt].aModel[4].dwNumMat,
			&g_aDog[nCnt].aModel[4].pMesh
		);

		//Xファイル読み込み
		D3DXLoadMeshFromX
		(
			DOG_LEFTBACKFOOT_NAME,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aDog[nCnt].aModel[5].pBuffMat,
			NULL,
			&g_aDog[nCnt].aModel[5].dwNumMat,
			&g_aDog[nCnt].aModel[5].pMesh
		);

		g_aDog[nCnt].nNumModel = NUM_MODEL_DOG;

		int nCntModel;
		for (nCntModel = 0; nCntModel < g_aDog[nCnt].nNumModel; nCntModel++)
		{

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_aDog[nCnt].aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aDog[nCnt].aModel[nCntModel].dwNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{//テクスチャがある
					//テクスチャの読み込み
					D3DXCreateTextureFromFile
					(
						pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_aDog[nCnt].aModel[nCntModel].apTexture[nCntMat]
					);
				}
			}

			//頂点数
			g_aDog[nCnt].aModel[nCntModel].nNumVtx = g_aDog[nCnt].aModel[nCntModel].pMesh->GetNumVertices();
			//頂点サイズ
			g_aDog[nCnt].aModel[nCntModel].sizeFVF = D3DXGetFVFVertexSize(g_aDog[nCnt].aModel[nCntModel].pMesh->GetFVF());
			//頂点バッファの取得
			g_aDog[nCnt].aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_aDog[nCnt].aModel[nCntModel].pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < g_aDog[nCnt].aModel[nCntModel].nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_aDog[nCnt].aModel[nCntModel].pVtxBuff;

				if (vtx.x > g_aDog[nCnt].aModel[nCntModel].vtxMax.x)
				{
					g_aDog[nCnt].aModel[nCntModel].vtxMax.x = vtx.x;
				}
				if (vtx.x < g_aDog[nCnt].aModel[nCntModel].vtxMin.x)
				{
					g_aDog[nCnt].aModel[nCntModel].vtxMin.x = vtx.x;
				}
				if (vtx.y > g_aDog[nCnt].aModel[nCntModel].vtxMax.y)
				{
					g_aDog[nCnt].aModel[nCntModel].vtxMax.y = vtx.y;
				}
				if (vtx.y < g_aDog[nCnt].aModel[nCntModel].vtxMin.y)
				{
					g_aDog[nCnt].aModel[nCntModel].vtxMin.y = vtx.y;
				}
				if (vtx.z > g_aDog[nCnt].aModel[nCntModel].vtxMax.z)
				{
					g_aDog[nCnt].aModel[nCntModel].vtxMax.z = vtx.z;
				}
				if (vtx.z < g_aDog[nCnt].aModel[nCntModel].vtxMin.z)
				{
					g_aDog[nCnt].aModel[nCntModel].vtxMin.z = vtx.z;
				}

				g_aDog[nCnt].aModel[nCntModel].pVtxBuff += g_aDog[nCnt].aModel[nCntModel].sizeFVF;
			}

			g_aDog[nCnt].aModel[nCntModel].vtxMinDef = g_aDog[nCnt].aModel[nCntModel].vtxMin;
			g_aDog[nCnt].aModel[nCntModel].vtxMaxDef = g_aDog[nCnt].aModel[nCntModel].vtxMax;
		}

		g_aDog[nCnt].aModel[0].nIdxModelParent = -1;
		g_aDog[nCnt].aModel[0].pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
		g_aDog[nCnt].aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aDog[nCnt].aModel[0].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aDog[nCnt].aModel[1].nIdxModelParent = 0;
		g_aDog[nCnt].aModel[1].pos = D3DXVECTOR3(0.0f, 40.0f, 10.0f);
		g_aDog[nCnt].aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aDog[nCnt].aModel[1].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aDog[nCnt].aModel[2].nIdxModelParent = 0;
		g_aDog[nCnt].aModel[2].pos = D3DXVECTOR3(-12.0f, 40.0f, 0.0f);
		g_aDog[nCnt].aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aDog[nCnt].aModel[2].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aDog[nCnt].aModel[3].nIdxModelParent = 0;
		g_aDog[nCnt].aModel[3].pos = D3DXVECTOR3(12.0f, 40.0f, 0.0f);
		g_aDog[nCnt].aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aDog[nCnt].aModel[3].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aDog[nCnt].aModel[4].nIdxModelParent = 0;
		g_aDog[nCnt].aModel[4].pos = D3DXVECTOR3(-7.5f, 0.0f, 0.0f);
		g_aDog[nCnt].aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aDog[nCnt].aModel[4].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aDog[nCnt].aModel[5].nIdxModelParent = 0;
		g_aDog[nCnt].aModel[5].pos = D3DXVECTOR3(7.5f, 0.0f, 0.0f);
		g_aDog[nCnt].aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aDog[nCnt].aModel[5].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{
			g_aDog[nCnt].aModel[nCntModel].posDef = g_aDog[nCnt].aModel[nCntModel].pos;
		}
	}
}

//-------------------
//ポリゴン終了処理
//-------------------
void UninitDog(void)
{
	for (int nCnt = 0; nCnt < MAX_DOG; nCnt++)
	{
		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{
			for (unsigned int i = 0; i < g_aDog[nCnt].aModel[nCntModel].dwNumMat; i++)
			{
				if (g_aDog[nCnt].aModel[nCntModel].apTexture[i] != NULL)
				{
					g_aDog[nCnt].aModel[nCntModel].apTexture[i]->Release();
					g_aDog[nCnt].aModel[nCntModel].apTexture[i] = NULL;
				}
			}
			//メッシュの破棄
			if (g_aDog[nCnt].aModel[nCntModel].pMesh != NULL)
			{
				g_aDog[nCnt].aModel[nCntModel].pMesh->Release();
				g_aDog[nCnt].aModel[nCntModel].pMesh = NULL;
			}
			//マテリアルの破棄
			if (g_aDog[nCnt].aModel[nCntModel].pBuffMat != NULL)
			{
				g_aDog[nCnt].aModel[nCntModel].pBuffMat->Release();
				g_aDog[nCnt].aModel[nCntModel].pBuffMat = NULL;
			}
		}
	}
}

//-------------------
//ポリゴン更新処理
//-------------------
void UpdateDog(void)
{
	for (int nCnt = 0; nCnt < MAX_DOG; nCnt++)
	{
		if (g_aDog[nCnt].bUse)
		{
			//移動処理
			Player* pPlayer = GetPlayer();

			float Oldrot = atan2f(g_aDog[nCnt].move.x, g_aDog[nCnt].move.z);//今の方向
			float Xlong = pPlayer->pos.x - g_aDog[nCnt].pos.x;
			float Zlong = pPlayer->pos.z - g_aDog[nCnt].pos.z;
			float Destrot = atan2f(Xlong, Zlong);//敵の方向

			float Diffrot = Destrot - Oldrot;//差の角度
			if (Diffrot > D3DX_PI)
			{//修正
				Diffrot -= D3DX_PI * 2;
			}
			else if (Diffrot < -D3DX_PI)
			{//修正
				Diffrot += D3DX_PI * 2;
			}

			Oldrot += Diffrot * TRACK_INA_DOG;//角度を補正

			if (Oldrot > D3DX_PI)
			{//修正
				Oldrot -= D3DX_PI * 2;
			}
			else if (Oldrot < -D3DX_PI)
			{//修正
				Oldrot += D3DX_PI * 2;
			}

			g_aDog[nCnt].move.x += sinf(Oldrot) * SPEED_DOG;
			g_aDog[nCnt].move.z += cosf(Oldrot) * SPEED_DOG;
			g_aDog[nCnt].Destrot.y = Oldrot - D3DX_PI;
			if (g_aDog[nCnt].motionType != MOTIONTYPE_JUMP && g_aDog[nCnt].motionType != MOTIONTYPE_LANDING && g_aDog[nCnt].motionType != MOTIONTYPE_ACTION)
			{
				g_aDog[nCnt].motionType = MOTIONTYPE_MOVE;
			}

			if (rand() % 100 == 0)//Sキー
			{//上
				if (!g_aDog[nCnt].bJump)
				{
					g_aDog[nCnt].move.y += JUMP;
					g_aDog[nCnt].bJump = true;
					g_aDog[nCnt].motionType = MOTIONTYPE_JUMP;
				}
			}

			if (sqrtf((pPlayer->pos.x - g_aDog[nCnt].pos.x) * (pPlayer->pos.x - g_aDog[nCnt].pos.x) + (pPlayer->pos.z - g_aDog[nCnt].pos.z) * (pPlayer->pos.z - g_aDog[nCnt].pos.z)) < DOG_ATTACK_SPACE)
			{
				g_aDog[nCnt].motionType = MOTIONTYPE_ACTION;
			}

			g_aDog[nCnt].move.y += GRAVITY;

			if (g_aDog[nCnt].bJump)
			{
				g_aDog[nCnt].move.x *= JUMP_INA_DOG;
				g_aDog[nCnt].move.z *= JUMP_INA_DOG;
			}

			g_aDog[nCnt].posOld = g_aDog[nCnt].pos;

			if (g_aDog[nCnt].motionType == MOTIONTYPE_ACTION)
			{
				g_aDog[nCnt].move.x = 0.0f;
				g_aDog[nCnt].move.z = 0.0f;
			}

			//位置の更新
			g_aDog[nCnt].pos.x += g_aDog[nCnt].move.x;
			g_aDog[nCnt].pos.y += g_aDog[nCnt].move.y;
			g_aDog[nCnt].pos.z += g_aDog[nCnt].move.z;

			//移動量の更新(減衰)
			g_aDog[nCnt].move.x += (SPEED_DOG_DEF - g_aDog[nCnt].move.x) * DOG_INA;
			g_aDog[nCnt].move.z += (SPEED_DOG_DEF - g_aDog[nCnt].move.z) * DOG_INA;

			CollisionPlayer(g_aDog[nCnt].pos, DOG_SIZE);

			for (int nCntDog = 0; nCntDog < MAX_DOG; nCntDog++)
			{
				if (g_aDog[nCntDog].bUse && nCntDog != nCnt)
				{
					float Space = sqrtf((g_aDog[nCntDog].pos.x - g_aDog[nCnt].pos.x) * (g_aDog[nCntDog].pos.x - g_aDog[nCnt].pos.x) + (g_aDog[nCntDog].pos.y - g_aDog[nCnt].pos.y) * (g_aDog[nCntDog].pos.y - g_aDog[nCnt].pos.y) + (g_aDog[nCntDog].pos.z - g_aDog[nCnt].pos.z) * (g_aDog[nCntDog].pos.z - g_aDog[nCnt].pos.z));
					if (Space < DOG_SIZE)
					{
						Space = DOG_SIZE - Space;
						D3DXVECTOR3 Hitvec = g_aDog[nCnt].pos - g_aDog[nCntDog].pos;
						D3DXVec3Normalize(&Hitvec, &Hitvec);
						g_aDog[nCnt].move += Hitvec * Space;
					}
				}
			}

			g_aDog[nCnt].pStage = NULL;

			g_aDog[nCnt].bJump = !CollisionStage(&g_aDog[nCnt].pStage);

			if (g_aDog[nCnt].pStage != NULL)
			{
				g_aDog[nCnt].pos += g_aDog[nCnt].pStage->move;
			}

			if (g_aDog[nCnt].pos.x < -GAME_WALL)
			{
				g_aDog[nCnt].pos.x = -GAME_WALL;
			}
			if (g_aDog[nCnt].pos.x > GAME_WALL)
			{
				g_aDog[nCnt].pos.x = GAME_WALL;
			}
			if (g_aDog[nCnt].pos.z < -GAME_WALL)
			{
				g_aDog[nCnt].pos.z = -GAME_WALL;
			}
			if (g_aDog[nCnt].pos.z > GAME_WALL)
			{
				g_aDog[nCnt].pos.z = GAME_WALL;
			}

			if (sqrtf(g_aDog[nCnt].move.x * g_aDog[nCnt].move.x + g_aDog[nCnt].move.z * g_aDog[nCnt].move.z) < 0.1f && g_aDog[nCnt].motionType == MOTIONTYPE_MOVE)
			{
				g_aDog[nCnt].move.x = 0.0f;
				g_aDog[nCnt].move.z = 0.0f;
				g_aDog[nCnt].motionType = MOTIONTYPE_NEUTRAL;
			}

			//正規化
			if (g_aDog[nCnt].Destrot.y > D3DX_PI)
			{
				g_aDog[nCnt].Destrot.y -= D3DX_PI * 2.0f;
			}
			else if (g_aDog[nCnt].Destrot.y < -D3DX_PI)
			{
				g_aDog[nCnt].Destrot.y += D3DX_PI * 2.0f;
			}

			//正規化
			if (g_aDog[nCnt].Destrot.y - g_aDog[nCnt].rot.y > D3DX_PI)
			{
				g_aDog[nCnt].Destrot.y = g_aDog[nCnt].rot.y + ((g_aDog[nCnt].Destrot.y - g_aDog[nCnt].rot.y) - D3DX_PI * 2.0f);
			}
			else if (g_aDog[nCnt].Destrot.y - g_aDog[nCnt].rot.y < -D3DX_PI)
			{
				g_aDog[nCnt].Destrot.y = g_aDog[nCnt].rot.y + ((g_aDog[nCnt].Destrot.y - g_aDog[nCnt].rot.y) + D3DX_PI * 2.0f);
			}

			g_aDog[nCnt].rot.y += (g_aDog[nCnt].Destrot.y - g_aDog[nCnt].rot.y) * ROT_SPEED_DOG;

			//正規化
			if (g_aDog[nCnt].rot.y > D3DX_PI)
			{
				g_aDog[nCnt].rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_aDog[nCnt].rot.y < -D3DX_PI)
			{
				g_aDog[nCnt].rot.y += D3DX_PI * 2.0f;
			}

			//正規化
			if (g_aDog[nCnt].Destrot.x > D3DX_PI)
			{
				g_aDog[nCnt].Destrot.x -= D3DX_PI * 2.0f;
			}
			else if (g_aDog[nCnt].Destrot.x < -D3DX_PI)
			{
				g_aDog[nCnt].Destrot.x += D3DX_PI * 2.0f;
			}

			//正規化
			if (g_aDog[nCnt].Destrot.x - g_aDog[nCnt].rot.x > D3DX_PI)
			{
				g_aDog[nCnt].Destrot.x = g_aDog[nCnt].rot.x + ((g_aDog[nCnt].Destrot.x - g_aDog[nCnt].rot.x) - D3DX_PI * 2.0f);
			}
			else if (g_aDog[nCnt].Destrot.x - g_aDog[nCnt].rot.x < -D3DX_PI)
			{
				g_aDog[nCnt].Destrot.x = g_aDog[nCnt].rot.x + ((g_aDog[nCnt].Destrot.x - g_aDog[nCnt].rot.x) + D3DX_PI * 2.0f);
			}

			g_aDog[nCnt].rot.x += (g_aDog[nCnt].Destrot.x - g_aDog[nCnt].rot.x) * ROT_SPEED_DOG;

			//正規化
			if (g_aDog[nCnt].rot.x > D3DX_PI)
			{
				g_aDog[nCnt].rot.x -= D3DX_PI * 2.0f;
			}
			else if (g_aDog[nCnt].rot.x < -D3DX_PI)
			{
				g_aDog[nCnt].rot.x += D3DX_PI * 2.0f;
			}

			//スケール制限
			g_aDog[nCnt].scale.x = max(SCALE_MIN, min(SCALE_MAX, g_aDog[nCnt].scale.x));
			g_aDog[nCnt].scale.y = max(SCALE_MIN, min(SCALE_MAX, g_aDog[nCnt].scale.y));
			g_aDog[nCnt].scale.z = max(SCALE_MIN, min(SCALE_MAX, g_aDog[nCnt].scale.z));

			int nCntModel;
			//パーツ分回す
			for (nCntModel = 0; nCntModel < g_aDog[nCnt].nNumModel; nCntModel++)
			{
				g_aDog[nCnt].aModel[nCntModel].vtxMax.x = g_aDog[nCnt].aModel[nCntModel].vtxMaxDef.x * g_aDog[nCnt].scale.x;
				g_aDog[nCnt].aModel[nCntModel].vtxMax.y = g_aDog[nCnt].aModel[nCntModel].vtxMaxDef.y * g_aDog[nCnt].scale.y;
				g_aDog[nCnt].aModel[nCntModel].vtxMax.z = g_aDog[nCnt].aModel[nCntModel].vtxMaxDef.z * g_aDog[nCnt].scale.z;
				g_aDog[nCnt].aModel[nCntModel].vtxMin.x = g_aDog[nCnt].aModel[nCntModel].vtxMinDef.x * g_aDog[nCnt].scale.x;
				g_aDog[nCnt].aModel[nCntModel].vtxMin.y = g_aDog[nCnt].aModel[nCntModel].vtxMinDef.y * g_aDog[nCnt].scale.y;
				g_aDog[nCnt].aModel[nCntModel].vtxMin.z = g_aDog[nCnt].aModel[nCntModel].vtxMinDef.z * g_aDog[nCnt].scale.z;
			}

			UpdateDogMotion(nCnt);

			if (g_aDog[nCnt].motionType == MOTIONTYPE_ACTION && g_aDog[nCnt].nKey == 2 && g_aDog[nCnt].nCounterMotion == 10)
			{
				SetHitShere(g_aDog[nCnt].pos + g_aDog[nCnt].aModel[0].pos + D3DXVECTOR3(sinf(g_aDog[nCnt].rot.y + g_aDog[nCnt].aModel[0].rot.y ) * cosf(g_aDog[nCnt].rot.x + g_aDog[nCnt].aModel[0].rot.x), sinf(g_aDog[nCnt].rot.x + g_aDog[nCnt].aModel[0].rot.x), cosf(g_aDog[nCnt].rot.y + g_aDog[nCnt].aModel[0].rot.y) * cosf(g_aDog[nCnt].rot.x + g_aDog[nCnt].aModel[0].rot.x)) * sqrtf((g_aDog[nCnt].aModel[1].pos.x - g_aDog[nCnt].aModel[0].pos.x) * (g_aDog[nCnt].aModel[1].pos.x - g_aDog[nCnt].aModel[0].pos.x) + (g_aDog[nCnt].aModel[1].pos.y - g_aDog[nCnt].aModel[0].pos.y) * (g_aDog[nCnt].aModel[1].pos.y - g_aDog[nCnt].aModel[0].pos.y) + (g_aDog[nCnt].aModel[1].pos.z - g_aDog[nCnt].aModel[0].pos.z) * (g_aDog[nCnt].aModel[1].pos.z - g_aDog[nCnt].aModel[0].pos.z)) + D3DXVECTOR3(sinf(g_aDog[nCnt].rot.y + g_aDog[nCnt].aModel[0].rot.y + g_aDog[nCnt].aModel[1].rot.y) * cosf(g_aDog[nCnt].rot.x + g_aDog[nCnt].aModel[0].rot.x + g_aDog[nCnt].aModel[1].rot.x), sinf(g_aDog[nCnt].rot.x + g_aDog[nCnt].aModel[0].rot.x + g_aDog[nCnt].aModel[1].rot.x), cosf(g_aDog[nCnt].rot.y + g_aDog[nCnt].aModel[0].rot.y + g_aDog[nCnt].aModel[1].rot.y) * cosf(g_aDog[nCnt].rot.x + g_aDog[nCnt].aModel[0].rot.x + g_aDog[nCnt].aModel[1].rot.x)) * sqrtf((g_aDog[nCnt].aModel[1].vtxMax.x - g_aDog[nCnt].aModel[1].vtxMin.x) * (g_aDog[nCnt].aModel[1].vtxMax.x - g_aDog[nCnt].aModel[1].vtxMin.x) + (g_aDog[nCnt].aModel[1].vtxMax.y - g_aDog[nCnt].aModel[1].vtxMin.y) * (g_aDog[nCnt].aModel[1].vtxMax.y - g_aDog[nCnt].aModel[1].vtxMin.y) + (g_aDog[nCnt].aModel[1].vtxMax.z - g_aDog[nCnt].aModel[1].vtxMin.z) * (g_aDog[nCnt].aModel[1].vtxMax.z - g_aDog[nCnt].aModel[1].vtxMin.z)), D3DXVECTOR3(100.0f, 100.0f, 100.0f), 10, ENEMY);
			}

			switch (g_aDog[nCnt].state)
			{
			case DOGSTATE_APPEAR:
				g_aDog[nCnt].bUse = false;
				break;
			case DOGSTATE_NORMAL:
				if (g_aDog[nCnt].nLife <= 0)
				{
					g_aDog[nCnt].state = DOGSTATE_DIE;
				}
				SetLife(g_aDog[nCnt].pos + g_aDog[nCnt].aModel[0].pos + g_aDog[nCnt].aModel[1].pos, (float)((float)g_aDog[nCnt].nLife / (float)DOG_LIFE), g_aDog[nCnt].nIdxLife);
				SetPositionShadow(g_aDog[nCnt].nIdxShadow, g_aDog[nCnt].pos, g_aDog[nCnt].scale, 200.0f);
				break;
			case DOGSTATE_DIE:
				g_aDog[nCnt].Destrot.x = D3DX_PI * 0.5f;
				static int nCntDie = 0;
				nCntDie++;
				if (nCntDie >= 20)
				{
					NullLife(g_aDog[nCnt].nIdxLife);
					NullShadow(g_aDog[nCnt].nIdxShadow);
					SetParticle(g_aDog[nCnt].pos, g_aDog[nCnt].scale);
					g_aDog[nCnt].state = DOGSTATE_APPEAR;
				}
				break;
			}
		}
	}
}

//-------------------
//ポリゴン描画処理
//-------------------
void DrawDog(void)
{
	for (int nCnt = 0; nCnt < MAX_DOG; nCnt++)
	{
		if (g_aDog[nCnt].bUse)
		{
			LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
			D3DXMATRIX mtxRot, mtxTrans, mtxScale;//計算マトリックス
			D3DMATERIAL9 matDef;//現在のマテリアル保存用
			D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

			//デバイスの取得
			pDevice = GetDevice();

			//マトリックス初期化
			D3DXMatrixIdentity(&g_aDog[nCnt].mtxWorld);

			//大きさの反映
			D3DXMatrixScaling(&mtxScale, g_aDog[nCnt].scale.x, g_aDog[nCnt].scale.y, g_aDog[nCnt].scale.z);
			D3DXMatrixMultiply(&g_aDog[nCnt].mtxWorld, &g_aDog[nCnt].mtxWorld, &mtxScale);

			//向きの反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aDog[nCnt].rot.y, g_aDog[nCnt].rot.x, g_aDog[nCnt].rot.z);
			D3DXMatrixMultiply(&g_aDog[nCnt].mtxWorld, &g_aDog[nCnt].mtxWorld, &mtxRot);

			//位置の反映
			D3DXMatrixTranslation(&mtxTrans, g_aDog[nCnt].pos.x, g_aDog[nCnt].pos.y, g_aDog[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aDog[nCnt].mtxWorld, &g_aDog[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aDog[nCnt].mtxWorld);

			int nCntModel;
			//パーツ分回す
			for (nCntModel = 0; nCntModel < g_aDog[nCnt].nNumModel; nCntModel++)
			{
				D3DXMATRIX mtxRotModel, mtxTransModel, mtxScaleModel;//計算マトリックス
				D3DXMATRIX mtxParent;
				//マトリックス初期化
				D3DXMatrixIdentity(&g_aDog[nCnt].aModel[nCntModel].mtxWorld);

				//大きさの反映
				D3DXMatrixScaling(&mtxScaleModel, g_aDog[nCnt].aModel[nCntModel].scale.x, g_aDog[nCnt].aModel[nCntModel].scale.y, g_aDog[nCnt].aModel[nCntModel].scale.z);
				D3DXMatrixMultiply(&g_aDog[nCnt].aModel[nCntModel].mtxWorld, &g_aDog[nCnt].aModel[nCntModel].mtxWorld, &mtxScaleModel);

				//向きの反映
				D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_aDog[nCnt].aModel[nCntModel].rot.y, g_aDog[nCnt].aModel[nCntModel].rot.x, g_aDog[nCnt].aModel[nCntModel].rot.z);
				D3DXMatrixMultiply(&g_aDog[nCnt].aModel[nCntModel].mtxWorld, &g_aDog[nCnt].aModel[nCntModel].mtxWorld, &mtxRotModel);

				//位置の反映
				D3DXMatrixTranslation(&mtxTransModel, g_aDog[nCnt].aModel[nCntModel].pos.x, g_aDog[nCnt].aModel[nCntModel].pos.y, g_aDog[nCnt].aModel[nCntModel].pos.z);
				D3DXMatrixMultiply(&g_aDog[nCnt].aModel[nCntModel].mtxWorld, &g_aDog[nCnt].aModel[nCntModel].mtxWorld, &mtxTransModel);

				//パーツの親のマトリックスの設定
				if (g_aDog[nCnt].aModel[nCntModel].nIdxModelParent != -1)
				{//親モデルがある
					mtxParent = g_aDog[nCnt].aModel[g_aDog[nCnt].aModel[nCntModel].nIdxModelParent].mtxWorld;
				}
				else
				{//親モデルがない
					mtxParent = g_aDog[nCnt].mtxWorld;
				}

				D3DXMatrixMultiply(&g_aDog[nCnt].aModel[nCntModel].mtxWorld, &g_aDog[nCnt].aModel[nCntModel].mtxWorld, &mtxParent);

				//ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_aDog[nCnt].aModel[nCntModel].mtxWorld);

				//現在のマテリアル取得
				pDevice->GetMaterial(&matDef);

				//マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_aDog[nCnt].aModel[nCntModel].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_aDog[nCnt].aModel[nCntModel].dwNumMat; nCntMat++)
				{
					//マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
					//テクスチャ
					pDevice->SetTexture(0, g_aDog[nCnt].aModel[nCntModel].apTexture[nCntMat]);

					//モデル描画
					g_aDog[nCnt].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
				}

				pDevice->SetMaterial(&matDef);
			}
		}
	}
}

//------------------------------
//位置取得
//------------------------------
Dog* GetDog(void)
{
	return &g_aDog[0];
}

//------------------------------
//設定
//------------------------------
void SetDog(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < MAX_DOG; nCnt++)
	{
		if (!g_aDog[nCnt].bUse)
		{
			g_aDog[nCnt].pos = pos;
			g_aDog[nCnt].posOld = pos;
			g_aDog[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aDog[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aDog[nCnt].Destrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aDog[nCnt].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_aDog[nCnt].bJump = false;
			g_aDog[nCnt].nLife = DOG_LIFE;
			g_aDog[nCnt].state = DOGSTATE_NORMAL;
			g_aDog[nCnt].nIdxShadow = SetShadow(g_aDog[nCnt].pos, g_aDog[nCnt].rot);
			g_aDog[nCnt].nIdxLife = LinkLife();
			g_aDog[nCnt].pStage = NULL;

			g_aDog[nCnt].bLoopMotion = false;
			g_aDog[nCnt].motionType = MOTIONTYPE_NEUTRAL;
			g_aDog[nCnt].nCounterMotion = 0;
			g_aDog[nCnt].nKey = -1;
			g_aDog[nCnt].nNumKey = 0;
			g_aDog[nCnt].nNumMotion = NUM_MOTION_DOG;
			g_aDog[nCnt].bUse = true;
			break;
		}
	}
}

//------------------------------
//モーション
//------------------------------
void UpdateDogMotion(int nNumber)
{
	static MOTIONTYPE OldMotion[MAX_DOG] = { MOTIONTYPE_NEUTRAL };
	static int BlendCnt[MAX_DOG] = { 0 };

	if (OldMotion[nNumber] != g_aDog[nNumber].motionType)
	{
		g_aDog[nNumber].aMotionInfo[OldMotion[nNumber]] = g_Motion[OldMotion[nNumber]];
		g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType] = g_Motion[g_aDog[nNumber].motionType];

		for (int nCntModel = 0; nCntModel < g_aDog[nNumber].nNumModel; nCntModel++)
		{
			D3DXVECTOR3 Oldpos = D3DXVECTOR3(g_aDog[nNumber].aMotionInfo[OldMotion[nNumber]].aKeyInfo[g_aDog[nNumber].aMotionInfo[OldMotion[nNumber]].nNumKey - 1].aKey[nCntModel].fPosX, g_aDog[nNumber].aMotionInfo[OldMotion[nNumber]].aKeyInfo[g_aDog[nNumber].aMotionInfo[OldMotion[nNumber]].nNumKey - 1].aKey[nCntModel].fPosY, g_aDog[nNumber].aMotionInfo[OldMotion[nNumber]].aKeyInfo[g_aDog[nNumber].aMotionInfo[OldMotion[nNumber]].nNumKey - 1].aKey[nCntModel].fPosZ);
			D3DXVECTOR3 Destpos = D3DXVECTOR3(g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[0].aKey[nCntModel].fPosX, g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[0].aKey[nCntModel].fPosY, g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[0].aKey[nCntModel].fPosZ);
			D3DXVECTOR3 posDif = Destpos - Oldpos;

			D3DXVECTOR3 Oldrot = D3DXVECTOR3(g_aDog[nNumber].aMotionInfo[OldMotion[nNumber]].aKeyInfo[g_aDog[nNumber].aMotionInfo[OldMotion[nNumber]].nNumKey - 1].aKey[nCntModel].fRotX, g_aDog[nNumber].aMotionInfo[OldMotion[nNumber]].aKeyInfo[g_aDog[nNumber].aMotionInfo[OldMotion[nNumber]].nNumKey - 1].aKey[nCntModel].fRotY, g_aDog[nNumber].aMotionInfo[OldMotion[nNumber]].aKeyInfo[g_aDog[nNumber].aMotionInfo[OldMotion[nNumber]].nNumKey - 1].aKey[nCntModel].fRotZ);
			D3DXVECTOR3 Destrot = D3DXVECTOR3(g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[0].aKey[nCntModel].fRotX, g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[0].aKey[nCntModel].fRotY, g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[0].aKey[nCntModel].fRotZ);

			//正規化
			if (Destrot.x - Oldrot.x > D3DX_PI)
			{
				Destrot.x = Oldrot.x + ((Destrot.x - Oldrot.x) - D3DX_PI * 2.0f);
			}
			else if (Destrot.x - Oldrot.x < -D3DX_PI)
			{
				Destrot.x = Oldrot.x + ((Destrot.x - Oldrot.x) + D3DX_PI * 2.0f);
			}
			//正規化
			if (Destrot.y - Oldrot.y > D3DX_PI)
			{
				Destrot.y = Oldrot.y + ((Destrot.y - Oldrot.y) - D3DX_PI * 2.0f);
			}
			else if (Destrot.y - Oldrot.y < -D3DX_PI)
			{
				Destrot.y = Oldrot.y + ((Destrot.y - Oldrot.y) + D3DX_PI * 2.0f);
			}
			//正規化
			if (Destrot.z - Oldrot.z > D3DX_PI)
			{
				Destrot.z = Oldrot.z + ((Destrot.z - Oldrot.z) - D3DX_PI * 2.0f);
			}
			else if (Destrot.z - Oldrot.z < -D3DX_PI)
			{
				Destrot.z = Oldrot.z + ((Destrot.z - Oldrot.z) + D3DX_PI * 2.0f);
			}

			D3DXVECTOR3 rotDif = Destrot - Oldrot;

			g_aDog[nNumber].aModel[nCntModel].pos = g_aDog[nNumber].aModel[nCntModel].posDef + Oldpos + posDif * (BlendCnt[nNumber] / BLEND_FRAME);
			g_aDog[nNumber].aModel[nCntModel].rot = Oldrot + rotDif * (BlendCnt[nNumber] / BLEND_FRAME);

			//正規化
			if (g_aDog[nNumber].aModel[nCntModel].rot.x > D3DX_PI)
			{
				g_aDog[nNumber].aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
			}
			else if (g_aDog[nNumber].aModel[nCntModel].rot.x < -D3DX_PI)
			{
				g_aDog[nNumber].aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
			}
			//正規化
			if (g_aDog[nNumber].aModel[nCntModel].rot.y > D3DX_PI)
			{
				g_aDog[nNumber].aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_aDog[nNumber].aModel[nCntModel].rot.y < -D3DX_PI)
			{
				g_aDog[nNumber].aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
			}
			//正規化
			if (g_aDog[nNumber].aModel[nCntModel].rot.z > D3DX_PI)
			{
				g_aDog[nNumber].aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
			}
			else if (g_aDog[nNumber].aModel[nCntModel].rot.z < -D3DX_PI)
			{
				g_aDog[nNumber].aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
			}
		}

		if (BlendCnt[nNumber] == (int)BLEND_FRAME)
		{
			BlendCnt[nNumber] = 0;
			OldMotion[nNumber] = g_aDog[nNumber].motionType;
			return;
		}
		BlendCnt[nNumber]++;
		return;
	}
	g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType] = g_Motion[g_aDog[nNumber].motionType];
	g_aDog[nNumber].nNumKey = g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].nNumKey;
	g_aDog[nNumber].bLoopMotion = g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].bLoop;
	static int nDestKey = g_aDog[nNumber].nKey + 1;

	if (g_aDog[nNumber].nCounterMotion >= g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[g_aDog[nNumber].nKey].nFrame)
	{
		g_aDog[nNumber].nCounterMotion = 0;
	}

	if (g_aDog[nNumber].nCounterMotion == 0)
	{
		if (nDestKey >= g_aDog[nNumber].nNumKey - 1)
		{
			if (g_aDog[nNumber].bLoopMotion)
			{
				g_aDog[nNumber].nKey++;
				nDestKey = 0;

				for (int nCntModel = 0; nCntModel < g_aDog[nNumber].nNumModel; nCntModel++)
				{
					g_aDog[nNumber].aModel[nCntModel].pos = g_aDog[nNumber].aModel[nCntModel].posDef + D3DXVECTOR3(g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[g_aDog[nNumber].nKey].aKey[nCntModel].fPosX, g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[g_aDog[nNumber].nKey].aKey[nCntModel].fPosY, g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[g_aDog[nNumber].nKey].aKey[nCntModel].fPosZ);
					g_aDog[nNumber].aModel[nCntModel].rot = D3DXVECTOR3(g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[g_aDog[nNumber].nKey].aKey[nCntModel].fRotX, g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[g_aDog[nNumber].nKey].aKey[nCntModel].fRotY, g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[g_aDog[nNumber].nKey].aKey[nCntModel].fRotZ);
				}
			}
			else
			{
				g_aDog[nNumber].nKey = -1;
				nDestKey = g_aDog[nNumber].nKey + 1;
				g_aDog[nNumber].motionType = MOTIONTYPE_NEUTRAL;
				return;
			}
		}
		else
		{
			g_aDog[nNumber].nKey++;
			if (g_aDog[nNumber].nKey > g_aDog[nNumber].nNumKey - 1)
			{
				g_aDog[nNumber].nKey = 0;
			}
			nDestKey = g_aDog[nNumber].nKey + 1;

			for (int nCntModel = 0; nCntModel < g_aDog[nNumber].nNumModel; nCntModel++)
			{
				g_aDog[nNumber].aModel[nCntModel].pos = g_aDog[nNumber].aModel[nCntModel].posDef + D3DXVECTOR3(g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[g_aDog[nNumber].nKey].aKey[nCntModel].fPosX, g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[g_aDog[nNumber].nKey].aKey[nCntModel].fPosY, g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[g_aDog[nNumber].nKey].aKey[nCntModel].fPosZ);
				g_aDog[nNumber].aModel[nCntModel].rot = D3DXVECTOR3(g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[g_aDog[nNumber].nKey].aKey[nCntModel].fRotX, g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[g_aDog[nNumber].nKey].aKey[nCntModel].fRotY, g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[g_aDog[nNumber].nKey].aKey[nCntModel].fRotZ);
			}
		}
	}

	for (int nCntModel = 0; nCntModel < g_aDog[nNumber].nNumModel; nCntModel++)
	{
		D3DXVECTOR3 Oldpos = D3DXVECTOR3(g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[g_aDog[nNumber].nKey].aKey[nCntModel].fPosX, g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[g_aDog[nNumber].nKey].aKey[nCntModel].fPosY, g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[g_aDog[nNumber].nKey].aKey[nCntModel].fPosZ);
		D3DXVECTOR3 Destpos = D3DXVECTOR3(g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[nDestKey].aKey[nCntModel].fPosX, g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[nDestKey].aKey[nCntModel].fPosY, g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[nDestKey].aKey[nCntModel].fPosZ);
		D3DXVECTOR3 posDif = Destpos - Oldpos;

		D3DXVECTOR3 Oldrot = D3DXVECTOR3(g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[g_aDog[nNumber].nKey].aKey[nCntModel].fRotX, g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[g_aDog[nNumber].nKey].aKey[nCntModel].fRotY, g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[g_aDog[nNumber].nKey].aKey[nCntModel].fRotZ);
		D3DXVECTOR3 Destrot = D3DXVECTOR3(g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[nDestKey].aKey[nCntModel].fRotX, g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[nDestKey].aKey[nCntModel].fRotY, g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[nDestKey].aKey[nCntModel].fRotZ);

		//正規化
		if (Destrot.x - Oldrot.x > D3DX_PI)
		{
			Destrot.x = Oldrot.x + ((Destrot.x - Oldrot.x) - D3DX_PI * 2.0f);
		}
		else if (Destrot.x - Oldrot.x < -D3DX_PI)
		{
			Destrot.x = Oldrot.x + ((Destrot.x - Oldrot.x) + D3DX_PI * 2.0f);
		}
		//正規化
		if (Destrot.y - Oldrot.y > D3DX_PI)
		{
			Destrot.y = Oldrot.y + ((Destrot.y - Oldrot.y) - D3DX_PI * 2.0f);
		}
		else if (Destrot.y - Oldrot.y < -D3DX_PI)
		{
			Destrot.y = Oldrot.y + ((Destrot.y - Oldrot.y) + D3DX_PI * 2.0f);
		}
		//正規化
		if (Destrot.z - Oldrot.z > D3DX_PI)
		{
			Destrot.z = Oldrot.z + ((Destrot.z - Oldrot.z) - D3DX_PI * 2.0f);
		}
		else if (Destrot.z - Oldrot.z < -D3DX_PI)
		{
			Destrot.z = Oldrot.z + ((Destrot.z - Oldrot.z) + D3DX_PI * 2.0f);
		}

		D3DXVECTOR3 rotDif = Destrot - Oldrot;

		g_aDog[nNumber].aModel[nCntModel].pos = g_aDog[nNumber].aModel[nCntModel].posDef + Oldpos + posDif * (g_aDog[nNumber].nCounterMotion / (float)g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[g_aDog[nNumber].nKey].nFrame);
		g_aDog[nNumber].aModel[nCntModel].rot = Oldrot + rotDif * (g_aDog[nNumber].nCounterMotion / (float)g_aDog[nNumber].aMotionInfo[g_aDog[nNumber].motionType].aKeyInfo[g_aDog[nNumber].nKey].nFrame);

		//正規化
		if (g_aDog[nNumber].aModel[nCntModel].rot.x > D3DX_PI)
		{
			g_aDog[nNumber].aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
		}
		else if (g_aDog[nNumber].aModel[nCntModel].rot.x < -D3DX_PI)
		{
			g_aDog[nNumber].aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
		}
		//正規化
		if (g_aDog[nNumber].aModel[nCntModel].rot.y > D3DX_PI)
		{
			g_aDog[nNumber].aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
		}
		else if (g_aDog[nNumber].aModel[nCntModel].rot.y < -D3DX_PI)
		{
			g_aDog[nNumber].aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
		}
		//正規化
		if (g_aDog[nNumber].aModel[nCntModel].rot.z > D3DX_PI)
		{
			g_aDog[nNumber].aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
		}
		else if (g_aDog[nNumber].aModel[nCntModel].rot.z < -D3DX_PI)
		{
			g_aDog[nNumber].aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
		}
	}
	g_aDog[nNumber].nCounterMotion++;
}