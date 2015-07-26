#include "polygon.h"

//	静的なメンバ変数の実体化
const DWORD CPolygon::CUSTOM_FVF =
	( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 );


/**
*	コンストラクタ
*	@param 描画デバイス
*/
CPolygon::CPolygon( LPDIRECT3DDEVICE9 pDevice ) : 
	m_pDevice( pDevice )
{

}

/**
*	描画
*	@param	テクスチャ
*	@param	位置X
*	@param	位置Y
*	@param	幅
*	@param	高さ
*	@param	色
*/
void CPolygon::Draw( LPDIRECT3DTEXTURE9 pTexture, float x, float y,
	float w, float h, DWORD color)
{
	//	頂点情報
	CUSTOMVERTEX v[] = 
	{
		{ x,	y,	0.5f, 1.f, color, 0.f, 0.f },
		{ x+w,	y,	0.5f, 1.f, color, 1.f, 0.f },
		{ x+w,	y+h,0.5f, 1.f, color, 1.f, 1.f },
		{ x,	y+h,0.5f, 1.f, color, 0.f, 1.f },
	};

	//	テクスチャのセット
	m_pDevice->SetTexture( 0, pTexture );
	//	頂点フォーマットの設定
	m_pDevice->SetFVF( CUSTOM_FVF );
	//	描画
	m_pDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2, v, sizeof(CUSTOMVERTEX));


}