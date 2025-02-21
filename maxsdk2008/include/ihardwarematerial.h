/**********************************************************************
 *<
	FILE: IHardwareMaterial.h

	DESCRIPTION: Hardware Material Extension Interface class

	CREATED BY: Norbert Jeske

	HISTORY:

 *>	Copyright (c) 2002, All Rights Reserved.
 **********************************************************************/

#ifndef _IHARDWARE_MATERIAL_H_
#define _IHARDWARE_MATERIAL_H_

#define IHARDWARE_MATERIAL_INTERFACE_ID Interface_ID(0x40c926b7, 0x7b3a66b7)

#if !defined( __D3DX9_H__ )
#  include <d3dx9.h>
#endif

/*! \sa  Class IDXDataBridge\n\n
\par Description:
<b>This class is only available in release 5 or later.</b>\n\n
A pointer to this class is provided by <b>IDXDataBridge::SetDXData()</b>. The
GFX layer will implement all these methods. Most of the methods are direct
replicas of the DirectX API for SetRenderState and SetTextureStageState.\n\n
The reason for this is that only one thread can access the graphics hardware at
any one time. Using this interface means that the GFX driver can have its
database initialized with the DirectX states required for this object, when it
comes to access the graphics device.\n\n
To use this class good knowledge of DirectX is needed, a copy of the DirectX
documentation is also recommended.\n\n
For an example usage of this class see
<b>MAXSDK/SAMPLES/HardwareShaders/LightMap/Lightmap.cpp</b>\n\n
   */
class IHardwareMaterial : public BaseInterface
{
public:
	/*! \remarks The returns the unique ID for this interface. By default it
	will return <b>IHARDWARE_MATERIAL_INTERFACE_ID</b> */
	virtual Interface_ID	GetID() { return IHARDWARE_MATERIAL_INTERFACE_ID; }

	// Interface Lifetime
	virtual LifetimeType	LifetimeControl() { return noRelease; }

	// Information provided from a Custom Attribute?
	virtual void	SetCustomFlag(bool bVal) = 0;

	// Render States
	/*! \remarks This is equivalent to the DirectX method
	SetRenderState(FILLMODE,mode)\n\n

	\par Parameters:
	<b>DWORD mode</b>\n\n
	A member of D3DFILLMODE\n\n
	  */
	virtual void	SetFillMode(DWORD mode) = 0;
	/*! \remarks This is equivalent to DirectX method
	SetRenderState(SHADEMODE,mode)\n\n

	\par Parameters:
	<b>DWORD mode</b>\n\n
	A member of D3DSHADEMODE\n\n
	  */
	virtual void	SetShadeMode(DWORD mode) = 0;

	// Material Colors
	/*! \remarks Please see the DirectX documentation for more information on
	this method\n\n
	  */
	virtual void	SetMaterial(LPD3DXMATERIAL pMtl) = 0;

	/*! \remarks Specifies Diffuse color to be set by using the DirectX data
	structure <b>LPD3DXCOLOR</b>.\n\n
	  */
	virtual void	SetDiffuseColor(LPD3DXCOLOR pClr) = 0;
	/*! \remarks Allows the Diffuse color to be set\n\n

	\par Parameters:
	<b>Color c</b>\n\n
	The diffuse color\n\n
	<b>float alpha</b>\n\n
	The colors alpha\n\n
	  */
	virtual void	SetDiffuseColor(Color c, float alpha = 1.0f) = 0;
	/*! \remarks Allows the Diffuse color to be set\n\n

	\par Parameters:
	<b>Point3 c</b>\n\n
	The diffuse color\n\n
	<b>float alpha</b>\n\n
	The colors alpha */
	virtual void	SetDiffuseColor(Point3 c, float alpha = 1.0f) = 0;

	/*! \remarks Specifies the Ambient color to set by using a DirectX data
	structure.\n\n
	  */
	virtual void	SetAmbientColor(LPD3DXCOLOR pClr) = 0;
	/*! \remarks Allows the Ambient color to be set
	\par Parameters:
	<b>Color c</b>\n\n
	The ambient color\n\n
	<b>float alpha</b>\n\n
	The colors alpha\n\n
	  */
	virtual void	SetAmbientColor(Color c, float alpha = 1.0f) = 0;
	/*! \remarks Allows the Ambient color to set
	\par Parameters:
	<b>Point3 c</b>\n\n
	The ambient color\n\n
	<b>float alpha</b>\n\n
	The colors alpha\n\n
	  */
	virtual void	SetAmbientColor(Point3 c, float alpha = 1.0f) = 0;

	/*! \remarks Specifies the Specular color to set by using a DirectX data
	structure.\n\n
	  */
	virtual void	SetSpecularColor(LPD3DXCOLOR pClr) = 0;
	/*! \remarks Allows the Specular color to be set
	\par Parameters:
	<b>Color c</b>\n\n
	The specular color\n\n
	<b>float alpha</b>\n\n
	The colors alpha\n\n
	  */
	virtual void	SetSpecularColor(Color c, float alpha = 1.0f) = 0;
	/*! \remarks Allows the Specular color to set
	\par Parameters:
	<b>Point3 c</b>\n\n
	The specular color\n\n
	<b>float alpha</b>\n\n
	The colors alpha\n\n
	  */
	virtual void	SetSpecularColor(Point3 c, float alpha = 1.0f) = 0;

