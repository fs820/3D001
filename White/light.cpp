//----------------------------------------
//
//ライト処理[light.cpp]
//Author fuma sato
//
//----------------------------------------

#include"main.h"
#include"light.h"
#include"input.h"

//グローバル変数宣言
D3DLIGHT9 g_light[LIGHT_MAX];
D3DXVECTOR3 g_vecDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
float g_angle = 0.0f;
bool g_Input = false;
//----------------------
//初期化処理
//----------------------
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCount = 0;

	g_Input = false;

	//ライトをクリアする
	ZeroMemory(&g_light, sizeof(g_light));

	//------------------------------
	// ディレクショナルライトの設定
	//------------------------------
	//種類
	g_light[0].Type = D3DLIGHT_DIRECTIONAL;
	//拡散光
	g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//環境光
	g_light[0].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//鏡面反射光
	g_light[0].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//方向
	g_vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
	//正規化
	D3DXVec3Normalize(&g_vecDir, &g_vecDir);
	g_light[0].Direction = g_vecDir;
	//ライトセット
	pDevice->SetLight(0,&g_light[0]);
	//有効化
	pDevice->LightEnable(0, TRUE);

	//種類
	g_light[1].Type = D3DLIGHT_DIRECTIONAL;
	//拡散光
	g_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//環境光
	g_light[1].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//鏡面反射光
	g_light[1].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//方向
	g_vecDir = D3DXVECTOR3(-0.9f, -0.8f, 0.8f);
	//正規化
	D3DXVec3Normalize(&g_vecDir, &g_vecDir);
	g_light[1].Direction = g_vecDir;
	//ライトセット
	pDevice->SetLight(1, &g_light[1]);
	//有効化
	pDevice->LightEnable(1, TRUE);

	//種類
	g_light[2].Type = D3DLIGHT_DIRECTIONAL;
	//拡散光
	g_light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//環境光
	g_light[2].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//鏡面反射光
	g_light[2].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//方向
	g_vecDir = D3DXVECTOR3(0.1f, -0.4f, 0.8f);
	//正規化
	D3DXVec3Normalize(&g_vecDir, &g_vecDir);
	g_light[2].Direction = g_vecDir;
	//ライトセット
	pDevice->SetLight(2, &g_light[2]);
	//有効化
	pDevice->LightEnable(2, TRUE);

	//種類
	g_light[3].Type = D3DLIGHT_DIRECTIONAL;
	//拡散光
	g_light[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//環境光
	g_light[3].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//鏡面反射光
	g_light[3].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//方向
	g_vecDir = D3DXVECTOR3(-0.6f, 0.8f, -0.2f);
	//正規化
	D3DXVec3Normalize(&g_vecDir, &g_vecDir);
	g_light[3].Direction = g_vecDir;
	//ライトセット
	pDevice->SetLight(3, &g_light[3]);
	//有効化
	pDevice->LightEnable(3, TRUE);

	//種類
	g_light[8].Type = D3DLIGHT_DIRECTIONAL;
	//拡散光
	g_light[8].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//環境光
	g_light[8].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//鏡面反射光
	g_light[8].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//方向
	g_vecDir = D3DXVECTOR3(0.7f, -0.1f, -0.2f);
	//正規化
	D3DXVec3Normalize(&g_vecDir, &g_vecDir);
	g_light[8].Direction = g_vecDir;
	//ライトセット
	pDevice->SetLight(8, &g_light[8]);
	//有効化
	pDevice->LightEnable(8, TRUE);

	//種類
	g_light[9].Type = D3DLIGHT_DIRECTIONAL;
	//拡散光
	g_light[9].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//環境光
	g_light[9].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//鏡面反射光
	g_light[9].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//方向
	g_vecDir = D3DXVECTOR3(0.7f, -0.1f, -0.2f);
	//正規化
	D3DXVec3Normalize(&g_vecDir, &g_vecDir);
	g_light[9].Direction = g_vecDir;
	//ライトセット
	pDevice->SetLight(9, &g_light[9]);
	//有効化
	pDevice->LightEnable(9, TRUE);

	//-----------------------
	// スポットライトの設定
	//-----------------------
	//種類
	g_light[4].Type = D3DLIGHT_SPOT;
	//拡散光
	g_light[4].Diffuse = D3DXCOLOR(10.0f, 10.0f, 10.0f, 1.0f);
	//環境光
	g_light[4].Ambient = D3DXCOLOR(10.0f, 10.0f, 10.0f, 1.0f);
	//鏡面反射光
	g_light[4].Specular = D3DXCOLOR(10.0f, 10.0f, 10.0f, 1.0f);
	//位置
	g_light[4].Position = D3DXVECTOR3(0.0f, 2000.0f, 1.0f);
	//方向
	g_vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	//正規化
	D3DXVec3Normalize(&g_vecDir, &g_vecDir);
	g_light[4].Direction = g_vecDir;
	//範囲
	g_light[4].Range = 3000.0f;
	//コーン減衰率
	g_light[4].Falloff = 0.01f;
	//距離減衰率
	g_light[4].Attenuation0 = 0.1f;
	//コーン角度(内)
	g_light[4].Theta = D3DXToRadian(0.0f);
	//コーン角度(外)
	g_light[4].Phi = D3DXToRadian(360.0f);
	//ライトセット
	pDevice->SetLight(4, &g_light[4]);
	//有効化
	pDevice->LightEnable(4, TRUE);

	//----------------------
	// ポイントライトの設定
	//----------------------
	//種類
	g_light[5].Type = D3DLIGHT_POINT;
	//拡散光
	g_light[5].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//環境光
	g_light[5].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//鏡面反射光
	g_light[5].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//位置
	g_light[5].Position = D3DXVECTOR3(0.0f, 500.0f, 0.0f);
	//範囲
	g_light[5].Range = 1000.0f;
	//距離減衰率(一定)
	g_light[5].Attenuation0 = 0.1f;
	//距離減衰率(距離)
	g_light[5].Attenuation1 = 0.0f;
	//距離減衰率(距離*2)
	g_light[5].Attenuation2 = 0.0f;
	//ライトセット
	pDevice->SetLight(5, &g_light[5]);
	//有効化
	pDevice->LightEnable(5, TRUE);

	//種類
	g_light[6].Type = D3DLIGHT_POINT;
	//拡散光
	g_light[6].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//環境光
	g_light[6].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//鏡面反射光
	g_light[6].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//位置
	g_light[6].Position = D3DXVECTOR3(-100.0f, 0.0f, 1500.0f);
	//範囲
	g_light[6].Range = 1000.0f;
	//距離減衰率(一定)
	g_light[6].Attenuation0 = 0.1f;
	//距離減衰率(距離)
	g_light[6].Attenuation1 = 0.0f;
	//距離減衰率(距離*2)
	g_light[6].Attenuation2 = 0.0f;
	//ライトセット
	pDevice->SetLight(6, &g_light[6]);
	//有効化
	pDevice->LightEnable(6, TRUE);

	//種類
	g_light[7].Type = D3DLIGHT_POINT;
	//拡散光
	g_light[7].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//環境光
	g_light[7].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//鏡面反射光
	g_light[7].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//位置
	g_light[7].Position = D3DXVECTOR3(0.0f, 0.0f, 1600.0f);
	//範囲
	g_light[7].Range = 1000.0f;
	//距離減衰率(一定)
	g_light[7].Attenuation0 = 0.1f;
	//距離減衰率(距離)
	g_light[7].Attenuation1 = 0.0f;
	//距離減衰率(距離*2)
	g_light[7].Attenuation2 = 0.0f;
	//ライトセット
	pDevice->SetLight(7, &g_light[7]);
	//有効化
	pDevice->LightEnable(7, TRUE);
}

