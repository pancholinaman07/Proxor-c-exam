# Makefile for exclip task
#
# to compile exclip, type
#
#   make
#

COMPILE = gcc -g -c
LINK = gcc

# note: make builds the first target (exclip) by default:

exclip: exclip.o
	$(LINK) -o exclip exclip.o

run: exclip
	./exclip

debug: exclip
	gdb exclip

clean:
	rm -rf exclip exclip-grade exclip.o

exclip.o: exclip.c
	$(COMPILE) -o exclip.o exclip.c

submit:
	rm -rf *.o exclip
	zip -r exclip-submission.zip *
	mv exclip-submission.zip ../exam-submission/.
