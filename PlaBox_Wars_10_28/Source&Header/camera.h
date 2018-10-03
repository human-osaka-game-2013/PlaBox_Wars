#pragma once

#define EYEPOS_Y_NORMAL		2.5f	//	������Ԃ̃J�����ʒu
#define LOOKPOS_Y_NORMAL	2.5f	//	������Ԃ̒����_

#define EYEPOS_Y_DOWN		0.65f	//	������Ԃ̃J�����ʒu
#define LOOKPOS_Y_DOWN		0.8f	//	������Ԃ̒����_

#define	PI	3.1415926f

void InitCamera();			//�J�����֐��E�E�E������

void Camera( float );		//�J�������_�ړ��Ǘ�

void Camera();				//�J���������֐�

void Jump ( bool *jflag );	

void Down ();

void CameraPosCheck();		// �J�������W�`�F�b�N

D3DXVECTOR3 GetEyePos();	//	�J�����ʒu�̎擾
D3DXVECTOR3 GetLookPos();	//	�����_�̎擾
float		GetRad();		//	�p�x(���W�A��)�̎擾

void SetCameraPos ( D3DXVECTOR3 vecPos, D3DXVECTOR3 vecRot );	//	�J�����ʒu���L�����̍��W��

#ifdef	CLASS
class CL_CAMERA
{
public:
	CL_CAMERA();	//	�J�����ʒu�A�����_�A�p�x(���W�A��)��������

	D3DXVECTOR3 GetEyePos();	//	�J�����ʒu�̎擾
	D3DXVECTOR3 GetLookPos();	//	�����_�̎擾
	float		GetRad();		//	�p�x(���W�A��)�̎擾
private:
	static	D3DXVECTOR3 g_eyePos;	// ���_���Wxyz
	static	D3DXVECTOR3 g_lookPos;	// �����_���Wxyz
	static	float		g_radian;	// ���_��]�␳
};
#endif

extern D3DXVECTOR3 g_eyePos;	// ���_���Wxyz
extern D3DXVECTOR3 g_lookPos;	// �����_���Wxyz
