/**************************************************************************

Filename    :   GDXTHelper.cpp
Content     :   Interface to external compression libraries 
Created     :   September, 2006
Authors     :   Artyom Bolgar, Dmitry Polenur

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
#define NOMINMAX


#include <nvtt/nvtt.h>
#include "PVRTexLib.h"


#include "Kernel/SF_File.h"
#include "Render/Render_Image.h"
#include "Kernel/SF_String.h"
#include "GFx/GFx_Stream.h"

#include "Render/Render_ResizeImage.h"
#include "Render/Render_TextureUtil.h"
// Standard includes
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <zlib.h>

#include "GDXTHelper.h"

using namespace Scaleform;
using namespace GFx;
using namespace Render;
/*
union nvColor32 {
    struct {
    UInt8 b, g, r, a;
    };
    UInt32 u;
};
*/
struct nvColor32 {
    UInt8 b, g, r, a;
};

int GDXTHelper::LastError = nvtt::Error_Unknown;


void ExportCompressor::CalculateResizeFilter(RescaleFilterTypes FilterType)
{
    bool norm = true;
    if (pRescaleFilterLut)
    {
        SF_ASSERT(0);
    }
    pRescaleFilterLut= new ImageFilterLut;
    switch(FilterType)
    {
    case FilterBicubic : pRescaleFilterLut->Calculate(ImageFilterBicubic (), norm); break;
    case FilterSpline16: pRescaleFilterLut->Calculate(ImageFilterSpline16(), norm); break;
    case FilterSpline36: pRescaleFilterLut->Calculate(ImageFilterSpline36(), norm); break;
    case FilterHanning : pRescaleFilterLut->Calculate(ImageFilterHanning (), norm); break;
    case FilterHamming : pRescaleFilterLut->Calculate(ImageFilterHamming (), norm); break;
    case FilterHermite : pRescaleFilterLut->Calculate(ImageFilterHermite (), norm); break;
    case FilterKaiser  : pRescaleFilterLut->Calculate(ImageFilterKaiser  (), norm); break;
    case FilterQuadric : pRescaleFilterLut->Calculate(ImageFilterQuadric (), norm); break;
    case FilterCatrom  : pRescaleFilterLut->Calculate(ImageFilterCatrom  (), norm); break;
    case FilterGaussian: pRescaleFilterLut->Calculate(ImageFilterGaussian(), norm); break;
    case FilterBessel  : pRescaleFilterLut->Calculate(ImageFilterBessel  (), norm); break;
    case FilterMitchell: pRescaleFilterLut->Calculate(ImageFilterMitchell(), norm); break;
    case FilterSinc    : pRescaleFilterLut->Calculate(ImageFilterSinc    (), norm); break;
    case FilterLanczos : pRescaleFilterLut->Calculate(ImageFilterLanczos (), norm); break;
    case FilterBlackman: pRescaleFilterLut->Calculate(ImageFilterBlackman(), norm); break;
    case FilterBox:
    case FilterBilinear:
        break;
    default:
        SF_ASSERT(0);

    }
}

void ExportCompressor::CalculateWH( UInt32 srcW, UInt32 srcH, UInt32 &destW, UInt32 &destH, ExportCompressor::RescaleTypes rescale )
{
    //calculation of the next higher or lower power or 2 can be implemented without using log, if necessary
    double wp=log(double(srcW))/log((double)2.0), hp=log(double(srcH))/log((double)2.0);
    switch (rescale)
    {
    case ExportCompressor::RescaleNearestPower2 :
        destW=1<<(int)floor(wp+0.5); destH=1<<(int)floor(hp+0.5);
        break;

    case ExportCompressor::RescaleBiggestPower2 :
        destW=1<<(int)ceil(wp); destH=1<<(int)ceil(hp);
        break;

    case ExportCompressor::RescaleSmallestPower2 :
        destW=1<<(int)floor(wp); destH=1<<(int)floor(hp);
        break;
    case ExportCompressor::RescaleNextSmallestPower2 :
        if (wp > 1)
            destW = 1<<(int)floor(wp-1);
        else
            destW = 1;
        if (hp > 1)
            destH = 1<<(int)floor(hp-1);
        else
            destH = 1;
        break;

    case ExportCompressor::RescalePreScale :
        destW=int((srcW + 3)&(~3)); destH=int((srcH + 3)&(~3));
        break;

    case ExportCompressor::RescaleNone :
        destW=srcW; destH=srcH;
        break;
    default:
        SF_ASSERT(0);
    }
}

