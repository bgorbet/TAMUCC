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

#ifndef _BUFFER_H_DEFINED_
#define _BUFFER_H_DEFINED_

#include <pthread.h>
#include <semaphore.h>

typedef int buffer_item;

class Buffer
{ 
private:
    static const int BUFFER_SIZE = 5;
    buffer_item buffer[BUFFER_SIZE];
    pthread_mutex_t mutex;
    sem_t full;
    sem_t empty;
    int ins;
    int rem;
public:
    
    Buffer();
    void buffer_init();
    bool buffer_insert_item( buffer_item item );
    bool buffer_remove_item( buffer_item *item );
    int buffer_insert_pos();
    int buffer_remove_pos();
    int buffer_retrieve_item( int pos );
    int buffer_size();
    int buffer_occupied();
};
#endif // _BUFFER_H_DEFINED_
