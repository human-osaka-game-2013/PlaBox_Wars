//	HitCheck.h
//	�����蔻��ׂ̈̃{�b�N�X������ē����蔻������B

#pragma once

#include "Lib.h"
#include "graphic.h"

//	�ǉ���	2/10	�T�c
#define ADJUSTMENT_OF_HOLE_PASTE 1.85f	//	�e���\��t�����̔�����

//	�e���\��t�����̊e�ʂ̊p�x����
#define	HIT_RAD_FRONT_MIN	0.5f	//	�O��	
#define	HIT_RAD_FRONT_MAX	2.5f	//	�O��
#define	HIT_RAD_BACK_MIN	-2.5f	//	�w��
#define	HIT_RAD_BACK_MAX	-0.5f	//	�w��
#define	HIT_RAD_RIGHT_MIN	-0.2f	//	�E����
#define	HIT_RAD_RIGHT_MAX	0.2f	//	�E����
#define	HIT_RAD_LEFT_MIN	-2.8f	//	������
#define	HIT_RAD_LEFT_MAX	2.8f	//	������

//	�֐�SegmentHitcheck�ɂĎg�p
#define CHECK_HIT_POINT	2	//	���e�_�̔�����
#define NUM_PRISM_VERTEX 8	//	�l�p���̒��_���i����pA�p�j
#define NUM_PRISM_FACE 6	//	�l�p���̖ʐ��i����pA�p�j

//	HRESULT InitBBox(LPDIRECT3DDEVICE9 pDevice,THING* pThing)
//	�����蔻��p�̃{�b�N�X�����
HRESULT InitBBox ( CL_THING* );

//	BOOL Impact ( THING* pTarget, THING* pBullet )
//	�Փ˔���������蔻��
BOOL Impact ( CL_THING* , CL_THING* );

//	BOOL Impact ( THING* pBullet, THING* pTarget )
//�@�����m�̏Փ˔���
BOOL BoxImpact ( CL_THING* , CL_THING* ,int );

//	�����蔻��p�̎l�p�`�̏��
/*
	a�|b
	|�@|
	d�|c
*/
struct HitRect
{
public:
	D3DXVECTOR3 a, b, c, d;
};

//	����pq���O�p�`abc�ƌ�_���Ă��邩�ǂ�����n��
//	�������Ă���ꍇ�A�����_�̏d�S���W(u,v,w)���Ԃ�t
bool IntersectSegmentTriangle( D3DXVECTOR3 p, D3DXVECTOR3 q,
	D3DXVECTOR3 a, D3DXVECTOR3 b, D3DXVECTOR3 c,
	float &u, float &v, float &w, float &t );

/*	�x�N�g��v�ɑ΂��Ē��_abc�|���S�����\���ǂ�������������߂�
	abc�ɂ͕K�������v���̕��тœ���鎖
	�֐�SegmentHitcheck����tmpRect�ł́uabc�v���́uacd�v�̏��ő�����邱��
	�߂�l	0�F��	1�F�\	-1�F�G���[
*/
int PolygonSideCheck( D3DXVECTOR3 a, D3DXVECTOR3 b, D3DXVECTOR3 c, D3DXVECTOR3 v );

//	���_abc����Ȃ�|���S���̖@�����v�Z
D3DXVECTOR3 GetPolygonNormal( D3DXVECTOR3 a, D3DXVECTOR3 b, D3DXVECTOR3 c );

/**	
*	@brief	�����Ǝl�p�����f���Ƃ̓����蔻��
*	@param[in]	pA	����A
*	@param[in]	pB	����B	
*	@param[in]	pHitVec		���e�_����pA�̊�_�̋����̊i�[�p	
*	@param[in]	pHitNomal	���e�ʂ̖@���x�N�g��
*	@param[in]	pHitFaceSita	���e�ʂ̖@���x�N�g����(0,0,1)�x�N�g���̊Ԃ̊p�x
*	@retval	true	�������Ă��āA����pB��pA�̍ŏ��̐ڐG�_��pA�|���S���̕\�ʂł������ꍇ
*	@retval	false	�������Ă��Ȃ��A����pB��pA�̍ŏ��̐ڐG�_��pA�|���S���̗��ʂł������ꍇ
*	@details �⑫
	����A�i���̏ꍇ�l�p���^�j��	����B�́i�O�t���[���ƌ��t���[���̍��W�j2�_�ŏo���������Ƃ�
	�����蔻����Ƃ蕨��A�̂ǂ̃|���S���ɕ\�ʂ��瓖���������𒲂ׂ�֐��B@n
	player.x�̖ʎw��	��F��0123�i������vector�^��localVec�Ɋi�[����Ă��钸�_�ԍ��j@n
	���			��0231@n
	���			��4675@n
	���ʁi�������j	��0462	��1375@n	
	���ʁi�L�����j	��0154	��2673	�i���e�ʂ̕��т͔����v����ɂ��Ă��܂��j@n
*	@todo	pHitFaceSita�����߂鐔�ׂ̖̈@���x�N�g���Ɣ�r�Ώۂ̃x�N�g���̒l�����_�I�Ȃ��̂���Ȃ��B@n
			�l���Ȃ����K�v����
*/
bool SegmentHitcheck( CL_THING* pA, CL_THING* pB, 
	D3DXVECTOR3* pHitVec, D3DXVECTOR3* pHitNomal, float* pHitFaceSita );