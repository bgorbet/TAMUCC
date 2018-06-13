/*******************************************************************
// Name: Betty Gorbet
// Class: COSC 5311
// Instructor: Marwa Hassan
// Lab 10 
// Date: Nov 9, 2011
// Program description: This program reads a file entered by the user
// and calculates and displays the average, highest, lowest, number
// of temperatures greater than or equal 85, and converts each 
// temperature to celsius and writes it to a file called celsius.txt
*********************************************************************/
#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;

// Function Prototypes
double getAverage(const double [], const int);
double getHighest(const double [], const int);
double getLowest(const double [], const int);
int getNumber85plus(const double [], const int);
void Celsius(const double [], const int);

// Array that will hold up to 100 temperatures
// Declared globally to initialize all elements to 0
const int ARRAY_SIZE = 100;
double temperatures[ARRAY_SIZE];

int main()
{
	ifstream fileIn;	// Input file stream object
	char filename[20];	// Character array that will hold filename
	int count = 0;		// Count will track number of temps added
				// to array
	
	// Format for numeric outputs
	cout << fixed << showpoint << setprecision(2);

	// Get the filename	
	cout << "Enter the filename of a file containing 100 temperatures ";
	cout << "or less (in Fahrenheit) or ctrl+c to exit.  The filename ";
	cout << "must be 20 characters or less.\n";
	cin >> filename;
	cout << "\n";

	// Open the file
	fileIn.open(filename);
	
	// Validate file exists, if not display error and ask to re-enter
	while(!fileIn)
	{
		cout << "File not found.  Enter another filename.\n";
		cin >> filename;
	}
	
	//  Read temps from file
	while(count < ARRAY_SIZE && fileIn >> temperatures[count])
			count++;
	
	// Close file
	fileIn.close();
		
	// Display total number of temps in file
	cout << "Total number of temperatures: " << count << endl;
	cout << "\n";
	
	//  Call getAverage function and display returned value
	cout << "The average temperature is ";
	cout << getAverage(temperatures, count) << " degrees Fahrenheit.\n";
		
	// Call getHighest function and display returned value
	cout << "The highest temperature is ";
	cout << getHighest(temperatures, count) << " degrees Fahrenheit.\n";
	
	// Call getLowest function and display returned value
	cout << "The lowest temperature is ";
	cout << getLowest(temperatures, count) << " degrees Fahrenheit.\n";
	
	// Call getNumber85plus function and display returned value
	cout << "The number of temperature 85+ degrees Fahrenheit is ";
	cout << getNumber85plus(temperatures, count) <<endl;
	cout << "\n";
		
	// Call Celsius function and display a status message
	cout << "Creating file celsius.txt... \n";
	cout << "\n";
	Celsius(temperatures, count);

	return 0;
}
	
//*************************************************************
// getAverage function
// This function accepts the array of temperatures and a
// constant integer representing the number of temperatures in
// the array. It then calculates the average tempterature and
// returns it to main.
//
// Return Value
// ------------
// double			Average temperature
//
// Parameters
// ------------
// const double temparray[]     Array of temperatures from file
// const int count              Number of temperatures in array
//*************************************************************
double getAverage(const double temparray[],const int count)
{
	double sum = 0;  // Initialize accumulator for sum
	double average;  // Will hold the average temp
	
	// Calculate sum of temps in array
	for(int i=0; i < count; i++)
		sum += temparray[i];
	
	// Divide by number of temps to get average
	average = sum/(count);

	return average;
}

//*************************************************************
// getHighest function
// This function accepts the array of temperatures and a
// constant integer representing the number of temperatures in
// the array. It then finds the highest temperature and
// returns it to main.
//
// Return Value
// ------------
// double			Highest temperature
//
// Parameters
// ------------
// const double temparray[]     Array of temperatures from file
// const int count              Number of temperatures in array
//*************************************************************
double getHighest(const double temparray[],const int count)
{
	double highest;		// This will hold highest temp
	highest = temparray[0]; // Set highest equal first temp
				// in array
	
	// This loops goes through array one element at a time
        // and assigns each to highest if it was greater than 
        // the previous element
	for(int i=1; i < count; i++)
	{
		if (temparray[i] > highest)
			highest = temparray[i];
	}
	return highest;
}

//*************************************************************
// getLowest function
// This function accepts the array of temperatures and a
// constant integer representing the number of temperatures in
// the array. It then finds the lowest temperature and
// returns it to main.
//
// Return Value
// ------------
// double			Lowest temperature
//
// Parameters
// ------------
// const double temparray[]     Array of temperatures from file
// const int count              Number of temperatures in array
//*************************************************************
double getLowest (const double temparray[],const int count)
{
	double lowest;		// This will hold lowest temp
	lowest = temparray[0];	// Set lowest equal first temp
				// in array
	
	// This loops goes through array one element at a time
	// and assigns each to lowest if it was less than the
	// previous element
	for(int i=1; i < count; i++)
	{
		if(temparray[i] < lowest)
			lowest = temparray[i];
	}
	return lowest;
}

//*************************************************************
// getNumber85plus function
// This function accepts the array of temperatures and a 
// constant integer representing the number of temperatures in
// the array.  It finds the number of temperatrues greater than
// or equal 85 and returns it to main.
//
// Return Value
// ------------
// int                    	Number of temperatures greater
//				than or equal 85 F
//
// Parameters
// ------------
// const double temparray[]     Array of temperatures from file
// const int count              Number of temperatures in array
//*************************************************************
int getNumber85plus(const double temparray[], const int count)
{
	int total = 0;	// This will keep track of the number
			// of temps >= 85
	
	// This loop examines each temp and tallies the 
	// number >= 85 using total
	for(int i=0; i < count; i++)
	{
		if(temparray[i] >= 85)
			total +=1;
	}
	return total;
}

//*************************************************************
// Celsius function
// This function accepts the array of temperatures and a 
// constant integer representing the number of temperatures in
// the array.  It then creates an array containing the 
// temperatures converted to celsius.  It then writes these
// converted temperatures to a file called celsius.txt and
// displays the file's contents.
//
// Return Value
// ------------
// void
//
// Parameters
// ------------
// const double temparray[]	Array of temperatures from file
// const int count 		Number of temperatures in array
//*************************************************************
void Celsius(const double temparray[], const int count)
{
	// Declare output file stream object and array that
	// will hold temps in celsius
	ofstream fileOut;
	double celsiusArray[count];
	
	// Convert each temp to celsius and store in new array
	for(int i=0; i < count; i++)
		celsiusArray[i] = (temparray[i]-32)*0.55556;
	
	// Create and open celsius.txt
	fileOut.open("celsius.txt");
	
	// Write contents of celsiusArray to celsius.txt
	for(int i=0; i < count; i++)
		fileOut << celsiusArray[i] << endl;
	
	// Display contents of celsius.txt	
	cout << " Contents of celsius.txt:\n";
	for(int i=0; i < count; i++)
		cout << celsiusArray[i] << endl;

	// Close celsius.txt
	fileOut.close();
}
