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
#include <stdio.h>

using namespace std;

//****************************************************
//
// Buffer Constructor
//
//****************************************************
Buffer::Buffer()
{
    buffer_init();
}
//****************************************************
//
// Buffer initialization
//
//****************************************************
void Buffer::buffer_init()
{
    int ii;

    // fill buffer with place-holder values

    for(ii = 0; ii < BUFFER_SIZE; ii++)
    {
        buffer[ii] = -1;
    }

    // initialize mutex and counting semaphores

    pthread_mutex_init( &mutex, NULL );
    sem_init( &full, 0, 0 );
    sem_init( &empty, 0, BUFFER_SIZE );
    
    // initialize read and write positions to 0
    ins = 0;
    rem = 0;
}

//****************************************************
//
// Insert buffer_item
//
// Parameters: buffer_item item ---- item to be inserted
//
// Return Value: bool
//
//****************************************************
bool Buffer::buffer_insert_item( buffer_item item )
{
    int retval = 0;

    // wait for buffer to not be full and increment empty semaphore

    retval = sem_wait( &empty );
    if( retval < 0 )
    {
        perror("Error with sem_wait");
        return(0);
    } 
   
    // lock mutex

    retval = pthread_mutex_lock( &mutex );
    if( retval < 0 )
    {
        perror("Error with mutex lock");
        return(0);
    }

    buffer[ins] = item;     // insert item
    ins = (ins + 1) % (BUFFER_SIZE);    // increment insert position
    
    // unlock mutex

    retval = pthread_mutex_unlock( &mutex );
    if( retval < 0 )
    {
        perror("Error with mutex unlock");
        return(0);
    }

    // increment full semaphore

    retval = sem_post( &full );
    if( retval < 0 )
    {
        perror("Effor with sem_post");
        return(0);
    }    

    return(1);
}

//****************************************************
//
// Remove buffer_item
//
// Parameters: buffer_item ---- item removed
//
// Return Value: bool
//
//****************************************************
bool Buffer::buffer_remove_item( buffer_item *item )
{
    int retval = 0;

    // wait until buffer is not empty and decrement full semaphore

    retval = sem_wait( &full );
    if( retval < 0 )
    {
        perror("Error with sem_wait");
        return(0);
    }
        
    // lock mutex

    retval = pthread_mutex_lock( &mutex );
    if( retval < 0 )
    {
        perror("Error with mutex lock");
        return(0);
    }

    *item = buffer[rem];  // retrieve an item
    buffer[rem] = -1;     // insert a place-holder value
    rem = (rem + 1) % (BUFFER_SIZE);  // increment remove position
    
    // unlock mutex

    retval = pthread_mutex_unlock( &mutex );
    if( retval < 0 )
    {
        perror("Error with mutex unlock");
        return(0);
    }

    // increment empty semaphore
  
    retval = sem_post( &empty );
    if( retval < 0 )
    {
        perror("Effor with sem_post");
        return(0);
    }    

    return(1);
}

//****************************************************
//
// Return insert position
//
// Return Value: int
//
//****************************************************
int Buffer::buffer_insert_pos()
{
    return( ins );
}

//****************************************************
//
// Return remove position
//
// Return Value: int
//
//****************************************************
int Buffer::buffer_remove_pos()
{
    return( rem );
}

//****************************************************
//
// Retrieve an item
//
// Parameters: int pos ---- position of item to be returned
//
// Return Value: int
//
//****************************************************
int Buffer::buffer_retrieve_item( int pos )
{
    return( buffer[pos] );
}

//****************************************************
//
// Return buffer size
//
// Return Value: int
//
//****************************************************
int Buffer::buffer_size()
{
    return( BUFFER_SIZE );
}

//****************************************************
//
// Return number of buffers occupied
//
// Return Value: int
//
//****************************************************
int Buffer::buffer_occupied()
{
    int o = 0;
    int ii;

    for( ii = 0; ii < BUFFER_SIZE; ii++ )
    {
        if( buffer[ii] != -1 )
            o++;
    }

    return(o);
}    
