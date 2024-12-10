//---------------------------------------
//
//�J�����̒�`�E�錾[camera.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include"main.h"

#define CAMERA_ROT_SPEED (0.05f)//��]�X�s�[�h
#define CAMERA_SPEED (2.0f)//�ړ��X�s�[�h
#define CAMERA_INA (0.05f)//�Ǐ]�{��
#define CAMERA_ROTX (0.2f)//�c��]�͈�
#define CAMERA_ROTX_GRA (0.01f)//�c��]�n�ʃX�y�[�X
#define CAMERA_DISTANCE_SPEED (50.0f)
#define CAMERA_DISTANCE_MIN (50.0f)//�Y�[������
#define CAMERA_DISTANCE_MAX (1000.0f)//�Y�[������
#define CAMERA_WIDTH (90.0f)//����̍L��
#define CAMERA_MIN (10.0f)//����̍ŏ�
#define CAMERA_MAX (10000.0f)//����̍ő�

//�J�����\����
typedef struct
{
	D3DXVECTOR3 posV;
	D3DXVECTOR3 posVDest;
	D3DXVECTOR3 posR;
	D3DXVECTOR3 posRDest;
	D3DXVECTOR3 posU;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxProjection;
	D3DXMATRIX mtxView;
	float fDistance;
}Camera;

void InitCamera(void);//����������
void UninitCamera(void);//�I������
void UpdateCamera(void);//�X�V����
void SetCamera(void);//�`�揈��
Camera* GetCamera(void);

#endif _CAMERA_H_