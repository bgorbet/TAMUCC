//*****************************************************************************
//
// Annie Gorbet
// Data Structures
// Programming Project #1: Recursion
// Jan 17, 2012
// Instructor: Dr. Michael C. Scherger
//
//*****************************************************************************


//*****************************************************************************
//
// Includes and Defines
//
//*****************************************************************************

#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include "Grid.h"

using namespace std;

//This is a look up table for cycling through color tags in the Mark method
const char color_array[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

//*******************************************************************
//
// Default Constructor
//
// This Method initializes variables N, M, c, n, and sizes_array pointer
// in the Class
//
//*******************************************************************
Grid::Grid()
{
            N=0; //No. of rows
            M=0; //No. of columns
            c=0; //Counter for no. of components
            n=0; //Keeps track of size of each component
	        sizes_array=NULL; //Pointer to array that keeps track of sizes	    
}


//********************************************************************
//
// Default Destructor
//
// deletes the memory allocation for the arrays in the Class
//
//*******************************************************************
Grid::~Grid()
{
             delete [] sizes_array;
}


//********************************************************************
//
// Store Grid Method
//
// This method reads data from a file and stores the dimensions of
// the grid, and then stores the grid its self into an array of
// strings, adding a border of '#' characters around it.
// Also, it calls the initComponents method.
// 
// Reference Parameters
//----------------------
// inputFile            fstream        the input file is passed to 
//                                     storeGrid by reference
//
// Local Variables
//-----------------
// border_string        string         To make a top and bottom '#' border
// i                    int            Index variable for reading file
//
//*******************************************************************
void Grid::storeGrid(fstream &inputFile)
{
     string border_string;        //To make a top and bottom '#' border
     int i=1;                     //Index variable for reading file

     inputFile>>N>>M;             //Get first line with dimensions & store
     inputFile.ignore();          //Ignore the rest of this line
     
     while(!inputFile.eof())      //Read each line until end of file
     {                            //into array, starting at 2nd element
                  getline(inputFile, grid_array[i]);
                  i++;
     }

     system("clear");             //Clear screen

     for(int x=0; x<N+2; x++)     //This loop displays the grid that was just
     {                            //read in from the file
	    for(int y=0; y<M+2; y++)
        {
	            cout<<grid_array[x][y];
	    }
        cout<<"\n";
     }

     cout<<"\n";

     
     for(int x=0; x<M+2; x++)    //Create top and bottom '#' border
     {
             border_string+='#';
     }
     
     grid_array[0] = border_string;   //Add '#' border to top and bottom
     grid_array[N+1] = border_string; 
     
     for(int x=1; x<N+1; x++)         //Add '#' to ends of strings
     {
             grid_array[x] = '#'+grid_array[x]+'#';
     }
     initComponents();       //Call initComponenrts member function
}


//********************************************************************
//
// initComponents 
//
// This method initializes the variables and array used to keep
// track of the sizes of the connected components.
//
//*******************************************************************
void Grid::initComponents()
{
     c=0; //Initialize component counter to 0               
     sizes_array=new int[N*M]; //Allocate memory to sizes_array based on N & M

     for(int i=0; i<M*N; i++)  //Initialize sizes_array to empty
     {
             sizes_array[i]=0;
     }
}


//********************************************************************
//
// Display Grid Method
//
// This method outputs the grid to the screen.
//
//*******************************************************************
void Grid::displayGrid()
{
     //Nested for loops display the grid
     for(int i=1; i<N+1; i++)
     {
             for(int j=1; j<M+1; j++)
             {
                     cout<<grid_array[i][j];
             }
             cout<<"\n";
     }
     cout<<"\n";
}


//********************************************************************
//
// Color Method
//
// This method searches the grid for a '*' character, and if found
// calls the recursive method Mark to color the component.  When done
// coloring, calls tally method and increments c.
//
//*******************************************************************
void Grid::Color()
{
     //Nested for loops scan each element of the grid
     for(int i=1; i<N+2; i++)
     {
             for(int j=1; j<M+2; j++)
             {
                     if(grid_array[i][j] == '*')
                     {
                                         n = 0; //Initialize n to 0 before
                                                //each call to Mark to reset
                                                //component size
                                         Mark(n, i, j);
                                         Tally(n);
                                         c++;
                     }
             }
     }
}


//********************************************************************
//
// Mark Method
//
// This method recursively assigns a color c to an element and any
// connected to it by searching north, east, south, and west in 
// relation to element [i][j].  Also keeps track of the size.
//
// Value Parameters
//------------------
// i                int              row number
// j                int              column number
//
// Reference Parameters
//----------------------
// *n                int             points to variable that holds
//                                   the size of the components
//
//*******************************************************************
void Grid::Mark(int &n, int i, int j)
{
  grid_array[i][j]=color_array[c%52]; //Replace '*' with a color tag
  n++; //Increase size for this component
  
  if(grid_array[i-1][j] == '*') //Scan north
  {                      
                         Mark(n, i-1, j);
  }
  
  if(grid_array[i][j-1] == '*') //Scan west
  {
                         Mark(n, i, j-1);
  }
  
  if(grid_array[i][j+1] == '*') //Scan east
  {
                         Mark(n, i, j+1);
  }
  
  if(grid_array[i+1][j] == '*') //Scan south
  {
                         Mark(n, i+1, j);
  }                 
}


//********************************************************************
//
// Tally method
//
// This method increments the element of sizes at the count'th index.
//
// Value Parameters
//------------------
// count            int              The component size
//
//*******************************************************************
void Grid::Tally(int count)
{
     sizes_array[count]++;
}


//********************************************************************
//
// numComponents Method
//
// This method outputs to screen the total number of connected components
// and then breaks down the number of components for each size.
//
//*******************************************************************
void Grid::numComponents()
{
     cout<<"There are "<<c<<" connected components.\n\n";
     
     for(int i=N*M; i>0; i--) //Start at last element
     {
             if(!(sizes_array[i] == 0)) //Display size (index) and number
             {                          //components for that size if not empty
                  cout<<sizes_array[i]<<" component(s) of size "<<i<<endl;
             }
     }

     cout<<"\n"<<endl;

}

