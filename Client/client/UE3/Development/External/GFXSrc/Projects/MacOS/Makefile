
XCODE_DEV := $(shell ls -d /Developer /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer 2>/dev/null | head -1)
MACOS_SDK := $(XCODE_DEV)/SDKs/MacOSX10.6.sdk
MACOS_VER := 10.6

APPS += kits

ifeq ($(strip $(USEFMOD)),1)
APPPKGLIBS += 3rdParty/fmod/MacOS/lib/libfmodex.dylib
endif

ifeq ($(strip $(PX)),)

ifeq ($(strip $(EVAL)),1)
MKEVAL := EVAL=1
endif

ARCHES := $(shell find $(MACOS_SDK)/usr/lib/ -name crt3.o |sed -ne '/[0-9\.]*\/[0-9a-z_]*\/crt/{s/^.*\/[0-9\.]*\/\(.*\)\/crt.*$$/\1/;p;}; /[0-9\.]*\/crt/{s/^.*\/\([a-z0-9_]*\)-apple.*$$/\1/;p;};'|sort|uniq|grep -v pc)
COMMONARCH := $(firstword $(ARCHES))

define EXPAND_ARCHES
$(foreach v,$(ARCHES),$(1)-$(v)/$(2))
endef
define BUILD_ARCHES
$(foreach v,$(ARCHES),
Bin/$(P)-$(v)/$(1):
	$(MAKE) P=$(P)/$(v) C=$(C) $(MKEVAL) Bin/$(P)-$(v)/$(2)
)
endef
define BUILD_ARCH_LIBS
$(foreach v,$(ARCHES),
Lib/$(P)-$(v)/%.a:
	$(MAKE) P=$(P)/$(v) C=$(C) $(MKEVAL) Lib/$(P)-$(v)/$$*.a
)
endef
$(eval $(call BUILD_ARCH_LIBS))

define BUILD_APP_EXE
TARGETS += $(BINDIR)/$(1)
$(BINDIR)/$(1): Bin/$(P)-$(COMMONARCH)/$(1)
	@mkdir -p $$(dir $$@)
	@echo "  lipo   $$@"
	@lipo -create -o $$@ $$^

$(call BUILD_ARCHES,$(1),$(1))
endef

define BUILD_APP_PKG
TARGETS += $(BINDIR)/$(1).app
.PHONY: $(BINDIR)/$(1).app $(call EXPAND_ARCHES,Bin/$(P),$(1).app/Contents/MacOS/$(1))

$(BINDIR)/$(1).app: $(call EXPAND_ARCHES,Bin/$(P),$(1).app/Contents/MacOS/$(1))
	@mkdir -p $$@/Contents/MacOS
	@(cd Bin/MacOS/Resources/FxPlayer/; tar c .) | (cd $(BINDIR)/$(1).app/Contents; tar x)
ifneq ($(strip $(APPPKGLIBS)),)
	@cp -f $(APPPKGLIBS) $(BINDIR)/$(1).app/Contents/MacOS
