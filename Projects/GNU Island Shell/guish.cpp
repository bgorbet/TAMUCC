//*********************************************************
//
// Annie Gorbet
// Operating Systems
// Project #1: New Island Shell - Writing Your Own Shell
// Due: October 3, 2012
// Instructor: Dr. Ajay Katangur
//
//*********************************************************


//*********************************************************
//
// Includes and Defines
//
//*********************************************************
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <cstdlib>
#include <deque>
#include <string>

using namespace std;


//*********************************************************
//
// Extern Declarations
//
//*********************************************************
using namespace std;
extern "C"
{
  extern char **gettoks();
} 

//*********************************************************
//
// Enum Declarations
//
//*********************************************************
enum PipeRedirect {PIPE, REDIRECT_IN, REDIRECT_OUT, NEITHER};

//*********************************************************
//
// Global Variables
//
//*********************************************************
int interruptcounter = 0; // Total interrupts
int int_interruptcounter = 0; // SIGINT interrupts
int stp_interruptcounter = 0; // SIGNSTP interrupts
int quit_interruptcounter = 0; // SIGQUIT inturrupts
int arg_count = 0; // number of arguments in command
bool internal_cmd = false;

//*********************************************************
//
// Function Prototypes
//
//*********************************************************

void myPromptFunction ();
void myCreateHistFunction ( char **toks, deque<string> &hist_deque );
PipeRedirect parse_pipe_redirect ( char **toks, char **cmd1, char **cmd2 );
void myInternalCommands( char **toks, deque<string> &hist_deque, 
                         PipeRedirect &pipe_redirect );
void myHistFunction ( deque<string> &hist_deque );
void rFunction ( char **toks, deque<string> &hist_deque );
void myCDFunction ( char **toks );
void myExitFunction ( char **toks, char **cmd1, char **cmd2 );

//*********************************************************
//
// Signal Trapping Functions
//
//*********************************************************

void int_handler ( int signo )
{
  interruptcounter++;
  int_interruptcounter++;
}

void stp_handler ( int signo )
{
  interruptcounter++;
  stp_interruptcounter++;
}

void quit_handler ( int signo )
{
  interruptcounter++;
  quit_interruptcounter++;
}

//*********************************************************
//
// Main Function
//
//*********************************************************
int main( int argc, char *argv[] )
{
  // local variables
  char **toks;
  int retval;
  deque<string> hist_deque;  // container for up to last 10 commands
  char **cmd1, **cmd2; // for splitting tokens in case of pipe or redirect
  PipeRedirect pipe_redirect; // indicates if there is pipe or redirect
  pid_t pid, pid2;
  int status, status2, error, pipefd[2];

  // initialize local variables
  cmd1 = new char*[100];
  cmd2 = new char*[100];
  retval = 0;
  pipe_redirect = NEITHER;

  for( int ii = 0; ii < 100; ii++ )
  {
    cmd1[ii] = NULL;
    cmd2[ii] = NULL;
  }

  // trap signals
  signal ( SIGINT, int_handler );
  signal ( SIGTSTP, stp_handler );
  signal ( SIGQUIT, quit_handler );

  // welcome
  cout << "Welcome to the New Island Shell" << endl;

  // main (infinite) loop
  while( true )
    {
      // assume each command is external initially
      internal_cmd = false;

      error = 0;

      // show prompt
      myPromptFunction ();

      // get arguments
      toks = gettoks();

      arg_count = 0;
      
      if( toks[0] != NULL )
      {
          // simple loop to keep track of args

          for( int ii=0; toks[ii] != NULL; ii++ )
          {
            arg_count++;
          }

          // check for exit command first

          if( !strcmp( toks[0], "exit" ))
				  {
            myExitFunction ( toks, cmd1, cmd2 );
          }
          
          // check for internal command and handle

          myInternalCommands( toks, hist_deque, pipe_redirect );          

          if( !internal_cmd )
          {        

            // check for pipe or redirect and split arguments accordingly

            pipe_redirect = parse_pipe_redirect( toks, cmd1, cmd2 ); 

            // fork process; returns child pid to parent, 0 to child

            pid = fork();

            if( pid < 0 )
            {
              // an error occurred

              perror( "fork()" );

              exit(-1);
            }
            else if( pid > 0 )
            {
              // this is the parent

              // wait for the child to terminate

              error = waitpid( -1, &status, 0 ); 

              if( error < 0 )
              {
                perror( "waitpid()" );
                exit( -1 );
              }

            }
            else
            {
              // this is the child

              if( pipe_redirect == NEITHER )
              {
                // execute the program

                error = execvp( toks[0], toks );

                if( error < 0 )
                {
                  perror( toks[0] );
                  exit( -1 );
                }
              }

              // if redirect, open file in cmd2 and redirect standard
              // input/output to file

              else if( pipe_redirect == REDIRECT_IN )
              {
                // open the input file

                int in = open( cmd2[0], O_RDONLY);

                // redirect input to file

                dup2( in, 0 );

                // execute the program

                error = execvp( cmd1[0], cmd1 );

                if( error < 0 )
                {
                  perror( cmd1[0] );
                  exit( -1 );
                }
              }

              else if( pipe_redirect == REDIRECT_OUT )
              {
                // open the file

                int out = open( cmd2[0], O_WRONLY | O_TRUNC | O_CREAT );

                // redirect output to the file

                dup2( out, 1 );

                // execute the program

                error = execvp( cmd1[0], cmd1 );

                if( error < 0 )
                {
                  perror( cmd1[0] );
                  exit( -1 );
                }
              }

              // if pipe, a pipe needs to be made, input/output needs to be
              // redirected to the appropriate ends of the pipe, and a second
              // child needs to get forked
 
              else if( pipe_redirect == PIPE )
              {
                // if pipe, make a pipe (fds go in pipefd[0] and pipefd[1])

                pipe( pipefd );

                // replace standard input with input part of pipe

                dup2( pipefd[0], 0 );

                // close unused half of pipe

                close( pipefd[1] );

                // execute cmd2

                error = execvp( cmd2[0], cmd2 );

                if( error < 0 )
                {
                  perror( cmd2[0] );
                  exit( -1 );
                }

                // fork again for the other program

                pid2 = fork();

                if( pid2 < 0 )
                {
                  perror( "fork()" );

                  exit( -1 );
                }

                else if( pid2 > 0 )
                {
                  // wait on the second child process

                  error = waitpid( -1, &status2, 0 );  

                  if( error < 0 )
                  {
                    perror( "waitpid()" );
                    exit( -1 );
                  }            
                }

                else
                {
                  // this is the second child

                  // replace standard output with the output part of pipe
                  
                  dup2( pipefd[1], 1 );

                  // close unused half of pipe

                  close( pipefd[0] );

                  // execute first command

                  error = execvp( cmd1[0], cmd1 );

                  if( error < 0 )
                  {
                    perror( cmd1[0] );
                    exit( -1 );
                  }
                }
              }
            }
          }

          // add arguments to history deque
          myCreateHistFunction( toks, hist_deque );
      }
    }

  // return to calling environment
  return( retval );
}

