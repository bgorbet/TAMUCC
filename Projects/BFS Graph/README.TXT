This program creates a graph according to the input data (number of 
vertices, number of edges, sets of adjacent vertices).  For each graph, it 
determines if it is bicolorable or not bicolorable using a breadth-first 
search. I used the adjacency matrix implementation of the graph because I 
find it easier to understand and use than the adjacency list 
implementation.  I modified the BFS algorithm from class to work with the 
matrix implementation and it appears to work well. Also, instead of 
computing the distance from the source to all reachable vertices, it 
starts at the source, coloring it red, then colors all adjacent vertices 
blue, then visits each of those vertices and colors their adjacent 
vertices red (if they have not already been colored) and so on 
and so forth until the entire graph is colored.  If the coloring function 
(bfs) encounters two adjacent vertices that are the same color, it returns 
false without continuing.  If the function completely colors the graph, 
then the graph is bicolorable.

CONTENTS:
bicolor.cpp    (the driver program)
Graph.h        (the Graph class)
Makefile       
input.txt      (a file with sample input)
README.TXT

The graph class I used is a modified version of the graph class found at 
www.algolist.net/Data_structures/Graph/Internal_representation


