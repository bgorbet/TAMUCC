/*******************************************************************
//Name: Betty Gorbet
//Class: COSC 5311
//Instructor: Marwa Hassan
//Lab 6 Problem 4
//Date: October 12, 2011
//Program description: This program gets the number of days the user
has worked and displays pennies earned each day, with the amount 
earned doubling each day.  It displays the total earned at the end.
*********************************************************************/

#include<iostream>
#include<iomanip>
using namespace std;

int main()
{	// assign and initialize variables
	int i, days;
	double amount=0.01, total=0.00; 
	
	//Get # of days worked.
	cout<<"Please enter the number of days worked: ";
	cin>>days;
	cout<<"\n";
	
	// set format for double variables (amount & total).
	cout<<fixed<<showpoint<<setprecision(2);
	
	// Use while loop to verify valid input.
	while(days <=0)
	{
		cout<<"The number of days must be at least one.\n";
		cout<<"Enter the number of days: ";
		cin>>days;
		cout<<"\n";
	}
	
	// Display chart of Days and Amount Earned.
	cout<<"Day\t\tAmount Earned\n";
	cout<<"-----------------------------\n";
	
	// This loop displays and increments days, dispalays and 
	// doubles pennies earned, and displays total at end.
	for(i=1; i<=days; i++)
	{
		cout<<i<<"  \t\t$ "<<amount<<endl;
		total+=amount;
		amount*=2;
	}
	
	cout<<"-----------------------------\n";
	cout<<"Total   \t$ "<<total<<endl;
	cout<<"\n";

	return 0;
}