//*****************************************************
//
// Function Definitions
//
//*****************************************************

// ***Prompt Function***
//
// Prints the prompt
//

void myPromptFunction ()
{
  cout << "\n" << get_current_dir_name () << "$ ";
}

// ***My Internal Commands Function***
//
// Checks to see if the command is internal, if so it calls functions
// that handle each internal command.  Also sets values for certain 
// critical flags
//
// Return Value: none
//
// Value Parameters: none
//
// Reference Parameters: 
//
// toks - dynamic 2D array containing command tokens
// hist_deque - deque for holding command history
// pipe_redirect - enum that keeps track of pipe-redirect status
//
// Local Variables: none

void myInternalCommands( char **toks, deque<string> &hist_deque,
                         PipeRedirect &pipe_redirect )
{
  // no pipes or redirects in internal commands

  pipe_redirect = NEITHER;

  // check for the following internal commands

  if( !strcmp( toks[0], "hist" ))
  {
    myHistFunction ( hist_deque );

    // flip internal_cmd flag
    internal_cmd = true;
  }

  else if( !strcmp( toks[0], "r" )) 

    rFunction ( toks, hist_deque );
    // still need to fork some external cmd, so don't flip internal_cmd flag

  else if( !strcmp( toks[0], "cd" ) )
  {
      myCDFunction( toks );
      internal_cmd = true;
  }
}

// ***My Create History Function***
//
// Adds commands to the history deque
//
// Return Value: none
//
// Value Parameters: none
//
// Reference Parameters:
//
// toks - dynamic 2D array containing command tokens
// hist_deque - deque for holding command history
//
// Local Variables: 
//
// string command_string - string to hold command tokens

void myCreateHistFunction ( char **toks, deque<string> &hist_deque )
{
  string command_string; 

  // cycle through tokens and add to the command_string

  for( int ii = 0; toks[ii] != NULL; ii++ )
  {
    command_string += toks[ii];

    if( toks[ii+1] != NULL ) // don't want to add spaces to the end
    {
      command_string += ' '; // add spaces internally only
    }
  }

  // add commands to deque, unless they are r or exit

  if( !(!strcmp(toks[0], "r") || !strcmp(toks[0], "exit")) )
  {
    // the deque will not have more than 10 items

    if( hist_deque.size() < 10 )
    {
      hist_deque.push_back( command_string );
    }

    else
    {
      hist_deque.pop_front();
      hist_deque.push_back( command_string );
    }
  }
}

