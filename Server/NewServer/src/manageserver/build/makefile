ROOT=../../..

TARGET=manageserver
TARGET_DIR=$(ROOT)/bin/linux

SUBDIRS := \
	arenateam \
	client \
	data \
	db \
	gs \
	guild \
	mail \
	master \
	onlinerole \
	queuematch \
	scene \
	team \
	timer
	
TOLUA_TARGET := script
TOLUA_DIR := ../script

EXTRA_LINK += ../script/ms_script_func.o
#TODO: move gameworld/data/ to baselib
EXTRA_LINK += ../../gameworld/build/data/item_data.o
##OR
##LBITS := $(shell getconf LONG_BIT)
#ifndef LBITS
#	LBITS:=$(shell getconf LONG_BIT)
#endif
#EXTRA_LINK := $(ROOT)/bin/lib/linux$(LBITS)/gameworld.a

include ../../server.mk

