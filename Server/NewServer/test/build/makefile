TINYTEST=tinytest

ROOT=../..
SRC=$(ROOT)/test/src/
SDU_PATH=$(ROOT)/3rd/sdu/include
SDU_LIB_PATH=$(ROOT)/3rd/sdu/lib/linux32
TINYXML_PATH=$(ROOT)/3rd/tinyxml
CC = g++
VPATH = $(SRC):$(ROOT)/inc/common/server:$(ROOT)/inc/protocol/server:\
	:$(ROOT)/inc/common/client

CPPFLAGS += -I../ -I$(INC) -I$(ROOT)/inc -I$(SRC) -I$(SDU_PATH) \
	-I$(SDU_PATH)/sdu -I$(SDU_PATH)/components/server/sdframework \
	-I$(ROOT)/inc/baselib -I$(ROOT)/inc/gameworld \
	-I$(SDU_PATH)/components/server -I$(ROOT)/src/gameworld/data \
	-I$(TINYXML_PATH)/include -Wall -g

LDFLAGS = -L./ -L$(SDU_LIB_PATH) -L$(TINYXML_PATH)/lib/linux32/debug \
	-L$(ROOT)/lib -lsdframework -lsdpipe -lsdnet -lsdlogger \
	-lsdconsole -lgameworld -lbaselib -lsdu -ldl -lz -lpthread -lrt \
	-liconv -lcharset -ltinyxml -lncurses

OBJS = testmap.o

all: $(TINYTEST)

$(TINYTEST): $(OBJS)
	$(CC) -o $(TINYTEST) $(OBJS) $(LDFLAGS)

clean:
	rm -rf $(OBJS) $(TINYTEST) *~
