
all:github



GITHUB_COMMIT := $(COMMIT)


ifeq ($(COMMIT), )
	GITHUB_COMMIT="增加了application/blcore/BLCoreMonitor, 大小核调度平台监视器..."
endif


.PHONY	:	github
github :
	git add -A
	git commit -m $(GITHUB_COMMIT)
	git push origin master


