/******************************************************************************
 * 
 * Annie Gorbet
 * Data Structures
 * Project 3: Infix to Postfis Conversion and Evaluation
 * March 22, 2012
 * Instructor: Dr. Michael C. Scherger
 *
 *****************************************************************************/
#include<iostream>
#include<sstream>
#include<string>
#include<stringutil.h>
#include<Stack.h>

using namespace std;

/*****FUNCTION PROTOTYPES*****/
bool parseWhiteSpace( string expression, int start = 0 );
bool parseParens( string expression );
bool parseOperandNumber( string expression );
bool parseOperatorsOperands( string expression );
int priority( string token );
string convertExpression( string expression );
double StringToNumber( string &Text );
void evaluateExpression( string expression );


int main()
{
  // local variables
  string postfix, infix;
  bool noErrors;
  
  // get expression 
  while( getline( cin, infix ) )
    {
      infix = Trim( infix );

      noErrors = true; // assume no errors for each expression

      // parse to find any syntax errors
      if( !parseWhiteSpace( infix ) )
	noErrors = false;
      else if( !parseParens( infix ) )
	noErrors = false;
      else if( !parseOperandNumber( infix ) )
	noErrors = false;
      else if( !parseOperatorsOperands( infix ) )
	noErrors = false;
      
      if( noErrors )
	{
	  // dislplay expression in infix form
	  cout << "INFIX: " << infix << endl;

	  // convert to postfix
	  postfix = convertExpression( infix );

	  // display expression in postfix form
	  cout << "POSTFIX: " << postfix << endl;

	  // evaluate if numeric and display result
	  evaluateExpression( postfix );
	}
    }
	
  return( 0 );
}

/**************************************************************************
*
* parseWhiteSpace Function
*
* This function recursively checks each character in the expression to 
* see if it conforms to the syntax for white space placement.  White space 
* must be between all characters unless they are part of a non-single 
* digit and/or a negative digit/letter.
*
* Value Parameters:
* ------------------
* expression	  string       	 the expression being parsed
* start		  int		 index of the character currently being
*				 checked; starts at default value of 0
* Return:
* --------
* bool		  returns false only if base case 2, 3, or 4 is met
*
**************************************************************************/
bool parseWhiteSpace( string expression, int start /* = 0 */ )
{
  // base case 1: start reaches end of expression
  while( start < expression.length()-1 )
    {
	
      if( isdigit( expression[start] ) )
	{
	  // base case 2: if character is digit, next character
	  // is not another digit or a white space
	  if( !( isdigit( expression[start+1] ) 
		 || expression[start+1] == ' ' ) )
	    {
	      cout << "ERROR: white space needed between all elements" << endl;
	      return( false );
	    }
	  else
	    // recursive call
	    return( parseWhiteSpace( expression, start+1 ) );
	}
 
      else if( expression[start] == '('
	       || expression[start] == ')'
	       || expression[start] == '*'
	       || expression[start] == '/'
	       || expression[start] == '+'
	       || isalpha( expression[start] ) )
	{
	  // base case 2: if character is paren or operator (not -), 
	  // next character is not a white space
	  if( expression[start+1] != ' ' )
	    {
	      cout << "ERROR: white space needed between all elements" << endl;
	      return( false );
	    }
	  else
	    // recursive call
	    return( parseWhiteSpace( expression, start+1 ) );
	}
		
      else if( expression[start] == '-' )
	{
	  // base case 3: if character is - operator, next character
	  // isn't a digit, alpha, for white space
	  if( !( isdigit( expression[start+1] )
		 || isalpha( expression[start+1] )
		 || expression[start+1] == ' ' ) )
	    {
	      cout << "ERROR: white space needed between all elements" << endl;
	      return( false );
	    }
	  else
	    // recursive call
	    return( parseWhiteSpace( expression, start+1 ) );
	}
      
      else if( expression[start] == ' ' ) // if character is a white space
	// recursive call
	return( parseWhiteSpace( expression, start+1 ) );
		
      // base case 4: the character is not paren, operator, or operand
      else
	{
	  cout << "ERROR4: invalid character in expression" << endl;
	  return( false );
	}
    }

  return( true );
}
/**************************************************************************
*
* parseParens Function
*
* This function parses the expression to make sure all opening-closing
* parentheses are paired
*
* Value Paramenters:
* ------------------
* expression	      string	       the expression being parsed
*
* Return Value:
* -------------
* bool		      returns false if there is an unpaired parenthesis
*
* Local Variables:
* -----------------
* stack	              Stack	       stack variable that holds strings
* token	              string	       token variable
*
**************************************************************************/
bool parseParens( string expression )
{
  // local variables
  Stack<string> stack;
  string token;
	
  while( expression.length() != 0 )
    {
      // get a token
      token = Token( expression );
		
      // push each opening parenthesis into the stack
      if( token == "(" )
	stack.Push( token );
		
      // if a closing parenthesis is encountered...
      else if( token == ")" )
	{
	  // the stack should not be empty
	  if( stack.IsEmpty() )
	    {
	      cout << "ERROR: a closing parenthesis is not matched" << endl;
	      return( false );
	    }
	  // pop out the corresponding opening parenthesis
	  else
	    stack.Pop();
	}
    }
	
  // If the stack isn't empty by the time the expression is fully parsed,
  // then there is an unmatched opening parenthesis
  if( !stack.IsEmpty() )
    {
      cout << "ERROR: an opening parenthesis is not matched" << endl;
      return( false );
    }
  
  return( true );
}

