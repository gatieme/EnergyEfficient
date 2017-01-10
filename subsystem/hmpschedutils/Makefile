ROOT=.
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)


INC = -I./


target=	main_hmpsched main_hmpsched_sdk


all:$(target)



main_hmpsched : mainhmp.o libhmpsched.a
	$(CC) $^ -o $@ $(CFLAGS)

main_hmpsched_sdk : mainhmp.o libhmpsched.so
	$(CC) $^ -o $@ -L./ -lhmpsched  $(CFLAGS)



libhmpsched.a : proc.o hmpsched.o
	ar crv $@ $^


libhmpsched.so : proc.o hmpsched.o
	$(CC) $(SHAREDLIB_LINK_OPTIONS) $(FPIC) $(LDFLAGS) $^ -o $@

%.o : %.cpp
	$(CXX) $(FPIC) $(CXXFLAGS) -c $^ -o $@ $(INC)


%.o : %.c
	$(CC) $(FPIC) $(CFLAGS) -c $^ -o $@ $(INC)


clean :
	rm -rf *.o
	rm -rf libhmpsched.so libhmpsched.a
	rm -rf $(target)
