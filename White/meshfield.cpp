//----------------------------------------
//
//�|���S���\������[meshfield.cpp]
//Author fuma sato
//
//----------------------------------------

#include"meshfield.h"
#include"player.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;//�o�b�t�@�̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;//�C���f�b�N�X�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;
MeshField g_aMeshField[MESHFIELD_MAX];

//----------------------
//�|���S���̏���������
//----------------------
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	VERTEX_3D* pVtx;//���_���|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * VT_MAX_MESH * MESHFIELD_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		MESHFIELD_TEX,
		&g_pTextureMeshField
	);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * INDEX_NUM * MESHFIELD_MAX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL
	);

	int nCntMeshField, nCntMeshField2, nCntMeshField3;
	for (nCntMeshField = 0; nCntMeshField < MESHFIELD_MAX; nCntMeshField++)
	{
		g_aMeshField[nCntMeshField].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshField[nCntMeshField].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshField[nCntMeshField].bAlpha = false;
		g_aMeshField[nCntMeshField].bUse = false;
	}
	//1��


	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntMeshField = 0; nCntMeshField < MESHFIELD_MAX; nCntMeshField++)
	{//���b�V���t�B�[���h��
		for (nCntMeshField2 = 0; nCntMeshField2 < MESHFIELD_ZNUM + 1; nCntMeshField2++)
		{//1������Z���̃��[�v
			for (nCntMeshField3 = 0; nCntMeshField3 < MESHFIELD_XNUM + 1; nCntMeshField3++)
			{//1������X���̃��[�v
				//���W�ݒ�
				pVtx[nCntMeshField2 * (MESHFIELD_XNUM + 1) + nCntMeshField3].pos = D3DXVECTOR3(g_aMeshField[nCntMeshField].pos.x - MESHFIELD_WIDTH * 0.5f + (MESHFIELD_WIDTH / MESHFIELD_XNUM) * nCntMeshField3, g_aMeshField[nCntMeshField].pos.y + MESHFIELD_HEIGHT, g_aMeshField[nCntMeshField].pos.z + MESHFIELD_Z * 0.5f - (MESHFIELD_Z / MESHFIELD_ZNUM) * nCntMeshField2);

				//nor
				pVtx[nCntMeshField2 * (MESHFIELD_XNUM + 1) + nCntMeshField3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				//�J���[
				pVtx[nCntMeshField2 * (MESHFIELD_XNUM + 1) + nCntMeshField3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//�e�N�X�`��
				pVtx[nCntMeshField2 * (MESHFIELD_XNUM + 1) + nCntMeshField3].tex = D3DXVECTOR2(((MESHFIELD_WIDTH / MESHFIELD_WIDTH_DEF) / MESHFIELD_XNUM) * nCntMeshField3, ((MESHFIELD_Z / MESHFIELD_Z_DEF) / MESHFIELD_ZNUM) * nCntMeshField2);
			}
		}
		pVtx += VT_MAX_MESH;
	}

	g_pVtxBuffMeshField->Unlock();

	WORD* pIdx;
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntMeshField = 0; nCntMeshField < MESHFIELD_MAX; nCntMeshField++)
	{
		for (nCntMeshField2 = 0; nCntMeshField2 < INDEX_NUM - (MESHFIELD_ZNUM - 1) * 2; nCntMeshField2++)
		{
			if (nCntMeshField2 % ((MESHFIELD_XNUM + 1) * 2) == 0 && nCntMeshField2 != 0)
			{
				//�C���f�b�N�X�w��
				pIdx[nCntMeshField2 - 2 + ((nCntMeshField2 / ((MESHFIELD_XNUM + 1) * 2)) * 2)] = (MESHFIELD_XNUM + 1) - (MESHFIELD_XNUM + 1) * ((nCntMeshField2 - 1) % 2) + ((nCntMeshField2 - 1) / 2);
				//�C���f�b�N�X�w��
				pIdx[nCntMeshField2 - 1 + ((nCntMeshField2 / ((MESHFIELD_XNUM + 1) * 2)) * 2)] = (MESHFIELD_XNUM + 1) - (MESHFIELD_XNUM + 1) * (nCntMeshField2 % 2) + (nCntMeshField2 / 2);
			}

			//�C���f�b�N�X�w��
			pIdx[nCntMeshField2 + ((nCntMeshField2 / ((MESHFIELD_XNUM + 1) * 2)) * 2)] = (MESHFIELD_XNUM + 1) - (MESHFIELD_XNUM + 1) * (nCntMeshField2 % 2) + (nCntMeshField2 / 2);
		}
		pIdx += INDEX_NUM;
	}

	g_pIdxBuffMeshField->Unlock();
}

