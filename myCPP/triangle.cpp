/*******************************************************************
//Name: Betty Gorbet
//Class: COSC 5311
//Instructor: Marwa Hassan
//Lab 6 Problem 3
//Date: October 12, 2011
//Program description: This program creates a triangular pattern of
incremented numbers.
*********************************************************************/

#include<iostream>
using namespace std;

int main()
{
        int i, j; // i and j control # of rows and columns

	// The ouside loop controls the # of rows and the inside 
	// loop controls the # of items in each row.
	// This loop creates the top half of the triangle.
        for(i=0; i<5; i++)
        {
		int count=1;
                for(j=0; j<=i; j++)
                {
                        cout<<count<<"\t";
                        count++;
                }
                cout<<"\n";
        }

	// This loop creates the bottom half of the triangle.
	for(i=4; i>0; i--)
	{
		int count=1;
		for(j=0; j<i; j++)
		{
			cout<<count<<"\t";
			count++;
		}
		cout<<"\n";
	}
	return 0;
}
