#include "graphic.h"
#include "menu.h"
#include "input.h"
#include "Audio.h"
//	メニューの初期化
void CL_MENU::Init ()
{
	LoadTexture ( "Texture\\Image\\menu.png", TEX_MENU, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_MENU, WIN_WIDTH/2, WIN_HEIGHT/2, NULL, NULL, NULL, NULL );
}
//	メニューの処理
void CL_MENU::Control ()
{

}

//　メニューの描画
void CL_MENU::Render ()
{
	TextureDraw ( TEX_MENU );
}

void CL_MENU::Release()
{
	ReleaseAllTexture();
	ReleaseAllSoundFile();
}