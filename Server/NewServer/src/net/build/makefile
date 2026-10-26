ROOT:=../../..

ifndef LBITS
	LBITS:=$(shell getconf LONG_BIT)
endif

TARGET:=net.a
TARGET_DIR:=$(ROOT)/bin/lib/linux$(LBITS)

COMMON_PATH:=$(ROOT)/../Common

SRC=$(ROOT)/src/net
INC=$(ROOT)/inc/net
VPATH = $(SRC):$(INC)

SDU_PATH=$(ROOT)/3rd/sdu

CC_OPT = -m$(LBITS) -ggdb3
CC = g++ $(CC_OPT)

CPPFLAGS += $(CC_OPT) \
	-I.. \
	-I$(INC) \
	-I$(SRC) \
	-I$(COMMON_PATH)/define \
	-I$(COMMON_PATH)/message \
	-I$(SDU_PATH)/include \
	-I$(SDU_PATH)/include/sdu \
	-I$(SDU_PATH)/include/components/server \
	-I$(ROOT)/inc \
	-I$(ROOT)/inc/baselib \
	-I$(ROOT)/3rd/mysql/include/ \
	-I$(ROOT)/3rd/lua/include \
	-I$(ROOT)/3rd/toluapp/include \
	-Wall -g

################ make all ##################
all: $(TARGET_DIR)/$(TARGET)
$(TARGET_DIR)/$(TARGET): $(TARGET)
	mkdir -p $(TARGET_DIR)
	cp $< $@

################ make script #################
TOLUA_TARGET := script
TOLUA_DIR := ../script
TOLUA_PKG := $(wildcard $(TOLUA_DIR)/*.pkg)
TOLUA_CPP := $(subst $(TOLUA_DIR)/,$(TOLUA_DIR)/tolua_,$(TOLUA_PKG:.pkg=.cpp))
TOLUA_OBJ := $(subst ../, ,$(TOLUA_CPP:.cpp=.o))

include ../../tolua.mk

################ make $(TARGET) #################

CPP_FILES := $(wildcard ../*.cpp )
CPP_OBJ := $(notdir $(CPP_FILES:.cpp=.o))

ifeq ($(MAKECMDGOALS),)
	-include $(CPP_FILES:.cpp=.d )
	include ../../h_dep.mk
endif
ifneq ($(MAKECMDGOALS), $(filter $(MAKECMDGOALS),clean clean_all))
	-include $(CPP_FILES:.cpp=.d )
	include ../../h_dep.mk
endif

MSG_FILE=external_message_size
$(MSG_FILE).o:$(COMMON_PATH)/message/$(MSG_FILE).cpp
	$(CC) $(CPPFLAGS) -c -o $@ $<

OBJS := $(TOLUA_OBJ) $(CPP_OBJ) $(MSG_FILE).o

$(TARGET): $(OBJS) $(H_FILES)
	ar rcs $@ $^

$(C_OBJ): %.o: ../%.c
	gcc $(CC_OPT) -c -o $@ $<
	
clean:
	rm -f $(TARGET_DIR)/$(TARGET)
	rm -f $(TARGET) 
	rm -f $(OBJS) *~

clean_all: clean clean_tolua
	rm -f $(CPP_FILES:.cpp=.d )
