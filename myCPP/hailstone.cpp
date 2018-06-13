/*******************************************************************
//Name: Betty Gorbet
//Class: COSC 5311
//Instructor: Marwa Hassan
//Lab 6 Problem 1
//Date: October 12, 2011
//Program description: This program displays a hailstone sequence starting
at the value the user enters and stops when the sequence gets to 1.
*********************************************************************/
#include<iostream>

using namespace std;

int main ()
{
	int N; // the first integer in the sequence
	
	// Get a value for N from user
	cout<<"Please enter a positive integer: ";
	cin>>N;
	
	// Verify that N is positive
	if(N<1)
	{
		cout<<"This is not a positive integer, run the program again and enter";
		cout<<" a positive integer."<<endl;
	}
	
	
	// If N is positive go to loop for the sequence
	else
	{
		cout<<N<<" ";
		while(N!=1)
		{
			if(N%2==0)
				N=N/2;
 			else
				N=N*3+1;
			cout<<N<<" ";
	    }
	}
cout<<"\n";
	return 0;
}
