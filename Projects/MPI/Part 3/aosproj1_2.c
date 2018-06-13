/******************************************************************************
*
* Betty (Annie) Gorbet
* Advanced Operating Systems
* Programming Project #1: Basic MPI Communication
* Part 2: Rock, Paper, Scissors Tournament
* Thursday, February 21, 2013
* Instructor: Dr. Ajay K. Katangur
*
******************************************************************************/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int play_rps( int rank, int opp );
void referee (int* opp, int size, int i, int winner );
int compare_function(const void *a,const void *b);

/******************************************************************************
*
* Main 
* 
* Contains the main loop that controls the tournament.
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
* r           int         The total number of rounds
* i           int         Loop iteration variable (and current round)
* opp         int         The current process opponent for the round
* winner      int         Flag to keep track if process is still in the
*                         tournament
*
******************************************************************************/
int main(int argc, char *argv[]) 
{
  /* local variables */
  int size, rank, r, i, opp, winner;
  MPI_Status status;
  
  MPI_Init( &argc, &argv );
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  
  /* Initialize r to log base 2 of the # of processes */
  r = log2( size );
  
  /* Initialize all processes as winners */
  winner = 1;
  
  /* main loop */
  i = 0;
  while( i < r )
  {
    
    /* Get the oppoenent.  For the first round, no communication is required.
        Even numbered processes compete with the process one rank higher and
        odd processes compete with the process one rank lower.  For subsequent
        rounds, the oppenent must be received in a message. */
    if( i == 0 )
    {
      if( rank%2 == 0 )
      {
        opp = rank+1;
      }
      else
      {
        opp = rank-1;
      }
    }
    else
    {
      if( rank != 0 )  /* Process 0 is referee that sends out opponents each */
      {                /* round, except to iteslf in order to avoid self-    */
                       /* self-communication                                 */
        MPI_Recv( &opp, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status );
      }
    }
    
    /* Play a round of Rock, Paper, Scissors. */
    if( winner )  /* this check is just for process 0, the only process that 
                     does not exit upon losing */
    {
      winner = play_rps( rank, opp );
    }
    
    /* If the process has won and it is not the last round, it should
        announce it has won and then send its rank to the referee, unless
        it is the referee. */
    if( winner && i < (r-1) )
    {
      printf("Round %d: Process %d wins over process %d\n", i, rank, opp );
      if( rank != 0 ) 
      {
        MPI_Send( &rank, 1, MPI_INT, 0, 2, MPI_COMM_WORLD );
      }
    }
    
    /* If it has lost, and it is not process
        0 (the referee process) then it should exit. */
    if( !winner && rank != 0 )
    {
      MPI_Finalize();
      exit(0);
    }
    
    /* If the process has won and it is the last round, it should announce
        its supreme victory and exit. */
    if( winner && i == (r-1) )
    {
      printf("Round %d: Process %d wins over process %d\n", i, rank, opp );
      printf("Process %d wins the rock, paper, scissors tournament\n", rank );
      MPI_Finalize();
      exit(0);    
    }
    
    /* If it is the last round and the process hasn't won or exited already,
        it should exit. (This should only be for process 0) */
    if( i == (r-1) )
    {
      MPI_Finalize();
      exit(0);
    }
    
    /* At the end of each round the referee must determine winners and
        inform them of their opponents for the next round. */
    if( rank == 0 )
    {
      referee( &opp, size, i, winner );
    }
    
    i++;
  }
  
  return 0;
}

