# include <iostream>
using namespace std;

void mySwap(int &x, int &y);

int main()
{
	int a, b, c;
	
	cout<<"Enter a, b, and c: \n";
	cin>>a>>b>>c;

	if(a>b)
		mySwap(a,b);
	if(b>c)
		mySwap(b,c);
	if(a>b)
		mySwap(a,b);

	cout<<"The order is: "<<a<<" "<<b<<" "<<c<<endl;
	return 0;
}

void mySwap(int &x, int &y)
{
	int temp;
	temp = x;
	x=y;
	y=temp;
}
