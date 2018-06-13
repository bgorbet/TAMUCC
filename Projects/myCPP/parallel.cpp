/*******************************************************************
//Name: Betty Gorbet
//Class: COSC 5311
//Instructor: Marwa Hassan
//Lab 13
//Date: Nov 30, 2011
//Program description: Reads a file containing student data and
// sorts the students by grade
*********************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// Array prototypes
void showArrays(int[], string[], int[], int);
void sort(int[], string[], int[], int);
int findMin(int[], int, int);
void Swap(int[], int, int);
void Swap2(string[], int, int);

int main()
{
    int array_ID[50]={0};      // Student ID array, initialized as empty
    int array_Grade[50]={0};   // Student Grades array, initialized as empty
    string array_Name[50]={""};// Student Names array, initialized as empty
    ifstream fileIn;           // Input file stream object
    int n=0;                   // Accumulator to keep total of elements read
                               // into the arrays, initialized to 0
    
    // Open file and verify that it exists
    fileIn.open("grade.dat");
    if(!fileIn)
    {
               cout<<"File not found."<<endl;
               exit(0);
    }
    
    // Read each column in the file into each of the three arrays
    while(n<50 && fileIn>>array_ID[n]>>array_Name[n]>>array_Grade[n])
                   n++;
    
    // Display contents of file/arrays
    cout<<"Contents of file:"<<endl;
    showArrays(array_ID, array_Name, array_Grade, n);
    
    // Call function to sort arrays according to grades
    sort(array_ID, array_Name, array_Grade, n);
    
    // Display the sorted arrays
    cout<<"\nSorted file contents:"<<endl;
    showArrays(array_ID, array_Name, array_Grade, n);
    
    return 0;
}

/**************************************************************************
// showArrays
// This function displays three parallel arrays in three columns
// parameters: int array, string array2, int array3, int size
//             (the three parallel arrays and their size)
// return value: none
**************************************************************************/
void showArrays(int array1[], string array2[], int array3[], int size)
{
        for(int i=0; i<size; i++)
	{
		cout<<array1[i]<<"\t"<<left<<setw(15)<<array2[i]<<array3[i];
		cout<<"\n";
	}
}

/***************************************************************************
// sort function
// This function sorts an array and two other parallel arrays with it using
// the selection sort method
// parameters: int array, string array2, int array3, int size
//             (three parallel arrays and their size)
// return value: none
***************************************************************************/
void sort(int array1[], string array2[], int array3[], int size)
{
          int unsortedMin;
          for(int index=0; index<(size-1); index++)
          {
                        unsortedMin=findMin(array3, size, index);
                        Swap(array1, index, unsortedMin);
                        Swap2(array2, index, unsortedMin);
                        Swap(array3, index, unsortedMin);
          }
}  

/***************************************************************************
// findMind function
// This function is called by sort and finds the least value in the unsorted
// part of the list.
// parameters: int array, int size, int index (first item in unsorted part)
// return value: int smallestAt (position of unsorted minimum)
****************************************************************************/
int findMin(int array[], int size, int index)
{
         int smallestAt=index;
         for(int j=(index+1); j<size; j++)
         {
                      if(array[j]<=array[smallestAt])
                            smallestAt=j;
         }
         return smallestAt;
}

/***************************************************************************
// Swap functions
// This function is called by sort and swaps the first item in the unsorted
// part with the unsorted minimum value
// parameters: int array, int x (position of first item in unsorted part), 
// int y (unsorted minimum)
// return value: none
****************************************************************************/
void Swap(int array[], int x, int y)
{
         int temp;
         temp=array[x];
         array[x]=array[y];
         array[y]=temp;
}

/***************************************************************************
// Swap functions
// This function is called by sort and swaps the first item in the unsorted
// part with the unsorted minimum value *for a string array*
// parameters: *string* array, int x (position of first item in unsorted part), 
// int y (unsorted minimum)
// return value: none
****************************************************************************/
void Swap2(string array[], int x, int y)
{
         string temp;
         temp=array[x];
         array[x]=array[y];
         array[y]=temp;
}

