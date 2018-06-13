//######################################################
//
// Annie Gorbet
// Data Structures
// Project 2: Line Editor Using Doubly Linked Lists
// Due Feb 28, 2012
// Instructor: Dr. Michael C. Scherger
//
//######################################################

//######################################################
//                                                                        
// LED                                                                    
//                                                                        
//######################################################


//######################################################
//                                                                        
// Includes and Defines                                                   
//                                                                        
//######################################################
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <ListType.h>
#include <string>
#include <stringutil.h>

#define STR_CMDNULL				""
#define STR_CMDHELP				"h"
#define STR_CMDREAD				"r"
#define STR_CMDWRITE			        "w"
#define STR_CMDCHANGEBUFFERNAME                 "f"
#define STR_CMDSAVEQUIT			        "q"
#define STR_CMDQUIT				"q!"
#define STR_CMDNEXTLINE			        "+"
#define STR_CMDPRINTCURRENT                     "p"
#define STR_CMDGOTOFIRST                        "t"
#define STR_CMDSEARCHBACK                       "?"
#define STR_CMDSEARCHFRONT                      "/"
#define STR_CMDCUT                              "d"
#define STR_CMDCUTMULTIPLE                      "dr"
#define STR_CMDCOPY                             "c"
#define STR_CMDCOPYMULTIPLE                     "cr"
#define STR_CMDPASTEBEFORE                      "pb"
#define STR_CMDPASTEAFTER                       "pa"
#define STR_CMDINSERTBEFORE                     "ib"
#define STR_CMDINSERTAFTER                      "ia"
#define STR_CMDINSERTAT                         "ic"
#define STR_CMDSUBSTCURRENT                     "s"
#define STR_CMDSUBSTSEVERAL                     "sr"
#define STR_CMDPRINTSEVERAL                     "pr"
#define STR_CMDPRINTNUMBER                      "#"
#define STR_CMDTOGGLEDISPLAYLINE                "n"
#define STR_CMDPRINTLINE                        "="
#define STR_CMDPREVIOUSLINE                     "-"
#define STR_CMDGOTOLINE                         "g"
#define STR_CMDGOTOLAST                         "b"                 

using namespace std;


//######################################################
//                                                                        
// Global Data Types                                                      
//                                                                        
//######################################################
enum LedReturnType{ LedOk, 
		    LedTooManyArgs, 
		    LedFileNotFound, 
		    LedInvalid 
                  };


enum CommandOperation{	CmdNull, 
		       	CmdHelp, 
		       	CmdRead,
		       	CmdWrite,
		       	CmdChangeBufferName,
		       	CmdSaveQuit, 
		       	CmdQuit, 
		       	CmdNextLine,
		       	CmdPrintCurrent,
		       	CmdGoToFirst,
		       	CmdSearchBack,
		       	CmdSearchFront,
                        CmdCut,
			CmdCutMultiple,
			CmdCopy,
			CmdCopyMultiple,
			CmdPasteBefore,
			CmdPasteAfter,
			CmdInsertBefore,
			CmdInsertAfter,
			CmdInsertAt,
			CmdSubstCurrent,
			CmdSubstSeveral,
			CmdPrintSeveral,
			CmdPrintNumber,
			CmdToggleDisplayLine,
			CmdPrintLine,
			CmdPreviousLine,
			CmdGoToLine,
			CmdGoToLast,		      
		       	CmdInvalid
		     };


struct CommandType
{
	CommandOperation cmd;
	string arg1;
	string arg2;
	string arg3;
	string arg4;
	string extra;
};


struct BufferType
{
	string filespec;
	bool dirty;
	ListType<string> lines;
};


struct OptionsType
{
	bool display_filespec;
	bool display_cmdnumber;
	bool display_linenumber;
};


//######################################################
//                                                                        
// Function Prototypes                                                    
//                                                                        
//######################################################
// utility functions 
void command_init( CommandType &c );
void buffer_init( BufferType &b, const string &filespec = "" );
void options_init( OptionsType &o );
void usage(const string & execname );
bool file_exists( const char *filespec );
void readbuffer( BufferType &b, ifstream &infile );
void print_prompt(OptionsType &options, BufferType &buffer, int cmdnumber);
LedReturnType command_process( OptionsType &options, BufferType &buffer );
CommandType command_get();

// driver functions 
void help_driver();
void read_driver( const CommandType &command, 
		  OptionsType &options, 
		  BufferType &buffer );
void write_driver( const CommandType &command,
	       	  OptionsType &options, 
      		  BufferType &buffer );
void changebuffername_driver( const CommandType &command, 
			      OptionsType &options, 
			      BufferType &buffer );
void savequit_driver( const CommandType &command,
		      OptionsType &options, 
         	      BufferType &buffer );
void quit_driver( const CommandType &command );
void nextline_driver( const CommandType &command,
		      OptionsType &options,
		      BufferType &buffer );
void printcurrent_driver( const CommandType &command,
			  OptionsType &options,
			  BufferType &buffer );
void gotofirst_driver( const CommandType &command,
		       OptionsType &options,
		       BufferType &buffer );
void searchback_driver( const CommandType &command,
		        OptionsType &options,
		        BufferType &buffer );
void searchfront_driver( const CommandType &command,
			 OptionsType &options,
			 BufferType &buffer );
void cut_driver( const CommandType &command,
                OptionsType &options,
                BufferType &buffer,
		BufferType &clipboard );
void cutmultiple_driver( const CommandType &command,
			 OptionsType &options,
			 BufferType &buffer,
			 BufferType &clipboard );
void copy_driver( const CommandType &command,
			 OptionsType &options,
			 BufferType &buffer,
		         BufferType &clipboard );
void copymultiple_driver( const CommandType &command,
			  OptionsType &options,
			  BufferType &buffer,
		          BufferType &clipboard );
void pastebefore_driver( const CommandType &command,
			 OptionsType &options,
			 BufferType &buffer,
		         BufferType &clipboard );
void pasteafter_driver( const CommandType &command,
			OptionsType &options,
			BufferType &buffer,
		        BufferType &clipboard );
void insertbefore_driver( const CommandType &command,
			  OptionsType &options,
			  BufferType &buffer );
void insertafter_driver( const CommandType &command,
			 OptionsType &options,
			 BufferType &buffer );
void insertat_driver( const CommandType &command,
		      OptionsType &options,
		      BufferType &buffer );
void substcurrent_driver( const CommandType &command,
			  OptionsType &options,
			  BufferType &buffer );
void substseveral_driver( const CommandType &command,
			  OptionsType &options,
			  BufferType &buffer );
void printseveral_driver( const CommandType &command,
			  OptionsType &options,
			  BufferType &buffer );
void printnumber_driver( const CommandType &command,
			  OptionsType &options,
			  BufferType &buffer );
void toggledisplayline_driver( const CommandType &command,
			       OptionsType &options );
void printline_driver( const CommandType &command,
		       OptionsType &options,
		       BufferType &buffer );
void previousline_driver( const CommandType &command,
			  OptionsType &options,
			  BufferType &buffer );
void gotoline_driver( const CommandType &command,
		      OptionsType &options,
		      BufferType &buffer );
void gotolast_driver( const CommandType &command,
		      OptionsType &options,
		      BufferType &buffer );
void invalid_driver( const CommandType &command );


//######################################################
//                                                                        
// main function                                                          
//                                                                        
//######################################################
int main( int argc, char *argv[] )
{
	// local variables 
        LedReturnType	        retval;
	BufferType		buffer;
	OptionsType		options;
	ifstream		infile;
      
	// initialize local varibles 
	retval = LedOk;
	buffer_init( buffer );
	options_init( options );

	// check for the correct number of command line arguments
	if( argc > 2 )
        {
		cout << "Too many command line arguments." << endl;
		usage( argv[0] );
		retval = LedTooManyArgs;
        }
	// check if the file does not exist
	else if(( argc == 2 ) && ( !file_exists( argv[1] )))
        {
		cout << "File " << argv[1] << " could not be opened." << endl;
		usage( argv[0] );
		retval = LedFileNotFound;
        }
	else
        {
		if( argc == 2 )
		{
		    buffer.filespec = argv[1];
		    infile.open( argv[1], ios::in );
		    readbuffer( buffer, infile );
		    buffer.lines.Seek();
		    infile.close();
		    cout << "File " << buffer.filespec << " read." << endl;
		    cout << buffer.lines.Size() << " lines in buffer." << endl;
	      	}

		// process the commands
		retval = command_process( options, buffer );

		// clear the buffer
		buffer.lines.Clear();
        }

	// return to calling environment
	return( retval );
}