	/*! \remarks Allows the Emissive color to set by using a DirectX data
	structure.\n\n
	  */
	virtual void	SetEmissiveColor(LPD3DXCOLOR pClr) = 0;
	/*! \remarks Allows the Emissive color to be set\n\n

	\par Parameters:
	<b>Color c</b>\n\n
	The emissive color\n\n
	<b>float alpha</b>\n\n
	The colors alpha\n\n
	  */
	virtual void	SetEmissiveColor(Color c, float alpha = 1.0f) = 0;
	/*! \remarks Allows the Emissive color to be set\n\n

	\par Parameters:
	<b>Point3 c</b>\n\n
	The emissive color\n\n
	<b>float alpha</b>\n\n
	The colors alpha\n\n
	  */
	virtual void	SetEmissiveColor(Point3 c, float alpha = 1.0f) = 0;

	/*! \remarks Allows the specular exponent of the material to be set
	\par Parameters:
	<b>float power</b>\n\n
	The specular amount\n\n
	  */
	virtual void	SetSpecularPower(float power) = 0;

	// Texture States
	/*! \remarks This sets the internal size for the table that will hold the
	Texture information for the material. If you are not using any Texture stages
	then this should be set to zero, otherwise it should match exactly the number
	of textures being used.
	\par Parameters:
	<b>DWORD numStages</b>\n\n
	The number of Texture stages */
	virtual bool	SetNumTexStages(DWORD numStages) = 0;
	/*! \remarks This allows a texture to be loaded to the graphics device. In
	this case the texture is loaded/created by the GFX via calls to
	IHardwareRenderer::BuildTexture() which will return a DWORD_PTR, which is
	an internal representation of the texture. The texture was allocated it
	will return true.\n\n

	\par Parameters:
	<b>DWORD stage</b>\n\n
	The stage to hold the texture\n\n
	<b>DWORD_PTR pTexture</b>\n\n
	A texture pointer returned by IHardwareRenderer::BuildTexture()\n\n
	  */
	virtual bool	SetTexture(DWORD stage, DWORD_PTR pTexture) = 0;
	/*! \remarks This allows a texture to be loaded to the graphics device.
	The file is assumed to exist. If successful it will return true.
	\par Parameters:
	<b>DWORD stage</b>\n\n
	The stage to hold the texture\n\n
	<b>LPCSTR filename</b>\n\n
	A string containing the filename of the texture to load \n\n
	  */
	virtual bool	SetTexture(DWORD stage, LPCSTR filename) = 0;
	/*! \remarks This specifies where the Texture Coordinates will be
	retrieved. Most of the time the mesh will supply them so the type would be
	UVSOURCE_HWGEN. However a Viewport Shader could create them dynamically so
	would supply. If successful it will return true.
	\par Parameters:
	<b>DWORD stage</b>\n\n
	The stage to set\n\n
	<b>DWORD type</b>\n\n
	The UVW Source. It can be any of the following :- \n\n
	<b>UVSOURCE_MESH</b>\n\n
	<b>UVSOURCE_XYZ</b>\n\n
	<b>UVSOURCE_MESH2</b>\n\n
	<b>UVSOURCE_WORLDXYZ</b>\n\n
	<b>UVSOURCE_FACEMAP</b>\n\n
	<b>UVSOURCE_HWGEN</b>\n\n
	  */
	virtual bool	SetTextureUVWSource(DWORD stage, DWORD type) = 0;
	/*! \remarks This specifies what mapping channel from the mesh the Texture
	Coordinates will be retrieved. This is used in the stripping code so that
	the VertexBuffer is populated with the correct TVs. If successful it will
	return true.
	\par Parameters:
	<b>DWORD stage</b>\n\n
	The stage to set\n\n
	<b>DWORD type</b>\n\n
	The mapping channel to use  */
	virtual bool	SetTextureMapChannel(DWORD stage, DWORD numChan) = 0;
	/*! \remarks This specifies what texture coordinate the stage will use.
	This value is used in the DirectX call <b>SetTextureStageState(stage,
	D3DTSS_TEXCOORDINDEX, index)</b>. If successful it will return true.
	\par Parameters:
	<b>DWORD stage</b>\n\n
	The stage to set\n\n
	<b>DWORD index</b>\n\n
	The texture coordinate index to use */
	virtual bool	SetTextureCoordIndex(DWORD stage, DWORD index) = 0;

