/*******************************************************************
//Name: Betty Gorbet
//Class: COSC 5311
//Instructor: Marwa Hassan
//Lab 11 Problem 2
//Date: Nov. 15, 2011
//Program description: This program
*********************************************************************/
#include<iostream> 
#include<iomanip>
using namespace std; 
 
int sequentialSearch(const int array[], int arraySize; int target)
{
        int position = -1, index = 0;
                        
        while(index < arraySize && position = -1)
        {
                if(array[index] = target
                        position = index;
                index++;
        }
        return index;
}
        
int binarySearch(const int a[], int size, int target)
{
        int count = 0, position = -1, first = 0, last = size-1;
 
        while(last >= first && position == -1)
        {
                int mid = (first+last)/2;
                if(a[mid] == target)
                        position = mid;
                else if(a[mid] > target)
                        last = mid - 1;
                else if(a[mid] < target)
                        first = mid + 1;
                count++;
        }
        return count;
}
        
int main()
{
        int numbers[20];
        int value;
                
  
         
        cout<<"\n";
        cout<<"Choose a value from the list: ";
        cin>>value;
         
        cout<<"\n";  
        cout<<"The linear search made "<<sequentialSearch(numbers, 24, value)<<" ";
        cout<<"comparisons.\n";
        cout<<"The binary serach made "<<binarySearch(numbers, 24, value)<<" ";
        cout<<"comparisons.\n";
        
        return 0;
}


         