//######################################################
//                                                                        
// Initialize Command Function Function                                        
//                                                                        
//######################################################
void command_init( CommandType &c )
{
	c.cmd = CmdInvalid;
	c.arg1 = "";
	c.arg2 = "";
	c.arg3 = "";
	c.arg4 = "";
}


//######################################################
//                                                                        
// Initialize Buffer Function
//                                                                        
//######################################################
void buffer_init( BufferType &b, const string & filespec /* = "" */ )
{
	b.filespec = filespec;
	b.dirty = false;
	b.lines.Clear();
}


//######################################################
//                                                                        
// Initialize Options Function
//                                                                        
//######################################################
void options_init( OptionsType &o )
{
	o.display_filespec = true;
	o.display_cmdnumber = true;
	o.display_linenumber = false;
}


//######################################################
//                                                                        
// Led Usage Function
//                                                                        
//######################################################
void usage( const string & execname )
{
	cout << "Usage: " << execname << " [file]" << endl;
}


//######################################################
//                                                                        
// File Exists Function 
//                                                                        
//######################################################
bool file_exists( const char *filespec )
{
	bool retval;
	ifstream infile;

	retval = false;
	infile.open( filespec, ios::in );
	if( infile )
        {
		retval = true;
		infile.close();
        }

	// return to calling function
	return( retval );
}


//######################################################
//                                                                        
// Print Prompt Function                                             
//                                                                        
//######################################################
void print_prompt(OptionsType &options, BufferType &buffer, int cmdnumber)
{
	cout <<"[led";
  
	if( options.display_filespec )
		cout << ":" << buffer.filespec;

	if( options.display_cmdnumber )
		cout << ":" << cmdnumber;

	if( options.display_linenumber )
		cout << ":" << buffer.lines.CurrentIndex()+1;

	cout <<"] ";
}


//######################################################
//                                                                        
// Process Commands Function                                             
//                                                                        
//######################################################
LedReturnType command_process( OptionsType &options, BufferType &buffer )
{
	// local variables
	LedReturnType	        retval;
	CommandType		command;
	BufferType 		clipboard;
	static int 		cmd_nbr = 1;

	// initialize local variables
	retval = LedOk;
	command_init( command );
	buffer_init( clipboard, "CLIPBOARD" );

	// process the commands
	// main menu loop 
	do
	{
	    print_prompt(options, buffer, cmd_nbr );
	    command = command_get();
      
	    switch( command.cmd )
	    {
     		case CmdNull: 
		     break;
	        case CmdHelp: 
		     help_driver(); 
		     break;
		case CmdRead: 
		     read_driver( command, options, buffer ); 
		     break;
	        case CmdWrite: 
		     write_driver( command, options, buffer ); 
		     break;
		case CmdChangeBufferName: 
		     changebuffername_driver( command, options, buffer ); 
		     break;
		case CmdSaveQuit: 
		     savequit_driver( command, options, buffer ); 
		     break;
		case CmdQuit: 
		     quit_driver( command ); 
		     break;
	        case CmdNextLine:
		     nextline_driver( command, options, buffer );
		     break;
		case CmdPrintCurrent:
		     printcurrent_driver( command, options, buffer );
		     break;
		case CmdGoToFirst:
		     gotofirst_driver( command, options, buffer );
		     break;
		case CmdSearchBack:
		     searchback_driver( command, options, buffer );
		     break;
		case CmdSearchFront:
		     searchfront_driver( command, options, buffer );
		     break;
	        case CmdCut:
		     cut_driver( command, options, buffer, clipboard );
                     break;
	        case CmdCutMultiple:
	             cutmultiple_driver( command, options, buffer, clipboard );
	             break;
	        case CmdCopy:
	             copy_driver( command, options, buffer, clipboard );
		     break;
	        case CmdCopyMultiple:
	            copymultiple_driver( command, options, buffer, clipboard );
	            break;
	        case CmdPasteBefore:
	             pastebefore_driver( command, options, buffer, clipboard );
	             break;
	        case CmdPasteAfter:
	             pasteafter_driver( command, options, buffer, clipboard );
	             break;
	        case CmdInsertBefore:
	             insertbefore_driver( command, options, buffer );
	             break;
	        case CmdInsertAfter:
	             insertafter_driver( command, options, buffer );
	             break;
	        case CmdInsertAt:
		     insertat_driver( command, options, buffer );
	             break;
	        case CmdSubstCurrent:
	             substcurrent_driver( command, options, buffer );
	             break;
	        case CmdSubstSeveral:
	             substseveral_driver( command, options, buffer );
	             break;
	        case CmdPrintSeveral:
	             printseveral_driver( command, options, buffer );
	             break;
	        case CmdPrintNumber: 
		     printnumber_driver( command, options, buffer ); 
		     break;
	        case CmdToggleDisplayLine: 
		     toggledisplayline_driver( command, options ); 
		     break;
                case CmdPrintLine: 
		     printline_driver( command, options, buffer ); 
		     break;
		case CmdPreviousLine: 
		     previousline_driver( command, options, buffer ); 
		     break;
                case CmdGoToLine: 
		     gotoline_driver( command, options, buffer ); 
		     break;
                case CmdGoToLast: 
		     gotolast_driver( command, options, buffer ); 
		     break;
		case CmdInvalid: 
		     invalid_driver( command ); 
		     break;
	    }

	    if( command.cmd != CmdNull )
	       	cmd_nbr++;

    } while(( command.cmd != CmdSaveQuit ) && ( command.cmd != CmdQuit ));
  

	// return to calling function
	return( retval );
}



//######################################################
//                                                                        
// Read Buffer Function 
//                                                                        
//######################################################
void readbuffer( BufferType &b, ifstream &infile )
{
	string textline;

	while( getline( infile, textline ))
		b.lines.InsertLast( textline );
}



