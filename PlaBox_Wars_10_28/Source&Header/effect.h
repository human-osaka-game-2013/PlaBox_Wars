#ifndef _EFFECT_H_
#define _EFFECT_H_
#include <vector>
#include "particle.h"

/**
*	@brief	�G�t�F�N�g���N���X
	@details�@���̃N���X���p�������������g���B

*/
class CEffect
{
private:
	D3DXVECTOR3 m_refPos;		///<	�G�t�F�N�g�𔭐��������_
	D3DXVECTOR3	m_refVec;		///<	�G�t�F�N�g�𔭐�����������
	eTEXTURE m_numTexture;	///<	�\������ۂ̃e�N�X�`��ID
	bool playFrag;	///<	�G�t�F�N�g�̍Đ��t���O
	
protected:
	std::vector< CParticle* > parVertex;	///<	�p�[�e�B�N���������̒��_���W
	
	/**
	*	@brief	vec3�^�̃����o�[�̗�
	*	@details	�Q�b�^�[�֐�����ɂ܂Ƃ߂�ׂɁA
	�����ɂ���ĕԂ�l�����߂�l�ɂ��Ă��܂��B
	*/
	enum	eVEC3_TYPE
	{
		VEC3_POS,
		VEC3_VEC,
	};

public:
	/**
	*	@brief	�G�t�F�N�g�N���X�̃R���X�g���N�^
	*/
	CEffect( D3DXVECTOR3 _pos, D3DXVECTOR3 _vec, eTEXTURE _numTexture );

	/**
	*	@brief	�p�[�e�B�N���I�u�W�F�N�g�̃C���X�^���X
	*	@details parVertex�ɔh���N���X�^�ɉ����āA
				 �G�t�F�N�g�ɕK�v���̃I�u�W�F�N�g���쐬�B
	*			 @n�e�G�t�F�N�g�ŗ��q�̐��͈Ⴄ�͂��Ȃ̂ŉ��z�֐��Ƃ��Đ錾���Ă��܂��B
	*/
	virtual void ParticleInstance(){};
	
	/**
	*	@brief	�p�[�e�B�N���ŗL�̏���
	*	@retval ture	�G�t�F�N�g�i�p�[�e�B�N���������Ă���j���Đ���
	*	@retval false	�G�t�F�N�g�i�p�[�e�B�N�������ł����j����~������
	*	@details �e���q�̓������R�R�Ő��䂵�܂��B
	*			@n�e�G�t�F�N�g�ŗ��q�̓����͈Ⴄ�͂��Ȃ̂ŉ��z�֐��Ƃ��Đ錾���Ă��܂��B
	*	@warning false��Ԃ��O�ɕK��Delete�֐����Ă�ŉ������B
	*/
	virtual bool ParticleControl(){return false;}
	
	/**
	*	@brief	�p�[�e�B�N���̕`��
	*	@details �e���q�̕`������܂��B
	*	@param[in]	�ϊ��s��X�V�t���O�|�C���^
	*/
	void ParticleRender( bool* _p_bMatrixInit );
	
	/**
	*	@brief	�I�u�W�F�N�g�̔j��
	*	details �p�[�e�B�N���̃I�u�W�F�N�g�̓x�N�^�Ő������Ă���̂ŁA
				�G�t�F�N�g���I������A�S���j�����܂��B
	*/
	void Delete();

public:
	///<	�A�N�Z�b�T
	/**
	*	@brief	�t���O�擾
	*/
	bool GetPlayFlag(){ return playFrag; }

	/**
	*	@brief	�t���O�X�V
	*/
	void SetPlayFlag( bool _flag ){ playFrag = _flag; }

	/**
	*	@brief	D3DXVECTOR�^�̃����o�[�ϐ����擾
	*	@param[in]	_type	�擾�����������o�[�̎��	
	*	@retval�@m_refPos�@or�@m_refVec
	*/
	D3DXVECTOR3 GetVec( eVEC3_TYPE _type );

	/**
	*	@brief	�e�N�X�`���ԍ��擾
	*/
	eTEXTURE GetTextureNum() { return m_numTexture; }
};

#endif