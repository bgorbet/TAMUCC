//######################################################
//
// Includes and Defines 
//
//######################################################
#ifndef _CPPSTRINGUTIL_H_
#define _CPPSTRINGUTIL_H_

#include <string>
using namespace std;

//######################################################
//
// Function Prototypes
//
//######################################################
string Reverse( const string &s );
string LTrim( const string &s, char trim_ch = ' ' );
string RTrim( const string &s, char trim_ch = ' ' );
string Trim( const string &s, char trim_ch = ' ' );
string Token( string &s, string delimiter = " \t\n" );

bool IsAlpha( const string &s );
bool IsNumeric( const string &s );
bool IsHexNumeric( const string &s );
bool IsAlphaNumeric( const string &s );
bool IsSpace( const string &s );
bool IsWhiteSpace( const string &s );
bool IsUpperCase( const string &s );
bool IsLowerCase( const string &s );
bool IsPunctuation( const string &s );

string ToLower( const string &s );
string ToUpper( const string &s );

//######################################################
//######################################################
#endif // _CPPSTRINGUTIL_H_