Render::RawImage* ExportCompressor::CreateResizedImage( const Render::ImageData *psrc, ExportCompressor::RescaleTypes rescale, ExportCompressor::RescaleFilterTypes filterType, bool square /*, unsigned targetWidth, unsigned targetHeight*/ )
{

	if (rescale == ExportCompressor::RescaleNone)
		return 0;
    SF_ASSERT(psrc->GetFormat() == Image_R8G8B8A8);
    UInt32 w=0, h=0; //destination width and height  

    CalculateWH( psrc->GetWidth(), psrc->GetHeight(), w, h, rescale );
    if (square)
        w = h = Alg::Max<unsigned>(w, h);
    

	if (w == psrc->GetWidth() && h == psrc->GetHeight())
		return 0;
	
	RawImage* pdstImage = RawImage::Create(Image_R8G8B8A8, psrc->GetMipLevelCount(), ImageSize(w,h), 0);
	ImageData dstImageData; 
	pdstImage->GetImageData(&dstImageData);
	
    switch(filterType)
    {
    case ExportCompressor::FilterBox:      
        ResizeImageBox(dstImageData.GetDataPtr(), w, h, dstImageData.GetPitch(), 
                        psrc->GetDataPtr(), psrc->GetWidth(),psrc->GetHeight(),psrc->GetPitch(), ResizeRgbaToRgba); 
        break;
    case ExportCompressor::FilterBilinear: 
        ResizeImageBilinear(dstImageData.GetDataPtr(), w, h, dstImageData.GetPitch(), 
                             psrc->GetDataPtr(), psrc->GetWidth(),psrc->GetHeight(),psrc->GetPitch(), ResizeRgbaToRgba); 
        break;
    default:       
        ResizeImage(dstImageData.GetDataPtr(), w, h, dstImageData.GetPitch(), 
                     psrc->GetDataPtr(), psrc->GetWidth(),psrc->GetHeight(),psrc->GetPitch(), ResizeRgbaToRgba, 
                     *pRescaleFilterLut); 
        break;
    }
	return pdstImage;
}