//######################################################
//                                                                        
// Get Menu Selection Function                                            
//                                                                        
//######################################################
CommandType command_get()
{
	// local variables 
	CommandType command;
	string textline;
	string tempcommand;
	
	// initialize local variables
	command_init( command );
	textline = "";
	tempcommand = "";

	// read the whole line of text 
	getline( cin, textline );

	// clean up the string!
	textline = Trim( textline );

	// parse off the command and arguments
	tempcommand = Token( textline );
	command.arg1 = Token( textline );
	command.arg2 = Token( textline );
	command.arg3 = Token( textline );
	command.arg4 = Token( textline );
	command.extra = textline;
 
	// make the approipriate command selection
	if( tempcommand == STR_CMDNULL )
		command.cmd = CmdNull;
	else if( tempcommand == STR_CMDHELP )
		command.cmd = CmdHelp;
	else if( tempcommand == STR_CMDREAD )
		command.cmd = CmdRead;
	else if( tempcommand == STR_CMDWRITE )
		command.cmd = CmdWrite;
	else if( tempcommand == STR_CMDCHANGEBUFFERNAME )
		command.cmd = CmdChangeBufferName;
	else if( tempcommand == STR_CMDSAVEQUIT )
		command.cmd = CmdSaveQuit;
	else if( tempcommand == STR_CMDQUIT )
		command.cmd = CmdQuit;
	else if( tempcommand == STR_CMDNEXTLINE )
		command.cmd = CmdNextLine;
	else if( tempcommand == STR_CMDPRINTCURRENT )
		command.cmd = CmdPrintCurrent;
	else if( tempcommand == STR_CMDGOTOFIRST )
		command.cmd = CmdGoToFirst;
	else if( tempcommand == STR_CMDSEARCHBACK )
		command.cmd = CmdSearchBack;
	else if( tempcommand == STR_CMDSEARCHFRONT )
		command.cmd = CmdSearchFront;
	else if( tempcommand == STR_CMDCUT )
	        command.cmd = CmdCut;
	else if( tempcommand == STR_CMDCUTMULTIPLE )
         	command.cmd = CmdCutMultiple;
	else if( tempcommand == STR_CMDCOPY )
	        command.cmd = CmdCopy;
	else if( tempcommand == STR_CMDCOPYMULTIPLE )
	        command.cmd = CmdCopyMultiple;
	else if( tempcommand == STR_CMDPASTEBEFORE )
	        command.cmd = CmdPasteBefore;
	else if( tempcommand == STR_CMDPASTEAFTER )
	        command.cmd = CmdPasteAfter;
	else if( tempcommand == STR_CMDINSERTBEFORE )
	        command.cmd = CmdInsertBefore;
	else if( tempcommand == STR_CMDINSERTAFTER )
	        command.cmd = CmdInsertAfter;
	else if( tempcommand == STR_CMDINSERTAT )
	        command.cmd = CmdInsertAt;
	else if( tempcommand == STR_CMDSUBSTCURRENT )
	        command.cmd = CmdSubstCurrent;
	else if( tempcommand == STR_CMDSUBSTSEVERAL )
	        command.cmd = CmdSubstSeveral;
	else if( tempcommand == STR_CMDPRINTSEVERAL )
       	        command.cmd = CmdPrintSeveral;
	else if( tempcommand == STR_CMDPRINTNUMBER )
       	        command.cmd = CmdPrintNumber;
	else if( tempcommand == STR_CMDTOGGLEDISPLAYLINE )
       	        command.cmd = CmdToggleDisplayLine;
	else if( tempcommand == STR_CMDPRINTLINE )
       	        command.cmd = CmdPrintLine;
	else if( tempcommand == STR_CMDPREVIOUSLINE )
       	        command.cmd = CmdPreviousLine;
	else if( tempcommand == STR_CMDGOTOLINE )
       	        command.cmd = CmdGoToLine;
	else if( tempcommand == STR_CMDGOTOLAST )
       	        command.cmd = CmdGoToLast;
	else
		command.cmd = CmdInvalid;
  
	// return to calling function
	return( command );
}


//######################################################
//                                                                        
// Help Driver Function                                                   
//                                                                        
//######################################################
void help_driver()
{
  cout << left << setw(8) << "Command" << left << setw(25)
       << "Arguments" << left << setw(45) << "Description" << endl;
  cout << left << setw(8) << "h" << left << setw(25) << ""
       << left << setw(45) << "display help" << endl;
  cout << left << setw(8) << "r" << left << setw(25) << "name"
       << left << setw(45) << "read a file into current buffer" << endl;
  cout << left << setw(8) << "w" << left << setw(25) << ""
       << left << setw(45) << "write the current buffer to disk" << endl;
  cout << left << setw(8) << "f" << left << setw(25) << "name"
       << left << setw(45) << "change the name of current buffer" << endl;
  cout << left << setw(8) << "q" << left << setw(25) << ""
       << left << setw(45) << "quit the line editor" << endl;
  cout << left << setw(8) << "q!" << left << setw(25) << ""
       << left << setw(45) << "quit the line editor without saving" << endl;
  cout << left << setw(8) << "t" << left << setw(25) << ""
       << left << setw(45) << "go to the first line in the buffer" << endl;
  cout << left << setw(8) << "b" << left << setw(25) << ""
       << left << setw(45) << "go to the last line in the buffer" << endl;
  cout << left << setw(8) << "g" << left << setw(25) << "num"
       << left << setw(45) << "go to line num in the buffer" << endl;
  cout << left << setw(8) << "-" << left << setw(25) << ""
       << left << setw(45) << "go to the previous line" << endl;
  cout << left << setw(8) << "+" << left << setw(25) << ""
       << left << setw(45) << "go to the next line" << endl;
  cout << left << setw(8) << "=" << left << setw(25) << ""
       << left << setw(45) << "print the current line number" << endl;
  cout << left << setw(8) << left << "n" << setw(25) << ""
       << left << setw(45) << "toggle line number displayed" << endl;
  cout << left << setw(8) << "#" << left << setw(25) << ""
       << left << setw(45) << "print num of lines & chars in buffer" << endl;
  cout << left << setw(8) << left << "p" << setw(25) << ""
       << left << setw(45) << "print the current line" << endl;
  cout << left << setw(8) << "pr" << left << setw(25) << "start stop"
       << left << setw(45) << "print several lines" << endl;
  cout << left << setw(8) << "?" << left << setw(25) << "pattern"
       << left << setw(45) << "search backwards for a pattern" << endl;
  cout << left << setw(8) << "/" << left << setw(25) << "pattern"
       << left << setw(45) << "Search forwards for a pattern" << endl;
  cout << left << setw(8) << "s" << left << setw(25) << "text1 text2"
       << left << setw(45) << "subst text1 with text2 on current line" << endl;
  cout << left << setw(8) << "sr" << left << setw(25) 
       << "text1 text2 start stop"
       << left << setw(45) << "subst text1 with text2 on all lines" << endl;
  cout << left << setw(8) << "" << left << setw(25) << ""
       << left << setw(45) << "between start and stop" << endl;
  cout << left << setw(8) << "d" << left << setw(25) << ""
       << left << setw(45) << "CUT current line" << endl;
  cout << left << setw(8) << "dr" << left << setw(25) << "start stop"
       << left << setw(45) << "CUT several lines" << endl;
  cout << left << setw(8) << "c" << left << setw(25) << ""
       << left << setw(45) << "COPY current line" << endl;
  cout << left << setw(8) << "cr" << left << setw(25) << "start stop"
       << left << setw(45) << "COPY several lines" << endl;
  cout << left << setw(8) << "pb" << left << setw(25) << ""
       << left << setw(45) << "PASTE before current line" << endl;
  cout << left << setw(8) << "pa" << left << setw(25) << ""
       << left << setw(45) << "PASTE after current line" << endl;
  cout << left << setw(8) << "ib" << left << setw(25) << ""
       << left << setw(45) << "insert new line before current line" << endl;
  cout << left << setw(8) << "ic" << left << setw(25) << ""
       << left << setw(45) << "insert new line at current line" << endl;
  cout << left << setw(8) << "ia" << left << setw(25) << ""
       << left << setw(45) << "insert new line after current line" << endl;
}


//######################################################
//                                                                        
// Read Buffer Driver Function                              
//                                                                        
//######################################################
void read_driver( const CommandType &command, 
		  OptionsType &options, 
		  BufferType &buffer )
{
  // local variables
  ifstream infile;
  ofstream outFile;
  bool ok = true;
  string textline;
  char save;
  
  
  // check for correct number of arguments
  if(( command.arg1 != "" ) && 
     ( command.arg2 == "" ) &&
     ( command.arg3 == "" ) &&
     ( command.arg4 == "" ) &&
     ( command.extra == "" ))
    {
      // if dirty bit is set, prompt user to save
      if( buffer.dirty )
	{
	  cout << "Unsaved modifications in the buffer. "
	       << "Save? (y/n) ";
	  cin.get( save );
	  cin.ignore(); // ignore newline charatcter
	  save = tolower( save );

	  // make sure input is valid
	  while( !(save == 'y' || save == 'n') )
	    {
	      cout << "Only enter 'y' for yes or 'n' for no.\n"
		   << "Save? (y/n)?";
	      cin.get( save );
	      cin.ignore(); // ignore newline character
	      save = tolower( save );
	    }
	  
	  // if the user chooses to save...
	  if( save == 'y' )
	    {
	      // write contents of buffer to disk
	      // open the file
	      outFile.open( buffer.filespec.c_str(), ios::out );
	      
	      // Seek to the beginning
	      buffer.lines.Seek();
	  
	      // not at end of buffer
	      while( ok )
		{
		  // read each line and write to outFile
		  ok = buffer.lines.DataRead( textline );
		  if( !ok )
		    {
		      cout << "Error: could not read data"
			   << "from line "
			   << buffer.lines.CurrentIndex()+1
			   << endl;
		      return;
		    }
	      
		  outFile << textline << endl;
		  ok = buffer.lines.Next();
		}
	      
	      // close the file
	      outFile.close();

	      buffer.dirty = false;
	    }
	}

      buffer.lines.Clear();

      // see if file exists
      if( !file_exists( command.arg1.c_str()) )
	cout << "File " << command.arg1 << " does not exist." << endl;
      else
	{
	  // open the file
	  infile.open( command.arg1.c_str(), ios::in );
	  
	  // read the text line into the file
	  readbuffer( buffer, infile );
	  
	  // done reading...seek to start of buffer
	  buffer.lines.Seek();
	  
	  // close the file
	  infile.close();
	      
	  buffer.filespec = command.arg1.c_str();

	  cout << "File " << buffer.filespec << " read." << endl;
	  cout << buffer.lines.Size() << " lines in buffer." << endl;

	  // set dirty bit
	  buffer.dirty = false;
	}
    }
  else
    cout << "Incorrect number of arguments for read command" << endl;
}