bool parseOperandNumber( string expression )
{
  // local variables
  string token;
  int operandCount;

  // initialize local variables
  operandCount = 0;

  while( expression.length() > 0 ) // while tokens remain in expression...
    {
      token = Token( expression );
      
      if( IsAlpha( token ) || IsNumeric( token ) )
	operandCount++;
    }

  if( operandCount < 2 )
    {
      cout << "ERROR: total operands must be > 1" << endl;
      return( false );
    }

  return( true );
}
				
		
/**********************************************************************
 *
 * parseOperatorsOperands Function
 *
 * This function checks each token in the expression string to ensure
 * that the syntax is correct. It compares each token to the next and
 * previous tokens and returns false for syntax errors depending on what
 * the token is: operator, operand, (, or ).
 *
 * Value Parameters:
 * -----------------
 * expression        string        the expression being parsed
 *
 * Local Variables:
 * ----------------
 * token             string        holds middle of three tokens
 * nextToken         string        holds third of three tokens
 * previousToken     string        holds first of three tokens
 *
 * Return:
 * -------
 * bool              returns false if a syntax error is found 
 *
 *********************************************************************/		
bool parseOperatorsOperands( string expression )
{
  // local variables
  string token, nextToken, previousToken;

  // initialize previousToken to # because empty string returns true
  // for IsAlpha and IsNumeric (see last statement block in the loop)
  previousToken = "#";

  // get first two tokens from the expression
  token = Token( expression );
  nextToken = Token( expression );

  // if the first token is an operator... 
  if( token == "+"
      || token == "-"
      || token == "*"
      || token == "/" )
    {
      cout << "ERROR: expression cannot begin with an operator" << endl;
      return( false );
    }
	
  while( nextToken.length() > 0 ) // while tokens remain in expression...
    {
      // if the token is an operator...
      if( token == "+"
	  || token == "-"
	  || token == "*"
	  || token == "/" )
	{
	  // if the next token or the previous token is an operator...
	  if( nextToken == "+"
	      || nextToken == "-"
	      || nextToken == "*"
	      || nextToken == "/" 
	      || previousToken == "+"
	      || previousToken == "-"
	      || previousToken == "*"
	      || previousToken == "/" )
	    {
	      cout << "ERROR: consecutive operators" << endl;
	      return( false );
	    }

	  // if the next token is not an operand or an opening parens
	  // or the previous token is not an operand or a closing parens
	  if( ((!IsAlpha( nextToken )) && (!IsNumeric( nextToken )) 
	       && (nextToken != "(" )) || ((!IsAlpha( previousToken ))
	       && (!IsNumeric( previousToken )) && (previousToken != ")")) )
	    {
	      cout << "ERROR: an operator is missing an operand" << endl;
	      return( false );
	    }
	}
		
      // else if the token is an opening parenthesis...
      else if( token == "(" )
	{
	  // if the next token is a closed parenthesis...
	  if( nextToken == ")" )
	    {
	      cout << "ERROR: empty parentheses" << endl;
	      return( false );
	    }
	}

      // if the next token is a closed parenthesis...
      else if( token == ")" )
	{
	  if( nextToken == "(" )
	    {
	      cout << "ERROR: expected operator between ')' and '(' " 
		   << endl;
	      return( false );
	    }
	}
		
      // the only other possibility is if the token is an operand...	     
      else 
	{	
	  // if the next or previous token is an operand...
	  if( IsAlpha( nextToken ) || IsNumeric( nextToken ) 
	      || IsAlpha( previousToken ) || IsNumeric( previousToken ) )
	    {
	      cout << "ERROR: consecutive operands " << endl;
	      return( false );
	    }

	  // if the next token is an opening parenthesis...
	  if( nextToken == "(" )
	    {
	      cout << "ERROR: expected operator between operand and '('" 
		   << endl;
	      return( false );
	    }

	  // if the previous token is a closing parenthesis...
	  if( previousToken == ")" )
	    {
	      cout << "ERROR: expected operator between ')' and operand"
		   << endl;
	      return( false );
	    }
	}
		
      // store token in previous token, store nextToken in token, 
      // and get the next token
      previousToken = token;
      token = nextToken;
      nextToken = Token( expression );
    }

  // if the last token is an operator...
  if( token == "+"
      || token == "-"
      || token == "*"
      || token == "/" )
    {
      cout << "ERROR: expression cannot end with an operator" << endl;
      return( false );
    }
	
  return( true );
}

