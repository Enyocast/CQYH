ROOT=../../..

TARGET=datalogserver
TARGET_DIR=$(ROOT)/bin/linux

#LBITS := $(shell getconf LONG_BIT)
ifndef LBITS
	LBITS:=$(shell getconf LONG_BIT)
endif
EXTRA_LINK := $(ROOT)/bin/lib/linux$(LBITS)/gameworld.a

include ../../server.mk

