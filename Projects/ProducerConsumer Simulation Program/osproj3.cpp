//********************************************************************
//
// Betty Gorbet
// Operating Systems
// Programming Project #3: The Producer / Consumer Problem With 
// Prime Number Detector
// November 21, 2012
// Instructor: Dr. Ajay K. Katangur
//
//********************************************************************

#include "buffer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/wait.h>
#include <sched.h>

// thread arguments struct
struct args_struct
{
    int seed;
    int item_total;
};

// global constants
const int MAX_THREADS = 512;

// global variables
Buffer cb;              // circular buffer object
int max_sleep;          // maximum thread sleep time
bool indiv_buff_out;    // flag for buffer snapshots
pthread_mutex_t mutex;  // mutual exclusion lock
int occupied;           // buffers occupied    
bool times_up;          // flag for end of simulation
int producer_wait;      // times producer(s) waited
int consumer_wait;      // times consumer(s) waited

// function prototypes
void *producer( void * );
void *consumer( void * );
void mySleep( unsigned int );
void buffer_snap();
void display_results( int length, int p_num, int c_num, int prod_total, 
                    int cons_total, struct args_struct pargs[], 
                    struct args_struct cargs[] );

int main( int argc, char *argv[] )
{
    // local variables
    int sim_length;                         // length of simulation
    int producer_num;                       // number of producers
    int consumer_num;                       // number of consumers
    int ii;                                 // loop control
    int total_produced;                     // total items produced
    int total_consumed;                     // total items consumed 
    int seed_offset;                        // offset to vary seeds
    unsigned int sleep_time;                // time main will sleep
    pthread_t pthreads[ MAX_THREADS ];      // pthreads array
    pthread_attr_t attr;                    // pthreads attributes
    struct args_struct pargs[MAX_THREADS];  // producer threads arg structs
    struct args_struct cargs[MAX_THREADS];  // consumer threads arg structs

    if( argc != 6 )
    {
        printf("Usage: progname l s p c o \nwhere: \nl = length of" 
                " simulation (seconds) \ns = max sleep time for threads" 
                " (seconds) \np = number producer threads \nc = number "
                "consumer threads \no = output individual buffer snapshots"
                " (yes or no)\n");
        exit(0);
    }

    // initialize variables
    sim_length = atoi( argv[1] );
    max_sleep = atoi( argv[2] );
    producer_num = atoi( argv[3] );
    consumer_num = atoi( argv[4] );
    sleep_time = (unsigned int) sim_length;
    pthread_mutex_init( &mutex, NULL );
    occupied = 0;
    total_produced = 0;
    total_consumed = 0;
    times_up = false;
    srand( time(NULL));
    seed_offset = rand();
    producer_wait = 0;
    consumer_wait = 0;

    if( !strcmp(argv[5], "yes") )
    {
        indiv_buff_out = true;
    }
    else if( !strcmp(argv[5], "no") )
    {
        indiv_buff_out = false;
    }
    else
    {
        printf("Problem with argument 5: must be yes or no \n");
        exit(0);
    }

    printf("Starting Threads...");

    pthread_attr_init( &attr );
    pthread_attr_setscope( &attr, PTHREAD_SCOPE_SYSTEM );

    // create producer threads

    for( ii = 0; ii < producer_num; ii++ )
    {
        pargs[ii].seed = ii + seed_offset;
        pargs[ii].item_total = 0;
        pthread_create( &pthreads[ii], &attr, producer, 
                        (void *)&pargs[ii] );
    }

    // create consumer threads

    for( ii = 0; ii < consumer_num; ii++ )
    {
        cargs[ii].seed = ii + producer_num + seed_offset;
        cargs[ii].item_total = 0;
        pthread_create( &pthreads[ii+producer_num], &attr, consumer, 
                        (void *)&cargs[ii]);
    }

    // sleep for specified time

    mySleep( sleep_time );

    // flip protected flag to signal end of simulation

    pthread_mutex_lock( &mutex );

    times_up = true;

    pthread_mutex_unlock( &mutex );

    // wait for all threads to terminate before joining
    // if this is left out, some threads will get errors
    // from sem_wait (interrupted by system call)

    wait( NULL );

    // join threads
    
    for( ii = 0; ii < producer_num; ii++ )
    {
        pthread_join( pthreads[ii], NULL );
    }

    for( ii = 0; ii < consumer_num; ii++ )
    {
        pthread_join( pthreads[ii+producer_num], NULL );
    }

    for( ii = 0; ii < producer_num; ii++ )
    {
        total_produced += pargs[ii].item_total;
    }

    for( ii = 0; ii < consumer_num; ii++ )
    {
        total_consumed += cargs[ii].item_total;
    }

    // display statistics for simulation

    display_results( sim_length, producer_num, consumer_num, total_produced, 
                    total_consumed, pargs, cargs );

    return(0);
}

