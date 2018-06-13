# include<iostream>
using namespace std;

int alternatingSum(int N);

int main()
{
	int x;
	
	cout<<"Enter positive integer: ";
	cin>>x;
	cout<<alternatingSum(x)<<endl;
}

int alternatingSum(int N)
{
	int sum=0, i=1;
	for(i=1; i<=N; i++)
	{
		if(i%2==1)
			sum+=i;
		else
			sum-=i;
	}
}
