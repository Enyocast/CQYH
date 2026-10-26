/** 
  * @note This file is part of Air UE3 integration
  * @date 2012-03-05
  * @copyright Allegorithmic. All rights reserved. 
  */

#ifndef ATC_API_TEXTUREFORMATS_H
#define ATC_API_TEXTUREFORMATS_H

namespace atc_api
{

//! @brief This has been extracted from UE3 to be directly compatible with it
enum TextureFormat
{
	TextureFormat_Unknown              =0,
	TextureFormat_A32B32G32R32F        =1,
	TextureFormat_A8R8G8B8             =2,
	TextureFormat_G8                   =3,
	TextureFormat_G16                  =4,
	TextureFormat_DXT1                 =5,
	TextureFormat_DXT3                 =6,
	TextureFormat_DXT5                 =7,
	TextureFormat_UYVY                 =8,
	TextureFormat_FloatRGB             =9,
	TextureFormat_FloatRGBA            =10,
	TextureFormat_DepthStencil         =11,
	TextureFormat_ShadowDepth          =12,
	TextureFormat_FilteredShadowDepth  =13,
	TextureFormat_R32F                 =14,
	TextureFormat_G16R16               =15,
	TextureFormat_G16R16F              =16,
	TextureFormat_G16R16F_FILTER       =17,
	TextureFormat_G32R32F              =18,
	TextureFormat_A2B10G10R10          =19,
	TextureFormat_A16B16G16R16         =20,
	TextureFormat_D24                  =21,
	TextureFormat_R16F                 =22,
	TextureFormat_R16F_FILTER          =23,
	TextureFormat_BC5                  =24,
	TextureFormat_V8U8                 =25,
	TextureFormat_A1                   =26,
	TextureFormat_MAX                  =27,
};

}

#endif // ATC_API_TEXTUREFORMATS_H
