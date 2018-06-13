#include<iostream>
#include<iomanip>
using namespace std;

int lcm(int, int);


int main()
{
	int a, b;

	cout<<"a,b: :";
	cin>>a>>b;

	cout<<lcm(a, b)<<endl;

	return 0;
}

int lcm(int a, int b)
{
	int n;
    	for(n=1;;n++)
    	{
  		if(n%a == 0 && n%b == 0)
  	  	return n;
    	}
}
