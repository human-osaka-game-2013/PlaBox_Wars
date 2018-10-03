#include <d3dx9.h>
#include "TexCharacter.h"

/**
 *	�R���X�g���N�^
 *	@param	�f�o�C�X
 *	@param	�쐬���镶��
 *	@param	��
 *	@param	����
 *	@param	�t�H���g��
 */
CTexCharacter::CTexCharacter(LPDIRECT3DDEVICE9 pDevice, const TCHAR* ch,
		int w, int h, LPCWSTR fontName) :
m_pDevice( pDevice )
{
	//���C�h������(WCHAR*)���}���`�o�C�g������(char*)�ɕϊ�

	//�ϊ��O������
	//fontName
	//�ϊ�������i�[�o�b�t�@
	char	wStrC[50];
	
	size_t wLen = 0;
	errno_t err = 0;
	
	//���P�[���w��
	setlocale(LC_ALL,"japanese");
	//�ϊ�
	err = wcstombs_s(&wLen, wStrC, 20, fontName, _TRUNCATE);

	// �t�H���g����
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

	// �f�o�C�X�R���e�L�X�g�擾
	HDC hdc = GetDC(NULL);
	// �ϊ��O�̃t�H���g���
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

	// �����R�[�h�擾
	UINT code = 0;
#if UNICODE
	code = (UINT)*ch;	// �P�������̃o�C�g�������̂܂ܑ��
#else
	// �S�p�����p���𔻒f����֐�
	if( IsDBCSLeadByte(*ch) ) {
		code = static_cast<BYTE>(ch[0]) << 8 | static_cast<BYTE>(ch[1]);
	} else {
		code = static_cast<BYTE>(ch[0]);
	}
#endif
	// �r�b�g�}�b�v�擾
	UINT format = GGO_GRAY4_BITMAP;
	int level = 17;
	GLYPHMETRICS gm;
	const MAT2 mat = {{0,1},{0,0},{0,0},{0,1}};
	// �o�b�t�@�̃T�C�Y�擾
	DWORD size = GetGlyphOutline(hdc, code, format, &gm, 0, NULL, &mat);
	// �t�H���g���������ރo�b�t�@
	BYTE* ptr = new BYTE[size];
	GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &gm, size, ptr, &mat);

	// �t�H���g���擾
	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);

	// �t�H���g�̃T�C�Y�v�Z�ɕK�v�ȏ��͎擾�����̂�
	// �K�v���Ȃ��I�u�W�F�N�g�̉�����s��
	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
	ReleaseDC(NULL, hdc);

	// �t�H���g�̃r�b�g�}�b�v���A�������v�Z
	int bmpH = gm.gmBlackBoxY;
	// ���̕����̓f�B�Z���g�̌v�Z
	int bmpW = gm.gmBlackBoxX + (4-(gm.gmBlackBoxX%4))%4; 

	// �]�����܂߂��T�C�Y�̌v�Z
	int fontH = tm.tmHeight;
	int fontW = gm.gmCellIncX;

	// �t�H���g�������o���ʒu���v�Z
	int ofsH = tm.tmAscent - gm.gmptGlyphOrigin.y;
	int ofsW = gm.gmptGlyphOrigin.x;

	// ��e�N�X�`���̐���
	D3DXCreateTexture(pDevice,
		fontW, fontH, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8B8G8R8,
		D3DPOOL_DEFAULT,	// �������݉\�ȃe�N�X�`��
		&m_pTexture);

	// �e�N�X�`��(�T�[�t�F�C�X)�̃��b�N
	D3DLOCKED_RECT loc;
	m_pTexture->LockRect( 0, &loc, NULL, D3DLOCK_DISCARD );

	// �T�[�t�F�C�X�̏�����
	// �������̈�A�̈�̃T�C�Y�A���ߐs�����l
	FillMemory(loc.pBits, loc.Pitch * fontH, 0);

	// �t�H���g���̏�������
	for( int y = ofsH; y < ofsH + bmpH; y++ ) {
		for( int x = ofsW; x < ofsW + gm.gmBlackBoxX; x++ ) {
			// �����������ވʒu
			DWORD trans = (255 * ptr[x-ofsW + bmpW * (y-ofsH)]) / (level-1);
			// �F���
			DWORD color = 0x00ffffff | (trans << 24);
			// ��������
			memcpy(((BYTE*)loc.pBits + loc.Pitch*y + 4*x), &color, sizeof(DWORD));
		}
	}

	// �e�N�X�`��(�T�[�t�F�C�X)�̃A�����b�N
	m_pTexture->UnlockRect(0);

	// �������݂��I������̂ňꎞ�f�[�^�͉��
	delete[] ptr;

	// �t�H���g�T�C�Y����
	m_height = fontH;
	m_width = fontW;
}

/**
 *	�e�N�X�`���擾
 *	@param	�Ȃ�
 *	@return	�e�N�X�`��
 */
LPDIRECT3DTEXTURE9 CTexCharacter::getTexture()
{
	return m_pTexture;
}

/**
 *	�����̍����擾
 *	@param	�Ȃ�
 *	@return	�����̍���
 */
int CTexCharacter::getHeight()
{
	return m_height;
}

/**
 *	�����̕��擾
 *	@param	�Ȃ�
 *	@return	�����̕�
 */
int CTexCharacter::getWidth()
{
	return m_width;
}