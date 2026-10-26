ROOT=../src
COMMON=../../Common
BIN_TARGET=$(ROOT)/gameserver/build\
	$(ROOT)/gateserver/build\
	$(ROOT)/dbserver/build\
	$(ROOT)/centerserver/build\
	$(ROOT)/loginserver/build

LIB_TARGET=$(ROOT)/baselib/build \
	$(ROOT)/gameworld/build

PROTO_TARGET=$(COMMON)/protocol/build

.PHONY: all clean $(BIN_TARGET) $(LIB_TARGET) $(PROTO_TARGET)

all: $(PROTO_TARGET) $(BIN_TARGET) $(LIB_TARGET)

clean: $(BIN_TARGET) $(LIB_TARGET) $(PROTO_TARGET)
	rm -rf ../lib/lib* *~

$(BIN_TARGET):
	$(MAKE) -C $@ $(MAKECMDGOALS) -j4 -s

$(LIB_TARGET):
	$(MAKE) -C $@ $(MAKECMDGOALS) -j4 -s

$(COMMON)/protocol/build:
	cd $(COMMON)/protocol;python $(COMMON)/protocol/gen.py
	$(MAKE) -C $@ $(MAKECMDGOALS) -j4 -s

$(ROOT)/gameworld/build: $(COMMON)/protocol/build $(ROOT)/baselib/build
$(ROOT)/gateserver/build: $(COMMON)/protocol/build $(ROOT)/baselib/build
$(ROOT)/centerserver/build: $(COMMON)/protocol/build $(ROOT)/baselib/build
$(ROOT)/loginserver/build: $(COMMON)/protocol/build $(ROOT)/baselib/build
$(ROOT)/dbserver/build: $(COMMON)/protocol/build $(ROOT)/baselib/build
$(ROOT)/gameserver/build: $(ROOT)/gameworld/build
