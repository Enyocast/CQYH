/**************************************************************************

Filename    :   X360_ShaderManager.h
Content     :   Shader Manager - tracks vertex/pixel shaders and
                declarations.
Created     :   May 2009
Authors     :   Michael Antonov

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#ifndef INC_SF_Render_D3D9_ShaderManager_H
#define INC_SF_Render_D3D9_ShaderManager_H

#include "Render/Render_HAL.h"
#include "Render/Render_Primitive.h"
#include "Render/Render_Containers.h"
#include "Render/X360/X360_Texture.h"
#include "Render/X360/X360_MeshCache.h"

namespace Scaleform { namespace Render { 
    
// Declare D3DVERTEXELEMENT9 to use it in MultiKeyCollection
inline bool operator == (const D3DVERTEXELEMENT9& e0, const D3DVERTEXELEMENT9& e1)
{   
    return memcmp(&e0, &e1, sizeof(D3DVERTEXELEMENT9)) == 0;
}


namespace X360 {

struct StdVertexShaderDesc;

// *** Vertex Shader / Vertex Declaration constansts


// ShaderManager - maintains shaders and declarations needed for rendering with 
// different fill styles and includes methods for applying them to the device.

class ShaderManager
{
    friend class ShaderGenerator;
    friend class HAL;

    IDirect3DDeviceX*   pDevice;
    // Set if device supports instancing (vs_3_0 HW only)
    bool                InstancingSupport;
    const ProfileViews* Profiler;

    struct VertexHandler
    {

        const VertexFormat *         pFormat[PositionType_Count];
        IDirect3DVertexDeclaration9* pDecl[PositionType_Count];
        IDirect3DVertexShader9*      pVShader[ShaderType_Count];
        bool                         VShaderInit[ShaderType_Count];

        VertexHandler()
        {
            memset(pFormat, 0, sizeof pFormat);
            memset(pDecl, 0, sizeof pDecl);
            memset(pVShader, 0, sizeof pVShader);
            memset(VShaderInit, 0, sizeof VShaderInit);
        }
    };

    enum {
        PSTable_PSTypeShift     = 4,
        PSTable_ElementsPerType = 1 << PSTable_PSTypeShift,
        PSTable_Size            = PS_Type_Count * PSTable_ElementsPerType,
        PSTable_InstancedBit    = PSBit_Instanced
    };

    // VHandlerTable for each type { Single, Batch, Instanced }
    VertexHandler           VHandlerTable[PrimFill_Type_Count  * 3];
    // Pixels shaders
    IDirect3DPixelShader9*  PSTable[PSTable_Size];
    // Used in delayed shader binding: 'true' if shader was created
    bool                    PSInitTable[PSTable_Size];

    // Number of textures currently applied to device
    DWORD                   AppliedTextureCount;

    // PSType computed by ApplyPrimitiveFill
    PSType                  PrimitivePSType;

    // Information about previously applied texture to avoid redundant state apply.
    struct PrevTextureDesc
    {
        Texture*        pTexture;
        ImageFillMode   Fill;
        DWORD           Stage;
        void    Clear() { pTexture = 0; }
        void    Set(Texture* tex, ImageFillMode fill, DWORD stage = 0)
        { pTexture = tex; Fill = fill; Stage = stage; }
        bool    Match(Texture* tex, ImageFillMode fill) const
        { return (pTexture == tex) && (Fill == fill); }
        bool    Match(Texture* tex, ImageFillMode fill, DWORD stage) const
        { return (pTexture == tex) && (Fill == fill) && (Stage == stage); }
    };

    IDirect3DVertexDeclaration9*    pPrevVDecl;
    IDirect3DVertexShader9 *        pPrevVShader;
    unsigned                        PrevPSIndex;
    PrevTextureDesc                 PrevTextures[2];

    MultiKeyCollection<D3DVERTEXELEMENT9,
                       Ptr<IDirect3DVertexDeclaration9>, 32>   VDecls;
    MultiKeyCollection<VertexElement, VertexFormat, 32>        VFormats;
    MultiKeyCollection<unsigned, Ptr<IDirect3DVertexShader9> > VShaders;
    MultiKeyCollection<unsigned, Ptr<IDirect3DPixelShader9> >  PShaders;


    bool            createVertexDeclaration(Ptr<IDirect3DVertexDeclaration9> *pdeclPtr,
                                            const D3DVERTEXELEMENT9 *pvertexElements);
    bool            createVertexShader(Ptr<IDirect3DVertexShader9> *pshaderPtr,
                                       const char* pshaderText);
    bool            createPixelShader(Ptr<IDirect3DPixelShader9> *pshaderPtr,
                                      const char* pshaderText);
    
    IDirect3DVertexShader9* registerVertexShader(const StdVertexShaderDesc& desc, ShaderType type);
    IDirect3DPixelShader9*       registerPixelShader(unsigned psBits);
    IDirect3DVertexDeclaration9* registerVertexDeclaration(const StdVertexShaderDesc& desc, PositionType posType);
    const VertexFormat* registerVertexFormat(const StdVertexShaderDesc& desc, PositionType posType);

public:

    void  applySolidColorConstant(Color c)
    {
        c = Profiler->GetColor(c);
        const float mult  = 1.0f / 255.0f;
        const float alpha = c.GetAlpha() * mult;
        float       rgba[4] = { c.GetRed() * mult,  c.GetGreen() * mult, c.GetBlue() * mult, alpha };
        pDevice->SetVertexShaderConstantF(0, rgba, 1);
    }

    ShaderManager();
    ~ShaderManager();

    bool   Initialize(IDirect3DDeviceX* pdevice, const ProfileViews* profiler, UInt32 vmcflags);
    void   Reset();

    bool    HasInstancingSupport() const { return InstancingSupport; }

    void    BeginScene();
    void    EndScene();

    // Applies the part of fill state that is shared between primitive batches.
    //  - Texture state is generally shared
    //  - If Apply returns false, rendering shouldn't take place
    bool   ApplyPrimitiveFill(PrimitiveFill* pfill);
    // Applies Primitive-Batch specific fills states.
    //  - pformat is passed since if is different from the one in pfill, due to being "Mapped"
    //    TBD: Can/should we map it as a part of pfill?
    bool   ApplyPrimitiveBatchFill(PrimitiveFillType fillType, UInt16 fillFlags,
                                   const VertexFormat* pformat, PrimitiveBatch::BatchType type);

    bool   ApplyClearMaskFill(PrimitiveBatch::BatchType type);
    bool   ApplySolidColorFill(Color c);

    // Obtains formats that renderer will use for single, batches and instanced rendering of
    // the specified source format.
    //   - Filled in pointer may be the same as sourceFormat.
    //   - 'instanced' format may be reported as 0,
    //     in which instancing is not supported for format.
    void    MapVertexFormat(PrimitiveFillType fill, const VertexFormat* sourceFormat,
                            const VertexFormat** single,
                            const VertexFormat** batch, const VertexFormat** instanced);

};


}}} // Scaleform::Render::D3D9

#endif
