//######################################################
//
// List Class
//
//######################################################
#ifndef _MODULE_LISTTYPE_
#define _MODULE_LISTTYPE_


//######################################################
//
// Includes and Defines
//
//######################################################
#include <cstdlib>
#include <iostream>
using namespace std;


//######################################################
//
// List Class Definition
//
//######################################################
template <class T>
class ListType
{
 public:
  // constructors
  ListType();
  ListType( const ListType<T>& L );
      
  // destructor
  ~ListType();

  // assignment operator
  ListType<T>& operator=( const ListType<T>& L );

  // method to clear the list
  void Clear();
      
  // methods to check list status
  int Size() const;               
  bool IsEmpty() const;
  int CurrentIndex() const;
  bool AtFirst() const;
  bool AtLast() const;

  // Data retrieval/modification
  bool DataRead( T &x );
  bool DataWrite( T &x );

  // Traversal methods
  bool First() const;
  bool Next() const;
  bool Last() const;
  bool Previous() const;
  bool Seek( int moveto_index = 0 ) const;
  bool Traverse( void visit( T& item ), int start_index = 0 );
  bool RTraverse( void visit( T& item ), int start_index = -1 );
      
  // Insertion methods
  bool InsertFirst( const T &item );
  bool InsertAt( const T &item );
  bool InsertLast( const T &item );
      
  // Deletion methods
  bool DeleteFirst();
  bool DeleteAt();
  bool DeleteLast();

 private:
  struct ListNodeType
  {
    T data;
    ListNodeType *previous;
    ListNodeType *next;
  };

  // pointers maintain access to first, last, and current node in list
  ListNodeType *first;
  ListNodeType *last;
  mutable ListNodeType *current;
      
  // number of elements and position index in the list
  int size;
  mutable int index;
};


//######################################################
//
// List Constructor
//
//######################################################
template <class T>
ListType<T>::ListType() 
  : first(NULL), last(NULL), current(NULL), size(0), index(-1)
{}


//######################################################
//
// List Copy Constructor
//
//######################################################
template <class T>
ListType<T>::ListType( const ListType<T>& L )
{
    // local variables
    ListNodeType *cur;

    // initialize local variables
    cur = L.first;
  
    // initialize all interal pointers, size, and index
    first = NULL;
    last = NULL;
    current = NULL;
    size = 0;
    index = -1;
  
    // copy the list L into the current list
    while( cur != NULL )
    {
        InsertLast( cur -> data );
        cur = cur -> next;
    }	

    // goto the first node in the list
    Seek();
}


//######################################################
//
// List Destructor
//
//######################################################
template <class T>
ListType<T>::~ListType()
{
  // call the Clear method
  Clear();

}


//######################################################
//
// List Assignment Operator (List = List)
//
//######################################################
template <class T>
ListType<T>& ListType<T>::operator=( const ListType<T>& L )
{
    // local variables
    ListNodeType *cur;

    // initialize local variables
    cur = L.first;
  
    // if the two lists are different, copy list L into current list
    if( this != &L )
    {
        Clear();
	    while( cur != NULL )
	    {
	        InsertLast( cur -> data );
	        cur = cur -> next;
	    }
	    Seek();
	}

    // return to calling function
    return( *this );
}


//######################################################
//
// List Clear Method
//
//######################################################
template <class T>
void ListType<T>::Clear()
{
	// Delete the first node until the list is empty
	while( !IsEmpty() )
	    DeleteFirst();
	
	// reset the list internal pointers, size and index
	first = NULL;
	last = NULL;
	current = NULL;
	size = 0;
	index = -1;
}


//######################################################
//
// List Size Method
//
//######################################################
template <class T>
int ListType<T>::Size() const
{    
    // return current list size to the calling function
    return( size );
}

                      
//######################################################
//
// List Is Empty Method
//
//######################################################
template <class T>
bool ListType<T>::IsEmpty() const
{
    // test if list is empty and return true or false to calling function
    return( size == 0 );
}


//######################################################
//
// List Return Current Index Method
//
//######################################################
template <class T>
int ListType<T>::CurrentIndex() const
{
    // return current index to calling function
    return( index );
}


//######################################################
//
// List Beginning of List Method
//
//######################################################
template <class T>
bool ListType<T>::AtFirst() const
{
    // local variables
    bool retval = false;

    // test if at the beginning of the list
    if( !IsEmpty() )
	    if( current -> previous == NULL )
	        retval = true;

    // return to calling function
    return( retval );
}


