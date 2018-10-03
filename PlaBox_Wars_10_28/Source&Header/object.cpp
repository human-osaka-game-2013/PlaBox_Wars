#include "object.h"

void CL_WALL::CharaInit ( int iCharaArrey )
{
	LoadThingFile(&object[SKY],"Texture\\Xfile\\tennai.x",&D3DXVECTOR3(0,-0.5f,0), &D3DXVECTOR3(1.f,1.f,1.f), &D3DXVECTOR3(0.f,0.f,0.f));
//	LoadThingFile(&object[GROUND],"Texture\\Xfile\\Ground.x", &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(1.5f,1.5f,1.5f), &D3DXVECTOR3(0.f,0.f,0.f));
	LoadThingFile(&object[ITEM],"Texture\\Xfile\\bottle.X",&D3DXVECTOR3(5,0,15), &D3DXVECTOR3(0.3f,0.5f,0.3f), &D3DXVECTOR3(0.f,0.f,0.f));

	object[ITEM].deadFlag = false;
	//	�ǉ����܂����@12/13
//	LoadThingFile(&object[WALL1],"Texture\\Xfile\\kabe.x", &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(0.05f,0.05f,0.05f), &D3DXVECTOR3(0.f,0.f,0.f));
}

void CL_WALL::CharaControl ( int iCharaArrey )	
{
	
}

void CL_WALL::CharaRender ( int iCharaArrey )	
{
	Transform ( &object[iCharaArrey] );
}

//	���b�V���̉��
void CL_WALL::FreeMesh()
{
	
	//���b�V�����
	SAFE_RELEASE( pMesh );
	SAFE_RELEASE( BBox.pBBoxMesh );
	
	//�e�N�X�`�����
	for( DWORD i=0; i<  dwNumMaterials; i++ )
	{
		SAFE_RELEASE( pMeshTextures[i] );
	}
	 
	//�z����
	NULL_ARRAY_DELETE( pMeshTextures);
	NULL_ARRAY_DELETE( pMeshMaterials);
	NULL_ARRAY_DELETE( BBox.pBBoxMeshMaterials);
}

void CL_HOLE::CharaInit ( int iCharaArrey )
{
	this -> deadFlag = true;
	this -> vecPosOfTarget.x = 0.f;
	this -> vecPosOfTarget.y = 0.f;
	this -> vecPosOfTarget.z = 0.f;
}

void CL_HOLE::CharaControl ( int iCharaArrey )	
{
//	this -> vecPosition += this -> vecPosOfTarget;
}

void CL_HOLE::CharaRender ( int iCharaArrey )	
{
	//	�ύX���܂����@2/11�@�T�c
	if ( !storm.deadFlag )
	{
		Transform(&storm);
	}
}

//	���b�V���̉��
void CL_HOLE::FreeMesh()
{
	//���b�V�����
	SAFE_RELEASE( this->pMesh );
	SAFE_RELEASE( this->BBox.pBBoxMesh );

	//�e�N�X�`�����
	for( DWORD i=0; i<this->dwNumMaterials; i++ )
	{
		SAFE_RELEASE( this->pMeshTextures[i] );
	}
	 
	//�z����
	NULL_ARRAY_DELETE(this->pMeshTextures);
	NULL_ARRAY_DELETE(this->pMeshMaterials);
	NULL_ARRAY_DELETE(this->BBox.pBBoxMeshMaterials);
}