This directory contains all the files required to compile and run the line 
editor program. The contents are: led.cpp, ListType.h, Makefile, stringutil.cpp
stringutil.h, this readme file.

Notes about solution:  I used the .find(), .erase(), and .insert() string 
class member functions to implement the search and substitute commands.  
In order to do this I had to pad the string arguments with spaces in order to
avoid finding "words within words."  Because of this, my led program will only
find and replace entire words and not partial words or words that are within 
or adjoined to other words.  I had to pad the lines with spaces after they
are read from the buffer also, in order for first and last words in the line
to be found.  In the case of the substitute commands, these spaces are removed
before the lines are written back into the buffer. 
       
