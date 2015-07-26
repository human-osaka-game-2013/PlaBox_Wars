#ifndef _TEXCHARACTER_H_
#define _TEXCHARACTER_H_

#include <d3d9.h>
#include <locale.h>

class CTexCharacter
{
private:
	LPDIRECT3DDEVICE9	m_pDevice;	//	描画デバイス
	LPDIRECT3DTEXTURE9	m_pTexture;	//	テクスチャ
	int					m_height;	//	文字の高さ
	int					m_width;	//	文字の幅

public:
	/**
	*	コンストラクタ
	*	@praram	デバイス
	*	@praram	作成する文字
	*	@praram	幅
	*	@praram	高さ
	*	@praram	フォント名
	*/
	CTexCharacter( LPDIRECT3DDEVICE9 pDevice, const TCHAR* ch,
		int w, int h, LPCWSTR fontName );

	/**
	*	テクスチャ取得
	*	@praram	無し
	*	@return	テクスチャ
	*/
	LPDIRECT3DTEXTURE9 getTexture();

	/**
	*	文字の高さ取得
	*	@praram	無し
	*	@return	文字の高さ
	*/
	int getHeight();

	/**
	*	文字の幅取得
	*	@praram	無し
	*	@return	文字の幅
	*/
	int getWidth();

	//ワイド文字列(WCHAR*)をマルチバイト文字列(char*)に変換
	//errno_t wcstombs_s(
	//   size_t *pReturnValue,//変換された文字数
	//   char *mbstr,			//変換結果のマルチバイト文字列用のバッファのアドレス(変換先)
	//   size_t sizeInBytes,	//mbstr バッファのサイズ 
	//   const wchar_t *wcstr,//変換されるワイド文字列のアドレス(変換元)
	//   size_t count 		//wcstr に格納するワイド文字の最大数
	//);
	//
	//char *setlocale(
	//	int category,		//ロケールの影響を受けるカテゴリ
	//	const char *locale 	//ロケール名
	//);
};

#endif