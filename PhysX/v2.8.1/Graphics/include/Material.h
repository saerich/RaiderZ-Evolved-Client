#ifndef _SG_MATERIAL_H__
#define _SG_MATERIAL_H__

/*----------------------------------------------------------------------------*\
|
|						     Ageia PhysX Technology
|
|							     www.ageia.com
|
\*----------------------------------------------------------------------------*/


#include <string>



namespace SceneGraph
	{
class Texture;

class Material
	{
	public:
	Material();
	~Material();

	void load(const char * fname);

	void renderAsLight(int lightNo);
/*-------------------------------*\
| pointer args are 4 element arrays
\*-------------------------------*/
	void activate(Texture * overrideTexture = 0);//use before rendering mesh
	void deactivate();				//call once after rendering mesh, regardless of # of passes. 



	float color[4];
	float specular[4];
	float specularExponent;
	
	Texture * textures[3];				//up to 3 way multitexture

	unsigned shaderID;					//the shader to use.
	int smooth;							//0- false, else true.
	bool bDualPass;

	std::string name;

	protected:
	void activatePass0();
	void activatePass1();
	};

};

#endif
//AGCOPYRIGHTBEGIN
///////////////////////////////////////////////////////////////////////////
// Copyright � 2005 AGEIA Technologies.
// All rights reserved. www.ageia.com
///////////////////////////////////////////////////////////////////////////
//AGCOPYRIGHTEND