//-------------------
//終了処理
//-------------------
void UninitLight(void)
{

}

//-------------------
//更新処理
//-------------------
void UpdateLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (GetKeyboradTrigger(DIK_I))
	{
		g_Input = !g_Input;
	}

	if (g_Input)
	{
		if (GetKeyboradPress(DIK_LEFT))
		{
			g_angle -= 0.01f;
		}

		if (GetKeyboradPress(DIK_RIGHT))
		{
			g_angle += 0.01f;
		}
	}
	else
	{
		//角度を更新
		g_angle += 0.01f;
	}

	//正規化
	if (g_angle > D3DX_PI)
	{
		g_angle -= D3DX_PI * 2.0f;
	}
	else if (g_angle < -D3DX_PI)
	{
		g_angle += D3DX_PI * 2.0f;
	}

	//ベクトルを計算
	g_vecDir = D3DXVECTOR3(sinf(g_angle) * 0.2f, -0.8f, cosf(g_angle) * -0.4f);

	//正規化
	D3DXVec3Normalize(&g_vecDir, &g_vecDir);
	g_light[0].Direction = g_vecDir;

	//セット
	pDevice->SetLight(0, &g_light[0]);

	static int nCnt = 0;
	if (nCnt % 60 == 0)
	{
		//ベクトルを計算
		g_vecDir = D3DXVECTOR3((((float)(rand() % 201) / 100) - 1.0f), (((float)(rand() % 201) / 100) - 1.0f), (((float)(rand() % 201) / 100) - 1.0f));

		//正規化
		D3DXVec3Normalize(&g_vecDir, &g_vecDir);
		g_light[9].Direction = g_vecDir;

		//セット
		pDevice->SetLight(9, &g_light[9]);
	}
	nCnt++;
}

//--------------------------
//角度取得
//--------------------------
float GetLightAngle(void)
{
	return g_angle;
}