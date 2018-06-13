#include<iostream>
#include<fstream>
using namespace std;

int main()
{
	int userIn;
	ofstream outFile;
	outFile.open("numbers.txt.");

	for(int count=0; count<3; count++)
	{
		cout<<"Enter integer: ";
		cin>>userIn;
		outFile<<userIn<<"\t"<<endl;
	}
	outFile.close();
	return 0;
}
