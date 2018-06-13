/*******************************************************************
//Name: Betty Gorbet
//Class: COSC 5311
//Instructor: Marwa Hassan
//Lab 7 Problem 2
//Date: Oct. 19, 2011
//Program description: This program calculates which division in a
//company's four divisions had the highest quarterly sales.
*********************************************************************/
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

// prototypes for inputDiv and findHighest
double inputDiv(string division);
void findHighest(double total1, double total2, double total3, double total4);

// this is the main function
int main()
{
	double nE, sE, nW, sW; // the variables for the quarterly sales 
			       // for each division.
	
	// Call the inputDiv function for each division
	nE = inputDiv("Northeast");
	sE = inputDiv("Southeast");
	nW = inputDiv("Northwest");
	sW = inputDiv("Southwest");
	cout<<"\n"; 

	findHighest(nE, sE, nW, sW); // Call the findHighest function
} 

//********************************************************************
// inputDiv Function
// This function asks the user for a division's quarterly sales figure,
// validates the input, and then returns it to main.
//
// Return Value
// ------------
// double                    the division's quarterly sales figure
//
// Parameters
// ------------
// division		     string for the name of the division 
//*******************************************************************
double inputDiv(string division)
{
	double total;
	cout<<"Enter the quarterly sales figure for the "<<division<<" division: ";
	cin>>total;
	while(total<0.00)
		{
		cout<<"The quarterly sales figure must be a positive dollar";
		cout<<" amount.\n";
		cout<<"Enter the quarterly sales figure for the "<<division;
		cout<<" division: ";
		cin>>total;
		}
	return total;
}

//********************************************************************
// findHighest Function
// This function is passed the four sales figures and finds which is
// the largest and displays which division it is along with it's sales figure.
//
// Return Value
// ------------
// void				this function does not return anything
//
// Parameters
// ------------
// total1			the total for the Northeast division
// total2			the toal for the Southeast division
// total3			the total for the Northwest division
// total4			the total for the Southwest division
//*******************************************************************
void findHighest(double total1, double total2, double total3, double total4)
{
	 // set format for doubles
        cout<<fixed<<showpoint<<setprecision(2);

	if(total1>total2 && total1>total3 && total1>total4)
		{
		cout<<"The Northeast division had the highest sales this quarter.\n";
		cout<<"That division's sales were $"<<total1<<endl;
		}
	else if(total2>total1 && total2>total3 && total2>total4)
		{
		cout<<"The Southeast division had the highest sales this quarter.\n";
		cout<<"That division's sales were $"<<total2<<endl;
		}
	else if(total3>total1 && total3>total2 && total3>total4)
		{
		cout<<"The Northwest division had the highest sales this quarter.\n";
		cout<<"That division's sales were $"<<total3<<endl;
		}
	else if(total4>total1 && total4>total2 && total4>total3)
		{
		cout<<"The Southwest division had the highest sales this quarter.\n";
		cout<<"That division's sales were $"<<total4<<endl;
		}
}
