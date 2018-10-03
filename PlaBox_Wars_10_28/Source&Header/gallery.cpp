#include "graphic.h"
#include "input.h"
#include "gallery.h"
#include"Audio.h"
//	�M�������[�̏�����
void CL_GALLERY::Init ()
{
	LoadTexture ( "Texture\\Image\\ending.png", TEX_GALLERY, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_GALLERY, 0, 0, NULL, NULL, NULL, NULL );

	//	�ǉ���	2/14	�T�c
	LoadTexture ( "Texture\\Image\\title_B.png", TEX_GO_TO_TITLE, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_GO_TO_TITLE, TITLE_BUTTON_X, TITLE_BUTTON_Y, NULL, NULL, NULL, NULL );
}

//	�M�������[�̏���
void CL_GALLERY::Control ()
{
	//	�ǉ���	2/14	�T�c
	if ( HitOfTexture ( poCurrentCursor.x, poCurrentCursor.y, TEX_GO_TO_TITLE ) )
	{
		ChangeColorKey ( ON_OF_BUTTON, TEX_GO_TO_TITLE );
		if ( MouseStCheck ( MOUSE_L, PUSH) )
		{
			ChangeScene ( S_TITLE );
		}
	}
	else
	{
		ChangeColorKey ( OUT_OF_BUTTON, TEX_GO_TO_TITLE );
	}
}

//�@�M�������[��3D�`��
void CL_GALLERY::Render ()
{

}

//�@�M�������[��2D�`��
void CL_GALLERY::Draw ()
{
	TextureDraw ( TEX_GALLERY );

	//	�ǉ���	2/14	�T�c
	TextureDraw ( TEX_GO_TO_TITLE );
}

void CL_GALLERY::Release()
{
	ReleaseAllTexture();
	ReleaseAllSoundFile();
}