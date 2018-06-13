/******************************************************************************
*
* Betty (Annie) Gorbet
* Advanced Operating Systems
* Programming Project #4: Chandy-Misra-Haas's Edge Chasing Algorithm 
* Thursday, April 18, 2013
* Instructor: Dr. Ajay K. Katangur
*
******************************************************************************/
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include "mpi.h"
using namespace std;

bool inFileOpen( ifstream&, char* );
int getData( ifstream&, vector<int>&, vector<int>&, int );
bool init_proc( int, vector<int>, vector<int>, int[] );
bool propagate( int, vector<int>, vector<int>, int[], int[], int );

/******************************************************************************
*
* Main 
* 
* Controls the simulation of Chandy-Misra-Haas's edge chasing algorithm for 
* distributed deadlock detection.
*
* Return Value
* ------------
* int
*
* Value Parameters
* ----------------
* int         argc
*
* Reference Parameters
* --------------------
* argv        char**
*
* Local Variables
* ---------------
* size        int         The number of processes
* rank        int         The pid of the current process
* init        int         Rank of initializing process
* r_probe     int[]       Receive probe buffer
* s_probe     int[]       Send probe buffer
* v1          vector<int> List of processes waiting on the process
* v2          vector<int> List of processes the process is waiting on
* no_deadlock bool        Flag for deadlock
*
******************************************************************************/
int main( int argc, char* argv[] )
{
  /* local variables */
  ifstream inFile;
  int init, size, rank;
  int s_probe[3], r_probe[3];
  vector<int> v1, v2;
  bool no_deadlock = false;
  
  /* initialize local variables */
  v1.clear();
  v2.clear();
  
  for( int i=0; i<3; i++ )
  {
    r_probe[i] = 0;
    s_probe[i] = 0;
  }
  
  MPI_Init( &argc, &argv );
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  
  /* open and test input file stream */
  if( !inFileOpen( inFile, argv[1] ) )
    exit(0);
  
  /* read and parse data from file */
  init = getData( inFile, v1, v2, rank );
  
  inFile.close();
  
  /* the initializing process calls init_proc */
  if( rank == init )
  {
    no_deadlock = init_proc( rank, v1, v2, s_probe );
  }

  /* if initializing process has no dependant processes, 
    there is no deadlock */
  if( no_deadlock )
  {
    MPI_Finalize();
    exit(0);
  }
  
  /* propagate the probe */
  no_deadlock = propagate( rank, v1, v2, r_probe, s_probe, init );
  
  /* if the initializing process gets its probe back, report deadlock. */
  if( rank == init )
  {
    if( no_deadlock )
    {
      printf("THE SYSTEM IS NOT DEADLOCKED.\n");
    }
    else
    {
      printf("THE SYSTEM IS DEADLOCKED.\n");
    }
  }
  
  MPI_Finalize();
  
  return 0;
    
}
  


/******************************************************************************
*
* inFileOpen function
* 
* Tests to see if the inFile can be opened, and if so, opens it.
*
* Return Value
* ------------
* bool
*
* Value Parameters
* ----------------
* none
*
* Reference Parameters
* --------------------
* inFile        ifstream          Input file stream object
* filename      char*             The input file name          
*
* Local Variables
* ---------------
* none
*
******************************************************************************/
bool inFileOpen( ifstream &inFile, char* filename )
{
  inFile.open( filename, std::ifstream::in );
  if( !inFile )
  {
    printf("ERROR: file could not be opened.\n");
    return false;
  }
  return true;
}

/******************************************************************************
*
* getData function
* 
* Gets the data from the file and parses it, putting into v1 and v2 for each
* process.
*
* Return Value
* ------------
* int
*
* Value Parameters
* ----------------
* rank          int               pid of the process
*
* Reference Parameters
* --------------------
* inFile        ifstream          Input file stream object
* v1            vector<int>       List of processes waiting on the process
* v2            vector<int>       List of processes the process is waiting on
*
* Local Variables
* ---------------
* s             string            String object
* t1            char*             First token
* t2            char*             Second token
* s2            char*             Char array to hold string
* p1            int               First process in edge
* p2            int               Second process in edge
* init          int               Initializing process
*
******************************************************************************/
int getData( ifstream &inFile, vector<int> &v1, vector<int> &v2, int rank )
{
  /* local variables */
  string s;
  char *t1, *t2, *s2;
  int p1, p2, init;
  
  /* get each line, tokenize to get the two processes for the edge, put
    first process in v1 and second process in v2, last line is init. */
  while( getline( inFile, s ) )
  {
    if( s.size() > 1 )
    {
      s2 = strdup( s.c_str() );
      t1 = strtok( s2, "-");
      t2 = strtok( NULL, "-");
      
      p1 = atoi(t1);
      p2 = atoi(t2);
      
      if( rank == p1 )
      {
        v2.push_back( p2 ); // process requesting resources from p2
      } 
      else if( rank == p2 )
      {
        v1.push_back( p1 ); // p1 requesting resources from process
      }
    }
    else if( s.size() == 1 )
    {
      init = s[0] - '0';
      return init;
    }
  }
}

