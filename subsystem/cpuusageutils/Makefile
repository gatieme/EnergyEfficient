ROOT=.
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)


INC = -I./


target=	main_cpuusage main_cpuusage_sdk


all:$(target)



main_cpuusage : mainusage.o libcpuusage.a
	$(CC) $^ -o $@ $(CFLAGS)

main_cpuusage_sdk : mainusage.o libcpuusage.so
	$(CC) $^ -o $@ -L./ -lcpuusage  $(CFLAGS)



libcpuusage.a : proc.o cpuusage.o
	ar crv $@ $^


libcpuusage.so : proc.o cpuusage.o
	$(CC) $(SHAREDLIB_LINK_OPTIONS) $(FPIC) $(LDFLAGS) $^ -o $@

%.o : %.cpp
	$(CXX) $(FPIC) $(CXXFLAGS) -c $^ -o $@ $(INC)


%.o : %.c
	$(CC) $(FPIC) $(CFLAGS) -c $^ -o $@ $(INC)


clean :
	rm -rf *.o
	rm -rf libcpuusage.so libcpuusage.a
	rm -rf $(target)