//-------------------
//�|���S���I������
//-------------------
void UninitMeshField(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//-------------------
//�|���S���X�V����
//-------------------
void UpdateMeshField(void)
{
	CollisionMeshField();
}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�}�g���b�N�X

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	int nCntMeshField;
	for (nCntMeshField = 0; nCntMeshField < MESHFIELD_MAX; nCntMeshField++)
	{
		if (g_aMeshField[nCntMeshField].bUse && !g_aMeshField[nCntMeshField].bAlpha)
		{
			//�}�g���b�N�X������
			D3DXMatrixIdentity(&g_aMeshField[nCntMeshField].mtxWorld);

			//�����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshField[nCntMeshField].rot.y, g_aMeshField[nCntMeshField].rot.x, g_aMeshField[nCntMeshField].rot.z);
			D3DXMatrixMultiply(&g_aMeshField[nCntMeshField].mtxWorld, &g_aMeshField[nCntMeshField].mtxWorld, &mtxRot);

			//�ʒu�̌v�Z
			D3DXMatrixTranslation(&mtxTrans, g_aMeshField[nCntMeshField].pos.x, g_aMeshField[nCntMeshField].pos.y, g_aMeshField[nCntMeshField].pos.z);
			D3DXMatrixMultiply(&g_aMeshField[nCntMeshField].mtxWorld, &g_aMeshField[nCntMeshField].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshField[nCntMeshField].mtxWorld);

			//���_�o�b�t�@
			pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffMeshField);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureMeshField);

			//�|���S���̕`��
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLESTRIP,//�^�C�v
				0,
				0,
				VT_MAX_MESH,//���_��
				nCntMeshField * INDEX_NUM,
				POLYGON_NUM//�|���S���̌�
			);
		}
	}
	for (nCntMeshField = 0; nCntMeshField < MESHFIELD_MAX; nCntMeshField++)
	{
		if (g_aMeshField[nCntMeshField].bUse && g_aMeshField[nCntMeshField].bAlpha)
		{
			//�}�g���b�N�X������
			D3DXMatrixIdentity(&g_aMeshField[nCntMeshField].mtxWorld);

			//�����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshField[nCntMeshField].rot.y, g_aMeshField[nCntMeshField].rot.x, g_aMeshField[nCntMeshField].rot.z);
			D3DXMatrixMultiply(&g_aMeshField[nCntMeshField].mtxWorld, &g_aMeshField[nCntMeshField].mtxWorld, &mtxRot);

			//�ʒu�̌v�Z
			D3DXMatrixTranslation(&mtxTrans, g_aMeshField[nCntMeshField].pos.x, g_aMeshField[nCntMeshField].pos.y, g_aMeshField[nCntMeshField].pos.z);
			D3DXMatrixMultiply(&g_aMeshField[nCntMeshField].mtxWorld, &g_aMeshField[nCntMeshField].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshField[nCntMeshField].mtxWorld);

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffMeshField);

			//���_�o�b�t�@
			pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureMeshField);

			//�|���S���̕`��
			pDevice->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLESTRIP,//�^�C�v
				0,
				0,
				VT_MAX_MESH,//���_��
				nCntMeshField * INDEX_NUM,
				POLYGON_NUM//�|���S���̌�
			);
		}
	}
}

