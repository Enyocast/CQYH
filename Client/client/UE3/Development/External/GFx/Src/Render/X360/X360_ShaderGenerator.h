/**************************************************************************

Filename    :   X360_ShaderGenerator.h
Content     :   Break-out shader code generation into a separate file, to support
                precompilation on PC.
Created     :   Nov 2010
Authors     :   Bart Muzzin

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#ifndef INC_SF_X360_SHADERGENERATOR_H
#define INC_SF_X360_SHADERGENERATOR_H
#pragma once

#include "Kernel/SF_Types.h"
#include "Render/X360/X360_Types.h"
#include "Render/Render_Primitive.h"

namespace Scaleform { 

class StringBuffer;

namespace Render { namespace X360 {

static const char * SF_RENDER_X360_VSHADER_PROFILE = "vs_3_0";
static const char * SF_RENDER_X360_PSHADER_PROFILE = "ps_3_0";

// StdVertexShaderDesc describes the features and type of vertex shader to use.
struct StdVertexShaderDesc
{
    UInt32  Flags;

    VSGroupMode     GetGroupMode() const    { return (VSGroupMode)(Flags & VSGroup_Mask); }
    VSColorInput    GetColorInput() const   { return (VSColorInput)(Flags & VSColor_Mask); }
    VSTextureInput  GetTextureInput() const { return (VSTextureInput)(Flags & VSTexture_Mask); }
    bool            HasFactors() const      { return (Flags & VFE_Factors_Mask) != 0; }

    unsigned        GetVertexShaderKey(ShaderType type) const
    {
        unsigned key  = Flags & (VSGroup_Mask | VSColor_Mask | VSTexture_Mask);
        if (HasFactors())
            key |= VSBit_Factor;
        key |= (unsigned)type;
        return key;
    }
};

// TexturePShader is used to associate an ImageFormat with a PixelShader type
// that supports it for a given fill style. Some pixel shaders may support multiple
// formats; however, some formats, such as YUV require a custom-tailored shader.
struct TexturePShader
{
    // Pixel shader texture type capability flags. Every bit identifies texture format 
    // type that a shader can accept. ImageFormat is mapped to one of these types.
    // If the texture cap bit is set, this shader can be used with texture.
    enum TextureType
    {
        Texture_None  = 0x0010,
        Texture_A     = 0x0020,
        Texture_RGBA  = 0x0040,
        Texture_YUV   = 0x0100,
        Texture_YUVA  = 0x0200,
    };
    enum {
        PSType_Mask = 0x0F, 
    };

    unsigned           Flags;
    TexturePShader*    pNext;

    static  TextureType ImageFormatToTextureType(ImageFormat format);

    PSType      GetShader() const                         { return (PSType)(Flags & PSType_Mask); }
    bool        SupportsTextureType(TextureType tt) const { return (Flags & tt) != 0; }

    TexturePShader* MatchImageFormat(ImageFormat format);
};


class ShaderGenerator
{
public:
    static const int INSTANCE_REGISTER = 241;
    static const int MAX_PIXEL_DESCS = PS_Type_Count-1;
    static const int MAX_VERTEX_DESCS = (PrimFill_Type_Count-1) * 3;

    static bool createVertexShaderString(StringBuffer& sb, const StdVertexShaderDesc& desc, ShaderType type);
    static bool createPixelShaderString(StringBuffer& sb, unsigned psBits);

    static const StdVertexShaderDesc & getVertexShaderDescriptor(unsigned index);
    static UInt32 getPixelShaderBits(unsigned index);
    static TexturePShader * getFillToPixelShader(PrimitiveFillType fillType);
};

}}}

#endif // INC_SF_X360_SHADERGENERATOR_H
