#TOLUAPP_PATH=
#
#TOLUA_TARGET :=
#TOLUA_DIR := 
#TOLUA_PKG := 
#TOLUA_CPP := 
#TOLUA_OBJ := 

ifndef LBITS
	LBITS := $(shell getconf LONG_BIT)
endif

#TOLUAPP=../../3rd/toluapp/bin/linux64/tolua++
TOLUAPP=../../3rd/toluapp/bin/linux$(LBITS)/toluappc

### make script
$(TOLUA_TARGET): %: fake_%
fake_$(TOLUA_TARGET):
	make $(filter %.cpp,$(TOLUA_CPP))
	make $(TOLUA_OBJ)

### make ../script/tolua_xxx.cpp
$(filter %, $(TOLUA_CPP)): $(TOLUA_DIR)/tolua_%.cpp: $(TOLUA_DIR)/%.pkg
	cd $(SRC) && $(TOLUAPP) -D -n $* -o script/tolua_$*.cpp -H script/tolua_$*.h script/$*.pkg;	

### make script/tolua_xxx.cpp
$(subst ../, ,$(TOLUA_CPP)): $(TOLUA_CPP)

### make script/tolua_xxx.o
$(filter %.o,$(TOLUA_OBJ)): %.o: ../%.cpp
	mkdir -p $(dir $@);
	$(CC) $(CPPFLAGS) -c -o $@ $<

clean_tolua:
	rm -f $(TOLUA_CPP) $(TOLUA_CPP:.cpp=.h) $(patsubst %.cpp,%.o,$(subst ../, ,$(TOLUA_CPP)) )
