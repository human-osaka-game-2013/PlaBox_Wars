#ifndef _PARTICLE_H_
#define _PARTICLE_H_
#include "graphic.h"

#define _DEF_ALPHA_ 255		///<	粒子の固定アルファ値
#define _DEF_WIDTH_ 0.25f	///<	粒子の各頂点の間隔
#define _DEF_ARRAY_INDEX_ 4	///<	粒子ポリゴンの添字定数
/**
*	@brief	粒子クラス
*	@details	粒子の描画ならびに操作に必要なデータを持ったクラス

*/
class CParticle
{
public:
	//static const char defAlpha = 255;	///<	粒子の固定アルファ値
	//const float defWidth = 10.f;		///<	粒子の各頂点の間隔
	//static const char defArrayIndex = 3;///<	粒子ポリゴンの添字定数
public:
	D3DXVECTOR3		m_pos;		///<	粒子の基準点
	D3DXVECTOR3		m_vec;		///<	粒子の向き
	D3DXVECTOR3		m_rot;		///<	粒子の回転度
	unsigned char	m_alpha;	///<	頂点アルファ値の変数
	
	CUSTOMVERTEX	vertex[_DEF_ARRAY_INDEX_];	///<	粒子のポリゴン頂点
	
public:
	/**
	*	@brief	コンストラクタ
		@param[in]	_pos	基準点
		@param[in]	_vec	向き
	*/
	CParticle( D3DXVECTOR3 _pos, D3DXVECTOR3 _vec );
	/**
	*	@brief	デストラクタ
	*/
	~CParticle();
};

#endif