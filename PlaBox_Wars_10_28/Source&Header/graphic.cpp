#include <math.h>

#include "main.h"
#include "graphic.h"
#include "camera.h"
#include "input.h"

IDirect3D9*			pDirect3D;
IDirect3DDevice9*	pD3Device; //�f�o�C�X�I�u�W�F�N�g

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
//	�O���t�B�b�N�̏�����
//
//==================================================================================

// Direct3D�̏�����
// ��1�����F�E�C���h�n���h��
bool InitRender ( HWND hWnd )
{
	D3DDISPLAYMODE d3ddm;
	
	// [Direct3D] �I�u�W�F�N�g�̍쐬
	if( NULL == (pDirect3D = Direct3DCreate9 (D3D_SDK_VERSION) ) )		
	{
		MessageBox(0,"Direct3D�̍쐬�Ɏ��s���܂���","",MB_OK);
		return false;
	}

	// Display Mode �̐ݒ�
	pDirect3D -> GetAdapterDisplayMode ( D3DADAPTER_DEFAULT, &d3ddm );

	ZeroMemory(	&d3dpp, sizeof ( D3DPRESENT_PARAMETERS ));

	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount  = 1;
	d3dpp.SwapEffect	   = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed		   = TRUE;

	////�t���X�N���[���ɂ���ꍇ////////////////////////////////////
	//D3DDISPLAYMODE DMode;
	//pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &DMode);
	//d3dpp.BackBufferFormat	= DMode.Format;
	//d3dpp.BackBufferWidth	= Win_Width;
	//d3dpp.BackBufferHeight	= Win_Height;
	//d3dpp.BackBufferCount	= 1;
	//d3dpp.SwapEffect		= D3DSWAPEFFECT_DISCARD;
	//d3dpp.Windowed		= FALSE;
	////////////////////////////////////////////////////////////////

	d3dpp.EnableAutoDepthStencil	= TRUE;			// Z�o�b�t�@�g�p�m�F
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;	// �t�H�[�}�b�g�֐��w��

	if(FAILED (pDirect3D->CreateDevice (
			D3DADAPTER_DEFAULT,					//�r�f�I�J�[�h�ݒ�(�������ڂłȂ����肱�̌`��)
			D3DDEVTYPE_HAL,						//HAL->�n�[�h�E�F�A�@�\�ŕ\��
			hWnd,								//�E�C���h�E�E�n���h��
			D3DCREATE_MIXED_VERTEXPROCESSING,		//�r�f�I�J�[�h�̃~�b�N�X���_����
												//���s�ł��Ȃ��ꍇ�E�E�E_SOFTWARE_ or _HARDWARE �ɐؑ�
			&d3dpp,								//D3DPRESENT_PARAMETERS�ϐ��̃A�h���X
			&pD3Device								//���e��̃f�o�C�X�I�u�W�F�N�g�ւ̃|�C���^�ϐ��̃A�h���X
												//	--> CreateDevice�֐��R�[����ɃA�h���X���i�[����g����悤�ɂȂ�
			) ) )
	{
		MessageBox(0,"HAL(�������[�h)��DIRECT3D�f�o�C�X���쐬�ł��܂���\nREF���[�h�ōĎ��s���܂�",NULL,MB_OK);
		if(FAILED	 (pDirect3D->CreateDevice (
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_MIXED_VERTEXPROCESSING,
				&d3dpp,
				&pD3Device
				) ) )
		{
			MessageBox(0,"DIRECT3D�f�o�C�X�̍쐬�Ɏ��s���܂���",NULL,MB_OK);
			return false;
		}
	}					
	return true;									
}													

