/*******************************************************************
Name: Betty Gorbet
Class: COSC 5311
Instructor: Marwa Hassan
Lab 4 Problem 2
Date: 9/28/11
Program description: This program inputs 3 grades and determines the average
to two decimal places.
*********************************************************************/
#include <iostream>
#include <iomanip>

using namespace std;
int main()
{
	double grade1, grade2, grade3; // the three grades
	double average; // the average of the three grades
	
	cout << "Please input the first grade" << endl;
	cin >> grade1;
	cout << "Please input the second grade" << endl; 
	cin >> grade2;
	cout << "Please input the thrid grade" << endl; 
	cin >> grade3;
	// The three grades are inputed.
	
	average=(grade1+grade2+grade3)/3; // The average is calculated.
	
	cout << "The average of the three grades is " << setprecision(2) << fixed << average << endl;
	// The average is outputed in fixed point notation with two decimal places of precision.
	
	return 0;
}
	