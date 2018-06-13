/*******************************************************************
//Name: Betty Gorbet
//Class: COSC 5311
//Instructor: Marwa Hassan
//Lab 5 Problem 2
//Date: Oct. 5, 2011
//Program description: This is a menu driven program that calculates the
speed of sound through the user's choice of medium using the inputted distance.
*********************************************************************/
#include <iostream>
#include <iomanip>

using namespace std;
int main()
{
	int choice;  // This will represent the user's menu choice.
	double distance, speed; // The distance will be used to calculate the speed
	
	cout<<"***Welcome to Speed of Sound Calculator***"<<endl;
	cout<<" "<<endl;
	cout<<"Select a medium:"<<endl;             // This is the menu with 
	cout<<"1. Air"<<endl;                       // choices for air, water,
	cout<<"2. Water"<<endl;                     // and steel mediums.
	cout<<"3. Steel"<<endl;
	cout<<" "<<endl;
	cout<<"Enter your choice: "<<endl;          // The user is first prompted
	cin>>choice;                                // to enter a menu choice: 1, 2
	                                            // or 3.
	switch (choice)
	{
		case 1: cout<<"Enter the distance: "<<endl; // If the choice is valid
				cin>>distance;                      // the user is prompted to
				cout<<" "<<endl;                    // enter the distance.
				if (distance<0)
					cout<<"The distance must be greater than zero."<<endl;
				else              // If the distance is positive, it calculates
				{                 // the speed for the chosen medium. Otherwise,
					speed=1100/distance;   // it displays an error message.
					cout<<"A sound wave takes "<<setprecision(4)<<fixed;
					cout<<speed<<" seconds to travel "<<setprecision(4);
					cout<<fixed<<distance<<" feet through air."<<endl;
				}	
				break;
		case 2: cout<<"Enter the distance: "<<endl;
				cin>>distance;
				cout<<" "<<endl; // Spaces are left between prompts and displays
				if (distance<0)  // for organizational/visual purposes.
					cout<<"The distance must be greater than zero."<<endl;
				else
				{
					speed=4900/distance;
					cout<<"A sound wave takes "<<setprecision(4)<<fixed<<speed;
					cout<< " seconds to travel "<<setprecision(4)<<fixed;
					cout<<distance<<" feet through water."<<endl;
				}
				break;
		case 3: cout<<"Enter the distance: "<<endl;
				cin>>distance;
				cout<<" "<<endl;
				if (distance<0)
					cout<<"The distance must be greater than zero."<<endl;
				else
				{
					speed=16400/distance;
					cout<<"A sound wave takes "<<setprecision(4)<<fixed<<speed;
					cout<< " seconds to travel "<<setprecision(4)<<fixed;
					cout<<distance<<" feet through steel."<<endl;
				}
				break;             // If the menu choice is not valid, none of
		default: cout<<" "<<endl;  // cases will apply and the program displays
				 cout<<"The valid choices are 1 through 3.";// a default message
				 cout<<" Run the program again and select a valid choice.";
				 cout<<endl;
		}
	return 0;
}

			
					
	