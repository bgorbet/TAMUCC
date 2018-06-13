/*******************************************************************
//Name: Betty Gorbet
//Class: COSC 5311
//Instructor: Marwa Hassan
//Lab 9 Problem 1 Resubmit
//Date: Nov. 2, 2011
//Program description: This program works like a lottery that 
//randomly generates 5 numbers and compares them to 5 numbers that
//it gets from the user and displays the number of matches and a 
//congratualtions if there are 5 matches.
*********************************************************************/

#include<iostream>
#include<cstdlib> // For rand and srand
#include<ctime>   // For the time function
using namespace std;

int main()
{
        unsigned seed = time(0); // Get the system time
        srand(seed);             // Seed the random number generator   
        const int SIZE = 5;      // Size for user array

	// Declare and initialize lottery array
        int lottery[] = {0+rand()%9, 0+rand()%9, 0+rand()%9, 0+rand()%9,
        	        0+rand()%9};

	// Declare user array but we don't know elements yet
        int user[SIZE];

	// This will be used to track matches
        int match = 0;
        
	// Get the user picks and assign them to each element in user
        cout<<"Enter your 5 lottery number picks."<<endl;
        for(int i=0; i<SIZE; i++)
	{
		cout<<"Enter Number "<<i+1<<" : ";
		cin>>user[i];

		// This loop ensures that the entry is in the range 0-9
		while(user[i]<0 || user[i]>9)
		{
			cout<<"Number must be in the range 0-9.\n";
			cout<<"Enter Number "<<i+1<<" : ";
			cin>>user[i];
		}
	}
        cout<<"\n";
        
	// This loop compares each element in each array
        for(int i=0; i<SIZE; i++)
	        if(lottery[i]==user[i])
	        	match+=1;
        
	// Display lottery array
        cout<<"Lottery numbers:\n"<<lottery[0]<<" "<<lottery[1]<<" ";
        cout<<lottery[2]<<" "<<lottery[3]<<" "<<lottery[4]<<endl;
        
	// Display user array
        cout<<"Your numbers:\n"<<user[0]<<" "<<user[1]<<" "<<user[2]<<" ";
        cout<<user[3]<<" "<<user[4]<<endl;
        
	// Display number of matches
        cout<<"You matched "<<match<<" number(s).\n"; 
        
	// Display congratulations if all numbers match
        if(match==5)
        	cout<<"Congratulations! You are a grand prize winner!"<<endl;
        
	return 0;
}
