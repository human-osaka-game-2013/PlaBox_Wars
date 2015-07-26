#include "logo.h"
#include "graphic.h"
#include"Audio.h"
// logoCount インクリメント++で使用に変更
int logoCount;

#define  NONDISP   18
#define  LOGOFI    NONDISP  +24
#define  LOGODISP  LOGOFI   +36
#define  LOGOFO    LOGODISP +24

//	ロゴの初期化
void CL_LOGO::Init ()
{
	Alpha = 0;

	LoadTexture ( "Texture\\Image\\logo2.png", TEX_LOGO, 0, 0, 0 );
	SetVertex ( NORMAL, TEX_LOGO, 120, 180, NULL, NULL, NULL, NULL );
	logoCount = 0;
}

//	ロゴの処理
void CL_LOGO::Control ()
{
	logoCount++;


	if (logoCount < NONDISP) {
	}
	else if (logoCount  < LOGOFI) {
		Alpha += 11;
		if ( Alpha > 255 ) Alpha = 255;
		//VerTex の　color を　0x1000000 でわる
		//その値に11をたす。もし、２５５より大きければ255にする
		//結果を0x1000000倍し、colorの0x1000000で割ったあまりに加える
	}
	else if (logoCount  < LOGODISP) {
	}
	else if (logoCount  < LOGOFO){
		Alpha -= 11;
		if ( Alpha < 0 ) Alpha = 0;
		//VerTex の　color を　0x1000000 でわる
		//その値から11を引く。もし、０より小さければ0にする
		//結果を0x1000000倍し、colorの0x1000000で割ったあまりに加える
	}
	else{
		ChangeScene ( S_TITLE );
	}
	
	SetAlpha ( TEX_LOGO, Alpha);

	//if ( !logoCount )	ChangeScene ( S_TITLE );
}

//　ロゴの3D描画
void CL_LOGO::Render ()
{
	
}

//　ロゴの2D描画
void CL_LOGO::Draw ()
{
	TextureDraw ( TEX_LOGO );
}

void CL_LOGO::Release()
{
	ReleaseAllTexture();
	ReleaseAllSoundFile();
}