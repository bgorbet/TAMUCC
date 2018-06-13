Contents:

README.txt
Makefile
aosproj4.cpp  source file
aosproj4.txt  sample test file

OBJECTIVE

The purpose of this programming assignment is to implement Chandy-Misra-Haas's edge chasing algorithm for distributed deadlock detection. 

DESCRIPTION
INPUT TO THE PROGRAM

You will need to define a file format for the connectivity matrix or edge list (graph) indicating the network connectivity of the processes in the distributed system. This file will also have to specify which process will initiate the deadlock detection algorithm. The name of this file will be passed as a command line argument to your program.

SAMPLE INPUT FILE

1-2
2-3
3-4
4-5
4-6
5-7
6-9
7-8
8-1

3

PROGRAM OUTPUT

At the beginning of the simulation, output the rank of processes which is initiating deadlock detection.

The program's output should be in this format:

"PROCESS I SENDS [A, B, C] TO PROCESS J."

where I and J are the MPI ranks of the source and destination process and A, B, and C are the contents of the probe message sent in the Chandy-Misra-Haas's algorithm. It should alwyas print a new probe message on a different line. Finally when the simulation is complete it should print either of these two messages.

If the system is deadlocked, it should print
"THE SYSTEM IS DEADLOCKED."

If the system is not deadlocked, it should print
"THE SYSTEM IS NOT DEADLOCKED."

My solution:

I separated the processes in each edge into vectors v1 and v2.  For each process,
the processes in v1 are dependent on it because they are waiting on resources that
it is holding, and the process itself is dependent of the processes in v2 because
they are holding resources that it is requesting.  I have the initial process first
check to see that v1 and v2 aren't empty (automatic no deadlock), then send out
and initial probe.  All processes receive probes from processes in v1 and propagate
them to processes in v2.  If the initial process receives its process back, the
simulation reports a deadlock.  A "ghost" probe is sent out be processes that have
nothing in v1, that way the simulation will not hang if there is no deadlock.