	// Texture Transforms
	/*! \remarks This specifies what texture flag the stage will use. This
	value is used in the DirectX call <b>SetTextureStageState(stage,
	D3DTSS_TEXTURETRANSFORMFLAGS, flag)</b>. If successful it will return true.
	\par Parameters:
	<b>DWORD stage</b>\n\n
	The stage to set\n\n
	<b>DWORD flag</b>\n\n
	The DirectX flag to set */
	virtual bool	SetTextureTransformFlag(DWORD stage, DWORD flag) = 0;
	/*! \remarks This specifies what texture flag the stage will use. This
	value is used in the DirectX call
	<b>SetTransform((D3DTRANSFORMSTATETYPE)(D3DTS_TEXTURE0+stage),
	pTransform)</b>. If successful it will return true.
	\par Parameters:
	<b>DWORD stage</b>\n\n
	The stage to set\n\n
	<b>LPD3DXMATRIX pTransform</b>\n\n
	The DirectX matrix to set  */
	virtual bool	SetTextureTransform(DWORD stage, LPD3DXMATRIX pTransform) = 0;

	// Texture Stage States
	/*! \remarks <b>This method is a direct replica if the DirectX color
	operators used with</b> D3DTSS_COLOROP. Please refer to the DirectX
	documentation for further information
	\par Parameters:
	<b>DWORD stage</b>\n\n
	The stage to set\n\n
	<b>DWORD colorOp</b>\n\n
	A member of the DirectX enumerated type <b>D3DTEXTUREOP</b>\n\n
	  */
	virtual bool	SetTextureColorOp(DWORD stage, DWORD colorOp) = 0;
	/*! \remarks This method is a direct replica if the DirectX Texture Argument
	flag used with D3DTSS_COLOROPARG. The argNum defines which argument to set.
	<b>Please refer to the DirectX documentation for further information</b>
	\par Parameters:
	<b>DWORD stage</b>\n\n
	The stage to set\n\n
	<b>DWORD argNum</b>\n\n
	The argument index to set. If this is set to 1 then <b>D3DTSS_COLORPARG1</b>
	will be addressed\n\n
	<b>DWORD colorArg</b>\n\n
	The Argument to set. \n\n
	  */
	virtual bool	SetTextureColorArg(DWORD stage, DWORD argNum, DWORD colorArg) = 0;
	/*! \remarks This method is a direct replica if the DirectX alpha blending
	operators used with D3DTSS_ALPHAOP. <b>Please refer to the DirectX
	documentation for further information</b>
	\par Parameters:
	<b>DWORD stage</b>\n\n
	The stage to set\n\n
	<b>DWORD alphaArg</b>\n\n
	A member of the DirectX enumerated type <b>D3DTEXTUREOP</b> */
	virtual bool	SetTextureAlphaOp(DWORD stage, DWORD alphaArg) = 0;
	/*! \remarks This method is a direct replica if the DirectX Texture Alpha
	Argument flag used with D3DTSS_APLHAPARG. The argNum defines which argument
	to set. <b>Please refer to the DirectX documentation for further
	information</b>
	\par Parameters:
	<b>DWORD stage</b>\n\n
	The stage to set\n\n
	<b>DWORD argNum</b>\n\n
	The alpha argument index to set. If this is set to 1 then
	<b>D3DTSS_ALPHAARG1</b> will be addressed\n\n
	<b>DWORD colorArg</b>\n\n
	The Alpha Argument to set. */
	virtual bool	SetTextureAlphaArg(DWORD stage, DWORD argNum, DWORD alphaArg) = 0;
	virtual bool	SetTextureAddressMode(DWORD stage, DWORD coordNum, DWORD mode) = 0;

	// Shaders
	/*! \remarks This method allows a DirectX vertex shader to be loaded. It
	is used in conjunction with IHardwareRenderer::LoadVertexShader which will
	return a DWORD_PTR of internal storage for the shader. There are methods in
	Class IHardwareRenderer that provide
	a means to supply the constants used in the shader.\n\n

	\par Parameters:
	<b>DWORD_PTR pVertexShader</b>\n\n
	The vertex shader to load.\n\n
	  */
	virtual bool	SetVertexShader(DWORD_PTR pVertexShader) = 0;
	/*! \remarks This method allows a DirectX pixel shader to be loaded. It is
	used in conjunction with IHardwareRenderer::LoadPixelShader which will
	return a DWORD_PTR of internal storage for the shader. There are methods
	Class IHardwareRenderer that provide
	a means to supply the constants used in the shader.\n\n

	\par Parameters:
	<b>DWORD_PTR pPixelShader</b>\n\n
	The vertex shader to load */
	virtual bool	SetPixelShader(DWORD_PTR pPixelShader) = 0;

	// Effects
	/*! \remarks This method allows a DirectX effect. It is used in
	conjunction with IHardwareRenderer::LoadEffectFile which will return a
	DWORD_PTR of internal storage for the file. There are methods in
	Class IHardwareRenderer that provide
	a means to connect the application to the effects file.\n\n

	\par Parameters:
	<b>DWORD_PTR pEffect</b>\n\n
	The effect file to load */
	virtual bool	SetEffect(DWORD_PTR pEffect) = 0;

	// User Plugin
	virtual bool	SetPlugin(BaseInterface *pPlugin) = 0;

	// Current Associated INode
	virtual bool	SetINode(INode *pINode) = 0;
};

#endif
