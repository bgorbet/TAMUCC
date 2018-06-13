Program name: findcc
findcc.cpp: primary source file for the findcc program
Grid.cpp: Grid class source file
Grid.h: Grid class header file
Makefile: includes rules to compile all code and clean up directory
t0.txt: test file
t1.txt: test file
This program solves the component labeling problem using a Grid class which includes member functions that perform the following tasks:
1. 	Open a file (containing the grid) entered using command line arguments
2.	Store the grid in an array of strings (add a ‘#’ border to avoid segmentation fault when searching the grid)
3.	Display the grid to standard output
4.	Find all components and recursively label them with color tags from a lookup table
5.	Display the colored grid to standard output
6.	Compute and display the total connected components, and a breakdown of the sizes of connected components.
Notes:
This program is designed to work for grids of varying sizes, with a maximum of 100 rows.
I did not find any use for the variables high, low, and total and my program functions properly without them, so I removed these.
