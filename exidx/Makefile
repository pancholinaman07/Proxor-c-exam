# Makefile for exidx task
#
# to compile exidx, type
#
#   make
#

COMPILE = gcc -g -c
LINK = gcc

# note: make builds the first target (exidx) by default:

exidx: exidx.o
	$(LINK) -o exidx exidx.o

run: exidx
	./exidx

debug: exidx
	gdb exidx

clean:
	rm -rf exidx exidx.o

exidx.o: exidx.c
	$(COMPILE) -o exidx.o exidx.c

submit:
	rm -rf *.o exidx
	zip -r exidx-submission.zip *
	mv exidx-submission.zip ../exam-submission/.
