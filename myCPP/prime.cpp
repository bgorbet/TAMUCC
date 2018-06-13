/*******************************************************************
//Name: Betty Gorbet
//Class: COSC 5311
//Instructor: Marwa Hassan
//Lab 15
//Date: Dec 4, 2011
//Program description: This program determines whether the user's
// entry is prime or not
*********************************************************************/
#include<iostream>
using namespace std;

// Function prototype
bool isPrime(int);

int main()
{
    int number;   // Variable for user entry
    bool prime;   // Variable to flag if entry is prime or not prime
    
    // Get user entry
    cout<<"Enter a number and I'll tell you whether it is prime: ";
    cin>>number;
    
    // Loops to control for only accepting positive entries
    while(number<1)
    {
       cout<<"Only positive numbers can be prime.  Enter a positive number: ";
       cin>>number;
    }
    
    // Call function to determine if entry is prime
    prime=isPrime(number);
    
    // Display result
    if(prime)
       cout<<number<<" is prime."<<endl;
    else if(!prime)
       cout<<number<<" is NOT prime."<<endl;
    
    return 0;
}
/****************************isPrime************************************
// This function accepts a number and returns true if is is prime and
// false if it is not prime.
// Parameters: int n (query number)
// Return value: bool p (true if query is prime, false if query is 
// not prime)
***********************************************************************/
bool isPrime(int n)
{
     bool p=true;
     for(int i=2; i<n; i++)
     {
        if(n%i==0)
           p=false;
     }
     
     return p;
}
                        

