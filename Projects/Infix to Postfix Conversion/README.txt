Contents of this directory:
i2p.cpp (main program source file)
ListType.h  (list class header file)
Makefile
README
Stack.h  (stack class header file)
stringutil.cpp (stringutil class implementation file)
stringutil.h  (stringutil class header file)
testInputs.txt (input data that tests all of the programs functions)


NOTES:	I changed the IsNumeric and IsAlpha member functions of the stringutil 
class so that if the last character in the string is a digit or letter, 
then they return true.  I did this so that negative numbers and letters in the 
expression would still be considered numeric/aphabetic by these functions.  
However, mixed alpha-numberics will still
cause an error because of the way that the parseWhiteSpace function is written.