#ifndef _PARTICLE_H_
#define _PARTICLE_H_
#include "graphic.h"

#define _DEF_ALPHA_ 255		///<	���q�̌Œ�A���t�@�l
#define _DEF_WIDTH_ 0.25f	///<	���q�̊e���_�̊Ԋu
#define _DEF_ARRAY_INDEX_ 4	///<	���q�|���S���̓Y���萔
/**
*	@brief	���q�N���X
*	@details	���q�̕`��Ȃ�тɑ���ɕK�v�ȃf�[�^���������N���X

*/
class CParticle
{
public:
	//static const char defAlpha = 255;	///<	���q�̌Œ�A���t�@�l
	//const float defWidth = 10.f;		///<	���q�̊e���_�̊Ԋu
	//static const char defArrayIndex = 3;///<	���q�|���S���̓Y���萔
public:
	D3DXVECTOR3		m_pos;		///<	���q�̊�_
	D3DXVECTOR3		m_vec;		///<	���q�̌���
	D3DXVECTOR3		m_rot;		///<	���q�̉�]�x
	unsigned char	m_alpha;	///<	���_�A���t�@�l�̕ϐ�
	
	CUSTOMVERTEX	vertex[_DEF_ARRAY_INDEX_];	///<	���q�̃|���S�����_
	
public:
	/**
	*	@brief	�R���X�g���N�^
		@param[in]	_pos	��_
		@param[in]	_vec	����
	*/
	CParticle( D3DXVECTOR3 _pos, D3DXVECTOR3 _vec );
	/**
	*	@brief	�f�X�g���N�^
	*/
	~CParticle();
};

#endif