/******************************************************************************
*
* init_proc function
* 
* This function essentially initializes the simulation.  It first checks to 
* see that the initializing process is indeed blocked, then it sends out the
* initial probe.
*
* Return Value
* ------------
* bool
*
* Value Parameters
* ----------------
* rank
* v1
* v2
*
* Reference Parameters
* --------------------
* s_probe
*
* Local Variables
* ---------------
* none
*
*
******************************************************************************/
bool init_proc( int rank, vector<int> v1, vector<int> v2, int s_probe[] )
{ 
  printf("PROCESS %d INITIATES DEADLOCK DETECTION.\n", rank );
    
  /* if v1 or v2 is empty, cannot be part of a cycle */
  if( v1.size() == 0 || v2.size() == 0 )
  {
    printf("THE SYSTEM IS NOT DEADLOCKED.\n");
    return true;
  }

  /* send out initial probe to each process in v2*/
  for( int i=0; i<v2.size(); i++ )
  {
    s_probe[0] = rank;
    s_probe[1] = rank;
    s_probe[2] = v2.at(i);
      
    printf("PROCESS %d SENDS [%d, %d, %d] TO PROCESS %d.\n", 
            rank, s_probe[0], s_probe[1], s_probe[2], v2.at(i) );    
      
    MPI_Send( s_probe, 3, MPI_INT, v2.at(i), 0, MPI_COMM_WORLD );  
  }
}

/******************************************************************************
*
* propagate function
* 
* Propagates received probes to all processes in v2 (processes being waited 
* on). 
*
* Return Value
* ------------
* bool
*
* Value Parameters
* ----------------
* rank
* v1
* v2
* init
*
* Reference Parameters
* --------------------
* s_probe
* r_probe
*
* Local Variables
* ---------------
* non_deadlock
* status              MPI_Status          Status envelope
*
******************************************************************************/
bool propagate( int rank, vector<int> v1, vector<int> v2, int s_probe[], 
               int r_probe[], int init )
{
  /* local variables */
  bool no_deadlock = true; // assume no deadlock
  MPI_Status status;
  
  /* if the process has dependent processes, receive probe from them. */
  if( v1.size() != 0 ) 
  {
    for( int i=0; i<v1.size(); i++ )
    {
      MPI_Recv( r_probe, 3, MPI_INT, v1.at(i), 0, MPI_COMM_WORLD, 
               &status );
      
      /* if init receives its own probe, there is a deadlock */
      if( rank == init )
      {
        if( r_probe[0] == rank )
        {
          no_deadlock = false;
        }
      }
      
      
      /* if process depends on other processes, propagate probe to them*/
      if( v2.size() != 0 )
      {
        for( int j=0; j<v2.size(); j++ )
        {
          s_probe[0] = r_probe[0];
          s_probe[1] = rank;
          s_probe[2] = v2.at(j);
          
          /* if probe is not a ghost probe, report that it is being sent */
          if( s_probe[0] != -1 )
          {
            printf("PROCESS %d SENDS [%d, %d, %d] TO PROCESS %d.\n", 
                  rank, s_probe[0], s_probe[1], s_probe[2], v2.at(j) );
          }
            
          MPI_Send( s_probe, 3, MPI_INT, v2.at(j), 0, MPI_COMM_WORLD );
        }
      }
    }
  }
  else
  {
    /* if process has no dependent processes, it cannot be part of a cycle.
      Send out a "ghost" probe to processes that are depending on it so that
      the simulation will not hang. */
    if( v2.size() != 0)
    {
      s_probe[0] = -1;
      for( int k=0; k<v2.size(); k++)
      {
        MPI_Send( s_probe, 3, MPI_INT, v2.at(k), 0, MPI_COMM_WORLD );
      }
    }
  }
  
  return no_deadlock;
}
