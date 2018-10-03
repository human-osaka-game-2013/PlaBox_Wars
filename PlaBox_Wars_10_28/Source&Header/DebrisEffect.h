#ifndef _DEBRIS_EFFECT_H_
#define _DEBRIS_EFFECT_H_

#include"effect.h"

#define _DEBRIS_PARTICLE_VOL_ 50

class CDebrisEffect : public CEffect	
{
public:
	
public:
	/**
	*	@brief	�j�ЃG�t�F�N�g�̃R���X�g���N�^
	*	@param[in]	_pos	�G�t�F�N�g�̏o���_
	*	@param[in]	_vec	�o�������̃x�N�g��
	*	@param[in]	_textureNum	�G�t�F�N�g�̃e�N�X�`���̔ԍ�
	*/	
	CDebrisEffect( D3DXVECTOR3 _pos, D3DXVECTOR3 _vec, 
		eTEXTURE _textureNum );

	/**
	*	@brief	�p�[�e�B�N���I�u�W�F�N�g�̃C���X�^���X
	*	@details parVertex�ɔh���N���X�^�ɉ����āA
				 �G�t�F�N�g�ɕK�v���̃I�u�W�F�N�g���쐬�B
	*			 
	*/
	void ParticleInstance();
	
	/**
	*	@brief	�p�[�e�B�N���ŗL�̏���
	*	@retval ture	�G�t�F�N�g�i�p�[�e�B�N���������Ă���j���Đ���
	*	@retval false	�G�t�F�N�g�i�p�[�e�B�N�������ł����j����~������
	*	@details �e���q�̓������R�R�Ő��䂵�܂��B
	*			
	*	@warning false��Ԃ��O�ɕK��Delete�֐����Ă�ŉ������B
	*/
	bool ParticleControl();
};

#endif