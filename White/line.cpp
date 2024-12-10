//----------------------------------------
//
//�|���S���\������[line.cpp]
//Author fuma sato
//
//----------------------------------------

#include"line.h"
#include"player.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLine = NULL;//�o�b�t�@�̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffLine = NULL;//�C���f�b�N�X�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureLine = NULL;
Line g_aLine[LINE_MAX];

//----------------------
//�|���S���̏���������
//----------------------
void InitLine(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	VERTEX_3D* pVtx;//���_���|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * VT_MAX_LINE * LINE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLine,
		NULL
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		LINE_TEX,
		&g_pTextureLine
	);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * INDEX_NUM_LINE * LINE_MAX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffLine,
		NULL
	);

	int nCntLine, nCntLine2, nCntLine3;
	for (nCntLine = 0; nCntLine < LINE_MAX; nCntLine++)
	{
		g_aLine[nCntLine].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLine[nCntLine].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLine[nCntLine].bUse = false;
	}
	//1��


	g_pVtxBuffLine->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLine = 0; nCntLine < LINE_MAX; nCntLine++)
	{//���b�V���t�B�[���h��
		for (nCntLine2 = 0; nCntLine2 < LINE_ZNUM + 1; nCntLine2++)
		{//1������Z���̃��[�v
			for (nCntLine3 = 0; nCntLine3 < LINE_XNUM + 1; nCntLine3++)
			{//1������X���̃��[�v
				//���W�ݒ�
				pVtx[nCntLine2 * (LINE_XNUM + 1) + nCntLine3].pos = D3DXVECTOR3(g_aLine[nCntLine].pos.x - LINE_WIDTH * 0.5f + (LINE_WIDTH / LINE_XNUM) * nCntLine3, g_aLine[nCntLine].pos.y + LINE_HEIGHT, g_aLine[nCntLine].pos.z + LINE_Z * 0.5f - (LINE_Z / LINE_ZNUM) * nCntLine2);

				//nor
				pVtx[nCntLine2 * (LINE_XNUM + 1) + nCntLine3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				//�J���[
				pVtx[nCntLine2 * (LINE_XNUM + 1) + nCntLine3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//�e�N�X�`��
				pVtx[nCntLine2 * (LINE_XNUM + 1) + nCntLine3].tex = D3DXVECTOR2(((LINE_WIDTH / LINE_WIDTH_DEF) / LINE_XNUM) * nCntLine3, ((LINE_Z / LINE_Z_DEF) / LINE_ZNUM) * nCntLine2);
			}
		}
		pVtx += VT_MAX_LINE;
	}

	g_pVtxBuffLine->Unlock();

	WORD* pIdx;
	g_pIdxBuffLine->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntLine = 0; nCntLine < LINE_MAX; nCntLine++)
	{
		for (nCntLine2 = 0; nCntLine2 < INDEX_NUM_LINE - (LINE_ZNUM - 1) * 2; nCntLine2++)
		{
			if (nCntLine2 % ((LINE_XNUM + 1) * 2) == 0 && nCntLine2 != 0)
			{
				//�C���f�b�N�X�w��
				pIdx[nCntLine2 - 2 + ((nCntLine2 / ((LINE_XNUM + 1) * 2)) * 2)] = (LINE_XNUM + 1) - (LINE_XNUM + 1) * ((nCntLine2 - 1) % 2) + ((nCntLine2 - 1) / 2);
				//�C���f�b�N�X�w��
				pIdx[nCntLine2 - 1 + ((nCntLine2 / ((LINE_XNUM + 1) * 2)) * 2)] = (LINE_XNUM + 1) - (LINE_XNUM + 1) * (nCntLine2 % 2) + (nCntLine2 / 2);
			}

			//�C���f�b�N�X�w��
			pIdx[nCntLine2 + ((nCntLine2 / ((LINE_XNUM + 1) * 2)) * 2)] = (LINE_XNUM + 1) - (LINE_XNUM + 1) * (nCntLine2 % 2) + (nCntLine2 / 2);
		}
		pIdx += INDEX_NUM_LINE;
	}

	g_pIdxBuffLine->Unlock();
}

//-------------------
//�|���S���I������
//-------------------
void UninitLine(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureLine != NULL)
	{
		g_pTextureLine->Release();
		g_pTextureLine = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffLine != NULL)
	{
		g_pVtxBuffLine->Release();
		g_pVtxBuffLine = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffLine != NULL)
	{
		g_pIdxBuffLine->Release();
		g_pIdxBuffLine = NULL;
	}
}

