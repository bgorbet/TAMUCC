/*******************************************************************
//Name: Betty Gorbet
//Class: COSC 5311
//Instructor: Marwa Hassan
//Lab 11 Problem 1
//Date: Nov. 15, 2011
//Program description: This program lets the user enter a charge 
// account number and searches a list to determine if the number is
// valid.
*********************************************************************/
#include <iostream>
using namespace std;

// Function prototype
int sequentialSearch(const int [], int, int);

main()
{
	// Array with list of valid account numbers
	int list[] = {5658845,      4520125,      7895122, 
		      8777541,      8451277,      1302850,
		      8080152,      4562555,      5552012,    
		      5050552,      7825877,      1250255,
		      1005231,      6545231,      3852085,      
		      7576651,      7881200,      4581002};
			      
	int query;	// Variable to store user's entry
	
	// Get user's account number
	cout<<"Enter your account number and press ENTER: ";
	cin>>query;
	
	// This loop calls sequentialSearch function and if
	// it returns -1, the query was not in the list and
	// it displays an error message and gets the query again
	while(sequentialSearch(list, 18, query) == -1)
	{
		cout<<"Invalid account number.\n";
		cout<<"Enter your account number and press ENTER: ";
		cin>>query;
	}
	
	// If the loop terminates, the query was found and the
	// user's account number is valid
	cout<<"Your account number is valid.\n";
		
	return 0;
}

//****************************************************************
// sequentialSearch function
// This function scans the array containing the list of account 
// numbers for the user's entry
//
// Return Value
// ------------
// int                    the position number
//
// Parameters
// ------------
// const int array[]      The list of valid account numbers
// int arraySize	  The size of the list
// int target		  The query/target value
//****************************************************************
int sequentialSearch(const int array[], int arraySize, int target)
{
	int position = -1, index = 0; // The position will tell if the
				      // target was found, the search
				      // starts at inex 0 or the first
				      // element of the list
	
	// This loops scans each element ih the array
	while(index < arraySize && position == -1)
	{
		if(array[index] == target)
			position = index; // The position remains -1 
		index++;		  // unless the target is found
	}
	return position;
}