//=====================================================================================
//
//	�e�N�X�`���A���b�V���̓ǂݍ���
//
//======================================================================================
// �e�N�X�`���̓ǂݍ���
// ��1�����F("�摜�̖��O.�g���q"), ��2�����F�e�N�X�`���̔ԍ�(enum eTEXTURE����), ���ߐFRGB 
bool LoadTexture ( LPCSTR lpFileName, eTEXTURE TextuerNumber, int iColorRed, int iColorGreen, int iColorBlue )
{
	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(lpFileName, &info);
	// �e�N�X�`�������ɓǂݍ���ł���ꍇ�͂����ŉ������
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

	// �e�N�X�`�����擾
	D3DSURFACE_DESC desc;

	TextureInfo [TextuerNumber].pTexture -> GetLevelDesc ( 0, &desc );
	TextureInfo [TextuerNumber].width = desc.Width;
	TextureInfo [TextuerNumber].height = desc.Height;

	return true;
}

//���b�V���̓Ǎ������`��o�b�t�@
bool CL_THING::LoadThingFile(CL_THING *pThing,LPCSTR szXFileName,D3DXVECTOR3* pvecPosition, D3DXVECTOR3* pvecScall, D3DXVECTOR3* pvecRotate)
{
	//���b�V���̏����ʒu
	memcpy(&pThing->vecPosition,pvecPosition,sizeof(D3DXVECTOR3));
	//���b�V���̏����{��
	memcpy(&pThing->vecScall,pvecScall,sizeof(D3DXVECTOR3));
	//���b�V���̏�������
	memcpy(&pThing->vecRotate,pvecRotate,sizeof(D3DXVECTOR3));

	//x�t�@�C�����烁�b�V�������[�h����
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
		MessageBox(NULL,"x�t�@�C���̓ǂݍ��݂Ɏ��s���܂���",szXFileName,MB_OK);
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
				MessageBox(NULL,"�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���",NULL,MB_OK);
			}
		}
	}

	
	pD3DXMtrlBuffer->Release();
	return true;
}

//==================================================================================
//
//	�`�揈��
//
//==================================================================================

// 3D�`��O����
void BeginRender (void)
{
	if ( !pD3Device ) return;

	pD3Device->SetRenderState( D3DRS_ZENABLE, TRUE );			// Z�o�b�t�@�[������L����
//	pD3Device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );	// �J�����O���Ȃ�
	pD3Device->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );	// �J�����O����
	pD3Device->SetRenderState( D3DRS_LIGHTING, TRUE );			// ���C�g��L����
	pD3Device->SetRenderState( D3DRS_AMBIENT, 0x00000000 );		// �A���r�G���g���C�g(����)��ݒ�
	pD3Device->SetRenderState( D3DRS_SPECULARENABLE, TRUE );	// �X�y�L����(���ʔ���)��L����

	pD3Device->LightEnable(0, TRUE);

	// ��ʂ̏���
	pD3Device -> Clear ( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ,
						D3DCOLOR_XRGB ( 0x00, 0x00, 0x00 ),
						1.0f, 0 );

	// �`��̊J�n
	pD3Device -> BeginScene();
}

// 2D�`��O����
void BeginDraw (void)
{
	if ( !pD3Device ) return;

	// �X�e�[�W�X�e�[�g�̐ݒ�
	pD3Device -> SetTextureStageState ( 0, D3DTSS_ALPHAOP,		D3DTOP_MODULATE );
	pD3Device -> SetTextureStageState ( 0, D3DTSS_COLORARG1,	D3DTA_TEXTURE	);
	pD3Device -> SetTextureStageState ( 0, D3DTSS_COLORARG2,	D3DTA_DIFFUSE	);

	// �`����@�̐ݒ�
	pD3Device -> SetRenderState ( D3DRS_ALPHABLENDENABLE, true );
	pD3Device -> SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	pD3Device -> SetRenderState ( D3DRS_ZENABLE, true );
	
	// �`��̊J�n
	pD3Device -> BeginScene();

	// ��ʂ̕`��
	pD3Device -> SetFVF ( D3DFVF_CUSTOMVERTEX );
}
//------------------------------------------------------------------------------
//
//	�e�N�X�`���`�揈��
//	��1�����F�e�N�X�`���̍\����, ��2�����F�e�N�X�`���̔ԍ�(enum eTEXTURE����)
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
// �����ŏk��
// ��1�����F�e�N�X�`���̔ԍ�(enum eTEXTURE����)
// ��2�����F�e�N�X�`���̏k��  1.0f�œǂݍ��ݎ��̑傫��
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
	x = vertex[ 2 ].x - vertex[ 0 ].x; // ���̒���
	y = vertex[ 2 ].y - vertex[ 0 ].y; // �c�̒���

	x *= Scall;	//�X�P�[�����|���āA������ω�������
	y *= Scall; //�X�P�[�����|���āA�c����ω�������

	vertex[ 1 ].x = vertex[ 2 ].x = vertex[ 0 ].x + x; // 0�Ԃ���ɃX�P�[���������������𑫂�
	vertex[ 2 ].y = vertex[ 3 ].y = vertex[ 0 ].y + y; // 0�Ԃ���ɃX�P�[�����������c���𑫂�

	pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		vertex,
		sizeof ( CUSTOMVERTEX ) );
}


