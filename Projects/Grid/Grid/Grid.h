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

#ifndef _GRID_H_
#define _GRID_H_
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

//*****************************************************************************
//
// Grid Class
//
// This class is used to implement a component labeling program.
//
//*****************************************************************************
class Grid{
public:
	Grid();
	~Grid();
	void storeGrid(fstream &inputFile);
	void initComponents();
	void displayGrid();
	void Color();
	void Tally(int count);
	void numComponents();
	string grid_array[102];

private:
	int N, M, c, n;
	int * sizes_array;
	void Mark(int &n, int i, int j);
};

#endif