//-------------------
//�|���S���X�V����
//-------------------
void UpdateLine(void)
{
	HitLine();
}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawLine(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxScale, mtxRot, mtxTrans;//�v�Z�}�g���b�N�X

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	int nCntLine;
	for (nCntLine = 0; nCntLine < LINE_MAX; nCntLine++)
	{
		if (g_aLine[nCntLine].bUse)
		{
			//�}�g���b�N�X������
			D3DXMatrixIdentity(&g_aLine[nCntLine].mtxWorld);

			//�傫���̔��f
			D3DXMatrixScaling(&mtxScale, g_aLine[nCntLine].scale.x, g_aLine[nCntLine].scale.y, g_aLine[nCntLine].scale.z);
			D3DXMatrixMultiply(&g_aLine[nCntLine].mtxWorld, &g_aLine[nCntLine].mtxWorld, &mtxScale);

			//�����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aLine[nCntLine].rot.y, g_aLine[nCntLine].rot.x, g_aLine[nCntLine].rot.z);
			D3DXMatrixMultiply(&g_aLine[nCntLine].mtxWorld, &g_aLine[nCntLine].mtxWorld, &mtxRot);

			//�ʒu�̌v�Z
			D3DXMatrixTranslation(&mtxTrans, g_aLine[nCntLine].pos.x, g_aLine[nCntLine].pos.y, g_aLine[nCntLine].pos.z);
			D3DXMatrixMultiply(&g_aLine[nCntLine].mtxWorld, &g_aLine[nCntLine].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aLine[nCntLine].mtxWorld);

			//���_�o�b�t�@
			pDevice->SetStreamSource(0, g_pVtxBuffLine, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffLine);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureLine);

			//�|���S���̕`��
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLESTRIP,//�^�C�v
				0,
				0,
				VT_MAX_LINE,//���_��
				nCntLine * INDEX_NUM_LINE,
				POLYGON_NUM_LINE//�|���S���̌�
			);
		}
	}
}

//----------
//�ݒ�
//----------
void SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale)
{
	int nCntLine;
	for (nCntLine = 0; nCntLine < LINE_MAX; nCntLine++)
	{
		if (!g_aLine[nCntLine].bUse)
		{
			g_aLine[nCntLine].pos = pos;
			g_aLine[nCntLine].rot = rot;
			g_aLine[nCntLine].scale = scale;
			g_aLine[nCntLine].bUse = true;
			break;
		}
	}
}

//----------------------
//�����蔻��
//----------------------
void HitLine(void)
{
	Player* pPlayer = GetPlayer();
	D3DXVECTOR3 aPos[4] = {}, Fieldvec = {}, Posvec = {};
	int nCntLine;
	for (nCntLine = 0; nCntLine < LINE_MAX; nCntLine++)
	{//�n�ʂ̐�
		if (g_aLine[nCntLine].bUse)
		{//�g���Ă����
			aPos[0] = D3DXVECTOR3(g_aLine[nCntLine].pos.x + LINE_WIDTH * 0.5f * g_aLine[nCntLine].scale.x * sinf(g_aLine[nCntLine].rot.y + D3DX_PI * -0.5f), g_aLine[nCntLine].pos.y, g_aLine[nCntLine].pos.z + LINE_Z * 0.5f * g_aLine[nCntLine].scale.z * cosf(g_aLine[nCntLine].rot.y + D3DX_PI * -0.5f));
			aPos[1] = D3DXVECTOR3(g_aLine[nCntLine].pos.x + LINE_WIDTH * 0.5f * g_aLine[nCntLine].scale.x * sinf(g_aLine[nCntLine].rot.y + D3DX_PI * 0.5f), g_aLine[nCntLine].pos.y, g_aLine[nCntLine].pos.z + LINE_Z * 0.5f * g_aLine[nCntLine].scale.z * cosf(g_aLine[nCntLine].rot.y + D3DX_PI * 0.5f));
			aPos[2] = D3DXVECTOR3(g_aLine[nCntLine].pos.x + LINE_WIDTH * 0.5f * g_aLine[nCntLine].scale.x * sinf(g_aLine[nCntLine].rot.y + D3DX_PI * 0.5f), g_aLine[nCntLine].pos.y, g_aLine[nCntLine].pos.z + LINE_Z * 0.5f * g_aLine[nCntLine].scale.z * cosf(g_aLine[nCntLine].rot.y + D3DX_PI * 0.5f));
			aPos[3] = D3DXVECTOR3(g_aLine[nCntLine].pos.x + LINE_WIDTH * 0.5f * g_aLine[nCntLine].scale.x * sinf(g_aLine[nCntLine].rot.y + D3DX_PI * -0.5f), g_aLine[nCntLine].pos.y, g_aLine[nCntLine].pos.z + LINE_Z * 0.5f * g_aLine[nCntLine].scale.z * cosf(g_aLine[nCntLine].rot.y + D3DX_PI * -0.5f));
			Fieldvec = aPos[1] - aPos[0];//�ǂ̃x�N�g��
			Posvec = pPlayer->pos - aPos[0];//�ǂɑ΂���v���C���[�̃x�N�g��
			if ((Fieldvec.z * Posvec.x) - (Fieldvec.x * Posvec.z) >= 0.0f && !pPlayer->bJump)
			{//����
				Fieldvec = aPos[2] - aPos[1];//�ǂ̃x�N�g��
				Posvec = pPlayer->pos - aPos[1];//�ǂɑ΂���v���C���[�̃x�N�g��
				if ((Fieldvec.z * Posvec.x) - (Fieldvec.x * Posvec.z) >= 0.0f && !pPlayer->bJump)
				{//����
					Fieldvec = aPos[3] - aPos[2];//�ǂ̃x�N�g��
					Posvec = pPlayer->pos - aPos[2];//�ǂɑ΂���v���C���[�̃x�N�g��
					if ((Fieldvec.z * Posvec.x) - (Fieldvec.x * Posvec.z) >= 0.0f && !pPlayer->bJump)
					{//����
						Fieldvec = aPos[0] - aPos[3];//�ǂ̃x�N�g��
						Posvec = pPlayer->pos - aPos[3];//�ǂɑ΂���v���C���[�̃x�N�g��
						if ((Fieldvec.z * Posvec.x) - (Fieldvec.x * Posvec.z) >= 0.0f && !pPlayer->bJump)
						{//����
							pPlayer->aModel[1].rot.x++;
						}
					}
				}
			}
		}
	}
}