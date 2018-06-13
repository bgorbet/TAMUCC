/*******************************************************************
//Name: Betty Gorbet
//Class: COSC 5311
//Instructor: Marwa Hassan
//Lab 5 Problem 1
//Date: Oct. 5, 2011
//Program description: This program gets a number of shirts and calculates the
price per shirt based on the number of shirts and the total price.
*********************************************************************/

#include <iostream>
#include <iomanip>

using namespace std;
int main()
{
	int n; /*Number of tshirts*/
	double ppshirt; /*Price per shirt*/
	double totalprice; /*Total cost of tshirts*/
	
	cout<<"How many shirts would you like?"<<endl;
	cin>>n;
	
	if(n<0)     		                        
		cout<<"Invalid input: Please enter a non-negative integer." <<endl;  
												/* Here it is determining */
	else										/* the price of each shirt */
	{											/* based on the number of */
		if(n<5)									/* shirts. If the user */	
			ppshirt=12;							/* enters a negative number */
		else if(n<=10)							/* the programs returns that */	
			ppshirt=12-(12*0.1);				/* the entry is not valid. */				
		else if(n<=20)                          /* If the user enters a */
			ppshirt=12-(12*0.15);               /* positive number then the*/
		else if(n<=30)							/* program calculates the */
			ppshirt=12-(12*0.2);                /* price per shirt and the */
		else if(n>30)							/* total price and returns */
			ppshirt=12-(12*0.25);				/* these values to the user.*/
	
		totalprice=n*ppshirt; 
	
		cout<<"The cost per shirt is $"<<setprecision(2)<<fixed<<ppshirt;
		cout<<" and the total cost is $"<<setprecision(2)<<fixed<<totalprice;
		cout<<endl;
		
		return 0;
	}
	
	return 0;
}
		
					
				