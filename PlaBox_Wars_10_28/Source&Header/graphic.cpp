#include <math.h>

#include "main.h"
#include "graphic.h"
#include "camera.h"
#include "input.h"

IDirect3D9*			pDirect3D;
IDirect3DDevice9*	pD3Device; //デバイスオブジェクト

D3DPRESENT_PARAMETERS	d3dpp;

TEXTUREINFO TextureInfo [TEXTURE_MAX];

CUSTOMVERTEX Textures [TEXTURE_MAX][4];

CUSTOMVERTEX	test[3] = {
	{ 0, 0, 0, 1.0, 0xFFFFFFFF, 1, 1},
	{ -3, 0, 0, 1.0, 0xFFFFFFFF, 1, 1},
	{ -3, 3, 0, 1.0, 0xFFFFFFFF, 1, 1},
};


//=================================================================================
//
//	グラフィックの初期化
//
//==================================================================================

// Direct3Dの初期化
// 第1引数：ウインドハンドル
bool InitRender ( HWND hWnd )
{
	D3DDISPLAYMODE d3ddm;
	
	// [Direct3D] オブジェクトの作成
	if( NULL == (pDirect3D = Direct3DCreate9 (D3D_SDK_VERSION) ) )		
	{
		MessageBox(0,"Direct3Dの作成に失敗しました","",MB_OK);
		return false;
	}

	// Display Mode の設定
	pDirect3D -> GetAdapterDisplayMode ( D3DADAPTER_DEFAULT, &d3ddm );

	ZeroMemory(	&d3dpp, sizeof ( D3DPRESENT_PARAMETERS ));

	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount  = 1;
	d3dpp.SwapEffect	   = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed		   = TRUE;

	////フルスクリーンにする場合////////////////////////////////////
	//D3DDISPLAYMODE DMode;
	//pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &DMode);
	//d3dpp.BackBufferFormat	= DMode.Format;
	//d3dpp.BackBufferWidth	= Win_Width;
	//d3dpp.BackBufferHeight	= Win_Height;
	//d3dpp.BackBufferCount	= 1;
	//d3dpp.SwapEffect		= D3DSWAPEFFECT_DISCARD;
	//d3dpp.Windowed		= FALSE;
	////////////////////////////////////////////////////////////////

	d3dpp.EnableAutoDepthStencil	= TRUE;			// Zバッファ使用確認
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;	// フォーマット関数指定

	if(FAILED (pDirect3D->CreateDevice (
			D3DADAPTER_DEFAULT,					//ビデオカード設定(複数搭載でない限りこの形式)
			D3DDEVTYPE_HAL,						//HAL->ハードウェア機能で表示
			hWnd,								//ウインドウ・ハンドル
			D3DCREATE_MIXED_VERTEXPROCESSING,		//ビデオカードのミックス頂点処理
												//実行できない場合・・・_SOFTWARE_ or _HARDWARE に切替
			&d3dpp,								//D3DPRESENT_PARAMETERS変数のアドレス
			&pD3Device								//内容空のデバイスオブジェクトへのポインタ変数のアドレス
												//	--> CreateDevice関数コール後にアドレスが格納され使えるようになる
			) ) )
	{
		MessageBox(0,"HAL(高速モード)でDIRECT3Dデバイスを作成できません\nREFモードで再試行します",NULL,MB_OK);
		if(FAILED	 (pDirect3D->CreateDevice (
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_MIXED_VERTEXPROCESSING,
				&d3dpp,
				&pD3Device
				) ) )
		{
			MessageBox(0,"DIRECT3Dデバイスの作成に失敗しました",NULL,MB_OK);
			return false;
		}
	}					
	return true;									
}													

//=====================================================================================
//
//	テクスチャ、メッシュの読み込み
//
//======================================================================================
// テクスチャの読み込み
// 第1引数：("画像の名前.拡張子"), 第2引数：テクスチャの番号(enum eTEXTUREから), 透過色RGB 
bool LoadTexture ( LPCSTR lpFileName, eTEXTURE TextuerNumber, int iColorRed, int iColorGreen, int iColorBlue )
{
	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(lpFileName, &info);
	// テクスチャを既に読み込んでいる場合はここで解放する
	if ( FAILED (D3DXCreateTextureFromFileEx (
					pD3Device,
					lpFileName,
					info.Width,
					info.Height,
					info.MipLevels,
					0,
					D3DFMT_UNKNOWN,
					D3DPOOL_MANAGED,
					D3DX_FILTER_NONE,
					D3DX_FILTER_NONE,
					D3DCOLOR_ARGB ( 0, iColorRed, iColorGreen, iColorBlue ),
					NULL, NULL,
					&TextureInfo [TextuerNumber].pTexture))) {
						return false;
	}

	// テクスチャ情報取得
	D3DSURFACE_DESC desc;

	TextureInfo [TextuerNumber].pTexture -> GetLevelDesc ( 0, &desc );
	TextureInfo [TextuerNumber].width = desc.Width;
	TextureInfo [TextuerNumber].height = desc.Height;

	return true;
}

