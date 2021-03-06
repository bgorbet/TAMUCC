/*******************************************************************
//Name: Betty Gorbet
//Class: COSC 5311
//Instructor: Marwa Hassan
//Lab 7 Problem 1 Part a
//Date: Oct. 19, 2011
//Program description: This program gets two positive integers from the
user and computes and displays the sum of the squares of the odd numbers
between them (inclusive).  It uses a function called sumSquares.
*********************************************************************/
#include<iostream>
using namespace std;

// prototype for sumSquares function
int sumSquares(int x, int  y);

// this is the main function
int main()
{
	int sum, m, n; // variables for the two integers and the sum of squares
	
	// Get the two integers
	cout<<"Enter two positive integers. The second integer must be greater";
	cout<<" than or equal to the first: ";
	cin>>m>>n;
	
	// Validate input using while loop
	while(m<=0 || n<=0 || n<m)
		{
		cout<<"Error: integers non-positive and/or first integer is ";
		cout<<"greater than the first. Please re-enter: ";
		cin>>m>>n;
		}
	
	// Call sumSquares function and display the sum
	sum=sumSquares(m,n);
	cout<<"The sum is: "<<sum<<endl;
	
	return 0;
}

//********************************************************************
// sumSquares Function
// This function computes the sum of the squares of the odd numbers
// between two integer values
//
// Return Value
// ------------
// int                       sum of squares of odd numbers
//
// Parameters
// ------------
// int x                     first positive integer  
// int y                     second positive integer where num2>=num1
//*******************************************************************

int sumSquares(int x, int  y)
{
     int sumOfSquares=0;
     for(int i=x; i<=y; i++)
     	{
	if(i%2==1)
		sumOfSquares+=(i*i);
  	}
  	return sumOfSquares;
}
