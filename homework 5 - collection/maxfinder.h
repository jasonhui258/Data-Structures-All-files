// Author: Sean Davis
#ifndef maxfinderH
#define maxfinderH
#include "NetDriver.h"

class MaxFinder
{
public:
  MaxFinder(const Computer *computers, int numComputers, int numTerminals);
  int calcMaxFlow(Edge *edges, int numEdges);
}; // class MaxFinder




#endif
