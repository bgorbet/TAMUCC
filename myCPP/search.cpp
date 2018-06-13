/***********************************************************************
// Betty Gorbet
// COSC5311
// Marwa Hassan
// Lab 12 Problem 2
// This program reads a list of integers from a file into an
// array, displays it to the user, sorts it using the selection 
// sort function, displays the sorted list, then searches the 
// list for a user entered integer and displays it's position
// as well as the median.
***********************************************************************/ 
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

// Function protoypes
void showArray(int[], int);
void sort(int[], int);
void Swap(int[], int, int);
int findMin(int[], int, int);
int search(int[], int, int);
double median(int[], int);


int main()
{
    ifstream inputFile;  // Input file object
    char filename[20];   // Char array to hold filename
    // Array to hold no more than 50 integers from file, variables
    // for user entry, position of user entry, and counter for
    // items loaded from file. 
    int array[50]={0}, number, position, count=0; 
    
    // Get filename
    cout<<"Enter filename: ";
    cin>>filename;
    
    inputFile.open(filename);   
    
    // Validate filename & display error message & ask for re-entry
    while(!inputFile)
    {                
                     cout<<"File not fount. Enter filename: ";
                     cin>>filename;
                     inputFile.open(filename);
    }   
     
    // Load file contents into array 
    while(count<50 && inputFile>>array[count])
                    count++;
     
    inputFile.close();
    
    // Call function to display array
    showArray(array, count);
    
    // Display number of valid items in array
    cout<<"\nNumber of items: "<<count<<endl;
    
    // Call function to sort array in ascending order
    sort(array, count);
    
    // Call function to display sorted array 
    showArray(array, count);
          
    // Get user entry
    cout<<"Enter an integer: ";
    cin>>number;
    
    // Call function to search array             
    position=search(array, count, number);
    
    // Display number position or "number not found" message        
    if(position== -1)
                 cout<<"The number was not in the file.\n";
    else
    {
                 cout<<number<<" is item number "<<position+1<<" in the file.";
                 cout<<"\n";
    }
                        
    // Call funtion to find median and display                    
    cout<<"The median is "<<median(array, count)<<endl;
                        
    return 0;
}

/*************************************************************************
// showArray function
// This function displays array in formatted rows
// parameters: int array and int size (number valid items)
// return value: none
**************************************************************************/
void showArray(int array[], int size)
{
                // This for loops displays the formatted list
          for(int i=0; i < size; i+=6)
              { 
                        for(int j = i; j < i+6 && j < size; j++)
                                cout<<setw(10)<<array[j];
                        cout<<endl;
           }
}
/**************************************************************************
// sort funtion
// This function sorts and array using selection sort, calling two other 
// functions: findMin and Swap.
// parameters: int array, int size (number valid items)
// return value: none
***************************************************************************/
void sort(int array[], int size)
{
          int unsortedMin;
          for(int index=0; index<(size-1); index++)
          {
                        unsortedMin=findMin(array, size, index);
                        Swap(array, index, unsortedMin);
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
// search function
// This is a binary search function
// parameters: int array, int size, int target (search query)
// return value: int position (position of query, -1 if query not found)
****************************************************************************/
int search(int array[], int size, int target)
{
         int position= -1;
         int first=0;
         int last=size-1;
          
         while (last >= first   &&   position== -1)
          {
               int mid=(first+last)/2;
               if(array[mid] == target)
                    position = mid;
               else if(array[mid] > target)
                    last = mid-1;
               else if(array[mid] < target)
                    first = mid+1;
         }
                      
         return position;
}
 
 /**************************************************************************
 // median function
 // This function computes the median of a sorted array
 // parameters: int array, int size
 // return value: double median
 **************************************************************************/
double median(int array[], int size)
{
         if(size%2==0)
               return static_cast<double>((array[size/2]+array[(size/2)-1]))/2;
         else
               return array[size/2];
}         
