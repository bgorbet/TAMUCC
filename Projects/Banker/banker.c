//-------------------------------------------------------------------------
//
// Annie Gorbet
// Operating Systems
// Programming Project #4: Implementation of Banker's Algorithm
// November 28, 2012
// Instructor: Dr. Ajay K. Katangur
//
//-------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10           
#define false 0
#define true 1
//---------------------------------global varables--------------------


char RESOURCE[MAX] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
int Max[MAX][MAX]={0};   // maximum resource requirements per process
int Avail[MAX]={0};      // currently available resources
int Alloc[MAX][MAX]={0}; // currently allocated resources
int Need[MAX][MAX]={0};  // resources currently needed per process
int Request[MAX]={0};    // the current requesting process vector
int m=0;                 // number of resource types
int n=0;                 // number of processes
int req_process=0;       // requesting process number

//------------------------------function prototypes--------------------


void getdata( char[] );
void showdata();
void compute_need();
void printlabels();
void printvector( int[] );
void changdata( int );
int chksafe();


//---------------------------------main--------------------------------



int main( int argc, char *argv[] )
{
  int i;

  if( argc < 2 )
  {
    printf("\nERROR: usage -> progname infile\n");
    exit(0);
  }

  // get the data from input file

  getdata( argv[1] );

  // echo n, m, Alloc, Max, Avail
  // (also, compute and show Need)

  showdata();

  // check if the system is in a safe state

  if(chksafe())
  {
    printf("\nTHE SYSTEM IS IN A SAFE STATE!\n");
  }
  else
  {
    printf("\nTHE SYSTEM IS NOT IN A SAFE STATE!\n");
    exit(0);
  }

  // echo request vector

  printf("\n");
  printf("The Request Vector is...");
  printf("\n   ");
  printlabels();
  printf("%d: ", req_process);
  printvector( Request );
     
  // if request is < need for the requested process, go to next step

  for(i=0;i<=m;i++)
  {
      if(Request[i]>Need[req_process][i])
      {
        // if not, print error and exit
        printf("\nERROR: process has exceeded its maximum claim\n");
        exit(0);
      }
  }

  // if request is < the available resources, go to next step

  for(i=0;i<=m;i++)
  {
    if(Request[i]>Avail[i])
    {
      printf("\nTHE REQUEST CANNOT BE GRANTED!\n");
      exit(0);
    }
  }

  // grant the request

  changdata(req_process);
  printf("\nTHE REQUEST CAN BE GRANTED!\n");
  printf("\n");

  // echo the new available vector

  printf("\nThe Avaliable Vector is...\n");
  printlabels();
  printvector(Avail);


  return(0);
}

//--------------------------------------------------------------------------

/* Get Data Function
	
  This function reads the data from the input file, line-by-line.

  Parameters: char *file --> the input file

  Return Value: none

  Local Variables: see comments below
*/


void getdata( char *file )
{
  FILE *fp;                // file pointer 
  char line[101];          // char string to hold each line
  char *token;             // char * to hold each token from each line
  int i, j;                // loop controls

  // open the file

  fp = fopen( file, "r" );

  if (fp == NULL) 
  {
    fprintf( stderr, "Can't open input file %s\n", file );
    exit(1);
  }

  // use fgets to get each line, then scan for the integers
	
  fgets( line, 100, fp );
  sscanf( line, "%d", &n );  // get n

  // skip blank lines

  fgets( line, 100, fp );

  fgets( line, 100, fp );
  sscanf( line, "%d", &m );  // get m

  fgets( line, 100, fp );

  if(!(n<=MAX && m<=MAX))
  {
    printf("ERROR: number of processes and/or resource types exceeds maximum");
    exit(0);
  }

  // lines with matrices and vectors need to be tokenized with this method

  for (i = 0; i < n; i++) 
  {
    // get a line from the first matrix

    fgets( line, 100, fp );

    // tokenize, and put each token into the Alloc matrix for that
    // particular row

    token = strtok( line, " " );
    j = 0;
    while( token != NULL )
    {
      sscanf( token, "%d", &Alloc[i][j] );
      j++;
      token = strtok( NULL, " " );
    }			
  }

  fgets( line, 100, fp );

  // repeat above for Max 

  for (i = 0; i < n; i++) 
  {
    fgets( line, 100, fp );
    token = strtok( line, " " );
    j = 0;
    while( token != NULL )
    {
      sscanf( token, "%d", &Max[i][j] );
      j++;
      token = strtok( NULL, " " );
    }			
  }

  fgets( line, 100, fp );

  // get the Available vector

  fgets( line, 100, fp );
  token = strtok( line, " " );
  j=0;
  while( token != NULL )
  {
    sscanf( token, "%d", &Avail[j] );
    j++;
    token = strtok( NULL, " " );
  }	

  fgets( line, 100, fp );

  fgets( line, 100, fp );
  token = strtok( line, " :" );
  req_process = atoi( token );    // the first token of the last line is the
  j = 0;                          // number of the requesting process
  token = strtok( NULL, " " );
  while( token != NULL )
  {
    sscanf( token, "%d", &Request[j] );  // the rest is the request vector
    j++;
    token = strtok( NULL, " " );
  }	

  fclose(fp);

}



