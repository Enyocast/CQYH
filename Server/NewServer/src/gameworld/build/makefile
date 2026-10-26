ROOT=../../..

#LBITS := $(shell getconf LONG_BIT)
ifndef LBITS
	LBITS:=$(shell getconf LONG_BIT)
endif

TARGET=gameworld.a
TARGET_DIR=$(ROOT)/bin/lib/linux$(LBITS)

COMMON_PATH=$(ROOT)/../Common
SRC=$(ROOT)/src/gameworld
INC=$(ROOT)/inc/gameworld

SDU_PATH=$(ROOT)/3rd/sdu
TINYXML_PATH=$(ROOT)/3rd/tinyxml
TOLUAPP_PATH=$(ROOT)/3rd/toluapp
LUA_PATH=$(ROOT)/3rd/lua

CC_OPT = -m$(LBITS) -ggdb3
CC=g++ $(CC_OPT)

VPATH = $(SRC):$(INC)

CPPFLAGS +=  $(CC_OPT) \
	-I.. \
	-I$(ROOT)/inc \
	-I$(INC)  -I$(SRC) \
	-I$(COMMON_PATH)/define \
	-I$(COMMON_PATH)/message \
	-I$(SDU_PATH) \
	-I$(SDU_PATH)/include \
	-I$(SDU_PATH)/include/sdu \
	-I$(SDU_PATH)/include/components/server \
	-I$(SDU_PATH)/include/components/server/sdframework \
	-I$(TINYXML_PATH)/include \
	-I$(TOLUAPP_PATH)/include \
	-I$(LUA_PATH)/include \
	-I$(ROOT)/inc/baselib \
	-I$(ROOT)/inc/net \
	-I$(ROOT)/inc/gameworld \
	-Wall -g

################ make all ##################
	
all: $(TARGET_DIR)/$(TARGET)

$(TARGET_DIR)/$(TARGET): $(TARGET)
	mkdir -p $(TARGET_DIR)
	cp $< $@

################ make script ##################

TOLUA_TARGET := script
TOLUA_DIR := ../script
TOLUA_PKG := $(wildcard $(TOLUA_DIR)/*.pkg)
TOLUA_CPP := $(subst $(TOLUA_DIR)/,$(TOLUA_DIR)/tolua_,$(TOLUA_PKG:.pkg=.cpp))
TOLUA_CPP := $(filter-out $(TOLUA_DIR)/tolua_robot_message_handler%,$(TOLUA_CPP))
TOLUA_OBJ := $(subst ../, ,$(TOLUA_CPP:.cpp=.o))

include ../../tolua.mk

################ make subdir ##################

# except subdir "script"
SUBDIRS := \
	achievement \
	affix \
	ai \
	attribute \
	bt \
	chat \
	data \
	friend \
	guild \
	item \
	master \
	message \
	object \
	quest \
	relation \
	scene \
	spell \
	spiritlevel \
	statistic \
	team \
	title 
	
SUBDIR_CPP := $(foreach dir,$(SUBDIRS),$(wildcard $(SRC)/$(dir)/*.cpp))
SUBDIR_OBJ := $(subst $(SRC)/, ,$(SUBDIR_CPP:.cpp=.o))

include ../../subdir.mk

################ make $(TARGET) ##################

ifeq ($(MAKECMDGOALS),)
	-include $(SUBDIR_CPP:.cpp=.d )
	include ../../h_dep.mk
endif
ifneq ($(MAKECMDGOALS), $(filter $(MAKECMDGOALS),clean clean_all))
	-include $(SUBDIR_CPP:.cpp=.d )
	include ../../h_dep.mk
endif

EXTRA_LINK := ../script/script_func.o
OBJS := $(EXTRA_LINK) $(TOLUA_OBJ) $(SUBDIR_OBJ)

$(TARGET): $(OBJS)
	ar rcs $@ $^

clean: clean_subdir 
	rm -f $(TARGET_DIR)/$(TARGET)
	rm -f $(TARGET) 
	rm -f $(OBJS) *~

clean_all: clean clean_tolua
	rm -f $(SUBDIR_CPP:.cpp=.d )
