/**************************************************************************

Filename    :   GDXTHelper.h
Content     :   Interface to NVidia DXT library 
Created     :   Sep, 2006
Authors     :   Artyom Bolgar, Dmitry Polenur

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#ifndef INC_GDXTHELPER_H
#define INC_GDXTHELPER_H

// GFx Includes
#include "Kernel/SF_Types.h"
#include "Kernel/SF_RefCount.h"
#include "Render/Render_ResizeImage.h"

using namespace Scaleform;
using namespace GFx;

// ***** GDXTHelper
// Does image rescaling and provides interface for nvtt library. 
// Used in GFxExport
struct CompressionSettinns;

class ExportCompressor : public RefCountBase<ExportCompressor, Stat_Default_Mem>
{
public:
    ExportCompressor() 
    {
        pRescaleFilterLut = 0;
    }
    virtual ~ExportCompressor()
    {
        if(pRescaleFilterLut)
            delete pRescaleFilterLut;
    }
    enum QualitySetting 
    {
        QualityFastest,
        QualityNormal,
        QualityProduction,
        QualityHighest,
    };
    enum RescaleTypes
    {
        RescaleNone,                // no rescale
        RescaleNearestPower2,       // rescale to nearest power of two
        RescaleBiggestPower2,       // rescale to next bigger power of 2
        RescaleSmallestPower2,      // rescale to smaller power of 2 
        RescaleNextSmallestPower2,  // rescale to next smaller power of 2
        RescalePreScale,            // rescale to this size
        RescaleRelScale,            // relative rescale
    };
    enum MipFilterTypes
    {
        nvFilterBox,      
        nvFilterTriangle, 
        nvFilterKaiser,
    };
    enum RescaleFilterTypes
    { 
        FilterBox,      
        FilterTriangle, 
        FilterQuadratic,
        FilterCatrom,   
        FilterMitchell, 
        FilterGaussian, 
        FilterSinc,     
        FilterBessel,   
        FilterHanning,  
        FilterHamming,  
        FilterBlackman, 
        FilterKaiser,
        FilterBicubic,
        FilterSpline16,
        FilterSpline36,
        FilterHermite,
        FilterQuadric,
        FilterLanczos,
        FilterBilinear,
    };
    Render::ImageFilterLut * pRescaleFilterLut;

    //Calculates destination width and height, made separate function for Info mode 
    static void CalculateWH(UInt32 srcW, UInt32 srcH, UInt32 &destW, UInt32 &destH, ExportCompressor::RescaleTypes rescale);
    //
    static UInt32 CalculateDDSSize( UInt32 srcW, UInt32 srcH, Render::ImageFormat format, 								int dxtN,
        bool IsUncompressed,
        bool doGenMipMap,
        bool isDxt1Allowed);

    Render::RawImage* Rescale(const Render::Image* psrcimage, 
        ExportCompressor::RescaleTypes rescale, 
        ExportCompressor::RescaleFilterTypes rescaleFilter, 
        Render::ImageFormat destImageFormat);

    virtual bool CompressToFile(const Render::Image* psrcimage, File* pdstFile, CompressionSettinns* psettings) = 0;
    virtual const char*  GetLastErrorString() {return NULL;}
    void CalculateResizeFilter(RescaleFilterTypes FilterType);
    Render::RawImage* CreateResizedImage(const Render::ImageData *psrc, ExportCompressor::RescaleTypes rescale, ExportCompressor::RescaleFilterTypes filterType, bool square = false /*, unsigned targetWidth, unsigned targetHeight*/);
};

struct CompressionSettinns
{
    ExportCompressor::RescaleTypes Rescale;
    ExportCompressor::RescaleFilterTypes RescaleFilter;
    bool IsUncompressed;
    bool DoGenMipMap;
};


class GDXTHelper : public ExportCompressor
{
public:
    GDXTHelper()
    {
    }
    virtual ~GDXTHelper()
    {
    }

    static int LastError;
    //
    static UInt32 CalculateDDSSize( UInt32 srcW, UInt32 srcH, Render::ImageFormat format, 								int dxtN,
        bool IsUncompressed,
        bool doGenMipMap,
        bool isDxt1Allowed);
    
    virtual bool CompressToFile(const Render::Image* psrcimage, File* pdstFile, CompressionSettinns* psettings);    
    virtual const char*  GetLastErrorString();
};

struct DXTSettings : public CompressionSettinns
{
    GDXTHelper::QualitySetting Quality;
    GDXTHelper::MipFilterTypes MipFilter;
    int DxtN; 
    bool IsDxt1Allowed;
};

class GPVRHelper : public ExportCompressor
{
public:
    GPVRHelper()
    {
    }
    virtual ~GPVRHelper()
    {
    }
    virtual bool CompressToFile(const Render::Image* psrcimage, File* pdstFile, CompressionSettinns* psettings);
    virtual const char*  GetLastErrorString() {return NULL;}
};

struct PVRSettings : public CompressionSettinns
{
    enum FormatTypes
    {
        FormatPVRTC,
        FormatETC
    };
    int PVRn;
    FormatTypes Format;
};


#endif //INC_GDXTHELPER_H