//メッシュの読込＆裏描画バッファ
bool CL_THING::LoadThingFile(CL_THING *pThing,LPCSTR szXFileName,D3DXVECTOR3* pvecPosition, D3DXVECTOR3* pvecScall, D3DXVECTOR3* pvecRotate)
{
	//メッシュの初期位置
	memcpy(&pThing->vecPosition,pvecPosition,sizeof(D3DXVECTOR3));
	//メッシュの初期倍率
	memcpy(&pThing->vecScall,pvecScall,sizeof(D3DXVECTOR3));
	//メッシュの初期方向
	memcpy(&pThing->vecRotate,pvecRotate,sizeof(D3DXVECTOR3));

	//xファイルからメッシュをロードする
	LPD3DXBUFFER	pD3DXMtrlBuffer	= NULL;

	if(FAILED(D3DXLoadMeshFromX(
		szXFileName,
		D3DXMESH_SYSTEMMEM,
		pD3Device,
		NULL,
		&pD3DXMtrlBuffer,
		NULL,
		&pThing->dwNumMaterials,
		&pThing->pMesh
		) ) )
	{
		MessageBox(NULL,"xファイルの読み込みに失敗しました",szXFileName,MB_OK);
		return false;
	}


	D3DXMATERIAL*	d3dxMaterials	= (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	pThing->pMeshMaterials		= new D3DMATERIAL9[pThing->dwNumMaterials];
	pThing->pMeshTextures		= new LPDIRECT3DTEXTURE9[pThing->dwNumMaterials];

	for(DWORD i=0;	i<pThing->dwNumMaterials;	i++)
	{
		pThing->pMeshMaterials[i]			= d3dxMaterials[i].MatD3D;
		pThing->pMeshMaterials[i].Ambient	= pThing->pMeshMaterials[i].Diffuse;
		pThing->pMeshTextures[i]			= NULL;

		if(d3dxMaterials[i].pTextureFilename != NULL && lstrlen(d3dxMaterials[i].pTextureFilename) >0)
		{
			if(FAILED (D3DXCreateTextureFromFileEx (pD3Device,
													d3dxMaterials[i].pTextureFilename,
													D3DX_DEFAULT_NONPOW2,
													D3DX_DEFAULT_NONPOW2,
													D3DX_DEFAULT,
													0,
													D3DFMT_UNKNOWN,
													D3DPOOL_MANAGED,
													D3DX_FILTER_NONE,
													D3DX_FILTER_NONE,
													D3DCOLOR_ARGB ( 0, 0, 255, 0),
													NULL, NULL,
													&pThing->pMeshTextures[i]) ) )
			{
				MessageBox(NULL,"テクスチャの読み込みに失敗しました",NULL,MB_OK);
			}
		}
	}

	
	pD3DXMtrlBuffer->Release();
	return true;
}

//==================================================================================
//
//	描画処理
//
//==================================================================================

// 3D描画前処理
void BeginRender (void)
{
	if ( !pD3Device ) return;

	pD3Device->SetRenderState( D3DRS_ZENABLE, TRUE );			// Zバッファー処理を有効に
//	pD3Device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );	// カリングしない
	pD3Device->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );	// カリングする
	pD3Device->SetRenderState( D3DRS_LIGHTING, TRUE );			// ライトを有効に
	pD3Device->SetRenderState( D3DRS_AMBIENT, 0x00000000 );		// アンビエントライト(環境光)を設定
	pD3Device->SetRenderState( D3DRS_SPECULARENABLE, TRUE );	// スペキュラ(鏡面反射)を有効に

	pD3Device->LightEnable(0, TRUE);

	// 画面の消去
	pD3Device -> Clear ( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ,
						D3DCOLOR_XRGB ( 0x00, 0x00, 0x00 ),
						1.0f, 0 );

	// 描画の開始
	pD3Device -> BeginScene();
}

// 2D描画前処理
void BeginDraw (void)
{
	if ( !pD3Device ) return;

	// ステージステートの設定
	pD3Device -> SetTextureStageState ( 0, D3DTSS_ALPHAOP,		D3DTOP_MODULATE );
	pD3Device -> SetTextureStageState ( 0, D3DTSS_COLORARG1,	D3DTA_TEXTURE	);
	pD3Device -> SetTextureStageState ( 0, D3DTSS_COLORARG2,	D3DTA_DIFFUSE	);

	// 描画方法の設定
	pD3Device -> SetRenderState ( D3DRS_ALPHABLENDENABLE, true );
	pD3Device -> SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	pD3Device -> SetRenderState ( D3DRS_ZENABLE, true );
	
	// 描画の開始
	pD3Device -> BeginScene();

	// 画面の描画
	pD3Device -> SetFVF ( D3DFVF_CUSTOMVERTEX );
}
//------------------------------------------------------------------------------
//
//	テクスチャ描画処理
//	第1引数：テクスチャの構造体, 第2引数：テクスチャの番号(enum eTEXTUREから)
//
//---------------------------------------------------------------------------------
void TextureDraw ( eTEXTURE TextuerNumber )
{

	pD3Device -> SetTexture ( 0, TextureInfo[TextuerNumber].pTexture );
	pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		Textures[TextuerNumber],
		sizeof ( CUSTOMVERTEX ) );
}