//######################################################
//                                                                        
// Write Buffer Driver Function                              
//                                                                        
//######################################################
void write_driver( const CommandType &command,
		   OptionsType &options, 
		   BufferType &buffer )
{	
  // local variables
  ofstream outFile;
  bool ok = true;
  string textline;
	
  // check for correct number of arguments
  if(( command.arg1 == "" ) && 
     ( command.arg2 == "" ) &&
     ( command.arg3 == "" ) &&
     ( command.arg4 == "" ) &&
     ( command.extra == "" ))
    {
      if( buffer.lines.IsEmpty() )
	{
	  cout << "Buffer is empty" << endl;
	  return;
	}

      if( buffer.dirty )
        {
	  // open the file
	  outFile.open( buffer.filespec.c_str(), ios::out );
	  
	  // Seek to the beginning
	  buffer.lines.Seek();
	  
	  // not at end of buffer
	  while( ok )
	    {
	      // read each line and write to outFile
	      ok = buffer.lines.DataRead( textline );
	      if( !ok )
		{
		  cout << "Error: could not read data"
		       << "from line "
		       << buffer.lines.CurrentIndex()+1
		       << endl;
		  return;
		}
	      
	      outFile << textline << endl;
	      ok = buffer.lines.Next();
	    }
	  
	  // close the file
	  outFile.close();

	  // reset dirty bit
	  buffer.dirty = false;
	}
  
      else
	cout<<"No modifications in buffer... file is up to date" << endl;
    }
  else
    cout << "Incorrect number of arguments for write command" << endl;
}

//######################################################
//                                                                        
// Change Buffer Name Driver Function                              
//                                                                        
//######################################################
void changebuffername_driver( const CommandType &command, 
			      OptionsType &options, 
			      BufferType &buffer )
{
  if( command.arg1 == "" )
    cout << "Error: Change Buffer Name: No Argument" << endl;
  else if( command.arg2 != "" )
    cout << "Error: Change Buffer Name: Too Many Arguments" << endl;
  else
    buffer.filespec = command.arg1;
  
  cout << "Buffer name is: " << buffer.filespec << endl;
}


//######################################################
//                                                                        
// Save File and Quit Driver Function                                     
//                                                                        
//######################################################
void savequit_driver( const CommandType &command,
                      OptionsType &options, 
                      BufferType &buffer )
{
  // local variables
  char save;
	
  // check for correct number of arguments
  if( ( command.arg1 == "" ) && 
      ( command.arg2 == "" ) &&
      ( command.arg3 == "" ) &&
      ( command.arg4 == "" ) &&
      ( command.extra == "" ) )
    {
      // if the dirty bit is set, prompt user to save buffer to disk
      if( buffer.dirty )
	{
	  cout << "Unsaved modifications in the buffer. "
	       << "Save? (y/n) ";
	  cin.get( save );
	  save = tolower( save );

	  // make sure input is valid
	  while( !( save == 'y' || save == 'n') )
	    {
	      cout << "Only enter 'y' for yes or 'n' for no.\n"
		   << "Save? (y/n)?";
	      cin.get( save );
	      save = tolower( save );
	    }
	  
	  // if the user chooses to save...
	  if( save == 'y' )
	    {
	      // write contents of buffer to disk
	      write_driver( command, options, buffer );
	    }
	}
      // quit the program
      exit( 0 );
    }
  else
    cout << "Incorrect number of arguments for save/quit command" << endl;  
}


//######################################################
//                                                                        
// Quit Driver Function                                                   
//                                                                        
//######################################################
void quit_driver( const CommandType &command )
{
	exit( 0 );
}

//######################################################
//
// Next Line Driver Function
//
//######################################################
void nextline_driver( const CommandType &command,
		      OptionsType &options,
		      BufferType &buffer )
{
  // local variables
  bool ok = false;
	
  // check for correct number of arguments
  if(( command.arg1 == "" ) && 
     ( command.arg2 == "" ) &&
     ( command.arg3 == "" ) &&
     ( command.arg4 == "" ) &&
     ( command.extra == "" ))
    {
      // if buffer is not empty and not at last line, go to next lien
      if( buffer.lines.IsEmpty() )
	cout << "Buffer is empty" << endl;
      else if( buffer.lines.AtLast() )
	cout<< "Can't go to next line.. already at last line" <<endl;
      else
       	{
	  ok = buffer.lines.Next();
	  if( !ok )
	    {
	      cout <<"Fatal Error with list class... could not go to"
		   << "next line" << endl;
	    }
	}
    }		
  else
    cout << "Incorrect number of arguments for next command" << endl;
}	

//######################################################
//
// Print Current Driver Function
//
//######################################################
void printcurrent_driver( const CommandType &command,
			  OptionsType &options,
			  BufferType &buffer )
{
  // local variables
  bool ok = false;
  string current_line;
	
  // check for correct number of arguments
  if(( command.arg1 == "" ) && 
     ( command.arg2 == "" ) &&
     ( command.arg3 == "" ) &&
     ( command.arg4 == "" ) &&
     ( command.extra == "" ))
    {
      // if buffer is not empty read data from current line and display
      if( buffer.lines.IsEmpty() )
	cout << "Buffer is empty" << endl;
      else
	{
	  ok = buffer.lines.DataRead( current_line );
	  if( !ok )
	    cout << "Error: could not read line" << endl;
	  else
	    cout << current_line << endl;
	}
    }
  else
    cout << "Incorrect number of arguments for print command" << endl;
}

//######################################################
//
// Go To First Line Driver Function
//
//######################################################
void gotofirst_driver( const CommandType &command,
		       OptionsType &options,
		       BufferType &buffer )
{
  // local variables
  bool ok = false;
	
  // check for correct number of arguments
  if(( command.arg1 == "" ) && 
     ( command.arg2 == "" ) &&
     ( command.arg3 == "" ) &&
     ( command.arg4 == "" ) &&
     ( command.extra == "" ))
    {
      // if buffer is not empty and not at first line...
      if( buffer.lines.IsEmpty() )
	cout << "Buffer is empty" << endl;
      else if( buffer.lines.AtFirst() )
	cout << "Already at first line" << endl;
      // Seek to the first line of the buffer
      else
	{
	  ok = buffer.lines.Seek();
	  if( !ok )
	    {
	      cout <<"Fatal Error with list class... could not go to"
		   << "first line" << endl;
	    }
	}
    }		
  else
    cout << "Incorrect number of arguments for go to first line command" 
	 << endl;
}

