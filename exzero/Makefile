# Makefile for exzero task
#
# to compile exzero, type
#
#   make
#

COMPILE = gcc -g -c
LINK = gcc

# note: make builds the first target (exzero) by default:

exzero: exzero.o
	$(LINK) -o exzero exzero.o

run: exzero
	./exzero

debug: exzero
	gdb exzero

clean:
	rm -rf exzero exzero.o

exzero.o: exzero.c
	$(COMPILE) -o exzero.o exzero.c

submit:
	rm -rf *.o exzero
	zip -r exzero-submission.zip *
	mv exzero-submission.zip ../exam-submission/.
