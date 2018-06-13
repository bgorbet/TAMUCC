Contents:

buffer.h: Circular Buffer Class Header File
buffer.cpp: Circular Buffer Class Implementation File
osproj3.cpp: Producer/Consumer Simulation Program
Makefile

Project Details:

OBJECTIVE

The purpose of this programming project is to explore process synchronization.  
This will be accomplished by writing a simulation to the Producer / Consumer 
problem.  

PROGRAM

The buffer used between producer and consumer processes consists of a fixed-size 
array of type buffer_item.  The queue of buffer_item objects is manipulated 
using a circular array.  The buffer is manipulated with two functions, 
buffer_insert_item() and buffer_remove_item(), which are called by the producer 
and consumer threads, respectively. The buffer_insert_item() and buffer_remove_item() 
functions synchronize the producer and consumer using the algorithms similar to 
those in in Figure 6.10 and 6.11.  The buffer also includes an initialization function 
that initializes the mutual exclusion object "mutex" along with the "empty" and "full" 
semaphores.  The buffer also includes various functions for retrieving information 
about the state of the buffer.

The producer thread alternates between sleeping for a random period of time and 
generating and inserting (trying to) an integer into the buffer.  Random numbers are
generated using the rand_r() function.  The sleep function used is a "thread safe" 
sleep function.  

The consumer thread alternates between sleeping for a random period of time 
(thread safe) and (trying to) removing a number out of the buffer.  The number removed
is then determined to be prime (or not).  

The main function creates the separate producer and consumer threads.  The buffer is initialized 
by its constructor upon creation. Once main() has created the producer and consumer threads, 
it sleeps (thread safe) for duration of the simulation.  Upon awakening, the main thread 
signals other threads to quit by setting a simulation flag which is a global variable.  
The main thread joins with the other threads and then displays the simulation statistics. 
The main() function is passed five parameters on the command line:

The length of time the main thread is to sleep before terminating (simulation length in seconds)
The maximum length of time the producer and consumer threads will sleep prior to producing or consuming a buffer_item
The number of producer threads
The number of consumer threads
A "yes" or "no" to output the individual buffer snapshots for each item produced and consumed

N.B.  There is one probem with the program.  It appears that every once in a while the 
simulation starts producing consumer threads before all of the producer threads get created,
(and vice versa) even though these threads are created separately in different loops.
This leads to a deadlock situation.  However, this problem does not happen often. 
I tried to fix this and make the program perfect, but after many hours of working on this one
problem, I ran out of time.