///////////////////////////////////////
//------------------------------------------------------------------------------
//
// 左上基準で縮尺
// 第1引数：テクスチャの番号(enum eTEXTUREから)
// 第2引数：テクスチャの縮尺  1.0fで読み込み時の大きさ
//
//---------------------------------------------------------------------------------
void TextureScallDraw ( eTEXTURE TextuerNumber, float Scall )
{
	pD3Device -> SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	pD3Device -> SetTexture ( 0, TextureInfo[TextuerNumber].pTexture );

	CUSTOMVERTEX vertex[4];

	for( int i = 0; i < 4; i++ )
	{
		vertex[i] = Textures[TextuerNumber][i];
	}

	float x, y;
	x = vertex[ 2 ].x - vertex[ 0 ].x; // 横の長さ
	y = vertex[ 2 ].y - vertex[ 0 ].y; // 縦の長さ

	x *= Scall;	//スケールを掛けて、横幅を変化させる
	y *= Scall; //スケールを掛けて、縦幅を変化させる

	vertex[ 1 ].x = vertex[ 2 ].x = vertex[ 0 ].x + x; // 0番を基準にスケールをかけた横幅を足す
	vertex[ 2 ].y = vertex[ 3 ].y = vertex[ 0 ].y + y; // 0番を基準にスケールをかけた縦幅を足す

	pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		vertex,
		sizeof ( CUSTOMVERTEX ) );
}


/*
	描画時変換行列
*/
void RenderMatrix( bool* _p_bMatrixInit )
{
	static D3DXMATRIXA16	matView;
	//プロジェクショントランスフォーム(射影変換)
	static D3DXMATRIXA16	matProj;
		
	if( *_p_bMatrixInit )
	{
		//ビュートランスフォーム
		//D3DXVECTOR3...3次の行ベクトル
		//D3DXMATRIXA16...4x4の行列
		//注視点やカメラ位置はcamera.cppから取ってくる
		D3DXVECTOR3 eyePos	= GetEyePos();
		D3DXVECTOR3 lookPos	= GetLookPos();
		float		radian	= GetRad();

		D3DXVECTOR3	vecEyePt	( eyePos );		//カメラ(視点)位置
		D3DXVECTOR3	vecLookatPt	( lookPos );	//注視位置
		D3DXVECTOR3	vecUpVec	(0.0f, 1.0f, 0.0f);		//上方位置
		
		D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	
		//注視点更新
		lookPos	 = vecLookatPt;

		//	変更しました	12/13
		D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.6f, 0.9f, 200.0f);
		//--------------------------------------------------------------------
	
		//ライトをあてる　白色で鏡面反射有りに設定
		D3DXVECTOR3	vecDirection(1,1,1);
		D3DLIGHT9		light;
		ZeroMemory(&light,sizeof(D3DLIGHT9) );
		light.Type		= D3DLIGHT_DIRECTIONAL;
		light.Diffuse.r	= 1.0f;
		light.Diffuse.g	= 1.0f;
		light.Diffuse.b	= 1.0f;
		light.Specular.r	= 1.0f;
		light.Specular.g	= 1.0f;
		light.Specular.b	= 1.0f;
		light.Ambient.r	= 1.0f;	
		light.Ambient.g	= 1.0f;
		light.Ambient.b	= 1.0f;

		D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction,&vecDirection);
		light.Range		= 200.f;
		pD3Device->SetLight(0,&light);
		pD3Device->LightEnable(0,TRUE);

		*_p_bMatrixInit = false;
	}

	pD3Device->SetTransform(D3DTS_VIEW, &matView);
	pD3Device->SetTransform(D3DTS_PROJECTION, &matProj);
}

