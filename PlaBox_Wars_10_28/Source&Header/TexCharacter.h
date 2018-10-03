#ifndef _TEXCHARACTER_H_
#define _TEXCHARACTER_H_

#include <d3d9.h>
#include <locale.h>

class CTexCharacter
{
private:
	LPDIRECT3DDEVICE9	m_pDevice;	//	�`��f�o�C�X
	LPDIRECT3DTEXTURE9	m_pTexture;	//	�e�N�X�`��
	int					m_height;	//	�����̍���
	int					m_width;	//	�����̕�

public:
	/**
	*	�R���X�g���N�^
	*	@praram	�f�o�C�X
	*	@praram	�쐬���镶��
	*	@praram	��
	*	@praram	����
	*	@praram	�t�H���g��
	*/
	CTexCharacter( LPDIRECT3DDEVICE9 pDevice, const TCHAR* ch,
		int w, int h, LPCWSTR fontName );

	/**
	*	�e�N�X�`���擾
	*	@praram	����
	*	@return	�e�N�X�`��
	*/
	LPDIRECT3DTEXTURE9 getTexture();

	/**
	*	�����̍����擾
	*	@praram	����
	*	@return	�����̍���
	*/
	int getHeight();

	/**
	*	�����̕��擾
	*	@praram	����
	*	@return	�����̕�
	*/
	int getWidth();

	//���C�h������(WCHAR*)���}���`�o�C�g������(char*)�ɕϊ�
	//errno_t wcstombs_s(
	//   size_t *pReturnValue,//�ϊ����ꂽ������
	//   char *mbstr,			//�ϊ����ʂ̃}���`�o�C�g������p�̃o�b�t�@�̃A�h���X(�ϊ���)
	//   size_t sizeInBytes,	//mbstr �o�b�t�@�̃T�C�Y 
	//   const wchar_t *wcstr,//�ϊ�����郏�C�h������̃A�h���X(�ϊ���)
	//   size_t count 		//wcstr �Ɋi�[���郏�C�h�����̍ő吔
	//);
	//
	//char *setlocale(
	//	int category,		//���P�[���̉e�����󂯂�J�e�S��
	//	const char *locale 	//���P�[����
	//);
};

#endif