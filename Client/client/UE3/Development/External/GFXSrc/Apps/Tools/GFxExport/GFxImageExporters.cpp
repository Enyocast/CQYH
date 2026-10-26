/**************************************************************************

Filename    :   GFxImageExporters.cpp
Content     :   SWF to GFX resource extraction and conversion tool
Created     :   October, 2006
Authors     :   Artyom Bolgar, Dmitry Polenur

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "GFxExport.h"
#include "Kernel/SF_SysFile.h"
#include "Render/ImageFiles/TGA_ImageFile.h"
#include "Render/ImageFiles/JPEG_ImageFile.h"
#include "Render/ImageFiles/DDS_ImageFile.h"
class GFxTGAExporter : public GFxImageExporter
{
    GFxImageExporterParams Params;
public:
    const char* GetName() const         { return "TGA"; }
    const char* GetDescription() const  { return "Truevision (Targa or TGA)"; }
    int         GetFormatId() const     { return FileTypeConstants::File_TGA; }
    const char* GetDefaultExtension() const { return "tga"; }

    GFxImageExporterParams& InitParams
        (UInt32 charId, const GFxDataExporter* pexp, GFxExportImageDescr* pimgDescr, Render::Image* pimage, File* pfile = 0,
         GFxImageExporterParams::ImageExportType expType = GFxImageExporterParams::IET_Image)
    {
        Params.Set(charId, pexp, pimgDescr, pimage, pfile, expType);
        return Params;
    }

    bool        MightBeRescaled() const { return true; }
    bool        NeedToBeConverted(Render::Image* pimage, int destFormat) const
    {
        return (destFormat != pimage->GetFormat());
    }

    bool        Write(ExportCompressor * pdxtHelper )
    {
        SF_UNUSED(pdxtHelper);
        //if (!Params.ImagePtr->WriteTga(Params.FilePtr))
		if(!Render::TGA::FileWriter::WriteImage(Params.FilePtr, Params.ImagePtr))
        {
            fprintf(stderr, "Error: Can't write to '%s' file\n", Params.FilePtr->GetFilePath());
            return false;
        }
        return true;
    }

    // Read file and create Image. This method used for sharing images. If this method
    // is not implemented (returns NULL) then images of this format cannot be shared
    Render::Image*     Read(const char* filePath)
    {
        Ptr<File> pin = *new SysFile(filePath, File::Open_Read);
        if (!pin || !pin->IsValid())
        {
            fprintf(stderr, "Error: Can't open source file '%s' to read from\n", filePath);
            return NULL;
        }
		return Render::TGA::FileReader::ReadImage(pin);
    }

    virtual void Clear() { Params.Clear(); }
};
GFX_REGISTER_IMAGE_EXPORTER(GFxTGAExporter);

class GFxDDSExporter : public GFxImageExporter
{
    struct GFxDDSImageExporterParams : public GFxImageExporterParams
    {
        bool                        UncompressedDDS;
    } Params;
public:
    const char* GetName() const         { return "DDS"; }
    const char* GetDescription() const  { return "DirectDraw Surface (DDS)"; }
    int         GetFormatId() const     { return FileTypeConstants::File_DDS; }
    const char* GetDefaultExtension() const { return "dds"; }

    GFxImageExporterParams& InitParams
        (UInt32 charId, const GFxDataExporter* pexp, GFxExportImageDescr* pimgDescr, Render::Image* pimage, File* pfile = 0,
         GFxImageExporterParams::ImageExportType expType = GFxImageExporterParams::IET_Image)
    {
        Params.Set(charId, pexp, pimgDescr, pimage, pfile, expType);
        Params.UncompressedDDS = pexp->IsUncompressedDDS();

        if (ResourceId(Params.CharacterId).GetIdType() == ResourceId::IdType_GradientImage)
        {
            if (Params.Exporter->GetGradientImagesBits() > 0)
                Params.UncompressedDDS = true;
            else
            {
                // check, is it for linear gradient (size 256x1) or not.
                // if linear - do not use compressed DDS, since this will 
                // resize gradient up to 256x4.
                if (Params.ImageDescr->TargetHeight == 1)
                    Params.UncompressedDDS = true;
                else
                    Params.UncompressedDDS = false;
            }
        }

        return Params;
    }

    bool        MightBeRescaled() const { return false; }
    bool        NeedToBeConverted(Render::Image*, int) const { return false; }

    bool        Write(ExportCompressor*  pdxtHelper)
    {
        DXTSettings settings;
        settings.DoGenMipMap = Params.Exporter->IsGenMipMapLevels();
        settings.IsDxt1Allowed = Params.Exporter->IsDXT1Allowed();
        settings.IsUncompressed = Params.UncompressedDDS;
        settings.MipFilter = Params.Exporter->GetMipFilter();
        settings.Quality = Params.Exporter->GetQuality();
        settings.Rescale = Params.Rescale;
        settings.RescaleFilter = Params.Exporter->GetRescaleFilter();
        settings.DxtN = Params.Exporter->GetDXTn();
        if (!pdxtHelper->CompressToFile(Params.ImagePtr, Params.FilePtr, &settings))
        {
            fprintf(stderr, "Error: Can't compress image '%s' to DDS, error: '%s'\n", Params.FilePtr->GetFilePath(), pdxtHelper->GetLastErrorString());
            return false;
        }
        return true;
    }

    // Read file and create Image. This method used for sharing images. If this method
    // is not implemented (returns NULL) then images of this format cannot be shared
    Render::Image*     Read(const char* filePath)
    {
        Ptr<File> pin = *new SysFile(filePath, File::Open_Read);
        if (!pin || !pin->IsValid())
        {
            fprintf(stderr, "Error: Can't open source file '%s' to read from\n", filePath);
            return NULL;
        }
        return Render::DDS::FileReader::ReadImage(pin);
    }

    virtual void Clear() { Params.Clear(); }
};
GFX_REGISTER_IMAGE_EXPORTER(GFxDDSExporter);

class GFxPVRExporter : public GFxImageExporter
{
    struct GFxPVRImageExporterParams : public GFxImageExporterParams
    {
        bool Uncompressed;
    } Params;
public:
    const char* GetName() const         { return "PVR"; }
    const char* GetDescription() const  { return "PVR"; }
    int         GetFormatId() const     { return FileTypeConstants::File_PVR; }
    const char* GetDefaultExtension() const { return "pvr"; }

    GFxImageExporterParams& InitParams
        (UInt32 charId, const GFxDataExporter* pexp, GFxExportImageDescr* pimgDescr, Render::Image* pimage, File* pfile = 0,
        GFxImageExporterParams::ImageExportType expType = GFxImageExporterParams::IET_Image)
    {
        Params.Set(charId, pexp, pimgDescr, pimage, pfile, expType);
        Params.Uncompressed = false;
        if (ResourceId(Params.CharacterId).GetIdType() == ResourceId::IdType_GradientImage)
        {
            if (Params.Exporter->GetGradientImagesBits() > 0)
                Params.Uncompressed = true;
            else
            {
                // check, is it for linear gradient (size 256x1) or not.
                // if linear - do not use compressed DDS, since this will 
                // resize gradient up to 256x4.
                if (Params.ImageDescr->TargetHeight == 1)
                    Params.Uncompressed = true;
                else
                    Params.Uncompressed = false;
            }
        }

        return Params;
    }

    bool        MightBeRescaled() const { return false; }
    bool        NeedToBeConverted(Render::Image*, int) const { return false; }

    bool        Write(ExportCompressor*  pdxtHelper)
    {
        PVRSettings settings;
        settings.DoGenMipMap = Params.Exporter->IsGenMipMapLevels();
        settings.IsUncompressed = Params.Uncompressed;
        settings.Rescale = Params.Rescale;
        settings.RescaleFilter = Params.Exporter->GetRescaleFilter();
        settings.PVRn = Params.Exporter->GetPVRn();
        settings.Format = PVRSettings::FormatPVRTC;
        if (!pdxtHelper->CompressToFile(Params.ImagePtr, Params.FilePtr, &settings))
        {
            fprintf(stderr, "Error: Can't compress image '%s' to DDS, error: '%s'\n", Params.FilePtr->GetFilePath(), pdxtHelper->GetLastErrorString());
            return false;
        }
        return true;
    }

    // Read file and create Image. This method used for sharing images. If this method
    // is not implemented (returns NULL) then images of this format cannot be shared
    Render::Image*     Read(const char* filePath)
    {
        SF_UNUSED(filePath);
        return NULL;
    }

    virtual void Clear() { Params.Clear(); }
};
GFX_REGISTER_IMAGE_EXPORTER(GFxPVRExporter);

class GFxETCExporter : public GFxImageExporter
{
    struct GFxETCImageExporterParams : public GFxImageExporterParams
    {
        bool Uncompressed;
    } Params;
public:
    const char* GetName() const         { return "ETC"; }
    const char* GetDescription() const  { return "ETC"; }
    int         GetFormatId() const     { return FileTypeConstants::File_ETC; }
    const char* GetDefaultExtension() const { return "pvr"; }

    GFxImageExporterParams& InitParams
        (UInt32 charId, const GFxDataExporter* pexp, GFxExportImageDescr* pimgDescr, Render::Image* pimage, File* pfile = 0,
        GFxImageExporterParams::ImageExportType expType = GFxImageExporterParams::IET_Image)
    {
        Params.Set(charId, pexp, pimgDescr, pimage, pfile, expType);
        Params.Uncompressed = false;
        if (ResourceId(Params.CharacterId).GetIdType() == ResourceId::IdType_GradientImage)
        {
            if (Params.Exporter->GetGradientImagesBits() > 0)
                Params.Uncompressed = true;
            else
            {
                // check, is it for linear gradient (size 256x1) or not.
                // if linear - do not use compressed DDS, since this will 
                // resize gradient up to 256x4.
                if (Params.ImageDescr->TargetHeight == 1)
                    Params.Uncompressed = true;
                else
                    Params.Uncompressed = false;
            }
        }

        return Params;
    }

    bool        MightBeRescaled() const { return false; }
    bool        NeedToBeConverted(Render::Image*, int) const { return false; }

    bool        Write(ExportCompressor*  pdxtHelper)
    {
        PVRSettings settings;
        settings.DoGenMipMap = Params.Exporter->IsGenMipMapLevels();
        settings.IsUncompressed = Params.Uncompressed;
        settings.Rescale = Params.Rescale;
        settings.RescaleFilter = Params.Exporter->GetRescaleFilter();
        settings.Format = PVRSettings::FormatETC;
        if (!pdxtHelper->CompressToFile(Params.ImagePtr, Params.FilePtr, &settings))
        {
            fprintf(stderr, "Error: Can't compress image '%s' to DDS, error: '%s'\n", Params.FilePtr->GetFilePath(), pdxtHelper->GetLastErrorString());
            return false;
        }
        return true;
    }
    // Read file and create Image. This method used for sharing images. If this method
    // is not implemented (returns NULL) then images of this format cannot be shared
    Render::Image*     Read(const char* filePath)
    {
        SF_UNUSED(filePath);
        return NULL;
    }

    virtual void Clear() { Params.Clear(); }
};
GFX_REGISTER_IMAGE_EXPORTER(GFxETCExporter);

class GFxORIGExporter : public GFxImageExporter
{
    struct GFxOrigImageExporterParams : public GFxImageExporterParams
    {
        String                  PathNoExt;
        const JpegDesc*         pJpegDesc;
    } Params;
public:
    const char* GetName() const         { return "ORIG"; }
    const char* GetDescription() const  { return "Original format: JPEG data will be saved as JPG files\n"
        "                         and lossless images will be saved as TGAs.\n"; }
    int         GetFormatId() const     { return FileTypeConstants::File_Original; }
    const char* GetDefaultExtension() const 
    { 
        if (Params.ImageDescr == NULL || Params.ImageDescr->Format == FileTypeConstants::File_JPEG)
        {
            return "jpg";
        }
        else
        {
            return "tga";
        }
        //return "jpg"; 
    }

    GFxImageExporterParams& InitParams
        (UInt32 charId, const GFxDataExporter* pexp, GFxExportImageDescr* pimgDescr, Render::Image* pimage, File* pfile = 0,
         GFxImageExporterParams::ImageExportType expType = GFxImageExporterParams::IET_Image)
    {
        Params.Set(charId, pexp, pimgDescr, pimage, pfile, expType);
        Params.pJpegDesc = Params.Exporter->GetJpegDescriptor(Params.CharacterId);
        if (Params.pJpegDesc)
        {
            if (Params.pJpegDesc->TagType != 35)
                Params.ImageDescr->Format = FileTypeConstants::File_JPEG;
            else
                Params.ImageDescr->Format = FileTypeConstants::File_TGA;
        }
        else
        {
            Params.ImageDescr->Format = FileTypeConstants::File_TGA;
            Params.pJpegDesc = 0;
        }
        return Params;
    }
    bool        MightBeRescaled() const { return false; }
    bool        NeedToBeConverted(Render::Image*, int) const { return false; }

    String   MakeFileName(const String& nameNoExt)
    {
        return nameNoExt + ((Params.ImageDescr->Format == FileTypeConstants::File_JPEG) ? ".jpg" : ".tga");
    }
    virtual String   MakePath(const String& path, const String& nameWithExt)
    {
        String p = path + nameWithExt;
        Params.PathNoExt = GFxDataExporter::CutExtension(p);
        return p;
    }

    bool        Write(ExportCompressor * pdxtHelper)
    {
        SF_UNUSED(pdxtHelper);
        if (Params.pJpegDesc)
        {
            if (Params.pJpegDesc->TagType == 35)
            {
                // if JPEG was used with alpha, we need to save the 32-bit TGA as main
                // image and only then JPEG.
                //if (!Params.ImagePtr->WriteTga(Params.FilePtr))
				if (!Render::TGA::FileWriter::WriteImage(Params.FilePtr, Params.ImagePtr))
                {
                    fprintf(stderr, "Error: Can't write to '%s' file\n", Params.FilePtr->GetFilePath());
                    return false;
                }
                Params.FilePtr->Close();

                // now need to reopen file as jpg and write data to it
                String destPath;
                destPath = Params.PathNoExt;
                destPath += ".jpg";
                Params.FilePtr = *new SysFile(destPath.ToCStr(),
                    File::Open_Write | File::Open_Truncate | File::Open_Create);
                if (!Params.FilePtr->IsValid() || !Params.FilePtr->IsWritable())
                {
                    fprintf(stderr, "Error: Can't open file '%s' for writing\n", destPath.ToCStr());
                    return false;
                }
            }

            // check if tagType == 6 and we have parsed tagType == 8 (JPEGTables) then
            // write these tables first.
            if (Params.pJpegDesc->TagType == 6)
            {
                const JpegDesc* pjpeg8Desc = Params.Exporter->GetJpegDescriptor(-1);
                if (pjpeg8Desc)
                {
                    if (Params.FilePtr->Write(pjpeg8Desc->pData, int(pjpeg8Desc->DataSize)) != int(pjpeg8Desc->DataSize))
                    {
                        fprintf(stderr, "Error: Can't write to '%s' file\n", Params.FilePtr->GetFilePath());
                        return false;
                    }
                }
            }
            if (Params.FilePtr->Write(Params.pJpegDesc->pData, int(Params.pJpegDesc->DataSize)) != int(Params.pJpegDesc->DataSize))
            {
                fprintf(stderr, "Error: Can't write to '%s' file\n", Params.FilePtr->GetFilePath());
                return false;
            }
            String destPath = Params.FilePtr->GetFilePath();
            Params.FilePtr->Close(); // close file and re-open for reading
            Params.FilePtr = *new SysFile(destPath.ToCStr(), File::Open_Read);
            if (!Params.FilePtr->IsValid())
            {
                fprintf(stderr, "Error: Can't open file '%s' for reading\n", destPath.ToCStr());
                return false;
            }

            Ptr<JPEGSystem> pjpegSystem = *JPEGSystem::CreateDefaultSystem();
            if (!pjpegSystem)  return false;
            // original format
            // Write original JPEG data without re-compression
            // First of all, re-read JPEG by jpeglib without decompression....
            JPEGInput* pjin = pjpegSystem->CreateSwfJpeg2HeaderOnly(Params.FilePtr);
            if (!pjin) return false;

            pjin->StartRawImage();
            void* prawData;
            pjin->ReadRawData(&prawData);
            Params.FilePtr->Close(); // close file and re-open for writing

            Params.FilePtr = *new SysFile(destPath.ToCStr(),
                File::Open_Write | File::Open_Truncate | File::Open_Create);
            if (!Params.FilePtr->IsValid() || !Params.FilePtr->IsWritable())
            {
                fprintf(stderr, "Error: Can't open file '%s' for writing\n", destPath.ToCStr());
                return false;
            }

            // write JPEG data back w/o re-compression
            JPEGOutput*    pjout = pjpegSystem->CreateOutput(Params.FilePtr);
            pjout->CopyCriticalParams(pjin->GetCInfo());
            pjout->WriteRawData(prawData);
            delete pjout;

            pjin->FinishImage();
            delete pjin;

            Params.FilePtr->Close();
        }
        else
        {
            //if (!Params.ImagePtr->WriteTga(Params.FilePtr))
			if (!Render::TGA::FileWriter::WriteImage(Params.FilePtr, Params.ImagePtr))
            {
                fprintf(stderr, "Error: Can't write to '%s' file\n", Params.FilePtr->GetFilePath());
                return false;
            }
        }
        return true;
    }

    // Read file and create Image. This method used for sharing images. If this method
    // is not implemented (returns NULL) then images of this format cannot be shared
    Render::Image*     Read(const char* filePath)
    {
        // check for extension first
        const char* pext = strrchr(filePath, '.');
        if (pext != NULL)
        {
            ++pext;
        }
        Ptr<File> pin = *new SysFile(filePath, File::Open_Read);
        if (!pin || !pin->IsValid())
        {
            fprintf(stderr, "Error: Can't open source file '%s' to read from\n", filePath);
            return NULL;
        }
        if (SFstricmp(pext, "tga") == 0)
            return Render::TGA::FileReader::ReadImage(pin);//Render::Image::ReadTga(pin);
        else if (SFstricmp(pext, "jpg") == 0)
        {
            //Ptr<JPEGSystem> pjpegSystem = *Render::JPEGSystem::CreateDefaultSystem();
            //if (pjpegSystem)
                return Render::JPEG::FileReader::ReadImage(pin);
        }
        return NULL;
    }

    virtual void Clear() { Params.Clear(); }
};
GFX_REGISTER_IMAGE_EXPORTER(GFxORIGExporter);