/*
	ポリゴン描画関数
*/
void PolygonRender( CUSTOMVERTEX* _pVertex, D3DXVECTOR3 _refPos, D3DXVECTOR3 _refRot, D3DXVECTOR3 _refSca,
	eTEXTURE _TextuerNumber, bool* _p_bMatrixInit )
{
	//ワールドトランスフォーム(絶対座標変換)
	//matWorld->y軸回転
	D3DXMATRIXA16	matWorld,matPosition, matScall, matRoate;	//[最終的なワールドトランスフォーム][平行移動行列を格納する行列]
	D3DXMatrixIdentity(&matWorld);								//単位行列の作成関数
	D3DXMatrixRotationYawPitchRoll(&matRoate, _refRot.y, _refRot.x, _refRot.z);	///	@todo現在は試験的に値をセット
	D3DXMatrixScaling(&matScall, _refSca.x, _refSca.y, _refSca.z);				///	@todo現在は試験的に値をセット
	D3DXMatrixTranslation(&matPosition, _refPos.x, _refPos.y, _refPos.z);			///	@todo現在は試験的に値をセット

	D3DXMatrixMultiply(&matWorld,&matWorld,&matRoate);		//行列を結合する	(絶対座標行列x回転行列)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matScall);		//行列を結合する関数(絶対座標行列x拡大行列)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matPosition);	//行列を結合する関数(絶対座標行列x平行移動行列行列)

	//｢D3DTS_WORLD(ワールドトランスフォーム)｣を｢matWorld行列を係数として｣様々な種類の変換を行うことをレンダリングパイプライン/Direct3Dに通知
	pD3Device->SetTransform(D3DTS_WORLD, &matWorld);

	RenderMatrix( _p_bMatrixInit );

	pD3Device -> SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	pD3Device->SetTexture( 0, TextureInfo[_TextuerNumber].pTexture);	///	@todo	現在は試験的に別のテクスチャを入れている。 
	pD3Device->DrawPrimitiveUP( D3DPT_TRIANGLEFAN,
		2,
		_pVertex,
		sizeof( CUSTOMVERTEX )
		);
}

//---------------------------------------------------------------------------
//
//	メッシュ描画処理
//
//----------------------------------------------------------------------------
void CL_THING::Transform(CL_THING* pThing)
{
	//ワールドトランスフォーム(絶対座標変換)
	//matWorld->y軸回転
	D3DXMATRIXA16	matWorld,matPosition, matScall, matRoate;						//[最終的なワールドトランスフォーム][平行移動行列を格納する行列]
	D3DXMatrixIdentity(&matWorld);												//単位行列の作成関数
	D3DXMatrixRotationYawPitchRoll(&matRoate, pThing->vecRotate.y, pThing->vecRotate.x, pThing->vecRotate.z);	//回転行列の作成関数
	D3DXMatrixScaling(&matScall, pThing->vecScall.x, pThing->vecScall.y, pThing->vecScall.z);					//拡大行列の作成関数
	D3DXMatrixTranslation(&matPosition, pThing->vecPosition.x, pThing->vecPosition.y, pThing->vecPosition.z);	//平行移動行列の作成関数

	D3DXMatrixMultiply(&matWorld,&matWorld,&matRoate);								//行列を結合する関数(第2引数x第3引数=>第1引数に格納)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matScall);								//行列を結合する関数(第2引数x第3引数=>第1引数に格納)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matPosition);							//行列を結合する関数(第2引数x第3引数=>第1引数に格納)

	//｢D3DTS_WORLD(ワールドトランスフォーム)｣を｢matWorld行列を係数として｣様々な種類の変換を行うことをレンダリングパイプライン/Direct3Dに通知
	pD3Device->SetTransform(D3DTS_WORLD, &matWorld);

	//ビュートランスフォーム
	//D3DXVECTOR3...3次の行ベクトル
	//D3DXMATRIXA16...4x4の行列
	//注視点やカメラ位置はcamera.cppから取ってくる
	D3DXVECTOR3 eyePos	= GetEyePos();
	D3DXVECTOR3 lookPos	= GetLookPos();
	float		radian	= GetRad();

	D3DXVECTOR3	vecEyePt	( eyePos );		//カメラ(視点)位置
	D3DXVECTOR3	vecLookatPt	( lookPos );	//注視位置
	D3DXVECTOR3	vecUpVec	(0.0f, 1.0f, 0.0f);		//上方位置
	D3DXMATRIXA16	matView;
	D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	pD3Device->SetTransform(D3DTS_VIEW, &matView);

	//注視点更新
	lookPos	 = vecLookatPt;

	//プロジェクショントランスフォーム(射影変換)
	D3DXMATRIXA16	matProj;

	//	変更しました	12/13
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.6f, 0.9f, 200.0f);
	//--------------------------------------------------------------------
	
	pD3Device->SetTransform(D3DTS_PROJECTION, &matProj);

	//ライトをあてる　白色で鏡面反射有りに設定
	D3DXVECTOR3	vecDirection(1,1,1);
	D3DLIGHT9		light;
	ZeroMemory(&light,sizeof(D3DLIGHT9) );
	light.Type		= D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r	= 1.0f;
	light.Diffuse.g	= 1.0f;
	light.Diffuse.b	= 1.0f;
	light.Specular.r	= 1.0f;
	light.Specular.g	= 1.0f;
	light.Specular.b	= 1.0f;
	light.Ambient.r	= 1.0f;	
	light.Ambient.g	= 1.0f;
	light.Ambient.b	= 1.0f;

	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction,&vecDirection);
	light.Range		= 200.f;
	pD3Device->SetLight(0,&light);
	pD3Device->LightEnable(0,TRUE);

	//レンダリング
	for(DWORD i=0;	i < pThing->dwNumMaterials ; i++)
	{
		pD3Device->SetMaterial(&pThing->pMeshMaterials[i]);
		pD3Device->SetTexture(0,pThing->pMeshTextures[i]);
		pThing->pMesh->DrawSubset(i);
	}

}