/******************************************************************************
*
* Play_rps Function
* 
* This function plays a round of rock, paper, scissors for the process and its
* opponent, then the process returns 1 if it has won and 0 if its opponent has  
* won. For simplicity, a tie goes to the process with the higher rank.
*
* Return Value
* ------------
* int                     1/0 if it has won/lost
*
* Value Parameters
* ----------------
* rank        int         The process's id
* opp         int         The id of the process's opponent
*
* Reference Parameters
* --------------------
* none
*
* Local Variables
* ---------------
* choice      int         The process's choice of rock, paper, or scissors 
* opp_choic   int         The opponent's choice of rock, paper, or scissors
*
******************************************************************************/
int play_rps( int rank, int opp )
{
  /* Local variables. */
  MPI_Status status;
  int choice, opp_choice;
  
  /* Seed the psuedo-random number generator.  Each process will be seeded
      uniquely, since it is based on their rank. */
  srand (time(NULL) + rank );
  
  /* Generate a chosen move. (1=rock, 2=paper, 3=scissors) */
  choice = rand() % 3 + 1;
  
  /* Send choice to opponent and receive opponents choice. */
  MPI_Send( &choice, 1, MPI_INT, opp, 1, MPI_COMM_WORLD );
  MPI_Recv( &opp_choice, 1, MPI_INT, opp, 1, MPI_COMM_WORLD, &status );
  
  /* Any of the following conditions result in a win. */
  if( choice == 1 && opp_choice == 3 )
  {
    return 1;
  }

  if( choice == 2 && opp_choice == 1 )
  {
    return 1;
  }
  
  if( choice == 3 && opp_choice == 2 )
  {
    return 1;
  }
  
  if( choice == opp_choice && rank > opp )
  {
    return 1;
  }
  
  return 0;
}
 
 /******************************************************************************
*
* Referee Function
* 
* This function enables process 0 to act as referee each round. Each round it
* receives the winners and creates an array of winners which it sorts (in case
* the winnners were received out of order) and uses to send each process its 
* opponent, based on its location in the array.  Caution is taken to ensure 
* that process 0 does not communicate with itself.
*
* Return Value
* ------------
* void
*
* Value Parameters
* ----------------
* size        int         The number of processes
* i           int         The current round number
* winner      int         Winner flag for process 0
*
* Reference Parameters
* --------------------
* opp         int*        The opponent for process 0
*
* Local Variables
* ---------------
* ii          int         Loop iteration variable
* n           int         Number of winners for the round
* array       int*        Array of winners (to hold ids of winners for the 
*                         round )
*
******************************************************************************/ 
void referee ( int* opp, int size, int i, int winner )
{
  /* Local variables. */
  MPI_Status status;
  int ii, n;
  int* array;
  
  /*Initialize n to the calculated number of winners for the current round. */
  n = size / ( exp2( i+1 ) );
  
  /* Allocate space to the array according to how many winners there are. */
  array = (int*)malloc(n*sizeof(int));
   
  /* If process 0 was a winner, it should insert itself in the array to avoid 
      self-communication, then receive the rest of the winners.  Otherwise, it 
      should receive all of the winners. */
  if( winner )
  {
    array[0] = 0; 
    ii=1;             
    while( ii < n )
    {
      MPI_Recv( &array[ii], 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, 
               &status );
      ii++;
    }
  }
  else 
  {
    ii = 0;
    while( ii < n )
    {
      MPI_Recv( &array[ii], 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, 
               &status );
      ii++;
    }
  }

  /* In case messages are received out of order, sort the array. */
  qsort( array, n, sizeof(int), compare_function );
  
  /* Send each process its opponent.  Processes whose index is even will
      compete with the process one index higher.  Process whose index is
      odd will compete with the process one index lower. */
  ii = 0;
  while( ii < n )
  {
    if( ii%2 == 0 )
    {
      MPI_Send( &array[ii], 1, MPI_INT, array[ii+1], 0, MPI_COMM_WORLD );
    }
    else
    {
      if( array[ii-1] != 0 ) /* Avoid sending to self */
      {
        MPI_Send( &array[ii], 1, MPI_INT, array[ii-1], 0, MPI_COMM_WORLD );
      }
      else
      {
        *opp = array[ii]; /* Process 0 assigns its own opponent */
      }
    }
    ii++;
  }
  
  free( array );
}

/******************************************************************************
*
* Compare_function Function
* 
* This function is required to impement the qsort standard library function.
* It tells qsort how to sort integers.
*
* Return Value
* ------------
* int                     -#/0/+# if a<b/a=b/a>b
*
* Value Parameters
* ----------------
* none
*
* Reference Parameters
* --------------------
* a           void*       First object to be compared
* b           void*       Second object to be compared
*
* Local Variables
* ---------------
* x           int*        a cast as int pointer
* y           int*        b cast as int pointer
*
******************************************************************************/      
int compare_function(const void *a,const void *b) 
{
  int *x = (int *) a;
  int *y = (int *) b;
  return *x - *y;
}
