/*******************************************************************
Name: Betty Gorbet
Class: COSC 5311 Foundations in Programming and Problem Solving I
Instructor: Marwa Hassan
Lab 3 Part I
Sept. 14, 2011
This Program caluculates the user's pay.
*********************************************************************/

#include <iostream>
using namespace std;

int main()
{
	double hours;
	double rate;
	double pay;
	
	// Get the number of hours worked.
	cout << "How many hours did you work? "<<endl;
	cin >> hours;
	
	// Get the hourly pay rate.
	cout << "How much do you get paid per hour? "<<endl;
	cin >> rate;
	
	// Calculate the pay.
	pay = hours * rate;
	
	// Display the pay.
	cout << "You have earned $" << pay << endl;
	return 0;
}


	
	
	