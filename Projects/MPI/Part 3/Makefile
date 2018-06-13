###########################################################
#
# Simple Makefile for Advanced Operating Systems Project 1
# Basic MPI Communication
#
###########################################################
.SUFFIXES: .h .c .cpp .l .o

aosproj1_2: aosproj1_2.c
	 mpicc -std=c99 aosproj1_2.c -lm -o aosproj1_2

run:
	mpirun -np 8 aosproj1_2

clean:
	/bin/rm -f *.o *~ core aosproj1_2


