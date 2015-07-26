#ifndef _EFFECT_H_
#define _EFFECT_H_
#include <vector>
#include "particle.h"

/**
*	@brief	エフェクト基底クラス
	@details　このクラスを継承させた物を使う。

*/
class CEffect
{
private:
	D3DXVECTOR3 m_refPos;		///<	エフェクトを発生させる基準点
	D3DXVECTOR3	m_refVec;		///<	エフェクトを発生させる基準向き
	eTEXTURE m_numTexture;	///<	表示する際のテクスチャID
	bool playFrag;	///<	エフェクトの再生フラグ
	
protected:
	std::vector< CParticle* > parVertex;	///<	パーティクル発生時の頂点座標
	
	/**
	*	@brief	vec3型のメンバーの列挙
	*	@details	ゲッター関数を一つにまとめる為に、
	引数によって返り値を決める様にしています。
	*/
	enum	eVEC3_TYPE
	{
		VEC3_POS,
		VEC3_VEC,
	};

public:
	/**
	*	@brief	エフェクトクラスのコンストラクタ
	*/
	CEffect( D3DXVECTOR3 _pos, D3DXVECTOR3 _vec, eTEXTURE _numTexture );

	/**
	*	@brief	パーティクルオブジェクトのインスタンス
	*	@details parVertexに派生クラス型に応じて、
				 エフェクトに必要分のオブジェクトを作成。
	*			 @n各エフェクトで粒子の数は違うはずなので仮想関数として宣言しています。
	*/
	virtual void ParticleInstance(){};
	
	/**
	*	@brief	パーティクル固有の処理
	*	@retval ture	エフェクト（パーティクルが動いている）が再生中
	*	@retval false	エフェクト（パーティクルが消滅した）が停止した時
	*	@details 各粒子の動きをココで制御します。
	*			@n各エフェクトで粒子の動きは違うはずなので仮想関数として宣言しています。
	*	@warning falseを返す前に必ずDelete関数を呼んで下さい。
	*/
	virtual bool ParticleControl(){return false;}
	
	/**
	*	@brief	パーティクルの描画
	*	@details 各粒子の描画をします。
	*	@param[in]	変換行列更新フラグポインタ
	*/
	void ParticleRender( bool* _p_bMatrixInit );
	
	/**
	*	@brief	オブジェクトの破棄
	*	details パーティクルのオブジェクトはベクタで生成しているので、
				エフェクトが終了次第、全部破棄します。
	*/
	void Delete();

public:
	///<	アクセッサ
	/**
	*	@brief	フラグ取得
	*/
	bool GetPlayFlag(){ return playFrag; }

	/**
	*	@brief	フラグ更新
	*/
	void SetPlayFlag( bool _flag ){ playFrag = _flag; }

	/**
	*	@brief	D3DXVECTOR型のメンバー変数を取得
	*	@param[in]	_type	取得したいメンバーの種類	
	*	@retval　m_refPos　or　m_refVec
	*/
	D3DXVECTOR3 GetVec( eVEC3_TYPE _type );

	/**
	*	@brief	テクスチャ番号取得
	*/
	eTEXTURE GetTextureNum() { return m_numTexture; }
};

#endif