/*
	�`�掞�ϊ��s��
*/
void RenderMatrix( bool* _p_bMatrixInit )
{
	static D3DXMATRIXA16	matView;
	//�v���W�F�N�V�����g�����X�t�H�[��(�ˉe�ϊ�)
	static D3DXMATRIXA16	matProj;
		
	if( *_p_bMatrixInit )
	{
		//�r���[�g�����X�t�H�[��
		//D3DXVECTOR3...3���̍s�x�N�g��
		//D3DXMATRIXA16...4x4�̍s��
		//�����_��J�����ʒu��camera.cpp�������Ă���
		D3DXVECTOR3 eyePos	= GetEyePos();
		D3DXVECTOR3 lookPos	= GetLookPos();
		float		radian	= GetRad();

		D3DXVECTOR3	vecEyePt	( eyePos );		//�J����(���_)�ʒu
		D3DXVECTOR3	vecLookatPt	( lookPos );	//�����ʒu
		D3DXVECTOR3	vecUpVec	(0.0f, 1.0f, 0.0f);		//����ʒu
		
		D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	
		//�����_�X�V
		lookPos	 = vecLookatPt;

		//	�ύX���܂���	12/13
		D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.6f, 0.9f, 200.0f);
		//--------------------------------------------------------------------
	
		//���C�g�����Ă�@���F�ŋ��ʔ��˗L��ɐݒ�
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
	�|���S���`��֐�
*/
void PolygonRender( CUSTOMVERTEX* _pVertex, D3DXVECTOR3 _refPos, D3DXVECTOR3 _refRot, D3DXVECTOR3 _refSca,
	eTEXTURE _TextuerNumber, bool* _p_bMatrixInit )
{
	//���[���h�g�����X�t�H�[��(��΍��W�ϊ�)
	//matWorld->y����]
	D3DXMATRIXA16	matWorld,matPosition, matScall, matRoate;	//[�ŏI�I�ȃ��[���h�g�����X�t�H�[��][���s�ړ��s����i�[����s��]
	D3DXMatrixIdentity(&matWorld);								//�P�ʍs��̍쐬�֐�
	D3DXMatrixRotationYawPitchRoll(&matRoate, _refRot.y, _refRot.x, _refRot.z);	///	@todo���݂͎����I�ɒl���Z�b�g
	D3DXMatrixScaling(&matScall, _refSca.x, _refSca.y, _refSca.z);				///	@todo���݂͎����I�ɒl���Z�b�g
	D3DXMatrixTranslation(&matPosition, _refPos.x, _refPos.y, _refPos.z);			///	@todo���݂͎����I�ɒl���Z�b�g

	D3DXMatrixMultiply(&matWorld,&matWorld,&matRoate);		//�s�����������	(��΍��W�s��x��]�s��)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matScall);		//�s�����������֐�(��΍��W�s��x�g��s��)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matPosition);	//�s�����������֐�(��΍��W�s��x���s�ړ��s��s��)

	//�D3DTS_WORLD(���[���h�g�����X�t�H�[��)���matWorld�s����W���Ƃ��ģ�l�X�Ȏ�ނ̕ϊ����s�����Ƃ������_�����O�p�C�v���C��/Direct3D�ɒʒm
	pD3Device->SetTransform(D3DTS_WORLD, &matWorld);

	RenderMatrix( _p_bMatrixInit );

	pD3Device -> SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	pD3Device->SetTexture( 0, TextureInfo[_TextuerNumber].pTexture);	///	@todo	���݂͎����I�ɕʂ̃e�N�X�`�������Ă���B 
	pD3Device->DrawPrimitiveUP( D3DPT_TRIANGLEFAN,
		2,
		_pVertex,
		sizeof( CUSTOMVERTEX )
		);
}

