#include <d3dx9.h>
#include "TexCharacter.h"

/**
 *	コンストラクタ
 *	@param	デバイス
 *	@param	作成する文字
 *	@param	幅
 *	@param	高さ
 *	@param	フォント名
 */
CTexCharacter::CTexCharacter(LPDIRECT3DDEVICE9 pDevice, const TCHAR* ch,
		int w, int h, LPCWSTR fontName) :
m_pDevice( pDevice )
{
	//ワイド文字列(WCHAR*)をマルチバイト文字列(char*)に変換

	//変換前文字列
	//fontName
	//変換文字列格納バッファ
	char	wStrC[50];
	
	size_t wLen = 0;
	errno_t err = 0;
	
	//ロケール指定
	setlocale(LC_ALL,"japanese");
	//変換
	err = wcstombs_s(&wLen, wStrC, 20, fontName, _TRUNCATE);

	// フォント生成
	HFONT hFont = CreateFont(
		h,
		w,
		0,
		0,
		0,
		FALSE,
		FALSE,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		FIXED_PITCH | FF_MODERN,
		wStrC);

	// デバイスコンテキスト取得
	HDC hdc = GetDC(NULL);
	// 変換前のフォント情報
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

	// 文字コード取得
	UINT code = 0;
#if UNICODE
	code = (UINT)*ch;	// １文字分のバイト数をそのまま代入
#else
	// 全角か半角かを判断する関数
	if( IsDBCSLeadByte(*ch) ) {
		code = static_cast<BYTE>(ch[0]) << 8 | static_cast<BYTE>(ch[1]);
	} else {
		code = static_cast<BYTE>(ch[0]);
	}
#endif
	// ビットマップ取得
	UINT format = GGO_GRAY4_BITMAP;
	int level = 17;
	GLYPHMETRICS gm;
	const MAT2 mat = {{0,1},{0,0},{0,0},{0,1}};
	// バッファのサイズ取得
	DWORD size = GetGlyphOutline(hdc, code, format, &gm, 0, NULL, &mat);
	// フォントを書き込むバッファ
	BYTE* ptr = new BYTE[size];
	GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &gm, size, ptr, &mat);

	// フォント情報取得
	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);

	// フォントのサイズ計算に必要な情報は取得したので
	// 必要がないオブジェクトの解放を行う
	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
	ReleaseDC(NULL, hdc);

	// フォントのビットマップ幅、高さを計算
	int bmpH = gm.gmBlackBoxY;
	// 後ろの部分はディセントの計算
	int bmpW = gm.gmBlackBoxX + (4-(gm.gmBlackBoxX%4))%4; 

	// 余白を含めたサイズの計算
	int fontH = tm.tmHeight;
	int fontW = gm.gmCellIncX;

	// フォントを書き出す位置を計算
	int ofsH = tm.tmAscent - gm.gmptGlyphOrigin.y;
	int ofsW = gm.gmptGlyphOrigin.x;

	// 空テクスチャの生成
	D3DXCreateTexture(pDevice,
		fontW, fontH, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8B8G8R8,
		D3DPOOL_DEFAULT,	// 書き込み可能なテクスチャ
		&m_pTexture);

	// テクスチャ(サーフェイス)のロック
	D3DLOCKED_RECT loc;
	m_pTexture->LockRect( 0, &loc, NULL, D3DLOCK_DISCARD );

	// サーフェイスの初期化
	// メモリ領域、領域のサイズ、埋め尽くす値
	FillMemory(loc.pBits, loc.Pitch * fontH, 0);

	// フォント情報の書き込み
	for( int y = ofsH; y < ofsH + bmpH; y++ ) {
		for( int x = ofsW; x < ofsW + gm.gmBlackBoxX; x++ ) {
			// 情報を書き込む位置
			DWORD trans = (255 * ptr[x-ofsW + bmpW * (y-ofsH)]) / (level-1);
			// 色情報
			DWORD color = 0x00ffffff | (trans << 24);
			// 書き込み
			memcpy(((BYTE*)loc.pBits + loc.Pitch*y + 4*x), &color, sizeof(DWORD));
		}
	}

	// テクスチャ(サーフェイス)のアンロック
	m_pTexture->UnlockRect(0);

	// 書き込みが終わったので一時データは解放
	delete[] ptr;

	// フォントサイズを代入
	m_height = fontH;
	m_width = fontW;
}

/**
 *	テクスチャ取得
 *	@param	なし
 *	@return	テクスチャ
 */
LPDIRECT3DTEXTURE9 CTexCharacter::getTexture()
{
	return m_pTexture;
}

/**
 *	文字の高さ取得
 *	@param	なし
 *	@return	文字の高さ
 */
int CTexCharacter::getHeight()
{
	return m_height;
}

/**
 *	文字の幅取得
 *	@param	なし
 *	@return	文字の幅
 */
int CTexCharacter::getWidth()
{
	return m_width;
}