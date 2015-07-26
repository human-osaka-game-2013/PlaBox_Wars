#include "effectMagager.h"

//	ê∂ê¨
void CEffectManager::PlayEffect( D3DXVECTOR3 _pos, D3DXVECTOR3 _vec, eEFFECT_TYPE _effectType )
{
	switch( _effectType )
	{
	case TYPE_DEBRIS:
		pEffect.push_back(new CDebrisEffect( _pos, _vec, (eTEXTURE)EFFECT_TEXTURE_DEBRIS ));

		break;

	case TYPE_EXPLOSION:


		break;
	}
}

//	èàóù
void CEffectManager::Control()
{
	int arrayIndex = pEffect.size();
	for( int i = 0; i < arrayIndex; i++ )
	{
		if( !pEffect[i]->ParticleControl())
			pEffect[i]->Delete();
	}
}

//	ï`âÊ
void CEffectManager::Render( bool* _p_bMatrixInit )
{
	int arrayIndex = pEffect.size();
	for( int i = 0; i < arrayIndex; i++ )
		pEffect[i]->ParticleRender(_p_bMatrixInit);
}

//	âï˙
void CEffectManager::Free()
{
	int arrayIndex = pEffect.size();
	for( int i = 0; i < arrayIndex; i++ )
		pEffect[i]->Delete();
}
