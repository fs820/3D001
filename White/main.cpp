//------------------------------------------
//
//テクスチャ表示プログラムのメインの処理[main.cpp]
//Author fuma sato
//
//------------------------------------------

#include"main.h"
#include"camera.h"
#include"light.h"
#include"cursor.h"
#include"fade.h"
#include"rank.h"
#include"result.h"
#include"sound.h"
#include"title.h"
#include"game.h"
#include"shadow.h"
#include"ground.h"
#include"wall.h"
#include"player.h"
#include"input.h"
#include"pause.h"

#define IDI_ICON1 (WORD)"IDI_ICON1"

LPDIRECT3D9 g_pD3D = NULL;//ダイレクトXオブジェクトのグローバルポインタを宣言
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;//ダイレクトXデバイスのグローバルポインタを宣言
MODE g_mode = MODE_TITLE;
HINSTANCE g_hInstance;
HWND g_hWnd;
bool g_bStop = false;
bool g_bFullScreen = false;
LPD3DXFONT g_pFont = NULL;//フォントポインタ
int g_nCountFPS = 0;//FPSカウンタ
bool g_bDebug = true;

//------------------------
//メイン関数
//------------------------
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{

	//ウインドウ設定
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),//メモリサイズ
		CS_CLASSDC,//スタイル
		WindowProc,//プロシージャ
		0,//0
		0,//0
		hInstance,//インスタンスハンドル
		LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)),//タスクバーアイコン
		LoadCursor(NULL,IDC_ARROW),//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 3),//背景色
		NULL,//メニューバー
		CLASS_NAME,//クラスの名前
		LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1))//アイコン
	};

	srand((int)time(NULL));//乱数設定
	HWND hWnd = nullptr;//ハンドル
	MSG msg = { 0 };//メッセージ
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };//ウインドウサイズの設定
	DWORD dwCurrntTime;//現在のシステム時刻
	DWORD dwExceLastTime;//前回のシステム時刻

	//ウインドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域のサイズ調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウインドウを生成
	hWnd = CreateWindowEx
	(
		0,//スタイル
		CLASS_NAME,//ウインドウクラスの名前
		WINDOW_NAME,//ウインドウの名前
		WS_OVERLAPPEDWINDOW,//スタイル
		CW_USEDEFAULT,//左上座標
		CW_USEDEFAULT,//右下座標
		(rect.right - rect.left),//幅
		(rect.bottom - rect.top),//高さ
		NULL,//親
		NULL,//メニューID
		hInstance,//インスタンスハンドル
		NULL//作成データ
	);
	// ウィンドウのアイコンを設定
	SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)));
	SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)));

	g_hInstance = hInstance;
	g_hWnd = hWnd;

	while (ShowCursor(FALSE) >= 0);
	ConfineCursorToWindow(hWnd);

	//表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

#ifdef _DEBUG

	if (FAILED(Init(hInstance, hWnd, TRUE)))//初期化処理
	{
		return E_FAIL;
	}

#endif

#ifndef _DEBUG

	if (FAILED(Init(hInstance, hWnd, FALSE)))//初期化処理
	{
		return E_FAIL;
	}

#endif

	timeBeginPeriod(1);//分解能の設定
	dwCurrntTime = 0;//初期時間
	dwExceLastTime = timeGetTime();//開始時刻を記録

	DWORD dwFrameCount;
	DWORD dwFPSLastTime;

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			if (msg.message == WM_QUIT)//終了メッセージ
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (!g_bStop)
			{
				dwCurrntTime = timeGetTime();//時刻を取得
				if ((dwCurrntTime-dwFPSLastTime)>=FPS_TIME)
				{//0.5秒
					//FPS算出
					g_nCountFPS = (dwFrameCount * 1000) / (dwCurrntTime - dwFPSLastTime);
					dwFPSLastTime = dwCurrntTime;
					dwFrameCount = 0;
				}

				if ((dwCurrntTime - dwExceLastTime) >= FPS)//設定した間隔が空いたら
				{//60分の1
					dwExceLastTime = dwCurrntTime;//今回の更新時刻を記録

					Update();//更新処理
					Draw();//描画処理

					dwFrameCount++;
				}
			}
		}
	}

	Uninit();//終了処理

	//ウインドウクラスの登録解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	timeEndPeriod(1);//分解能を戻す

	ReleaseCursor();
	while (ShowCursor(TRUE) < 0);

	//終了
	return (int)msg.wParam;
}

