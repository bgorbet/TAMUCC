###########################################################
#
# Simple Makefile for Operating Systems Project 3
# osproj3
#
###########################################################
.SUFFIXES: .h .c .cpp .l .o

osproj3: osproj3.o buffer.o
	g++ osproj3.o buffer.o -g -lpthread -lrt -o osproj3

osproj3.o: osproj3.cpp
	g++ -c osproj3.cpp -g 

buffer.o: buffer.h buffer.cpp
	g++ -c buffer.h buffer.cpp -g 

clean:
	/bin/rm -f *.o *~ core osproj3 



