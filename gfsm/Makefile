# Makefile for gfsm task
#
# to compile gfsm, type
#
#   make
#

COMPILE = gcc -g -c
LINK = gcc

# note: make builds the first target (gfsm) by default:

gfsm: gfsm.o
	$(LINK) -o gfsm gfsm.o

run: gfsm
	./gfsm

debug: gfsm
	gdb gfsm

clean:
	rm -rf gfsm gfsm-test gfsm.o

gfsm.o: gfsm.c
	$(COMPILE) -o gfsm.o gfsm.c

submit:
	rm -rf *.o cmcmd
	zip -r ~/exam-submission/gfsm-submission.zip *
