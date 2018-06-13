//*********************************************************************
// Annie Gorbet
// Data Structures
// Programming Project #4: Binary Search Trees and Concordance Tables
// April 5, 2012
// Instructor: Michail C. Scherger
//*********************************************************************
#include <cctype>
#include <cstring>
#include "stringutil.h"
#include "BTree.h"

using namespace std;

// Global Constants
const int MAX = 50;

// Definition of Stats structure
struct Stats
{
	string filename;
	int numWords,
	  numUniqueWords,
	  numLines;
};

// Function Prototypes
bool openFile( ifstream& inputFile, char filename[] );
void removePunct( string& text );
void tokenizeLine( string& text, string *stringArray );
void processFile( ifstream& file, BTree& bt, Stats& stats );
void updateNodeData( BTType ptr, int line );
void insertNode( BTree& bt, string& word, int line );
void writeReports( BTree& bt, Stats& stats );
void writeFile( ofstream& outFile, BTree& bt );



//********************************************************************
//
// Main
//
// Calls all functions and methods to open and read a file from
// command line, then builds a word frequency table using binary search trees
// as the basic data structure.
//
// Return Value
// ------------
// int
//
// Function Parameters
// ----------------
// arc		int		value		number command line arguements
// *argv[]	int		value		string from command line
//
//*******************************************************************
int main(int argc, char *argv[])
{
	ifstream inputFile; 
	Stats fileStats;
	
	cout << "Concordance Table Program" << endl;
	cout << "-------------------------" << endl;
	
	if ( argc < 2 ) // argc should be greater than 2 for correct execution
	  cout<<"usage: concord <filename1> <filename2> ...\n";
    
	// for each command line argument...
	for( int ii=1; ii<argc; ii++ )
	{
	  if(!openFile(inputFile, argv[ii]))  
	    exit(EXIT_FAILURE);
	  else
	  {
	    // have to use cerr here or this line won't be printed out before
	    // the function starts processing the file.
	    cerr << "Processing " << argv[ii] << "...";
			
	    // create the btree
	    BTree btree;
			
	    fileStats.filename.assign( argv[ii] );

	    // process the file
	    processFile( inputFile, btree, fileStats );

	    // close the file
	    inputFile.close();

	    // generate the report
	    writeReports( btree, fileStats );
			
			cout << "Complete." << endl;
	  }
	}
	
	return( 0 );
}

//********************************************************************
//
// Open File
//
// This function opens a file for input
//
// Return Value
// ------------
// bool                     True/False if open is successful
//
// Function Parameters
// ----------------
// inputFile	fstream		file stream
// *filename[]	char		points to name of file from command line
//
//*******************************************************************
bool openFile( ifstream& inputFile, char filename[])
{
	inputFile.open(filename); //Open input file
	if(!inputFile)
	{   //Test if input file opened successfully
	  cout << "ERROR: file could not be opened.\n";
	  return(false);
	}
	else
	  return(true);
}

//*******************************************************************
// 
// Revome Punctuation Function
//
// This Function removes all non-alphabetic characters in a line of text
//
// Reference Parameters
// --------------------
// text           string      the line of text 
//
// Local Variables
// ---------------
// textLength     int         the size of text
// ii             int         loop iteration variables       
//*******************************************************************
void removePunct( string& text )
{
	// local variables
	int textLength;
	int ii;

	// initialize local variables
	textLength = text.length();
	ii = 0;

	// test for non-alpha; if found, replace with white space
	for( ii=0; ii<textLength; ii++ )
	{
	  if( !isalpha( text[ii] ) )
	    text[ii] = ' ';
	}
}

