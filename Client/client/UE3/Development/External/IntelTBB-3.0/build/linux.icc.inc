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

COMPILE_ONLY = -c -MMD
PREPROC_ONLY = -E -x c++
INCLUDE_KEY = -I
DEFINE_KEY = -D
OUTPUT_KEY = -o #
OUTPUTOBJ_KEY = -o #
PIC_KEY = -fPIC
WARNING_AS_ERROR_KEY = -Werror
WARNING_KEY = -w1
DYLIB_KEY = -shared
EXPORT_KEY = -Wl,--version-script,
NOINTRINSIC_KEY = -fno-builtin
LIBDL = -ldl

TBB_NOSTRICT = 1

CPLUS = icpc
CONLY = icc

ifeq (release,$(cfg))
CPLUS_FLAGS = -O2 -strict-ansi -DUSE_PTHREAD
else
CPLUS_FLAGS = -O0 -g -strict-ansi -DUSE_PTHREAD -DTBB_USE_DEBUG
endif

ifneq (,$(codecov))
    CPLUS_FLAGS += -prof-genx
else
    CPLUS_FLAGS += -DDO_ITT_NOTIFY
endif

OPENMP_FLAG = -openmp
LIB_LINK_FLAGS = -shared -i-static -Wl,-soname=$(BUILDING_LIBRARY)
LIBS = -lpthread -lrt
C_FLAGS = $(CPLUS_FLAGS)

TBB_ASM.OBJ=
MALLOC_ASM.OBJ=

ifeq (ia32,$(arch))
    CPLUS_FLAGS += -falign-stack=maintain-16-byte
endif

ifeq (ia64,$(arch))
# Position-independent code (PIC) is a must on IA-64, even for regular (not shared) executables
    CPLUS_FLAGS += $(PIC_KEY)
endif

ifneq (00,$(lambdas)$(cpp0x))
	CPLUS_FLAGS += -std=c++0x -D_TBB_CPP0X
endif

#------------------------------------------------------------------------------
# Setting assembler data.
#------------------------------------------------------------------------------
ASM = as
ifeq (intel64,$(arch))
    ASM_FLAGS += --64
endif
ifeq (ia32,$(arch))
    ASM_FLAGS += --32
endif
ifeq ($(cfg),debug)
    ASM_FLAGS += -g
endif

ASSEMBLY_SOURCE=$(arch)-gas
ifeq (ia64,$(arch))
    ASM_FLAGS += -xexplicit
    TBB_ASM.OBJ += atomic_support.o lock_byte.o log2.o pause.o ia64_misc.o
    MALLOC_ASM.OBJ += atomic_support.o lock_byte.o pause.o
endif
#------------------------------------------------------------------------------
# End of setting assembler data.
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# Setting tbbmalloc data.
#------------------------------------------------------------------------------

M_CPLUS_FLAGS = $(CPLUS_FLAGS) -fno-rtti -fno-exceptions

#------------------------------------------------------------------------------
# End of setting tbbmalloc data.
#------------------------------------------------------------------------------

