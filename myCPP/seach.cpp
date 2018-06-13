#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

void showArray(int[], int);
void sort(int[], int);
int search(int[], int, int);
int median(int[], int);
int findMin(int[], int, int);

int main()
{
    ifstream inputFile;
    char filename[20];
    int array[50], number, position, count=0;
    
    cout<<"Enter filename: ";
    cin>>filename;
    
    inputFile.open(filename);
    
    while(!inputFile)
    {
                     cout<<"File not fount. Enter filename: ";
                     cin>>filename;
		     inputFile.open(filename);
    }
    
    while(count<50 && inputFile>>array[count])
                    count++;
                    
    inputFile.close();

    showArray(array, count);
    
    cout<<"\nNumber of items: "<<count<<endl;
	
    sort(array, count);  

    showArray(array, count);
         
    cout<<"Enter an integer: ";
    cin>>number;
    
    position=search(array, count, number);
    
    if(position= -1)
                 cout<<"The number was not in the file.\n";
    else
    {
                 cout<<number<<" is item number "<<position+1<<" in the file.";
                 cout<<"\n";
    }
    
    cout<<"The median is "<<median(array, count)<<endl;
    
    return 0;
}
    
void showArray(int array[], int size)
{
         	// This for loops displays the formatted list
          for(int i=0; i < size; i+=6)
	      {
	              	for(int j = i; j < i+6 && j < size; j++)
        		    	cout<<setw(10)<<array[j];
     	          	cout<<endl;
           }
}

void sort(int array[], int size)
{
          int index=0, unsortedMin;
          while(index<size-1)
          {
                        unsortedMin=findMin(array, size, index);
                        swap(array[index], array[unsortedMin]);
                        index++;
          }
}

int findMin(int array[], int size, int index)
{
         int smallestAt, i, j;
         smallestAt=i;
         j=i+1;
         while(j<size)
         {
                      if(array[j]<array[smallestAt])
                            smallestAt=j;
                      j++;              
         }
         return smallestAt;
}

int search(int array[], int size, int target)
{
         int position= -1;
         int first=0;
         int last=size-1;
         
         while (last >= first   &&   position== -1)
         {
               int mid=(first+last)/2;
               if(array[mid] == target)
                    position = mid;
               else if(array[mid] > target) 
                    last = mid-1;
               else if(array[mid] < target)
                    first = mid+1;
         }
     
         return position;
}

int median(int array[], int size)
{
         if(size%2==0)
               return (array[size/2]+array[(size/2)-1])/2;
         else
               return array[size/2];
}