//---------------------------------------------------------------------------
//
//	���b�V���`�揈��
//
//----------------------------------------------------------------------------
void CL_THING::Transform(CL_THING* pThing)
{
	//���[���h�g�����X�t�H�[��(��΍��W�ϊ�)
	//matWorld->y����]
	D3DXMATRIXA16	matWorld,matPosition, matScall, matRoate;						//[�ŏI�I�ȃ��[���h�g�����X�t�H�[��][���s�ړ��s����i�[����s��]
	D3DXMatrixIdentity(&matWorld);												//�P�ʍs��̍쐬�֐�
	D3DXMatrixRotationYawPitchRoll(&matRoate, pThing->vecRotate.y, pThing->vecRotate.x, pThing->vecRotate.z);	//��]�s��̍쐬�֐�
	D3DXMatrixScaling(&matScall, pThing->vecScall.x, pThing->vecScall.y, pThing->vecScall.z);					//�g��s��̍쐬�֐�
	D3DXMatrixTranslation(&matPosition, pThing->vecPosition.x, pThing->vecPosition.y, pThing->vecPosition.z);	//���s�ړ��s��̍쐬�֐�

	D3DXMatrixMultiply(&matWorld,&matWorld,&matRoate);								//�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matScall);								//�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matPosition);							//�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)

	//�D3DTS_WORLD(���[���h�g�����X�t�H�[��)���matWorld�s����W���Ƃ��ģ�l�X�Ȏ�ނ̕ϊ����s�����Ƃ������_�����O�p�C�v���C��/Direct3D�ɒʒm
	pD3Device->SetTransform(D3DTS_WORLD, &matWorld);

	//�r���[�g�����X�t�H�[��
	//D3DXVECTOR3...3���̍s�x�N�g��
	//D3DXMATRIXA16...4x4�̍s��
	//�����_��J�����ʒu��camera.cpp�������Ă���
	D3DXVECTOR3 eyePos	= GetEyePos();
	D3DXVECTOR3 lookPos	= GetLookPos();
	float		radian	= GetRad();

	D3DXVECTOR3	vecEyePt	( eyePos );		//�J����(���_)�ʒu
	D3DXVECTOR3	vecLookatPt	( lookPos );	//�����ʒu
	D3DXVECTOR3	vecUpVec	(0.0f, 1.0f, 0.0f);		//����ʒu
	D3DXMATRIXA16	matView;
	D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	pD3Device->SetTransform(D3DTS_VIEW, &matView);

	//�����_�X�V
	lookPos	 = vecLookatPt;

	//�v���W�F�N�V�����g�����X�t�H�[��(�ˉe�ϊ�)
	D3DXMATRIXA16	matProj;

	//	�ύX���܂���	12/13
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.6f, 0.9f, 200.0f);
	//--------------------------------------------------------------------
	
	pD3Device->SetTransform(D3DTS_PROJECTION, &matProj);

	//���C�g�����Ă�@���F�ŋ��ʔ��˗L��ɐݒ�
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

	//�����_�����O
	for(DWORD i=0;	i < pThing->dwNumMaterials ; i++)
	{
		pD3Device->SetMaterial(&pThing->pMeshMaterials[i]);
		pD3Device->SetTexture(0,pThing->pMeshTextures[i]);
		pThing->pMesh->DrawSubset(i);
	}

}

