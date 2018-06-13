/*******************************************************************
//Name: Betty Gorbet
//Class: COSC 5311
//Instructor: Marwa Hassan
//Lab 11 Problem 2
//Date: Nov. 15, 2011
//Program description: This program lets the user choose a value from
// a list and determines the number of comparisons it takes to find
// the value using a linear and binary search.
*********************************************************************/
#include<iostream>
#include<iomanip>
using namespace std;

// Function prototypes
int sequentialSearch(const int [], int, int);
int binarySearch(const int [], int, int);

int main()
{
	// Declare and initialize the array containing the list
	int numbers[]={1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,	
			15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
	int value; // Variable to store user's entry
	
	// This for loops displays the formatted list
	for(int i=0; i < 24; i+=6)
	{
		for(int j = i; j < i+6; j++)
			cout<<setw(5)<<numbers[j];
		cout<<endl;
	}
	
	// Get the user's entry
	cout<<"\n";
	cout<<"Choose a value from the list: ";
	cin>>value;
	
	// This loop validates the entry is in the list
	while(value < 1 || value > 24)
	{
		cout<<"The value is not in the list.\n";
		cout<<"Choose a value from the list: ";
		cin>>value;
	}
	
	// Call sequentialSearch and binarySearch functions and display
	// their returned values
	cout<<"\n";
	cout<<"The linear search made "<<sequentialSearch(numbers, 24, 
value);
	cout<<" comparisons.\n";
	cout<<"The binary serach made "<<binarySearch(numbers, 24, 
value);
	cout<<" comparisons.\n";
	
	return 0;
}
	
//**************************************************************************
// sequentialSearch function
// This function performs sequential search of the list for the user's 
entry
// and returns the number of comparisons made
//
// Return Value
// ------------
// int                    number comparisons made
//
// Parameters
// ------------
// const int array[]	  array with the list of numbers
// int arraySize	  size of the array
// int target		  the user's entry
//**************************************************************************
int sequentialSearch(const int array[], int arraySize, int target)
{
	int position = -1, index = 0; // The position is initialized to 
-1
				      // and will determine when the 
target
				      // is found, the search starts at
				      // index 0

	// Scan the array one entry at a time
	while(index < arraySize && position == -1)
	{
		if(array[index] == target)
			position = index; // Position only changes when 
		index++;		  // target is found
	}
	return index; // index reflects number of comparisons made
}

//************************************************************************** 
// binarySearch function 
// This function performs binary search of the list for the user's entry 
// and returns the number of comparisons made
//
// Return Value
// ------------
// int                    number comparisons made
// 
// Parameters
// ------------
// const int array[]      array with the list of numbers
// int arraySize          size of the array
// int target             the user's entry 
//************************************************************************** 
int binarySearch(const int a[], int size, int target)
{
	// Initialize accumulator (for tracking # of comparisons) and 
	// position to -1, first to index 0, and last to the index
	// of the last element (size-1)
	int count = 0, position = -1, first = 0, last = size-1;
	
	// Scan the array as long as position is -1 and there
	// are still elements to search in the array
	while(last >= first && position == -1)
	{
		int mid = (first+last)/2;  // Sart w/ the middle (floor)
		if(a[mid] == target)
			position = mid;    // If mid is target change 
		else if(a[mid] > target)   // position to mid
			last = (mid - 1);  // if target is greater, scan
		else if(a[mid] < target)   // mid of top half
			first = (mid + 1); // if target is less, scan
		count++;		   // mid of bottom half
	}				   // repeat until target found
	return count;
}
