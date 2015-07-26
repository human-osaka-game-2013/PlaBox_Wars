#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <d3d9.h>

class CPolygon
{
private:
	//	頂点フォーマット
	static const DWORD CUSTOM_FVF;
	struct CUSTOMVERTEX
	{
		float x,y,z;
		float rhw;
		DWORD color;
		float u, v;
	};

	LPDIRECT3DDEVICE9	m_pDevice;	//	描画デバイス

public:
	/**
	*	コンストラクタ
	*	@param 描画デバイス
	*/
	CPolygon( LPDIRECT3DDEVICE9 pDevice );

	/**
	*	描画
	*	@param	テクスチャ
	*	@param	位置X
	*	@param	位置Y
	*	@param	幅
	*	@param	高さ
	*	@param	色
	*/
	void Draw( LPDIRECT3DTEXTURE9 pTexture, float x, float y,
		float w, float h, DWORD color);

};

#endif