//	ビルボード用のメッシュ描画
void CL_THING::BillboardingTransform(CL_THING* pThing)
{
	//ワールドトランスフォーム（絶対座標変換）
	 D3DXMATRIXA16 matWorld,matCurrentView,matPosition;
	 D3DXMatrixIdentity(&matWorld);
	 D3DXMatrixTranslation(&matPosition,pThing->vecPosition.x,pThing->vecPosition.y,
		 pThing->vecPosition.z);
	 D3DXMatrixMultiply(&matWorld,&matWorld,&matPosition);
	 //現在のビュー行列を得て、、
	 pD3Device->GetTransform(D3DTS_VIEW,&matCurrentView);
	 // それを逆行列にして、、
	 D3DXMatrixInverse(&matCurrentView,NULL,&matCurrentView);
	 // ワールド行列に掛け合わせると、ビュー変換を打ち消すことになる
	 D3DXMatrixMultiply(&matWorld,&matWorld,&matCurrentView);

     pD3Device->SetTransform( D3DTS_WORLD, &matWorld );
	 
	 //ビュートランスフォーム
	//D3DXVECTOR3...3次の行ベクトル
	//D3DXMATRIXA16...4x4の行列
	//注視点やカメラ位置はcamera.cppから取ってくる
	D3DXVECTOR3 eyePos	= GetEyePos();
	D3DXVECTOR3 lookPos	= GetLookPos();
	float		radian	= GetRad();

	D3DXVECTOR3	vecEyePt	( eyePos );		//カメラ(視点)位置
	D3DXVECTOR3	vecLookatPt	( lookPos );	//注視位置
	D3DXVECTOR3	vecUpVec	(0.0f, 1.0f, 0.0f);		//上方位置
	D3DXMATRIXA16	matView;
	D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	pD3Device->SetTransform(D3DTS_VIEW, &matView);

	//注視点更新
	lookPos	 = vecLookatPt;

	//プロジェクショントランスフォーム(射影変換)
	D3DXMATRIXA16	matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.6f, 0.9f, 100.0f);
	pD3Device->SetTransform(D3DTS_PROJECTION, &matProj);

	//ライトをあてる　白色で鏡面反射有りに設定
	D3DXVECTOR3	vecDirection(1,1,1);
	D3DLIGHT9		light;
	ZeroMemory(&light,sizeof(D3DLIGHT9) );
	light.Type		= D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r	= 1.0f;
	light.Diffuse.g	= 1.0f;
	light.Diffuse.b	= 1.0f;
	light.Specular.r	= 1.0f;
	light.Specular.g	= 1.0f;
	light.Specular.b	= 1.0f;
	light.Ambient.r	= 1.0f;	
	light.Ambient.g	= 1.0f;
	light.Ambient.b	= 1.0f;

	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction,&vecDirection);
	light.Range		= 200.f;
	pD3Device->SetLight(0,&light);
	pD3Device->LightEnable(0,TRUE);

	//レンダリング
	for(DWORD i=0;	i < pThing->dwNumMaterials ; i++)
	{
		pD3Device->SetMaterial(&pThing->pMeshMaterials[i]);
		pD3Device->SetTexture(0,pThing->pMeshTextures[i]);
		pThing->pMesh->DrawSubset(i);
	}
}

//----------------------------------------------------------------------------
//
// 描画後処理
//
//----------------------------------------------------------------------------
void EndRender (void)
{
	// 描画の終了
	pD3Device -> EndScene();
}

//===============================================================================
//
//	解放
//
//============================================================================

// テクスチャの解放
// 第1引数：テクスチャの番号(enum eTEXTUREから)
void ReleaseTexture ( int TextuerNumber )
{
	SAFE_RELEASE ( TextureInfo[TextuerNumber].pTexture );
}

// 使用している全てのテクスチャの解放
void ReleaseAllTexture (void)
{
	for ( int i = 0; i < TEXTURE_MAX; i++ )
	{
		ReleaseTexture (i);
	}
}

// Direct3Dオブジェクトの解放
void ReleaseRender (void)
{
	SAFE_RELEASE(pD3Device);
	SAFE_RELEASE(pDirect3D);
}


//=========================================================================================
//
// グラフィックの座標計算
//
//========================================================================================

