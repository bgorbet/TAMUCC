/*******************************************************************
Name: Betty Gorbet
Class: COSC 5311
Instructor: Marwa Hassan
Lab 3 Part 2
Sept. 21, 2011
This program converts a length to feet when given a length in centimeters.
*********************************************************************/
#include <iostream>
using namespace std;

int main ()
{
	double lengthFT;
	double lengthCM;
	
	//Get the length in feet.
	cout<<"Please input length in feet:"<<endl;
	cin>>lengthFT;
	
	//Calculate the length in centimeters.
	lengthCM=lengthFT*30.48;
	
	//Display the length in centimeters.
	cout<<"Length in centimeters is:"<<lengthCM<<endl;
	return 0;
}

	