int priority( string token )
{
  if( token == "+" || token == "-" )
    return( 1 );
  else
    return( 2 );
}


/***********************************************************************
 *
 * convertExpression Function
 *
 * This function converts an infix expression to a postfix expression
 * via an algorithm that utilizes a string stack.
 *
 * Value Parameters:
 * -----------------
 * expression        string        the expression being parsed
 *
 * Local Variables:
 * ----------------
 * stack             Stack         a string stack
 * token             string        stores tokens from expression
 * postfix           string        postfix expression string
 * topToken          string        to access data in stack
 *
 * Return:
 * -------
 * string            the expression converted to postfix
 *
 **********************************************************************/
string convertExpression( string expression )
{
  // local variables
  Stack<string> stack;
  string token, 
    postfix, 
    topToken;

  // loop through entire expression	
  while( expression.length() > 0 )
    {
      // get a token
      token = Token( expression );

      // push open parentheses directly into stack
      if( token == "(" )
	{
	  stack.Push( token );
	}

      // when close parenthesis is encountered, access top element in 
      // stack, append each operator in stack to postfix until open
      // parenthesis is encountered or the stack is empty
      else if( token == ")" )
	{
	  stack.Top( topToken );
	  
	  while( topToken != "(" && !stack.IsEmpty() )
	    {
	      postfix += topToken + " ";
	      stack.Pop();
	      stack.Top( topToken );
	    }
	  
	  // discard the open parenthesis
	  stack.Pop();
	  
	}

      // when an operator is encountered, pop each operator in the stack
      // and append it as long as its priority is higher than the current
      // token and the stack is empty (don't append open parens)
      else if( token == "*" 
	       || token == "/"
	       || token == "+"
	       || token == "-" )
	{
	  
	  stack.Top( topToken );
	  
	  while( !stack.IsEmpty() && priority( token ) 
		 <= priority( topToken ) && topToken != "(" )
	    
	    {
	      postfix += topToken + " ";
	      stack.Pop();
	      stack.Top( topToken );
	    }
	  stack.Push( token );
	}

      // push operands directly onto stack
      else
	{
	  stack.Push( token );
	}
    }

  // after the expression is fully scanned, append remaining operators in 
  // stack to postfix
  while( !stack.IsEmpty() )
    {
      stack.Top( topToken );
      postfix += topToken + " ";
      stack.Pop();
    }

  return( postfix );
}

