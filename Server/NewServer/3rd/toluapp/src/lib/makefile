TARGET:=libtolua++.a
ifndef LBITS
	LBITS:=$(shell getconf LONG_BIT)
endif

CC=gcc -m$(LBITS) -ggdb3

CFLAGS:=-I. -I../../include -I../../../lua/include
LDFLAGS:=../../../lua/lib/linux$(LBITS)

C_FILE:=$(wildcard *.c)
C_OBJ:=$(C_FILE:.c=.o)

../../lib/linux$(LBITS)/$(TARGET): $(C_OBJ)
	ar rcs $@ $^
clean:
	rm ../../lib/linux$(LBITS)/$(TARGET) $(C_OBJ)