//--------------------------
//ウインドウプロシージャ
//--------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID = 0;//返り値の格納
	static bool bFreeMause=false;

	switch (uMsg)
	{
	case WM_DESTROY://破棄
		//WM_QUITメッセージ
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN://キー押下
		switch (wParam)
		{
		case VK_ESCAPE://ESCキー
			ReleaseCursor();
			while (ShowCursor(TRUE) < 0);
			nID = MessageBox(hWnd, "終了しますか?", "終了メッセージ....だよね??...たぶん...............おそらく...............", MB_YESNO | MB_ICONQUESTION);
			if (nID == IDYES)
			{
				//破棄(WM_DESTROY)
				DestroyWindow(hWnd);
			}
			else
			{
				while (ShowCursor(FALSE) >= 0);
				ConfineCursorToWindow(hWnd);
			}
			break;
		case VK_F2:
			g_bDebug = !g_bDebug;
			break;
		case VK_F4:
			if (bFreeMause)
			{
				bFreeMause = false;

				while (ShowCursor(FALSE) >= 0);
				ConfineCursorToWindow(hWnd);
			}
			else
			{
				bFreeMause = true;

				ReleaseCursor();
				while (ShowCursor(TRUE) < 0);
			}
			break;
		case VK_F5:
			CrCursor(!GetCursorIn()->bUse);
			break;
		}
		break;
	case WM_SETFOCUS:
		g_bStop = false;
		ConfineCursorToWindow(hWnd);
		break;
	case WM_KILLFOCUS:
		g_bStop = true;
		break;
	}
	//必要データを返す
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//------------------------------
//初期化処理
//------------------------------
HRESULT Init(HINSTANCE hInstanse, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;//ダイレクトXディスプレイモードの変数宣言
	D3DPRESENT_PARAMETERS d3dpp;//ダイレクトXパラメータの変数宣言

	//オブジェクト生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//ディスプレイモード
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	ZeroMemory(&d3dpp, sizeof(d3dpp));//0を敷き詰める

	//バックバッファの設定
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//デバイス生成
	if (FAILED(g_pD3D->CreateDevice
	(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice
	)))
	{
		if (FAILED(g_pD3D->CreateDevice
		(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice
		)))
		{
			if (FAILED(g_pD3D->CreateDevice
			(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice
			)))
			{
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//カリング
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);//透明度
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//デバッグ用フォント生成
	D3DXCreateFont
	(
	    g_pD3DDevice,
		FONT_SIZE, 0,0,0,
		FALSE,SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,
		"Terminal",
		&g_pFont
	);

	//オブジェクトの初期化処理
	if (FAILED(InitKeyboard(hInstanse, hWnd)))//キー入力
	{
		return E_FAIL;
	}
	if (FAILED(InitMouse(hInstanse, hWnd)))//キー入力
	{
		return E_FAIL;
	}
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}
	if (FAILED(InitdJoypad(hInstanse, hWnd)))//キー入力
	{
		return E_FAIL;
	}
	InitSound(hWnd);
	InitLight();
	InitCamera();
	InitCursor();
	InitPause();

	InitFade(g_mode);

	return S_OK;
}

//------------------------------
//終了処理
//------------------------------
void Uninit(void)
{
	EndSound();

	UninitPause();
	UninitCursor();
	UninitSound();
	UninitCamera();
	UninitLight();
	UninitFade();

	//現在の画面の終了処理
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;
	case MODE_GAME:
		UninitGame();
		break;
	case MODE_RESULT:
		UninitResult();
		break;
	case MODE_RANK:
		UninitRank();
		break;
	}

	UninitdJoypad();//dパッド入力
	UninitJoypad();//パッド入力
	UninitMouse();//マウス入力
	UninitKeyborad();//キー入力

	//デバッグフォント破棄
	if (g_pFont!=NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//デバイス破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//オブジェクト破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//------------------------------
//更新処理
//------------------------------
void Update(void)
{
	UpdateKeyborad();//キー入力
	UpdateMouse();//マウス入力
	UpdateJoypad();//パッド入力
	UpdatedJoypad();//dパッド入力

	UpdateFade();
	UpdateCursor();
	UpdateLight();
	UpdatePause();
	UpdateCamera();

	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;
	case MODE_GAME:
		UpdateGame();
		break;
	case MODE_RESULT:
		UpdateResult();
		break;
	case MODE_RANK:
		UpdateRank();
		break;
	}
}

//------------------------------
//描画処理
//------------------------------
void Draw(void)
{
	g_pD3DDevice->Clear//フロントバッファのクリア
	(
		0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0
	);

	if (SUCCEEDED(g_pD3DDevice->BeginScene()))//描画開始
	{
		SetCamera();

		//オブジェクト描画
		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;
		case MODE_GAME:
			DrawGame();
			break;
		case MODE_RESULT:
			DrawResult();
			break;
		case MODE_RANK:
			DrawRank();
			break;
		}

		DrawPause();
		DrawCursor();
		DrawFade();


#ifdef _DEBUG

		if (g_bDebug)
		{
			DrawDebug();
		}

#endif

		g_pD3DDevice->EndScene();//描画終了
	}
	//バックバッファに表示を切り替える
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//------------------------
//モードの切り替え
//------------------------
void SetMode(MODE mode)
{
	//現在の画面の終了処理
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;
	case MODE_GAME:
		UninitGame();
		break;
	case MODE_RESULT:
		UninitResult();
		break;
	case MODE_RANK:
		UninitRank();
		break;
	}

	g_mode = mode;

	//新しい画面の初期化処理
	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;
	case MODE_GAME:
		InitGame();
		break;
	case MODE_RESULT:
		InitResult();
		break;
	case MODE_RANK:
		InitRank();
		break;
	}
}

