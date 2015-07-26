#include"UI.h"
#include"graphic.h"
#include"player.h"
void DrawAmmoStock()
{
	int ammostock = player.GetAmmoStock();
	int stock1 = ammostock % 10;
	int stock10 = ammostock / 10;
	int stock100 = ammostock / 100;
	CUSTOMVERTEX stockvertex[4];
	for( int ii = 0 ; ii < 4 ; ii++ )
	{
		stockvertex[ii].rhw = 1.f;
		stockvertex[ii].z = 0.f;
		stockvertex[ii].color = D3DCOLOR_ARGB(255,255,255,255);
	}
	

	stockvertex[0].x = stockvertex[3].x = AMMOSTOCKPOSX_1;
	stockvertex[1].x = stockvertex[2].x = AMMOSTOCKPOSX_1 + 50.f;
	stockvertex[0].y = stockvertex[1].y = AMMOSTOCKPOSY;
	stockvertex[2].y = stockvertex[3].y = AMMOSTOCKPOSY + 50.f;
	for( int ii = 0 ; ii < 4 ; ii++ )
	{
		stockvertex[ii].rhw = 1.f;
		stockvertex[ii].z = 0.f;
		stockvertex[ii].color = D3DCOLOR_ARGB(255,255,255,255);
	}
	stockvertex[0].tu = stockvertex[3].tu = 0.f  + (float)stock1 / 10;
	stockvertex[1].tu = stockvertex[2].tu = 0.1f + (float)stock1 / 10;
	stockvertex[0].tv = stockvertex[1].tv = 0.f;
	stockvertex[2].tv = stockvertex[3].tv = 1.f;

	pD3Device -> SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	pD3Device -> SetTexture ( 0, GetTEXTUREINFO(TEX_NUM_SET).pTexture );

	pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		stockvertex,
		sizeof ( CUSTOMVERTEX ) );
	// 10‚ÌˆÊ
	if( stock10 != 0 || stock100 != 0)
	{
		stockvertex[0].x = stockvertex[3].x = AMMOSTOCKPOSX_10;
		stockvertex[1].x = stockvertex[2].x = AMMOSTOCKPOSX_10 + 50.f;
		stockvertex[0].y = stockvertex[1].y = AMMOSTOCKPOSY;
		stockvertex[2].y = stockvertex[3].y = AMMOSTOCKPOSY + 50.f;

		stockvertex[0].tu = stockvertex[3].tu = 0.f  + (float)stock10 / 10;
		stockvertex[1].tu = stockvertex[2].tu = 0.1f + (float)stock10 / 10;
		stockvertex[0].tv = stockvertex[1].tv = 0.f;
		stockvertex[2].tv = stockvertex[3].tv = 1.f;

		pD3Device -> SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

		pD3Device -> SetTexture ( 0, GetTEXTUREINFO(TEX_NUM_SET).pTexture );

		pD3Device -> DrawPrimitiveUP(
			D3DPT_TRIANGLEFAN,
			2,
			stockvertex,
			sizeof ( CUSTOMVERTEX ) );
	}
	//100 ‚ÌˆÊ
	if( stock100 != 0)
	{
		stockvertex[0].x = stockvertex[3].x = AMMOSTOCKPOSX_100;
		stockvertex[1].x = stockvertex[2].x = AMMOSTOCKPOSX_100 + 50.f;
		stockvertex[0].y = stockvertex[1].y = AMMOSTOCKPOSY;
		stockvertex[2].y = stockvertex[3].y = AMMOSTOCKPOSY + 50.f;

		stockvertex[0].tu = stockvertex[3].tu = 0.f  + (float)stock100 / 10;
		stockvertex[1].tu = stockvertex[2].tu = 0.1f + (float)stock100 / 10;
		stockvertex[0].tv = stockvertex[1].tv = 0.f;
		stockvertex[2].tv = stockvertex[3].tv = 1.f;

		pD3Device -> SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

		pD3Device -> SetTexture ( 0, GetTEXTUREINFO(TEX_NUM_SET).pTexture );

		pD3Device -> DrawPrimitiveUP(
			D3DPT_TRIANGLEFAN,
			2,
			stockvertex,
			sizeof ( CUSTOMVERTEX ) );
	}
	int maxammo1 = 0;
	int maxammo10 = 0;
	int maxammo100 = 0;
	int testes = player.GetMainWeapon()->iBulletType;
	if(player.GetMainWeapon()->iBulletType == W_RIFLE)
	{
		maxammo1 = 0;
		maxammo10 = 12;
		maxammo100 = 1;
	}
	else if(player.GetMainWeapon()->iBulletType == W_MG)
	{
		maxammo1 = 0;
		maxammo10 = 12;
		maxammo100 = 1;
	}
	else if(player.GetMainWeapon()->iBulletType == W_BAZOOKA)
	{
		maxammo1 = 0;
		maxammo10 = 12;
		maxammo100 = 1;
	}
	else if(player.GetMainWeapon()->iBulletType == W_GATLING)
	{
		maxammo1 = 0;
		maxammo10 = 12;
		maxammo100 = 1;
	}

	stockvertex[0].x = stockvertex[3].x = AMMOMAXPOSX_1;
	stockvertex[1].x = stockvertex[2].x = AMMOMAXPOSX_1 + 50.f;
	stockvertex[0].y = stockvertex[1].y = AMMOMAXPOSY;
	stockvertex[2].y = stockvertex[3].y = AMMOMAXPOSY + 50.f;

	stockvertex[0].tu = stockvertex[3].tu = 0.f  + (float)maxammo1 / 10;
	stockvertex[1].tu = stockvertex[2].tu = 0.1f + (float)maxammo1 / 10;
	stockvertex[0].tv = stockvertex[1].tv = 0.f;
	stockvertex[2].tv = stockvertex[3].tv = 1.f;

	pD3Device -> SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	pD3Device -> SetTexture ( 0, GetTEXTUREINFO(TEX_NUM_SET).pTexture );

	pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		stockvertex,
		sizeof ( CUSTOMVERTEX ) );
	if( maxammo10 != 0 || maxammo100 != 0)
	{
		stockvertex[0].x = stockvertex[3].x = AMMOMAXPOSX_10;
		stockvertex[1].x = stockvertex[2].x = AMMOMAXPOSX_10 + 50.f;
		stockvertex[0].y = stockvertex[1].y = AMMOMAXPOSY;
		stockvertex[2].y = stockvertex[3].y = AMMOMAXPOSY + 50.f;

		stockvertex[0].tu = stockvertex[3].tu = 0.f  + (float)maxammo10 / 10;
		stockvertex[1].tu = stockvertex[2].tu = 0.1f + (float)maxammo10 / 10;
		stockvertex[0].tv = stockvertex[1].tv = 0.f;
		stockvertex[2].tv = stockvertex[3].tv = 1.f;

		pD3Device -> SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

		pD3Device -> SetTexture ( 0, GetTEXTUREINFO(TEX_NUM_SET).pTexture );

		pD3Device -> DrawPrimitiveUP(
			D3DPT_TRIANGLEFAN,
			2,
			stockvertex,
			sizeof ( CUSTOMVERTEX ) );
	}
	if( maxammo100 != 0)
	{
		stockvertex[0].x = stockvertex[3].x = AMMOMAXPOSX_100;
		stockvertex[1].x = stockvertex[2].x = AMMOMAXPOSX_100 + 50.f;
		stockvertex[0].y = stockvertex[1].y = AMMOMAXPOSY;
		stockvertex[2].y = stockvertex[3].y = AMMOMAXPOSY + 50.f;

		stockvertex[0].tu = stockvertex[3].tu = 0.f  + (float)maxammo100 / 10;
		stockvertex[1].tu = stockvertex[2].tu = 0.1f + (float)maxammo100 / 10;
		stockvertex[0].tv = stockvertex[1].tv = 0.f;
		stockvertex[2].tv = stockvertex[3].tv = 1.f;

		pD3Device -> SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

		pD3Device -> SetTexture ( 0, GetTEXTUREINFO(TEX_NUM_SET).pTexture );

		pD3Device -> DrawPrimitiveUP(
			D3DPT_TRIANGLEFAN,
			2,
			stockvertex,
			sizeof ( CUSTOMVERTEX ) );
	}

	//ƒ{ƒgƒ‹‚Ì”
	stockvertex[0].x = stockvertex[3].x = BOTTLEPOS_X;
	stockvertex[1].x = stockvertex[2].x = BOTTLEPOS_X + 50.f;
	stockvertex[0].y = stockvertex[1].y = BOTTLEPOS_Y;
	stockvertex[2].y = stockvertex[3].y = BOTTLEPOS_Y + 50.f;

	stockvertex[0].tu = stockvertex[3].tu = 0.f  + (float)player.GetBottleNum()/10;
	stockvertex[1].tu = stockvertex[2].tu = 0.1f + (float)player.GetBottleNum()/10;
	stockvertex[0].tv = stockvertex[1].tv = 0.f;
	stockvertex[2].tv = stockvertex[3].tv = 1.f;

	pD3Device -> SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	pD3Device -> SetTexture ( 0, GetTEXTUREINFO(TEX_NUM_SET).pTexture );

	pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		stockvertex,
		sizeof ( CUSTOMVERTEX ) );
}

