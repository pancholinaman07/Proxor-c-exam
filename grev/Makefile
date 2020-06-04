# Makefile for grev task
#
# to compile grev, type
#
#   make
#

COMPILE = gcc -g -c
LINK = gcc

# note: make builds the first target (grev) by default:

grev: grev.o
	$(LINK) -o grev grev.o

run: grev
	./grev

debug: grev
	gdb grev

clean:
	rm -rf grev grev-test grev.o

grev.o: grev.c
	$(COMPILE) -o grev.o grev.c

submit:
	rm -rf *.o cmcmd
	zip -r ~/exam-submission/grev-submission.zip *
