###########################################################
#
# Simple Makefile for Operating Systems Project 1
# guish
#
###########################################################
.SUFFIXES: .h .c .cpp .l .o

guish: lex.yy.o guish.o
	g++ lex.yy.o guish.o -o guish -lfl

guish.o: guish.cpp
	g++ -c guish.cpp

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

lex.yy.c: guish.l
	flex guish.l

clean:
	/bin/rm -f *.o *~ core guish lex.yy.c



