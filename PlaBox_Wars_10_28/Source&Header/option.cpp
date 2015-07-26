#include "graphic.h"
#include "input.h"
#include "option.h"
#include"Audio.h"
//	オプションの初期化
void CL_OPTION::Init ()
{
	LoadTexture ( "Texture\\Image\\option.png", TEX_OPTION, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_OPTION, 0, 0, NULL, NULL, NULL, NULL );
}

//	オプションの処理
void CL_OPTION::Control ()
{
	if ( StCheck ( K_TITLE, PUSH ) )	
	{
		MessageBox(0,"タイトルに戻ります。","",MB_OK);
		ChangeScene ( S_TITLE );
	}
}

//　オプションの3D描画
void CL_OPTION::Render ()
{
	
}

//　オプションの2D描画
void CL_OPTION::Draw ()
{
	TextureDraw ( TEX_OPTION );
}

void CL_OPTION::Release()
{
	ReleaseAllTexture();
	ReleaseAllSoundFile();
}