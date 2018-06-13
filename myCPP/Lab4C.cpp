/*******************************************************************
Name: Betty Gorbet
Class: COSC 5311
Instructor: Marwa Hassan
Lab 4 Problem 3
Date: 9/28/11
Program description: This program inputs the amount of chairs in three styles
and displays the total dollar sales of each style as well as the total sales of 
all chairs.
*********************************************************************/
#include <iostream>
#include <iomanip>

using namespace std;
int main ()
{
	int AmCol, Mod, FreCla; // The three types of chairs are American Colonial, 
	// Modern, and French Classical.
	double AmColTotal, ModTotal, FreClaTotal, AllTotal; // The total sales for 
	// each style of chair and all styles combined.
	
	cout << "Please input the number of American Colonial chairs sold." << endl;
	cin >> AmCol;
	cout << "Please input the number of Modern chairs sold." << endl;
	cin >> Mod;
	cout << "Please input the number of French Classical chairs sold." << endl;
	cin >> FreCla;
	// Gets the number of each syle sold.
	
	AmColTotal=AmCol*85.00;
	ModTotal=Mod*57.50;
	FreClaTotal=FreCla*127.75;
	AllTotal=AmColTotal+ModTotal+FreClaTotal;
	// Calculates totals of each sale and overall sales.
	
	cout << "The total sales of American Colonial chairs: $" << setprecision(2) << fixed << AmColTotal << endl;
	cout << "The total sales of Modern chairs: $" << setprecision(2) << fixed << ModTotal << endl;
	cout << "The total sales of French Classical chairs: $" << setprecision(2) << fixed << FreClaTotal << endl;
	cout << "The total sales of all chairs: $" << setprecision(2) << fixed << AllTotal << endl;
	// Displays the totals of each sale and overall sales in fixed notation with two decimals of precision.
	
	return 0;
}

	