//*********************************************************************
//
// Producer Function
//
// This is the handler for producer threads. It alternates between
// sleeping and generating random numbers and inserting them into the
// circular buffer object.
//
// Parameters: void * s --------- pointer to unspecified data type
//
// Return value: none
//
//*********************************************************************
void *producer( void *s )
{
    int ii; // loop control
    int item; // item to be inserted into cb

    // get arguments struct

    struct args_struct *args = (struct args_struct *)s;

    // get seed from arguments struct

    unsigned int seed = (unsigned int ) args -> seed;
    
    do
    {
        // sleep...zzz...

        unsigned int sleep_time = rand_r( &seed ) % max_sleep+1;
        mySleep( sleep_time );

        // check if the buffer is full

        if( cb.buffer_occupied() == cb.buffer_size() )
        {
            printf("All buffers full. Producer %d waits.\n", pthread_self());
            producer_wait++;
            continue;
        }

        // lock mutex

        pthread_mutex_lock( &mutex );

        // **CRITICAL SECTION**

        if( indiv_buff_out )    
        {
            buffer_snap(); // Display buffer snapshot
        }

        // produce an item

        item = rand_r( &seed ) % 100;
        
        // insert item in buffer

        if( !cb.buffer_insert_item( item ) ) 
        {
            printf("Error inserting item in buffer");
            exit(0);
        }

        // increment total items produced for this thread

        args -> item_total ++;
        
        printf( "\nProducer %d writes %d\n", pthread_self(), item );

        // unlock mutex

        pthread_mutex_unlock( &mutex );

        // check for end of simulation

        if( times_up )  
        {
            pthread_exit(0);
        }

    }while(true);

}

//*********************************************************************
//
// Consumer Function
//
// This is the handler for consumer threads. It alternates between
// sleeping and removing an item from the circular buffer object
// and determining whether or not it is prime.
//
// Parameters: void * s --------- pointer to unspecified data type
//
// Return value: none
//
//*********************************************************************
void *consumer( void *s)
{
    int item;   // an item from the buffer
    int ii;
    bool prime; // flag for prime number detection

    // get args struct

    struct args_struct *args = (struct args_struct *)s;

    // get seed from args struct

    unsigned int seed = (unsigned int ) args -> seed;

    do
    {
        // sleep...zzz...

        unsigned int sleep_time = rand_r( &seed ) % max_sleep+1;
        mySleep( sleep_time );

        // check if buffer is empty

        if( cb.buffer_occupied() == 0 )
        {
            printf("All buffers empty. Consumer %d waits.\n", pthread_self());
            consumer_wait++;
            continue;
        }
    
        // lock mutex

        pthread_mutex_lock( &mutex );

        // **CRITICAL SECTION**

        if( indiv_buff_out )    
        {
            buffer_snap(); // display buffer snapshot
        }

        // remove an item from the buffer

        if( !cb.buffer_remove_item( &item ) )
        {
            printf("Error removing item from buffer");
            exit(0);
        }

        // increment total items consumed for this thread

        args -> item_total ++;

        // assume item is prime

        prime = true;

        // if it is divisible by any number between 2 and
        // itself-1 (inclusive) then it is not prime

        for( ii = 2; ii < item; ii++ )
        {
            if( item % ii == 0 )
                prime = false;
        }

        printf( "\nConsumer %d reads %d\n", pthread_self(), item );
        
        if( prime )
        {
            printf( "   * * * PRIME * * *   \n");
        }

        // unlock mutex

        pthread_mutex_unlock( &mutex );

        // check for end of simulation

        if( times_up )  
        {
            pthread_exit(0);
        }

    }while(true);
}

