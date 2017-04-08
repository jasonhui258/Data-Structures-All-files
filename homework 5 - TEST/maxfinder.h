// Author: Sean Davis
#ifndef maxfinderH
#define maxfinderH
#include "QuadraticProbing.h"
#include <cstring>
#include "NetDriver.h"
#include "Node.h"

class MaxFinder
{
public:

	bool bfs();
	int fordFulkerson();
    Node* source;
    Node** graph;
    int graphsize;
    QuadraticHashTable* hash;
    int numComp, numTerm;
    MaxFinder(const Computer *computers, int numComputers, int numTerminals);
  int calcMaxFlow(Edge *edges, int numEdges);
    
}; // class MaxFinder






#endif
