
##  guardserver
##  "dbserver",
##  "manageserver",
##  "gameserver",  gameworld

##  "loginserver",
##  "gateserver",
##  "datalogserver",
##  "balanceserver",

LBITS:=64
export LBITS

CC_OPT:=-m$(LBITS) -gdwarf-2 -ggdb3

root_dir := ..

SUBDIRS := \
	baselib \
	net \
	guardserver \
	gameworld \
	gameserver \
	manageserver \
	loginserver \
	gateserver \
	datalogserver \
	dbserver \
	balanceserver 

clean_dirs := $(addprefix _clean_,$(SUBDIRS) )
clean_all_dirs := $(addprefix _clean_all_,$(SUBDIRS) )
install_dirs := $(addprefix _install_,$(filter-out gameworld,$(filter-out net, $(filter-out baselib, $(SUBDIRS) ) ) ) )

.PHONY: all $(SUBDIRS) clean clean_all install

all: $(SUBDIRS)

clean: $(clean_dirs)

clean_all: $(clean_all_dirs)

install: all $(install_dirs)

$(SUBDIRS):
	$(MAKE) -C $@/build

$(clean_dirs):
	$(MAKE) -C $(patsubst _clean_%,%,$@)/build clean

$(clean_all_dirs):
	$(MAKE) -C $(patsubst _clean_all_%,%,$@)/build clean_all
	
$(install_dirs):
	mkdir -p $(root_dir)/bin/$(patsubst _install_%,%,$@)
	cp $(root_dir)/bin/linux/$(patsubst _install_%,%,$@) $(root_dir)/bin/$(patsubst _install_%,%,$@)/$(patsubst _install_%,%,$@)
