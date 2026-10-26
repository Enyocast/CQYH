
ifneq ($(strip $(call HAS_HEADER,X11/Xlib.h)),)
ifneq ($(findstring GFC_USE_ZLIB,$(CXXFLAGS) $(GCONFIG_DEFS)),)

GFXEXPORT_SRCS := Apps/Tools/GFxExport/GFxExport.cpp Apps/Tools/GFxExport/GFxExportMain.cpp Apps/Tools/GFxExport/GDXTHelper.cpp Apps/Tools/GFxExport/GFxExportFsCommands.cpp Apps/Tools/GFxExport/GFxImageExporters.cpp Apps/Demos/Common/FxSettings.cpp Apps/Tools/GFxExport/GFxExportPluginHandler.cpp

ifeq ($(strip $(USEFMOD)),1)
GFXEXPORT_SRCS += Apps/Tools/GFxExport/GFxSoundExporterFMOD.cpp
endif

INCLUDES += -isystem $(OBJDIRP)/3rdParty/nvtt/src

$(call BUILD_GFX_APP,gfxexport,$(GFXEXPORT_SRCS),-L$(OBJDIRP)/3rdParty/nvtt -lnvtt -ldl)

endif
endif