//	�r���{�[�h�p�̃��b�V���`��
void CL_THING::BillboardingTransform(CL_THING* pThing)
{
	//���[���h�g�����X�t�H�[���i��΍��W�ϊ��j
	 D3DXMATRIXA16 matWorld,matCurrentView,matPosition;
	 D3DXMatrixIdentity(&matWorld);
	 D3DXMatrixTranslation(&matPosition,pThing->vecPosition.x,pThing->vecPosition.y,
		 pThing->vecPosition.z);
	 D3DXMatrixMultiply(&matWorld,&matWorld,&matPosition);
	 //���݂̃r���[�s��𓾂āA�A
	 pD3Device->GetTransform(D3DTS_VIEW,&matCurrentView);
	 // ������t�s��ɂ��āA�A
	 D3DXMatrixInverse(&matCurrentView,NULL,&matCurrentView);
	 // ���[���h�s��Ɋ|�����킹��ƁA�r���[�ϊ���ł��������ƂɂȂ�
	 D3DXMatrixMultiply(&matWorld,&matWorld,&matCurrentView);

     pD3Device->SetTransform( D3DTS_WORLD, &matWorld );
	 
	 //�r���[�g�����X�t�H�[��
	//D3DXVECTOR3...3���̍s�x�N�g��
	//D3DXMATRIXA16...4x4�̍s��
	//�����_��J�����ʒu��camera.cpp�������Ă���
	D3DXVECTOR3 eyePos	= GetEyePos();
	D3DXVECTOR3 lookPos	= GetLookPos();
	float		radian	= GetRad();

	D3DXVECTOR3	vecEyePt	( eyePos );		//�J����(���_)�ʒu
	D3DXVECTOR3	vecLookatPt	( lookPos );	//�����ʒu
	D3DXVECTOR3	vecUpVec	(0.0f, 1.0f, 0.0f);		//����ʒu
	D3DXMATRIXA16	matView;
	D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	pD3Device->SetTransform(D3DTS_VIEW, &matView);

	//�����_�X�V
	lookPos	 = vecLookatPt;

	//�v���W�F�N�V�����g�����X�t�H�[��(�ˉe�ϊ�)
	D3DXMATRIXA16	matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.6f, 0.9f, 100.0f);
	pD3Device->SetTransform(D3DTS_PROJECTION, &matProj);

	//���C�g�����Ă�@���F�ŋ��ʔ��˗L��ɐݒ�
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

	//�����_�����O
	for(DWORD i=0;	i < pThing->dwNumMaterials ; i++)
	{
		pD3Device->SetMaterial(&pThing->pMeshMaterials[i]);
		pD3Device->SetTexture(0,pThing->pMeshTextures[i]);
		pThing->pMesh->DrawSubset(i);
	}
}

//----------------------------------------------------------------------------
//
// �`��㏈��
//
//----------------------------------------------------------------------------
void EndRender (void)
{
	// �`��̏I��
	pD3Device -> EndScene();
}

//===============================================================================
//
//	���
//
//============================================================================

// �e�N�X�`���̉��
// ��1�����F�e�N�X�`���̔ԍ�(enum eTEXTURE����)
void ReleaseTexture ( int TextuerNumber )
{
	SAFE_RELEASE ( TextureInfo[TextuerNumber].pTexture );
}

// �g�p���Ă���S�Ẵe�N�X�`���̉��
void ReleaseAllTexture (void)
{
	for ( int i = 0; i < TEXTURE_MAX; i++ )
	{
		ReleaseTexture (i);
	}
}

// Direct3D�I�u�W�F�N�g�̉��
void ReleaseRender (void)
{
	SAFE_RELEASE(pD3Device);
	SAFE_RELEASE(pDirect3D);
}


//=========================================================================================
//
// �O���t�B�b�N�̍��W�v�Z
//
//========================================================================================

// ��1�����F���W�v�Z�̃p�^�[��, ��2�����F�e�N�X�`���̔ԍ�(enum eTEXTURE����), ��3�����F�e�N�X�`���̍\����,
// ����������ANIMATION�Ȃ���́B����ȊO�Ȃ�NULL�Ł�
// ��4,5�����F����̒��_����, ��6,7�����F�A�j���[�V�����摜�̃T�C�Y, ��8,9�����F����̃e�N�X�`���[UV���W����
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