//--------------------------------------------------------------------------

/* Show Data Function

  This Function echos what was read in from the file, as well as calls the
  compute_need function and displays the Need matrix.

  Parameters: none

  Return Value: none

  Local Variables: see comments below
*/



void showdata()
{
  int i, j;   // controls loops

  // echo n and m

  printf("There are %d processes in the system\n", n);
  printf("\nThere are %d resource types\n", m);

  // echo allocation matrix, with labels for resources

  printf("\nThe Allocation Matrix is...\n");
  printf("\n   ");
  printlabels();

  for( i = 0; i < n; i++ )
  {
    printf("\n%d: ", i);
    printvector( Alloc[i] );
  }

  // echo max matrix, with resource labels

  printf("\nThe Max Matrix is...\n");
  printf("\n   ");
  printlabels();

  for( i = 0; i < n; i++ )
  {
    printf("\n%d: ", i);
    printvector( Max[i] );
  }

  // compute and display need matrix

  compute_need();

  printf("\nThe Need Matrix is...\n");
  printf("\n   ");
  printlabels();

  for( i = 0; i < n; i++ )
  {
    printf("\n%d: ", i);
    printvector( Need[i] );
  }

  // echo available vector

  printf("\nThe Avaliable Vector is...\n");
  printlabels();
	printvector( Avail );
}



//--------------------------------------------------------------------------

/* Compute Need Function

  This function computes the need matrix.

  Parameters: none

  Return Value: none

  Local Variables: see comments below
*/


void compute_need()
{
  int i, j;   // controls loops

  // compute need for each index by subracting the allocation matrix
  // from the max matrix

  for( i = 0; i < n; i++ )
  {
    for( j = 0; j < m; j++ )
    {
      Need[i][j] = Max[i][j] - Alloc[i][j];
    }
  }
}



//---------------------------------------------------------------------------

/* Print Labels Function

  This function prints the resource type labels.

  Parameters: none

  Return Value: none

  Local Variables: see comments below
*/


void printlabels()
{
  int i;   // controls loop

  for( i = 0; i < m; i++ )
  {
    printf("%c ", RESOURCE[i]);
  }
  printf("\n");
	
}




//---------------------------------------------------------------------------

/* Print Vector Function

  This function displays a single vector.

  Parameters: int v[] --> the vector to be printed

  Return Value: none

  Local Variables: see comments below
*/


void printvector( int v[] )
{
  int i;   // controls loop

  for( i = 0; i < m; i++ )
  {
    printf("%d ", v[i]);
  }
  printf("\n");
}



//---------------------------------------------------------------------------

/* Change Data Function

  This function changes the available vector, allocation matrix, and
  need matrix after a request has been granted.

  Parameters: int k --> the number of the requesting process

  Return Value: none

  Local Variables: see comments below
*/


void changdata(int k)
{
  int j;   // controls loop

  for (j=0;j<n;j++)
  {
    Avail[j]=Avail[j]-Request[j];		
    Alloc[k][j]=Alloc[k][j]+Request[j];
    Need[k][j]=Need[k][j]-Request[j];
  }
}




//--------------------------------------------------------------------------

/* Check Safe Function

  This function checks if the currect state is safe given the current
  resources needed for each process and what is available.

  Parameters: none

  Return Value: none

  Local Variables: see comments below
*/


int chksafe()
{
  int work[m],finish[n];  // two vectors of size n and m
  int i,j,k,flag,count=0; // loop control

  // initialize finish to false for every process

  for(i=0;i<n;i++)finish[i]=false;

  // initialize work to be the same as the available vector

  for(i=0;i<m;i++)
  {
    work[i]=Avail[i];
  }

  // first, find an i such that finish[i] is false and
  // all needed resources for process i are less than what
  // is currently available, according to work

  while( count != n )
  {
    count = 0;
    for(i=0;i<n;i++)
    {
      flag = true;
      k = 0;
      for(j=0;j<m;j++)
      {
        if(Need[i][j]>work[j])
        {
        k++;
        }
      }

      // for each such i found, add its allocated resources to 
      // work and flag it as finished

      if (finish[i]==false&&k==0)
      {
        for(j=0;j<m;j++)
        {
          work[j]=work[j]+Alloc[i][j];
        }
        finish[i] = true;
        flag = false;
      }
      if(flag)
      {
        count++;
      }
    }
  }  // once all processes are either finished or cannot be "granted"
     // resources, the loop will end
	
  // when the loop ends, if all processes weren't finished then the
  // system is not in a safe state, because some processes cannot receive
  // resources given what is available

  for(i=0;i<n;i++)
  {
    if(finish[i]==false)
    {
      return false;
    }
  }

  return true;
		
}






