//----------------------------------------
//
//カメラ処理[camera.cpp]
//Author fuma sato
//
//----------------------------------------

#include"main.h"
#include"camera.h"
#include"player.h"
#include"input.h"
#include"pause.h"

//グローバル変数宣言
Camera g_camera;//カメラ情報
//----------------------
//初期化処理
//----------------------
void InitCamera(void)
{
	//カメラ設定
	g_camera.posV = D3DXVECTOR3(0.0f, 120.0f, START_Z - 300.0f);
	g_camera.posVDest = D3DXVECTOR3(0.0f, 120.0f, START_Z - 300.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, START_Z);
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, START_Z);
	g_camera.posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	g_camera.rot = D3DXVECTOR3(-atan2f(120.0f, 300.0f), 0.0f, 0.0f);
	g_camera.fDistance = sqrtf((g_camera.posR.x - g_camera.posV.x) * (g_camera.posR.x - g_camera.posV.x) + (g_camera.posR.y - g_camera.posV.y) * (g_camera.posR.y - g_camera.posV.y) + (g_camera.posR.z - g_camera.posV.z) * (g_camera.posR.z - g_camera.posV.z));
	g_camera.fDistanceMin = CAMERA_DISTANCE_MIN;
	g_camera.fDistanceMax = CAMERA_DISTANCE_MAX;
}

//-------------------
//終了処理
//-------------------
void UninitCamera(void)
{

}

