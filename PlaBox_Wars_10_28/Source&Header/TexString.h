#ifndef _TEXSTRING_H_
#define _TEXSTRING_H_

#include <vector>
#include <d3d9.h>
#include <string>

#include "Polygon.h"
#include "TexCharacter.h"

class CTexString
{
private:
	std::vector<CTexCharacter*> m_str;	// 表示する文字列
	CPolygon* m_pPolygon;				// 板ポリゴン

public:
	// コンストラクタ
	CTexString(LPDIRECT3DDEVICE9 pDevice,
		std::string str, int w, int h,
		LPCWSTR fontName);
	
	// デストラクタ
	~CTexString();

	// 描画
	void Draw(float x, float y, UINT index);

	// 描画
	void Draw(float x, float y, UINT index, DWORD color);

	// 文字列の長さを取得する
	UINT getLength();

	// テクスチャ情報を取得
	LPDIRECT3DTEXTURE9 getTexture(int no);
};

#endif