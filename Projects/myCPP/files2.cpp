#include<iostream>
#include<fstream>
using namespace std;

int main()
{
	ifstream inFile;
	inFile.open("numbers.txt");
	int num;
	int sum = 0;

	if(!inFile)
	{
		cout<<"File not found!\n";
		exit(0);
	}

	else
	{	
		while(inFile>>num)
		{
			cout<<num<<" ";
			sum+=num;
		}
		cout<<"\n";
		cout<<sum<<endl;
		cout<<sum/3<<endl;
	}
	inFile.close();
	return 0;
}
