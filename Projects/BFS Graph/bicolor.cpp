//#####################################################################
//
// Annie Gorbet
// Data Structures
// Extra Credit Programming Project
// May 2, 2012
// Instructor: Dr. Michael C. Scherger
//
//#####################################################################

#include <queue>
#include <iostream>
#include <Graph.h>

// Function Prototype
bool bfs( Graph G, int V, int s=0 );

int main()
{
    // local variables
    int V=-1, E=0;      // no. vertices, no. edges
    int x, y;           // egde vertex pair (x, y)
    
    // get |V| and |E| and create graph, then add each edge, then perform
    // the bfs (coloring function), until |V| = 0
    cin>>V;
    do
    {
        cin>>E;
        Graph MyGraph(V);
        for( int i = 0; i < E; i++)
        {
           cin >> x >> y;
           MyGraph.addEdge(x, y);
        }

        if( bfs( MyGraph, V ) )
           cout << "BICOLORABLE" << endl;
        else
           cout << "NOT BICOLORABLE" << endl;

        cin>>V;
    }while( V!=0 );

    return(0);
}

//#####################################################################
//
// Breadth-First Search Function
//
// This function uses the algorithm for a Breadth-First search to color
// each pair of vertices different colors, if possible.  If this is not
// possible, the function returns false.  If the function completes the
// coloring, then true is returned.
//
// Return Value
// ------------
// bool                True if function completes, false if not
//
// Value Parameters
// ----------------
// V                   int              |V|
// s                   int              source index
// G                   Graph            the graph being colored
//
// Local Variables
// ---------------
// color[V]            string           an array of colors for each vertex
// Q                   queue<int>       a queue of integers
// u                   int              to hold current vertex index
// v                   int              to hold index of vertices adj. to u
//
//######################################################################

bool bfs( Graph G, int V, int s /* = 0 */ )
{
    // local variables
    string color[V];
    queue<int> Q;
    int u, v;

    // initialize all colors to "white"
    for( int i = 0; i < V; i++ )
    {
        color[i] = "white";
    }

    // set source color to "red"
    color[s] = "red";

    // add source to queue
    Q.push( s );

    // while there are values in the queue, compare the color of the vertex 
    // whose index is in the front of the queue to all its adjacent vertices
    while( !Q.empty() )
    {
        u = Q.front();
        for( int v = 0; v < V; v++ )
        {
            if( G.isEdge(u, v) )
            {
                // if the adjacent vertex has not been colored already, color
                // it the color of the vertex at the front of the queue is not
                // colored
                if( color[v] == "white" )
                {
                    if( color[u] == "red" )
                        color[v] = "blue";
                    else
                        color[v] = "red";
                    Q.push( v );
                }
                // if it has been colored, if it is the same color as the 
                // vertex at the front of the queue, the graph is not 
                // bicolorable, else continue to the next adj. vertex
                else if( color[v] == color[u] )
                    return( false );
            }
        }
        Q.pop();
    }

    return( true );
}

