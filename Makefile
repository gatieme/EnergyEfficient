
all:github



GITHUB_COMMIT := $(COMMIT)


ifeq ($(COMMIT), )
	GITHUB_COMMIT="application/blcore/BLCoreMonitor, 完善了CpuFreqInfo和CpuFreqUtils接口..."
endif


.PHONY	:	github
github :
	git add -A
	git commit -m $(GITHUB_COMMIT)
	git push origin master