// 第1引数：座標計算のパターン, 第2引数：テクスチャの番号(enum eTEXTUREから), 第3引数：テクスチャの構造体,
// ここから先はANIMATIONなら入力。それ以外ならNULLで↓
// 第4,5引数：左上の頂点ｘｙ, 第6,7引数：アニメーション画像のサイズ, 第8,9引数：左上のテクスチャーUV座標ｘｙ
void SetVertex ( eSETVERTEX_PATTERN setPattern, eTEXTURE TextuerNumber, 
				float fX, float fY,	float fSize_X, float fSize_Y, float fTu, float fTv )
{
	switch ( setPattern )
	{
	case NORMAL:
		Textures[TextuerNumber][0].x = fX;
		Textures[TextuerNumber][0].y = fY;
		Textures[TextuerNumber][0].tu = 0;
		Textures[TextuerNumber][0].tv = 0;
		
		Textures[TextuerNumber][1].x = fX + TextureInfo[TextuerNumber].width;
		Textures[TextuerNumber][1].y = fY;
		Textures[TextuerNumber][1].tu = 1.0f;
		Textures[TextuerNumber][1].tv = 0;	
		
		Textures[TextuerNumber][2].x = fX + TextureInfo[TextuerNumber].width;
		Textures[TextuerNumber][2].y = fY + TextureInfo[TextuerNumber].height;
		Textures[TextuerNumber][2].tu = 1.0f;
		Textures[TextuerNumber][2].tv = 1.0f;	
		
		Textures[TextuerNumber][3].x = fX;
		Textures[TextuerNumber][3].y = fY + TextureInfo[TextuerNumber].height;
		Textures[TextuerNumber][3].tu = 0.0f;
		Textures[TextuerNumber][3].tv = 1.0f;
		
		for (int i = 0; i < 4; i++) {
			Textures[TextuerNumber][i].z = 0.f;
			Textures[TextuerNumber][i].rhw = 1.0f;
			Textures[TextuerNumber][i].color = 0xFFFFFFFF;
		}	

		break;

	case CENTER:
		Textures[TextuerNumber][0].x = fX-TextureInfo[TextuerNumber].width/ 2.f;
		Textures[TextuerNumber][0].y = fY-TextureInfo[TextuerNumber].height/ 2.f;
		Textures[TextuerNumber][0].tu = 0;
		Textures[TextuerNumber][0].tv = 0;
		
		Textures[TextuerNumber][1].x = fX + TextureInfo[TextuerNumber].width/ 2.f;
		Textures[TextuerNumber][1].y = fY - TextureInfo[TextuerNumber].height/ 2.f;
		Textures[TextuerNumber][1].tu = 1.0f;
		Textures[TextuerNumber][1].tv = 0;	
		
		Textures[TextuerNumber][2].x = fX + TextureInfo[TextuerNumber].width/ 2.f;
		Textures[TextuerNumber][2].y = fY + TextureInfo[TextuerNumber].height/ 2.f;
		Textures[TextuerNumber][2].tu = 1.0f;
		Textures[TextuerNumber][2].tv = 1.0f;	
		
		Textures[TextuerNumber][3].x = fX -  TextureInfo[TextuerNumber].width/ 2.f;
		Textures[TextuerNumber][3].y = fY + TextureInfo[TextuerNumber].height/ 2.f;
		Textures[TextuerNumber][3].tu = 0.0f;
		Textures[TextuerNumber][3].tv = 1.0f;
		
		for (int i = 0; i < 4; i++) {
			Textures[TextuerNumber][i].z = 0.f;
			Textures[TextuerNumber][i].rhw = 1.0f;
			Textures[TextuerNumber][i].color = 0xFFFFFFFF;
		}	


	case ROTATE:

		break;

	case ANIMATION:
		Textures[TextuerNumber][0].tu = (fTu + 0.5f) / TextureInfo[TextuerNumber].width;
		Textures[TextuerNumber][0].tv = (fTv + 0.5f) / TextureInfo[TextuerNumber].height;
		
		Textures[TextuerNumber][1].tu = (fTu + fSize_X + 0.5f) / TextureInfo[TextuerNumber].width;
		Textures[TextuerNumber][1].tv = (fTv + 0.5f) / TextureInfo[TextuerNumber].height;
		
		Textures[TextuerNumber][2].tu = (fTu + fSize_X + 0.5f) / TextureInfo[TextuerNumber].width;
		Textures[TextuerNumber][2].tv = (fTv + fSize_Y + 0.5f) / TextureInfo[TextuerNumber].height;
		
		Textures[TextuerNumber][3].tu = (fTu + 0.5f) / TextureInfo[TextuerNumber].width;
		Textures[TextuerNumber][3].tv = (fTv + fSize_Y + 0.5f) / TextureInfo[TextuerNumber].height;

		break;

	default:
		break;
	};	
}

void SetAlpha ( eTEXTURE TextuerNumber, int Alpha)
{
	for (int i = 0 ; i < 4 ; i++) {
		unsigned long col;
		col = Textures[TextuerNumber][i].color;
		Textures[TextuerNumber][i].color = (unsigned long)Alpha * 0x01000000 + col % 0x01000000;
	//	Textures[TextuerNumber][i].color = D3DCOLOR_ARGB(Alpha,255,255,255);
	}
}

