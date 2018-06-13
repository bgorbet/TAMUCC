/*******************************************************************
//Name: Betty Gorbet
//Class: COSC 5311
//Instructor: Marwa Hassan
//Lab 7 Problem 1 Part b
//Date: Oct. 19, 2011
//Program description: This program gets two positive integers from the
user and computes and displays the sum of the squares of the odd numbers
between them (inclusive).  It uses a function called sumSquares.
*********************************************************************/
#include<iostream>
using namespace std;

// prototypes for sumSquares and checkValues functions
int sumSquares(int x, int y);
bool checkValues(int num1, int num2);

// this is the main function
int main()
{
	int sum, m, n; // variables for two integers and sum of squares
	
	// Get the two integers
	cout<<"Enter two positive integers. The second integer must be greater";
	cout<<" than or equal to the first: ";
	cin>>m>>n;
	
	// Call checkValues function in while loop to validate input
	while(!checkValues(m,n)) // execute loop while checkValues is false
		{
		cout<<"Error: integers non-positive and/or first integer is ";
		cout<<"greater than the first. Please re-enter: ";
		cin>>m>>n;
		}
	
	// Call function sumSquares and display sum
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

int sumSquares(int x, int y)
{
     int sumOfSquares=0;
     for(int i=x; i<=y; i++)
     	{
	if(i%2==1)
	     sumOfSquares+=(i*i);
  	}
  	 return sumOfSquares;
}

//*******************************************************************
// checkValues Function
// This function checks that the values entered by the user are valid
//
// Return Value
// ------------
// bool			result (true=1 and false=0)
// 
// Parameters
// -----------
// int num1		the first number entered
// int num2		the second number entered
//*******************************************************************

bool checkValues(int num1, int num2)
{
	bool result;
	if(num1>0 && num2>0 && num2>=num1)
		result = true;
	else
		result = false;
	return result;
}
