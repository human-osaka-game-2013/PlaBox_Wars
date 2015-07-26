#pragma once
#include "scene.h"


//	ƒƒS‚ÌƒNƒ‰ƒX
class CL_LOGO:public CL_MANAGE_SCENE
{
public:
	void Init ();		//	ƒƒS‚Ì‰Šú‰»
	void Control ();	//	ƒƒS‚Ìˆ—
	void Render ();	//	ƒƒS‚Ì3D•`‰æ
	void Draw ();		//	ƒƒS‚Ì2D•`‰æ
	void Release();
private:
	int Alpha;
};
