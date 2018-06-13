/*******************************************************************
//Name: Betty Gorbret
//Class: COSC 5311
//Instructor: Marwa Hassan
//Lab 9 Problem 2 Resubmit
//Date: Nov 9, 2011
//Program description: This is a modular program that gets a number
// of rooms to be painted, price of paint per gallon, and square 
// footage of each rooms and calculates the number of gallons required,
// the hours of labor required, the cost of paint, the labor charges,
// and the total cost of the paint job.
*********************************************************************/
#include<iostream>
#include<cmath>    // For the ceil() function
#include<iomanip>  // For the setprecision() function
using namespace std;

// Function prototypes
int getNumberOfRooms();
double getPaintPrice();
void getWallSquareFeet(double [], int);
int numberOfGallons(double);
double laborHours(double);
void displayCost(int, double, double);

const int SIZE = 100;	  // Set boundary for array high since array
			  // size is inknown at this point.

double squareFeet[SIZE];  // Difine array to hold square feet of each
			  // room, globally so all elements are 
			  // initialized to 0.

// Main function
int main()
{
	// Declare variables 
	int totalGallons;	   // The total gallons of paint needed
	int numberOfRooms; 	   // The number of rooms to be painted
	double pricePerGallon;     // The price per gallon of paint
	double totalHours;	   // The total labor hours needed
	
	// Set the format for double values
	cout<<fixed<<showpoint<<setprecision(2);

	// Call function getNumberOfRooms and store the returned value
	// to numberOfRooms
	numberOfRooms = getNumberOfRooms();

	// Call function getPaintPrice and store returned value to
	// pricePerGallon	
	pricePerGallon = getPaintPrice();
	
	// Call getWallSquareFeet function to set values of elements
	// in squareFeet array for the number of rooms entered
	getWallSquareFeet(squareFeet, numberOfRooms);

	// Calculate total square feet
	double totalSquareFeet=0; // Initialize the accumulator
	for(int i=0; i<numberOfRooms; i++)
	{
		totalSquareFeet+=squareFeet[i];
	}

	// Call numberOfGallons function and store returned value to
	// total Gallons
	totalGallons = numberOfGallons(totalSquareFeet);

	// Call laborHours function and store returned value to
	// totalHours
	totalHours = laborHours(totalSquareFeet);
	
	// Call displayCosts function to display the charges
	displayCost(totalGallons, pricePerGallon, totalHours);
	
	return 0;
}

//*************************************************
// getNumberOfRooms function
// This function prompts the user for the number
// of rooms, validates and returns it to main function.
// 
// Return Value
// -------------
// int               the validated number of rooms
//
// Parameters
// -------------
// none
//*************************************************
int getNumberOfRooms()
{
	int rooms; // This will be the number of rooms
	
	// Get the number of rooms
	cout<<"Enter the number of rooms to be painted: ";
	cin>>rooms;
	
	// Validation loop
	while(rooms<1)
	{
		cout<<"ERROR: Number of rooms must be greater than or";
		cout<<" equal 1.\nEnter the number of rooms to be painted: ";
		cin>>rooms;
	}
	return rooms;
}

//***************************************************
// getPaintPrice function
// This function  prompts the user to enter the
// price of the paint per gallon, validates and returns it 
// to main function.
// 
// Return Value
// ------------
// double                  the validated price of paint
//
// Parameters
// ------------
// none
//***************************************************
double getPaintPrice()
{
	double price; // This will be the price per gallon of paint
	
	// Get the price of paint per gallon
	cout<<"Enter the price of the paint, per gallon: ";
	cin>>price;
	
	// Validation loop
	while(price<10.00)
	{
		cout<<"ERROR: Paint price must be at least $10.00.\n";
		cout<<"Enter the price of the paint, per gallon: ";
		cin>>price;
	}
	return price;
}

//********************************************************
// getWallSquareFeet function
// This function prompts the user to enter the square feet
// of wall space for each room, validates and stores it to
// the squareFeet array.	
//
// Return Value
// -------------
// void               Since array arguements are passed by
//			reference, the orignial array elements
//  			are modified without needing to return
//  			values to main.
//
// Parameters
// -------------
// double sqFeet[]    accepts address of array 
// int numOfRooms     size of array
//*********************************************************
void getWallSquareFeet(double sqFeet[], int numOfRooms)
{
	// Get the square feet for each room and store in array
	for(int index=0; index<numOfRooms; index++)
	{
		cout<<"Room "<<index+1<<": Enter the area of wall space"; 
		cout<<" in square feet: ";
		cin>>sqFeet[index];
		while(sqFeet[index] <= 0)
		{
			cout<<"ERROR: Area of wall space must be"; 
			cout<<" greater than zero.\n";
			cout<<"Room "<<index+1<<": Enter the area of"; 
			cout<<" wall space in square feet: ";
			cin>>sqFeet[index];
		}
	}
}

//************************************************************
// numberOfGallons function
// This function accepts as an argument the total square feet
// of wall space and calculates the number of gallons of paint
// required. The number of gallons is returned to main.
//
// Return Value
// -------------
// int                The number of gallons
//
// Parameters
// -------------
// double totalSqFt   The total square feet of wall space
//*************************************************************
int numberOfGallons(double totalSqFt)
{
	int gallons; // This will be the number of gallons
	
	// Calculate number of gallons from total square feet
	gallons = static_cast<int>(ceil(totalSqFt/115));
	
	return gallons;
}

//*************************************************************
// laborHours function
// This function accepts as an argument the total square feet
// of wall space and calculates the hours of labor needed to
// paint that amount of wall space. The number of hours is
// returned to main.
//
// Return Value
// -------------
// double               The total number of hours
//
// Parameters
// -------------
// double totSqFt       The total square feet of wall space
//**************************************************************
double laborHours(double totSqFt)
{
	double hours; // This will be the number of hours;
	
	// Calculate the number of hours from the total square feet
	hours = (totSqFt/115)*2;
	
	return hours;
}

//**************************************************************
// displayCost function
// This function accepts as arguments the number of gallons of
// paint, the price per gallon, and hours of labor required for
// the job. It calculates and displays the total estimated charges.
//
// Return Value
// ----------------
// none
// 
// Parameters
// ----------------
// int numGallons		The total number of gallons
// double ppGallon		The price per gallon
// double hoursOfLabor		The total hours of labor
//**************************************************************
void displayCost(int numGallons, double ppGallon, double hoursOfLabor)
{
	double paintCost, laborCharges; // Cost for paint and labor
	double totalCharges; 		// Total cost
	
	// Calculate cost for paint, labor, and total costs
	paintCost = ppGallon*numGallons;
	laborCharges = 18.00*hoursOfLabor;
	totalCharges = paintCost + laborCharges;
	
	// Display the number of gallons and hours, the charges for paint
	// and labor, and the total charges.
	cout<<"ESTIMATED CHARGES"<<endl;
	cout<<"-------------------------\n";
	cout<<"Gallons of Paint:\t "<<numGallons<<endl;
	cout<<"Hours of labor:\t\t "<<hoursOfLabor<<endl;
	cout<<"Paint cost:\t\t$"<<paintCost<<endl;
	cout<<"Labor charges:\t\t$"<<laborCharges<<endl;
	cout<<"-------------------------\n";
	cout<<"Total charges:\t\t$"<<totalCharges<<endl;
}