endif
	@echo "  lipo   $$@"
	@lipo -create -o $$@/Contents/MacOS/$(1) $$^
	@cp -f Bin/$(P)-powerpc/$(1).app/Contents/*.swf $$@/Contents 2>/dev/null || true

$(call BUILD_ARCHES,$(1).app/Contents/MacOS/$(1),$(1).app)
endef

define BUILD_LIPO_LIB
TARGETS += $(LIBDIRP)/$(1)
$(LIBDIRP)/$(1): $(call EXPAND_ARCHES,Lib/$(P),$(1))
	@mkdir -p $$(dir $$@)
	@echo "  lipo   $$@"
	@lipo -create -o $$@ $$^
endef

ALLTARGETS := $(shell $(MAKE) P=$(P)/$(COMMONARCH) C=$(C) $(MKEVAL) list | grep -v ^make)
APPTARGETS := $(shell for i in $(ALLTARGETS); do echo $$i | grep ^Bin.*app | sed -e 's/Bin\/$(P)-$(COMMONARCH)\///g;s/\.app//g'; done)
EXETARGETS := $(shell for i in $(ALLTARGETS); do echo $$i | grep ^Bin/$(P).* | sed -e 's/Bin\/$(P)-$(COMMONARCH)\///g;s/.*\.app//g'; done)
LIBTARGETS := $(shell for i in $(ALLTARGETS); do echo $$i | grep ^Lib/$(P).* | grep -v gfxvideo | sed -e 's/Lib\/$(P)-$(COMMONARCH)\///g'; done)

$(foreach v,$(LIBTARGETS),$(eval $(call BUILD_LIPO_LIB,$(v))))
$(foreach v,$(APPTARGETS),$(eval $(call BUILD_APP_PKG,$(v))))
$(foreach v,$(EXETARGETS),$(eval $(call BUILD_APP_EXE,$(v))))

default: $(TARGETS)

SPECIAL_BUILD := 1

else

LD_Map        :=
LD_Strip      :=

PXM := $(PX)
ifeq ($(PX),x86_64)
MACOS_SDK := $(XCODE_DEV)/SDKs/MacOSX10.6.sdk
PXM := i686
else
ifeq ($(PX),ppc64)
PXM := powerpc
endif
endif


ifneq ($(PT),clang)

MACOS_VER := $(shell echo $(MACOS_SDK) | sed -e 's/^.*MacOSX\([0-9]*\)\.\([0-9]*\).*/\1.\2/')

DARWINV := $(firstword $(shell (cd $(MACOS_SDK)/usr/lib/gcc/ && ls -rd $(PXM)-apple-darwin* | sed -e 's/.*darwin\(.*\)$$/\1/;')))
CCV := $(firstword $(shell (cd $(MACOS_SDK)/usr/lib/gcc/$(PXM)-apple-darwin$(DARWINV) && ls)))


PCFLAGS += -nostdinc -F$(MACOS_SDK)/System/Library/Frameworks -isystem $(MACOS_SDK)/usr/lib/gcc/$(PXM)-apple-darwin$(DARWINV)/$(CCV)/include -isystem $(MACOS_SDK)/usr/include -isystem $(MACOS_SDK)/usr/include/c++/4.0.0/$(PXM)-apple-darwin$(DARWINV) -isystem $(MACOS_SDK)/usr/include/c++/4.0.0 
PCFLAGS += -mmacosx-version-min=$(MACOS_VER)

ifeq ($(PX),x86_64)
LDFLAGS += -L$(MACOS_SDK)/usr/lib/gcc/$(PXM)-apple-darwin$(DARWINV)/$(CCV)/x86_64
endif
LDFLAGS += -L$(MACOS_SDK)/usr/lib/gcc/$(PXM)-apple-darwin$(DARWINV)/$(CCV) -Wl,-syslibroot,$(MACOS_SDK) #-L$(MACOS_SDK)/usr/X11R6/lib

LDFLAGS += -mmacosx-version-min=$(MACOS_VER)

endif

PP :=

ifeq ($(PX),powerpc)
PCFLAGS += -arch ppc -maltivec
LDFLAGS += -arch ppc
endif
ifeq ($(PX),ppc64)
PCFLAGS += -arch ppc64 -maltivec
LDFLAGS += -arch ppc64
endif
ifeq ($(PX),i686)
PCFLAGS += -arch i686 -msse -msse2 -mmmx
LDFLAGS += -arch i686
endif
ifeq ($(PX),x86_64)
PCFLAGS += -arch x86_64
LDFLAGS += -arch x86_64
endif

EXT_BUILD_ENVS = CC="$(PP)gcc $(PCFLAGS)" CXX="$(PP)g++ $(PCFLAGS)" LDFLAGS="$(LDFLAGS)" LD="$(PP)ld" AR="$(PP)ar rc" RANLIB=$(P_RANLIB)

BUILD_REQ := diskutil