UInt32 GDXTHelper::CalculateDDSSize( UInt32 srcW, UInt32 srcH, ImageFormat format,                              int dxtN,
                                  bool isUncompressedDDS,
                                  bool doGenMipMap,
                                  bool isDxt1Allowed )
{
    nvtt::InputOptions       inputOptions;
    nvtt::CompressionOptions compressionOptions;
    nvtt::Compressor         compressor;
    inputOptions.setTextureLayout(nvtt::TextureType_2D, srcW, srcH);
    inputOptions.setWrapMode(nvtt::WrapMode_Clamp);
    inputOptions.setNormalMap(false);
    inputOptions.setConvertToNormalMap(false);
    inputOptions.setNormalizeMipmaps(false);
    if (doGenMipMap)
        inputOptions.setMipmapGeneration(true);
    else
        inputOptions.setMipmapGeneration(false);

    switch (format)
    {
    case Image_R8G8B8A8:
        if (isUncompressedDDS)
            compressionOptions.setFormat(nvtt::Format_RGBA);
        else
        {
            if (dxtN == 1)
                compressionOptions.setFormat(nvtt::Format_DXT1a);
            else if (dxtN == 3)
                compressionOptions.setFormat(nvtt::Format_DXT3);
            else
                compressionOptions.setFormat(nvtt::Format_DXT5);
        }
        break;

    case Image_R8G8B8:
        if (isUncompressedDDS)
        {
            if (!doGenMipMap)
                compressionOptions.setFormat(nvtt::Format_RGB); //for current nvtt implementation, same as RGBA
            else
                compressionOptions.setFormat(nvtt::Format_RGBA); // mipmaps should be ALWAYS generated as 32-bit and with dimension power of 2
            // to avoid any resampling in the renderer! (AB)
        }
        else
        {
            if (isDxt1Allowed)
                compressionOptions.setFormat(nvtt::Format_DXT1);
            else if (dxtN == 3)
                compressionOptions.setFormat(nvtt::Format_DXT3);
            else
                compressionOptions.setFormat(nvtt::Format_DXT5);
        }
        break;
    case Image_A8:
        compressionOptions.setFormat(nvtt::Format_RGBA); //no A_8 format in current implementation of nvtt
        break;

    default:
        break;
    }
    //int tmp=nvtt::estimateSize(inputOptions, compressionOptions);
    return compressor.estimateSize(inputOptions, compressionOptions);
}

//OutputHandler is used by nvtt::compress to write output DDS file
struct GOutputHandler : public nvtt::OutputHandler
{
    GOutputHandler() : Total(0), Progress(0), Percentage(0), pOutFile(NULL) {}
    GOutputHandler(File *pFile ) : Total(0), Progress(0), Percentage(0) 
    {
        pOutFile = pFile;
    }
    virtual ~GOutputHandler() { }

    virtual void setTotal(int t)
    {
        Total = t;
    }

    virtual void beginImage(int size, int width, int height, int depth, int face, int miplevel)
    {
        SF_UNUSED4(size, width, height, depth);
        SF_UNUSED2(face, miplevel);
        // ignore.
    }

    // Output data.
    virtual bool writeData(const void * data, int size)
    {
        return ((int)size == pOutFile->Write((const UByte*)data, (int)size));
        
    }

    int     Total;
    int     Progress;
    int     Percentage;
    File * pOutFile;
};

//OutputHandler is used by nvtt::compress
struct GErrorHandler : public nvtt::ErrorHandler
{
    virtual void error(nvtt::Error e)
    {
        GDXTHelper::LastError=e;    
        SF_ASSERT(0);//
    }
};

static void GImage2NvColor32Buff(const ImageData& srcImg, nvColor32* nvImage)
{
    SF_ASSERT(nvImage);
    for (unsigned y = 0; y < srcImg.GetSize().Height; y++)
    {
        const UByte* pscanline = srcImg.GetScanline(y);
        switch(srcImg.Format)
        {
        case Image_R8G8B8:
            {
                for (unsigned x = 0; x < srcImg.GetWidth(); x++, pscanline += 3)
                {
                    nvColor32 & pix = nvImage[y*srcImg.GetWidth()+x];
                    pix.r = pscanline[0];
                    pix.g = pscanline[1];
                    pix.b = pscanline[2];
                    pix.a = 0xFF;
                }
            }
            break;

        case Image_R8G8B8A8:
            {
                for (unsigned x = 0; x < srcImg.GetWidth(); x++, pscanline += 4)
                {
                    nvColor32 & pix = nvImage[y*srcImg.GetWidth()+x];
                    pix.r = pscanline[0];
                    pix.g = pscanline[1];
                    pix.b = pscanline[2];
                    pix.a = pscanline[3];

                }

            }
            break;

        case Image_A8:
            {
                for (unsigned x = 0; x < srcImg.GetWidth(); x++, pscanline += 1)
                {
                    nvColor32 & pix = nvImage[y*srcImg.GetWidth()+x];

                    pix.r = pscanline[0];
                    pix.g = pscanline[0];
                    pix.b = pscanline[0];
                    pix.a = pscanline[0];

                }
            }
            break;

                default:
                    SF_ASSERT(0);
        }
    }
}

