/************************************************************************
//Name: Betty Gorbet
//Class: COSC 5311
//Instructor: Marwa Hassan
//Lab 15
//Date: Dec 4, 2011
//Program description: This is a program that plays rock, paper, scissors
// with the user.
*************************************************************************/
#include<iostream>
using namespace std;

// Function prototypes
string showChoice(int);
void winner(int, int);

int main ()
{
    unsigned seed = time(0); // Get the system time
    srand(seed);             // Seed the random number generator  
    int n, choice;           // Variables for user and computer choice
    
    // This loops displays the menu, gets user and computer choices, and
    // determines winner until the user chooses to quit
    do{
         // Randomly get computer choice
         n=1+rand()%3;
         
         // Display game menu
         cout<<"\nGame Menu \n---------"<<endl;
         cout<<"1.) Rock \n2.) Paper \n3.) Scissors \n4.) Quit"<<endl;
         cout<<"\nEnter your choice: ";
         cin>>choice;
         
         // Loops to validate user choice
         while(choice<1 || choice>4)
         {
                        cout<<"Invalid selection.  Enter 1, 2, 3, or 4: ";
                        cin>>choice;
         }
         
         // Leave loop if user chooses 4
         if(choice==4)
                      break;
                      
         // Call function to display user and computer choice
         cout<<"\nYou selected: "<<showChoice(choice)<<endl;
         cout<<"The computer selected: "<<showChoice(n)<<endl;
         
         // Call function to determine the winner
         winner(choice, n);
         
      }while(choice!=4);
      
      return 0;
}

/********************************showChoice*********************************
// This function displays the choice (rock, paper or scissors) based on the
// numbers 1, 2, or 3.
// Parameters: int x (the choice number)
// Return value: string choice (string corresponding the the choice)
***************************************************************************/
string showChoice(int x)
{
               string choice;
               if(x==1)
                  choice="Rock";
               else if(x==2)
                  choice="Paper";
               else if(x==3)
                  choice="Scissors";
               return choice;
}

/**************************Winner******************************************
// This function takes the user and computer choices and determines the 
// winner or if it is a tie.
// Parameters: int user, int computer (numbers for user and computer choices)
// Return value: none
**************************************************************************/
void winner(int user, int computer)
{
     if(user==1)
     {
                if(computer==1)
                   cout<<"Tie. No winner."<<endl;
                else if(computer==2)
                   cout<<"Computer Wins! Paper wraps rock."<<endl;
                else if(computer==3)
                   cout<<"YOU win! Rock smashes scissors."<<endl;
     }
     if(user==2)
     {
                if(computer==1)
                   cout<<"YOU win! Paper wraps rock."<<endl;
                else if(computer==2)
                   cout<<"Tie. No winner."<<endl;
                else if(computer==3)
                   cout<<"Computer wins! Scissors cut paper."<<endl;
     }
     if(user==3)
     {
                if(computer==1)
                   cout<<"Computer wins! Rock smashes scissors."<<endl;
                else if(computer==2)
                   cout<<"YOU win! Scissors cut paper."<<endl;
                else if(computer==3)
                   cout<<"Tie. No winner."<<endl;
     }
}
                   
      
         
         
         
