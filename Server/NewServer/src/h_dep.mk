
%.d:%.cpp
	set -e; \
	g++ -MM $< $(CPPFLAGS) > $@; \
	sed -i 's,\($*\)\.o[ :]*,\1.o $@ : ,g' $@; 

%.d:%.c
	set -e; \
	gcc -MM $< $(CFLAGS) > $@; \
	sed -i 's,\($*\)\.o[ :]*,\1.o $@ : ,g' $@; 