static nvtt::MipmapFilter NvFilterConst(GDXTHelper::MipFilterTypes filter)
{
    switch(filter)
    {
    case GDXTHelper::nvFilterBox:         return nvtt::MipmapFilter_Box;    
    case GDXTHelper::nvFilterTriangle:    return nvtt::MipmapFilter_Triangle;
    case GDXTHelper::nvFilterKaiser:      return nvtt::MipmapFilter_Kaiser;
    }
    return nvtt::MipmapFilter_Box;
}


static nvtt::Quality NvQualityConst(GDXTHelper::QualitySetting qual)
{
    switch(qual)
    {
    case GDXTHelper::QualityFastest:    return nvtt::Quality_Fastest;
    case GDXTHelper::QualityNormal:     return nvtt::Quality_Normal;
    case GDXTHelper::QualityProduction: return nvtt::Quality_Production;
    case GDXTHelper::QualityHighest:    return nvtt::Quality_Highest;
    }
    SF_ASSERT(0);
    return nvtt::Quality_Fastest;
}

RawImage* ExportCompressor::Rescale(const Image* psrcimage, 
                            ExportCompressor::RescaleTypes rescale, 
                            ExportCompressor::RescaleFilterTypes rescaleFilter, 
                            ImageFormat destImageFormat)
{
    SF_UNUSED(destImageFormat);
    //Ptr<RawImage> pimage = *new RawImage(*psrcimage);
    //Ptr<RawImage> pargbImage = *pimage->ConvertImage(Image_R8G8B8A8);
	ImageData srcimgData;
	RawImage* ptempImage;
	ptempImage = RawImage::Create(Image_R8G8B8A8, 1, psrcimage->GetSize(), 0);
	ptempImage->GetImageData(&srcimgData);
	psrcimage->Decode(&srcimgData, GetImageConvertFunc(Image_R8G8B8A8, psrcimage->GetFormat()));
	RawImage* prescaledImage = CreateResizedImage(&srcimgData, rescale, rescaleFilter /*, targetWidth, targetHeight*/);
	if (prescaledImage)
	{
		ptempImage->Release();
		return prescaledImage;
	}
	else
	{
		return ptempImage;
	}
}

