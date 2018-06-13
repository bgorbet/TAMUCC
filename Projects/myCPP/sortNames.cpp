/*************************************************************************
// Betty Gorbet
// COSC 5311
// Marwa Hassan
// Lab 12 Problem 1
// This program opens a hardcoded file of names and loads each name into
// a string array, and it then sorts the names in alphabetical order.
*************************************************************************/
#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;

// Function protoype
void sortNames(string[], int);

int main()
{
	ifstream inFile;             // File stream object
	string array[20] = {""};     // Empty string array capable of holding
                                 // 20 strings
	
	inFile.open("names.dat");    // Open file and validate 
	if(!inFile)
	{
		cout<<"File not found!"<<endl;
		exit(0);
	}

    // This loop reads a name from each line of the file into the array
	for(int i=0; i<20; i++)
	{
		getline(inFile, array[i]);
	}
	inFile.close();

    // Display unsorted array
	cout<<"Unsorted names list:\n";
	for(int i=0; i<20; i++)
		cout<<array[i]<<endl;
	cout<<"\n";

    // Call function to sort array
	sortNames(array, 20);

    // Display sorted array
	cout<<"Sorted names list:\n";
	for(int i=0; i<20; i++)
                cout<<array[i]<<endl;
        cout<<"\n";

	return 0;
}

/**********************************************************************
// sortNames function
// This function accepts a string array and its size and sorts it
// in alphabetical order
// parameters: string array, int size (size of array)
// return value: none
**********************************************************************/
void sortNames(string a[], int size)
{
	int pivot=1, i;
	string temp;
	while(pivot<size)
	{
		temp=a[pivot];
		i=pivot-1;
		while(i>=0 && a[i]>temp)
		{
			a[i+1]=a[i];
			i=i-1;
		}
		a[i+1]=temp;
		pivot=pivot+1;
	}
}
