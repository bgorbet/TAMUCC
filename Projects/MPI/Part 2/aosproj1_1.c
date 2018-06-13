/******************************************************************************
*
* Betty (Annie) Gorbet
* Advanced Operating Systems
* Programming Project #1: Basic MPI Communication
* Part 1: Ping Pong program
* Thursday, February 21, 2013
* Instructor: Dr. Ajay K. Katangur
*
******************************************************************************/
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

/******************************************************************************
*
* Main 
* 
* Contains the main loop that controls the program.  A message is send from 
* process 0 to process 1 and then immediately back again.  The message time is
* measured.  This is done for varying message sizes between 0 and 1 MB. The 
* average of 20 message times for each message size is printed to the screen,
* along with the size of the message.
*
* Return Value
* ------------
* int
*
* Value Parameters
* ----------------
* argc        int
*
* Reference Parameters
* --------------------
* argv        char[]
*
* Local Variables
* ---------------
* size        int         The number of processes
* rank        int         The pid of the current process
* i           int         Loop iteration variable 
* ii          int         Loop iteration variable 
* s           int         Number of integers being sent
* msg         int[]       Array of integers (the message)
* t0          double      The initial time
* t1          double      The time the message is received back
* ave         double      The average time for 20 messages
* total       double      The total time for 20 messages
*
******************************************************************************/
int main(int argc, char *argv[]) 
{
  
  // local variables
  int rank, size, ii, i, s;
  int msg[250];
  double t0, t1, ave, total;  
  MPI_Status status;
  
  MPI_Init( &argc, &argv );
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  
  /* Main loop (varries the message size) */
  for( s=1; s<250; s+=5 )
  {
    /* Initialize average to 0 for each message size */
    ave=0;
    
    /* Fill the message with integers */
    for( i=0; i<s; ++i ) { msg[i] = i;}
      
    /* Inner loop (calculates average time of 20 messages for each size) */
    for( ii=0; ii<20; ++ii )
    {
      /* Process 0 records the time, sends the message, records the time again,
          divides it by 2 to get the time one-way, then adds it to the total */
      if(rank==0)
      {
      
        t0 = MPI_Wtime();
  
        MPI_Send(msg, s, MPI_INT, 1, 1, MPI_COMM_WORLD);
        MPI_Recv(msg, s, MPI_INT, 1, 1, MPI_COMM_WORLD, &status);
    
        t1 = MPI_Wtime();
      
        total+=(t1-t0)/2;
    
      }
      /* Process 1 receives the messsage, then bounces it back */
      else
      {
    
        MPI_Recv(msg, s, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        MPI_Send(msg, s, MPI_INT, 0, 1, MPI_COMM_WORLD);
  
      }
    }
    
    /* Process 0 finds the average, then prints it out along with the size */
    if( rank==0)
    {
      
      ave=total/20;
      printf( "\n%d\t%.8f", sizeof(s)*s, ave );
      
    }
    
  }
  
  MPI_Finalize();
  return 0;
}
