/**********************************************************************
Annie Gorbet
5312 Lab 7 Part B
February 29, 2012
Instructor: Phyllis Tedford

This program asks the user for their name and a password.  It uses 
5 criteria to determine whether the password is valid.  It uses 5 
functions to test these criteria and a sixth   function to check
which criteria were violated, if there were any violations.

The criteria are:
     cannot be user's name
     must contain one upper and one lower case alpha
     must contain at least one digit
     must contain at least one special character (non-alphnumeric)
     must not contain spaces
***********************************************************************/
#include<iostream>
#include<cstring>
#include<cctype>
using namespace std;

//Function Protoypes
bool criteriaNotName(char *name, char *password);
bool criteriaAlphaCase(char *password);
bool criteriaDigit(char *password);
bool criteriaSpecialChar(char *password);
bool criteriaNoSpaces(char *password);
void check(bool, bool, bool, bool, bool);

//Constant for char array sizes
const int MAX = 12;

int main()
{
    //Bool variables for each criteria
    bool criteria_NotName, 
         criteria_AlphaCase, 
         criteria_Digit, 
         criteria_SpecialChar, 
         criteria_NoSpaces, 
         flag = 0;

    //Char arrays for the name and password
    char *name = new char[MAX], 
         *password = new char[MAX];

    //Counter for number of attempts
    int count = 0;
    
    //Get user's name
    cout<<"What is your name? (enter no more that 12 characters)";
    cin.getline(name, MAX);  //Use getline so program doesn't freak out if
                             //the user enters a space
                             
    cout<<"\nHello "<<name<<endl; //Say hi! :)
    
    //This loop ends after 3 unsuccessful attempts
    do
    {
       	do
       	{
	       	cout<<"\nPlease enter a password: "
		    <<"(must be between 8 and 12 characters) "
		    << endl;
		cin.getline(password, MAX);

	}while(strlen(password) < 8 );
       
       //Call functions to test criteria
       criteria_NotName = criteriaNotName(name, password);
       criteria_AlphaCase = criteriaAlphaCase(password);
       criteria_Digit = criteriaDigit(password);
       criteria_SpecialChar = criteriaSpecialChar(password);
       criteria_NoSpaces = criteriaNoSpaces(password);

       //If all criteria are met, exit program
       if(criteria_NotName && criteria_AlphaCase && criteria_Digit
           && criteria_SpecialChar && criteria_NoSpaces)
       {
            cout<<"That password is valid.\n";
            exit(0);
       }
       
       //If all criteria are not met, check which ones weren't
       check(criteria_NotName, criteria_AlphaCase, criteria_Digit, 
             criteria_SpecialChar, criteria_NoSpaces);
       
       //Update counter
       count++;
       }while(count<3);
       
       cout<<"\n  You have made 3 unsuccessful attempts.  Wait one ";
       cout<<"hour and try again.";
    
    return 0;
}

/**********************************************************************
Purpose: uses strcmp to test if the password is the user's name.
Precondition:
Postcondition:
***********************************************************************/
bool criteriaNotName(char *name, char *password)
{
     if(strcmp(name, password) == 0)
     {
          return false;
     }
     return true;
}


/**********************************************************************
Purpose: This function tests to see if the password meets the 2nd criteria
         It uses the cctype library functions islower and isupper.
Precondition:
Postcondition:
***********************************************************************/
bool criteriaAlphaCase(char *password)
{
     int count_lower = 0,
         count_upper = 0;
         
     for(int i=0; i<strlen(password); i++)
     {
             if(islower(password[i]))
             
                  count_lower++;
                  
             if(isupper(password[i]))
             
                  count_upper++;
     }
     
     if(count_lower>0 && count_upper>0)
     {
          return true;
     }
     return false;
}

/**********************************************************************
Purpose: This function tests whether the password meets the 3rd criteria
         It uses the isdigit cctype library function.
Precondition:
Postcondition:
***********************************************************************/
bool criteriaDigit(char *password)
{
     for(int i=0; i<strlen(password); i++)
     {
     
         if(isdigit(password[i]))
         
              return true;
              
     }
     return false;
}

/**********************************************************************
Purpose: This function tests whether the password meets the 4th criteria
         It uses the ispunct cctype library function.   
Precondition:
Postcondition:
***********************************************************************/
bool criteriaSpecialChar(char *password)
{
     for(int i=0; i<strlen(password); i++)
     {
         if(ispunct(password[i]))
         
              return true;
         
     }
     return false;
}

/**********************************************************************
Purpose:  tests whether the password meets the last criteria
          It uses the isspace cctype library function.          
Precondition:
Postcondition:
**********************************************************************/
bool criteriaNoSpaces(char *password)
{
     for(int i=0; i<strlen(password); i++)
     {
             
         if(isspace(password[i]))
         
              return false;
              
     }
     return true;
}
/********************************Check*********************************
Purpose: checks which criteria the password is violating,
         displays a message for each violated criteria explaining the
         violation.
Precondition:
Postcondition:
***********************************************************************/
void check( bool criteria_NotName, bool criteria_AlphaCase,
            bool criteria_Digit, bool criteria_SpecialChar,
	    bool criteria_NoSpaces)
{
     if(!criteria_NotName)
     {
           cout<<"A valid password cannot be your name.\n";
     }
     
     if(!criteria_AlphaCase)
     {
           cout<<"A valid password must contain at least one upper case ";
           cout<<"letter and at least one lower case letter.\n";
     }
     
     if(!criteria_Digit)
     {
           cout<<"A valid password must contain at least one digit.\n";
     }
     
     if(!criteria_SpecialChar)
     {
           cout<<"A valid password must contain at least one ";
           cout<<"non-alphanumeric character.\n";
     }
     
     if(!criteria_NoSpaces)
     {
           cout<<"A valid password may not contain any spaces.\n";
     }
     
}
         
     
                      
                      
    
       

