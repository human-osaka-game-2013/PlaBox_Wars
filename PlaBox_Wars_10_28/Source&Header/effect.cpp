#include "effect.h"



//	�G�t�F�N�g�N���X�̃R���X�g���N�^
CEffect::CEffect( D3DXVECTOR3 _pos, D3DXVECTOR3 _vec, eTEXTURE _numTexture )
{
	m_refPos = _pos;
	m_refVec = _vec;
	m_numTexture = _numTexture;
}

//	�p�[�e�B�N���̕`��
void CEffect::ParticleRender( bool* _p_bMatrixInit )
{
	int arrayIndex = parVertex.size();
	for( int i = 0; i < arrayIndex; i++ )
		PolygonRender( parVertex[0]->vertex, parVertex[i]->m_pos, 
		parVertex[i]->m_rot, D3DXVECTOR3(1,1,1) ,GetTextureNum(), _p_bMatrixInit );
}

//	�I�u�W�F�N�g�̔j��
void CEffect::Delete()
{
	parVertex.clear();
}

/*
	�A�N�Z�b�T
*/
D3DXVECTOR3 CEffect::GetVec( eVEC3_TYPE _type )
{
	D3DXVECTOR3	_ret;
	switch( _type)
	{
	case VEC3_POS:
		_ret =  m_refPos;
		break;
	case VEC3_VEC:
		_ret = m_refVec;
		break;
	}
	return _ret;
}
