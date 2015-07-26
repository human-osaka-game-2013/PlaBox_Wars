#ifndef _DEBRIS_EFFECT_H_
#define _DEBRIS_EFFECT_H_

#include"effect.h"

#define _DEBRIS_PARTICLE_VOL_ 50

class CDebrisEffect : public CEffect	
{
public:
	
public:
	/**
	*	@brief	破片エフェクトのコンストラクタ
	*	@param[in]	_pos	エフェクトの出現点
	*	@param[in]	_vec	出現向きのベクトル
	*	@param[in]	_textureNum	エフェクトのテクスチャの番号
	*/	
	CDebrisEffect( D3DXVECTOR3 _pos, D3DXVECTOR3 _vec, 
		eTEXTURE _textureNum );

	/**
	*	@brief	パーティクルオブジェクトのインスタンス
	*	@details parVertexに派生クラス型に応じて、
				 エフェクトに必要分のオブジェクトを作成。
	*			 
	*/
	void ParticleInstance();
	
	/**
	*	@brief	パーティクル固有の処理
	*	@retval ture	エフェクト（パーティクルが動いている）が再生中
	*	@retval false	エフェクト（パーティクルが消滅した）が停止した時
	*	@details 各粒子の動きをココで制御します。
	*			
	*	@warning falseを返す前に必ずDelete関数を呼んで下さい。
	*/
	bool ParticleControl();
};

#endif