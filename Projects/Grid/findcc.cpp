//*****************************************************************************
//
// Annie Gorbet
// Data Structures
// Programming Project #1: Recursion
// Jan 17, 2012
// Instructor: Dr. Michael C. Scherger
//
//*****************************************************************************


//*****************************************************************************
//
// Includes and Defines
//
//*****************************************************************************
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "Grid.h"

using namespace std;


//*****************************************************************************
//
// Function Prototypes
//
//*****************************************************************************
bool openFile(fstream&, char []);


//********************************************************************
//
// Main
//
// Calls all functions and methods to open and read a file from
// command line, then colors the components and outputs the grid to
// screen along with the number of components
//
// Return Value
// ------------
// int
//
// Function Parameters
// ----------------
// arc		int		value		number of command line arguements
// *argv[]	int		value		string from command line
//
//*******************************************************************
int main(int argc, char *argv[])
{
	fstream inputFile;  //Create fstream object
	Grid theGrid;       //Create Grid object
	
	
	if ( argc != 2 ) // argc should be 2 for correct execution
	
        cout<<"usage: findcc <filename>\n";
       

	if(!openFile(inputFile, argv[1])) //Call openFile function 
	
		exit(EXIT_FAILURE);
       
	
	theGrid.storeGrid(inputFile);     //Call storeGrid, Grid member function
	
	
	inputFile.close();                //Close input file
	
	
	theGrid.Color();                  //Call Color, Grid member function
	
	
	theGrid.displayGrid();            //Call displayGrid, Grid member function
	
	
	theGrid.numComponents();          //Call numComponents, Grid member function
	
	
	return 0;
}

//********************************************************************
//
// Open File
//
// This function opens a file for input
//
// Return Value
// ------------
// bool                         True/False if open is successful
//
// Function Parameters
// ----------------
// inputFile	fstream		file stream
// *filename[]	char		points to name of file from command line
//
//*******************************************************************
bool openFile(fstream& inputFile, char filename[])
{
	inputFile.open(filename); //Open input file
	if(!inputFile)
	{   //Test if input file opened successfully
		cout << "ERROR: file could not be opened.\n";
		return false;
	}
	else
		return true;
}