void PlayerHoleDraw()
{
	CUSTOMVERTEX stockvertex[4];
	for( int ii = 0 ; ii < HOLE_MAX ; ii++ )
	{
		if(player.hitCount/2 > ii*10 )
		{
			if( player.holepos[ii].x == 0.f && player.holepos[ii].y == 0.f)
			{
				player.holepos[ii].x = (float)(rand()%1180);
				player.holepos[ii].y = (float)(rand()%620);
			}
			for( int jj = 0 ; jj < 4 ; jj++ )
			{
				stockvertex[jj].rhw = 1.f;
				stockvertex[jj].z = 0.f;
				stockvertex[jj].color = D3DCOLOR_ARGB(200,255,255,255);
			}
			stockvertex[0].x = stockvertex[3].x = player.holepos[ii].x;
			stockvertex[1].x = stockvertex[2].x = stockvertex[0].x + 200.f;
			stockvertex[0].y = stockvertex[1].y = player.holepos[ii].y;
			stockvertex[2].y = stockvertex[3].y = stockvertex[0].y + 200.f;

			stockvertex[0].tu = stockvertex[3].tu = 0.f;
			stockvertex[1].tu = stockvertex[2].tu = 1.f;
			stockvertex[0].tv = stockvertex[1].tv = 0.f;
			stockvertex[2].tv = stockvertex[3].tv = 1.f;

			pD3Device -> SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

			pD3Device -> SetTexture ( 0, GetTEXTUREINFO(TEX_DANKON).pTexture );

			pD3Device -> DrawPrimitiveUP(
				D3DPT_TRIANGLEFAN,
				2,
				stockvertex,
				sizeof ( CUSTOMVERTEX ) );
		}
	}
}