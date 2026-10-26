# Copyright 2005-2011 Intel Corporation.  All Rights Reserved.
#
# The source code contained or described herein and all documents related
# to the source code ("Material") are owned by Intel Corporation or its
# suppliers or licensors.  Title to the Material remains with Intel
# Corporation or its suppliers and licensors.  The Material is protected
# by worldwide copyright laws and treaty provisions.  No part of the
# Material may be used, copied, reproduced, modified, published, uploaded,
# posted, transmitted, distributed, or disclosed in any way without
# Intel's prior express written permission.
#
# No license under any patent, copyright, trade secret or other
# intellectual property right is granted to or conferred upon you by
# disclosure or delivery of the Materials, either expressly, by
# implication, inducement, estoppel or otherwise.  Any license under such
# intellectual property rights must be express and approved by Intel in
# writing.

# This file should be always located and called in $(tbb_root)/examples

# Usage:
#   make [all] [clean] [release] [debug] [test]
#      executes specified targets for all examples.
#   make {example's dir}/{target}
#      calls specified example with specified target.
#      For instance: make task/tree_sum/all

tbb_root?=..
BUILDING_PHASE:=0
include ../build/common.inc

#check, if tbb_root is not absolute path (the filter keeps only /* paths)
ifeq ($(filter /% $(SLASH)%, $(subst :, ,$(tbb_root)) ),)
    # also changes related variables like work_dir
    override tbb_root := $(CWD)$(SLASH)..
    export TBB30_INSTALL_DIR := $(tbb_root)
endif

ifeq ($(tbb_os),windows)
    ifeq ($(UNIXMODE),1)
        EXAMPLE_MAKEFILE = Makefile
        EXAMPLES = $(wildcard */*/$(EXAMPLE_MAKEFILE))
        ifeq ($(compiler),gcc)
            override CXXFLAGS += -Wl,--enable-auto-import
        endif
        export CPATH := $(CPATH);$(tbb_root)/include
        export LIBRARY_PATH := $(LIBRARY_PATH);$(work_dir)_release;$(work_dir)_debug
        export RM = cmd /C del /Q /F
    else
        EXAMPLE_MAKEFILE = Makefile.windows
        EXAMPLES = $(wildcard */*/$(EXAMPLE_MAKEFILE))
        EXAMPLE_MAKEFILE := $(if $(EXAMPLES),Makefile.windows,Makefile)
        export INCLUDE := $(tbb_root)$(SLASH)include;$(INCLUDE)
        export LIB := $(work_dir)_release;$(work_dir)_debug;$(LIB)
    endif
    work_dir := $(subst /,$(SLASH),$(work_dir))
    export PATH := $(work_dir)_release;$(work_dir)_debug;$(PATH)
    export TBB_ARCH_PLATFORM = $(arch)\$(runtime)
    export TBB_TARGET_ARCH = $(arch)
else
    EXAMPLE_MAKEFILE = Makefile
    EXAMPLES := $(wildcard */*/$(EXAMPLE_MAKEFILE))
    # platform-specific settings
    ifeq ($(arch),ia64)
        override CXXFLAGS += $(PIC_KEY)
    endif
    ifeq ($(compiler),gcc)
        ifeq ($(arch),intel64)
            override CXXFLAGS += -m64
        endif
        ifeq ($(arch),ia32)
            override CXXFLAGS += -m32
        endif
        ifeq ($(arch),ppc64)
            override CXXFLAGS += -m64
        endif
        ifeq ($(arch),ppc32)
            override CXXFLAGS += -m32
        endif
        ifeq ($(arch),sparc)
            override CXXFLAGS += -mcpu=v9 -m64
        endif
    endif
    ifeq ($(compiler),suncc)
        override CXXFLAGS += -I$(tbb_root)$(SLASH)include -library=stlport4 -M$(tbb_root)/build/suncc.map.pause -erroff=unassigned,attrskipunsup,badargtype2w,badbinaryopw,wbadasg,wvarhidemem,wbadinit
        ifeq ($(arch),intel64)
            override CXXFLAGS += -m64
        endif
        ifeq ($(arch),ia32)
            override CXXFLAGS += -m32
        endif
        ifeq ($(arch),sparc)
            override CXXFLAGS += -m64
        endif
    endif
    ifeq ($(tbb_os),macos)
        # GUI for examples does not support 64-bit platforms
        ifeq ($(arch),intel64)
            export UI=con
        endif
        ifeq ($(arch),ppc64)
            export UI=con
        endif
        export DYLD_LIBRARY_PATH := $(DYLD_LIBRARY_PATH):$(work_dir)_release:$(work_dir)_debug
    else
        export LD_LIBRARY_PATH := $(LD_LIBRARY_PATH):$(work_dir)_release:$(work_dir)_debug
    endif
    export LIBS
    export LIBRARY_PATH := $(LIBRARY_PATH):$(work_dir)_release:$(work_dir)_debug
    export CPATH := $(CPATH):$(tbb_root)/include
endif

COMMON_TARGETS := all clean release debug test
# list of directories of examples
EXAMPLES_DIRS := $(foreach T,$(EXAMPLES),$(dir $(T)))
# targets to explicitly call example have format: {example's dir}/{example's target}
EXAMPLES_TARGETS := $(foreach T,$(COMMON_TARGETS),$(addsuffix $(T),$(EXAMPLES_DIRS)))

.PHONY: $(COMMON_TARGETS) $(EXAMPLES_TARGETS)

.DEFAULT: all

# execute standard targets for all examples
$(COMMON_TARGETS):: % : $(addsuffix %,$(EXAMPLES_DIRS))

# proxy rule for calling appropriate example
$(EXAMPLES_TARGETS)::
	-$(MAKE) SHELL=$(SHELL) -C $(@D)  -f $(EXAMPLE_MAKEFILE) $(notdir $@) CXX="$(CPLUS)" CXXFLAGS="$(CXXFLAGS)"

printenv:
ifeq ($(tbb_os),windows)
	@cmd /C set PATH
	@cmd /C set LIB
	@cmd /C set INCLUDE
else
	@env | grep PATH
endif