//######################################################
//
// List End of List Method
//
//######################################################
template <class T>
bool ListType<T>::AtLast() const
{
    // local variables
    bool retval = false;

    // test if at the end of the list
    if( !IsEmpty() )
	    if( current -> next == NULL )
		    retval = true;
			
    // return to calling function
    return( retval );
}


//######################################################
//
// List Read Data Method
//
//######################################################
template <class T>
bool ListType<T>::DataRead( T &x )
{
    // local variables
    bool retval = false;

    // if list is not empty...return data
    if( !IsEmpty() )
	{
	    x = current -> data;
	    retval = true;
	}
	
    // return to calling function
    return( retval );
}


//######################################################
//
// List Write Data Method
//
//######################################################
template <class T>
bool ListType<T>::DataWrite( T &x )
{
    // local variables
    bool retval = false;

    // if list is not empty...write x at current location
	if( !IsEmpty() )
	{
		current -> data = x;
		retval = true;
	}

    // return to calling function
    return( retval );
}


//######################################################
//
// List First List Node Method
//
//######################################################
template <class T>
bool ListType<T>::First() const 
{
  // seek to the front node
  return( Seek() );
  
}


//######################################################
//
// List Next List Node Method
//
//######################################################
template <class T>
bool ListType<T>::Next() const 
{
    // local variables
    bool retval = false;
  
    // if traversal has reached the end of the list or
    // the list is empty, just return
    if( !IsEmpty() )
	// otherwise go to the next node
        if( current -> next != NULL )
	    {
	        current = current -> next;
		index++;
		retval = true;
	    }
		
   // return to calling function	
   return( retval );
}


//######################################################
//
// List Last List Node Method
//
//######################################################
template <class T>
bool ListType<T>::Last() const
{
  // seek to the last node and return true or false accordingly
  return( Seek( size-1 ) );
}


//######################################################
//
// List Previous List Node Method
//
//######################################################
template <class T>
bool ListType<T>::Previous() const 
{
    // local variables
    bool retval = false;
	
    // if traversal has reached the end of the list or
    // the list is empty, just return
    if( !IsEmpty() )
	// otherwise go to the previous node
        if( current -> previous != NULL )
	    {
	        current = current -> previous;
		index--;
	        retval = true;
	    }
	
    // return to calling function
    return( retval );
}


//######################################################
//
// List Seek Current Method
//
//######################################################
template <class T>
bool ListType<T>::Seek( int moveto_index /* = 0 */ ) const 
{
    // local variables
    bool retval = false;
   
    // if list is not empty and moveto_index is valid...
    if( !IsEmpty() )
	{
	    if(  ( moveto_index < size ) && 
	         ( moveto_index >= 0 ) )
	      {    
		// go there traversing forwards or backwards
		if( index < moveto_index )
		  {
		    for( int i = index; i < moveto_index; i++ )
		      {
			retval = Next();
		      }
		  }
		else if( index > moveto_index )
		  {
		    for( int i = index; i > moveto_index; i--)
		      {
			retval = Previous();
		      }
		  }	
		else
		  retval = true;
	      }
	}	
    // return to calling function
    return( retval );
}


//######################################################
//
// List Traverse Method
//
//######################################################
template <class T>
bool ListType<T>::Traverse( void visit( T& item ), int start_index /* = 0 */ )
{
    // local variables
    bool retval = false,
         flag = false;
	
    // if list is not empty then "visit" each node traversing forwards
    if( !IsEmpty() )
        if( ( flag = Seek( start_index ) ) == true)
	    {
		    while( flag == true )
			{
			    visit( current -> data );
			    flag = Next();
			}
	        retval = true;
        }
	
    // return to calling function
    return( retval );
}		 


//######################################################
//
// List Reverse Traverse Method
//
//######################################################
template <class T>
bool ListType<T>::RTraverse( void visit( T& item ), int start_index /* = -1 */ )
{
    // local variables
    bool retval = false,
	 flag = false;

    // if starting index is -1 then seek to the last node
    if( start_index == -1)
	    start_index = size-1;

    // if the list is not empty then "visit" each node traversing backwards
    // the list
    if( !IsEmpty() )
    if( ( flag = Seek( start_index ) ) == true)
     {
           while( flag == true )
	    {
	      visit( current -> data );
	      flag = Previous();
	    }
	   retval = true;
     }
	
    // return to calling function
    return( retval );
}