//######################################################
//
// Search Backwards Driver Function
//
//######################################################
void searchback_driver( const CommandType &command,
			OptionsType &options,
			BufferType &buffer )
{
  // local variables
  bool ok = true;
  string textline;
  string arg1;
  size_t found; // to hold location of argument, if found
  int index = buffer.lines.CurrentIndex(); // hold current place in buffer

  // check for correct number of arguments
  if(( command.arg1 != "" ) && 
     ( command.arg2 == "" ) &&
     ( command.arg3 == "" ) &&
     ( command.arg4 == "" ) &&
     ( command.extra == "" ))
    {
      // just return to calling function if buffer is empty
      if( buffer.lines.IsEmpty() )
	{
	  cout << "Buffer is empty" << endl;
	  return;
	}

      // convert argument to lower case
      arg1 = ToLower( command.arg1 );
      
      // pad with spaces (see readme file)
      arg1 = ' ' + arg1 + ' ';
      
      while( ok ) // while there are still lines to be searhed...
	{
	  // Read data from line and store in textline
	  ok = buffer.lines.DataRead( textline );
	  textline = ToLower( textline );  // convert to lower-case
	  textline = ' ' + textline + ' '; // pad line with spaces
	      
	  if( !ok )
	    {	
	      cout << "Error: could not read data from line "
		   << buffer.lines.CurrentIndex()+1 << endl;
	      return;
	    }

	  else
	    {
	      // Use find string class memeber function to search for 
	      // arg2 in textline & display position of each occurance
	      found = textline.find( arg1 );
	      if( found != string::npos ) 
		{
		  cout << command.arg1 << " found in line "
		       << buffer.lines.CurrentIndex()+1
		       << " at column " << found+1 <<endl;
		}

	      // after first occurance search starting at found+1 for more
	      while( found != string::npos )
		{
		  found = textline.find( arg1, found+1 );
		  if( found != string::npos ) 
		    {
		      cout << command.arg1 << " found in line "
			   << buffer.lines.CurrentIndex()+1
			   << " at column " << found+1 <<endl;
		    }
		}
	      found = 0;
	    }
	  ok = buffer.lines.Previous();
	}
      buffer.lines.Seek( index ); // go back to original place in buffer
    }
  else
    cout << "Incorrect number of arguments for search backward command" 
	 << endl;
}
			
//######################################################
//
// Seach Forwards Command Driver Functions
// 
//######################################################
void searchfront_driver( const CommandType &command,
			 OptionsType &options,
			 BufferType &buffer )
{
  // local variables
  bool ok = true;
  string textline;
  string arg1;
  size_t found; // to hold position of argument, if found
  int index = buffer.lines.CurrentIndex(); // hold current place in buffer
	
  // check for correct number of arguments
  if(( command.arg1 != "" ) && 
     ( command.arg2 == "" ) &&
     ( command.arg3 == "" ) &&
     ( command.arg4 == "" ) &&
     ( command.extra == "" ))
    {
      // just return to calling function if buffer is empty
      if( buffer.lines.IsEmpty() )
	{
	  cout << "Buffer is empty" << endl;
	  return;
	}

      // convert argument to lower-case
      arg1 = ToLower( command.arg1 );
      
      // pad with spaces
      arg1 = ' ' + arg1 + ' ';
      
      while( ok ) // while there are still lines to be searhed...
	{
	  // Read data from line and store in textline
	  ok = buffer.lines.DataRead( textline );
	  textline = ToLower( textline );
	  textline = ' ' + textline + ' ';

	  if( !ok )
	    {	
	      cout << "Error: could not read data from line "
		   << buffer.lines.CurrentIndex()+1 << endl;
	      return;
	    }

	  else
	    {
	      // Use find string class memeber function to search for 
	      // arg1 in textline & display position of all ocurrances
	      found = textline.find( arg1 );
	      if( found != string::npos )
		{
		  cout << command.arg1 << " found in line "
		       << buffer.lines.CurrentIndex()+1
		       << " at column " << found+1 <<endl;
		}
	      // after first occurance, search for others starting at found+1
	      while( found != string::npos )
		{
		  found = textline.find( arg1, found+1 );
		  if( found != string::npos )
		    {
		      cout << command.arg1 << " found in line "
			   << buffer.lines.CurrentIndex()+1
			   << " at column " << found+1 <<endl;
		    }
		}
	      found = 0;
	    }
	  ok = buffer.lines.Next();
	}
      buffer.lines.Seek( index ); // go back to original place in buffer
    }
  else
    cout << "Incorrect number of arguments for search forward command" << endl;
}
	

//######################################################
//
// Cut Line Command Driver Function
//
//######################################################
void cut_driver( const CommandType &command,
                 OptionsType &options,
		 BufferType &buffer,
		 BufferType &clipboard )
{
  //local variables
  bool ok = true;
  string textline;

  // check argument number
  if(( command.arg1 == "" ) && 
     ( command.arg2 == "" ) &&
     ( command.arg3 == "" ) &&
     ( command.arg4 == "" ) &&
     ( command.extra == "" ))
    {
      // if empty, just return
      if( buffer.lines.IsEmpty() )
	{
	  cout << "Buffer is empty" << endl;
	  return;
	}
	  
      // read data from current line
      ok = buffer.lines.DataRead( textline );

      if (!ok)
	{
	  cout << "Error: could not read data from line "
	       << buffer.lines.CurrentIndex()+1 << endl;
	  return;
	}
	  
      // flush the clipboard
      clipboard.lines.Clear();

      // insert new line into clipboard, containing data read from line
      ok = clipboard.lines.InsertFirst( textline );
      if( !ok )
	{
	  cout << "Could not copy line to clibpboard." << endl;
	  return;
	}

      // delete the current line
      buffer.lines.DeleteAt();
      
      // set dirty bit
      buffer.dirty = true;
    }
  else
    cout << "Incorrect number of arguments for cut command" << endl;
}  


//######################################################
//
// Cut Multiple Lines Driver Function
//
//######################################################
void cutmultiple_driver( const CommandType &command,
                 OptionsType &options,
		 BufferType &buffer,
		 BufferType &clipboard )
{
  // local variables
  bool ok = true;
  string textline; // to hold data from buffer temporarily
  int arg1, // to hold value of arg1 as int type
      arg2, // to hold value of arg2 as int type
      index = buffer.lines.CurrentIndex(); // save current spot in buffer

  // check argument number
  if(( command.arg1 != "" ) && 
     ( command.arg2 != "" ) &&
     ( command.arg3 == "" ) &&
     ( command.arg4 == "" ) &&
     ( command.extra == "" ))
    {
      // if buffer is empty, just return
      if( buffer.lines.IsEmpty() )
	{
	  cout << "Buffer is empty" << endl;
	  return;
	}

      // check if arguments are numeric
      if( !IsNumeric( command.arg1 ) )
	{
	  cout << "First argument must be numeric" << endl;
	  return;
	}

      if( !IsNumeric( command.arg2 ) )
	{
	  cout << "Second argument must be numeric" << endl;
	  return;
	}
     
      // store values of arg1 and arg2
      arg1 = atoi( command.arg1.data() );
      arg2 = atoi( command.arg2.data() );

      // check if arguments are valid
      if( arg1 < 1 || arg2 > buffer.lines.Size() )
	{
	  cout << "Invalid argument values" << endl;
	  return;
	}
     
      // go to line in buffer indicated by arg1
      ok = buffer.lines.Seek( arg1-1 );
      if( !ok )
	{
	  cout << "Fatal error with list class... could not seek to line "
	       << arg1 << endl;
	  return;
	}
      
      // flush the clipboard
      clipboard.lines.Clear();
      
      // copy lines in buffer between arg1 and arg2 (inclusive) to clipboard
      for( int i = 0; i < ((arg2-arg1)+1); i++ )
	{
	  ok = buffer.lines.DataRead( textline );
	  if (!ok)
	    {
	      cout << "Error: could not read data from line "
		   << buffer.lines.CurrentIndex()+1 << endl;
	      return;
	    }
	  ok = clipboard.lines.InsertLast( textline );
	  if( !ok )
	    {
	      cout << "Error: could not copy line "
		   << buffer.lines.CurrentIndex()+1 
		   << " to clipboard." << endl;
	      return;
	    }
	  
	  // delete line after it is copied, this puts you at next line
	  // in buffer
	  ok = buffer.lines.DeleteAt();
	  if( !ok )
	    {
	      cout << "Error: could not delete line "
		   << buffer.lines.CurrentIndex()+1 << endl;
	      return;
	    }
	}

      // go back to original line in buffer
      buffer.lines.Seek( index );

      // set dirty bit
      buffer.dirty = true;
    }
  else
    cout << "Incorrect number of arguments for cut multiple command"
	 << endl;
}


