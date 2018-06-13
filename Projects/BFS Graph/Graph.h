//#####################################################################
//
// Annie Gorbet
// Data Structures
// Extra Credit Programming Project
// May 2, 2012
// Instructor: Dr. Michael C. Scherger
//
//#####################################################################

#ifndef _MODULE_GRAPH_
#define _MODULE_GRAPH_
using namespace std;

// Graph Class definition
class Graph 
{
  private:
     
      // Graph attributes
      bool** adjacencyMatrix;
      int vertexCount;

  public:

      // Graph methods
      Graph();
      Graph(int vertexCount);
      Graph( const Graph &otherGraph );
      ~Graph();
      void clear();
      void addEdge(int i, int j);
      void removeEdge(int i, int j);
      bool isEdge(int i, int j);
};

//#####################################################################
//
// Default Constructor
//
//#####################################################################

Graph::Graph()
{
    adjacencyMatrix = NULL;
    vertexCount = 0;
}

//#####################################################################
//
// Constructor
//
//#####################################################################

Graph::Graph(int vertexCount)
{
    this->vertexCount = vertexCount;
    adjacencyMatrix = new bool*[vertexCount];
    for (int i = 0; i < vertexCount; i++) 
    {
        adjacencyMatrix[i] = new bool[vertexCount];
        for (int j = 0; j < vertexCount; j++)
            adjacencyMatrix[i][j] = false;
    }
}

//#####################################################################
//
// Copy Constructor
//
//#####################################################################
Graph::Graph( const Graph &otherGraph )
{
    vertexCount = otherGraph.vertexCount;
    adjacencyMatrix = new bool*[vertexCount];
    for (int i = 0; i < vertexCount; i++) 
    {
        adjacencyMatrix[i] = new bool[vertexCount];
        for (int j = 0; j < vertexCount; j++)
            adjacencyMatrix[i][j] = otherGraph.adjacencyMatrix[i][j];
    }
}

//#####################################################################
//
// Destructor
// 
//#####################################################################

Graph::~Graph() 
{
    clear();
}

//#####################################################################
// 
// Clear Method
//
//#####################################################################

void Graph::clear()
{
    for ( int i = 0; i < vertexCount; i++ )
        delete[] adjacencyMatrix[i];
    delete[] adjacencyMatrix;
}

//#####################################################################
//
// Add Edge Method
//
//#####################################################################

void Graph::addEdge(int i, int j) 
{
    if (i >= 0 && i < vertexCount && j >= 0 && j < vertexCount) 
    {
        adjacencyMatrix[i][j] = true;
        adjacencyMatrix[j][i] = true;
    }
}

//#####################################################################
//
// Remove Edge Method
//
//#####################################################################

void Graph::removeEdge(int i, int j) 
{
    if (i >= 0 && i < vertexCount && j >= 0 && j < vertexCount) 
    {
        adjacencyMatrix[i][j] = false;
        adjacencyMatrix[j][i] = false;
    }
}

//#####################################################################
//
// Is Edge Method
//
//#####################################################################

bool Graph::isEdge(int i, int j) 
{
    if (i >= 0 && i < vertexCount && j >= 0 && j < vertexCount)
        return adjacencyMatrix[i][j];
    else
        return false;
}

#endif

