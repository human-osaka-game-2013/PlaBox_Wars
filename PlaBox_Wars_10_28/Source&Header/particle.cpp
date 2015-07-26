#include "effectMagager.h"
#include "particle.h"

//	コンストラクタ
CParticle::CParticle( D3DXVECTOR3 _pos, D3DXVECTOR3 _vec )
{
	m_pos = _pos;
	m_vec = _vec;
	m_rot = D3DXVECTOR3( 0,0,0 );
	m_alpha = _DEF_ALPHA_;
	for ( int ii = 0; ii < _DEF_ARRAY_INDEX_; ii++ )
	{
		vertex[ii].z = 0.5f;
		vertex[ii].rhw = 1.0f;
		vertex[ii].color = D3DCOLOR_ARGB(_DEF_ALPHA_,255,255,255);

		switch ( ii )
		{
		case 0:
			vertex[ii].x = -_DEF_WIDTH_ / 2.f;
			vertex[ii].y = -_DEF_WIDTH_ / 2.f;
			vertex[ii].tu = 1.0f;
			vertex[ii].tv = 1.0f;
			break;

		case 1:
			vertex[ii].x = -_DEF_WIDTH_ / 2.f;
			vertex[ii].y = _DEF_WIDTH_ / 2.f;
			vertex[ii].tu = 0.0f;
			vertex[ii].tv = 1.0f;	
			break;
			
		case 2:
			vertex[ii].x = _DEF_WIDTH_ / 2.f;
			vertex[ii].y = _DEF_WIDTH_ / 2.f;
			vertex[ii].tu = 0.0f;
			vertex[ii].tv = 0.0f;	
			break;
			
			
		case 3:
			vertex[ii].x = _DEF_WIDTH_ / 2.f;
			vertex[ii].y = -_DEF_WIDTH_ / 2.f;
			vertex[ii].tu = 0.0f;
			vertex[ii].tv = 1.0f;	
			break;
		}
		
	}
}

CParticle::~CParticle()
{

}