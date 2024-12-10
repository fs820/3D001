//----------------------------------------
//
//�|���S���\������[sphere.cpp]
//Author fuma sato
//
//----------------------------------------

#include"sphere.h"
#include"camera.h"
#include"effect.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSphere = NULL;//�o�b�t�@�̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSphere = NULL;//�C���f�b�N�X�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureSphere[2] = { NULL };
Sphere g_aSphere[SPHERE_MAX];

//----------------------
//�|���S���̏���������
//----------------------
void InitSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	VERTEX_3D* pVtx;//���_���|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * VT_MAX_SP * SPHERE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSphere,
		NULL
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		SPHERE_TEX,
		&g_pTextureSphere[0]
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		SPHERE_TEX2,
		&g_pTextureSphere[1]
	);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * INDEX_SP_NUM * SPHERE_MAX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSphere,
		NULL
	);

	int nCntSphere, nCntSphere2, nCntSphere3;
	for (nCntSphere = 0; nCntSphere < SPHERE_MAX; nCntSphere++)
	{
		g_aSphere[nCntSphere].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSphere[nCntSphere].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSphere[nCntSphere].bUse = false;
	}
	//1��

	g_pVtxBuffSphere->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntSphere = 0; nCntSphere < SPHERE_MAX; nCntSphere++)
	{//���̐�

		//�ɒ��_
		pVtx[0].pos = D3DXVECTOR3(g_aSphere[nCntSphere].pos.x, g_aSphere[nCntSphere].pos.y + SPHERE_RADIUS, g_aSphere[nCntSphere].pos.z);

		D3DXVECTOR3 npos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), dpos = D3DXVECTOR3(g_aSphere[nCntSphere].pos.x, g_aSphere[nCntSphere].pos.y + SPHERE_RADIUS, g_aSphere[nCntSphere].pos.z);
		D3DXVec3Normalize(&npos, &dpos);
		pVtx[0].nor = -npos;

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

		pVtx[0].tex = D3DXVECTOR2((float)(((((SPHERE_RADIUS + SPHERE_RADIUS) * D3DX_PI) / SPHERE_WIDTH_DEF) / SPHERE_HNUM)), (float)((((SPHERE_RADIUS + SPHERE_RADIUS) * D3DX_PI * 0.5f) / SPHERE_HEIGHT_DEF) / SPHERE_VNUM));

		for (nCntSphere2 = 0; nCntSphere2 < SPHERE_VNUM/* - 1*/; nCntSphere2++)
		{//1������Z���̃��[�v
			for (nCntSphere3 = 0; nCntSphere3 < SPHERE_HNUM + 1; nCntSphere3++)
			{//1������X���̃��[�v

				//�~�`�̊p�x
				float fangleH = (360.0f / SPHERE_HNUM) * nCntSphere3 * (D3DX_PI / 180.0f), fangleV = (SPHERE_ANG / SPHERE_VNUM) * (nCntSphere2 + 1) * (D3DX_PI / 180.0f);

				//���W�ݒ�
				pVtx[nCntSphere2 * (SPHERE_HNUM + 1) + nCntSphere3 + 1].pos = D3DXVECTOR3(g_aSphere[nCntSphere].pos.x + sinf(fangleH) * sinf(fangleV) * SPHERE_RADIUS, g_aSphere[nCntSphere].pos.y + cosf(fangleV) * SPHERE_RADIUS, g_aSphere[nCntSphere].pos.z + cosf(fangleH) * sinf(fangleV) * SPHERE_RADIUS);

				//nor
				D3DXVECTOR3 npos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), dpos = D3DXVECTOR3(g_aSphere[nCntSphere].pos.x + sinf(fangleH) * sinf(fangleV) * SPHERE_RADIUS, g_aSphere[nCntSphere].pos.y + cosf(fangleV) * SPHERE_RADIUS, g_aSphere[nCntSphere].pos.z + cosf(fangleH) * sinf(fangleV) * SPHERE_RADIUS);
				D3DXVec3Normalize(&npos, &dpos);
				pVtx[nCntSphere2 * (SPHERE_HNUM + 1) + nCntSphere3 + 1].nor = -npos;

				//�J���[
				pVtx[nCntSphere2 * (SPHERE_HNUM + 1) + nCntSphere3 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

				//�e�N�X�`��
				pVtx[nCntSphere2 * (SPHERE_HNUM + 1) + nCntSphere3 + 1].tex = D3DXVECTOR2((float)(((((SPHERE_RADIUS + SPHERE_RADIUS) * D3DX_PI) / SPHERE_WIDTH_DEF) / SPHERE_HNUM) * nCntSphere3), (float)((((SPHERE_RADIUS + SPHERE_RADIUS) * D3DX_PI * 0.5f) / SPHERE_HEIGHT_DEF) / SPHERE_VNUM) * nCntSphere2);
			}
		}

		////�ɒ��_
		//pVtx[VT_MAX_SP - 1].pos = D3DXVECTOR3(g_aSphere[nCntSphere].pos.x, g_aSphere[nCntSphere].pos.y - SPHERE_RADIUS, g_aSphere[nCntSphere].pos.z);

		//npos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), dpos = D3DXVECTOR3(g_aSphere[nCntSphere].pos.x, g_aSphere[nCntSphere].pos.y - SPHERE_RADIUS, g_aSphere[nCntSphere].pos.z);
		//D3DXVec3Normalize(&npos, &dpos);
		//pVtx[VT_MAX_SP - 1].nor = npos;

		//pVtx[VT_MAX_SP - 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

		//pVtx[VT_MAX_SP - 1].tex = D3DXVECTOR2((float)(((((SPHERE_RADIUS + SPHERE_RADIUS) * D3DX_PI) / SPHERE_WIDTH_DEF) / SPHERE_HNUM)), (float)((((SPHERE_RADIUS + SPHERE_RADIUS) * D3DX_PI * 0.5f) / SPHERE_HEIGHT_DEF) / SPHERE_VNUM));

		pVtx += VT_MAX_SP;
	}

	g_pVtxBuffSphere->Unlock();

	WORD* pIdx;
	g_pIdxBuffSphere->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntSphere = 0; nCntSphere < SPHERE_MAX; nCntSphere++)
	{//���̐�
		pIdx[0] = 0;
		for (nCntSphere2 = 1; nCntSphere2 < SPHERE_HNUM + 2; nCntSphere2++)
		{//FAN����
			pIdx[nCntSphere2] = SPHERE_HNUM + 2 - nCntSphere2;
		}
		for (nCntSphere2 = SPHERE_HNUM + 2; nCntSphere2 < INDEX_SP_NUM - (SPHERE_VNUM - 2) * 2/* - SPHERE_HNUM*/; nCntSphere2++)
		{//STRIP����
			if ((nCntSphere2 - (SPHERE_HNUM + 2)) % (((SPHERE_HNUM + 1) * 2)) == 0 && (nCntSphere2 - (SPHERE_HNUM + 2)) != 0)
			{//�k�ރ|���S��
				//�C���f�b�N�X�w��
				pIdx[nCntSphere2 - 2 + (((nCntSphere2 - (SPHERE_HNUM + 2)) / ((SPHERE_HNUM + 1) * 2)) * 2)] = (SPHERE_HNUM + 1) - (SPHERE_HNUM + 1) * (((nCntSphere2 - (SPHERE_HNUM + 2)) - 1) % 2) + (((nCntSphere2 - (SPHERE_HNUM + 2)) - 1) / 2) + 1;

				//�C���f�b�N�X�w��
				pIdx[nCntSphere2 - 1 + (((nCntSphere2 - (SPHERE_HNUM + 2)) / ((SPHERE_HNUM + 1) * 2)) * 2)] = (SPHERE_HNUM + 1) - (SPHERE_HNUM + 1) * ((nCntSphere2 - (SPHERE_HNUM + 2)) % 2) + ((nCntSphere2 - (SPHERE_HNUM + 2)) / 2) + 1;
			}

			//�C���f�b�N�X�w��
			pIdx[nCntSphere2 + (((nCntSphere2 - (SPHERE_HNUM + 2)) / ((SPHERE_HNUM + 1) * 2)) * 2)] = (SPHERE_HNUM + 1) - (SPHERE_HNUM + 1) * ((nCntSphere2 - (SPHERE_HNUM + 2)) % 2) + ((nCntSphere2 - (SPHERE_HNUM + 2)) / 2) + 1;
		}

		//for (nCntSphere2 = 1; nCntSphere2 < SPHERE_HNUM + 2; nCntSphere2++)
		//{//FAN����
		//	pIdx[INDEX_SP_NUM - nCntSphere2] = VT_MAX_SP - (nCntSphere2 + 1);
		//}
		//pIdx[INDEX_SP_NUM - (SPHERE_HNUM + 2)] = VT_MAX_SP - 1;

		pIdx += INDEX_SP_NUM;
	}

	g_pIdxBuffSphere->Unlock();
}

