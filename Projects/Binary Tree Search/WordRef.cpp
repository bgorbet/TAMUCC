#include "WordRef.h"

/***************************************************************************
*
*                           Default Constructor
*
***************************************************************************/
WordRef::WordRef()
{
	word.clear();
	count = 0;
	size = 0;
	lineNumbers.clear();
}

/***************************************************************************
*
*                          Overloaded Constructor
*
***************************************************************************/
WordRef::WordRef( const string &s, const list<int> &l, int c, int sz )
{
	word = s;
	count = c;
	size = sz;
	lineNumbers = l; 
}

/***************************************************************************
*
*                            Copy Constructor
*
***************************************************************************/
WordRef::WordRef( const WordRef & other )
{
	word = other.word;
	count = other.count;
	size = other.size;
	lineNumbers = other.lineNumbers;
}

/***************************************************************************
*
*                   Assignment Operator (WordRef = WordRef)
*
***************************************************************************/
WordRef& WordRef::operator=( const WordRef &other )
{
	if( this != &other )
	{
		word = other.word;
		count = other.count;
		size = other.size;
		lineNumbers = other.lineNumbers;
	}

	return( *this );
}

/***************************************************************************
*
*                             Destructor
*
***************************************************************************/
WordRef::~WordRef()
{
	word.erase();
	count = 0;
	size = 0;
	lineNumbers.clear();
}

/***************************************************************************
*
*                          Get Word Function
*
***************************************************************************/
string WordRef::GetWord() const
 {
	 return( word );
 }

 /**************************************************************************
 * 
 *                          Get Count Function
 *
 **************************************************************************/
 int WordRef::GetCount() const
 {
	 return( count );
 }

 /**************************************************************************
 *
 *                          Get Size Function
 *
 **************************************************************************/
 int WordRef::GetSize() const
 {
	 return( size );
 }

 /**************************************************************************
 *
 *                      Get Line Numbers Function
 *
 **************************************************************************/
 list<int> WordRef::GetLineNumbers() const
 {
	 return( lineNumbers );
 }
 
 /***************************************************************************
*
*                            Print Word Method 
*
***************************************************************************/
void WordRef::printWord( ofstream& file) const
{
	list<int> l;
	list<int>::iterator current;
	l = lineNumbers;
	current = l.begin();
	file << setw(20) << left << word << " "
             << setw(4) << left << size << " "
             << setw(5) << left << count << " ";
	for( int i=0; i<count; i++ )
	{
		file << *current << " ";
		current++;
	}
	file << endl;
}

/***************************************************************************
*
*                           Set Word Function
*
/**************************************************************************/
void WordRef::SetWord( const string &s )
{
	word = s;
}

/***************************************************************************
*
*                           Set Count Funtion
*
***************************************************************************/
void WordRef::SetCount( int i )
{
	count = i;
}

/***************************************************************************
*
*                           Set Size Function
*
***************************************************************************/
void WordRef::SetSize( int i )
{
	size = i;
}

/***************************************************************************
*
*                         Set Line Numbers Function
*
***************************************************************************/
void WordRef::SetLineNumbers( const list<int> &l )
{
	lineNumbers = l;
}