TEXTUREINFO GetTEXTUREINFO( int TEXNUM )
{
	return TextureInfo[TEXNUM];
}

//画像サイズ取得
int GetTexWidth( int TextuerNumber )
{
	return TextureInfo [TextuerNumber].width;
}

int GetTexHeight( int TextuerNumber )
{
	return TextureInfo [TextuerNumber].height;
}
//サイズ書き換え
void SetTexSize( int TextuerNumber , float _x , float _y )
{
	TextureInfo [TextuerNumber].width = (int)_x;
	TextureInfo [TextuerNumber].height = (int)_y;
}

//----------------------------------------------------------------------
//	追加日　2/14	亀田
//	点xyが画像の中に入っているかの判定
bool	HitOfTexture ( int _x, int _y, int iTexNum )
{
	if ( _x >= Textures[iTexNum][0].x && _x <= Textures[iTexNum][1].x )
	{
		if ( _y >= Textures[iTexNum][0].y && _y <= Textures[iTexNum][2].y  ) return true;
	}
	return false;
}

//	テクスチャの色彩を変更する関数
void	ChangeColorKey ( int iR, int iG, int iB, int iTexNum )
{
	for ( int ii = 0; ii < 4; ii++ )
	{
		Textures[iTexNum][ii].color = ((unsigned long)iR * 0x0010000 + (unsigned long)iB * 0x0000001 + (unsigned long)iG * 0x00000100) - 0xFFFFFFFF;
	}
}

//	メッシュのポリゴンの頂点取得
void CL_THING::GetMeshVertex()
{
	HRESULT hr = NULL;	//	バッファ取得結果
	BYTE* pVB = NULL;	//	頂点バッファ

	DWORD numVertex;	//	頂点の数
	DWORD FVF;			//　頂点のフォーマット
	DWORD sizeVertex;	//	頂点のサイズ
	D3DXVECTOR3 vertex;	//	頂点座標

	std::vector<D3DXVECTOR3>::iterator itVec;	//	localVec操作用のイテレータ

	//	メッシュの頂点バッファーをロック
	if ( FAILED ( this->pMesh->LockVertexBuffer( D3DLOCK_READONLY, (void **)&pVB ) ) )
	{

	}

	numVertex = this->pMesh->GetNumVertices();	//	頂点の数の取得
	FVF = this->pMesh->GetFVF();					//	フォーマット情報の取得
	sizeVertex = D3DXGetFVFVertexSize( FVF );		//　フォーマットを元に頂点のサイズを取得

	for( DWORD i = 0; i < numVertex; i++ )
	{
		vertex = *(D3DXVECTOR3*)pVB;
		pVB += sizeVertex;
		this->localVec.push_back(vertex);
	}

	//	メッシュの頂点バッファーをアンロック
	if ( FAILED ( this->pMesh->UnlockVertexBuffer() ) )
	{

	} 
}

//------------------------------------------------------------------
//	スクリーン座標をワールド座標に変換する
//	制作日	12/12	
//------------------------------------------------------------------
// スクリーン座標をワールド座標に変換
D3DXVECTOR3* CalcScreenToWorld
(
   D3DXVECTOR3* pout,	
   int Sx,				//	スクリーン座標内ｘ
   int Sy,				//	スクリーン座標内ｙ
   float fZ,			//	射影空間でのZ値（0～1）
   int Screen_w,		//	スクリーンの横幅
   int Screen_h,		//	スクリーンの縦幅
   D3DXMATRIXA16* View,	//	ビュー行列
   D3DXMATRIXA16* Prj	//	射影変換行列
)
{
   // 各行列の逆行列を算出
   D3DXMATRIXA16 InvView, InvPrj, VP, InvViewport;
   D3DXMatrixInverse( &InvView, NULL, View );
   D3DXMatrixInverse( &InvPrj, NULL, Prj );
   D3DXMatrixIdentity( &VP );
   VP._11 = Screen_w/2.0f; VP._22 = -Screen_h/2.0f;
   VP._41 = Screen_w/2.0f; VP._42 = Screen_h/2.0f;
   D3DXMatrixInverse( &InvViewport, NULL, &VP );

   // 逆変換
   D3DXMATRIXA16 tmp = InvViewport * InvPrj * InvView;
   D3DXVec3TransformCoord( pout, &D3DXVECTOR3((float)Sx,(float)Sy,fZ), &tmp );

   return pout;
}

