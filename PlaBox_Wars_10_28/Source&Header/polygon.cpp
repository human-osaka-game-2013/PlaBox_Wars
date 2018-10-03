#include "polygon.h"

//	�ÓI�ȃ����o�ϐ��̎��̉�
const DWORD CPolygon::CUSTOM_FVF =
	( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 );


/**
*	�R���X�g���N�^
*	@param �`��f�o�C�X
*/
CPolygon::CPolygon( LPDIRECT3DDEVICE9 pDevice ) : 
	m_pDevice( pDevice )
{

}

/**
*	�`��
*	@param	�e�N�X�`��
*	@param	�ʒuX
*	@param	�ʒuY
*	@param	��
*	@param	����
*	@param	�F
*/
void CPolygon::Draw( LPDIRECT3DTEXTURE9 pTexture, float x, float y,
	float w, float h, DWORD color)
{
	//	���_���
	CUSTOMVERTEX v[] = 
	{
		{ x,	y,	0.5f, 1.f, color, 0.f, 0.f },
		{ x+w,	y,	0.5f, 1.f, color, 1.f, 0.f },
		{ x+w,	y+h,0.5f, 1.f, color, 1.f, 1.f },
		{ x,	y+h,0.5f, 1.f, color, 0.f, 1.f },
	};

	//	�e�N�X�`���̃Z�b�g
	m_pDevice->SetTexture( 0, pTexture );
	//	���_�t�H�[�}�b�g�̐ݒ�
	m_pDevice->SetFVF( CUSTOM_FVF );
	//	�`��
	m_pDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2, v, sizeof(CUSTOMVERTEX));


}