/****************************************************************************
 *
 * StringToNumber Function
 *
 * This function converts a string to a double so that it can be evaluated
 * by mathematical operators.
 *
 * Reference Parameters:
 * ---------------------
 * Text        string        a string containing a number
 *
 * Return:
 * -------
 * double      the number from the string, converted to double type 
 *
 ***************************************************************************/
double StringToNumber ( string &Text )
{                              
  stringstream ss( Text );
  double result;
  return( ss >> result ? result : 0 );
}

/***************************************************************************
 * 
 * evaluateExpression Function
 *
 * This function evaluates a string that is in postfix form.
 *
 * Value Parameters:
 * -----------------
 * postfix        string        postfix expression in string form
 *
 * Local Variables:
 * ----------------
 * s_length       int           holds length of postfix
 * ii             int           counter used in test for alpha
 * isAlpha        bool          flag in test for alpha
 * expressionOk   bool          flag for errors in expression
 * token          string        holds tokens from expression
 * num            double        holds number converted from string token
 * op1            double        operand 1
 * op2            double        operand 2
 * result         double        holds evaluation result
 * stack          stack         stack that holds doubles         
 *
 **************************************************************************/
void evaluateExpression( string postfix )
{
  // local variables
  int s_length;
  int ii;
  bool isAlpha, expressionOk;
  string token;
  double num, op1, op2, result;
  Stack<double> stack;
	

  // initialize local variables
  s_length = postfix.length();
  ii = 0;
  isAlpha = false;
  expressionOk = true;

  // test for an alphabetic letter in the string, stopping at first occurance
  for( ii=0; (ii<s_length) && (!isAlpha); ii++ )
    isAlpha = ( isalpha( postfix[ii] )) ? true : false;
  
  if( isAlpha )
    {
      cout << "EVALUATED: N/A" << endl;
      return;
    }

  //get a token		
  token = Token( postfix );

  // loop through entire expression	
  while( (postfix.length() > 0) && expressionOk )
    {
      // if token as an operand, convert to double
      if( IsNumeric( token ) )
	{
	  num = StringToNumber( token );
	  stack.Push( num );
	}

      // else if token is an operator, pop two operands from stack,
      // perform operation, and push results into stack		
      else
	{
	  if( stack.IsEmpty() )
	    expressionOk = false;
	  else
	    {
	      stack.Top( op1 );
	      stack.Pop();
	      if( stack.IsEmpty() )
		expressionOk = false;
	      else
		{
		  stack.Top( op2 );
		  stack.Pop();
		  
		  if( token == "+" )
		    stack.Push( op2 + op1 );
		  else if( token == "-" )
		    stack.Push( op2 - op1 );
		  else if( token == "*" )
		    stack.Push( op2 * op1 );
		  else if( token == "/" )
		    stack.Push( op2 / op1 );
		  else
		    {
		      cout << "operation illegal" << endl;
		      expressionOk = false;
		    }
		}
	    }
	}
      
      // get another token
      token = Token( postfix );
    }

  // get result and display	
  stack.Top( result );
	
  cout << "EVALUATED: " << result << endl;
  
}
				

	


		
		
		
			
		
		
	
	
	
