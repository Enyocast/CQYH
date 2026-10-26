/**************************************************************************

PublicHeader:   GFx
Filename    :   GFx_ImageCreator.cpp
Content     :   
Created     :   June 21, 2005
Authors     :   Michael Antonov

Notes       :   Redesigned to use inherited state objects for GFx 2.0.

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "Kernel/SF_Types.h"
#include "Kernel/SF_RefCount.h"
#include "Kernel/SF_File.h"

#include "Render/Render_Image.h"
#include "Render/Render_ImageFiles.h"
#include "GFx_ImageCreator.h"

namespace Scaleform { namespace GFx {

using Render::ImageFileReader;
using Render::ImageCreateArgs;
    
ImageCreator::ImageCreator(TextureManager* textureManager) 
: State(State_ImageCreator), pTextureManager(textureManager) 
{ 
}

// Looks up image for "img://" protocol.
Image* ImageCreator::LoadProtocolImage(const ImageCreateInfo& info, const String& url)
{
    SF_UNUSED2(info, url);
    return 0;
}

// Loads image from file.
Image* ImageCreator::LoadImageFile(const ImageCreateInfo& info, const String& url)
{
    ImageFileHandlerRegistry* registry = info.GetImageFileHandlerRegistry();
    if (!registry || !info.GetFileOpener())
        return 0;

    Ptr<File> file = *info.GetFileOpener()->OpenFile(url);

    ImageFileReader* reader;
    ImageCreateArgs args;
    if (registry->DetectFormat(&reader, file) != Render::ImageFile_Unknown)
    {
        // Get image source.
        args.pHeap      = info.pHeap;
        args.Use        = info.Use;
        args.pManager   = pTextureManager;
        if (info.RUse == Resource::Use_FontTexture)
            args.Format = Render::Image_A8;

        Ptr<ImageSource> source = *reader->ReadImageSource(file, args);
        if (source)
        {
            return CreateImage(info, source);
        }
    }

    return registry->ReadImage(file, args);
}

// Loads exported image file.
Image* ImageCreator::LoadExportedImage(const ImageCreateExportInfo& info, const String& url)
{
    Image* result = LoadImageFile(info, url);

    // Fall-back trying ".dds", ".tga"
    if (!result && url.HasExtension())
    {
        if (url.GetExtension().ToLower() != ".dds")
        {
            String url2 = url;
            url2.StripExtension();
            url2 += ".dds";
            result = LoadImageFile(info, url2);
        }
    }

    return result;
}

// Creates image
//  - Returns image that matches expected protocol.
Image* ImageCreator::CreateImage(const ImageCreateInfo& info, ImageSource* source)
{
    ImageCreateArgs args;
    args.pHeap = info.pHeap;
    args.Use = info.Use;
    args.pManager = pTextureManager;
    if (info.RUse == Resource::Use_FontTexture)
        args.Format = Render::Image_A8;

    return source->CreateCompatibleImage(args);

}

void ImageFileHandlerRegistry::AddHandler(ImageFileHandler* handler)
{
    Render::ImageFileHandlerRegistry::AddHandler(handler);
}

}} // Scaleform::GFx
