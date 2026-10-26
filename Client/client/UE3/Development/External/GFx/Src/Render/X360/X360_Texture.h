/**************************************************************************

Filename    :   X360_Texture.h
Content     :   D3D9 Texture and TextureManager header
Created     :   January 2010
Authors     :   Michael Antonov

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#ifndef INC_SF_Render_X360_Texture_H
#define INC_SF_Render_X360_Texture_H

#include "Kernel/SF_List.h"
#include "Kernel/SF_Threads.h"
#include "Render/Render_Image.h"
#include "Render/Render_ThreadCommandQueue.h"
#include "Kernel/SF_HeapNew.h"
#include "X360_MemoryManager.h"
#include "X360_Types.h"

namespace Scaleform { namespace Render { namespace X360 {


// TextureFormat describes format of the texture and its caps.
// Format includes allowed usage capabilities and ImageFormat
// from which texture is supposed to be initialized.

struct TextureFormat
{
    struct Mapping
    {
        ImageFormat              Format;
        D3DFORMAT                D3DFormat;
        UByte                    BytesPerPixel;
        bool                     Mappable;
        Image::CopyScanlineFunc  CopyFunc;
        Image::CopyScanlineFunc  UncopyFunc;
    };

    const Mapping*  pMapping;
    DWORD           D3DUsage;

    ImageFormat     GetImageFormat() const { return pMapping->Format; }
    D3DFORMAT       GetD3DFormat() const   { return pMapping->D3DFormat; }

    unsigned        GetPlaneCount() const
    { return ImageData::GetFormatPlaneCount(GetImageFormat()); }
    
    bool            CanAutoGenMipmaps() const
    { return true; }
    bool            CanBeDynamic() const
    { return true; }
};

class MappedTexture;
class TextureManager;


// X360 Texture class implementation; it man actually include several HW 
// textures (one for each ImageFormat plane).

class Texture : public Render::Texture
{
public:
    // Bits stored in TextureFlags.
    enum TextureFlagBits
    {
        TF_Rescale    = 0x01,
        TF_SWMipGen   = 0x02,
        TF_UserAlloc  = 0x04,
        TF_NoRefCount = 0x08,
    };

    const TextureFormat*    pFormat;

    // If texture is currently mapped, it is here.
    MappedTexture*          pMap;
    
    struct HWTextureDesc
    {        
        ImageSize           Size;
        UByte*              pTexData;
        D3DTexture *        Tex;
        D3DSurface *        Surface;
    };

    // TextureDesc array is allocated if more then one is needed.
    HWTextureDesc*          pTextures;
    HWTextureDesc           Texture0;

    Render::MemoryManager*  pMemManager;

    Texture(TextureManagerLocks* pmanagerLocks, const TextureFormat* pformat, unsigned mipLevels,
        const ImageSize& size, unsigned use, ImageBase* pimage, Render::MemoryManager* pmemManager = 0);
    Texture(TextureManagerLocks* pmanagerLocks, IDirect3DTexture9* ptexture, const ImageSize& size, ImageBase* pimage,
        Render::MemoryManager* pmemManager, bool useRefCount = true);
    ~Texture();

    ImageFormat             GetImageFormat() const { return pFormat->pMapping->Format; }
    TextureManager*         GetManager() const     { return (TextureManager*)pManagerLocks->pManager; }
    bool                    IsValid() const        { return pTextures != 0; }

    void                    LoseManager();    
    bool                    Initialize();
    bool                    Initialize(IDirect3DTexture9* ptexture);
    void                    ReleaseHWTextures();

    // Applies a texture to device starting at pstageIndex, advances index
    // TBD: Texture matrix may need to be adjusted if image scaling is done.
    void                    ApplyTexture(DWORD stageIndex, ImageFillMode fm);

    // *** Interface implementation
    virtual Image*          GetImage() const
    { SF_ASSERT(!pImage || (pImage->GetImageType() != Image::Type_ImageBase)); return (Image*)pImage; }
    virtual ImageFormat     GetFormat() const         { return GetImageFormat(); }
    
    virtual bool            Map(ImageData* pdata, unsigned mipLevel, unsigned levelCount);
    virtual bool            Unmap();

    virtual bool            Update(const UpdateDesc* updates, unsigned count = 1, unsigned mipLevel = 0);    
    virtual bool            Update();

    // Copies the image data from the hardware.
    SF_AMP_CODE( virtual bool Copy(ImageData* pdata); )
};

// D3D9 DepthStencilSurface implementation. 
class DepthStencilSurface : public Render::DepthStencilSurface
{
public:
    DepthStencilSurface(TextureManagerLocks* pmanagerLocks, const ImageSize& size);
    ~DepthStencilSurface();

    virtual ImageSize               GetSize() const { return Size; }
    bool                            Initialize();

    ImageSize                 Size;
    IDirect3DSurface9 *       pDepthStencilSurface;
    Texture::CreateState      State;

};

// MappedTexture object repents a Texture mapped into memory with Texture::Map() call;
// it is also used internally during updates.
// The key part of this class is the Data object, stored Locked texture level plains.

class MappedTexture : public NewOverrideBase<StatRender_TextureManager_Mem>
{
    friend class Texture;

    Texture*      pTexture;
    // We support mapping sub-range of levels, in which case
    // StartMipLevel may be non-zero.
    unsigned      StartMipLevel;
    int           LevelCount;
    // Pointer data that can be copied to.
    ImageData     Data;

    enum { PlaneReserveSize = 4 };
    ImagePlane    Planes[PlaneReserveSize];

public:
    MappedTexture()
        : pTexture(0), StartMipLevel(false), LevelCount(0) { }
    ~MappedTexture()
    {
        SF_ASSERT(!IsMapped());
    }

    bool        Reserve()  { AtomicOps<int>::CompareAndSet_Sync(&LevelCount, 0, -1); return LevelCount == -1; }
    bool        IsMapped() { return (LevelCount > 0); }
    bool        Map(Texture* ptexture, unsigned mipLevel, unsigned levelCount);
    void        Unmap();
};


// X360 Texture Manger.
// This class is responsible for creating textures and keeping track of them
// in the list.
// 

class TextureManager : public Render::TextureManager
{
    friend class Texture;
    friend class DepthStencilSurface;

    typedef ArrayConstPolicy<8, 8, false>   KillListArrayPolicy;
    typedef ArrayLH<IDirect3DTexture9*,
                    StatRender_TextureManager_Mem,
                    KillListArrayPolicy>    D3DTextureArray;
    typedef ArrayLH<IDirect3DSurface9*,
                    StatRender_TextureManager_Mem,
                    KillListArrayPolicy>    D3DSurfaceArray;
    typedef List<Texture, Render::Texture>  TextureList;
    typedef List<DepthStencilSurface, Render::DepthStencilSurface> DepthStencilList;

    IDirect3DDevice9*   pDevice;
    Render::MemoryManager*      pMemoryManager;
    ThreadId            RenderThreadId;
    MappedTexture       MappedTexture0;
    ThreadCommandQueue* pRTCommandQueue;    

    // Lists protected by TextureManagerLocks::TextureMutex.
    TextureList               Textures;
    TextureList               TextureInitQueue;
    DepthStencilList          DepthStencilInitQueue;
    D3DTextureArray           D3DTextureKillList;
    D3DTextureArray           D3DTextureReleaseList;
    
    // Texture format table, organized by supported HW features.
    ArrayLH<TextureFormat>   TextureFormats;

    // Detecting redundant sampler/address setting.
    static const int MaximumStages = 4;
    D3DTEXTUREADDRESS    AddressMode[MaximumStages];
    D3DTEXTUREFILTERTYPE FilterType[MaximumStages];

    // Detects supported D3DFormats and capabilities.
    void            initTextureFormats();
    const Render::TextureFormat* getTextureFormat(ImageFormat format) const;    
    virtual bool    isMappable(const Render::TextureFormat* ptformat) { return ((TextureFormat*)ptformat)->pMapping->Mappable; }

    // Texture Memory-mapping support.
    MappedTexture*  mapTexture(Texture* p, unsigned mipLevel, unsigned levelCount);
    MappedTexture*  mapTexture(Texture* p) { return mapTexture(p, 0, p->MipLevels); }
    void            unmapTexture(Texture *ptexture);    
    
    virtual void    processTextureKillList();
    virtual void    processInitTextures();    

public:
    TextureManager(IDirect3DDevice9* pdevice, Render::MemoryManager* pmemmanager,
                   ThreadId renderThreadId, ThreadCommandQueue* commandQueue );
    ~TextureManager();

    Render::MemoryManager* GetMemoryManager() { return pMemoryManager; }

	// Used once texture manager is no longer necessary.
	void    Reset();

    bool IsMultiThreaded() const    { return RenderThreadId != 0; }

    void            SetSamplerState(unsigned stage,
                                    D3DTEXTUREFILTERTYPE filter, D3DTEXTUREADDRESS address);

    virtual void    BeginScene();
    virtual void    EndScene();

    // *** TextureManager
    virtual Render::Texture* CreateTexture(ImageFormat format, unsigned mipLevels,
                                           const ImageSize& size,
                                           unsigned use, ImageBase* pimage,
                                           Render::MemoryManager* manager = 0);
    virtual Render::Texture* CreateTexture(IDirect3DTexture9* ptexture,
                                           ImageSize imgSize = ImageSize(0), ImageBase* pimage = 0,
                                           Render::MemoryManager* manager = 0,
                                           bool useRefCount = true);

    virtual unsigned        GetTextureUseCaps(ImageFormat format);
 
    virtual Render::DepthStencilSurface* CreateDepthStencilSurface(const ImageSize& size,
                                                                   Render::MemoryManager* manager = 0);
    virtual Render::DepthStencilSurface* CreateDepthStencilSurface(IDirect3DSurface9* psurface);
};


}}};  // namespace Scaleform::Render::X360

#endif
