/*******************************************************************
Name: Betty Gorbet
Class: COSC 5311
Instructor: Marwa Hassan
Lab 4 Problem 1
Date: 9/28/11
Program description: This program will input the value of two sides of a right 
triangle and then determine the size of the hypotenuse.
*********************************************************************/
#include <iostream>
#include <cmath> // needed for math functions lide sqrt()
#include <iomanip>

using namespace std;
int main()
{
	float a,b; // the smaller two sides of the triangle
	float hyp; // the hypotenuse calculated by the program
	
	cout << "Please input the value of the two sides" << endl;
	cin >> a >> b;
	
	hyp=sqrt(a*a+b*b); // this calculates the hypotenuse
	
	cout << "The sides of the right triangle are "<< a <<" and "<< b << endl;
	cout << "The hypotenuse is " <<setprecision(2)<< fixed << hyp << endl; // Displays
	// the hypotenuse rounded to two decimal places
	
	return 0;
}