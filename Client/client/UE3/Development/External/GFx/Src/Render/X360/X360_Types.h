/**************************************************************************

Filename    :   X360_Types.h
Content     :   Types and defines for X360.
Created     :   Nov 2010
Authors     :   Bart Muzzin

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#ifndef INC_SF_X360_TYPES_H
#define INC_SF_X360_TYPES_H
#pragma once

enum VSGroupMode
{
    VSGroup_Single      = 0x0000,
    VSGroup_Batch       = 0x0100,
    VSGroup_Instanced   = 0x0200,
    VSGroup_Mask        = 0x0300
};
enum VSColorInput
{
    VSColor_None        = 0x0000,
    VSColor_Solid       = 0x0400,
    VSColor_Vertex      = 0x0800,
    VSColor_Mask        = 0x0C00,
};
enum VSTextureInput
{
    VSTexture_None      = 0x0000,
    VSTexture_Gen1      = 0x1000,
    VSTexture_Gen2      = 0x2000,
    VSTexture_UV1       = 0x3000,
    VSTexture_Mask      = 0xF000,
};

// Generate VertexElement
enum VertexElementBits
{    
    // Elements of VertexFormat
    VFE_IIndex          = 0x0001, // Instance index
    VFE_EAlpha          = 0x0002,
    VFE_Weight          = 0x0004,
    VFE_VColor          = 0x0008, 
    VFE_UV32f           = 0x0010,

    VFE_Factors_Mask    = VFE_EAlpha | VFE_Weight | VFE_IIndex,
    VFE_Mask            = 0x00FF,

    VSBit_Factor        = 0x10000
};



// Pixel shader texture key bit flags. These bits are used to both generate and uniquely
// identify a pixel shader; note that they don't map one-to-one to PSTypes, as some
// combinations are not needed.
enum PSKeyBits
{
    // Low 8 bits, always created.
    // In addition to being used as a part of PShader key, there 3 bits
    // also index ShaderManager::PSTable.
    PSBit_Multiply    = 0x0001,
    PSBit_AlphaWrite  = 0x0002,
    PSBit_Cxform      = 0x0004,
    PSBit_Instanced   = 0x0008,
    PSBit_LowBitCount = 4,  
    // Shader has EAlpha stage after cxform (requires factor).
    PSBit_EAlpha      = 0x0010,
    // PSFillOP index occupies the higher bits, identifies operation used
    // to assign color from texture(s).
    PSBit_FillOp_Mask = 0x01E0,
    PSBit_FillOp_Shift= 5,
};


// PSType describes the significantly-different types of pixel shaders used in
// renderer and indexable through ShaderManager::PStable.
// For each type there are 8 versions matching low PSBit values
// (Multiply, AlphaWrite, Instanced).
enum PSType
{
    PS_None,
    PS_NoColor, // Color = 1.0, used for masks.
    PS_Color,
    PS_Color_EAlpha,
    PS_Texture,
    PS_Texture_EAlpha,
    PS_Texture_VColor,
    PS_Texture_VColor_EAlpha,
    PS_2Texture,
    PS_2Texture_EAlpha,
    PS_TextureA_VColor,
    PS_TextureYUV,
    PS_TextureYUVA,
    PS_Type_Count
};

// Texture sample/weight operation done by pixel shader
// Indexed based on PrimitiveFillType + Texture type(s).

enum PSFillOp
{
    PSFillOp_None,
    PSFillOp_NoColor,
    PSFillOp_Texture,
    PSFillOp_Texture_VColor,
    PSFillOp_2Texture,
    PSFillOp_TextureA_VColor,
    PSFillOp_TextureYUV,
    PSFillOp_TextureYUVA,
    PSFillOp_Count
};

// PositionType is used to differentiate vertex formats/decls.
enum PositionType
{
    PositionType_SInt16,
    PositionType_Float32,
    PositionType_Count
};

// ShaderType is used to differentiate shaders with special features.
enum ShaderType
{
    ShaderType_Normal,
    ShaderType_NoCxform,
    ShaderType_Count
};

#define D3DUSAGE_AUTOGENMIPMAP    (0x00000000L)    // Not included in X360 (can always auto-gen).
#define D3DUSAGE_DYNAMIC        (0x00000000L)    // Not included in X360 (can always have dynamic).

// DirectX compatibility defines
#define IDirect3DDeviceX        IDirect3DDevice9
#define IDirect3DTextureX       IDirect3DTexture9
#define IDirect3DSurfaceX       IDirect3DSurface9
#define IDirect3DIndexBufferX   IDirect3DIndexBuffer9
#define IDirect3DVertexBufferX  IDirect3DVertexBuffer9
#define D3DCAPSx                D3DCAPS9
#define D3DVIEWPORTx            D3DVIEWPORT9
#define LPDIRECT3Dx             LPDIRECT3D9
#define LPDIRECT3DDEVICEx       LPDIRECT3DDEVICE9

#endif // INC_SF_X360_TYPES_H