//-------------------
//更新処理
//-------------------
void UpdateCamera(void)
{
	if (!bPause())
	{
		float fMouseWheel;
		fMouseWheel = GetMouseWheel();
		g_camera.fDistance += fMouseWheel * CAMERA_DISTANCE_SPEED;
		if (GetKeyboradPress(DIK_1) || GetJoykeyPress(JOYKEY_RB, CONTROLLER_1))
		{
			g_camera.fDistance += CAMERA_DISTANCE_SPEED;
		}
		if (GetKeyboradPress(DIK_2) || GetJoykeyPress(JOYKEY_RT, CONTROLLER_1))
		{
			g_camera.fDistance += -CAMERA_DISTANCE_SPEED;
		}

		if (!strcmp(ControllerName(CONTROLLER_1), ELE_CON))
		{
			if (GetdJoykeyPress(ELEKEY_RB, CONTROLLER_1))
			{
				g_camera.fDistance += CAMERA_DISTANCE_SPEED;
			}
			if (GetdJoykeyPress(ELEKEY_RT, CONTROLLER_1))
			{
				g_camera.fDistance += -CAMERA_DISTANCE_SPEED;
			}
		}
		else if (!strcmp(ControllerName(CONTROLLER_1), PS_CON))
		{
			if (GetdJoykeyPress(PSKEY_RB, CONTROLLER_1))
			{
				g_camera.fDistance += CAMERA_DISTANCE_SPEED;
			}
			if (GetdJoykeyPress(PSKEY_RT, CONTROLLER_1))
			{
				g_camera.fDistance += -CAMERA_DISTANCE_SPEED;
			}
		}
		else if (!strcmp(ControllerName(CONTROLLER_1), NIN_CON))
		{
			if (GetdJoykeyPress(NINKEY_RB, CONTROLLER_1))
			{
				g_camera.fDistance += CAMERA_DISTANCE_SPEED;
			}
			if (GetdJoykeyPress(NINKEY_RT, CONTROLLER_1))
			{
				g_camera.fDistance += -CAMERA_DISTANCE_SPEED;
			}
		}
		else if (!IsXInputControllerConnected(CONTROLLER_1) && IsDirectInputControllerConnected(CONTROLLER_1))
		{
			if (GetdJoykeyPress(DKEY_RB, CONTROLLER_1))
			{
				g_camera.fDistance += CAMERA_DISTANCE_SPEED;
			}
			if (GetdJoykeyPress(DKEY_RT, CONTROLLER_1))
			{
				g_camera.fDistance += -CAMERA_DISTANCE_SPEED;
			}
		}

		//スケール制限
		g_camera.fDistance = max(g_camera.fDistanceMin, min(g_camera.fDistanceMax, g_camera.fDistance));
	}

	if (GetMode() == MODE_TITLE || GetMode() == MODE_RESULT || GetMode() == MODE_RANK)
	{
		g_camera.rot.y += CAMERA_VIEW_SPEED;

		//スケール制限
		g_camera.rot.x = max(-D3DX_PI * CAMERA_ROTX - D3DX_PI * CAMERA_ROTX, min(D3DX_PI * CAMERA_ROTX - D3DX_PI * CAMERA_ROTX - D3DX_PI * CAMERA_ROTX_GRA, g_camera.rot.x));

		//正規化
		if (g_camera.rot.x > D3DX_PI)
		{
			g_camera.rot.x -= D3DX_PI * 2.0f;
		}
		else if (g_camera.rot.x < -D3DX_PI)
		{
			g_camera.rot.x += D3DX_PI * 2.0f;
		}

		//正規化
		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y -= D3DX_PI * 2.0f;
		}
		else if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y += D3DX_PI * 2.0f;
		}

		if (GetKeyboradPress(DIK_R))
		{
			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * cosf(g_camera.rot.x) * g_camera.fDistance;
			g_camera.posR.y = g_camera.posV.y + sinf(g_camera.rot.x) * g_camera.fDistance;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * cosf(g_camera.rot.x) * g_camera.fDistance;
		}
		else
		{
			g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y - D3DX_PI) * cosf(g_camera.rot.x) * g_camera.fDistance;
			g_camera.posV.y = g_camera.posR.y + sinf(g_camera.rot.x - D3DX_PI) * g_camera.fDistance;
			g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y - D3DX_PI) * cosf(g_camera.rot.x) * g_camera.fDistance;
		}
	}
	else if(!bPause())
	{
		Player* pPlayer = GetPlayer();
		float* pStick;
		float* pMouseMove;
		float Oldrot = g_camera.rot.y;
		//X
		if (IsXInputControllerConnected(CONTROLLER_1))
		{
			//右スティック処理
			pStick = GetJoyStick(STICK_RIGHT, CONTROLLER_1);
			if (sqrtf(*pStick * *pStick + *(pStick + 1) * *(pStick + 1)) >= STICK_DED)
			{
				g_camera.rot.y += cosf(atan2f(*(pStick + 1), *pStick)) * CAMERA_ROT_SPEED;
				g_camera.rot.x += sinf(atan2f(*(pStick + 1), *pStick)) * CAMERA_ROT_SPEED;
			}
		}
		//d
		else if (IsDirectInputControllerConnected(CONTROLLER_1))
		{
			//右スティック処理
			pStick = GetdJoyStick(STICK_RIGHT, CONTROLLER_1);
			if (sqrtf(*pStick * *pStick + *(pStick + 1) * *(pStick + 1)) >= STICK_DED)
			{
				g_camera.rot.y += cosf(atan2f(*(pStick + 1), *pStick)) * CAMERA_ROT_SPEED;
				g_camera.rot.x += sinf(-atan2f(*(pStick + 1), *pStick)) * CAMERA_ROT_SPEED;
			}
		}

		pMouseMove = GetMouseMove();
		if (sqrtf(*pMouseMove * *pMouseMove + *(pMouseMove + 1) * *(pMouseMove + 1)) >= STICK_DED)
		{
			g_camera.rot.y += cosf(atan2f(*(pMouseMove + 1), *pMouseMove)) * CAMERA_ROT_SPEED;
			g_camera.rot.x += sinf(-atan2f(*(pMouseMove + 1), *pMouseMove)) * CAMERA_ROT_SPEED;
		}

		if (GetKeyboradPress(DIK_DOWN))
		{
			g_camera.rot.x -= CAMERA_ROT_SPEED;
		}

		if (GetKeyboradPress(DIK_UP))
		{
			g_camera.rot.x += CAMERA_ROT_SPEED;
		}

		if (GetKeyboradPress(DIK_LEFT))
		{
			g_camera.rot.y -= CAMERA_ROT_SPEED;
		}

		if (GetKeyboradPress(DIK_RIGHT))
		{
			g_camera.rot.y += CAMERA_ROT_SPEED;
		}

		if (pPlayer->move.x == 0.0f && pPlayer->move.z == 0.0f && Oldrot == g_camera.rot.y)
		{
			static int nCnt = 0;
			float rot = g_camera.rot.y;
			nCnt++;
			if (nCnt % 300 < 50)
			{
				rot = pPlayer->Destrot.y - D3DX_PI;
			}
			//正規化
			if (rot - g_camera.rot.y > D3DX_PI)
			{
				rot = g_camera.rot.y + ((rot - g_camera.rot.y) - D3DX_PI * 2.0f);
			}
			else if (rot - g_camera.rot.y < -D3DX_PI)
			{
				rot = g_camera.rot.y + ((rot - g_camera.rot.y) + D3DX_PI * 2.0f);
			}

			g_camera.rot.y += (rot - g_camera.rot.y) * CAMERA_INA;
		}

		if (!GetKeyboradPress(DIK_R) && !GetMousePress(MOUSE_B1))
		{
			//スケール制限
			g_camera.rot.x = max(-D3DX_PI * CAMERA_ROTX - D3DX_PI * CAMERA_ROTX, min(D3DX_PI * CAMERA_ROTX - D3DX_PI * CAMERA_ROTX - D3DX_PI * CAMERA_ROTX_GRA, g_camera.rot.x));
		}

		//正規化
		if (g_camera.rot.x > D3DX_PI)
		{
			g_camera.rot.x -= D3DX_PI * 2.0f;
		}
		else if (g_camera.rot.x < -D3DX_PI)
		{
			g_camera.rot.x += D3DX_PI * 2.0f;
		}

		//正規化
		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y -= D3DX_PI * 2.0f;
		}
		else if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y += D3DX_PI * 2.0f;
		}

		if (GetKeyboradPress(DIK_R) || GetMousePress(MOUSE_B1))
		{
			//スケール制限
			g_camera.rot.x = max(-D3DX_PI * CAMERA_ROTX - D3DX_PI * CAMERA_ROTX * 0.5f, min(D3DX_PI * CAMERA_ROTX - D3DX_PI * CAMERA_ROTX * 0.5f, g_camera.rot.x));
			g_camera.posV = pPlayer->pos;
			g_camera.posV.y += pPlayer->aModel[0].pos.y + pPlayer->aModel[1].pos.y;
			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * cosf(g_camera.rot.x) * g_camera.fDistance;
			g_camera.posR.y = g_camera.posV.y + sinf(g_camera.rot.x) * g_camera.fDistance;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * cosf(g_camera.rot.x) * g_camera.fDistance;
		}
		else
		{
			Player* pPlayer = GetPlayer();
			g_camera.posRDest.x = pPlayer->pos.x + sinf(atan2f(pPlayer->move.z, pPlayer->move.x)) * SPEED;
			g_camera.posRDest.y = pPlayer->pos.y + cosf(g_camera.rot.x) * SPEED;
			g_camera.posRDest.z = pPlayer->pos.z + cosf(atan2f(pPlayer->move.z, pPlayer->move.x)) * SPEED;
			g_camera.posVDest.x = pPlayer->pos.x + sinf(g_camera.rot.y - D3DX_PI) * cosf(g_camera.rot.x) * g_camera.fDistance;
			g_camera.posVDest.y = pPlayer->pos.y + sinf(g_camera.rot.x - D3DX_PI) * g_camera.fDistance;
			g_camera.posVDest.z = pPlayer->pos.z + cosf(g_camera.rot.y - D3DX_PI) * cosf(g_camera.rot.x) * g_camera.fDistance;

			g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * CAMERA_INA;
			g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * CAMERA_INA;
			g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * CAMERA_INA;
			g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * CAMERA_INA;
			g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * CAMERA_INA;
			g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * CAMERA_INA;
		}

		if (GetKeyboradPress(DIK_P) || GetMousePress(MOUSE_B2) == true || GetJoykeyPress(JOYKEY_X, CONTROLLER_1) == true)
		{
			float* pStick;
			float* pMouseMove;
			//X
			if (IsXInputControllerConnected(CONTROLLER_1))
			{
				//右スティック処理
				pStick = GetJoyStick(STICK_RIGHT, CONTROLLER_1);
				if (sqrtf(*pStick * *pStick + *(pStick + 1) * *(pStick + 1)) >= STICK_DED)
				{
					g_camera.posV.x += sinf(g_camera.rot.y - D3DX_PI * 0.5f + atan2f(*(pStick + 1), -*pStick)) * CAMERA_SPEED;
					g_camera.posV.z += cosf(g_camera.rot.y - D3DX_PI * 0.5f + atan2f(*(pStick + 1), -*pStick)) * CAMERA_SPEED;
				}
			}
			//d
			else if (IsDirectInputControllerConnected(CONTROLLER_1))
			{
				//右スティック処理
				pStick = GetdJoyStick(STICK_RIGHT, CONTROLLER_1);
				if (sqrtf(*pStick * *pStick + *(pStick + 1) * *(pStick + 1)) >= STICK_DED)
				{
					g_camera.posV.x += sinf(g_camera.rot.y - D3DX_PI * 0.5f + atan2f(-*(pStick + 1), -*pStick)) * CAMERA_SPEED;
					g_camera.posV.z += cosf(g_camera.rot.y - D3DX_PI * 0.5f + atan2f(-*(pStick + 1), -*pStick)) * CAMERA_SPEED;
				}
			}

			pMouseMove = GetMouseMove();
			if (sqrtf(*pMouseMove * *pMouseMove + *(pMouseMove + 1) * *(pMouseMove + 1)) >= STICK_DED)
			{
				g_camera.posV.x -= sinf(g_camera.rot.y - D3DX_PI * 0.5f + atan2f(*(pMouseMove + 1), *pMouseMove)) * CAMERA_SPEED;
				g_camera.posV.z -= cosf(g_camera.rot.y - D3DX_PI * 0.5f + atan2f(*(pMouseMove + 1), *pMouseMove)) * CAMERA_SPEED;
			}

			if (GetKeyboradPress(DIK_LEFT) || GetJoykeyPress(JOYKEY_LEFT, CONTROLLER_1))
			{
				g_camera.posV.x += sinf(g_camera.rot.y - D3DX_PI * 0.5f) * CAMERA_SPEED;
				g_camera.posV.z += cosf(g_camera.rot.y - D3DX_PI * 0.5f) * CAMERA_SPEED;
			}

			if (GetKeyboradPress(DIK_RIGHT) || GetJoykeyPress(JOYKEY_RIGHT, CONTROLLER_1))
			{
				g_camera.posV.x -= sinf(g_camera.rot.y - D3DX_PI * 0.5f) * CAMERA_SPEED;
				g_camera.posV.z -= cosf(g_camera.rot.y - D3DX_PI * 0.5f) * CAMERA_SPEED;
			}

			if (GetKeyboradPress(DIK_DOWN) || GetJoykeyPress(JOYKEY_DOWN, CONTROLLER_1))
			{
				g_camera.posV.x += sinf(g_camera.rot.y - D3DX_PI) * CAMERA_SPEED;
				g_camera.posV.z += cosf(g_camera.rot.y - D3DX_PI) * CAMERA_SPEED;
			}

			if (GetKeyboradPress(DIK_UP) || GetJoykeyPress(JOYKEY_UP, CONTROLLER_1))
			{
				g_camera.posV.x -= sinf(g_camera.rot.y - D3DX_PI) * CAMERA_SPEED;
				g_camera.posV.z -= cosf(g_camera.rot.y - D3DX_PI) * CAMERA_SPEED;
			}

			if (GetKeyboradPress(DIK_RSHIFT) || GetJoykeyPress(JOYKEY_X, CONTROLLER_1))
			{
				g_camera.posV.y += CAMERA_SPEED;
			}

			if (GetKeyboradPress(DIK_RCONTROL) || GetJoykeyPress(JOYKEY_X, CONTROLLER_1))
			{
				g_camera.posV.y -= CAMERA_SPEED;
			}

			g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * cosf(g_camera.rot.x) * g_camera.fDistance;
			g_camera.posR.y = g_camera.posV.y + sinf(g_camera.rot.x) * g_camera.fDistance;
			g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * cosf(g_camera.rot.x) * g_camera.fDistance;
		}
	}
}

