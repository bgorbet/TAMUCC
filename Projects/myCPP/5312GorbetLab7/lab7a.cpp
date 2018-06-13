/***************************************************************************
* Annie Gorbet
* COSC5312
* Lab 7 Part A
* Feb 29, 2012
* 
* Description:
* Inputs:
* Outputs:
***************************************************************************/

#include<iostream>
#include<ctime>
using namespace std;

// Function Prototypes
int getComputersChoice();
int getHumansChoice();
char determineWinner( int *humanChoice, int *computerChoice );
void showCurrentRound( char *lastResult );
void updateTotals( char *lastResult, int *totalGames, int *humanWins,
		   int *computerWins, int *numberTies );
void displayResults( int *totalGames, int *humanWins, int *computerWins,
	             int *numberTies );


int main()
{
    // local variables
    int *humanChoice = new int,
        *computerChoice = new int,
        *totalGames = new int,
        *humanWins = new int,
        *computerWins = new int,
        *numberTies = new int;
    char *lastResult = new char,
         *playAgain = new char;

    // initialize local variables
    *totalGames = 0;
    *humanWins = 0;
    *computerWins = 0;
    *numberTies = 0;

    // seed the random number generator for computerChoice
    srand( time(NULL) );

    do
    {
        *computerChoice = getComputersChoice();
        *humanChoice = getHumansChoice();
        *lastResult = determineWinner( humanChoice, computerChoice );
        showCurrentRound( lastResult );
        updateTotals( lastResult, totalGames, humanWins, computerWins, 
        	      numberTies );

	cout << "Do you want to play again? (y/n)" << endl;
	cin.ignore();
	cin >> *playAgain;

    }while( *playAgain == 'y' || *playAgain == 'Y' );

    displayResults( totalGames, humanWins, computerWins, numberTies );

    delete humanChoice, computerChoice, totalGames, humanWins, 
	   computerWins, numberTies, lastResult, playAgain;

    return( 0 );
}

/***************************************************************************
* Function:
* Purpose:
* Precondition:
* Postcondition:
***************************************************************************/
int getComputersChoice()
{
    return( rand()%3+1 );
}

/***************************************************************************
* Function:
* Purpose:
* Precondition:
* Postcondition:
***************************************************************************/
int getHumansChoice()
{
    // local variables
    int *choice = new int;

    do
    {
	    cout << "Choose from one of the following options: \n"
		 << "1. Rock\n"
		 << "2. Scissors\n"
	      	 << "3. Paper" << endl;
	    cin >> *choice;

    }while( *choice < 1 || *choice > 3 );

    return( *choice );
}

/***************************************************************************
* Function:
* Purpose:
* Precondition:
* Postcondition:
***************************************************************************/
char determineWinner( int *humanChoice, int *computerChoice )
{
    if( *humanChoice == *computerChoice )
	return( 't' );
    else
    {
	switch( *humanChoice )
	{
	    case 1: if( *computerChoice == 2 )
	            {
		        cout << "rock smashed scissors" << endl;
			return( 'h'	);	
		    }
		    else if( *computerChoice == 3 )
		    {
		       	cout << "paper wraps rock" << endl;
		       	return( 'c' );		
		    }
		    break;
	    case 2: if( *computerChoice == 1 )			
                    {
		       	cout << "rock smashed scissors" << endl;
		       	return( 'c' );
		    }
		    else if( *computerChoice == 3 )
		    {
		       	cout << "scissors cut paper" << endl;
		       	return( 'h' );
		    }
		    break;
	    case 3: if( *computerChoice == 1 )
		    {
		       	cout << "paper wraps rock" << endl;
		       	return( 'h' );
		    }
		    else if( *computerChoice == 2 )
		    {
		       	cout << "scissors cuts paper" << endl;
		       	return( 'c' );
		    }
		    break;
        }
    }
}

/***************************************************************************
* Function:
* Purpose:
* Precondition:
* Postcondition:
***************************************************************************/
void showCurrentRound( char *lastResult )
{
    cout << "For this round, ";
    switch( *lastResult )
    {
       	case 't':   cout << "it was a tie." << endl;
		    break;
        case 'h':   cout << "you beat the computer!" << endl;
		    break;
	case 'c':   cout << "the computer beat you. :-(" << endl;
		    break;
    }
}

/***************************************************************************
* Function:
* Purpose:
* Precondition:
* Postcondition:
***************************************************************************/
void updateTotals( char *lastResult, int *totalGames, int *humanWins,
				   int *computerWins, int *numberTies )
{
    *totalGames = *totalGames + 1;

    switch( *lastResult )
    {
       	case 't':	*numberTies = *numberTies + 1;
       			break;
       	case 'h':	*humanWins = *humanWins + 1;
       			break;
       	case 'c':	*computerWins = *computerWins + 1;
	       		break;
    }
}

/***************************************************************************
* Function:
* Purpose:
* Precondition:
* Postcondition:
***************************************************************************/
void displayResults( int *totalGames, int *humanWins, int *computerWins,
	                 int *numberTies )
{
	cout << "There were a total of " << *totalGames << " games." << endl;
	cout << "The computer won " << *computerWins << " games." << endl;
	cout << "You won " << *humanWins << " games." << endl;
	cout << "There were " << *numberTies << " tied games." << endl;

	if( *humanWins > *computerWins )
	{
		cout << "Congratulations! You beat the computer by "
		     << *humanWins - *computerWins << " games!" << endl;
	}
}




