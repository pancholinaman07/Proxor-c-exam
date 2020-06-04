# Makefile for gbitset task
#
# to compile gbitset, type
#
#   make
#

COMPILE = gcc -g -c
LINK = gcc

# note: make builds the first target (gbitset) by default:

gbitset: gbitset.o
	$(LINK) -o gbitset gbitset.o

run: gbitset
	./gbitset

debug: gbitset
	gdb gbitset

clean:
	rm -rf gbitset gbitset-test gbitset.o

gbitset.o: gbitset.c
	$(COMPILE) -o gbitset.o gbitset.c

submit:
	rm -rf *.o cmcmd
	zip -r ~/exam-submission/gbitset-submission.zip *
