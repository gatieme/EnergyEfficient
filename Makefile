all:github



GITHUB_COMMIT := $(COMMIT)


ifeq ($(COMMIT), )
	GITHUB_COMMIT="为subsystem增加了Makefile..."
endif


.PHONY	:	github
github :
	git pull
	git add -A
	git commit -m $(GITHUB_COMMIT)
	git push origin master


