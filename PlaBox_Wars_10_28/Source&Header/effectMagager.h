#ifndef _EFFECTMANAGER_H_
#define _EFFECTMANAGER_H_
#include <vector>
#include "graphic.h"
#include "effect.h"
#include "DebrisEffect.h"
#include "ExplosionEffect.h"

/**
*	@brief	エフェクト管理クラス

*/
class	CEffectManager
{
public:
	/**
	*	@brief	エフェクトの種類番号
	*	@warning 必ずCEffectの派生クラスに合う番号を引数として渡してあげて下さい。
		またエフェクトを追加する際は必要であるならココの列挙の更新もお願いします。
	*/
	enum eEFFECT_TYPE
	{
		TYPE_DEBRIS,	///<	破片エフェクトの種類番号
		TYPE_EXPLOSION,	///<	爆発エフェクトの種類番号
	};

	/**
	*	@brief	エフェクト固有のテクスチャ番号
	*	@warning 必ずCEffectの派生クラスに合う番号を引数として渡してあげて下さい。
		またエフェクトを追加する際は必要であるならココの列挙の更新もお願いします。
	*/
	enum eEFFECT_TEXTURE
	{
		EFFECT_TEXTURE_DEBRIS = eTEXTURE::TEX_EFF_DEBRIS,		///<	破片エフェクトのテクスチャ番号
		EFFECT_TEXTURE_EXPLOSION = eTEXTURE::TEX_EFF_EXPROSION,	///<	爆発エフェクトのテクスチャ番号
	};

private:
	std::vector< CEffect* > pEffect;	///<	エフェクトオブジェクトのベクタ

public:
	/**
	*	@brief	コンストラクタ
	*	@param[in]	_pos	エフェクトの出現点
	*	@param[in]	_vec	出現向きのベクトル
	*	@param[in]	_effectType	再生するエフェクトの種類
	*	@warning	現時点では_vecは破片用としての用意
	*/
	void PlayEffect( D3DXVECTOR3 _pos, D3DXVECTOR3 _vec, eEFFECT_TYPE _effectType );
	
	/**
	*	@brief	サブルーチン処理
	*/
	void Control();

	/**
	*	@brief	描画
	*	@param[in]	変換行列更新フラグポインタ
	*/
	void Render( bool* _p_bMatrixInit );

	/**
	*	@brief	解放
	*/
	void Free();
};

#endif