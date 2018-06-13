Contents:

banker.c: The source code
Makefile

This program reads the allocation, max, available, and request vectors 
from a file.  The name of the file is passed to the program as a command 
line argument.  The input file format is the following:

number of processes: n
number of resource types: m
An n x m allocation matrix
An n x m max matrix
A 1 x m available vector
A i : 1 x m request vector

This program outputs the following in a standardized format.

Echo the number of processes.
Echo the number of resource types.
Echo the allocation matrix.  
Echo the max matrix.  
Compute and print the need matrix.  
Echo the available vector.  
Compute if the system is in a safe state.
Echo the request vector.  
Compute if the request can be granted.
Compute the new available vector.
