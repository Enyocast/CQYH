TARGET:=toluappc
ifndef LBITS
	LBITS:=$(shell getconf LONG_BIT)
endif

CC=gcc -m$(LBITS) -ggdb3 
CFLAGS:=-I../lib -I../../include -I../../../lua/include 
LDFLAGS:=../../lib/linux$(LBITS)/libtolua++.a ../../../lua/lib/linux$(LBITS)/liblua.a -lc -lm -lrt -ldl

#C_FILE:=$(filter-out toluabind_default.c, $(wildcard *.c) )
C_FILE:=tolua.c toluabind_new.c
C_OBJ:=$(C_FILE:.c=.o)

../../bin/linux$(LBITS)/$(TARGET):$(C_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f ../../bin/linux$(LBITS)/$(TARGET) $(C_OBJ)
