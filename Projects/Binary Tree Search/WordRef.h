#ifndef _WORDREF_
#define _WORDREF_

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>

using namespace std;

class WordRef
{
 public:
 
  // default constructor and overloaded constructor
  WordRef();
  WordRef( const string &s, const list<int> &l, int c=0, int sz=0 );

  // copy constructor and assignment operator
  WordRef( const WordRef & other );
  WordRef & operator=( const WordRef &other );
  
  // destructor
  ~WordRef();


  // accessor methods
  string GetWord() const;
  int GetCount() const;
  int GetSize() const;
  list<int> GetLineNumbers() const;
  void printWord( ofstream& file ) const;

  // mutator methods
  void SetWord( const string &s );
  void SetCount( int i );
  void SetSize( int i );
  void SetLineNumbers( const list<int> &l );

 
 private:

  // private data memebers...not complete..
  string word;
  int count;
  int size;
  list<int> lineNumbers;


};

#endif