//######################################################
//
// Copy Line Command Driver Function
//
//######################################################
void copy_driver( const CommandType &command,
                 OptionsType &options,
		 BufferType &buffer,
		 BufferType &clipboard )
{
  // local variables
   bool ok = true;
   string textline;

   // check number of arguments
   if(( command.arg1 == "" ) && 
      ( command.arg2 == "" ) &&
      ( command.arg3 == "" ) &&
      ( command.arg4 == "" ) &&
      ( command.extra == "" ))
     {
       // if buffer empty, return
       if( buffer.lines.IsEmpty() )
	{
	  cout << "Buffer is empty" << endl;
	  return;
	}

       // read data from current line
       ok = buffer.lines.DataRead( textline );

       if (!ok)
	 {
	   cout << "Error: could not read data from line "
		<< buffer.lines.CurrentIndex()+1 << endl;
	   return;
	 }

       // flush clipboard
       clipboard.lines.Clear();

       // insert new line in clipboard containing data read from buffer
       ok = clipboard.lines.InsertLast( textline );
       if( !ok )
	 {
	   cout << "Could not copy line to clipboard" << endl;
	 }
    }
  else
    cout << "Invalid number of arguments for copy command;" << endl;
}


//######################################################
//
// Copy Multiple Lines Command Driver Function
//
//######################################################
void copymultiple_driver( const CommandType &command,
                 OptionsType &options,
		 BufferType &buffer,
		 BufferType &clipboard )
{
  // local variables
  bool ok = true;
  string textline;
  int arg1, // to store value of arg1 as int type
      arg2, // to store value of arg2 as int type
      index = buffer.lines.CurrentIndex(); // save current spot in buffer

  // check argument number
  if(( command.arg1 != "" ) && 
     ( command.arg2 != "" ) &&
     ( command.arg3 == "" ) &&
     ( command.arg4 == "" ) &&
     ( command.extra == "" ))
    { 
      if( buffer.lines.IsEmpty() )
	{
	  cout << "Buffer is empty" << endl;
	  return;
	}

      // check if arguements are numeric
      if( !IsNumeric( command.arg1 ) )
	{
	  cout << "First argument must be numeric" << endl;
	  return;
	}

      if( !IsNumeric( command.arg2 ) )
	{
	  cout << "Second argument must be numeric" << endl;
	  return;
	}
      
      // store values of arg1 and arg2
      arg1 = atoi( command.arg1.data() );
      arg2 = atoi( command.arg2.data() );

      // check if arguments are valid
      if( arg1 < 1 || arg2 > buffer.lines.Size() )
	{
	  cout << "Invalid argument values" << endl;
	  return;
	}
      
      // go to the line indicated by arg1
      ok = buffer.lines.Seek( arg1-1 );
      if( !ok )
	{
	  cout << "Fatal error with list class... could not seek to line "
	       << arg1 << endl;
	  return;
	}
      
      // flush the clipboard
      clipboard.lines.Clear();
      
      // copy data between arg1 line to arg2 line (inclusive) to clipboard
      for( int i = 0; i < ((arg2-arg1)+1); i++ )
	{
	  ok = buffer.lines.DataRead( textline );
	  if (!ok)
	    {
	      cout << "Error: could not read data from line "
		   << buffer.lines.CurrentIndex()+1 << endl;
	      return;
	    }
	  ok = clipboard.lines.InsertLast( textline );
	  if( !ok )
	    {
	      cout << "Error: could not copy line "
		   << buffer.lines.CurrentIndex()+1 
		   << " to clipboard." << endl;
	      return;
	    }
	  buffer.lines.Next();
	}
     
      // Go back to original line in buffer
      buffer.lines.Seek( index );
      
      // set dirty bit
      buffer.dirty = true;
    }
  else
    cout << "Incorrect number of arguments for copy multiple command"
	 << endl;
}


//######################################################
//
// Paste Before Command Driver Function
//
//######################################################
void pastebefore_driver(  const CommandType &command,
			  OptionsType &options,
			  BufferType &buffer,
			  BufferType &clipboard )
{
  // local variables
   bool ok = true;
   string textline;

   // check argument number
   if(( command.arg1 == "" ) && 
      ( command.arg2 == "" ) &&
      ( command.arg3 == "" ) &&
      ( command.arg4 == "" ) &&
      ( command.extra == "" ))
     {
       if( buffer.lines.IsEmpty() )
	{
	  cout << "Buffer is empty" << endl;
	  return;
	}

       if( clipboard.lines.IsEmpty() )
	 cout << "Nothing in clipboard." << endl;
       else
	 {
	   // seek to end of clipboard
	   clipboard.lines.Seek( clipboard.lines.Size()-1 );
	   
	   // while there are still lines to be read...
	   while( ok )
	     {
	       // read data from current line
	       ok = clipboard.lines.DataRead( textline );
	       if( !ok )
		 {
		   cout << "Error: could not read data from clipboard."
			<< endl;
		   return;
		 }

	       // insert before current line
	       ok = buffer.lines.InsertAt( textline );
	       if( !ok )
		 {
		   cout << "Error: could copy data to buffer." << endl;
		   return;
		 }
	       
	       // go to previous line in clipboard
	       ok = clipboard.lines.Previous();
	     }

	   // set dirty bit 
	   buffer.dirty = true;
	 }
     }
   else 
     cout << "Incorrect number of arguments for paste before command" << endl;
}
	

//######################################################
//
// Paste After Command Driver Function
//
//######################################################
void pasteafter_driver( const CommandType &command,
			OptionsType &options,
			BufferType &buffer,
		        BufferType &clipboard )
{
  // local variables
   bool ok = true;
   string textline;

   // check argument number
   if(( command.arg1 == "" ) && 
      ( command.arg2 == "" ) &&
      ( command.arg3 == "" ) &&
      ( command.arg4 == "" ) &&
      ( command.extra == "" ))
     {
       if( buffer.lines.IsEmpty() )
	{
	  cout << "Buffer is empty" << endl;
	  return;
	}

       if( clipboard.lines.IsEmpty() )
	 cout << "Nothing in clipboard." << endl;
       else
	 {
	   // if not at the end of the buffer...
	   if( !buffer.lines.AtLast() )
	     {
	       // go to the next line in buffer
	       buffer.lines.Next();

	       // go to the last line in clipboard
	       clipboard.lines.Seek( clipboard.lines.Size()-1 );
	       
	       // while there are still lines to be read...
	       while( ok )
		 {
		   // read current line in clipboard
		   ok = clipboard.lines.DataRead( textline );
		   if( !ok )
		     {
		       cout << "Error: could not read data from clipboard."
			    << endl;
		       return;
		     }

		   // insert before current line
		   ok = buffer.lines.InsertAt( textline );
		   if( !ok )
		     {
		       cout << "Error: could not copy data to buffer." << endl;
		       return;
		     }

		   // go to previous line in clipboard
		   ok = clipboard.lines.Previous();
		 }
	       // set dirty bit
	       buffer.dirty = true;
	     }
	   else // at the end of the buffer...
	     {
	       // go to beginning of clipboard
	       clipboard.lines.Seek();
	       
	       while( ok ) // while still lines to be read...
		 {
		   // read current line
		   ok = clipboard.lines.DataRead( textline );
		   if( !ok )
		     {
		       cout << "Error: could not read data from clipboard."
			    << endl;
		       return;
		     }

		   // insert after the last line
		   ok = buffer.lines.InsertLast( textline );
		   if( !ok )
		     {
		       cout << "Error: could not copy data to buffer." << endl;
		       return;
		     }
		   ok = clipboard.lines.Next();
		 }

	       // set dirty bit
	       buffer.dirty = true;
	     }
	 }
     }
   else 
     cout << "Incorrect number of arguments for paste after command" << endl;
}


