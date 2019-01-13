beargit: main.c beargit.c beargit.h util.h
	gcc -std=c99 main.c beargit.c -o beargit

clean:
	rm -rf beargit autotest test

check::
ifndef INSTMANPATH
	$(error You need to run 'make check' on an instructional machine, such as hive*.cs.berkeley.edu)
endif
	python2.7 tester.pyc beargit.c
