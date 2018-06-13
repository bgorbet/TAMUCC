//######################################################
//
// Stack Class
//
//######################################################
#ifndef _MODULE_STACK_
#define _MODULE_STACK_


//######################################################
//
// Includes and Defines
//
//######################################################
#include<ListType.h>

//######################################################
//
// Stack Class Definition
//
//######################################################
template<class T>
class Stack
{
 public:
  Stack();
  Stack( const Stack<T> &other );
  Stack<T> & operator=( const Stack<T> &other );
  ~Stack();

  int Size();

  bool IsEmpty();
  bool IsFull();

  bool Push( const T &x );
  bool Top( T &x );
  bool Pop();

 private:
  ListType<T> list;
};


//######################################################
//
// Stack Constructor
//
//######################################################
template<class T>
Stack<T>::Stack()
{
  list.Clear();
}


//######################################################
//
// Stack Copy Constructor
//
//######################################################
template<class T>
Stack<T>::Stack( const Stack<T> &other )
{
  list = other;
}


//######################################################
//
// Stack Assignment Operator
//
//######################################################
template<class T>
Stack<T> & Stack<T>::operator=( const Stack<T> &other )
{  
  // if the two lists are different, copy other into current list
  if( this != &other )
  
    list = other;

  // return to calling function
  return( *this );
}


//######################################################
//
// Stack Destructor
//
//######################################################
template<class T>
Stack<T>::~Stack()
{
  list.Clear();
}


//######################################################
//
// Stack Size Method
//
//######################################################
template<class T>
int Stack<T>::Size()
{
  return list.Size();
}


//######################################################
//
// Stack Is Empty Method
//
//######################################################
template<class T>
bool Stack<T>::IsEmpty()
{ 
  return( list.IsEmpty() );
}


//######################################################
//
// Stack IsFull Method
//
//######################################################
template<class T>
bool Stack<T>::IsFull()
{
  return( false );
}


//######################################################
//
// Stack Push Method
//
//######################################################
template<class T>
bool Stack<T>::Push( const T &x )
{
  return( list.InsertLast( x ) );
}


//######################################################
//
// Stack Top Method
//
//######################################################
template<class T>
bool Stack<T>::Top( T &x )
{
  list.Seek( list.Size()-1 );
  return( list.DataRead( x ) );
}


//######################################################
//
// Stack Pop Method
//
//######################################################
template<class T>
bool Stack<T>::Pop()
{
  bool retval = false;
  if( !IsEmpty() )
    retval = list.DeleteLast();

  return( retval );
}




//######################################################
//######################################################
#endif