//�摜�T�C�Y�擾
int GetTexWidth( int TextuerNumber )
{
	return TextureInfo [TextuerNumber].width;
}

int GetTexHeight( int TextuerNumber )
{
	return TextureInfo [TextuerNumber].height;
}
//�T�C�Y��������
void SetTexSize( int TextuerNumber , float _x , float _y )
{
	TextureInfo [TextuerNumber].width = (int)_x;
	TextureInfo [TextuerNumber].height = (int)_y;
}

//----------------------------------------------------------------------
//	�ǉ����@2/14	�T�c
//	�_xy���摜�̒��ɓ����Ă��邩�̔���
bool	HitOfTexture ( int _x, int _y, int iTexNum )
{
	if ( _x >= Textures[iTexNum][0].x && _x <= Textures[iTexNum][1].x )
	{
		if ( _y >= Textures[iTexNum][0].y && _y <= Textures[iTexNum][2].y  ) return true;
	}
	return false;
}

//	�e�N�X�`���̐F�ʂ�ύX����֐�
void	ChangeColorKey ( int iR, int iG, int iB, int iTexNum )
{
	for ( int ii = 0; ii < 4; ii++ )
	{
		Textures[iTexNum][ii].color = ((unsigned long)iR * 0x0010000 + (unsigned long)iB * 0x0000001 + (unsigned long)iG * 0x00000100) - 0xFFFFFFFF;
	}
}

//	���b�V���̃|���S���̒��_�擾
void CL_THING::GetMeshVertex()
{
	HRESULT hr = NULL;	//	�o�b�t�@�擾����
	BYTE* pVB = NULL;	//	���_�o�b�t�@

	DWORD numVertex;	//	���_�̐�
	DWORD FVF;			//�@���_�̃t�H�[�}�b�g
	DWORD sizeVertex;	//	���_�̃T�C�Y
	D3DXVECTOR3 vertex;	//	���_���W

	std::vector<D3DXVECTOR3>::iterator itVec;	//	localVec����p�̃C�e���[�^

	//	���b�V���̒��_�o�b�t�@�[�����b�N
	if ( FAILED ( this->pMesh->LockVertexBuffer( D3DLOCK_READONLY, (void **)&pVB ) ) )
	{

	}

	numVertex = this->pMesh->GetNumVertices();	//	���_�̐��̎擾
	FVF = this->pMesh->GetFVF();					//	�t�H�[�}�b�g���̎擾
	sizeVertex = D3DXGetFVFVertexSize( FVF );		//�@�t�H�[�}�b�g�����ɒ��_�̃T�C�Y���擾

	for( DWORD i = 0; i < numVertex; i++ )
	{
		vertex = *(D3DXVECTOR3*)pVB;
		pVB += sizeVertex;
		this->localVec.push_back(vertex);
	}

	//	���b�V���̒��_�o�b�t�@�[���A�����b�N
	if ( FAILED ( this->pMesh->UnlockVertexBuffer() ) )
	{

	} 
}

//------------------------------------------------------------------
//	�X�N���[�����W�����[���h���W�ɕϊ�����
//	�����	12/12	
//------------------------------------------------------------------
// �X�N���[�����W�����[���h���W�ɕϊ�
D3DXVECTOR3* CalcScreenToWorld
(
   D3DXVECTOR3* pout,	
   int Sx,				//	�X�N���[�����W����
   int Sy,				//	�X�N���[�����W����
   float fZ,			//	�ˉe��Ԃł�Z�l�i0�`1�j
   int Screen_w,		//	�X�N���[���̉���
   int Screen_h,		//	�X�N���[���̏c��
   D3DXMATRIXA16* View,	//	�r���[�s��
   D3DXMATRIXA16* Prj	//	�ˉe�ϊ��s��
)
{
   // �e�s��̋t�s����Z�o
   D3DXMATRIXA16 InvView, InvPrj, VP, InvViewport;
   D3DXMatrixInverse( &InvView, NULL, View );
   D3DXMatrixInverse( &InvPrj, NULL, Prj );
   D3DXMatrixIdentity( &VP );
   VP._11 = Screen_w/2.0f; VP._22 = -Screen_h/2.0f;
   VP._41 = Screen_w/2.0f; VP._42 = Screen_h/2.0f;
   D3DXMatrixInverse( &InvViewport, NULL, &VP );

   // �t�ϊ�
   D3DXMATRIXA16 tmp = InvViewport * InvPrj * InvView;
   D3DXVec3TransformCoord( pout, &D3DXVECTOR3((float)Sx,(float)Sy,fZ), &tmp );

   return pout;
}