bool GDXTHelper::CompressToFile(const Render::Image* psrcimage, File* pdstFile, CompressionSettinns* psettings)
{
    DXTSettings* ps = (DXTSettings*) psettings;
    ExportCompressor::RescaleTypes rescale = ps->Rescale;
    bool isUncompressedDDS = ps->IsUncompressed;
    // If we compress dds or generate mipmaps image must be rescaled
    if (rescale == RescaleNone && (!isUncompressedDDS || ps->DoGenMipMap ))
        rescale = RescaleBiggestPower2;
    //Ptr<RawImage> pimage     = *new RawImage(*psrcimage);
    //Ptr<RawImage> pargbImage = *pimage->ConvertImage(RawImage::Image_ARGB_8888);
	ImageData srcimgData;
	Ptr<RawImage> ptempImage;
	ptempImage = *RawImage::Create(Image_R8G8B8A8, 1, psrcimage->GetSize(), 0);
	ptempImage->GetImageData(&srcimgData);
	psrcimage->Decode(&srcimgData, GetImageConvertFunc(Image_R8G8B8A8, psrcimage->GetFormat())); 
	Ptr<RawImage> scaledImage;
	scaledImage =  *CreateResizedImage(&srcimgData, rescale, ps->RescaleFilter);
	if (!scaledImage)
		scaledImage = ptempImage;

    // Do not compress DDS for images smaller then 4x4
    if ((scaledImage->GetSize().Width < 4) || (scaledImage->GetSize().Height < 4))
        isUncompressedDDS = true;

    nvtt::InputOptions       inputOptions;
    nvtt::CompressionOptions compressionOptions;
    nvtt::Compressor         compressor;
    
    nvtt::MipmapFilter  nvMipFilter = NvFilterConst(ps->MipFilter);
    nvtt::Quality       nvQuality   = NvQualityConst(ps->Quality);

	ImageData scaledImageData;
	scaledImage->GetImageData(&scaledImageData);
    nvColor32 *pimgBuff = (nvColor32*) SF_ALLOC(scaledImageData.GetWidth() * scaledImageData.GetHeight() * sizeof(nvColor32),
        Stat_Image_Mem);
    GImage2NvColor32Buff(scaledImageData, pimgBuff);

    inputOptions.setTextureLayout(nvtt::TextureType_2D, scaledImageData.GetWidth(), scaledImageData.GetHeight());
    inputOptions.setMipmapData(pimgBuff, scaledImageData.GetWidth(), scaledImageData.GetHeight());
    SF_FREE(pimgBuff);

    inputOptions.setWrapMode(nvtt::WrapMode_Clamp);

    inputOptions.setNormalMap(false);
    inputOptions.setConvertToNormalMap(false);
    inputOptions.setGamma(2.2f, 2.2f); //values from nvidia code
    inputOptions.setNormalizeMipmaps(false);

    compressionOptions.setQuality(nvQuality);
    compressor.enableCudaAcceleration(false); //no cuda
    compressionOptions.setColorWeights(1, 1, 1);

    if (ps->DoGenMipMap)
    {
        inputOptions.setMipmapGeneration(true);
        inputOptions.setMipmapFilter(nvMipFilter);
    }
    else
        inputOptions.setMipmapGeneration(false);

    switch (psrcimage->GetFormat())
    {
	case Image_R8G8B8A8:
        if (isUncompressedDDS)
            compressionOptions.setFormat(nvtt::Format_RGBA);
        else
        {
            if (ps->DxtN == 1)
                compressionOptions.setFormat(nvtt::Format_DXT1a);
            else if (ps->DxtN == 3)
                compressionOptions.setFormat(nvtt::Format_DXT3);
            else
                compressionOptions.setFormat(nvtt::Format_DXT5);
        }
        break;

    case Image_R8G8B8:
        if (isUncompressedDDS)
        {
            if (!ps->DoGenMipMap)
                compressionOptions.setFormat(nvtt::Format_RGB); //for current nvtt implementation, same as RGBA
            else
                compressionOptions.setFormat(nvtt::Format_RGBA); // mipmaps should be ALWAYS generated as 32-bit and with dimension power of 2
            // to avoid any resampling in the renderer! (AB)
        }
        else
        {
            if (ps->IsDxt1Allowed)
                compressionOptions.setFormat(nvtt::Format_DXT1);
            else if (ps->DxtN == 3)
                compressionOptions.setFormat(nvtt::Format_DXT3);
            else
                compressionOptions.setFormat(nvtt::Format_DXT5);
        }
        break;
    case Image_A8:
        compressionOptions.setFormat(nvtt::Format_A8); 
        break;

        default:
            break;
    }

    GOutputHandler outputHandler(pdstFile);
    GErrorHandler  errorHandler;
    outputHandler.setTotal(compressor.estimateSize(inputOptions, compressionOptions));
    
    nvtt::OutputOptions outputOptions;
    outputOptions.setOutputHandler(&outputHandler);
    outputOptions.setErrorHandler(&errorHandler);

    compressor.process(inputOptions, compressionOptions, outputOptions);

    return true;    
}


const char* GDXTHelper::GetLastErrorString()
{
    return nvtt::errorString( (nvtt::Error)GDXTHelper::LastError);
}