//----------
//�ݒ�
//----------
void SetMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntMeshField;
	for (nCntMeshField = 0; nCntMeshField < MESHFIELD_MAX; nCntMeshField++)
	{
		if (!g_aMeshField[nCntMeshField].bUse)
		{
			g_aMeshField[nCntMeshField].pos = pos;
			g_aMeshField[nCntMeshField].rot = rot;
			g_aMeshField[nCntMeshField].bAlpha = false;
			g_aMeshField[nCntMeshField].bUse = true;
			break;
		}
	}
}

//----------------------
//�����蔻��
//----------------------
void CollisionMeshField(void)
{
	Player* pPlayer = GetPlayer();
	D3DXVECTOR3 aPos[2] = {}, Fieldvec = {}, Posvec = {}, PosOldvec = {}, movevec = {}, Norvec = {}, Dovec = {}, Hit = {};
	int nCntMeshField;
	float FieldCross, PosCross;
	for (nCntMeshField = 0; nCntMeshField < MESHFIELD_MAX; nCntMeshField++)
	{//�n�ʂ̐�
		if (g_aMeshField[nCntMeshField].bUse && !g_aMeshField[nCntMeshField].bAlpha)
		{//�g���Ă��铧���łȂ���
			aPos[0] = D3DXVECTOR3(g_aMeshField[nCntMeshField].pos.x + MESHFIELD_WIDTH * 0.5f * sinf(g_aMeshField[nCntMeshField].rot.z + D3DX_PI * -0.5f), g_aMeshField[nCntMeshField].pos.y + MESHFIELD_WIDTH * 0.5f * cosf(g_aMeshField[nCntMeshField].rot.z + D3DX_PI * 0.5f), g_aMeshField[nCntMeshField].pos.z);
			aPos[1] = D3DXVECTOR3(g_aMeshField[nCntMeshField].pos.x + MESHFIELD_WIDTH * 0.5f * sinf(g_aMeshField[nCntMeshField].rot.z + D3DX_PI * 0.5f), g_aMeshField[nCntMeshField].pos.y + MESHFIELD_WIDTH * 0.5f * cosf(g_aMeshField[nCntMeshField].rot.z + D3DX_PI * -0.5f), g_aMeshField[nCntMeshField].pos.z);
			Fieldvec = aPos[1] - aPos[0];//�ǂ̃x�N�g��
			Posvec = pPlayer->pos - aPos[0];//�ǂɑ΂���v���C���[�̃x�N�g��
			PosOldvec = pPlayer->posOld - aPos[0];//�ǂɑ΂���v���C���[�̋��x�N�g��
			movevec = pPlayer->pos - pPlayer->posOld;//�v���C���[�̈ړ��x�N�g��
			if ((Fieldvec.x * Posvec.y) - (Fieldvec.y * Posvec.x) <= 0.0f && (Fieldvec.x * PosOldvec.y) - (Fieldvec.y * PosOldvec.x) >= 0.0f && pPlayer->pos.z < g_aMeshField[nCntMeshField].pos.z + MESHFIELD_WIDTH * 0.5f && pPlayer->pos.z + pPlayer->aModel[1].pos.z + pPlayer->aModel[1].vtxMax.z > g_aMeshField[nCntMeshField].pos.z - MESHFIELD_WIDTH * 0.5f)
			{//�n�ʂ̉�
				FieldCross = (Fieldvec.x * movevec.y) - (Fieldvec.y * movevec.x);
				PosCross = (Posvec.x * movevec.y) - (Posvec.y * movevec.x);
				PosCross /= FieldCross;
				if (PosCross >= -0.01f && PosCross < 1.01f)
				{
					Hit = aPos[0] + Fieldvec * PosCross;
					movevec = pPlayer->pos - Hit;//�v���C���[�̈ړ��x�N�g��
					Norvec = D3DXVECTOR3(Fieldvec.y, -Fieldvec.x, Fieldvec.z);
					D3DXVec3Normalize(&Norvec, &Norvec);
					Dovec = Norvec * ((-movevec.x * Norvec.x) + (-movevec.y * Norvec.y));
					pPlayer->pos += Dovec * 1.001f;
					pPlayer->move.y = 0.0f;
					pPlayer->move.y = 0.0f;
					pPlayer->bJump = false;
				}
			}
		}
	}
}