// ***Parse Pipe Redirect Function***
//
// Searches the command tokens for a pipe or redirect
//
// Return Value: PipeRedirect - enum that indicates the pipe redirect status
//                              (whether there is a pipe or redirect)
//
// Value Parameters:  none
//
// Reference Parameters:
//
// toks - dynamic 2D array containing command tokens
// cmd1 - dynamic 2D array which holds prog and args when there is a split
//        by pipe or redirect
// cmd2 - dynamic 2D array which holds prog and args (or a file) when there 
//        is a split by pipe or redirect
//
// Local Variables: 
//                           
// PipeRedirect result - returned to calling function, indicates whether
//                       pipe, redirect, or neither was found
// int split - integer that indicates the position of the pipe or redirect

PipeRedirect parse_pipe_redirect ( char **toks, char **cmd1, char **cmd2 )
{
  PipeRedirect result = NEITHER;
  int split = -1;

  // clear any values that may be in cmd1

  for( int ii = 0; cmd1[ii] != NULL; ii++ )
  {
    cmd1[ii] = NULL;
  }

  // clear any values that may be in cmd2

  for( int ii = 0; cmd2[ii] != NULL; ii++ )
  {
    cmd2[ii] = NULL;
  }

  // cycle through toks and look for pipe or redirect symbols

  for( int ii = 0; toks[ii] != NULL; ii++ )
  {

    if( !strcmp( toks[ii], "|" ))
    {
      result = PIPE;
      split = ii;
    }

    else if( !strcmp( toks[ii], "<" )) 
    {
      result = REDIRECT_IN;
      split = ii;
    }

    else if( !strcmp( toks[ii], ">"))
    {
      result = REDIRECT_OUT;
      split = ii;
    }
  }

  // Depending on what is found, the tokens are split up into cmd1 and cmd2

  if( result == PIPE )
  {
    // cmd2 gets the first program and its args

    for( int ii = 0; ii < split; ii++)
    { 
      cmd2[ii] = new char[100];
      strcpy( cmd2[ii], toks[ii] );
    }

    // cmd1 gets the second programs and its args

    int count = 0;
    for( int ii = split+1; toks[ii] != NULL; ii++ )
    {
      cmd1[count] = new char[100];
      strcpy( cmd1[count], toks[ii] );
      count++;
    }
  }

  else if( result == REDIRECT_OUT || result == REDIRECT_IN )
  {
    // for redirect, there are three different orders the program, symbol,
    // and file can occur in

    // case: prog [args] (>or<) file
    if( toks[split+2] == NULL )
    {
      for( int ii = 0; ii < split; ii++ )
      {
        cmd1[ii] = new char[100];
        strcpy( cmd1[ii], toks[ii] );
      }
      cmd2[0] = new char[100];
      strcpy( cmd2[0], toks[split+1] );
    }

    // case: prog [args] file (>or<)
    else if( toks[split+1] == NULL )
    {
      for( int ii = 0; ii < split-1; ii++ )
      {
        cmd1[ii] = new char[100];
        strcpy( cmd1[ii], toks[ii] );
      }
      cmd2[0] = new char[100];
      strcpy( cmd2[0], toks[split-1] );
    }

    // case: (>or<) prog [args] file 
    else if( split == 0 )
    {
      int count = 1;
      for( int ii = 1; toks[ii]!= NULL; ii++ )
      {
        count++; 
      }
      for( int ii = 0; ii < count-2; ii++ )
      {
        cmd1[ii] = new char[100];
        strcpy( cmd1[ii], toks[ii+1] );
      }
      cmd2[0] = new char[100];
      strcpy( cmd2[0], toks[count-1] );
    }
  }

  return result;
}

// ***My History Function***
//
// Simply displays the contents of the command history deque
//
// Return Value: none
//
// Value Parameters: none
//
// Reference Parameters: hist_deque - command history deque
//
// Local Variables: none

void myHistFunction ( deque<string> &hist_deque )
{
  cout << "Command history:" << endl;
 
  for( int ii = 0; ii < hist_deque.size(); ii++ )
  {
    cout << ii+1 << ": " << hist_deque.at(ii) << endl;
  }
}

// *** R Function***
//
// Implements the R command
//
// Return Value: none
//
// Value Parameters: none
//
// Reference Parameters:
//
// toks - dynamic 2D array containing command tokens
// hist_deque - deque for holding command history
//
// Local Variables:
//
// char ** char_array - dynamic 2D char array to hold tokens from strings 
//                      retrieved from the command history deque
// char * token - to contain single token from string retrieved from history 
//                deque
// string command - to contain string from the history deque
// int index - to hold command history number
// char[] cs_command - to hold c-string copy of command string
// int count - simple counter
// bool spaces - flag to determine if spaces in command string
// PipeRedirect temp - dummy arguement for internal commands function

