#include "effectMagager.h"

//	生成
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

//	処理
void CEffectManager::Control()
{
	int arrayIndex = pEffect.size();
	for( int i = 0; i < arrayIndex; i++ )
	{
		if( !pEffect[i]->ParticleControl())
			pEffect[i]->Delete();
	}
}

//	描画
void CEffectManager::Render( bool* _p_bMatrixInit )
{
	int arrayIndex = pEffect.size();
	for( int i = 0; i < arrayIndex; i++ )
		pEffect[i]->ParticleRender(_p_bMatrixInit);
}

//	解放
void CEffectManager::Free()
{
	int arrayIndex = pEffect.size();
	for( int i = 0; i < arrayIndex; i++ )
		pEffect[i]->Delete();
}