//--------------------------------------------------------------------
//	スクリーン座標とXZ平面のワールド座標交点算出
D3DXVECTOR3* CalcScreenToXZ(
   D3DXVECTOR3* pout,
   int Sx,
   int Sy,
   int Screen_w,
   int Screen_h,
   D3DXMATRIXA16* View,
   D3DXMATRIXA16* Prj	)
{
   D3DXVECTOR3 nearpos;
   D3DXVECTOR3 farpos;
   D3DXVECTOR3 ray;
   CalcScreenToWorld( &nearpos, Sx, Sy, 0.0f, Screen_w, Screen_h, View, Prj );
   CalcScreenToWorld( &farpos, Sx, Sy, 1.0f, Screen_w, Screen_h, View, Prj );
   ray = farpos - nearpos;
   D3DXVec3Normalize( &ray, &ray );

   // 床との交差が起きている場合は交点を
   // 起きていない場合は遠くの壁との交点を出力
   if( ray.y <= 0 ) {
      // 床交点
      float Lray = D3DXVec3Dot( &ray, &D3DXVECTOR3(0,1,0) );
      float LP0 = D3DXVec3Dot( &(-nearpos), &D3DXVECTOR3(0,1,0) );
      *pout = nearpos + (LP0/Lray)*ray;
   }
   else {
      *pout = farpos;
   }

   return pout;
}


// 指定したベクトルへ向かせる行列算出関数
D3DXMATRIX* CalcLookAtMatrix(
   D3DXMATRIX* pout,
   D3DXVECTOR3* pPos,
   D3DXVECTOR3* pLook,
   D3DXVECTOR3* pUp)
{
   D3DXVECTOR3 X, Y, Z;
   Z = *pLook - *pPos;
   D3DXVec3Normalize( &Z, &Z );
   D3DXVec3Cross( &X, D3DXVec3Normalize(&Y, pUp), &Z );
   D3DXVec3Normalize( &X, &X );
   D3DXVec3Normalize( &Y, D3DXVec3Cross( &Y, &Z, &X ));


   pout->_11 = X.x; pout->_12 = X.y; pout->_13 = X.z; pout->_14 = 0;
   pout->_21 = Y.x; pout->_22 = Y.y; pout->_23 = Y.z; pout->_24 = 0;
   pout->_31 = Z.x; pout->_32 = Z.y; pout->_33 = Z.z; pout->_34 = 0;
   pout->_41 = 0.0f; pout->_42 = 0.0f; pout->_43 = 0.0f; pout->_44 = 1.0f;

   return pout;
}

//	Y軸回転行列
D3DXVECTOR3 RotateYMatrix ( D3DXVECTOR3* pVec, float _y )
{
	float x = pVec -> x * cos( _y ) + pVec -> z  * sin(_y );
	float y = pVec -> y;
	float z = pVec -> x * -sin( _y ) + pVec -> z * cos( _y );

	return D3DXVECTOR3 ( x , y , z );	
}

//	モデルの頂点座標のワールド座標変換(test)
//	モデルの回転度：rx,ry,rz
//	モデルの拡縮：sx,sy,sz
//	モデルの基準点(親)：px,py,pz
//	モデルの頂点(子)：l_v_px,l_v_py,l_v_pz
D3DXVECTOR3 CL_THING::LocalToWarldTransform( float rx, float ry, float rz,
					 float sx, float sy, float sz,
					 float px, float py, float pz,
					 float l_v_px, float l_v_py, float l_v_pz )
{
	//ワールドトランスフォーム(絶対座標変換)
	//matWorld->y軸回転
	D3DXMATRIXA16	matWorld, matPosition, matScall, matRoate, matVecPos;
	//[最終的なワールドトランスフォーム][平行移動行列を格納する行列]
	D3DXMatrixIdentity(&matWorld);								//単位行列の作成関数
	D3DXMatrixRotationYawPitchRoll(&matRoate, ry, rx, rz);		//回転行列の作成関数
	D3DXMatrixScaling(&matScall, sx, sy, sz);					//拡大行列の作成関数
	D3DXMatrixTranslation(&matPosition, px, py, pz);			//親の平行移動行列の作成関数
	D3DXMatrixTranslation(&matVecPos, l_v_px, l_v_py, l_v_pz);	//子の平行移動行列の作成関数
	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matRoate);		//	行列を結合する関数(第2引数x第3引数=>第1引数に格納)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matVecPos);		//	行列を結合する関数(第2引数x第3引数=>第1引数に格納)
	D3DXMatrixMultiply(&matWorld,&matWorld,&matRoate);		//	行列を結合する関数(第2引数x第3引数=>第1引数に格納)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matScall);		//	行列を結合する関数(第2引数x第3引数=>第1引数に格納)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matPosition);	//	行列を結合する関数(第2引数x第3引数=>第1引数に格納)
	
	return D3DXVECTOR3( matWorld._41, matWorld._42, matWorld._43 );
}

//ベクトルの長さ
float GetVectorLength( D3DXVECTOR3 _v ) {
	return pow( ( _v.x * _v.x ) + ( _v.y * _v.y ) + ( _v.z * _v.z ) , 0.5f );
}