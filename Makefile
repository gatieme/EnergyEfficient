all:github



GITHUB_COMMIT := $(COMMIT)


ifeq ($(COMMIT), )
	GITHUB_COMMIT="application, 修复了两处重大bug--[UpdateAllCpusScalingCurFrequency和UpdateAllCpusUsage返回值为list, 但是并为显示return, 导致外部使用时地址违规, 程序异常终止..."
endif


.PHONY	:	github
github :
	git pull
	git add -A
	git commit -m $(GITHUB_COMMIT)
	git push origin master