ifeq ($(PT),clang)
$(OBJDIR)/%.$(CSO)o : %.mm
	@mkdir -p $(dir $@)
	@echo "  cc     $<"
	$(CMD)$(P_CXX) $(CXXFLAGS) $(CXXCFLAGS) $(OBJCXXFLAGS) -Wp,-dependency-file,$(@:.o=.d),-MT,$@ -o $@ -c $<
else
$(OBJDIR)/%.$(CSO)o : %.mm
	@mkdir -p $(dir $@)
	@echo "  cc     $<"
	$(CMD)$(P_CXX) $(CXXFLAGS) $(CXXCFLAGS) $(OBJCXXFLAGS) -Wp,-MMD,$(@:.o=.d),-MT,$@ -o $@ -c $<
endif

SRCS += Src/Platform/Platform_Mac_GL.cpp Src/Platform/Platform_Posix.cpp

$(call BUILD_GFX_LIB,libgfxrender_gl)

GFXlibgfxSRCS += Src/Kernel/SF_ThreadsPthread.cpp

GFX_RENDERERS += MAC
GFXLIBS_MAC = -framework Cocoa -framework OpenGL

GFXDEPS_MAC := $(LIBDIR)/libgfx.a $(LIBDIR)/libgfxrender_gl.a $(LIBDIRP)/libjpeg.a \
               $(SF_PLATFORM) $(OBJDIR)/Src/Platform/Platform_Mac_GL.o \
               $(OBJDIR)/Src/Platform/Platform_Posix.o \
               $(LIBDIR)/libgfxrender_gl$(LIBSUFFIX)

FMODLIB := libfmodex.dylib

define BUILD_GFX_REN_APP
TARGETS += $(BINDIR)/$(1)$(6)$(CSX).app
SRCS += $(2) $(patsubst %.cpp,%.$(3).cpp,$(5))
.PHONY: $(BINDIR)/$(1)$(6)$(CSX).app
LIBDEPTARGETS += $(BINDIR)/$(1)$(6)$(CSX).app/Contents/MacOS/$(1)$(6)$(CSX)
ifneq ($(5),)
$(call COMPILE_CPP_RULE,.$(3),$$(GFXCCFLAGS_$(3)))
endif
$(BINDIR)/$(1)$(6)$(CSX).app: $(BINDIR)/$(1)$(6)$(CSX).app/Contents/MacOS/$(1)$(6)$(CSX)
	@mkdir -p $$(dir $$@)
	@(cd Bin/MacOS/Resources/FxPlayer/; tar c .) | (cd $(BINDIR)/$(1)$(6)$(CSX).app/Contents; tar x)
ifneq ($(strip $(APPPKGLIBS)),)
	@cp -f $(APPPKGLIBS) $(BINDIR)/$(1)$(CSX).app/Contents/MacOS
endif
$(BINDIR)/$(1)$(6)$(CSX).app/Contents/MacOS/$(1)$(6)$(CSX): $$(GFXDEPS_$(3)) $(patsubst %.cpp,$(OBJDIR)/%.o,$(2)) $(patsubst %.cpp,$(OBJDIR)/%.$(3).o,$(5)) $(GFXDEPS) $(GFXPLDEPS)
	@mkdir -p $$(dir $$@)
	@echo "  ld     $$@"
	$$(CMD)$$(P_CXXLD) $$(LDFLAGS) $$(GFXLDFLAGS_$(3)) -o $$@ $$^ $$(LIBDIR)/libgfx.a $$(APPLIBS) $$(GFXLIBS) $$(GFXLIBS_$(3)) $(4)
ifeq ($(strip $(USEFMOD)),1)
	@install_name_tool -change ./libfmodex.dylib @executable_path/libfmodex.dylib $$@
endif
endef


