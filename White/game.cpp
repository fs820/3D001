//------------------------------------------
//
//�Q�[�����C���̏���[game.cpp]
//Author fuma sato
//
//------------------------------------------

#include"game.h"
#include"input.h"
#include"player.h"
#include"ground.h"
#include"wall.h"
#include"shadow.h"
#include"billboard.h"
#include"bullet.h"
#include"explosion.h"
#include"effect.h"
#include"particle.h"
#include"stage.h"
#include"file.h"
#include"meshfield.h"
#include"cylinder.h"
#include"sphere.h"
#include"model.h"
#include"meshwall.h"
#include"line.h"
#include"snowball.h"

#define SELECT_WIDTH (512)
#define SELECT_HEIGHT (128)

typedef enum
{
	SELECT_RESTART = 0,
	SELECT_RETRY,
	SELECT_BACK,
	SELECT_EXIT,
	SELECT_MAX,
}SELECT;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureGame[SELECT_MAX] = { NULL };//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGame = NULL;//�o�b�t�@�̃|�C���^
GAMESTATE g_gameState = GAMESTATE_NONE;
int g_nCounterGameState = 0;
int g_BossNumber = 0;//�ǂ̃{�X��
bool g_bClear = false;

//--------------------
//����������
//--------------------
void InitGame(void)
{
	InitModel();
	InitShadow();
	InitStage();
	InitGround();
	InitMeshField();
	InitLine();
	InitCylinder();
	InitSphere();
	InitSnowBall();
	InitWall();
	InitMeshWall();
	InitPlayer();//�v���C���[
	InitBullet();
	InitExplosion();
	InitEffect();
	InitParticle();
	InitBillboard();

	//���
	SetMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetCylinder(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetSphere(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//��
	SetSnowBall(D3DXVECTOR3(0.0f, SNOWBALL_RADIUS, 1500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	//�X�e�[�W
	LoadStage();

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	VERTEX_2D* pVtx;//���_���|�C���^
	D3DXVECTOR3 posSelect;//�X�R�A�̈ʒu

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�o�b�t�@�[�̐ݒ�
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * VT_MAX * SELECT_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGame,
		NULL
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		0,
		&g_apTextureGame[0]
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		0,
		&g_apTextureGame[1]
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		0,
		&g_apTextureGame[2]
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		0,
		&g_apTextureGame[3]
	);


	g_gameState = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
	posSelect = D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2-SELECT_HEIGHT*1.5f,0.0f);
	g_bClear = false;

	g_pVtxBuffGame->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

	for (int i = 0; i < SELECT_MAX; i++)
	{
		//���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(posSelect.x - SELECT_WIDTH / 2, posSelect.y - SELECT_HEIGHT / 2 + i * SELECT_HEIGHT, posSelect.z);
		pVtx[1].pos = D3DXVECTOR3(posSelect.x + SELECT_WIDTH / 2, posSelect.y - SELECT_HEIGHT / 2 + i * SELECT_HEIGHT, posSelect.z);
		pVtx[2].pos = D3DXVECTOR3(posSelect.x - SELECT_WIDTH / 2, posSelect.y + SELECT_HEIGHT / 2 + i * SELECT_HEIGHT, posSelect.z);
		pVtx[3].pos = D3DXVECTOR3(posSelect.x + SELECT_WIDTH / 2, posSelect.y + SELECT_HEIGHT / 2 + i * SELECT_HEIGHT, posSelect.z);

		//rhw
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`��
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += VT_MAX;

	}

	g_pVtxBuffGame->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N
}

//------------------
//�I������
//------------------
void UninitGame(void)
{
	g_gameState = GAMESTATE_NONE;

	UninitParticle();
	UninitEffect();
	UninitExplosion();
	UninitBullet();
	UninitBillboard();
	UninitMeshWall();
	UninitWall();
	UninitCylinder();
	UninitSnowBall();
	UninitSphere();
	UninitLine();
	UninitGround();
	UninitMeshField();
	UninitPlayer();//�v���C���[
	UninitStage();
	UninitShadow();
	UninitModel();
}

//--------------
//�X�V����
//--------------
void UpdateGame(void)
{
	UpdateModel();
	UpdateShadow();
	UpdateStage();
	UpdateGround();
	UpdatePlayer();//�v���C���[
	UpdateWall();
	UpdateMeshWall();
	UpdateMeshField();
	UpdateLine();
	UpdateCylinder();
	UpdateSphere();
	UpdateSnowBall();
	UpdateBillboard();
	UpdateBullet();
	UpdateExplosion();
	UpdateEffect();
	UpdateParticle();
}

//-------------------
//�`�揈��
//-------------------
void DrawGame(void)
{
	DrawModel();
	DrawLine();
	DrawGround();
	DrawMeshField();
	DrawWall();
	DrawCylinder();
	DrawSphere();
	DrawShadow();
	DrawStage();
	DrawMeshWall();
	DrawBillboard();
	DrawEffect();
	DrawBullet();
	DrawExplosion();
	DrawSnowBall();
	DrawPlayer();//�v���C���[
	DrawAlphaWall();

	if(g_gameState==GAMESTATE_PAUSE)
	{
		LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^

        //�f�o�C�X�̎擾
		pDevice = GetDevice();

		//���_�o�b�t�@
		pDevice->SetStreamSource(0, g_pVtxBuffGame, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		for (int i = 0; i < SELECT_MAX; i++)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureGame[i]);

			//�w�i�̕`��
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,//�^�C�v
				i*VT_MAX,//�n�܂�̔ԍ�
				2//�|���S���̌�
			);
		}
	}
}

//----------------------
//�Q�[����Ԑؑ�
//----------------------
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//-----------------------
//�Q�[����Ԏ擾
//-----------------------
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//---------------------------
//�ǂ̃{�X��
//---------------------------
void SetBossNumber(int Boss)
{
	g_BossNumber = Boss;
}

//---------------------------
//�{�X�擾	
//---------------------------
int GetBossNumber(void)
{
	return g_BossNumber;
}

//---------------------
//�N���A�擾
//---------------------
bool GetClear(void)
{
	return g_bClear;
}