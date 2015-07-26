#include "TexString.h"
#include "Lib.h"

// コンストラクタ
CTexString::CTexString(LPDIRECT3DDEVICE9 pDevice,
		std::string str, int w, int h,
		LPCWSTR fontName)
{
	// 引数としてもらってきた文字列を１文字ずつに分解
	for( UINT i = 0; i < str.size(); i++ )
	{
		// 1文字分取得
		std::string s = str.substr(i, 1).c_str();

		// テクスチャにする
		m_str.push_back( new CTexCharacter(pDevice,
			s.c_str(), w, h, fontName) );
	}
	// 板ポリゴンを生成
	m_pPolygon = new CPolygon(pDevice);
}
	
// デストラクタ
CTexString::~CTexString()
{
	// 文字描画クラスの解放
	for( UINT i = 0; i < m_str.size(); i++ ) {
		NULL_DELETE( m_str[i] );
	}
	// ポリゴンクラス解放
	NULL_DELETE( m_pPolygon );
}

// 描画
void CTexString::Draw(float x, float y, UINT index)
{
	Draw(x, y, index, D3DCOLOR_ARGB(255,255,255,255));
}

// 描画
void CTexString::Draw(float x, float y, UINT index, DWORD color)
{
	float drawPos = x;	// 文字列描画開始位置
	for( UINT i = 0; i < index; i++ ) {
		// 1文字分の長さ、高さを取得
		float w = static_cast<float>(m_str[i]->getWidth());
		float h = static_cast<float>(m_str[i]->getHeight());

		// １文字分描画
		m_pPolygon->Draw(m_str[i]->getTexture(),
			drawPos, y, w, h, color);

		// 次の文字描画位置を計算
		drawPos += w;
	}

}

// 文字列の長さを取得する
UINT CTexString::getLength()
{
	return m_str.size();
}

// テクスチャ情報を取得
LPDIRECT3DTEXTURE9 CTexString::getTexture(int no)
{
	return m_str[no]->getTexture();
}