//------------------------
//デバイスの取得
//------------------------
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//-----------------
//モードの取得
//-----------------
MODE GetMode(void)
{
	return g_mode;
}

//-----------------
//ハンドルの取得
//-----------------
HWND GethWnd(void)
{
	return g_hWnd;
}

//-----------------
//インスタンスハンドル取得
//-----------------
HINSTANCE GethInstanse(void)
{
	return g_hInstance;
}

//------------------
//マウス制限
//------------------
void ConfineCursorToWindow(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);

	rect.left += 10;
	rect.top += 10;
	rect.right -= 10;
	rect.bottom -= 10;

	MapWindowPoints(hWnd, NULL, (POINT*)&rect, 2);
	ClipCursor(&rect);
}

//-----------------
//マウス解放
//-----------------
void ReleaseCursor(void)
{
	ClipCursor(NULL); // 制限を解除
}

//--------------------
//
//デバッグ用
//
//--------------------

//--------------------
//デバッグ表示
//--------------------
void DrawDebug(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[1024] = { '\0' };
	float LightAngle = GetLightAngle();
	Camera* pCamera = GetCamera();
	Player* pPlayer = GetPlayer();

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "FPS:%d\n", g_nCountFPS);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "ライトアングル:%f\n", LightAngle);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "カメラアングルY:%f\n", pCamera->rot.y);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "カメラアングルX:%f\n", pCamera->rot.x);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "視点:%f %f %f\n", pCamera->posV.x, pCamera->posV.y, pCamera->posV.z);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "目標視点:%f %f %f\n", pCamera->posVDest.x, pCamera->posVDest.y, pCamera->posVDest.z);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "注視点:%f %f %f\n", pCamera->posR.x, pCamera->posR.y, pCamera->posR.z);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "目標注視点:%f %f %f\n", pCamera->posRDest.x, pCamera->posRDest.y, pCamera->posRDest.z);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "距離:%f\n", pCamera->fDistance);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "プレイヤー位置:%f %f %f\n", pPlayer->pos.x, pPlayer->pos.y, pPlayer->pos.z);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "プレイヤー過去位置:%f %f %f\n", pPlayer->posOld.x, pPlayer->posOld.y, pPlayer->posOld.z);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "プレイヤー移動:%f %f %f\n", pPlayer->move.x, pPlayer->move.y, pPlayer->move.z);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "プレイヤー回転:%f %f %f\n", pPlayer->rot.x, pPlayer->rot.y, pPlayer->rot.z);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "プレイヤー回転目標:%f %f %f\n", pPlayer->Destrot.x, pPlayer->Destrot.y, pPlayer->Destrot.z);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "プレイヤースケール:%f %f %f\n", pPlayer->scale.x, pPlayer->scale.y, pPlayer->scale.z);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "プレイヤー体力:%d\n", pPlayer->nLife);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "プレイヤー状態:%d\n", pPlayer->state);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "プレイヤー最大頂点:%f %f %f\n", pPlayer->aModel[0].vtxMax.x, pPlayer->aModel[0].vtxMax.y, pPlayer->aModel[0].vtxMax.z);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "プレイヤー最小頂点:%f %f %f\n", pPlayer->aModel[0].vtxMin.x, pPlayer->aModel[0].vtxMin.y, pPlayer->aModel[0].vtxMin.z);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "影:%d\n", pPlayer->nIdxShadow);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "頂点数:%d\n", pPlayer->aModel[0].nNumVtx);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "モーションループ:%s\n", pPlayer->bLoopMotion ? "true" : "false");

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "モーションタイプ:%d\n", pPlayer->motionType);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "モーション数:%d\n", pPlayer->nNumMotion);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "キー数:%d\n", pPlayer->nNumKey);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "キー番号:%d\n", pPlayer->nKey);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;

	//文字列の代入
	snprintf(&aStr[0], sizeof(aStr), "モーションカウント:%d\n", pPlayer->nCounterMotion);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	rect.top += FONT_SIZE;
}