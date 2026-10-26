EXEFILE=testnetsvr

ROOT=../../../..
COMMON_PATH=$(ROOT)/../Common
SRC=$(ROOT)/test/net
INC=-I$(ROOT)/inc/baselib -I$(ROOT)/inc/net -I$(COMMON_PATH)/message
LIB_PATH=$(ROOT)/lib
SDU_PATH=$(ROOT)/3rd/sdu/include
CC = g++ -ggdb3
VPATH = $(SRC):$(INC)

CPPFLAGS += -I../ $(INC) -I$(ROOT)/inc -I$(SRC) -I$(SDU_PATH) \
	-I$(COMMON_PATH)/define/ -I$(ROOT)/3rd/mysql/include/ \
	-I$(SDU_PATH)/components/server -I$(ROOT)/3rd/lua/include \
	-I$(ROOT)/3rd/toluapp/include \
	-I$(SDU_PATH)/sdu -Wall -g

CPP_FILES := $(wildcard ../*.cpp)
OBJ_FILES := $(addprefix ../,$(notdir $(CPP_FILES:.cpp=.o)))


LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
LDFLAGS = -L./ -L$(ROOT)/3rd/sdu/lib/linux64 -L$(TINYXML_PATH)/lib/linux64/debug \
					-L$(ROOT)/lib -L$(ROOT)/3rd/lua/lib/linux64 \
					-L$(ROOT)/3rd/toluapp/lib/linux64 \
					-L$(ROOT)/3rd/recast/lib \
					-lsdframework -lsdpipe -lsdnet -lsdlogger \
					-lsdconsole -lbaselib -lsdu -ldl -lz -lpthread -lrt -lc
else
LDFLAGS = -L./ -L$(ROOT)/3rd/sdu/lib/linux32 -L$(TINYXML_PATH)/lib/linux32/debug \
					-L$(ROOT)/lib -L$(ROOT)/3rd/lua/lib/linux32 \
					-L$(ROOT)/3rd/toluapp/lib/linux32 \
					-L$(ROOT)/3rd/recast/lib \
					-lsdframework -lsdpipe -lsdnet -lsdlogger \
					-lsdconsole -lbaselib -lsdu -ldl -lz -lpthread -lrt 
endif

$(EXEFILE): $(OBJ_FILES) 
	$(CC) -o $@ $^ -L$(LIB_PATH) -lbaselib -lnetlib $(LDFLAGS)

../%.o : ../%cpp stdafx.h
	$(CC) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -rf $(EXEFILE) $(OBJ_FILES) *~
