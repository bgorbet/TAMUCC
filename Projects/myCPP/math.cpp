/*******************************************************************
//Name: Betty Gorbet
//Class: COSC 5311
//Instructor: Marwa Hassan
//Lab 6 Problem 2
//Date: October 12, 2011
//Program description: This is a math tutor program that randomly 
generates addition, subtraction, and multiplication problems and gets 
an answer from the user and gives feedback on the correctness of the 
answer. 
*********************************************************************/
#include<iostream>
#include<iomanip>
#include<cstdlib> // for the rand and srand functions
#include<ctime> // for the time function
using namespace std;

int main()
{
	unsigned seed = time(0); // needed to seed random # generator
	int choice;
	double x, y, ans1, ans2, ans3, sum, diff, prod;
	srand(seed); // seed the random # generator 
	
	// do-while driven menu 
	do
	{	
		// Display the menu
		cout<<"\t Math Tutor Menu \t"<<endl;
		cout<<"-------------------------"<<endl;
		cout<<"1. Addition problem"<<endl;
		cout<<"2. Subtraction problem"<<endl;
		cout<<"3. Multiplication problem"<<endl;
		cout<<"4. Quit this program"<<endl;
		cout<<"-------------------------"<<endl;
		cout<<"Enter your choice (1-4):";
		cin>>choice;
		
		// Use while loop to verify valid choice
		while(choice<1 || choice>4)
		{
			cout<<"Please enter 1, 2, 3, or 4:";
			cin>>choice;
		}
		
		cout<<"\n";

		// Switch function to generate problem based on choice
		switch(choice)
		{
			case 1: 	x=1+rand()%500, y=1+rand()%500;
				 	sum=x+y;
				 	cout<<setw(5)<<x<<endl;
				 	cout<<"+"<<setw(4)<<y<<endl;
				 	cout<<"-----"<<endl;
				 	cin>>ans1;
					cout<<"\n";
			 		if(ans1==sum)
			 			cout<<"Correct! That's right."<<endl;
			 		else
			 			cout<<"Sorry, the correct answer is "<<sum<<endl;
			 		cout<<"\n";
					break;

			case 2:		x=1+rand()%499, y=1+rand()%100;
			 		diff=x-y;
			 		cout<<setw(5)<<x<<endl;
			 		cout<<"-"<<setw(4)<<y<<endl;
			 		cout<<"-----"<<endl;
			 		cin>>ans2;
					cout<<"\n";
			 		if(ans2==diff)
			 			cout<<"Correct! That's right."<<endl;
			 		else
			 			cout<<"Sorry, the correct answer is "<<diff<<endl;
			 		cout<<"\n";
					break;

			case 3: 	x=1+rand()%100, y=1+rand()%9;
				 	prod=x*y;
				 	cout<<setw(5)<<x<<endl;
				 	cout<<"*"<<setw(4)<<y<<endl;
				 	cout<<"-----"<<endl;
				 	cin>>ans3;
					cout<<"\n";
				 	if(ans3==prod)
				 		cout<<"Correct! That's right."<<endl;
				 	else
				 		cout<<"Sorry, the correct answer is "<<prod<<endl;
				 	cout<<"\n";
					break;

			case 4: 	cout<<"Thank you for using Math Tutor."<<endl;
					cout<<"\n";
					break;
		}

	} while (choice != 4);

	return 0;
}