define BUILD_GFX_PKG_APP
TARGETS += $(BINDIR)/$(1)$(CSX).app
SRCS += $(2)
.PHONY: $(BINDIR)/$(1)$(CSX).app
LIBDEPTARGETS += $(BINDIR)/$(1)$(CSX).app/Contents/MacOS/$(1)$(CSX)
$(BINDIR)/$(1)$(CSX).app: $(BINDIR)/$(1)$(CSX).app/Contents/MacOS/$(1)$(CSX)
	@mkdir -p $$(dir $$@)
	@(cd Bin/MacOS/Resources/FxPlayer/; tar c .) | (cd $(BINDIR)/$(1)$(CSX).app/Contents; tar x)
ifneq ($(strip $(APPPKGLIBS)),)
	@cp -f $(APPPKGLIBS) $(BINDIR)/$(1)$(CSX).app/Contents/MacOS
endif
$(BINDIR)/$(1)$(CSX).app/Contents/MacOS/$(1)$(CSX): $(patsubst %.cpp,$(OBJDIR)/%.o,$(patsubst %.mm,$(OBJDIR)/%.o,$(2))) $(GFXDEPS)
	@mkdir -p $$(dir $$@)
	@echo "  ld     $$@"
	$$(CMD)$$(P_CXXLD) $$(LDFLAGS) -o $$@ $$^ $$(APPLIBS) $$(GFXLIBS) $(3)
ifeq ($(strip $(USEFMOD)),1)
	@install_name_tool -change ./libfmodex.dylib @executable_path/libfmodex.dylib $$@
endif
endef

# Disabled for the time being.
#$(eval $(call BUILD_GFX_PKG_APP,FxPlayerTiny,Src/GRenderer/GRendererOGLImpl.cpp Src/GRenderer/GRendererCommonImpl.cpp \
#    Apps/Samples/GFxPlayerTiny/GFxPlayerTinyMacGL.mm,-framework Cocoa -framework OpenGL))
#
#$(BINDIR)/FxPlayerTiny$(CSX).app: $(BINDIR)/FxPlayerTiny$(CSX).app/Contents/Window.swf
#$(BINDIR)/FxPlayerTiny$(CSX).app/Contents/Window.swf: Bin/Samples/Window.swf
#	@mkdir -p $(dir $@)
#	@cp $^ $@
#
#FXPLAYER_RT_SRCS := Apps/Samples/Common/FontConfigParser.cpp
#
#$(call BUILD_GFX_REN_APPS,FxPlayerSWFToTexture,$(FXPLAYER_RT_SRCS) Apps/Samples/RenderTexture/FxPlayerSWFToTextureGL.cpp Apps/Samples/Common/MathLib.cpp)
#$(call BUILD_GFX_REN_APPS,FxPlayerTextureInSWF,$(FXPLAYER_RT_SRCS) Apps/Samples/RenderTexture/FxPlayerTextureInSWFGL.cpp)
#
#$(BINDIR)/FxPlayerSWFToTexture$(CSX).app: $(BINDIR)/FxPlayerSWFToTexture$(CSX).app/Contents/3DWindow.swf $(BINDIR)/FxPlayerSWFToTexture$(CSX).app/Contents/3DWindowBackground.swf
#$(BINDIR)/FxPlayerSWFToTexture$(CSX).app/Contents/3DWindow.swf: Bin/SWFToTexture/3DWindow.swf
#	@mkdir -p $(dir $@)
#	@cp $^ $@
#$(BINDIR)/FxPlayerSWFToTexture$(CSX).app/Contents/3DWindowBackground.swf: Bin/SWFToTexture/3DWindowBackground.swf
#	@mkdir -p $(dir $@)
#	@cp $^ $@
#
#$(BINDIR)/FxPlayerTextureInSWF$(CSX).app: $(BINDIR)/FxPlayerTextureInSWF$(CSX).app/Contents/Window_texture.swf
#$(BINDIR)/FxPlayerTextureInSWF$(CSX).app/Contents/Window_texture.swf: Bin/RenderTexture/Window_texture.swf
#	@mkdir -p $(dir $@)
#	@cp $^ $@

endif