//#####################################################
// 
// Insert Line Before Command Driver Function
//
//#####################################################
void insertbefore_driver( const CommandType &command,
			  OptionsType &options,
			  BufferType &buffer )
{
  // local variables
  string textline;
  bool ok = true;
  
  // check argument number
  if(( command.arg1 == "" ) && 
      ( command.arg2 == "" ) &&
      ( command.arg3 == "" ) &&
      ( command.arg4 == "" ) &&
      ( command.extra == "" ))
     {
       // get the line to be inserted
       cout << "Enter a line of text to insert before the current line:\n ";
       getline( cin, textline, '.' ); // use period as delimitor
       cin.ignore(); // ignore newline character
       textline = textline + '.'; // put period back onto sentence

       if( buffer.lines.IsEmpty() )
	 {
	   ok = buffer.lines.InsertLast( textline );
	   if( !ok )
	     {
	       cout << "Error: could not insert line" << endl;
	       return;
	     }
	 }
       else
	 {
	   // insert before current line
	   ok = buffer.lines.InsertAt( textline );
	   if( !ok )
	     {
	       cout << "Error: could not insert line" << endl;
	       return;
	     }
	 }
	
       // set dirty bit
       buffer.dirty = true;
     }
  else
    cout << "Incorrect number of arguments for insert before function" << endl;
}


//######################################################
//
// Insert After Command Driver Function
//
//######################################################
void insertafter_driver( const CommandType &command,
			  OptionsType &options,
			  BufferType &buffer )
{
  // local variables
  string textline;
  bool ok = true;
  
  // check argument number
  if(( command.arg1 == "" ) && 
     ( command.arg2 == "" ) &&
     ( command.arg3 == "" ) &&
     ( command.arg4 == "" ) &&
     ( command.extra == "" ))
    {
      // get line to be inserted
      cout << "Enter a line of text to insert after the current line:\n ";
      getline( cin, textline, '.' );
      cin.ignore(); // ignore newline character
      textline = textline + '.'; // put period back onto sentence

      // insert after current line
      if( !buffer.lines.AtLast() )
	{
	  buffer.lines.Next();
	  ok = buffer.lines.InsertAt( textline );
	  if( !ok )
	    {
	      cout << "Error: could not insert line" << endl;
	      return;
	    }
	  
	  //set dirty bit
	  buffer.dirty = true;
	}
      else
	{
	  ok = buffer.lines.InsertLast( textline );
	  if( !ok )
	    {
	      cout << "Error: could not insert line" << endl;
	      return;
	    }
	  // set dirty bit
	  buffer.dirty = true;
	}
    }
  else
    cout << "Incorrect number of arguments for insert after current line "
	 << "command" << endl;
}


//######################################################
//
// Insert At Command Driver Function
//
//######################################################
void insertat_driver(  const CommandType &command,
		       OptionsType &options,
		       BufferType &buffer )
{
  // local variables
  string textline;
  bool ok = true;

  // check argument number
  if(( command.arg1 == "" ) && 
     ( command.arg2 == "" ) &&
     ( command.arg3 == "" ) &&
     ( command.arg4 == "" ) &&
     ( command.extra == "" ))
    {
      // get line to be inserted
      cout << "Enter a line of text to insert at the current line:\n ";
      getline( cin, textline, '.' );
      cin.ignore(); // ignore newline character
      textline = textline + '.'; // put period back onto sentence

      // if buffer is empty, insert new first line
      if( buffer.lines.IsEmpty() )
	{
	  ok = buffer.lines.InsertLast( textline );
	  if( !ok )
	    {
	      cout << "Error: could not insert line" << endl;
	      return;
	    }
	}
      // else write data to current line
      else
	buffer.lines.DataWrite( textline );
    }
  else
    cout << "Incorrect number of arguments for insert at current line"
	 << " command" << endl;
}


//######################################################
//
// Substitute Text on Current Line Command Driver Function
//
//######################################################
void substcurrent_driver( const CommandType &command, 
			 OptionsType &options,
			 BufferType &buffer )
{
  // local variables
  bool ok = true;
  string textline;
  string arg1,arg2;
  size_t found = 0;
  
  // check for correct number of arguments
  if(( command.arg1 != "" ) && 
     ( command.arg2 != "" ) &&
     ( command.arg3 == "" ) &&
     ( command.arg4 == "" ) &&
     ( command.extra == "" ))
    {
      if( buffer.lines.IsEmpty() )
	{
	  cout << "Buffer is empty" << endl;
	  return;
	}

      // conver arguments to lower and pad with spaces
      arg1 = ToLower( command.arg1 );
      arg2 = ToLower( command.arg2 );

      arg1 = ' ' + arg1 + ' ';
      arg2 = ' ' + arg2 + ' ';

      // Read data from line and store in textline
      ok = buffer.lines.DataRead( textline );
      textline = ToLower( textline );
      textline = ' ' + textline + ' ';
  
      if( !ok )
	{	
	  cout << "Error: could not read data from line "
	       << buffer.lines.CurrentIndex()+1 << endl;
	  return;
	}
      
      // Use find string class memeber function to search for 
      // arg1 in textline, replacing all occurances with arg2
      // using erase and insert string class member functions
      while( found != string::npos )
	{
	  found = textline.find( arg1 );
	  if( found != string::npos )
	    {
	      textline.insert( found, arg2 );
	      textline.erase( found+arg2.length(), arg1.length() );
	      buffer.dirty = true;
	    }
	}

      // remove spaces before writing data back to line
      textline = Trim( textline );
      ok = buffer.lines.DataWrite( textline );
      if( !ok )
	cout << "Error: could not write data." << endl;
    }
  else
    cout << "Incorrect number of arguments for substitute command." << endl;
}

//######################################################
//
// Substitute Text on Several Lines Command Driver Function
//
//######################################################
void substseveral_driver( const CommandType &command, 
			 OptionsType &options,
			 BufferType &buffer )
{
  // local variables
  bool ok = false;
  string textline, arg1,arg2;
  int arg3, arg4;
  size_t found = 0;
  int index = buffer.lines.CurrentIndex(); // hold current place in buffer
 
	
  // check for correct number of arguments
  if(( command.arg1 != "" ) && 
     ( command.arg2 != "" ) &&
     ( command.arg3 != "" ) &&
     ( command.arg4 != "" ) &&
     ( command.extra == "" ))
    {
      if( buffer.lines.IsEmpty() )
	{
	  cout << "Buffer is empty" << endl;
	  return;
	}

      // convert args to lower case and pad with spaces
      arg1 = ToLower( command.arg1 );
      arg2 = ToLower( command.arg2 );
      arg3 = atoi( command.arg3.data() );
      arg4 = atoi( command.arg4.data() );
      
      arg1 = ' ' + arg1 + ' ';
      arg2 = ' ' + arg2 + ' ';

      // Seek to line indicated by arg3
      ok = buffer.lines.Seek( arg3-1 );
      if( !ok )
	{
	  cout <<"Fatal Error with list class... could not go to"
	       << "start line" << endl;
	  return;
	}
      else
	{
	  for( int i = 0; i < ((arg4-arg3)+1); i++ )
	    {
	      // Read data from line and store in textline
	      ok = buffer.lines.DataRead( textline );
	      textline = ToLower( textline );
	      textline = ' ' + textline + ' ';
	      
	      if( !ok )
		{	
		  cout << "Error: could not read data from line "
		       << buffer.lines.CurrentIndex()+1 << endl;
		  return;
		}

	      else
		{
		  // Use find string class memeber function to search for 
		  // arg1 in textline, replacing all occurances with arg2
		  // using erase and insert string class member functions
		  while( found != string::npos )
		    {
		      found = textline.find( arg1 );
		      if( found != string::npos )
			{
			  textline.insert( found, arg2 );
			  textline.erase( found+arg2.length(), arg1.length() );
			  buffer.dirty = true;
			}
		    }
		  found = 0;
		  textline = Trim( textline );
		  buffer.lines.DataWrite( textline );
		}
	      buffer.lines.Next();
	    }
	  buffer.lines.Seek( index ); // go back to original place
	}
    }
  else 
    cout << "Incorrect number of arguments for substitute several command."
	 << endl;
}


