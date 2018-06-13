//######################################################
//
// Includes and Defines 
//
//######################################################
#include <string>
#include <stringutil.h>
#include <cctype>
#include <iostream>
using namespace std;


//######################################################
//
// String Reverse Function 
//
//######################################################
string Reverse( const string &s )
{
  string t = s;
  int ii;
  int s_len = s.length();

  for( ii=0; ii<s_len; ii++ )
    t[ii] = s[ s_len - ii - 1 ];

  return( t );
}


//######################################################
//
// String Left Trim Function 
//
//######################################################
string LTrim( const string &s, char trim_ch /* = ' ' */ )
{
  // local variables
  string t = s;

  // remove all trim_ch characters from left
  t.erase( 0, t.find_first_not_of( trim_ch ));

  return( t );
}


//######################################################
//
// String Right Trim Function 
//
//######################################################
string RTrim( const string &s, char trim_ch /* = ' ' */)
{
  // local variables
  string t = s;

  // trim the right side by reversing the string and ltrimming
  t = Reverse( t );
  t = LTrim( t, trim_ch );
  t = Reverse( t );

  // return to calling function
  return( t );
}


//######################################################
//
// String Trim Function 
//
//######################################################
string Trim( const string &s, char trim_ch /* = ' ' */ )
{
  // local variables
  string t = s;

  // trim the left and right
  t = LTrim( t, trim_ch );
  t = RTrim( t, trim_ch );

  // return to calling function
  return( t );
}


//######################################################
//
// String Token Function 
//
//######################################################
string Token( string &s, string delimiter /* = " " */ )
{
  // note: s is modified!!!

  // local variables
  string token;
  unsigned int pos = 0;

  // remove all delimiter characters from left

  s.erase( 0, s.find_first_not_of( delimiter ));

  // get the token 
  pos = s.find_first_of( delimiter );
  token = s.substr( 0, pos );
  s.erase( 0, pos );

  // return to calling function
  return( token );
}


//######################################################
//
// String Is Alpha Function 
//
//######################################################
bool IsAlpha( const string &s )
{
  // local variables
  int s_length;
  int ii;
  bool retval;

  // initialize local variables
  s_length = s.length();
  ii = 0;
  retval = true;

  // test for alpha string
  for( ii=0; (ii<s_length) && (retval); ii++ )
    retval = ( isalpha( s[ii] )) ? true : false;

  // return to calling function 
  return( retval );
}


//######################################################
//
// String Is Numeric Function 
//
//######################################################
bool IsNumeric( const string &s )
{
  // local variables
  int s_length;
  int ii;
  bool retval;

  // initialize local variables
  s_length = s.length();
  ii = 0;
  retval = true;

  // test for numeric string
  for( ii=0; (ii<s_length) && (retval); ii++ )
    retval = ( isdigit( s[ii] )) ? true : false;

  // return to calling function 
  return( retval );
}


//######################################################
//
// String Is Hexadecimal Numeric Function 
//
//######################################################
bool IsHexNumeric( const string &s )
{
  // local variables
  int s_length;
  int ii;
  bool retval;

  // initialize local variables
  s_length = s.length();
  ii = 0;
  retval = true;

  // test for hex digit string
  for( ii=0; (ii<s_length) && (retval); ii++ )
    retval = ( isxdigit( s[ii] )) ? true : false;

  // return to calling function 
  return( retval );
}


//######################################################
//
// String Is Alphanumeric Function 
//
//######################################################
bool IsAlphaNumeric( const string &s )
{
  // local variables
  int s_length;
  int ii;
  bool retval;

  // initialize local variables
  s_length = s.length();
  ii = 0;
  retval = true;

  // test for alpha-numeric string
  for( ii=0; (ii<s_length) && (retval); ii++ )
    retval = ( isalnum( s[ii] )) ? true : false;

  // return to calling function 
  return( retval );
}


//######################################################
//
// String Is Space Function 
//
//######################################################
bool IsSpace( const string &s )
{
  // local variables
  int s_length;
  int ii;
  bool retval;

  // initialize local variables
  s_length = s.length();
  ii = 0;
  retval = true;

  // test for space string
  for( ii=0; (ii<s_length) && (retval); ii++ )
    retval = ( s[ii] == ' ' ) ? true : false;

  // return to calling function 
  return( retval );
}


//######################################################
//
// String Is White Space Function 
//
//######################################################
bool IsWhiteSpace( const string &s )
{
  // local variables
  int s_length;
  int ii;
  bool retval;

  // initialize local variables
  s_length = s.length();
  ii = 0;
  retval = true;

  // test for white space string
  for( ii=0; (ii<s_length) && (retval); ii++ )
    retval = ( isspace( s[ii] )) ? true : false;

  // return to calling function 
  return( retval );
}


//######################################################
//
// String Is Uppercase Function 
//
//######################################################
bool IsUpperCase( const string &s )
{
  // local variables
  int s_length;
  int ii;
  bool retval;

  // initialize local variables
  s_length = s.length();
  ii = 0;
  retval = true;

  // test for upper case alpha string
  for( ii=0; (ii<s_length) && (retval); ii++ )
    retval = ( isupper( s[ii] )) ? true : false;

  // return to calling function 
  return( retval );
}


//######################################################
//
// String Is Lowercase Function 
//
//######################################################
bool IsLowerCase( const string &s )
{
  // local variables
  int s_length;
  int ii;
  bool retval;

  // initialize local variables
  s_length = s.length();
  ii = 0;
  retval = true;

  // test for lower case alpha string
  for( ii=0; (ii<s_length) && (retval); ii++ )
    retval = ( islower( s[ii] )) ? true : false;

  // return to calling function 
  return( retval );
}


//######################################################
//
// String Is Punctuation Function 
//
//######################################################
bool IsPunctuation( const string &s )
{
  // local variables
  int s_length;
  int ii;
  bool retval;

  // initialize local variables
  s_length = s.length();
  ii = 0;
  retval = true;

  // test for punctuation string
  for( ii=0; (ii<s_length) && (retval); ii++ )
    retval = ( ispunct( s[ii] )) ? true : false;

  // return to calling function 
  return( retval );
}


//######################################################
//
// String To Lowercase Function 
//
//######################################################
string ToLower( const string &s )
{
  // local variables
  string t = s;
  int ii;
  int t_length = t.length();

  for( ii=0; ii<t_length; ii++ )
    t[ii] = tolower( t[ii] );

  return( t );
}


//######################################################
//
// String To Uppercase Function 
//
//######################################################
string ToUpper( const string &s )
{
  // local variables
  string t = s;
  int ii;
  int t_length = t.length();

  for( ii=0; ii<t_length; ii++ )
    t[ii] = toupper( t[ii] );

  return( t );
}





