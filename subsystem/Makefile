# director config
ROOT	:=	$(shell pwd)
SRC		:=	$(ROOT)
#include $(SRC)/Make.defines.$(PLATFORM)
#include $(SRC)/Make.readme


BIN=$(ROOT)/bin/
CPUFREQ_SRC=$(SRC)/cpufrequtils
CPUUSAGE_SRC=$(SRC)/cpuusageutils
FPGA_SRC=$(SRC)/fpgautils

DIRS=$(CPUFREQ_SRC) $(CPUUSAGE_SRC) $(FPGA_SRC)



SUBDIRS=$(DIRS)

.PHONY:all $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
		$(MAKE) -C $@

#all	:
#	for i in $(DIRS); do \
#		(cd $$i && echo "making $$i" && $(MAKE) ) || exit 1; \
#	done

clean:
	for i in $(DIRS); do \
		(cd $$i && echo "cleaning $$i" && $(MAKE) clean) || exit 1; \
	done

install :
	for i in $(DIRS); do \
		(cd $$i && echo "install $$i" && $(MAKE) install) || exit 1; \
	done

github:
	make clean
	cd $(ROOT)/..
	git add -A
	git commit -m $(GITHUB_COMMIT)
	git push origin master
