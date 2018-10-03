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
	std::vector<CTexCharacter*> m_str;	// �\�����镶����
	CPolygon* m_pPolygon;				// �|���S��

public:
	// �R���X�g���N�^
	CTexString(LPDIRECT3DDEVICE9 pDevice,
		std::string str, int w, int h,
		LPCWSTR fontName);
	
	// �f�X�g���N�^
	~CTexString();

	// �`��
	void Draw(float x, float y, UINT index);

	// �`��
	void Draw(float x, float y, UINT index, DWORD color);

	// ������̒������擾����
	UINT getLength();

	// �e�N�X�`�������擾
	LPDIRECT3DTEXTURE9 getTexture(int no);
};

#endif