//-------------------
//描画処理
//-------------------
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATRIX mtxRot, mtxTrans;//計算マトリックス

	//デバイスの取得
	pDevice = GetDevice();
	//ビューマトリックス初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH
	(
		&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.posU
	);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);

	//プロジェクションマトリックス初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH
	(
		&g_camera.mtxProjection,
		D3DXToRadian(CAMERA_WIDTH),//視界の広さ
		(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,//比率
		CAMERA_MIN,//どこから
		CAMERA_MAX//どこまで
	);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
}

//--------------------------
//カメラ取得
//--------------------------
Camera* GetCamera(void)
{
	return &g_camera;
}

//--------------------
//背景用
//--------------------
void ViewCamera(void)
{
	g_camera.posV = D3DXVECTOR3(0.0f, 120.0f, -6000.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fDistance = sqrtf((g_camera.posR.x - g_camera.posV.x) * (g_camera.posR.x - g_camera.posV.x) + (g_camera.posR.y - g_camera.posV.y) * (g_camera.posR.y - g_camera.posV.y) + (g_camera.posR.z - g_camera.posV.z) * (g_camera.posR.z - g_camera.posV.z));
	g_camera.fDistanceMax = CAMERA_DISTANCE_VIEW_MAX;
}

//--------------------
//ゲーム用
//--------------------
void GameCamera(void)
{
	g_camera.posV = D3DXVECTOR3(0.0f, 120.0f, START_Z - 300.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, START_Z);
	g_camera.fDistance = sqrtf((g_camera.posR.x - g_camera.posV.x) * (g_camera.posR.x - g_camera.posV.x) + (g_camera.posR.y - g_camera.posV.y) * (g_camera.posR.y - g_camera.posV.y) + (g_camera.posR.z - g_camera.posV.z) * (g_camera.posR.z - g_camera.posV.z));
	g_camera.fDistanceMax = CAMERA_DISTANCE_MAX;
}