//######################################################
//
// Print Several Lines Driver Function
//
//######################################################
void printseveral_driver( const CommandType &command,
			  OptionsType &options,
			  BufferType &buffer )
{
  // local variables
  bool ok = false;
  string current_line;
  int arg1, arg2;
  int index = buffer.lines.CurrentIndex(); // place holder
	
  // check for correct number of arguments
  if(( command.arg1 != "" ) && 
     ( command.arg2 != "" ) &&
     ( command.arg3 == "" ) &&
     ( command.arg4 == "" ) &&
     ( command.extra == "" ))
    {
      // check if arguements are numeric
      if( !IsNumeric( command.arg1 ) )
	{
	  cout << "First argument must be numeric" << endl;
	  return;
	}

      if( !IsNumeric( command.arg2 ) )
	{
	  cout << "Second argument must be numeric" << endl;
	  return;
	}
      
      // store values of arg1 and arg2
      arg1 = atoi( command.arg1.data() );
      arg2 = atoi( command.arg2.data() );

      // check if arguments are valid
      if( arg1 < 1 || arg2 > buffer.lines.Size() )
	{
	  cout << "Invalid argument values" << endl;
	  return;
	}

      // if buffer is not empty...
      if( buffer.lines.IsEmpty() )
	cout << "Buffer is empty" << endl;
      else
	{
	  // seek to first argument
	  buffer.lines.Seek( arg1-1 );

	  // print each line until & including arg2
	  for( int i = 0; i < ((arg2-arg1)+1); i++)
	    {
	      ok = buffer.lines.DataRead( current_line );
	      if( !ok )
		{
		  cout << "Error: could not read line" 
		       << buffer.lines.CurrentIndex()+1 << endl;
		}
	      else
		cout << current_line << endl;

	      buffer.lines.Next();
	    }

	  // seek back to original position
	  buffer.lines.Seek( index );
	}
    }
  else
    cout << "Incorrect number of arguments for print command" << endl;
}


//######################################################
//
// Print Number Command Driver Function
//
//######################################################
void printnumber_driver( const CommandType &command,
			 OptionsType &options,
			 BufferType &buffer )
{
  // local variables
  int lines, characters = 0;
  string textline, withoutSpaces;
  int index = buffer.lines.CurrentIndex();
  
  // check for correct number of arguments
  if(( command.arg1 == "" ) && 
     ( command.arg2 == "" ) &&
     ( command.arg3 == "" ) &&
     ( command.arg4 == "" ) &&
     ( command.extra == "" ))
    {
      if( buffer.lines.IsEmpty() )
	cout << "Buffer is empty." << endl;
      else
	{
	  // use Size() for number of lines
	  lines = buffer.lines.Size();

	  // for characters, use Token function to get number of characters
	  // for each line & add to characters variable one at a time
	  for(int i = 0; i < lines; i++ )
	    {
	      buffer.lines.DataRead( textline );
	      
	      withoutSpaces = "";

	      while( textline.length() > 0 )		
		  withoutSpaces += Token( textline );		 	       

	      characters += withoutSpaces.length();
	      buffer.lines.Next();
	    }

	  // display lines and characters numbers
	  cout << "Lines: " << lines << endl;
	  cout << "Characters: " << characters << endl;

	  // seek back to original place
	  buffer.lines.Seek( index );
	}
    }
  else
    cout << "Incorrect number of arguments for print number command." << endl;
}
	   
	      
//######################################################
//
// Toggle Display Line Number Function
//
//######################################################
void toggledisplayline_driver( const CommandType &command,
			      OptionsType &options )
{
  // check for correct number of arguments
  if(( command.arg1 == "" ) && 
     ( command.arg2 == "" ) &&
     ( command.arg3 == "" ) &&
     ( command.arg4 == "" ) &&
     ( command.extra == "" ))
    {
      if( options.display_linenumber )
	options.display_linenumber = false;
      else
	options.display_linenumber = true;
    }
  else
    cout << "Incorrect number of arguments for toggle display line number"
	 << " command." << endl;
}


//######################################################
//                                                                        
// Print Current Line Command Driver Function            
//                                                                        
//######################################################
void printline_driver( const CommandType &command,
		       OptionsType &options,
		       BufferType &buffer )
{
  // check for correct number of arguments
  if(( command.arg1 == "" ) && 
     ( command.arg2 == "" ) &&
     ( command.arg3 == "" ) &&
     ( command.arg4 == "" ) &&
     ( command.extra == "" ))
    {
      if( buffer.lines.IsEmpty() )
	cout << "Buffer is empty." << endl;
      
      else
	cout << "Current Line: " << buffer.lines.CurrentIndex()+1 << endl;
    }
  else
    cout << "Incorrect number of arguments for print current line command."
	 << endl;
}


//######################################################
//                                                                        
// Previous Line Command Driver Function            
//                                                                        
//######################################################
void previousline_driver( const CommandType &command,
		      OptionsType &options,
		      BufferType &buffer )
{
  // local variables
  bool ok = false;
	
  // check for correct number of arguments
  if(( command.arg1 == "" ) && 
     ( command.arg2 == "" ) &&
     ( command.arg3 == "" ) &&
     ( command.arg4 == "" ) &&
     ( command.extra == "" ))
    {
      if( buffer.lines.IsEmpty() )
	cout << "Buffer is empty" << endl;
      else if( buffer.lines.AtFirst() )
	cout<< "Can't go to previous line.. already at first line" <<endl;
      else
       	{
	  ok = buffer.lines.Previous();
	  if( !ok )
	    {
	      cout <<"Fatal Error with list class... could not go to"
		   << "previous line" << endl;
	    }
	}
    }		
  else
    cout << "Incorrect number of arguments for previous command" << endl;
}

//######################################################
//                                                                        
// Go To Line Command Driver Function            
//                                                                        
//######################################################
void gotoline_driver( const CommandType &command,
		      OptionsType &options,
		      BufferType &buffer )
{
  // local variables
  bool ok = false;
  int arg1;

  // check for correct number of arguments
  if(( command.arg1 != "" ) && 
     ( command.arg2 == "" ) &&
     ( command.arg3 == "" ) &&
     ( command.arg4 == "" ) &&
     ( command.extra == "" ))
    {
      
      // check if arguement is numeric
      if( !IsNumeric( command.arg1 ) )
	{
	  cout << "Argument must be numeric" << endl;
	  return;
	}
      
      // convert to int type
      arg1 = atoi( command.arg1.data() );


      // validate
      if( arg1 <= 0 || arg1 > buffer.lines.Size() )
	{
	  cout << "Invalid argument value." << endl;
	  return;
	}

      if( buffer.lines.IsEmpty() )
	cout << "Buffer is empty" << endl;
      else if( buffer.lines.CurrentIndex() == arg1-1 )
	cout << "Already at line " << arg1 << endl;
      else
       	{
	  // seek to that line
	  ok = buffer.lines.Seek( arg1-1 );
	  if( !ok )
	    {
	      cout <<"Fatal Error with list class... could not go to"
		   <<  "line " << arg1 << endl;
	    }
	}
    }		
  else
    cout << "Incorrect number of arguments for go to line command" << endl;
}


//######################################################
//                                                                        
// Go To Last Line Command Driver Function            
//                                                                        
//######################################################
void gotolast_driver( const CommandType &command,
		       OptionsType &options,
		       BufferType &buffer )
{
  // local variables
  bool ok = false;
	
  // check for correct number of arguments
  if(( command.arg1 == "" ) && 
     ( command.arg2 == "" ) &&
     ( command.arg3 == "" ) &&
     ( command.arg4 == "" ) &&
     ( command.extra == "" ))
    {
      if( buffer.lines.IsEmpty() )
	cout << "Buffer is empty" << endl;
      else if( buffer.lines.AtLast() )
	cout << "Already at last line" << endl;
      // Seek to the last line of the buffer
      else
	{
	  ok = buffer.lines.Seek( buffer.lines.Size()-1 );
	  if( !ok )
	    {
	      cout <<"Fatal Error with list class... could not go to"
		   << "last line" << endl;
	    }
	}
    }		
  else
    cout << "Incorrect number of arguments for go to last line command" 
	 << endl;
}


//######################################################
//                                                                        
// Invalid Command Driver Function                                        
//                                                                        
//######################################################
void invalid_driver( const CommandType &command )
{
	cout << "Invalid command" << endl;
}




