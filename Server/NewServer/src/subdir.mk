#SUBDIRS := 
#SUBDIR_CPP :=
#SUBDIR_OBJ :=

#VPATH +=	$(subst :, ,$(SUBDIRS) )

### make subdir
$(SUBDIRS): %: fake_%
$(addprefix fake_,$(SUBDIRS) ):
	make $(filter $(subst fake_, ,$@)/%.o,$(SUBDIR_OBJ))

### make subdir/file.o
$(filter %.o,$(SUBDIR_OBJ)): %.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) -c -o $@ $<

clean_subdir:
	rm -rf $(SUBDIRS) $(TOLUA_TARGET)
