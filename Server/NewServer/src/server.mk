### var below be set in sub makefile
#ROOT :=
#TARGET := 
#TARGET_DIR := 

#LBITS := $(shell getconf LONG_BIT)
ifndef LBITS
	LBITS := $(shell getconf LONG_BIT)
endif

COMMON_PATH=$(ROOT)/../Common

SRC=$(ROOT)/src/$(TARGET)
INC=$(ROOT)/inc/$(TARGET)
VPATH = $(SRC):$(INC)

LIB=$(ROOT)/bin/lib/linux$(LBITS)

SDU_PATH=$(ROOT)/3rd/sdu
SDO_PATH=$(ROOT)/3rd/sdobase_2.0.2
TINYXML_PATH=$(ROOT)/3rd/tinyxml
TOLUAPP_PATH=$(ROOT)/3rd/toluapp
LUA_PATH=$(ROOT)/3rd/lua
MYSQL_PATH=$(ROOT)/3rd/mysql-5.1.65

CC_OPT = -m$(LBITS) -ggdb3
CC = g++ $(CC_OPT)

CPPFLAGS = $(CC_OPT) \
	-I.. \
	-I$(INC) \
	-I$(SRC)  \
	-I$(COMMON_PATH)/define \
	-I$(COMMON_PATH)/message \
	-I$(ROOT)/inc  \
	-I$(ROOT)/inc/net \
	-I$(ROOT)/inc/baselib \
	-I$(ROOT)/inc/gameworld \
	-I$(SDO_PATH)/include \
	-I$(TINYXML_PATH)/include \
	-I$(TOLUAPP_PATH)/include \
	-I$(LUA_PATH)/include \
	-I$(SDU_PATH)/include \
	-I$(SDU_PATH)/include/sdu \
	-I$(SDU_PATH)/include/components/server \
	-I$(SDU_PATH)/include/components/server/sdframework \
	-I$(MYSQL_PATH)/include \
	-Wall -g

LDFLAGS = $(CC_OPT) \
	-L.. \
	-L$(LIB) \
	$(LIB)/net.a \
	$(LIB)/baselib.a \
	$(SDU_PATH)/lib/linux$(LBITS)/libsdu.a \
	-L$(TOLUAPP_PATH)/lib/linux$(LBITS) \
	-L$(LUA_PATH)/lib/linux$(LBITS) \
	-L$(TINYXML_PATH)/lib/linux$(LBITS)/debug \
	-ltinyxml -llua -ltolua++ \
	-L$(SDO_PATH)/lib/linux$(LBITS) \
	-lSdoBase $(SDO_PATH)/lib/linux$(LBITS)/libcrypto.so.6 \
	-L$(MYSQL_PATH)/lib/linux$(LBITS) \
	$(MYSQL_PATH)/lib/linux$(LBITS)/libmysqlclient.a \
	-lpthread -lrt -ldl -lz 

################ make all ##################

all: $(TARGET_DIR)/$(TARGET)

$(TARGET_DIR)/$(TARGET): $(TARGET)
	mkdir -p $(TARGET_DIR)
	cp $< $@
	
################ make subdir ##################
#SUBDIRS :=
	
SUBDIR_CPP := $(foreach dir,$(SUBDIRS),$(wildcard $(SRC)/$(dir)/*.cpp))
SUBDIR_OBJ := $(subst $(SRC)/, ,$(SUBDIR_CPP:.cpp=.o))

include ../../subdir.mk

################ make script #################
#TOLUA_TARGET := script
#TOLUA_DIR := ../script

TOLUA_PKG := $(wildcard $(TOLUA_DIR)/*.pkg)
TOLUA_CPP := $(subst $(TOLUA_DIR)/,$(TOLUA_DIR)/tolua_,$(TOLUA_PKG:.pkg=.cpp))
TOLUA_OBJ := $(subst ../, ,$(TOLUA_CPP:.cpp=.o))

include ../../tolua.mk

################ make $(TARGET)#######################
# $(EXTRA_LINK) += 
CPP_FILES := $(wildcard ../*.cpp)
OBJ_FILES := $(notdir $(CPP_FILES:.cpp=.o))

ifeq ($(MAKECMDGOALS),)
	-include $(CPP_FILES:.cpp=.d )
	include ../../h_dep.mk
endif
ifneq ($(MAKECMDGOALS), $(filter $(MAKECMDGOALS),clean clean_all))
	-include $(CPP_FILES:.cpp=.d )
	include ../../h_dep.mk
endif

MSG_FILE := external_message_size

OBJ := $(MSG_FILE).o $(OBJ_FILES) $(EXTRA_LINK) $(SUBDIR_OBJ) $(TOLUA_OBJ)

$(TARGET) : $(OBJ) $(LIB)/net.a $(LIB)/baselib.a $(EXTRA_LINK) 
	$(CC) -o $@ $^ $(LDFLAGS)

$(MSG_FILE).o:$(COMMON_PATH)/message/$(MSG_FILE).cpp
	$(CC) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET_DIR)/${TARGET} 
	rm -f $(TARGET) 
	rm -f $(OBJ) *~
	rm -rf $(SUBDIRS)

clean_all: clean clean_tolua
	rm -f $(CPP_FILES:.cpp=.d )