//-------------------
//�|���S���I������
//-------------------
void UninitSphere(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureSphere[nCnt] != NULL)
		{
			g_pTextureSphere[nCnt]->Release();
			g_pTextureSphere[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSphere != NULL)
	{
		g_pVtxBuffSphere->Release();
		g_pVtxBuffSphere = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffSphere != NULL)
	{
		g_pIdxBuffSphere->Release();
		g_pIdxBuffSphere = NULL;
	}
}

//-------------------
//�|���S���X�V����
//-------------------
void UpdateSphere(void)
{

}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�}�g���b�N�X

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	int nCntSphere;
	for (nCntSphere = 0; nCntSphere < SPHERE_MAX; nCntSphere++)
	{
		if (g_aSphere[nCntSphere].bUse)
		{
			//�}�g���b�N�X������
			D3DXMatrixIdentity(&g_aSphere[nCntSphere].mtxWorld);

			//�����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aSphere[nCntSphere].rot.y, g_aSphere[nCntSphere].rot.x, g_aSphere[nCntSphere].rot.z);
			D3DXMatrixMultiply(&g_aSphere[nCntSphere].mtxWorld, &g_aSphere[nCntSphere].mtxWorld, &mtxRot);

			//�ʒu�̌v�Z
			D3DXMatrixTranslation(&mtxTrans, g_aSphere[nCntSphere].pos.x, g_aSphere[nCntSphere].pos.y, g_aSphere[nCntSphere].pos.z);
			D3DXMatrixMultiply(&g_aSphere[nCntSphere].mtxWorld, &g_aSphere[nCntSphere].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aSphere[nCntSphere].mtxWorld);

			//���_�o�b�t�@
			pDevice->SetStreamSource(0, g_pVtxBuffSphere, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffSphere);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureSphere[1]);

			//�Ƀ|���S���̕`��
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLEFAN,//�^�C�v
				0,
				0,
				SPHERE_HNUM + 2,//���_��
				nCntSphere * INDEX_SP_NUM,
				SPHERE_HNUM//�|���S���̌�
			);

			pDevice->SetTexture(0, g_pTextureSphere[0]);

			//�|���S���̕`��
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLESTRIP,//�^�C�v
				0,
				0,
				VT_MAX_SP - (SPHERE_HNUM + 2)/* * 2*/,//���_��
				nCntSphere * INDEX_SP_NUM + SPHERE_HNUM + 2,
				POLYGON_SP_NUM - SPHERE_HNUM/* * 2*///�|���S���̌�
			);

			//pDevice->SetTexture(0, g_pTextureSphere[1]);

			////�Ƀ|���S���̕`��
			//pDevice->DrawIndexedPrimitive
			//(
			//	D3DPT_TRIANGLEFAN,//�^�C�v
			//	0,
			//	0,
			//	SPHERE_HNUM + 2,//���_��
			//	nCntSphere * INDEX_SP_NUM + INDEX_SP_NUM - (SPHERE_HNUM + 2),
			//	SPHERE_HNUM//�|���S���̌�
			//);
		}
	}
}

//----------
//�ݒ�
//----------
void SetSphere(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntSphere;
	for (nCntSphere = 0; nCntSphere < SPHERE_MAX; nCntSphere++)
	{//���̐�
		if (!g_aSphere[nCntSphere].bUse)
		{//�g�p���Ă��Ȃ�
			//�L����
			g_aSphere[nCntSphere].pos = pos;
			g_aSphere[nCntSphere].rot = rot;
			g_aSphere[nCntSphere].bUse = true;
			break;
		}
	}
}