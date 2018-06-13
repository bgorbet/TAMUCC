###########################################################
#
# Simple Makefile for Advanced Operating Systems Project 1
# Basic MPI Communication
#
###########################################################
.SUFFIXES: .h .c .cpp .l .o

aosproj1_1: aosproj1_1.c
	mpicc aosproj1_1.c -o aosproj1_1

run:
	mpirun -np 2 aosproj1_1

clean:
	/bin/rm -f *.o *~ core aosproj1_1


