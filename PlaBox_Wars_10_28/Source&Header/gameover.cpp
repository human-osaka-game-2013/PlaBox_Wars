#include "graphic.h"
#include "input.h"
#include "gameover.h"
#include"Audio.h"
#include "UI.h"
//	ゲームオーバーの初期化
CUSTOMVERTEX vertextemp[4];
void CL_GAMEOVER::Init ()
{	LoadSoundFile("Sound\\BGM\\lose.wav", BGM_04);
	SoundPlay( BGM_04, false);
	LoadTexture ( "Texture\\Image\\gameover.png", TEX_GAMEOVER, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_GAMEOVER, 0, 0, NULL, NULL, NULL, NULL );
}

//	ゲームオーバーの処理
void CL_GAMEOVER::Control ()
{
	
	if ( StCheck ( K_TITLE, PUSH ) )	
	{
		MessageBox(0,"タイトルに戻ります。","",MB_OK);
		ChangeScene ( S_TITLE );
	}
	if ( StCheck ( RELOAD, PUSH ) )
	{
		MessageBox(0,"リトライします。","",MB_OK);
		ChangeScene ( S_GAME );
	}
}

//　ゲームオーバーの3D描画
void CL_GAMEOVER::Render ()
{
	for( int ii = 0 ; ii < 4 ; ii++ )
	{
		vertextemp[ii].rhw = 1.f;
		vertextemp[ii].z = 0.f;
		vertextemp[ii].color = D3DCOLOR_ARGB(255,255,255,255);
	}
	vertextemp[0].x = vertextemp[3].x = 0.f;
	vertextemp[1].x = vertextemp[2].x = 1280.f;
	vertextemp[0].y = vertextemp[1].y = 0.f;
	vertextemp[2].y = vertextemp[3].y = 720.f;
	vertextemp[0].tu = vertextemp[3].tu = 0.f;
	vertextemp[1].tu = vertextemp[2].tu = 1.f;
	vertextemp[0].tv = vertextemp[1].tv = 0.f;
	vertextemp[2].tv = vertextemp[3].tv = 1.f;
	pD3Device -> SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	pD3Device -> SetTexture ( 0, GetTEXTUREINFO(TEX_GAMEOVER).pTexture );

	pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		vertextemp,
		sizeof ( CUSTOMVERTEX ) );
}

//　ゲームオーバーの2D描画
void CL_GAMEOVER::Draw ()
{
	
}

void CL_GAMEOVER::Release()
{
	ReleaseAllTexture();
	ReleaseAllSoundFile();
}