//*******************************************************************
// 
// Tokenize Line Function
//
// This function tokenizes a line of text and puts each word into 
// a string array
// 
// Reference Parameters
// --------------------
// text            string      the line of text
// stringArray     string[]    string array to hold tokens
//
// Local Variables
// ---------------
// count           int         loop iteration variable  
// token           string      to hold each token
//*******************************************************************
void tokenizeLine( string& text, string *stringArray )
{
        // local variables
	int count = 0;
	string token;

        // trim white space from both ends of line and get a token
	text = Trim( text );
	token = Token( text );
	
	// put each token into the array
	while( count < MAX && token.length() != 0 )
	{
	  stringArray[count] = token;
	  count++;
	  token = Token( text );
	}
}

//*******************************************************************
// 
// Process File Function
//
// This function calls other functions necessary to process the file
// and build the binary search tree.
//
// Reference Parameters
// --------------------
// file           ifstream     the file being processed
// bt             BTree        binary search tree variable
// stats          Stats        file statistics variable
//
// Local Variables
// ---------------
// tokens         *string      pointer to array to hold tokens from each line
// aLine          string       string to hold each line from the file
// btreePtr       BTType       a pointer to a binary search tree node
//*******************************************************************
void processFile( ifstream& file, BTree& bt, Stats& stats )
{
        // local variables
	string *tokens;
	string aLine;
	BTType btreePtr;
	
        // initialize file statistics
	stats.numWords = 0;
	stats.numUniqueWords = 0;
	stats.numLines = 0;

        // get a line from the file
	while( getline( file, aLine ) )
	{
          // update line number stat for each line
	  stats.numLines = stats.numLines+1;
		
          // create dynamic string array, with tokens pointing to it
	  tokens = new string[MAX];
		
          // if the line is not empty, "fix" the line and tokenize into 
          // tokens array
	  if( aLine.length() != 0 )
	  {
	    removePunct( aLine );
	    aLine = ToUpper( aLine );
	    tokenizeLine( aLine, tokens );
	  }

	  // for each word, update btree node data or insert a new node
	  for( int ii=0; tokens[ii].length()!=0; ii++ )
	  {
	    stats.numWords = stats.numWords+1;
	    btreePtr = bt.bt_search( tokens[ii] );
	    if( btreePtr != NULL )
	      updateNodeData( btreePtr, stats.numLines );
	    else
	      insertNode( bt , tokens[ii], stats.numLines );
	  }
	
	  delete [] tokens;
	}
	
	// number of unique words will be equal to number of nodes in btree
	stats.numUniqueWords = bt.bt_nodeCount();
}

//*******************************************************************
// 
// Update Node Data Function
//
// This function updates data for an existing node in the binary search tree
//
// Value Parameters
// ----------------
// ptr         BTType        a pointer to a binary search tree node
// line        int           the line number 
//
// Local Variables
// ---------------
// l           list<int>     a list of integers to hold line numbers
// count       int           an int variable to hold word count
//*******************************************************************
void updateNodeData( BTType ptr, int line )
{
        // local variables
	list<int> l;
	int count;
	
	// initialize local variables
	l = ptr->data.GetLineNumbers();
	count = ptr->data.GetCount();
	
	// updata line number and word count for node
	l.push_back( line );
	count=count+1;
	
	// put the updated data in the node
	ptr->data.SetLineNumbers( l );
	ptr->data.SetCount( count );
}

//*******************************************************************
// 
// Insert Node Function
//
// This function inserts a new node into the binary search tree
//
// Reference Parameters
// --------------------
// bt              BTree      the binary search tree
// word            string     the word to be added to the new node
//
// Value Parameters
// ----------------
// line            int        the line number the word first appears on
// 
// Local Variables
// ---------------
// newWord         WordRef    word reference variable to hold info for new node
// l               list<int>  to hold line numbers list (of size 1)
//*******************************************************************
void insertNode( BTree& bt, string& word, int line )
{
        // local variables
	WordRef newWord;
	list<int> l;
	
	// make line numbers list
	l.assign( 1, line );
	
	// set data for the new node
	newWord.SetWord( word );
	newWord.SetSize( word.length() );
	newWord.SetCount( 1 );
	newWord.SetLineNumbers( l );
	
	// insert the new node
	bt.bt_insert( newWord );
}
	