using namespace pvrtexlib;
bool GPVRHelper::CompressToFile(const Render::Image* psrcimage, File* pdstFile, CompressionSettinns* psettings)
{
    PVRSettings* ps = (PVRSettings*) psettings;
    ExportCompressor::RescaleTypes rescale = ps->Rescale;

    if (rescale == RescaleNone || rescale == RescalePreScale) //looks like PVRTC formats require power of 2
        rescale = RescaleBiggestPower2;
    ImageData srcimgData;
    Ptr<RawImage> ptempImage;
    ptempImage = *RawImage::Create(Image_R8G8B8A8, 1, psrcimage->GetSize(), 0);
    ptempImage->GetImageData(&srcimgData);
    psrcimage->Decode(&srcimgData, GetImageConvertFunc(Image_R8G8B8A8, psrcimage->GetFormat())); 
    Ptr<RawImage> scaledImage;
    scaledImage =  *CreateResizedImage(&srcimgData, rescale, ps->RescaleFilter, true);
    if (!scaledImage)
        scaledImage = ptempImage;

    ImageData scaledImageData;
    scaledImage->GetImageData(&scaledImageData);

    PixelType format;
    if (ps->IsUncompressed || 
        scaledImageData.GetWidth() < 8 || scaledImageData.GetHeight() < 8 ||
        (ps->PVRn == 2 && (scaledImageData.GetWidth() < 16 || scaledImageData.GetHeight() < 16)))
    {
        format = OGL_RGBA_8888;
    }
    else if (ps->Format == PVRSettings::FormatETC)
    {
        if (psrcimage->GetFormat() == Image_R8G8B8A8) //currently ETC does not support alpha
        {
            format = OGL_RGBA_8888;
            fprintf(stderr, "\nETC compression does not support alpha. Saving uncompressed texture.\n");
        }
        else
            format = ETC_RGB_4BPP;
    }
    else
    {
        if (ps->PVRn == 2)
            format = MGLPT_PVRTC2;
        else
            format = MGLPT_PVRTC4;
    }

    UInt32 mipcount = 0;
    if (ps->DoGenMipMap)
    {
        UInt32 size = Alg::Max<UInt32>(scaledImageData.GetWidth(), scaledImageData.GetHeight());
        while ( size >>= 1 )
            ++mipcount;
    }
    bool success = true;
    PVRTRY
    {
        PVRTextureUtilities *PVRU = PVRTextureUtilities::getPointer();
        CPVRTexture sOriginalTexture( scaledImageData.GetWidth(), // u32Width,
            scaledImageData.GetHeight(), // u32Height,
            0, // u32MipMapCount,
            1, // u32NumSurfaces,
            false, // bBorder,
            false, // bTwiddled,
            false, // bCubeMap,
            false, // bVolume,
            false, // bFalseMips,
            true, // bHasAlpha
            false, // bVerticallyFlipped
            eInt8StandardPixelType, // ePixelType,
            0.0f, // fNormalMap,
            (uint8*)scaledImageData.pPlanes->pData);

        CPVRTextureHeader sProcessHeader(sOriginalTexture.getHeader());
        // specify desired mip map levels
        sProcessHeader.setMipMapCount(mipcount);

        // preprocess the texture; creates MIP-levels and calculates normal map
        PVRU->ProcessRawPVR(sOriginalTexture,sProcessHeader);
        // create texture to encode to
        CPVRTexture sCompressedTexture(sOriginalTexture.getHeader());
        // set required encoded pixel type
        sCompressedTexture.setPixelType(format);
        // encode texture
        PVRU->CompressPVR(sOriginalTexture, sCompressedTexture);
        // write to file specified
        String path = pdstFile->GetFilePath();
        pdstFile->Close();
        sCompressedTexture.writeToFile(path.ToCStr()); //"C:\\dev\\gfxexport\\image/image.pvr");

    }
    PVRCATCH(myException)
    {
        success = false;
        // handle any exceptions here
        fprintf(stderr, "Exception PVRTCLib: %s",myException.what());
    }

    return success;
}
