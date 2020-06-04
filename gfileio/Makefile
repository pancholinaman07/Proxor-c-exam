# Makefile for gfileio task
#
# to compile gfileio, type
#
#   make
#

COMPILE = gcc -g -c
LINK = gcc

# note: make builds the first target (gfileio) by default:

gfileio: gfileio.o
	$(LINK) -o gfileio gfileio.o

run: gfileio
	./gfileio numbers.txt

debug: gfileio
	gdb gfileio

clean:
	rm -rf gfileio gfileio-test gfileio.o

gfileio.o: gfileio.c
	$(COMPILE) -o gfileio.o gfileio.c

submit:
	rm -rf *.o cmcmd
	zip -r ~/exam-submission/gfileio-submission.zip *