//*******************************************************************
// 
// Write Reports Function
//
// This function writes the report, containing the word frequency table
// and file stats, for a file
//
// Reference Parameters
// --------------------
// bt                BTree       a binary search tree
// stats             Stats       file statistics variable
//
// Local Variables
// ---------------
// inorder           ofstream    ouput file object
// preorder          ofstream    ouput file object
// postorder         ofstream    ouput file object
// inorderFilename   string      string to hold file name
// preorderFilename  string      string to hold file name
// postorderFilename string      string to hold file name
//*******************************************************************
void writeReports( BTree& bt, Stats& stats )
{
        // local variables
	ofstream inorder, preorder, postorder;	
	string inorderFilename = stats.filename;
	string preorderFilename = stats.filename;
	string postorderFilename = stats.filename;
	
	// add extensions to each file name
	inorderFilename += ".inorder.txt";
	preorderFilename += ".preorder.txt";
	postorderFilename += ".postorder.txt";
	
	// open and write inorder traversal file
	inorder.open( inorderFilename.c_str() );
	if( !inorder )
	  cout << "Error: could not open " << inorderFilename << endl;
	else
	{
	  inorder<<"INORDER CONCORDANCE TABLE"<< endl
		 << "\n"
		 << setw(30) << left << "FILE:" << stats.filename << endl
		 << setw(30) << left << "NUMBER OF LINES:" << stats.numLines 
		 << endl
		 << setw(30) << left << "NUMBER OF WORDS:" << stats.numWords 
		 << endl
		 << setw(30) << left << "NUMBER OF UNIQUE WORDS:"
		 << stats.numUniqueWords << endl
		 << "\n"
		 << setw(21) << left << "WORD" 
		 << setw(5) << left << "SIZE"
		 << setw(6) << left << "FREQ"
		 << "LINE REFERENCE" << endl
		 << "--------------------------------------------------" 
		 << endl;
					
	  bt.bt_inorderTraversal( inorder );
	}
		
	// open and write preorder traversal file
	preorder.open( preorderFilename.c_str() );
	if( !preorder )
	  cout << "Error: could not open " << preorderFilename << endl;
	else
	{
	  preorder<<"PREORDER CONCORDANCE TABLE"<<endl
		  << "\n"
		  << setw(30) << left << "FILE:" << stats.filename << endl
		  << setw(30) << left << "NUMBER OF LINES:" << stats.numLines 
		  << endl
		  << setw(30) << left << "NUMBER OF WORDS:" << stats.numWords 
		  << endl
		  << setw(30) << left << "NUMBER OF UNIQUE WORDS:"
		  << stats.numUniqueWords << endl
		  << "\n"
		  << setw(21) << left << "WORD" 
		  << setw(5) << left << "SIZE"
		  << setw(6) << left << "FREQ"
		  << "LINE REFERENCE" << endl
		  << "--------------------------------------------------" 
		  << endl;
					
	  bt.bt_preorderTraversal( preorder );
	}
		
	// open and write postorder traversal file
	postorder.open( postorderFilename.c_str() );
	if( !postorder )
	  cout << "Error: could not open " << postorderFilename << endl;
	else
	{
	  postorder<<"POSTORDER CONCORDANCE TABLE"<<endl
		   << "\n"
		   << setw(30) << left << "FILE:" << stats.filename << endl
		   << setw(30) << left << "NUMBER OF LINES:" << stats.numLines 
		   << endl
		   << setw(30) << left << "NUMBER OF WORDS:" << stats.numWords 
		   << endl
		   << setw(30) << left << "NUMBER OF UNIQUE WORDS:"
		   << stats.numUniqueWords << endl
		   << "\n"
		   << setw(21) << left << "WORD" 
		   << setw(5) << left << "SIZE"
		   << setw(6) << left << "FREQ"
		   << "LINE REFERENCE" << endl
		   << "--------------------------------------------------" 
		   << endl;
					
	  bt.bt_postorderTraversal( postorder );
	}
}




