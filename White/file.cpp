//---------------------------------------
//
//セーブ・ロード処理[file.cpp]
//Author fuma sato
//
//---------------------------------------

#include"file.h"
#include"stage.h"
#include"meshwall.h"
#include"line.h"
#include"billboard.h"
#include"player.h"

//------------------
//ソート関数
//------------------
int *Soat(int* pData)
{
	//変数を宣言
	int nRam = 0;

	for (int i = 0; i < MAX_DATA; i++)
	{//比較対象1
		for (int i2 = i + 1; i2 < MAX_DATA+1; i2++)
		{//比較対象2
			if (pData[i] < pData[i2])
			{
				//大きいほうに入れ替える
				nRam = pData[i];
				pData[i] = pData[i2];
				pData[i2] = nRam;
			}
		}
	}
	return &pData[0];
}
//---------------------------------------
//セーブ処理
//---------------------------------------
void SaveFile(int* pData)
{
	FILE* pFile;//ファイルポインタを宣言

	pFile = fopen(DATA_FILE, "wb");//ファイルを開く
	if (pFile != NULL)
	{//開けたら
		fwrite(pData, sizeof(int), MAX_DATA,pFile);//数値を書き入れ

		fclose(pFile);//ファイルを閉じる
	}
	else
	{//開けなかった
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "セーブエラー", "セーブできなかったよ", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}
}

//---------------------------------------
//ロード処理
//---------------------------------------
int *LoadFile(void)
{
	FILE* pFile;//ファイルポインタを宣言
	static int aData[MAX_DATA] = { 0 };

	for (int i = 0; i < MAX_DATA; i++)
	{
		aData[i] = 0;
	}

	pFile = fopen(DATA_FILE, "rb");//ファイルを開く
	if (pFile != NULL)
	{//開けたら
		fread(&aData[0], sizeof(int), MAX_DATA, pFile);//数値を書き入れ

		fclose(pFile);//ファイルを閉じる
		return &aData[0];
	}
	else
	{//開けなかった
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "ロードエラー", "ロードできなかったよ", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
		return &aData[0];
	}
}

//---------------------------------------
//ロード処理
//---------------------------------------
void LoadStage(void)
{
	FILE* pFile;//ファイルポインタを宣言
	int nCount = 0;
	char name[64] = { "\0" };
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f), scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//Xファイル
	pFile = fopen(STAGE_FILE, "r");//ファイルを開く
	if (pFile != NULL)
	{//開けたら
		for (nCount = 0; nCount < STAGE_MAX; nCount++)
		{
			if (fscanf(pFile, "%63s", name) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &pos.x) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &pos.y) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &pos.z) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &rot.x) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &rot.y) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &rot.z) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &scale.x) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &scale.y) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &scale.z) == EOF)break;//数値を書き入れ

			//角度変換
			rot = D3DXToRadian(rot);
			//オブジェクト設置
			SetStage(name, pos, rot, scale);
		}
		fclose(pFile);//ファイルを閉じる
	}
	else
	{//開けなかった
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "ロードエラー", "ロードできなかったよ", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}

	//壁
	pFile = fopen(WALL_FILE, "r");//ファイルを開く
	if (pFile != NULL)
	{//開けたら
		for (nCount = 0; nCount < MESHWALL_MAX; nCount++)
		{
			if (fscanf(pFile, "%f", &pos.x) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &pos.y) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &pos.z) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &rot.x) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &rot.y) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &rot.z) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &scale.x) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &scale.y) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &scale.z) == EOF)break;//数値を書き入れ

			//角度変換
			rot = D3DXToRadian(rot);
			//オブジェクト設置
			SetMeshWall(pos, rot, scale);
		}
		fclose(pFile);//ファイルを閉じる
	}
	else
	{//開けなかった
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "ロードエラー", "ロードできなかったよ", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}

	//線
	pFile = fopen(LINE_FILE, "r");//ファイルを開く
	if (pFile != NULL)
	{//開けたら
		for (nCount = 0; nCount < LINE_MAX; nCount++)
		{
			if (fscanf(pFile, "%f", &pos.x) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &pos.y) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &pos.z) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &rot.x) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &rot.y) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &rot.z) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &scale.x) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &scale.y) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &scale.z) == EOF)break;//数値を書き入れ

			//角度変換
			rot = D3DXToRadian(rot);
			//オブジェクト設置
			SetLine(pos, rot, scale);
		}
		fclose(pFile);//ファイルを閉じる
	}
	else
	{//開けなかった
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "ロードエラー", "ロードできなかったよ", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}

	//ビルボード
	pFile = fopen(BILL_FILE, "r");//ファイルを開く
	if (pFile != NULL)
	{//開けたら
		for (nCount = 0; nCount < BILLBOARD_MAX; nCount++)
		{
			if (fscanf(pFile, "%f", &pos.x) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &pos.y) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &pos.z) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &scale.x) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &scale.y) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &scale.z) == EOF)break;//数値を書き入れ

			//オブジェクト設置
			SetBillboard(pos, scale);
		}
		fclose(pFile);//ファイルを閉じる
	}
	else
	{//開けなかった
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "ロードエラー", "ロードできなかったよ", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}
}

//----------------------------
//
//----------------------------
void LoadModel(void)
{
	FILE* pFile;//ファイルポインタを宣言
	int nCount = 0;
	char name[64] = { "\0" };
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f), scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pFile = fopen(MODEL_FILE, "r");//ファイルを開く
	if (pFile != NULL)
	{//開けたら
		for (nCount = 0; nCount < MAX_MODEL; nCount++)
		{
			if (fscanf(pFile, "%63s", name) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &pos.x) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &pos.y) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &pos.z) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &rot.x) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &rot.y) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &rot.z) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &scale.x) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &scale.y) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &scale.z) == EOF)break;//数値を書き入れ

			//角度変換
			rot = D3DXToRadian(rot);
		}
		fclose(pFile);//ファイルを閉じる
	}
	else
	{//開けなかった
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "ロードエラー", "ロードできなかったよ", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}
}