//*************************************************************************
//
// mySleep Function
//
// This is a thread-safe sleep function that uses nanosleep.
//
// Parameters:  unsigned int seconds ------ the number of seconds to sleep
//
// Return Value: none
//*************************************************************************
void mySleep( unsigned int seconds )
{
    struct timespec req={0};   // argument for nanosleep
    time_t sec=(int)(seconds); // get the number of seconds to sleep
    req.tv_sec=sec;            // put this number into argument 
    req.tv_nsec=0;
    while(nanosleep(&req,&req)==-1) // if nanosleep returns -1 it was 
         continue;                  // interrupted, so try again
}

//*************************************************************************
//
// buffer_snap Function
//
// This function displays the state of the buffer at the moment it is called.
//
// Parameters: none
//
// Return Value: none
//*************************************************************************
void buffer_snap()
{
    int ii;

    // get the number of buffers occupied and display this

    occupied = cb.buffer_occupied();
    printf( "\n(buffers occupied: %d)\n", occupied );

    // display the content of the buffers

    printf( "buffers: " );  
    for( ii = 0; ii < cb.buffer_size(); ii++ )
    {
        printf( " %d  ", cb.buffer_retrieve_item(ii) );
    }
    printf("\n         ");
    for( ii = 0; ii < cb.buffer_size(); ii++ )
    {
        printf( "---- ");
    }
    printf("\n          ");

    // display the positions to read from and write to

    if( cb.buffer_remove_pos() <= cb.buffer_insert_pos())
    {
        for( ii = 0; ii < cb.buffer_remove_pos()*5; ii++ )
        {
           printf( " " );
        }
        printf( "R" );
        for( ii=0; ii<(cb.buffer_insert_pos()-cb.buffer_remove_pos())*5; ii++)
        {
            printf( " ");
        }
        printf( "W");
        printf("\n");
    }
    else 
    {
        for( ii = 0; ii < cb.buffer_insert_pos()*5; ii++ )
        {
            printf( " " );
        }
        printf( "W" );
        for( ii=0; ii<(cb.buffer_remove_pos()-cb.buffer_insert_pos())*5; ii++)
        {
            printf( " ");
        }
        printf( "R");
        printf("\n");
    }
}

//*************************************************************************
//
// display_results Function
//
// This function displays the statistics of the simulation
//
// Parameters: int length -------------- the length of the simulation
//             int p_num  -------------- the number of producer threads
//             int c_num  -------------- the number of consumer threads
//             int prod_total ---------- total items produced
//             int cons_total ---------- total items consumed
//             args_struct p_args[] ---- array of structs containing data from
//                                       produder threads
//             args_struct c_args[] ---- array of structs containing data from
//                                       consumer threads
//
// Return Value: none
//*************************************************************************
void display_results( int length, int p_num, int c_num, int prod_total, 
                    int cons_total, struct args_struct pargs[], 
                    struct args_struct cargs[] )
{
    int ii;
    
    printf("PRODUCER / CONSUMER SIMULATION COMPLETE\n");
    printf("=======================================\n");
    printf("Simulation Time:                     %d \n", length);
    printf("Maximum Thread Sleep Time:           %d \n", max_sleep);
    printf("Number of Producer Threads:          %d \n", p_num);
    printf("Number of Consumer Threads:          %d \n", c_num);
    printf("Size of Buffer:                      %d \n", cb.buffer_size());
    printf("\n");
    printf("Total Number of Items Produced:      %d \n", prod_total);
    
    for( ii = 0; ii < p_num; ii++ )
    {
        printf("\tThread %d:                    %d \n", ii+1, 
                pargs[ii].item_total);
    }
    
    printf("Total Number of Items Consumed:      %d \n", cons_total);
    
    for( ii = 0; ii < c_num; ii++ )
    {
        printf("\tThread %d:                    %d \n", ii+1+p_num, 
                cargs[ii].item_total);
    }

    printf("Number Of Items Remaining in Buffer: %d \n", 
            cb.buffer_occupied());
    printf("Number Of Times Buffer Was Full:     %d \n", producer_wait );
    printf("Number Of Times Buffer Was Empty:    %d\n", consumer_wait );
}
