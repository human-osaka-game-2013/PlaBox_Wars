#ifndef _EFFECTMANAGER_H_
#define _EFFECTMANAGER_H_
#include <vector>
#include "graphic.h"
#include "effect.h"
#include "DebrisEffect.h"
#include "ExplosionEffect.h"

/**
*	@brief	�G�t�F�N�g�Ǘ��N���X

*/
class	CEffectManager
{
public:
	/**
	*	@brief	�G�t�F�N�g�̎�ޔԍ�
	*	@warning �K��CEffect�̔h���N���X�ɍ����ԍ��������Ƃ��ēn���Ă����ĉ������B
		�܂��G�t�F�N�g��ǉ�����ۂ͕K�v�ł���Ȃ�R�R�̗񋓂̍X�V�����肢���܂��B
	*/
	enum eEFFECT_TYPE
	{
		TYPE_DEBRIS,	///<	�j�ЃG�t�F�N�g�̎�ޔԍ�
		TYPE_EXPLOSION,	///<	�����G�t�F�N�g�̎�ޔԍ�
	};

	/**
	*	@brief	�G�t�F�N�g�ŗL�̃e�N�X�`���ԍ�
	*	@warning �K��CEffect�̔h���N���X�ɍ����ԍ��������Ƃ��ēn���Ă����ĉ������B
		�܂��G�t�F�N�g��ǉ�����ۂ͕K�v�ł���Ȃ�R�R�̗񋓂̍X�V�����肢���܂��B
	*/
	enum eEFFECT_TEXTURE
	{
		EFFECT_TEXTURE_DEBRIS = eTEXTURE::TEX_EFF_DEBRIS,		///<	�j�ЃG�t�F�N�g�̃e�N�X�`���ԍ�
		EFFECT_TEXTURE_EXPLOSION = eTEXTURE::TEX_EFF_EXPROSION,	///<	�����G�t�F�N�g�̃e�N�X�`���ԍ�
	};

private:
	std::vector< CEffect* > pEffect;	///<	�G�t�F�N�g�I�u�W�F�N�g�̃x�N�^

public:
	/**
	*	@brief	�R���X�g���N�^
	*	@param[in]	_pos	�G�t�F�N�g�̏o���_
	*	@param[in]	_vec	�o�������̃x�N�g��
	*	@param[in]	_effectType	�Đ�����G�t�F�N�g�̎��
	*	@warning	�����_�ł�_vec�͔j�Зp�Ƃ��Ă̗p��
	*/
	void PlayEffect( D3DXVECTOR3 _pos, D3DXVECTOR3 _vec, eEFFECT_TYPE _effectType );
	
	/**
	*	@brief	�T�u���[�`������
	*/
	void Control();

	/**
	*	@brief	�`��
	*	@param[in]	�ϊ��s��X�V�t���O�|�C���^
	*/
	void Render( bool* _p_bMatrixInit );

	/**
	*	@brief	���
	*/
	void Free();
};

#endif