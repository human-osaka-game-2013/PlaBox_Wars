#include "effect.h"



//	エフェクトクラスのコンストラクタ
CEffect::CEffect( D3DXVECTOR3 _pos, D3DXVECTOR3 _vec, eTEXTURE _numTexture )
{
	m_refPos = _pos;
	m_refVec = _vec;
	m_numTexture = _numTexture;
}

//	パーティクルの描画
void CEffect::ParticleRender( bool* _p_bMatrixInit )
{
	int arrayIndex = parVertex.size();
	for( int i = 0; i < arrayIndex; i++ )
		PolygonRender( parVertex[0]->vertex, parVertex[i]->m_pos, 
		parVertex[i]->m_rot, D3DXVECTOR3(1,1,1) ,GetTextureNum(), _p_bMatrixInit );
}

//	オブジェクトの破棄
void CEffect::Delete()
{
	parVertex.clear();
}

/*
	アクセッサ
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