//######################################################
//
// List Insert New Front Node Method
//
//######################################################
template <class T>
bool ListType<T>::InsertFirst( const T& item )
{
    bool retval = false;
    
    // call Seek() if the list is not empty
    if( !IsEmpty() )
	{
		retval = Seek();
		// insert at front
		retval = InsertAt( item );
	}
    else
      // if the list is empty, insert without seeking
      retval = InsertAt( item );
	
    return( retval );
}


//######################################################
//
// List Insert At Current Location Method
//
//######################################################
template <class T>
bool ListType<T>::InsertAt( const T& item )
{
    // local variables
    ListNodeType *newnode = NULL;
    bool retval = false;
	
    // create new list node and insert into linked list
    newnode = new ListNodeType;
	
    if( newnode != NULL )
    {		
	    newnode -> data = item;
	    newnode -> next = current;
	    if( first == NULL )
	      {
		newnode -> previous = NULL;
		current = newnode;
		last = newnode;
	      }
	    else
	      {
		newnode -> previous = current -> previous;
		current -> previous = newnode;
		current = newnode;
	      }
	  
	    if( newnode -> previous == NULL )
	      first = newnode;
	    else 
	      newnode -> previous -> next = newnode;
	    
	    size++;
	    
	    retval = true;
    }
    
    // return to calling function
    return( retval );
}


//######################################################
//
// List Insert New Last Node Method
//
//######################################################
template <class T>
bool ListType<T>::InsertLast( const T& item )
{
    // local variables
    ListNodeType *newnode = NULL;
    bool retval = false;
	
    // create new ListNode and insert node in list
    newnode = new ListNodeType;
	
	if( newnode != NULL )
	{
	    newnode -> data = item;
	    newnode -> next = NULL;
	    newnode -> previous = last;
	
            if( first == NULL )
	      first = newnode;
	    else
	      last -> next = newnode;
		
	    last = newnode;
            current = last;
	    index = Size();
      	    size++;
	    retval = true;
	}
	
	// return to calling function
    return( retval );
}	


//######################################################
//
// List Delete Front List Node Method
//
//######################################################
template <class T>
bool ListType<T>::DeleteFirst()
{
   // local variables
    ListNodeType *delptr;
    bool retval = false;
  
    // initialize local variables
    delptr = NULL;
	
    // if list is not empty delete the last node of the linked list
    if( !IsEmpty() )
	{
	    delptr = first;
	    first = first -> next;
		
	    if( first == NULL )
	        last = NULL;
	    else
		first -> previous = NULL;
			
	    delete delptr;
	    current = first;
		
	    size--;
		
	    retval = true;
	}
	
    // return to calling function
    return( retval );
}


//######################################################
//
// List Delete Current List Node Method
//
//######################################################
template <class T>
bool ListType<T>::DeleteAt()
{
    // local variables
    ListNodeType *delptr;
    bool retval = false;

    // initialize local variables
    delptr = NULL;

    // delete the current node in the linked list
    if( !IsEmpty() )
    {
        if( AtLast() )
	    retval = DeleteLast();
	else if( AtFirst() )
	    retval = DeleteFirst();
	else
	{
	    delptr = current;
	    current -> previous -> next = current -> next;
	    current -> next -> previous = current -> previous;
	    current = current -> next;
			
	    delete delptr;
	    size--;
			
	    retval = true;
	}
    }	
			
    // return to calling function
    return( retval );
}


//######################################################
//
// List Delete Last List Node Method
//
//######################################################
template<class T>
bool ListType<T>::DeleteLast()
{
    // local variables
    ListNodeType *delptr;
    bool retval = false;
  
    // initialize local variables
    delptr = NULL;
	
    // if list is not empty delete the last node of the linked list
    if( !IsEmpty() )
	{
	    delptr = last;
	    last = last -> previous;
		
	    if( last == NULL )
		    first = NULL;
	    else
		    last -> next = NULL;
			
	    delete delptr;
	    current = last;
		
	    size--;
	    index = size - 1;
		
	    retval = true;
	}
	
    // return to calling function
    return( retval );
}

//######################################################
//######################################################
#endif  // _MODULE_LISTTYPE_





