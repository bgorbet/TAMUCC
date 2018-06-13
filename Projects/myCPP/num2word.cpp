#include<iostream>
#include<string>
using namespace std;

string num2word(int num);

int main()
{
	int integer;
	cout<<"enter an integer in the range 1-9: ";
	cin>>integer;
	cout<<num2word(integer)<<endl;
}

string num2word(int num)
{
	string result;
	switch(num)
	{
		case 1:	result = "one";
			break;
		case 2: result = "two";
			break;
		case 3:	result = "three";
			break;
		case 4: result = "four";
			break;
		case 5: result = "five";
			break;
		case 6: result = "six";
			break;
		case 7: result = "seven";
			break;
		case 8: result = "eight";
			break;
		case 9: result = "nine";
			break;
		default:cout<<"you did not enter a number in the range "; 
			cout<<"1-9.";
			break;
	}
	return result;
}