//--------------------------------------------------------------------
//	�X�N���[�����W��XZ���ʂ̃��[���h���W��_�Z�o
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

   // ���Ƃ̌������N���Ă���ꍇ�͌�_��
   // �N���Ă��Ȃ��ꍇ�͉����̕ǂƂ̌�_���o��
   if( ray.y <= 0 ) {
      // ����_
      float Lray = D3DXVec3Dot( &ray, &D3DXVECTOR3(0,1,0) );
      float LP0 = D3DXVec3Dot( &(-nearpos), &D3DXVECTOR3(0,1,0) );
      *pout = nearpos + (LP0/Lray)*ray;
   }
   else {
      *pout = farpos;
   }

   return pout;
}


// �w�肵���x�N�g���֌�������s��Z�o�֐�
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

//	Y����]�s��
D3DXVECTOR3 RotateYMatrix ( D3DXVECTOR3* pVec, float _y )
{
	float x = pVec -> x * cos( _y ) + pVec -> z  * sin(_y );
	float y = pVec -> y;
	float z = pVec -> x * -sin( _y ) + pVec -> z * cos( _y );

	return D3DXVECTOR3 ( x , y , z );	
}

//	���f���̒��_���W�̃��[���h���W�ϊ�(test)
//	���f���̉�]�x�Frx,ry,rz
//	���f���̊g�k�Fsx,sy,sz
//	���f���̊�_(�e)�Fpx,py,pz
//	���f���̒��_(�q)�Fl_v_px,l_v_py,l_v_pz
D3DXVECTOR3 CL_THING::LocalToWarldTransform( float rx, float ry, float rz,
					 float sx, float sy, float sz,
					 float px, float py, float pz,
					 float l_v_px, float l_v_py, float l_v_pz )
{
	//���[���h�g�����X�t�H�[��(��΍��W�ϊ�)
	//matWorld->y����]
	D3DXMATRIXA16	matWorld, matPosition, matScall, matRoate, matVecPos;
	//[�ŏI�I�ȃ��[���h�g�����X�t�H�[��][���s�ړ��s����i�[����s��]
	D3DXMatrixIdentity(&matWorld);								//�P�ʍs��̍쐬�֐�
	D3DXMatrixRotationYawPitchRoll(&matRoate, ry, rx, rz);		//��]�s��̍쐬�֐�
	D3DXMatrixScaling(&matScall, sx, sy, sz);					//�g��s��̍쐬�֐�
	D3DXMatrixTranslation(&matPosition, px, py, pz);			//�e�̕��s�ړ��s��̍쐬�֐�
	D3DXMatrixTranslation(&matVecPos, l_v_px, l_v_py, l_v_pz);	//�q�̕��s�ړ��s��̍쐬�֐�
	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matRoate);		//	�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matVecPos);		//	�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)
	D3DXMatrixMultiply(&matWorld,&matWorld,&matRoate);		//	�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matScall);		//	�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)	
	D3DXMatrixMultiply(&matWorld,&matWorld,&matPosition);	//	�s�����������֐�(��2����x��3����=>��1�����Ɋi�[)
	
	return D3DXVECTOR3( matWorld._41, matWorld._42, matWorld._43 );
}

//�x�N�g���̒���
float GetVectorLength( D3DXVECTOR3 _v ) {
	return pow( ( _v.x * _v.x ) + ( _v.y * _v.y ) + ( _v.z * _v.z ) , 0.5f );
}