/**************************************************************************

Filename    :   GFxExportMain.cpp
Content     :   SWF to GFX resource extraction and conversion tool
Created     :   October, 2006
Authors     :   Artyom Bolgar

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
#include "GFxExport.h"

GFxImageExporterFactoryBase* GFxImageExporterFactoriesArray[GFX_MAX_NUM_OF_IMAGE_EXPORTERS];
unsigned                     GFxImageExporterFactoriesArrayCount = 0; 

int main(int argc, char *argv[])
{
    GFx::System gfxInit;

    if (argc > 0)
    {
        GFxDataExporter exporter;
        for (unsigned i = 0; i < GFxImageExporterFactoriesArrayCount; ++i)
        {
            // fill 'exporter' by all registered image exporters.
            GFxImageExporter* pexp = GFxImageExporterFactoriesArray[i]->Create();
            exporter.AddImageExporter(pexp->GetFormatId(), pexp);
        }

#ifdef GFX_ENABLE_SOUND
        exporter.SetSoundExporter(CreateSoundExporter());
#endif

        if (argc == 1)
        {
            exporter.ShowHelpScreen();
            return -1;
        }

        if (exporter.ParseCommandLine(argc, argv))
        {
            exporter.Process();
        }
    }
    return 0;
}
