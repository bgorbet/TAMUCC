#include <iostream>
using namespace std;

void rotateArray(float array[], int size)
{
	float temp=array[size-1];
	for(int i=size-1; i>0; i--)
		array[i]=array[i-1];
	array[0]=temp;
}

int main()
{
	float array[]={5.8, 2.6, 9.1, 3.4, 7.0};
	
	rotateArray(array, 5);

	for(int i=0; i<5; i++)
		cout<<array[i]<<" | ";
	return 0;
}
