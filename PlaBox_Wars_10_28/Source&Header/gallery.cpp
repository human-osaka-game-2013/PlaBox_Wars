#include "graphic.h"
#include "input.h"
#include "gallery.h"
#include"Audio.h"
//	ギャラリーの初期化
void CL_GALLERY::Init ()
{
	LoadTexture ( "Texture\\Image\\ending.png", TEX_GALLERY, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_GALLERY, 0, 0, NULL, NULL, NULL, NULL );

	//	追加日	2/14	亀田
	LoadTexture ( "Texture\\Image\\title_B.png", TEX_GO_TO_TITLE, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_GO_TO_TITLE, TITLE_BUTTON_X, TITLE_BUTTON_Y, NULL, NULL, NULL, NULL );
}

//	ギャラリーの処理
void CL_GALLERY::Control ()
{
	//	追加日	2/14	亀田
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

//　ギャラリーの3D描画
void CL_GALLERY::Render ()
{

}

//　ギャラリーの2D描画
void CL_GALLERY::Draw ()
{
	TextureDraw ( TEX_GALLERY );

	//	追加日	2/14	亀田
	TextureDraw ( TEX_GO_TO_TITLE );
}

void CL_GALLERY::Release()
{
	ReleaseAllTexture();
	ReleaseAllSoundFile();
}