void rFunction ( char **toks, deque<string> &hist_deque )
{
  // local variables

  char **char_array;  
  char *token; 
  string command;  
  int index; 
  char cs_command[100]; 
  int count;
  bool spaces = false; 
  PipeRedirect temp; 

  // memory allocation

  char_array = new char*[100];
  token = new char[100];

  for( int ii = 0; ii < 100; ii++ )
  {
    char_array[ii] = new char[100];
  }

  // first get a command string from the history deque

  // case 1: r with no command history number

  if( toks[1] == NULL )
  {
    // just retrieve the last string in the deque

    command = hist_deque.at( hist_deque.size()-1 );
  }

  // case 2: r with command history number

  else if( !strcmp( toks[1], "1" ) ||
           !strcmp( toks[1], "2" ) ||
           !strcmp( toks[1], "3" ) ||
           !strcmp( toks[1], "4" ) ||
           !strcmp( toks[1], "5" ) ||
           !strcmp( toks[1], "6" ) ||
           !strcmp( toks[1], "7" ) ||
           !strcmp( toks[1], "8" ) ||
           !strcmp( toks[1], "9" ) ||
           !strcmp( toks[1], "10" ) )
  {
    // get the index

    index = atoi( toks[1] ) - 1;

    // retrieve the specified 

    command = hist_deque.at( index );
  }

  // case 3: incorrect usage

  else
  {
    cout << "usage: r n, where n is command history number (1-10) or blank "
         << "for last command" << endl;
  }

  // convert command to a c-string using strcpy for it to work with strtok
  // because the c_str() method will not work in strtok

  strcpy( cs_command, command.c_str() );

  // determine if the command has multiple words

  for( int ii = 0; ii < strlen( cs_command ); ii++ )
  {
    if( cs_command[ii] == ' ' )
      spaces = true;
  }

  // if it does, tokenize it

  if( spaces )
  {
    // tokenize this string into char_array
    token = strtok( cs_command, " " );
    
    count = 0;
    while( token != NULL )
    {
      cerr << token << endl;
      strcpy( char_array[count], token );
      token = strtok ( NULL, " " );
      count++;
    }
  }

  // otherwise, just copy it into the char array

  else 
  {
    strcpy( char_array[0], cs_command );
  }

  // clear toks of the r n command

  toks[0] = NULL;
  toks[1] = NULL;

  // replace with char_array

  for( int ii = 0; strlen( char_array[ii] ) > 0; ii++ )
  {
    toks[ii] = new char[100];
    strcpy( toks[ii], char_array[ii] );
  }

  // check to see if r command was used to make another internal command

  myInternalCommands( toks, hist_deque, temp );

  // de-allocate memory

  for( int ii = 0; ii < 100; ii++ )
  {
    delete [] char_array[ii];
  }

  delete [] token;
}

// ***My CD Function***
//
// Changes the current working directory
//
// Return Value: none
// 
// Value Parameters: none
//
// Reference Paramters: toks - contains command tokens
//
// Local Variables:
//
// int retval - checks for errors returned from chdir()
// string current_path - to hold the current path
// string requested_path - to hold the requested path

void myCDFunction( char **toks )
{
  int retval;
  string current_path = get_current_dir_name(); // get current path
  string requested_path;

  requested_path = toks[1];

  // need to add this for cases when there is space(s) in file name

  if( toks[2] != NULL )
  {
    for( int ii = 2; toks[ii] != NULL; ii++ )
    {
      requested_path += " ";
      requested_path += toks[ii];
    }
  }

  // add the requested path

  string command_path = current_path + "/" + requested_path; 

  retval = chdir( command_path.c_str() ); // changes path to requested folder

  if( retval < 0 )
  {
    cout << "Error: cannot change directory" << endl;
  }
}

// ***My Exit Function***
//
// Displays interrupts, de-allocates memory, and exits the shell
//
// Return Value: none
//
// Value Parameters: none
//
// Reference Parameters: toks, cmd1, cmd2
//
// Local Variables: none

void myExitFunction ( char **toks, char **cmd1, char **cmd2 )
{
  // display inturrupts

  cout << "Total inturrupts: " << interruptcounter << endl;
  cout << "SIGINT inturrupts: " << int_interruptcounter << endl;
  cout << "SIGSTP inturrupts: " << stp_interruptcounter << endl;
  cout << "SIGQUIT inturrupts: " << quit_interruptcounter << endl;
  
  // de-allocate memory

  for( int ii=0; ii < arg_count; ii++ )
  {
    delete [] toks[ii];
  }

  for( int ii=0; cmd1[ii]!=NULL; ii++ )
  {
    delete [] cmd1[ii];
  }

  for( int ii=0; cmd2[ii]!=NULL; ii++ )
  {
    delete [] cmd2[ii];
  }

  // exit normally
  exit(0);
}
   



    
    

      

  

