//----------------------------------------
//
//モデル表示処理[model.cpp]
//Author fuma sato
//
//----------------------------------------

#include"model.h"
#include"camera.h"
#include"input.h"

//グローバル変数宣言
//Model g_aModel[MODEL_MAX];
//----------------------
//ポリゴンの初期化処理
//----------------------
void InitModel(void)
{
	//LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	//D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	////デバイスの取得
	//pDevice = GetDevice();

	//int nCnt;
	//for (nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	//{
	//	g_aModel[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	g_aModel[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	g_aModel[nCnt].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//	//Xファイル読み込み
	//	D3DXLoadMeshFromX
	//	(
	//		X_NAME,
	//		D3DXMESH_SYSTEMMEM,
	//		pDevice,
	//		NULL,
	//		&g_pBuffMatModel,
	//		NULL,
	//		&g_dwNumMatModel,
	//		&g_pMeshModel
	//	);

	//	//マテリアルデータへのポインタを取得
	//	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	//	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	//	{
	//		if (pMat[nCntMat].pTextureFilename != NULL)
	//		{//テクスチャがある
	//			//テクスチャの読み込み
	//			D3DXCreateTextureFromFile
	//			(
	//				pDevice,
	//				pMat[nCntMat].pTextureFilename,
	//				&g_apTextureModel[nCntMat]
	//			);
	//		}
	//	}
	//}
}

//-------------------
//ポリゴン終了処理
//-------------------
void UninitModel(void)
{
	//for (int i = 0; i < 128; i++)
	//{
	//	if (g_apTextureModel[i]!=NULL)
	//	{
	//		g_apTextureModel[i]->Release();
	//		g_apTextureModel[i] = NULL;
	//	}
	//}
	////メッシュの破棄
	//if (g_pMeshModel != NULL)
	//{
	//	g_pMeshModel->Release();
	//	g_pMeshModel = NULL;
	//}
	////マテリアルの破棄
	//if (g_pBuffMatModel != NULL)
	//{
	//	g_pBuffMatModel->Release();
	//	g_pBuffMatModel = NULL;
	//}
}

//-------------------
//ポリゴン更新処理
//-------------------
void UpdateModel(void)
{

}

//-------------------
//ポリゴン描画処理
//-------------------
void DrawModel(void)
{
	//LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	//D3DXMATRIX mtxRot, mtxTrans, mtxScale;//計算マトリックス
	//D3DMATERIAL9 matDef;//現在のマテリアル保存用
	//D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	////デバイスの取得
	//pDevice = GetDevice();
	////マトリックス初期化
	//D3DXMatrixIdentity(&g_mtxWorldModel);

	////大きさの反映
	//D3DXMatrixScaling(&mtxScale, g_scaleModel.x, g_scaleModel.y, g_scaleModel.z);
	//D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxScale);

	////向きの反映
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);
	//D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	////位置の反映
	//D3DXMatrixTranslation(&mtxTrans, g_posModel.x, g_posModel.y, g_posModel.z);
	//D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	////ワールドマトリックスの設定
	//pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	////現在のマテリアル取得
	//pDevice->GetMaterial(&matDef);

	////マテリアルデータへのポインタを取得
	//pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	//for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	//{
	//	//マテリアルの設定
	//	pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
	//	//テクスチャ
	//	pDevice->SetTexture(0, g_apTextureModel[nCntMat]);

	//	//モデル描画
	//	g_pMeshModel->DrawSubset(nCntMat);
	//}

	//pDevice->SetMaterial(&matDef);
}

////------------------------------
////位置取得
////------------------------------
//Model* GetModel(void)
//{
//	return &g_aModel[0];
//}