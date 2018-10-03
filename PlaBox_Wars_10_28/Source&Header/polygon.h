#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <d3d9.h>

class CPolygon
{
private:
	//	���_�t�H�[�}�b�g
	static const DWORD CUSTOM_FVF;
	struct CUSTOMVERTEX
	{
		float x,y,z;
		float rhw;
		DWORD color;
		float u, v;
	};

	LPDIRECT3DDEVICE9	m_pDevice;	//	�`��f�o�C�X

public:
	/**
	*	�R���X�g���N�^
	*	@param �`��f�o�C�X
	*/
	CPolygon( LPDIRECT3DDEVICE9 pDevice );

	/**
	*	�`��
	*	@param	�e�N�X�`��
	*	@param	�ʒuX
	*	@param	�ʒuY
	*	@param	��
	*	@param	����
	*	@param	�F
	*/
	void Draw( LPDIRECT3DTEXTURE9 pTexture, float x, float y,
		float w, float h, DWORD color);

};

#endif