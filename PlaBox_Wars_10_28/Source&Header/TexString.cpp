#include "TexString.h"
#include "Lib.h"

// �R���X�g���N�^
CTexString::CTexString(LPDIRECT3DDEVICE9 pDevice,
		std::string str, int w, int h,
		LPCWSTR fontName)
{
	// �����Ƃ��Ă�����Ă�����������P�������ɕ���
	for( UINT i = 0; i < str.size(); i++ )
	{
		// 1�������擾
		std::string s = str.substr(i, 1).c_str();

		// �e�N�X�`���ɂ���
		m_str.push_back( new CTexCharacter(pDevice,
			s.c_str(), w, h, fontName) );
	}
	// �|���S���𐶐�
	m_pPolygon = new CPolygon(pDevice);
}
	
// �f�X�g���N�^
CTexString::~CTexString()
{
	// �����`��N���X�̉��
	for( UINT i = 0; i < m_str.size(); i++ ) {
		NULL_DELETE( m_str[i] );
	}
	// �|���S���N���X���
	NULL_DELETE( m_pPolygon );
}

// �`��
void CTexString::Draw(float x, float y, UINT index)
{
	Draw(x, y, index, D3DCOLOR_ARGB(255,255,255,255));
}

// �`��
void CTexString::Draw(float x, float y, UINT index, DWORD color)
{
	float drawPos = x;	// ������`��J�n�ʒu
	for( UINT i = 0; i < index; i++ ) {
		// 1�������̒����A�������擾
		float w = static_cast<float>(m_str[i]->getWidth());
		float h = static_cast<float>(m_str[i]->getHeight());

		// �P�������`��
		m_pPolygon->Draw(m_str[i]->getTexture(),
			drawPos, y, w, h, color);

		// ���̕����`��ʒu���v�Z
		drawPos += w;
	}

}

// ������̒������擾����
UINT CTexString::getLength()
{
	return m_str.size();
}

// �e�N�X�`�������擾
LPDIRECT3DTEXTURE9 CTexString::getTexture(int no)
{
	return m_str[no]->getTexture();
}