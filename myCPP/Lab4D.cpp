/*******************************************************************
Name: Betty Gorbet
Class: COSC 5311
Instructor: Marwa Hassan
Lab 4 Problem 4
Date: 9/28/11
Program description: This program inputs the diameter of a pizza and 
determines the number of slices that can be taken from a pizza of that size.
*********************************************************************/
#include <iostream>
#include <iomanip>

using namespace std;
int main()
{
	double d, r, A; // diameter, radius, and Area of pizza.
	int n; // number of slices.
	const double PI=3.14159; // the constant value of pi.
	
	cout << "Please enter the diameter of the pizza in inches." << endl;
	cin >> d;
	// Gets the diameter of the pizza.
	
	r=d/2;
	A=PI*(r*r);
	n=static_cast<int>(A/14.125);
	// Calculates the radius, area, and number of slices.  The double 
	// on the right side of the expression n=A/14.125 is autmatically 
	// converted to an integer because the variable on the left in an 
	// integer, which is the desired outcome.
	
	cout << "The number of slices is: " << n << endl;
	//displays the number of slices.
	
	return 0;
}




	